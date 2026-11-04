// The arena that everything allocated with new lives in, so that a pointer the game
// stores in 32 bits can be an offset into it (port/guest.h).
//
// One address range is reserved at startup and used from its start upwards. Blocks
// carry boundary tags, so a freed block merges with free neighbours; free blocks are
// kept in lists by power-of-two size and the first that fits is split. The same
// sequence of allocations gives the same offsets on every platform, and new memory is
// zeroed, so what the game reads from a block it never wrote is always the same.
//
// The allocator's state lives in the arena's first 64 KB, and its links are offsets,
// not addresses: the bytes of an arena up to its highest block are the whole heap, and
// copied into another arena they are the same heap there. A build of several games
// (EFZ_MULTI_INSTANCE) saves and restores games that way (LoadArena).
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
#include "log.h"

namespace efz {

EFZ_THREAD_LOCAL char* g_arena;
uintptr_t g_arenaSize;
EFZ_THREAD_LOCAL char* g_stack;

namespace {

const uintptr_t kReserve = (uintptr_t)2 << 30;
const uintptr_t kAlign = 16;
const int kClasses = 40;
// Memory is committed this much at a time (Windows).
const uintptr_t kCommitStep = (uintptr_t)1 << 22;

// A block: its size and whether it is used, and the size of the block below it, so it
// can find both neighbours. Free blocks also hold their list links after the header,
// as offsets in the arena (0: none).
struct Block {
    uintptr_t prevSize;
    uintptr_t size; // header included; bit 0: in use
    uintptr_t next;
    uintptr_t prev;
};
const uintptr_t kHeader = 2 * sizeof(uintptr_t);
const uintptr_t kMin = (sizeof(Block) + kAlign - 1) & ~(kAlign - 1);

// The heap, at kHeapState in the arena.
struct Heap {
    uintptr_t top;       // offset of the first byte never handed out
    uintptr_t committed; // offset up to which memory is usable (the arena's, not the
                         // heap's: LoadArena keeps it)
    uintptr_t last;      // offset of the highest block, below top; 0 none
    uintptr_t free[kClasses];
};

#ifndef EFZ_MULTI_INSTANCE
// Taken by everything that changes the free lists. The audio thread doesn't allocate,
// so it is almost never contended. (With several games, each arena is only ever used
// by the thread running its game.)
std::atomic_flag g_lock = ATOMIC_FLAG_INIT;

struct Guard {
    Guard()
    {
        while (g_lock.test_and_set(std::memory_order_acquire)) {
        }
    }
    ~Guard() { g_lock.clear(std::memory_order_release); }
};
#else
struct Guard {
};
#endif

Heap* H() { return (Heap*)(g_arena + kHeapState); }
Block* At(uintptr_t off) { return off ? (Block*)(g_arena + off) : nullptr; }
uintptr_t Off(Block* b) { return b ? (uintptr_t)((char*)b - g_arena) : 0; }
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
    Heap* h = H();
    int c = ClassOf(SizeOf(b));
    b->prev = 0;
    b->next = h->free[c];
    if (b->next)
        At(b->next)->prev = Off(b);
    h->free[c] = Off(b);
}

void Unlink(Block* b)
{
    if (b->prev)
        At(b->prev)->next = b->next;
    else
        H()->free[ClassOf(SizeOf(b))] = b->next;
    if (b->next)
        At(b->next)->prev = b->prev;
}

// Both through the log, which allocates nothing, to the crash report.
[[noreturn]] void OutOfMemory(uintptr_t size)
{
    Fatal("arena", "the arena has no room for %llu more bytes", (unsigned long long)size);
}

// Makes [0, end) of `arena` usable, end rounded up; `committed` is how far it is.
bool Commit(char* arena, uintptr_t& committed, uintptr_t end)
{
    if (end <= committed)
        return true;
#ifdef _WIN32
    end = (end + kCommitStep - 1) & ~(kCommitStep - 1);
    if (end > kReserve)
        end = kReserve;
    if (!VirtualAlloc(arena + committed, end - committed, MEM_COMMIT, PAGE_READWRITE))
        return false;
#else
    (void)arena;
#endif
    committed = end;
    return true;
}

// A new arena: address space reserved, its first 64 KB usable and the heap empty.
char* Reserve()
{
    char* arena;
#ifdef _WIN32
    arena = (char*)VirtualAlloc(nullptr, kReserve, MEM_RESERVE, PAGE_NOACCESS);
#else
    void* p = mmap(nullptr, kReserve, PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS | MAP_NORESERVE, -1, 0);
    arena = p == MAP_FAILED ? nullptr : (char*)p;
#endif
    if (!arena)
        Fatal("arena", "cannot reserve an arena's %llu bytes of address space",
              (unsigned long long)kReserve);
    g_arenaSize = kReserve;
    uintptr_t committed = 0;
    if (!Commit(arena, committed, kArenaStart))
        OutOfMemory(kArenaStart);
    Heap* h = (Heap*)(arena + kHeapState);
    memset(h, 0, sizeof(Heap));
    h->top = kArenaStart;
    h->committed = committed;
    return arena;
}

// Makes [top, top + size) usable.
void Grow(uintptr_t size)
{
    Heap* h = H();
    if (h->top + size > kReserve || !Commit(g_arena, h->committed, h->top + size))
        OutOfMemory(size);
}

void* Allocate(size_t request)
{
    Guard guard;
#ifndef EFZ_MULTI_INSTANCE
    if (!g_arena)
        g_arena = Reserve();
#endif
    Heap* h = H();
    uintptr_t size = (request + kHeader + kAlign - 1) & ~(kAlign - 1);
    if (size < kMin)
        size = kMin;
    Block* b = nullptr;
    for (int c = ClassOf(size); c < kClasses && !b; c++) {
        for (Block* f = At(h->free[c]); f; f = At(f->next)) {
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
            if (Off(b) == h->last)
                h->last = Off(rest);
            else
                Above(rest)->prevSize = rest->size;
            Link(rest);
            have = size;
        }
        b->size = have | 1;
    } else {
        Grow(size);
        b = (Block*)(g_arena + h->top);
        b->prevSize = h->last ? SizeOf(At(h->last)) : 0;
        b->size = size | 1;
        h->last = Off(b);
        h->top += size;
    }
    memset((char*)b + kHeader, 0, SizeOf(b) - kHeader);
    return (char*)b + kHeader;
}

void Free(void* p)
{
    if (!p)
        return;
    Guard guard;
    Heap* h = H();
    Block* b = (Block*)((char*)p - kHeader);
    b->size &= ~(uintptr_t)1;
    if (Off(b) != h->last && !Used(Above(b))) {
        Block* a = Above(b);
        Unlink(a);
        if (Off(a) == h->last)
            h->last = Off(b);
        b->size += SizeOf(a);
    }
    if (b->prevSize && (char*)b - b->prevSize >= g_arena + kArenaStart && !Used(Below(b))) {
        Block* l = Below(b);
        Unlink(l);
        if (Off(b) == h->last)
            h->last = Off(l);
        l->size += SizeOf(b);
        b = l;
    }
    if (Off(b) != h->last)
        Above(b)->prevSize = SizeOf(b);
    Link(b);
}

#ifdef EFZ_MULTI_INSTANCE
// operator new outside a game (no arena bound: the library's own containers, threads)
// takes from the C library's heap, and operator delete gives back to whichever heap
// the block came from.
void* New(size_t size)
{
    if (g_arena)
        return Allocate(size);
    void* p = malloc(size ? size : 1);
    if (!p)
        throw std::bad_alloc();
    return p;
}

void Delete(void* p)
{
    if (!p)
        return;
    if (g_arena && (uintptr_t)((char*)p - g_arena) < g_arenaSize)
        Free(p);
    else
        free(p);
}
#else
void* New(size_t size)
{
    return Allocate(size);
}

void Delete(void* p)
{
    Free(p);
}
#endif

} // namespace

