// An agent's combos from built-in routes, planned as play.py --assist plans them
// (runs/human-ayu/combo_support.py's LiveRoutes, with redteam.py's Planner): at the frame
// the agent's hit lands, the game is copied; on the copy the agent's inputs for the
// `delay` frames until it sees the hit are played (already chosen, from what it has
// seen), the opponent holding back, and from there each of the library's routes that
// begin with the move that hit (the first per_start, of those long enough to be played
// from that point; a library kept per victim: those landed on this opponent first) and
// its own play (seeing the copy as late as it sees the game) are played on copies, the
// opponent guarding once it can, until each combo ends. The one that dealt the most is
// chosen if it beats its own play. The Player (policy.h) plays it once it sees its hit.
// With routes.ending (redteam.Planner's ending) the victim on the copies also presses a
// button every other frame, which recovers it in the air as soon as the game lets it, as a
// person does; each option is played a few frames past its combo's end, and one that
// leaves the victim lying (not recovered in the air) is worth that many HP more.
// Planned again at a later move's hit of the combo (routes.replan, round 15b's), the
// routes are also joined where that move hit in them (the pool's entries), and the rest
// of the route being played is one more option.
//
// The copies are of the World: the native game's own fight (port/agent/play.cpp), saved
// and written back as netplay's rollback does, or a headless environment's (efz_env's
// efz_env_agent_plan, which tests that a plan is the Python planner's). A plan is worked
// on in pieces (Work, up to a deadline): the game's time between frames. Between pieces
// the World's game is as it was; nothing the plan does reaches it, its sounds, its
// records or a network match: an agent plays through its controls only.
#ifndef EFZ_AGENT_ROUTES_H
#define EFZ_AGENT_ROUTES_H

#include <stdint.h>
#include <chrono>
#include <random>
#include <vector>

#include "agent/observe.h"

namespace efz {
namespace agent {

class Policy;

// A copy of a fight, as its World saves it.
struct Snapshot {
    struct Region {
        char* at;
        size_t size, offset;
    };
    std::vector<Region> regions;
    std::vector<char> bytes;
    uint32_t rng = 0;
    uint32_t tag = 0; // the World's: which fight it is of
    bool valid = false;
};

class World {
public:
    virtual ~World() {}
    // Planning begins and ends: what the fight's frames do besides the fight (sounds,
    // keys, records, drawing) is left out in between.
    virtual void Enter() {}
    virtual void Leave() {}
    // The fight as it is now, and back as it was; Load is false if the fight it was saved
    // from is gone (another fight, another scene), and nothing is written then.
    virtual void Save(Snapshot* s) = 0;
    virtual bool Load(const Snapshot& s) = 0;
    // The fight as the agent saw it last (by default as it is now: Save): what a plan
    // starts from.
    virtual void Now(Snapshot* s) { Save(s); }
    // One frame, with each player's control byte as the screen has it (left is left);
    // false: the fight can't go on (its scene ended).
    virtual bool Step(const uint8_t input[2]) = 0;
    // The fight as it is: player `side`'s view (observe.h), and of player p where it
    // faces (1 right, -1 left), its HP (0 at least), its combo's hits, the controls it
    // read on the frame just run (ControlsRead); whether a round is over (a KO) or the
    // match. The planner sees the game only through these: a World may keep its game
    // where the planner's own memory isn't (efz_env's arenas).
    virtual void View(int side, float* out) = 0;
    virtual int Facing(int p) = 0;
    virtual int Hp(int p) = 0;
    virtual int ComboHits(int p) = 0;
    virtual uint8_t Read(int p) = 0;
    virtual bool Over() = 0;
};

class Planner {
public:
    typedef std::chrono::steady_clock Clock;
    enum Outcome {
        kNone,    // not done (or nothing asked)
        kPlanned, // a route chosen (chosen >= 0) or its own play (chosen -1)
        kOwn,     // not planned: the opponent isn't one of the routes' victims
        kApart,   // the copies couldn't be played (the fight ended)
    };

    Planner(const Policy* policy, World* world, uint64_t seed);

