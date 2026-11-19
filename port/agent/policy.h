// A trained agent in the game: its network, read from an agent file that
// python/examples/export_agent.py writes from a model.zip and its config.json (or from a
// pack: everything the agent plays with, in the one file), and an agent playing one side
// as efz_env.agent.Agent plays in python/examples/play.py.
//
// The file (.efzagent, little-endian):
//   "EFZAGENT", uint32 format (2; 1 is still read)
//   uint32 size, then that many bytes of text: "key=value" lines
//   uint32 count, then that many tensors: uint16 name size, the name, uint8 type (0
//     float32, 1 int32, 2 uint8), uint8 dimensions, uint32 each, the values
//
// What the agent is made of, its modules, each of a version (format 2's key modules, e.g.
// "policy:1,routes:1,chooser:1"; format 1: the policy, and its routes if it has them). A
// game refuses a file with a module, or a version of one, it doesn't play, and says which:
//
// policy:1, the network: the actor of Stable-Baselines3's ActorCriticPolicy. Keys name,
//   character, frame_skip, history, delay, width, actions, table, features, activation,
//   layers, the feature columns below. Its features (features=efz: python/efz_env/
//   policy.py's EfzFeatures, the continuous columns scaled and the actions and characters
//   embedded; features=flat: the view as it is), `layers` hidden layers (pi.K.weight,
//   pi.K.bias) each followed by the activation, and the action layer (action.weight,
//   action.bias), whose softmax is the policy.
// routes:1, its combos from a library of people's (routes.h). Keys routes (their count),
//   route_per_start, route_limit, route_by_victim, route_victims (character numbers,
//   comma-separated; none: all), route_replan (plan again at each new move's hit),
//   route_pool (the planner's pool's entries; 0: the routes themselves), route_source;
//   tensors routes.starter and routes.opponent (int32, a route each: the action that hit,
//   the character it was landed on or -1), routes.offset (int32, count + 1: where each
//   route's actions begin in routes.actions), routes.actions (uint8); with a pool,
//   routes.pool.route, routes.pool.at, routes.pool.starter (int32, an entry each: a
//   route's actions from its step `at` on, joined where move `starter` hit in it; each
//   starter's entries in the order the planner takes them).
// chooser:1, a network saying from the agent's view at its hit what each route would
//   deal and what its own play would (runs/human-ayu/combo_net.py's chooser), played when
//   a combo's first plan isn't ready in time. Keys chooser_features, chooser_activation,
//   chooser_layers, chooser_per_start, chooser_margin; tensors as the policy's under
//   "chooser.": chooser.features.*, chooser.layer.K.*, chooser.out.* (routes + 1 outputs,
//   in thousands of HP).
//
// okiplan:1, its okizeme planned from a library of people's (mix.h, which has its keys and
//   tensors). okiplan:2: with oki_sight (the riser guards by sight) or oki_bait (a
//   reversal waited out is worth its punish), which a game of the first version would
//   read past: a file that uses either says 2.
// pressplan:1, its pressure after a guarded move planned from another (mix.h's Press).
//   pressplan:2: with press_sight.
// airthrow:1, an air throw of an opponent that recovers in the air out of its combo, when
//   one catches inside the recovery (mix.h's Catch; key air_near).
// rise:1, its own rising guarded by sight when it sees the attacker on it (Rise, below;
//   keys rise_prior, rise_meaty, rise_low, rise_high, rise_near, rise_fly, rise_decay).
// risk:1, a raw special of its own play let out or stopped at its input by how that move
//   has paid in the match (Risk, below; keys risk_prior, risk_temperature, risk_window,
//   risk_look, risk_look_down, risk_decay, risk_ahead, and risk_moves: "0x105:-131,0xfc:-326,...",
//   each move's action and its prior, HP a use).
//
// Keys of no module say where the file came from (version, source.*, exporter, exported,
// dropped): the menus show the version, the log the rest. A file may also carry what a game
// doesn't play and reads past: its training part (key train, keys and tensors train.*:
// the model's critic and settings, python/efz_env/export.py's unpack_agent makes the model
// to train further from them) and the routes' record for the planner in Python (tensors
// routes.damage, routes.kept, routes.marks, routes.marks.offset).
#ifndef EFZ_AGENT_POLICY_H
#define EFZ_AGENT_POLICY_H

#include <stdint.h>
#include <deque>
#include <map>
#include <random>
#include <string>
#include <vector>

#include "agent/mix.h"

