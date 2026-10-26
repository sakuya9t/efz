// The practice session (VS PLAYER, mode 2).
//
// Pause holds the fight back: Game::setGameSpeed(0) patches out the scene's updates (the
// frame still runs, so the scene is drawn and the overlay updated), and a frame step
// runs one frame at speed 3 before patching them out again, counting the frames
// stepped. Each player's inputs go through a Recorder, which records them into a
// buffer, replays one (or a random non-empty one), and delays them; switching players
// swaps the two players' key bindings, and mirroring reflects both around the
// stage's middle.
#include "PracticeSession.h"
#include <stdlib.h>
#include <sstream>
#include "InputDisplay.h"
#include "EfzGame.h"
#include "../DDRAW/EfzTimer.h"

// DDRAW.dll's frame timer (getEfzTimer): its inline functions are emitted here, the first
// object to use them.
// FUNCTION: 0x10028c80 EfzTimer::setFps
// FUNCTION: 0x10028cf0 EfzTimer::reset

// FUNCTION: 0x10029090 ??_GPracticeSession@@UAEPAXI@Z

// FUNCTION: 0x10076da0 ??0Recorder@@QAE@H@Z
Recorder::Recorder(int player)
{
    player_ = player;
}

// FUNCTION: 0x10076e00
Recorder::~Recorder()
{
}

// FUNCTION: 0x10076b70
void Recorder::setRecoilGuard(bool enable)
{
    BYTE *player = (BYTE *)g_game.player(player_);
    player[0x14e] = enable ? 60 : 0;  // CPlayer 0x14e
}

// FUNCTION: 0x10076b90
int Recorder::randomBuffer()
{
    std::vector<int> buffers;
    for (unsigned int i = 0; i < buffers_.size(); i++) {
        if (buffers_[i].size() != 0)
            buffers.push_back(i);
    }
    unsigned int buffer = buffers.size();
    if (buffer != 0)
        buffer = buffers[rand() % buffer];
    return buffer;
}

// FUNCTION: 0x10076c40
void Recorder::stopReplay()
{
    if (state_ == RECORDER_REPLAYING) {
        StartCondition start = start_;
        state_ = RECORDER_IDLE;
        if (start == START_WAKE_UP || start == START_TECH || start == START_GUARD
            || start == START_RECOIL_GUARD || start == START_RANDOM_RG)
            state_ = RECORDER_REPLAY_WAIT;
    } else if (state_ == RECORDER_REPLAY_WAIT) {
        state_ = RECORDER_IDLE;
    }
}

// FUNCTION: 0x10076c70
void Recorder::stopRecord()
{
    if (state_ == RECORDER_RECORDING) {
        g_game.swapBindings();
        StartCondition start = start_;
        state_ = RECORDER_IDLE;
        if (start == START_WAKE_UP || start == START_TECH || start == START_GUARD
            || start == START_RECOIL_GUARD || start == START_RANDOM_RG)
            state_ = RECORDER_RECORD_WAIT;
    } else if (state_ == RECORDER_RECORD_WAIT) {
        state_ = RECORDER_IDLE;
    }
}

// FUNCTION: 0x10076cb0
void Recorder::startReplay()
{
    stopRecord();
    stopReplay();
    state_ = RECORDER_REPLAYING;
    if (random_ == REPLAY_RANDOM)
        replayBuffer_ = randomBuffer();
    replayPos_ = buffers_[replayBuffer_].begin();
}

// Recording plays the dummy: the human's keys drive the other player.
// FUNCTION: 0x10076d00
void Recorder::startRecord()
{
    g_game.swapBindings();
    stopReplay();
    stopRecord();
    buffers_[recordBuffer_].clear();
    state_ = RECORDER_RECORDING;
}

// Back towards the opponent, and down unless the opponent is in the air.
// FUNCTION: 0x10076d40
BYTE Recorder::guardInput(int player)
{
    BYTE input = 2;
    if (g_game.player(player)->facing != 1)
        input = 1;
    // TODO: differs: the original copies y to the stack through eax/edx first.
    if (g_game.player((player + 1) % 2)->y >= -5.0)
        input |= 4;
    return input;
}

