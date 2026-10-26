// The practice session (VS PLAYER): pause and frame step, save/load state, recording
// and replaying the dummy's inputs, input delay, box display, game speed. The launcher
// starts it for local play (mode 2); EfzRevival.cpp also switches to it.
#pragma once
#include "../EfzRevivalLauncher/Config.h"  // boost.asio's winsock2.h before windows.h
#include <deque>
#include <queue>
#include <string>
#include <vector>
#include "Session.h"
#include "Efz.h"
#include "Music.h"
#include "GameState.h"

// When a recording or replay begins: at once, or when the dummy next does something.
enum StartCondition : char {
    START_NOW,
    START_WAKE_UP,
    START_TECH,
    START_GUARD,
    START_RECOIL_GUARD,     // replays guard with a recoil guard
    START_RANDOM_RG,        // recoil guards half the time
};

// FUNCTION: 0x1002b350 ??E@YAAAW4StartCondition@@AAW40@@Z
inline StartCondition &operator++(StartCondition &condition)
{
    switch (condition) {
    case START_NOW:
        condition = START_WAKE_UP;
        break;
    case START_WAKE_UP:
        condition = START_TECH;
        break;
    case START_TECH:
        condition = START_GUARD;
        break;
    case START_GUARD:
        condition = START_RECOIL_GUARD;
        break;
    case START_RECOIL_GUARD:
        condition = START_RANDOM_RG;
        break;
    case START_RANDOM_RG:
        condition = START_NOW;
        break;
    default:
        condition = START_NOW;
        break;
    }
    return condition;
}

// Which buffer a replay plays: the selected one, or a random non-empty one.
enum ReplayChoice : char {
    REPLAY_FIXED,
    REPLAY_RANDOM,
};

enum RecorderState : char {
    RECORDER_IDLE,
    RECORDER_RECORDING,
    RECORDER_RECORD_WAIT,   // records once the start condition holds
    RECORDER_REPLAYING,
    RECORDER_REPLAY_WAIT,   // replays once the start condition holds
};

// One player's inputs: recorded into one of the buffers (1-5) and replayed from one
// (or a random non-empty one), delayed by some frames, and kept for the input
// display. 0x5c bytes.
class Recorder {
public:
    Recorder(int player);
    ~Recorder();

    void input(BYTE *input);
    void reset();
    void checkStart();
    void stop();
    void toggleRecord();
    void toggleReplay();
    void toggleRandom();
    void nextStartCondition();
    void setBuffer(unsigned int buffer);
    void setDelay(int frames);
    unsigned int delay();
    void onSaveState();
    void onLoadState();

    std::wstring stateName();
    std::wstring startConditionName();
    std::wstring recordBufferName();
    std::wstring replayBufferName();

    std::vector<BYTE> history_;             // 0x00 every input, for the input display

private:
    void startRecord();
    void stopRecord();
    void startReplay();
    void stopReplay();
    int randomBuffer();
    void setRecoilGuard(bool enable);
    BYTE guardInput(int player);

    int player_;                            // 0x0c
    int unknown10_[4];                      // 0x10
    RecorderState state_;                   // 0x20
    ReplayChoice random_;                   // 0x21
    StartCondition start_;                  // 0x22
    std::deque<BYTE>::const_iterator replayPos_;  // 0x24
    int replayBuffer_;                      // 0x30
    int recordBuffer_;                      // 0x34
    std::vector<std::deque<BYTE> > buffers_;  // 0x38 10 of them, 1-5 used
    int delay_;                             // 0x44 frames
    std::queue<BYTE> delayed_;              // 0x48 3 bytes a frame
};

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
    std::vector<int> unknown5c_;            // 0x5c
    std::vector<int> unknown68_;            // 0x68
    int inputDelay_;                        // 0x74
    std::queue<BYTE> unknown78_[2];         // 0x78
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
