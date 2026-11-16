// A trained agent's network and an agent playing one side (policy.h).
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <chrono>
#include <map>
#include <random>

#include "platform.h"
#include "agent/observe.h"
#include "agent/policy.h"
#include "agent/routes.h"

namespace efz {
namespace agent {

namespace {

const char kMagic[8] = {'E', 'F', 'Z', 'A', 'G', 'E', 'N', 'T'};
const uint32_t kFormat = 2;   // the newest format read (1 is read too)
const int kInputFeatures = 6; // per step of history: forward-back, up-down, A B C D pressed
const int kComboHits = 30;    // the view's self_combo_hits (/ 30)
const int kSelfAction = 18;   // self_action: the move that hit
const int kOppCharacter = 66; // opp_character

// The modules this game plays, each up to its version.
const struct {
    const char* name;
    int version;
} kModules[] = {{"policy", 1}, {"routes", 1}, {"chooser", 1}};

int Hits(const float* view)
{
    return (int)nearbyintf(view[kComboHits] * 30);
}

struct Tensor {
    int type = 0; // 0 float32, 1 int32, 2 uint8
    std::vector<uint32_t> dims;
    std::vector<float> f;
    std::vector<int32_t> i;
    std::vector<uint8_t> u;
    size_t Count() const
    {
        size_t n = 1;
        for (uint32_t d : dims)
            n *= d;
        return n;
    }
};

typedef std::map<std::string, std::string> Keys;
typedef std::map<std::string, Tensor> Tensors;

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

int ToInt(const Keys& keys, const std::string& key, int fallback)
{
    auto it = keys.find(key);
    return it == keys.end() || it->second.empty() ? fallback : atoi(it->second.c_str());
}

float ToFloat(const Keys& keys, const std::string& key, float fallback)
{
    auto it = keys.find(key);
    return it == keys.end() || it->second.empty() ? fallback : (float)strtod(it->second.c_str(), nullptr);
}

// The text's "key=value" lines.
Keys ReadKeys(const std::string& text)
{
    Keys keys;
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
    return keys;
}

std::string Playable()
{
    std::string s;
    for (const auto& m : kModules)
        s += (s.empty() ? "" : ", ") + std::string(m.name) + ":" + std::to_string(m.version);
    return s;
}

// A module list ("policy:1,routes:1"): its names, and the first module this game doesn't
// play, or not in that version ("" if it plays them all).
std::string Unplayable(const std::string& list, std::vector<std::string>* names)
{
    for (size_t at = 0; at < list.size();) {
        size_t end = list.find(',', at);
        if (end == std::string::npos)
            end = list.size();
        std::string item = list.substr(at, end - at);
        at = end + 1;
        if (item.empty())
            continue;
        size_t colon = item.find(':');
        std::string name = item.substr(0, colon);
        int version = colon == std::string::npos ? 1 : atoi(item.c_str() + colon + 1);
        names->push_back(name);
        bool known = false;
        for (const auto& m : kModules)
            known = known || (name == m.name && version >= 1 && version <= m.version);
        if (!known)
            return item;
    }
    return "";
}

bool Has(const std::vector<std::string>& names, const char* name)
{
    return std::find(names.begin(), names.end(), name) != names.end();
}

// A network of the file (policy.h's Net): its features (keys prefix + "features",
// tensors under tprefix + "features."), activation, hidden layers (keys prefix +
// "layers", tensors layer + ".K"), its output layer `outName`; it takes `width` numbers.
bool ReadNet(Net* net, const Keys& keys, Tensors& tensors, const std::string& prefix,
             const std::string& tprefix, const std::string& layer, const std::string& outName,
             int width, const std::string& whose, std::string* error)
{
    auto key = [&](const std::string& k) {
        auto it = keys.find(prefix + k);
        return it == keys.end() ? std::string() : it->second;
    };
    net->width = width;
    std::string features = key("features"), activation = key("activation");
    net->efzFeatures = features == "efz";
    if (!net->efzFeatures && features != "flat") {
        *error = whose + " features are '" + features + "': this game knows efz and flat";
        return false;
    }
    net->tanh = activation == "tanh";
    if (!net->tanh && activation != "relu") {
        *error = whose + " activation is '" + activation + "': this game knows relu and tanh";
        return false;
    }
    auto take = [&](const std::string& tname, int type, size_t dims, Tensor* out) {
        auto it = tensors.find(tname);
        if (it == tensors.end() || it->second.type != type || it->second.dims.size() != dims) {
            *error = "the agent file has no " + tname + " of the right shape";
            return false;
        }
        *out = std::move(it->second);
        tensors.erase(it);
        return true;
    };
    int in = width;
    if (net->efzFeatures) {
        net->selfAction = ToInt(keys, "self_action", 18);
        net->oppAction = ToInt(keys, "opp_action", 50);
        net->selfChar = ToInt(keys, "self_char", 34);
        net->oppChar = ToInt(keys, "opp_char", 66);
        net->actionVocab = ToInt(keys, "action_vocab", 1024);
        net->characters = ToInt(keys, "characters", 25);
        const std::string f = tprefix + "features.";
        Tensor cont, mean, scale, action, own, chr;
        if (!take(f + "cont", 1, 1, &cont) || !take(f + "mean", 0, 1, &mean) ||
            !take(f + "scale", 0, 1, &scale) || !take(f + "action", 0, 2, &action) ||
            !take(f + "own_action", 0, 2, &own) || !take(f + "char", 0, 2, &chr))
            return false;
        size_t n = cont.i.size();
        if (mean.f.size() != n || scale.f.size() != n ||
            action.dims[0] != (uint32_t)net->actionVocab ||
            own.dims[0] != (uint32_t)(net->actionVocab * net->characters) ||
            own.dims[1] != action.dims[1] || chr.dims[0] != (uint32_t)net->characters) {
            *error = whose + " features don't fit together";
            return false;
        }
        for (int32_t c : cont.i) {
            if (c < 0 || c >= width) {
                *error = whose + " features read past its view";
                return false;
            }
        }
        for (int c : {net->selfAction, net->oppAction, net->selfChar, net->oppChar}) {
            if (c < 0 || c >= width) {
                *error = whose + " features read past its view";
                return false;
            }
        }
        net->cont = std::move(cont.i);
        net->mean = std::move(mean.f);
        net->scale = std::move(scale.f);
        net->actionDim = (int)action.dims[1];
        net->charDim = (int)chr.dims[1];
        net->action = std::move(action.f);
        net->ownAction = std::move(own.f);
        net->chr = std::move(chr.f);
        in = (int)net->cont.size() + 4 * net->actionDim + 2 * net->charDim;
    }
    int layers = ToInt(keys, prefix + "layers", 0);
    if (layers < 0 || layers > 16) {
        *error = whose + " network has " + std::to_string(layers) + " layers";
        return false;
    }
    net->layers.assign(layers, Net::Dense());
    for (int k = 0; k <= layers; k++) {
        Net::Dense& d = k < layers ? net->layers[k] : net->out;
        std::string base = k < layers ? layer + "." + std::to_string(k) : outName;
        Tensor w, b;
        if (!take(base + ".weight", 0, 2, &w) || !take(base + ".bias", 0, 1, &b))
            return false;
        if (w.dims[1] != (uint32_t)in || b.dims[0] != w.dims[0]) {
            *error = whose + " layer " + base + " doesn't fit the one before";
            return false;
        }
        d.in = in;
        d.out = (int)w.dims[0];
        d.weight = std::move(w.f);
        d.bias = std::move(b.f);
        in = d.out;
    }
    return true;
}

// efz_env.history.InputHistory.push: the newest step first.
void Push(std::vector<float>& h, uint8_t& prev, uint8_t c)
{
    if (h.empty())
        return;
    std::copy_backward(h.begin(), h.end() - kInputFeatures, h.end());
    float* f = h.data();
    f[0] = (float)((c & 0x01) != 0) - (float)((c & 0x02) != 0); // forward, back
    f[1] = (float)((c & 0x08) != 0) - (float)((c & 0x04) != 0); // up, down
    unsigned pressed = (unsigned)(c & ~prev) >> 4;
    for (int b = 0; b < 4; b++)
        f[2 + b] = (float)((pressed >> b) & 1);
    prev = c;
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

bool Policy::Peek(const char* path, std::string* name, int* character, std::string* version,
                  std::string* error)
{
    FILE* f = OpenPath(path, "rb");
    if (!f) {
        *error = std::string("can't open ") + path;
        return false;
    }
    unsigned char head[16];
    bool ok = fread(head, 1, 16, f) == 16 && memcmp(head, kMagic, 8) == 0;
    uint32_t format = 0, size = 0;
    if (ok) {
        memcpy(&format, head + 8, 4);
        memcpy(&size, head + 12, 4);
        ok = format >= 1 && format <= kFormat && size < (1u << 20);
    }
    std::string text(ok ? size : 0, '\0');
    ok = ok && (size == 0 || fread(&text[0], 1, size, f) == size);
    fclose(f);
    if (!ok) {
        *error = format > kFormat ? "an agent file of format " + std::to_string(format) +
                                        ": a newer game plays it"
                                  : std::string("not an agent file");
        return false;
    }
    Keys keys = ReadKeys(text);
    *name = keys.count("name") ? keys["name"] : std::string("agent");
    *character = ToInt(keys, "character", -1);
    if (*character < -1 || *character >= kCharacters)
        *character = -1;
    *version = keys["version"];
    return true;
}

bool Policy::Parse(const unsigned char* data, size_t size, std::string* error)
{
    Reader r(data, size);
    char magic[8];
    uint32_t fileFormat = 0, textSize = 0, count = 0;
    if (!r.Bytes(magic, 8) || memcmp(magic, kMagic, 8) != 0) {
        *error = "not an agent file (export one with python/examples/export_agent.py)";
        return false;
    }
    if (!r.Get(&fileFormat) || fileFormat < 1 || fileFormat > kFormat) {
        *error = "an agent file of format " + std::to_string(fileFormat) + "; this game reads 1 to " +
                 std::to_string(kFormat) + (fileFormat > kFormat ? ": a newer game plays it" : "");
        return false;
    }
    format = (int)fileFormat;
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
    Keys keys = ReadKeys(text);
    Tensors tensors;
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
            type > 2 || ndim > 4) {
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
        } else if (type == 1) {
            t.i.resize(n);
            ok = r.Bytes(t.i.data(), n * 4);
        } else {
            t.u.resize(n);
            ok = r.Bytes(t.u.data(), n);
        }
        if (!ok) {
            *error = "the agent file is cut short";
            return false;
        }
        tensors[tname] = std::move(t);
    }

