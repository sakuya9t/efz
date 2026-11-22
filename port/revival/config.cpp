// EfzRevival.ini (config.h).
#include "config.h"

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <vector>

#include "../platform.h"
#include "../log.h"

namespace efz {
namespace revival {

namespace {

struct KeyEntry {
    const char* name;
    int code;
};

// Config.cpp's loadKeyNames: DirectInput's names, then the alternate ones. The first
// name of a code is the one KeyName gives.
const KeyEntry kKeys[] = {
    {"None", kNoKey},
    {"DIK_ESCAPE", 0x01}, {"DIK_1", 0x02}, {"DIK_2", 0x03}, {"DIK_3", 0x04},
    {"DIK_4", 0x05}, {"DIK_5", 0x06}, {"DIK_6", 0x07}, {"DIK_7", 0x08},
    {"DIK_8", 0x09}, {"DIK_9", 0x0a}, {"DIK_0", 0x0b}, {"DIK_MINUS", 0x0c},
    {"DIK_EQUALS", 0x0d}, {"DIK_BACK", 0x0e}, {"DIK_TAB", 0x0f}, {"DIK_Q", 0x10},
    {"DIK_W", 0x11}, {"DIK_E", 0x12}, {"DIK_R", 0x13}, {"DIK_T", 0x14},
    {"DIK_Y", 0x15}, {"DIK_U", 0x16}, {"DIK_I", 0x17}, {"DIK_O", 0x18},
    {"DIK_P", 0x19}, {"DIK_LBRACKET", 0x1a}, {"DIK_RBRACKET", 0x1b},
    {"DIK_RETURN", 0x1c}, {"DIK_LCONTROL", 0x1d}, {"DIK_A", 0x1e}, {"DIK_S", 0x1f},
    {"DIK_D", 0x20}, {"DIK_F", 0x21}, {"DIK_G", 0x22}, {"DIK_H", 0x23},
    {"DIK_J", 0x24}, {"DIK_K", 0x25}, {"DIK_L", 0x26}, {"DIK_SEMICOLON", 0x27},
    {"DIK_APOSTROPHE", 0x28}, {"DIK_GRAVE", 0x29}, {"DIK_LSHIFT", 0x2a},
    {"DIK_BACKSLASH", 0x2b}, {"DIK_Z", 0x2c}, {"DIK_X", 0x2d}, {"DIK_C", 0x2e},
    {"DIK_V", 0x2f}, {"DIK_B", 0x30}, {"DIK_N", 0x31}, {"DIK_M", 0x32},
    {"DIK_COMMA", 0x33}, {"DIK_PERIOD", 0x34}, {"DIK_SLASH", 0x35},
    {"DIK_RSHIFT", 0x36}, {"DIK_MULTIPLY", 0x37}, {"DIK_LMENU", 0x38},
    {"DIK_SPACE", 0x39}, {"DIK_CAPITAL", 0x3a}, {"DIK_F1", 0x3b}, {"DIK_F2", 0x3c},
    {"DIK_F3", 0x3d}, {"DIK_F4", 0x3e}, {"DIK_F5", 0x3f}, {"DIK_F6", 0x40},
    {"DIK_F7", 0x41}, {"DIK_F8", 0x42}, {"DIK_F9", 0x43}, {"DIK_F10", 0x44},
    {"DIK_NUMLOCK", 0x45}, {"DIK_SCROLL", 0x46}, {"DIK_NUMPAD7", 0x47},
    {"DIK_NUMPAD8", 0x48}, {"DIK_NUMPAD9", 0x49}, {"DIK_SUBTRACT", 0x4a},
    {"DIK_NUMPAD4", 0x4b}, {"DIK_NUMPAD5", 0x4c}, {"DIK_NUMPAD6", 0x4d},
    {"DIK_ADD", 0x4e}, {"DIK_NUMPAD1", 0x4f}, {"DIK_NUMPAD2", 0x50},
    {"DIK_NUMPAD3", 0x51}, {"DIK_NUMPAD0", 0x52}, {"DIK_DECIMAL", 0x53},
    {"DIK_OEM_102", 0x56}, {"DIK_F11", 0x57}, {"DIK_F12", 0x58}, {"DIK_F13", 0x64},
    {"DIK_F14", 0x65}, {"DIK_F15", 0x66}, {"DIK_KANA", 0x70}, {"DIK_ABNT_C1", 0x73},
    {"DIK_CONVERT", 0x79}, {"DIK_NOCONVERT", 0x7b}, {"DIK_YEN", 0x7d},
    {"DIK_ABNT_C2", 0x7e}, {"DIK_NUMPADEQUALS", 0x8d}, {"DIK_PREVTRACK", 0x90},
    {"DIK_AT", 0x91}, {"DIK_COLON", 0x92}, {"DIK_UNDERLINE", 0x93},
    {"DIK_KANJI", 0x94}, {"DIK_STOP", 0x95}, {"DIK_AX", 0x96},
    {"DIK_UNLABELED", 0x97}, {"DIK_NEXTTRACK", 0x99}, {"DIK_NUMPADENTER", 0x9c},
    {"DIK_RCONTROL", 0x9d}, {"DIK_MUTE", 0xa0}, {"DIK_CALCULATOR", 0xa1},
    {"DIK_PLAYPAUSE", 0xa2}, {"DIK_MEDIASTOP", 0xa4}, {"DIK_VOLUMEDOWN", 0xae},
    {"DIK_VOLUMEUP", 0xb0}, {"DIK_WEBHOME", 0xb2}, {"DIK_NUMPADCOMMA", 0xb3},
    {"DIK_DIVIDE", 0xb5}, {"DIK_SYSRQ", 0xb7}, {"DIK_RMENU", 0xb8},
    {"DIK_PAUSE", 0xc5}, {"DIK_HOME", 0xc7}, {"DIK_UP", 0xc8}, {"DIK_PRIOR", 0xc9},
    {"DIK_LEFT", 0xcb}, {"DIK_RIGHT", 0xcd}, {"DIK_END", 0xcf}, {"DIK_DOWN", 0xd0},
    {"DIK_NEXT", 0xd1}, {"DIK_INSERT", 0xd2}, {"DIK_DELETE", 0xd3},
    {"DIK_LWIN", 0xdb}, {"DIK_RWIN", 0xdc}, {"DIK_APPS", 0xdd}, {"DIK_POWER", 0xde},
    {"DIK_SLEEP", 0xdf}, {"DIK_WAKE", 0xe3}, {"DIK_WEBSEARCH", 0xe5},
    {"DIK_WEBFAVORITES", 0xe6}, {"DIK_WEBREFRESH", 0xe7}, {"DIK_WEBSTOP", 0xe8},
    {"DIK_WEBFORWARD", 0xe9}, {"DIK_WEBBACK", 0xea}, {"DIK_MYCOMPUTER", 0xeb},
    {"DIK_MAIL", 0xec}, {"DIK_MEDIASELECT", 0xed},
    // the alternate names
    {"DIK_BACKSPACE", 0x0e}, {"DIK_NUMPADSTAR", 0x37}, {"DIK_LALT", 0x38},
    {"DIK_CAPSLOCK", 0x3a}, {"DIK_NUMPADMINUS", 0x4a}, {"DIK_NUMPADPLUS", 0x4e},
    {"DIK_NUMPADPERIOD", 0x53}, {"DIK_NUMPADSLASH", 0xb5}, {"DIK_RALT", 0xb8},
    {"DIK_UPARROW", 0xc8}, {"DIK_PGUP", 0xc9}, {"DIK_LEFTARROW", 0xcb},
    {"DIK_RIGHTARROW", 0xcd}, {"DIK_DOWNARROW", 0xd0}, {"DIK_PGDN", 0xd1},
    {"DIK_CIRCUMFLEX", 0x90},
};

std::string Trim(const std::string& s)
{
    size_t a = 0, b = s.size();
    while (a < b && isspace((unsigned char)s[a]))
        a++;
    while (b > a && isspace((unsigned char)s[b - 1]))
        b--;
    return s.substr(a, b - a);
}

std::string Lower(std::string s)
{
    for (char& c : s)
        c = (char)tolower((unsigned char)c);
    return s;
}

// UTF-16LE to UTF-8.
std::string FromUtf16(const unsigned char* p, size_t n)
{
    std::string out;
    for (size_t i = 0; i + 1 < n; i += 2) {
        uint32_t c = p[i] | (p[i + 1] << 8);
        if (c >= 0xd800 && c < 0xdc00 && i + 3 < n) {
            uint32_t low = p[i + 2] | (p[i + 3] << 8);
            if (low >= 0xdc00 && low < 0xe000) {
                c = 0x10000 + ((c - 0xd800) << 10) + (low - 0xdc00);
                i += 2;
            }
        }
        if (c < 0x80) {
            out.push_back((char)c);
        } else if (c < 0x800) {
            out.push_back((char)(0xc0 | (c >> 6)));
            out.push_back((char)(0x80 | (c & 0x3f)));
        } else if (c < 0x10000) {
            out.push_back((char)(0xe0 | (c >> 12)));
            out.push_back((char)(0x80 | ((c >> 6) & 0x3f)));
            out.push_back((char)(0x80 | (c & 0x3f)));
        } else {
            out.push_back((char)(0xf0 | (c >> 18)));
            out.push_back((char)(0x80 | ((c >> 12) & 0x3f)));
            out.push_back((char)(0x80 | ((c >> 6) & 0x3f)));
            out.push_back((char)(0x80 | (c & 0x3f)));
        }
    }
    return out;
}

// The first `chars` characters of a UTF-8 string (GetPrivateProfileString's buffer).
std::string Truncate(const std::string& s, size_t chars)
{
    size_t i = 0, n = 0;
    while (i < s.size() && n < chars) {
        unsigned char c = (unsigned char)s[i];
        i += c < 0x80 ? 1 : c < 0xe0 ? 2 : c < 0xf0 ? 3 : 4;
        n++;
    }
    return s.substr(0, i < s.size() ? i : s.size());
}

struct Ini {
    // section and key, lower case, to the value
    std::vector<std::pair<std::string, std::string>> entries;
    std::set<std::string> keys;

