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
// Keys of no module say where the file came from (version, source.*, exporter, exported,
// dropped): the menus show the version, the log the rest.
#ifndef EFZ_AGENT_POLICY_H
#define EFZ_AGENT_POLICY_H

#include <stdint.h>
#include <deque>
#include <map>
#include <random>
#include <string>
#include <vector>

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

private:
    void PushInput(uint8_t controls);
    int Sample(const float* in, bool deterministic);
    void Begin(const float* view, bool deterministic);
    void Result(const float* view);

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
};

} // namespace agent
} // namespace efz

#endif
