// Starting efz.exe and injecting EfzRevival.dll into it.
#include "GameProcess.h"
// OBJECT: 0x41aa50 0x41de10
#include <cstdlib>
#include <cstring>
#include <iostream>

// Folded with std::allocator<char>::allocator (0x4364e0).
GameProcess::GameProcess()
{
}

// Folded with std::basic_ios<char>::_Add_vtordisp1 (0x433550).
GameProcess::~GameProcess()
{
}

// FUNCTION: 0x41ca40
bool GameProcess::check()
{
    if (!info_.hProcess) {
        std::cout << "Could not open EFZ.exe, check that it is in the same directory and you "
                     "have the rights to run it.\n";
        return false;
    }
    SIZE_T read;
    char byte;
    if (!ReadProcessMemory(info_.hProcess, (LPCVOID)0x787237, &byte, 1, &read)) {
        std::cout << "Cannot read from the memory. Check user access rights.\n";
        return false;
    }
    DWORD value;
    ReadProcessMemory(info_.hProcess, (LPCVOID)0x7871f4, &value, 4, &read);
    unsigned char expected[4] = { 0x8f, 0x99, 0x86, 0x43 };
    if (memcmp(expected, &value, 4) != 0) {
        std::cout << "Efz.exe is not EFZ Memorial 4.02\n";
        return false;
    }
    return true;
}

// FUNCTION: 0x41d8f0
void GameProcess::inject(const std::string &exe, const std::string &dll, const void *data, SIZE_T size)
{
    int wait;
    SIZE_T written;
    DWORD module;
    const char *dllName = dll.c_str();
    launch(exe, CREATE_SUSPENDED);
    if (!check()) {
        close();
        system("pause");
        return;
    }
    LPVOID path = VirtualAllocEx(info_.hProcess, NULL, dll.size(), MEM_COMMIT, PAGE_READWRITE);
    if (!path) {
        TerminateProcess(info_.hProcess, 9);
        std::cout << "The loader could not allocate memory in EFZ.\n";
        std::cin >> wait;
        return;
    }
    WriteProcessMemory(info_.hProcess, path, dllName, dll.size(), &written);
    HANDLE thread = CreateRemoteThread(info_.hProcess, NULL, 0,
        (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleW(L"Kernel32"), "LoadLibraryA"),
        path, 0, NULL);
    if (!thread) {
        TerminateProcess(info_.hProcess, 9);
        std::cout << "Could not create a remote thread\n";
        std::cin >> wait;
        return;
    }
    WaitForSingleObject(thread, INFINITE);
    GetExitCodeThread(thread, &module);
    CloseHandle(thread);
    VirtualFreeEx(info_.hProcess, path, 0, MEM_RELEASE);
    if (!module) {
        TerminateProcess(info_.hProcess, 9);
        std::cout << "EFZ could not load EfzRevival.dll. Make sure that it is in the same "
                     "directory as the EFZ executable.\n";
        std::cin >> wait;
        return;
    }
    HMODULE local = LoadLibraryA(dllName);
    if (!local) {
        TerminateProcess(info_.hProcess, 9);
        std::cout << "The loader could not load EfzRevival.dll. Make sure that they are in the "
                     "same directory.\n";
        std::cin >> wait;
        return;
    }
    DWORD init = (DWORD)GetProcAddress(local, "init") - (DWORD)local;
    LPVOID args = VirtualAllocEx(info_.hProcess, NULL, size, MEM_COMMIT, PAGE_READWRITE);
    if (!args) {
        TerminateProcess(info_.hProcess, 9);
        std::cout << "The loader could not allocate memory in EFZ.\n";
        std::cin >> wait;
        return;
    }
    WriteProcessMemory(info_.hProcess, args, data, size, &written);
    DWORD start = module + init;
    HANDLE initThread = CreateRemoteThread(info_.hProcess, NULL, 0,
        (LPTHREAD_START_ROUTINE)start, args, 0, NULL);
    if (!initThread) {
        TerminateProcess(info_.hProcess, 9);
        std::cout << "Could not create a remote thread for the dll\n";
        std::cin >> wait;
        return;
    }
    WaitForSingleObject(initThread, 5000);
    VirtualFreeEx(info_.hProcess, args, 0, MEM_RELEASE);
    CloseHandle(initThread);
    FreeLibrary(local);
    HMODULE ddraw = GetModuleHandleA("DDRAW");
    if (ddraw)
        FreeLibrary(ddraw);
    std::cout << "Successfully loaded\n";
}
// FUNCTION: 0x41cb40
void GameProcess::close()
{
    TerminateProcess(info_.hProcess, 0);
}

// FUNCTION: 0x41d8b0
PROCESS_INFORMATION GameProcess::getProcessInfo()
{
    return info_;
}

// FUNCTION: 0x41db60
void GameProcess::launch(std::string exe, DWORD flags)
{
    STARTUPINFOA startup;
    ZeroMemory(&startup, sizeof(startup));
    startup.cb = sizeof(startup);
    startup.lpReserved = NULL;
    startup.lpDesktop = NULL;
    startup.lpTitle = NULL;
    startup.dwFlags = 0;
    startup.cbReserved2 = 0;
    startup.lpReserved2 = NULL;
    ZeroMemory(&info_, sizeof(info_));
    CreateProcessA(exe.c_str(), NULL, NULL, NULL, FALSE, flags, NULL, NULL, &startup, &info_);
}
