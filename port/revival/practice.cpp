// The practice session (local.h): revival/EfzRevival/PracticeSession.cpp and Recorder.cpp.
//
// Pause holds the fight back (the frame isn't run, the last one is shown again with the
// overlay), and a frame step runs one frame, counting the frames stepped. Each player's
// inputs go through a Recorder, which records them into a buffer, replays one (or a
// random non-empty one) and delays them; switching players swaps the two players' key
// bindings, and mirroring reflects both around the stage's middle.
//
// Otherwise than Revival: the recorder acts in VS PLAYER's and PRACTICE's fights only
// (Revival's runs in every fight, which is the same unless a start condition was left
// on); its random draws are its own, not the game's rand (Revival's rand is its own
// generator, which the game's fights here don't use); Esc while paused goes on, so that
// the fight can be left; and a fight that a load, a mirror or the recoil-guard dummy
// changed from outside the game has no record from then on (record.h).
#include "local_internal.h"


#include "../record.h"
#include "../netplay/session.h"

namespace efz {
namespace revival {

namespace {

std::mt19937& Random()
{
    static std::mt19937 generator(std::random_device{}());
    return generator;
}

bool IsPracticeFight()
{
    int choice = MenuChoice();
    return SceneId() == 3 && (choice == 3 || choice == 2);
}

bool IsVsPlayer()
{
    return SceneId() == 3 && MenuChoice() == 2;
}

// When a recording or replay begins: at once, or when the dummy next does something.
enum StartCondition {
    kStartNow,
    kStartWakeUp,
    kStartTech,
    kStartGuard,
    kStartRecoilGuard, // guards with a recoil guard
    kStartRandomRg,    // recoil guards half the time
};

enum RecorderState {
    kIdle,
    kRecording,
    kRecordWait, // records once the start condition holds
    kReplaying,
    kReplayWait, // replays once the start condition holds
};

// One player's inputs: recorded into one of the buffers (1-5) and replayed from one (or
// a random non-empty one), delayed by some frames, and kept for the input display.
class Recorder {
public:
    explicit Recorder(int player) : player_(player) {}

    std::vector<char> history; // every input, for the input display

    void Reset()
    {
        buffers_.assign(10, std::deque<char>());
        SetBuffer(1);
        replayPos_ = 0;
        state_ = kIdle;
        random_ = false;
        start_ = kStartNow;
        delay_ = 0;
        history.clear();
        SetDelay(delay_);
    }

    void SetDelay(int frames)
    {
        if (frames < 0)
            frames = 0;
        while (delay_ < frames) {
            for (int i = 0; i < 3; i++)
                delayed_.push(0);
            delay_++;
        }
        while (delay_ > frames) {
            for (int i = 0; i < 3; i++)
                if (!delayed_.empty())
                    delayed_.pop();
            delay_--;
        }
    }

    unsigned Delay() const { return (unsigned)delayed_.size() / 3; }

    // Every frame: a waiting recording or replay starts once its condition holds.
    void CheckStart()
    {
        if (start_ == kStartRecoilGuard)
            SetRecoilGuard(true);
        if (start_ == kStartRandomRg)
            SetRecoilGuard(Random()() % 2 != 0);
        if ((start_ == kStartWakeUp && IsWakingUp(player_)) ||
            (start_ == kStartTech && IsTeching(player_)) ||
            (start_ == kStartGuard && IsGuarding(player_)) || start_ == kStartRecoilGuard ||
            (start_ == kStartRandomRg && IsRecoilGuarding(player_))) {
            if (state_ == kRecordWait) {
                StartRecord();
                return;
            }
            if (state_ == kReplayWait)
                StartReplay();
        }
    }

    void Stop()
    {
        StopReplay();
        StopRecord();
    }

    // A player's input byte for this read (CInput::GetInput, three a frame).
    void Input(char* input)
    {
        if (state_ == kRecording) {
            delayed_.push(*input);
            *input = delayed_.front();
            delayed_.pop();
            history.push_back(*input);
            buffers_[recordBuffer_].push_back(*input);
            return;
        }
        if (state_ == kReplaying) {
            std::deque<char>& buffer = buffers_[replayBuffer_];
            if (replayPos_ >= buffer.size()) {
                StopReplay();
                if (start_ != kStartNow)
                    return;
                StartReplay();
                std::deque<char>& again = buffers_[replayBuffer_];
                if (replayPos_ < again.size()) {
                    *input = again[replayPos_++];
                    history.push_back(*input);
                    return;
                }
                StopReplay();
                return;
            }
            *input = buffer[replayPos_++];
            history.push_back(*input);
            return;
        }
        if (start_ == kStartGuard || start_ == kStartRecoilGuard || start_ == kStartRandomRg) {
            *input = (char)GuardInput();
            history.push_back(*input);
        }
        delayed_.push(*input);
        *input = delayed_.front();
        history.push_back(*input);
        delayed_.pop();
    }

