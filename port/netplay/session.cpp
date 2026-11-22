// Netplay's session (session.h): OnlineSession.cpp, OnlineSync.cpp and GameState.cpp of
// revival/EfzRevival/, with the game's objects in place of efz.exe's addresses.
#include "session.h"

#include <limits.h>
#include <math.h>
#include <time.h>
#include <algorithm>

#include "efz.h"
#include "../platform.h"
#include "../log.h"
#include "../agents.h"
#include "../revival/config.h"
#include "../revival/keys.h"

// src/scene3.cpp: whether an F-key was down on the last frame (efz.exe's word that
// Revival's save states keep).
extern int g_fkeyHeld;

namespace efz {
// The size of a player's object, by its character class (CScene2::CreateCharacter):
// platform.h.
size_t PlayerSize(CPlayer* p)
{
    switch (p->m_charId) {
    case 0: return sizeof(CNanase);
    case 1: return sizeof(CAyu);
    case 2: return sizeof(CMai);
    case 3: return sizeof(CMakoto);
    case 4: return sizeof(CAkane);
    case 5: return sizeof(CMayu);
    case 6: return sizeof(CNagamori);
    case 7: return sizeof(CMisaki);
    case 8: return sizeof(CShiori);
    case 9: return sizeof(CSayuri);
    case 0xa: return sizeof(CNayuki);
    case 0xb: return sizeof(CMio);
    case 0xc: return sizeof(CEXNanase);
    case 0xd: return sizeof(CKaori);
    case 0xe: return sizeof(CIkumi);
    case 0xf: return sizeof(CMishio);
    case 0x10: return sizeof(CAkiko);
    case 0x11: return sizeof(CNayukiB);
    case 0x12: return sizeof(CMizukaB);
    case 0x13: return sizeof(CKanna);
    case 0x14: return sizeof(CKano);
    case 0x15: return sizeof(CMinagi);
    case 0x16: return sizeof(CNayuki);
    case 0x17: return sizeof(CMisuzu);
    case 0x18: return sizeof(CMizuka);
    }
    return sizeof(CPlayer);
}

namespace netplay {

namespace {

// Rollback starts this many frames into a fight, and stops this many after the match is
// decided (OnlineSession.cpp).
const int kFightSettleFrames = 20;
const int kMatchOverFrames = 120;
// What _controlfp_s gives in efz.exe under Revival, for the sync records: the x87 at
// 53-bit precision, rounding to nearest, every exception masked (_PC_53 | _MCW_EM, the
// CRT's start-up state, which Revival's Direct3D device preserves).
const uint32_t kFpuControl = 0x9001f;
// Milliseconds a frame lasts (Revival takes it from DDRAW.dll's timer).
const double kMsPerFrame = 1000.0 / 64;
// DIK_ codes.
const int kDikEscape = 0x01, kDikF4 = 0x3e, kDikF9 = 0x43, kDikF10 = 0x44;

const revival::Config& Ini()
{
    return revival::GetConfig();
}

GameObjects G()
{
    return Objects();
}

CScene3* Fight()
{
    return (CScene3*)G().scenes[3];
}

CPlayer* Player(int i)
{
    CScene3* fight = Fight();
    if (!fight)
        return nullptr;
    PTR32(CPlayer)* ref = i == 0 ? (PTR32(CPlayer)*)fight->m_player1Ref
                                 : (PTR32(CPlayer)*)fight->m_player2Ref;
    return ref ? (CPlayer*)*ref : nullptr;
}


// Game::character, paletteNumber, hasPalette, canChoosePalette.
int CharacterOf(int player)
{
    GameObjects o = G();
    int scene = *o.scene;
    if (scene == 2 || scene == 3) {
        CScene* s = o.scenes[scene];
        PTR32(CPlayer)* ref = player == 0 ? (PTR32(CPlayer)*)s->m_player1Ref
                                          : (PTR32(CPlayer)*)s->m_player2Ref;
        CPlayer* p = ref ? (CPlayer*)*ref : nullptr;
        return p ? p->m_charId : -1;
    }
    if (scene == 1)
        return ((CScene1*)o.scenes[1])->m_charId[player];
    return -1;
}

int PaletteNumber(int player)
{
    GameObjects o = G();
    switch (*o.scene) {
    case 1:
    case 2:
        return ((CScene1*)o.scenes[1])->m_paletteIndex[player];
    case 3:
        if (CPlayer* p = Player(player))
            return p->m_paletteIndex;
        return 0;
    }
    return 0;
}

bool HasPalette(int player)
{
    GameObjects o = G();
    int scene = *o.scene;
    return scene >= 1 && scene <= 3 && (o.game->m_editColor[player] & 0xff) != 0;
}

bool CanChoosePalette(int player)
{
    GameObjects o = G();
    switch (*o.scene) {
    case 1:
        return ((CScene1*)o.scenes[1])->m_state[player] == 6;
    case 2:
    case 3:
        return true;
    }
    return false;
}

// std::put_time's, local time.
std::string TimeText(time_t t, const char* format)
{
    tm local;
#ifdef _WIN32
    localtime_s(&local, &t);
#else
    localtime_r(&t, &local);
#endif
    char text[64];
    strftime(text, sizeof(text), format, &local);
    return text;
}

// A field padded as an iostream's width pads it: to `width` characters (UTF-16 units: a
// wide stream's, as Revival's lines are made) or bytes (the narrow file stream's), on the
// right (left-aligned) or the left.
size_t Units(const std::string& utf8, bool bytes)
{
    if (bytes)
        return utf8.size();
    size_t n = 0;
    for (size_t i = 0; i < utf8.size(); i++) {
        unsigned char c = (unsigned char)utf8[i];
        if ((c & 0xc0) != 0x80)
            n += c >= 0xf0 ? 2 : 1;
    }
    return n;
}

std::string Pad(const std::string& s, size_t width, bool left, bool bytes = false, char fill = ' ')
{
    size_t n = Units(s, bytes);
    if (n >= width)
        return s;
    std::string padding(width - n, fill);
    return left ? s + padding : padding + s;
}

// The names Revival gives the characters in replay file names (Game::characterName).
const char* CharacterName(int c)
{
    static const char* const names[] = {
        "Rumi",    "Ayu",  "Mai",    "Makoto",  "Akane",   "Mayu",  "Nagamori",
        "Misaki",  "Shiori", "Sayuri", "NayukiS", "Mio",   "Doppel", "Kaori",
        "Ikumi",   "Mishio", "Akiko", "NayukiA", "Unknown", "Kanna", "Kano",
        "Minagi",  "AltNayukiS", "Misuzu", "BossUnknown"};
    return c >= 0 && c < 25 ? names[c] : "error";
}

// A name as part of a file name.
std::string FileSafe(const std::string& s)
{
    std::string out;
    for (char c : s)
        out.push_back((unsigned char)c < 0x20 || strchr("\\/:*?\"<>|", c) ? '_' : c);
    return out;
}

} // namespace

// --- SaveState: the fight scene, CGame and both players, the screen's palette and back
// buffer, the stage's animation, the F-key word and rand's state.

void SaveState::Add(void* at, size_t size)
{
    size_t offset = data_.size();
    data_.resize(offset + size);
    memcpy(data_.data() + offset, at, size);
    regions_.push_back(Region{(char*)at, size, offset});
}

void SaveState::Save()
{
    Clear();
    GameObjects o = G();
    CScene3* fight = Fight();
    Add(&g_fkeyHeld, sizeof(g_fkeyHeld));
    Add(fight, sizeof(CScene3));
    Add(o.game, sizeof(CGame));
    for (int i = 0; i < 2; i++) {
        if (CPlayer* p = Player(i))
            Add(p, PlayerSize(p));
    }
    if (PALETTEENTRY* palette = ScreenPalette(o.graphics))
        Add(palette, 0x100 * sizeof(PALETTEENTRY));
    if (IDirectDrawSurface* back = o.graphics->m_back)
        Add(back->pixels, (size_t)back->pitch * back->height);
    if (CAnimBg* bg = o.game->m_background) {
        if (bg->m_objects)
            Add((BgObject*)bg->m_objects, bg->m_number == 16 ? 0x1c0 : 0xe0);
    }
    rng_ = RandState();
    saved_ = true;
}

void SaveState::AddInt(int* value)
{
    Add(value, sizeof(*value));
}

void SaveState::Load()
{
    if (!saved_)
        return;
    SetRandState(rng_);
    for (const Region& r : regions_)
        memcpy(r.at, data_.data() + r.offset, r.size);
}

void SaveState::Clear()
{
    regions_.clear();
    data_.clear();
    saved_ = false;
}

// --- Starting and stopping

void Session::Start(Protocol* protocol)
{
    protocol_ = protocol;
    local_ = protocol->localPlayer;
    remote_ = protocol->remotePlayer;
    GameObjects o = G();

    // OnlineSession::start
    SetRevivalRand(true);
    SeedRevivalRand(protocol->seed);
    SetInputDelay(protocol->delay);
    maxRollback_ = protocol->rollback;
    frame_ = 0;
    scene_ = 0;
    newScene_ = 0;
    fightStart_ = 0;
    confirmedFrame_ = 0;
    syncedFrame_ = 0;
    played_.assign(30, std::map<int, int>());
    confirmed_.assign(30, std::map<int, int>());
    soundCounts_.clear();
    states_.resize(60);
    for (SaveState& s : states_)
        s.Clear();
    sceneFrames_ = 0;
    matchOverFrame_ = INT_MAX - 1000;
    matchNumber_ = 0;
    lastFrame_ = 0;
    wins_[0] = wins_[1] = 0;
    stalled = 0;
    rollbacks_ = rerun_ = deepest_ = 0;
    ping_ = PingStats();
    writeReplay_ = true;
    replayOpen_ = false;
    pending_ = false;
    pendingWords_.clear();
    pendingInputs_.clear();
    replayFlushed_ = replaySaved_ = false;
    hideRemotePalettes_ = palettesToggled_ = false;
    rounds_[0] = rounds_[1] = 0;
    palettes_[0].Clear();
    palettes_[1].Clear();
    palettes_[local_].LoadCustom();
    OpenBattleLog();
    // P1's inputs through the title to VS HUMAN: down, down, A; P2's are nothing.
    static const char start[22] = {0, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0,
                                   4, 0, 0, 0, 0, 0x10, 0, 0, 0, 0, 0};
    for (char c : start)
        AddInput(FrameInput{local_ == 0 ? c : (char)0, 0});
    // Game::setSpectating and setup's setGameFlag1366: normal effects, every frame drawn,
    // 100% damage, two rounds, whatever this side's key.ini says.
    CGame* game = o.game;
    game->m_fullEffects = 1;
    game->m_oddFrame = 0;
    game->m_drawEveryFrame = 1;
    game->m_damageLevel = 2;
    game->m_roundsSetting = 2;
    LogInfo("net", "the match starts: P%d here, delay %d, rollback %d, seed %u", local_ + 1,
            inputDelay_, maxRollback_, protocol->seed);
}

void Session::Stop()
{
    if (!protocol_)
        return;
    if (replayOpen_)
        ReplayClose();
    pending_ = false;
    pendingWords_.clear();
    pendingInputs_.clear();
    LogInfo("net", "the match ran %d frames; %d rollbacks ran %d frames again, at most %d at once",
            frame_, rollbacks_, rerun_, deepest_);
    g_skipDrawing = false;
    SetRevivalRand(false);
    for (SaveState& s : states_)
        s.Clear();
    protocol_ = nullptr;
}

// --- Each real frame (OnlineSession::update)

int Session::Scene() const
{
    return *G().scene;
}

void Session::Update()
{
    newScene_ = Scene();
    if (newScene_ != scene_)
        SceneChanged();
    ping_ = protocol_->sessionPing;
    // receivePalettes: the opponent's, as they came.
    for (const ColorPalette& palette : protocol_->remotePalettes) {
        int key;
        memcpy(&key, palette.data, 4);
        if (!palettes_[remote_].Has(key))
            LogInfo("net", "%s's custom palette %d of %s came", protocol_->names[remote_].c_str(),
                    (key & 0xff) + 1, PaletteFolder(key >> 24 & 0xff));
        palettes_[remote_].Add(palette);
    }
    protocol_->remotePalettes.clear();
    if (frame_ > lastFrame_)
        lastFrame_ = frame_;
    KeyPressed();
    int before = frame_;
    int iterations;
    switch (newScene_) {
    case 0:
        iterations = MenuFramesToRun();
        RunQuitFrames(iterations);
        break;
    case 3:
        if (frame_ >= fightStart_ + kFightSettleFrames)
            maxRollback_ = protocol_->rollback;
        if (frame_ >= matchOverFrame_ + kMatchOverFrames)
            maxRollback_ = 0;
        iterations = FightFramesToRun();
        RunFightFrames(iterations);
        break;
    case 1:
    case 2:
        iterations = MenuFramesToRun();
        RunMenuFrames(iterations);
        break;
    default:
        iterations = MenuFramesToRun();
        RunFrames(iterations);
        break;
    }
    stalled = frame_ == before && iterations == 0 ? stalled + 1 : 0;
    // The launcher's handleQueueEvent: the new local inputs go out.
    protocol_->SendInputs();
}

// Loads the last confirmed state, having run the frames from there up to the current
// one with the drawing off, and the last one with it on.
void Session::RunFightFrames(int count)
{
    for (int i = 0; i < 2; i++) {
        if (CPlayer* p = Player(i))
            rounds_[i] = p->m_roundsWon;
    }
    g_skipDrawing = true;
    for (int i = 0; i < count; i++) {
        if (i == count - 1)
            g_skipDrawing = false;
        int frame = frame_;
        if (CanSave(frame))
            Confirmed(frame).clear();
        SaveFrameState();
        scene_ = Scene();
        RunFrame();
        // The frame drawn, the one the player sees: an agent playing this side sees it
        // too (once, not again when a rollback runs it again).
        if (i == count - 1)
            NetplayAgentShown();
        if (frame_ > lastFrame_) {
            lastFrame_ = frame_;
            Played(frame_).clear();
        }
        if (Scene() != scene_) {
            g_skipDrawing = false;
            return;
        }
    }
    g_skipDrawing = false;
    LoadState(frame_);
}

void Session::RunQuitFrames(int count)
{
    for (int i = 0; i < count; i++) {
        if ((unsigned)frame_ >= Local().size())
            AddInput(ReadInput());
        scene_ = Scene();
        RunFrame();
        if (Scene() != scene_)
            break;
    }
}

void Session::RunMenuFrames(int count)
{
    // The local player's custom palette goes to the other side every 30 frames, from the
    // colour's choice on.
    if (frame_ % 30 == 0)
        SendLocalPalette();
    for (int i = 0; i < count; i++) {
        if ((unsigned)frame_ >= Local().size() - 1)
            AddInput(ReadInput());
        scene_ = Scene();
        RunFrame();
        if (Scene() != scene_)
            return;
    }
}

void Session::RunFrames(int count)
{
    for (int i = 0; i < count; i++) {
        if ((unsigned)frame_ >= Local().size())
            AddInput(ReadInput());
        if ((unsigned)frame_ >= Remote().size())
            return;
        scene_ = Scene();
        RunFrame();
        if (Scene() != scene_)
            return;
    }
}

// One frame of the game, its sync record made the first time it is final.
void Session::RunFrame()
{
    // Out of a fight, frames still without a record were left behind: the fight ended
    // on a frame run before the other side's input for it came (Esc, predicted), and
    // no rollback runs them again. EfzRevival.dll's runFrame makes no record after
    // such a frame for the rest of the session; this one goes on from the frame after,
    // so that the comparison, and the warning of a desync, go on (Protocol: those
    // frames are holes, never compared and never sent).
    if (syncedFrame_ < frame_ && Scene() != 3)
        syncedFrame_ = frame_;
    if (frame_ == syncedFrame_ && Remote().size() > (unsigned)frame_ &&
        Local().size() > (unsigned)frame_) {
        SendSync(protocol_->inputs[0][frame_], protocol_->inputs[1][frame_]);
        syncedFrame_++;
    }
    GameObjects o = G();
    SetLogFrame(frame_, *o.scene);
    *o.scene = o.scenes[*o.scene]->Update();
    sceneFrames_++;
    frame_++;
}

// Out of a fight: the frames the remote inputs cover, none when there are too few.
int Session::MenuFramesToRun()
{
    int delay = (int)ceil(PingFrames(ping_.maximum));
    int last = (int)Local().size() - delay - 1;
    if (last < 0 || last >= (int)Remote().size())
        return 0;
    AddInput(ReadInput());
    return last + 1 - frame_;
}

int Session::FightFramesToRun()
{
    if (maxRollback_ == 0)
        return MenuFramesToRun();
    int ahead = (int)Local().size() - (int)Remote().size();
    FrameInput last = Local().back();
    if (ahead > maxRollback_ + inputDelay_)
        return 0; // too far ahead of the remote inputs: wait
    AddInput(ReadInput());
    if ((unsigned)(inputDelay_ + frame_) >= Local().size() && frame_ > 0) {
        AddInput(last); // too little delay left
        return 0;
    }
    int behind = (int)floor(PingFrames(ping_.minimum)) - 1;
    if (ahead < behind)
        AddInput(last); // the remote side is ahead: catch up a frame
    return (int)Local().size() - frame_ - inputDelay_ - 1;
}

void Session::SceneChanged()
{
    LogInfo("net", "frame %d: scene %d after %d frames of scene %d", frame_, Scene(), sceneFrames_,
            scene_);
    sceneFrames_ = 0;
    matchOverFrame_ = INT_MAX - 1000;
    int previous = scene_;
    scene_ = Scene();
    CGame* game = G().game;
    switch (scene_) {
    case 1:
        inputDelay_ = (int)ceil(PingFrames(ping_.maximum));
        break;
    case 3: {
        maxRollback_ = 0;
        SetInputDelay(matchDelay_);
        fightStart_ = frame_;
        confirmedFrame_ = frame_;
        ApplyPalette(local_, HasPalette(local_));
        ApplyPalette(remote_, HasPalette(remote_) && !hideRemotePalettes_);
        states_[frame_ % states_.size()].Save();
        fightTime_ = time(nullptr);
        // Game::setRandomSeed(newRandomSeed()): the replay's random state.
        replaySeed_ = RandState();
        for (int i = 0; i < 2; i++) {
            CPlayer* p = Player(i);
            characters_[i] = p ? p->m_charId : -1;
        }
        LogInfo("net", "match %d, fight at frame %d", matchNumber_, frame_);
        break;
    }
    case 2:
        matchNumber_++;
        replayName_ = ReplayName();
        SetNetplay(true);
        writeReplay_ = true;
        replayFlushed_ = replaySaved_ = false;
        break;
    case 5:
        if (game->m_winner == 0 || game->m_winner == 1)
            wins_[(int)game->m_winner]++;
        LogGame();
        rounds_[0] = rounds_[1] = 0;
        break;
    default:
        break;
    }
    (void)previous;
}

// --- Rollback

bool Session::CanSave(unsigned frame)
{
    return frame < Local().size() && frame < Remote().size() && frame == (unsigned)confirmedFrame_;
}

// The state of the current frame, if both players' inputs for it are known.
void Session::SaveFrameState()
{
    if (Scene() != 3)
        return;
    if (CanSave(frame_)) {
        // ToggleRemotePalettes takes effect on a confirmed frame, so that a rollback
        // doesn't undo it.
        if (palettesToggled_) {
            ApplyPalette(remote_, HasPalette(remote_) && !hideRemotePalettes_);
            RefreshPalette(remote_);
            palettesToggled_ = false;
        }
        SaveState& s = states_[frame_ % states_.size()];
        s.Save();
        s.AddInt(&frame_);
        s.AddInt(&sceneFrames_);
        confirmedFrame_++;
        writeReplay_ = true;
        replayInputs_.push_back(protocol_->inputs[0][frame_]);
        replayInputs_.push_back(protocol_->inputs[1][frame_]);
        if (IsMatchOver() && frame_ < matchOverFrame_)
            matchOverFrame_ = frame_;
    } else {
        writeReplay_ = false;
    }
}

// The frame a rollback goes back to: the last confirmed one, not before the fight.
int Session::LoadFrame()
{
    return std::max(confirmedFrame_ - 1, fightStart_);
}

// Back to the last confirmed frame, with the sounds of the frames to run again counted
// so that they don't play twice.
void Session::LoadState(int to)
{
    if (Scene() != 3 || maxRollback_ == 0)
        return;
    int frame = LoadFrame();
    CountSounds(frame, to);
    soundCounts_.clear();
    for (int i = std::max(frame, fightStart_); i <= to; i++)
        for (const auto& sound : Played(i))
            soundCounts_[sound.first] += sound.second;
    rollbacks_++;
    rerun_ += frame_ - frame;
    deepest_ = std::max(deepest_, frame_ - frame);
    states_[frame % states_.size()].Load();
}

std::map<int, int>& Session::Played(int frame)
{
    static std::map<int, int> none;
    if (frame < 0) {
        none.clear();
        return none;
    }
    return played_[frame % played_.size()];
}

std::map<int, int>& Session::Confirmed(int frame)
{
    static std::map<int, int> none;
    if (frame < 0) {
        none.clear();
        return none;
    }
    return confirmed_[frame % confirmed_.size()];
}

// Stops the sounds played on predicted inputs that neither were confirmed nor will be
// played again, and forgets them.
void Session::CountSounds(int from, int to)
{
    std::map<int, int> recent, confirmed, replayed;
    for (int i = from; i <= to; i++)
        for (const auto& s : Played(i))
            replayed[s.first] += s.second;
    for (int i = from - maxRollback_; i <= from; i++)
        for (const auto& s : Played(i))
            recent[s.first] += s.second;
    for (int i = from - maxRollback_; i <= from; i++)
        for (const auto& s : Confirmed(i))
            confirmed[s.first] += s.second;
    for (const auto& s : recent) {
        if (confirmed.find(s.first) == confirmed.end() && replayed.find(s.first) == replayed.end()) {
            G().sound->Stop((WORD)s.first);
            for (int i = from - maxRollback_ - 1; i < to; i++)
                Played(i).erase(s.first);
        }
    }
}

bool Session::Sound(unsigned short id, int)
{
    if (Scene() != 3)
        return false;
    unsigned frame = frame_;
    if (frame < Local().size() && frame < Remote().size())
        Confirmed(frame_)[id]++;
    if (--soundCounts_[id] < 0) {
        Played(frame_)[id]++;
        return false; // play it
    }
    return true; // played already, the first time this frame ran
}

// --- Inputs

void Session::Input(int player, unsigned char* input)
{
    if (player == local_) {
        std::vector<FrameInput>& local = Local();
        if ((unsigned)frame_ < local.size())
            *input = (unsigned char)local[frame_].first;
        else
            *input = local.empty() ? 0 : (unsigned char)local.back().first;
        return;
    }
    std::vector<FrameInput>& remote = Remote();
    int frame = frame_;
    if (frame >= (int)remote.size() - 1)
        frame = (int)remote.size() - 1;
    *input = frame >= 0 ? (unsigned char)remote[frame].first : 0;
}

// The fight's update: F4-F8 and Esc as either player pressed them.
void Session::FightKeys(char* keys)
{
    if (Scene() != 3 || Local().empty())
        return;
    unsigned i = frame_;
    char local = i < Local().size() ? Local()[i].second : Local().back().second;
    char remote = 0;
    if (!Remote().empty())
        remote = i >= Remote().size() ? Remote().back().second : Remote()[i].second;
    char pressed = local | remote;
    for (int key = 0; key < 5; key++)
        keys[kDikF4 + key] = (pressed & (1 << key)) ? (char)0x80 : 0;
    keys[kDikEscape] = (char)((pressed & 0xe0) << 2);
}

FrameInput Session::ReadInput()
{
    char input = (char)LocalControls();
    // An agent playing this side: its input, decided once for this frame of input. Out
    // of a fight the inputs take effect after the ping's frames.
    unsigned char agent = 0;
    if (NetplayAgentInput(Scene(), (int)ceil(PingFrames(ping_.maximum)), &agent))
        input = (char)agent;
    const unsigned char* keyboard = KeyboardState();
    char keys = 0;
    for (int key = 0; key < 5; key++)
        if (keyboard[kDikF4 + key] & 0x80)
            keys |= 1 << key;
    if (keyboard[kDikEscape] & 0x80)
        keys |= 0x20;
    if (Scene() == 3)
        keys &= protocol_->practiceKeys ? 0x23 : 0x20;
    if (Scene() == 1)
        keys &= 0x20; // and Esc leaves, which netplay.cpp sees itself
    return FrameInput{input, keys};
}

void Session::AddInput(const FrameInput& input)
{
    Local().push_back(input);
}

void Session::SetInputDelay(int delay)
{
    delay = std::max(0, std::min(delay, 20));
    inputDelay_ = delay;
    matchDelay_ = delay;
}

// A round trip, in frames each way.
float Session::PingFrames(int ping)
{
    return (float)(ping / (kMsPerFrame * 2));
}

// OnlineSession::keyPressed: SavePreviousReplay on character select and the results;
// in a fight IncreaseInputDelay and DecreaseInputDelay (the keypad's + and - as Revival
// ships; F10 and F9 too, for keyboards without a keypad) and ToggleRemotePalettes.
void Session::KeyPressed()
{
    const revival::Config& ini = Ini();
    int scene = Scene();
    if ((scene == 1 || scene == 5) && revival::Pressed(ini.savePreviousReplay)) {
        replayFlushed_ = true;
        replaySaved_ |= FlushReplay();
    }
    if (scene != 3)
        return;
    if (revival::Pressed(ini.increaseInputDelay) || revival::Pressed(kDikF10))
        SetInputDelay(inputDelay_ + 1);
    if (revival::Pressed(ini.decreaseInputDelay) || revival::Pressed(kDikF9)) {
        int minimum = (int)ceil(PingFrames(ping_.maximum)) - maxRollback_;
        SetInputDelay(std::max(inputDelay_ - 1, minimum));
    }
    if (revival::Pressed(ini.toggleRemotePalettes)) {
        hideRemotePalettes_ = !hideRemotePalettes_;
        if (HasPalette(remote_))
            palettesToggled_ = true;
        LogInfo("net", "the opponent's palette %s", hideRemotePalettes_ ? "hidden" : "shown");
    }
}

// --- Sync records (OnlineSync.cpp's makeSyncBlock)

void Session::SendSync(const FrameInput& p1, const FrameInput& p2)
{
    SyncBlock sync;
    memset(&sync, 0, sizeof(sync));
    sync.frame = frame_;
    sync.state = Scene();
    sync.inputP1 = p1;
    sync.inputP2 = p2;
    sync.fpuCW = kFpuControl;
    sync.rng = RandState();
    if (Scene() == 3) {
        CPlayer* a = Player(0);
        CPlayer* b = Player(1);
        if (a && b) {
            sync.stateP1 = (int16_t)a->pattern;
            sync.stateP2 = (int16_t)b->pattern;
            sync.p1x = a->x;
            sync.p1y = a->y;
            sync.p2x = b->x;
            sync.p2y = b->y;
        }
    }
    protocol_->AddLocalSync(sync);
}

// --- The game's state

bool Session::IsMatchOver()
{
    return Scene() == 3 && Fight()->m_leave == 2;
}

// Game::setNetplay: from match setup on the game plays as a recorded replay (mode 5,
// recording), so that it writes the replay; the end of the fight makes it VS HUMAN.
void Session::SetNetplay(bool on)
{
    CGame* game = G().game;
    game->m_gameMode = on ? 5 : 4;
    game->m_cpuLevel = on ? 1 : 4;
    game->m_replayMode = on ? 2 : 0;
}

// applyPalette, as a fight starts: the player's custom palette when EDIT COLOR picked one
// (this side's from its file, the other's as it sent it), else the colour's own from the
// character's .dat.
void Session::ApplyPalette(int player, bool custom)
{
    ColorPalette palette;
    memset(palette.data, 0xff, 4); // no palette found
    palettes_[player].Find(CharacterOf(player), custom, PaletteNumber(player), &palette);
    int key;
    memcpy(&key, palette.data, 4);
    if (key == -1)
        return;
    bool customFound = (key >> 16 & 0xf) != 0;
    LogInfo("net", "P%d's palette: %s, number %d of %s", player + 1,
            !customFound        ? "the colour's own"
            : player == local_ ? "custom, this computer's"
                               : "custom, the one the other side sent",
            (key & 0xff) + 1, PaletteFolder(key >> 24 & 0xff));
    CGame* game = G().game;
    memcpy(&game->m_palette[95 + player * 40], palette.data + 4, 40 * sizeof(PALETTEENTRY));
    G().graphics->BuildBlendTables(game->m_palette);
}

// The palette applied to the screen's at once (Game::refreshPalette).
void Session::RefreshPalette(int player)
{
    GameObjects o = G();
    if (PALETTEENTRY* screen = ScreenPalette(o.graphics)) {
        int start = 95 + player * 40;
        memcpy(&screen[start], &o.game->m_palette[start], 40 * sizeof(PALETTEENTRY));
    }
}

void Session::SendLocalPalette()
{
    if (!CanChoosePalette(local_) || !HasPalette(local_))
        return;
    ColorPalette palette;
    if (palettes_[local_].Find(CharacterOf(local_), true, PaletteNumber(local_), &palette))
        protocol_->SendPalette(palette);
}

bool Session::DisplayScore() const
{
    return Ini().displayScore;
}

std::string Session::ReplayMessage() const
{
    if (!replayFlushed_)
        return "";
    if (Ini().saveAllReplays)
        return "All replays get autosaved";
    return replaySaved_ ? "Saved replay to disk" : "Failed to save replay";
}

bool Session::ShowInfo() const
{
    int scene = Scene();
    return scene != 0 && scene != 2;
}

void Session::MatchLeft()
{
    G().game->m_replay.Close();
    SetNetplay(false);
}

// --- The replay (EfzGame.cpp: openReplayWrite, writeInput, closeReplay,
// writeExtendedReplay): the game's own words, then 30 blank records, the random state,
// both players' inputs of every confirmed frame, where that part starts, and -1.

std::string Session::ReplayName()
{
    std::string stamp = TimeText(time(nullptr), "%Y%m%d-%H%M%S");
    int c[2];
    for (int i = 0; i < 2; i++) {
        CPlayer* p = nullptr;
        if (CScene* s = G().scenes[2]) {
            PTR32(CPlayer)* ref = i == 0 ? (PTR32(CPlayer)*)s->m_player1Ref
                                         : (PTR32(CPlayer)*)s->m_player2Ref;
            p = ref ? (CPlayer*)*ref : nullptr;
        }
        c[i] = p ? p->m_charId : -1;
    }
    // <ReplayFolder>\<time> <P1> (<character>) vs <P2> (<character>).rep
    std::string folder = Ini().replayFolder;
    if (!folder.empty() && folder.back() != '/' && folder.back() != '\\')
        folder += "/";
    return folder + stamp + " " + FileSafe(protocol_->names[0]) + " (" + CharacterName(c[0]) +
           ") vs " + FileSafe(protocol_->names[1]) + " (" + CharacterName(c[1]) + ").rep";
}

void Session::ReplayOpen()
{
    // openReplayWrite: the last match's replay, never saved, is let go.
    if (pending_)
        LogInfo("net", "the previous match's replay is let go (not saved)");
    pending_ = false;
    pendingWords_.clear();
    pendingInputs_.clear();
    replayWords_.clear();
    replayInputs_.clear();
    replayOpen_ = true;
}

void Session::ReplayWrite(short value)
{
    if (replayOpen_ && writeReplay_)
        replayWords_.push_back(value);
}

// The replay as Revival writes it (writeExtendedReplay).
void Session::WriteReplay(FILE* f, const std::vector<short>& words, uint32_t seed,
                          const std::vector<FrameInput>& inputs)
{
    fwrite(words.data(), 2, words.size(), f);
    int32_t end[4] = {9999 << 16, 0, 0, 0};
    for (int i = 0; i < 30; i++)
        fwrite(end, sizeof(end), 1, f);
    int32_t offset = (int32_t)ftell(f);
    int32_t seed32 = (int32_t)seed;
    int32_t count = (int32_t)inputs.size();
    int32_t marker = -1;
    fwrite(&seed32, 4, 1, f);
    fwrite(&count, 4, 1, f);
    fwrite(inputs.data(), 2, inputs.size(), f);
    fwrite(&offset, 4, 1, f);
    fwrite(&marker, 4, 1, f);
}

void Session::ReplayClose()
{
    if (!replayOpen_)
        return;
    replayOpen_ = false;
    std::string name = replayName_.empty() ? "replay/netplay/match.rep" : replayName_;
    if (!Ini().saveAllReplays) {
        // closeReplay: kept for SavePreviousReplay.
        pending_ = true;
        pendingWords_.swap(replayWords_);
        pendingInputs_.swap(replayInputs_);
        pendingSeed_ = replaySeed_;
        pendingName_ = name;
        LogInfo("net", "the match's replay is kept until saved (SaveAllReplays = 0)");
        return;
    }
    FILE* f = OpenGameFile(name.c_str(), "wb");
    if (!f) {
        LogWarn("net", "can't write the replay %s", name.c_str());
        return;
    }
    WriteReplay(f, replayWords_, replaySeed_, replayInputs_);
    fclose(f);
    savedReplay = name;
    LogInfo("net", "replay saved: %s (%u frames)", name.c_str(),
            (unsigned)replayInputs_.size() / 2);
}

// Game::flushReplay: the replay kept back, saved now.
bool Session::FlushReplay()
{
    if (!pending_ || Ini().saveAllReplays)
        return false;
    FILE* f = OpenGameFile(pendingName_.c_str(), "wb");
    if (!f) {
        LogWarn("net", "can't write the replay %s", pendingName_.c_str());
        return false;
    }
    WriteReplay(f, pendingWords_, pendingSeed_, pendingInputs_);
    fclose(f);
    savedReplay = pendingName_;
    LogInfo("net", "replay saved: %s (%u frames)", pendingName_.c_str(),
            (unsigned)pendingInputs_.size() / 2);
    pending_ = false;
    pendingWords_.clear();
    pendingInputs_.clear();
    return true;
}

// --- The battle log (OnlineSession::start and sceneChanged's scene 5): a line for the
// session, then one a game, in Revival's columns.

void Session::OpenBattleLog()
{
    battleLog_.clear();
    const revival::Config& ini = Ini();
    if (!ini.saveBattleLog || ini.battleLogFile.empty())
        return;
    battleLog_ = ini.battleLogFile;
    FILE* existing = OpenGameFile(battleLog_.c_str(), "rb");
    bool there = existing != nullptr;
    if (existing)
        fclose(existing);
    FILE* f = OpenGameFile(battleLog_.c_str(), "ab");
    if (!f) {
        LogWarn("net", "can't write the battle log %s", battleLog_.c_str());
        battleLog_.clear();
        return;
    }
    std::string names = Pad(protocol_->names[0], 21, false) + " VS " +
                        Pad(protocol_->names[1], 21, true);
    std::string line = (there ? "\n" : "") +
                       Pad(TimeText(time(nullptr), "%Y/%m/%d %H:%M:%S"), 19, true, true) +
                       Pad(names, 46, true, true) + "\n";
    fwrite(line.data(), 1, line.size(), f);
    fclose(f);
}

void Session::LogGame()
{
    if (battleLog_.empty())
        return;
    FILE* f = OpenGameFile(battleLog_.c_str(), "ab");
    if (!f)
        return;
    long elapsed = (long)difftime(time(nullptr), fightTime_);
    if (elapsed < 0)
        elapsed = 0;
    char seconds[8];
    snprintf(seconds, sizeof(seconds), "%02ld", elapsed % 60);
    std::string duration = Pad(std::to_string(elapsed / 60), 3, false) + ":" + seconds;
    std::string characters = Pad(CharacterName(characters_[0]), 21, false) + " VS " +
                             Pad(CharacterName(characters_[1]), 21, true);
    std::string line =
        Pad(TimeText(fightTime_, "%Y/%m/%d %H:%M:%S"), 19, true) + Pad(characters, 46, true) +
        Pad("Rounds: " + std::to_string(rounds_[0]) + " " + std::to_string(rounds_[1]), 15, true) +
        Pad("Duration: " + duration, 20, true) +
        Pad("Score: " + Pad(std::to_string(wins_[0]), 3, false) + " " + std::to_string(wins_[1]),
            15, true) +
        "\n";
    fwrite(line.data(), 1, line.size(), f);
    fclose(f);
}

} // namespace netplay
} // namespace efz