namespace efz {
namespace agent {

class Planner;

// A network of the file: its features, hidden layers each followed by the activation,
// an output layer.
struct Net {
    struct Dense {
        int in = 0, out = 0;
        std::vector<float> weight; // [out][in]
        std::vector<float> bias;
    };
    bool Empty() const { return out.out == 0; }
    int Outputs() const { return out.out; }
    // The outputs for a view (the agent's: its view, then its input history).
    void Forward(const float* view, float* outputs) const;

    int width = 0;
    bool efzFeatures = false;
    bool tanh = false;
    // EfzFeatures
    int selfAction = 18, oppAction = 50, selfChar = 34, oppChar = 66;
    int actionVocab = 1024, characters = 25;
    std::vector<int32_t> cont;
    std::vector<float> mean, scale;
    int actionDim = 0, charDim = 0;
    std::vector<float> action, ownAction, chr;
    std::vector<Dense> layers;
    Dense out;
};

// People's combos the agent plays at its hits (routes.h), as action sequences.
struct Routes {
    struct Route {
        int starter = 0;   // the action (pattern) of the move that hit
        int opponent = -1; // the character it was landed on
        uint32_t begin = 0, size = 0; // its actions in `actions`
    };
    // What the planner tries: a route from its step `at` on (0: the whole of it; else
    // where a later move of it first hit, joined there at a plan made on that move).
    struct Entry {
        int route = 0;
        int at = 0;
    };
    std::vector<Route> list;               // as the library had them (by damage)
    std::map<int, std::vector<int>> byStarter; // indices into list
    std::vector<Entry> pool;
    std::map<int, std::vector<int>> poolByStarter; // indices into pool, in order
    std::vector<uint8_t> actions;
    int perStart = 12;     // routes tried at a hit
    int limit = 900;       // frames a copy is played for at most
    bool byVictim = false; // a library kept per victim: those landed on the opponent first
    bool replan = false;   // a plan again at each new move's hit
    int ending = 0;        // the HP a knockdown at a combo's end is worth over any other
                           // end (0: damage alone); with it the copies' victim recovers
                           // in the air as soon as it can (redteam.Planner's ending)
    std::vector<int> victims; // the characters planned against (empty: all)
    std::string source;
    bool Empty() const { return list.empty(); }
};

// The chooser (format's chooser:1).
struct Chooser {
    Net net;
    int perStart = 12;     // routes it chooses among
    float margin = 200;    // HP a route must promise beyond its own play's
    bool Empty() const { return net.Empty(); }
};

// Its own rising (format's rise:1; runs/human-ayu/rise.py's guard by sight). A rising on
// which the agent sees the attacker on it (while it sees itself down: the attacker in a
// move of its own, or in the air within `fly` pixels, or nearer than `near`: 0, off) is
// guarded through with a probability read from the match: the share of the risings it
// has seen at which the attacker was in a move of its own as the agent saw itself up,
// over a prior (`meaty`, counting as `prior` risings); none at the rate `low`, all at
// `high`, in a line between. A rising guarded through: while it sees itself down, a
// standing guard while it sees the attacker in the air, else its own play's guard, else
// a crouching one. The counts are kept from match to match, scaled by `decay` (the same
// opponent next).
struct Rise {
    bool on = false;
    float prior = 2, meaty = 0.56f, low = 0.3f, high = 0.6f;
    float near = 0, fly = 200, decay = 0.7f;
    int stand = -1, crouch = -1; // the actions of a standing and a crouching guard
};

// Its raw specials (format's risk:1; runs/human-ayu/risk.py). A step that is its own
// play's and presses a button, the agent not seeing its opponent in a hit reaction: the
// press is tried on the game as it is (Player::SetRisk's World), the opponent pressing
// nothing: the press, then nothing, for `look` frames (lookDown while the agent is down:
// a reversal's button is read while it rises). If that starts (an action it was not in)
// one of `moves`, the move's account decides: its worth the mean HP swing (the
// opponent's HP lost less its own over `window` steps after the press, as the agent sees
// it) of the times it was let out in this match, over its prior (`worth`, counting as
// `prior` uses); with the probability 1 / (1 + exp(worth / temperature)) the action's
// button is left out. The accounts are kept from match to match, scaled by `decay`.
// ahead: the inputs of its own play that a planner chooses ahead (for the frames between a
// contact and its seeing it) are drawn for as they are played, as any step of its own
// play is: whatever the contact was, which it has not seen (a plan made from an input
// that is then left out finds the game elsewhere and is dropped).
struct Risk {
    bool on = false;
    float prior = 4, temperature = 75, decay = 0.7f;
    int window = 180, look = 10, lookDown = 50;
    bool ahead = false; // its own play's inputs chosen ahead (a planner's lead-in) drawn for too
    std::vector<int> moves;   // the moves with an account (their actions)
    std::vector<float> worth; // ... and each's prior, HP a use
    std::vector<int> plain;   // per action, the action of the same direction with no button
};

// What its raw specials did: presses that would start a move with an account (drawn
// for), those stopped and let out, and of the ones let out the moves it then saw.
struct RiskStats {
    int seen = 0, stopped = 0, let = 0, came = 0;
};

// What its risings did: the knockdowns it saw, those the attacker was on, of them the
// ones guarded through, the steps it held a guard for and of them the standing ones.
struct RiseStats {
    int knockdowns = 0, met = 0, guarded = 0, steps = 0, stood = 0;
};

class Policy {
public:
    // Reads an agent file; false with *error saying why.
    bool Load(const char* path, std::string* error);
    // The same from the file's bytes.
    bool Parse(const unsigned char* data, size_t size, std::string* error);
    // An agent file's name, character and version from its header alone (for a list of
    // them).
    static bool Peek(const char* path, std::string* name, int* character, std::string* version,
                     std::string* error);

