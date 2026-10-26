// The DLL's replay files (EfzReplay.cpp, 0x1006dfa0-0x1006e090): EfzRevival.cpp points
// CReplayFile's methods at these, so the game's own replay code reads and writes
// through a C++ stream (Game::openReplayRead/openReplayWrite) that the extended
// replay's trailer and the netplay recording can share. Laid out as CReplayFile.
#pragma once
#include <winsock2.h>
#include <windows.h>
#include <iosfwd>

class ReplayFile {
public:
    // Opens a replay to play back; returns its size.
    DWORD openRead(const char *name);
    void openWrite(const char *name);
    void close();
    // The next input word, or 0 and eof at the end.
    short read();
    void write(short value);

    BOOL eof;                   // 0x0
    std::iostream *file;        // 0x4 CReplayFile's handle
    DWORD remaining;            // 0x8 bytes left to read
};
