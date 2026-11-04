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
//   batch without game data fails with a message.
//
// The game itself, with its data, is the compatibility suite's (tools/compat.py check
// runs it in both the game and the headless runner).
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <thread>

#include "efz.h"
#include "efz_env.h"
#include "headless.h"

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
    CHECK(sizeof(EfzEnvConfig) == 64);
    CHECK(sizeof(EfzMatch) == 20);
    CHECK(sizeof(EfzInfo) == 32);
    CHECK(sizeof(EfzBuffers) == 6 * sizeof(void*));
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
    config.num_envs = 2;
    CHECK(efz_env_create("no-such-efz-folder", &config, error, sizeof(error)) == nullptr);
    CHECK(strstr(error, "no game data") != nullptr);
}

} // namespace

int main()
{
    TestArenaCopy();
    TestThreads();
    TestSprites();
    TestApi();
    if (g_failures) {
        fprintf(stderr, "%d checks failed\n", g_failures);
        return 1;
    }
    printf("headless: all checks passed\n");
    return 0;
}
