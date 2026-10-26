// The template's DllMain. In efz.exe 4.02 (and not a Revival session) DDRAW.dll fixes
// the game itself from WinMain's start (initVanilla); otherwise the process has to be
// EfzRevival's.
#include "stdafx.h"
#include "EfzFixes.h"
#include "Hook.h"
#include <tlhelp32.h>
#include <boost/algorithm/string/predicate.hpp>

// FUNCTION: 0x1001bb50
static bool isRevivalSession()
{
    return false;
}

// A dword of efz.exe 4.02's data.
// FUNCTION: 0x1001bb60
static bool isVersion402()
{
    DWORD value = *(DWORD *)0x7871f4;
    DWORD expected = 0x4386998f;
    if (memcmp(&expected, &value, sizeof(DWORD)) == 0)
        return true;
    return false;
}

// The fixes, from WinMain's start (0x401016). The window is made here, so WinMain
// skips its own.
// FUNCTION: 0x1001bb90
static void initVanilla()
{
    skipWindowCreation();
    createWindow();
    fixGame();
    fixSounds();
    copyInput();
    fixIkumi();
    hookTimer();
    fixScene();
    hookReplays();
}

// Whether this process's executable is efz.exe.
// FUNCTION: 0x1001bbc0
static bool isEfzProcess()
{
    DWORD id = GetCurrentProcessId();
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, id);
    PROCESSENTRY32W entry;
    if (snapshot) {
        entry.dwSize = sizeof(entry);
        BOOL more = Process32FirstW(snapshot, &entry);
        while (more && entry.th32ProcessID != id)
            more = Process32NextW(snapshot, &entry);
        CloseHandle(snapshot);
    }
    if (boost::algorithm::iequals(entry.szExeFile, L"efz.exe"))
        return true;
    return false;
}

// Whether this process's executable has EfzRevival in its name.
// FUNCTION: 0x1001bc80
static bool isRevivalProcess()
{
    DWORD id = GetCurrentProcessId();
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, id);
    PROCESSENTRY32W entry;
    if (snapshot) {
        entry.dwSize = sizeof(entry);
        BOOL more = Process32FirstW(snapshot, &entry);
        bool found = false;
        while (more) {
            if (entry.th32ProcessID == id) {
                found = true;
                break;
            }
            more = Process32NextW(snapshot, &entry);
        }
        CloseHandle(snapshot);
        if (!found)
            return false;
    }
    if (boost::algorithm::icontains(entry.szExeFile, L"EfzRevival"))
        return true;
    return false;
}

// FUNCTION: 0x1001bd60
static bool isVanilla()
{
    return !isRevivalSession() && isEfzProcess() && isVersion402();
}

// FUNCTION: 0x1001bd90
BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    switch (reason) {
    case DLL_PROCESS_ATTACH:
        if (isVanilla()) {
            hook((void *)0x401016, 6, (void *)initVanilla);
            return TRUE;
        }
        if (!isRevivalProcess()) {
            MessageBoxA(NULL, "Only use DDRAW.dll with EFZ -Memorial- edition, version 4.02",
                "Error", MB_OK);
            TerminateProcess(GetCurrentProcess(), 0);
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}