// FUNCTION: 0x10076e20
void Recorder::reset()
{
    buffers_.resize(10);
    setBuffer(1);
    replayPos_ = buffers_.begin()->begin();
    state_ = RECORDER_IDLE;
    random_ = REPLAY_FIXED;
    start_ = START_NOW;
    delay_ = 0;
    history_.clear();
    setDelay(delay_);
}

// A state was saved: what was being recorded or replayed starts again from here.
// FUNCTION: 0x10076e90
void Recorder::onSaveState()
{
    RecorderState state = state_;
    stopReplay();
    stopRecord();
    if (state == RECORDER_RECORD_WAIT)
        state_ = state;
    else if (state == RECORDER_REPLAY_WAIT)
        state_ = state;
    else if (state == RECORDER_RECORDING) {
        if (start_ == START_NOW)
            startRecord();
    } else if (state == RECORDER_REPLAYING) {
        if (start_ == START_NOW)
            startReplay();
    }
}

// FUNCTION: 0x10076ee0
void Recorder::onLoadState()
{
    history_.clear();
    RecorderState state = state_;
    stopReplay();
    stopRecord();
    if (state == RECORDER_RECORD_WAIT)
        state_ = state;
    else if (state == RECORDER_REPLAY_WAIT)
        state_ = state;
    else if (state == RECORDER_RECORDING) {
        if (start_ == START_NOW)
            startRecord();
    } else if (state == RECORDER_REPLAYING) {
        if (start_ == START_NOW)
            startReplay();
    }
    setDelay(delay_);
}

// FUNCTION: 0x10076f60
void Recorder::toggleReplay()
{
    stopRecord();
    RecorderState state = state_;
    if (state == RECORDER_REPLAY_WAIT) {
        if (start_ == START_NOW)
            startReplay();
        else
            state_ = RECORDER_IDLE;
        return;
    }
    switch (start_) {
    case START_NOW:
        if (state == RECORDER_REPLAYING)
            stopReplay();
        else
            startReplay();
        break;
    case START_WAKE_UP:
    case START_TECH:
    case START_GUARD:
    case START_RECOIL_GUARD:
    case START_RANDOM_RG:
        if (state == RECORDER_REPLAYING)
            stopReplay();
        else
            state_ = RECORDER_REPLAY_WAIT;
        break;
    }
}

// FUNCTION: 0x10076fc0
void Recorder::toggleRecord()
{
    stopReplay();
    RecorderState state = state_;
    if (state == RECORDER_RECORD_WAIT) {
        if (start_ == START_NOW)
            startRecord();
        else
            state_ = RECORDER_IDLE;
        return;
    }
    switch (start_) {
    case START_NOW:
        if (state == RECORDER_RECORDING)
            stopRecord();
        else
            startRecord();
        break;
    case START_WAKE_UP:
    case START_TECH:
    case START_GUARD:
    case START_RECOIL_GUARD:
    case START_RANDOM_RG:
        if (state == RECORDER_RECORDING)
            stopRecord();
        else
            state_ = RECORDER_RECORD_WAIT;
        break;
    }
}

// A player's input byte for this frame (CInput::GetInput, three calls a frame).
// FUNCTION: 0x10077010
void Recorder::input(BYTE *input)
{
    if (g_game.sceneId() != 3)
        return;
    if (state_ == RECORDER_RECORDING) {
        delayed_.push(*input);
        *input = delayed_.front();
        delayed_.pop();
        history_.push_back(*input);
        buffers_[recordBuffer_].push_back(*input);
        return;
    }
    if (state_ == RECORDER_REPLAYING) {
        if (replayPos_ == buffers_[replayBuffer_].end()) {
            stopReplay();
            if (start_ != START_NOW)
                return;
            startReplay();
            if (replayPos_ != buffers_[replayBuffer_].end()) {
                *input = *replayPos_;
                history_.push_back(*input);
                ++replayPos_;
                return;
            }
            stopReplay();
            return;
        }
        *input = *replayPos_;
        history_.push_back(*input);
        ++replayPos_;
        return;
    }
    if (start_ == START_GUARD || start_ == START_RECOIL_GUARD || start_ == START_RANDOM_RG) {
        *input = guardInput(player_);
        history_.push_back(*input);
    }
    delayed_.push(*input);
    *input = delayed_.front();
    history_.push_back(*input);
    delayed_.pop();
}