    // What it is made of: format 2 says; format 1 was the policy and perhaps its routes.
    int routeCount = ToInt(keys, "routes", 0);
    if (format >= 2) {
        modules = keys["modules"];
        if (modules.empty()) {
            *error = "the agent file doesn't say what it is made of (its modules)";
            return false;
        }
    } else {
        modules = routeCount > 0 ? "policy:1,routes:1" : "policy:1";
    }
    std::vector<std::string> names;
    std::string unplayable = Unplayable(modules, &names);
    if (!unplayable.empty()) {
        *error = "the agent has the module " + unplayable + ", which this game doesn't play (it "
                 "plays " + Playable() + "): a newer game does";
        return false;
    }
    bool hasRoutes = Has(names, "routes"), hasChooser = Has(names, "chooser");
    if (!Has(names, "policy") || hasRoutes != (routeCount > 0) || (hasChooser && !hasRoutes)) {
        *error = "the agent file's parts don't fit its modules (" + modules + ")";
        return false;
    }

    name = keys.count("name") ? keys["name"] : std::string("agent");
    version = keys["version"];
    about.clear();
    for (const auto& kv : keys) {
        if (kv.first.compare(0, 7, "source.") == 0 || kv.first == "exporter" ||
            kv.first == "exported" || kv.first == "dropped")
            about[kv.first] = kv.second;
    }
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

