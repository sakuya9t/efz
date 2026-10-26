// The online session: rollback netplay, the input exchange with the launcher, desync
// detection records, replays and the battle log (OnlineSession.h).
//
// The scenes it follows (efz.exe's g_scene): 0 the title, 1 the menus, 2 character
// select, 3 the fight, 5 the results.
#include "OnlineSession.h"
#include <math.h>
#include <time.h>
#include <iomanip>
#include <sstream>
#include "EfzGame.h"
#include "EfzRevival.h"
#include "stubs/EfzTimer.h"
#include "Hook.h"
#include "Log.h"

// The rollback window: inputs older than this many frames are final.
static const int FIGHT_SETTLE_FRAMES = 20;
// Rollback stops this many frames after the match is decided.
static const int MATCH_OVER_FRAMES = 120;

// Converts to UTF-8, for the battle log. The same two functions are in Config.cpp's and
// the tournament session's objects, so each has its own (static) copy. They match
// (0x10073cc0 and 0x10073d00), but aren't annotated: the link map names a static
// function only by its decorated name, which is Config.cpp's to_utf8's.
static std::string to_utf8(const wchar_t *text, int length);

static std::string to_utf8(const std::wstring &text)
{
    return to_utf8(text.c_str(), text.size());
}

static std::string to_utf8(const wchar_t *text, int length)
{
    int size = WideCharToMultiByte(CP_UTF8, 0, text, length, NULL, 0, NULL, NULL);
    if (size == 0)
        return "";
    std::string result;
    result.resize(size);
    WideCharToMultiByte(CP_UTF8, 0, text, length, (char *)result.c_str(), size, NULL, NULL);
    return result;
}

// FUNCTION: 0x10073df0
OnlineSession::OnlineSession()
    : config_(L"./EfzRevival.ini"),
      initQueue_("Init", 1),
      netQueue_("Net", 100),
      syncQueue_("Sync", 200),
      quitQueue_("Quit", 1),
      loadMatchQueue_("LoadMatch", 100)
{
    localPlayer_ = 0;
    remotePlayer_ = 1;
    inputDelay_ = 0;
    maxRollback_ = 0;
    matchDelay_ = 0;
    launcher_ = NULL;
    music_ = NULL;
    frame_ = 0;
    scene_ = 0;
    newScene_ = 0;
    fightStart_ = 0;
    confirmedFrame_ = 0;
    syncedFrame_ = 0;
    sceneFrames_ = 0;
    hideRemotePalettes_ = false;
    palettesToggled_ = false;
    replayFlushed_ = false;
    replaySaved_ = false;
    matchOverFrame_ = INT_MAX - 1000;
    matchNumber_ = 0;
    lastFrame_ = 0;
    inputQueues_.push_back(SharedQueue<FrameInput>("InputP1", 600));
    inputQueues_.push_back(SharedQueue<FrameInput>("InputP2", 600));
    paletteQueues_.push_back(SharedQueue<ColorPalette>("PaletteP1", 10));
    paletteQueues_.push_back(SharedQueue<ColorPalette>("PaletteP2", 10));
    // The game's own handling of the replay at the end of a match (efz.exe 0x763f04 and
    // 0x763e50) goes to EfzRevival.cpp instead.
    hook((void *)0x763f04, 7, onReplayDone);
    hook((void *)0x763e50, 7, onReplayDone);
    char zero = 0;
    patchCode((void *)0x754c1a, &zero, 1);
    BYTE nops[0x14];
    memset(nops, 0x90, sizeof(nops));
    patchCode((void *)0x7599ed, nops, sizeof(nops));
}

// FUNCTION: 0x10073b60
OnlineSession::~OnlineSession()
{
    delete music_;
    music_ = NULL;
}

