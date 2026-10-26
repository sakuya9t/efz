// The spectator session (mode 1): the launcher relays a netplay match's inputs as they
// are confirmed ("InputP1"/"InputP2"), the players' palettes ("PaletteP1"/"PaletteP2"),
// the players' match number ("LoadMatch") and the session parameters ("Init").
// Every frame the session runs as many frames as it has inputs for, at most `speed_`
// (1-9, IncreaseSpecSpeed/DecreaseSpecSpeed), with the game's drawing off for all but
// the last, so a spectator that fell behind catches up. It sends one SyncBlock per frame
// back ("Sync") and writes the match's replay (SavePreviousReplay keeps it).
//
// init() creates it with operator new(0x500) when the launcher's mode is 1. Its vtable is
// 0x10090424.
#pragma once
#include "../EfzRevivalLauncher/Config.h"  // boost.asio's winsock2.h before windows.h
#include <fstream>
#include <string>
#include <vector>
#include "EfzPalettes.h"
#include "Music.h"
#include "Session.h"
#include "../EfzRevivalLauncher/SharedData.h"
#include "../EfzRevivalLauncher/SharedQueue.h"

// 0x500 bytes
class SpectatorSession : public Session {
public:
    SpectatorSession();
    ~SpectatorSession();
    void start();
    void update();
    void keyPressed(int key);
    void input(BYTE *input, int player);
    void fightUpdate(void *frame);
    void playSound(WORD id, int arg);
    void setVolume(WORD id, int volume);
    void stopSound(WORD id);

private:
    bool isRunning(HANDLE process);
    std::wstring replayFileName();
    void drawInfo();
    void applyPalette(int player);
    void sceneChanged();
    void sendSync();
    void receivePalettes(int player);
    void receiveInputs(int player);
    void receiveLoadMatch();
    void receiveInit();
    void setSpeed(int speed);

    int unknown4_;                                      // 0x04
    int speed_;                                         // 0x08 frames run a frame, 1-9
    Palettes palettes_[2];                              // 0x0c
    std::vector<FrameInput> inputs_[2];                 // 0x1c every frame's, P1's and P2's
    HANDLE launcher_;                                   // 0x34
    std::wstring p1Name_;                               // 0x38
    std::wstring p2Name_;                               // 0x50
    int frame_;                                         // 0x68 the next frame to run
    int syncedFrame_;                                   // 0x6c the next frame to send
    int scene_;                                         // 0x70 the scene the frame ran in
    int newScene_;                                      // 0x74
    bool unknown78_;                                    // 0x78
    bool flushed_;                                      // 0x79 SavePreviousReplay pressed
    bool saved_;                                        // 0x7a the replay was written
    int hostMatch_;                                     // 0x7c the players' match (MatchInfo)
    int wins_[2];                                       // 0x80
    int matchNumber_;                                   // 0x88
    GameInfo init_;                                     // 0x8c
    Config config_;                                     // 0x1a0
    std::vector<SharedQueue<FrameInput> > inputQueues_;     // 0x374 "InputP1", "InputP2"
    std::vector<SharedQueue<ColorPalette> > paletteQueues_; // 0x380 "PaletteP1", "PaletteP2"
    SharedQueue<GameInfo> initQueue_;                   // 0x38c "Init"
    SharedQueue<SyncBlock> syncQueue_;                  // 0x3b4 "Sync"
    SharedQueue<bool> quitQueue_;                       // 0x3dc "Quit"
    SharedQueue<MatchInfo> loadMatchQueue_;             // 0x404 "LoadMatch"
    MusicPlayer *music_;                                // 0x42c
    Playlist playlist_;                                 // 0x430
    std::fstream unknown440_;                           // 0x440
};
