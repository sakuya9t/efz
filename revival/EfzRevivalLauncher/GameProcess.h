// efz.exe as the launcher starts it: created suspended, checked to be EFZ Memorial 4.02,
// then EfzRevival.dll is loaded into it (LoadLibraryA in a remote thread) and its export
// init is run, in another remote thread, on a copy of the launcher's arguments. The
// caller resumes the main thread. 0x10 bytes.
#pragma once
#include <windows.h>
#include <string>

class GameProcess {
public:
    GameProcess();
    ~GameProcess();
    // Whether the process exists and is EFZ 4.02 (a value the game holds at 0x7871f4).
    bool check();
    void close();
    PROCESS_INFORMATION getProcessInfo();
    // Starts exe suspended and runs dll's init(data) in it; on failure the process is
    // terminated and the launcher waits for input.
    void inject(const std::string &exe, const std::string &dll, const void *data, SIZE_T size);
    void launch(std::string exe, DWORD flags);

private:
    PROCESS_INFORMATION info_;
};
