// 32-bit pointers for a 64-bit build.
//
// The game's structures hold pointers in 32 bits, and its code keeps pointers in ints,
// adds offsets to them and casts them back. The native build keeps that: everything the
// game allocates lives in one arena (port/arena.cpp), and a pointer stored in 32 bits
// is its offset in the arena, a "handle". Handle 0 is NULL. The game also passes the
// addresses of locals around as integers (the fight's collision checks do), so the main
// thread's stack has handles too, from kStackHandle up. src/efz.h marks the pointer
// members and each cast between a pointer and an integer with the macros at the end of
// this file.
#ifndef EFZ_GUEST_H
#define EFZ_GUEST_H

#include <stdint.h>
#include <type_traits>

namespace efz {

extern char* g_arena;
extern uintptr_t g_arenaSize;
// The lowest address of the stack window: kStackSize bytes ending a little above
// main's frame (SetStack).
extern char* g_stack;
const uint32_t kStackHandle = 0xf0000000u;
const uintptr_t kStackSize = (uintptr_t)16 << 20;

// Called first thing in main with the address of one of its locals.
void SetStack(void* local);

// Reports a pointer outside the arena and the stack that the game tried to store, and
// stops.
uint32_t BadHandle(const void* p);

inline char* Ptr(uint32_t h)
{
    if (h < kStackHandle)
        return h ? g_arena + h : nullptr;
    return g_stack + (h - kStackHandle);
}

inline uint32_t Handle(const void* p)
{
    // First: on Windows the main thread's stack lies just above address 0, so the
    // stack window can take it in.
    if (!p)
        return 0;
    uintptr_t d = (uintptr_t)((const char*)p - g_arena);
    if (d < g_arenaSize)
        return (uint32_t)d;
    uintptr_t s = (uintptr_t)((const char*)p - g_stack);
    if (s < kStackSize)
        return kStackHandle + (uint32_t)s;
    return BadHandle(p);
}

// A pointer field of the game's structures: 4 bytes, used like a T*.
template <class T>
struct Ptr32 {
    uint32_t h;

    Ptr32() = default;
    Ptr32(T* p) : h(Handle(p)) {}
    operator T*() const { return (T*)Ptr(h); }
    T* operator->() const { return (T*)Ptr(h); }
    Ptr32& operator=(T* p)
    {
        h = Handle(p);
        return *this;
    }
    // Casts as a T* has them: to another pointer type (through T*, so that a cast to a
    // base class adjusts the pointer as it would), and to an integer, which gives the
    // handle (as TOINT does).
    template <class U>
    explicit operator U*() const { return (U*)(T*)Ptr(h); }
    template <class I, class = typename std::enable_if<std::is_integral<I>::value &&
                                                       !std::is_same<I, bool>::value>::type>
    explicit operator I() const { return (I)h; }
};

} // namespace efz

#define PTR32(T) ::efz::Ptr32<T>
#define PTRAT(addr) (::efz::Ptr(*(uint32_t*)(addr)))
#define PTRSET(addr, v) (*(uint32_t*)(addr) = ::efz::Handle(v))
#define TOPTR(T, v) ((T)::efz::Ptr((uint32_t)(v)))
#define TOINT(T, p) ((T)::efz::Handle(p))

#endif
