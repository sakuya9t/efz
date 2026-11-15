// The routes' planner (routes.h): runs/human-ayu/combo_support.py's _live_worker and
// redteam.py's Planner.plan, the same steps in the same order.
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
                    uint8_t prev, bool deterministic, const float* view)
{
    Cancel();
    side_ = side;
    starter_ = starter;
    actions_ = actions;
    history_.assign(history, history + (size_t)policy_->history * kInputFeatures);
    prev_ = prev;
    deterministic_ = deterministic;
    chosen = -1;
    offset = (int)actions.size();
    tried.clear();
    dealt.clear();
    best = own = 0;
    ms = 0;
    frames = 0;
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
        View(side_, &seen_[(size_t)(delay - 1 - k) * kObsDim]);
    }
    memcpy(expected, seen_.data(), sizeof(expected));
    world_->Save(&afterDelay_);
    hp0_ = world_->Hp(1 - side_);

    // Redteam's route_pool: of the routes with this starter (by damage), those landed on
    // this opponent first if the library was kept per victim; those long enough to be
    // played from `offset`; the first per_start.
    const Routes& routes = policy_->routes;
    std::vector<int> pool;
    auto it = routes.byStarter.find(starter_);
    if (it != routes.byStarter.end()) {
        std::vector<int> order = it->second;
        if (routes.byVictim) {
            int victim = (int)nearbyintf(seen_[kOppCharacter]);
            std::stable_partition(order.begin(), order.end(), [&](int r) {
                return routes.list[r].opponent == victim;
            });
        }
        for (int r : order) {
            if ((int)routes.list[r].size > offset && (int)pool.size() < routes.perStart)
                pool.push_back(r);
        }
    }
    int longest = 0;
    for (int r : pool)
        longest = std::max(longest, (int)routes.list[r].size - offset);
    longest_ = std::max(std::min(routes.limit, longest + kTail), kShortest);
    options_.clear();
    for (int r : pool) {
        Option o;
        o.route = r;
        options_.push_back(std::move(o));
    }
    Option self;
    self.route = -1;
    options_.push_back(std::move(self));
    current_ = 0;
    return true;
}

// Planner.plan's loop, for one option: the route's actions (none once they run out) or
// its own play's, the defender holding back; the most it dealt, until its combo is over.
bool Planner::Play(Option& o, Clock::time_point deadline)
{
    const Routes& routes = policy_->routes;
    const int delay = offset;
    if (!o.started) {
        o.started = true;
        if (o.route < 0) {
            o.delayed = seen_;
            o.history = history_;
            o.prev = prev_;
        }
    }
    float now[kObsDim];
    while (o.t < longest_) {
        if (Clock::now() >= deadline)
            return false;
        uint8_t bits = 0;
        if (o.route >= 0) {
            const Routes::Route& r = routes.list[o.route];
            int at = offset + o.t;
            if (at < (int)r.size)
                bits = policy_->table[routes.actions[r.begin + at]];
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
        input[side_] = ToScreen(bits, facing[side_]);
        input[1 - side_] = ToScreen(kBack, facing[1 - side_]);
        if (!world_->Step(input))
            return true;
        frames++;
        if (o.route < 0) // its history: the controls the game read (info['input'])
            Push(o.history, o.prev, ToScreen(world_->Read(side_), facing[side_]));
        o.dealt = std::max(o.dealt, (float)(hp0_ - world_->Hp(1 - side_)));
        o.t++;
        // Its combo over, or the round (a KO: what it dealt can't grow).
        if (world_->ComboHits(side_) == 0 || world_->Over())
            return true;
    }
    return true;
}

void Planner::Choose()
{
    tried.clear();
    dealt.clear();
    size_t n = options_.size();
    size_t top = 0;
    for (size_t j = 0; j < n; j++) {
        tried.push_back(options_[j].route);
        dealt.push_back(options_[j].dealt);
        if (options_[j].dealt > options_[top].dealt)
            top = j;
    }
    best = options_[top].dealt;
    own = options_[n - 1].dealt;
    chosen = top + 1 < n && options_[top].dealt > own ? options_[top].route : -1;
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
            Choose();
        else
            phase_ = kOptions;
    }
    while (!apart && phase_ == kOptions && Clock::now() < deadline) {
        Option& o = options_[current_];
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
