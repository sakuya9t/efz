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
//   its own inputs at once; a file cut short is refused.
//
// The game itself, with its data, is the compatibility suite's (tools/compat.py check
// runs it in both the game and the headless runner).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <string>
#include <thread>
#include <vector>

#include "efz.h"
#include "efz_env.h"
#include "headless.h"
#include "agent/observe.h"
#include "agent/policy.h"

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
    CHECK(sizeof(EfzAgentInfo) == 88);
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

// An agent file of a network without hidden layers, two actions (control bytes 0x01
// and 0x10): logit 0 = 2 * view[5] (the global "dx"... any column) + 0.5, logit 1 =
// view[kObsDim] (its last input's forward-back) * 3.
std::vector<unsigned char> TinyAgent(int frameSkip, int history, int delay)
{
    using efz::agent::kObsDim;
    int width = kObsDim + 6 * history;
    std::string text = "name=tiny\ncharacter=1\nframe_skip=" + std::to_string(frameSkip) +
                       "\nhistory=" + std::to_string(history) + "\ndelay=" +
                       std::to_string(delay) + "\nwidth=" + std::to_string(width) +
                       "\nactions=2\ntable=0110\nfeatures=flat\nactivation=relu\nlayers=0\n";
    std::vector<unsigned char> b;
    auto put = [&](const void* p, size_t n) {
        b.insert(b.end(), (const unsigned char*)p, (const unsigned char*)p + n);
    };
    auto u32 = [&](uint32_t v) { put(&v, 4); };
    put("EFZAGENT", 8);
    u32(1);
    u32((uint32_t)text.size());
    put(text.data(), text.size());
    u32(2);
    auto tensor = [&](const char* name, std::vector<uint32_t> dims, const std::vector<float>& v) {
        uint16_t n = (uint16_t)strlen(name);
        put(&n, 2);
        put(name, n);
        unsigned char type = 0, ndim = (unsigned char)dims.size();
        put(&type, 1);
        put(&ndim, 1);
        for (uint32_t d : dims)
            u32(d);
        put(v.data(), v.size() * 4);
    };
    std::vector<float> w(2 * width, 0.0f);
    w[5] = 2.0f;
    if (history)
        w[width + kObsDim] = 3.0f;
    tensor("action.weight", {2, (uint32_t)width}, w);
    tensor("action.bias", {2}, {0.5f, 0.0f});
    return b;
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
    if (g_failures) {
        fprintf(stderr, "%d checks failed\n", g_failures);
        return 1;
    }
    printf("headless: all checks passed\n");
    return 0;
}
