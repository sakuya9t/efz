// EfzRevival.ini: the launcher's settings, the names its keys may be given, and the
// address and text helpers that go with them.
#include "Config.h"
// OBJECT: 0x401000 0x40ff60
#include "stubs/Network.h"
#include "Version.h"
#include <boost/algorithm/string.hpp>
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <cstdlib>
#include <vector>

// FUNCTION: 0x405e90
Config::Config(const std::wstring &path)
{
    path_ = path;
    loadKeyNames();
    loadPadNames();
    load(path);
}

// FUNCTION: 0x406780
Config::~Config()
{
}

// FUNCTION: 0x40a770
bool isValidAddress(const std::string &address)
{
    std::vector<std::string> parts;
    std::string text = boost::algorithm::trim_copy(address);
    text.erase(std::remove(text.begin(), text.end(), '['), text.end());
    text.erase(std::remove(text.begin(), text.end(), ']'), text.end());
    boost::algorithm::split(parts, text, boost::algorithm::is_any_of(":"));
    if (parts.size() < 2)
        return false;
    int port = atoi(parts[parts.size() - 1].c_str());
    std::string host = parts[0];
    for (unsigned int i = 1; i < parts.size() - 1; i++) {
        host.append(":");
        host.append(parts[i]);
    }
    try {
        boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(host), port);
    } catch (std::exception e) {
        return false;
    }
    return true;
}

void Config::reload()
{
    load(path_);
}

// FUNCTION: 0x40aa90
bool Config::load(const std::wstring &path)
{
    debug = readInt(L"Global", L"Debug") != 0;
    windowX = readInt(L"Global", L"WindowX");
    windowY = readInt(L"Global", L"WindowY");
    windowWidth = readInt(L"Global", L"WindowWidth");
    windowHeight = readInt(L"Global", L"WindowHeight");
    backBufferWidth = readInt(L"Global", L"BackBufferWidth");
    backBufferHeight = readInt(L"Global", L"BackBufferHeight");
    toggleBGM = readKey(L"Global", L"ToggleBGM");
    muteBGM = readInt(L"Global", L"MuteBGM");
    softwareRendering = readInt(L"Global", L"SoftwareRendering");
    bgmFolder = readString(L"Global", L"BGMFolder", 256);

    name = readString(L"Network", L"Name", 20);
    maxRollback = readInt(L"Network", L"MaxRollback");
    port = readInt(L"Network", L"Port");
    protocol = readString(L"Network", L"Protocol", 16);
    player = readInt(L"Network", L"Player");
    allowPracticeKeys = readInt(L"Network", L"AllowPracticeKeys");
    player = 1;
    holePunchingServer = parseEndpoint(to_utf8(readString(L"Network", L"HolePunchingServer", 32)));
    std::wstring allowSpectatingText = readString(L"Network", L"AllowSpectating", 16);
    bool spectatingOff = boost::algorithm::iequals(allowSpectatingText, L"False");
    allowSpectating = !spectatingOff;
    battleLogFile = readString(L"Network", L"BattleLogFile", 256);
    saveBattleLog = readInt(L"Network", L"SaveBattleLog") != 0;
    increaseInputDelay = readKey(L"Network", L"IncreaseInputDelay");
    decreaseInputDelay = readKey(L"Network", L"DecreaseInputDelay");
    increaseSpecSpeed = readKey(L"Network", L"IncreaseSpecSpeed");
    decreaseSpecSpeed = readKey(L"Network", L"DecreaseSpecSpeed");
    toggleRemotePalettes = readKey(L"Network", L"ToggleRemotePalettes ");
    displayScore = readInt(L"Network", L"DisplayScore");
    logScore = readInt(L"Network", L"LogScore");
    saveAllReplays = readInt(L"Network", L"SaveAllReplays");
    replayFolder = readString(L"Network", L"ReplayFolder", 256);
    savePreviousReplay = readKey(L"Network", L"SavePreviousReplay");
    replayFormat = readString(L"Network", L"ReplayFormat", 256);

    pause = readKey(L"Practice", L"Pause");
    stepFrame = readKey(L"Practice", L"StepFrame");
    saveState = readKey(L"Practice", L"Save");
    loadState = readKey(L"Practice", L"Load");
    toggleReplay = readKey(L"Practice", L"ToggleReplay");
    toggleRecord = readKey(L"Practice", L"ToggleRecord");
    switchStartCondition = readKey(L"Practice", L"SwitchStartCondition ");
    toggleReplayRandom = readKey(L"Practice", L"ToggleReplayRandom");
    toggleDisplay = readKey(L"Practice", L"ToggleDisplay");
    toggleHitBoxes = readKey(L"Practice", L"ToggleHitBoxes");
    toggleHurtBoxes = readKey(L"Practice", L"ToggleHurtBoxes");
    toggleCollisionBoxes = readKey(L"Practice", L"ToggleCollisionBoxes");
    switchPlayers = readKey(L"Practice", L"SwitchPlayers");
    mirrorPlayers = readKey(L"Practice", L"MirrorPlayers");
    increaseFPS = readKey(L"Practice", L"IncreaseFPS");
    decreaseFPS = readKey(L"Practice", L"DecreaseFPS");
    resetFPS = readKey(L"Practice", L"ResetFPS");
    setBuffer[0] = readKey(L"Practice", L"SetBuffer1");
    setBuffer[1] = readKey(L"Practice", L"SetBuffer2");
    setBuffer[2] = readKey(L"Practice", L"SetBuffer3");
    setBuffer[3] = readKey(L"Practice", L"SetBuffer4");
    setBuffer[4] = readKey(L"Practice", L"SetBuffer5");

    p1Name = readString(L"Tournament", L"P1_Name", 20);
    p2Name = readString(L"Tournament", L"P2_Name", 20);
    tournamentFolder = readString(L"Tournament", L"TournamentFolder", 256);
    return true;
}

