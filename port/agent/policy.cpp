// A trained agent's network and an agent playing one side (policy.h).
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <map>

#include "platform.h"
#include "agent/observe.h"
#include "agent/policy.h"

namespace efz {
namespace agent {

namespace {

const char kMagic[8] = {'E', 'F', 'Z', 'A', 'G', 'E', 'N', 'T'};
const uint32_t kVersion = 1;
const int kInputFeatures = 6; // per step of history: forward-back, up-down, A B C D pressed

struct Tensor {
    int type = 0; // 0 float32, 1 int32
    std::vector<uint32_t> dims;
    std::vector<float> f;
    std::vector<int32_t> i;
    size_t Count() const
    {
        size_t n = 1;
        for (uint32_t d : dims)
            n *= d;
        return n;
    }
};

class Reader {
public:
    Reader(const unsigned char* p, size_t n) : p_(p), end_(p + n) {}
    bool Bytes(void* out, size_t n)
    {
        if ((size_t)(end_ - p_) < n)
            return false;
        memcpy(out, p_, n);
        p_ += n;
        return true;
    }
    template <class T> bool Get(T* v) { return Bytes(v, sizeof(T)); }

private:
    const unsigned char* p_;
    const unsigned char* end_;
};

int ToInt(const std::map<std::string, std::string>& keys, const char* key, int fallback)
{
    auto it = keys.find(key);
    return it == keys.end() || it->second.empty() ? fallback : atoi(it->second.c_str());
}

} // namespace

bool Policy::Load(const char* path, std::string* error)
{
    FILE* f = OpenPath(path, "rb");
    if (!f) {
        *error = std::string("can't open ") + path;
        return false;
    }
    std::vector<unsigned char> data;
    unsigned char buf[1 << 16];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f)) > 0)
        data.insert(data.end(), buf, buf + n);
    fclose(f);
    return Parse(data.data(), data.size(), error);
}

bool Policy::Peek(const char* path, std::string* name, int* character, std::string* error)
{
    FILE* f = OpenPath(path, "rb");
    if (!f) {
        *error = std::string("can't open ") + path;
        return false;
    }
    unsigned char head[16];
    bool ok = fread(head, 1, 16, f) == 16 && memcmp(head, kMagic, 8) == 0;
    uint32_t version = 0, size = 0;
    if (ok) {
        memcpy(&version, head + 8, 4);
        memcpy(&size, head + 12, 4);
        ok = version == kVersion && size < (1u << 16);
    }
    std::string text(ok ? size : 0, '\0');
    ok = ok && (size == 0 || fread(&text[0], 1, size, f) == size);
    fclose(f);
    if (!ok) {
        *error = version && version != kVersion ? "an agent file of another version"
                                                : "not an agent file";
        return false;
    }
    *name = "agent";
    *character = -1;
    for (size_t at = 0; at < text.size();) {
        size_t end = text.find('\n', at);
        if (end == std::string::npos)
            end = text.size();
        std::string line = text.substr(at, end - at);
        at = end + 1;
        if (line.compare(0, 5, "name=") == 0)
            *name = line.substr(5);
        else if (line.compare(0, 10, "character=") == 0)
            *character = atoi(line.c_str() + 10);
    }
    if (*character < -1 || *character >= kCharacters)
        *character = -1;
    return true;
}

