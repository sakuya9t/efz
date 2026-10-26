// The DLL's replay files (EfzReplay.h).
#include "EfzReplay.h"
#include "EfzGame.h"
#include <istream>

// In place of CReplayFile::Read (efz.exe 0x405fb0).
// FUNCTION: 0x1006dfa0
short ReplayFile::read()
{
    if (remaining) {
        remaining -= 2;
        return g_game.readInput(file);
    }
    eof = TRUE;
    return 0;
}

// In place of CReplayFile::Close (efz.exe 0x405f50).
// FUNCTION: 0x1006dfc0
void ReplayFile::close()
{
    g_game.closeReplay(file);
    remaining = 0;
    eof = FALSE;
    file = 0;
}

// In place of CReplayFile::Write (efz.exe 0x406020).
// FUNCTION: 0x1006dff0
void ReplayFile::write(short value)
{
    g_game.writeInput(file, value);
}

// In place of CReplayFile::OpenRead (efz.exe 0x405e90).
// FUNCTION: 0x1006e010
DWORD ReplayFile::openRead(const char *name)
{
    file = g_game.openReplayRead(name);
    file->seekg(0, std::ios::end);
    remaining = (int)file->tellg();
    file->seekg(0, std::ios::beg);
    eof = FALSE;
    return remaining;
}

// In place of CReplayFile::OpenWrite (efz.exe 0x405f00).
// FUNCTION: 0x1006e070
void ReplayFile::openWrite(const char *name)
{
    file = g_game.openReplayWrite(name);
}
