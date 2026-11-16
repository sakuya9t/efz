// What the headless library (port/headless/, docs/headless.md) relies on, checked
// without the game's data, so that it runs in CI (ctest -L headless):
//
// - an arena's bytes are its whole heap: copied into another arena (LoadArena), the
//   same allocations and frees give the same handles and the same contents there;
// - arenas bound on different threads at once don't touch each other, and operator new
//   outside a game takes from the C library's heap;
// - a sprite loaded without drawing (efz::Drawing false) takes as many bytes of its
//   .dat stream and has the same first pixel (the colour key the game keeps) as one
//   decoded whole, for random raw and run-length coded images;
// - the C API's structures have the sizes python/efz_env/_native.py declares, and a
//   batch without game data fails with a message;
// - an agent file (port/agent/policy.h) is read and its network run, and an agent plays
//   a side as play.py's HumanMatch runs one: its decisions held frame_skip frames,
//   nothing pressed while the controls do nothing, the game seen `delay` decisions late,
//   its own inputs at once; a file cut short is refused; its modules (format 2) are
//   checked, one this game doesn't play refused by name, and a format 1 file still read;
// - its routes are planned (port/agent/routes.h) and played as LiveRoutes plays them: at
//   the first hit, and with replan again at each new move's hit (the rest of the route
//   one of the options, routes joined where that move hit in them); a plan dropped when
//   the game is elsewhere or the plan late, the chooser's pick played for a late first
//   plan.
//
// The game itself, with its data, is the compatibility suite's (tools/compat.py check
// runs it in both the game and the headless runner).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <chrono>
#include <deque>
#include <map>
#include <random>
#include <string>
#include <thread>
#include <vector>

#include "efz.h"
#include "efz_env.h"
#include "headless.h"
#include "agent/observe.h"
#include "agent/policy.h"
#include "agent/routes.h"

using namespace efz;

