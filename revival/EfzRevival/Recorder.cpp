// Recording and replaying a player's inputs in the practice session (Recorder.h).
#include "stdafx.h"
#include "EfzGame.h"
#include "Recorder.h"
#include <stdlib.h>

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

// Every frame: a waiting recording or replay starts once its condition holds.
// (start_ is read in each test, not copied to a local first: with a local the compiler
// sees that the cases exclude each other and returns as soon as one fails.)
// FUNCTION: 0x10077510
void Recorder::checkStart()
{
    if (start_ == START_RECOIL_GUARD)
        setRecoilGuard(true);
    if (start_ == START_RANDOM_RG)
        setRecoilGuard(rand() % 2 != 0);
    if ((start_ == START_WAKE_UP && g_game.isWakingUp(player_))
        || (start_ == START_TECH && g_game.isTeching(player_))
        || (start_ == START_GUARD && g_game.isGuarding(player_))
        || start_ == START_RECOIL_GUARD
        || (start_ == START_RANDOM_RG && g_game.isRecoilGuarding(player_))) {
        if (state_ == RECORDER_RECORD_WAIT) {
            startRecord();
            return;
        }
        if (state_ == RECORDER_REPLAY_WAIT)
            startReplay();
    }
}

// FUNCTION: 0x10077500
void Recorder::stop()
{
    stopReplay();
    stopRecord();
}

// FUNCTION: 0x100774e0
unsigned int Recorder::delay()
{
    return delayed_.size() / 3;
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

// FUNCTION: 0x100773a0
std::wstring Recorder::recordBufferName()
{
    std::wstringstream name;
    name << recordBuffer_;
    return name.str();
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

// FUNCTION: 0x100771e0
void Recorder::nextStartCondition()
{
    stopRecord();
    stopReplay();
    state_ = RECORDER_IDLE;
    ++start_;
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

// FUNCTION: 0x10077190
void Recorder::toggleRandom()
{
    stopReplay();
    stopRecord();
    random_ = random_ != REPLAY_RANDOM ? REPLAY_RANDOM : REPLAY_FIXED;
}

// A player's input byte for this frame (CInput::GetInput, three calls a frame).
// FUNCTION: 0x10077010
void Recorder::input(char *input)
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

// FUNCTION: 0x10076e00
Recorder::~Recorder()
{
}

// FUNCTION: 0x10076da0 ??0Recorder@@QAE@H@Z
Recorder::Recorder(int player)
{
    player_ = player;
}

// Back towards the opponent, and down unless the opponent is in the air.
// FUNCTION: 0x10076d40
BYTE Recorder::guardInput(int player)
{
    BYTE input = 2;
    if (g_game.player(player)->facing != 1)
        input = 1;
    double y = g_game.player((player + 1) % 2)->y;
    if (y >= -5.0)
        input |= 4;
    return input;
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

// FUNCTION: 0x10076b70
void Recorder::setRecoilGuard(bool enable)
{
    BYTE *player = (BYTE *)g_game.player(player_);
    if (enable)
        player[0x14e] = 60;  // CPlayer 0x14e
    else
        player[0x14e] = 0;
}
