// The tournament session (mode 3): offline matches between two named players (the ini's
// [Tournament] P1_Name and P2_Name), with the score on screen, every match's replay
// saved, and each set's results appended to TournamentFolder\tournament_results.txt.
// At startup it walks the title menu to VS PLAYER by itself; holding Esc for
// escHoldFrames_ frames in a fight quits it (one press does nothing), and a return to
// the title ends the program.
#pragma once
#include "Config.h"
#include <chrono>
#include <fstream>
#include <queue>
#include <string>
#include "Session.h"
#include "../EfzRevivalLauncher/SharedData.h"

// 0x310 bytes
class TournamentSession : public Session {
public:
    TournamentSession();
    ~TournamentSession();
    void start();
    void update();
    void keyPressed(int key);
    void input(BYTE *input, int player);
    void fightUpdate(void *frame);

private:
    std::wstring formatDuration(const std::chrono::system_clock::time_point &start,
                                const std::chrono::system_clock::time_point &end);
    std::wstring formatTime(const std::chrono::system_clock::time_point &time);
    std::wstring timestamp(bool fileName);
    std::wstring replayFileName();
    void checkDevices();
    void drawInfo();
    void sceneChanged();
    void fightFrame();
    void selectFrame();
    void titleFrame();

    int rounds_[2];                                     // 0x04 won in this fight
    int characters_[2];                                 // 0x0c
    int unknown14_;                                     // 0x14
    std::fstream results_;                              // 0x18 tournament_results.txt
    std::wstring p1Name_;                               // 0xd8 the fight's
    std::wstring p2Name_;                               // 0xf0
    int escHoldFrames_;                                 // 0x108 to quit
    int lastScene_;                                     // 0x10c
    Config config_;                                     // 0x110
    std::queue<FrameInput> menuInputs_;                 // 0x2e4 P1's, from the title to VS PLAYER
    int setNumber_;                                     // 0x2f8 changes with the players' names
    int wins_[2];                                       // 0x2fc in this set
    std::chrono::system_clock::time_point fightStart_;  // 0x308
};
