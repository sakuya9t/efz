// An agent's okizeme, planned as runs/human-ayu/okiplan.py plans it (the module okiplan:1
// of an agent file): at its opponent's knockdown, people's okizeme from a library
// (runs/human-ayu/oki_library.py's: what a character's players did from a knockdown to
// their first contact on the riser, timed by the rising) are tried on copies of the fight,
// each against the ways a riser answers (a crouching guard, a standing one, its invincible
// move as it rises, a jump away, a button), and one is drawn by what the match has shown
// of this opponent: the planner's steps, in its order, so that a plan here is the plan
// there (python/tests/test_agents.py).
//
// - The options: the library's entries whose player stood where the agent stands, as many
//   frames before the rising as are left (an entry is played with its recorded rising on
//   the frame this opponent rises), the closest first, at most perClass of a kind and
//   perPlan in all; a wait (a crouching guard through the rising and `wait` frames more);
//   and its own play (the network).
// - The answers: on each copy the riser holds a crouching guard, or a standing one, or
//   plays its reversal (the file's wake moves for its character: the first its gauges
//   allow, the motion and then the button held from 2 frames before it is up), or holds
//   up-back from 2 frames before, or presses 2A every other frame from 1 before. After an
//   option's inputs the agent holds a crouching guard (okiplan.py's after='guard': what a
//   frame's spare time affords).
// - What an option is worth against an answer: the HP it took less the HP it lost by
//   `window` frames after the rising, a first hit of the agent's counted as hitWorth at
//   least (the combo its routes make of it) and one taken as hurtWorth at least.
// - The choice: each answer's share, from the counts of what this opponent did on its
//   wake-ups and how it guards (Counts: efz_env.memory's, of the view the agent has) over
//   a prior of the community's players; with `doubt` d the option is drawn from the mix
//   that does best if the shares are (1 - d) right and the rest is the worst answer for
//   it (a matrix game, by regret matching), else with weight exp(expected / temperature).
//
// The copies are the World's (routes.h), worked on in pieces up to a deadline.
#ifndef EFZ_AGENT_MIX_H
#define EFZ_AGENT_MIX_H

#include <stdint.h>
#include <chrono>
#include <random>
#include <string>
#include <vector>

#include "agent/observe.h"
#include "agent/routes.h"

