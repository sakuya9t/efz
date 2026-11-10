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
//
// A build of several games in one process (EFZ_MULTI_INSTANCE, the headless library of
// port/headless/) gives each game an arena of its own: g_arena and g_stack are then the
// calling thread's, set to the game it is running (BindArena), and the game's state
// outside its objects (rand's, the clock's) is kept in its arena too (Globals), so that
// copying an arena copies the whole game.
#ifndef EFZ_GUEST_H
#define EFZ_GUEST_H

#include <stddef.h>
#include <stdint.h>
#include <type_traits>

#ifdef EFZ_MULTI_INSTANCE
#if defined(__linux__) && defined(__GNUC__)
// The arena's base is read on every pointer the game follows: the static TLS model, not
// a __tls_get_addr call each time. Two pointers fit in what glibc keeps for libraries
// loaded later. Only these: with -ftls-model=initial-exec on everything, libstdc++'s own
// thread-locals (std::call_once's) were bound that way too, and loading the library
// after torch failed ("cannot allocate memory in static TLS block").
#define EFZ_THREAD_LOCAL thread_local __attribute__((tls_model("initial-exec")))
#else
#define EFZ_THREAD_LOCAL thread_local
#endif
#else
#define EFZ_THREAD_LOCAL
#endif

namespace efz {

extern EFZ_THREAD_LOCAL char* g_arena;
extern uintptr_t g_arenaSize;
// The lowest address of the stack window: kStackSize bytes ending a little above
// main's frame (SetStack).
extern EFZ_THREAD_LOCAL char* g_stack;
const uint32_t kStackHandle = 0xf0000000u;
const uintptr_t kStackSize = (uintptr_t)16 << 20;

// Called first thing in main with the address of one of its locals; in a build of
// several games, by each thread before it runs one.
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

// The arena's first 64 KB hold no blocks: no handle is below kArenaStart. The
// allocator keeps its state there (at kHeapState), and a build of several games each
// game's Globals (at kGlobals).
const uintptr_t kArenaStart = 0x10000;
const uintptr_t kHeapState = 0x1000;
const uintptr_t kGlobals = 0x2000;

#ifdef EFZ_MULTI_INSTANCE
// What a game has outside its objects, kept in its arena.
struct Globals {
    uint32_t holdrand;   // rand()'s state (x87.cpp)
    uint32_t clock;      // timeGetTime's, in milliseconds
    uint8_t input[2];    // what CInput::GetInput gives each player
    uint8_t drawing;     // whether pictures are drawn (sprites decoded, blitters run)
    uint8_t quit;        // the game asked to close: WM_CLOSE, or a MessageBox
    uint32_t root[16];   // the platform's own handles: what WinMain kept in globals
    float damageTaken[2]; // a scale on the damage each player takes, set by the headless
                          // env (efz_env_set_damage_scale) for each step; 0 (an arena as
                          // NewArena makes it) is 1, the game's
};

inline Globals* G()
{
    return (Globals*)(g_arena + kGlobals);
}

// The scale on the damage player `side` takes (CPlayer::DefenseFactor): the game's 1
// unless the headless env set one.
inline double DamageTaken(int side)
{
    float s = G()->damageTaken[side & 1];
    return s > 0 ? (double)s : 1.0;
}

// An arena of its own for another game: reserved, its first 64 KB and heap set up
// empty. NewArena leaves the calling thread's arena as it was.
char* NewArena();
void FreeArena(char* arena);
// Makes `arena` the calling thread's (nullptr: none, so that operator new takes from
// the C library's heap again).
inline void BindArena(char* arena)
{
    g_arena = arena;
}
// The bytes of the bound arena that hold its game: [0, ArenaUsed()). Copying them into
// another arena with LoadArena makes that one the same game.
uintptr_t ArenaUsed();
void LoadArena(const void* bytes, uintptr_t size);
#else
inline double DamageTaken(int) { return 1.0; }
#endif

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
