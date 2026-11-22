// The replay session (local.h): revival/EfzRevival/ReplaySession.cpp.
//
// While a replay plays (the REPLAY menu's fight, replay mode 1) the game reads both
// players' inputs from the file. An extended replay (EfzRevival's: its inputs, a frame
// each, and its random state after the game's part) is played from that copy instead,
// with the game's replay mode 0 and the file left alone (CReplayFile::Read's hook), and
// Revival's random generator seeded from it, as Revival plays its own; then a player who
// presses a direction or a button takes that character over, the other going on with
// the replay, until Load. Either kind can be paused, stepped, sped up or slowed down,
// saved and loaded, and sought by the states kept every 64 frames (IncreaseInputDelay
// and DecreaseInputDelay, as Revival has them); the boxes show as in practice. While the
// REPLAY menu records a replay (replay mode 2), pause, step, speed and the boxes too.
//
// Otherwise than Revival: an extended replay is played to Revival's rules for netplay
// (normal effects, every frame drawn, 100% damage, 2 rounds: what it was played with),
// as tools' conversions play one (record.h); a state not saved yet isn't sought to; the
// replays this game records are the game's own, without Revival's extended part.
#include "local_internal.h"


#include "../netplay/session.h"
#include "../record.h"

namespace efz {
namespace revival {

namespace {

bool g_readReplay = true; // Game::readReplay_

struct FrameInput {
    char first, second;
};

// A save state of the replay and where its file was then.
struct ReplayState {
    netplay::SaveState state;
    DWORD position = 0;
    bool saved = false;
};

HANDLE ReplayHandle()
{
    return GameObject()->m_replay.m_handle;
}

DWORD FilePosition()
{
    HANDLE h = ReplayHandle();
    return h && h != INVALID_HANDLE_VALUE ? SetFilePointer(h, 0, nullptr, FILE_CURRENT) : 0;
}

void SeekFile(DWORD position)
{
    HANDLE h = ReplayHandle();
    if (h && h != INVALID_HANDLE_VALUE)
        SetFilePointer(h, (LONG)position, nullptr, FILE_BEGIN);
}

bool IsReplaying()
{
    int mode = ReplayMode();
    return SceneId() == 3 && MenuChoice() == 4 && (mode == 0 || mode == 1);
}

bool IsControlling()
{
    return SceneId() == 3 && MenuChoice() == 4 && ReplayMode() == 2;
}

class ReplaySession : public Session {
public:
    bool Enabled() override { return ReplayTools(); }
    void Start() override
    {
        frame_ = 0;
        fps_ = kDefaultFps;
        controlled_ = 0;
        quit_ = false;
        display_ = true;
        hitBoxes_ = hurtBoxes_ = collisionBoxes_ = false;
        state_ = ReplayState();
        states_.clear();
        states_.resize(300);
        g_revival.replayRead = [] { return g_readReplay; };
    }

    ~ReplaySession() override
    {
        Restore();
        g_readReplay = true;
        g_revival.replayRead = nullptr;
    }

    bool Holds() override
    {
        if (!(IsReplaying() || IsControlling()) || IsRoundOver() || !paused_ || step_)
            return false;
        if (IsReplaying())
            DrawInfo();
        ShowAllBoxes();
        return true;
    }

