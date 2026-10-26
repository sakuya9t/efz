// Session's default handlers: no key handling, nothing to do in the fight's update,
// and the game's own sound calls passed through. Its constructor is the implicit one
// (a COMDAT, 0x100224c0), and so is its scalar deleting destructor (0x100224d0).
#include "EfzGame.h"     // winsock2.h (Efz.h) before Session.h's windows.h
#include "Session.h"

// FUNCTION: 0x100224c0 ??0Session@@QAE@XZ
// FUNCTION: 0x100224d0 ??_GSession@@UAEPAXI@Z

// FUNCTION: 0x10078900
Session::~Session()
{
}

// FUNCTION: 0x10078910
void Session::keyPressed(int key)
{
}

// FUNCTION: 0x10078920
void Session::fightUpdate(void *frame)
{
}

// FUNCTION: 0x10078930
void Session::playSound(WORD id, int arg)
{
    g_game.playSound(id, arg);
}

// FUNCTION: 0x10078940
void Session::setVolume(WORD id, int volume)
{
    g_game.setSoundVolume(id, volume);
}

// FUNCTION: 0x10078950
void Session::stopSound(WORD id)
{
    g_game.stopSound(id);
}