    void ToggleRecord()
    {
        StopReplay();
        RecorderState state = state_;
        if (state == kRecordWait) {
            if (start_ == kStartNow)
                StartRecord();
            else
                state_ = kIdle;
            return;
        }
        if (start_ == kStartNow) {
            if (state == kRecording)
                StopRecord();
            else
                StartRecord();
        } else {
            if (state == kRecording)
                StopRecord();
            else
                state_ = kRecordWait;
        }
    }

    void ToggleReplay()
    {
        StopRecord();
        RecorderState state = state_;
        if (state == kReplayWait) {
            if (start_ == kStartNow)
                StartReplay();
            else
                state_ = kIdle;
            return;
        }
        if (start_ == kStartNow) {
            if (state == kReplaying)
                StopReplay();
            else
                StartReplay();
        } else {
            if (state == kReplaying)
                StopReplay();
            else
                state_ = kReplayWait;
        }
    }

    void ToggleRandom()
    {
        StopReplay();
        StopRecord();
        random_ = !random_;
    }

    void NextStartCondition()
    {
        StopRecord();
        StopReplay();
        state_ = kIdle;
        start_ = (StartCondition)((start_ + 1) % 6);
    }

    void SetBuffer(unsigned buffer)
    {
        StopRecord();
        StopReplay();
        if (buffer <= buffers_.size()) {
            recordBuffer_ = (int)buffer;
            replayBuffer_ = (int)buffer;
        }
    }

    // A state was saved: what was being recorded or replayed starts again from here.
    void OnSaveState()
    {
        RecorderState state = state_;
        StopReplay();
        StopRecord();
        Resume(state);
    }

    void OnLoadState()
    {
        history.clear();
        RecorderState state = state_;
        StopReplay();
        StopRecord();
        Resume(state);
        SetDelay(delay_);
    }

    std::string StateName() const
    {
        switch (state_) {
        case kIdle: return "Nothing";
        case kRecording: return "Record";
        case kReplaying: return "Replay";
        case kRecordWait: return "Record Wait";
        case kReplayWait: return "Replay Wait";
        }
        return "Error";
    }

    std::string StartConditionName() const
    {
        static const char* const names[] = {"Now", "Wake-Up", "Tech", "Guard", "Recoil Guard",
                                            "Random RG"};
        return names[start_];
    }

    std::string RecordBufferName() const { return std::to_string(recordBuffer_); }
    std::string ReplayBufferName() const
    {
        return random_ ? "Rand" : std::to_string(replayBuffer_);
    }
    bool ChangesTheFight() const
    {
        return start_ == kStartRecoilGuard || start_ == kStartRandomRg;
    }

private:
    void Resume(RecorderState state)
    {
        if (state == kRecordWait || state == kReplayWait)
            state_ = state;
        else if (state == kRecording && start_ == kStartNow)
            StartRecord();
        else if (state == kReplaying && start_ == kStartNow)
            StartReplay();
    }

    // Back towards the opponent, and down unless the opponent is in the air.
    unsigned char GuardInput()
    {
        CPlayer* p = PlayerOf(player_);
        CPlayer* other = PlayerOf((player_ + 1) % 2);
        if (!p || !other)
            return 0;
        unsigned char input = p->facing != 1 ? kInputRight : kInputLeft;
        if (other->y >= -5.0)
            input |= kInputDown;
        return input;
    }

    // Recording plays the dummy: the human's keys drive the other player.
    void StartRecord()
    {
        SwapBindings();
        StopReplay();
        StopRecord();
        buffers_[recordBuffer_].clear();
        state_ = kRecording;
    }

    void StartReplay()
    {
        StopRecord();
        StopReplay();
        state_ = kReplaying;
        if (random_)
            replayBuffer_ = RandomBuffer();
        replayPos_ = 0;
    }

