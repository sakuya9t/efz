// The practice session (VS PLAYER): pause and frame step, save/load state, recording
// and replaying the dummy's inputs, input delay, box display, game speed. The launcher
// starts it for local play (mode 2); EfzRevival.cpp also switches to it.
#pragma once
#include "Config.h"
#include <deque>
#include <list>
#include <queue>
#include <string>
#include <vector>
#include "Session.h"
#include "Efz.h"
#include "Playlist.h"
#include "GameState.h"

class MusicPlayer;   // Music.h
// Recorder.h comes after the class: the original's object instantiates the members of
// this class's containers (std::vector<Recorder>'s push_back, destructor and
// operator[]) before those of Recorder's (std::vector<char>::size), so Recorder's
// definition, and its containers, came later in the source than this class's.
class Recorder;

// 0x2b0 bytes
class PracticeSession : public Session {
public:
    PracticeSession();
    ~PracticeSession();
    void start();
    void update();
    void keyPressed(int key);
    void input(BYTE *input, int player);
    void playSound(WORD id, int arg);
    void setVolume(WORD id, int volume);
    void stopSound(WORD id);

private:
    bool isVsPlayer();
    bool isPracticeFight();
    int otherPlayer();
    void setInputDelay(int frames);
    void checkDevices();
    void frame();
    void reset();
    void restoreBindings();
    void saveBindings();
    void toggleCollisionBoxes();
    void toggleHurtBoxes();
    void toggleHitBoxes();
    void showBoxes();
    void drawHud();
    void toggleDisplay();
    void nextStartCondition();
    void togglePause();
    void setBuffer(unsigned int buffer);
    void toggleRandom();
    void restoreState();
    void storeState();
    void toggleRecord();
    void toggleReplay();
    void loadState();
    void saveState();

    KeyBindings bindings_[2];               // 0x04 the game's, while the players are switched
    int dummy_;                             // 0x24 the player whose recorder the keys drive
    std::vector<int>::iterator unknown28_;  // 0x28
    int unknown2c_;                         // 0x2c
    int unknown30_;                         // 0x30
    SaveState saveState_;                   // 0x34
    // Two vectors nothing uses but the constructor and destructor. Their elements are 8
    // bytes with std::list's destructor (the original's ~PracticeSession destroys them
    // through _Destroy_range with a stride of 8, and the element's destructor folds
    // with std::list<linked_streambuf *>'s); what the lists hold is unknown.
    std::vector<std::list<int> > unknown5c_;    // 0x5c
    std::vector<std::list<int> > unknown68_;    // 0x68
    int inputDelay_;                        // 0x74
    std::queue<char> unknown78_[2];         // 0x78
    std::vector<Recorder> recorders_;       // 0xa0
    bool step_;                             // 0xac
    int stepCount_;                         // 0xb0 frames stepped since pausing
    bool paused_;                           // 0xb4
    bool display_;                          // 0xb5
    bool hitBoxes_;                         // 0xb6
    bool hurtBoxes_;                        // 0xb7
    bool collisionBoxes_;                   // 0xb8
    int lastScene_;                         // 0xbc
    double fps_;                            // 0xc0
    Config config_;                         // 0xc8
    MusicPlayer *music_;                    // 0x29c
    Playlist playlist_;                     // 0x2a0
};

#include "Recorder.h"

// Here rather than in InputDisplay.h: the session's header functions have it before
// EfzTimer.h's (setFps, reset), and those before the input display's.
// FUNCTION: 0x10028c40 ?toWString@@YA?AV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@std@@H@Z
inline std::wstring toWString(int value)
{
    wchar_t buffer[64];
    swprintf_s(buffer, 64, L"%d", value);
    return std::wstring(buffer);
}