    // The numbers the network takes: the player's view (kObsDim), then `history` steps
    // of its own inputs (6 each), cut to this many.
    int Width() const { return width_; }
    int Actions() const { return (int)table.size(); }
    // The log-probability of each action (Actions() of them) for a view of Width().
    void LogProbs(const float* view, float* out) const;
    // The chooser's pick for an input of Width() (the agent's on the frame it sees its hit
    // of `starter`), its routes played from `offset`: a route (an index into
    // routes.list), or -1 for its own play. values: what it says each route and its own
    // play (the last) would deal, in HP (routes.list.size() + 1).
    int Choose(const float* in, int starter, int offset, std::vector<float>* values) const;

    std::string name;   // what the menus show
    int character = -1; // the character it was trained to play (0-24), -1 any
    int frameSkip = 1;  // frames each decision is held for
    int history = 0;    // steps of its own inputs it sees
    int delay = 0;      // steps late it sees the game (its reaction time)
    std::vector<uint8_t> table; // per action, the control byte (forward/back relative)
    Routes routes;      // its combos' routes; empty: it plays its own
    Chooser chooser;    // its routes' chooser; empty: none
    Mix mix;            // its planned okizeme's library (mix.h); empty: none
    Press press;        // its planned pressure's (mix.h); empty: none
    Catch air;          // its catch of an air recovery (mix.h); off: none
    Rise rise;          // its own rising guarded by sight; off: none
    Risk risk;          // its raw specials by their accounts; off: none
    int format = 0;
    std::string modules; // as "policy:1,routes:1"
    std::string version; // the version it was exported as (empty: none given)
    std::map<std::string, std::string> about; // where it came from: source.*, exporter...

private:
    int width_ = 0;
    Net net_;
};

// What an agent's routes did: plans made (and of those, a route chosen), plans dropped
// and why, of all those asked the ones asked at a later move's hit of a combo (again), the
// routes the chooser played for first plans late, the time planning took and the time the
// game waited for a plan.
struct RouteStats {
    int plans = 0, routes = 0, again = 0;
    int late = 0, elsewhere = 0, over = 0, own = 0, apart = 0;
    int chooser = 0;
    double planMs = 0, planMsMost = 0, waitedMs = 0, waitedMsMost = 0;
    int dropped() const { return late + elsewhere + over + own + apart; }
};

// What an agent's planned okizeme did: plans asked for (a knockdown each), made, and of
// those the ones that drew an option of the library or the wait (played) and not its own
// play; plans dropped and why (late; the game elsewhere than planned from; nothing to
// plan: the opponent up too soon; the fight over); what was drawn, by kind (the library's
// kinds, then the wait and its own play); the time planning took and the game waited.
struct OkiStats {
    int asked = 0, plans = 0, played = 0;
    int late = 0, elsewhere = 0, nothing = 0, apart = 0;
    std::vector<int> drawn;
    double planMs = 0, planMsMost = 0, waitedMs = 0, waitedMsMost = 0;
    long frames = 0;
};

// An agent playing one side of a match: each frame, the view of its player and whether
// the controls do anything (no intro, no KO, no pause), and it gives that frame's control
// byte (forward/back relative to where the player faces), as play.py's HumanMatch runs
// it: a decision on a frame the controls do something, held for frameSkip frames, the
// game seen `delay` decisions late, its own last `history` inputs seen at once; nothing
// pressed while the controls do nothing.
//
// With a planner (SetPlanner: the agent file's routes), its combos are played as
// play.py --assist plays them (runs/human-ayu/combo_support.py's LiveRoutes): at the
// frame its hit lands it chooses its inputs for the `delay` frames until it sees the hit
// (from what it has seen already), the planner tries the routes from where those leave
// the game, and once it sees the hit it plays the route chosen, if the game is where the
// plan expected and the combo goes on. With routes.replan, again at each new move's hit
// of the combo: the rest of the route it is on one of the options, and its inputs until
// it sees that hit that route's. A combo's first plan not ready in time: the chooser's
// pick, if the file has one, else its own play; a later plan's: on with the route.
class Player {
public:
    Player(const Policy* policy, uint64_t seed);
    // A new match (or fight): no inputs yet, the next view seen as the delay's whole
    // past, no plan, its routes' stats from 0.
    void Reset();
    // This frame's control byte. deterministic: the likeliest action instead of a draw.
    uint8_t Step(const float* view, bool actionable, bool deterministic = false);
    // The action of the last decision (-1 before the first).
    int LastAction() const { return last_; }
    const Policy* policy() const { return policy_; }

