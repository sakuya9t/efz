// The arena that everything allocated with new lives in, so that a pointer the game
// stores in 32 bits can be an offset into it (port/guest.h).
//
// One address range is reserved at startup and used from its start upwards. Blocks
// carry boundary tags, so a freed block merges with free neighbours; free blocks are
// kept in lists by power-of-two size and the first that fits is split. The same
// sequence of allocations gives the same offsets on every platform, and new memory is
// zeroed, so what the game reads from a block it never wrote is always the same.
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atomic>
#include <new>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#else
#include <sys/mman.h>
#endif

#include "guest.h"

namespace efz {

char* g_arena;
uintptr_t g_arenaSize;
char* g_stack;

namespace {

const uintptr_t kReserve = (uintptr_t)2 << 30;
// Handle 0 is NULL, and no handle is below this.
const uintptr_t kStart = 0x10000;
const uintptr_t kAlign = 16;
const int kClasses = 40;

// A block: its size and whether it is used, and the size of the block below it, so it
// can find both neighbours. Free blocks also hold their list links after the header.
struct Block {
    uintptr_t prevSize;
    uintptr_t size; // header included; bit 0: in use
    Block* next;
    Block* prev;
};
const uintptr_t kHeader = 2 * sizeof(uintptr_t);
const uintptr_t kMin = (sizeof(Block) + kAlign - 1) & ~(kAlign - 1);

// Taken by everything that changes the free lists. The audio thread doesn't allocate,
// so it is almost never contended.
std::atomic_flag g_lock = ATOMIC_FLAG_INIT;

struct Guard {
    Guard()
    {
        while (g_lock.test_and_set(std::memory_order_acquire)) {
        }
    }
    ~Guard() { g_lock.clear(std::memory_order_release); }
};
Block* g_free[kClasses];
uintptr_t g_top;       // offset of the first byte never handed out
uintptr_t g_committed; // offset up to which memory is usable
Block* g_last;         // the highest block, below g_top

uintptr_t SizeOf(Block* b) { return b->size & ~(uintptr_t)1; }
bool Used(Block* b) { return b->size & 1; }
Block* Above(Block* b) { return (Block*)((char*)b + SizeOf(b)); }
Block* Below(Block* b) { return (Block*)((char*)b - b->prevSize); }

int ClassOf(uintptr_t size)
{
    int c = 0;
    while (c < kClasses - 1 && ((uintptr_t)2 << c) * kAlign <= size)
        c++;
    return c;
}

void Link(Block* b)
{
    int c = ClassOf(SizeOf(b));
    b->prev = nullptr;
    b->next = g_free[c];
    if (b->next)
        b->next->prev = b;
    g_free[c] = b;
}

void Unlink(Block* b)
{
    if (b->prev)
        b->prev->next = b->next;
    else
        g_free[ClassOf(SizeOf(b))] = b->next;
    if (b->next)
        b->next->prev = b->prev;
}

[[noreturn]] void OutOfMemory(uintptr_t size)
{
    fprintf(stderr, "efz: the arena has no room for %llu more bytes\n",
            (unsigned long long)size);
    abort();
}

void Reserve()
{
#ifdef _WIN32
    g_arena = (char*)VirtualAlloc(nullptr, kReserve, MEM_RESERVE, PAGE_NOACCESS);
#else
    void* p = mmap(nullptr, kReserve, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    g_arena = p == MAP_FAILED ? nullptr : (char*)p;
#endif
    if (!g_arena) {
        fprintf(stderr, "efz: cannot reserve the arena\n");
        abort();
    }
    g_arenaSize = kReserve;
    g_top = kStart;
    g_committed = kStart;
}

// Makes [g_top, g_top + size) usable.
void Grow(uintptr_t size)
{
    if (g_top + size > kReserve)
        OutOfMemory(size);
#ifdef _WIN32
    const uintptr_t step = (uintptr_t)1 << 22;
    if (g_top + size > g_committed) {
        uintptr_t end = (g_top + size + step - 1) & ~(step - 1);
        if (end > kReserve)
            end = kReserve;
        if (!VirtualAlloc(g_arena + g_committed, end - g_committed, MEM_COMMIT,
                          PAGE_READWRITE))
            OutOfMemory(size);
        g_committed = end;
    }
#else
    g_committed = g_top + size;
#endif
}

void* Allocate(size_t request)
{
    Guard guard;
    if (!g_arena)
        Reserve();
    uintptr_t size = (request + kHeader + kAlign - 1) & ~(kAlign - 1);
    if (size < kMin)
        size = kMin;
    Block* b = nullptr;
    for (int c = ClassOf(size); c < kClasses && !b; c++) {
        for (Block* f = g_free[c]; f; f = f->next) {
            if (SizeOf(f) >= size) {
                b = f;
                break;
            }
        }
    }
    if (b) {
        Unlink(b);
        uintptr_t have = SizeOf(b);
        if (have - size >= kMin) {
            Block* rest = (Block*)((char*)b + size);
            rest->prevSize = size;
            rest->size = have - size;
            if (b == g_last)
                g_last = rest;
            else
                Above(rest)->prevSize = rest->size;
            Link(rest);
            have = size;
        }
        b->size = have | 1;
    } else {
        Grow(size);
        b = (Block*)(g_arena + g_top);
        b->prevSize = g_last ? SizeOf(g_last) : 0;
        b->size = size | 1;
        g_last = b;
        g_top += size;
    }
    memset((char*)b + kHeader, 0, SizeOf(b) - kHeader);
    return (char*)b + kHeader;
}

void Free(void* p)
{
    if (!p)
        return;
    Guard guard;
    Block* b = (Block*)((char*)p - kHeader);
    b->size &= ~(uintptr_t)1;
    if (b != g_last && !Used(Above(b))) {
        Block* a = Above(b);
        Unlink(a);
        if (a == g_last)
            g_last = b;
        b->size += SizeOf(a);
    }
    if (b->prevSize && (char*)b - b->prevSize >= g_arena + kStart && !Used(Below(b))) {
        Block* l = Below(b);
        Unlink(l);
        if (b == g_last)
            g_last = l;
        l->size += SizeOf(b);
        b = l;
    }
    if (b != g_last)
        Above(b)->prevSize = SizeOf(b);
    Link(b);
}

} // namespace

void SetStack(void* local)
{
    g_stack = (char*)local + ((uintptr_t)64 << 10) - kStackSize;
}

uint32_t BadHandle(const void* p)
{
    fprintf(stderr, "efz: a pointer outside the arena and the stack (%p) was stored in the "
                    "game's memory\n", p);
    abort();
}

} // namespace efz

void* operator new(size_t size) { return efz::Allocate(size); }
void* operator new[](size_t size) { return efz::Allocate(size); }
void* operator new(size_t size, const std::nothrow_t&) noexcept { return efz::Allocate(size); }
void* operator new[](size_t size, const std::nothrow_t&) noexcept { return efz::Allocate(size); }
void operator delete(void* p) noexcept { efz::Free(p); }
void operator delete[](void* p) noexcept { efz::Free(p); }
void operator delete(void* p, size_t) noexcept { efz::Free(p); }
void operator delete[](void* p, size_t) noexcept { efz::Free(p); }
void operator delete(void* p, const std::nothrow_t&) noexcept { efz::Free(p); }
void operator delete[](void* p, const std::nothrow_t&) noexcept { efz::Free(p); }
