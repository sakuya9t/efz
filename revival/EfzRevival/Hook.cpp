// The hooks into efz.exe's code (Hook.h): each allocates an executable trampoline,
// records it with the bytes it replaces in g_detours (which a later hook of the same
// address undoes first), and writes a jump to it, or to the target, over the code.
#include "Hook.h"
#include <stdlib.h>

// GLOBAL: 0x100a0854
Detours g_detours;

// The jump written over the hooked code.
#define JMP 0xe9
#define CALL 0xe8

// The function's own code jumps to target; the trampoline (its first size bytes and a
// jump back) is kept but nothing calls it.
// FUNCTION: 0x1006f7a0
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

// The replaced bytes become a call to target, then the game's code goes on.
// FUNCTION: 0x1006f860
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

// pushad, pushfd, call target, popfd, popad, the replaced bytes, and back.
// FUNCTION: 0x1006f910
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

// FUNCTION: 0x1006fa10
void hook(void *address, int size, void *target)
{
    Patch patch(address, size);
    savingTrampoline(patch, target);
}

// FUNCTION: 0x1006fa30
bool patchCode(void *address, const void *bytes, int size)
{
    if (size <= 0)
        return false;
    DWORD protect;
    BOOL ok = VirtualProtect(address, size, PAGE_READWRITE, &protect);
    memcpy(address, bytes, size);
    return ok && VirtualProtect(address, size, protect, &protect);
}

// FUNCTION: 0x1006faa0
void hookCall(void *address, int size, void *target)
{
    Patch patch(address, size);
    callTrampoline(patch, target);
}

// FUNCTION: 0x1006fac0
void replaceFunction(void *function, void *target)
{
    Patch patch(function, 0);
    redirect(patch, target);
}
