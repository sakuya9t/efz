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
} kModules[] = {{"policy", 1}, {"routes", 1}, {"chooser", 1}, {"okiplan", 1},
               {"pressplan", 1}, {"airthrow", 1}};

int Hits(const float* view)
{
    return (int)nearbyintf(view[kComboHits] * 30);
}

const int kOppAction = 50;    // opp_action
const int kOppFrame = 51;     // opp_action_frame
const int kSelfHitstun = 20;  // self_hitstun

// A guard (src/efz.h: the guards, the air guard, the recoil guards).
bool IsGuard(int a)
{
    return (a >= 0x96 && a <= 0x9c) || (a >= 0xa8 && a <= 0xaa);
}

// The opponent is knocked down (src/efz.h: rising, the knockdowns, lying).
bool IsDown(const float* view)
{
    int a = (int)nearbyintf(view[kOppAction]);
    return a >= 0x60 && a <= 0x63;
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
        routes.ending = std::max(0, ToInt(keys, "route_ending", 0));
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

    // okiplan:1 (mix.h)
    mix = Mix();
    if (Has(names, "okiplan")) {
        if (frameSkip != 1 || delay <= 0 || history <= 0) {
            *error = "the agent's planned okizeme needs it to decide every frame, with a delay "
                     "and its input history";
            return false;
        }
        int count = ToInt(keys, "oki_entries", 0);
        Tensor offset, actions, dist, air, rise, moveAt, kind, victim, corner;
        Tensor wchar, wneeds, wpress, woffset, wbytes, ichar, iaction;
        if (!take("oki.offset", 1, 1, &offset) || !take("oki.actions", 2, 1, &actions) ||
            !take("oki.dist", 1, 1, &dist) || !take("oki.air", 2, 1, &air) ||
            !take("oki.rise", 1, 1, &rise) || !take("oki.move_at", 1, 1, &moveAt) ||
            !take("oki.kind", 1, 1, &kind) || !take("oki.victim", 1, 1, &victim) ||
            !take("oki.corner", 1, 1, &corner) || !take("oki.wake.character", 1, 1, &wchar) ||
            !take("oki.wake.needs", 1, 1, &wneeds) || !take("oki.wake.press", 1, 1, &wpress) ||
            !take("oki.wake.offset", 1, 1, &woffset) || !take("oki.wake.bytes", 2, 1, &wbytes) ||
            !take("oki.invincible.character", 1, 1, &ichar) ||
            !take("oki.invincible.action", 1, 1, &iaction))
            return false;
        size_t n = (size_t)std::max(0, count), steps = actions.u.size(), moves = wchar.i.size();
        bool fits = n > 0 && offset.i.size() == n + 1 && offset.i[0] == 0 &&
                    (size_t)offset.i[n] == steps && dist.i.size() == steps && air.u.size() == steps &&
                    rise.i.size() == n && moveAt.i.size() == n && kind.i.size() == n &&
                    victim.i.size() == n && corner.i.size() == n && wneeds.i.size() == moves &&
                    wpress.i.size() == moves && woffset.i.size() == moves + 1 &&
                    woffset.i[0] == 0 && (size_t)woffset.i[moves] == wbytes.u.size() &&
                    ichar.i.size() == iaction.i.size();
        for (size_t k = 0; fits && k < n; k++)
            fits = offset.i[k] <= offset.i[k + 1];
        for (size_t k = 0; fits && k < moves; k++)
            fits = woffset.i[k] <= woffset.i[k + 1] && wpress.i[k] >= 0;
        for (size_t k = 0; fits && k < steps; k++)
            fits = actions.u[k] < table.size();
        if (!fits) {
            *error = "the agent's okizeme library doesn't fit together";
            return false;
        }
        mix.entries.resize(n);
        for (size_t k = 0; k < n; k++) {
            Mix::Entry& e = mix.entries[k];
            e.begin = (uint32_t)offset.i[k];
            e.size = (uint32_t)(offset.i[k + 1] - offset.i[k]);
            e.rise = rise.i[k];
            e.moveAt = moveAt.i[k];
            e.kind = kind.i[k];
            e.victim = victim.i[k];
            e.corner = corner.i[k] != 0;
        }
        mix.actions = std::move(actions.u);
        mix.dist = std::move(dist.i);
        mix.air = std::move(air.u);
        mix.wake.resize(moves);
        for (size_t k = 0; k < moves; k++) {
            Mix::Reversal& m = mix.wake[k];
            m.character = wchar.i[k];
            m.needs = wneeds.i[k];
            m.press = wpress.i[k];
            m.bytes.assign(wbytes.u.begin() + woffset.i[k], wbytes.u.begin() + woffset.i[k + 1]);
        }
        mix.invincible.assign((size_t)Mix::kCharacters * Mix::kActs, 0);
        for (size_t k = 0; k < ichar.i.size(); k++) {
            int c = ichar.i[k], a = iaction.i[k];
            if (c >= 0 && c < Mix::kCharacters && a >= 0 && a < Mix::kActs)
                mix.invincible[(size_t)c * Mix::kActs + a] = 1;
        }
        const std::string& kindNames = keys["oki_kinds"];
        for (size_t at = 0; at <= kindNames.size();) {
            size_t end = kindNames.find('|', at);
            if (end == std::string::npos)
                end = kindNames.size();
            mix.kinds.push_back(kindNames.substr(at, end - at));
            at = end + 1;
        }
        mix.perPlan = std::max(1, ToInt(keys, "oki_per_plan", 6));
        mix.perClass = std::max(1, ToInt(keys, "oki_per_class", 2));
        mix.window = std::max(1, ToInt(keys, "oki_window", 45));
        mix.wait = std::max(0, ToInt(keys, "oki_wait", 40));
        mix.tolerance = std::max(0, ToInt(keys, "oki_tolerance", 24));
        mix.temperature = std::max(1e-6f, ToFloat(keys, "oki_temperature", 200));
        mix.doubt = std::min(1.0f, std::max(0.0f, ToFloat(keys, "oki_doubt", 0)));
        mix.hitWorth = ToFloat(keys, "oki_hit_worth", 1300);
        mix.hurtWorth = ToFloat(keys, "oki_hurt_worth", 1200);
        mix.prior = std::max(0.0f, ToFloat(keys, "oki_prior", 6));
        mix.decay = std::min(1.0f, std::max(0.0f, ToFloat(keys, "oki_decay", 0.7f)));
        mix.skip = std::min(1.0f, std::max(0.0f, ToFloat(keys, "oki_skip", 0)));
        mix.think = std::min(60, std::max(0, ToInt(keys, "oki_think", 0)));
        mix.source = keys["oki_source"];
    }

    // pressplan:1 (mix.h's Press)
    press = Press();
    if (Has(names, "pressplan")) {
        if (frameSkip != 1 || delay <= 0 || history <= 0) {
            *error = "the agent's planned pressure needs it to decide every frame, with a delay "
                     "and its input history";
            return false;
        }
        int count = ToInt(keys, "press_entries", 0);
        Tensor offset, actions, adv, distance, kind, victim, corner;
        Tensor rchar, rneeds, rpress, roffset, rbytes, ichar, iaction;
        if (!take("press.offset", 1, 1, &offset) || !take("press.actions", 2, 1, &actions) ||
            !take("press.adv", 1, 1, &adv) || !take("press.distance", 1, 1, &distance) ||
            !take("press.kind", 1, 1, &kind) || !take("press.victim", 1, 1, &victim) ||
            !take("press.corner", 1, 1, &corner) || !take("press.rev.character", 1, 1, &rchar) ||
            !take("press.rev.needs", 1, 1, &rneeds) || !take("press.rev.press", 1, 1, &rpress) ||
            !take("press.rev.offset", 1, 1, &roffset) || !take("press.rev.bytes", 2, 1, &rbytes) ||
            !take("press.invincible.character", 1, 1, &ichar) ||
            !take("press.invincible.action", 1, 1, &iaction))
            return false;
        size_t n = (size_t)std::max(0, count), steps = actions.u.size(), moves = rchar.i.size();
        bool fits = n > 0 && offset.i.size() == n + 1 && offset.i[0] == 0 &&
                    (size_t)offset.i[n] == steps && adv.i.size() == n && distance.i.size() == n &&
                    kind.i.size() == n && victim.i.size() == n && corner.i.size() == n &&
                    rneeds.i.size() == moves && rpress.i.size() == moves &&
                    roffset.i.size() == moves + 1 && roffset.i[0] == 0 &&
                    (size_t)roffset.i[moves] == rbytes.u.size() &&
                    ichar.i.size() == iaction.i.size();
        for (size_t k = 0; fits && k < n; k++)
            fits = offset.i[k] <= offset.i[k + 1];
        for (size_t k = 0; fits && k < moves; k++)
            fits = roffset.i[k] <= roffset.i[k + 1] && rpress.i[k] >= 0;
        for (size_t k = 0; fits && k < steps; k++)
            fits = actions.u[k] < table.size();
        if (!fits) {
            *error = "the agent's pressure library doesn't fit together";
            return false;
        }
        press.entries.resize(n);
        for (size_t k = 0; k < n; k++) {
            Press::Entry& e = press.entries[k];
            e.begin = (uint32_t)offset.i[k];
            e.size = (uint32_t)(offset.i[k + 1] - offset.i[k]);
            e.adv = adv.i[k];
            e.distance = distance.i[k];
            e.kind = kind.i[k];
            e.victim = victim.i[k];
            e.corner = corner.i[k] != 0;
        }
        press.actions = std::move(actions.u);
        press.reversals.resize(moves);
        for (size_t k = 0; k < moves; k++) {
            Mix::Reversal& m = press.reversals[k];
            m.character = rchar.i[k];
            m.needs = rneeds.i[k];
            m.press = rpress.i[k];
            m.bytes.assign(rbytes.u.begin() + roffset.i[k], rbytes.u.begin() + roffset.i[k + 1]);
        }
        press.invincible.assign((size_t)Mix::kCharacters * Mix::kActs, 0);
        for (size_t k = 0; k < ichar.i.size(); k++) {
            int c = ichar.i[k], a = iaction.i[k];
            if (c >= 0 && c < Mix::kCharacters && a >= 0 && a < Mix::kActs)
                press.invincible[(size_t)c * Mix::kActs + a] = 1;
        }
        const std::string& kindNames = keys["press_kinds"];
        for (size_t at = 0; at <= kindNames.size();) {
            size_t end = kindNames.find('|', at);
            if (end == std::string::npos)
                end = kindNames.size();
            press.kinds.push_back(kindNames.substr(at, end - at));
            at = end + 1;
        }
        press.perPlan = std::max(1, ToInt(keys, "press_per_plan", 4));
        press.perClass = std::max(1, ToInt(keys, "press_per_class", 2));
        press.window = std::max(1, ToInt(keys, "press_window", 40));
        press.wait = std::max(0, ToInt(keys, "press_wait", 24));
        press.tolerance = std::max(0, ToInt(keys, "press_tolerance", 16));
        press.slack = std::max(0, ToInt(keys, "press_slack", 2));
        press.near = std::max(1, ToInt(keys, "press_near", 160));
        press.maxWait = std::max(0, ToInt(keys, "press_max_wait", 20));
        press.temperature = std::max(1e-6f, ToFloat(keys, "press_temperature", 200));
        press.doubt = std::min(1.0f, std::max(0.0f, ToFloat(keys, "press_doubt", 0.3f)));
        press.hitWorth = ToFloat(keys, "press_hit_worth", 1300);
        press.hurtWorth = ToFloat(keys, "press_hurt_worth", 1200);
        press.prior = std::max(0.0f, ToFloat(keys, "press_prior", 8));
        press.skip = std::min(1.0f, std::max(0.0f, ToFloat(keys, "press_skip", 0.05f)));
        press.source = keys["press_source"];
    }

    // airthrow:1 (mix.h's Catch)
    air = Catch();
    if (Has(names, "airthrow")) {
        if (frameSkip != 1 || delay <= 0 || history <= 0) {
            *error = "the agent's air throw of a recovery needs it to decide every frame, with "
                     "a delay and its input history";
            return false;
        }
        air.on = true;
        air.near = std::max(1, ToInt(keys, "air_near", 320));
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
    wasDown_ = okiWanted_ = okiPending_ = okiOn_ = pressPending_ = false;
    throwWanted_ = throwPending_ = false;
    air_ = OkiStats();
    okiRoute_.clear();
    pressRest_.clear();
    okiAt_ = 0;
    nowAct_ = -1;
    nowFrame_ = 0;
    oki_ = OkiStats();
    press_ = OkiStats();
    if (mix_)
        mix_->Cancel();
    if (counted_) { // the match's end: the same opponent next, what it showed older
        counts_.End(policy_->mix.decay);
        counted_ = false;
    }
}

void Player::SetMix(MixPlanner* mix, int side, double patienceMs)
{
    const Policy& p = *policy_;
    if (mix && ((p.mix.Empty() && p.press.Empty() && !p.air.on) || p.frameSkip != 1 || p.delay <= 0 ||
                p.history <= 0))
        mix = nullptr;
    mix_ = mix;
    side_ = side;
    if (!planner_)
        patienceMs_ = patienceMs;
    counts_.Clear();
    counted_ = false;
    Reset();
}

// At its opponent's knockdown (as the game is): its inputs for the `delay` frames until it
// sees it, its own play's from what it will see then, and the plan asked for from where
// they leave the fight.
void Player::OkiBegin(const float* view, bool deterministic)
{
    (void)view;
    const int delay = policy_->delay;
    std::vector<float> hist = inputs_, in(in_.size());
    uint8_t prev = prev_;
    std::vector<int> actions;
    for (int k = 0; k < delay; k++) {
        std::copy(seen_.begin() + (size_t)(delay - k) * kObsDim,
                  seen_.begin() + (size_t)(delay - k + 1) * kObsDim, in.begin());
        std::copy(hist.begin(), hist.end(), in.begin() + kObsDim);
        int a = Sample(in.data(), deterministic);
        actions.push_back(a);
        Push(hist, prev, policy_->table[a]);
    }
    // (then a crouching guard while the planner works on: the plan is for after it)
    int guard = 0;
    for (int a = 0; a < policy_->Actions(); a++) {
        if (policy_->table[a] == 0x06)
            guard = a;
    }
    for (int k = 0; k < policy_->mix.think; k++) {
        actions.push_back(guard);
        Push(hist, prev, policy_->table[guard]);
    }
    double shares[kAnswers];
    counts_.Belief(policy_->mix.prior, shares);
    mix_->Begin(side_, actions, hist.data(), prev, deterministic, shares);
    queue_.assign(actions.begin(), actions.end());
    okiPending_ = true;
    okiWanted_ = false;
    okiOn_ = false;
    oki_.asked++;
}

// The plans due on this frame (the inputs chosen when they were asked for are played).
void Player::MixResults(const float* view)
{
    if (okiPending_ && queue_.empty())
        OkiResult(view);
    if (pressPending_ && queue_.empty())
        PressResult(view);
    if (throwPending_ && queue_.empty())
        ThrowResult(view);
}

// The plans to ask for on this frame, as the game is: its opponent's knockdown, planned
// for once no other plan or route is on, while it is still down; a move of its own
// touching the opponent's guard (a contact: the guard starts, or starts again), planned
// from unless a plan or a combo's route is on.
void Player::MixBegins(const float* view, bool deterministic)
{
    const Policy& p = *policy_;
    int act = (int)nearbyintf(view[kOppAction]), frame = (int)nearbyintf(view[kOppFrame]);
    bool contact = IsGuard(act) && (!IsGuard(nowAct_) || act != nowAct_ || frame < nowFrame_);
    // Its opponent recovering in the air out of a hit reaction (src/efz.h: 0x9d, 0x9e
    // from 0x32-0x5f): wanted from the frame it begins, while it lasts.
    bool recovering = act == 0x9d || act == 0x9e;
    throwWanted_ = p.air.on && recovering &&
        (throwWanted_ || (nowAct_ >= 0x32 && nowAct_ < 0x60));
    nowAct_ = act;
    nowFrame_ = frame;
    bool down = IsDown(view);
    okiWanted_ = !p.mix.Empty() && down && (okiWanted_ || !wasDown_);
    wasDown_ = down;
    bool busy = pending_ || okiPending_ || pressPending_ || throwPending_ || routeOn_ ||
        !queue_.empty();
    if (okiWanted_ && !busy) {
        OkiBegin(view, deterministic);
        return;
    }
    if (throwWanted_ && !busy && !(in_[kSelfHitstun] > 0)) {
        ThrowBegin(view, deterministic);
        return;
    }
    if (contact && !busy && !p.press.Empty() && !(in_[kSelfHitstun] > 0))
        PressBegin(view, deterministic);
}

// On the frame its opponent's air recovery begins (airplan.py's live_throw): its inputs for
// the `delay` frames until it sees the recovery, its own play's from what it will see, and
// the catch asked for from where they leave the fight.
void Player::ThrowBegin(const float* view, bool deterministic)
{
    (void)view;
    const int delay = policy_->delay;
    okiOn_ = false;
    std::vector<float> hist = inputs_, in(in_.size());
    uint8_t prev = prev_;
    std::vector<int> actions;
    for (int k = 0; k < delay; k++) {
        std::copy(seen_.begin() + (size_t)(delay - k) * kObsDim,
                  seen_.begin() + (size_t)(delay - k + 1) * kObsDim, in.begin());
        std::copy(hist.begin(), hist.end(), in.begin() + kObsDim);
        int a = Sample(in.data(), deterministic);
        actions.push_back(a);
        Push(hist, prev, policy_->table[a]);
    }
    mix_->BeginThrow(side_, actions, inputs_.data(), prev_, deterministic, policy_->air.near);
    queue_.assign(actions.begin(), actions.end());
    throwPending_ = true;
    throwWanted_ = false;
    air_.asked++;
}

// `delay` frames after the recovery began, the throw, if there is one that catches and
// the game is where it was planned from.
void Player::ThrowResult(const float* view)
{
    typedef MixPlanner::Clock Clock;
    throwPending_ = false;
    Clock::time_point t0 = Clock::now();
    bool done = mix_->Done();
    if (!done) {
        Clock::time_point until = patienceMs_ < 0 ? Clock::time_point::max()
            : t0 + std::chrono::duration_cast<Clock::duration>(
                       std::chrono::duration<double, std::milli>(patienceMs_));
        done = mix_->Work(until);
    }
    double waited = std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
    air_.waitedMs += waited;
    air_.waitedMsMost = std::max(air_.waitedMsMost, waited);
    if (!done) {
        mix_->Cancel();
        air_.late++;
        return;
    }
    air_.planMs += mix_->ms;
    air_.planMsMost = std::max(air_.planMsMost, mix_->ms);
    air_.frames += mix_->frames;
    MixPlanner::Outcome outcome = mix_->outcome;
    mix_->outcome = MixPlanner::kNone;
    if (outcome != MixPlanner::kPlanned) {
        (outcome == MixPlanner::kNothing ? air_.nothing : air_.apart)++;
        return;
    }
    for (int i = 0; i < kObsDim; i++) {
        if (!(mix_->view[i] == view[i])) {
            air_.elsewhere++;
            return;
        }
    }
    air_.plans++;
    air_.played++;
    okiRoute_ = mix_->option;
    okiAt_ = 0;
    okiOn_ = !okiRoute_.empty();
}

// On the frame a move of its own touches the opponent's guard (pressplan.py's live plan):
// its inputs for the `delay` frames until it sees the guard (what is left of a planned
// move's own first, then its own play's from what it will see), and the plan asked for.
void Player::PressBegin(const float* view, bool deterministic)
{
    const int delay = policy_->delay;
    std::vector<int> rest;
    if (okiOn_) {
        rest.assign(okiRoute_.begin() + okiAt_, okiRoute_.end());
        okiOn_ = false;
    }
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
    pressRest_.clear();
    if ((int)rest.size() > delay)
        pressRest_.assign(rest.begin() + delay, rest.end());
    double shares[kAnswers];
    counts_.PressBelief(policy_->press.prior, shares);
    int theirs = (int)nearbyintf(view[kOppAction]);
    bool crouching = (theirs >= 0x99 && theirs <= 0x9b) || theirs == 0xa9;
    // (its history as it is now: the planner pushes each input as it plays it)
    mix_->BeginPress(side_, actions, inputs_.data(), prev_, deterministic, shares,
                     crouching ? 0x06 : 0x02);
    queue_.assign(actions.begin(), actions.end());
    pressPending_ = true;
    press_.asked++;
}

// `delay` frames after the contact, the plan, if the game is where it was planned from;
// nothing planned: on with what was left of the planned move it was playing.
void Player::PressResult(const float* view)
{
    typedef MixPlanner::Clock Clock;
    pressPending_ = false;
    std::vector<int> rest;
    rest.swap(pressRest_);
    auto on = [&](const std::vector<int>& actions) {
        okiRoute_ = actions;
        okiAt_ = 0;
        okiOn_ = !actions.empty();
    };
    Clock::time_point t0 = Clock::now();
    bool done = mix_->Done();
    if (!done) {
        Clock::time_point until = patienceMs_ < 0 ? Clock::time_point::max()
            : t0 + std::chrono::duration_cast<Clock::duration>(
                       std::chrono::duration<double, std::milli>(patienceMs_));
        done = mix_->Work(until);
    }
    double waited = std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
    press_.waitedMs += waited;
    press_.waitedMsMost = std::max(press_.waitedMsMost, waited);
    if (!done) {
        mix_->Cancel();
        press_.late++;
        on(rest);
        return;
    }
    press_.planMs += mix_->ms;
    press_.planMsMost = std::max(press_.planMsMost, mix_->ms);
    press_.frames += mix_->frames;
    MixPlanner::Outcome outcome = mix_->outcome;
    mix_->outcome = MixPlanner::kNone;
    if (outcome != MixPlanner::kPlanned) {
        (outcome == MixPlanner::kNothing ? press_.nothing : press_.apart)++;
        on(rest);
        return;
    }
    for (int i = 0; i < kObsDim; i++) {
        if (!(mix_->view[i] == view[i])) {
            press_.elsewhere++;
            return;
        }
    }
    press_.plans++;
    int kinds = (int)policy_->press.kinds.size(), k = mix_->kinds[mix_->chosen];
    press_.drawn.resize((size_t)kinds + 2, 0);
    size_t slot = k == MixPlanner::kWait ? (size_t)kinds : k == MixPlanner::kOwnPlay
        ? (size_t)kinds + 1 : (size_t)std::min(std::max(k, 0), kinds - 1);
    press_.drawn[slot]++;
    if (k != MixPlanner::kOwnPlay)
        press_.played++;
    on(mix_->option);
}

// `delay` frames after the knockdown, the plan, if the game is where it was planned from.
void Player::OkiResult(const float* view)
{
    typedef MixPlanner::Clock Clock;
    okiPending_ = false;
    Clock::time_point t0 = Clock::now();
    bool done = mix_->Done();
    if (!done) {
        Clock::time_point until = patienceMs_ < 0 ? Clock::time_point::max()
            : t0 + std::chrono::duration_cast<Clock::duration>(
                       std::chrono::duration<double, std::milli>(patienceMs_));
        done = mix_->Work(until);
    }
    double waited = std::chrono::duration<double, std::milli>(Clock::now() - t0).count();
    oki_.waitedMs += waited;
    oki_.waitedMsMost = std::max(oki_.waitedMsMost, waited);
    if (!done) {
        mix_->Cancel();
        oki_.late++;
        return;
    }
    oki_.planMs += mix_->ms;
    oki_.planMsMost = std::max(oki_.planMsMost, mix_->ms);
    oki_.frames += mix_->frames;
    MixPlanner::Outcome outcome = mix_->outcome;
    mix_->outcome = MixPlanner::kNone;
    if (outcome != MixPlanner::kPlanned) {
        (outcome == MixPlanner::kNothing ? oki_.nothing : oki_.apart)++;
        return;
    }
    for (int i = 0; i < kObsDim; i++) {
        if (!(mix_->view[i] == view[i])) {
            oki_.elsewhere++;
            return;
        }
    }
    oki_.plans++;
    // (by kind: the library's, then the wait and its own play)
    int kinds = (int)policy_->mix.kinds.size(), k = mix_->kinds[mix_->chosen];
    oki_.drawn.resize((size_t)kinds + 2, 0);
    size_t slot = k == MixPlanner::kWait ? (size_t)kinds : k == MixPlanner::kOwnPlay
        ? (size_t)kinds + 1 : (size_t)std::min(std::max(k, 0), kinds - 1);
    oki_.drawn[slot]++;
    if (!mix_->option.empty()) {
        oki_.played++;
        okiRoute_ = mix_->option;
        okiAt_ = 0;
        okiOn_ = true;
    }
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
    if (routeOn_) {
        rest.assign(route_.begin() + routeAt_, route_.end());
    } else if (okiOn_) { // its okizeme hit: what is left of it, as a route it is on
        rest.assign(okiRoute_.begin() + okiAt_, okiRoute_.end());
        okiOn_ = false;
    }
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
    if (mix_) { // what it sees of its opponent, counted
        counts_.Update(in_.data(), policy_->mix.Empty() ? policy_->press.invincible
                                                         : policy_->mix.invincible);
        counted_ = true;
    }
    int action;
    if (!planner_ && !mix_) {
        action = Sample(in_.data(), deterministic);
    } else if (!planner_) {
        // Its okizeme and pressure planned, its combos its own.
        MixResults(view);
        MixBegins(view, deterministic);
        if (okiOn_ && (okiAt_ >= okiRoute_.size() || in_[kSelfHitstun] > 0))
            okiOn_ = false;
        if (!queue_.empty()) {
            action = queue_.front();
            queue_.pop_front();
        } else if (okiOn_) {
            action = okiRoute_[okiAt_++];
        } else {
            action = Sample(in_.data(), deterministic);
        }
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
        if (mix_)
            MixResults(view);
        if (routeOn_ && ((hits == 0 && routeAt_ > 0) || routeAt_ >= route_.size()))
            routeOn_ = false; // it ended, or dropped
        bool again = policy_->routes.replan ? !(planned_ && hitMove_ == plannedMove_)
                                            : prevHits_ == 0 && !routeOn_;
        // (a plan of the one kind while the other's inputs are being played waits)
        if (!pending_ && !okiPending_ && !pressPending_ && !throwPending_ && hits > 0 && again)
            Begin(view, deterministic);
        if (mix_) {
            MixBegins(view, deterministic);
            // What it planned: until its inputs end, it sees itself hit, or a route is on.
            if (okiOn_ && (okiAt_ >= okiRoute_.size() || in_[kSelfHitstun] > 0 || routeOn_))
                okiOn_ = false;
        }
        if (!queue_.empty()) {
            action = queue_.front();
            queue_.pop_front();
        } else if (routeOn_) {
            action = route_[routeAt_++];
        } else if (okiOn_) {
            action = okiRoute_[okiAt_++];
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