    void Update() override
    {
        if (lastScene_ != SceneId())
            SceneChanged();
        unsigned char p1 = CleanInput(ControlsOf(0));
        unsigned char p2 = CleanInput(ControlsOf(1));
        inputs_[0] = FrameInput{(char)p1, (char)FunctionKeys()};
        inputs_[1] = FrameInput{(char)p2, (char)FunctionKeys()};
        if (IsControlling()) {
            ShowAllBoxes();
            if (paused_) {
                if (step_) {
                    RunGameFrame();
                    step_ = false;
                }
                return;
            }
            RunGameFrame();
            return;
        }
        if (!IsReplaying()) {
            RunGameFrame();
            return;
        }
        if (IsRoundOver()) {
            SetEfzReplay(true);
            SetTextRender(false);
            if (controlled_ == 1) {
                SwapBindings();
                controlled_ = 0;
            }
            RunGameFrame();
            return;
        }
        if (frame_ == 1) {
            SaveTo(state_);
            SetEfzReplay(replayInputs_.empty());
            // (Revival's random generator and its copy of the inputs: a record of the
            // fight couldn't be played back as the game's own)
            if (!replayInputs_.empty())
                InterruptRecord("replay: played from EfzRevival's inputs");
        }
        if (inputs_[controlled_].first != 0 && frame_ > 1 && !replayInputs_.empty() &&
            !IsMatchOver() && !control_) {
            control_ = true;
            LogInfo("revival", "replay: P%d taken over at frame %d", controlled_ + 1, frame_);
        }
        if (frame_ % 64 == 0 && !control_ && frame_ / 64 < (int)states_.size())
            SaveTo(states_[frame_ / 64]);
        DrawInfo();
        ShowAllBoxes();
        if (paused_) {
            if (step_) {
                bool read = g_readReplay;
                g_readReplay = replayInputs_.empty();
                RunGameFrame();
                g_readReplay = read;
                frame_++;
                step_ = false;
            }
            return;
        }
        RunGameFrame();
        frame_++;
    }

    void KeyPressed(int key) override
    {
        if (!(IsReplaying() || IsControlling()) || IsRoundOver())
            return;
        const Config& ini = GetConfig();
        if (IsReplaying()) {
            if (key == ini.saveState && !control_)
                SaveTo(state_);
            if (key == ini.loadState)
                LoadFrom(state_);
            // IncreaseInputDelay and DecreaseInputDelay seek by the states kept
            if (key == ini.increaseInputDelay) {
                size_t i = (size_t)ceil((frame_ + 1.0) / 64.0);
                if (i < states_.size() && states_[i].saved)
                    LoadFrom(states_[i]);
            }
            if (key == ini.decreaseInputDelay && frame_ > 64) {
                size_t i = (size_t)floor((frame_ - 64.0 / 2) / 64.0);
                if (i < states_.size() && states_[i].saved)
                    LoadFrom(states_[i]);
            }
            if (key == ini.switchPlayers) {
                controlled_ = controlled_ == 0;
                SwapBindings();
            }
        }
        if (key == ini.pause) {
            paused_ = !paused_;
            step_ = false;
        }
        if (key == ini.stepFrame) {
            paused_ = true;
            step_ = true;
        }
        if (key == 0x01 && paused_) { // Esc: go on, and leave the fight
            paused_ = false;
            step_ = false;
        }
        if (key == ini.toggleDisplay) {
            display_ = !display_;
            SetTextRender(display_);
        }
        if (key == ini.toggleHitBoxes)
            hitBoxes_ = !hitBoxes_;
        if (key == ini.toggleHurtBoxes)
            hurtBoxes_ = !hurtBoxes_;
        if (key == ini.toggleCollisionBoxes)
            collisionBoxes_ = !collisionBoxes_;
        if (key == ini.increaseFPS) {
            fps_ += 16.0;
            SetFps(fps_);
        }
        if (key == ini.decreaseFPS) {
            fps_ -= 16.0;
            fps_ = fps_ < 1.0 ? 1.0 : fps_;
            SetFps(fps_);
        }
        if (key == ini.resetFPS) {
            fps_ = kDefaultFps;
            SetFps(fps_);
        }
    }

    void Input(unsigned char* input, int player) override
    {
        if (IsReplaying() && !replayInputs_.empty()) {
            if (control_ && player == controlled_) {
                *input = (unsigned char)inputs_[player].first;
                return;
            }
            size_t index = (size_t)player + (size_t)frame_ * 2;
            if (index < replayInputs_.size()) {
                *input = (unsigned char)replayInputs_[index].first;
            } else {
                *input = 0;
                quit_ = true;
            }
        }
        if (IsControlling())
            *input = (unsigned char)inputs_[player].first;
    }