// FUNCTION: 0x10077190
void Recorder::toggleRandom()
{
    stopReplay();
    stopRecord();
    random_ = random_ != REPLAY_RANDOM ? REPLAY_RANDOM : REPLAY_FIXED;
}

// FUNCTION: 0x100771b0
void Recorder::setBuffer(unsigned int buffer)
{
    stopRecord();
    stopReplay();
    if (buffer <= buffers_.size()) {
        recordBuffer_ = buffer;
        replayBuffer_ = buffer;
    }
}

// FUNCTION: 0x100771e0
void Recorder::nextStartCondition()
{
    stopRecord();
    stopReplay();
    state_ = RECORDER_IDLE;
    ++start_;
}

// FUNCTION: 0x10077200
std::wstring Recorder::stateName()
{
    switch (state_) {
    case RECORDER_IDLE:
        return L"Nothing";
    case RECORDER_RECORDING:
        return L"Record";
    case RECORDER_RECORD_WAIT:
        return L"Record Wait";
    case RECORDER_REPLAYING:
        return L"Replay";
    case RECORDER_REPLAY_WAIT:
        return L"Replay Wait";
    default:
        return L"Error";
    }
}

// FUNCTION: 0x100772c0
std::wstring Recorder::startConditionName()
{
    switch (start_) {
    case START_NOW:
        return L"Now";
    case START_WAKE_UP:
        return L"Wake-Up";
    case START_TECH:
        return L"Tech";
    case START_GUARD:
        return L"Guard";
    case START_RECOIL_GUARD:
        return L"Recoil Guard";
    case START_RANDOM_RG:
        return L"Random RG";
    default:
        return L"Error";
    }
}

// FUNCTION: 0x100773a0
std::wstring Recorder::recordBufferName()
{
    std::wstringstream name;
    name << recordBuffer_;
    return name.str();
}

// FUNCTION: 0x10077420
std::wstring Recorder::replayBufferName()
{
    std::wstringstream name;
    name << replayBuffer_;
    switch (random_) {
    case REPLAY_FIXED:
        return name.str();
    case REPLAY_RANDOM:
        return L"Rand";
    default:
        return L"Error";
    }
}

// FUNCTION: 0x100774e0
unsigned int Recorder::delay()
{
    return delayed_.size() / 3;
}

// FUNCTION: 0x10077500
void Recorder::stop()
{
    stopReplay();
    stopRecord();
}

// Every frame: a waiting recording or replay starts once its condition holds.
// TODO: differs: the original keeps start_ in bl and tests every case in turn after a
// failed check; this compiles to a chain that returns as soon as its case fails.
// FUNCTION: 0x10077510
void Recorder::checkStart()
{
    if (start_ == START_RECOIL_GUARD)
        setRecoilGuard(true);
    if (start_ == START_RANDOM_RG)
        setRecoilGuard(rand() % 2 != 0);
    StartCondition start = start_;
    if ((start == START_WAKE_UP && g_game.isWakingUp(player_))
        || (start == START_TECH && g_game.isTeching(player_))
        || (start == START_GUARD && g_game.isGuarding(player_))
        || start == START_RECOIL_GUARD
        || (start == START_RANDOM_RG && g_game.isRecoilGuarding(player_))) {
        if (state_ == RECORDER_RECORD_WAIT) {
            startRecord();
            return;
        }
        if (state_ == RECORDER_REPLAY_WAIT)
            startReplay();
    }
}

// FUNCTION: 0x100775c0
void Recorder::setDelay(int frames)
{
    if (frames < 0)
        frames = 0;
    while (delay_ < frames) {
        delayed_.push(0);
        delayed_.push(0);
        delayed_.push(0);
        delay_++;
    }
    while (delay_ > frames) {
        for (int i = 0; i < 3; i++) {
            if (!delayed_.empty())
                delayed_.pop();
        }
        delay_--;
    }
}

// FUNCTION: 0x100769e0
PracticeSession::PracticeSession()
    : config_(L"./EfzRevival.ini")
{
    recorders_.push_back(Recorder(0));
    recorders_.push_back(Recorder(1));
    dummy_ = 1;
    paused_ = false;
    display_ = true;
    hitBoxes_ = false;
    hurtBoxes_ = false;
    lastScene_ = 0;
    stepCount_ = 0;
    step_ = false;
    collisionBoxes_ = false;
    fps_ = 64.0;
    inputDelay_ = 0;
    music_ = NULL;
    unknown2c_ = 0;
    unknown30_ = 0;
}

