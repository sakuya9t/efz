// The tournament session (mode 3). See TournamentSession.h.
//
// The results file gets a header line when a set begins (the time, then "P1 VS P2")
// and a line per match: when it began, the two characters, the rounds each won, how
// long it took and the set's score.
#include "TournamentSession.h"
#include <iomanip>
#include <sstream>
#include <time.h>
#include "EfzGame.h"
#include "EfzRevival.h"
#include "Hook.h"
#include "Log.h"

// FUNCTION: 0x1002d8f0 ??_GTournamentSession@@UAEPAXI@Z

// The tournament object's own copies of Config.cpp's UTF-8 conversions.
// FUNCTION: 0x10079d50 ?toUtf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@PB_WH@Z
static std::string toUtf8(const wchar_t *text, int length)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, text, length, NULL, 0, NULL, NULL);
    if (size == 0)
        return std::string("");
    std::string result;
    result.resize(size);
    WideCharToMultiByte(CP_UTF8, 0, text, length, (char *)result.c_str(), size, NULL, NULL);
    return std::string(result);
}

// FUNCTION: 0x10079d10 ?toUtf8@@YA?AV?$basic_string@DU?$char_traits@D@std@@V?$allocator@D@2@@std@@ABV?$basic_string@_WU?$char_traits@_W@std@@V?$allocator@_W@2@@2@@Z
static std::string toUtf8(const std::wstring &text)
{
    return toUtf8(text.c_str(), (int)text.size());
}

// "minutes:seconds"
// FUNCTION: 0x10078a50
std::wstring TournamentSession::formatDuration(const std::chrono::system_clock::time_point &start,
                                              const std::chrono::system_clock::time_point &end)
{
    std::chrono::system_clock::duration duration = end - start;
    std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
    duration -= minutes;
    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
    std::wstringstream text;
    text.width(3);
    text << minutes.count() << L":";
    text.width(2);
    text << std::setfill(L'0') << seconds.count();
    return text.str();
}

// FUNCTION: 0x10078d90
std::wstring TournamentSession::formatTime(const std::chrono::system_clock::time_point &time)
{
    time_t seconds = std::chrono::system_clock::to_time_t(time);
    tm local;
    localtime_s(&local, &seconds);
    std::wstringstream text;
    text << std::put_time(&local, L"%Y/%m/%d %H:%M:%S");
    return text.str();
}

// The tournament only asks for the readable form, so link-time code generation drops
// the file name's.
// FUNCTION: 0x10078e30
std::wstring TournamentSession::timestamp(bool fileName)
{
    time_t now = time(NULL);
    tm local;
    localtime_s(&local, &now);
    std::wstringstream stream;
    if (fileName)
        stream << std::put_time(&local, L"%Y%m%d-%H%M%S");
    else
        stream << std::put_time(&local, L"%Y/%m/%d %H:%M:%S");
    return stream.str();
}

