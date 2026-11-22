// The fight recorder: the records, the checks and the replay. See record.h and
// docs/logging.md.
//
// It reads the game's state in the harness's tick hooks (src/trace.cpp) and changes
// nothing in it, except when replaying: then it loads the recorded state at the first
// tick and supplies the controls.
#include <SDL3/SDL.h>
#include <cmath>
#include <memory>
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
#include "agents.h"
#include "mp4.h"

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
    // The fight was changed from outside the game (InterruptRecord): no record of it.
    bool interrupted = false;
    long fightFrame = 0;
    bool started = false;
    long tick = 0;
    bool inTick = false;
    CScene3* fight = nullptr; // during the hooks
    intptr_t file = -1;
    char name[300] = ""; // the fight's files' name: fight-NNN, or a replay's (RecordPath)
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
    bool cpu[2] = {false, false}; // each player's CPlayer::m_cpu at the last tick's start
    Observed obs[2];
    Anomaly anomalies[64];
    int anomalyCount = 0;
    int snapshots = 0;
    Still still[2];
    Line line;
    Line event;
    bool swallowEsc = false; // the Esc that left a record is still down
    char lastRecord[1100] = ""; // the last fight's record, and its ticks
    long lastTicks = 0;
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

bool RecordPath(const char* name, char* out, size_t size);