bool Policy::Parse(const unsigned char* data, size_t size, std::string* error)
{
    Reader r(data, size);
    char magic[8];
    uint32_t version = 0, textSize = 0, count = 0;
    if (!r.Bytes(magic, 8) || memcmp(magic, kMagic, 8) != 0) {
        *error = "not an agent file (export one with python/examples/export_agent.py)";
        return false;
    }
    if (!r.Get(&version) || version != kVersion) {
        *error = "an agent file of version " + std::to_string(version) + "; this game reads " +
                 std::to_string(kVersion);
        return false;
    }
    std::string text;
    if (!r.Get(&textSize) || textSize > size) {
        *error = "the agent file is cut short";
        return false;
    }
    text.resize(textSize);
    if (textSize && !r.Bytes(&text[0], textSize)) {
        *error = "the agent file is cut short";
        return false;
    }
    std::map<std::string, std::string> keys;
    for (size_t at = 0; at < text.size();) {
        size_t end = text.find('\n', at);
        if (end == std::string::npos)
            end = text.size();
        std::string line = text.substr(at, end - at);
        at = end + 1;
        size_t eq = line.find('=');
        if (eq != std::string::npos)
            keys[line.substr(0, eq)] = line.substr(eq + 1);
    }
    std::map<std::string, Tensor> tensors;
    if (!r.Get(&count)) {
        *error = "the agent file is cut short";
        return false;
    }
    for (uint32_t k = 0; k < count; k++) {
        uint16_t nameSize = 0;
        uint8_t type = 0, ndim = 0;
        std::string tname;
        Tensor t;
        if (!r.Get(&nameSize)) {
            *error = "the agent file is cut short";
            return false;
        }
        tname.resize(nameSize);
        if ((nameSize && !r.Bytes(&tname[0], nameSize)) || !r.Get(&type) || !r.Get(&ndim) ||
            type > 1 || ndim > 4) {
            *error = "the agent file is damaged";
            return false;
        }
        t.type = type;
        t.dims.resize(ndim);
        for (uint8_t d = 0; d < ndim; d++) {
            if (!r.Get(&t.dims[d])) {
                *error = "the agent file is cut short";
                return false;
            }
        }
        size_t n = t.Count();
        if (n > size) {
            *error = "the agent file is damaged";
            return false;
        }
        bool ok;
        if (type == 0) {
            t.f.resize(n);
            ok = r.Bytes(t.f.data(), n * 4);
        } else {
            t.i.resize(n);
            ok = r.Bytes(t.i.data(), n * 4);
        }
        if (!ok) {
            *error = "the agent file is cut short";
            return false;
        }
        tensors[tname] = std::move(t);
    }

    name = keys.count("name") ? keys["name"] : std::string("agent");
    character = ToInt(keys, "character", -1);
    if (character < -1 || character >= kCharacters)
        character = -1;
    frameSkip = std::max(1, ToInt(keys, "frame_skip", 1));
    history = std::max(0, ToInt(keys, "history", 0));
    delay = std::max(0, ToInt(keys, "delay", 0));
    width_ = ToInt(keys, "width", 0);
    table.clear();
    const std::string& hex = keys["table"];
    for (size_t i = 0; i + 1 < hex.size(); i += 2)
        table.push_back((uint8_t)strtoul(hex.substr(i, 2).c_str(), nullptr, 16));
    if (width_ <= 0 || width_ > kObsDim + history * kInputFeatures) {
        *error = "the agent's network takes " + std::to_string(width_) +
                 " numbers: more than its view and its history";
        return false;
    }
    efzFeatures_ = keys["features"] == "efz";
    if (!efzFeatures_ && keys["features"] != "flat") {
        *error = "the agent's features are '" + keys["features"] + "': this game knows efz and flat";
        return false;
    }
    tanh_ = keys["activation"] == "tanh";
    if (!tanh_ && keys["activation"] != "relu") {
        *error = "the agent's activation is '" + keys["activation"] + "': this game knows relu and tanh";
        return false;
    }

    auto take = [&](const std::string& tname, int type, size_t dims, Tensor* out) {
        auto it = tensors.find(tname);
        if (it == tensors.end() || it->second.type != type || it->second.dims.size() != dims) {
            *error = "the agent file has no " + tname + " of the right shape";
            return false;
        }
        *out = std::move(it->second);
        return true;
    };
    int features = width_;
    if (efzFeatures_) {
        selfAction_ = ToInt(keys, "self_action", 18);
        oppAction_ = ToInt(keys, "opp_action", 50);
        selfChar_ = ToInt(keys, "self_char", 34);
        oppChar_ = ToInt(keys, "opp_char", 66);
        actionVocab_ = ToInt(keys, "action_vocab", 1024);
        characters_ = ToInt(keys, "characters", 25);
        Tensor cont, mean, scale, action, own, chr;
        if (!take("features.cont", 1, 1, &cont) || !take("features.mean", 0, 1, &mean) ||
            !take("features.scale", 0, 1, &scale) || !take("features.action", 0, 2, &action) ||
            !take("features.own_action", 0, 2, &own) || !take("features.char", 0, 2, &chr))
            return false;
        size_t n = cont.i.size();
        if (mean.f.size() != n || scale.f.size() != n || action.dims[0] != (uint32_t)actionVocab_ ||
            own.dims[0] != (uint32_t)(actionVocab_ * characters_) || own.dims[1] != action.dims[1] ||
            chr.dims[0] != (uint32_t)characters_) {
            *error = "the agent's features don't fit together";
            return false;
        }
        for (int32_t c : cont.i) {
            if (c < 0 || c >= width_) {
                *error = "the agent's features read past its view";
                return false;
            }
        }
        for (int c : {selfAction_, oppAction_, selfChar_, oppChar_}) {
            if (c < 0 || c >= width_) {
                *error = "the agent's features read past its view";
                return false;
            }
        }
        cont_ = std::move(cont.i);
        mean_ = std::move(mean.f);
        scale_ = std::move(scale.f);
        actionDim_ = (int)action.dims[1];
        charDim_ = (int)chr.dims[1];
        action_ = std::move(action.f);
        ownAction_ = std::move(own.f);
        char_ = std::move(chr.f);
        features = (int)cont_.size() + 4 * actionDim_ + 2 * charDim_;
    }
    int layers = ToInt(keys, "layers", 0);
    layers_.assign(layers, Dense());
    int in = features;
    for (int k = 0; k <= layers; k++) {
        Dense& d = k < layers ? layers_[k] : out_;
        std::string base = k < layers ? "pi." + std::to_string(k) : std::string("action");
        Tensor w, b;
        if (!take(base + ".weight", 0, 2, &w) || !take(base + ".bias", 0, 1, &b))
            return false;
        if (w.dims[1] != (uint32_t)in || b.dims[0] != w.dims[0]) {
            *error = "the agent's layer " + base + " doesn't fit the one before";
            return false;
        }
        d.in = in;
        d.out = (int)w.dims[0];
        d.weight = std::move(w.f);
        d.bias = std::move(b.f);
        in = d.out;
    }
    if (out_.out != (int)table.size() || table.empty()) {
        *error = "the agent has " + std::to_string(out_.out) + " actions and " +
                 std::to_string(table.size()) + " control bytes for them";
        return false;
    }
    return true;
}

