// The online session (OnlineSession.cpp, 0x10070600-0x10074210): rollback netplay
// against the launcher. The launcher (EfzRevival.exe) does the networking; the two
// exchange records through named shared memory (SharedQueue): this side pushes the
// local player's inputs ("InputP1"/"InputP2"), its palettes ("PaletteP1"/"PaletteP2"),
// one SyncBlock per confirmed frame ("Sync"), the match results ("LoadMatch") and a
// quit request ("Quit"); the launcher pushes the remote inputs and palettes, the
// session parameters ("Init") and the ping statistics ("Net").
//
// Every frame (update) the session drains those queues and, in a fight, runs the game
// from its last confirmed frame (the newest with both players' inputs) to the newest
// local input less the input delay, with the rendering off but for the last frame:
// remote inputs not yet received are predicted by repeating the last one (input). Each
// frame confirmed on the way is saved (saveState, with the session's frame counters)
// and its sync record sent; at the end the state of the last confirmed frame is loaded
// again (loadState), so the next update runs the unconfirmed frames once more with
// whatever remote inputs have arrived. Sounds played on frames that get run again are
// counted so that they play once, and those played on mispredicted inputs are stopped.
// Out of a fight there is no rollback: the menus wait for the remote inputs.
//
// init() creates it with operator new(0x690) when the launcher's mode is 0. No RTTI;
// its vtable is 0x10090400.
#pragma once
#include "../EfzRevivalLauncher/Config.h"  // boost.asio's winsock2.h before windows.h
#include <chrono>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "Session.h"
#include "Music.h"
#include "EfzPalettes.h"
#include "GameState.h"
#include "RingBuffer.h"
#include "../EfzRevivalLauncher/SharedData.h"
#include "../EfzRevivalLauncher/SharedQueue.h"

// The records the launcher and the DLL exchange are the launcher's SharedData.h. Their
// inline functions the DLL emits:
// FUNCTION: 0x100222b0 ??0GameInfo@@QAE@XZ
// FUNCTION: 0x10022290 ??0PingStats@@QAE@XZ
// FUNCTION: 0x10022270 ??0FrameInput@@QAE@DD@Z
// FUNCTION: 0x100285d0 ??0SyncBlock@@QAE@XZ
// FUNCTION: 0x10028620 ?toString@SyncBlock@@QBE?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@XZ

// The record of a frame about to run (0x100756a0, in the spectator's object): its
// inputs, the game's state and random seed.
SyncBlock makeSyncBlock(int frame, const FrameInput &inputP1, const FrameInput &inputP2);

class OnlineSession : public Session {
public:
    OnlineSession();
    // FUNCTION: 0x10022490 ??_GOnlineSession@@UAEPAXI@Z
    // (the scalar deleting destructor, vtable slot 0)
    virtual ~OnlineSession();
    virtual void start();
    virtual void update();
    virtual void keyPressed(int key);
    virtual void input(BYTE *input, int player);
    virtual void fightUpdate(void *frame);
    virtual void playSound(WORD id, int loop);
    virtual void setVolume(WORD id, int volume);
    virtual void stopSound(WORD id);

private:
    // Running frames
    void runFightFrames(int count);
    void logInputs(int count);
    void sceneChanged();
    void drawInfo();
    void sendSync(const FrameInput &p1, const FrameInput &p2);
    void loadState(int frame);
    void countSounds(int from, int to);
    int menuFramesToRun();
    int fightFramesToRun();
    void saveState();
    void checkControls();
    bool canSave(unsigned int frame);
    void runFrame();
    int loadFrame();
    void runFrames(int count);
    void runMenuFrames(int count);
    void runQuitFrames(int count);
    // Inputs
    FrameInput readInput();
    void addInput(int player, const FrameInput &input);
    void receiveInputs(int player);
    void setInputDelay(int delay);
    float pingFrames(int ping);
    // Palettes
    void applyPalette(int player, int number, bool custom);
    void sendPalette(int player, const ColorPalette &palette);
    void receivePalettes(int player);
    // The launcher
    void receiveInit();
    void receivePing();
    void sendLoadMatch(MatchInfo match);
    bool isRunning(HANDLE process);
    // Replays and the battle log
    std::wstring timestamp(bool fileName);
    std::wstring formatTime(const std::chrono::system_clock::time_point &time);
    std::wstring formatDuration(const std::chrono::system_clock::time_point &start,
                                const std::chrono::system_clock::time_point &end);
    std::wstring replayFileName();