// FUNCTION: 0x40bf40
void Config::loadKeyNames()
{
    keys_[L""] = -1;
    keys_[L"None"] = -1;
    keys_[L"DIK_ESCAPE"] = DIK_ESCAPE;
    keys_[L"DIK_1"] = DIK_1;
    keys_[L"DIK_2"] = DIK_2;
    keys_[L"DIK_3"] = DIK_3;
    keys_[L"DIK_4"] = DIK_4;
    keys_[L"DIK_5"] = DIK_5;
    keys_[L"DIK_6"] = DIK_6;
    keys_[L"DIK_7"] = DIK_7;
    keys_[L"DIK_8"] = DIK_8;
    keys_[L"DIK_9"] = DIK_9;
    keys_[L"DIK_0"] = DIK_0;
    keys_[L"DIK_MINUS"] = DIK_MINUS;
    keys_[L"DIK_EQUALS"] = DIK_EQUALS;
    keys_[L"DIK_BACK"] = DIK_BACK;
    keys_[L"DIK_TAB"] = DIK_TAB;
    keys_[L"DIK_Q"] = DIK_Q;
    keys_[L"DIK_W"] = DIK_W;
    keys_[L"DIK_E"] = DIK_E;
    keys_[L"DIK_R"] = DIK_R;
    keys_[L"DIK_T"] = DIK_T;
    keys_[L"DIK_Y"] = DIK_Y;
    keys_[L"DIK_U"] = DIK_U;
    keys_[L"DIK_I"] = DIK_I;
    keys_[L"DIK_O"] = DIK_O;
    keys_[L"DIK_P"] = DIK_P;
    keys_[L"DIK_LBRACKET"] = DIK_LBRACKET;
    keys_[L"DIK_RBRACKET"] = DIK_RBRACKET;
    keys_[L"DIK_RETURN"] = DIK_RETURN;
    keys_[L"DIK_LCONTROL"] = DIK_LCONTROL;
    keys_[L"DIK_A"] = DIK_A;
    keys_[L"DIK_S"] = DIK_S;
    keys_[L"DIK_D"] = DIK_D;
    keys_[L"DIK_F"] = DIK_F;
    keys_[L"DIK_G"] = DIK_G;
    keys_[L"DIK_H"] = DIK_H;
    keys_[L"DIK_J"] = DIK_J;
    keys_[L"DIK_K"] = DIK_K;
    keys_[L"DIK_L"] = DIK_L;
    keys_[L"DIK_SEMICOLON"] = DIK_SEMICOLON;
    keys_[L"DIK_APOSTROPHE"] = DIK_APOSTROPHE;
    keys_[L"DIK_GRAVE"] = DIK_GRAVE;
    keys_[L"DIK_LSHIFT"] = DIK_LSHIFT;
    keys_[L"DIK_BACKSLASH"] = DIK_BACKSLASH;
    keys_[L"DIK_Z"] = DIK_Z;
    keys_[L"DIK_X"] = DIK_X;
    keys_[L"DIK_C"] = DIK_C;
    keys_[L"DIK_V"] = DIK_V;
    keys_[L"DIK_B"] = DIK_B;
    keys_[L"DIK_N"] = DIK_N;
    keys_[L"DIK_M"] = DIK_M;
    keys_[L"DIK_COMMA"] = DIK_COMMA;
    keys_[L"DIK_PERIOD"] = DIK_PERIOD;
    keys_[L"DIK_SLASH"] = DIK_SLASH;
    keys_[L"DIK_RSHIFT"] = DIK_RSHIFT;
    keys_[L"DIK_MULTIPLY"] = DIK_MULTIPLY;
    keys_[L"DIK_LMENU"] = DIK_LMENU;
    keys_[L"DIK_SPACE"] = DIK_SPACE;
    keys_[L"DIK_CAPITAL"] = DIK_CAPITAL;
    keys_[L"DIK_F1"] = DIK_F1;
    keys_[L"DIK_F2"] = DIK_F2;
    keys_[L"DIK_F3"] = DIK_F3;
    keys_[L"DIK_F4"] = DIK_F4;
    keys_[L"DIK_F5"] = DIK_F5;
    keys_[L"DIK_F6"] = DIK_F6;
    keys_[L"DIK_F7"] = DIK_F7;
    keys_[L"DIK_F8"] = DIK_F8;
    keys_[L"DIK_F9"] = DIK_F9;
    keys_[L"DIK_F10"] = DIK_F10;
    keys_[L"DIK_NUMLOCK"] = DIK_NUMLOCK;
    keys_[L"DIK_SCROLL"] = DIK_SCROLL;
    keys_[L"DIK_NUMPAD7"] = DIK_NUMPAD7;
    keys_[L"DIK_NUMPAD8"] = DIK_NUMPAD8;
    keys_[L"DIK_NUMPAD9"] = DIK_NUMPAD9;
    keys_[L"DIK_SUBTRACT"] = DIK_SUBTRACT;
    keys_[L"DIK_NUMPAD4"] = DIK_NUMPAD4;
    keys_[L"DIK_NUMPAD5"] = DIK_NUMPAD5;
    keys_[L"DIK_NUMPAD6"] = DIK_NUMPAD6;
    keys_[L"DIK_ADD"] = DIK_ADD;
    keys_[L"DIK_NUMPAD1"] = DIK_NUMPAD1;
    keys_[L"DIK_NUMPAD2"] = DIK_NUMPAD2;
    keys_[L"DIK_NUMPAD3"] = DIK_NUMPAD3;
    keys_[L"DIK_NUMPAD0"] = DIK_NUMPAD0;
    keys_[L"DIK_DECIMAL"] = DIK_DECIMAL;
    keys_[L"DIK_OEM_102"] = DIK_OEM_102;
    keys_[L"DIK_F11"] = DIK_F11;
    keys_[L"DIK_F12"] = DIK_F12;
    keys_[L"DIK_F13"] = DIK_F13;
    keys_[L"DIK_F14"] = DIK_F14;
    keys_[L"DIK_F15"] = DIK_F15;
    keys_[L"DIK_KANA"] = DIK_KANA;
    keys_[L"DIK_ABNT_C1"] = DIK_ABNT_C1;
    keys_[L"DIK_CONVERT"] = DIK_CONVERT;
    keys_[L"DIK_NOCONVERT"] = DIK_NOCONVERT;
    keys_[L"DIK_YEN"] = DIK_YEN;
    keys_[L"DIK_ABNT_C2"] = DIK_ABNT_C2;
    keys_[L"DIK_NUMPADEQUALS"] = DIK_NUMPADEQUALS;
    keys_[L"DIK_PREVTRACK"] = DIK_PREVTRACK;
    keys_[L"DIK_AT"] = DIK_AT;
    keys_[L"DIK_COLON"] = DIK_COLON;
    keys_[L"DIK_UNDERLINE"] = DIK_UNDERLINE;
    keys_[L"DIK_KANJI"] = DIK_KANJI;
    keys_[L"DIK_STOP"] = DIK_STOP;
    keys_[L"DIK_AX"] = DIK_AX;
    keys_[L"DIK_UNLABELED"] = DIK_UNLABELED;
    keys_[L"DIK_NEXTTRACK"] = DIK_NEXTTRACK;
    keys_[L"DIK_NUMPADENTER"] = DIK_NUMPADENTER;
    keys_[L"DIK_RCONTROL"] = DIK_RCONTROL;
    keys_[L"DIK_MUTE"] = DIK_MUTE;
    keys_[L"DIK_CALCULATOR"] = DIK_CALCULATOR;
    keys_[L"DIK_PLAYPAUSE"] = DIK_PLAYPAUSE;
    keys_[L"DIK_MEDIASTOP"] = DIK_MEDIASTOP;
    keys_[L"DIK_VOLUMEDOWN"] = DIK_VOLUMEDOWN;
    keys_[L"DIK_VOLUMEUP"] = DIK_VOLUMEUP;
    keys_[L"DIK_WEBHOME"] = DIK_WEBHOME;
    keys_[L"DIK_NUMPADCOMMA"] = DIK_NUMPADCOMMA;
    keys_[L"DIK_DIVIDE"] = DIK_DIVIDE;
    keys_[L"DIK_SYSRQ"] = DIK_SYSRQ;
    keys_[L"DIK_RMENU"] = DIK_RMENU;
    keys_[L"DIK_PAUSE"] = DIK_PAUSE;
    keys_[L"DIK_HOME"] = DIK_HOME;
    keys_[L"DIK_UP"] = DIK_UP;
    keys_[L"DIK_PRIOR"] = DIK_PRIOR;
    keys_[L"DIK_LEFT"] = DIK_LEFT;
    keys_[L"DIK_RIGHT"] = DIK_RIGHT;
    keys_[L"DIK_END"] = DIK_END;
    keys_[L"DIK_DOWN"] = DIK_DOWN;
    keys_[L"DIK_NEXT"] = DIK_NEXT;
    keys_[L"DIK_INSERT"] = DIK_INSERT;
    keys_[L"DIK_DELETE"] = DIK_DELETE;
    keys_[L"DIK_LWIN"] = DIK_LWIN;
    keys_[L"DIK_RWIN"] = DIK_RWIN;
    keys_[L"DIK_APPS"] = DIK_APPS;
    keys_[L"DIK_POWER"] = DIK_POWER;
    keys_[L"DIK_SLEEP"] = DIK_SLEEP;
    keys_[L"DIK_WAKE"] = DIK_WAKE;
    keys_[L"DIK_WEBSEARCH"] = DIK_WEBSEARCH;
    keys_[L"DIK_WEBFAVORITES"] = DIK_WEBFAVORITES;
    keys_[L"DIK_WEBREFRESH"] = DIK_WEBREFRESH;
    keys_[L"DIK_WEBSTOP"] = DIK_WEBSTOP;
    keys_[L"DIK_WEBFORWARD"] = DIK_WEBFORWARD;
    keys_[L"DIK_WEBBACK"] = DIK_WEBBACK;
    keys_[L"DIK_MYCOMPUTER"] = DIK_MYCOMPUTER;
    keys_[L"DIK_MAIL"] = DIK_MAIL;
    keys_[L"DIK_MEDIASELECT"] = DIK_MEDIASELECT;
    keys_[L"DIK_BACKSPACE"] = DIK_BACKSPACE;
    keys_[L"DIK_NUMPADSTAR"] = DIK_NUMPADSTAR;
    keys_[L"DIK_LALT"] = DIK_LALT;
    keys_[L"DIK_CAPSLOCK"] = DIK_CAPSLOCK;
    keys_[L"DIK_NUMPADMINUS"] = DIK_NUMPADMINUS;
    keys_[L"DIK_NUMPADPLUS"] = DIK_NUMPADPLUS;
    keys_[L"DIK_NUMPADPERIOD"] = DIK_NUMPADPERIOD;
    keys_[L"DIK_NUMPADSLASH"] = DIK_NUMPADSLASH;
    keys_[L"DIK_RALT"] = DIK_RALT;
    keys_[L"DIK_UPARROW"] = DIK_UPARROW;
    keys_[L"DIK_PGUP"] = DIK_PGUP;
    keys_[L"DIK_LEFTARROW"] = DIK_LEFTARROW;
    keys_[L"DIK_RIGHTARROW"] = DIK_RIGHTARROW;
    keys_[L"DIK_DOWNARROW"] = DIK_DOWNARROW;
    keys_[L"DIK_PGDN"] = DIK_PGDN;
    keys_[L"DIK_CIRCUMFLEX"] = DIK_CIRCUMFLEX;
}

