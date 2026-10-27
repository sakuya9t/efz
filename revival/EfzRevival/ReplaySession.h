// The replay session: watching a replay from the game's REPLAY menu (EfzRevival.cpp's
// switchSession creates it in practice mode). An extended .rep (one this DLL recorded)
// also holds every frame's inputs, so the session can pause, step and seek it (a save
// state every 64 frames, 300 of them), show the input display, and let a player take
// control of a character from any point: pressing a button in a fight hands that
// player's inputs to the keyboard, and the game records the rest of the fight.
#pragma once
#include "Config.h"
#include <memory>
#include <string>
#include <vector>
#include "Session.h"
#include "Efz.h"
#include "GameState.h"
#include "Playlist.h"
#include "RingBuffer.h"
#include "../EfzRevivalLauncher/SharedData.h"

class MusicPlayer;   // Music.h

// A save state of the replay and where its file was then. 0x2c bytes.
struct ReplayState {
    // FUNCTION: 0x1002cb70 ??0ReplayState@@QAE@XZ
    ReplayState()
    {
    }

    // FUNCTION: 0x1002cb10 ?reset@ReplayState@@QAEXXZ
    void reset()
    {
        state.clear();
        position = 0;
    }

    SaveState state;                        // 0x00
    unsigned int position;                  // 0x28 in the replay file
};

// A player's input of this frame, read from the keyboard or pad.
struct LiveInput : public FrameInput {
    // FUNCTION: 0x1002cb60 ??0LiveInput@@QAE@XZ
    LiveInput()
        : FrameInput(0, 0)
    {
    }

};

// 0xa0 bytes
class ReplaySession : public Session {
public:
    ReplaySession();
    ~ReplaySession();
    void start();
    void update();
    void keyPressed(int key);
    void input(BYTE *input, int player);
    void fightUpdate(void *frame);
    void playSound(WORD id, int arg);
    void setVolume(WORD id, int volume);
    void stopSound(WORD id);

private:
    void setPaused(bool paused);
    void drawInfo();
    void loadState(ReplayState &state);
    void saveState(ReplayState &state);
    void showBoxes();
    void sceneChanged(int &scene);
    void setEfzReplay(bool play);
    bool isControlling();
    bool isReplaying();

    std::unique_ptr<Config> config_;        // 0x04
    int frame_;                             // 0x08
    double fps_;                            // 0x10
    bool paused_;                           // 0x18
    bool step_;                             // 0x19
    bool control_;                          // 0x1a a player has taken control
    bool quit_;                             // 0x1b the replay ran out of inputs
    bool display_;                          // 0x1c
    bool hitBoxes_ : 1;                     // 0x1d
    bool hurtBoxes_ : 1;
    bool collisionBoxes_ : 1;
    LiveInput inputs_[2];                   // 0x1e
    int controlled_;                        // 0x24 the player who may take control
    ReplayState state_;                     // 0x28 SaveState/LoadState's
    std::vector<FrameInput> replayInputs_;  // 0x54 the extended replay's, P1's then P2's
    int lastScene_;                         // 0x60
    MusicPlayer *music_;                    // 0x64
    Playlist playlist_;                     // 0x68
    std::vector<char> p1Inputs_;            // 0x78 for the input display
    std::vector<char> p2Inputs_;            // 0x84
    RingBuffer<ReplayState> states_;        // 0x90 every 64 frames
};