namespace efz {
namespace agent {

class Policy;

enum { kAnswers = 5 }; // okiplan.ANSWERS: crouch, stand, reversal, jump, mash

// The library and the planner's settings (the module okiplan:1). Keys oki_entries (their
// count), oki_per_plan, oki_per_class, oki_window, oki_wait, oki_tolerance,
// oki_temperature, oki_doubt, oki_hit_worth, oki_hurt_worth, oki_prior, oki_decay,
// oki_skip, oki_think, oki_sight, oki_bait (okiplan:2; without them 0), oki_out (okiplan:3),
// oki_kinds (the kinds' names, '|' between them), oki_source; tensors oki.offset (int32,
// count + 1: where each entry's steps begin), oki.actions (uint8: the agent's actions),
// oki.dist (int32: the player's distance from the riser in pixels at each step), oki.air
// (uint8: in the air or not), oki.rise, oki.move_at, oki.kind, oki.victim (the character
// it was done to, -1 unknown), oki.corner (int32, an entry each); the risers' reversals
// oki.wake.character, oki.wake.needs (0 nothing, 1 a level of power, 2 half the RF gauge
// or blue), oki.wake.press (the step of its bytes the button is first on),
// oki.wake.offset (count + 1), oki.wake.bytes (uint8: control bytes, forward/back
// relative), in the order they are preferred; and the moves that are invincible from their
// start, oki.invincible.character and oki.invincible.action (int32, a pair each).
struct Mix {
    struct Entry {
        uint32_t begin = 0, size = 0;
        int rise = 0, moveAt = 0, kind = 0, victim = -1;
        bool corner = false;
    };
    struct Reversal {
        int character = 0, needs = 0, press = 0;
        std::vector<uint8_t> bytes;
    };
    std::vector<Entry> entries;
    std::vector<uint8_t> actions;
    std::vector<int32_t> dist;
    std::vector<uint8_t> air;
    std::vector<std::string> kinds;
    std::vector<Reversal> wake;
    std::vector<uint8_t> invincible; // [character * kActs + action]
    int perPlan = 6, perClass = 2, window = 45, wait = 40, tolerance = 24;
    double temperature = 200, doubt = 0, hitWorth = 1300, hurtWorth = 1200;
    double prior = 6, decay = 0.7;
    double skip = 0; // an answer with a share under this isn't played or counted
    int think = 0;   // frames of crouching guard after the agent sees the knockdown, before
                     // the plan's first input: the planner's working time beyond the delay
    int sight = 0;   // okiplan's sight: the riser's 'crouch' answer guards by what it saw of
                     // the agent this many frames ago, standing against one in the air (0:
                     // it crouches whatever comes); its 'stand' answer is then kSightStand
                     // of its guards
    bool out = false; // okiplan's out (okiplan:3): a riser with its back to a wall, the agent
                      // on the open side, jumps forward over the agent in its 'jump' answer
                      // (without: up-back, which in a corner goes nowhere)
    double bait = 0; // okiplan's bait: the HP a riser's reversal that came out is worth to
                     // the agent on the plays where neither hit first (the punish, which
                     // the copies do not play)
    std::string source;
    enum { kActs = 0x400, kCharacters = 64 };
    bool Empty() const { return entries.empty(); }
    bool Invincible(int character, int action) const
    {
        return character >= 0 && character < kCharacters && action >= 0 && action < kActs &&
               !invincible.empty() && invincible[(size_t)character * kActs + action] != 0;
    }
};

// The planned pressure's library and settings (the module pressplan:1; runs/human-ayu/
// pressplan.py's live plan, pressure_library.py's entries): what a character's players did
// next when a move of theirs was guarded and they could act again beside the guarding
// player, each with the frame advantage it was done at. Keys press_entries, press_per_plan,
// press_per_class, press_window, press_wait, press_tolerance, press_slack, press_near,
// press_max_wait, press_temperature, press_doubt, press_hit_worth, press_hurt_worth,
// press_prior, press_skip, press_sight (pressplan:2; as oki_sight), press_kinds,
// press_source; tensors press.offset (int32, count +
// 1), press.actions (uint8), press.adv, press.distance, press.kind, press.victim,
// press.corner (int32, an entry each); the guarding player's reversals press.rev.* (as
// oki.wake.*: the motion, the button, then the button again every other frame) and the
// invincible moves press.invincible.* (as oki.invincible.*).
struct Press {
    struct Entry {
        uint32_t begin = 0, size = 0;
        int adv = 0, distance = 0, kind = 0, victim = -1;
        bool corner = false;
    };
    std::vector<Entry> entries;
    std::vector<uint8_t> actions;
    std::vector<std::string> kinds;
    std::vector<Mix::Reversal> reversals;
    std::vector<uint8_t> invincible;
    int perPlan = 4, perClass = 2, window = 40, wait = 24, tolerance = 16, slack = 2;
    int near = 160, maxWait = 20;
    double temperature = 200, doubt = 0.3, hitWorth = 1300, hurtWorth = 1200;
    double prior = 8, skip = 0.05;
    int sight = 0; // as Mix::sight, of the guarding player
    std::string source;
    bool Empty() const { return entries.empty(); }
};

// The catch (the module airthrow:1; runs/human-ayu/airplan.py's sure throw): when its
// opponent recovers in the air out of a combo (src/player.cpp's TryAirRecovery: free
// again, beside the agent), the air throws that would catch it before the recovery is
// over are looked for on copies of the fight, and the soonest is played. Until its
// recovery ends the opponent can do nothing, so what a copy shows is what happens: no
// answers to weigh, no library. Keys air_near (the most pixels apart it is looked for at).
struct Catch {
    bool on = false;
    int near = 320;
};

// What the agent has seen its opponent do (efz_env.memory.Memory's counts that the
// planner's belief reads, made the same way from the same views: the agent's, `delay`
// frames late): on its wake-ups, after its guards, and how it guards.
class Counts {
public:
    enum {
        kWakes, kWakeMove, kWakeInvincible, kWakeJump, kWakeBack,
        kGuarded, kGuardedMove, kGuardedInvincible, kGuardedJump, kGuardedBack,
        kGuards, kGuardsCrouch, kCount
    };
    Counts() { Clear(); }
    // Another opponent: nothing kept.
    void Clear();
    // A match ended, the next against the same opponent: the counts scaled by `decay`.
    void End(double decay);
    // A frame's view (the agent's). invincible: the moves invincible from their start,
    // [character * Mix::kActs + action] (a Mix's or a Press's; empty: the timer alone).
    void Update(const float* view, const std::vector<uint8_t>& invincible);
    // okiplan.belief: the shares of the answers a riser is expected to give. sight: the
    // planner's (Mix::sight > 0): the 'crouch' answer is the guard by sight and the
    // 'stand' one kSightStand of the guards, whatever its guards showed.
    void Belief(double prior, double shares[kAnswers], bool sight = false) const;
    // pressplan.belief: of the answers a player gives after guarding.
    void PressBelief(double prior, double shares[kAnswers], bool sight = false) const;
    float c[kCount];

private:
    struct Side {
        int act = -1, frame = 0;
        bool stun = false, guard = false, air = false, thrown = false;
        // (of the frame just seen)
        bool isNew = false, hit = false, struck = false, contact = false, move = false;
        bool backdash = false, jump = false, rose = false, wasGuard = false, inv = false;
        void Step(const float* view, bool opponent, const std::vector<uint8_t>& invincible);
        void Clear() { *this = Side(); }
    };
    struct Window {
        int age = -1, moved = 0, life = 0;
        bool chose = false;
        void Open() { age = 0; chose = false; moved = 0; }
        void Close() { age = -1; moved = 0; }
        void Tick();
    };
    void Choice(Window& w, int base);
    Side me_, it_;
    Window wake_, press_;
};

class MixPlanner {
public:
    typedef std::chrono::steady_clock Clock;
    enum Outcome {
        kNone,    // not done (or nothing asked)
        kPlanned, // an option drawn: `option` (empty: its own play)
        kNothing, // not planned: the opponent isn't down, or is up too soon
        kApart,   // the copies couldn't be played (the fight ended)
    };
    enum { kWait = -1, kOwnPlay = -2 }; // kinds besides the library's
    enum { kMinLead = 24, kMotion = 8, kLook = 110 }; // okiplan.MIN_LEAD, MOTION, LOOK
    enum { kPressLook = 80, kFreeLong = 30 };         // pressplan.LOOK; its free_for limit
    // airplan.LOOK, SURE_SPAN, SURE_MIN_LEAD
    enum { kThrowLook = 60, kThrowSpan = 24, kThrowMinLead = 3 };

