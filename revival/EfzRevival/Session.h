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
    // [5] CScene3::Vf2, the fight's update (efz.exe 0x7656a7). `frame` is the keyboard
    // state the fight reads (256 DIK_* bytes, 0x80 held): the sessions write F4-F8 and
    // Esc there (spectator, replay), or clear F1-F10 and hold back Esc (tournament).
    virtual void fightUpdate(void *frame);
    // [6]-[8] the hooks of CSound::Play, SetVolume and Stop (efz.exe 0x40de80, 0x40e5d0,
    // 0x40de40; EfzRevival.cpp 0x1006eb50 calls [7], 0x1006eb30 [8]). The defaults
    // (Session.cpp) call the game's own.
    virtual void playSound(WORD id, int arg);
    virtual void setVolume(WORD id, int volume);
    virtual void stopSound(WORD id);
};

// The current session (EfzRevival.cpp)
extern Session *g_session;
