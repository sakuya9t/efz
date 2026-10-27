// A player's input recorder in the practice session (Recorder.cpp, 0x10076b70-0x10077650,
// the object after PracticeSession.cpp's).
#pragma once
#include <deque>
#include <queue>
#include <string>
#include <vector>
#include <windows.h>

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

    void input(char *input);
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

    std::vector<char> history_;             // 0x00 every input, for the input display

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
    std::deque<char>::const_iterator replayPos_;  // 0x24
    int replayBuffer_;                      // 0x30
    int recordBuffer_;                      // 0x34
    std::vector<std::deque<char> > buffers_;  // 0x38 10 of them, 1-5 used
    int delay_;                             // 0x44 frames
    std::queue<char> delayed_;              // 0x48 3 bytes a frame
};
