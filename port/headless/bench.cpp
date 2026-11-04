// efz-bench: how fast the training library (efz_env.h) runs, and a check that it runs
// the same game every time.
//
//   efz-bench --data DIR [--envs N] [--threads N] [--steps N] [--frame-skip N]
//             [--cpu] [--draw] [--char C] [--stage S] [--check]
//
// Random controls on both sides (or the game's CPU on P2 with --cpu); prints steps,
// frames and ticks of the simulation per second. --check plays the same matches twice
// in two batches and in a save state, and fails if anything differs.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <chrono>
#include <string>
#include <vector>

#include "efz_env.h"

namespace {

uint64_t g_rng = 12345;

uint32_t Next()
{
    g_rng ^= g_rng << 13;
    g_rng ^= g_rng >> 7;
    g_rng ^= g_rng << 17;
    return (uint32_t)g_rng;
}

// Held directions with button taps, roughly as a person mashes.
void RandomActions(std::vector<uint8_t>& act, std::vector<uint8_t>& held)
{
    for (size_t i = 0; i < act.size(); i++) {
        if (Next() % 8 == 0)
            held[i] = (uint8_t)(Next() & 0x0f);
        uint8_t buttons = Next() % 4 == 0 ? (uint8_t)(0x10 << (Next() % 4)) : 0;
        act[i] = held[i] | buttons;
    }
}

struct Options {
    std::string data;
    int envs = 64, threads = 0, steps = 2000, frameSkip = 1, ch = -1, stage = -1;
    bool cpu = false, draw = false, check = false;
};

EfzEnv* Make(const Options& o, int envs, uint64_t seed)
{
    EfzEnvConfig c;
    efz_env_default_config(&c);
    c.num_envs = envs;
    c.num_threads = o.threads;
    c.frame_skip = o.frameSkip;
    c.drawing = o.draw;
    c.seed = seed;
    c.max_frames = 64 * 60 * 3;
    char error[256];
    EfzEnv* env = efz_env_create(o.data.c_str(), &c, error, sizeof(error));
    if (!env) {
        fprintf(stderr, "efz-bench: %s\n", error);
        exit(1);
    }
    EfzMatch m;
    memset(&m, 0, sizeof(m));
    m.chars[0] = m.chars[1] = (int8_t)o.ch;
    m.stage = (int8_t)o.stage;
    m.palettes[0] = m.palettes[1] = -1;
    m.cpu[1] = o.cpu;
    efz_env_set_matches(env, &m, 1);
    return env;
}

int Bench(const Options& o)
{
    EfzEnv* env = Make(o, o.envs, 1);
    EfzBuffers b;
    efz_env_buffers(env, &b);
    auto t0 = std::chrono::steady_clock::now();
    efz_env_reset(env, nullptr);
    auto t1 = std::chrono::steady_clock::now();
    printf("reset of %d envs (first: loads each match): %.1f ms\n", o.envs,
           std::chrono::duration<double, std::milli>(t1 - t0).count());
    t0 = std::chrono::steady_clock::now();
    efz_env_reset(env, nullptr);
    t1 = std::chrono::steady_clock::now();
    printf("reset again (%s): %.1f ms; a game is %.1f MB\n",
           o.ch >= 0 && o.stage >= 0 ? "the same matches" : "new random matches",
           std::chrono::duration<double, std::milli>(t1 - t0).count(),
           efz_env_state_size(env, 0) / 1048576.0);
    std::vector<uint8_t> act((size_t)o.envs * 2), held(act.size());
    // Warm up: every match of the batch loaded once.
    for (int s = 0; s < 50; s++) {
        RandomActions(act, held);
        efz_env_step(env, act.data());
    }
    uint64_t ticks0 = efz_env_ticks(env);
    long episodes = 0;
    t0 = std::chrono::steady_clock::now();
    for (int s = 0; s < o.steps; s++) {
        RandomActions(act, held);
        efz_env_step(env, act.data());
        for (int i = 0; i < o.envs; i++)
            episodes += b.terminated[i] | b.truncated[i];
    }
    t1 = std::chrono::steady_clock::now();
    double sec = std::chrono::duration<double>(t1 - t0).count();
    double ticks = (double)(efz_env_ticks(env) - ticks0);
    printf("%d envs, %d steps x %d frames: %.2f s\n", o.envs, o.steps, o.frameSkip, sec);
    printf("  %.0f env steps/s, %.0f ticks/s (%.0fx real time), %ld matches ended\n",
           o.envs * (double)o.steps / sec, ticks / sec, ticks / sec / 192.0, episodes);
    efz_env_destroy(env);
    return 0;
}

// Plays `steps` steps with actions from a fixed seed; returns a hash of everything seen.
uint64_t Play(EfzEnv* env, int envs, int steps, uint64_t seed)
{
    EfzBuffers b;
    efz_env_buffers(env, &b);
    g_rng = seed;
    std::vector<uint8_t> act((size_t)envs * 2), held(act.size());
    uint64_t h = 1469598103934665603ull;
    auto mix = [&](const void* p, size_t n) {
        for (size_t i = 0; i < n; i++)
            h = (h ^ ((const uint8_t*)p)[i]) * 1099511628211ull;
    };
    for (int s = 0; s < steps; s++) {
        RandomActions(act, held);
        efz_env_step(env, act.data());
        mix(b.obs, (size_t)envs * 2 * efz_env_obs_dim() * sizeof(float));
        mix(b.reward, (size_t)envs * 2 * sizeof(float));
        mix(b.terminated, envs);
    }
    return h;
}

int Check(const Options& o)
{
    int envs = 8, steps = 1500;
    Options one = o;
    one.threads = 1;
    // The same seeds on 1 thread and on many: the same games.
    EfzEnv* a = Make(one, envs, 7);
    EfzEnv* b = Make(o, envs, 7);
    efz_env_reset(a, nullptr);
    efz_env_reset(b, nullptr);
    uint64_t ha = Play(a, envs, steps, 99), hb = Play(b, envs, steps, 99);
    printf("1 thread vs %d threads: %s\n", o.threads, ha == hb ? "same" : "DIFFERENT");
    bool ok = ha == hb;

    // A save state played on twice from the same point: the same game.
    std::vector<uint8_t> state(efz_env_state_size(a, 3));
    efz_env_save_state(a, 3, state.data(), state.size());
    EfzBuffers ba;
    efz_env_buffers(a, &ba);
    std::vector<uint8_t> act((size_t)envs * 2, 0);
    std::vector<float> first;
    for (int pass = 0; pass < 2; pass++) {
        efz_env_load_state(a, 3, state.data(), state.size());
        efz_env_load_state(b, 5, state.data(), state.size()); // into another batch's env
        std::vector<float> seen;
        g_rng = 5;
        for (int s = 0; s < 400; s++) {
            std::vector<uint8_t> held(act.size());
            RandomActions(act, held);
            efz_env_step(a, act.data());
            seen.insert(seen.end(), ba.obs + 3 * 2 * efz_env_obs_dim(),
                        ba.obs + 4 * 2 * efz_env_obs_dim());
        }
        if (pass == 0)
            first = seen;
        else {
            bool same = first == seen;
            printf("save state replayed: %s\n", same ? "same" : "DIFFERENT");
            ok &= same;
        }
    }
    efz_env_destroy(a);
    efz_env_destroy(b);
    return ok ? 0 : 1;
}

} // namespace

int main(int argc, char** argv)
{
    Options o;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        bool more = i + 1 < argc;
        if (a == "--data" && more)
            o.data = argv[++i];
        else if (a == "--envs" && more)
            o.envs = atoi(argv[++i]);
        else if (a == "--threads" && more)
            o.threads = atoi(argv[++i]);
        else if (a == "--steps" && more)
            o.steps = atoi(argv[++i]);
        else if (a == "--frame-skip" && more)
            o.frameSkip = atoi(argv[++i]);
        else if (a == "--char" && more)
            o.ch = atoi(argv[++i]);
        else if (a == "--stage" && more)
            o.stage = atoi(argv[++i]);
        else if (a == "--cpu")
            o.cpu = true;
        else if (a == "--draw")
            o.draw = true;
        else if (a == "--check")
            o.check = true;
        else {
            fprintf(stderr, "usage: %s --data DIR [--envs N] [--threads N] [--steps N] "
                            "[--frame-skip N] [--cpu] [--draw] [--char C] [--stage S] "
                            "[--check]\n", argv[0]);
            return 2;
        }
    }
    if (o.data.empty()) {
        const char* env = getenv("EFZ_DATA");
        o.data = env ? env : ".";
    }
    return o.check ? Check(o) : Bench(o);
}