    // At the agent's hit, on the game as World::Now has it: the plan asked for (one
    // before it, if any, dropped). side: the agent's player; starter: the move that hit
    // (its view's action); actions: its inputs (actions) for the frames until it sees the
    // hit; history, prev: its input history after them (Policy::history x 6, newest first)
    // and its last control byte; deterministic: its own play's choice on the copies;
    // view: its player's view of the game now (whose opponent says if it plans). late:
    // the frames since the hit (a plan awaited when it landed): the routes are played from
    // that much further in. extra: one more option, actions from where `actions` leave
    // the game (the rest of the route being played). again: a later plan of a combo
    // already planned for (the target below goes on from that combo's).
    void Begin(int side, int starter, const std::vector<int>& actions, const float* history,
               uint8_t prev, bool deterministic, const float* view, int late = 0,
               const std::vector<int>& extra = std::vector<int>(), bool again = false);
    // What the plans aim at. 1 (an agent's, the default): the option worth the most, if
    // that is more than its own play. Less (the game's CPU with combos: its level's share,
    // play.cpp): a combo's first plan takes the option nearest that share of the most any
    // option is worth, and a later plan of the combo the one nearest what is left of that
    // target (the target less what the combo has dealt between the two plans' starts); its
    // own play is one of the options. Ties go to what it would go on with (the first
    // played: the rest of its route, else its own play).
    void SetShare(float share) { share_ = share; }
    float Share() const { return share_; }
    // Its own play played last of the options, not first (the game's CPU with combos):
    // a plan due before it is done is then chosen from the routes played by then, and the
    // network's frames on the copies, half a plan's time, come after them.
    void SetOwnLast(bool on) { ownLast_ = on; }
    // Works on the plan until `deadline`, or until it is done; true once done.
    bool Work(Clock::time_point deadline);
    bool Busy() const { return phase_ == kPrelude || phase_ == kOptions; }
    bool Done() const { return phase_ == kDone; }
    void Cancel();
    // The plan is due and not done: the best of the options played to their end so far,
    // if what the agent goes on with otherwise is among them (the rest of the route it
    // is on, else its own play: played first for this), and that one unless another
    // dealt more; true: done, with `partial` set and `played` saying how many. False:
    // nothing to choose from yet (the plan is to be dropped). The game gives a plan
    // the idle time of the frames until the agent sees its hit; a quarter of the plans
    // at a later hit of a combo were not done by then (the user's sessions, 16-19
    // November) and were dropped whole.
    bool Settle();
    // The work a plan may take, in frames on copies (one of its own play's counts
    // `own`: the network's decision, 14 frames' worth of time as measured), 0 for no
    // limit: once spent, Work does nothing more and says the plan is not done. For an
    // evaluation, which otherwise works every plan to its end, to play as the game does
    // on a machine with that much time.
    void SetBudget(long cost, int own = 15)
    {
        budget_ = cost;
        ownCost_ = own > 0 ? own : 15;
    }

    // A plan done:
    enum { kOwnPlay = -1, kExtra = -2 };
    Outcome outcome = kNone;
    int chosen = -1;          // the option chosen (an index into tried), -1 its own play
    std::vector<int> route;   // its actions, from where `actions` leave the game
    int offset = 0;           // the routes' actions are played from this one (delay + late)
    std::vector<int> tried;   // the options: pool entries (Policy::routes.pool), kExtra,
                              // then kOwnPlay
    std::vector<float> dealt; // the most each dealt (HP), in that order
    std::vector<int> ends;    // how each left the victim: 1 lying, 2 recovered in the air, 0
                              // neither (routes.ending; else all 0)
    float best = 0, own = 0;  // the most any option dealt, its own play's
    float target = -1;        // with a share under 1: the worth it aimed at (else -1)
    float expected[kObsDim];  // the agent's view when it sees its hit, on the copy
    double ms = 0;            // time worked on it
    long frames = 0;          // frames run on copies
    long cost = 0;            // the work it took (SetBudget's unit)
    int played = 0;           // the options played to their end
    bool partial = false;     // chosen from some of them only (Settle)

private:
    enum Phase { kIdle, kPrelude, kOptions, kDone };
    struct Option {
        int entry = kOwnPlay; // a pool entry, kExtra or kOwnPlay
        bool started = false;
        int t = 0;
        float dealt = 0;
        int over = -1;                  // the frame its combo ended on (routes.ending)
        bool down = false, recovered = false; // how it left the victim: lying; recovered in the air
        Snapshot state;             // where it was left, when the work stopped in it
        std::vector<float> delayed; // its own play: the views it has seen, newest first
        std::vector<float> history; // its own play: its input history
        uint8_t prev = 0;
    };

    bool Prelude();
    // Plays an option on, frame by frame; true once its combo is over.
    bool Play(Option& o, Clock::time_point deadline);
    void Choose(size_t done);
    void View(int side, float* out);
    void Finish(Outcome why);

    const Policy* policy_;
    World* world_;
    std::mt19937_64 rng_;
    Phase phase_ = kIdle;
    int side_ = 0, starter_ = 0;
    bool deterministic_ = false;
    std::vector<int> actions_, extra_;
    std::vector<float> history_;
    uint8_t prev_ = 0;
    Snapshot start_, afterDelay_, real_;
    std::vector<float> seen_; // (delay + 1) views, newest first, as the agent will see them
    std::vector<Option> options_;
    std::vector<size_t> work_; // the options in the order they are played
    size_t current_ = 0;       // (into work_)
    long budget_ = 0;
    int ownCost_ = 15;
    int longest_ = 0;
    int hp0_ = 0;
    float share_ = 1;
    bool ownLast_ = false;
    bool again_ = false;
    bool comboSet_ = false;  // a target set by this combo's first plan:
    int comboHp0_ = 0;       // the victim's HP where that plan's options began,
    float comboTarget_ = 0;  // and the worth aimed at from there
    std::vector<float> in_, probs_;
};

} // namespace agent
} // namespace efz

#endif