    void StopRecord()
    {
        if (state_ == kRecording) {
            SwapBindings();
            state_ = start_ != kStartNow ? kRecordWait : kIdle;
        } else if (state_ == kRecordWait) {
            state_ = kIdle;
        }
    }

    void StopReplay()
    {
        if (state_ == kReplaying)
            state_ = start_ != kStartNow ? kReplayWait : kIdle;
        else if (state_ == kReplayWait)
            state_ = kIdle;
    }

    int RandomBuffer()
    {
        std::vector<int> full;
        for (size_t i = 0; i < buffers_.size(); i++)
            if (!buffers_[i].empty())
                full.push_back((int)i);
        if (full.empty())
            return 0;
        return full[Random()() % full.size()];
    }

    // The low byte of m_recoilGuardWindow: 60 makes the next guard a recoil guard.
    void SetRecoilGuard(bool enable)
    {
        CPlayer* p = PlayerOf(player_);
        if (!p)
            return;
        InterruptRecord("practice: the recoil-guard dummy");
        *(unsigned char*)&p->m_recoilGuardWindow = enable ? 60 : 0;
    }

    int player_;
    RecorderState state_ = kIdle;
    bool random_ = false;
    StartCondition start_ = kStartNow;
    size_t replayPos_ = 0;
    int replayBuffer_ = 1;
    int recordBuffer_ = 1;
    std::vector<std::deque<char>> buffers_ = std::vector<std::deque<char>>(10);
    int delay_ = 0;
    std::queue<char> delayed_;
};

class PracticeSession : public Session {
public:
    void Start() override
    {
        dummy_ = 1;
        paused_ = false;
        display_ = true;
        hitBoxes_ = hurtBoxes_ = collisionBoxes_ = false;
        lastScene_ = 0;
        stepCount_ = 0;
        step_ = false;
        fps_ = kDefaultFps;
        inputDelay_ = 0;
        for (Recorder& r : recorders_)
            r.Reset();
        SetInputDelay(inputDelay_);
    }

    void KeyPressed(int key) override
    {
        const Config& ini = GetConfig();
        if (!IsPracticeFight() || ((CScene3*)SceneAt(3))->m_leave == 2)
            return;
        if (key == ini.saveState)
            SaveStateNow();
        if (key == ini.loadState)
            LoadStateNow();
        if (IsVsPlayer()) {
            if (key == ini.toggleRecord)
                recorders_[dummy_].ToggleRecord();
            if (key == ini.toggleReplay)
                recorders_[dummy_].ToggleReplay();
            if (key == ini.switchStartCondition)
                recorders_[dummy_].NextStartCondition();
            if (key == ini.toggleReplayRandom)
                recorders_[dummy_].ToggleRandom();
            if (key == ini.switchPlayers) {
                dummy_ = dummy_ == 0;
                SwapBindings();
            }
            for (int i = 0; i < 5; i++)
                if (key == ini.setBuffer[i])
                    recorders_[dummy_].SetBuffer(i + 1);
            if (key == ini.toggleRecord || key == ini.toggleReplay ||
                key == ini.switchStartCondition || key == ini.toggleReplayRandom ||
                key == ini.switchPlayers ||
                std::find(ini.setBuffer, ini.setBuffer + 5, key) != ini.setBuffer + 5) {
                const Recorder& r = recorders_[dummy_];
                LogInfo("revival", "practice: the dummy is P%d: %s, when %s, buffers %s/%s",
                        dummy_ + 1, r.StateName().c_str(), r.StartConditionName().c_str(),
                        r.RecordBufferName().c_str(), r.ReplayBufferName().c_str());
            }
            if (key == ini.mirrorPlayers) {
                InterruptRecord("practice: the players mirrored");
                const double middle = (619.0 - 20.0) / 2.0 + 20.0;
                for (int i = 0; i < 2; i++)
                    if (CPlayer* p = PlayerOf(i))
                        p->x = (p->x - middle) * -1.0 + middle;
            }
        }
        if (key == ini.pause) {
            TogglePause();
            step_ = false;
        }
        if (key == ini.stepFrame) {
            paused_ = true;
            step_ = true;
        }
        if (key == 0x01 && paused_) { // Esc: go on, and leave the fight
            paused_ = false;
            step_ = false;
            stepCount_ = 0;
        }
        if (key == ini.toggleDisplay)
            display_ = !display_;
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
        if (key == ini.increaseInputDelay)
            SetInputDelay(inputDelay_ + 1);
        if (key == ini.decreaseInputDelay)
            SetInputDelay(inputDelay_ - 1);
        if (key == ini.resetFPS) {
            fps_ = kDefaultFps;
            SetFps(fps_);
        }
    }