void Policy::Forward(const Dense& d, const float* x, float* y) const
{
    for (int o = 0; o < d.out; o++) {
        const float* w = &d.weight[(size_t)o * d.in];
        double sum = 0;
        for (int i = 0; i < d.in; i++)
            sum += (double)w[i] * x[i];
        y[o] = (float)(sum + d.bias[o]);
    }
}

void Policy::LogProbs(const float* view, float* out) const
{
    std::vector<float> x, y;
    if (efzFeatures_) {
        // python/efz_env/policy.py's EfzFeatures.forward.
        x.reserve(cont_.size() + 4 * actionDim_ + 2 * charDim_);
        for (size_t i = 0; i < cont_.size(); i++) {
            float v = (view[cont_[i]] - mean_[i]) * scale_[i];
            x.push_back(std::min(10.0f, std::max(-10.0f, v)));
        }
        auto index = [&](int column, int count) {
            long v = (long)nearbyintf(view[column]);
            return (int)std::min<long>(count - 1, std::max<long>(0, v));
        };
        auto append = [&](const std::vector<float>& table, int row, int dim) {
            x.insert(x.end(), table.begin() + (size_t)row * dim, table.begin() + (size_t)(row + 1) * dim);
        };
        int pairs[2][2] = {{selfAction_, selfChar_}, {oppAction_, oppChar_}};
        for (auto& pair : pairs) {
            int act = index(pair[0], actionVocab_);
            int chr = index(pair[1], characters_);
            append(action_, act, actionDim_);
            append(ownAction_, chr * actionVocab_ + act, actionDim_);
        }
        append(char_, index(selfChar_, characters_), charDim_);
        append(char_, index(oppChar_, characters_), charDim_);
    } else {
        x.assign(view, view + width_);
    }
    for (const Dense& d : layers_) {
        y.resize(d.out);
        Forward(d, x.data(), y.data());
        for (float& v : y)
            v = tanh_ ? tanhf(v) : std::max(0.0f, v);
        x.swap(y);
    }
    Forward(out_, x.data(), out);
    float most = *std::max_element(out, out + out_.out);
    double sum = 0;
    for (int a = 0; a < out_.out; a++)
        sum += exp((double)out[a] - most);
    float logSum = (float)(most + log(sum));
    for (int a = 0; a < out_.out; a++)
        out[a] -= logSum;
}

