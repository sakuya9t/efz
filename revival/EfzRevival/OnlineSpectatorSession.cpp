// The spectator session (mode 1). See OnlineSpectatorSession.h.
#include "OnlineSpectatorSession.h"
#include "OnlineSession.h"   // makeSyncBlock
#include <float.h>
#include <iomanip>
#include <sstream>
#include <time.h>
#include "EfzGame.h"
#include "EfzRevival.h"
#include "Hook.h"
#include "Log.h"
#include "../DDRAW/EfzTimer.h"

// FUNCTION: 0x100281a0 ??_GSpectatorSession@@UAEPAXI@Z

// FUNCTION: 0x100756a0
SyncBlock makeSyncBlock(int frame, const FrameInput &inputP1, const FrameInput &inputP2)
{
    SyncBlock sync;
    sync.frame = frame;
    sync.state = g_game.sceneId();
    sync.inputP1 = inputP1;
    sync.inputP2 = inputP2;
    unsigned int control = 0;
    _controlfp_s(&control, 0, 0);
    sync.fpuCW = control;
    sync.rng = g_game.newRandomSeed();
    if (g_game.sceneId() == 3) {
        CScene *fight = EFZ_SCENES[3];
        CPlayer *p1 = *fight->players[0];
        CPlayer *p2 = *fight->players[1];
        sync.stateP1 = g_game.playerAction(0);
        sync.stateP2 = g_game.playerAction(1);
        sync.p1x = p1->x;
        sync.p1y = p1->y;
        sync.p2x = p2->x;
        sync.p2y = p2->y;
    } else {
        sync.stateP1 = 0;
        sync.stateP2 = 0;
        sync.p1x = 0;
        sync.p1y = 0;
        sync.p2x = 0;
        sync.p2y = 0;
    }
    g_log << "Sync " << sync.toString();
    g_log.flush();
    return sync;
}

// FUNCTION: 0x10075370
SpectatorSession::SpectatorSession()
    : config_(L"./EfzRevival.ini"), initQueue_("Init", 1), syncQueue_("Sync", 200),
      quitQueue_("Quit", 1), loadMatchQueue_("LoadMatch", 100)
{
    speed_ = 1;
    launcher_ = NULL;
    frame_ = 0;
    syncedFrame_ = 0;
    scene_ = 0;
    newScene_ = 0;
    flushed_ = false;
    saved_ = false;
    matchNumber_ = 0;
    music_ = NULL;
    inputQueues_.push_back(SharedQueue<FrameInput>("InputP1", 600));
    inputQueues_.push_back(SharedQueue<FrameInput>("InputP2", 600));
    paletteQueues_.push_back(SharedQueue<ColorPalette>("PaletteP1", 10));
    paletteQueues_.push_back(SharedQueue<ColorPalette>("PaletteP2", 10));
    // the end of a match goes through onReplayDone, as online
    hookCall((void *)0x763f04, 7, onReplayDone);
    hookCall((void *)0x763e50, 7, onReplayDone);
    char zero = 0;
    patchCode((void *)0x754c1a, &zero, 1);
    DWORD nops[5] = { 0x90909090, 0x90909090, 0x90909090, 0x90909090, 0x90909090 };
    patchCode((void *)0x7599ed, nops, sizeof(nops));
}

// FUNCTION: 0x10075250
SpectatorSession::~SpectatorSession()
{
    delete music_;
}

// FUNCTION: 0x10075010
void SpectatorSession::start()
{
    g_log << "Start init Spectator\n";
    g_log.flush();
    receiveInit();
    g_game.setRandomState(init_.seed);
    g_game.setSpectating();
    p1Name_ = std::wstring(init_.names[0]);
    p2Name_ = std::wstring(init_.names[1]);
    launcher_ = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_TERMINATE, FALSE,
                            init_.launcher);
    g_log.flush();
    g_game.setRendering(true);
    speed_ = 1;
    frame_ = 0;
    inputs_[0] = std::vector<FrameInput>();
    inputs_[1] = std::vector<FrameInput>();
    syncedFrame_ = 0;
    scene_ = 0;
    newScene_ = 0;
    memset(&hostMatch_, 0, sizeof(hostMatch_) + sizeof(wins_) + sizeof(matchNumber_));
    flushed_ = false;
    saved_ = false;
    unsigned int control = 0;
    _controlfp_s(&control, 0, 0);
    music_ = new MusicPlayer();
    music_->muted = false;
    playlist_.load(config_.bgmFolder);
    playlist_.shuffle();
    g_log << "FPU control word: " << std::hex << control << "\n";
    g_log << "Random Seed: " << std::dec << init_.seed << "\n";
    g_log << "EFZ Init Start as Spec\n";
    g_log.flush();
}