    bool Holds() override
    {
        if (!IsPracticeFight() || !paused_ || step_)
            return false;
        Overlay(); // the overlay of the frame shown again
        return true;
    }

    void Update() override
    {
        int scene = SceneId();
        if (lastScene_ != scene) {
            lastScene_ = scene;
            if (!IsPracticeFight())
                Reset();
        }
        if (scene == 1 || scene == 0)
            CheckDevices();
        if (IsPracticeFight()) {
            Frame();
            return;
        }
        RunGameFrame();
    }

    void Input(unsigned char* input, int player) override
    {
        if (IsPracticeFight())
            recorders_[player].Input((char*)input);
    }

private:
    void Overlay()
    {
        DrawHud();
        ShowAllBoxes();
        SetTextRender(display_);
    }

    // A frame of the fight.
    void Frame()
    {
        Overlay();
        recorders_[0].CheckStart();
        recorders_[1].CheckStart();
        if (paused_) {
            if (step_) {
                stepCount_++;
                RunGameFrame();
                step_ = false;
            }
            return;
        }
        RunGameFrame();
    }

    // Out of the fight: everything back to normal.
    void Reset()
    {
        paused_ = false;
        step_ = false;
        stepCount_ = 0;
        SetTextRender(false);
        ClearBoxes();
        fps_ = kDefaultFps;
        SetFps(fps_);
        dummy_ = HumanPlayer() == 0;
        saveState_.Clear();
        for (Recorder& r : recorders_)
            r.Stop();
        UnswapBindings();
    }

    void TogglePause()
    {
        paused_ = !paused_;
        stepCount_ = 0;
    }

    void SaveStateNow()
    {
        for (Recorder& r : recorders_)
            r.OnSaveState();
        saveState_.Save();
        LogInfo("revival", "practice: the state saved");
    }

    void LoadStateNow()
    {
        InterruptRecord("practice: a state loaded");
        LoadKeepingFps(saveState_);
        if (paused_) {
            step_ = false;
            stepCount_ = 0;
            // The frame the state has, shown now (its back buffer and palette are in it).
            GameObjects o = Objects();
            if (o.graphics && o.graphics->m_back)
                Present(o.graphics->m_back, ScreenPalette(o.graphics));
        }
        for (Recorder& r : recorders_)
            r.OnLoadState();
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

    void DrawHud()
    {
        ClearText();
        int x = dummy_ == 0 ? 10 : 450;
        int line = 0;
        auto add = [&](const std::string& text) { AddText(text, x, 96 + 14 * line++); };
        if (IsVsPlayer()) {
            add(std::string("Player:        ") + (dummy_ == 0 ? "P2" : "P1"));
            const Recorder& r = recorders_[dummy_];
            add("What:          " + r.StateName());
            add("When:          " + r.StartConditionName());
            add("Record Buffer: " + r.RecordBufferName());
            add("Replay Buffer: " + r.ReplayBufferName());
        } else {
            add("Player:        Fixed");
        }
        add("Input Delay:   " + std::to_string(recorders_[Other()].Delay()));
        add("Frame Step:    " + std::to_string(stepCount_));
        if (fps_ != kDefaultFps)
            add("Speed:         " + std::to_string((int)fps_) + " FPS");
        DrawInputs(recorders_[Other()].history, 200, 10, 3);
    }

    // The delay applies to the human player's inputs.
    void SetInputDelay(int frames)
    {
        if (frames < 0)
            frames = 0;
        inputDelay_ = frames;
        recorders_[Other()].SetDelay(frames);
    }

    int Other() const { return (dummy_ + 1) % 2; }

    Recorder recorders_[2] = {Recorder(0), Recorder(1)};
    int dummy_ = 1; // the player the recording and replay keys drive
    netplay::SaveState saveState_;
    int inputDelay_ = 0;
    bool step_ = false;
    int stepCount_ = 0; // frames stepped since pausing
    bool paused_ = false;
    bool display_ = true;
    bool hitBoxes_ = false, hurtBoxes_ = false, collisionBoxes_ = false;
    int lastScene_ = 0;
    double fps_ = kDefaultFps;
};

} // namespace

Session* NewPracticeSession()
{
    return new PracticeSession();
}

} // namespace revival
} // namespace efz