// FUNCTION: 0x40e3c0
void Config::loadPadNames()
{
    keys_[L"BUTTON_1"] = 0x201;
    keys_[L"BUTTON_2"] = 0x202;
    keys_[L"BUTTON_3"] = 0x203;
    keys_[L"BUTTON_4"] = 0x204;
    keys_[L"BUTTON_5"] = 0x205;
    keys_[L"BUTTON_6"] = 0x206;
    keys_[L"BUTTON_7"] = 0x207;
    keys_[L"BUTTON_8"] = 0x208;
    keys_[L"BUTTON_9"] = 0x209;
    keys_[L"BUTTON_10"] = 0x20a;
    keys_[L"BUTTON_11"] = 0x20b;
    keys_[L"BUTTON_12"] = 0x20c;
    keys_[L"BUTTON_13"] = 0x20d;
    keys_[L"BUTTON_14"] = 0x20e;
    keys_[L"BUTTON_15"] = 0x20f;
    keys_[L"BUTTON_16"] = 0x210;
    keys_[L"BUTTON_17"] = 0x211;
    keys_[L"BUTTON_18"] = 0x212;
    keys_[L"BUTTON_19"] = 0x213;
    keys_[L"BUTTON_20"] = 0x214;
    keys_[L"BUTTON_21"] = 0x215;
    keys_[L"BUTTON_22"] = 0x216;
    keys_[L"BUTTON_23"] = 0x217;
    keys_[L"BUTTON_24"] = 0x218;
    keys_[L"BUTTON_25"] = 0x219;
    keys_[L"BUTTON_26"] = 0x21a;
    keys_[L"BUTTON_27"] = 0x21b;
    keys_[L"BUTTON_28"] = 0x21c;
    keys_[L"BUTTON_29"] = 0x21d;
    keys_[L"BUTTON_30"] = 0x21e;
    keys_[L"BUTTON_31"] = 0x21f;
    keys_[L"BUTTON_32"] = 0x220;
}