    int rounds_[2];                                     // 0x04 rounds won in this game
    int characters_[2];                                 // 0x0c
    Config config_;                                     // 0x14
    std::fstream battleLog_;                            // 0x1e8 BattleLogFile
    int localPlayer_;                                   // 0x2a8
    int remotePlayer_;                                  // 0x2ac
    int inputDelay_;                                    // 0x2b0
    int maxRollback_;                                   // 0x2b4 0 out of a fight
    int matchDelay_;                                    // 0x2b8 the delay a fight starts with
    HANDLE launcher_;                                   // 0x2bc
    bool hideRemotePalettes_;                           // 0x2c0 ToggleRemotePalettes
    bool palettesToggled_;                              // 0x2c1
    bool replayFlushed_;                                // 0x2c2
    bool replaySaved_;                                  // 0x2c3
    int frame_;                                         // 0x2c4
    int matchNumber_;                                   // 0x2c8
    int scene_;                                         // 0x2cc the scene the frame ran in
    int newScene_;                                      // 0x2d0
    int fightStart_;                                    // 0x2d4 the frame the fight began
    int sceneFrames_;                                   // 0x2d8
    int confirmedFrame_;                                // 0x2dc the next frame to save
    int syncedFrame_;                                   // 0x2e0 the next frame to send
    std::wstring p1Name_;                               // 0x2e4
    std::wstring p2Name_;                               // 0x2fc
    std::vector<FrameInput> localInputs_;               // 0x314 one per frame
    std::vector<FrameInput> remoteInputs_;              // 0x320
    std::vector<FrameInput> startInputs_;               // 0x32c through the menus
    std::vector<FrameInput> *inputs_[2];                // 0x338 P1's, P2's
    Palettes palettes_[2];                              // 0x340
    RingBuffer<std::map<WORD, int> > played_;           // 0x350 sounds played, per frame
    RingBuffer<std::map<WORD, int> > confirmed_;        // 0x360 of those, on final inputs
    std::map<short, int> soundCounts_;                  // 0x370 to skip when run again
    std::map<short, int> unknown378_;                   // 0x378
    RingBuffer<SaveState> states_;                      // 0x380
    int unknown390_[2];                                 // 0x390
    std::chrono::system_clock::time_point fightTime_;   // 0x398 when the fight began
    PingStats ping_;                                    // 0x3a0
    GameInfo init_;                                     // 0x3b0
    // The record "LoadMatch" sends: the match number and each player's wins. TODO: the
    // stub SharedData.h names its fields a, b, c; the wins are an array (indexed by
    // the winner in sceneChanged).
    MatchInfo match_;                               // 0x4c4
    int matchOverFrame_;                                // 0x4d0
    int lastFrame_;                                     // 0x4d4 the furthest frame run
    std::vector<SharedQueue<FrameInput> > inputQueues_;     // 0x4d8 "InputP1", "InputP2"
    std::vector<SharedQueue<ColorPalette> > paletteQueues_; // 0x4e4 "PaletteP1", "PaletteP2"
    SharedQueue<GameInfo> initQueue_;                   // 0x4f0 "Init"
    SharedQueue<PingStats> netQueue_;                   // 0x518 "Net"
    SharedQueue<SyncBlock> syncQueue_;                   // 0x540 "Sync"
    SharedQueue<bool> quitQueue_;                       // 0x568 "Quit"
    SharedQueue<MatchInfo> loadMatchQueue_;         // 0x590 "LoadMatch"
    MusicPlayer *music_;                                // 0x5b8
    Playlist playlist_;                                 // 0x5bc
    std::fstream unknown5d0_;                           // 0x5d0
};
