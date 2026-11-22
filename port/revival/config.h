// EfzRevival.ini in the native game (docs/revival-features.md): the settings of
// EfzRevival 1.02h's netplay, practice, tournament and music, read as Revival reads them
// (revival/EfzRevival/Config.cpp), from the save folder or the game's folder.
//
// The file is Revival's own: UTF-16 (as Revival ships it) or UTF-8, [Section] and
// "Key = value" lines, ';' comments. Keys are DirectInput's names (DIK_SPACE...) or a
// button of P1's controller (BUTTON_1 to BUTTON_32), "None" for none. What the file
// doesn't say is what Revival's own EfzRevival.ini says, so that the game behaves as
// Revival as shipped without one.
#ifndef EFZ_REVIVAL_CONFIG_H
#define EFZ_REVIVAL_CONFIG_H

#include <string>

namespace efz {
namespace revival {

// A key: a DIK_ code (0-0xff), a button of P1's controller (kButton + 1 to 32), or kNoKey.
const int kNoKey = -1;
const int kButton = 0x200;

struct Config {
    // [Global]
    bool debug = false;
    int windowX = 10, windowY = 10;
    int windowWidth = 640, windowHeight = 480;
    int backBufferWidth = 1280, backBufferHeight = 960; // (not used: SDL scales)
    bool softwareRendering = false;
    int toggleBGM = 0x58; // DIK_F12
    bool muteBGM = false;
    std::string bgmFolder; // UTF-8; empty: the game's own music
    // [Network]
    std::string name = "EfzPlayer";
    int port = 10800;
    int maxRollback = 4;
    std::string holePunchingServer = "128.199.38.97:10800"; // "None": none
    bool allowPracticeKeys = false;
    int increaseInputDelay = 0x4e; // DIK_ADD
    int decreaseInputDelay = 0x4a; // DIK_SUBTRACT
    int toggleRemotePalettes = 0x39; // DIK_SPACE
    bool displayScore = true;
    bool logScore = true;
    bool saveAllReplays = true;
    std::string replayFolder = "replay/netplay/";
    int savePreviousReplay = 0x1f; // DIK_S
    std::string battleLogFile = "BattleLog.txt";
    bool saveBattleLog = true;
    // [Practice]
    int pause = 0x39;        // DIK_SPACE
    int stepFrame = 0x19;    // DIK_P
    int saveState = 0x22;    // DIK_G
    int loadState = 0x30;    // DIK_B
    int toggleRecord = 0x23; // DIK_H
    int toggleReplay = 0x31; // DIK_N
    int switchStartCondition = 0x1d; // DIK_LCONTROL
    int toggleReplayRandom = 0x0b;   // DIK_0
    int setBuffer[5] = {0x02, 0x03, 0x04, 0x05, 0x06}; // DIK_1 to DIK_5
    int toggleDisplay = 0x1c;        // DIK_RETURN
    int toggleHitBoxes = 0xc9;       // DIK_PRIOR
    int toggleHurtBoxes = 0xd1;      // DIK_NEXT
    int toggleCollisionBoxes = 0xc7; // DIK_HOME
    int switchPlayers = 0x52;        // DIK_NUMPAD0
    int mirrorPlayers = 0x51;        // DIK_NUMPAD3
    int increaseFPS = 0xd2;          // DIK_INSERT
    int decreaseFPS = 0xd3;          // DIK_DELETE
    int resetFPS = 0xcf;             // DIK_END
    // [Tournament]
    std::string p1Name = "P1", p2Name = "P2";
    std::string tournamentFolder = "Tournament/";

    // Where it was read from ("" Revival's defaults, no file).
    std::string path;
    // Whether the file named the key (else it has Revival's default).
    bool Has(const char* section, const char* key) const;
};

// The settings, read once (and again by Reload: the tournament reads them again at
// character select, for the players' names).
const Config& GetConfig();
void ReloadConfig();
// For tests: the settings as the text of an ini file would give them, and a file's bytes
// as that text (UTF-16 with or without its mark, or UTF-8).
Config ParseConfig(const std::string& text);
std::string DecodeIni(const unsigned char* data, size_t size);
// A key's name as Revival's ini spells it ("DIK_SPACE", "BUTTON_3", "None").
std::string KeyName(int key);
// The key a name stands for, kNoKey for "None", -2 for a name that isn't one.
int KeyCode(const std::string& name);

} // namespace revival
} // namespace efz

#endif
