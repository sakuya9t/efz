// Netplay's session: EfzRevival 1.02h's OnlineSession (revival/EfzRevival/
// OnlineSession.cpp), in the game's process.
//
// The match runs from the title as Revival runs it: both games start where efz.exe
// starts, P1's first 22 inputs are scripted to pick VS HUMAN, and from then on every
// frame of both games runs on both players' inputs for that frame, the menus included.
// Each real frame (Update) the session runs the game from its last confirmed frame (the
// newest with both players' inputs) up to the newest local input less the input delay,
// drawing only the last: a remote input not yet received repeats the last one. Each
// frame confirmed on the way is saved and its sync record made; then the last confirmed
// frame's state is loaded again, so the next update runs the unconfirmed frames once
// more with whatever has arrived. Out of a fight there is no rollback: the menus wait
// for the remote inputs.
//
// Left out, as in protocol.h: custom palettes, the custom BGM folder, the battle log.
#ifndef EFZ_NETPLAY_SESSION_H
#define EFZ_NETPLAY_SESSION_H

#include <stdint.h>
#include <map>
#include <string>
#include <vector>

#include "protocol.h"

namespace efz {
namespace netplay {

// A copy of the fight's state that can be written back (GameState.cpp's SaveState): the
// regions Revival copies, by the native game's types.
class SaveState {
public:
    void Save();
    // A variable of the session's to keep with the state.
    void AddInt(int* value);
    void Load();
    void Clear();

private:
    struct Region {
        char* at;
        size_t size;
        size_t offset;
    };
    void Add(void* at, size_t size);
    std::vector<Region> regions_;
    std::vector<char> data_;
    uint32_t rng_ = 0;
    bool saved_ = false;
};

class Session {
public:
    void Start(Protocol* protocol);
    // The game is left as it is, to be made anew (netplay.cpp); Revival's rules end.
    void Stop();
    // One real frame: runs as many of the game's frames as the inputs allow (0 or more).
    void Update();
    bool Running() const { return protocol_ != nullptr; }

    // The hooks (efz::NetplayHooks, netplay.h).
    void Input(int player, unsigned char* input);
    void FightKeys(char* keys);
    void MatchLeft();
    void ReplayOpen();
    void ReplayWrite(short value);
    void ReplayClose();
    bool Sound(unsigned short id, int loop);

    // For the screen: drawInfo's.
    bool ShowInfo() const;
    int InputDelay() const { return inputDelay_; }
    int Wins(int player) const { return wins_[player]; }
    int Scene() const;
    // Frames of the game run so far, and real frames since the last one ran.
    int Frame() const { return frame_; }
    int stalled = 0;
    // The local player gave up waiting or left (netplay.cpp ends the session).
    std::string savedReplay; // the last replay written, for the screen

private:
    std::vector<FrameInput>& Local() { return protocol_->inputs[local_]; }
    std::vector<FrameInput>& Remote() { return protocol_->inputs[remote_]; }

    void RunFrame();
    void RunFightFrames(int count);
    void RunMenuFrames(int count);
    void RunQuitFrames(int count);
    void RunFrames(int count);
    int MenuFramesToRun();
    int FightFramesToRun();
    void SceneChanged();
    void SaveFrameState();
    void LoadState(int to);
    void CountSounds(int from, int to);
    bool CanSave(unsigned frame);
    int LoadFrame();
    FrameInput ReadInput();
    void AddInput(const FrameInput& input);
    void SetInputDelay(int delay);
    float PingFrames(int ping);
    void SendSync(const FrameInput& p1, const FrameInput& p2);
    bool IsMatchOver();
    void SetNetplay(bool on);
    void ApplyPalettes();
    void KeyPressed();
    std::map<int, int>& Played(int frame);
    std::map<int, int>& Confirmed(int frame);
    std::string ReplayName();

    Protocol* protocol_ = nullptr;
    int local_ = 0;
    int remote_ = 1;
    int inputDelay_ = 0;
    int maxRollback_ = 0;    // 0 out of a fight
    int matchDelay_ = 0;     // the delay a fight starts with
    int frame_ = 0;
    int matchNumber_ = 0;
    int scene_ = 0;          // the scene the frame ran in
    int newScene_ = 0;
    int fightStart_ = 0;     // the frame the fight began
    int sceneFrames_ = 0;
    int confirmedFrame_ = 0; // the next frame to save
    int syncedFrame_ = 0;    // the next frame to make a sync record of
    int matchOverFrame_ = 0;
    int lastFrame_ = 0;      // the furthest frame run
    int wins_[2] = {0, 0};
    // For the log: rollbacks, the frames they ran again, the most at once.
    int rollbacks_ = 0;
    int rerun_ = 0;
    int deepest_ = 0;
    int characters_[2] = {0, 0};
    std::vector<std::map<int, int>> played_;    // sounds played, per frame (30)
    std::vector<std::map<int, int>> confirmed_; // of those, on final inputs
    std::map<int, int> soundCounts_;            // to skip when run again
    std::vector<SaveState> states_;             // per frame (60)
    PingStats ping_;
    bool keysDown_[0x100] = {};
    // The replay (EfzGame.cpp's): the game's words of the confirmed frames, then both
    // players' inputs for the extended part.
    bool writeReplay_ = true;
    bool replayOpen_ = false;
    std::string replayName_;
    uint32_t replaySeed_ = 0;
    std::vector<short> replayWords_;
    std::vector<FrameInput> replayInputs_;
};

} // namespace netplay
} // namespace efz

#endif