// FUNCTION: 0x10076930
PracticeSession::~PracticeSession()
{
    delete music_;
}

// FUNCTION: 0x100767d0
void PracticeSession::start()
{
    dummy_ = 1;
    paused_ = false;
    display_ = true;
    hitBoxes_ = false;
    hurtBoxes_ = false;
    lastScene_ = 0;
    stepCount_ = 0;
    step_ = false;
    collisionBoxes_ = false;
    fps_ = g_game.timer->defaultFps;
    inputDelay_ = 0;
    saveBindings();
    music_ = new MusicPlayer();
    music_->muted = config_.muteBGM != 0;
    playlist_.load(config_.bgmFolder);
    playlist_.shuffle();
    unknown2c_ = 0;
    unknown30_ = 0;
    for (Recorder &recorder : recorders_)
        recorder.reset();
    setInputDelay(inputDelay_);
}

// FUNCTION: 0x100761c0
void PracticeSession::update()
{
    if (lastScene_ != g_game.sceneId()) {
        if (g_game.sceneId() == 2)
            playlist_.next();
        lastScene_ = g_game.sceneId();
        if (!isPracticeFight())
            reset();
    }
    if (g_game.sceneId() == 1 || g_game.sceneId() == 0)
        checkDevices();
    if (music_->isFinished() && g_game.sceneId() == 3)
        music_->play(playlist_.current());
    if (isPracticeFight()) {
        frame();
        return;
    }
    g_game.runFrame();
}

// FUNCTION: 0x10076490
void PracticeSession::keyPressed(int key)
{
    if (isPracticeFight() && g_game.currentScene()->unk2d != 2) {
        if (key == config_.saveState)
            saveState();
        if (key == config_.loadState)
            loadState();
        if (isVsPlayer()) {
            if (key == config_.toggleRecord)
                toggleRecord();
            if (key == config_.toggleReplay)
                toggleReplay();
            if (key == config_.switchStartCondition)
                nextStartCondition();
            if (key == config_.toggleReplayRandom)
                toggleRandom();
            if (key == config_.switchPlayers) {
                dummy_ = dummy_ == 0;
                g_game.swapBindings();
            }
            if (key == config_.setBuffer[0])
                setBuffer(1);
            if (key == config_.setBuffer[1])
                setBuffer(2);
            if (key == config_.setBuffer[2])
                setBuffer(3);
            if (key == config_.setBuffer[3])
                setBuffer(4);
            if (key == config_.setBuffer[4])
                setBuffer(5);
            // TODO: differs: the original multiplies by -1.0 (0x10090620, kept in a
            // register for both players); this compiles to middle - (x - middle).
            if (key == config_.mirrorPlayers) {
                CPlayer *p1 = g_game.player(0);
                CPlayer *p2 = g_game.player(1);
                double middle = (619.0 - 20.0) / 2.0 + 20.0;
                p1->x = (p1->x - middle) * -1.0 + middle;
                p2->x = (p2->x - middle) * -1.0 + middle;
            }
        }
        if (key == config_.pause) {
            togglePause();
            step_ = false;
        }
        if (key == config_.stepFrame) {
            paused_ = true;
            step_ = true;
        }
        if (key == config_.toggleDisplay)
            toggleDisplay();
        if (key == config_.toggleHitBoxes)
            toggleHitBoxes();
        if (key == config_.toggleHurtBoxes)
            toggleHurtBoxes();
        if (key == config_.toggleCollisionBoxes)
            toggleCollisionBoxes();
        if (key == config_.increaseFPS) {
            fps_ += 16.0;
            g_game.timer->setFps(fps_);
        }
        if (key == config_.decreaseFPS) {
            fps_ -= 16.0;
            if (fps_ < 1.0)
                fps_ = 1.0;
            g_game.timer->setFps(fps_);
        }
        if (key == config_.increaseInputDelay)
            setInputDelay(inputDelay_ + 1);
        if (key == config_.decreaseInputDelay)
            setInputDelay(inputDelay_ - 1);
        if (key == config_.resetFPS) {
            fps_ = g_game.timer->defaultFps;
            g_game.timer->setFps(fps_);
        }
    }
    if (key == config_.toggleBGM) {
        music_->muted = !music_->muted;
        if (music_->muted)
            stopSound(g_game.musicId());
        else
            playSound(g_game.musicId(), 1);
    }
}