    MixPlanner(const Policy* policy, World* world, uint64_t seed);

    // At the opponent's knockdown, on the fight as World::Now has it. side: the agent's
    // player; actions: its inputs for the frames until the plan is played (the frames
    // until it sees the knockdown; none: from the fight as it is); history, prev: its
    // input history after them and its last control byte; seen: its views as it will have
    // them then, (delay + 1) newest first, or nullptr: those of the frames `actions` are
    // played on (delay of them); shares: of the answers (Counts::Belief).
    void Begin(int side, const std::vector<int>& actions, const float* history, uint8_t prev,
               bool deterministic, const double shares[kAnswers], const float* seen = nullptr);
    // The planned pressure (pressplan.live_plan), on the frame a move of the agent's
    // touches the opponent's guard: actions, its inputs for the `delay` frames until it
    // sees the guard, the opponent holding `hold` (a control byte, forward/back relative:
    // the guard it holds); then a crouching guard until the agent is free on the ground;
    // then the library's follow-ups done at that frame advantage and distance. The plan
    // drawn (`option`) is those waiting frames and then the follow-up; `view` is the
    // agent's view after `actions`, `waited` the frames of guard before the follow-up.
    // kNothing: a hit either way before the agent is free, or the agent not free in
    // time, or the opponent out of reach. history, prev: its input history as it is now,
    // before `actions` (the okizeme's Begin takes it after them).
    void BeginPress(int side, const std::vector<int>& actions, const float* history,
                    uint8_t prev, bool deterministic, const double shares[kAnswers],
                    uint8_t hold);
    // The catch (airplan.live_throw), on the frame the opponent's air recovery begins:
    // actions, the agent's inputs for the `delay` frames until it sees the recovery, the
    // opponent pressing nothing; then, from there, the air throws of airplan.throws (C
    // with forward held after every second frame of holding forward, of a second jump or
    // a dash at the opponent, or that far into a jump from the ground), each on a copy
    // until the recovery's end. The plan (`option`) is the one that catches soonest:
    // `caught`, the frame of it the throw catches on; `tried`, how many were looked at;
    // `view`, the agent's view after `actions`. kNothing: the round over or the agent
    // hit on the way, the opponent not in the air or beyond `near` pixels, under
    // kThrowMinLead frames of its recovery left, or no throw that catches inside it.
    void BeginThrow(int side, const std::vector<int>& actions, const float* history,
                    uint8_t prev, bool deterministic, int near);
    // Works on the plan until `deadline`, or until it is done; true once done.
    bool Work(Clock::time_point deadline);
    bool Busy() const { return phase_ != kIdle && phase_ != kDone; }
    bool Done() const { return phase_ == kDone; }
    void Cancel();

