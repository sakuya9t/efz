// Patching efz.exe's code: DDRAW.dll's copy of the hooks EfzRevival.dll also has
// (revival/EfzRevival/Hook.h), a month older. A Patch remembers the bytes it is about
// to overwrite, so the game's code can be put back: Detours keeps them by address,
// with the trampolines the hooks allocate.
//
// The same as EfzRevival.dll's but for Detours::patch, which here takes the
// trampoline to record and refuses more than 16 bytes, and three more kinds of hook
// (hookShort, hookCallAfter, saveStack). Only hook and hookCall are used.
#pragma once
#include <windows.h>
#include <string.h>
#include <map>

struct Patch {
    // FUNCTION: 0x10011d20
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
    // Overwrites size bytes at address with bytes, keeping what was there (and the
    // trampoline, if any, to free with it).
    void patch(void *address, unsigned int size, const void *bytes, void *trampoline);
    // Puts the bytes back that a patch or hook at address replaced.
    void restore(void *address);
    void restoreAll();
    // Records a hook's patch and its trampoline.
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
// target is called with every register saved; the size bytes it replaced run after it.
void hook(void *address, int size, void *target);
// The same where there is no room for a jump: a short jump (2 bytes) goes to offset
// bytes after it, where the jump to the trampoline is written.
void hookShort(void *address, int size, void *target, char offset);
// size bytes are replaced by a call to target.
void hookCall(void *address, int size, void *target);
// A call to target, then all but the first two of the size bytes.
void hookCallAfter(void *address, int size, void *target);
// The function jumps to target, which replaces it.
void replaceFunction(void *function, void *target);
// The replaced code runs after the game's esp + offset is stored at variable.
void saveStack(Patch &patch, int offset, void *variable);
