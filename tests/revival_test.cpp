// EfzRevival.ini as the game reads it (port/revival/config.cpp) and the endpoints the
// launcher puts in its messages (port/netplay/net.cpp): no game, no files, no network.
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include "revival/config.h"
#include "netplay/net.h"
#include "log.h"

using namespace efz;

// What config.cpp needs of the game: no file (the defaults), and a log that says nothing.
namespace efz {
void LogV(LogLevel, const char*, const char*, va_list) {}
FILE* OpenGameFile(const char*, const char*)
{
    return nullptr;
}
} // namespace efz

static int g_failed;

#define CHECK(c)                                                                    \
    do {                                                                            \
        if (!(c)) {                                                                 \
            fprintf(stderr, "%s:%d: failed: %s\n", __FILE__, __LINE__, #c);         \
            g_failed++;                                                             \
        }                                                                           \
    } while (0)

// Lines of Revival's own EfzRevival.ini (1.02h), as it spells them: aligned values,
// comments, a quoted folder, and a section of keys Revival reads with a trailing space.
static const char kIni[] =
    ";/*  ---\r\n"
    "[Network]\r\n"
    "Name                 = EfzPlayer\r\n"
    "MaxRollback          = 6\r\n"
    "HolePunchingServer   = None\r\n"
    "AllowPracticeKeys    = 1\r\n"
    "ToggleRemotePalettes = DIK_TAB\r\n"
    "SaveAllReplays       = 0\r\n"
    "ReplayFolder         = replay/mine/\r\n"
    "SavePreviousReplay   = BUTTON_13\r\n"
    "[Practice]\r\n"
    "; Pause = DIK_P\r\n"
    "Pause                = DIK_PGUP\r\n"
    "SwitchStartCondition = BUTTON_3\r\n"
    "SetBuffer2           = None\r\n"
    "ToggleHitBoxes       = DIK_NOSUCHKEY\r\n"
    "[Tournament]\r\n"
    "P1_Name           = Aaaaaaaaaabbbbbbbbbbcccc\r\n"
    "[Global]\r\n"
    "BGMFolder            = \"C:\\Home\\Music\\\"\r\n"
    "MuteBGM              = 1\r\n"
    "WindowWidth          = 1280\r\n";

int main()
{
    // The text, from UTF-16 with its mark, as Revival ships the file.
    std::string utf16 = "\xff\xfe";
    for (const char* c = kIni; *c; c++) {
        utf16.push_back(*c);
        utf16.push_back(0);
    }
    std::string text = revival::DecodeIni((const unsigned char*)utf16.data(), utf16.size());
    CHECK(text == kIni);
    revival::Config c = revival::ParseConfig(text);
    CHECK(c.name == "EfzPlayer");
    CHECK(c.maxRollback == 6);
    CHECK(c.holePunchingServer.empty()); // None
    CHECK(c.allowPracticeKeys);
    CHECK(c.toggleRemotePalettes == 0x0f);
    CHECK(!c.saveAllReplays);
    CHECK(c.replayFolder == "replay/mine/");
    CHECK(c.savePreviousReplay == revival::kButton + 13);
    CHECK(c.pause == 0xc9); // DIK_PGUP, an alternate name
    CHECK(c.switchStartCondition == revival::kButton + 3);
    CHECK(c.setBuffer[1] == revival::kNoKey);
    CHECK(c.toggleHitBoxes == revival::kNoKey); // not a key's name: none
    CHECK(c.p1Name == "Aaaaaaaaaabbbbbbbbbb"); // 20 characters at most
    CHECK(c.bgmFolder == "C:\\Home\\Music\\");
    CHECK(c.muteBGM);
    CHECK(c.windowWidth == 1280);
    CHECK(c.Has("Global", "WindowWidth") && !c.Has("Global", "WindowHeight"));
    // What the file doesn't say: Revival's own defaults.
    CHECK(c.port == 10800);
    CHECK(c.stepFrame == 0x19);           // DIK_P
    CHECK(c.toggleBGM == 0x58);           // DIK_F12
    CHECK(c.increaseInputDelay == 0x4e);  // DIK_ADD
    CHECK(c.tournamentFolder == "Tournament/");
    CHECK(c.saveBattleLog && c.battleLogFile == "BattleLog.txt");
    // No file at all: those, and Revival's server.
    revival::Config none = revival::ParseConfig("");
    CHECK(none.holePunchingServer == "128.199.38.97:10800");
    CHECK(none.maxRollback == 4 && none.pause == 0x39);
    // The key names, both ways.
    CHECK(revival::KeyCode("DIK_NUMPAD0") == 0x52);
    CHECK(revival::KeyCode("BUTTON_32") == revival::kButton + 32);
    CHECK(revival::KeyCode("BUTTON_33") == -2);
    CHECK(revival::KeyCode("None") == revival::kNoKey);
    CHECK(revival::KeyName(0x39) == "DIK_SPACE");
    CHECK(revival::KeyName(revival::kButton + 5) == "BUTTON_5");
    // UTF-8 with a mark, and UTF-16 without one.
    const char utf8[] = "\xef\xbb\xbf[Network]\nName = \xe3\x81\x82\n";
    revival::Config named = revival::ParseConfig(
        revival::DecodeIni((const unsigned char*)utf8, sizeof(utf8) - 1));
    CHECK(named.name == "\xe3\x81\x82");
    const unsigned char bare[] = {'[', 0, 'N', 0};
    CHECK(revival::DecodeIni(bare, sizeof(bare)) == "[N");

    // OPTIONS' writing: the value replaced where it is, the name's alignment kept...
    std::string edited = revival::SetIniValue(kIni, "network", "maxrollback", "9");
    CHECK(edited.find("MaxRollback          = 9\r\n") != std::string::npos);
    CHECK(edited.size() == strlen(kIni));
    CHECK(revival::ParseConfig(edited).maxRollback == 9);
    // ... a key the section lacks after its last setting, the file's line ends kept ...
    edited = revival::SetIniValue(kIni, "Network", "SaveBattleLog", "0");
    CHECK(edited.find("SavePreviousReplay   = BUTTON_13\r\nSaveBattleLog = 0\r\n[Practice]") !=
          std::string::npos);
    CHECK(!revival::ParseConfig(edited).saveBattleLog);
    // ... a commented-out key isn't the key ...
    edited = revival::SetIniValue(kIni, "Practice", "Pause", "DIK_P");
    CHECK(edited.find("; Pause = DIK_P\r\n") != std::string::npos);
    CHECK(revival::ParseConfig(edited).pause == 0x19);
    // ... a section the file lacks at its end, and a file that isn't there made.
    edited = revival::SetIniValue("[Global]\nMuteBGM = 0\n", "Network", "HolePunchingServer", "None");
    CHECK(edited == "[Global]\nMuteBGM = 0\n\n[Network]\nHolePunchingServer = None\n");
    CHECK(revival::SetIniValue("", "Global", "MuteBGM", "1") == "[Global]\r\nMuteBGM = 1\r\n");

    // The launcher's endpoints: a 32-bit Windows boost::asio endpoint's bytes.
    net::Endpoint e;
    std::string error;
    CHECK(net::Resolve("1.2.3.4:10800", 0, &e, &error));
    std::string b = net::RevivalEndpoint(e);
    CHECK(b.size() == 28);
    CHECK((unsigned char)b[0] == 2 && b[1] == 0);                                  // AF_INET
    CHECK((unsigned char)b[2] == 0x2a && (unsigned char)b[3] == 0x30);             // 10800
    CHECK(b[4] == 1 && b[5] == 2 && b[6] == 3 && b[7] == 4);
    net::Endpoint back;
    CHECK(net::FromRevivalEndpoint(b, &back) && back == e);
    CHECK(net::Resolve("[2001:db8::1]:10801", 0, &e, &error));
    b = net::RevivalEndpoint(e);
    CHECK((unsigned char)b[0] == 23); // Windows' AF_INET6
    CHECK(net::FromRevivalEndpoint(b, &back) && back == e && back.IsV6());
    CHECK(!net::FromRevivalEndpoint(std::string(28, '\0'), &back));

    if (g_failed) {
        fprintf(stderr, "%d check(s) failed\n", g_failed);
        return 1;
    }
    printf("revival: all checks passed\n");
    return 0;
}