    // Its combos from the routes, planned by `planner` for player `side` (nullptr: its
    // own). patienceMs: how long a frame waits for a combo's first plan not done when the
    // agent sees its hit (< 0: until it is done), before the agent plays on without it;
    // againMs: the same for a later plan of the combo.
    void SetPlanner(Planner* planner, int side, double patienceMs, double againMs = 8);
    const RouteStats& Stats() const { return stats_; }
    bool Planning() const { return planner_ != nullptr; }

    // Its okizeme planned by `mix` for player `side` (nullptr: its own), as
    // runs/human-ayu/okiplan.py's module plays it: at its opponent's knockdown it chooses
    // its inputs for the `delay` frames until it sees the knockdown, the planner tries the
    // library's okizeme from where those leave the fight, and once it sees the knockdown
    // it plays the one drawn, until its inputs end, it sees itself hit, or a route takes
    // over (a hit of the okizeme's: the routes plan from it, the rest of the okizeme one
    // of their options). The answers' shares are its counts of this opponent (Counts),
    // kept from match to match, older ones counting for less.
    void SetMix(MixPlanner* mix, int side, double patienceMs);
    const OkiStats& Oki() const { return oki_; }
    // Its planned pressure's (the same counts: a guarded move each; played: a plan that
    // drew something other than its own play). With a pressure library the same planner
    // also plans from each move of the agent's that touches the opponent's guard
    // (pressplan.py's live plan): its inputs for the `delay` frames until it sees the
    // guard chosen at once, then a crouching guard until it is free, then the follow-up
    // drawn.
    const OkiStats& Pressure() const { return press_; }
    // Its catches' (the module airthrow:1): asked, the opponent's air recoveries out of
    // its combos planned from, on the frame they begin (its inputs for the `delay` frames
    // until it sees one chosen at once); plans and played, those with an air throw that
    // catches inside the recovery, played when it sees the recovery; nothing: no such
    // throw (or the opponent out of reach); the rest as the okizeme's.
    const OkiStats& Air() const { return air_; }
    // Its risings' (the module rise:1), the probability the next one the attacker is on
    // is guarded through, and its accounts (account 0 its own play, 1 the guard: the
    // risings counted and their swings' sum).
    const RiseStats& Rising() const { return rise_; }
    double RiseChance() const;
    double RiseSeen() const { return riseSeen_; } // the risings it saw; of them, the
    double RiseOn() const { return riseOn_; }     // attacker in a move as it rose
    // Its raw specials by their accounts (the module risk:1), tried on `world`'s game for
    // player `side` (nullptr: off: nothing is stopped). RiskStarts: the move (an index
    // into policy()->risk.moves, -1 none) that `action` starts on the game as it is, the
    // game left as it was; `view`: that game's view. RiskChance: the probability that a
    // press starting that move is stopped now.
    void SetRisk(World* world, int side);
    const RiskStats& Risks() const { return risks_; }
    int RiskStarts(const float* view, int action);
    double RiskChance(int move) const;
    bool Mixing() const { return mix_ != nullptr; }
    // Another opponent: what it counted of the last one forgotten.
    void Forget()
    {
        counts_.Clear();
        counted_ = false;
        riseSeen_ = riseOn_ = 0;
        risen_ = false;
        std::fill(riskCount_.begin(), riskCount_.end(), 0.0);
        std::fill(riskTotal_.begin(), riskTotal_.end(), 0.0);
        risked_ = false;
    }
    const Counts& Seen() const { return counts_; }

private:
    void PushInput(uint8_t controls);
    int Sample(const float* in, bool deterministic);
    void Begin(const float* view, bool deterministic);
    void Result(const float* view);
    void OkiBegin(const float* view, bool deterministic);
    void OkiResult(const float* view);
    void MixResults(const float* view);
    void MixBegins(const float* view, bool deterministic);
    void PressBegin(const float* view, bool deterministic);
    void PressResult(const float* view);
    void ThrowBegin(const float* view, bool deterministic);
    void ThrowResult(const float* view);
    void RiseWatch();
    int RiseAct(int action);
    void RiskWatch();
    int RiskAct(const float* view, int action);
    void RiskSettle();

