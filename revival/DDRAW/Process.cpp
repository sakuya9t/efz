// Process (Process.h).
#include "stdafx.h"
#include "Process.h"
#include <tlhelp32.h>
#include <algorithm>
#include <ctype.h>
#include <string>
#include <string.h>

// FUNCTION: 0x10010f80
Process::Process()
{
    info.dwProcessId = 0;
    info.dwThreadId = 0;
    info.hProcess = NULL;
    info.hThread = NULL;
}

// FUNCTION: 0x10010fb0
void Process::close()
{
    CloseHandle(info.hProcess);
    CloseHandle(info.hThread);
}

// FUNCTION: 0x10010fd0
PROCESS_INFORMATION Process::launch(LPCWSTR path, LPCWSTR arguments, bool position)
{
    STARTUPINFOW startup;
    startup.cb = sizeof(startup);
    startup.lpReserved = NULL;
    startup.lpDesktop = NULL;
    startup.lpTitle = NULL;
    startup.dwFlags = position ? STARTF_USEPOSITION : 0;
    startup.cbReserved2 = 0;
    startup.lpReserved2 = NULL;
    CreateProcessW(path, NULL, NULL, NULL, FALSE, NORMAL_PRIORITY_CLASS, NULL, NULL, &startup, &info);
    return info;
}

// FUNCTION: 0x10011050
PROCESS_INFORMATION Process::open(const wchar_t *name, int length)
{
    PROCESS_INFORMATION process;
    DWORD id = findId(name, length);
    process.hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, id);
    process.dwProcessId = id;
    return process;
}

// FUNCTION: 0x10011140
PROCESS_INFORMATION Process::attach(const wchar_t *name, int length)
{
    PROCESS_INFORMATION process;
    process.dwProcessId = findId(name, length);
    process.hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, process.dwProcessId);
    return process;
}

// FUNCTION: 0x10011080
std::vector<PROCESS_INFORMATION> Process::openAll(const wchar_t *name, int length)
{
    std::vector<PROCESS_INFORMATION> processes;
    std::vector<DWORD> ids = findIds(name, length);
    for (unsigned int i = 0, count = ids.size(); i < count; i++) {
        PROCESS_INFORMATION process;
        process.hProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, ids[i]);
        process.dwProcessId = ids[i];
        processes.push_back(process);
    }
    return processes;
}

// Clears only MAX_PATH bytes of the name.
// FUNCTION: 0x10011170
DWORD Process::findId(const wchar_t *name, int length)
{
    wchar_t lower[MAX_PATH];
    memset(lower, 0, MAX_PATH);
    memcpy(lower, name, length * sizeof(wchar_t));
    std::transform(lower, lower + MAX_PATH, lower, ::tolower);
    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(entry);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot != INVALID_HANDLE_VALUE) {
        Process32FirstW(snapshot, &entry);
        wchar_t exe[MAX_PATH];
        memcpy(exe, entry.szExeFile, sizeof(exe));
        std::transform(exe, exe + MAX_PATH, exe, ::tolower);
        CloseHandle(snapshot);
    }
    return 0;
}

// FUNCTION: 0x10011230
std::vector<DWORD> Process::findIds(const wchar_t *name, int length)
{
    std::vector<DWORD> ids;
    PROCESSENTRY32W entry;
    entry.dwSize = sizeof(entry);
    std::wstring lower;
    lower = name;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE)
        return ids;
    Process32FirstW(snapshot, &entry);
    std::wstring exe;
    exe = entry.szExeFile;
    std::transform(exe.begin(), exe.end(), exe.begin(), ::tolower);
    if (ids.size() == 0)
        CloseHandle(snapshot);
    return ids;
}