    // A plan done:
    Outcome outcome = kNone;
    int lead = 0;               // frames from the plan's start to the opponent's rising
                                // (the pressure's: to its guard's end, 0 if it is over)
    int adv = 0;                // the pressure's: the frame advantage planned at
    int waited = 0;             // the pressure's: frames of guard before the follow-up
    int caught = -1;            // the catch's: the frame of `option` its throw catches on
    int tried = 0;              // the catch's: the throws looked at
    std::vector<int> entries;   // the library's entries tried
    std::vector<int> kinds;     // each option's kind: the entries', then kWait, kOwnPlay
    std::vector<double> worth;  // [option * kAnswers + answer]
    std::vector<int> first;     // who hit first there: 1 the agent, -1 the opponent, 0
    std::vector<double> expected, mix; // an option each
    int chosen = -1;            // the option drawn
    std::vector<int> option;    // its actions, from the plan's start (empty: its own play)
    float view[kObsDim];        // the agent's view at the plan's start, on the copy
    double ms = 0;
    long frames = 0;

    // The row player's mix of the matrix game worth[options][answers] (okiplan.maximin).
    static std::vector<double> Maximin(const std::vector<double>& worth, int options,
                                       int rounds = 2000);

private:
    enum Phase { kIdle, kPrelude, kPlays, kThrows, kDone };
    struct Play {
        int option = 0, answer = 0;
        bool started = false;
        int t = 0, first = 0;
        bool moved = false;       // the opponent started a move of its own (its reversal)
        std::vector<uint8_t> air; // the agent in the air or not, a frame each (sight)
        bool stun[2] = {false, false}, thrown[2] = {false, false};
        int hp[2] = {0, 0};
        Snapshot state;
        std::vector<float> delayed, history; // its own play's
        uint8_t prev = 0;
    };

    bool Prelude();
    bool PressPrelude();
    bool ThrowPrelude();
    bool ThrowRun();
    void Candidates(const float* now);
    void PressCandidates(const float* now);
    void Plays();
    bool Run(Play& p, Clock::time_point deadline);
    void Choose();
    void Finish(Outcome why);

    const Policy* policy_;
    World* world_;
    std::mt19937_64 rng_;
    Phase phase_ = kIdle;
    int side_ = 0;
    bool deterministic_ = false;
    std::vector<int> actions_;
    std::vector<float> history_, seen_;
    bool seenGiven_ = false;
    uint8_t prev_ = 0;
    double shares_[kAnswers];
    Snapshot start_, from_, real_;
    std::vector<std::vector<int>> options_; // each option's actions
    std::vector<uint8_t> schedule_;         // the riser's reversal, a control byte a frame
    std::vector<Play> plays_;
    bool counted_[kAnswers]; // the answers played: those with a share of skip or more
    size_t current_ = 0;
    int hp0_[2] = {0, 0};
    bool stun0_[2] = {false, false}, thrown0_[2] = {false, false};
    int guard_ = 0; // the action that is a crouching guard
    bool press_ = false; // the plan asked for is the pressure's
    bool throw_ = false; // ... is the catch's
    int near_ = 320;     // the catch's: the most pixels apart
    std::vector<std::vector<int>> throws_; // the catch's: the throws to try
    size_t throwAt_ = 0;                   // ... the next of them
    int best_ = -1;                        // ... the one that catches soonest so far
    // (the actions that are nothing, forward, up-forward, up, forward + C: -1 without)
    int neutral_ = -1, forward_ = -1, upForward_ = -1, up_ = -1, grab_ = -1;
    uint8_t hold_ = 0;   // the pressure's: what the opponent holds until the plan's start
    int window_ = 0;     // frames past the lead each play runs
    // (the library's of the plan asked for: the okizeme's or the pressure's)
    double skip_ = 0, doubt_ = 0, temperature_ = 200, hitWorth_ = 1300, hurtWorth_ = 1200;
    int sight_ = 0;   // Mix::sight or Press::sight
    double bait_ = 0; // Mix::bait (the okizeme's alone)
    bool out_ = false, cornered_ = false; // Mix::out; the riser cornered at the plan's start
    std::vector<int> waits_; // the pressure's: the guard frames before the follow-up
    std::vector<float> in_, probs_;
};

} // namespace agent
} // namespace efz

#endif