// FUNCTION: 0x10073220
void OnlineSession::start()
{
    g_log << "Start init player\n";
    g_log.flush();
    receiveInit();
    g_game.setRandomState(init_.seed);
    localPlayer_ = init_.player;
    setInputDelay(init_.delay);
    maxRollback_ = init_.rollback;
    p1Name_ = std::wstring(init_.names[0]);
    p2Name_ = std::wstring(init_.names[1]);
    launcher_ = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_TERMINATE, FALSE,
                            init_.launcher);
    g_log.flush();
    frame_ = 0;
    scene_ = 0;
    newScene_ = 0;
    fightStart_ = 0;
    confirmedFrame_ = 0;
    syncedFrame_ = 0;
    if (localPlayer_ == 0) {
        remotePlayer_ = 1;
        inputs_[0] = &localInputs_;
        inputs_[1] = &remoteInputs_;
    } else {
        remotePlayer_ = 0;
        inputs_[1] = &localInputs_;
        inputs_[0] = &remoteInputs_;
    }
    // P1's inputs through the menus to character select
    startInputs_.clear();
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(4, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(4, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0x10, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    startInputs_.push_back(FrameInput(0, 0));
    played_.resize(30);
    confirmed_.resize(30);
    soundCounts_.clear();
    states_.resize(60);
    for (int i = 0; i < 60; i++)
        states_[i].clear();
    sceneFrames_ = 0;
    hideRemotePalettes_ = false;
    palettesToggled_ = false;
    replayFlushed_ = false;
    replaySaved_ = false;
    matchOverFrame_ = INT_MAX - 1000;
    matchNumber_ = 0;
    lastFrame_ = 0;
    match_.wins[0] = 0;
    match_.wins[1] = 0;
    // TODO: differs: the original stores these two zeros and fpuControl's from eax
    unsigned int fpuControl = 0;
    match_.match = 1;
    _controlfp_s(&fpuControl, 0, 0);
    palettes_[localPlayer_].loadAll();
    frame_ = 0;
    if (localPlayer_ == 1) {
        g_log << "Switch inputs\n";
        g_log.flush();
        g_game.swapBindings();
    }
    for (FrameInput input : startInputs_) {
        if (localPlayer_ == 0)
            addInput(localPlayer_, input);
        else
            addInput(localPlayer_, FrameInput(0, 0));
    }
    g_game.setSpectating();
    g_log << "EFZ Init Done, local player is P" << init_.player + 1 << "\n";
    g_log << "FPU control word: " << std::hex << fpuControl << "\n";
    g_log << "Input delay " << std::dec << (int)init_.delay << " Max Roll "
          << (int)init_.rollback << " seed " << std::dec << init_.seed << "\n";
    g_log.flush();
    rounds_[0] = rounds_[1] = characters_[0] = characters_[1] = 0;

    // The battle log: a line for the session, then one per game
    std::wstringstream line;
    if (config_.saveBattleLog) {
        std::ifstream existing;
        existing.open(config_.battleLogFile);
        if (existing.good()) {
            battleLog_.open(config_.battleLogFile, std::ios::out | std::ios::app);
            battleLog_ << std::endl;
        } else {
            battleLog_.open(config_.battleLogFile, std::ios::out | std::ios::app);
        }
        existing.close();
    }
    line.str(L"");
    line << timestamp(false);
    battleLog_.width(19);
    battleLog_.flags(std::ios::left);
    battleLog_ << to_utf8(line.str());
    line.str(L"");
    line.width(21);
    line.flags(std::ios::right);
    line << p1Name_;
    line << " VS ";
    line.width(21);
    line.flags(std::ios::left);
    line << p2Name_;
    battleLog_.width(46);
    battleLog_.flags(std::ios::left);
    battleLog_ << to_utf8(line.str()) << std::endl;
    battleLog_.flush();

    playlist_.load(config_.bgmFolder);
    playlist_.shuffle();
    music_ = new MusicPlayer();
    music_->muted = config_.muteBGM != 0;
}

// FUNCTION: 0x10072e90
void OnlineSession::update()
{
    if (!isRunning(launcher_) || !quitQueue_.isEmpty()) {
        quitQueue_.clear();
        g_log << "Quit\n";
        g_log.flush();
        g_log.close();
        ExitProcess(0);
    }
    newScene_ = g_game.sceneId();
    if (newScene_ != scene_)
        sceneChanged();
    receivePing();
    receiveInputs(remotePlayer_);
    receivePalettes(remotePlayer_);
    if (frame_ > lastFrame_)
        lastFrame_ = frame_;
    g_log << std::dec << "Match " << matchNumber_ << " CurrentFrame " << frame_
          << " Current State: " << newScene_ << " input sizes " << localInputs_.size() << " "
          << remoteInputs_.size() << " inputDelay " << inputDelay_ << " MaxRoll "
          << maxRollback_ << std::endl;
    g_log.flush();
    if (music_->isFinished() && g_game.sceneId() == 3)
        music_->play(playlist_.current());
    int iterations;
    switch (newScene_) {
    case 0:
        iterations = menuFramesToRun();
        runQuitFrames(iterations);
        break;
    case 3:
        if (frame_ >= fightStart_ + FIGHT_SETTLE_FRAMES)
            maxRollback_ = config_.maxRollback;
        if (frame_ >= matchOverFrame_ + MATCH_OVER_FRAMES) {
            g_log << "Set maxRoll to 0\n";
            maxRollback_ = 0;
        }
        drawInfo();
        iterations = fightFramesToRun();
        runFightFrames(iterations);
        break;
    case 1:
        drawInfo();
        checkControls();
        // fall through
    case 2:
        iterations = menuFramesToRun();
        runMenuFrames(iterations);
        break;
    default:
        drawInfo();
        iterations = menuFramesToRun();
        runFrames(iterations);
        break;
    }
    g_log << "iterations: " << iterations << "\n";
    g_log.flush();
    // TODO: differs: the original calls a SharedQueue member (0x100232d0) that does
    inputQueues_[localPlayer_].notify();
}

// FUNCTION: 0x10072d30
// Loads the last confirmed state, runs the frames from there up to the current one with
// the rendering off, and the last one with it on.
void OnlineSession::runFightFrames(int count)
{
    DWORD begin = timeGetTime();
    rounds_[0] = g_game.playerFlagAc(0);
    rounds_[1] = g_game.playerFlagAc(1);
    g_game.setRendering(false);
    for (int i = 0; i < count; i++) {
        if (i == count - 1) {
            g_log << "Render Frame " << frame_ << "\n";
            g_game.setRendering(true);
        }
        int frame = frame_;
        if (canSave(frame))
            confirmed_[frame].clear();
        saveState();
        scene_ = g_game.sceneId();
        runFrame();
        if (frame_ > lastFrame_) {
            lastFrame_ = frame_;
            played_[frame_].clear();
        }
        if (g_game.sceneId() != scene_) {
            g_game.setRendering(true);
            return;
        }
    }
    loadState(frame_);
    int spent = timeGetTime() - begin;
    g_log << "Time spent " << spent << std::endl;
}

// Not called: its strings are all that is left of it.
void OnlineSession::logInputs(int count)
{
    g_log << "Frames to log: " << count << " inputsLocal " << localInputs_.size()
          << " inputsRemote " << remoteInputs_.size() << "\n";
    for (int i = frame_ - count; i < frame_; i++) {
        g_log << "Loc Frame " << i << ": " << (int)localInputs_[i].first << " "
              << (int)localInputs_[i].second << "  " << "\n";
        g_log << "Rem Frame " << i << ": " << (int)remoteInputs_[i].first << " "
              << (int)remoteInputs_[i].second << "  " << "\n";
    }
    g_log << " ";
}

// FUNCTION: 0x10072270
void OnlineSession::sceneChanged()
{
    g_log << "\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
             " Frames spent in state "
          << scene_ << " " << sceneFrames_
          << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
    g_log.flush();
    sceneFrames_ = 0;
    matchOverFrame_ = INT_MAX - 1000;
    scene_ = g_game.sceneId();
    if (g_game.sceneId() == 1) {
        g_game.setTextRender(true);
        inputDelay_ = (int)ceil(pingFrames(ping_.maximum));
    } else if (g_game.sceneId() == 3) {
        fightTime_ = std::chrono::system_clock::now();
        time_t now = time(NULL);
        tm local;
        localtime_s(&local, &now);
        g_log << std::put_time(&local, "%H:%M:%S");
        g_log << "\n\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
                 " MatchID "
              << matchNumber_ << "       Frame " << frame_
              << " !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n\n";
        g_log.flush();
        maxRollback_ = 0;
        setInputDelay(matchDelay_);
        fightStart_ = frame_;
        confirmedFrame_ = frame_;
        applyPalette(localPlayer_, g_game.paletteNumber(localPlayer_),
                     g_game.hasPalette(localPlayer_));
        applyPalette(remotePlayer_, g_game.paletteNumber(remotePlayer_),
                     g_game.hasPalette(remotePlayer_) && !hideRemotePalettes_);
        g_game.setTextRender(true);
        states_[frame_].save(true);
        g_game.setRandomSeed(g_game.newRandomSeed());
        characters_[0] = g_game.character(0);
        characters_[1] = g_game.character(1);
    } else if (g_game.sceneId() == 2) {
        playlist_.next();
        matchNumber_++;
        match_.match = matchNumber_;
        replayFlushed_ = false;
        replaySaved_ = false;
        sendLoadMatch(match_);
        g_game.setNetplay(true);
        g_game.setReplayName(replayFileName());
        g_game.setWriteReplay(true);
        g_game.setTextRender(false);
    } else if (g_game.sceneId() == 5) {
        match_.wins[g_game.roundWinner()]++;
        std::wstringstream line;
        std::wstringstream entry;
        line.str(L"");
        line << formatTime(fightTime_);
        entry.width(19);
        entry.flags(std::ios::left);
        entry << line.str();
        line.str(L"");
        line.width(21);
        line.flags(std::ios::right);
        line << g_game.characterNameW(characters_[0]);
        line << " VS ";
        line.width(21);
        line.flags(std::ios::left);
        line << g_game.characterNameW(characters_[1]);
        entry.width(46);
        entry.flags(std::ios::left);
        entry << line.str();
        line.str(L"");
        line.width(1);
        line << "Rounds: " << rounds_[0] << " " << rounds_[1];
        entry.width(15);
        entry.flags(std::ios::left);
        entry << line.str();
        line.str(L"");
        line << "Duration: " << formatDuration(fightTime_, std::chrono::system_clock::now());
        entry.width(20);
        entry.flags(std::ios::left);
        entry << line.str();
        line.str(L"");
        line << "Score: ";
        line.width(3);
        line.flags(std::ios::right);
        line << match_.wins[0];
        line << " ";
        line.flags(std::ios::left);
        line << match_.wins[1];
        entry.width(15);
        entry.flags(std::ios::left);
        entry << line.str();
        entry << std::endl;
        entry.flush();
        battleLog_ << to_utf8(entry.str());
        battleLog_.flush();
        rounds_[0] = 0;
        rounds_[1] = 0;
    } else if (g_game.sceneId() == 0 && scene_ == 1) {
        // Back to the title from the menus: the player quit
        if (!quitQueue_.isFull()) {
            bool quit = true;
            quitQueue_.push(quit);
        }
        ExitProcess(0);
    }
}

// FUNCTION: 0x10072000
void OnlineSession::keyPressed(int key)
{
    if ((g_game.sceneId() == 1 || g_game.sceneId() == 5) && key == config_.savePreviousReplay) {
        g_log << "Flush " << replayFlushed_ << "\n";
        replayFlushed_ = true;
        replaySaved_ |= g_game.flushReplay();
    }
    if (key == config_.toggleBGM) {
        music_->muted = !music_->muted;
        if (music_->muted)
            stopSound(g_game.musicId());
        else
            playSound(g_game.musicId(), 1);
    }
    if (g_game.sceneId() == 3) {
        if (key == config_.increaseInputDelay)
            setInputDelay(inputDelay_ + 1);
        if (key == config_.decreaseInputDelay) {
            int delay = inputDelay_ - 1;
            int minimum = (int)ceil(pingFrames(ping_.maximum)) - maxRollback_;
            if (delay < minimum)
                delay = minimum;
            setInputDelay(delay);
        }
        if (key == config_.toggleRemotePalettes) {
            hideRemotePalettes_ = !hideRemotePalettes_;
            if (g_game.hasPalette(remotePlayer_))
                palettesToggled_ = true;
        }
    }
}

// FUNCTION: 0x100719e0
// The overlay: delay, ping, the replay message and the names (with the wins).
void OnlineSession::drawInfo()
{
    g_game.clearText();
    int ping = ping_.last;
    std::wstringstream text;
    if (g_game.sceneId() == 3) {
        int delay = inputDelay_;
        if (delay <= 1)
            text << "Delay: " << delay << " frame";
        else
            text << "Delay: " << delay << " frames";
        g_game.addText(text.str(), 10, 465, DT_LEFT);
        text.str(L"");
    }
    text << "Ping: " << ping << "ms";
    g_game.addText(text.str(), 630, 465, DT_RIGHT);
    text.str(L"");
    if (replayFlushed_) {
        if (config_.saveAllReplays)
            text << "All replays get autosaved";
        else if (replaySaved_)
            text << "Saved replay to disk";
        else
            text << "Failed to save replay";
        g_game.addText(text.str(), 10, 20, DT_LEFT);
        text.str(L"");
    }
    int p1x = 10;
    int p2x = 630;
    if (config_.displayScore) {
        text << "Wins: " << match_.wins[0];
        g_game.addText(text.str(), p1x, 5, DT_LEFT);
        p1x = 80;
        text.str(L"");
    }
    text << p1Name_;
    g_game.addText(text.str(), p1x, 5, DT_LEFT);
    text.str(L"");
    if (config_.displayScore) {
        text << "Wins: " << match_.wins[1] << "   ";
        g_game.addText(text.str(), 630, 5, DT_RIGHT);
        p2x = 560;
        text.str(L"");
    }
    text << p2Name_;
    g_game.addText(text.str(), p2x, 5, DT_RIGHT);
    text.str(L"");
}

// FUNCTION: 0x100718d0
void OnlineSession::sendSync(const FrameInput &p1, const FrameInput &p2)
{
    if (!syncQueue_.isFull()) {
        syncQueue_.push(makeSyncBlock(frame_, p1, p2));
        return;
    }
    g_log << "Full Sync queue\n";
}

// FUNCTION: 0x100712a0
// Rollback: back to the last confirmed frame, with the sounds of the frames to run again
// counted so that they don't play twice.
void OnlineSession::loadState(int to)
{
    if (g_game.sceneId() != 3 || maxRollback_ == 0)
        return;
    int frame = loadFrame();
    countSounds(frame, to);
    soundCounts_.clear();
    int first = frame;
    if (fightStart_ > first)
        first = fightStart_;
    for (int i = first; i <= to; i++) {
        std::map<WORD, int> sounds = played_[i];
        for (std::pair<const WORD, int> sound : sounds)
            soundCounts_[sound.first] += sound.second;
    }
    g_log << "Load " << frame << " from " << frame_ << "\n";
    states_[frame].load();
}

// FUNCTION: 0x10071430
// Stops the sounds played on predicted inputs that neither were confirmed nor will be
// played again, and forgets them.
void OnlineSession::countSounds(int from, int to)
{
    std::map<WORD, int> recent;
    std::map<WORD, int> confirmed;
    std::map<WORD, int> replayed;
    for (int i = from; i <= to; i++) {
        std::map<WORD, int> sounds = played_[i];
        for (std::pair<const WORD, int> sound : sounds)
            replayed[sound.first] += sound.second;
    }
    for (int i = from - maxRollback_; i <= from; i++) {
        std::map<WORD, int> sounds = played_[i];
        for (std::pair<const WORD, int> sound : sounds)
            recent[sound.first] += sound.second;
    }
    for (int i = from - maxRollback_; i <= from; i++) {
        std::map<WORD, int> sounds = confirmed_[i];
        for (std::pair<const WORD, int> sound : sounds)
            confirmed[sound.first] += sound.second;
    }
    for (std::pair<const WORD, int> sound : recent) {
        if (confirmed.find(sound.first) == confirmed.end()
            && replayed.find(sound.first) == replayed.end()) {
            g_game.stopSound(sound.first);
            for (int i = from - maxRollback_ - 1; i < to; i++)
                played_[i].erase(sound.first);
        }
    }
}

// FUNCTION: 0x10071170
// Out of a fight there is no rollback: run the frames the remote inputs cover, pausing
// when there are none.
int OnlineSession::menuFramesToRun()
{
    int delay = (int)ceil(pingFrames(ping_.maximum));
    int last = localInputs_.size() - delay - 1;
    if ((unsigned int)last >= remoteInputs_.size()) {
        g_log << "Pause, too few remote inputs, ping " << ping_.maximum << " delay " << delay
              << "\n";
        g_log.flush();
        // TODO: differs: a SharedQueue member in the original (see update)
        inputQueues_[localPlayer_].notify();
        return 0;
    }
    addInput(localPlayer_, readInput());
    // TODO: differs: the original adds the 1 before subtracting frame_
    int iterations = last + 1 - frame_;
    g_log << "Iterations " << iterations << " delay " << delay << std::endl;
    return iterations;
}

// FUNCTION: 0x10070f10
int OnlineSession::fightFramesToRun()
{
    if (maxRollback_ == 0)
        return menuFramesToRun();
    int ahead = localInputs_.size() - remoteInputs_.size();
    FrameInput last = localInputs_.back();
    if (ahead > maxRollback_ + inputDelay_) {
        g_log << "\t\tPause, need more remote frames " << localInputs_.size() << " "
              << remoteInputs_.size() << "\n";
        g_log.flush();
        return 0;
    }
    addInput(localPlayer_, readInput());
    if ((unsigned int)(inputDelay_ + frame_) >= localInputs_.size() && frame_ > 0) {
        g_log << "\t\tPause, too little inputDelay " << localInputs_.size() << " "
              << remoteInputs_.size() << "\n";
        g_log.flush();
        addInput(localPlayer_, last);
        return 0;
    }
    int behind = (int)floor(pingFrames(ping_.minimum)) - 1;
    if (ahead < behind) {
        g_log << "\t\tAdd frame, remote is ahead " << localInputs_.size() << " "
              << remoteInputs_.size() << " " << behind << "\n";
        g_log.flush();
        addInput(localPlayer_, last);
    }
    return localInputs_.size() - frame_ - inputDelay_ - 1;
}

// FUNCTION: 0x10070c10
// Saves the state of the current frame if both players' inputs for it are known.
void OnlineSession::saveState()
{
    if (g_game.sceneId() != 3)
        return;
    if (canSave(frame_)) {
        int p2 = inputs_[1]->at(frame_).first;
        int p1 = inputs_[0]->at(frame_).first;
        g_log << "Save " << frame_ << " Inputs " << p1 << " " << p2 << std::endl;
        g_log.flush();
        if (palettesToggled_) {
            g_log << "Toggle remote palettes\n";
            applyPalette(remotePlayer_, g_game.paletteNumber(remotePlayer_),
                         g_game.hasPalette(remotePlayer_) && !hideRemotePalettes_);
            g_game.refreshPalette(remotePlayer_);
            palettesToggled_ = false;
        }
        states_[frame_].save(true);
        states_[frame_].addInt(&frame_);
        states_[frame_].addInt(&sceneFrames_);
        confirmedFrame_++;
        g_game.setWriteReplay(true);
        g_game.recordInputs(inputs_[0]->at(frame_), inputs_[1]->at(frame_));
        if (g_game.isMatchOver() && frame_ < matchOverFrame_)
            matchOverFrame_ = frame_;
    } else {
        g_game.setWriteReplay(false);
    }
}

// FUNCTION: 0x10070b10
// Picks up key.ini changes and joysticks plugged in, every 32 frames while the game's
// window is in front. P2 plays with P1's keys.
void OnlineSession::checkControls()
{
    static int frames;
    if (frames % 32 == 0 && GetForegroundWindow() == g_game.window()) {
        if (g_game.keyIniChanged()) {
            g_game.reloadKeys();
            g_game.reacquireJoysticks();
            if (localPlayer_ == 1) {
                g_log << "Switch inputs\n";
                g_log.flush();
                g_game.swapBindings();
            }
        } else if (g_game.joystickAdded()) {
            g_game.reacquireJoysticks();
            if (localPlayer_ == 1) {
                g_log << "Switch inputs\n";
                g_log.flush();
                g_game.swapBindings();
            }
        }
    }
    frames++;
}

// FUNCTION: 0x10070bd0
bool OnlineSession::canSave(unsigned int frame)
{
    if (frame < localInputs_.size() && frame < remoteInputs_.size()
        && frame == (unsigned int)confirmedFrame_)
        return true;
    return false;
}

// FUNCTION: 0x10070e70
// Runs one frame of the game, sending its sync record the first time it is final.
void OnlineSession::runFrame()
{
    if (frame_ == syncedFrame_ && remoteInputs_.size() > (unsigned int)frame_
        && localInputs_.size() > (unsigned int)frame_) {
        sendSync(inputs_[0]->at(frame_), inputs_[1]->at(frame_));
        syncedFrame_++;
    }
    g_game.runFrame();
    sceneFrames_++;
    frame_++;
}

// FUNCTION: 0x10070ef0
// The frame a rollback goes back to: the last confirmed one, not before the fight.
int OnlineSession::loadFrame()
{
    int frame = confirmedFrame_ - 1;
    if (fightStart_ > frame)
        frame = fightStart_;
    return frame;
}

// FUNCTION: 0x10070de0
void OnlineSession::runFrames(int count)
{
    for (int i = 0; i < count; i++) {
        if ((unsigned int)frame_ >= localInputs_.size())
            addInput(localPlayer_, readInput());
        if ((unsigned int)frame_ >= remoteInputs_.size())
            return;
        scene_ = g_game.sceneId();
        runFrame();
        if (g_game.sceneId() != scene_)
            return;
    }
}

// FUNCTION: 0x10071ec0
// The menus and character select: the palettes go to the launcher every 30 frames.
void OnlineSession::runMenuFrames(int count)
{
    int player = localPlayer_;
    if (g_game.canChoosePalette(player) && g_game.hasPalette(player)
        && frame_ % 30 == 0) {
        int character = g_game.character(player);
        int number = g_game.paletteNumber(player);
        ColorPalette palette;
        if (palettes_[player].find(character, true, number, &palette))
            sendPalette(localPlayer_, palette);
    }
    for (int i = 0; i < count; i++) {
        if ((unsigned int)frame_ >= localInputs_.size() - 1)
            addInput(localPlayer_, readInput());
        scene_ = g_game.sceneId();
        runFrame();
        if (g_game.sceneId() != scene_)
            return;
    }
}

// FUNCTION: 0x10072ca0
void OnlineSession::runQuitFrames(int count)
{
    if (scene_ != 0)
        ExitProcess(0);
    for (int i = 0; i < count; i++) {
        if ((unsigned int)frame_ >= localInputs_.size())
            addInput(localPlayer_, readInput());
        scene_ = g_game.sceneId();
        runFrame();
        if (g_game.sceneId() != scene_)
            break;
    }
}

// FUNCTION: 0x100721d0
FrameInput OnlineSession::readInput()
{
    BYTE input = g_game.cleanInput(g_game.efzInput(localPlayer_));
    BYTE keys = g_game.functionKeys();
    if (g_game.sceneId() == 3) {
        if (init_.practiceKeys)
            keys &= 0x23;
        else
            keys &= 0x20;
    }
    if (g_game.sceneId() == 1) {
        keys &= 0x20;
        if (keys != 0 && !quitQueue_.isFull()) {
            bool quit = true;
            quitQueue_.push(quit);
        }
    }
    return FrameInput(input, keys);
}

// FUNCTION: 0x10071db0
void OnlineSession::addInput(int player, const FrameInput &input)
{
    if (!inputQueues_[player].isFull()) {
        inputs_[player]->push_back(input);
        inputQueues_[player].push(input);
    }
}

// FUNCTION: 0x10071e00
void OnlineSession::receiveInputs(int player)
{
    while (!inputQueues_[player].isEmpty()) {
        FrameInput input = inputQueues_[player].pop();
        inputs_[player]->push_back(input);
    }
}

// FUNCTION: 0x10071fb0
void OnlineSession::setInputDelay(int delay)
{
    if (delay <= 0) {
        inputDelay_ = 0;
        matchDelay_ = 0;
    } else if (delay >= 20) {
        inputDelay_ = 20;
        matchDelay_ = 20;
    } else {
        matchDelay_ = delay;
        inputDelay_ = delay;
    }
}

// FUNCTION: 0x10071d80
// A round trip in frames each way.
float OnlineSession::pingFrames(int ping)
{
    return (float)(ping / (g_game.timer->getMsPerFrame() * 2));
}

// FUNCTION: 0x10071e70
void OnlineSession::applyPalette(int player, int number, bool custom)
{
    ColorPalette palette;
    palettes_[player].find(g_game.character(player), custom, number, &palette);
    g_game.setPalette(player, palette);
}

// FUNCTION: 0x100717d0
void OnlineSession::sendPalette(int player, const ColorPalette &palette)
{
    if (!paletteQueues_[player].isFull())
        paletteQueues_[player].push(palette);
}

// FUNCTION: 0x10071960
void OnlineSession::receivePalettes(int player)
{
    while (!paletteQueues_[player].isEmpty()) {
        ColorPalette palette = paletteQueues_[player].pop();
        palettes_[player].add(palette);
    }
}

// FUNCTION: 0x10071880
void OnlineSession::receiveInit()
{
    if (!initQueue_.isEmpty())
        init_ = initQueue_.pop();
}

// FUNCTION: 0x10071810
void OnlineSession::receivePing()
{
    while (!netQueue_.isEmpty())
        ping_ = netQueue_.pop();
}

// FUNCTION: 0x100717a0
void OnlineSession::sendLoadMatch(MatchInfo match)
{
    if (!loadMatchQueue_.isFull())
        loadMatchQueue_.push(match);
}

// FUNCTION: 0x10071930
bool OnlineSession::isRunning(HANDLE process)
{
    DWORD code = 0xffffffff;
    GetExitCodeProcess(process, &code);
    if (code != STILL_ACTIVE)
        return false;
    return true;
}

// FUNCTION: 0x10070a60
std::wstring OnlineSession::timestamp(bool fileName)
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

// FUNCTION: 0x100709c0
std::wstring OnlineSession::formatTime(const std::chrono::system_clock::time_point &time)
{
    time_t seconds = std::chrono::system_clock::to_time_t(time);
    tm local;
    localtime_s(&local, &seconds);
    std::wstringstream stream;
    stream << std::put_time(&local, L"%Y/%m/%d %H:%M:%S");
    return stream.str();
}

// FUNCTION: 0x10070890
std::wstring OnlineSession::formatDuration(const std::chrono::system_clock::time_point &start,
                                           const std::chrono::system_clock::time_point &end)
{
    std::chrono::system_clock::duration elapsed = end - start;
    std::chrono::minutes minutes = std::chrono::duration_cast<std::chrono::minutes>(elapsed);
    std::chrono::seconds seconds = std::chrono::duration_cast<std::chrono::seconds>(elapsed -= minutes);
    std::wstringstream stream;
    stream.width(3);
    stream << minutes.count();
    stream << ":";
    stream.width(2);
    stream << std::setfill(L'0');
    stream << seconds.count();
    return stream.str();
}

// FUNCTION: 0x100706a0
// <ReplayFolder>\<time> <P1 name> (<P1 character>) vs <P2 name> (<P2 character>).rep
std::wstring OnlineSession::replayFileName()
{
    std::wstringstream name;
    std::string p1 = g_game.characterName(g_game.character(0));
    std::string p2 = g_game.characterName(g_game.character(1));
    name << config_.replayFolder << "\\" << timestamp(true) << " " << p1Name_ << " ("
         << std::wstring(p1.begin(), p1.end()) << ")" << " vs " << p2Name_ << " ("
         << std::wstring(p2.begin(), p2.end()) << ")" << ".rep";
    return name.str();
}

// FUNCTION: 0x10072b60
void OnlineSession::playSound(WORD id, int loop)
{
    if (playlist_.size() != 0 && g_game.isMusic(id)
        && (g_game.sceneId() == 2 || g_game.sceneId() == 3)) {
        music_->play(playlist_.current());
        return;
    }
    if (music_->muted && g_game.isMusic(id))
        return;
    if (g_game.sceneId() != 3) {
        g_game.playSound(id, loop);
        return;
    }
    unsigned int frame = frame_;
    if (frame < localInputs_.size() && frame < remoteInputs_.size())
        confirmed_[frame][id]++;
    soundCounts_[id]--;
    if (soundCounts_[id] < 0) {
        played_[frame_][id]++;
        g_game.playSound(id, loop);
    }
}

// FUNCTION: 0x10072140
// The fight's update: F4-F8 and Esc as both players pressed them.
void OnlineSession::fightUpdate(void *frame)
{
    BYTE *keys = (BYTE *)frame;
    if (g_game.sceneId() != 3)
        return;
    unsigned int i = frame_;
    char local = localInputs_[i].second;
    if (i >= remoteInputs_.size())
        i = remoteInputs_.size() - 1;
    char pressed = remoteInputs_[i].second | local;
    // TODO: differs: the original keeps this a loop (a rotating mask, a pointer and a
    // count); this one gets unrolled
    for (int key = 0; key < 5; key++)
        keys[0x3e + key] = (pressed & (1 << key)) ? 0x80 : 0;
    keys[1] = (pressed & 0xe0) << 2;
}

// FUNCTION: 0x100731b0
void OnlineSession::input(BYTE *input, int player)
{
    if (player == localPlayer_) {
        *input = localInputs_[frame_].first;
        return;
    }
    int frame = frame_;
    if (frame >= (int)remoteInputs_.size() - 1)
        frame = remoteInputs_.size() - 1;
    *input = remoteInputs_[frame].first;
}

// FUNCTION: 0x10070650
void OnlineSession::setVolume(WORD id, int volume)
{
    if (playlist_.size() != 0 && g_game.isMusic(id) && music_->isPlaying()) {
        music_->setVolume(volume);
        return;
    }
    g_game.setSoundVolume(id, volume);
}

// FUNCTION: 0x10070600
void OnlineSession::stopSound(WORD id)
{
    if (playlist_.size() != 0 && g_game.isMusic(id) && music_->isPlaying()) {
        music_->stop();
        return;
    }
    g_game.stopSound(id);
}

// The CRT's inline time() and localtime_s() (time.inl) close the object:
// FUNCTION: 0x10073dd0 _time
// FUNCTION: 0x10073de0 _localtime_s
