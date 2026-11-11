// The training library (efz_env.h): batches of headless games stepped on a pool of
// threads.
//
// Each environment is a game in an arena of its own (port/guest.h). A thread runs an
// environment by binding its arena; nothing else in a game is shared, so any thread can
// run any environment, one at a time. A match starts from a saved copy of the game just
// after its intro: the first time a match (characters, stage, palettes, CPU sides) is
// asked for, a game is set up for it as the menus would and played through scene 2
// (the loading) and the intro, and its arena saved (Snapshot); after that, starting
// that match is copying the bytes back (LoadArena). A batch keeps the last cache_size
// of these.
//
// Nothing here allocates while an arena is bound, except through Unbound: operator new
// takes from the bound arena (arena.cpp), which must hold the game alone.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <atomic>
#include <condition_variable>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <unordered_map>
#include <vector>

#if defined(_MSC_VER) && (defined(_M_X64) || defined(_M_IX86))
#include <intrin.h>
#define EFZ_PAUSE() _mm_pause()
#elif defined(__x86_64__) || defined(__i386__)
#define EFZ_PAUSE() __builtin_ia32_pause()
#elif defined(__aarch64__)
#define EFZ_PAUSE() __asm__ __volatile__("yield")
#else
#define EFZ_PAUSE() ((void)0)
#endif

#include "efz.h"
#include "efz_env.h"
#include "headless.h"
#include "platform.h"

using namespace efz;
using namespace efz::headless;

namespace {

// --- Observations: per environment, each player's view, self first.

const int kGlobalFeatures = 8;
const int kPlayerFeatures = 32;
const int kObjects = 8; // per player: the active ones nearest the viewer
const int kObjectFeatures = 6;
const int kObsDim = kGlobalFeatures + 2 * kPlayerFeatures + 2 * kObjects * kObjectFeatures;

const char* const kGlobalNames[kGlobalFeatures] = {
    "frame",       // frames into the match / max_frames (or / 10000)
    "round",       // the round being played, from 1
    "intro",       // a round's intro is running: the controls do nothing
    "round_over",  // a KO happened and the next round hasn't started
    "dx",          // the opponent's x minus the viewer's, / 640
    "dy",          // the opponent's y minus the viewer's, / 240
    "side",        // the viewer is player 1 (0) or 2 (1)
    "rounds_to_win",
};

const char* const kPlayerNames[kPlayerFeatures] = {
    "hp",            // / 9999
    "gauge",         // / 3000: a level per 1000
    "rf_gauge",      // / 1000
    "rf_blue",       // the RF gauge filled and turned blue
    "guard_gauge",   // / 360
    "x",             // (x - 320) / 320: the stage is 0-640
    "y",             // / 240: 0 on the ground, negative in the air
    "vx",            // / 20
    "vy",            // / 20
    "facing",        // 1 right, -1 left
    "action",        // the action (pattern) number: categorical, 0-~600
    "action_frame",  // the frame of the action's animation
    "hitstun",       // in a hit reaction
    "guarding",
    "dashing",
    "hitstop",       // / 30
    "freeze",        // a super's flash stops the opponent
    "invulnerable",
    "no_guard",
    "armor",
    "throw_protected",
    "untech",        // ticks before an air recovery, / 100
    "combo_hits",    // / 30
    "proration",     // / 10000
    "rounds_won",
    "air_actions",   // double jumps and air dashes used
    "character",     // 0-24: categorical
    "own_action",    // the action is the character's own (a move), not common
    "cpu",           // the game's CPU plays this side
    "sealed",        // Akiko's seal level
    "combo_damage",  // / 9999, while a combo goes on
    "airborne",
};

const char* const kObjectNames[kObjectFeatures] = {
    "active", "x", "y", "vx", "vy", "can_hit",
};

const char* const kCharacterNames[EFZ_CHARACTERS] = {
    "nanase", "ayu", "mai", "makoto", "akane", "mayu", "nagamori", "misaki", "shiori",
    "sayuri", "nayuki", "mio", "exnanase", "kaori", "ikumi", "mishio", "akiko", "nayukib",
    "mizukab", "kanna", "kano", "minagi", "nayuki2", "misuzu", "mizuka",
};

// Characters drawn when a match's pool is 0: all but 22 (a second Nayuki) and 24 (the
// boss Mizuka, not on the select screen).
const uint32_t kDefaultCharPool = ((1u << EFZ_CHARACTERS) - 1) & ~(1u << 22) & ~(1u << 24);
const uint32_t kDefaultStagePool = (1u << EFZ_STAGES) - 1;

std::once_flag g_namesOnce;
char g_names[kObsDim][40];

void MakeNames()
{
    int n = 0;
    for (int i = 0; i < kGlobalFeatures; i++)
        snprintf(g_names[n++], sizeof(g_names[0]), "%s", kGlobalNames[i]);
    for (int p = 0; p < 2; p++) {
        for (int i = 0; i < kPlayerFeatures; i++)
            snprintf(g_names[n++], sizeof(g_names[0]), "%s_%s", p ? "opp" : "self",
                     kPlayerNames[i]);
    }
    for (int p = 0; p < 2; p++) {
        for (int k = 0; k < kObjects; k++) {
            for (int i = 0; i < kObjectFeatures; i++)
                snprintf(g_names[n++], sizeof(g_names[0]), "%s_obj%d_%s", p ? "opp" : "self", k,
                         kObjectNames[i]);
        }
    }
}

// --- Saved games.

// The bytes of an arena (guest.h): a whole game.
struct Snapshot {
    char* bytes = nullptr;
    size_t size = 0;

    Snapshot() = default;
    Snapshot(const Snapshot&) = delete;
    Snapshot& operator=(const Snapshot&) = delete;
    ~Snapshot() { free(bytes); }

    // The bound game. malloc, not new: it may be called with an arena bound.
    bool Save()
    {
        free(bytes);
        size = ArenaUsed();
        bytes = (char*)malloc(size);
        if (!bytes)
            return false;
        memcpy(bytes, g_arena, size);
        return true;
    }
    void Load() const { LoadArena(bytes, size); }
};

// While it lives, no arena is bound: operator new takes from the C library's heap.
struct Unbound {
    char* saved;
    Unbound() : saved(g_arena) { BindArena(nullptr); }
    ~Unbound() { BindArena(saved); }
};

// What a match is, as the key of the cache.
struct Match {
    int8_t chars[2];
    int8_t stage;
    int8_t palettes[2];
    uint8_t cpu[2];