// FUNCTION: 0x100762d0
void PracticeSession::input(BYTE *input, int player)
{
    recorders_[player].input(input);
}

// FUNCTION: 0x10075880
void PracticeSession::playSound(WORD id, int arg)
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

// FUNCTION: 0x10075830
void PracticeSession::setVolume(WORD id, int volume)
{
    if (playlist_.size() != 0 && g_game.isMusic(id) && music_->isPlaying()) {
        music_->setVolume(volume);
        return;
    }
    g_game.setSoundVolume(id, volume);
}

// FUNCTION: 0x100757e0
void PracticeSession::stopSound(WORD id)
{
    if (playlist_.size() != 0 && g_game.isMusic(id) && music_->isPlaying()) {
        music_->stop();
        return;
    }
    g_game.stopSound(id);
}

// FUNCTION: 0x10075c30
bool PracticeSession::isVsPlayer()
{
    if (g_game.sceneId() == 3 && g_game.menuChoice() == 2)
        return true;
    return false;
}

// FUNCTION: 0x10075c50
bool PracticeSession::isPracticeFight()
{
    char choice = g_game.menuChoice();
    if (g_game.sceneId() == 3 && (choice == 3 || choice == 2))
        return true;
    return false;
}

// FUNCTION: 0x10075900
int PracticeSession::otherPlayer()
{
    return (dummy_ + 1) % 2;
}

// The delay applies to the human player's inputs.
// FUNCTION: 0x10075920
void PracticeSession::setInputDelay(int frames)
{
    if (frames < 0)
        frames = 0;
    inputDelay_ = frames;
    recorders_[otherPlayer()].setDelay(frames);
}