// FUNCTION: 0x40eee0
int Config::readInt(const std::wstring &section, const std::wstring &key)
{
    return GetPrivateProfileIntW(section.data(), key.data(), 0, path_.c_str());
}

// FUNCTION: 0x40ef10
int Config::readKey(const std::wstring &section, const std::wstring &key)
{
    std::wstring keyName = readString(section, key, 50);
    std::map<std::wstring, int>::iterator it = keys_.find(keyName);
    if (it == keys_.end())
        return -1;
    return it->second;
}

// FUNCTION: 0x40efa0
std::wstring Config::readString(const std::wstring &section, const std::wstring &key, int size)
{
    int length = size + 1;
    wchar_t *buffer = (wchar_t *)malloc(length * sizeof(wchar_t));
    GetPrivateProfileStringW(section.data(), key.data(), L"None", buffer, length, path_.c_str());
    std::wstring value(buffer);
    free(buffer);
    return value;
}

// FUNCTION: 0x40fbc0 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@2@@Z
std::string to_utf8(const std::wstring &text)
{
    return to_utf8(text.c_str(), text.size());
}

// FUNCTION: 0x40fc00 ?to_utf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PB_WH@Z
std::string to_utf8(const wchar_t *text, int length)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, text, length, NULL, 0, NULL, NULL);
    if (size == 0)
        return "";
    std::string result;
    result.resize(size);
    WideCharToMultiByte(CP_UTF8, 0, text, length, (char *)result.c_str(), size, NULL, NULL);
    return result;
}
