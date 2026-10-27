// Detours: the code patches' registry (Hook.h). Its object comes before Hook.cpp's,
// which holds the hooks and g_detours (as in EfzRevival.dll); the Patch constructor and
// the std::map code it instantiates come with its functions (0x10011d20-0x10015790).
#include "stdafx.h"
#include "Hook.h"
#include <stdlib.h>

// The same copy twice: once into the patch, once over the game's code. Defined after
// their callers (their code follows Detours::restore's).
static bool readCode(void *buffer, const void *address, int size);
static bool writeCode(void *address, const void *bytes, int size);

// FUNCTION: 0x10011d70
Detours::Detours()
{
}

// FUNCTION: 0x10011de0
Detours::~Detours()
{
}

// FUNCTION: 0x10011e00
void Detours::patch(void *address, unsigned int size, const void *bytes, void *trampoline)
{
    if (size > 16)
        throw std::exception("Save too large");
    Patch patch;
    patch.address = address;
    patch.size = size;
    readCode(patch.code, address, size);
    writeCode(address, bytes, size);
    patches_[address] = patch;
    if (trampoline != 0)
        trampolines_[address] = trampoline;
}

// FUNCTION: 0x10011eb0
void Detours::add(const Patch &patch, void *trampoline)
{
    patches_[patch.address] = patch;
    if (trampoline != 0)
        trampolines_[patch.address] = trampoline;
}

// The trampoline is meant to be freed with it; what is freed is the address.
// FUNCTION: 0x10011f20
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

// FUNCTION: 0x10011fd0
static bool writeCode(void *address, const void *bytes, int size)
{
    if (size <= 0)
        return false;
    DWORD protect;
    BOOL ok = VirtualProtect(address, size, PAGE_READWRITE, &protect);
    memcpy(address, bytes, size);
    return ok && VirtualProtect(address, size, protect, &protect);
}

// FUNCTION: 0x10012040
static bool readCode(void *buffer, const void *address, int size)
{
    if (size <= 0)
        return false;
    DWORD protect;
    BOOL ok = VirtualProtect(buffer, size, PAGE_READWRITE, &protect);
    memcpy(buffer, address, size);
    return ok && VirtualProtect(buffer, size, protect, &protect);
}

// FUNCTION: 0x100120b0
void Detours::restoreAll()
{
    for (auto entry : patches_)
        restore(entry.second.address);
}