    uint64_t Key() const
    {
        return (uint64_t)(uint8_t)chars[0] | (uint64_t)(uint8_t)chars[1] << 8 |
               (uint64_t)(uint8_t)stage << 16 | (uint64_t)(uint8_t)palettes[0] << 24 |
               (uint64_t)(uint8_t)palettes[1] << 32 | (uint64_t)cpu[0] << 40 |
               (uint64_t)cpu[1] << 48;
    }
};

struct CacheEntry {
    std::mutex lock;
    bool ready = false;
    bool failed = false;
    Snapshot snapshot;
};

// The matches ready to start, the least recently used dropped first.
class MatchCache {
public:
    void SetCapacity(size_t capacity) { m_capacity = capacity < 1 ? 1 : capacity; }

    std::shared_ptr<CacheEntry> Get(uint64_t key)
    {
        Unbound unbound;
        std::lock_guard<std::mutex> lock(m_lock);
        auto it = m_map.find(key);
        if (it != m_map.end()) {
            m_lru.splice(m_lru.begin(), m_lru, it->second.second);
            return it->second.first;
        }
        auto entry = std::make_shared<CacheEntry>();
        m_lru.push_front(key);
        m_map.emplace(key, std::make_pair(entry, m_lru.begin()));
        while (m_map.size() > m_capacity) {
            m_map.erase(m_lru.back());
            m_lru.pop_back();
        }
        return entry;
    }

    void Clear()
    {
        std::lock_guard<std::mutex> lock(m_lock);
        m_map.clear();
        m_lru.clear();
    }

private:
    std::mutex m_lock;
    size_t m_capacity = 64;
    std::list<uint64_t> m_lru;
    std::unordered_map<uint64_t, std::pair<std::shared_ptr<CacheEntry>, std::list<uint64_t>::iterator>> m_map;
};

// --- The threads.

// A job: fn(0..n-1), run by the pool's workers and the thread that waits for it.
struct Job {
    std::function<void(int)> fn;
    int n = 0;
    std::atomic<int> next{0};
    int done = 0;   // under the pool's lock
    int active = 0; // workers inside it; under the pool's lock
    bool queued = false;
    bool running = false;
};

// One pool of threads for every batch of the process, so that batches stepped one after
// another (double-buffered, step_async) find its threads awake, and don't compete with
// threads of their own. Jobs are taken in the order they come. Each worker sets its
// stack window (guest.h) once; a thread waiting for a job helps with it and sets its
// own. The pool lives as long as the process: its threads are never joined, which on
// Windows a library mustn't do while it unloads.
class Pool {
public:
    static Pool& Get()
    {
        static Pool* pool = new Pool;
        return *pool;
    }

    // At least `threads` threads (the waiting one included) work on jobs.
    void Grow(int threads)
    {
        std::lock_guard<std::mutex> lock(m_lock);
        while ((int)m_workers + 1 < threads) {
            std::thread([this] { Work(); }).detach();
            m_workers++;
        }
    }

    void Launch(Job& job, int n, std::function<void(int)> fn)
    {
        std::lock_guard<std::mutex> lock(m_lock);
        job.fn = std::move(fn);
        job.n = n;
        job.next.store(0);
        job.done = 0;
        job.active = 0;
        job.running = true;
        job.queued = true;
        m_queue.push_back(&job);
        m_pending.store((int)m_queue.size(), std::memory_order_release);
        m_wake.notify_all();
    }

    void Wait(Job& job)
    {
        if (!job.running)
            return;
        int stackMark;
        SetStack(&stackMark);
        int did = RunItems(job);
        std::unique_lock<std::mutex> lock(m_lock);
        job.done += did;
        Dequeue(job);
        m_finished.wait(lock, [&] { return job.done == job.n && job.active == 0; });
        job.running = false;
        job.fn = nullptr;
    }

private:
    static int RunItems(Job& job)
    {
        int did = 0;
        for (;;) {
            int i = job.next.fetch_add(1);
            if (i >= job.n)
                return did;
            job.fn(i);
            did++;
        }
    }

    // Under the lock: the job has no items left to hand out.
    void Dequeue(Job& job)
    {
        if (!job.queued)
            return;
        job.queued = false;
        for (size_t k = 0; k < m_queue.size(); k++) {
            if (m_queue[k] == &job) {
                m_queue.erase(m_queue.begin() + k);
                break;
            }
        }
        m_pending.store((int)m_queue.size(), std::memory_order_release);
    }

    void Work()
    {
        int stackMark;
        SetStack(&stackMark);
        for (;;) {
            // A short spin first: steps come back to back while a program trains.
            for (int spin = 0; spin < 4000 && m_pending.load(std::memory_order_acquire) == 0; spin++)
                EFZ_PAUSE();
            std::unique_lock<std::mutex> lock(m_lock);
            m_wake.wait(lock, [&] { return !m_queue.empty(); });
            Job& job = *m_queue.front();
            job.active++;
            lock.unlock();
            int did = RunItems(job);
            lock.lock();
            job.done += did;
            Dequeue(job);
            if (--job.active == 0 && job.done == job.n)
                m_finished.notify_all();
        }
    }

    std::mutex m_lock;
    std::condition_variable m_wake, m_finished;
    std::vector<Job*> m_queue;
    std::atomic<int> m_pending{0};
    size_t m_workers = 0;
};

// --- The environments.

uint64_t SplitMix(uint64_t& state)
{
    uint64_t z = (state += 0x9e3779b97f4a7c15ull);
    z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ull;
    z = (z ^ (z >> 27)) * 0x94d049bb133111ebull;
    return z ^ (z >> 31);
}

int DrawFromPool(uint32_t pool, uint64_t& rng)
{
    int count = 0;
    for (uint32_t p = pool; p; p &= p - 1)
        count++;
    int pick = (int)(SplitMix(rng) % (uint64_t)count);
    for (int i = 0; i < 32; i++) {
        if ((pool >> i & 1) && pick-- == 0)
            return i;
    }
    return 0;
}

// What a save state holds besides the arena: the environment's match so far.
struct Episode {
    Match match;
    int32_t frame;
    int32_t episode;
    int32_t prevHp[2];
    int8_t prevRounds[2];
    float ret[2];
    uint64_t rng;
};

struct Slot {
    char* arena = nullptr;
    EfzMatch spec;
    Episode ep;
    bool started = false;
    bool broken = false;   // its game asked to close (a file it needs is missing)
    bool pending = false;  // its match ended: the next step starts the next (NEXT_STEP)
    bool finished = false; // its match ended: it waits for efz_env_reset (DISABLED)
    int recordPage = 0;    // efz_env_record: its next match is recorded to this slot
    int recordSlot = 0;
    bool recording = false; // the game is writing its match's replay
    std::string playNext;  // efz_env_play: its next match plays this replay back
    Match playMatch;       // the replay's characters, stage and palettes
    long playTrailer = 0;  // bytes at the replay's end that aren't the game's
    bool playing = false;  // the game is reading its match's replay
    bool inputTaken = false; // input[] holds the step's first frame's
    uint8_t input[2] = {0, 0}; // EfzInfo.input
};

const uint32_t kStateMagic = 0x5a464545; // "EEFZ"

struct StateHeader {
    uint32_t magic;
    uint32_t version;
    uint64_t arenaSize;
    uint64_t base; // where the library is loaded (LibraryBase): what the state's pointers assume
    Episode ep;
};

// The game's objects in an arena hold the addresses of their C++ classes' tables, which
// are the library's: a state is only good where the library is loaded at the same address
// (in the process that saved it; in another only by chance, as address randomisation
// places it).
uint64_t LibraryBase()
{
    return (uint64_t)(uintptr_t)&efz_env_version;
}

} // namespace

