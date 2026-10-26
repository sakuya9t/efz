// The replay session. See ReplaySession.h.
//
// While a replay plays (Game::replayMode 0 or 1 in the REPLAY menu's fight) the game
// reads both players' inputs from the file; an extended replay's own copy of them
// (Game::readExtendedReplay) drives input() instead, frame_ counting the frames. Once a
// player takes control (control_), that player's inputs come from the pad, and the
// session tells the game to record (setEfzReplay(false): replay mode 2).
#include "ReplaySession.h"
#include <math.h>
#include <iostream>
#include <sstream>
#include "EfzGame.h"
#include "EfzReplay.h"
#include "InputDisplay.h"
#include "Log.h"
#include "../DDRAW/EfzTimer.h"

// FUNCTION: 0x1002cb30 ??_GReplaySession@@UAEPAXI@Z
// FUNCTION: 0x1002cb80 ??1ReplayState@@QAE@XZ

// FUNCTION: 0x10078820
ReplaySession::ReplaySession()
{
    paused_ = false;
    step_ = false;
    control_ = false;
    lastScene_ = 0;
    config_ = nullptr;
    hitBoxes_ = false;
    hurtBoxes_ = false;
    collisionBoxes_ = false;
    frame_ = 0;
    fps_ = 64.0;
    controlled_ = 0;
    quit_ = false;
    display_ = false;
    music_ = NULL;
}

// FUNCTION: 0x10078790
ReplaySession::~ReplaySession()
{
    delete music_;
}

// FUNCTION: 0x100785c0
void ReplaySession::start()
{
    config_ = std::unique_ptr<Config>(new Config(L"./EfzRevival.ini"));
    frame_ = 0;
    fps_ = g_game.timer->defaultFps;
    controlled_ = 0;
    quit_ = false;
    display_ = true;
    g_game.setReplayName(std::wstring());
    hitBoxes_ = false;
    hurtBoxes_ = false;
    collisionBoxes_ = false;
    g_game.setSaveReplays(true);
    music_ = new MusicPlayer();
    music_->muted = config_->muteBGM != 0;
    playlist_.load(config_->bgmFolder);
    playlist_.shuffle();
    state_.state.clear();
    states_.resize(300);
    for (int i = 0; i < states_.size(); i++)
        states_[i].state.clear();
}

// FUNCTION: 0x10078310
void ReplaySession::update()
{
    if (lastScene_ != g_game.sceneId()) {
        if (g_game.sceneId() == 2)
            playlist_.next();
        sceneChanged(lastScene_);
    }
    if (music_->isFinished() && g_game.sceneId() == 3)
        music_->play(playlist_.current());
    BYTE p1 = g_game.cleanInput(g_game.efzInput(0));
    BYTE p2 = g_game.cleanInput(g_game.efzInput(1));
    static_cast<FrameInput &>(inputs_[0]) = FrameInput(p1, g_game.functionKeys());
    static_cast<FrameInput &>(inputs_[1]) = FrameInput(p2, g_game.functionKeys());
    if (isReplaying() || isControlling()) {
        if (!isControlling()) {
            if (g_game.isRoundOver()) {
                setEfzReplay(true);
                g_game.setTextRender(false);
                if (controlled_ == 1) {
                    g_game.swapBindings();
                    controlled_ = 0;
                }
                g_game.runFrame();
                return;
            }
            if (frame_ == 1) {
                saveState(state_);
                setEfzReplay(replayInputs_.size() == 0);
            }
            if (inputs_[controlled_].first != 0 && frame_ > 1 && replayInputs_.size() != 0
                && !g_game.isMatchOver())
                control_ = true;
            if (frame_ % 64 == 0 && !control_)
                saveState(states_[frame_ / 64]);
            drawInfo();
            showBoxes();
            if (paused_) {
                if (step_) {
                    g_game.clearRects();
                    g_game.setReadReplay(true);
                    g_game.setGameSpeed(3);
                    g_game.runFrame();
                    frame_++;
                    g_game.setGameSpeed(0);
                    g_game.setReadReplay(false);
                    step_ = false;
                    return;
                }
            } else {
                g_game.clearRects();
            }
            g_game.runFrame();
            if (!paused_)
                frame_++;
            return;
        }
        showBoxes();
        if (paused_) {
            if (step_) {
                g_game.clearRects();
                g_game.recordInputs(inputs_[0], inputs_[1]);
                g_game.setWriteReplay(true);
                g_game.setGameSpeed(3);
                g_game.runFrame();
                g_game.setGameSpeed(0);
                g_game.setWriteReplay(false);
                step_ = false;
                return;
            }
        } else {
            g_game.clearRects();
            g_game.recordInputs(inputs_[0], inputs_[1]);
        }
    }
    g_game.runFrame();
}