// Every 32 frames on the title and character select: reload key.ini if it changed,
// and pick up new joysticks.
// FUNCTION: 0x10075950
void PracticeSession::checkDevices()
{
    static int frames;
    if (frames % 32 == 0) {
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
}

// A frame of the fight.
// FUNCTION: 0x100759c0
void PracticeSession::frame()
{
    drawHud();
    showBoxes();
    g_game.setTextRender(display_);
    recorders_[0].checkStart();
    recorders_[1].checkStart();
    if (paused_) {
        if (step_) {
            g_game.clearRects();
            stepCount_++;
            g_game.setGameSpeed(3);
            g_game.runFrame();
            g_game.setGameSpeed(0);
            step_ = false;
            return;
        }
    } else {
        g_game.clearRects();
    }
    g_game.runFrame();
}

// Out of the fight: everything back to normal.
// FUNCTION: 0x10075a60
void PracticeSession::reset()
{
    paused_ = false;
    step_ = false;
    stepCount_ = 0;
    g_game.setGameSpeed(3);
    g_game.setTextRender(false);
    g_game.clearBoxes();
    g_game.timer->reset();
    dummy_ = g_game.humanPlayer() == 0;
    saveState_.clear();
    for (Recorder &recorder : recorders_)
        recorder.stop();
    restoreBindings();
}

// FUNCTION: 0x10075b30
void PracticeSession::restoreBindings()
{
    memcpy(g_game.bindings(), bindings_, sizeof(bindings_));
}

// FUNCTION: 0x10075b50
void PracticeSession::saveBindings()
{
    memcpy(bindings_, g_game.bindings(), sizeof(bindings_));
}

// FUNCTION: 0x10075b70
void PracticeSession::toggleCollisionBoxes()
{
    collisionBoxes_ = !collisionBoxes_;
}

// FUNCTION: 0x10075b90
void PracticeSession::toggleHurtBoxes()
{
    hurtBoxes_ = !hurtBoxes_;
}

// FUNCTION: 0x10075bb0
void PracticeSession::toggleHitBoxes()
{
    hitBoxes_ = !hitBoxes_;
}

// FUNCTION: 0x10075bd0
void PracticeSession::showBoxes()
{
    g_game.clearBoxes();
    if (hitBoxes_) {
        g_game.showBoxes(0, 0);
        g_game.showBoxes(1, 0);
    }
    if (hurtBoxes_) {
        g_game.showBoxes(0, 1);
        g_game.showBoxes(1, 1);
    }
    if (collisionBoxes_) {
        g_game.showBoxes(0, 2);
        g_game.showBoxes(1, 2);
    }
}

// FUNCTION: 0x10075c70
void PracticeSession::drawHud()
{
    g_game.clearText();
    std::wstringstream text;
    int x = 0;
    switch (dummy_) {
    case 0:
        x = 10;
        break;
    case 1:
        x = 450;
        break;
    }
    text << "Player:        ";
    if (isVsPlayer()) {
        switch (dummy_) {
        case 0:
            text << "P2";
            break;
        case 1:
            text << "P1";
            break;
        }
    } else {
        text << "Fixed";
    }
    int line = 0;
    g_game.addText(text.str(), x, 96 + 14 * line++, 0);
    text.str(L"");
    if (isVsPlayer()) {
        text << "What:          " << recorders_[dummy_].stateName();
        g_game.addText(text.str(), x, 96 + 14 * line++, 0);
        text.str(L"");
        text << "When:          " << recorders_[dummy_].startConditionName();
        g_game.addText(text.str(), x, 96 + 14 * line++, 0);
        text.str(L"");
        text << "Record Buffer: " << recorders_[dummy_].recordBufferName();
        g_game.addText(text.str(), x, 96 + 14 * line++, 0);
        text.str(L"");
        text << "Replay Buffer: " << recorders_[dummy_].replayBufferName();
        g_game.addText(text.str(), x, 96 + 14 * line++, 0);
        text.str(L"");
    }
    text.str(L"Input Delay:   " + toWString(recorders_[otherPlayer()].delay()));
    g_game.addText(text.str(), x, 96 + 14 * line++, 0);
    text.str(L"");
    text.str(L"Frame Step:    " + toWString(stepCount_));
    g_game.addText(text.str(), x, 96 + 14 * line++, 0);
    text.str(L"");
    drawInputs(recorders_[otherPlayer()].history_, 200, 10, 0, 3);
}

// FUNCTION: 0x10076130
void PracticeSession::toggleDisplay()
{
    display_ = !display_;
}

// FUNCTION: 0x10076150
void PracticeSession::nextStartCondition()
{
    recorders_[dummy_].nextStartCondition();
}

// FUNCTION: 0x10076170
void PracticeSession::togglePause()
{
    paused_ = !paused_;
    if (paused_) {
        g_game.setGameSpeed(0);
        stepCount_ = 0;
        return;
    }
    g_game.setGameSpeed(3);
    stepCount_ = 0;
}

// FUNCTION: 0x10076290
void PracticeSession::setBuffer(unsigned int buffer)
{
    recorders_[dummy_].setBuffer(buffer);
}

// FUNCTION: 0x100762b0
void PracticeSession::toggleRandom()
{
    recorders_[dummy_].toggleRandom();
}

// FUNCTION: 0x100762f0
void PracticeSession::restoreState()
{
    saveState_.load();
    char speed = ((CScene3 *)g_game.scene(3))->speed;
    if (paused_) {
        step_ = false;
        stepCount_ = 0;
        g_game.setGameSpeed(0);
        return;
    }
    if (speed == 0)
        g_game.setGameSpeed(3);
}

// FUNCTION: 0x10076350
void PracticeSession::storeState()
{
    saveState_.clear();
    saveState_.save(false);
}

// FUNCTION: 0x10076370
void PracticeSession::toggleRecord()
{
    recorders_[dummy_].toggleRecord();
}

// FUNCTION: 0x10076390
void PracticeSession::toggleReplay()
{
    recorders_[dummy_].toggleReplay();
}

// FUNCTION: 0x100763b0
void PracticeSession::loadState()
{
    restoreState();
    for (Recorder &recorder : recorders_)
        recorder.onLoadState();
}

// FUNCTION: 0x10076420
void PracticeSession::saveState()
{
    for (Recorder &recorder : recorders_)
        recorder.onSaveState();
    storeState();
}