struct EfzEnv {
    EfzEnvConfig cfg;
    std::string dataDir;
    int n = 0;
    std::vector<Slot> slots;
    // The buffers of efz_env_buffers.
    std::vector<float> obs, finalObs, reward;
    std::vector<uint8_t> terminated, truncated, actions;
    std::vector<EfzInfo> info;
    float* obsOut = nullptr;
    float* finalObsOut = nullptr;
    Snapshot init; // a game made as WinMain made it, before any match
    MatchCache cache;
    Job job; // its steps and resets, on the shared Pool
    std::atomic<uint64_t> ticks{0};
    std::mutex errorLock;
    std::string error;

    void SetError(const std::string& e)
    {
        Unbound unbound;
        std::lock_guard<std::mutex> lock(errorLock);
        error = e;
    }
};

namespace {

CScene3* Fight()
{
    return (CScene3*)Scene(3);
}

// The controls do something: no intro, no KO waiting for the next round.
bool Actionable()
{
    CGame* game = Game();
    return SceneIndex() == 3 && game->m_intro == 0 && game->m_roundOver == 0 &&
           Fight()->m_enter == 0;
}

// How BuildMatch starts a match besides: recorded, or a replay played back.
struct Build {
    int recordPage = 0;          // 1-9, with recordSlot: as the replay menu's record item
    int recordSlot = 0;
    const char* play = nullptr;  // a replay file: as the replay menu's play item
    long trailer = 0;            // bytes at its end that aren't the game's
};

// Sets up the bound arena's game for `m` (a copy of env->init) and plays it through the
// loading and the intro, as the menus would have started it: VS on the replay menu's
// footing (mode 5, no replay), which keeps records and replays unwritten. With a page and
// slot (1-9), as the replay menu's record item: the game writes the match's replay there
// from the loading on. With a replay file, as its play item: the loader reads the
// characters, stage and palettes from it (the same as m's), and the game its inputs.
bool BuildMatch(EfzEnv* env, const Match& m, const Build& how = Build(), unsigned seed = 1)
{
    env->init.Load();
    const EfzEnvConfig& cfg = env->cfg;
    CGame* game = Game();
    game->m_gameMode = 5;
    game->m_replayMode = 0;
    if (how.recordPage > 0) {
        game->m_replayMode = 2;
        game->m_replayPage = (char)(how.recordPage - 1);
        game->m_replaySlot = (char)(how.recordSlot - 1);
    } else if (how.play) {
        game->m_replayMode = 1;
        game->m_replayPage = 0;
        game->m_replaySlot = 0;
    }
    game->m_roundsToWin = (char)cfg.rounds_to_win;
    game->m_roundsSetting = (char)cfg.rounds_to_win;
    game->m_isCpu[0] = m.cpu[0];
    game->m_isCpu[1] = m.cpu[1];
    game->m_stage = m.stage;
    game->m_arcadeMatch = 1;
    game->m_beatenChars = 0;
    game->m_playedStages = 0;
    game->m_editColor[0] = 0;
    game->m_editColor[1] = 0;
    game->m_cpuLevel = (char)cfg.cpu_level;
    game->m_damageLevel = (char)cfg.damage_level;
    game->m_drawEveryFrame = 1;
    game->m_fullEffects = 1;
    if (!how.play) {
        CScene2* loader = (CScene2*)Scene(2);
        loader->CreateCharacter(loader->m_player1Ref, loader->m_player2Ref, 0, m.chars[0]);
        loader->CreateCharacter(loader->m_player2Ref, loader->m_player1Ref, 1, m.chars[1]);
        (*loader->m_player1Ref)->m_paletteIndex = m.palettes[0];
        (*loader->m_player2Ref)->m_paletteIndex = m.palettes[1];
    }
    G()->input[0] = G()->input[1] = 0;
    srand(seed);
    SceneIndex() = 2;
    SetReplayFile(how.play); // the loader opens it as replay slot 1-1's file
    bool opened = !how.play, ok = false;
    for (int frame = 0; frame < 2000; frame++) {
        RunFrame();
        if (!opened && game->m_replay.m_handle) {
            // What follows the game's part (EfzRevival's block) reads as the file's end.
            opened = true;
            SetReplayFile(nullptr);
            DWORD& left = game->m_replay.m_remaining;
            left = left > (DWORD)how.trailer ? left - (DWORD)how.trailer : 0;
        }
        if (QuitRequested() || (SceneIndex() != 2 && SceneIndex() != 3))
            break;
        if (Actionable()) {
            ok = true;
            break;
        }
    }
    SetReplayFile(nullptr);
    if (ok && how.play) { // the replay the loader read is the one efz_env_play read
        CScene3* fight = (CScene3*)Scene(3);
        ok = game->m_replayMode == 1 && fight->m_players[0]->m_charId == m.chars[0] &&
             fight->m_players[1]->m_charId == m.chars[1];
    }
    return ok;
}

Match DrawMatch(const EfzMatch& spec, uint64_t& rng)
{
    Match m;
    for (int p = 0; p < 2; p++) {
        m.chars[p] = spec.chars[p];
        if (m.chars[p] < 0 || m.chars[p] >= EFZ_CHARACTERS) {
            uint32_t pool = spec.char_pool[p] & ((1u << EFZ_CHARACTERS) - 1);
            m.chars[p] = (int8_t)DrawFromPool(pool ? pool : kDefaultCharPool, rng);
        }
        m.cpu[p] = spec.cpu[p] ? 1 : 0;
    }
    m.stage = spec.stage;
    if (m.stage < 0 || m.stage >= EFZ_STAGES) {
        uint32_t pool = spec.stage_pool & kDefaultStagePool;
        m.stage = (int8_t)DrawFromPool(pool ? pool : kDefaultStagePool, rng);
    }
    m.palettes[0] = spec.palettes[0] >= 0 ? spec.palettes[0] : 0;
    m.palettes[1] = spec.palettes[1] >= 0 ? spec.palettes[1] : (m.chars[0] == m.chars[1]);
    return m;
}

bool LoadMatch(EfzEnv* env, Slot& s, const Match& m);

// Starts the replay efz_env_play gave the slot, in its (bound) arena: built from its
// start, the loader reading the replay.
bool StartPlayback(EfzEnv* env, Slot& s)
{
    std::string path;
    {
        Unbound unbound; // the slot's strings are the C library's
        path.swap(s.playNext);
    }
    Build how;
    how.play = path.c_str();
    how.trailer = s.playTrailer;
    bool ok = BuildMatch(env, s.playMatch, how);
    {
        Unbound unbound;
        std::string().swap(path);
    }
    if (!ok) {
        if (Game()->m_replayMode == 1) {
            Game()->m_replay.Close();
            Game()->m_replayMode = 0;
        }
        env->SetError("the replay could not be played back");
        s.broken = true;
        return false;
    }
    s.playing = true;
    return true;
}

// Starts the slot's next match in its (bound) arena.
bool StartMatch(EfzEnv* env, Slot& s)
{
    Match m;
    if (!s.playNext.empty()) {
        m = s.playMatch;
        if (!StartPlayback(env, s))
            return false;
    } else {
        m = DrawMatch(s.spec, s.ep.rng);
        int page = s.recordPage, slot = s.recordSlot;
        s.recordPage = s.recordSlot = 0;
        if (page > 0 && (m.cpu[0] || m.cpu[1])) {
            env->SetError("not recorded: a replay doesn't hold the CPU's decisions, so "
                          "both players must be the program's");
            page = 0;
        }
        if (page > 0) {
            // Recorded: built from its start with the game writing the replay, not copied.
            Build how;
            how.recordPage = page;
            how.recordSlot = slot;
            if (!BuildMatch(env, m, how, (unsigned)SplitMix(s.ep.rng))) {
                Game()->m_replay.Close();
                Game()->m_replayMode = 0;
                env->SetError("the recorded match could not be started");
                s.broken = true;
                return false;
            }
            s.recording = true;
        } else if (!LoadMatch(env, s, m)) {
            return false;
        }
    }
    s.ep.match = m;
    s.ep.frame = 0;
    s.ep.episode++;
    s.ep.prevHp[0] = s.ep.prevHp[1] = 9999;
    s.ep.prevRounds[0] = s.ep.prevRounds[1] = 0;
    s.ep.ret[0] = s.ep.ret[1] = 0;
    s.input[0] = s.input[1] = 0;
    s.started = true;
    s.broken = false;
    return true;
}

// Ends the slot's replay (its arena bound). One played back is closed. One recorded,
// after a match won, plays on as the game does after a match (the end fade) until it
// closes the replay; else it is closed now.
void EndReplay(Slot& s, bool playOut)
{
    if (s.playing) {
        s.playing = false;
        if (Game()->m_replayMode == 1) {
            Game()->m_replay.Close();
            Game()->m_replayMode = 0;
        }
    }
    if (!s.recording)
        return;
    s.recording = false;
    if (playOut) {
        G()->input[0] = G()->input[1] = 0;
        for (int frame = 0; frame < 2000 && SceneIndex() == 3 && Game()->m_replayMode == 2;
             frame++)
            RunFrame();
    }
    if (Game()->m_replayMode == 2) {
        Game()->m_replay.Close();
        Game()->m_replayMode = 0;
    }
}

// Starts match `m` in the slot's (bound) arena from its saved copy, made the first time
// it is asked for.
bool LoadMatch(EfzEnv* env, Slot& s, const Match& m)
{
    std::shared_ptr<CacheEntry> entry = env->cache.Get(m.Key());
    {
        std::lock_guard<std::mutex> lock(entry->lock);
        if (!entry->ready && !entry->failed) {
            if (BuildMatch(env, m) && entry->snapshot.Save())
                entry->ready = true;
            else
                entry->failed = true;
        }
    }
    if (!entry->ready) {
        char text[96];
        snprintf(text, sizeof(text), "the match %s vs %s on stage %d could not be started",
                 kCharacterNames[m.chars[0]], kCharacterNames[m.chars[1]], m.stage);
        env->SetError(text);
        s.broken = true;
        return false;
    }
    entry->snapshot.Load();
    {
        Unbound unbound;
        entry.reset();
    }
    // The CPU and the effects draw from rand: a seed of its own for each match.
    srand((unsigned)SplitMix(s.ep.rng));
    return true;
}

// Swaps forward and back for a player facing left (from controls relative to facing, or
// to them).
uint8_t Mirror(uint8_t bits, bool relative, int facing)
{
    if (relative && facing < 0)
        bits = (uint8_t)((bits & ~3) | (bits & 1) << 1 | (bits & 2) >> 1);
    return bits;
}

// The controls `p` played on the frame just run, as CPlayer::ReadInput read them: its
// directions on the screen and its buttons held (or pressed: the CPU presses them
// without holding).
uint8_t ControlsRead(CPlayer* p)
{
    uint8_t bits = 0;
    if (p->m_inputX == 1)
        bits |= EFZ_RIGHT;
    else if (p->m_inputX == -1)
        bits |= EFZ_LEFT;
    if (p->m_inputY == 1)
        bits |= EFZ_DOWN;
    else if (p->m_inputY == -1)
        bits |= EFZ_UP;
    if (p->m_holdA || p->m_pressA)
        bits |= EFZ_A;
    if (p->m_holdB || p->m_pressB)
        bits |= EFZ_B;
    if (p->m_holdC || p->m_pressC)
        bits |= EFZ_C;
    if (p->m_holdD || p->m_pressD)
        bits |= EFZ_D;
    return bits;
}

// One frame with the players' controls (relative to their facing, if so configured);
// adds to the rewards. Returns the match's winner once it is decided, else -1; -2 if
// the fight scene ended otherwise, -3 if the replay played back ran out.
int Frame(EfzEnv* env, Slot& s, const uint8_t* act, float* reward)
{
    const EfzEnvConfig& cfg = env->cfg;
    CScene3* fight = Fight();
    Globals* g = G();
    int facing[2];
    for (int p = 0; p < 2; p++) {
        facing[p] = fight->m_players[p]->facing;
        g->input[p] = Mirror(act ? act[p] : 0, cfg.relative_actions != 0, facing[p]);
    }
    RunFrame();
    env->ticks.fetch_add(fight->m_speed, std::memory_order_relaxed);
    s.ep.frame++;
    if (SceneIndex() != 3)
        return -2;
    if (!s.inputTaken) {
        s.inputTaken = true;
        for (int p = 0; p < 2; p++)
            s.input[p] = Mirror(ControlsRead(fight->m_players[p]), cfg.relative_actions != 0,
                                facing[p]);
    }

    int taken[2];
    int8_t rounds[2];
    for (int p = 0; p < 2; p++) {
        CPlayer* player = fight->m_players[p];
        // HP only counts down to 0 (a KO's blow can take it below), and its refill for
        // the next round isn't damage.
        int hp = player->m_hp > 0 ? player->m_hp : 0;
        taken[p] = s.ep.prevHp[p] > hp ? s.ep.prevHp[p] - hp : 0;
        s.ep.prevHp[p] = hp;
        rounds[p] = (int8_t)(player->m_roundsWon - s.ep.prevRounds[p]);
        s.ep.prevRounds[p] = player->m_roundsWon;
    }
    int winner = fight->m_leave == 2 ? Game()->m_winner : -1;
    for (int p = 0; p < 2; p++) {
        float r = cfg.reward_damage * (float)(taken[1 - p] - taken[p]) / 9999.0f +
                  cfg.reward_round * (float)(rounds[p] - rounds[1 - p]);
        if (winner >= 0)
            r += winner == p ? cfg.reward_match : -cfg.reward_match;
        reward[p] += r;
        s.ep.ret[p] += r;
    }
    // The replay's end: the scene leaves the next frame (CScene3::HandleKeys).
    if (winner == -1 && s.playing && (Game()->m_replay.m_eof || fight->m_leave == 1))
        return -3;
    return winner;
}

float Clamp(double v, double lo, double hi)
{
    return (float)(v < lo ? lo : v > hi ? hi : v);
}

void WritePlayer(float* o, CPlayer* p)
{
    o[0] = p->m_hp / 9999.0f;
    o[1] = p->m_gauge / 3000.0f;
    o[2] = (float)(p->m_rfGauge / 1000.0);
    o[3] = p->m_rfBlue != 0;
    o[4] = (float)p->m_guardGauge / 360.0f;
    o[5] = (float)((p->x - 320.0) / 320.0);
    o[6] = (float)(p->y / 240.0);
    o[7] = Clamp(p->vx / 20.0, -10, 10);
    o[8] = Clamp(p->vy / 20.0, -10, 10);
    o[9] = p->facing;
    o[10] = p->pattern;
    o[11] = p->frame;
    o[12] = p->IsInHitstun() != 0;
    o[13] = p->IsGuarding() != 0;
    o[14] = p->IsDashing() != 0;
    o[15] = p->m_hitstop / 30.0f;
    o[16] = p->m_freezeTime > 0;
    o[17] = p->m_invulTime > 0;
    o[18] = p->m_noGuardTime > 0;
    o[19] = p->m_armorTime > 0;
    o[20] = p->m_throwProtect > 0;
    o[21] = p->m_untechTime / 100.0f;
    o[22] = p->m_comboHits / 30.0f;
    o[23] = (float)(p->m_proration / 10000.0);
    o[24] = p->m_roundsWon;
    o[25] = p->m_airActions;
    o[26] = p->m_charId;
    o[27] = p->pattern >= kFirstCharacterAction;
    o[28] = p->m_cpu != 0;
    o[29] = (float)p->m_sealLevel;
    o[30] = p->m_comboHits > 0 ? p->m_comboDamage / 9999.0f : 0.0f;
    o[31] = p->y < 0.0;
}

// The `owner`'s active objects nearest the viewer, nearest first.
void WriteObjects(float* o, CPlayer* owner, CPlayer* viewer)
{
    int slots[0x40];
    double dist[0x40];
    int n = 0;
    for (int k = 0; k < 0x40; k++) {
        if (!owner->m_objectActive[k])
            continue;
        const PlayerObject& obj = owner->m_objects[k];
        slots[n] = k;
        dist[n] = fabs(obj.x - viewer->x) + fabs(obj.y - viewer->y);
        n++;
    }
    for (int k = 0; k < kObjects; k++, o += kObjectFeatures) {
        if (k >= n) {
            memset(o, 0, kObjectFeatures * sizeof(float));
            continue;
        }
        int best = k;
        for (int j = k + 1; j < n; j++) {
            if (dist[j] < dist[best])
                best = j;
        }
        std::swap(slots[k], slots[best]);
        std::swap(dist[k], dist[best]);
        const PlayerObject& obj = owner->m_objects[slots[k]];
        o[0] = 1.0f;
        o[1] = (float)((obj.x - viewer->x) / 320.0);
        o[2] = (float)(obj.y / 240.0);
        o[3] = Clamp(obj.vx / 20.0, -10, 10);
        o[4] = Clamp(obj.vy / 20.0, -10, 10);
        o[5] = obj.hitsLeft > 0;
    }
}

void WriteObs(EfzEnv* env, const Slot& s, float* out)
{
    CScene3* fight = Fight();
    CGame* game = Game();
    for (int v = 0; v < 2; v++) {
        float* o = out + v * kObsDim;
        CPlayer* self = fight->m_players[v];
        CPlayer* opp = fight->m_players[1 - v];
        int max = env->cfg.max_frames > 0 ? env->cfg.max_frames : 10000;
        o[0] = (float)s.ep.frame / max;
        o[1] = game->m_round;
        o[2] = game->m_intro != 0;
        o[3] = game->m_roundOver != 0;
        o[4] = (float)((opp->x - self->x) / 640.0);
        o[5] = (float)((opp->y - self->y) / 240.0);
        o[6] = (float)v;
        o[7] = game->m_roundsToWin;
        o += kGlobalFeatures;
        WritePlayer(o, self);
        WritePlayer(o + kPlayerFeatures, opp);
        o += 2 * kPlayerFeatures;
        WriteObjects(o, self, self);
        WriteObjects(o + kObjects * kObjectFeatures, opp, self);
    }
}

void WriteInfo(const Slot& s, EfzInfo& info, int winner, bool ended)
{
    CScene3* fight = Fight();
    info.frame = s.ep.frame;
    info.episode = s.ep.episode;
    for (int p = 0; p < 2; p++) {
        CPlayer* player = fight->m_players[p];
        info.hp[p] = (int16_t)(player->m_hp < 0 ? 0 : player->m_hp);
        info.gauge[p] = player->m_gauge;
        info.rounds_won[p] = player->m_roundsWon;
        info.chars[p] = s.ep.match.chars[p];
        info.episode_return[p] = s.ep.ret[p];
    }
    info.round = Game()->m_round;
    info.winner = (int8_t)winner;
    info.stage = s.ep.match.stage;
    info.ended = ended;
    info.input[0] = s.input[0];
    info.input[1] = s.input[1];
    info.replay = s.playing;
    info.reserved = 0;
}

float* ObsOf(EfzEnv* env, float* base, int i)
{
    return base + (size_t)i * 2 * kObsDim;
}

// A reset of environment i, on the thread that binds it.
void ResetOne(EfzEnv* env, int i)
{
    Slot& s = env->slots[i];
    s.pending = s.finished = false;
    BindArena(s.arena);
    EndReplay(s, false); // a reset cuts a replay short
    env->reward[2 * i] = env->reward[2 * i + 1] = 0;
    env->terminated[i] = env->truncated[i] = 0;
    if (StartMatch(env, s)) {
        WriteObs(env, s, ObsOf(env, env->obsOut, i));
        WriteInfo(s, env->info[i], -1, false);
    } else {
        memset(ObsOf(env, env->obsOut, i), 0, 2 * kObsDim * sizeof(float));
        env->terminated[i] = 1;
    }
    BindArena(nullptr);
}

// A step of environment i, on the thread that binds it.
void StepOne(EfzEnv* env, int i)
{
    Slot& s = env->slots[i];
    const EfzEnvConfig& cfg = env->cfg;
    float* reward = &env->reward[2 * i];
    const uint8_t* act = &env->actions[2 * i];
    reward[0] = reward[1] = 0;
    if (s.finished) // DISABLED: as it ended, until efz_env_reset
        return;
    env->terminated[i] = env->truncated[i] = 0;
    if (!s.started || s.broken || s.pending) {
        ResetOne(env, i);
        return;
    }
    BindArena(s.arena);
    int winner = -1;
    s.inputTaken = false;
    for (int k = 0; k < cfg.frame_skip && winner == -1; k++)
        winner = Frame(env, s, act, reward);
    if (cfg.skip_noninteractive) {
        for (int guard = 0; winner == -1 && !Actionable() && guard < 4000; guard++)
            winner = Frame(env, s, nullptr, reward);
    }
    bool ranOut = winner == -3; // the replay played back ends here, the match unfinished
    if (ranOut)
        winner = -1;
    bool terminated = winner != -1;
    bool truncated = !terminated &&
                     (ranOut || (cfg.max_frames > 0 && s.ep.frame >= cfg.max_frames));
    if (winner == -2) { // the fight scene ended some other way: start over
        winner = -1;
        s.broken = true;
    }
    if (!terminated && !truncated) {
        WriteObs(env, s, ObsOf(env, env->obsOut, i));
        WriteInfo(s, env->info[i], -1, false);
        BindArena(nullptr);
        return;
    }
    env->terminated[i] = terminated;
    env->truncated[i] = truncated;
    if (!s.broken) {
        WriteObs(env, s, ObsOf(env, env->finalObsOut, i));
        WriteInfo(s, env->info[i], winner, true);
    } else {
        memset(ObsOf(env, env->finalObsOut, i), 0, 2 * kObsDim * sizeof(float));
    }
    EndReplay(s, terminated && !s.broken);
    if (cfg.autoreset != EFZ_AUTORESET_SAME_STEP) {
        // The step's observation is the match's last; the next match waits.
        memcpy(ObsOf(env, env->obsOut, i), ObsOf(env, env->finalObsOut, i),
               2 * kObsDim * sizeof(float));
        if (cfg.autoreset == EFZ_AUTORESET_NEXT_STEP)
            s.pending = true;
        else
            s.finished = true;
        BindArena(nullptr);
        return;
    }
    if (StartMatch(env, s)) {
        WriteObs(env, s, ObsOf(env, env->obsOut, i));
        if (!env->info[i].ended)
            WriteInfo(s, env->info[i], -1, false);
    }
    BindArena(nullptr);
}

void Finish(EfzEnv* env)
{
    if (env->job.running)
        Pool::Get().Wait(env->job);
}

} // namespace

