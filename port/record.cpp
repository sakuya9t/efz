// The fight recorder: the records, the checks and the replay. See record.h and
// docs/logging.md.
//
// It reads the game's state in the harness's tick hooks (src/trace.cpp) and changes
// nothing in it, except when replaying: then it loads the recorded state at the first
// tick and supplies the controls.
#include <SDL3/SDL.h>
#include <cmath>
#include <stdarg.h>
#include <stdint.h>
#include <string>
#include <utility>
#include <vector>

#include "efz.h"
#include "platform.h"
#include "crash.h"
#include "log.h"
#include "record.h"

// src/scene3.cpp: one of F5-F8 is held, so that each press acts once.
extern int g_fkeyHeld;

namespace efz {

namespace {

const char* const kSceneNames[9] = {"title", "character select", "match setup", "fight", "?",
                                    "results", "config", "staff roll", "replays"};
const char* const kModeNames[7] = {"arcade", "practice", "arcade with score", "vs cpu",
                                   "vs human", "replay", "demo"};
// What CScene3::HandleKeys reads of the keyboard, as DIK_ codes: Esc, F1-F10, F11, F12.
const unsigned char kSysKeys[] = {0x01, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40,
                                  0x41, 0x42, 0x43, 0x44, 0x57, 0x58};
const int kSysKeyCount = (int)sizeof(kSysKeys);
const int kPatternCount = 0x1f9; // m_patterns and anims, one per pattern
// A player whose update stops this long while the round is on is reported: 10 s at the
// fight's 3 ticks a frame.
const long kStuckTicks = 1920;
// The state files a fight writes for its anomalies, at most.
const int kMaxSnapshots = 4;

const char* SceneName(int scene)
{
    return scene >= 0 && scene < 9 ? kSceneNames[scene] : "?";
}

const char* ModeName(int mode)
{
    return mode >= 0 && mode < 7 ? kModeNames[mode] : "?";
}

const char* Who(int player)
{
    return player < 0 ? "the game" : player ? "P2" : "P1";
}

// The shortest text that reads back as the same double; null for NaN and infinities,
// which JSON hasn't.
void FormatDouble(double d, char* out, size_t size)
{
    if (!std::isfinite(d)) {
        snprintf(out, size, "null");
        return;
    }
    for (int precision = 15; precision <= 17; precision++) {
        snprintf(out, size, "%.*g", precision, d);
        if (strtod(out, nullptr) == d)
            return;
    }
}

// A line of JSON, built in a fixed buffer.
struct Line {
    char text[16384];
    size_t n = 0;

    void Reset()
    {
        n = 0;
        text[0] = 0;
    }
    void Add(const char* s)
    {
        size_t k = strlen(s);
        if (n + k >= sizeof(text))
            k = sizeof(text) - 1 - n;
        memcpy(text + n, s, k);
        n += k;
        text[n] = 0;
    }
    void VPrintf(const char* format, va_list args)
    {
        int k = vsnprintf(text + n, sizeof(text) - n, format, args);
        if (k > 0)
            n = n + (size_t)k < sizeof(text) ? n + (size_t)k : sizeof(text) - 1;
    }
    void Printf(const char* format, ...) EFZ_PRINTF(2, 3)
    {
        va_list args;
        va_start(args, format);
        VPrintf(format, args);
        va_end(args);
    }
    void Double(double d)
    {
        char b[40];
        FormatDouble(d, b, sizeof(b));
        Add(b);
    }
    void String(const char* s)
    {
        char b[1024];
        JsonString(s, b, sizeof(b));
        Add(b);
    }
    void Hashes(const uint32_t* h)
    {
        for (int i = 0; i < TRACE_BLOCKS; i++)
            Printf("%08x", (unsigned)h[i]);
    }
};

uint32_t Fnv(const void* data, unsigned size)
{
    const unsigned char* p = (const unsigned char*)data;
    uint32_t h = 2166136261u;
    for (unsigned i = 0; i < size; i++) {
        h ^= p[i];
        h *= 16777619u;
    }
    return h;
}

// A player as the last tick left it: for the fight's end and the crash report, which
// can't look at the players themselves (a fight's end deletes them).
struct Observed {
    bool valid;
    char name[17];
    int cpu;
    int action, frame;
    double x, y;
    int hp, gauge, roundsWon;
};

struct Anomaly {
    const char* check;
    int player;
    long first, last, count;
};

// What a player's update last changed: for the stuck check.
struct Still {
    int action, frame, timer;
    long since;
};

struct Recorder {
    RecordOptions options;
    CGame* game = nullptr;
    CScene** scenes = nullptr;
    long sessionFrame = -1;
    int scene = -1;
    int fights = 0;
    // The fight scene's visit.
    bool inScene3 = false;
    long fightFrame = 0;
    bool started = false;
    long tick = 0;
    bool inTick = false;
    CScene3* fight = nullptr; // during the hooks
    intptr_t file = -1;
    char name[32] = "";
    char path[1100] = "";
    uint32_t rng = 0; // rand()'s state at the tick's start
    unsigned char in[2] = {0, 0};
    int prevIntro = 0, prevOver = 0, prevWon[2] = {0, 0};
    bool matchEnd = false;
    int winner = -1;
    int replayMode = 0;
    int paused = 0;
    unsigned keys = 0;   // the F-keys held, a bit per kSysKeys entry
    long keyFrame = -1;  // the fight frame whose keyboard was read last
    unsigned char pad[2] = {0, 0}; // GetInput outside the ticks
    Observed obs[2];
    Anomaly anomalies[64];
    int anomalyCount = 0;
    int snapshots = 0;
    Still still[2];
    Line line;
    Line event;
};
Recorder g;

// --- The state's files: the harness's dump format, a record per block of
// [tick, block, size] (32-bit, little-endian) and its bytes.

struct StateFile {
    intptr_t file;
    uint32_t tick;
    uint32_t hashes[TRACE_BLOCKS];
    bool ok;
};

void SaveBlock(void* context, int block, const void* data, unsigned size)
{
    StateFile* s = (StateFile*)context;
    s->hashes[block] = Fnv(data, size);
    if (s->file < 0)
        return;
    uint32_t header[3] = {s->tick, (uint32_t)block, size};
    s->ok = s->ok && RawWrite(s->file, header, sizeof(header)) && RawWrite(s->file, data, size);
}

// Writes the state to `name` in the session folder (no file: only hashes it).
bool SaveState(CScene3* scene, const char* name, long tick, uint32_t* hashes)
{
    StateFile s;
    s.file = -1;
    s.tick = (uint32_t)tick;
    s.ok = true;
    if (name) {
        char path[1100];
        if (!SessionPath(name, path, sizeof(path)) || (s.file = RawOpen(path, false)) < 0)
            return false;
    }
    TraceSaveState(scene, SaveBlock, &s);
    if (s.file >= 0)
        RawClose(s.file);
    if (hashes)
        memcpy(hashes, s.hashes, sizeof(s.hashes));
    return s.ok;
}

// --- The replay.

struct ReplayTick {
    long f;
    uint32_t rng;
    unsigned char in[2];
    bool hashed;
    uint32_t h[TRACE_BLOCKS];
};

// A recorded change of the F-keys or of GetInput outside the ticks, from fight frame f.
struct Change {
    long f;
    int player;
    unsigned value;
};

struct Replay {
    bool active = false;
    std::string path, dir;
    int chars[2] = {0, 0}, palettes[2] = {0, 0}, cpu[2] = {0, 0}, editColor[2] = {0, 0};
    int stage = 0, roundsToWin = 2, fkeyHeld = 0;
    uint32_t rng = 0;
    std::string stateFile, repCopy;
    long repOffset = 0;
    uint32_t stateHashes[TRACE_BLOCKS];
    std::vector<ReplayTick> ticks;
    std::vector<Change> keys, pads;
    std::vector<unsigned char> state;
    const void* blocks[TRACE_BLOCKS];
    unsigned sizes[TRACE_BLOCKS];
    bool loaded = false, done = false;
    long firstDiff = -1, diffs = 0, compared = 0;
};
Replay r;

// JSON, as much as the records need: a small reader into a tree.
struct Json {
    enum Kind { kNull, kBool, kNumber, kString, kArray, kObject };
    Kind kind = kNull;
    double number = 0;
    std::string text;
    std::vector<Json> items;
    std::vector<std::pair<std::string, Json>> members;