// Writes the state to `name` beside the fight's record (no file: only hashes it).
bool SaveState(CScene3* scene, const char* name, long tick, uint32_t* hashes)
{
    StateFile s;
    s.file = -1;
    s.tick = (uint32_t)tick;
    s.ok = true;
    if (name) {
        char path[1100];
        if (!RecordPath(name, path, sizeof(path)) || (s.file = RawOpen(path, false)) < 0)
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

// The player_fields of a tick line ("p"), in its order.
const int kPlayerFields = 18;

struct ReplayTick {
    long f;
    uint32_t rng;
    unsigned char in[2];
    bool hashed;
    uint32_t h[TRACE_BLOCKS];
    bool hasP;
    double p[2][kPlayerFields];
};

// A recorded change of the F-keys or of GetInput outside the ticks, from fight frame f.
struct Change {
    long f;
    int player;
    unsigned value;
};

// What the replaying game keeps its own of, in place of the recorded state's: the sounds
// it loaded for the fight, slots of its CSound, which the state holds by number
// (CGame::m_sounds and m_music, each player's m_voices; they follow what the game loaded
// before: the menus, the demo, earlier fights); and the replay mode, 2 while the game
// writes a replay of the record. Each tick is hashed with the record's put back.
struct Kept {
    WORD sounds[0x41];
    WORD music;
    short voices[2][0x32];
    char replayMode;

    void Read(CScene3* scene)
    {
        memcpy(sounds, scene->m_game->m_sounds, sizeof(sounds));
        music = scene->m_game->m_music;
        for (int i = 0; i < 2; i++)
            memcpy(voices[i], scene->m_players[i]->m_voices, sizeof(voices[i]));
        replayMode = scene->m_game->m_replayMode;
    }
    void Write(CScene3* scene) const
    {
        memcpy(scene->m_game->m_sounds, sounds, sizeof(sounds));
        scene->m_game->m_music = music;
        for (int i = 0; i < 2; i++)
            memcpy(scene->m_players[i]->m_voices, voices[i], sizeof(voices[i]));
        scene->m_game->m_replayMode = replayMode;
    }
    // How many sounds differ from `other`'s; the first, and other's there.
    int Differ(const Kept& other, int* first, int* otherFirst) const
    {
        int n = 0;
        auto note = [&](int x, int y) {
            if (x != y && n++ == 0) {
                *first = x;
                *otherFirst = y;
            }
        };
        note(music, other.music);
        for (int i = 0; i < 0x41; i++)
            note(sounds[i], other.sounds[i]);
        for (int p = 0; p < 2; p++) {
            for (int i = 0; i < 0x32; i++)
                note(voices[p][i], other.voices[p][i]);
        }
        return n;
    }
};

// What the replay machinery is doing.
enum Task {
    kNoTask,
    kCheck,  // --replay-fight: a record replayed and compared, then the game quits
    kWatch,  // the REPLAY menu's RECORDS page: a record played to be watched
    kWrite,  // a record replayed with the game recording a replay of it (record to .rep)
    kVerify, // that replay played back and compared with the record
    kImport, // a .rep played back with the fight recorded (.rep to record)
    kVideo,  // a record replayed, as watched, into a video (record to .mp4)
    kVideoRep, // a .rep played back into a video (.rep to .mp4)
};

struct Replay {
    bool active = false;
    Task task = kNoTask;
    std::string path, dir;
    int chars[2] = {0, 0}, palettes[2] = {0, 0}, cpu[2] = {0, 0}, editColor[2] = {0, 0};
    int stage = 0, roundsToWin = 2, fkeyHeld = 0, mode = -1, replayMode = 0, fight = 0;
    std::string session;
    uint32_t rng = 0;
    std::string stateFile, repCopy;
    long repOffset = 0;
    uint32_t stateHashes[TRACE_BLOCKS];
    std::vector<ReplayTick> ticks;
    std::vector<Change> keys, pads;
    // The CPU's side handed to its combo file and back ("cpu" lines: f the tick, the
    // player, value m_cpu), in tick order; the next to apply.
    std::vector<Change> handoffs;
    size_t handoffAt = 0;
    std::vector<unsigned char> state;
    const void* blocks[TRACE_BLOCKS];
    unsigned sizes[TRACE_BLOCKS];
    bool loaded = false, done = false;
    long firstDiff = -1, diffs = 0, compared = 0;
    bool keptDiffers = false; // the game keeps values of its own, `kept` the record's
    Kept kept;
    bool left = false;       // Esc, from the menu
    bool paused = false;     // F8, outside the game (RecordPaused)
    bool pauseKey = false;
    // The fight's settings of key.ini, as the recorded state has them (kWrite), for
    // playing its replay back (kVerify).
    char damageLevel = 2, fullEffects = 1;
    int drawEveryFrame = 1;
    std::string rep; // the .rep kWrite writes and kVerify plays; kImport's
};
Replay r;

// A conversion: a record to a .rep (kWrite, then kVerify), a .rep to a record
// (kImport), or either to a video (kVideo, kVideoRep).
struct Job {
    Conversion::Kind kind = Conversion::kToRep;
    std::string in;
    std::string outDir;  // where what it makes goes ("": the session folder's, a record)
    std::string out;     // what it made: a path
    std::string outName; // a replay from the menu: the replay slot's game file name
    int videoScale = 2;
    int status = -1;     // 0 done, 3 its replay plays otherwise, 4 not converted
    std::string said;    // what came of it
};

// The replay machinery's work away from the menus: a record played from the REPLAY
// menu, the menu's conversions, or the command line's. `game` is CGame as it was before
// (restored between the jobs and after them), `save` the save folder.
struct Tasks {
    bool on = false;
    bool inGame = false; // back to the REPLAY menu afterwards; else the game quits
    std::vector<unsigned char> game;
    std::string save, scratch;
    std::vector<Job> jobs;
    size_t at = 0;
    bool over = false;   // the command line's: all done
    bool stay = false;   // the replay tool's: the game waits for more when done
    std::string note;    // for the menu: how the last one went, and whether it was done
    bool noteOk = false;
    // A record from a .rep, in a folder of the job's, named for the replay.
    std::string recordDir, recordName;
    // A video being made: the last frame shown (repeated for a frame not drawn), and
    // whether this frame of the game's showed one.
    std::unique_ptr<Mp4Writer> video;
    std::vector<uint32_t> picture;
    int pictureW = 0, pictureH = 0;
    bool shown = false;
} g_tasks;

// What the task does with the record, by kind.
bool Replays()   // the record's state, inputs and F-keys replayed
{
    return r.task == kCheck || r.task == kWatch || r.task == kWrite || r.task == kVideo;
}
bool Quiet()     // no record of the fight, no checks
{
    return r.task == kWatch || r.task == kWrite || r.task == kVerify || r.task == kVideo ||
           r.task == kVideoRep;
}
bool Hurried()   // no frame waited for
{
    return r.task == kWrite || r.task == kVerify || r.task == kImport || r.task == kVideo ||
           r.task == kVideoRep;
}
bool Undrawn()   // nor drawn
{
    return r.task == kWrite || r.task == kVerify || r.task == kImport;
}
bool Filming()
{
    return g_tasks.video && r.active && (r.task == kVideo || r.task == kVideoRep);
}

// A file of the fight's record: in the session folder, or a .rep's record's folder.
bool RecordPath(const char* name, char* out, size_t size)
{
    if (g_tasks.on && r.task == kImport && !g_tasks.recordDir.empty()) {
        int n = snprintf(out, size, "%s/%s", g_tasks.recordDir.c_str(), name);
        return n > 0 && (size_t)n < size;
    }
    return SessionPath(name, out, size);
}

// Why a record can't be replayed: in the log, and in short for the REPLAY menu's page.
std::string g_refusal;

void Refuse(const char* reason, const char* format, ...) EFZ_PRINTF(2, 3);
void Refuse(const char* reason, const char* format, ...)
{
    va_list args;
    va_start(args, format);
    LogV(kLogError, "replay", format, args);
    va_end(args);
    if (g_refusal.empty())
        g_refusal = reason;
}

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
    bool Bool(const char* key) const
    {
        const Json* j = Get(key);
        return j && j->kind == kBool && j->number != 0;
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
        Refuse("its state file can't be read", "cannot read the state %s: %s", path.c_str(),
               SDL_GetError());
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
            Refuse("its state file is incomplete", "the state %s has no block %s", path.c_str(),
                   TraceBlockName(i));
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
        Refuse("the record can't be read", "cannot read %s: %s", path, SDL_GetError());
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
                    Refuse("it isn't a fight record this game reads",
                           "%s isn't an efz-fight record of version 1", path);
                    SDL_free(data);
                    return false;
                }
                const Json* players = j.Get("players");
                for (int i = 0; i < 2; i++) {
                    if (!players || players->items.size() != 2) {
                        Refuse("the record has no players", "%s has no players", path);
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
                r.mode = (int)j.Number("mode", -1);
                r.session = j.String("session");
                r.fight = (int)j.Number("fight");
                r.replayMode = (int)j.Number("replay_mode");
                r.rng = (uint32_t)j.Number("rng");
                r.fkeyHeld = (int)j.Number("fkey_held");
                r.stateFile = j.String("state");
                r.repCopy = j.String("replay_copy");
                r.repOffset = (long)j.Number("replay_offset");
                if (!ParseHashes(j.String("state_hashes"), r.stateHashes)) {
                    Refuse("the record has no state hashes", "%s has no state_hashes", path);
                    SDL_free(data);
                    return false;
                }
            } else if (type == "tick") {
                ReplayTick t;
                if ((long)j.Number("t", -1) != (long)r.ticks.size()) {
                    Refuse("the record misses ticks", "%s:%ld: tick %ld where %ld was due", path,
                           lineNumber, (long)j.Number("t", -1), (long)r.ticks.size());
                    SDL_free(data);
                    return false;
                }
                t.f = (long)j.Number("f");
                t.rng = (uint32_t)j.Number("rng");
                const Json* in = j.Get("in");
                t.in[0] = in ? (unsigned char)in->At(0) : 0;
                t.in[1] = in ? (unsigned char)in->At(1) : 0;
                t.hashed = ParseHashes(j.String("h"), t.h);
                const Json* p = j.Get("p");
                t.hasP = p && p->items.size() == 2;
                for (int i = 0; i < 2; i++) {
                    for (int k = 0; k < kPlayerFields; k++)
                        t.p[i][k] = t.hasP ? p->items[i].At((size_t)k) : 0;
                }
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
            } else if (type == "cpu") {
                Change c = {(long)j.Number("t"), (int)j.Number("p"), (unsigned)j.Number("v")};
                if (c.player == 0 || c.player == 1)
                    r.handoffs.push_back(c);
            }
        }
        p = e + 1;
    }
    SDL_free(data);
    if (!header || r.ticks.empty()) {
        Refuse(header ? "the record has no ticks" : "the record has no header", "%s has %s",
               path, header ? "no ticks" : "no header");
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
            Refuse("the characters aren't the record's", "P%d is character %d, the record's %d",
                   i + 1, scene->m_players[i]->m_charId, r.chars[i]);
            return false;
        }
    }
    Kept live;
    live.Read(scene);
    int bad = TraceLoadState(scene, r.blocks, r.sizes);
    if (bad >= 0) {
        Refuse("it was recorded by a game of another layout",
               "the state's block %s has %u bytes where this build has others",
               TraceBlockName(bad), r.sizes[bad]);
        return false;
    }
    srand(r.rng);
    g_fkeyHeld = r.fkeyHeld;
    // The replay file the fight read or wrote: the record's copy, or a scratch file; or,
    // writing a replay of the record, the one match setup opened, its header written.
    if (r.task == kWrite) {
    } else if (game->m_replayMode == 1) {
        std::string copy = r.dir + "/" + r.repCopy;
        FILE* f = r.repCopy.empty() ? nullptr : OpenUtf8(copy.c_str(), "rb");
        if (!f) {
            Refuse("the replay file it played is missing",
                   "the fight played a replay, and its copy %s is missing", copy.c_str());
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
            Refuse("its state doesn't load as recorded",
                   "the loaded state's block %s doesn't hash as recorded", TraceBlockName(i));
            return false;
        }
    }
    // The game must play and free the sounds it loaded, not the record's (and played
    // from the menu, it goes on after the fight); writing a replay of the record, it
    // records one. The record's values are put back only to hash the state as the
    // record's game had it (OnTick).
    r.kept.Read(scene);
    live.replayMode = r.task == kWrite ? 2 : r.kept.replayMode;
    int first = 0, here = 0;
    int moved = r.kept.Differ(live, &first, &here);
    if (moved)
        LogInfo("replay", "%d of the record's sounds were in other slots than this game's "
                          "(the first in %d, here %d): this game's are kept",
                moved, first, here);
    if (moved || live.replayMode != r.kept.replayMode) {
        live.Write(scene);
        r.keptDiffers = true;
    }
    r.damageLevel = game->m_damageLevel;
    r.fullEffects = game->m_fullEffects;
    r.drawEveryFrame = game->m_drawEveryFrame;
    LogInfo("replay", "loaded the recorded state at the first tick");
    return true;
}