namespace {

int g_failures;

#define CHECK(cond)                                                                    \
    do {                                                                               \
        if (!(cond)) {                                                                 \
            fprintf(stderr, "%s:%d: failed: %s\n", __FILE__, __LINE__, #cond);         \
            g_failures++;                                                              \
        }                                                                              \
    } while (0)

uint32_t Next(uint64_t& s)
{
    s ^= s << 13;
    s ^= s >> 7;
    s ^= s << 17;
    return (uint32_t)(s >> 11);
}

// A heap workload: blocks of random sizes allocated and freed at random, each filled
// with bytes that depend on its handle. Its record lives outside any arena.
struct Workload {
    static const int kSlots = 256;
    uint32_t handle[kSlots];
    uint32_t size[kSlots];
    uint64_t rng;

    explicit Workload(uint64_t seed) : rng(seed) { memset(handle, 0, sizeof(handle)); }

    // `ops` steps in the bound arena; the handles each allocation gave go to `log`.
    void Run(int ops, uint32_t* log)
    {
        for (int i = 0; i < ops; i++) {
            int k = Next(rng) % kSlots;
            if (handle[k]) {
                delete[] (char*)Ptr(handle[k]);
                handle[k] = 0;
                log[i] = 0;
                continue;
            }
            size[k] = 1 + Next(rng) % (Next(rng) % 8 == 0 ? 200000 : 2000);
            char* p = new char[size[k]];
            bool zero = true;
            for (uint32_t j = 0; j < size[k]; j++)
                zero &= p[j] == 0;
            CHECK(zero); // the arena hands out zeroed memory
            handle[k] = Handle(p);
            for (uint32_t j = 0; j < size[k]; j++)
                p[j] = (char)(handle[k] * 31 + j);
            log[i] = handle[k];
        }
    }

    // Every live block holds what was written into it, in the bound arena.
    bool Intact() const
    {
        for (int k = 0; k < kSlots; k++) {
            if (!handle[k])
                continue;
            const char* p = Ptr(handle[k]);
            for (uint32_t j = 0; j < size[k]; j++) {
                if (p[j] != (char)(handle[k] * 31 + j))
                    return false;
            }
        }
        return true;
    }
};

const int kOps = 4000;
uint32_t g_logA[kOps], g_logB[kOps];

void TestArenaCopy()
{
    int mark;
    SetStack(&mark);
    char* a = NewArena();
    char* b = NewArena();
    BindArena(a);
    Workload w(1);
    w.Run(kOps, g_logA);
    CHECK(w.Intact());
    // Copy a into b: the same game there.
    uintptr_t used = ArenaUsed();
    BindArena(b);
    LoadArena(a, used);
    CHECK(ArenaUsed() == used);
    CHECK(w.Intact());
    // The same workload goes on in both: the same handles, the same contents.
    Workload wa = w, wb = w;
    BindArena(a);
    wa.Run(kOps, g_logA);
    CHECK(wa.Intact());
    BindArena(b);
    wb.Run(kOps, g_logB);
    CHECK(wb.Intact());
    CHECK(memcmp(g_logA, g_logB, sizeof(g_logA)) == 0);
    BindArena(a);
    uintptr_t usedA = ArenaUsed();
    BindArena(b);
    CHECK(ArenaUsed() == usedA);
    BindArena(nullptr);
    FreeArena(a);
    FreeArena(b);
}

void TestThreads()
{
    // Two threads, each its own arena, the same workload at once: the same handles.
    uint32_t logs[2][kOps];
    bool intact[2];
    auto work = [&](int t) {
        int mark;
        SetStack(&mark);
        char* arena = NewArena();
        BindArena(arena);
        Workload w(7);
        w.Run(kOps, logs[t]);
        intact[t] = w.Intact();
        BindArena(nullptr);
        FreeArena(arena);
    };
    BindArena(nullptr);
    std::thread t0(work, 0), t1(work, 1);
    t0.join();
    t1.join();
    CHECK(intact[0] && intact[1]);
    CHECK(memcmp(logs[0], logs[1], sizeof(logs[0])) == 0);

    // Outside a game, operator new is the C library's.
    char* arena = NewArena();
    BindArena(nullptr);
    char* p = new char[64];
    CHECK((uintptr_t)p - (uintptr_t)arena >= g_arenaSize);
    delete[] p;
    FreeArena(arena);
}

// A random .dat image: width, height, then raw pixels or a run-length stream (a byte up
// to `rle` is a pixel; a higher one repeats the last pixel for itself and byte - rle - 1
// more), then bytes of the next image.
size_t MakeImage(uint8_t* out, uint64_t& rng, BYTE rle)
{
    int w = Next(rng) % 5 == 0 ? 0 : Next(rng) % 45;
    int h = Next(rng) % 5 == 0 ? 0 : Next(rng) % 33;
    size_t n = 0;
    out[n++] = (uint8_t)w;
    out[n++] = (uint8_t)(w >> 8);
    out[n++] = (uint8_t)h;
    out[n++] = (uint8_t)(h >> 8);
    long pixels = (long)w * h;
    if (rle == 0) {
        for (long i = 0; i < pixels; i++)
            out[n++] = (uint8_t)Next(rng);
    } else {
        for (long covered = 0; covered < pixels;) {
            if (Next(rng) % 3 == 0) {
                uint8_t b = (uint8_t)(rle + 1 + Next(rng) % (255 - rle));
                out[n++] = b;
                covered += b - rle;
            } else {
                out[n++] = (uint8_t)(Next(rng) % (rle + 1));
                covered++;
            }
        }
    }
    for (int i = 0; i < 16; i++)
        out[n++] = (uint8_t)Next(rng);
    return n;
}

void TestSprites()
{
    int mark;
    SetStack(&mark);
    char* arena = NewArena();
    BindArena(arena);
    CGraphics* graphics = new CGraphics;
    static uint8_t data[1 << 16];
    uint64_t rng = 99;
    const BYTE rles[] = {0, 81, 128, 200};
    int images = 0;
    for (int i = 0; i < 4000; i++) {
        BYTE rle = rles[i % 4];
        BYTE base = (BYTE)Next(rng);
        bool high = Next(rng) & 1;
        MakeImage(data, rng, rle);
        PTR32(IDirectDrawSurface) whole, sparse;
        G()->drawing = 1;
        int took = high ? graphics->LoadSurfaceHigh(&whole, data, rle, base)
                        : graphics->LoadSurface(&whole, data, rle, base);
        G()->drawing = 0;
        int skipped = high ? graphics->LoadSurfaceHigh(&sparse, data, rle, base)
                           : graphics->LoadSurface(&sparse, data, rle, base);
        CHECK(took == skipped);
        CHECK(whole->width == sparse->width && whole->height == sparse->height);
        CHECK(graphics->GetColorKey(whole) == graphics->GetColorKey(sparse));
        if (took != skipped || graphics->GetColorKey(whole) != graphics->GetColorKey(sparse)) {
            fprintf(stderr, "  image %d: %dx%d rle %d: %d vs %d bytes\n", i, whole->width,
                    whole->height, rle, took, skipped);
            break;
        }
        whole->Release();
        sparse->Release();
        images++;
    }
    printf("sprites: %d random images load the same drawn and not\n", images);
    BindArena(nullptr);
    FreeArena(arena);
}

void TestApi()
{
    // python/efz_env/_native.py declares the same.
    CHECK(sizeof(EfzEnvConfig) == 72);
    CHECK(sizeof(EfzMatch) == 20);
    CHECK(sizeof(EfzInfo) == 36);
    CHECK(sizeof(EfzBuffers) == 6 * sizeof(void*));
    CHECK(sizeof(EfzSoundEvent) == 60);
    CHECK(sizeof(EfzAgentInfo) == 11 * 4 + 3 * 64);
    CHECK(sizeof(EfzPlan) == 16 + 3 * 64 * 4 + 168 * 4 + 8);
    CHECK(efz_env_version() == EFZ_ENV_VERSION);
    int dim = efz_env_obs_dim();
    CHECK(dim == 168);
    for (int i = 0; i < dim; i++) {
        const char* name = efz_env_obs_name(i);
        CHECK(name && *name);
        for (int j = 0; name && j < i; j++)
            CHECK(strcmp(name, efz_env_obs_name(j)) != 0);
    }
    CHECK(efz_env_obs_name(dim) == nullptr);
    CHECK(strcmp(efz_env_character_name(1), "ayu") == 0);
    char error[256] = "";
    EfzEnvConfig config;
    efz_env_default_config(&config);
    CHECK(config.autoreset == EFZ_AUTORESET_SAME_STEP);
    config.num_envs = 2;
    CHECK(efz_env_create("no-such-efz-folder", &config, error, sizeof(error)) == nullptr);
    CHECK(strstr(error, "no game data") != nullptr);
    config.autoreset = 3;
    CHECK(efz_env_create("no-such-efz-folder", &config, error, sizeof(error)) == nullptr);
    CHECK(strstr(error, "autoreset") != nullptr);
    CHECK(efz_env_seed(nullptr, 0, 1) == -1);
}

// An agent file of a network without hidden layers: logit 0 = 2 * view[5] (the global
// "dx"... any column) + bias[0], logit 1 = view[kObsDim] (its last input's forward-back) *
// 3 + bias[1], and the others' their bias. table: each action's control byte.
// routes: each route's actions and its starter (none: an agent without routes). pool: the
// planner's entries (route, at, starter), none: the routes. chooser: what the chooser says
// each route and its own play would deal (thousands of HP), whatever it sees (none: no
// chooser). format 1 or 2; modules: format 2's (empty: those it has).
struct Tiny {
    int frameSkip = 1, history = 1, delay = 0;
    std::vector<uint8_t> table = {0x01, 0x10};
    std::vector<float> bias = {0.5f, 0.0f};
    std::vector<std::vector<uint8_t>> routes;
    std::vector<int> starters; // (default 5)
    std::vector<std::vector<int>> pool;
    bool replan = false;
    std::vector<float> chooser;
    int format = 1;
    std::string modules;
};

std::vector<unsigned char> TinyFile(const Tiny& t)
{
    using efz::agent::kObsDim;
    int width = kObsDim + 6 * t.history;
    uint32_t actions = (uint32_t)t.table.size();
    std::string table;
    for (uint8_t c : t.table) {
        char hex[3];
        snprintf(hex, sizeof(hex), "%02x", c);
        table += hex;
    }
    std::string text = "name=tiny\ncharacter=1\nframe_skip=" + std::to_string(t.frameSkip) +
                       "\nhistory=" + std::to_string(t.history) + "\ndelay=" +
                       std::to_string(t.delay) + "\nwidth=" + std::to_string(width) +
                       "\nactions=" + std::to_string(actions) + "\ntable=" + table +
                       "\nfeatures=flat\nactivation=relu\nlayers=0\n";
    if (!t.routes.empty())
        text += "routes=" + std::to_string(t.routes.size()) + "\nroute_per_start=12\n"
                "route_limit=900\nroute_by_victim=0\nroute_victims=\nroute_replan=" +
                std::to_string(t.replan) + "\nroute_pool=" + std::to_string(t.pool.size()) + "\n";
    if (!t.chooser.empty())
        text += "chooser_features=flat\nchooser_activation=relu\nchooser_layers=0\n"
                "chooser_per_start=12\nchooser_margin=200\n";
    if (t.format >= 2) {
        std::string modules = t.modules;
        if (modules.empty())
            modules = std::string("policy:1") + (t.routes.empty() ? "" : ",routes:1") +
                      (t.chooser.empty() ? "" : ",chooser:1");
        if (modules != "none")
            text += "modules=" + modules + "\n";
        text += "version=test\nsource.model=model.zip sha256:00\n";
    }
    std::vector<unsigned char> b;
    auto put = [&](const void* p, size_t n) {
        b.insert(b.end(), (const unsigned char*)p, (const unsigned char*)p + n);
    };
    auto u32 = [&](uint32_t v) { put(&v, 4); };
    put("EFZAGENT", 8);
    u32((uint32_t)t.format);
    u32((uint32_t)text.size());
    put(text.data(), text.size());
    u32(2 + (t.routes.empty() ? 0 : 4) + (t.pool.empty() ? 0 : 3) + (t.chooser.empty() ? 0 : 2));
    auto header = [&](const char* name, unsigned char type, std::vector<uint32_t> dims) {
        uint16_t n = (uint16_t)strlen(name);
        put(&n, 2);
        put(name, n);
        unsigned char ndim = (unsigned char)dims.size();
        put(&type, 1);
        put(&ndim, 1);
        for (uint32_t d : dims)
            u32(d);
    };
    auto tensor = [&](const char* name, std::vector<uint32_t> dims, const std::vector<float>& v) {
        header(name, 0, dims);
        put(v.data(), v.size() * 4);
    };
    auto ints = [&](const char* name, const std::vector<int32_t>& v) {
        header(name, 1, {(uint32_t)v.size()});
        put(v.data(), v.size() * 4);
    };
    std::vector<float> w(actions * width, 0.0f);
    w[5] = 2.0f;
    if (t.history)
        w[width + kObsDim] = 3.0f;
    tensor("action.weight", {actions, (uint32_t)width}, w);
    std::vector<float> bias = t.bias;
    bias.resize(actions, -100.0f);
    tensor("action.bias", {actions}, bias);
    if (!t.routes.empty()) {
        uint32_t n = (uint32_t)t.routes.size();
        std::vector<int32_t> starter(n, 5), opponent(n, -1), offset(1, 0);
        for (size_t k = 0; k < t.starters.size() && k < n; k++)
            starter[k] = t.starters[k];
        std::vector<uint8_t> acts;
        for (const auto& r : t.routes) {
            acts.insert(acts.end(), r.begin(), r.end());
            offset.push_back((int32_t)acts.size());
        }
        ints("routes.starter", starter);
        ints("routes.opponent", opponent);
        ints("routes.offset", offset);
        header("routes.actions", 2, {(uint32_t)acts.size()});
        put(acts.data(), acts.size());
    }
    if (!t.pool.empty()) {
        std::vector<int32_t> route, at, by;
        for (const auto& e : t.pool) {
            route.push_back(e[0]);
            at.push_back(e[1]);
            by.push_back(e[2]);
        }
        ints("routes.pool.route", route);
        ints("routes.pool.at", at);
        ints("routes.pool.starter", by);
    }
    if (!t.chooser.empty()) {
        uint32_t n = (uint32_t)t.chooser.size();
        tensor("chooser.out.weight", {n, (uint32_t)width}, std::vector<float>(n * width, 0.0f));
        tensor("chooser.out.bias", {n}, t.chooser);
    }
    return b;
}

std::vector<unsigned char> TinyAgent(int frameSkip, int history, int delay,
                                     const std::vector<std::vector<uint8_t>>& routes = {})
{
    Tiny t;
    t.frameSkip = frameSkip;
    t.history = history;
    t.delay = delay;
    t.routes = routes;
    return TinyFile(t);
}

// A game of a few numbers for the routes' planner: player 0's button hits (A 100 HP, move
// 5; B 300, move 6; C as A, move 7) and its combo goes on; `drop` frames in a row without
// one drop the combo. The view shows its combo's hits, the move that hit last and the
// frame; `twist` adds what player 1 pressed last, so that a plan made with it holding
// back finds the game elsewhere.
class FakeWorld : public efz::agent::World {
public:
    struct State {
        int frame = 0, hits = 0, idle = 0, hp = 1000000, oppLast = 0, move = 5;
        uint8_t last[2] = {0, 0};
    } g;
    bool twist = false;
    int drop = 2;
    int steps = 0;

    void Save(efz::agent::Snapshot* s) override
    {
        s->bytes.assign((const char*)&g, (const char*)&g + sizeof(g));
        s->valid = true;
    }
    bool Load(const efz::agent::Snapshot& s) override
    {
        if (!s.valid || s.bytes.size() != sizeof(g))
            return false;
        memcpy(&g, s.bytes.data(), sizeof(g));
        return true;
    }
    bool Step(const uint8_t input[2]) override
    {
        steps++;
        g.frame++;
        g.last[0] = input[0];
        g.last[1] = input[1];
        g.oppLast = input[1];
        if (input[0] & 0xf0) {
            g.hits++;
            g.hp -= input[0] & 0x20 ? 300 : 100;
            g.move = input[0] & 0x20 ? 6 : input[0] & 0x40 ? 7 : 5;
            g.idle = 0;
        } else if (g.hits > 0 && ++g.idle >= drop) {
            g.hits = 0;
        }
        return true;
    }
    void View(int, float* out) override
    {
        memset(out, 0, efz::agent::kObsDim * sizeof(float));
        out[30] = g.hits / 30.0f;
        out[18] = (float)g.move;
        out[1] = (float)g.frame;
        if (twist)
            out[100] = (float)g.oppLast;
    }
    int Facing(int) override { return 1; }
    int Hp(int p) override { return p == 1 ? g.hp : 9999; }
    int ComboHits(int p) override { return p == 0 ? g.hits : 0; }
    uint8_t Read(int p) override { return g.last[p]; }
    bool Over() override { return g.hp <= 0; }
};

void TestRoutes()
{
    using efz::agent::kObsDim;
    std::string error;
    // Route 0: A every frame (100 a frame); route 1: forward only (drops at once). Its
    // own play alternates forward and A (100 every other frame) for as long as the longest
    // route and a second more: route 0 is chosen.
    std::vector<uint8_t> allA(400, 1), forward(40, 0);
    std::vector<unsigned char> file = TinyAgent(1, 1, 2, {allA, forward});
    efz::agent::Policy p;
    CHECK(p.Parse(file.data(), file.size(), &error));
    CHECK(p.routes.list.size() == 2 && p.routes.byStarter[5].size() == 2);

    // The agent, as the game plays it: each frame its view, its byte, the frame run with
    // the opponent holding back (left: 0x02, facing right).
    auto play = [&](FakeWorld& world, efz::agent::Player& a, int frames, std::vector<uint8_t>* out) {
        float view[kObsDim];
        for (int f = 0; f < frames; f++) {
            world.View(0, view);
            uint8_t input[2] = {a.Step(view, true, true), 0x02};
            if (world.twist && f % 2)
                input[1] = 0x04;
            out->push_back(input[0]);
            world.Step(input);
        }
    };
    {
        FakeWorld world;
        efz::agent::Planner planner(&p, &world, 3);
        efz::agent::Player a(&p, 7);
        a.SetPlanner(&planner, 0, -1);
        CHECK(a.Planning());
        std::vector<uint8_t> out;
        play(world, a, 40, &out);
        // forward, A (the hit), then the two inputs chosen at the hit (forward, A), then
        // route 0 from its third action: A.
        CHECK(out[0] == 0x01 && out[1] == 0x10 && out[2] == 0x01 && out[3] == 0x10);
        for (int f = 4; f < 40; f++)
            CHECK(out[f] == 0x10);
        CHECK(a.Stats().plans == 1 && a.Stats().routes == 1 && a.Stats().dropped() == 0);
        CHECK(planner.tried.size() == 3 && planner.tried[2] == -1);
        CHECK(planner.dealt[0] > planner.dealt[2] && planner.dealt[1] == 0);
        // The real game is as the agent's inputs left it: the planner's copies didn't
        // reach it (its HP: 100 a hit landed, here).
        int hits = 0;
        for (uint8_t b : out)
            hits += (b & 0xf0) != 0;
        CHECK(world.g.hp == 1000000 - 100 * hits);
    }
    {
        // The opponent did something else than hold back: the game isn't where the plan
        // expected, and the agent plays on by itself.
        FakeWorld world;
        world.twist = true;
        efz::agent::Planner planner(&p, &world, 3);
        efz::agent::Player a(&p, 7);
        a.SetPlanner(&planner, 0, -1);
        std::vector<uint8_t> out;
        play(world, a, 12, &out);
        CHECK(a.Stats().plans == 0 && a.Stats().elsewhere == 1);
        CHECK(out[4] == 0x01); // its own play again: forward after A
    }
    {
        // No time to plan (patience 0, no work between frames): dropped as late.
        FakeWorld world;
        efz::agent::Planner planner(&p, &world, 3);
        efz::agent::Player a(&p, 7);
        a.SetPlanner(&planner, 0, 0);
        std::vector<uint8_t> out;
        play(world, a, 12, &out);
        CHECK(a.Stats().plans == 0 && a.Stats().late == 1);
    }
    {
        // Worked on in pieces, as between the game's frames: the same plan.
        FakeWorld world;
        efz::agent::Planner planner(&p, &world, 3);
        efz::agent::Player a(&p, 7);
        a.SetPlanner(&planner, 0, -1);
        float view[kObsDim];
        std::vector<uint8_t> out;
        for (int f = 0; f < 40; f++) {
            world.View(0, view);
            uint8_t input[2] = {a.Step(view, true, true), 0x02};
            out.push_back(input[0]);
            world.Step(input);
            // a piece of work: a deadline already past still plays a frame's prelude,
            // then a few frames at a time.
            for (int k = 0; k < 3 && planner.Busy(); k++)
                planner.Work(efz::agent::Planner::Clock::now() + std::chrono::microseconds(30));
        }
        CHECK(a.Stats().plans == 1 && a.Stats().routes == 1);
        for (int f = 4; f < 40; f++)
            CHECK(out[f] == 0x10);
    }
    // An agent without a delay can't have routes.
    file = TinyAgent(1, 1, 0, {allA});
    efz::agent::Policy q;
    CHECK(!q.Parse(file.data(), file.size(), &error) && error.find("routes") != std::string::npos);
    printf("routes: planned, played, dropped when the game is elsewhere or the plan late\n");
}

// Round 15b's replanning, and the chooser for a first plan late. The agent's own play is
// A every frame (100 a frame); B deals 300 and is another move (6). Route 0: A x 4, then
// B x 100; route 1: A x 3, then B x `tail`, joined where its B first hit (step 3, move 6).
void TestReplan()
{
    using efz::agent::kObsDim;
    typedef efz::agent::Planner Planner;
    std::string error;
    auto make = [](int tail) {
        Tiny t;
        t.history = 1;
        t.delay = 2;
        t.table = {0x01, 0x10, 0x20};
        t.bias = {-100.0f, 5.0f, -100.0f};
        std::vector<uint8_t> r0(4, 1), r1(3, 1);
        r0.resize(104, 2);
        r1.resize(3 + tail, 2);
        t.routes = {r0, r1};
        t.pool = {{0, 0, 5}, {1, 3, 6}};
        t.replan = true;
        t.format = 2;
        return t;
    };
    auto play = [&](FakeWorld& world, efz::agent::Player& a, int frames, std::vector<uint8_t>* out) {
        float view[kObsDim];
        for (int f = 0; f < frames; f++) {
            world.View(0, view);
            uint8_t input[2] = {a.Step(view, true, true), 0x02};
            out->push_back(input[0]);
            world.Step(input);
        }
    };
    auto run = [&](const efz::agent::Policy& p, double patience, double again, int frames,
                   std::vector<uint8_t>* out, Planner** last) {
        static FakeWorld* world;
        static Planner* planner;
        static efz::agent::Player* a;
        delete a;
        delete planner;
        delete world;
        world = new FakeWorld;
        planner = new Planner(&p, world, 3);
        a = new efz::agent::Player(&p, 7);
        a->SetPlanner(planner, 0, patience, again);
        play(*world, *a, frames, out);
        *last = planner;
        return a->Stats();
    };
    {
        // The first plan (at A's hit, frame 1): route 0 from its third step (A, A, then
        // its B's: 30,200) beats its own play (240 frames of A: 24,000). At its first B's
        // hit (frame 5), planned again: route 1 joined there (298 B's) beats the rest of
        // route 0 (97 B's) and its own play.
        efz::agent::Policy p;
        std::vector<unsigned char> file = TinyFile(make(300));
        CHECK(p.Parse(file.data(), file.size(), &error));
        CHECK(p.format == 2 && p.routes.replan && p.routes.pool.size() == 2 &&
              p.routes.poolByStarter[6].size() == 1 && p.version == "test");
        std::vector<uint8_t> out;
        Planner* planner;
        efz::agent::RouteStats st = run(p, -1, -1, 200, &out, &planner);
        CHECK(st.plans == 2 && st.again == 1 && st.routes == 2 && st.dropped() == 0);
        CHECK(out[0] == 0x10 && out[1] == 0x10 && out[2] == 0x10 && out[3] == 0x10 && out[4] == 0x10);
        for (int f = 5; f < 200; f++)
            CHECK(out[f] == 0x20);
        CHECK(planner->tried.size() == 3 && planner->tried[0] == 1 &&
              planner->tried[1] == Planner::kExtra && planner->tried[2] == Planner::kOwnPlay);
        CHECK(planner->chosen == 0 && planner->dealt[0] == 298 * 300 && planner->dealt[1] == 97 * 300);
    }
    {
        // Route 1 short (5 B's): the rest of route 0 is chosen, played to its end.
        efz::agent::Policy p;
        std::vector<unsigned char> file = TinyFile(make(5));
        CHECK(p.Parse(file.data(), file.size(), &error));
        std::vector<uint8_t> out;
        Planner* planner;
        efz::agent::RouteStats st = run(p, -1, -1, 140, &out, &planner);
        CHECK(st.plans >= 2 && st.again >= 1 && st.routes >= 2);
        for (int f = 5; f < 105; f++) // (route 0's 100 B's)
            CHECK(out[f] == 0x20);
        CHECK(out[105] == 0x10); // its own play again
    }
    {
        // Once (no replan): the first plan's route 0 played to its end, B's and all (route 1
        // another move's: not tried).
        Tiny t = make(300);
        t.replan = false;
        t.pool.clear();
        t.starters = {5, 7};
        efz::agent::Policy p;
        std::vector<unsigned char> file = TinyFile(t);
        CHECK(p.Parse(file.data(), file.size(), &error) && !p.routes.replan);
        std::vector<uint8_t> out;
        Planner* planner;
        efz::agent::RouteStats st = run(p, -1, -1, 140, &out, &planner);
        CHECK(st.plans == 1 && st.again == 0 && st.routes == 1);
        for (int f = 5; f < 105; f++)
            CHECK(out[f] == 0x20);
        CHECK(out[105] == 0x10);
    }
    {
        // A first plan late (no time to plan): the chooser's pick, route 0 from where the
        // agent sees its hit; one promising less than its margin more than its own play
        // isn't played.
        Tiny t = make(300);
        t.replan = false;
        t.pool.clear();
        t.chooser = {50.0f, 0.0f, 0.0f};
        efz::agent::Policy p;
        std::vector<unsigned char> file = TinyFile(t);
        CHECK(p.Parse(file.data(), file.size(), &error) && !p.chooser.Empty());
        CHECK(p.modules == "policy:1,routes:1,chooser:1");
        std::vector<float> values;
        std::vector<float> in(p.Width(), 0.0f);
        CHECK(p.Choose(in.data(), 5, 2, &values) == 0 && values.size() == 3 && values[0] == 50000);
        CHECK(p.Choose(in.data(), 5, 200, &values) == -1); // too short for that offset
        CHECK(p.Choose(in.data(), 6, 2, &values) == -1);   // no route of that starter
        std::vector<uint8_t> out;
        Planner* planner;
        efz::agent::RouteStats st = run(p, 0, 0, 120, &out, &planner);
        CHECK(st.late == 1 && st.chooser == 1 && st.plans == 0);
        for (int f = 5; f < 105; f++)
            CHECK(out[f] == 0x20);
        t.chooser = {0.1f, 0.0f, 0.0f};
        file = TinyFile(t);
        efz::agent::Policy q;
        CHECK(q.Parse(file.data(), file.size(), &error));
        out.clear();
        st = run(q, 0, 0, 120, &out, &planner);
        CHECK(st.late == 1 && st.chooser == 0);
        for (int f = 3; f < 120; f++)
            CHECK(out[f] == 0x10);
    }
    printf("routes: planned again at a new move's hit, joined, the route kept, the chooser's "
           "when late\n");
}

// Format 2's modules: a module this game doesn't play is refused by name; format 1 read.
void TestFormat()
{
    std::string error;
    Tiny t;
    t.delay = 2;
    t.routes = {std::vector<uint8_t>(10, 1)};
    t.chooser = {1.0f, 0.0f};
    t.format = 2;
    std::vector<unsigned char> file = TinyFile(t);
    efz::agent::Policy p;
    CHECK(p.Parse(file.data(), file.size(), &error));
    CHECK(p.about.count("source.model") && p.about["source.model"] == "model.zip sha256:00");
    auto refused = [&](const Tiny& x, const char* why) {
        std::vector<unsigned char> f = TinyFile(x);
        efz::agent::Policy q;
        std::string e;
        bool no = !q.Parse(f.data(), f.size(), &e);
        if (!no || e.find(why) == std::string::npos)
            fprintf(stderr, "  (refused for '%s'? %s)\n", why, e.c_str());
        return no && e.find(why) != std::string::npos;
    };
    Tiny x = t;
    x.modules = "policy:1,routes:1,chooser:1,oki:1";
    CHECK(refused(x, "oki:1"));
    x.modules = "policy:1,routes:2,chooser:1";
    CHECK(refused(x, "routes:2"));
    x.modules = "none";
    CHECK(refused(x, "modules"));
    x.modules = "policy:1,chooser:1"; // its routes not listed
    CHECK(refused(x, "modules"));
    x = t;
    x.format = 3;
    CHECK(refused(x, "newer game"));
    x = t;
    x.format = 1; // format 1: no chooser then
    x.chooser.clear();
    std::vector<unsigned char> old = TinyFile(x);
    efz::agent::Policy q;
    CHECK(q.Parse(old.data(), old.size(), &error) && q.format == 1 &&
          q.modules == "policy:1,routes:1" && q.routes.pool.size() == 1 && !q.routes.replan);
    printf("agent files: format 2's modules checked, format 1 read\n");
}

void TestAgent()
{
    using efz::agent::kObsDim;
    std::string error;
    efz::agent::Policy p;
    std::vector<unsigned char> file = TinyAgent(1, 1, 0);
    CHECK(p.Parse(file.data(), file.size(), &error));
    CHECK(p.Width() == kObsDim + 6 && p.Actions() == 2 && p.character == 1 && p.name == "tiny");
    std::vector<float> view(p.Width(), 0.0f), out(2);
    view[5] = 1.0f;
    p.LogProbs(view.data(), out.data());
    double l0 = 2.5, l1 = 0.0, norm = log(exp(l0) + exp(l1));
    CHECK(fabs(out[0] - (l0 - norm)) < 1e-5 && fabs(out[1] - (l1 - norm)) < 1e-5);

    // Its own last input seen at once: forward (0x01) last makes action 1 likelier,
    // 2 * dx + 0.5 against 3. Deterministic: dx 1 -> action 0 (forward); then its input
    // was forward, so with dx 1 again 2.5 < 3: action 1 (A).
    efz::agent::Player a(&p, 7);
    std::vector<float> obs(kObsDim, 0.0f);
    obs[5] = 1.0f;
    CHECK(a.Step(obs.data(), true, true) == 0x01);
    CHECK(a.Step(obs.data(), true, true) == 0x10);
    CHECK(a.Step(obs.data(), false, true) == 0); // the controls do nothing
    a.Reset();                                   // a new match: no input yet
    CHECK(a.Step(obs.data(), true, true) == 0x01);

    // frame_skip 3: a decision held three frames, whatever happens; then none while the
    // controls do nothing.
    efz::agent::Policy held;
    file = TinyAgent(3, 0, 0);
    CHECK(held.Parse(file.data(), file.size(), &error));
    efz::agent::Player h(&held, 7);
    CHECK(h.Step(obs.data(), true, true) == 0x01);
    CHECK(h.Step(obs.data(), false, true) == 0x01 && h.Step(obs.data(), false, true) == 0x01);
    CHECK(h.Step(obs.data(), false, true) == 0);

    // delay 2: a decision sees the view of two decisions before (a match's first view
    // fills the past): dx -1, -1, +1, +1 -> sees -1, -1, -1, -1, then +1.
    efz::agent::Policy late;
    file = TinyAgent(1, 0, 2);
    CHECK(late.Parse(file.data(), file.size(), &error));
    efz::agent::Player d(&late, 7);
    float dx[] = {-1, -1, 1, 1, 1};
    unsigned char want[] = {0x10, 0x10, 0x10, 0x10, 0x01};
    for (int i = 0; i < 5; i++) {
        obs[5] = dx[i];
        CHECK(d.Step(obs.data(), true, true) == want[i]);
    }

    // Draws: by the probabilities (about 92% action 0 here).
    efz::agent::Player r(&late, 11);
    obs[5] = 1.0f;
    int zeros = 0;
    for (int i = 0; i < 2000; i++) {
        r.Reset();
        zeros += r.Step(obs.data(), true, false) == 0x01;
    }
    double expect = 2000 * exp(2.5) / (exp(2.5) + 1.0);
    CHECK(fabs(zeros - expect) < 60);

    // Damaged files are refused.
    efz::agent::Policy bad;
    file = TinyAgent(1, 1, 0);
    CHECK(!bad.Parse(file.data(), file.size() - 3, &error) && !error.empty());
    file[0] = 'X';
    CHECK(!bad.Parse(file.data(), file.size(), &error));
    printf("agent: an agent file read and played\n");
}

} // namespace

int main()
{
    TestArenaCopy();
    TestThreads();
    TestSprites();
    TestApi();
    TestAgent();
    TestRoutes();
    TestReplan();
    TestFormat();
    if (g_failures) {
        fprintf(stderr, "%d checks failed\n", g_failures);
        return 1;
    }
    printf("headless: all checks passed\n");
    return 0;
}
