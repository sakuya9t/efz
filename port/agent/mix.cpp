// The planned okizeme (mix.h): runs/human-ayu/okiplan.py's OkiPlanner.plan and its
// module's counts (python/efz_env/memory.py), the same steps in the same order.
#include <math.h>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <random>
#include <set>
#include <string>
#include <vector>

#include "agent/mix.h"
#include "agent/observe.h"
#include "agent/policy.h"
#include "agent/routes.h"

namespace efz {
namespace agent {

namespace {

// The view's columns (efz_env_obs_name).
const int kIntro = 2, kRoundOver = 3, kDx = 4, kOppX = 45;
const int kOwnGauge = 9, kOwnRf = 10, kOwnBlue = 11;
const int kSelfAct = 18, kSelfFrame = 19, kSelfStun = 20, kSelfInv = 25, kSelfChar = 34, kSelfAir = 39;
const int kOppAct = 50, kOppFrame = 51, kOppStun = 52, kOppInv = 57, kOppChar = 66, kOppAir = 71;
const int kInputFeatures = 6;

// Control bytes, forward/back relative (efz_env.actions.encode).
const uint8_t kBack = 0x02;        // 4
const uint8_t kCrouchGuard = 0x06; // 1
const uint8_t kUpBack = 0x0a;      // 7
const uint8_t kDown = 0x04;        // 2
const uint8_t kDownA = 0x14;       // 2 + A

// efz_env.memory's windows.
const int kChoice = 16, kInv = 8, kWakeLife = 96, kPressLife = 64;
// okiplan.PRIOR: the community's players.
const double kPriorReversal = 0.10, kPriorMash = 0.19, kPriorJump = 0.04, kPriorCrouch = 0.8;

bool Down(int a) { return a >= 0x60 && a <= 0x63; }
bool Thrown(int a) { return a >= 0x64 && a < 0x79; }
bool Guard(int a) { return (a >= 0x96 && a <= 0x9c) || (a >= 0xa8 && a <= 0xaa); }
bool GuardGround(int a) { return (a >= 0x96 && a <= 0x9b) || a == 0xa8 || a == 0xa9; }
bool GuardCrouch(int a) { return (a >= 0x99 && a <= 0x9b) || a == 0xa9; }

int Rint(float x) { return (int)nearbyintf(x); }

// Forward and back as the screen's right and left.
uint8_t ToScreen(uint8_t bits, int facing)
{
    if (facing < 0)
        bits = (uint8_t)((bits & ~3) | (bits & 1) << 1 | (bits & 2) >> 1);
    return bits;
}

// efz_env.history.InputHistory.push, newest first.
void Push(std::vector<float>& h, uint8_t& prev, uint8_t c)
{
    if (h.empty())
        return;
    std::copy_backward(h.begin(), h.end() - kInputFeatures, h.end());
    float* f = h.data();
    f[0] = (float)((c & 0x01) != 0) - (float)((c & 0x02) != 0);
    f[1] = (float)((c & 0x08) != 0) - (float)((c & 0x04) != 0);
    unsigned pressed = (unsigned)(c & ~prev) >> 4;
    for (int b = 0; b < 4; b++)
        f[2 + b] = (float)((pressed >> b) & 1);
    prev = c;
}

} // namespace

// --- Counts: efz_env.memory.Memory.update, the counts okiplan.belief reads ---

void Counts::Side::Step(const float* view, bool opponent, const std::vector<uint8_t>& invincible)
{
    int a = Rint(view[opponent ? kOppAct : kSelfAct]);
    a = std::min(std::max(a, 0), (int)Mix::kActs - 1);
    int f = Rint(view[opponent ? kOppFrame : kSelfFrame]);
    bool s = view[opponent ? kOppStun : kSelfStun] > 0;
    bool inAir = view[opponent ? kOppAir : kSelfAir] > 0;
    bool g = Guard(a), th = Thrown(a);
    isNew = a != act;
    hit = s && !stun;
    struck = hit || (th && !thrown);
    contact = g && (!guard || isNew || f < frame);
    move = isNew && ((a >= 0xc8 && a < 0x190) || a == 0xa2);
    backdash = isNew && a == 0xa4;
    jump = inAir && !air && !s && !th && !g;
    rose = (act == 0x60 && a != 0x60) || (isNew && a == 0xa2 && Down(std::max(act, 0)));
    int c = Rint(view[opponent ? kOppChar : kSelfChar]);
    c = std::min(std::max(c, 0), (int)Mix::kCharacters - 1);
    inv = view[opponent ? kOppInv : kSelfInv] > 0 ||
          (!invincible.empty() && invincible[(size_t)c * Mix::kActs + a] != 0);
    wasGuard = guard;
    act = a;
    frame = f;
    stun = s;
    guard = g;
    air = inAir;
    thrown = th;
}

void Counts::Window::Tick()
{
    if (age >= 0)
        age++;
    if (moved > 0)
        moved--;
    if (age >= life)
        age = -1;
}

void Counts::Clear()
{
    for (float& x : c)
        x = 0;
    me_.Clear();
    it_.Clear();
    wake_ = Window();
    press_ = Window();
    wake_.life = kWakeLife;
    press_.life = kPressLife;
}

void Counts::End(double decay)
{
    for (float& x : c)
        x = (float)(x * (float)decay);
    me_.Clear();
    it_.Clear();
    wake_.Close();
    press_.Close();
}

void Counts::Choice(Window& w, int base)
{
    bool choosing = w.age >= 0 && !w.chose && w.age < kChoice;
    bool move = choosing && it_.move, back = choosing && it_.backdash;
    bool jump = choosing && it_.jump && !it_.move;
    if (move)
        c[base] += 1; // (base: its move; + 1 invincible, + 2 a jump, + 3 a backdash)
    if (back)
        c[base + 3] += 1;
    if (jump)
        c[base + 2] += 1;
    if (move)
        w.moved = kInv;
    if (w.age >= 0 && w.moved > 0 && it_.inv) {
        c[base + 1] += 1;
        w.moved = 0;
    }
    w.chose = w.chose || move || back || jump || (choosing && (it_.contact || it_.struck));
}

void Counts::Update(const float* view, const std::vector<uint8_t>& invincible)
{
    me_.Step(view, false, invincible);
    it_.Step(view, true, invincible);
    bool live = view[kIntro] == 0 && view[kRoundOver] == 0;
    if (!live) {
        wake_.Close();
        press_.Close();
    }
    if (it_.rose && live) { // its wake-up
        wake_.Open();
        c[kWakes] += 1;
    }
    Choice(wake_, kWakeMove);
    if (it_.wasGuard && !it_.guard && live) { // after its guard
        press_.Open();
        c[kGuarded] += 1;
    }
    Choice(press_, kGuardedMove);
    if (it_.contact && live && GuardGround(it_.act)) { // its guard
        c[kGuards] += 1;
        if (GuardCrouch(it_.act))
            c[kGuardsCrouch] += 1;
    }
    wake_.Tick();
    press_.Tick();
}

void Counts::Belief(double prior, double shares[kAnswers]) const
{
    double n = c[kWakes], inv = c[kWakeInvincible];
    double move = std::max(0.0, (double)c[kWakeMove] - inv);
    double away = (double)(float)(c[kWakeJump] + c[kWakeBack]);
    double rev = (prior * kPriorReversal + inv) / (prior + n);
    double mash = (prior * kPriorMash + move) / (prior + n);
    double jump = (prior * kPriorJump + away) / (prior + n);
    double guard = std::max(0.0, 1.0 - rev - mash - jump);
    double g = c[kGuards];
    double crouch = (prior * kPriorCrouch + (double)c[kGuardsCrouch]) / (prior + g);
    shares[0] = guard * crouch;
    shares[1] = guard * (1 - crouch);
    shares[2] = rev;
    shares[3] = jump;
    shares[4] = mash;
}

void Counts::PressBelief(double prior, double shares[kAnswers]) const
{
    // pressplan.PRIOR: what a guarding player does next, the community's.
    const double kReversal = 0.05, kMash = 0.22, kJump = 0.15, kCrouch = 0.8;
    double n = c[kGuarded], inv = c[kGuardedInvincible];
    double move = std::max(0.0, (double)c[kGuardedMove] - inv);
    double away = (double)(float)(c[kGuardedJump] + c[kGuardedBack]);
    double rev = (prior * kReversal + inv) / (prior + n);
    double mash = (prior * kMash + move) / (prior + n);
    double jump = (prior * kJump + away) / (prior + n);
    double guard = std::max(0.0, 1.0 - rev - mash - jump);
    double g = c[kGuards];
    double crouch = (prior * kCrouch + (double)c[kGuardsCrouch]) / (prior + g);
    shares[0] = guard * crouch;
    shares[1] = guard * (1 - crouch);
    shares[2] = rev;
    shares[3] = jump;
    shares[4] = mash;
}

// --- MixPlanner ---

MixPlanner::MixPlanner(const Policy* policy, World* world, uint64_t seed)
    : policy_(policy), world_(world), rng_(seed)
{
    in_.assign((size_t)kObsDim + (size_t)policy->history * kInputFeatures, 0.0f);
    probs_.assign(policy->Actions(), 0.0f);
    for (int a = 0; a < policy->Actions(); a++) {
        if (policy->table[a] == kCrouchGuard)
            guard_ = a;
    }
    memset(view, 0, sizeof(view));
    for (double& s : shares_)
        s = 0;
}

void MixPlanner::Cancel()
{
    phase_ = kIdle;
    outcome = kNone;
    plays_.clear();
    options_.clear();
    start_.valid = from_.valid = false;
}

void MixPlanner::Finish(Outcome why)
{
    outcome = why;
    phase_ = kDone;
    plays_.clear();
}

void MixPlanner::Begin(int side, const std::vector<int>& actions, const float* history,
                       uint8_t prev, bool deterministic, const double shares[kAnswers],
                       const float* seen)
{
    Cancel();
    const Mix& lib = policy_->mix;
    press_ = false;
    window_ = lib.window;
    skip_ = lib.skip;
    doubt_ = lib.doubt;
    temperature_ = lib.temperature;
    hitWorth_ = lib.hitWorth;
    hurtWorth_ = lib.hurtWorth;
    side_ = side;
    actions_ = actions;
    history_.assign(history, history + (size_t)policy_->history * kInputFeatures);
    prev_ = prev;
    deterministic_ = deterministic;
    for (int r = 0; r < kAnswers; r++)
        shares_[r] = shares[r];
    seenGiven_ = seen != nullptr;
    if (seenGiven_)
        seen_.assign(seen, seen + (size_t)(policy_->delay + 1) * kObsDim);
    lead = adv = waited = 0;
    waits_.clear();
    entries.clear();
    kinds.clear();
    worth.clear();
    first.clear();
    expected.clear();
    mix.clear();
    chosen = -1;
    option.clear();
    ms = 0;
    frames = 0;
    world_->Now(&start_);
    phase_ = kPrelude;
}

// okiplan.Entries.pick.
void MixPlanner::Candidates(const float* now)
{
    const Mix& lib = policy_->mix;
    double distance = fabs((double)now[kDx]) * 640;
    bool air = now[kSelfAir] > 0;
    int victim = Rint(now[kOppChar]);
    bool corner = fabs((double)now[kOppX]) > 0.8;
    std::vector<std::pair<double, int>> order;
    std::vector<int> from(lib.entries.size(), 0);
    for (size_t k = 0; k < lib.entries.size(); k++) {
        const Mix::Entry& e = lib.entries[k];
        int j0 = e.rise - lead; // the entry's step that is now
        if (j0 < 0 || j0 > e.moveAt - kMotion || j0 >= (int)e.size)
            continue;
        double off = fabs((double)lib.dist[e.begin + j0] - distance);
        if (off > lib.tolerance || (lib.air[e.begin + j0] != 0) != air)
            continue;
        from[k] = j0;
        order.push_back(std::make_pair(
            off + 6.0 * (e.victim != victim) + 10.0 * (e.corner != corner), (int)k));
    }
    std::stable_sort(order.begin(), order.end(),
                     [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
                         return a.first < b.first;
                     });
    std::set<std::string> seen;
    std::vector<int> classes;                // in the order of their best
    std::vector<std::vector<int>> by;        // a class's entries, the closest first
    for (const auto& o : order) {
        const Mix::Entry& e = lib.entries[o.second];
        std::string key((const char*)&lib.actions[e.begin + from[o.second]],
                        e.size - from[o.second]);
        if (!seen.insert(key).second)
            continue; // the same inputs from here on
        size_t c = std::find(classes.begin(), classes.end(), e.kind) - classes.begin();
        if (c == classes.size()) {
            classes.push_back(e.kind);
            by.push_back(std::vector<int>());
        }
        if ((int)by[c].size() < lib.perClass)
            by[c].push_back(o.second);
    }
    entries.clear();
    kinds.clear();
    options_.clear();
    for (int rank = 0; rank < lib.perClass; rank++) {
        for (size_t c = 0; c < classes.size(); c++) {
            if (rank < (int)by[c].size() && (int)entries.size() < lib.perPlan) {
                int k = by[c][rank];
                const Mix::Entry& e = lib.entries[k];
                entries.push_back(k);
                kinds.push_back(e.kind);
                options_.push_back(std::vector<int>(lib.actions.begin() + e.begin + from[k],
                                                    lib.actions.begin() + e.begin + e.size));
            }
        }
    }
    kinds.push_back(kWait);
    options_.push_back(std::vector<int>((size_t)(lead + lib.wait), guard_));
    kinds.push_back(kOwnPlay);
    options_.push_back(std::vector<int>());
}

// The frames until the plan is played, the agent's inputs chosen already; the frames to
// the rising (okiplan's lead); the options and the riser's reversal.
bool MixPlanner::Prelude()
{
    const Mix& lib = policy_->mix;
    const int delay = policy_->delay;
    if (!world_->Load(start_))
        return false;
    float now[kObsDim];
    if (!seenGiven_) {
        world_->View(side_, now);
        seen_.assign((size_t)(delay + 1) * kObsDim, 0.0f);
        for (int k = 0; k <= delay; k++)
            std::copy(now, now + kObsDim, seen_.begin() + (size_t)k * kObsDim);
    }
    for (size_t k = 0; k < actions_.size(); k++) {
        uint8_t input[2];
        input[side_] = ToScreen(policy_->table[actions_[k]], world_->Facing(side_));
        input[1 - side_] = ToScreen(kBack, world_->Facing(1 - side_));
        if (!world_->Step(input) || world_->Over())
            return false;
        frames++;
        if (!seenGiven_) {
            world_->View(side_, now);
            std::copy_backward(seen_.begin(), seen_.end() - kObsDim, seen_.end());
            std::copy(now, now + kObsDim, seen_.begin());
        }
    }
    world_->Save(&from_);
    world_->View(side_, view);
    float theirs[kObsDim];
    world_->View(1 - side_, theirs);
    hp0_[0] = world_->Hp(side_);
    hp0_[1] = world_->Hp(1 - side_);
    stun0_[0] = view[kSelfStun] > 0;
    stun0_[1] = view[kOppStun] > 0;
    thrown0_[0] = Thrown(Rint(view[kSelfAct]));
    thrown0_[1] = Thrown(Rint(view[kOppAct]));
    // The frames until the opponent is up, both holding a crouching guard.
    lead = -1;
    for (int t = 0; t < kLook; t++) {
        world_->View(side_, now);
        if (now[kRoundOver] != 0)
            break;
        if (!Down(Rint(now[kOppAct]))) {
            lead = t;
            break;
        }
        uint8_t input[2];
        input[side_] = ToScreen(kCrouchGuard, world_->Facing(side_));
        input[1 - side_] = ToScreen(kCrouchGuard, world_->Facing(1 - side_));
        if (!world_->Step(input))
            break;
        frames++;
    }
    if (lead < kMinLead) {
        Finish(kNothing);
        return true;
    }
    Candidates(view);
    // The riser's reversal: its first wake move its gauges allow.
    schedule_.clear();
    int victim = Rint(view[kOppChar]);
    for (const Mix::Reversal& m : lib.wake) {
        if (m.character != victim)
            continue;
        if (m.needs == 1 && (double)theirs[kOwnGauge] < 1.0 / 3)
            continue;
        if (m.needs == 2 && theirs[kOwnRf] < 0.5 && theirs[kOwnBlue] < 0.5)
            continue;
        schedule_.assign((size_t)std::max(0, lead - 2 - m.press), kCrouchGuard);
        schedule_.insert(schedule_.end(), m.bytes.begin(), m.bytes.end());
        break;
    }
    Plays();
    return true;
}

// Each option against each answer counted (those with a share of skip or more).
void MixPlanner::Plays()
{
    plays_.clear();
    bool any = false;
    for (int r = 0; r < kAnswers; r++)
        any = (counted_[r] = shares_[r] >= skip_) || any;
    for (int r = 0; r < kAnswers && !any; r++)
        counted_[r] = true;
    for (size_t o = 0; o < options_.size(); o++) {
        for (int r = 0; r < kAnswers; r++) {
            if (!counted_[r])
                continue;
            Play p;
            p.option = (int)o;
            p.answer = r;
            plays_.push_back(std::move(p));
        }
    }
    current_ = 0;
    phase_ = kPlays;
}

void MixPlanner::BeginPress(int side, const std::vector<int>& actions, const float* history,
                            uint8_t prev, bool deterministic, const double shares[kAnswers],
                            uint8_t hold)
{
    Begin(side, actions, history, prev, deterministic, shares, nullptr);
    const Press& lib = policy_->press;
    press_ = true;
    hold_ = hold;
    window_ = lib.window;
    skip_ = lib.skip;
    doubt_ = lib.doubt;
    temperature_ = lib.temperature;
    hitWorth_ = lib.hitWorth;
    hurtWorth_ = lib.hurtWorth;
}

// pressplan.Followups.pick.
void MixPlanner::PressCandidates(const float* now)
{
    const Press& lib = policy_->press;
    double distance = fabs((double)now[kDx]) * 640;
    int victim = Rint(now[kOppChar]);
    bool corner = fabs((double)now[kOppX]) > 0.8;
    std::vector<std::pair<double, int>> order;
    for (size_t k = 0; k < lib.entries.size(); k++) {
        const Press::Entry& e = lib.entries[k];
        double off = fabs((double)e.distance - distance);
        int late = abs(e.adv - adv);
        if (off > lib.tolerance || late > lib.slack)
            continue;
        order.push_back(std::make_pair(
            off + 4.0 * late + 6.0 * (e.victim != victim) + 10.0 * (e.corner != corner), (int)k));
    }
    std::stable_sort(order.begin(), order.end(),
                     [](const std::pair<double, int>& a, const std::pair<double, int>& b) {
                         return a.first < b.first;
                     });
    std::set<std::string> seen;
    std::vector<int> classes;
    std::vector<std::vector<int>> by;
    for (const auto& o : order) {
        const Press::Entry& e = lib.entries[o.second];
        std::string key((const char*)&lib.actions[e.begin], e.size);
        if (!seen.insert(key).second)
            continue;
        size_t c = std::find(classes.begin(), classes.end(), e.kind) - classes.begin();
        if (c == classes.size()) {
            classes.push_back(e.kind);
            by.push_back(std::vector<int>());
        }
        if ((int)by[c].size() < lib.perClass)
            by[c].push_back(o.second);
    }
    entries.clear();
    kinds.clear();
    options_.clear();
    for (int rank = 0; rank < lib.perClass; rank++) {
        for (size_t c = 0; c < classes.size(); c++) {
            if (rank < (int)by[c].size() && (int)entries.size() < lib.perPlan) {
                int k = by[c][rank];
                const Press::Entry& e = lib.entries[k];
                entries.push_back(k);
                kinds.push_back(e.kind);
                options_.push_back(std::vector<int>(lib.actions.begin() + e.begin,
                                                    lib.actions.begin() + e.begin + e.size));
            }
        }
    }
    kinds.push_back(kWait);
    options_.push_back(std::vector<int>((size_t)(lead + lib.wait), guard_));
    kinds.push_back(kOwnPlay);
    options_.push_back(std::vector<int>());
}

// pressplan.live_plan: the frames until the agent sees the guard, its inputs chosen
// already, the opponent holding its guard; a crouching guard until the agent is free; the
// frames of guard the opponent has left (pressplan's lead) and the options.
bool MixPlanner::PressPrelude()
{
    const Press& lib = policy_->press;
    const int delay = policy_->delay;
    if (!world_->Load(start_))
        return false;
    float now[kObsDim];
    world_->View(side_, now);
    seen_.assign((size_t)(delay + 1) * kObsDim, 0.0f);
    for (int k = 0; k <= delay; k++)
        std::copy(now, now + kObsDim, seen_.begin() + (size_t)k * kObsDim);
    int freeFor = 0;
    // A frame of the agent's `action`; false: the round over, or a hit either way.
    auto step = [&](int action) {
        uint8_t input[2];
        input[side_] = ToScreen(policy_->table[action], world_->Facing(side_));
        input[1 - side_] = ToScreen(hold_, world_->Facing(1 - side_));
        if (!world_->Step(input))
            return false;
        frames++;
        world_->View(side_, now);
        if (world_->Over() || now[kRoundOver] != 0 || now[kSelfStun] > 0 || now[kOppStun] > 0)
            return false;
        Push(history_, prev_, policy_->table[action]);
        std::copy_backward(seen_.begin(), seen_.end() - kObsDim, seen_.end());
        std::copy(now, now + kObsDim, seen_.begin());
        freeFor = Guard(Rint(now[kOppAct])) ? 0 : freeFor + 1;
        return true;
    };
    // (history_ and prev_: as they are before `actions`, each input pushed as it is played)
    for (size_t k = 0; k < actions_.size(); k++) {
        if (!step(actions_[k])) {
            Finish(kNothing);
            return true;
        }
    }
    memcpy(view, now, sizeof(view));
    waits_.clear();
    auto busy = [&]() {
        int a = Rint(now[kSelfAct]);
        bool free = (a >= 0 && a <= 9) || a == 0xe || a == 0xf || a == 0x10; // tactics.FREE
        return !free || now[kSelfAir] > 0;
    };
    while (busy()) {
        if ((int)waits_.size() >= lib.maxWait || !step(guard_)) {
            Finish(kNothing);
            return true;
        }
        waits_.push_back(guard_);
    }
    waited = (int)waits_.size();
    if (now[kOppAir] > 0 || fabs((double)now[kDx]) * 640 > lib.near || freeFor > kFreeLong ||
        Down(Rint(now[kOppAct]))) {
        Finish(kNothing);
        return true;
    }
    world_->Save(&from_);
    float mine[kObsDim], theirs[kObsDim];
    memcpy(mine, now, sizeof(mine));
    world_->View(1 - side_, theirs);
    hp0_[0] = world_->Hp(side_);
    hp0_[1] = world_->Hp(1 - side_);
    stun0_[0] = mine[kSelfStun] > 0;
    stun0_[1] = mine[kOppStun] > 0;
    thrown0_[0] = Thrown(Rint(mine[kSelfAct]));
    thrown0_[1] = Thrown(Rint(mine[kOppAct]));
    // The frames until the opponent's guard is over, both holding a crouching guard.
    lead = -1;
    for (int t = 0; t < kPressLook; t++) {
        world_->View(side_, now);
        if (!Guard(Rint(now[kOppAct]))) {
            lead = t;
            break;
        }
        uint8_t input[2];
        input[side_] = ToScreen(kCrouchGuard, world_->Facing(side_));
        input[1 - side_] = ToScreen(kCrouchGuard, world_->Facing(1 - side_));
        if (!world_->Step(input) || world_->Over())
            break;
        frames++;
    }
    if (lead < 0) {
        Finish(kNothing);
        return true;
    }
    adv = lead > 0 ? lead : 1 - std::max(1, freeFor);
    PressCandidates(mine);
    // The guarding player's reversal: its fastest invincible move its gauges allow, the
    // motion input so that its button lands on the first frame its guard is over.
    schedule_.clear();
    int victim = Rint(mine[kOppChar]);
    for (const Mix::Reversal& m : lib.reversals) {
        if (m.character != victim)
            continue;
        if (m.needs == 1 && (double)theirs[kOwnGauge] < 1.0 / 3)
            continue;
        if (m.needs == 2 && theirs[kOwnRf] < 0.5 && theirs[kOwnBlue] < 0.5)
            continue;
        schedule_.assign((size_t)std::max(0, lead - m.press), kCrouchGuard);
        schedule_.insert(schedule_.end(), m.bytes.begin(), m.bytes.end());
        break;
    }
    Plays();
    return true;
}

// An option against an answer, frame by frame (okiplan's tryout); true once it is over.
bool MixPlanner::Run(Play& p, Clock::time_point deadline)
{
    const int delay = policy_->delay;
    const std::vector<int>& acts = options_[p.option];
    const bool own = kinds[p.option] == kOwnPlay;
    if (!p.started) {
        p.started = true;
        for (int k = 0; k < 2; k++) {
            p.stun[k] = stun0_[k];
            p.thrown[k] = thrown0_[k];
            p.hp[k] = hp0_[k];
        }
        if (own) {
            p.delayed = seen_;
            p.history = history_;
            p.prev = prev_;
        }
    }
    const int total = lead + window_;
    float now[kObsDim];
    while (p.t < total) {
        if (Clock::now() >= deadline)
            return false;
        uint8_t bits = kCrouchGuard;
        if (p.t < (int)acts.size()) {
            bits = policy_->table[acts[p.t]];
        } else if (own) { // as late as the player sees the game
            std::copy(p.delayed.begin() + (size_t)delay * kObsDim,
                      p.delayed.begin() + (size_t)(delay + 1) * kObsDim, in_.begin());
            std::copy(p.history.begin(), p.history.end(), in_.begin() + kObsDim);
            policy_->LogProbs(in_.data(), probs_.data());
            int n = policy_->Actions(), action = n - 1;
            if (deterministic_) {
                action = (int)(std::max_element(probs_.begin(), probs_.begin() + n) - probs_.begin());
            } else {
                double u = std::uniform_real_distribution<double>(0.0, 1.0)(rng_), sum = 0;
                for (int a = 0; a < n; a++) {
                    sum += exp((double)probs_[a]);
                    if (u < sum) {
                        action = a;
                        break;
                    }
                }
            }
            bits = policy_->table[action];
        }
        uint8_t theirs = kCrouchGuard;
        if (p.answer == 1)
            theirs = kBack;
        else if (p.answer == 2 && p.t < (int)schedule_.size())
            theirs = schedule_[p.t];
        else if (p.answer == 3 && p.t >= lead - 2)
            theirs = kUpBack;
        else if (p.answer == 4 && p.t >= lead - 1)
            theirs = p.t % 2 == 0 ? kDownA : kDown;
        int facing[2] = {world_->Facing(0), world_->Facing(1)};
        uint8_t input[2];
        input[side_] = ToScreen(bits, facing[side_]);
        input[1 - side_] = ToScreen(theirs, facing[1 - side_]);
        if (!world_->Step(input))
            return true;
        frames++;
        world_->View(side_, now);
        if (own) {
            Push(p.history, p.prev, ToScreen(world_->Read(side_), facing[side_]));
            std::copy_backward(p.delayed.begin(), p.delayed.end() - kObsDim, p.delayed.end());
            std::copy(now, now + kObsDim, p.delayed.begin());
        }
        bool stun[2] = {now[kSelfStun] > 0, now[kOppStun] > 0};
        bool thrown[2] = {Thrown(Rint(now[kSelfAct])), Thrown(Rint(now[kOppAct]))};
        bool began[2];
        for (int k = 0; k < 2; k++) {
            began[k] = (stun[k] && !p.stun[k]) || (thrown[k] && !p.thrown[k]);
            p.stun[k] = stun[k];
            p.thrown[k] = thrown[k];
        }
        if (p.t >= lead - 2 && p.first == 0) // (before: the knockdown's own reactions)
            p.first = began[1] ? 1 : began[0] ? -1 : 0;
        p.hp[0] = world_->Hp(side_);
        p.hp[1] = world_->Hp(1 - side_);
        p.t++;
        if (world_->Over())
            return true;
    }
    return true;
}

std::vector<double> MixPlanner::Maximin(const std::vector<double>& worth, int options, int rounds)
{
    const int O = options, R = O > 0 ? (int)worth.size() / O : 0;
    std::vector<double> regretP(O, 0.0), regretQ(R, 0.0), total(O, 0.0), p(O), q(R), rows(O), cols(R);
    for (int it = 0; it < rounds; it++) {
        double sp = 0, sq = 0;
        for (int o = 0; o < O; o++)
            sp += p[o] = std::max(regretP[o], 0.0);
        for (int o = 0; o < O; o++)
            p[o] = sp > 0 ? p[o] / sp : 1.0 / O;
        for (int r = 0; r < R; r++)
            sq += q[r] = std::max(regretQ[r], 0.0);
        for (int r = 0; r < R; r++)
            q[r] = sq > 0 ? q[r] / sq : 1.0 / R;
        for (int o = 0; o < O; o++)
            total[o] += p[o];
        double pr = 0, qc = 0;
        for (int o = 0; o < O; o++) {
            rows[o] = 0;
            for (int r = 0; r < R; r++)
                rows[o] += worth[(size_t)o * R + r] * q[r];
            pr += p[o] * rows[o];
        }
        for (int r = 0; r < R; r++) {
            cols[r] = 0;
            for (int o = 0; o < O; o++)
                cols[r] += p[o] * worth[(size_t)o * R + r];
            qc += q[r] * cols[r];
        }
        for (int o = 0; o < O; o++)
            regretP[o] += rows[o] - pr;
        for (int r = 0; r < R; r++)
            regretQ[r] += qc - cols[r]; // (the column wants the row's gain small)
    }
    double sum = 0;
    for (double x : total)
        sum += x;
    for (double& x : total)
        x /= sum;
    return total;
}

void MixPlanner::Choose()
{
    const int O = (int)options_.size();
    worth.assign((size_t)O * kAnswers, 0.0);
    first.assign((size_t)O * kAnswers, 0);
    expected.assign(O, 0.0);
    for (const Play& p : plays_) {
        double dealt = std::max(hp0_[1] - p.hp[1], 0), taken = std::max(hp0_[0] - p.hp[0], 0);
        double w = (p.first > 0 ? std::max(dealt, hitWorth_) : dealt) -
                   (p.first < 0 ? std::max(taken, hurtWorth_) : taken);
        worth[(size_t)p.option * kAnswers + p.answer] = w;
        first[(size_t)p.option * kAnswers + p.answer] = p.first;
    }
    double counted = 0;
    int R = 0;
    for (int r = 0; r < kAnswers; r++) {
        if (counted_[r]) {
            counted += shares_[r];
            R++;
        }
    }
    for (int o = 0; o < O; o++) {
        for (int r = 0; r < kAnswers; r++) {
            if (counted_[r])
                expected[o] += worth[(size_t)o * kAnswers + r] * (shares_[r] / counted);
        }
    }
    if (doubt_ > 0) { // the shares may be wrong by `doubt`, the worst way for the mix
        std::vector<double> game;
        game.reserve((size_t)O * R);
        for (int o = 0; o < O; o++) {
            for (int r = 0; r < kAnswers; r++) {
                if (counted_[r])
                    game.push_back((1 - doubt_) * expected[o] +
                                   doubt_ * worth[(size_t)o * kAnswers + r]);
            }
        }
        mix = Maximin(game, O);
    } else {
        double top = *std::max_element(expected.begin(), expected.end()), sum = 0;
        mix.assign(O, 0.0);
        for (int o = 0; o < O; o++)
            sum += mix[o] = exp((expected[o] - top) / temperature_);
        for (double& x : mix)
            x /= sum;
    }
    double sum = 0;
    for (double x : mix)
        sum += x;
    double u = std::uniform_real_distribution<double>(0.0, 1.0)(rng_) * sum, run = 0;
    chosen = O - 1;
    for (int o = 0; o < O; o++) {
        run += mix[o];
        if (u < run) {
            chosen = o;
            break;
        }
    }
    option = waits_; // (the pressure's guard until it is free; the okizeme's: none)
    if (kinds[chosen] != kOwnPlay)
        option.insert(option.end(), options_[chosen].begin(), options_[chosen].end());
    Finish(kPlanned);
}

bool MixPlanner::Work(Clock::time_point deadline)
{
    if (!Busy())
        return phase_ == kDone;
    Clock::time_point t0 = Clock::now();
    world_->Enter();
    world_->Save(&real_);
    bool apart = false;
    if (phase_ == kPrelude && !(press_ ? PressPrelude() : Prelude()))
        apart = true;
    while (!apart && phase_ == kPlays && Clock::now() < deadline) {
        Play& p = plays_[current_];
        bool loaded = p.started && p.state.valid ? world_->Load(p.state) : world_->Load(from_);
        if (!loaded) {
            apart = true;
            break;
        }
        if (!Run(p, deadline)) {
            world_->Save(&p.state);
            break;
        }
        p.state = Snapshot();
        if (++current_ == plays_.size())
            Choose();
    }
    world_->Load(real_);
    world_->Leave();
    if (apart)
        Finish(kApart);
    ms += std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
    return phase_ == kDone;
}

} // namespace agent
} // namespace efz