// The record's player_fields of a player, as WriteTick writes them.
void PlayerFields(CPlayer* p, double* out)
{
    int objects = 0;
    for (int j = 0; j < 0x40; j++)
        objects += p->m_objectActive[j] != 0;
    double v[kPlayerFields] = {(double)p->pattern, (double)p->frame, p->x, p->y, p->vx, p->vy,
                               (double)p->facing, (double)p->m_hp, (double)p->m_gauge,
                               (double)p->m_guardGauge, (double)p->m_rfGauge,
                               (double)p->m_comboHits, (double)p->m_comboDamage,
                               (double)p->m_hitstop, (double)p->m_freezeTime,
                               (double)p->m_command, (double)p->m_roundsWon, (double)objects};
    memcpy(out, v, sizeof(v));
}

// Failures from the menu are the player's to see, not the game's errors.
LogLevel Severity()
{
    return g_tasks.inGame ? kLogWarn : kLogError;
}

void Compare(const uint32_t* hashes)
{
    long t = g.tick;
    // (Esc, played from the menu, is the player's: the fight is left from then on.)
    if (!r.loaded || r.left || t >= (long)r.ticks.size())
        return;
    // A replay of the record played back (kVerify) is the same fight from a state of its
    // own, as in any game a replay is played in: CGame has a replay's mode and file; the
    // fight scene and the effects' ring keep what earlier fights left in them that a fight
    // doesn't reset (CScene3::m_endFade, the ring's idle slots); the players' blocks have
    // the sounds this game loaded, the HP a replay's F-key words set (m_refillHp) and no
    // character records (CharRecord, read for VS HUMAN). What plays must be the record's:
    // the players' fields, their objects and characters' blocks, rand() and the inputs.
    // The frame count needn't be (no pauses in a replay).
    bool verify = r.task == kVerify;
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
            if (verify && (i == TRACE_P1 || i == TRACE_P2 || i == TRACE_GAME ||
                           i == TRACE_SCENE || i == TRACE_FX))
                continue;
            if (hashes[i] != rec.h[i])
                note(TraceBlockName(i));
        }
    }
    if (g.rng != rec.rng)
        note("rand");
    if (!verify && g.fightFrame != rec.f)
        note("frame");
    if (g.in[0] != rec.in[0] || g.in[1] != rec.in[1])
        note("input");
    if (verify && rec.hasP && g.fight) {
        for (int i = 0; i < 2; i++) {
            double p[kPlayerFields];
            PlayerFields(g.fight->m_players[i], p);
            if (memcmp(p, rec.p[i], sizeof(p)) != 0)
                note(i ? "P2" : "P1");
        }
    }
    r.compared++;
    if (n) {
        r.diffs++;
        if (r.firstDiff < 0) {
            r.firstDiff = t;
            char state[48];
            snprintf(state, sizeof(state), "desync-t%06ld.state", t);
            bool saved = SaveState(g.fight, state, t, nullptr);
            Log(Severity(), "replay", "tick %ld differs from the record: %s%s%s", t, what,
                saved ? "; this state is in " : "", saved ? state : "");
        }
        // A replay made of it would be wrong: no further.
        if (r.task == kWrite || r.task == kVerify)
            r.done = true;
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
// fight's is the record's copy: the replay's game has no replay files; a .rep played to
// be recorded (kImport) is that file.
void CopyReplay(CGame* game, Line& l)
{
    char name[40];
    snprintf(name, sizeof(name), "replay\\data%d-%d.rep", game->m_replayPage + 1,
             game->m_replaySlot + 1);
    FILE* in = r.task == kImport ? OpenUtf8(r.rep.c_str(), "rb")
               : r.active        ? OpenUtf8((r.dir + "/" + r.repCopy).c_str(), "rb")
                                 : OpenGameFile(name, "rb");
    char copy[320], path[1100];
    snprintf(copy, sizeof(copy), "%s.rep", g.name);
    intptr_t out = in && RecordPath(copy, path, sizeof(path)) ? RawOpen(path, false) : -1;
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
    g.prevIntro = (char)game->m_intro;
    g.prevOver = game->m_roundOver != 0;
    g.prevWon[0] = p[0]->m_roundsWon;
    g.prevWon[1] = p[1]->m_roundsWon;
    g.cpu[0] = p[0]->m_cpu != 0;
    g.cpu[1] = p[1]->m_cpu != 0;
    g.matchEnd = false;
    g.winner = -1;
    g.anomalyCount = 0;
    g.snapshots = 0;
    for (int i = 0; i < 2; i++)
        g.still[i] = Still{-1, -1, -1, 0};
    // A record played to be watched, or to write and check a replay of it, isn't a fight
    // of this session's: no record of it, nor checks (its own were made as it was
    // recorded).
    if (Quiet()) {
        LogInfo("replay", "%s %s: %s (P1) vs %s (P2), %ld ticks",
                r.task == kWatch   ? "playing"
                : r.task == kWrite ? "writing a replay of"
                                   : "checking the replay of",
                r.path.c_str(), names[0], names[1], (long)r.ticks.size());
        return;
    }
    g.fights++;
    if (r.task == kImport && !g_tasks.recordName.empty())
        snprintf(g.name, sizeof(g.name), "%s", g_tasks.recordName.c_str());
    else
        snprintf(g.name, sizeof(g.name), "fight-%03d", g.fights);
    CountSession("fights");
    LogInfo("fight", "fight %d: %s (P1, %s) vs %s (P2, %s), stage %d, %s%s", g.fights, names[0],
            p[0]->m_cpu ? "cpu" : "human", names[1], p[1]->m_cpu ? "cpu" : "human",
            game->m_stage, ModeName(game->m_gameMode),
            game->m_replayMode == 1   ? ", playing a replay"
            : game->m_replayMode == 2 ? ", recording a replay"
                                      : "");
    if (!g.options.record)
        return;

    char file[320];
    snprintf(file, sizeof(file), "%s.jsonl", g.name);
    if (!RecordPath(file, g.path, sizeof(g.path))) {
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
        l.Printf(",\"edit_color\":%d", game->m_editColor[i] != 0);
        // The CPU with combos (agents.h): the file that plays its combos, and the share
        // of the most damaging its level aims at. Its "cpu" lines say when it had the side.
        if (const char* combos = p[i]->m_cpu ? CpuComboFile(i) : nullptr) {
            l.Add(",\"cpu_combos\":");
            l.String(combos);
            l.Add(",\"cpu_combo_share\":");
            l.Double(CpuComboShare(i));
        }
        // VS HUMAN: the agent that plays the side (agents.h), null for a person.
        if (game->m_gameMode == 4) {
            const char* agent = AgentName(i);
            l.Add(",\"agent\":");
            if (agent) {
                l.String(agent);
                l.Add(",\"agent_file\":");
                l.String(AgentFileName(i));
            } else {
                l.Add("null");
            }
        }
        l.Add("}");
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
    if (Quiet()) {
        LogInfo("replay", "%s: left after %ld of its %ld ticks (%s)", r.path.c_str(), g.tick,
                (long)r.ticks.size(), r.left ? "Esc" : reason);
        return;
    }
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
    snprintf(g.lastRecord, sizeof(g.lastRecord), "%s", g.path);
    g.lastTicks = g.tick;
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
    char state[340] = "";
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
    g.interrupted = false;
    g.tick = 0;
}

void OnTickStart(CScene3* scene)
{
    if (!g.inScene3)
        EnterFightScene();
    g.fight = scene;
    if (!g.started && !g.interrupted) {
        if (r.active && Replays() && !r.loaded && !r.done) {
            r.loaded = ReplayLoad(scene);
            if (!r.loaded) {
                r.done = true; // (a task: on to what follows it, RecorderFrameEnd)
                if (r.task == kCheck)
                    RequestQuit();
            }
        } else if (r.active && r.task == kVerify && !r.loaded) {
            // The replay starts as the record did: rand() and the F-key global.
            srand(r.rng);
            g_fkeyHeld = r.fkeyHeld;
            r.loaded = true;
        }
        BeginFight(scene);
    }
    // The CPU's side handed to its combo file, or back (agents.h): a replay does it at the
    // record's ticks; a record notes it, a line before the tick's.
    if (r.active && r.loaded) {
        while (r.handoffAt < r.handoffs.size() && r.handoffs[r.handoffAt].f <= g.tick) {
            const Change& c = r.handoffs[r.handoffAt++];
            if (c.f == g.tick)
                scene->m_players[c.player]->m_cpu = c.value ? 1 : 0;
        }
    }
    for (int i = 0; i < 2 && g.started; i++) {
        bool cpu = scene->m_players[i]->m_cpu != 0;
        if (cpu != g.cpu[i]) {
            Event("{\"type\":\"cpu\",\"t\":%ld,\"f\":%ld,\"p\":%d,\"v\":%d}", g.tick,
                  g.fightFrame, i, cpu ? 1 : 0);
            g.cpu[i] = cpu;
        }
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
    if (r.keptDiffers && traceHashes) {
        // The state's hashes as the record's game had it, its values in.
        Kept live;
        live.Read(scene);
        r.kept.Write(scene);
        SaveState(scene, nullptr, g.tick, hashes);
        live.Write(scene);
    }
    if (!Quiet())
        Check(scene);
    Events(scene);
    WriteTick(scene, traceHashes ? hashes : nullptr);
    if (r.active && r.task != kImport)
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

namespace {

// The loaded record's match, set up for match setup (scene 2): as the harness's recording
// sets one up (src/trace.cpp), without a replay file, so that scene 2 only loads the
// players and the stage; or, to write a replay of it (kWrite), as the REPLAY menu's RECORD
// item does, so that scene 2 also opens the replay file (slot 1-1, in the scratch save
// folder) and writes its header. The recorded state, mode included, is loaded at the
// first tick.
void SetUpMatch(Task task)
{
    CGame* game = g.game;
    CScene2* loader = (CScene2*)g.scenes[2];
    game->m_isCpu[0] = (BYTE)(r.cpu[0] != 0);
    game->m_isCpu[1] = (BYTE)(r.cpu[1] != 0);
    game->m_gameMode = 5;
    game->m_replayMode = task == kWrite ? 2 : 0;
    game->m_replayPage = 0;
    game->m_replaySlot = 0;
    game->m_roundsToWin = (char)r.roundsToWin;
    game->m_stage = (char)r.stage;
    game->m_editColor[0] = r.editColor[0];
    game->m_editColor[1] = r.editColor[1];
    loader->CreateCharacter(loader->m_player1Ref, loader->m_player2Ref, 0, (char)r.chars[0]);
    loader->CreateCharacter(loader->m_player2Ref, loader->m_player1Ref, 1, (char)r.chars[1]);
    (*loader->m_player1Ref)->m_paletteIndex = (char)r.palettes[0];
    (*loader->m_player2Ref)->m_paletteIndex = (char)r.palettes[1];
    r.task = task;
    r.active = true;
    LogInfo("replay", "replaying %s: characters %d and %d, stage %d, %ld ticks",
            r.path.c_str(), r.chars[0], r.chars[1], r.stage, (long)r.ticks.size());
}

// A .rep's match, set up as the REPLAY menu's PLAY item sets one up (src/scene0.cpp,
// scene8.cpp): scene 2 reads the replay's header from `path`, in place of the slot's
// file, and creates the players; the replay is played to 2 rounds won.
void SetUpReplay(Task task, const std::string& path)
{
    CGame* game = g.game;
    game->m_isCpu[0] = 0;
    game->m_isCpu[1] = 0;
    game->m_gameMode = 5;
    game->m_roundsToWin = 2;
    game->m_replayMode = 1;
    game->m_replayPage = 0;
    game->m_replaySlot = 0;
    r.rep = path;
    SetReplayFile(r.rep.c_str());
    r.task = task;
    r.active = true;
    LogInfo("replay", "%s %s", task == kVerify ? "playing back" : "playing", path.c_str());
}

// What a record's state, loaded at its first tick, sets in CGame (the whole of it is in
// the state) that outlasts the fight: the controls as the menu last read them, the
// modes, the settings of key.ini and the matches. They are put back as they were before
// the tasks, between them and after them.
void RestoreGame(CGame* game, const CGame* was)
{
#define EFZ_KEEP(m) memcpy(&game->m, &was->m, sizeof(game->m));
    EFZ_KEEP(m_inputX) EFZ_KEEP(m_inputY) EFZ_KEEP(m_pressA) EFZ_KEEP(m_pressB)
    EFZ_KEEP(m_pressC) EFZ_KEEP(m_pressD) EFZ_KEEP(m_holdA) EFZ_KEEP(m_holdB)
    EFZ_KEEP(m_holdC) EFZ_KEEP(m_holdD)
    EFZ_KEEP(m_gameMode) EFZ_KEEP(m_isCpu) EFZ_KEEP(m_humanSide) EFZ_KEEP(m_replayMode)
    EFZ_KEEP(m_replaySlot) EFZ_KEEP(m_replayPage) EFZ_KEEP(m_replayVersion)
    EFZ_KEEP(m_cpuLevel) EFZ_KEEP(m_fullEffects) EFZ_KEEP(m_drawEveryFrame)
    EFZ_KEEP(m_damageLevel) EFZ_KEEP(m_roundsSetting) EFZ_KEEP(m_hasConfig)
    EFZ_KEEP(m_extraChars)
    EFZ_KEEP(m_stage) EFZ_KEEP(m_round) EFZ_KEEP(m_roundsToWin) EFZ_KEEP(m_winner)
    EFZ_KEEP(m_editColor) EFZ_KEEP(m_dummyStance) EFZ_KEEP(m_dummyGuard)
    EFZ_KEEP(m_arcadeMatch) EFZ_KEEP(m_beatenChars) EFZ_KEEP(m_playedStages)
    EFZ_KEEP(m_continued) EFZ_KEEP(m_continuedAt)
#undef EFZ_KEEP
}

// The game away from its menus for the tasks: CGame as it was kept, its files to a
// scratch folder (a recorded F6 restarting a recorded replay would write the player's
// replay file; a replay is written there first), each tick hashed (--no-record).
bool BeginTasks(bool inGame)
{
    if (g_tasks.on || r.active)
        return false;
    char scratch[1100];
    if (!SessionPath("scratch", scratch, sizeof(scratch))) {
        g_tasks.note = "this game has no logs folder (--log-dir none)";
        return false;
    }
    g_tasks = Tasks();
    g_tasks.on = true;
    g_tasks.inGame = inGame;
    g_tasks.game.assign((const unsigned char*)g.game,
                        (const unsigned char*)g.game + sizeof(CGame));
    g_tasks.save = SaveDir();
    g_tasks.scratch = scratch;
    SDL_CreateDirectory(scratch);
    SetDataDir(DataDir(), scratch);
    g_traceHooks.hashes = 1;
    return true;
}

// The tasks are over: the game as it was; back to the REPLAY menu (scene 8), or the
// command line's run is over.
void EndTasks(unsigned char* scene)
{
    SetReplayFile(nullptr);
    RestoreGame(g.game, (const CGame*)g_tasks.game.data());
    // The REPLAY menu leaves on Esc too: not on the one that left a record.
    g.swallowEsc = r.left;
    SetDataDir(DataDir(), g_tasks.save.c_str());
    g_traceHooks.hashes = g.options.record || g.options.replay;
    MuteSounds(false);
    PauseSoundDevice(false);
    g_tasks.video.reset();
    r = Replay();
    g_tasks.on = false;
    if (g_tasks.inGame)
        *scene = 8;
    else if (g_tasks.stay)
        *scene = 0; // (the replay tool doesn't run the scenes between its jobs)
    else
        g_tasks.over = true;
}

// How a job went (what was done, or why it wasn't): in the log, on the command line's
// output, and for the menu.
void Said(Job& job, int status, const std::string& text)
{
    job.status = status;
    job.said = (status == 0 ? "" : "not converted: ") + text;
    Log(status == 0 ? kLogInfo : Severity(), "convert", "%s: %s", job.in.c_str(),
        job.said.c_str());
    if (g_tasks.inGame) {
        g_tasks.note = text;
        g_tasks.noteOk = status == 0;
    } else {
        printf("%s: %s\n", job.in.c_str(), job.said.c_str());
        fflush(stdout);
    }
}

bool LoadBytes(const std::string& path, std::vector<unsigned char>* out)
{
    FILE* f = OpenUtf8(path.c_str(), "rb");
    if (!f)
        return false;
    out->clear();
    unsigned char buffer[1 << 16];
    size_t k;
    while ((k = fread(buffer, 1, sizeof(buffer), f)) > 0)
        out->insert(out->end(), buffer, buffer + k);
    fclose(f);
    return true;
}

// A finished replay to where the job puts it: a replay slot in the save folder (from
// the menu), or a path.
bool WriteOut(const Job& job, const std::string& from)
{
    std::vector<unsigned char> bytes;
    if (!LoadBytes(from, &bytes))
        return false;
    FILE* f;
    if (!job.outName.empty()) {
        SetDataDir(DataDir(), g_tasks.save.c_str());
        f = OpenGameFile(job.outName.c_str(), "wb");
        SetDataDir(DataDir(), g_tasks.scratch.c_str());
    } else {
        f = OpenUtf8(job.out.c_str(), "wb");
    }
    if (!f)
        return false;
    bool ok = fwrite(bytes.data(), 1, bytes.size(), f) == bytes.size();
    return fclose(f) == 0 && ok;
}

std::string Where(const Job& job)
{
    return job.outName.empty() ? job.out : job.outName;
}

// A .rep this game can play: the header's characters and stage in range; and whether it
// is EfzRevival's extended replay (its trailer ends in -1).
bool ReadsAsReplay(const std::string& path, bool* extended)
{
    std::vector<unsigned char> bytes;
    if (!LoadBytes(path, &bytes) || bytes.size() < 12)
        return false;
    auto word = [&](size_t i) {
        int16_t w;
        memcpy(&w, &bytes[i * 2], 2);
        return (int)w;
    };
    int stage = word(2) > 100 ? word(3) : word(2);
    int32_t marker = 0;
    memcpy(&marker, &bytes[bytes.size() - 4], 4);
    *extended = bytes.size() >= 16 && marker == -1;
    return word(0) >= 0 && word(0) < 25 && word(1) >= 0 && word(1) < 25 && stage >= 0 &&
           stage < 23;
}

// A path's file name without its folder and extension.
std::string BaseName(const std::string& path)
{
    size_t slash = path.find_last_of("/\\");
    std::string name = slash == std::string::npos ? path : path.substr(slash + 1);
    size_t dot = name.find_last_of('.');
    return dot == std::string::npos || dot == 0 ? name : name.substr(0, dot);
}

bool IsReplayFile(const std::string& path)
{
    size_t dot = path.find_last_of('.');
    std::string ext = dot == std::string::npos ? "" : path.substr(dot);
    for (char& c : ext)
        c = (char)tolower((unsigned char)c);
    return ext == ".rep";
}

bool Exists(const std::string& path)
{
    SDL_PathInfo info;
    return SDL_GetPathInfo(path.c_str(), &info);
}

// A file in the job's folder ("": as given).
std::string OutPath(const Job& job, const std::string& file)
{
    return job.outDir.empty() ? file : job.outDir + "/" + file;
}

void AddVideoFrame(const uint32_t* pixels, int w, int h)
{
    float sound[2 * Mp4Writer::kSamplesPerFrame];
    MixSounds(sound, Mp4Writer::kSamplesPerFrame, Mp4Writer::kRate);
    if (!g_tasks.video->AddFrame(pixels, w, h, sound) && !r.done) {
        LogError("convert", "the video stops: %s", g_tasks.video->Error().c_str());
        r.done = true; // (the fight is left; the job says why)
    }
}

// A video to be made: the file opened, the sound device's sound taken by the video.
bool StartVideo(Job& job)
{
    g_tasks.video.reset(new Mp4Writer);
    g_tasks.picture.clear();
    if (!g_tasks.video->Open(job.out, 640 * job.videoScale, 480 * job.videoScale)) {
        Said(job, 4, g_tasks.video->Error());
        g_tasks.video.reset();
        return false;
    }
    PauseSoundDevice(true);
    MuteSounds(false);
    return true;
}

// Sets the job going: true when the game plays it (the next scene in *scene); false when
// it is done already (said why).
bool StartJob(Job& job, unsigned char* scene)
{
    RestoreGame(g.game, (const CGame*)g_tasks.game.data());
    SetReplayFile(nullptr);
    r = Replay();
    g_refusal.clear();
    g.lastRecord[0] = 0;
    g.lastTicks = 0;
    g_tasks.recordDir.clear();
    g_tasks.recordName.clear();
    bool video = job.kind == Conversion::kToVideo;
    if (IsReplayFile(job.in)) {
        if (job.kind == Conversion::kToRep) {
            Said(job, 4, "it is a replay already");
            return false;
        }
        bool extended = false;
        if (!ReadsAsReplay(job.in, &extended)) {
            Said(job, 4, "it isn't a replay this game reads");
            return false;
        }
        // EfzRevival plays its own replays to its rules (netplay's setSpectating).
        if (extended) {
            g.game->m_fullEffects = 1;
            g.game->m_drawEveryFrame = 1;
            g.game->m_damageLevel = 2;
            g.game->m_roundsSetting = 2;
        }
        if (video) {
            job.out = OutPath(job, BaseName(job.in) + ".mp4");
            if (!StartVideo(job))
                return false;
            SetUpReplay(kVideoRep, job.in);
        } else {
            // Its record, in the job's folder, named for it: a name none of the record's
            // three files has yet (its copy of the replay mustn't be the replay played).
            if (!job.outDir.empty()) {
                std::string name = BaseName(job.in);
                auto taken = [&](const std::string& n) {
                    std::string at = job.outDir + "/" + n;
                    return Exists(at + ".jsonl") || Exists(at + ".state") || Exists(at + ".rep");
                };
                for (int n = 2; taken(name); n++)
                    name = BaseName(job.in) + " (" + std::to_string(n) + ")";
                g_tasks.recordDir = job.outDir;
                g_tasks.recordName = name;
            }
            SetUpReplay(kImport, job.in);
            MuteSounds(true);
        }
        *scene = 2;
        return true;
    }
    if (job.kind == Conversion::kToRecord) {
        Said(job, 4, "it is a record already");
        return false;
    }
    if (!LoadRecord(job.in.c_str())) {
        Said(job, 4, g_refusal);
        return false;
    }
    std::string name = BaseName(job.in);
    if (!r.session.empty()) {
        char fight[16];
        snprintf(fight, sizeof(fight), "-fight-%03d", r.fight);
        name = r.session + fight;
    }
    if (video) {
        job.out = OutPath(job, name + ".mp4");
        if (!StartVideo(job))
            return false;
        SetUpMatch(kVideo);
        *scene = 2;
        return true;
    }
    if (job.outName.empty())
        job.out = OutPath(job, name + ".rep");
    if (r.cpu[0] || r.cpu[1]) {
        Said(job, 4, "the CPU plays in it, and a replay can't hold the CPU's decisions");
        return false;
    }
    if (r.roundsToWin != 2) {
        Said(job, 4, "it was played to " + std::to_string(r.roundsToWin) +
                         " rounds won, and a replay is always played to 2");
        return false;
    }
    if (r.replayMode == 1) {
        // The fight played a replay: that is its replay, copied as it was recorded.
        if (r.repCopy.empty() || !WriteOut(job, r.dir + "/" + r.repCopy))
            Said(job, 4, "the replay it played is missing");
        else
            Said(job, 0, "the replay it played, copied to " + Where(job));
        return false;
    }
    SetUpMatch(kWrite);
    MuteSounds(true);
    *scene = 2;
    return true;
}

// From the current job on, the first the game plays; the end when none is left.
bool RunJobs(unsigned char* scene)
{
    for (; g_tasks.at < g_tasks.jobs.size(); g_tasks.at++) {
        if (StartJob(g_tasks.jobs[g_tasks.at], scene))
            return true;
    }
    EndTasks(scene);
    return false;
}

// The fight scene was left: what follows the task.
void FinishTask(unsigned char* scene)
{
    Task task = r.task;
    long total = (long)r.ticks.size();
    if (task == kWatch) {
        LogInfo("replay", "back to the REPLAY menu from %s%s", r.path.c_str(),
                r.firstDiff >= 0 ? "; it played otherwise than recorded" : "");
        if (!r.loaded)
            g_tasks.note = "The record couldn't be played: " + g_refusal + ".";
        EndTasks(scene);
        return;
    }
    Job& job = g_tasks.jobs[g_tasks.at];
    std::unique_ptr<Mp4Writer> video = std::move(g_tasks.video);
    PauseSoundDevice(false);
    if (r.left) {
        Said(job, 4, "cancelled");
        g_tasks.at = g_tasks.jobs.size();
    } else if (task == kVideo || task == kVideoRep) {
        long frames = video ? video->Frames() : 0;
        if (video && video->Close()) {
            char length[32];
            snprintf(length, sizeof(length), "%ld:%02ld", frames / Mp4Writer::kFps / 60,
                     frames / Mp4Writer::kFps % 60);
            std::string otherwise =
                task == kVideo && r.firstDiff >= 0
                    ? "; this game plays the record otherwise than recorded from tick " +
                          std::to_string(r.firstDiff)
                    : "";
            Said(job, 0, "made " + job.out + ", " + length + " (" + std::to_string(frames) +
                             " frames)" + otherwise);
        } else {
            Said(job, 4, video ? video->Error() : "the video wasn't made");
        }
    } else if (task == kWrite) {
        if (!r.loaded) {
            Said(job, 4, g_refusal);
        } else if (r.firstDiff >= 0 || r.compared < total) {
            long from = r.firstDiff >= 0 ? r.firstDiff : r.compared;
            Said(job, 4, "this game doesn't replay the record as it was recorded (from "
                         "tick " + std::to_string(from) + ")");
        } else {
            // Written: now played back as a replay is, and compared with the record. It
            // plays with the record's fight settings (which a replay doesn't hold).
            char damage = r.damageLevel, effects = r.fullEffects;
            int every = r.drawEveryFrame;
            RestoreGame(g.game, (const CGame*)g_tasks.game.data());
            g.game->m_damageLevel = damage;
            g.game->m_fullEffects = effects;
            g.game->m_drawEveryFrame = every;
            r.loaded = r.done = false;
            r.firstDiff = -1;
            r.diffs = r.compared = 0;
            r.keptDiffers = false;
            SetUpReplay(kVerify, g_tasks.scratch + "/replay/data1-1.rep");
            *scene = 2;
            return;
        }
    } else if (task == kVerify) {
        if (r.firstDiff < 0 && r.compared == total) {
            static const char* const damages[4] = {"", "50%", "100%", "200%"};
            std::string damage = r.damageLevel >= 1 && r.damageLevel <= 3
                                     ? damages[(int)r.damageLevel]
                                     : "?";
            std::string as = r.damageLevel != 2
                                 ? " (in a game set to " + damage + " damage, as it was)"
                                 : "";
            if (!WriteOut(job, r.rep))
                Said(job, 4, Where(job) + " can't be written");
            else
                Said(job, 0, "written to " + Where(job) + ": its " + std::to_string(total) +
                                 " ticks play back as recorded" + as);
        } else {
            long from = r.firstDiff >= 0 ? r.firstDiff : r.compared;
            Said(job, 3, "its replay plays otherwise than the record from tick " +
                             std::to_string(from));
        }
    } else if (task == kImport) {
        if (g.lastRecord[0] && g.lastTicks > 0)
            Said(job, 0, "recorded in " + std::string(g.lastRecord) + ", " +
                             std::to_string(g.lastTicks) + " ticks");
        else
            Said(job, 4, "the fight wasn't recorded (--no-record?)");
    }
    g_tasks.at++;
    RunJobs(scene);
}

} // namespace

bool ReadRecordSummary(const char* path, RecordSummary* out)
{
    FILE* f = OpenUtf8(path, "rb");
    if (!f)
        return false;
    // The header: the first line (a few hundred bytes).
    std::string head;
    char buffer[4096];
    size_t k;
    while (head.find('\n') == std::string::npos && head.size() < (1u << 16) &&
           (k = fread(buffer, 1, sizeof(buffer), f)) > 0)
        head.append(buffer, k);
    // The end: the last line, or the last tick's when the record stops short.
    fseek(f, 0, SEEK_END);
    long size = ftell(f);
    long from = size > (long)sizeof(buffer) ? size - (long)sizeof(buffer) : 0;
    fseek(f, from, SEEK_SET);
    std::string tail(buffer, fread(buffer, 1, sizeof(buffer), f));
    fclose(f);
    size_t nl = head.find('\n');
    Json h;
    if (nl == std::string::npos || !ParseJson(head.data(), head.data() + nl, h) ||
        h.String("type") != "fight" || h.String("format") != "efz-fight")
        return false;
    *out = RecordSummary();
    out->path = path;
    out->session = h.String("session");
    out->started = h.String("started");
    out->fight = (int)h.Number("fight");
    out->mode = (int)h.Number("mode", -1);
    out->replayMode = (int)h.Number("replay_mode");
    out->roundsToWin = (int)h.Number("rounds_to_win", 2);
    out->replayed = h.Get("replay_of") != nullptr;
    if (const Json* b = h.Get("build")) {
        out->revision = b->String("revision");
        out->os = b->String("os");
        out->dirty = b->Bool("dirty");
    }
    const Json* players = h.Get("players");
    for (int i = 0; players && i < 2 && i < (int)players->items.size(); i++) {
        const Json& p = players->items[i];
        out->chars[i] = (int)p.Number("char", -1);
        out->cpu[i] = p.Number("cpu") != 0;
        out->agent[i] = p.String("agent");
        out->cpuCombos[i] = p.String("cpu_combos");
        // Records before agents were noted say nothing of who played VS HUMAN's sides.
        out->unknown[i] = !out->cpu[i] && out->mode == 4 && !p.Get("agent");
    }
    // Lines of the tail, last first; the first may be cut.
    size_t end = tail.size();
    while (end > 0) {
        size_t start = tail.rfind('\n', end - 1);
        start = start == std::string::npos ? 0 : start + 1;
        Json j;
        if (end > start && (start > 0 || from == 0) &&
            ParseJson(tail.data() + start, tail.data() + end, j)) {
            std::string type = j.String("type");
            if (type == "end" && out->reason.empty()) {
                out->reason = j.String("reason");
                out->winner = (int)j.Number("winner", -1);
                if (const Json* won = j.Get("rounds_won")) {
                    out->roundsWon[0] = (int)won->At(0);
                    out->roundsWon[1] = (int)won->At(1);
                }
                out->ticks = (long)j.Number("t");
                out->frames = (long)j.Number("f");
                break;
            }
            if (type == "tick") {
                out->ticks = (long)j.Number("t") + 1;
                out->frames = (long)j.Number("f") + 1;
                break;
            }
        }
        if (start == 0)
            break;
        end = start - 1;
    }
    return true;
}

bool StartReplay(unsigned char* scene)
{
    if (!g.options.replay)
        return false;
    if (!LoadRecord(g.options.replay))
        return false;
    SetUpMatch(kCheck);
    *scene = 2;
    return true;
}

bool PlayRecord(const char* path, std::string* error)
{
    if (!BeginTasks(true)) {
        *error = g_tasks.note.empty() ? "a record is playing" : g_tasks.note;
        return false;
    }
    g_refusal.clear();
    if (!LoadRecord(path)) {
        *error = g_refusal.empty() ? "it can't be read" : g_refusal;
        unsigned char scene = 8;
        EndTasks(&scene);
        return false;
    }
    SetUpMatch(kWatch);
    return true;
}

bool SaveRecordAsReplay(const char* path, int page, int slot, std::string* error)
{
    if (!BeginTasks(true)) {
        *error = g_tasks.note.empty() ? "a record is playing" : g_tasks.note;
        return false;
    }
    Job job;
    job.in = path;
    char name[40];
    snprintf(name, sizeof(name), "replay\\data%d-%d.rep", page + 1, slot + 1);
    job.outName = name;
    g_tasks.jobs.push_back(job);
    unsigned char scene = 8;
    if (RunJobs(&scene))
        return true;
    // Done without the game (copied), or refused: said in the note.
    *error = g_tasks.jobs[0].status == 0 ? "" : g_tasks.note;
    return false;
}

bool StartConversions(const std::vector<Conversion>& list, unsigned char* scene, bool stay)
{
    std::vector<Job> jobs;
    for (const Conversion& c : list) {
        Job job;
        job.kind = c.kind;
        job.in = c.in;
        job.outDir = c.outDir;
        job.videoScale = c.videoScale == 1 ? 1 : 2;
        jobs.push_back(job);
    }
    if (!BeginTasks(false)) {
        std::string why = g_tasks.note;
        g_tasks.jobs = jobs;
        g_tasks.over = !stay;
        for (Job& job : g_tasks.jobs)
            Said(job, 4, why);
        return false;
    }
    g_tasks.stay = stay;
    g_tasks.jobs = jobs;
    return RunJobs(scene);
}

std::vector<ConversionState> Conversions()
{
    std::vector<ConversionState> out;
    for (const Job& job : g_tasks.jobs)
        out.push_back(ConversionState{job.in, job.out, job.said, job.status});
    return out;
}

ConversionProgress Progress()
{
    ConversionProgress p;
    p.running = g_tasks.on && !g_tasks.inGame;
    p.job = g_tasks.at;
    p.jobs = g_tasks.jobs.size();
    p.checking = r.task == kVerify;
    p.video = r.task == kVideo || r.task == kVideoRep;
    if (!r.ticks.empty()) {
        p.done = (float)(r.loaded ? g.tick : 0) / r.ticks.size();
    } else if (r.task == kImport || r.task == kVideoRep) {
        // A .rep: how much of it the game has read.
        SDL_PathInfo info;
        const CReplayFile& file = g.game->m_replay;
        if (SDL_GetPathInfo(r.rep.c_str(), &info) && info.size > 0 && g.inScene3)
            p.done = 1.0f - (float)file.m_remaining / (float)info.size;
    }
    p.done = p.done < 0 ? 0 : p.done > 1 ? 1 : p.done;
    return p;
}

void CancelConversions()
{
    if (g_tasks.on && r.active)
        r.left = r.done = true;
}

void FrameShown(const uint32_t* pixels, int width, int height)
{
    if (!Filming() || g.scene != 3)
        return;
    AddVideoFrame(pixels, width, height);
    g_tasks.picture.assign(pixels, pixels + (size_t)width * height);
    g_tasks.pictureW = width;
    g_tasks.pictureH = height;
    g_tasks.shown = true;
}

int ConversionResult()
{
    int code = 0;
    for (const Job& job : g_tasks.jobs) {
        if (job.status == 4 || job.status < 0)
            code = 4;
        else if (job.status == 3 && code == 0)
            code = 3;
    }
    return code;
}

const RecordView* ViewingRecord()
{
    static RecordView view;
    if (!g_tasks.on || !g_tasks.inGame || !r.active)
        return nullptr;
    view.path = r.path.c_str();
    view.tick = r.loaded ? g.tick : 0;
    view.ticks = (long)r.ticks.size();
    view.firstDiff = r.firstDiff;
    view.paused = r.paused;
    view.done = r.done;
    view.saving = r.task == kWrite || r.task == kVerify;
    view.checking = r.task == kVerify;
    return &view;
}

std::string TakeRecordNote(bool* done)
{
    std::string note;
    std::swap(note, g_tasks.note);
    if (done)
        *done = g_tasks.noteOk;
    g_tasks.noteOk = false;
    return note;
}

bool RecordPaused(int scene)
{
    if (!r.active || r.task != kWatch)
        return false;
    const unsigned char* keys = KeyboardState();
    bool f8 = (keys[0x42] & 0x80) != 0;
    CScene3* fight = (CScene3*)g.scenes[3];
    bool playing = scene == 3 && g.inScene3 && g.started && !r.done && fight->m_enter == 0 &&
                   fight->m_leave == 0;
    if (f8 && !r.pauseKey && playing)
        r.paused = !r.paused;
    r.pauseKey = f8;
    // Esc goes on, to leave (FilterKeyboard).
    if (!playing || (keys[0x01] & 0x80))
        r.paused = false;
    return r.paused;
}

bool RecordHurry()
{
    return g_tasks.on && r.active && Hurried();
}

bool RecordUndrawn()
{
    return g_tasks.on && r.active && Undrawn();
}

bool RecordTasksRunning()
{
    return g_tasks.on;
}

void RecorderFrameStart(long frame, int scene)
{
    g.sessionFrame = frame;
    g.scene = scene;
    g_tasks.shown = false;
    // A video: the fight's frames-per-second count (at the top of the screen, out of the
    // state) says the game's 64, not how fast the video is made.
    if (Filming() && scene == 3) {
        CScene3* fight = (CScene3*)g.scenes[3];
        fight->m_fps = Mp4Writer::kFps;
        fight->m_secondStart = (int)timeGetTime();
    }
    if (scene != 3)
        return;
    if (!g.inScene3)
        EnterFightScene();
    else
        g.fightFrame++;
}

bool RecorderFrameEnd(unsigned char* sceneRef)
{
    int scene = *sceneRef;
    bool left = g.inScene3 && scene != 3;
    // A video's frame the game didn't draw (30 FPS, a pause): the last one again, so that
    // the video keeps the game's time.
    if (Filming() && g.scene == 3 && !g_tasks.shown && !g_tasks.picture.empty())
        AddVideoFrame(g_tasks.picture.data(), g_tasks.pictureW, g_tasks.pictureH);
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
            if (r.active && !r.ticks.empty() && fought && !r.done && !r.left) {
                r.done = true;
                Log(Severity(), "replay", "the fight ended after %ld ticks; the record has %ld",
                    g.tick, (long)r.ticks.size());
            }
        }
    }
    if (r.task == kCheck)
        return r.active && r.done;
    if (!g_tasks.on)
        return g_tasks.over;
    // A task: once the record's last tick has played (or it couldn't be), the fight is
    // left as Esc leaves it. A record watched is left even from the fade at a match's end
    // (that fade goes on to the results, without the replay mode a replay has); one
    // written or checked as a replay lets the fade end by itself, as the replay's
    // recording did. Whatever the scene goes to then, what follows the task does.
    CScene3* fight = (CScene3*)g.scenes[3];
    if (scene == 3 && r.done && fight->m_enter == 0 &&
        (r.task == kWatch ? fight->m_leave != 1 : fight->m_leave == 0)) {
        fight->m_leave = 1;
        fight->m_paused = 0;
    }
    if (left)
        FinishTask(sceneRef);
    return g_tasks.over;
}

void InterruptRecord(const char* why)
{
    if (r.active || !g.inScene3 || g.interrupted)
        return;
    g.interrupted = true;
    if (g.started) {
        LogInfo("record", "the fight's record ends: %s", why);
        EndFight(why);
    }
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
    if (!r.active || r.task != kCheck) // (a task: EndFight said where it was left)
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
        // From the menu, Esc is the player's own: it leaves the record, or the conversion.
        bool esc = g_tasks.inGame && g.inScene3 && size > 1 && (keys[0x01] & 0x80);
        memset(keys, 0, size);
        unsigned held = g.inScene3 && Replays() ? ValueAt(r.keys, g.fightFrame, -1) : 0;
        for (int i = 0; i < kSysKeyCount; i++) {
            if ((held & (1u << i)) && kSysKeys[i] < size)
                keys[kSysKeys[i]] = 0x80;
        }
        if (esc) {
            keys[0x01] = 0x80;
            r.left = r.done = true;
        }
        return;
    }
    if (g.swallowEsc && size > 1) {
        if (keys[0x01] & 0x80)
            keys[0x01] = 0;
        else
            g.swallowEsc = false;
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