// --- The C API.

extern "C" {

void efz_env_default_config(EfzEnvConfig* c)
{
    memset(c, 0, sizeof(*c));
    c->num_envs = 1;
    c->num_threads = 0;
    c->frame_skip = 1;
    c->max_frames = 0;
    c->rounds_to_win = 2;
    c->cpu_level = 2;
    c->damage_level = 2;
    c->skip_noninteractive = 1;
    c->relative_actions = 1;
    c->drawing = 0;
    c->cache_size = 64;
    c->reward_damage = 1.0f;
    c->reward_round = 0.0f;
    c->reward_match = 1.0f;
    c->seed = 0;
    c->autoreset = EFZ_AUTORESET_SAME_STEP;
}

int32_t efz_env_version(void)
{
    return EFZ_ENV_VERSION;
}

int32_t efz_env_obs_dim(void)
{
    return kObsDim;
}

const char* efz_env_obs_name(int32_t i)
{
    std::call_once(g_namesOnce, MakeNames);
    return i >= 0 && i < kObsDim ? g_names[i] : nullptr;
}

const char* efz_env_character_name(int32_t c)
{
    return c >= 0 && c < EFZ_CHARACTERS ? kCharacterNames[c] : nullptr;
}

EfzEnv* efz_env_create(const char* dataDir, const EfzEnvConfig* config, char* error,
                       size_t errorSize)
{
    auto fail = [&](const char* text) -> EfzEnv* {
        if (error && errorSize)
            snprintf(error, errorSize, "%s", text);
        return nullptr;
    };
    BindArena(nullptr);
    EfzEnvConfig cfg;
    efz_env_default_config(&cfg);
    if (config)
        cfg = *config;
    if (cfg.num_envs < 1)
        return fail("num_envs must be at least 1");
    if (cfg.num_threads <= 0)
        cfg.num_threads = (int)std::max(1u, std::thread::hardware_concurrency());
    cfg.num_threads = std::min(cfg.num_threads, cfg.num_envs);
    cfg.frame_skip = std::max(1, cfg.frame_skip);
    cfg.rounds_to_win = std::min(3, std::max(1, cfg.rounds_to_win));
    cfg.cpu_level = std::min(4, std::max(1, cfg.cpu_level));
    cfg.damage_level = std::min(3, std::max(1, cfg.damage_level));
    if (cfg.cache_size <= 0)
        cfg.cache_size = 64;
    if (cfg.autoreset < EFZ_AUTORESET_SAME_STEP || cfg.autoreset > EFZ_AUTORESET_DISABLED)
        return fail("autoreset must be EFZ_AUTORESET_SAME_STEP, _NEXT_STEP or _DISABLED");
    if (!dataDir || !*dataDir)
        return fail("no data_dir: the folder of an EFZ 4.02 install");
    std::string probe = std::string(dataDir) + "/system/effect/effect.dat";
    if (FILE* f = fopen(probe.c_str(), "rb"))
        fclose(f);
    else
        return fail("no game data in data_dir (expected system/effect/effect.dat there)");
    SetDataDir(dataDir, dataDir);
    SetMessages(false);

    std::unique_ptr<EfzEnv> env(new EfzEnv);
    env->cfg = cfg;
    env->dataDir = dataDir;
    env->n = cfg.num_envs;
    env->cache.SetCapacity((size_t)cfg.cache_size);
    size_t obsSize = (size_t)env->n * 2 * kObsDim;
    env->obs.assign(obsSize, 0.0f);
    env->finalObs.assign(obsSize, 0.0f);
    env->reward.assign((size_t)env->n * 2, 0.0f);
    env->terminated.assign(env->n, 0);
    env->truncated.assign(env->n, 0);
    env->actions.assign((size_t)env->n * 2, 0);
    env->info.assign(env->n, EfzInfo());
    env->obsOut = env->obs.data();
    env->finalObsOut = env->finalObs.data();
    env->slots.resize(env->n);

    // The first game, made as WinMain made it; every environment starts as a copy.
    {
        int stackMark;
        SetStack(&stackMark);
        char* arena = NewArena();
        BindArena(arena);
        CreateGame(cfg.drawing != 0, 0);
        srand(1);
        bool ok = !QuitRequested() && env->init.Save();
        BindArena(nullptr);
        FreeArena(arena);
        if (!ok)
            return fail("the game could not be set up from data_dir");
    }
    uint64_t seed = cfg.seed;
    for (int i = 0; i < env->n; i++) {
        Slot& s = env->slots[i];
        s.arena = NewArena();
        BindArena(s.arena);
        env->init.Load();
        BindArena(nullptr);
        memset(&s.spec, 0, sizeof(s.spec));
        s.spec.chars[0] = s.spec.chars[1] = -1;
        s.spec.stage = -1;
        s.spec.palettes[0] = s.spec.palettes[1] = -1;
        memset(&s.ep, 0, sizeof(s.ep));
        s.ep.rng = SplitMix(seed) ^ (uint64_t)i;
    }
    Pool::Get().Grow(cfg.num_threads);
    return env.release();
}

void efz_env_destroy(EfzEnv* env)
{
    if (!env)
        return;
    BindArena(nullptr);
    Finish(env);
    for (Slot& s : env->slots) {
        if (s.recording || s.playing) { // its replay ends where the match is
            BindArena(s.arena);
            EndReplay(s, false);
            BindArena(nullptr);
        }
        FreeArena(s.arena);
    }
    delete env;
}

int32_t efz_env_num_envs(const EfzEnv* env)
{
    return env ? env->n : 0;
}

void efz_env_buffers(EfzEnv* env, EfzBuffers* out)
{
    out->obs = env->obsOut;
    out->final_obs = env->finalObsOut;
    out->reward = env->reward.data();
    out->terminated = env->terminated.data();
    out->truncated = env->truncated.data();
    out->info = env->info.data();
}

void efz_env_set_obs_buffers(EfzEnv* env, float* obs, float* finalObs)
{
    Finish(env);
    env->obsOut = obs ? obs : env->obs.data();
    env->finalObsOut = finalObs ? finalObs : env->finalObs.data();
}

int efz_env_set_matches(EfzEnv* env, const EfzMatch* matches, int32_t count)
{
    if (!env || !matches || (count != 1 && count != env->n))
        return -1;
    Finish(env);
    for (int i = 0; i < env->n; i++)
        env->slots[i].spec = matches[count == 1 ? 0 : i];
    return 0;
}

int efz_env_reset(EfzEnv* env, const uint8_t* mask)
{
    if (!env)
        return -1;
    BindArena(nullptr);
    Finish(env);
    std::vector<int> which;
    for (int i = 0; i < env->n; i++) {
        if (!mask || mask[i])
            which.push_back(i);
    }
    Pool::Get().Launch(env->job, (int)which.size(), [env, &which](int k) { ResetOne(env, which[k]); });
    Pool::Get().Wait(env->job);
    return 0;
}

int efz_env_record(EfzEnv* env, int32_t index, int32_t page, int32_t slot)
{
    if (!env || index < 0 || index >= env->n)
        return -1;
    Finish(env);
    if (page < 1 || page > 9 || slot < 1 || slot > 9) {
        env->SetError("replay slots are page 1-9, slot 1-9");
        return -1;
    }
    Slot& s = env->slots[index];
    if (s.spec.cpu[0] || s.spec.cpu[1]) {
        env->SetError("a replay doesn't hold the CPU's decisions: both players must be the "
                      "program's (set_matches cpu=(False, False))");
        return -1;
    }
    s.recordPage = page;
    s.recordSlot = slot;
    return 0;
}

int efz_env_play(EfzEnv* env, int32_t index, const char* path)
{
    if (!env || index < 0 || index >= env->n || !path || !*path)
        return -1;
    Finish(env);
    Unbound unbound;
    std::vector<uint8_t> b;
    if (FILE* f = OpenPath(path, "rb")) {
        uint8_t buf[65536];
        size_t n;
        while ((n = fread(buf, 1, sizeof(buf), f)) > 0)
            b.insert(b.end(), buf, buf + n);
        fclose(f);
    } else {
        env->SetError(std::string("cannot read ") + path);
        return -1;
    }
    auto word = [&](size_t at) { return (int)(int16_t)(b[at] | b[at + 1] << 8); };
    auto dword = [&](size_t at) {
        return (int32_t)(b[at] | b[at + 1] << 8 | b[at + 2] << 16 | (uint32_t)b[at + 3] << 24);
    };
    // The header CScene2 reads: P1, P2, [a version over 100,] stage, P1's palette, P2's.
    Match m;
    memset(&m, 0, sizeof(m));
    size_t at = 6;
    if (b.size() >= 12) {
        m.chars[0] = (int8_t)word(0);
        m.chars[1] = (int8_t)word(2);
        int stage = word(4);
        if (stage > 100) {
            stage = word(6);
            at = 8;
        }
        m.stage = (int8_t)stage;
        m.palettes[0] = (int8_t)word(at);
        m.palettes[1] = (int8_t)word(at + 2);
    }
    bool ok = b.size() >= 12 && word(0) >= 0 && word(0) < EFZ_CHARACTERS && word(2) >= 0 &&
              word(2) < EFZ_CHARACTERS && m.stage >= 0 && m.stage < EFZ_STAGES;
    if (!ok) {
        env->SetError(std::string("not a replay: ") + path);
        return -1;
    }
    // EfzRevival's block after the game's part ends with its offset and -1
    // (Game::readExtendedReplay): the game would read it as inputs.
    long game = (long)b.size();
    if (b.size() >= 28 && dword(b.size() - 4) == -1) {
        int32_t offset = dword(b.size() - 8);
        if (offset >= 12 && (size_t)offset + 16 <= b.size())
            game = offset;
    }
    game &= ~1L; // whole words
    Slot& s = env->slots[index];
    s.playNext = path;
    s.playMatch = m;
    s.playTrailer = (long)b.size() - game;
    return 0;
}

int efz_env_set_save_dir(EfzEnv* env, const char* dir)
{
    if (!env)
        return -1;
    Finish(env);
    SetDataDir(env->dataDir.c_str(), dir && *dir ? dir : env->dataDir.c_str());
    return 0;
}

int efz_env_set_gauges(EfzEnv* env, int32_t index, int32_t player, int32_t power, double rf,
                       int32_t blue)
{
    if (!env || index < 0 || index >= env->n || player < 0 || player > 1)
        return -1;
    Finish(env);
    Slot& s = env->slots[index];
    if (!s.started || s.broken)
        return -1;
    BindArena(s.arena);
    int ok = -1;
    if (SceneIndex() == 3) {
        CPlayer* p = Fight()->m_players[player];
        if (power >= 0)
            p->m_gauge = (short)std::min(power, 3000);
        if (rf >= 0)
            p->m_rfGauge = std::min(rf, 1000.0);
        if (blue >= 0)
            p->m_rfBlue = blue ? 1 : 0;
        WriteObs(env, s, ObsOf(env, env->obsOut, index));
        WriteInfo(s, env->info[index], -1, false);
        ok = 0;
    }
    BindArena(nullptr);
    return ok;
}

int efz_env_seed(EfzEnv* env, int32_t index, uint64_t seed)
{
    if (!env || index < 0 || index >= env->n)
        return -1;
    Finish(env);
    uint64_t state = seed;
    env->slots[index].ep.rng = SplitMix(state);
    return 0;
}

int efz_env_step_async(EfzEnv* env, const uint8_t* actions)
{
    if (!env)
        return -1;
    BindArena(nullptr);
    Finish(env);
    if (actions)
        memcpy(env->actions.data(), actions, env->actions.size());
    else
        memset(env->actions.data(), 0, env->actions.size());
    Pool::Get().Launch(env->job, env->n, [env](int i) { StepOne(env, i); });
    return 0;
}

int efz_env_step_wait(EfzEnv* env)
{
    if (!env)
        return -1;
    Finish(env);
    return 0;
}

int efz_env_step(EfzEnv* env, const uint8_t* actions)
{
    int r = efz_env_step_async(env, actions);
    if (r == 0)
        r = efz_env_step_wait(env);
    return r;
}

size_t efz_env_state_size(EfzEnv* env, int32_t index)
{
    if (!env || index < 0 || index >= env->n)
        return 0;
    Finish(env);
    BindArena(env->slots[index].arena);
    size_t size = sizeof(StateHeader) + ArenaUsed();
    BindArena(nullptr);
    return size;
}

size_t efz_env_save_state(EfzEnv* env, int32_t index, void* out, size_t size)
{
    size_t need = efz_env_state_size(env, index);
    if (!need || !out || size < need)
        return 0;
    Slot& s = env->slots[index];
    StateHeader h;
    memset(&h, 0, sizeof(h));
    h.magic = kStateMagic;
    h.version = EFZ_ENV_VERSION;
    h.arenaSize = need - sizeof(StateHeader);
    h.base = LibraryBase();
    h.ep = s.ep;
    memcpy(out, &h, sizeof(h));
    memcpy((char*)out + sizeof(h), s.arena, (size_t)h.arenaSize);
    return need;
}

int efz_env_load_state(EfzEnv* env, int32_t index, const void* state, size_t size)
{
    if (!env || index < 0 || index >= env->n || !state || size < sizeof(StateHeader))
        return -1;
    StateHeader h;
    memcpy(&h, state, sizeof(h));
    if (h.magic != kStateMagic || h.version != EFZ_ENV_VERSION ||
        h.arenaSize + sizeof(StateHeader) != size) {
        env->SetError("not a save state of this library");
        return -1;
    }
    if (h.base != LibraryBase()) {
        env->SetError("the state was saved where the library was loaded at another address "
                      "(another process): its objects' pointers would be wrong here");
        return -1;
    }
    Finish(env);
    int stackMark;
    SetStack(&stackMark);
    Slot& s = env->slots[index];
    BindArena(s.arena);
    EndReplay(s, false);
    LoadArena((const char*)state + sizeof(h), (uintptr_t)h.arenaSize);
    // Saved while recording or playing a replay back: a loaded game neither writes one
    // nor reads one (the file is the saving environment's), its players play on.
    if (Game()->m_replayMode == 1 || Game()->m_replayMode == 2) {
        Game()->m_replay.m_handle = NULL;
        Game()->m_replayMode = 0;
    }
    s.ep = h.ep;
    s.started = true;
    s.broken = false;
    s.pending = s.finished = false;
    env->reward[2 * index] = env->reward[2 * index + 1] = 0;
    env->terminated[index] = env->truncated[index] = 0;
    WriteObs(env, s, ObsOf(env, env->obsOut, index));
    WriteInfo(s, env->info[index], -1, false);
    BindArena(nullptr);
    return 0;
}

int efz_env_render(EfzEnv* env, int32_t index, uint8_t* rgb)
{
    if (!env || index < 0 || index >= env->n || !rgb || !env->cfg.drawing)
        return 0;
    BindArena(nullptr);
    Finish(env);
    std::vector<uint8_t> frame((size_t)640 * 480 * 3);
    BindArena(env->slots[index].arena);
    int w = 0, h = 0;
    bool ok = FrameRGB(frame.data(), &w, &h);
    BindArena(nullptr);
    if (!ok || w != EFZ_FRAME_WIDTH || h != EFZ_FRAME_HEIGHT)
        return 0;
    memcpy(rgb, frame.data(), (size_t)w * h * 3);
    return 1;
}

void efz_env_sound_log(int32_t on)
{
    SetSoundLog(on != 0);
}

int32_t efz_env_sound_events(EfzEnv* env, int32_t index, EfzSoundEvent* out, int32_t max)
{
    static_assert(sizeof(EfzSoundEvent) == sizeof(SoundEvent), "EfzSoundEvent");
    if (!env || index < 0 || index >= env->n || !out || max <= 0)
        return 0;
    BindArena(nullptr);
    Finish(env);
    BindArena(env->slots[index].arena);
    int n = TakeSoundEvents((SoundEvent*)out, max);
    BindArena(nullptr);
    return n;
}

uint64_t efz_env_ticks(const EfzEnv* env)
{
    return env ? env->ticks.load() : 0;
}

const char* efz_env_error(const EfzEnv* env)
{
    return env ? env->error.c_str() : "";
}

} // extern "C"