// Runs the frames the launcher has inputs for, at most speed_ of them, drawing only the
// last (and the versus screen's).
// FUNCTION: 0x10074c60
void SpectatorSession::update()
{
    receiveInputs(0);
    receiveInputs(1);
    receivePalettes(0);
    receivePalettes(1);
    receiveLoadMatch();
    if (!isRunning(launcher_) || !quitQueue_.isEmpty() || g_game.functionKeys() == 0x20) {
        quitQueue_.clear();
        g_log << "Quit\n";
        g_log.flush();
        g_log.close();
        ExitProcess(0);
    }
    if (music_->isFinished() && g_game.sceneId() == 3)
        music_->play(playlist_.current());
    newScene_ = g_game.sceneId();
    if (newScene_ != scene_) {
        sceneChanged();
        g_game.setRendering(true);
    } else {
        g_game.setRendering(false);
    }
    int available = inputs_[0].size() - 1;
    g_log << "Update, available frames " << available << " current frame " << frame_ << "\n";
    g_log.flush();
    if (frame_ <= available) {
        int frames = available - frame_;
        if (speed_ < frames)
            frames = speed_;
        if (g_game.sceneId() == 3 || g_game.sceneId() == 1 || g_game.sceneId() == 5)
            drawInfo();
        for (int i = 0; i < frames; i++) {
            if (frame_ == syncedFrame_) {
                sendSync();
                syncedFrame_++;
            }
            if (i == frames - 1 || g_game.sceneId() == 2)
                g_game.setRendering(true);
            g_game.recordInputs(inputs_[0][frame_], inputs_[1][frame_]);
            scene_ = g_game.sceneId();
            g_game.runFrame();
            frame_++;
            if (g_game.sceneId() != scene_)
                break;
        }
        g_game.setRendering(true);
    }
}

// FUNCTION: 0x10074f40
void SpectatorSession::keyPressed(int key)
{
    if (g_game.sceneId() == 1 || g_game.sceneId() == 5) {
        if (key == config_.savePreviousReplay) {
            g_log << "Flush " << flushed_ << "\n";
            flushed_ = true;
            saved_ |= g_game.flushReplay();
        }
    }
    if (key == config_.toggleBGM) {
        music_->muted = !music_->muted;
        if (music_->muted)
            stopSound(g_game.musicId());
        else
            playSound(g_game.musicId(), 1);
    }
    if (key == config_.increaseSpecSpeed)
        setSpeed(speed_ + 1);
    if (key == config_.decreaseSpecSpeed)
        setSpeed(speed_ - 1);
}

// FUNCTION: 0x10074ef0
void SpectatorSession::input(BYTE *input, int player)
{
    if ((unsigned int)frame_ < inputs_[player].size()) {
        *input = inputs_[player][frame_].first;
        return;
    }
    throw "CurrentFrame > playerInput.size";
}

// The players' function keys (F4-F8, Esc) of the frame, from the inputs' second byte.
// FUNCTION: 0x10074e80
void SpectatorSession::fightUpdate(void *frame)
{
    if (g_game.sceneId() != 3)
        return;
    BYTE *keys = (BYTE *)frame;
    char pressed = inputs_[0][frame_].second | inputs_[1][frame_].second;
    // TODO: differs: the original keeps this a loop (a mask rotated left each time).
    for (int i = 0; i < 5; i++)
        keys[DIK_F4 + i] = (pressed & (1 << i)) ? 0x80 : 0;
    keys[DIK_ESCAPE] = (pressed & 0xe0) << 2;
}

// FUNCTION: 0x100742b0
void SpectatorSession::playSound(WORD id, int arg)
{
    if (playlist_.size() != 0 && g_game.isMusic(id)
        && (g_game.sceneId() == 2 || g_game.sceneId() == 3)) {
        music_->play(playlist_.current());
        return;
    }
    if (music_->muted && g_game.isMusic(id))
        return;
    g_game.playSound(id, arg);
}

// FUNCTION: 0x10074260
void SpectatorSession::setVolume(WORD id, int volume)
{
    if (playlist_.size() != 0 && g_game.isMusic(id) && music_->isPlaying()) {
        music_->setVolume(volume);
        return;
    }
    g_game.setSoundVolume(id, volume);
}

// FUNCTION: 0x10074210
void SpectatorSession::stopSound(WORD id)
{
    if (playlist_.size() != 0 && g_game.isMusic(id) && music_->isPlaying()) {
        music_->stop();
        return;
    }
    g_game.stopSound(id);
}

// FUNCTION: 0x10074330
bool SpectatorSession::isRunning(HANDLE process)
{
    DWORD code = 0xffffffff;
    GetExitCodeProcess(process, &code);
    if (code != STILL_ACTIVE)
        return false;
    return true;
}