    bool Find(const char* section, const char* key, std::string* value) const
    {
        std::string want = Lower(section) + "/" + Lower(key);
        for (const auto& e : entries) {
            if (e.first == want) {
                *value = e.second;
                return true;
            }
        }
        return false;
    }
};

// GetPrivateProfileString's reading: the first of a section's keys of that name, the value
// trimmed and taken out of the quotes around it.
Ini ParseIni(const std::string& text)
{
    Ini ini;
    std::string section;
    size_t pos = 0;
    while (pos < text.size()) {
        size_t end = text.find('\n', pos);
        std::string line = text.substr(pos, end == std::string::npos ? std::string::npos : end - pos);
        pos = end == std::string::npos ? text.size() : end + 1;
        line = Trim(line);
        if (line.empty() || line[0] == ';')
            continue;
        if (line[0] == '[') {
            size_t close = line.find(']');
            section = Lower(Trim(line.substr(1, close == std::string::npos ? std::string::npos : close - 1)));
            continue;
        }
        size_t eq = line.find('=');
        if (eq == std::string::npos)
            continue;
        std::string key = Lower(Trim(line.substr(0, eq)));
        std::string value = Trim(line.substr(eq + 1));
        if (value.size() >= 2 && (value[0] == '"' || value[0] == '\'') && value.back() == value[0])
            value = value.substr(1, value.size() - 2);
        std::string full = section + "/" + key;
        if (ini.keys.insert(full).second)
            ini.entries.push_back({full, value});
    }
    return ini;
}

std::set<std::string> g_named; // Config::Has's, of the file read
Config g_config;
bool g_read = false;

void ReadInt(const Ini& ini, const char* section, const char* key, int* out)
{
    std::string v;
    if (ini.Find(section, key, &v))
        *out = atoi(v.c_str()); // GetPrivateProfileInt's: the number it starts with, or 0
}

void ReadBool(const Ini& ini, const char* section, const char* key, bool* out)
{
    int v = *out ? 1 : 0;
    ReadInt(ini, section, key, &v);
    *out = v != 0;
}

void ReadString(const Ini& ini, const char* section, const char* key, size_t chars,
                std::string* out)
{
    std::string v;
    if (ini.Find(section, key, &v))
        *out = Truncate(v, chars);
}

void ReadKey(const Ini& ini, const char* section, const char* key, int* out)
{
    std::string v;
    if (!ini.Find(section, key, &v))
        return;
    int code = KeyCode(Truncate(v, 50));
    if (code == -2) {
        LogWarn("revival", "EfzRevival.ini [%s] %s = %s: not a key's name; none", section, key,
                v.c_str());
        code = kNoKey;
    }
    *out = code;
}

} // namespace

std::string KeyName(int key)
{
    if (key > kButton && key <= kButton + 32)
        return "BUTTON_" + std::to_string(key - kButton);
    for (const KeyEntry& k : kKeys) {
        if (k.code == key)
            return k.name;
    }
    return "None";
}

int KeyCode(const std::string& name)
{
    if (name.empty())
        return kNoKey;
    if (name.compare(0, 7, "BUTTON_") == 0) {
        int n = atoi(name.c_str() + 7);
        if (n >= 1 && n <= 32 && name == "BUTTON_" + std::to_string(n))
            return kButton + n;
        return -2;
    }
    for (const KeyEntry& k : kKeys) {
        if (name == k.name)
            return k.code;
    }
    return -2;
}

bool Config::Has(const char* section, const char* key) const
{
    return g_named.count(Lower(section) + "/" + Lower(key)) != 0;
}

Config ParseConfig(const std::string& text)
{
    Ini ini = ParseIni(text);
    g_named = ini.keys;
    Config c;
    const char* g = "Global";
    ReadBool(ini, g, "Debug", &c.debug);
    ReadInt(ini, g, "WindowX", &c.windowX);
    ReadInt(ini, g, "WindowY", &c.windowY);
    ReadInt(ini, g, "WindowWidth", &c.windowWidth);
    ReadInt(ini, g, "WindowHeight", &c.windowHeight);
    ReadInt(ini, g, "BackBufferWidth", &c.backBufferWidth);
    ReadInt(ini, g, "BackBufferHeight", &c.backBufferHeight);
    ReadKey(ini, g, "ToggleBGM", &c.toggleBGM);
    ReadBool(ini, g, "MuteBGM", &c.muteBGM);
    ReadBool(ini, g, "SoftwareRendering", &c.softwareRendering);
    ReadString(ini, g, "BGMFolder", 256, &c.bgmFolder);
    const char* n = "Network";
    ReadString(ini, n, "Name", 20, &c.name);
    ReadInt(ini, n, "MaxRollback", &c.maxRollback);
    ReadInt(ini, n, "Port", &c.port);
    ReadString(ini, n, "HolePunchingServer", 32, &c.holePunchingServer);
    ReadBool(ini, n, "AllowPracticeKeys", &c.allowPracticeKeys);
    ReadKey(ini, n, "IncreaseInputDelay", &c.increaseInputDelay);
    ReadKey(ini, n, "DecreaseInputDelay", &c.decreaseInputDelay);
    ReadKey(ini, n, "ToggleRemotePalettes", &c.toggleRemotePalettes);
    ReadBool(ini, n, "DisplayScore", &c.displayScore);
    ReadBool(ini, n, "LogScore", &c.logScore);
    ReadBool(ini, n, "SaveAllReplays", &c.saveAllReplays);
    ReadString(ini, n, "ReplayFolder", 256, &c.replayFolder);
    ReadKey(ini, n, "SavePreviousReplay", &c.savePreviousReplay);
    ReadString(ini, n, "BattleLogFile", 256, &c.battleLogFile);
    ReadBool(ini, n, "SaveBattleLog", &c.saveBattleLog);
    const char* p = "Practice";
    ReadKey(ini, p, "Pause", &c.pause);
    ReadKey(ini, p, "StepFrame", &c.stepFrame);
    ReadKey(ini, p, "Save", &c.saveState);
    ReadKey(ini, p, "Load", &c.loadState);
    ReadKey(ini, p, "ToggleRecord", &c.toggleRecord);
    ReadKey(ini, p, "ToggleReplay", &c.toggleReplay);
    ReadKey(ini, p, "SwitchStartCondition", &c.switchStartCondition);
    ReadKey(ini, p, "ToggleReplayRandom", &c.toggleReplayRandom);
    for (int i = 0; i < 5; i++) {
        char key[16];
        snprintf(key, sizeof(key), "SetBuffer%d", i + 1);
        ReadKey(ini, p, key, &c.setBuffer[i]);
    }
    ReadKey(ini, p, "ToggleDisplay", &c.toggleDisplay);
    ReadKey(ini, p, "ToggleHitBoxes", &c.toggleHitBoxes);
    ReadKey(ini, p, "ToggleHurtBoxes", &c.toggleHurtBoxes);
    ReadKey(ini, p, "ToggleCollisionBoxes", &c.toggleCollisionBoxes);
    ReadKey(ini, p, "SwitchPlayers", &c.switchPlayers);
    ReadKey(ini, p, "MirrorPlayers", &c.mirrorPlayers);
    ReadKey(ini, p, "IncreaseFPS", &c.increaseFPS);
    ReadKey(ini, p, "DecreaseFPS", &c.decreaseFPS);
    ReadKey(ini, p, "ResetFPS", &c.resetFPS);
    const char* t = "Tournament";
    ReadString(ini, t, "P1_Name", 20, &c.p1Name);
    ReadString(ini, t, "P2_Name", 20, &c.p2Name);
    ReadString(ini, t, "TournamentFolder", 256, &c.tournamentFolder);
    // Revival's own ini names a folder of the author's ("C:\Home\Music\"): taken as given,
    // it is simply not there.
    if (Lower(c.holePunchingServer) == "none")
        c.holePunchingServer.clear();
    return c;
}

std::string DecodeIni(const unsigned char* data, size_t size)
{
    if (size >= 2 && data[0] == 0xff && data[1] == 0xfe)
        return FromUtf16(data + 2, size - 2);
    if (size >= 2 && data[1] == 0 && data[0] != 0)
        return FromUtf16(data, size);
    if (size >= 3 && data[0] == 0xef && data[1] == 0xbb && data[2] == 0xbf)
        return std::string((const char*)data + 3, size - 3);
    return std::string((const char*)data, size);
}

void ReloadConfig()
{
    g_read = true;
    std::string text;
    FILE* f = OpenGameFile("EfzRevival.ini", "rb");
    bool found = f != nullptr;
    if (f) {
        std::vector<unsigned char> data;
        unsigned char buf[4096];
        size_t got;
        while ((got = fread(buf, 1, sizeof(buf), f)) > 0)
            data.insert(data.end(), buf, buf + got);
        fclose(f);
        text = DecodeIni(data.data(), data.size());
    }
    g_config = ParseConfig(text);
    g_config.path = found ? "EfzRevival.ini" : "";
    if (found)
        LogInfo("revival", "EfzRevival.ini read: %zu settings", g_named.size());
    else
        LogInfo("revival", "no EfzRevival.ini: Revival's own settings");
}

const Config& GetConfig()
{
    if (!g_read)
        ReloadConfig();
    return g_config;
}

} // namespace revival
} // namespace efz
