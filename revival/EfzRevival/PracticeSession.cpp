// The practice session (VS PLAYER, mode 2).
//
// Pause holds the fight back: Game::setGameSpeed(0) patches out the scene's updates (the
// frame still runs, so the scene is drawn and the overlay updated), and a frame step
// runs one frame at speed 3 before patching them out again, counting the frames
// stepped. Each player's inputs go through a Recorder, which records them into a
// buffer, replays one (or a random non-empty one), and delays them; switching players
// swaps the two players' key bindings, and mirroring reflects both around the
// stage's middle.
#include "stdafx.h"
#include "EfzGame.h"
#include "PracticeSession.h"
#include "Music.h"
#include <stdlib.h>
#include <sstream>
#include "InputDisplay.h"
#include "Log.h"
#include "../DDRAW/EfzTimer.h"

// DDRAW.dll's frame timer (getEfzTimer): its inline functions are emitted here, the first
// object to use them.
// FUNCTION: 0x10028c80 EfzTimer::setFps
// FUNCTION: 0x10028cf0 EfzTimer::reset

// FUNCTION: 0x10029090 ??_GPracticeSession@@UAEPAXI@Z

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
            fps_ = fps_ < 1.0 ? 1.0 : fps_;
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

// FUNCTION: 0x10076420
void PracticeSession::saveState()
{
    for (Recorder &recorder : recorders_)
        recorder.onSaveState();
    storeState();
}

// FUNCTION: 0x100763b0
void PracticeSession::loadState()
{
    restoreState();
    for (Recorder &recorder : recorders_)
        recorder.onLoadState();
}

// FUNCTION: 0x10076390
void PracticeSession::toggleReplay()
{
    recorders_[dummy_].toggleReplay();
}

// FUNCTION: 0x10076370
void PracticeSession::toggleRecord()
{
    recorders_[dummy_].toggleRecord();
}

// FUNCTION: 0x10076350
void PracticeSession::storeState()
{
    saveState_.clear();
    saveState_.save(false);
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

// FUNCTION: 0x100762d0
void PracticeSession::input(BYTE *input, int player)
{
    recorders_[player].input((char *)input);
}

// FUNCTION: 0x100762b0
void PracticeSession::toggleRandom()
{
    recorders_[dummy_].toggleRandom();
}

// FUNCTION: 0x10076290
void PracticeSession::setBuffer(unsigned int buffer)
{
    recorders_[dummy_].setBuffer(buffer);
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

// FUNCTION: 0x10076150
void PracticeSession::nextStartCondition()
{
    recorders_[dummy_].nextStartCondition();
}

// FUNCTION: 0x10076130
void PracticeSession::toggleDisplay()
{
    display_ = !display_;
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

// FUNCTION: 0x10075c50
bool PracticeSession::isPracticeFight()
{
    char choice = g_game.menuChoice();
    if (g_game.sceneId() == 3 && (choice == 3 || choice == 2))
        return true;
    return false;
}

// FUNCTION: 0x10075c30
bool PracticeSession::isVsPlayer()
{
    if (g_game.sceneId() == 3 && g_game.menuChoice() == 2)
        return true;
    return false;
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

// FUNCTION: 0x10075bb0
void PracticeSession::toggleHitBoxes()
{
    hitBoxes_ = !hitBoxes_;
}

// FUNCTION: 0x10075b90
void PracticeSession::toggleHurtBoxes()
{
    hurtBoxes_ = !hurtBoxes_;
}

// FUNCTION: 0x10075b70
void PracticeSession::toggleCollisionBoxes()
{
    collisionBoxes_ = !collisionBoxes_;
}

// FUNCTION: 0x10075b50
void PracticeSession::saveBindings()
{
    memcpy(bindings_, g_game.bindings(), sizeof(bindings_));
}

// FUNCTION: 0x10075b30
void PracticeSession::restoreBindings()
{
    memcpy(g_game.bindings(), bindings_, sizeof(bindings_));
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

// Every 32 frames on the title and character select: reload key.ini if it changed,
// and pick up new joysticks.
// FUNCTION: 0x10075950
void PracticeSession::checkDevices()
{
    static int frames = 1;  // initialized data (0x1009f0f8-0x1009f104)
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

// The delay applies to the human player's inputs.
// FUNCTION: 0x10075920
void PracticeSession::setInputDelay(int frames)
{
    if (frames < 0)
        frames = 0;
    inputDelay_ = frames;
    recorders_[otherPlayer()].setDelay(frames);
}

// FUNCTION: 0x10075900
int PracticeSession::otherPlayer()
{
    return (dummy_ + 1) % 2;
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
