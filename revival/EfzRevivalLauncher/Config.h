// EfzRevival.ini, read once into public fields. Keys are stored as DirectInput scan
// codes (DIK_*), joystick buttons as 0x200 + n (BUTTON_n), -1 when unset ("None").
// 0x1d4 bytes.
#pragma once
#include <boost/asio.hpp>
#include <windows.h>
#include <map>
#include <string>

class Config {
public:
    Config(const std::wstring &path);
    ~Config();
    // Reads the ini again (EfzRevival.dll's tournament does, at character select).
    void reload();

    // [Global]
    bool debug;                                         // 0x00 Debug
    int windowX;                                        // 0x04 WindowX
    int windowY;                                        // 0x08 WindowY
    int windowWidth;                                    // 0x0c WindowWidth
    int windowHeight;                                   // 0x10 WindowHeight
    int backBufferWidth;                                // 0x14 BackBufferWidth
    int backBufferHeight;                               // 0x18 BackBufferHeight
    int softwareRendering;                              // 0x1c SoftwareRendering
    int toggleBGM;                                      // 0x20 ToggleBGM (key)
    int muteBGM;                                        // 0x24 MuteBGM
    std::wstring bgmFolder;                             // 0x28 BGMFolder
    // [Network]
    std::wstring name;                                  // 0x40 Name
    int port;                                           // 0x58 Port
    int maxRollback;                                    // 0x5c MaxRollback
    std::wstring protocol;                              // 0x60 Protocol (IPv4/IPv6)
    boost::asio::ip::udp::endpoint holePunchingServer;  // 0x78 HolePunchingServer
    int allowPracticeKeys;                              // 0x94 AllowPracticeKeys
    int player;                                         // 0x98 Player (then forced to 1)
    bool allowSpectating;                               // 0x9c AllowSpectating
    int increaseInputDelay;                             // 0xa0 keys
    int decreaseInputDelay;                             // 0xa4
    int increaseSpecSpeed;                              // 0xa8
    int decreaseSpecSpeed;                              // 0xac
    int saveAllReplays;                                 // 0xb0 SaveAllReplays
    int displayScore;                                   // 0xb4 DisplayScore
    int logScore;                                       // 0xb8 LogScore
    int savePreviousReplay;                             // 0xbc key
    std::wstring replayFolder;                          // 0xc0 ReplayFolder
    std::wstring replayFormat;                          // 0xd8 ReplayFormat
    std::wstring battleLogFile;                         // 0xf0 BattleLogFile
    bool saveBattleLog;                                 // 0x108 SaveBattleLog
    // [Practice] keys (toggleRemotePalettes is in [Network])
    int pause;                                          // 0x10c
    int stepFrame;                                      // 0x110
    int saveState;                                      // 0x114 Save
    int loadState;                                      // 0x118 Load
    int toggleRemotePalettes;                           // 0x11c
    int toggleRecord;                                   // 0x120
    int toggleReplay;                                   // 0x124
    int switchStartCondition;                           // 0x128
    int toggleReplayRandom;                             // 0x12c
    int unknown130;                                     // 0x130 not read here
    int toggleDisplay;                                  // 0x134
    int toggleHitBoxes;                                 // 0x138
    int toggleHurtBoxes;                                // 0x13c
    int toggleCollisionBoxes;                           // 0x140
    int switchPlayers;                                  // 0x144
    int mirrorPlayers;                                  // 0x148
    int increaseFPS;                                    // 0x14c
    int decreaseFPS;                                    // 0x150
    int resetFPS;                                       // 0x154
    int setBuffer[5];                                   // 0x158 SetBuffer1-5
    // [Tournament]
    std::wstring p1Name;                                // 0x16c P1_Name
    std::wstring p2Name;                                // 0x184 P2_Name
    std::wstring tournamentFolder;                      // 0x19c TournamentFolder

private:
    bool load(const std::wstring &path);
    void loadKeyNames();
    void loadPadNames();
    int readInt(const std::wstring &section, const std::wstring &key);
    int readKey(const std::wstring &section, const std::wstring &key);
    std::wstring readString(const std::wstring &section, const std::wstring &key, int size);

    std::wstring path_;                                 // 0x1b4
    std::map<std::wstring, int> keys_;                  // 0x1cc key and button names
};

// Whether "host:port" (an IPv6 host may be in brackets) parses as a UDP endpoint.
bool isValidAddress(const std::string &address);

std::string to_utf8(const std::wstring &text);
std::string to_utf8(const wchar_t *text, int length);
