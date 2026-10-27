// Detours: the code patches' registry (Hook.h). Its functions come right after
// Config.cpp's (0x1006a850-0x1006abb0), before dllmain.cpp's.
#include "stdafx.h"
#include "Hook.h"
#include "Log.h"
#include <stdlib.h>

static bool writeCode(void *address, const void *bytes, int size);
static bool readCode(void *buffer, const void *address, int size);

// FUNCTION: 0x1006ab70
Detours::Detours()
{
}

// FUNCTION: 0x1006ab50
Detours::~Detours()
{
}

// FUNCTION: 0x1006aad0
void Detours::patch(void *address, int size, const void *bytes, bool keep)
{
    Patch patch;
    patch.address = address;
    patch.size = size;
    readCode(patch.code, address, size);
    writeCode(address, bytes, size);
    if (keep)
        patches_[address] = patch;
}

// FUNCTION: 0x1006aa60
void Detours::add(const Patch &patch, void *trampoline)
{
    patches_[patch.address] = patch;
    if (trampoline != 0)
        trampolines_[patch.address] = trampoline;
}

// FUNCTION: 0x1006a9a0
void Detours::restore(void *address)
{
    if (patches_.find(address) == patches_.end())
        return;
    Patch patch = patches_[address];
    writeCode(patch.address, patch.code, patch.size);
    if (trampolines_.find(address) != trampolines_.end()) {
        trampolines_.erase(address);
        free(address);
    }
}

// FUNCTION: 0x1006a930
static bool writeCode(void *address, const void *bytes, int size)
{
    if (size <= 0)
        return false;
    DWORD protect;
    BOOL ok = VirtualProtect(address, size, PAGE_READWRITE, &protect);
    memcpy(address, bytes, size);
    return ok && VirtualProtect(address, size, protect, &protect);
}

// The same copy twice: once into the patch, once over the game's code.
// FUNCTION: 0x1006a8c0
static bool readCode(void *buffer, const void *address, int size)
{
    if (size <= 0)
        return false;
    DWORD protect;
    BOOL ok = VirtualProtect(buffer, size, PAGE_READWRITE, &protect);
    memcpy(buffer, address, size);
    return ok && VirtualProtect(buffer, size, protect, &protect);
}

// FUNCTION: 0x1006a850
void Detours::restoreAll()
{
    for (auto entry : patches_)
        restore(entry.second.address);
}

// Unused (only its string is left, the object's one string): keeping more of the game's
// code than a Patch holds.
static void savePatch(Patch &patch, void *address, int size)
{
    if (size > (int)sizeof(patch.code))
        throw "Save too large";
    readCode(patch.code, address, size);
    patch.address = address;
    patch.size = size;
}