    // The function keys (F4-F8, Esc): the replay's, or the pads' once in control.
    void FightKeys(unsigned char* keys) override
    {
        if (!(IsReplaying() || IsControlling()))
            return;
        char pressed = 0;
        if (!IsControlling() && !replayInputs_.empty() && !control_) {
            size_t index = (size_t)frame_ * 2;
            if (index + 1 < replayInputs_.size())
                pressed = replayInputs_[index].second | replayInputs_[index + 1].second;
        } else {
            pressed = inputs_[0].second | inputs_[1].second;
        }
        if (!replayInputs_.empty() || IsControlling() || control_) {
            for (int i = 0; i < 5; i++)
                keys[0x3e + i] = (pressed & (1 << i)) ? 0x80 : 0;
            if (pressed & 0x20)
                keys[0x01] = 0x80;
        }
        if (quit_) {
            quit_ = false;
            keys[0x01] = 0x80;
        }
    }

private:
    // Whether the game reads the replay's inputs (1) or not (0: an extended replay's own).
    void SetEfzReplay(bool play)
    {
        GameObject()->m_replayMode = play ? 1 : 0;
        g_readReplay = play;
    }

    void SceneChanged()
    {
        lastScene_ = SceneId();
        if (IsReplaying()) {
            SetFps(fps_);
            quit_ = false;
            frame_ = 0;
            replayInputs_.clear();
            state_ = ReplayState();
            for (ReplayState& s : states_)
                s = ReplayState();
            control_ = false;
            ReadExtendedReplay();
            p1Inputs_.clear();
            p2Inputs_.clear();
            for (size_t i = 0; i + 1 < replayInputs_.size(); i += 2) {
                p1Inputs_.push_back(replayInputs_[i].first);
                p2Inputs_.push_back(replayInputs_[i + 1].first);
            }
            SetTextRender(display_);
            SetEfzReplay(true);
            return;
        }
        if (IsControlling()) {
            SetFps(fps_);
            quit_ = false;
            frame_ = 0;
            replayInputs_.clear();
            return;
        }
        SetFps(kDefaultFps);
        SetTextRender(false);
        g_readReplay = true;
        ClearBoxes();
        paused_ = false;
        step_ = false;
        quit_ = false;
        Restore();
    }

    // The random state and both players' inputs an extended replay keeps after the game's
    // own part (Game::readExtendedReplay): its trailer is the offset of that part, then -1.
    void ReadExtendedReplay()
    {
        HANDLE h = ReplayHandle();
        if (!h || h == INVALID_HANDLE_VALUE)
            return;
        DWORD start = FilePosition();
        DWORD size = GetFileSize(h, nullptr);
        DWORD got = 0;
        int32_t tail[2] = {0, 0};
        if (size >= 16 && SetFilePointer(h, (LONG)(size - 8), nullptr, FILE_BEGIN) != INVALID_FILE_SIZE &&
            ReadFile(h, tail, 8, &got, nullptr) && got == 8 && tail[1] == -1 && tail[0] > 0 &&
            (DWORD)tail[0] + 8 <= size) {
            SetFilePointer(h, tail[0], nullptr, FILE_BEGIN);
            uint32_t seed = 0;
            int32_t count = 0;
            ReadFile(h, &seed, 4, &got, nullptr);
            if (seed == 0) {
                LogInfo("revival", "replay: extended, but without its random state (an old "
                                   "Revival's): played as the game's own");
            } else if (ReadFile(h, &count, 4, &got, nullptr) && count > 0 &&
                       (DWORD)tail[0] + 8 + (DWORD)count * 2 <= size) {
                replayInputs_.resize((size_t)count);
                ReadFile(h, replayInputs_.data(), (DWORD)count * 2, &got, nullptr);
                if (got != (DWORD)count * 2)
                    replayInputs_.clear();
            }
            if (!replayInputs_.empty()) {
                // As Revival plays its own: its random generator, from the replay's state,
                // and netplay's settings.
                CGame* game = GameObject();
                saved_[0] = game->m_fullEffects;
                saved_[1] = (char)game->m_drawEveryFrame;
                saved_[2] = game->m_damageLevel;
                saved_[3] = game->m_roundsSetting;
                changed_ = true;
                game->m_fullEffects = 1;
                game->m_drawEveryFrame = 1;
                game->m_damageLevel = 2;
                game->m_roundsSetting = 2;
                SetRevivalRand(true);
                SetRevivalRandState(seed);
                LogInfo("revival", "replay: EfzRevival's, %zu frames of inputs, random state %u",
                        replayInputs_.size() / 2, seed);
            }
        } else {
            LogInfo("revival", "replay: not an extended .rep");
        }
        SeekFile(start);
    }

