// Session's default handlers: no key handling, nothing to do in the fight's update,
// and the game's own sound calls passed through. Its constructor is the implicit one
// (a COMDAT, 0x100224c0), and so is its scalar deleting destructor (0x100224d0).
#include "stdafx.h"
#include "EfzGame.h"     // winsock2.h (Efz.h) before Session.h's windows.h
#include "Session.h"
// A stand-in: <functional> adds an odd number of symbols to the compiler's count here,
// between ReplaySession.cpp's strings and TournamentSession.cpp's, and nothing to the
// image. The original's count between them was odd too (the tournament session's string
// pairs show it, see docs/revival.md, Strings); what it was is not known.
#include <functional>

// FUNCTION: 0x100224c0 ??0Session@@QAE@XZ
// FUNCTION: 0x100224d0 ??_GSession@@UAEPAXI@Z

// FUNCTION: 0x10078950
void Session::stopSound(WORD id)
{
    g_game.stopSound(id);
}

// FUNCTION: 0x10078940
void Session::setVolume(WORD id, int volume)
{
    g_game.setSoundVolume(id, volume);
}

// FUNCTION: 0x10078930
void Session::playSound(WORD id, int arg)
{
    g_game.playSound(id, arg);
}

// FUNCTION: 0x10078920
void Session::fightUpdate(void *frame)
{
}

// FUNCTION: 0x10078910
void Session::keyPressed(int key)
{
}

// FUNCTION: 0x10078900
Session::~Session()
{
}