// FUNCTION: 0x10079e40
TournamentSession::TournamentSession()
    : escHoldFrames_(80), config_(L"./EfzRevival.ini")
{
    g_log << "Starting Tournament Mode\n";
    g_log.flush();
    hookCall((void *)0x763f04, 7, onReplayDone);
    hookCall((void *)0x763e50, 7, onReplayDone);
    char zero = 0;
    patchCode((void *)0x754c1a, &zero, 1);
    lastScene_ = 0;
    memset(&setNumber_, 0, sizeof(setNumber_) + sizeof(wins_));
    // P1 on the title menu: down, down, A (VS PLAYER)
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(4, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(4, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0x10, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    menuInputs_.push(FrameInput(0, 0));
    if (config_.saveBattleLog) {
        std::ifstream test;
        std::wstring path = config_.tournamentFolder + L"tournament_results.txt";
        test.open(path);
        if (test.good()) {
            g_log << "Tournament log exists\n";
            results_.open(path, std::ios::out | std::ios::app);
            g_log.flush();
        } else {
            g_log << "Tournament log doesn't exist\n";
            g_log << toUtf8(path) << "\n";
            g_log.flush();
            results_.open(path, std::ios::out | std::ios::app);
        }
        test.close();
    }
    DWORD nops[5] = { 0x90909090, 0x90909090, 0x90909090, 0x90909090, 0x90909090 };
    patchCode((void *)0x7599ed, nops, sizeof(nops));
}

// FUNCTION: 0x10079cc0
TournamentSession::~TournamentSession()
{
}

// FUNCTION: 0x10079cb0
void TournamentSession::start()
{
    g_log << "Init\n";
    g_log.flush();
}

// FUNCTION: 0x10079c10
void TournamentSession::update()
{
    if (lastScene_ != g_game.sceneId())
        sceneChanged();
    if (g_game.sceneId() == 3 || g_game.sceneId() == 1 || g_game.sceneId() == 5)
        drawInfo();
    lastScene_ = g_game.sceneId();
    switch (g_game.sceneId()) {
    case 0:
        titleFrame();
        return;
    case 1:
        checkDevices();
        selectFrame();
        return;
    case 3:
        fightFrame();
        return;
    default:
        g_game.runFrame();
    }
}

// FUNCTION: 0x10078a40
void TournamentSession::keyPressed(int key)
{
}

// FUNCTION: 0x100789e0
void TournamentSession::input(BYTE *input, int player)
{
    if (!menuInputs_.empty()) {
        if (player == 1) {
            *input = 0;
            return;
        }
        *input = menuInputs_.front().first;
        menuInputs_.pop();
        return;
    }
    *input = g_game.cleanInput(g_game.efzInput(player));
}

// No function keys in a fight, and Esc only once held.
// FUNCTION: 0x10078960
void TournamentSession::fightUpdate(void *frame)
{
    static bool held;
    static int frames;
    if (g_game.sceneId() == 3) {
        BYTE *keys = (BYTE *)frame;
        memset(keys + DIK_F1, 0, 15);
        if (keys[DIK_ESCAPE] == 0x80) {
            g_log << "Esc\n";
            g_log.flush();
            frames++;
            if (!held || frames < escHoldFrames_) {
                keys[DIK_ESCAPE] = 0;
                held = true;
                return;
            }
        } else {
            held = false;
            frames = 0;
        }
    }
}

// FUNCTION: 0x10078b80
std::wstring TournamentSession::replayFileName()
{
    time_t now = time(NULL);
    tm local;
    localtime_s(&local, &now);
    std::wstringstream name;
    std::string p1 = g_game.characterName(g_game.character(0));
    std::string p2 = g_game.characterName(g_game.character(1));
    name << config_.tournamentFolder << "\\" << std::put_time(&local, L"%Y%m%d-%H%M%S") << " "
         << config_.p1Name << " (" << std::wstring(p1.begin(), p1.end()) << ")" << " vs " << config_.p2Name
         << " (" << std::wstring(p2.begin(), p2.end()) << ")" << ".rep";
    return name.str();
}

// Every 32 frames: key.ini and the pads.
// FUNCTION: 0x10078ed0
void TournamentSession::checkDevices()
{
    static int frames;
    if (frames % 32 == 0) {
        if (GetForegroundWindow() == g_game.window()) {
            if (g_game.keyIniChanged()) {
                g_game.reloadKeys();
                g_game.reacquireJoysticks();
            } else if (!g_game.pollDevices(0) || !g_game.pollDevices(1)) {
                g_game.reacquireJoysticks();
            }
        }
    }
    frames++;
}

// FUNCTION: 0x10078f40
void TournamentSession::drawInfo()
{
    g_game.clearText();
    std::wstringstream text;
    int right = 630;
    text << "Wins: " << wins_[0];
    g_game.addText(text.str(), 10, 5, 0);
    text.str(L"");
    text << config_.p1Name;
    g_game.addText(text.str(), 80, 5, 0);
    text.str(L"");
    if (config_.displayScore != 0) {
        text << "Wins: " << wins_[1] << "   ";
        g_game.addText(text.str(), 630, 5, 2);
        right = 560;
        text.str(L"");
    }
    text << config_.p2Name;
    g_game.addText(text.str(), right, 5, 2);
}

// FUNCTION: 0x10079110
void TournamentSession::sceneChanged()
{
    if (g_game.sceneId() == 3) {
        g_game.setTextRender(true);
        g_game.setRandomSeed(g_game.newRandomSeed());
        fightStart_ = std::chrono::system_clock::now();
        characters_[0] = g_game.character(0);
        characters_[1] = g_game.character(1);
        return;
    }
    if (g_game.sceneId() == 1) {
        g_game.setTextRender(true);
        return;
    }
    if (g_game.sceneId() == 2) {
        p1Name_ = std::wstring(config_.p1Name);
        p2Name_ = std::wstring(config_.p2Name);
        g_game.setNetplay(true);
        g_game.setReplayName(replayFileName());
        g_game.setWriteReplay(true);
        g_game.setTextRender(false);
        if (wins_[0] != 0 || wins_[1] != 0)
            return;
        // a new set: its header
        std::wstringstream line;
        line.str(L"");
        line << timestamp(false);
        results_ << std::endl;
        results_.width(19);
        results_.flags(std::ios::left);
        results_ << toUtf8(line.str());
        line.str(L"");
        line.width(21);
        line.flags(std::ios::right);
        line << p1Name_;
        line << " VS ";
        line.width(21);
        line.flags(std::ios::left);
        line << p2Name_;
        results_.width(46);
        results_.flags(std::ios::left);
        results_ << toUtf8(line.str()) << std::endl;
        results_.flush();
    } else if (g_game.sceneId() == 5) {
        wins_[g_game.roundWinner()]++;
        std::wstringstream cell;
        std::wstringstream row;
        cell.str(L"");
        cell << formatTime(fightStart_);
        row.width(19);
        row.flags(std::ios::left);
        row << cell.str();
        cell.str(L"");
        cell.width(21);
        cell.flags(std::ios::right);
        cell << g_game.characterNameW(characters_[0]);
        cell << " VS ";
        cell.width(21);
        cell.flags(std::ios::left);
        cell << g_game.characterNameW(characters_[1]);
        row.width(46);
        row.flags(std::ios::left);
        row << cell.str();
        cell.str(L"");
        cell.width(1);
        cell << "Rounds: " << rounds_[0] << " " << rounds_[1];
        row.width(15);
        row.flags(std::ios::left);
        row << cell.str();
        cell.str(L"");
        cell << "Duration: " << formatDuration(fightStart_, std::chrono::system_clock::now());
        row.width(20);
        row.flags(std::ios::left);
        row << cell.str();
        cell.str(L"");
        cell << "Score: ";
        cell.width(3);
        cell.flags(std::ios::right);
        cell << wins_[0];
        cell << " ";
        cell.flags(std::ios::left);
        cell << wins_[1];
        row.width(15);
        row.flags(std::ios::left);
        row << cell.str();
        row << std::endl;
        row.flush();
        results_ << toUtf8(row.str());
        results_.flush();
        rounds_[0] = 0;
        rounds_[1] = 0;
    }
}

// FUNCTION: 0x10079a60
void TournamentSession::fightFrame()
{
    rounds_[0] = g_game.playerFlagAc(0);
    rounds_[1] = g_game.playerFlagAc(1);
    g_game.runFrame();
}

// Every 64 frames of the character select: the ini again (the players' names may have
// changed: a new set), the results file, key.ini and new pads.
// FUNCTION: 0x10079a80
void TournamentSession::selectFrame()
{
    static int frames;
    if (frames % 64 == 0) {
        frames = 0;
        std::wstring p1 = config_.p1Name;
        std::wstring p2 = config_.p2Name;
        config_.reload();
        if (config_.saveBattleLog) {
            if (results_.is_open())
                results_.close();
            std::wstring path = config_.tournamentFolder + L"tournament_results.txt";
            results_.open(path, std::ios::out | std::ios::app);
        }
        if (p1.compare(config_.p1Name) != 0 || p2.compare(config_.p2Name) != 0) {
            memset(wins_, 0, sizeof(wins_));
            setNumber_++;
        }
        if (GetForegroundWindow() == g_game.window()) {
            if (g_game.keyIniChanged()) {
                g_game.reloadKeys();
                g_game.reacquireJoysticks();
            } else if (g_game.joystickAdded()) {
                g_game.reacquireJoysticks();
            }
        }
    }
    frames++;
    g_game.runFrame();
}

// Back on the title once the menu inputs ran out: the tournament is over.
// FUNCTION: 0x10079bf0
void TournamentSession::titleFrame()
{
    if (menuInputs_.empty())
        ExitProcess(0);
    g_game.runFrame();
}
