// The hooks into efz.exe's code (Hook.h): each allocates an executable trampoline,
// records it with the bytes it replaces in g_detours (which a later hook of the same
// address undoes first), and writes a jump to it, or to the target, over the code.
// Detours, the registry, is here too: its functions and their std::map code come
// first in the object (0x10011d20-0x10015790), the trampolines after them.
#include "stdafx.h"
#include "Hook.h"
#include <stdlib.h>

// GLOBAL: 0x100b6a80
Detours g_detours;

// The jump written over the hooked code.
#define JMP 0xe9
#define CALL 0xe8

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

// FUNCTION: 0x100120b0
void Detours::restoreAll()
{
    for (auto entry : patches_)
        restore(entry.second.address);
}

// FUNCTION: 0x10011eb0
void Detours::add(const Patch &patch, void *trampoline)
{
    patches_[patch.address] = patch;
    if (trampoline != 0)
        trampolines_[patch.address] = trampoline;
}

// pushad, pushfd, call target, popfd, popad, the replaced bytes, and back.
// FUNCTION: 0x100157c0
static void savingTrampoline(Patch &patch, void *target)
{
    g_detours.restore(patch.address);
    DWORD protect;
    VirtualProtect(patch.address, patch.size, PAGE_EXECUTE_READWRITE, &protect);
    char *trampoline = (char *)malloc(patch.size + 14);
    if (!trampoline)
        throw "Trampoline malloc failed";
    VirtualProtect(trampoline, patch.size + 14, PAGE_EXECUTE_READWRITE, &protect);
    int at = 0;
    trampoline[at++] = 0x60;    // pushad
    trampoline[at++] = 0x9c;    // pushfd
    trampoline[at++] = CALL;
    *(int *)(trampoline + at) = (int)target - (int)(trampoline + at) - 4;
    at += 4;
    trampoline[at++] = 0x9d;    // popfd
    trampoline[at++] = 0x61;    // popad
    memcpy(trampoline + at, patch.code, patch.size);
    at += patch.size;
    trampoline[at++] = JMP;
    *(int *)(trampoline + at) = (int)patch.address + patch.size - (int)(trampoline + at) - 4;
    g_detours.add(patch, trampoline);
    char jump[5];
    jump[0] = JMP;
    *(int *)(jump + 1) = (int)trampoline - (int)patch.address - 5;
    memcpy(patch.address, jump, 5);
    if (patch.size > 5) {
        for (int i = 5; i < patch.size; i++)
            ((char *)patch.address)[i] = 0x90;
    }
}

// FUNCTION: 0x10015790
void hook(void *address, int size, void *target)
{
    Patch patch(address, size);
    savingTrampoline(patch, target);
}

// savingTrampoline's, reached through a short jump to a jump offset bytes away.
// FUNCTION: 0x100158f0
static void shortTrampoline(Patch &patch, void *target, char offset)
{
    g_detours.restore(patch.address);
    DWORD protect;
    VirtualProtect(patch.address, patch.size, PAGE_EXECUTE_READWRITE, &protect);
    char *trampoline = (char *)malloc(patch.size + 14);
    if (!trampoline)
        throw "Trampoline malloc failed";
    VirtualProtect(trampoline, patch.size + 14, PAGE_EXECUTE_READWRITE, &protect);
    int at = 0;
    trampoline[at++] = 0x60;    // pushad
    trampoline[at++] = 0x9c;    // pushfd
    trampoline[at++] = CALL;
    *(int *)(trampoline + at) = (int)target - (int)(trampoline + at) - 4;
    at += 4;
    trampoline[at++] = 0x9d;    // popfd
    trampoline[at++] = 0x61;    // popad
    memcpy(trampoline + at, patch.code, patch.size);
    at += patch.size;
    trampoline[at++] = JMP;
    *(int *)(trampoline + at) = (int)patch.address + patch.size - (int)(trampoline + at) - 4;
    g_detours.add(patch, trampoline);
    char shortJump[2];
    shortJump[0] = (char)0xeb;
    shortJump[1] = offset - (char)(int)patch.address - 2;
    memcpy(patch.address, shortJump, 2);
    char *jumpAt = (char *)patch.address + 2 + shortJump[1];
    if (patch.size > 2) {
        for (int i = 2; i < patch.size; i++)
            ((char *)patch.address)[i] = 0x90;
    }
    VirtualProtect(jumpAt, 5, PAGE_EXECUTE_READWRITE, &protect);
    char jump[5];
    jump[0] = JMP;
    *(int *)(jump + 1) = (int)trampoline - (int)jumpAt - 5;
    memcpy(jumpAt, jump, 5);
}

// FUNCTION: 0x100158c0
void hookShort(void *address, int size, void *target, char offset)
{
    Patch patch(address, size);
    shortTrampoline(patch, target, offset);
}

