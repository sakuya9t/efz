// The routes' planner (routes.h): runs/human-ayu/combo_support.py's _live_worker and
// redteam.py's Planner.plan (round 15b's, with replan), the same steps in the same order.
#include <math.h>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <random>
#include <vector>

#include "agent/observe.h"
#include "agent/policy.h"
#include "agent/routes.h"

namespace efz {
namespace agent {

namespace {

const uint8_t kBack = 0x02;     // efz_env.actions.BACK: back, relative to facing
const uint8_t kBackPress = 0x12; // redteam.BACK_PRESS: with A, the victim's air recovery
const int kEndingTail = 12;      // redteam.ENDING_TAIL
const int kOppAction = 50;       // the view's opp_action

// redteam.LYING and AIR_RECOVERY (src/efz.h: wake-up, the knockdowns, lying; the air
// recoveries forward and back).
bool Lying(int action) { return action >= 0x60 && action <= 0x63; }
bool Recovering(int action) { return action == 0x9d || action == 0x9e; }
const int kOppCharacter = 66;   // opp_character
const int kInputFeatures = 6;
const int kShortest = 240;      // its own play's combo is played this long at least
const int kTail = 60;           // and the routes' longest this much more

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

Planner::Planner(const Policy* policy, World* world, uint64_t seed)
    : policy_(policy), world_(world), rng_(seed)
{
    in_.assign((size_t)kObsDim + (size_t)policy->history * kInputFeatures, 0.0f);
    probs_.assign(policy->Actions(), 0.0f);
}

void Planner::View(int side, float* out)
{
    world_->View(side, out);
}

void Planner::Cancel()
{
    phase_ = kIdle;
    outcome = kNone;
    options_.clear();
    start_.valid = afterDelay_.valid = false;
}

void Planner::Finish(Outcome why)
{
    outcome = why;
    phase_ = kDone;
    options_.clear();
}

void Planner::Begin(int side, int starter, const std::vector<int>& actions, const float* history,
                    uint8_t prev, bool deterministic, const float* view, int late,
                    const std::vector<int>& extra, bool again)
{
    Cancel();
    again_ = again;
    if (!again)
        comboSet_ = false;
    target = -1;
    side_ = side;
    starter_ = starter;
    actions_ = actions;
    extra_ = extra;
    history_.assign(history, history + (size_t)policy_->history * kInputFeatures);
    prev_ = prev;
    deterministic_ = deterministic;
    chosen = -1;
    route.clear();
    offset = (int)actions.size() + std::max(0, late);
    tried.clear();
    dealt.clear();
    best = own = 0;
    ms = 0;
    frames = 0;
    cost = 0;
    played = 0;
    partial = false;
    memset(expected, 0, sizeof(expected));
    // Redteam's plans_against: only against the routes' victims, if it has any.
    const Routes& routes = policy_->routes;
    if (!routes.victims.empty()) {
        int c = (int)nearbyintf(view[kOppCharacter]);
        if (std::find(routes.victims.begin(), routes.victims.end(), c) == routes.victims.end()) {
            Finish(kOwn);
            return;
        }
    }
    world_->Now(&start_);
    phase_ = kPrelude;
}

// _live_worker: the frames until the player sees its hit, its inputs chosen already,
// the opponent holding back; then the routes that can be played from there.
bool Planner::Prelude()
{
    const int delay = (int)actions_.size();
    seen_.assign((size_t)(delay + 1) * kObsDim, 0.0f);
    if (!world_->Load(start_))
        return false;
    View(side_, &seen_[(size_t)delay * kObsDim]);
    for (int k = 0; k < delay; k++) {
        uint8_t input[2];
        input[side_] = ToScreen(policy_->table[actions_[k]], world_->Facing(side_));
        input[1 - side_] = ToScreen(kBack, world_->Facing(1 - side_));
        // (a KO in them: the agent won't see its hit in a fight going on; and a copy is
        // never played on toward the fight's end)
        if (!world_->Step(input) || world_->Over())
            return false;
        frames++;
        cost++;
        View(side_, &seen_[(size_t)(delay - 1 - k) * kObsDim]);
    }
    memcpy(expected, seen_.data(), sizeof(expected));
    world_->Save(&afterDelay_);
    hp0_ = world_->Hp(1 - side_);

    // Redteam's route_pool: of the pool's entries with this starter (by damage), those
    // landed on this opponent first if the library was kept per victim; those long enough
    // to be played from `offset`; the first per_start. Then the extra option.
    const Routes& routes = policy_->routes;
    auto size = [&](int e) {
        return (int)routes.list[routes.pool[e].route].size - routes.pool[e].at;
    };
    std::vector<int> pool;
    auto it = routes.poolByStarter.find(starter_);
    if (it != routes.poolByStarter.end()) {
        std::vector<int> order = it->second;
        if (routes.byVictim) {
            int victim = (int)nearbyintf(seen_[kOppCharacter]);
            std::stable_partition(order.begin(), order.end(), [&](int e) {
                return routes.list[routes.pool[e].route].opponent == victim;
            });
        }
        for (int e : order) {
            if (size(e) > offset && (int)pool.size() < routes.perStart)
                pool.push_back(e);
        }
    }
    int longest = 0;
    for (int e : pool)
        longest = std::max(longest, size(e) - offset);
    longest = std::max(longest, (int)extra_.size());
    longest_ = std::max(std::min(routes.limit, longest + kTail), kShortest);
    options_.clear();
    for (int e : pool) {
        Option o;
        o.entry = e;
        options_.push_back(std::move(o));
    }
    if (!extra_.empty()) {
        Option o;
        o.entry = kExtra;
        options_.push_back(std::move(o));
    }
    Option self;
    self.entry = kOwnPlay;
    options_.push_back(std::move(self));
    // Played first: what the agent goes on with if no plan comes (Settle): the rest of
    // its route, else its own play. Then the others as they stand. (SetOwnLast: the rest
    // of its route, the routes, its own play.)
    const size_t n = options_.size();
    size_t first = extra_.empty() ? n - 1 : n - 2;
    if (ownLast_ && extra_.empty() && n > 1)
        first = 0;
    work_.assign(1, first);
    for (size_t j = 0; j < n; j++) {
        if (j != first && !(ownLast_ && j == n - 1))
            work_.push_back(j);
    }
    if (ownLast_ && first != n - 1)
        work_.push_back(n - 1);
    current_ = 0;
    return true;
}

// Planner.plan's loop, for one option: the route's actions (none once they run out) or
// its own play's, the defender holding back; the most it dealt, until its combo is over.
bool Planner::Play(Option& o, Clock::time_point deadline)
{
    const Routes& routes = policy_->routes;
    const int delay = (int)actions_.size();
    if (!o.started) {
        o.started = true;
        if (o.entry == kOwnPlay) {
            o.delayed = seen_;
            o.history = history_;
            o.prev = prev_;
        }
    }
    float now[kObsDim];
    while (o.t < longest_) {
        if (Clock::now() >= deadline || (budget_ > 0 && cost >= budget_))
            return false;
        uint8_t bits = 0;
        if (o.entry >= 0) {
            const Routes::Entry& e = routes.pool[o.entry];
            const Routes::Route& r = routes.list[e.route];
            int at = e.at + offset + o.t;
            if (at < (int)r.size)
                bits = policy_->table[routes.actions[r.begin + at]];
        } else if (o.entry == kExtra) {
            if (o.t < (int)extra_.size())
                bits = policy_->table[extra_[o.t]];
        } else {
            // As late as the player sees the game: the view `delay` frames old (the first
            // frame's is the hit's, which `delayed` has already).
            if (o.t > 0) {
                View(side_, now);
                std::copy_backward(o.delayed.begin(), o.delayed.end() - kObsDim, o.delayed.end());
                std::copy(now, now + kObsDim, o.delayed.begin());
            }
            std::copy(o.delayed.begin() + (size_t)delay * kObsDim,
                      o.delayed.begin() + (size_t)(delay + 1) * kObsDim, in_.begin());
            std::copy(o.history.begin(), o.history.end(), in_.begin() + kObsDim);
            policy_->LogProbs(in_.data(), probs_.data());
            int n = policy_->Actions(), action = 0;
            if (deterministic_) {
                action = (int)(std::max_element(probs_.begin(), probs_.begin() + n) - probs_.begin());
            } else {
                double u = std::uniform_real_distribution<double>(0.0, 1.0)(rng_), sum = 0;
                action = n - 1;
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
        int facing[2] = {world_->Facing(0), world_->Facing(1)};
        uint8_t input[2];
        const int ending = routes.ending;
        input[side_] = ToScreen(bits, facing[side_]);
        input[1 - side_] = ToScreen(ending > 0 && o.t % 2 ? kBackPress : kBack, facing[1 - side_]);
        if (!world_->Step(input))
            return true;
        frames++;
        cost += o.entry == kOwnPlay ? ownCost_ : 1;
        if (o.entry == kOwnPlay) // its history: the controls the game read (info['input'])
            Push(o.history, o.prev, ToScreen(world_->Read(side_), facing[side_]));
        if (o.over < 0) {
            o.dealt = std::max(o.dealt, (float)(hp0_ - world_->Hp(1 - side_)));
            // Its combo over, or the round (a KO: what it dealt can't grow).
            if (world_->ComboHits(side_) == 0 || world_->Over())
                o.over = o.t;
        }
        if (ending > 0) { // how it leaves the victim, to a little after its combo's end
            View(side_, now);
            int action = (int)lround(now[kOppAction]);
            o.recovered = o.recovered || Recovering(action);
            o.down = o.down || Lying(action);
        }
        o.t++;
        if (o.over >= 0 && (ending <= 0 || o.t - 1 - o.over >= kEndingTail))
            return true;
    }
    return true;
}

// The choice among the first `done` options of work_: all of them, the most any is worth
// if that is more than its own play's; some of them (Settle), the one it goes on with
// otherwise (the first played) unless another played is worth more.
void Planner::Choose(size_t done)
{
    tried.clear();
    dealt.clear();
    size_t n = options_.size();
    std::vector<char> have(n, 0);
    for (size_t k = 0; k < done && k < n; k++)
        have[work_[k]] = 1;
    partial = done < n;
    played = (int)std::min(done, n);
    size_t top = partial ? work_[0] : 0;
    const float ending = (float)policy_->routes.ending;
    ends.clear();
    std::vector<float> worth(n);
    best = 0;
    for (size_t j = 0; j < n; j++) {
        const Option& o = options_[j];
        tried.push_back(o.entry);
        dealt.push_back(o.dealt);
        ends.push_back(o.recovered ? 2 : o.down ? 1 : 0);
        worth[j] = o.dealt + (o.down && !o.recovered ? ending : 0.0f);
    }
    for (size_t j = 0; j < n; j++) {
        if (!have[j])
            continue;
        best = std::max(best, options_[j].dealt);
        if (worth[j] > worth[top])
            top = j;
    }
    own = options_[n - 1].dealt;
    if (share_ < 1.0f) {
        // A share of the most: the first plan's target, or what is left of it.
        float most = 0;
        for (size_t j = 0; j < n; j++) {
            if (have[j])
                most = std::max(most, worth[j]);
        }
        if (again_ && comboSet_) {
            target = std::max(0.0f, comboTarget_ - (float)(comboHp0_ - hp0_));
        } else {
            target = share_ * most;
            comboTarget_ = target;
            comboHp0_ = hp0_;
            comboSet_ = true;
        }
        // The nearest, in the order played (ties: what it would go on with).
        size_t pick = work_[0];
        for (size_t k = 0; k < done && k < n; k++) {
            size_t j = work_[k];
            if (fabsf(worth[j] - target) < fabsf(worth[pick] - target))
                pick = j;
        }
        top = pick;
        chosen = top + 1 < n ? (int)top : -1;
    } else if (partial) {
        chosen = top + 1 < n ? (int)top : -1;
    } else {
        chosen = top + 1 < n && worth[top] > worth[n - 1] ? (int)top : -1;
    }
    // (its own play last and not played: a route that dealt nothing isn't taken for it)
    if (ownLast_ && partial && !have[n - 1] && chosen >= 0 && worth[top] <= 0)
        chosen = -1;
    route.clear();
    if (chosen >= 0 && options_[top].entry == kExtra) {
        route = extra_;
    } else if (chosen >= 0) {
        const Routes& routes = policy_->routes;
        const Routes::Entry& e = routes.pool[options_[top].entry];
        const Routes::Route& r = routes.list[e.route];
        route.assign(routes.actions.begin() + r.begin + e.at + offset,
                     routes.actions.begin() + r.begin + r.size);
    }
    Finish(kPlanned);
}

bool Planner::Work(Clock::time_point deadline)
{
    if (!Busy())
        return phase_ == kDone;
    Clock::time_point t0 = Clock::now();
    world_->Enter();
    world_->Save(&real_);
    bool apart = false;
    if (phase_ == kPrelude) {
        if (!Prelude())
            apart = true;
        else if (options_.size() == 1) // no route to try: its own play, unplayed
            Choose(1);
        else
            phase_ = kOptions;
    }
    while (!apart && phase_ == kOptions && Clock::now() < deadline &&
           !(budget_ > 0 && cost >= budget_)) {
        Option& o = options_[work_[current_]];
        bool loaded = o.started && o.state.valid ? world_->Load(o.state) : world_->Load(afterDelay_);
        if (!loaded) {
            apart = true;
            break;
        }
        if (!Play(o, deadline)) {
            world_->Save(&o.state);
            break;
        }
        o.state = Snapshot();
        if (++current_ == options_.size())
            Choose(current_);
    }
    world_->Load(real_);
    world_->Leave();
    if (apart)
        Finish(kApart);
    ms += std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
    return phase_ == kDone;
}

bool Planner::Settle()
{
    if (phase_ != kOptions || current_ == 0)
        return false;
    Choose(current_);
    return true;
}

} // namespace agent
} // namespace efz