void SetStack(void* local)
{
    g_stack = (char*)local + ((uintptr_t)64 << 10) - kStackSize;
}

uint32_t BadHandle(const void* p)
{
    Fatal("arena", "a pointer outside the arena and the stack (%p) was stored in the game's "
                   "memory", p);
}

#ifdef EFZ_MULTI_INSTANCE
char* NewArena()
{
    return Reserve();
}

void FreeArena(char* arena)
{
    if (!arena)
        return;
#ifdef _WIN32
    VirtualFree(arena, 0, MEM_RELEASE);
#else
    munmap(arena, kReserve);
#endif
}

uintptr_t ArenaUsed()
{
    return H()->top;
}

void LoadArena(const void* bytes, uintptr_t size)
{
    Heap* h = H();
    uintptr_t committed = h->committed;
    if (size < kArenaStart || size > kReserve || !Commit(g_arena, committed, size))
        OutOfMemory(size);
    memcpy(g_arena, bytes, size);
    H()->committed = committed;
}
#endif

} // namespace efz

void* operator new(size_t size) { return efz::New(size); }
void* operator new[](size_t size) { return efz::New(size); }
void* operator new(size_t size, const std::nothrow_t&) noexcept { return efz::New(size); }
void* operator new[](size_t size, const std::nothrow_t&) noexcept { return efz::New(size); }
void operator delete(void* p) noexcept { efz::Delete(p); }
void operator delete[](void* p) noexcept { efz::Delete(p); }
void operator delete(void* p, size_t) noexcept { efz::Delete(p); }
void operator delete[](void* p, size_t) noexcept { efz::Delete(p); }
void operator delete(void* p, const std::nothrow_t&) noexcept { efz::Delete(p); }
void operator delete[](void* p, const std::nothrow_t&) noexcept { efz::Delete(p); }
