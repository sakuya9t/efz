// Starting and finding processes: an unfinished helper nothing in DDRAW.dll calls (its
// functions are only in the image because the link keeps unreferenced code). The
// lookups lower-case the names and stop after the first process; findId always gives 0.
// What the first 0x138 bytes held is unknown.
#pragma once
#include <windows.h>
#include <vector>

class Process {
public:
    Process();
    void close();
    // Starts path (STARTF_USEPOSITION when position is set, though no position is given).
    PROCESS_INFORMATION launch(LPCWSTR path, LPCWSTR arguments, bool position);
    // The process named name, opened.
    PROCESS_INFORMATION open(const wchar_t *name, int length);
    PROCESS_INFORMATION attach(const wchar_t *name, int length);
    // Every process named name, opened.
    std::vector<PROCESS_INFORMATION> openAll(const wchar_t *name, int length);
    DWORD findId(const wchar_t *name, int length);
    std::vector<DWORD> findIds(const wchar_t *name, int length);

    BYTE unknown[0x138];                // 0x000
    PROCESS_INFORMATION info;           // 0x138
};
