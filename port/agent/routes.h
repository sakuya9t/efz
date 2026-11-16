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
    // the game (the rest of the route being played).
    void Begin(int side, int starter, const std::vector<int>& actions, const float* history,
               uint8_t prev, bool deterministic, const float* view, int late = 0,
               const std::vector<int>& extra = std::vector<int>());
    // Works on the plan until `deadline`, or until it is done; true once done.
    bool Work(Clock::time_point deadline);
    bool Busy() const { return phase_ == kPrelude || phase_ == kOptions; }
    bool Done() const { return phase_ == kDone; }
    void Cancel();

    // A plan done:
    enum { kOwnPlay = -1, kExtra = -2 };
    Outcome outcome = kNone;
    int chosen = -1;          // the option chosen (an index into tried), -1 its own play
    std::vector<int> route;   // its actions, from where `actions` leave the game
    int offset = 0;           // the routes' actions are played from this one (delay + late)
    std::vector<int> tried;   // the options: pool entries (Policy::routes.pool), kExtra,
                              // then kOwnPlay
    std::vector<float> dealt; // the most each dealt (HP), in that order
    float best = 0, own = 0;  // the most any option dealt, its own play's
    float expected[kObsDim];  // the agent's view when it sees its hit, on the copy
    double ms = 0;            // time worked on it
    long frames = 0;          // frames run on copies

private:
    enum Phase { kIdle, kPrelude, kOptions, kDone };
    struct Option {
        int entry = kOwnPlay; // a pool entry, kExtra or kOwnPlay
        bool started = false;
        int t = 0;
        float dealt = 0;
        Snapshot state;             // where it was left, when the work stopped in it
        std::vector<float> delayed; // its own play: the views it has seen, newest first
        std::vector<float> history; // its own play: its input history
        uint8_t prev = 0;
    };

    bool Prelude();
    // Plays an option on, frame by frame; true once its combo is over.
    bool Play(Option& o, Clock::time_point deadline);
    void Choose();
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
    size_t current_ = 0;
    int longest_ = 0;
    int hp0_ = 0;
    std::vector<float> in_, probs_;
};

} // namespace agent
} // namespace efz

#endif