// FUNCTION: 0x10074360
std::wstring SpectatorSession::replayFileName()
{
    time_t now = time(NULL);
    tm local;
    localtime_s(&local, &now);
    std::wstringstream name;
    std::string p1 = g_game.characterName(g_game.character(0));
    std::string p2 = g_game.characterName(g_game.character(1));
    name << config_.replayFolder << "\\" << std::put_time(&local, L"%Y%m%d-%H%M%S") << " "
         << p1Name_ << " (" << std::wstring(p1.begin(), p1.end()) << ")" << " vs " << p2Name_
         << " (" << std::wstring(p2.begin(), p2.end()) << ")" << ".rep";
    return name.str();
}

// FUNCTION: 0x10074560
void SpectatorSession::drawInfo()
{
    g_game.clearText();
    std::wstringstream text;
    if (flushed_) {
        const char *message;
        if (config_.saveAllReplays != 0)
            message = "All replays get autosaved";
        else
            message = saved_ ? "Saved replay to disk" : "Failed to save replay";
        text << message;
        g_game.addText(text.str(), 10, 20, 0);
        text.str(L"");
    }
    int left = 10;
    int right = 630;
    if (config_.displayScore != 0) {
        text << "Wins: " << wins_[0];
        g_game.addText(text.str(), left, 5, 0);
        text.str(L"");
        left = 80;
    }
    text << p1Name_;
    g_game.addText(text.str(), left, 5, 0);
    text.str(L"");
    if (config_.displayScore != 0) {
        text << "Wins: " << wins_[1] << "   ";
        g_game.addText(text.str(), 630, 5, 2);
        text.str(L"");
        right = 560;
    }
    text << p2Name_;
    g_game.addText(text.str(), right, 5, 2);
    text.str(L"");
    text << "Game Speed: " << speed_ << "x";
    g_game.addText(text.str(), 10, 465, 0);
    text.str(L"");
    text << "Match " << matchNumber_ << " / " << hostMatch_;
    g_game.addText(text.str(), 630, 465, 2);
}

// FUNCTION: 0x100748b0
void SpectatorSession::applyPalette(int player)
{
    if (g_game.hasPalette(player)) {
        ColorPalette palette;
        palettes_[player].find(g_game.character(player), true, g_game.paletteNumber(player),
                               &palette);
        g_game.setPalette(player, palette);
    }
}

// FUNCTION: 0x10074910
void SpectatorSession::sceneChanged()
{
    scene_ = g_game.sceneId();
    if (g_game.sceneId() == 3) {
        applyPalette(0);
        applyPalette(1);
        g_game.refreshPalette(0);
        g_game.refreshPalette(1);
        g_game.setTextRender(true);
        g_game.setRandomSeed(g_game.newRandomSeed());
        return;
    }
    if (g_game.sceneId() == 1) {
        g_game.setTextRender(true);
        return;
    }
    if (g_game.sceneId() == 2) {
        playlist_.next();
        flushed_ = false;
        saved_ = false;
        g_game.setNetplay(true);
        g_game.setReplayName(replayFileName());
        g_game.setWriteReplay(true);
        matchNumber_++;
        g_game.setTextRender(false);
        return;
    }
    if (g_game.sceneId() == 5)
        wins_[g_game.roundWinner()]++;
}

// FUNCTION: 0x10074a60
void SpectatorSession::sendSync()
{
    SyncBlock sync = makeSyncBlock(frame_, inputs_[0].at(frame_), inputs_[1].at(frame_));
    syncQueue_.push(sync);
}

// FUNCTION: 0x10074ab0
void SpectatorSession::receivePalettes(int player)
{
    while (!paletteQueues_[player].isEmpty()) {
        ColorPalette palette = paletteQueues_[player].pop();
        palettes_[player].add(palette);
    }
}

// FUNCTION: 0x10074b30
void SpectatorSession::receiveInputs(int player)
{
    while (!inputQueues_[player].isEmpty()) {
        FrameInput input = inputQueues_[player].pop();
        inputs_[player].push_back(input);
    }
}

// FUNCTION: 0x10074ba0
void SpectatorSession::receiveLoadMatch()
{
    if (!loadMatchQueue_.isEmpty())
        hostMatch_ = loadMatchQueue_.pop().match;
}

// FUNCTION: 0x10074be0
void SpectatorSession::receiveInit()
{
    if (!initQueue_.isEmpty())
        init_ = initQueue_.pop();
}

// FUNCTION: 0x10074c30
void SpectatorSession::setSpeed(int speed)
{
    if (speed > 9) {
        speed_ = 9;
        return;
    }
    if (speed < 1)
        speed = 1;
    speed_ = speed;
}