    // policy:1
    if (!ReadNet(&net_, keys, tensors, "", "", "pi", "action", width_, "the agent's", error))
        return false;
    if (net_.Outputs() != (int)table.size() || table.empty()) {
        *error = "the agent has " + std::to_string(net_.Outputs()) + " actions and " +
                 std::to_string(table.size()) + " control bytes for them";
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

    // routes:1 (routes.h)
    routes = Routes();
    if (hasRoutes) {
        if (frameSkip != 1 || delay <= 0 || history <= 0) {
            *error = "the agent's routes need it to decide every frame, with a delay and its "
                     "input history";
            return false;
        }
        Tensor starter, opponent, offset, actions;
        if (!take("routes.starter", 1, 1, &starter) || !take("routes.opponent", 1, 1, &opponent) ||
            !take("routes.offset", 1, 1, &offset) || !take("routes.actions", 2, 1, &actions))
            return false;
        if (starter.i.size() != (size_t)routeCount || opponent.i.size() != (size_t)routeCount ||
            offset.i.size() != (size_t)routeCount + 1 || offset.i[0] != 0 ||
            (size_t)offset.i[routeCount] != actions.u.size()) {
            *error = "the agent's routes don't fit together";
            return false;
        }
        for (int k = 0; k < routeCount; k++) {
            if (offset.i[k + 1] < offset.i[k]) {
                *error = "the agent's routes don't fit together";
                return false;
            }
            Routes::Route rt;
            rt.starter = starter.i[k];
            rt.opponent = opponent.i[k];
            rt.begin = (uint32_t)offset.i[k];
            rt.size = (uint32_t)(offset.i[k + 1] - offset.i[k]);
            routes.list.push_back(rt);
            routes.byStarter[rt.starter].push_back(k);
        }
        for (uint8_t a : actions.u) {
            if (a >= table.size()) {
                *error = "the agent's routes play actions it hasn't got";
                return false;
            }
        }
        routes.actions = std::move(actions.u);
        // The planner's pool: the file's (routes joined at their moves' hits, in the order
        // the planner takes them), else the routes themselves.
        int poolCount = ToInt(keys, "route_pool", 0);
        if (poolCount > 0) {
            Tensor route, at, by;
            if (!take("routes.pool.route", 1, 1, &route) || !take("routes.pool.at", 1, 1, &at) ||
                !take("routes.pool.starter", 1, 1, &by))
                return false;
            if (route.i.size() != (size_t)poolCount || at.i.size() != (size_t)poolCount ||
                by.i.size() != (size_t)poolCount) {
                *error = "the agent's routes don't fit together";
                return false;
            }
            for (int k = 0; k < poolCount; k++) {
                int rk = route.i[k];
                if (rk < 0 || rk >= routeCount || at.i[k] < 0 ||
                    (uint32_t)at.i[k] >= routes.list[rk].size) {
                    *error = "the agent's routes don't fit together";
                    return false;
                }
                routes.pool.push_back(Routes::Entry{rk, at.i[k]});
                routes.poolByStarter[by.i[k]].push_back(k);
            }
        } else {
            for (int k = 0; k < routeCount; k++) {
                routes.pool.push_back(Routes::Entry{k, 0});
                routes.poolByStarter[routes.list[k].starter].push_back(k);
            }
        }
        routes.perStart = std::max(1, ToInt(keys, "route_per_start", 12));
        routes.limit = std::max(1, ToInt(keys, "route_limit", 900));
        routes.byVictim = ToInt(keys, "route_by_victim", 0) != 0;
        routes.replan = ToInt(keys, "route_replan", 0) != 0;
        const std::string& victims = keys["route_victims"];
        for (size_t at = 0; at < victims.size();) {
            size_t end = victims.find(',', at);
            if (end == std::string::npos)
                end = victims.size();
            int c = atoi(victims.substr(at, end - at).c_str());
            if (c >= 0 && c < kCharacters)
                routes.victims.push_back(c);
            at = end + 1;
        }
        routes.source = keys["route_source"];
    }

    // chooser:1
    chooser = Chooser();
    if (hasChooser) {
        if (!ReadNet(&chooser.net, keys, tensors, "chooser_", "chooser.", "chooser.layer",
                     "chooser.out", width_, "the chooser's", error))
            return false;
        if (chooser.net.Outputs() != routeCount + 1) {
            *error = "the agent's chooser is of " + std::to_string(chooser.net.Outputs() - 1) +
                     " routes, its library of " + std::to_string(routeCount);
            return false;
        }
        chooser.perStart = std::max(1, ToInt(keys, "chooser_per_start", 12));
        chooser.margin = ToFloat(keys, "chooser_margin", 200);
    }
    return true;
}

void Net::Forward(const float* view, float* outputs) const
{
    auto apply = [](const Dense& d, const float* x, float* y) {
        for (int o = 0; o < d.out; o++) {
            const float* w = &d.weight[(size_t)o * d.in];
            double sum = 0;
            for (int i = 0; i < d.in; i++)
                sum += (double)w[i] * x[i];
            y[o] = (float)(sum + d.bias[o]);
        }
    };
    std::vector<float> x, y;
    if (efzFeatures) {
        // python/efz_env/policy.py's EfzFeatures.forward.
        x.reserve(cont.size() + 4 * actionDim + 2 * charDim);
        for (size_t i = 0; i < cont.size(); i++) {
            float v = (view[cont[i]] - mean[i]) * scale[i];
            x.push_back(std::min(10.0f, std::max(-10.0f, v)));
        }
        auto index = [&](int column, int count) {
            long v = (long)nearbyintf(view[column]);
            return (int)std::min<long>(count - 1, std::max<long>(0, v));
        };
        auto append = [&](const std::vector<float>& table, int row, int dim) {
            x.insert(x.end(), table.begin() + (size_t)row * dim, table.begin() + (size_t)(row + 1) * dim);
        };
        int pairs[2][2] = {{selfAction, selfChar}, {oppAction, oppChar}};
        for (auto& pair : pairs) {
            int act = index(pair[0], actionVocab);
            int c = index(pair[1], characters);
            append(action, act, actionDim);
            append(ownAction, c * actionVocab + act, actionDim);
        }
        append(chr, index(selfChar, characters), charDim);
        append(chr, index(oppChar, characters), charDim);
    } else {
        x.assign(view, view + width);
    }
    for (const Dense& d : layers) {
        y.resize(d.out);
        apply(d, x.data(), y.data());
        for (float& v : y)
            v = tanh ? tanhf(v) : std::max(0.0f, v);
        x.swap(y);
    }
    apply(out, x.data(), outputs);
}

void Policy::LogProbs(const float* view, float* out) const
{
    net_.Forward(view, out);
    int n = net_.Outputs();
    float most = *std::max_element(out, out + n);
    double sum = 0;
    for (int a = 0; a < n; a++)
        sum += exp((double)out[a] - most);
    float logSum = (float)(most + log(sum));
    for (int a = 0; a < n; a++)
        out[a] -= logSum;
}

// combo_net.NetPlanner.plan: of the routes redteam's route_pool takes (the whole routes of
// the starter, by the library's order; those landed on this opponent first if it was kept
// per victim; long enough to be played from `offset`; the first per_start), the one it
// says deals the most, if that is more than its own play by the margin.
int Policy::Choose(const float* in, int starter, int offset, std::vector<float>* values) const
{
    values->assign(chooser.net.Outputs(), 0.0f);
    if (chooser.Empty())
        return -1;
    chooser.net.Forward(in, values->data());
    for (float& v : *values)
        v *= 1000.0f;
    float own = values->back();
    auto it = routes.byStarter.find(starter);
    if (it == routes.byStarter.end())
        return -1;
    std::vector<int> order = it->second;
    if (routes.byVictim) {
        int victim = (int)nearbyintf(in[kOppCharacter]);
        std::stable_partition(order.begin(), order.end(),
                              [&](int r) { return routes.list[r].opponent == victim; });
    }
    int best = -1, taken = 0;
    for (int r : order) {
        if ((int)routes.list[r].size <= offset)
            continue;
        if (taken++ >= chooser.perStart)
            break;
        if (best < 0 || (*values)[r] > (*values)[best])
            best = r;
    }
    return best >= 0 && (*values)[best] > own + chooser.margin ? best : -1;
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
    queue_.clear();
    pending_ = pendingFirst_ = false;
    route_.clear();
    routeAt_ = 0;
    routeOn_ = false;
    kept_.clear();
    keptOn_ = false;
    planned_ = false;
    hitMove_ = hitAge_ = 0;
    prevHits_ = 0;
    stats_ = RouteStats();
    if (planner_)
        planner_->Cancel();
}

void Player::SetPlanner(Planner* planner, int side, double patienceMs, double againMs)
{
    const Policy& p = *policy_;
    if (planner && (p.routes.Empty() || p.frameSkip != 1 || p.delay <= 0 || p.history <= 0))
        planner = nullptr;
    planner_ = planner;
    side_ = side;
    patienceMs_ = patienceMs;
    againMs_ = patienceMs < 0 ? patienceMs : againMs;
    Reset();
}

void Player::PushInput(uint8_t c)
{
    Push(inputs_, prev_, c);
}

int Player::Sample(const float* in, bool deterministic)
{
    policy_->LogProbs(in, probs_.data());
    int n = policy_->Actions();
    if (deterministic)
        return (int)(std::max_element(probs_.begin(), probs_.end()) - probs_.begin());
    double u = std::uniform_real_distribution<double>(0.0, 1.0)(rng_), sum = 0;
    for (int a = 0; a < n; a++) {
        sum += exp((double)probs_[a]);
        if (u < sum)
            return a;
    }
    return n - 1;
}

// LiveRoutes._begin: at its hit (or hitAge_ frames after: a plan was awaited), its inputs
// for the `delay` frames until it sees the hit, chosen now: the route's it is on, then
// its own play's from what it will see then (the views it has); and the plan asked for,
// the rest of that route after them one of the options.
void Player::Begin(const float* view, bool deterministic)
{
    const int delay = policy_->delay;
    std::vector<int> rest;
    if (routeOn_)
        rest.assign(route_.begin() + routeAt_, route_.end());
    std::vector<float> hist = inputs_, in(in_.size());
    uint8_t prev = prev_;
    std::vector<int> actions;
    for (int k = 0; k < delay; k++) {
        int a;
        if (k < (int)rest.size()) {
            a = rest[k];
        } else {
            std::copy(seen_.begin() + (size_t)(delay - k) * kObsDim,
                      seen_.begin() + (size_t)(delay - k + 1) * kObsDim, in.begin());
            std::copy(hist.begin(), hist.end(), in.begin() + kObsDim);
            a = Sample(in.data(), deterministic);
        }
        actions.push_back(a);
        Push(hist, prev, policy_->table[a]);
    }
    stats_.again += planned_;
    pendingFirst_ = !planned_;
    waitMs_ = planned_ ? againMs_ : patienceMs_;
    keptOn_ = (int)rest.size() > delay;
    std::vector<int> extra;
    if (keptOn_)
        extra.assign(rest.begin() + delay, rest.end());
    kept_ = keptOn_ ? rest : std::vector<int>();
    planner_->Begin(side_, hitMove_, actions, hist.data(), prev, deterministic, view, hitAge_, extra);
    pendingMove_ = hitMove_;
    pendingOffset_ = delay + hitAge_;
    queue_.assign(actions.begin(), actions.end());
    pending_ = true;
    routeOn_ = false;
    planned_ = true;
    plannedMove_ = hitMove_;
}

// LiveRoutes._result: `delay` frames after its hit, the plan, if the game is where it was
// planned from and the combo goes on. Until a plan says otherwise, on with the route it
// was on; a combo's first plan late: the chooser's pick.
void Player::Result(const float* view)
{
    typedef Planner::Clock Clock;
    pending_ = false;
    Clock::time_point t0 = Clock::now();
    bool done = planner_->Done();
    if (!done) {
        Clock::time_point until = waitMs_ < 0 ? Clock::time_point::max()
            : t0 + std::chrono::duration_cast<Clock::duration>(
                       std::chrono::duration<double, std::milli>(waitMs_));
        done = planner_->Work(until);
    }
    double waited = std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
    stats_.waitedMs += waited;
    stats_.waitedMsMost = std::max(stats_.waitedMsMost, waited);
    int hits = Hits(view);
    bool kept = keptOn_;
    keptOn_ = false;
    if (hits > 0 && kept) {
        route_.swap(kept_);
        routeAt_ = (size_t)policy_->delay;
        routeOn_ = true;
    }
    kept_.clear();
    if (!done) {
        planner_->Cancel();
        stats_.late++;
        // (the chooser sees what the agent sees now: its hit)
        if (pendingFirst_ && hits > 0 && !policy_->chooser.Empty()) {
            int r = policy_->Choose(in_.data(), pendingMove_, pendingOffset_, &values_);
            if (r >= 0) {
                const Routes& routes = policy_->routes;
                const Routes::Route& rt = routes.list[r];
                route_.assign(routes.actions.begin() + rt.begin + pendingOffset_,
                              routes.actions.begin() + rt.begin + rt.size);
                routeAt_ = 0;
                routeOn_ = true;
                stats_.chooser++;
            }
        }
        return;
    }
    stats_.planMs += planner_->ms;
    stats_.planMsMost = std::max(stats_.planMsMost, planner_->ms);
    Planner::Outcome outcome = planner_->outcome;
    planner_->outcome = Planner::kNone;
    if (outcome == Planner::kOwn) {
        stats_.own++;
        return;
    }
    if (outcome != Planner::kPlanned) {
        stats_.apart++;
        return;
    }
    if (hits == 0) {
        stats_.over++;
        return;
    }
    for (int i = 0; i < kObsDim; i++) {
        if (!(planner_->expected[i] == view[i])) {
            stats_.elsewhere++;
            return;
        }
    }
    stats_.plans++;
    if (planner_->chosen >= 0) {
        stats_.routes++;
        route_ = planner_->route;
        routeAt_ = 0;
        routeOn_ = true;
    } else {
        routeOn_ = false;
    }
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
    int action;
    if (!planner_) {
        action = Sample(in_.data(), deterministic);
    } else {
        // LiveRoutes.__call__: the inputs chosen at its hit, then the route chosen (until
        // its actions run out or the combo is over), else its own play; a hit of its own
        // (its combo counter, as the game is) starts a plan: the combo's first, and with
        // replan each new move's.
        int hits = Hits(view);
        if (hits > prevHits_) {
            hitMove_ = (int)nearbyintf(view[kSelfAction]);
            hitAge_ = 0;
        } else {
            hitAge_++;
        }
        if (hits == 0)
            planned_ = false;
        if (pending_ && queue_.empty())
            Result(view);
        if (routeOn_ && ((hits == 0 && routeAt_ > 0) || routeAt_ >= route_.size()))
            routeOn_ = false; // it ended, or dropped
        bool again = policy_->routes.replan ? !(planned_ && hitMove_ == plannedMove_)
                                            : prevHits_ == 0 && !routeOn_;
        if (!pending_ && hits > 0 && again)
            Begin(view, deterministic);
        if (!queue_.empty()) {
            action = queue_.front();
            queue_.pop_front();
        } else if (routeOn_) {
            action = route_[routeAt_++];
        } else {
            action = Sample(in_.data(), deterministic);
        }
        prevHits_ = hits;
    }
    last_ = action;
    bytes_ = policy_->table[action];
    PushInput(bytes_);
    held_ = policy_->frameSkip - 1;
    return bytes_;
}

} // namespace agent
} // namespace efz