    const Policy* policy_;
    std::mt19937_64 rng_;
    std::vector<float> seen_; // (delay + 1) views, newest first
    bool fresh_ = true;
    std::vector<float> inputs_; // history x 6, newest first
    uint8_t prev_ = 0;
    int held_ = 0;
    int last_ = -1;
    uint8_t bytes_ = 0;
    std::vector<float> in_, probs_;

    // The routes (LiveRoutes's state).
    Planner* planner_ = nullptr;
    int side_ = 0;
    double patienceMs_ = 50, againMs_ = 8, waitMs_ = 50;
    std::deque<int> queue_; // its inputs chosen at the hit, for the frames until it sees it
    std::deque<bool> queueOwn_; // ... each its own play's (drawn from the network), or a plan's
    // The inputs chosen ahead, queued: `planned` of them (the first) a plan's, the rest
    // its own play's.
    void Queue(const std::vector<int>& actions, size_t planned, size_t own);
    bool pending_ = false;  // a plan asked for
    bool pendingFirst_ = false; // (a combo's first)
    int pendingMove_ = 0, pendingOffset_ = 0;
    std::vector<int> route_; // the route being played (actions), from routeAt_
    size_t routeAt_ = 0;
    bool routeOn_ = false;
    std::vector<int> kept_; // the route it was on when it asked for the plan, played from
    bool keptOn_ = false;   // `delay` on until the plan says otherwise
    bool planned_ = false;  // a plan made on a hit of this combo, of move plannedMove_
    int plannedMove_ = 0;
    int hitMove_ = 0, hitAge_ = 0; // its last hit's move, the frames since
    int prevHits_ = 0;
    std::vector<float> values_;
    RouteStats stats_;

    // The planned okizeme.
    MixPlanner* mix_ = nullptr;
    Counts counts_;
    bool counted_ = false;   // a view counted since the last match's end
    bool wasDown_ = false;   // the opponent was down on the frame before (as the game is)
    bool okiWanted_ = false; // a knockdown not planned for yet
    bool okiPending_ = false; // a plan asked for
    std::vector<int> okiRoute_; // what it planned and is playing (an okizeme, or a
    size_t okiAt_ = 0;          // guarded move's follow-up), from okiAt_
    bool okiOn_ = false;
    OkiStats oki_;
    bool pressPending_ = false;  // a pressure plan asked for
    std::vector<int> pressRest_; // what was left of the planned move it was playing then
    int nowAct_ = -1, nowFrame_ = 0; // the opponent's action and its frame, as the game was
    OkiStats press_;
    bool throwWanted_ = false;  // the opponent recovering in the air, not planned from yet
    bool throwPending_ = false; // a catch asked for
    OkiStats air_;

    // Its own rising (rise.py's Rise, the guard by sight), from what it sees.
    double riseSeen_ = 0, riseOn_ = 0; // the risings it saw; the attacker in a move at them
    bool risen_ = false;      // a view seen since the last match's end
    bool riseDown_ = false;   // it saw itself down on the step before
    bool riseMet_ = false;    // this rising: the attacker seen on it
    bool riseDrawn_ = false;  // ... and its guard drawn for
    bool riseVeto_ = false;   // ... guarded through
    RiseStats rise_;

    // Its raw specials (risk.py's Risk).
    World* riskWorld_ = nullptr;
    int riskSide_ = 0;
    Snapshot riskSnap_;
    std::vector<double> riskCount_, riskTotal_; // the accounts, a move each
    bool risked_ = false;      // a view seen since the last match's end
    int riskT_ = 0;            // steps
    int riskDrawn_ = -1, riskDrawnAt_ = 0; // the press being tried: its move, the step,
    bool riskStop_ = false;                // and whether it is stopped
    int riskOpen_ = -1;        // the use being followed: its move (-1 none), its age,
    int riskAge_ = 0;          // both HP at the press, whether the move was seen
    float riskHp_ = 0, riskOppHp_ = 0;
    bool riskCame_ = false;
    RiskStats risks_;
};

} // namespace agent
} // namespace efz

#endif