    // Out of the replay: the game's rules again.
    void Restore()
    {
        if (!changed_)
            return;
        changed_ = false;
        SetRevivalRand(false);
        CGame* game = GameObject();
        if (!game)
            return;
        game->m_fullEffects = saved_[0];
        game->m_drawEveryFrame = saved_[1];
        game->m_damageLevel = saved_[2];
        game->m_roundsSetting = saved_[3];
        UnswapBindings();
        controlled_ = 0;
    }

    void SaveTo(ReplayState& state)
    {
        state.state.Save();
        state.state.AddInt(&frame_);
        state.position = FilePosition();
        state.saved = true;
    }

    void LoadFrom(ReplayState& state)
    {
        if (!state.saved)
            return;
        InterruptRecord("replay: a state loaded");
        control_ = false;
        LoadKeepingFps(state.state);
        SeekFile(state.position);
        if (paused_) {
            GameObjects o = Objects();
            if (o.graphics && o.graphics->m_back)
                Present(o.graphics->m_back, ScreenPalette(o.graphics));
        }
    }

    void ShowAllBoxes()
    {
        ClearBoxes();
        for (int i = 0; i < 2; i++) {
            if (hitBoxes_)
                ShowBoxes(i, kBoxHit);
            if (hurtBoxes_)
                ShowBoxes(i, kBoxHurt);
            if (collisionBoxes_)
                ShowBoxes(i, kBoxCollision);
        }
    }

    void DrawInfo()
    {
        ClearText();
        int x = controlled_ == 0 ? 450 : 10;
        if (replayInputs_.empty()) {
            AddText("Not an extended .rep", x, 96);
            return;
        }
        AddText(std::string("Player:        ") + (controlled_ == 0 ? "P1" : "P2"), x, 96);
        AddText(std::string("State:         ") + (control_ ? "Control" : "Replay"), x, 110);
        size_t n = std::min((size_t)std::max(frame_, 0), p1Inputs_.size());
        if (InputDisplay()) {
            DrawInputs(std::vector<char>(p1Inputs_.begin(), p1Inputs_.begin() + n), 200, 10, 1);
            DrawInputs(std::vector<char>(p2Inputs_.begin(), p2Inputs_.begin() + n), 200, 550, 1);
        }
    }

    int frame_ = 0;
    double fps_ = kDefaultFps;
    bool paused_ = false;
    bool step_ = false;
    bool control_ = false; // a player has taken control
    bool quit_ = false;    // the replay ran out of inputs
    bool display_ = true;
    bool hitBoxes_ = false, hurtBoxes_ = false, collisionBoxes_ = false;
    FrameInput inputs_[2] = {{0, 0}, {0, 0}};
    int controlled_ = 0; // the player who may take control
    ReplayState state_;
    std::vector<FrameInput> replayInputs_; // the extended replay's, P1's then P2's
    int lastScene_ = 0;
    std::vector<char> p1Inputs_, p2Inputs_;
    std::vector<ReplayState> states_; // every 64 frames
    bool changed_ = false; // Revival's rules on for an extended replay
    char saved_[4] = {0, 0, 0, 0};
};

} // namespace

Session* NewReplaySession()
{
    return new ReplaySession();
}

} // namespace revival
} // namespace efz
