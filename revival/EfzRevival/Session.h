// What EfzRevival.dll does in the game: one session object, chosen by the launcher's
// mode (init) or by the game's own mode (EfzRevival.cpp switches to practice or replay
// sessions), receives the game's events through the hooks EfzRevival.cpp installs.
// No RTTI in the DLL: the classes are known from their vtables (0x100903dc: Session,
// then the online and spectator sessions; 0x10090544: practice, replay, tournament).
// Slot names are descriptive; the callers are in EfzRevival.cpp.
#pragma once
#include <windows.h>

class Session {
public:
    virtual ~Session();
    // [1] once, from the first frame of the game (EfzRevival.cpp's deferred setup)
    virtual void start() = 0;
    // [2] every frame, from WinMain's loop (efz.exe 0x401642)
    virtual void update() = 0;
    // [3] a key or joystick button went down (0-255 keys, 0x201+ buttons)
    virtual void keyPressed(int key);
    // [4] CInput::GetInput (efz.exe 0x40d131): a player's input byte, to read or replace
    virtual void input(BYTE *input, int player) = 0;
    // [5] CScene3::Vf2, the fight's update (efz.exe 0x7656a7)
    virtual void fightUpdate(void *frame);
    // [6]-[8] CSound::Play, Stop and SetVolume (efz.exe 0x40de80, 0x40de40, 0x40e5d0)
    virtual void playSound(short id, int arg);
    virtual void stopSound(short id, int arg);
    virtual void setVolume(short volume);
};

// The current session (EfzRevival.cpp)
extern Session *g_session;