// pushad, esi = esp + offset, *variable = esi, popad, the replaced bytes, and back.
// FUNCTION: 0x10015a20
void saveStack(Patch &patch, int offset, void *variable)
{
    g_detours.restore(patch.address);
    DWORD protect;
    VirtualProtect(patch.address, patch.size, PAGE_EXECUTE_READWRITE, &protect);
    char *trampoline = (char *)malloc(patch.size + 22);
    if (!trampoline)
        throw "Trampoline malloc failed";
    VirtualProtect(trampoline, patch.size + 22, PAGE_EXECUTE_READWRITE, &protect);
    int at = 0;
    trampoline[at++] = 0x60;    // pushad
    char code[15] = {
        (char)0x89, (char)0xe6,             // mov esi, esp
        (char)0x81, (char)0xc6, 0, 0, 0, 0, // add esi, offset
        (char)0xbf, 0, 0, 0, 0,             // mov edi, variable
        (char)0x89, 0x37,                   // mov [edi], esi
    };
    *(int *)(code + 4) = offset;
    *(void **)(code + 9) = variable;
    memcpy(trampoline + at, code, sizeof(code));
    at += sizeof(code);
    trampoline[at++] = 0x61;    // popad
    memcpy(trampoline + at, patch.code, patch.size);
    at += patch.size;
    trampoline[at++] = JMP;
    *(int *)(trampoline + at) = (int)patch.address + patch.size - (int)(trampoline + at) - 4;
    g_detours.add(patch, trampoline);
    char jump[5];
    jump[0] = JMP;
    *(int *)(jump + 1) = (int)trampoline - (int)patch.address - 5;
    memcpy(patch.address, jump, 5);
}

// The replaced bytes become a call to target, then the game's code goes on.
// FUNCTION: 0x10015ba0
static void callTrampoline(Patch &patch, void *target)
{
    g_detours.restore(patch.address);
    DWORD protect;
    VirtualProtect(patch.address, patch.size, PAGE_EXECUTE_READWRITE, &protect);
    char *trampoline = (char *)malloc(10);
    if (!trampoline)
        throw "Trampoline malloc failed";
    VirtualProtect(trampoline, 10, PAGE_EXECUTE_READWRITE, &protect);
    int at = 0;
    trampoline[at++] = CALL;
    *(int *)(trampoline + at) = (int)target - (int)(trampoline + at) - 4;
    at += 4;
    trampoline[at++] = JMP;
    *(int *)(trampoline + at) = (int)patch.address + patch.size - (int)(trampoline + at) - 4;
    g_detours.add(patch, trampoline);
    char jump[5];
    jump[0] = JMP;
    *(int *)(jump + 1) = (int)trampoline - (int)patch.address - 5;
    memcpy(patch.address, jump, 5);
}

// The only use (EfzFixes.cpp) is specialised into it: 0x10015b20 hooks 0x40c72e.
// FUNCTION: 0x10015b20
void hookCall(void *address, int size, void *target)
{
    Patch patch(address, size);
    callTrampoline(patch, target);
}

// A call to target, then the replaced bytes but the first two, and back.
// FUNCTION: 0x10015c50
static void callAfterTrampoline(Patch &patch, void *target)
{
    g_detours.restore(patch.address);
    DWORD protect;
    VirtualProtect(patch.address, patch.size, PAGE_EXECUTE_READWRITE, &protect);
    char *trampoline = (char *)malloc(patch.size + 8);
    if (!trampoline)
        throw "Trampoline malloc failed";
    VirtualProtect(trampoline, 10, PAGE_EXECUTE_READWRITE, &protect);
    int at = 0;
    trampoline[at++] = CALL;
    *(int *)(trampoline + at) = (int)target - (int)(trampoline + at) - 4;
    at += 4;
    memcpy(trampoline + at, patch.code + 2, patch.size - 2);
    at += patch.size - 2;
    trampoline[at++] = JMP;
    *(int *)(trampoline + at) = (int)patch.address + patch.size - (int)(trampoline + at) - 4;
    g_detours.add(patch, trampoline);
    char jump[5];
    jump[0] = JMP;
    *(int *)(jump + 1) = (int)trampoline - (int)patch.address - 5;
    memcpy(patch.address, jump, 5);
}

// FUNCTION: 0x10015b50
void hookCallAfter(void *address, int size, void *target)
{
    Patch patch(address, size);
    callAfterTrampoline(patch, target);
}

// The function's own code jumps to target; the trampoline (its first size bytes and a
// jump back) is kept but nothing calls it.
// FUNCTION: 0x10015d20
static void redirect(Patch &patch, void *target)
{
    g_detours.restore(patch.address);
    DWORD protect;
    VirtualProtect(patch.address, patch.size + 5, PAGE_EXECUTE_READWRITE, &protect);
    char *trampoline = (char *)malloc(patch.size + 5);
    if (!trampoline)
        throw "Trampoline malloc failed";
    VirtualProtect(trampoline, patch.size + 5, PAGE_EXECUTE_READWRITE, &protect);
    int at = 0;
    memcpy(trampoline + at, patch.code, patch.size);
    at += patch.size;
    trampoline[at++] = JMP;
    *(int *)(trampoline + at) = (int)patch.address + patch.size - (int)(trampoline + at) - 4;
    g_detours.add(patch, trampoline);
    char jump[5];
    jump[0] = JMP;
    *(int *)(jump + 1) = (int)target - (int)patch.address - 5;
    memcpy(patch.address, jump, 5);
}

// FUNCTION: 0x10015b70
void replaceFunction(void *function, void *target)
{
    Patch patch(function, 0);
    redirect(patch, target);
}

// FUNCTION: 0x10015de0
bool patchCode(void *address, const void *bytes, int size)
{
    if (size <= 0)
        return false;
    DWORD protect;
    BOOL ok = VirtualProtect(address, size, PAGE_READWRITE, &protect);
    memcpy(address, bytes, size);
    return ok && VirtualProtect(address, size, protect, &protect);
}