Player::Player(const Policy* policy, uint64_t seed) : policy_(policy), rng_(seed)
{
    seen_.assign((size_t)(policy->delay + 1) * kObsDim, 0.0f);
    inputs_.assign((size_t)policy->history * kInputFeatures, 0.0f);
    in_.assign((size_t)kObsDim + inputs_.size(), 0.0f);
    probs_.assign(policy->Actions(), 0.0f);
    Reset();
}

void Player::Reset()
{
    fresh_ = true;
    std::fill(inputs_.begin(), inputs_.end(), 0.0f);
    prev_ = 0;
    held_ = 0;
    last_ = -1;
    bytes_ = 0;
}

// efz_env.history.InputHistory.push: the newest step first.
void Player::PushInput(uint8_t c)
{
    if (inputs_.empty())
        return;
    std::copy_backward(inputs_.begin(), inputs_.end() - kInputFeatures, inputs_.end());
    float* f = inputs_.data();
    f[0] = (float)((c & 0x01) != 0) - (float)((c & 0x02) != 0); // forward, back
    f[1] = (float)((c & 0x08) != 0) - (float)((c & 0x04) != 0); // up, down
    unsigned pressed = (unsigned)(c & ~prev_) >> 4;
    for (int b = 0; b < 4; b++)
        f[2 + b] = (float)((pressed >> b) & 1);
    prev_ = c;
}

uint8_t Player::Step(const float* view, bool actionable, bool deterministic)
{
    if (held_ > 0) {
        held_--;
        return bytes_;
    }
    if (!actionable)
        return 0;
    // efz_env.history.Delay.push: the view of `delay` decisions before (a match's first
    // view fills the past).
    const int delay = policy_->delay;
    if (fresh_) {
        for (int k = 0; k <= delay; k++)
            std::copy(view, view + kObsDim, seen_.begin() + (size_t)k * kObsDim);
        fresh_ = false;
    } else {
        std::copy_backward(seen_.begin(), seen_.end() - kObsDim, seen_.end());
        std::copy(view, view + kObsDim, seen_.begin());
    }
    std::copy(seen_.begin() + (size_t)delay * kObsDim, seen_.begin() + (size_t)(delay + 1) * kObsDim,
              in_.begin());
    std::copy(inputs_.begin(), inputs_.end(), in_.begin() + kObsDim);
    policy_->LogProbs(in_.data(), probs_.data());
    int n = policy_->Actions();
    int action = 0;
    if (deterministic) {
        action = (int)(std::max_element(probs_.begin(), probs_.end()) - probs_.begin());
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
    last_ = action;
    bytes_ = policy_->table[action];
    PushInput(bytes_);
    held_ = policy_->frameSkip - 1;
    return bytes_;
}

} // namespace agent
} // namespace efz