// FUNCTION: 0x10077f70
void ReplaySession::keyPressed(int key)
{
    if (!(isReplaying() || isControlling()) || g_game.isRoundOver()) {
        if (key == config_->toggleBGM) {
            music_->muted = !music_->muted;
            if (music_->muted)
                stopSound(g_game.musicId());
            else
                playSound(g_game.musicId(), 1);
        }
        return;
    }
    if (key == config_->toggleBGM) {
        music_->muted = !music_->muted;
        if (music_->muted)
            stopSound(g_game.musicId());
        else
            playSound(g_game.musicId(), 1);
    }
    if (isReplaying()) {
        if (key == config_->saveState && !control_)
            saveState(state_);
        if (key == config_->loadState)
            loadState(state_);
        // IncreaseInputDelay and DecreaseInputDelay seek by the saved states
        if (key == config_->increaseInputDelay)
            loadState(states_[(int)ceil((frame_ + 1.0) / 64.0)]);
        if (key == config_->decreaseInputDelay && frame_ > 64)
            loadState(states_[(int)floor((frame_ - 32.0) / 64.0)]);
        if (key == config_->switchPlayers) {
            controlled_ = controlled_ == 0;
            g_game.swapBindings();
        }
    }
    if (key == config_->pause)
        setPaused(!paused_);
    if (key == config_->stepFrame) {
        paused_ = true;
        g_game.setReadReplay(false);
        step_ = true;
    }
    if (key == config_->toggleDisplay) {
        display_ = !display_;
        g_game.setTextRender(display_);
    }
    if (key == config_->toggleHitBoxes)
        hitBoxes_ = !hitBoxes_;
    if (key == config_->toggleHurtBoxes)
        hurtBoxes_ = !hurtBoxes_;
    if (key == config_->toggleCollisionBoxes)
        collisionBoxes_ = !collisionBoxes_;
    if (key == config_->increaseFPS) {
        fps_ += 16.0;
        g_game.timer->setFps(fps_);
    }
    if (key == config_->decreaseFPS) {
        fps_ -= 16.0;
        if (fps_ < 1.0)
            fps_ = 1.0;
        g_game.timer->setFps(fps_);
    }
    if (key == config_->resetFPS) {
        fps_ = g_game.timer->defaultFps;
        g_game.timer->setFps(fps_);
    }
}

// FUNCTION: 0x10077ee0
void ReplaySession::input(BYTE *input, int player)
{
    if (isReplaying() && replayInputs_.size() != 0) {
        if (control_ && player == controlled_) {
            *input = inputs_[player].first;
            return;
        }
        unsigned int index = player + frame_ * 2;
        if (index < replayInputs_.size()) {
            *input = replayInputs_[index].first;
        } else {
            g_log << "Not enough inputs\n";
            *input = 0;
            quit_ = true;
        }
    }
    if (isControlling())
        *input = inputs_[player].first;
}

// The function keys (F4-F8, Esc): the replay's, or the pads' once in control.
// FUNCTION: 0x100777b0
void ReplaySession::fightUpdate(void *frame)
{
    if (isReplaying() || isControlling()) {
        BYTE *keys = (BYTE *)frame;
        char pressed = 0;
        if (!isControlling() && replayInputs_.size() != 0 && !control_) {
            if (isReplaying() && replayInputs_.size() != 0) {
                int index = frame_ * 2;
                pressed = replayInputs_[index].second | replayInputs_[index + 1].second;
            }
        } else {
            pressed = inputs_[0].second | inputs_[1].second;
        }
        for (int i = 0; i < 5; i++)
            keys[DIK_F4 + i] = (pressed & (1 << i)) ? 0x80 : 0;
        if (pressed & 0x20)
            keys[DIK_ESCAPE] = 0x80;
        if (quit_) {
            g_log << "DoQuit\n";
            quit_ = false;
            keys[DIK_ESCAPE] = 0x80;
        }
        if (isReplaying() && keys[DIK_ESCAPE] == 0x80) {
            g_log << "Get input esc\n";
            g_log.flush();
        }
    }
}

// FUNCTION: 0x10077690
void ReplaySession::setVolume(WORD id, int volume)
{
    if (playlist_.size() != 0 && g_game.isMusic(id) && music_->isPlaying()) {
        music_->setVolume(volume);
        return;
    }
    g_game.setSoundVolume(id, volume);
}

// FUNCTION: 0x10077650
void ReplaySession::stopSound(WORD id)
{
    if (playlist_.size() != 0 && g_game.isMusic(id) && music_->isPlaying()) {
        music_->stop();
        return;
    }
    g_game.stopSound(id);
}

// FUNCTION: 0x100776e0
void ReplaySession::playSound(WORD id, int arg)
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

