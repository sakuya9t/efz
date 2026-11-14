// A trained agent in the game: its network, read from an agent file that
// python/examples/export_agent.py writes from a model.zip and its config.json, and an
// agent playing one side as efz_env.agent.Agent plays in python/examples/play.py.
//
// The file (.efzagent, little-endian):
//   "EFZAGENT", uint32 version (1)
//   uint32 size, then that many bytes of text: "key=value" lines (name, character,
//     frame_skip, history, delay, width, actions, table, features, activation, layers,
//     and the feature columns below)
//   uint32 count, then that many tensors: uint16 name size, the name, uint8 type (0
//     float32, 1 int32), uint8 dimensions, uint32 each, the values
// The network is the actor of Stable-Baselines3's ActorCriticPolicy: its features
// (features=efz: python/efz_env/policy.py's EfzFeatures, the continuous columns scaled
// and the actions and characters embedded; features=flat: the view as it is), `layers`
// hidden layers (pi.K.weight, pi.K.bias) each followed by the activation, and the action
// layer (action.weight, action.bias), whose softmax is the policy.
#ifndef EFZ_AGENT_POLICY_H
#define EFZ_AGENT_POLICY_H

#include <stdint.h>
#include <random>
#include <string>
#include <vector>

namespace efz {
namespace agent {

class Policy {
public:
    // Reads an agent file; false with *error saying why.
    bool Load(const char* path, std::string* error);
    // The same from the file's bytes.
    bool Parse(const unsigned char* data, size_t size, std::string* error);
    // An agent file's name and character from its header alone (for a list of them).
    static bool Peek(const char* path, std::string* name, int* character, std::string* error);

    // The numbers the network takes: the player's view (kObsDim), then `history` steps
    // of its own inputs (6 each), cut to this many.
    int Width() const { return width_; }
    int Actions() const { return (int)table.size(); }
    // The log-probability of each action (Actions() of them) for a view of Width().
    void LogProbs(const float* view, float* out) const;

    std::string name;   // what the menus show
    int character = -1; // the character it was trained to play (0-24), -1 any
    int frameSkip = 1;  // frames each decision is held for
    int history = 0;    // steps of its own inputs it sees
    int delay = 0;      // steps late it sees the game (its reaction time)
    std::vector<uint8_t> table; // per action, the control byte (forward/back relative)

private:
    struct Dense {
        int in = 0, out = 0;
        std::vector<float> weight; // [out][in]
        std::vector<float> bias;
    };
    void Forward(const Dense& d, const float* x, float* y) const;

    int width_ = 0;
    bool efzFeatures_ = false;
    bool tanh_ = false;
    // EfzFeatures
    int selfAction_ = 18, oppAction_ = 50, selfChar_ = 34, oppChar_ = 66;
    int actionVocab_ = 1024, characters_ = 25;
    std::vector<int32_t> cont_;
    std::vector<float> mean_, scale_;
    int actionDim_ = 0, charDim_ = 0;
    std::vector<float> action_, ownAction_, char_;
    std::vector<Dense> layers_;
    Dense out_;
};

// An agent playing one side of a match: each frame, the view of its player and whether
// the controls do anything (no intro, no KO, no pause), and it gives that frame's control
// byte (forward/back relative to where the player faces), as play.py's HumanMatch runs
// it: a decision on a frame the controls do something, held for frameSkip frames, the
// game seen `delay` decisions late, its own last `history` inputs seen at once; nothing
// pressed while the controls do nothing.
class Player {
public:
    Player(const Policy* policy, uint64_t seed);
    // A new match: no inputs yet, the next view seen as the delay's whole past.
    void Reset();
    // This frame's control byte. deterministic: the likeliest action instead of a draw.
    uint8_t Step(const float* view, bool actionable, bool deterministic = false);
    // The action of the last decision (-1 before the first).
    int LastAction() const { return last_; }
    const Policy* policy() const { return policy_; }

private:
    void PushInput(uint8_t controls);

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
};

} // namespace agent
} // namespace efz

#endif