    const Json* Get(const char* key) const
    {
        for (const auto& m : members) {
            if (m.first == key)
                return &m.second;
        }
        return nullptr;
    }
    double Number(const char* key, double fallback = 0) const
    {
        const Json* j = Get(key);
        return j && j->kind == kNumber ? j->number : fallback;
    }
    std::string String(const char* key) const
    {
        const Json* j = Get(key);
        return j && j->kind == kString ? j->text : std::string();
    }
    double At(size_t i) const
    {
        return i < items.size() && items[i].kind == kNumber ? items[i].number : 0;
    }
};

struct JsonReader {
    const char* p;
    const char* end;

    void Space()
    {
        while (p < end && (*p == ' ' || *p == '\t' || *p == '\r' || *p == '\n'))
            p++;
    }
    bool Word(const char* word)
    {
        size_t n = strlen(word);
        if ((size_t)(end - p) < n || strncmp(p, word, n) != 0)
            return false;
        p += n;
        return true;
    }
    bool String(std::string& out)
    {
        if (p >= end || *p != '"')
            return false;
        p++;
        while (p < end && *p != '"') {
            if (*p != '\\') {
                out += *p++;
                continue;
            }
            if (++p >= end)
                return false;
            char c = *p++;
            switch (c) {
            case 'n': out += '\n'; break;
            case 't': out += '\t'; break;
            case 'r': out += '\r'; break;
            case 'b': out += '\b'; break;
            case 'f': out += '\f'; break;
            case 'u': {
                if (end - p < 4)
                    return false;
                char hex[5] = {p[0], p[1], p[2], p[3], 0};
                unsigned v = (unsigned)strtoul(hex, nullptr, 16);
                p += 4;
                if (v < 0x80) {
                    out += (char)v;
                } else if (v < 0x800) {
                    out += (char)(0xc0 | (v >> 6));
                    out += (char)(0x80 | (v & 0x3f));
                } else {
                    out += (char)(0xe0 | (v >> 12));
                    out += (char)(0x80 | ((v >> 6) & 0x3f));
                    out += (char)(0x80 | (v & 0x3f));
                }
                break;
            }
            default: out += c;
            }
        }
        if (p >= end)
            return false;
        p++;
        return true;
    }
    bool Value(Json& v)
    {
        Space();
        if (p >= end)
            return false;
        switch (*p) {
        case '{':
            p++;
            v.kind = Json::kObject;
            Space();
            if (p < end && *p == '}') {
                p++;
                return true;
            }
            for (;;) {
                Space();
                std::string key;
                if (!String(key))
                    return false;
                Space();
                if (p >= end || *p++ != ':')
                    return false;
                v.members.emplace_back(std::move(key), Json());
                if (!Value(v.members.back().second))
                    return false;
                Space();
                if (p < end && *p == ',') {
                    p++;
                    continue;
                }
                return p < end && *p++ == '}';
            }
        case '[':
            p++;
            v.kind = Json::kArray;
            Space();
            if (p < end && *p == ']') {
                p++;
                return true;
            }
            for (;;) {
                v.items.emplace_back();
                if (!Value(v.items.back()))
                    return false;
                Space();
                if (p < end && *p == ',') {
                    p++;
                    continue;
                }
                return p < end && *p++ == ']';
            }
        case '"':
            v.kind = Json::kString;
            return String(v.text);
        case 't':
            v.kind = Json::kBool;
            v.number = 1;
            return Word("true");
        case 'f':
            v.kind = Json::kBool;
            return Word("false");
        case 'n':
            return Word("null");
        default: {
            char* e;
            v.number = strtod(p, &e);
            if (e == p)
                return false;
            p = e;
            v.kind = Json::kNumber;
            return true;
        }
        }
    }
};

bool ParseJson(const char* begin, const char* end, Json& out)
{
    JsonReader reader = {begin, end};
    if (!reader.Value(out))
        return false;
    reader.Space();
    return reader.p == end;
}

bool ParseHashes(const std::string& text, uint32_t* h)
{
    if (text.size() != TRACE_BLOCKS * 8)
        return false;
    for (int i = 0; i < TRACE_BLOCKS; i++)
        h[i] = (uint32_t)strtoul(text.substr(i * 8, 8).c_str(), nullptr, 16);
    return true;
}

bool LoadState(const std::string& path)
{
    size_t size = 0;
    unsigned char* data = (unsigned char*)SDL_LoadFile(path.c_str(), &size);
    if (!data) {
        LogError("replay", "cannot read the state %s: %s", path.c_str(), SDL_GetError());
        return false;
    }
    r.state.assign(data, data + size);
    SDL_free(data);
    bool seen[TRACE_BLOCKS] = {};
    size_t at = 0;
    while (at + 12 <= r.state.size()) {
        uint32_t header[3];
        memcpy(header, &r.state[at], sizeof(header));
        at += 12;
        if (header[1] >= TRACE_BLOCKS || at + header[2] > r.state.size())
            break;
        r.blocks[header[1]] = &r.state[at];
        r.sizes[header[1]] = header[2];
        seen[header[1]] = true;
        at += header[2];
    }
    for (int i = 0; i < TRACE_BLOCKS; i++) {
        if (!seen[i]) {
            LogError("replay", "the state %s has no block %s", path.c_str(), TraceBlockName(i));
            return false;
        }
    }
    return true;
}

bool LoadRecord(const char* path)
{
    size_t size = 0;
    char* data = (char*)SDL_LoadFile(path, &size);
    if (!data) {
        LogError("replay", "cannot read %s: %s", path, SDL_GetError());
        return false;
    }
    r.path = path;
    size_t slash = r.path.find_last_of("/\\");
    r.dir = slash == std::string::npos ? "." : r.path.substr(0, slash);
    bool header = false;
    long lineNumber = 0;
    for (const char* p = data; p < data + size;) {
        const char* nl = (const char*)memchr(p, '\n', (size_t)(data + size - p));
        const char* e = nl ? nl : data + size;
        lineNumber++;
        Json j;
        if (e > p && !ParseJson(p, e, j)) {
            // The last line of a record cut by a crash is expected.
            if (nl)
                LogWarn("replay", "%s:%ld isn't JSON; left out", path, lineNumber);
        } else if (e > p) {
            std::string type = j.String("type");
            if (type == "fight" && !header) {
                header = true;
                if (j.String("format") != "efz-fight" || j.Number("version") != 1) {
                    LogError("replay", "%s isn't an efz-fight record of version 1", path);
                    SDL_free(data);
                    return false;
                }
                const Json* players = j.Get("players");
                for (int i = 0; i < 2; i++) {
                    if (!players || players->items.size() != 2) {
                        LogError("replay", "%s has no players", path);
                        SDL_free(data);
                        return false;
                    }
                    const Json& p = players->items[i];
                    r.chars[i] = (int)p.Number("char");
                    r.palettes[i] = (int)p.Number("palette");
                    r.cpu[i] = (int)p.Number("cpu");
                    r.editColor[i] = (int)p.Number("edit_color");
                }
                r.stage = (int)j.Number("stage");
                r.roundsToWin = (int)j.Number("rounds_to_win", 2);
                r.rng = (uint32_t)j.Number("rng");
                r.fkeyHeld = (int)j.Number("fkey_held");
                r.stateFile = j.String("state");
                r.repCopy = j.String("replay_copy");
                r.repOffset = (long)j.Number("replay_offset");
                if (!ParseHashes(j.String("state_hashes"), r.stateHashes)) {
                    LogError("replay", "%s has no state_hashes", path);
                    SDL_free(data);
                    return false;
                }
            } else if (type == "tick") {
                ReplayTick t;
                if ((long)j.Number("t", -1) != (long)r.ticks.size()) {
                    LogError("replay", "%s:%ld: tick %ld where %ld was due", path, lineNumber,
                             (long)j.Number("t", -1), (long)r.ticks.size());
                    SDL_free(data);
                    return false;
                }
                t.f = (long)j.Number("f");
                t.rng = (uint32_t)j.Number("rng");
                const Json* in = j.Get("in");
                t.in[0] = in ? (unsigned char)in->At(0) : 0;
                t.in[1] = in ? (unsigned char)in->At(1) : 0;
                t.hashed = ParseHashes(j.String("h"), t.h);
                r.ticks.push_back(t);
            } else if (type == "keys") {
                Change c = {(long)j.Number("f"), -1, 0};
                const Json* down = j.Get("down");
                for (size_t k = 0; down && k < down->items.size(); k++) {
                    for (int i = 0; i < kSysKeyCount; i++) {
                        if ((int)down->At(k) == kSysKeys[i])
                            c.value |= 1u << i;
                    }
                }
                r.keys.push_back(c);
            } else if (type == "pad") {
                Change c = {(long)j.Number("f"), (int)j.Number("p"), (unsigned)j.Number("v")};
                r.pads.push_back(c);
            }
        }
        p = e + 1;
    }
    SDL_free(data);
    if (!header || r.ticks.empty()) {
        LogError("replay", "%s has %s", path, header ? "no ticks" : "no header");
        return false;
    }
    return LoadState(r.dir + "/" + r.stateFile);
}

// The recorded F-keys or GetInput outside the ticks, as of fight frame f.
unsigned ValueAt(const std::vector<Change>& changes, long f, int player)
{
    unsigned value = 0;
    for (const Change& c : changes) {
        if (c.f > f)
            break;
        if (c.player == player)
            value = c.value;
    }
    return value;
}

// At the first tick: the recorded state, and the files and globals it goes with.
bool ReplayLoad(CScene3* scene)
{
    CGame* game = scene->m_game;
    for (int i = 0; i < 2; i++) {
        if (scene->m_players[i]->m_charId != r.chars[i]) {
            LogError("replay", "P%d is character %d, the record's %d", i + 1,
                     scene->m_players[i]->m_charId, r.chars[i]);
            return false;
        }
    }
    int bad = TraceLoadState(scene, r.blocks, r.sizes);
    if (bad >= 0) {
        LogError("replay", "the state's block %s has %u bytes where this build has others",
                 TraceBlockName(bad), r.sizes[bad]);
        return false;
    }
    srand(r.rng);
    g_fkeyHeld = r.fkeyHeld;
    // The replay file the fight read or wrote: the record's copy, or a scratch file.
    if (game->m_replayMode == 1) {
        std::string copy = r.dir + "/" + r.repCopy;
        FILE* f = r.repCopy.empty() ? nullptr : OpenUtf8(copy.c_str(), "rb");
        if (!f) {
            LogError("replay", "the fight played a replay, and its copy %s is missing",
                     copy.c_str());
            return false;
        }
        fseek(f, r.repOffset, SEEK_SET);
        game->m_replay.m_handle = AdoptFile(f);
    } else if (game->m_replayMode == 2) {
        char scratch[1100];
        FILE* f = SessionPath("replay-scratch.rep", scratch, sizeof(scratch))
                      ? OpenUtf8(scratch, "w+b")
                      : nullptr;
        game->m_replay.m_handle = f ? AdoptFile(f) : 0;
    }
    uint32_t h[TRACE_BLOCKS];
    SaveState(scene, nullptr, 0, h);
    for (int i = 0; i < TRACE_BLOCKS; i++) {
        if (h[i] != r.stateHashes[i]) {
            LogError("replay", "the loaded state's block %s doesn't hash as recorded",
                     TraceBlockName(i));
            return false;
        }
    }
    LogInfo("replay", "loaded the recorded state at the first tick");
    return true;
}

void Compare(const uint32_t* hashes)
{
    long t = g.tick;
    if (!r.loaded || t >= (long)r.ticks.size())
        return;
    const ReplayTick& rec = r.ticks[t];
    char what[256] = "";
    size_t n = 0;
    auto note = [&](const char* s) {
        n += (size_t)snprintf(what + n, sizeof(what) - n, "%s%s", n ? ", " : "", s);
        if (n >= sizeof(what))
            n = sizeof(what) - 1;
    };
    if (hashes && rec.hashed) {
        for (int i = 0; i < TRACE_BLOCKS; i++) {
            if (hashes[i] != rec.h[i])
                note(TraceBlockName(i));
        }
    }
    if (g.rng != rec.rng)
        note("rand");
    if (g.fightFrame != rec.f)
        note("frame");
    if (g.in[0] != rec.in[0] || g.in[1] != rec.in[1])
        note("input");
    r.compared++;
    if (n) {
        r.diffs++;
        if (r.firstDiff < 0) {
            r.firstDiff = t;
            char state[48];
            snprintf(state, sizeof(state), "desync-t%06ld.state", t);
            bool saved = SaveState(g.fight, state, t, nullptr);
            LogError("replay", "tick %ld differs from the record: %s%s%s", t, what,
                     saved ? "; this state is in " : "", saved ? state : "");
        }
    }
    if (t + 1 == (long)r.ticks.size())
        r.done = true;
}

// --- The record.

void WriteLine(Line& l)
{
    if (g.file >= 0 && !RawWrite(g.file, l.text, l.n)) {
        LogError("record", "cannot write %s; the fight's record stops here", g.name);
        RawClose(g.file);
        g.file = -1;
    }
}

void Event(const char* format, ...) EFZ_PRINTF(1, 2);
void Event(const char* format, ...)
{
    if (g.file < 0)
        return;
    Line& l = g.event;
    l.Reset();
    va_list args;
    va_start(args, format);
    l.VPrintf(format, args);
    va_end(args);
    l.Add("\n");
    WriteLine(l);
}

void KeysEvent()
{
    Line& l = g.event;
    l.Reset();
    l.Printf("{\"type\":\"keys\",\"f\":%ld,\"down\":[", g.keyFrame);
    int n = 0;
    for (int i = 0; i < kSysKeyCount; i++) {
        if (g.keys & (1u << i))
            l.Printf("%s%d", n++ ? "," : "", kSysKeys[i]);
    }
    l.Add("]}\n");
    WriteLine(l);
}

void PlayerName(CPlayer* p, char* out)
{
    memcpy(out, p->m_name, 16);
    out[16] = 0;
}

void Observe(CScene3* scene)
{
    for (int i = 0; i < 2; i++) {
        CPlayer* p = scene->m_players[i];
        Observed& o = g.obs[i];
        o.valid = true;
        PlayerName(p, o.name);
        o.cpu = p->m_cpu != 0;
        o.action = p->pattern;
        o.frame = p->frame;
        o.x = p->x;
        o.y = p->y;
        o.hp = p->m_hp;
        o.gauge = p->m_gauge;
        o.roundsWon = p->m_roundsWon;
    }
}

// A copy of the .rep the fight plays, from where its next word is read. A replayed
// fight's is the record's copy: the replay's game has no replay files.
void CopyReplay(CGame* game, Line& l)
{
    char name[40];
    snprintf(name, sizeof(name), "replay\\data%d-%d.rep", game->m_replayPage + 1,
             game->m_replaySlot + 1);
    FILE* in = r.active ? OpenUtf8((r.dir + "/" + r.repCopy).c_str(), "rb")
                        : OpenGameFile(name, "rb");
    char copy[48], path[1100];
    snprintf(copy, sizeof(copy), "%s.rep", g.name);
    intptr_t out = in && SessionPath(copy, path, sizeof(path)) ? RawOpen(path, false) : -1;
    long size = 0;
    bool ok = in && out >= 0;
    char buffer[4096];
    size_t k;
    while (ok && (k = fread(buffer, 1, sizeof(buffer), in)) > 0) {
        ok = RawWrite(out, buffer, k);
        size += (long)k;
    }
    if (in)
        fclose(in);
    if (out >= 0)
        RawClose(out);
    l.Add("\"replay_file\":");
    l.String(name);
    if (!ok) {
        LogWarn("record", "cannot copy %s for %s: the record can't be replayed", name, g.name);
        l.Add(",");
        return;
    }
    l.Printf(",\"replay_copy\":\"%s\",\"replay_offset\":%ld,", copy,
             size - (long)game->m_replay.m_remaining);
}

void BeginFight(CScene3* scene)
{
    CGame* game = scene->m_game;
    CPlayer* p[2] = {scene->m_players[0], scene->m_players[1]};
    char names[2][17];
    PlayerName(p[0], names[0]);
    PlayerName(p[1], names[1]);
    g.started = true;
    g.tick = 0;
    g.fights++;
    snprintf(g.name, sizeof(g.name), "fight-%03d", g.fights);
    g.prevIntro = (char)game->m_intro;
    g.prevOver = game->m_roundOver != 0;
    g.prevWon[0] = p[0]->m_roundsWon;
    g.prevWon[1] = p[1]->m_roundsWon;
    g.matchEnd = false;
    g.winner = -1;
    g.anomalyCount = 0;
    g.snapshots = 0;
    for (int i = 0; i < 2; i++)
        g.still[i] = Still{-1, -1, -1, 0};
    CountSession("fights");
    LogInfo("fight", "fight %d: %s (P1, %s) vs %s (P2, %s), stage %d, %s%s", g.fights, names[0],
            p[0]->m_cpu ? "cpu" : "human", names[1], p[1]->m_cpu ? "cpu" : "human",
            game->m_stage, ModeName(game->m_gameMode),
            game->m_replayMode == 1   ? ", playing a replay"
            : game->m_replayMode == 2 ? ", recording a replay"
                                      : "");
    if (!g.options.record)
        return;

    char file[48];
    snprintf(file, sizeof(file), "%s.jsonl", g.name);
    if (!SessionPath(file, g.path, sizeof(g.path))) {
        g.path[0] = 0;
        return;
    }
    g.file = RawOpen(g.path, false);
    if (g.file < 0) {
        LogError("record", "cannot write %s", g.path);
        return;
    }
    snprintf(file, sizeof(file), "%s.state", g.name);
    uint32_t hashes[TRACE_BLOCKS];
    if (!SaveState(scene, file, 0, hashes))
        LogError("record", "cannot write %s: the record can't be replayed", file);

    char time[48];
    IsoTime(time, sizeof(time));
    Line& l = g.event;
    l.Reset();
    l.Printf("{\"type\":\"fight\",\"format\":\"efz-fight\",\"version\":1,\"session\":\"%s\","
             "\"fight\":%d,\"started\":\"%s\",\"session_frame\":%ld,\"build\":{%s},",
             SessionId(), g.fights, time, g.sessionFrame, BuildJson());
    if (r.active) {
        l.Add("\"replay_of\":");
        l.String(r.path.c_str());
        l.Add(",");
    }
    l.Printf("\"mode\":%d,\"mode_name\":\"%s\",\"replay_mode\":%d,", game->m_gameMode,
             ModeName(game->m_gameMode), game->m_replayMode);
    if (game->m_replayMode == 1)
        CopyReplay(game, l);
    l.Printf("\"stage\":%d,\"round\":%d,\"rounds_to_win\":%d,\"cpu_level\":%d,"
             "\"draw_every_frame\":%d,\"players\":[",
             game->m_stage, game->m_round, game->m_roundsToWin, game->m_cpuLevel,
             game->m_drawEveryFrame);
    for (int i = 0; i < 2; i++) {
        l.Printf("%s{\"side\":%d,\"char\":%d,\"name\":", i ? "," : "", i, p[i]->m_charId);
        l.String(names[i]);
        l.Printf(",\"palette\":%d,\"cpu\":%d,\"cpu_skill\":", p[i]->m_paletteIndex,
                 p[i]->m_cpu != 0);
        l.Double(p[i]->m_cpuSkill);
        l.Printf(",\"edit_color\":%d}", game->m_editColor[i] != 0);
    }
    l.Printf("],\"rng\":%u,\"fkey_held\":%d,\"state\":\"%s.state\",\"state_hashes\":\"",
             (unsigned)RandState(), g_fkeyHeld, g.name);
    l.Hashes(hashes);
    l.Add("\",\"player_fields\":[\"action\",\"frame\",\"x\",\"y\",\"vx\",\"vy\",\"facing\","
          "\"hp\",\"gauge\",\"guard\",\"rf\",\"combo\",\"combo_damage\",\"hitstop\","
          "\"freeze\",\"command\",\"rounds_won\",\"objects\"],"
          "\"game_fields\":[\"round\",\"intro\",\"round_over\"],\"blocks\":[");
    for (int i = 0; i < TRACE_BLOCKS; i++)
        l.Printf("%s\"%s\"", i ? "," : "", TraceBlockName(i));
    l.Add("]}\n");
    WriteLine(l);
    // The F-keys and the controls as the fight began.
    if (g.keys)
        KeysEvent();
    for (int i = 0; i < 2; i++) {
        if (g.pad[i])
            Event("{\"type\":\"pad\",\"f\":%ld,\"p\":%d,\"v\":%u}", g.fightFrame, i, g.pad[i]);
    }
}

void EndFight(const char* reason)
{
    if (!g.started)
        return;
    g.started = false;
    for (int i = 0; i < g.anomalyCount; i++) {
        const Anomaly& a = g.anomalies[i];
        if (a.count > 1)
            LogWarn("check", "fight %d: %s, %s, on %ld ticks in all, %ld to %ld", g.fights,
                    a.check, Who(a.player), a.count, a.first, a.last);
    }
    int winner = g.matchEnd ? g.winner : -1;
    if (g.file >= 0) {
        Line& l = g.event;
        l.Reset();
        l.Printf("{\"type\":\"end\",\"t\":%ld,\"f\":%ld,\"reason\":\"%s\",\"winner\":%d,"
                 "\"rounds_won\":[%d,%d],\"hp\":[%d,%d],\"anomalies\":{",
                 g.tick, g.fightFrame, reason, winner, g.obs[0].roundsWon, g.obs[1].roundsWon,
                 g.obs[0].hp, g.obs[1].hp);
        for (int i = 0; i < g.anomalyCount; i++) {
            const Anomaly& a = g.anomalies[i];
            l.Printf("%s\"%s/%s\":%ld", i ? "," : "", a.check,
                     a.player < 0 ? "game" : a.player ? "p2" : "p1", a.count);
        }
        l.Add("}}\n");
        WriteLine(l);
        if (g.file >= 0)
            RawClose(g.file);
        g.file = -1;
    }
    char result[64] = "";
    if (winner >= 0)
        snprintf(result, sizeof(result), ", P%d %s won %d-%d", winner + 1, g.obs[winner].name,
                 g.obs[winner].roundsWon, g.obs[1 - winner].roundsWon);
    LogInfo("fight", "fight %d ended (%s%s) after %ld ticks%s%s", g.fights, reason, result,
            g.tick, g.path[0] ? "; record " : "", g.path[0] ? g.path : "");
    g.path[0] = 0;
}

// --- The checks: what the game's state should never be. Each kind is logged the first
// tick it shows in a fight (with the state, in a file), and counted after.

void Flag(LogLevel level, const char* check, int player, const char* format, ...)
    EFZ_PRINTF(4, 5);
void Flag(LogLevel level, const char* check, int player, const char* format, ...)
{
    Anomaly* a = nullptr;
    for (int i = 0; i < g.anomalyCount && !a; i++) {
        if (g.anomalies[i].check == check && g.anomalies[i].player == player)
            a = &g.anomalies[i];
    }
    if (!a) {
        if (g.anomalyCount == (int)(sizeof(g.anomalies) / sizeof(g.anomalies[0])))
            return;
        a = &g.anomalies[g.anomalyCount++];
        *a = Anomaly{check, player, g.tick, g.tick, 0};
    }
    a->count++;
    a->last = g.tick;
    if (a->count > 1)
        return;
    char detail[512];
    va_list args;
    va_start(args, format);
    vsnprintf(detail, sizeof(detail), format, args);
    va_end(args);
    Log(level, "check", "fight %d tick %ld: %s, %s: %s", g.fights, g.tick, check, Who(player),
        detail);
    CountSession("anomalies");
    if (g.file < 0)
        return;
    char state[48] = "";
    if (g.snapshots < kMaxSnapshots) {
        snprintf(state, sizeof(state), "%s-t%06ld.state", g.name, g.tick);
        if (SaveState(g.fight, state, g.tick, nullptr))
            g.snapshots++;
        else
            state[0] = 0;
    }
    Line& l = g.event;
    l.Reset();
    l.Printf("{\"type\":\"anomaly\",\"t\":%ld,\"f\":%ld,\"check\":\"%s\",\"player\":%d,"
             "\"level\":\"%s\",\"detail\":",
             g.tick, g.fightFrame, check, player, level >= kLogError ? "error" : "warn");
    l.String(detail);
    if (state[0])
        l.Printf(",\"state\":\"%s\"", state);
    l.Add("}\n");
    WriteLine(l);
}

bool Finite(const ObjBase& o)
{
    return std::isfinite(o.x) && std::isfinite(o.y) && std::isfinite(o.vx) &&
           std::isfinite(o.vy) && std::isfinite(o.ax) && std::isfinite(o.ay);
}

void CheckPlayer(CScene3* scene, int i)
{
    CPlayer* p = scene->m_players[i];
    CPlayer* other = scene->m_players[1 - i];
    CGame* game = scene->m_game;
    if (!Finite(*p))
        Flag(kLogError, "nonfinite", i, "x %g y %g vx %g vy %g ax %g ay %g", p->x, p->y,
                 p->vx, p->vy, p->ax, p->ay);
    else if (p->x < -100 || p->x > 740 || p->y > 100 || p->y < -2000)
        Flag(kLogWarn, "position", i, "x %.2f y %.2f (the stage is x 20 to 619, y 0 on "
                 "the ground)", p->x, p->y);
    if (p->facing != 1 && p->facing != -1)
        Flag(kLogError, "facing", i, "facing %d", p->facing);
    PatternData* patterns = (PatternData*)p->m_patterns;
    EffectAnim* anims = (EffectAnim*)p->anims;
    if (p->pattern >= kPatternCount) {
        Flag(kLogError, "action", i, "action %d, beyond the %d", p->pattern, kPatternCount);
    } else {
        if (patterns && !(PatternFrame*)patterns[p->pattern].frames)
            Flag(kLogError, "action", i, "action %d has no frames", p->pattern);
        if (anims && anims[p->pattern].frameCount && p->frame >= anims[p->pattern].frameCount)
            Flag(kLogError, "frame", i, "frame %d of action %d, which has %d", p->frame,
                     p->pattern, anims[p->pattern].frameCount);
    }
    if (p->m_hp > 9999 || p->m_hp < -9999)
        Flag(kLogWarn, "hp", i, "hp %d", p->m_hp);
    if (p->m_gauge < 0 || p->m_gauge > 3000)
        Flag(kLogWarn, "gauge", i, "gauge %d", p->m_gauge);
    double guard = p->m_guardGauge;
    if (!(guard >= 0 && guard <= 360))
        Flag(kLogWarn, "guard_gauge", i, "guard gauge %g", guard);
    if (!(p->m_rfGauge >= 0 && p->m_rfGauge <= 1000))
        Flag(kLogWarn, "rf_gauge", i, "RF gauge %g", p->m_rfGauge);
    if (p->m_comboHits < 0 || (p->m_comboHits > 0 && p->m_comboDamage < 0))
        Flag(kLogWarn, "combo", i, "%d hits, %d damage", p->m_comboHits, p->m_comboDamage);
    if (p->m_hitstop < 0 || p->m_freezeTime < 0)
        Flag(kLogWarn, "timers", i, "hitstop %d, freeze %d", p->m_hitstop, p->m_freezeTime);
    for (int j = 0; j < 0x40; j++) {
        if (!p->m_objectActive[j])
            continue;
        const PlayerObject& o = p->m_objects[j];
        if (!Finite(o))
            Flag(kLogError, "object_nonfinite", i, "object %d (action %d): x %g y %g vx %g "
                     "vy %g", j, o.pattern, o.x, o.y, o.vx, o.vy);
        if (o.pattern >= kPatternCount)
            Flag(kLogError, "object_action", i, "object %d: action %d, beyond the %d", j,
                     o.pattern, kPatternCount);
        else if (anims && anims[o.pattern].frameCount && o.frame >= anims[o.pattern].frameCount)
            Flag(kLogError, "object_frame", i, "object %d: frame %d of action %d, which "
                     "has %d", j, o.frame, o.pattern, anims[o.pattern].frameCount);
    }
    // Stuck: the round is on and nothing stops the player, yet its action, frame and the
    // ticks on that frame stay as they are.
    Still& s = g.still[i];
    bool live = game->m_intro == 0 && game->m_roundOver == 0 && p->m_hitstop == 0 &&
                other->m_freezeTime == 0;
    if (live && s.action == p->pattern && s.frame == p->frame && s.timer == p->timer) {
        if (g.tick - s.since >= kStuckTicks)
            Flag(kLogWarn, "stuck", i, "action %d frame %d hasn't moved for %ld ticks",
                     p->pattern, p->frame, g.tick - s.since);
    } else {
        s = Still{p->pattern, p->frame, p->timer, g.tick};
    }
}

void Check(CScene3* scene)
{
    CheckPlayer(scene, 0);
    CheckPlayer(scene, 1);
    CGame* game = scene->m_game;
    if (game->m_effectHead < 0 || game->m_effectHead >= 0x280 || game->m_effectTail < 0 ||
        game->m_effectTail >= 0x280)
        Flag(kLogError, "effects", -1, "the effects' ring at %d to %d, of 640",
                 game->m_effectHead, game->m_effectTail);
    if (scene->m_speed < 1 || scene->m_speed > 3)
        Flag(kLogWarn, "speed", -1, "%d ticks a frame", scene->m_speed);
}

// Rounds and the match, as the game's state changes.
void Events(CScene3* scene)
{
    CGame* game = scene->m_game;
    CPlayer* p0 = scene->m_players[0];
    CPlayer* p1 = scene->m_players[1];
    int intro = (char)game->m_intro;
    int over = game->m_roundOver != 0;
    if (g.prevIntro != 0 && intro == 0)
        Event("{\"type\":\"event\",\"t\":%ld,\"f\":%ld,\"event\":\"round_start\",\"round\":%d}",
              g.tick, g.fightFrame, game->m_round);
    if (!g.prevOver && over) {
        int a = p0->m_roundsWon != g.prevWon[0];
        int b = p1->m_roundsWon != g.prevWon[1];
        int winner = a && b ? -1 : a ? 0 : b ? 1 : -1;
        Event("{\"type\":\"event\",\"t\":%ld,\"f\":%ld,\"event\":\"round_end\",\"winner\":%d,"
              "\"rounds_won\":[%d,%d],\"hp\":[%d,%d]}",
              g.tick, g.fightFrame, winner, p0->m_roundsWon, p1->m_roundsWon, p0->m_hp,
              p1->m_hp);
    }
    if (scene->m_leave == 2 && !g.matchEnd) {
        g.matchEnd = true;
        g.winner = game->m_winner;
        Event("{\"type\":\"event\",\"t\":%ld,\"f\":%ld,\"event\":\"match_end\",\"winner\":%d}",
              g.tick, g.fightFrame, g.winner);
    }
    g.prevIntro = intro;
    g.prevOver = over;
    g.prevWon[0] = p0->m_roundsWon;
    g.prevWon[1] = p1->m_roundsWon;
    g.replayMode = game->m_replayMode;
}

void WriteTick(CScene3* scene, const uint32_t* hashes)
{
    if (g.file < 0)
        return;
    CGame* game = scene->m_game;
    Line& l = g.line;
    l.Reset();
    l.Printf("{\"type\":\"tick\",\"t\":%ld,\"f\":%ld,\"rng\":%u,\"in\":[%u,%u],\"g\":[%d,%d,%d],"
             "\"p\":[",
             g.tick, g.fightFrame, (unsigned)g.rng, g.in[0], g.in[1], game->m_round,
             (char)game->m_intro, game->m_roundOver != 0);
    for (int i = 0; i < 2; i++) {
        CPlayer* p = scene->m_players[i];
        int objects = 0;
        for (int j = 0; j < 0x40; j++)
            objects += p->m_objectActive[j] != 0;
        l.Printf("%s[%d,%d,", i ? "," : "", p->pattern, p->frame);
        l.Double(p->x);
        l.Add(",");
        l.Double(p->y);
        l.Add(",");
        l.Double(p->vx);
        l.Add(",");
        l.Double(p->vy);
        l.Printf(",%d,%d,%d,", p->facing, p->m_hp, p->m_gauge);
        l.Double(p->m_guardGauge);
        l.Add(",");
        l.Double(p->m_rfGauge);
        l.Printf(",%d,%d,%d,%d,%d,%d,%d]", p->m_comboHits, p->m_comboDamage, p->m_hitstop,
                 p->m_freezeTime, p->m_command, p->m_roundsWon, objects);
    }
    l.Add("]");
    if (hashes) {
        l.Add(",\"h\":\"");
        l.Hashes(hashes);
        l.Add("\"");
    }
    l.Add("}\n");
    WriteLine(l);
}

// A player's input this tick as the bits of a replay's input word: for a human what
// ReadInput read (the buttons held), for the CPU what it chose (the buttons pressed).
unsigned char EffectiveInput(CPlayer* p)
{
    unsigned char bits = 0;
    if (p->m_inputY < 0)
        bits |= kInputUp;
    else if (p->m_inputY > 0)
        bits |= kInputDown;
    if (p->m_inputX > 0)
        bits |= kInputRight;
    else if (p->m_inputX < 0)
        bits |= kInputLeft;
    bool cpu = p->m_cpu != 0;
    if (cpu ? p->m_pressA != 0 : p->m_holdA != 0)
        bits |= kInputA;
    if (cpu ? p->m_pressB != 0 : p->m_holdB != 0)
        bits |= kInputB;
    if (cpu ? p->m_pressC != 0 : p->m_holdC != 0)
        bits |= kInputC;
    if (cpu ? p->m_pressD != 0 : p->m_holdD != 0)
        bits |= kInputD;
    return bits;
}

// --- The hooks.

void EnterFightScene()
{
    g.inScene3 = true;
    g.fightFrame = 0;
    g.keyFrame = -1;
    g.keys = 0;
    g.pad[0] = g.pad[1] = 0;
    g.paused = 0;
    g.started = false;
    g.tick = 0;
}

void OnTickStart(CScene3* scene)
{
    if (!g.inScene3)
        EnterFightScene();
    g.fight = scene;
    if (!g.started) {
        if (r.active && !r.loaded && !r.done) {
            r.loaded = ReplayLoad(scene);
            if (!r.loaded) {
                r.done = true;
                RequestQuit();
            }
        }
        BeginFight(scene);
    }
    g.rng = RandState();
    g.inTick = true;
}

void OnInputsRead(CScene3* scene)
{
    g.in[0] = EffectiveInput(scene->m_players[0]);
    g.in[1] = EffectiveInput(scene->m_players[1]);
}

void OnTick(CScene3* scene, const unsigned* traceHashes)
{
    uint32_t hashes[TRACE_BLOCKS];
    if (traceHashes) {
        for (int i = 0; i < TRACE_BLOCKS; i++)
            hashes[i] = traceHashes[i];
    }
    g.fight = scene;
    if (!g.started) { // a tick without its start: not this hook's fight
        g.inTick = false;
        return;
    }
    Check(scene);
    Events(scene);
    WriteTick(scene, traceHashes ? hashes : nullptr);
    if (r.active)
        Compare(traceHashes ? hashes : nullptr);
    Observe(scene);
    g.tick++;
    g.inTick = false;
}

int OnInput(BYTE player, BYTE* input)
{
    if (!r.active)
        return 0;
    if (g.inScene3 && g.inTick && g.tick < (long)r.ticks.size())
        *input = r.ticks[g.tick].in[player];
    else if (g.inScene3)
        *input = (BYTE)ValueAt(r.pads, g.fightFrame, player);
    else
        *input = 0;
    return 1;
}

} // namespace

void StartRecorder(const RecordOptions& options, CGame* game, CScene** scenes)
{
    g.options = options;
    g.game = game;
    g.scenes = scenes;
    g_traceHooks.tickStart = OnTickStart;
    g_traceHooks.inputsRead = OnInputsRead;
    g_traceHooks.tick = OnTick;
    g_traceHooks.input = OnInput;
    g_traceHooks.hashes = options.record || options.replay;
    SetCrashContext(DescribeGame, RecorderCrashed);
    LogInfo("record", "fight records %s", options.record ? "on" : "off");
}

bool StartReplay(unsigned char* scene)
{
    if (!g.options.replay)
        return false;
    if (!LoadRecord(g.options.replay))
        return false;
    CGame* game = g.game;
    CScene2* loader = (CScene2*)g.scenes[2];
    // The match as the harness's recording sets one up (src/trace.cpp), without a replay
    // file: scene 2 then only loads the players and the stage. The recorded state, mode
    // included, is loaded at the first tick.
    game->m_isCpu[0] = (BYTE)(r.cpu[0] != 0);
    game->m_isCpu[1] = (BYTE)(r.cpu[1] != 0);
    game->m_gameMode = 5;
    game->m_replayMode = 0;
    game->m_roundsToWin = (char)r.roundsToWin;
    game->m_stage = (char)r.stage;
    game->m_editColor[0] = r.editColor[0];
    game->m_editColor[1] = r.editColor[1];
    loader->CreateCharacter(loader->m_player1Ref, loader->m_player2Ref, 0, (char)r.chars[0]);
    loader->CreateCharacter(loader->m_player2Ref, loader->m_player1Ref, 1, (char)r.chars[1]);
    (*loader->m_player1Ref)->m_paletteIndex = (char)r.palettes[0];
    (*loader->m_player2Ref)->m_paletteIndex = (char)r.palettes[1];
    *scene = 2;
    r.active = true;
    LogInfo("replay", "replaying %s: characters %d and %d, stage %d, %ld ticks",
            r.path.c_str(), r.chars[0], r.chars[1], r.stage, (long)r.ticks.size());
    return true;
}

void RecorderFrameStart(long frame, int scene)
{
    g.sessionFrame = frame;
    g.scene = scene;
    if (scene != 3)
        return;
    if (!g.inScene3)
        EnterFightScene();
    else
        g.fightFrame++;
}

bool RecorderFrameEnd(int scene)
{
    if (g.inScene3) {
        CScene3* fight = (CScene3*)g.scenes[3];
        if (g.started && fight->m_paused != g.paused) {
            g.paused = fight->m_paused;
            Event("{\"type\":\"event\",\"t\":%ld,\"f\":%ld,\"event\":\"%s\"}", g.tick,
                  g.fightFrame, g.paused ? "pause" : "resume");
        }
        if (scene != 3) {
            bool fought = g.started;
            EndFight(g.matchEnd           ? "match_end"
                     : g.keys & 1         ? "escape"
                     : g.replayMode == 1  ? "replay_end"
                                          : "left");
            g.inScene3 = false;
            if (r.active && fought && !r.done) {
                r.done = true;
                LogError("replay", "the fight ended after %ld ticks; the record has %ld",
                         g.tick, (long)r.ticks.size());
            }
        }
    }
    return r.active && r.done;
}

void SuspendRecorder(bool suspend)
{
    static TraceHooks saved;
    static bool suspended;
    if (suspend == suspended)
        return;
    suspended = suspend;
    if (suspend) {
        if (g.inScene3) {
            EndFight("netplay");
            g.inScene3 = false;
        }
        saved = g_traceHooks;
        memset(&g_traceHooks, 0, sizeof(g_traceHooks));
        LogInfo("record", "fight records off for the network match");
    } else {
        g_traceHooks = saved;
    }
}

void StopRecorder()
{
    EndFight("exit");
    if (!r.active)
        return;
    long total = (long)r.ticks.size();
    if (!r.loaded)
        LogError("replay", "%s wasn't replayed", r.path.c_str());
    else if (r.firstDiff < 0 && r.compared == total)
        LogInfo("replay", "%s: all %ld ticks as recorded", r.path.c_str(), total);
    else if (r.firstDiff < 0)
        LogError("replay", "%s: %ld of %ld ticks replayed, as recorded", r.path.c_str(),
                 r.compared, total);
    else
        LogError("replay", "%s: %ld of %ld ticks replayed, %ld differ, the first at tick %ld",
                 r.path.c_str(), r.compared, total, r.diffs, r.firstDiff);
}

int ReplayResult()
{
    if (!r.active || !r.loaded)
        return 4;
    return r.firstDiff < 0 && r.compared == (long)r.ticks.size() ? 0 : 3;
}

void FilterKeyboard(unsigned char* keys, size_t size)
{
    bool first = g.inScene3 && g.keyFrame != g.fightFrame;
    if (first)
        g.keyFrame = g.fightFrame;
    if (r.active) {
        memset(keys, 0, size);
        unsigned held = g.inScene3 ? ValueAt(r.keys, g.fightFrame, -1) : 0;
        for (int i = 0; i < kSysKeyCount; i++) {
            if ((held & (1u << i)) && kSysKeys[i] < size)
                keys[kSysKeys[i]] = 0x80;
        }
        return;
    }
    // Recording: what the fight's first read of each frame (CScene3::HandleKeys) saw.
    if (!first)
        return;
    unsigned held = 0;
    for (int i = 0; i < kSysKeyCount; i++) {
        if (kSysKeys[i] < size && (keys[kSysKeys[i]] & 0x80))
            held |= 1u << i;
    }
    if (held != g.keys) {
        g.keys = held;
        if (g.file >= 0)
            KeysEvent();
    }
}

void NoteInput(int player, unsigned char input)
{
    if (r.active || !g.inScene3 || g.inTick || player < 0 || player > 1)
        return;
    if (input != g.pad[player]) {
        g.pad[player] = input;
        Event("{\"type\":\"pad\",\"f\":%ld,\"p\":%d,\"v\":%u}", g.fightFrame, player, input);
    }
}

void DescribeGame(char* out, size_t size)
{
    size_t n = 0;
    auto add = [&](const char* format, ...) {
        if (n + 1 >= size)
            return;
        va_list args;
        va_start(args, format);
        int k = vsnprintf(out + n, size - n, format, args);
        va_end(args);
        if (k > 0)
            n = n + (size_t)k < size ? n + (size_t)k : size - 1;
    };
    out[0] = 0;
    add("  scene %d (%s), frame %ld of the session\n", g.scene, SceneName(g.scene),
        g.sessionFrame);
    if (g.inScene3 && g.started) {
        add("  fight %d: tick %ld, frame %ld of the fight%s\n", g.fights, g.tick, g.fightFrame,
            g.inTick ? ", during the tick" : "");
        for (int i = 0; i < 2; i++) {
            const Observed& o = g.obs[i];
            if (o.valid)
                add("  P%d %s (%s), at the last tick's end: action %d frame %d, x %.2f y %.2f, "
                    "hp %d, gauge %d, rounds won %d\n",
                    i + 1, o.name, o.cpu ? "cpu" : "human", o.action, o.frame, o.x, o.y, o.hp,
                    o.gauge, o.roundsWon);
        }
        if (g.path[0])
            add("  its record: %s\n  to replay it: efz --data DIR --replay-fight \"%s\"\n",
                g.path, g.path);
    }
    if (r.active)
        add("  replaying %s: tick %ld of %ld\n", r.path.c_str(), g.tick, (long)r.ticks.size());
}

void RecorderCrashed()
{
    intptr_t file = g.file;
    if (file < 0)
        return;
    // On a line of its own, after whatever the crash cut short.
    char text[160];
    int n = snprintf(text, sizeof(text), "\n{\"type\":\"end\",\"t\":%ld,\"f\":%ld,"
                                         "\"reason\":\"crash\"}\n", g.tick, g.fightFrame);
    RawWrite(file, text, (size_t)n);
}

} // namespace efz