// FUNCTION: 0x10077750
void ReplaySession::setPaused(bool paused)
{
    paused_ = paused;
    if (paused) {
        g_game.setReadReplay(false);
        g_game.setWriteReplay(false);
        g_game.setGameSpeed(0);
        step_ = false;
        return;
    }
    g_game.setWriteReplay(true);
    g_game.setReadReplay(true);
    g_game.setGameSpeed(3);
    step_ = false;
}

// FUNCTION: 0x100778c0
void ReplaySession::drawInfo()
{
    g_game.clearText();
    std::wstringstream text;
    int x = 0;
    switch (controlled_) {
    case 0:
        x = 450;
        break;
    case 1:
        x = 10;
        break;
    }
    if (replayInputs_.size() == 0) {
        text << "Not an extended .rep";
        g_game.addText(text.str(), x, 96, 0);
        text.str(L"");
        return;
    }
    text << "Player:        ";
    switch (controlled_) {
    case 0:
        text << "P1";
        break;
    case 1:
        text << "P2";
        break;
    }
    g_game.addText(text.str(), x, 96, 0);
    text.str(L"");
    text << "State:         " << (control_ ? "Control" : "Replay");
    g_game.addText(text.str(), x, 110, 0);
    text.str(L"");
    std::vector<BYTE> p1(&p1Inputs_[0], &p1Inputs_[frame_]);
    std::vector<BYTE> p2(&p2Inputs_[0], &p2Inputs_[frame_]);
    drawInputs(p1, 200, 10, 0, 1);
    drawInputs(p2, 200, 550, 0, 1);
}

// FUNCTION: 0x10077b00
void ReplaySession::loadState(ReplayState &state)
{
    control_ = false;
    CScene3 *fight = (CScene3 *)g_game.scene(3);
    char speed = fight->speed;
    state.state.load();
    ((ReplayFile *)g_game.replayFile())->file->seekg(state.position);
    fight->speed = speed;
}

// FUNCTION: 0x10077b60
void ReplaySession::saveState(ReplayState &state)
{
    state.state.clear();
    state.state.save(false);
    state.state.addInt(&frame_);
    state.position = (int)((ReplayFile *)g_game.replayFile())->file->tellg();
}

// FUNCTION: 0x10077bc0
void ReplaySession::showBoxes()
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

// FUNCTION: 0x10077c20
void ReplaySession::sceneChanged(int &scene)
{
    scene = g_game.sceneId();
    if (isReplaying()) {
        g_game.timer->setFps(fps_);
        quit_ = false;
        frame_ = 0;
        replayInputs_.clear();
        state_.reset();
        for (int i = 0; i < states_.size(); i++)
            states_[i].reset();
        control_ = false;
        g_game.readExtendedReplay(replayInputs_);
        p1Inputs_.clear();
        p2Inputs_.clear();
        if (replayInputs_.size() != 0) {
            for (unsigned int i = 0; i < replayInputs_.size() - 1; i += 2) {
                p1Inputs_.push_back(replayInputs_[i].first);
                p2Inputs_.push_back(replayInputs_[i + 1].first);
            }
        }
        g_game.setTextRender(display_);
        setEfzReplay(true);
        return;
    }
    if (!isControlling()) {
        g_game.timer->setFps(g_game.timer->defaultFps);
        g_game.setTextRender(false);
        g_game.setGameSpeed(3);
        g_game.setReadReplay(true);
        g_game.setWriteReplay(true);
        g_game.clearBoxes();
        paused_ = false;
        step_ = false;
        quit_ = false;
        return;
    }
    g_game.timer->setFps(fps_);
    quit_ = false;
    frame_ = 0;
    replayInputs_.clear();
    state_.reset();
    for (int i = 0; i < states_.size(); i++)
        states_[i].reset();
    g_game.setRandomSeed(g_game.newRandomSeed());
}

// Whether the game reads the replay's inputs (1) or records (2, the player in control).
// FUNCTION: 0x10077e30
void ReplaySession::setEfzReplay(bool play)
{
    g_log << "Set efz Replay " << play << "\n";
    g_log.flush();
    g_game.setReplayMode(play);
    g_game.setReadReplay(play);
}

// FUNCTION: 0x10077e80
bool ReplaySession::isControlling()
{
    if (g_game.sceneId() == 3 && g_game.menuChoice() == 4 && g_game.replayMode() == 2)
        return true;
    return false;
}

// FUNCTION: 0x10077eb0
bool ReplaySession::isReplaying()
{
    if (g_game.sceneId() == 3 && g_game.menuChoice() == 4
        && (g_game.replayMode() == 0 || g_game.replayMode() == 1))
        return true;
    return false;
}
