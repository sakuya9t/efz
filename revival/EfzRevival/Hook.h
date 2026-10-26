// Patching efz.exe's code. A Patch remembers the bytes it is about to overwrite, so the
// game's code can be put back: Detours keeps them by address, with the trampolines the
// hooks allocate. Detours.cpp holds Detours' functions, Hook.cpp the hooks and
// g_detours, the registry the hooks use (Game has another for its own patches).
//
// Three kinds of hook (Hook.cpp), each reached by a jump written over the first bytes:
//   replaceFunction: the code jumps to the target, which replaces the game's function;
//   hookCall:        size bytes are replaced by a call to the target;
//   hook:            the target is called with every register saved (pushad, pushfd),
//                    and the bytes it replaced run after it. The target reads the
//                    game's registers and stack from its caller's frame.
#pragma once
#include <winsock2.h>
#include <windows.h>
#include <string.h>
#include <map>

struct Patch {
    // FUNCTION: 0x1000b770
    Patch(void *address_ = 0, int size_ = 0)
    {
        if (size_ > 16)
            throw "Error: code too long";
        address = address_;
        size = size_;
        memcpy(code, address_, size_);
    }

    void *address;              // 0x00
    char code[16];              // 0x04 the bytes at address
    int size;                   // 0x14
};

class Detours {
public:
    Detours();
    ~Detours();
    // Overwrites size bytes at address with bytes, keeping what was there.
    void patch(void *address, int size, const void *bytes, bool keep = true);
    // Puts the bytes back that a patch or hook at address replaced; frees its
    // trampoline.
    void restore(void *address);
    void restoreAll();
    // Records a hook's patch and its trampoline (g_detours only).
    void add(const Patch &patch, void *trampoline);

private:
    std::map<void *, Patch> patches_;       // 0x00
    std::map<void *, void *> trampolines_;  // 0x08
};

// The hooks' registry (Hook.cpp)
extern Detours g_detours;

// Copies size bytes over the game's code at address. False if size isn't positive or
// the page's protection can't be changed.
bool patchCode(void *address, const void *bytes, int size);
void hook(void *address, int size, void *target);
void hookCall(void *address, int size, void *target);
void replaceFunction(void *function, void *target);
