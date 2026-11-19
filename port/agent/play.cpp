// Trained agents playing in the native game (agents.h, docs/agents.md).
//
// An agent plays a side through that side's controls: once a frame, before the scene
// runs, it is given the fight as its player sees it (agent/observe.h: the view it was
// trained on) and gives a control byte, which CInput::GetInput hands the game in place
// of the keys (out of netplay), or the network session sends as this computer's input.
// It draws its random choices from a generator of its own, never the game's rand(), and
// decides once a frame shown, never again when netplay's rollback runs frames again: the
// game, its replays and the other side see a player's inputs and nothing else, which is
// what keeps a network match against EfzRevival 1.02h as it is.
//
// On character select it picks its own character (the one the file says it was trained
// to play) by moving the cursor and pressing A as a person would, then leaves the stage
// to the person. In a fight it acts as play.py's HumanMatch runs it (policy.h's Player).
//
// An agent file with routes plans its combos as play.py --assist does (agent/routes.h):
// on copies of the fight, saved and written back as netplay's rollback does it (the
// regions Revival copies, and rand's state), worked on between frames (AgentsIdle). The
// copies' frames run with the drawing off, no sound (sound.cpp), no keys (input.cpp, the
// network match's function keys), no replay written, the fight recorder's tick hooks
// set aside and the controls the plan's: when the fight is written back, nothing of
// them is left, and nothing of them was sent anywhere.
#include <SDL3/SDL.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <chrono>
#include <deque>
#include <map>
#include <memory>
// Before efz.h, whose x87.h makes sin, cos and atan2 macros: agent/policy.h and
// agent/routes.h need these, and the <cmath> they bring does not compile after them.
#include <random>
#include <string>
#include <vector>

#include "efz.h"
#include "agents.h"
#include "log.h"
#include "netplay.h"
#include "platform.h"
#include "agent/observe.h"
#include "agent/policy.h"
#include "agent/routes.h"
#include "agent/mix.h"

extern int g_fkeyHeld; // src/scene3.cpp

namespace efz {

namespace {

bool g_planning = false;
BYTE g_planInput[2];

// The plan's controls, in place of CInput::GetInput's (the harness's input hook).
int PlanInput(BYTE player, BYTE* input)
{
    *input = player < 2 ? g_planInput[player] : 0;
    return 1;
}

// The native game's fight as the routes' planner plays it (agent/routes.h).
class GameWorld : public agent::World {
public:
    // A fight begins: copies of another are no good in it.
    void NewFight()
    {
        fight_++;
        shown_.valid = false;
    }
    // Netplay: a plan starts from the frame shown (CaptureShown), not from the game as
    // it is when the session reads the input (its last confirmed frame).
    void SetShown(bool on)
    {
        shownMode_ = on;
        shown_.valid = false;
    }
    void CaptureShown() { Save(&shown_); }

    void Enter() override
    {
        hooks_ = g_traceHooks;
        memset(&g_traceHooks, 0, sizeof(g_traceHooks));
        g_traceHooks.input = PlanInput;
        drawing_ = g_skipDrawing;
        g_skipDrawing = true;
        g_planning = true;
        GameObjects o = Objects();
        back_ = o.graphics ? o.graphics->m_back : nullptr;
        if (back_)
            backBytes_.assign((char*)back_->pixels,
                              (char*)back_->pixels + (size_t)back_->pitch * back_->height);
    }
    void Leave() override
    {
        if (back_ && Objects().graphics && Objects().graphics->m_back == back_)
            memcpy(back_->pixels, backBytes_.data(), backBytes_.size());
        g_traceHooks = hooks_;
        g_skipDrawing = drawing_;
        g_planning = false;
    }
    void Save(agent::Snapshot* s) override
    {
        Regions(&s->regions);
        size_t total = 0;
        for (agent::Snapshot::Region& r : s->regions) {
            r.offset = total;
            total += r.size;
        }
        s->bytes.resize(total);
        for (const agent::Snapshot::Region& r : s->regions)
            memcpy(s->bytes.data() + r.offset, r.at, r.size);
        s->rng = RandState();
        s->tag = fight_;
        s->valid = true;
    }
    bool Load(const agent::Snapshot& s) override
    {
        if (!s.valid || s.tag != fight_)
            return false;
        Regions(&check_);
        if (check_.size() != s.regions.size())
            return false;
        for (size_t i = 0; i < check_.size(); i++) {
            if (check_[i].at != s.regions[i].at || check_[i].size != s.regions[i].size)
                return false;
        }
        for (const agent::Snapshot::Region& r : s.regions)
            memcpy(r.at, s.bytes.data() + r.offset, r.size);
        SetRandState(s.rng);
        return true;
    }
    void Now(agent::Snapshot* s) override
    {
        if (shownMode_)
            *s = shown_;
        else
            Save(s);
    }
    bool Step(const uint8_t input[2]) override
    {
        g_planInput[0] = input[0];
        g_planInput[1] = input[1];
        GameObjects o = Objects();
        CScene3* fight = (CScene3*)o.scenes[3];
        // Not recorded into the match's replay (CReplayFile::Write, mode 2), which the
        // game's play doesn't otherwise read.
        char mode = o.game->m_replayMode;
        o.game->m_replayMode = 0;
        if (!g_netplay.active) // WinMain's, every frame (a network match's: once a real one)
            o.game->m_oddFrame = !o.game->m_oddFrame;
        BYTE next = fight->Update();
        o.game->m_replayMode = mode;
        return next == 3 && fight->m_enter == 0;
    }
    void View(int side, float* out) override
    {
        GameObjects o = Objects();
        agent::WriteView(out, (CScene3*)o.scenes[3], o.game, side, 0, 0);
    }
    int Facing(int p) override { return P(p)->facing; }
    int Hp(int p) override { return P(p)->m_hp > 0 ? P(p)->m_hp : 0; }
    int ComboHits(int p) override { return P(p)->m_comboHits; }
    uint8_t Read(int p) override { return agent::ControlsRead(P(p)); }
    bool Over() override
    {
        GameObjects o = Objects();
        return o.game->m_roundOver != 0 || ((CScene3*)o.scenes[3])->m_leave == 2;
    }

private:
    static CPlayer* P(int p) { return ((CScene3*)Objects().scenes[3])->m_players[p]; }
    // What netplay's SaveState copies (session.cpp), less the back buffer (the copies
    // don't draw; Enter and Leave keep it all the same).
    void Regions(std::vector<agent::Snapshot::Region>* out)
    {
        out->clear();
        GameObjects o = Objects();
        CScene3* fight = (CScene3*)o.scenes[3];
        auto add = [&](void* at, size_t size) {
            agent::Snapshot::Region r;
            r.at = (char*)at;
            r.size = size;
            r.offset = 0;
            out->push_back(r);
        };
        add(&g_fkeyHeld, sizeof(g_fkeyHeld));
        if (!fight)
            return;
        add(fight, sizeof(CScene3));
        add(o.game, sizeof(CGame));
        for (int i = 0; i < 2; i++) {
            if (CPlayer* p = fight->m_players[i])
                add(p, PlayerSize(p));
        }
        if (PALETTEENTRY* palette = ScreenPalette(o.graphics))
            add(palette, 0x100 * sizeof(PALETTEENTRY));
        if (CAnimBg* bg = o.game->m_background) {
            if (bg->m_objects)
                add((BgObject*)bg->m_objects, bg->m_number == 16 ? 0x1c0 : 0xe0);
        }
    }

    uint32_t fight_ = 1;
    bool shownMode_ = false;
    agent::Snapshot shown_;
    std::vector<agent::Snapshot::Region> check_;
    TraceHooks hooks_;
    bool drawing_ = false;
    IDirectDrawSurface* back_ = nullptr;
    std::vector<char> backBytes_;
};

GameWorld g_world;
bool g_fast = false;
// How long a frame waits for a combo's first plan not done when the agent sees its hit
// (ms): a local match can stutter a little, a network match should not; for a later plan
// of the combo (replan), half a frame: the combo goes on with its route meanwhile.
const double kPatienceLocal = 40, kPatienceNet = 8, kPatienceAgain = 8;

const unsigned char kRight = 0x01, kLeft = 0x02, kDown = 0x04, kUp = 0x08, kA = 0x10, kC = 0x40;
const int kDikF5 = 0x3f, kDikF6 = 0x40, kDikLShift = 0x2a, kDikRShift = 0x36;
const int kVsHuman = 4;   // CGame::m_gameMode
const int kSelectWait = 3; // frames between character select presses, at the least

struct Entry {
    std::string path; // UTF-8
    std::string file; // its file name
    std::string name;
    int character = -1;
    std::string version;
    bool added = false; // from the command line, not the folders
    std::shared_ptr<agent::Policy> policy; // read when first played
};

std::vector<Entry> g_agents;
std::vector<std::string> g_labels;
bool g_on = false;

// A side an agent may play.
struct Side {
    std::string path; // empty: a person
    std::string name;
    std::shared_ptr<agent::Policy> policy;
    std::unique_ptr<agent::Player> player;
    std::unique_ptr<agent::Planner> planner; // its routes', if it has some
    std::unique_ptr<agent::MixPlanner> mix;  // its okizeme's, if it has a library of them
    unsigned char input = 0; // this frame's
    bool playing = false;    // this frame's input is the agent's
    int wait = 0;            // character select: frames before the next press
};

Side g_sides[2];
int g_lastScene = -1;
bool g_keyDown[2];
std::string g_note;
Uint64 g_noteUntil = 0;

// Netplay: this computer's side.
Side g_net;
int g_netLocal = -1;
int g_netScene = -1;
float g_shown[agent::kObsDim];
bool g_shownValid = false, g_shownActionable = false;
int g_shownFacing = 1;

uint64_t Seed()
{
    static uint64_t n = 0;
    return SDL_GetPerformanceCounter() ^ (++n * 0x9e3779b97f4a7c15ull);
}

std::string CharacterLabel(int c)
{
    const char* name = agent::CharacterName(c);
    if (!name)
        return "any character";
    std::string s = name;
    s[0] = (char)toupper((unsigned char)s[0]);
    return s;
}

void Note(const std::string& text)
{
    g_note = text;
    g_noteUntil = SDL_GetTicks() + 4000;
    LogInfo("agent", "%s", text.c_str());
}

std::string FileName(const std::string& path)
{
    size_t slash = path.find_last_of("/\\");
    return slash == std::string::npos ? path : path.substr(slash + 1);
}

// What the menus show: its name, version and character.
std::string Label(const Entry& e)
{
    return e.name + (e.version.empty() ? "" : " " + e.version) + " (" +
           CharacterLabel(e.character) + ")";
}

bool Peek(Entry* e)
{
    std::string error;
    if (!agent::Policy::Peek(e->path.c_str(), &e->name, &e->character, &e->version, &error)) {
        LogWarn("agent", "%s: %s", e->path.c_str(), error.c_str());
        return false;
    }
    return true;
}

void Scan()
{
    std::vector<Entry> found;
    for (const char* base : {SaveDir(), DataDir()}) {
        std::string dir = std::string(base) + "/agents";
        int count = 0;
        char** files = SDL_GlobDirectory(dir.c_str(), "*.efzagent", SDL_GLOB_CASEINSENSITIVE, &count);
        for (int i = 0; files && i < count; i++) {
            Entry e;
            e.path = dir + "/" + files[i];
            e.file = FileName(e.path);
            bool seen = false;
            for (const Entry& f : found)
                seen = seen || f.file == e.file;
            if (!seen && Peek(&e))
                found.push_back(std::move(e));
        }
        SDL_free(files);
    }
    std::sort(found.begin(), found.end(),
              [](const Entry& a, const Entry& b) { return a.name < b.name; });
    for (Entry& old : g_agents) {
        if (old.added) {
            found.push_back(std::move(old));
            continue;
        }
        for (Entry& e : found) {
            if (e.path == old.path)
                e.policy = std::move(old.policy);
        }
    }
    g_agents.swap(found);
    g_labels.clear();
    for (const Entry& e : g_agents)
        g_labels.push_back(Label(e));
}

int IndexOf(const std::string& path)
{
    for (size_t i = 0; i < g_agents.size(); i++) {
        if (g_agents[i].path == path)
            return (int)i;
    }
    return -1;
}

// What was drawn, by kind, for the log.
std::string Drawn(const agent::OkiStats& o, const std::vector<std::string>& kinds)
{
    std::string drawn;
    for (size_t k = 0; k < o.drawn.size(); k++) {
        if (!o.drawn[k])
            continue;
        std::string name = k < kinds.size() ? kinds[k]
                                            : k == kinds.size() ? "wait" : "its own play";
        drawn += (drawn.empty() ? "" : ", ") + name + " " + std::to_string(o.drawn[k]);
    }
    return drawn.empty() ? "none" : drawn;
}

// What an agent's planned pressure did, for the log.
void LogPressure(const char* who, const Side& s)
{
    const agent::OkiStats& o = s.player->Pressure();
    if (!o.asked)
        return;
    const agent::Press& lib = s.policy->press;
    double shares[agent::kAnswers];
    s.player->Seen().PressBelief(lib.prior, shares, lib.sight > 0);
    LogInfo("agent", "%s's pressure: %d guarded moves planned from: %d plans made, %d played "
                     "(%s); %d dropped (late %d, the game elsewhere %d, nothing to plan %d, the "
                     "fight over %d); planning %.1f ms a plan (at most %.1f), the game waited "
                     "%.2f ms a plan (at most %.1f); it expects of this opponent after a guard: "
                     "a crouching guard %.0f%%, a standing one %.0f%%, a reversal %.0f%%, a "
                     "jump %.0f%%, a button %.0f%%",
            who, o.asked, o.plans, o.played, Drawn(o, lib.kinds).c_str(),
            o.late + o.elsewhere + o.nothing + o.apart, o.late, o.elsewhere, o.nothing, o.apart,
            o.planMs / std::max(1, o.asked - o.late), o.planMsMost, o.waitedMs / o.asked,
            o.waitedMsMost, shares[0] * 100, shares[1] * 100, shares[2] * 100, shares[3] * 100,
            shares[4] * 100);
}

// What an agent's air throws of its opponent's recoveries did, for the log.
void LogCatches(const char* who, const Side& s)
{
    const agent::OkiStats& o = s.player->Air();
    if (!o.asked)
        return;
    LogInfo("agent", "%s's catches: %d air recoveries of its opponent planned from: an air "
                     "throw that catches inside the recovery found and played in %d; none in "
                     "%d; %d dropped (late %d, the game elsewhere %d, the fight over %d); "
                     "planning %.1f ms a plan (at most %.1f), %ld frames on copies a plan, the "
                     "game waited %.2f ms a plan (at most %.1f)",
            who, o.asked, o.played, o.nothing, o.late + o.elsewhere + o.apart, o.late,
            o.elsewhere, o.apart, o.planMs / std::max(1, o.asked - o.late), o.planMsMost,
            o.frames / std::max(1, o.asked - o.late), o.waitedMs / o.asked, o.waitedMsMost);
}

// What an agent's guard on rising did, for the log.
void LogRising(const char* who, const Side& s)
{
    if (!s.player || !s.policy || !s.policy->rise.on)
        return;
    const agent::RiseStats& r = s.player->Rising();
    if (!r.knockdowns)
        return;
    LogInfo("agent", "%s's risings: %d knockdowns, the attacker on it in %d, %d of those "
                     "guarded through (%d steps, %d standing); the next one guarded with "
                     "probability %.2f",
            who, r.knockdowns, r.met, r.guarded, r.steps, r.stood, s.player->RiseChance());
}

// What an agent's raw specials by their accounts did, for the log.
void LogRisks(const char* who, const Side& s)
{
    if (!s.player || !s.policy || !s.policy->risk.on)
        return;
    const agent::RiskStats& r = s.player->Risks();
    if (!r.seen)
        return;
    LogInfo("agent", "%s's raw specials: %d presses that would start a move with an account: "
                     "%d stopped, %d let out (%d of them seen to start)",
            who, r.seen, r.stopped, r.let, r.came);
}

// What an agent's planned okizeme did, for the log.
void LogOkizeme(const char* who, const Side& s)
{
    LogRising(who, s);
    LogRisks(who, s);
    if (!s.player || !s.player->Mixing())
        return;
    LogPressure(who, s);
    LogCatches(who, s);
    const agent::OkiStats& o = s.player->Oki();
    if (!o.asked)
        return;
    const agent::Mix& lib = s.policy->mix;
    std::string drawn = Drawn(o, lib.kinds);
    double shares[agent::kAnswers];
    s.player->Seen().Belief(lib.prior, shares, lib.sight > 0);
    LogInfo("agent", "%s's okizeme: %d knockdowns planned for: %d plans made, %d played (%s); "
                     "%d dropped (late %d, the game elsewhere %d, the opponent up too soon %d, "
                     "the fight over %d); planning %.1f ms a plan (at most %.1f), %ld frames on "
                     "copies a plan, the game waited %.2f ms a plan (at most %.1f); it expects "
                     "of this opponent's wake-ups: a crouching guard %.0f%%, a standing one "
                     "%.0f%%, a reversal %.0f%%, a jump %.0f%%, a button %.0f%%",
            who, o.asked, o.plans, o.played, drawn.c_str(),
            o.late + o.elsewhere + o.nothing + o.apart, o.late, o.elsewhere, o.nothing, o.apart,
            o.planMs / std::max(1, o.asked - o.late), o.planMsMost,
            o.frames / std::max(1, o.asked - o.late), o.waitedMs / o.asked, o.waitedMsMost,
            shares[0] * 100, shares[1] * 100, shares[2] * 100, shares[3] * 100, shares[4] * 100);
}

// What an agent's routes did, for the log.
void LogRoutes(const char* who, const Side& s)
{
    LogOkizeme(who, s);
    if (!s.player || !s.player->Planning())
        return;
    const agent::RouteStats& r = s.player->Stats();
    int asked = r.plans + r.dropped();
    if (!asked)
        return;
    LogInfo("agent", "%s's routes: %d plans asked (%d at a later move's hit of a combo): %d "
                     "made, a route chosen in %d; %d dropped (late %d, of them %d a combo's "
                     "first played by the chooser's route; the game elsewhere %d, the combo "
                     "over %d, not this opponent %d, the fight over %d); planning %.1f ms a "
                     "plan (at most %.1f), the game waited %.2f ms a plan (at most %.1f)",
            who, asked, r.again, r.plans, r.routes, r.dropped(), r.late, r.chooser, r.elsewhere,
            r.over, r.own, r.apart, r.planMs / std::max(1, asked - r.late - r.own), r.planMsMost,
            r.waitedMs / asked, r.waitedMsMost);
}

// Has the side played by the agent at `path` (empty: a person); false with *error.
// player: the side it plays (its routes planned for it); -1 only to read it. net: in a
// network match.
bool Choose(Side* s, const std::string& path, std::string* error, int player, bool net = false)
{
    *s = Side();
    if (path.empty())
        return true;
    int at = IndexOf(path);
    if (at < 0) {
        *error = "no agent " + path;
        return false;
    }
    Entry& e = g_agents[at];
    if (!e.policy) {
        auto p = std::make_shared<agent::Policy>();
        if (!p->Load(e.path.c_str(), error)) {
            *error = e.file + ": " + *error;
            return false;
        }
        e.policy = p;
        std::string combos = "its own combos";
        if (!p->routes.Empty()) {
            combos = "its combos from " + std::to_string(p->routes.list.size()) + " routes (" +
                     p->routes.source + "), planned " +
                     (p->routes.replan ? "again at each new move's hit" : "at the first hit") +
                     ", " + std::to_string(p->routes.perStart) + " tried" +
                     (p->chooser.Empty() ? "" : "; the chooser's when a plan is late");
        }
        if (!p->mix.Empty()) {
            combos += "; its okizeme planned from " + std::to_string(p->mix.entries.size()) +
                      " of people's (" + p->mix.source + "), " + std::to_string(p->mix.perPlan) +
                      " tried a knockdown";
        }
        if (!p->press.Empty()) {
            combos += "; its pressure after a guarded move planned from " +
                      std::to_string(p->press.entries.size()) + " of people's (" +
                      p->press.source + "), " + std::to_string(p->press.perPlan) + " tried";
        }
        if (p->air.on)
            combos += "; an air throw of an opponent's air recovery when one catches inside it";
        if (p->rise.on)
            combos += "; its rising guarded by sight when the attacker is on it";
        if (p->risk.on)
            combos += "; its raw specials let out or stopped by how each has paid in the match";
        LogInfo("agent", "%s: \"%s\"%s, %s, format %d (%s), deciding every %d frame(s), %d "
                         "frames late, %d inputs of history; %s",
                e.path.c_str(), p->name.c_str(),
                p->version.empty() ? "" : (" " + p->version).c_str(),
                CharacterLabel(p->character).c_str(), p->format, p->modules.c_str(), p->frameSkip,
                p->delay, p->history, combos.c_str());
        for (const auto& kv : p->about)
            LogInfo("agent", "%s: %s %s", e.file.c_str(), kv.first.c_str(), kv.second.c_str());
    }
    s->path = e.path;
    s->name = e.name + (e.version.empty() ? "" : " " + e.version);
    s->policy = e.policy;
    s->player.reset(new agent::Player(s->policy.get(), Seed()));
    if (player >= 0 && !s->policy->routes.Empty()) {
        s->planner.reset(new agent::Planner(s->policy.get(), &g_world, Seed()));
        double patience = g_fast ? -1 : net ? kPatienceNet : kPatienceLocal;
        s->player->SetPlanner(s->planner.get(), player, patience, kPatienceAgain);
        if (!s->player->Planning())
            s->planner.reset();
    }
    if (player >= 0 && (!s->policy->mix.Empty() || !s->policy->press.Empty() ||
                        s->policy->air.on)) {
        s->mix.reset(new agent::MixPlanner(s->policy.get(), &g_world, Seed()));
        s->player->SetMix(s->mix.get(), player,
                          g_fast ? -1 : net ? kPatienceNet : kPatienceLocal);
        if (!s->player->Mixing())
            s->mix.reset();
    }
    if (player >= 0 && s->policy->risk.on)
        s->player->SetRisk(&g_world, player);
    return true;
}

// Character select: the side is still choosing its character (or about to: the
// screen's intro); after that, the stage is the person's to choose.
bool Choosing(int side)
{
    CScene1* select = (CScene1*)Objects().scenes[1];
    int state = select ? select->m_state[side] : 5;
    return state == 0 || state == 1 || state == 2 || state == 3 || state == 5;
}

bool Selectable(CGame* game, int c)
{
    if (game->m_extraChars == 0 && (c == 19 || c == 20 || c == 21 || c == 23))
        return false;
    if (game->m_extraChars == -1 && c >= 12 && c <= 15)
        return false;
    return true;
}

// Character select: the agent's character chosen as a person chooses it, one press at
// a time, each given `wait` frames to show before the next.
unsigned char SelectInput(Side& s, int side, int wait)
{
    GameObjects o = Objects();
    CScene1* select = (CScene1*)o.scenes[1];
    if (!select)
        return 0;
    if (s.wait > 0) {
        s.wait--;
        return 0;
    }
    int state = select->m_state[side];
    if (state == 3) { // its colour, as it is
        s.wait = wait;
        return kA;
    }
    if (state != 0 || select->m_randomTime[side] > 0)
        return 0;
    int c = s.policy->character, target = -1;
    for (int i = 0; c >= 0 && Selectable(o.game, c) && i < 0x18; i++) {
        if (select->m_grid[i] == c)
            target = i;
    }
    s.wait = wait;
    if (target < 0)
        return kC; // any character: the game's own random choice
    int x = select->m_cursorX[side], y = select->m_cursorY[side];
    int tx = target % 3, ty = target / 3;
    if (y != ty)
        return (ty - y + 8) % 8 <= 4 ? kDown : kUp;
    if (x != tx)
        return (tx - x + 3) % 3 == 1 ? kRight : kLeft;
    return kA;
}

// The fight as player `side` sees it, whether its controls do anything (as training's:
// no intro, no KO waiting; and no pause) and where it faces; false before the fight
// scene has taken its players.
bool View(int side, float* view, bool* actionable, int* facing)
{
    GameObjects o = Objects();
    CScene3* fight = (CScene3*)o.scenes[3];
    if (!fight || fight->m_enter != 0 || !fight->m_players[0] || !fight->m_players[1])
        return false;
    CGame* game = o.game;
    agent::WriteView(view, fight, game, side, 0, 0);
    *actionable = game->m_intro == 0 && game->m_roundOver == 0 && fight->m_paused == 0;
    *facing = fight->m_players[side]->facing;
    return true;
}

// Forward and back as the screen's right and left.
unsigned char ToScreen(unsigned char bits, int facing)
{
    if (facing < 0)
        bits = (unsigned char)((bits & ~3) | (bits & 1) << 1 | (bits & 2) >> 1);
    return bits;
}

unsigned char FightInput(Side& s, int side)
{
    float view[agent::kObsDim];
    bool actionable = false;
    int facing = 1;
    bool seen = View(side, view, &actionable, &facing);
    return ToScreen(s.player->Step(view, seen && actionable), facing);
}

// F5/F6: the side's next player, `step` 1 (on through the agents) or -1 (Shift: back),
// the person between the last agent and the first.
void Cycle(int side, int step)
{
    Scan();
    Side& s = g_sides[side];
    int count = (int)g_agents.size();
    int at = s.path.empty() ? -1 : IndexOf(s.path);
    std::string error;
    for (int next = at + step;; next += step) {
        if (next < -1)
            next = count - 1;
        if (next < 0 || next >= count) {
            Choose(&s, "", &error, side);
            Note(std::string(side ? "P2" : "P1") + ": a person");
            return;
        }
        if (Choose(&s, g_agents[next].path, &error, side)) {
            Note(std::string(side ? "P2" : "P1") + ": " + g_labels[next]);
            return;
        }
        Note("can't play " + error);
    }
}

// --- Drawing, with SDL's 8x8 font over the 640x480 screen (as netplay's screens).

void Text(SDL_Renderer* r, float x, float y, const std::string& text, float scale, SDL_Color c)
{
    std::string s;
    for (char ch : text)
        s.push_back((unsigned char)ch < 0x80 ? ch : '?');
    SDL_SetRenderScale(r, scale, scale);
    SDL_SetRenderDrawColor(r, 0, 0, 0, 200);
    SDL_RenderDebugText(r, x / scale + 1, y / scale + 1, s.c_str());
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderDebugText(r, x / scale, y / scale, s.c_str());
    SDL_SetRenderScale(r, 1, 1);
}

float Width(const std::string& s, float scale)
{
    return (float)s.size() * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * scale;
}

const SDL_Color kWhite = {255, 255, 255, 255};
const SDL_Color kGrey = {170, 170, 170, 255};
const SDL_Color kTeal = {80, 210, 190, 255};
const SDL_Color kYellow = {255, 220, 110, 255};

} // namespace

void InitAgents(const AgentOptions& options)
{
    g_on = true;
    g_fast = options.fast;
    Scan();
    LogInfo("agent", "%d agent(s) in the agents folders", (int)g_agents.size());
    const char* given[2] = {options.p1, options.p2};
    for (int side = 0; side < 2; side++) {
        if (!given[side])
            continue;
        int at = FindAgent(given[side]);
        std::string error = std::string("no agent file ") + given[side];
        if (at < 0 || !Choose(&g_sides[side], g_agents[at].path, &error, side))
            LogError("agent", "%s", error.c_str());
        else
            LogInfo("agent", "P%d is played by %s", side + 1, g_labels[at].c_str());
    }
}

void AgentsFrame()
{
    if (!g_on)
        return;
    GameObjects o = Objects();
    int scene = *o.scene;
    bool vs = o.game && o.game->m_gameMode == kVsHuman;
    const unsigned char* keys = KeyboardState();
    bool shift = ((keys[kDikLShift] | keys[kDikRShift]) & 0x80) != 0;
    for (int k = 0; k < 2; k++) {
        bool down = (keys[k ? kDikF6 : kDikF5] & 0x80) != 0;
        if (down && !g_keyDown[k] && scene == 1 && vs)
            Cycle(k, shift ? -1 : 1);
        g_keyDown[k] = down;
    }
    if (scene == 3 && g_lastScene != 3)
        g_world.NewFight();
    for (int side = 0; side < 2; side++) {
        Side& s = g_sides[side];
        s.playing = false;
        s.input = 0;
        if (!s.player)
            continue;
        if (g_lastScene == 3 && scene != 3) {
            LogRoutes(side ? "P2" : "P1", s);
            s.player->Reset(); // (its plan dropped with the fight)
        }
        if (!vs)
            continue;
        if (scene == 1) {
            if (g_lastScene != 1)
                s.wait = 0;
            if (Choosing(side)) {
                s.input = SelectInput(s, side, kSelectWait);
                s.playing = true;
            }
        } else if (scene == 3) {
            if (g_lastScene != 3)
                s.player->Reset();
            s.input = FightInput(s, side);
            s.playing = true;
        }
    }
    g_lastScene = scene;
}

void AgentInput(int player, unsigned char* input)
{
    if (!g_on || player < 0 || player > 1)
        return;
    if (g_sides[player].playing) {
        *input = g_sides[player].input;
        return;
    }
    // P1 an agent's in VS HUMAN: its person may play P2 with P1's controls too.
    GameObjects o = Objects();
    if (player == 1 && g_sides[0].player && o.game->m_gameMode == kVsHuman &&
        (*o.scene == 1 || *o.scene == 3))
        *input |= LocalControls();
}

bool AgentPlanning()
{
    return g_planning;
}

void StopAgents()
{
    if (!g_on)
        return;
    if (g_lastScene == 3) {
        LogRoutes("P1", g_sides[0]);
        LogRoutes("P2", g_sides[1]);
    }
    for (Side& s : g_sides) {
        if (s.planner)
            s.planner->Cancel();
    }
}

void AgentsIdle(uint64_t deadlineNs)
{
    if (!g_on)
        return;
    GameObjects o = Objects();
    CScene3* fight = (CScene3*)o.scenes[3];
    if (*o.scene != 3 || !fight || fight->m_enter != 0)
        return;
    // A little of the time left kept back, for the frame's own work.
    const uint64_t margin = 1500000;
    uint64_t now = SDL_GetTicksNS();
    if (deadlineNs <= now + margin)
        return;
    agent::Planner::Clock::time_point until =
        agent::Planner::Clock::now() + std::chrono::nanoseconds(deadlineNs - now - margin);
    Side* sides[3] = {&g_sides[0], &g_sides[1], &g_net};
    for (Side* s : sides) {
        if (s->planner && s->planner->Busy())
            s->planner->Work(until);
        if (s->mix && s->mix->Busy())
            s->mix->Work(until);
    }
}

void DrawAgents(SDL_Renderer* r)
{
    if (!g_on)
        return;
    GameObjects o = Objects();
    int scene = *o.scene;
    bool vs = o.game && o.game->m_gameMode == kVsHuman;
    if (vs && (scene == 1 || scene == 3)) {
        for (int side = 0; side < 2; side++) {
            const Side& s = g_sides[side];
            if (scene == 3 && !s.player)
                continue;
            std::string text = std::string(side ? "P2 " : "P1 ") +
                               (s.player ? "AGENT " + s.name : std::string("PLAYER")) +
                               (s.planner ? " +routes" : "");
            // Character select: at the bottom; a fight: at the top, over the life bars
            // (where netplay writes the names).
            float x = side ? 634 - Width(text, 1) : 6;
            Text(r, x, scene == 1 ? 456 : 3, text, 1, s.player ? kTeal : kGrey);
        }
        if (scene == 1) {
            std::string hint = g_agents.empty()
                                   ? "Agents: put .efzagent files in the game's agents folder"
                                   : "F5 / F6: P1 / P2 played by an agent (Shift: back)";
            Text(r, 320 - Width(hint, 1) / 2, 468, hint, 1, kGrey);
        }
    }
    if (!g_note.empty() && SDL_GetTicks() < g_noteUntil)
        Text(r, 320 - Width(g_note, 1) / 2, 24, g_note, 1, kYellow);
}

// --- Netplay

int AgentCount()
{
    return (int)g_agents.size();
}

const char* AgentLabel(int i)
{
    return i >= 0 && i < (int)g_labels.size() ? g_labels[i].c_str() : "";
}

const char* AgentFile(int i)
{
    return i >= 0 && i < (int)g_agents.size() ? g_agents[i].file.c_str() : "";
}

void RescanAgents()
{
    Scan();
}

int FindAgent(const char* nameOrPath)
{
    if (!nameOrPath || !*nameOrPath)
        return -1;
    std::string s = nameOrPath;
    for (size_t i = 0; i < g_agents.size(); i++) {
        if (g_agents[i].file == s || g_agents[i].path == s)
            return (int)i;
    }
    if (s.find_first_of("/\\") == std::string::npos) {
        FILE* f = OpenPath(s.c_str(), "rb");
        if (!f)
            return -1;
        fclose(f);
    }
    Entry e;
    e.path = s;
    e.file = FileName(s);
    e.added = true;
    if (!Peek(&e))
        return -1;
    g_agents.push_back(e);
    g_labels.push_back(Label(e));
    return (int)g_agents.size() - 1;
}

bool NetplayAgentStart(int index, int localPlayer, const char** error)
{
    static std::string why;
    NetplayAgentStop();
    if (index < 0)
        return true;
    if (index >= (int)g_agents.size() ||
        !Choose(&g_net, g_agents[index].path, &why, localPlayer, true)) {
        if (index >= (int)g_agents.size())
            why = "no such agent";
        *error = why.c_str();
        return false;
    }
    g_netLocal = localPlayer;
    if (localPlayer >= 0) {
        LogInfo("agent", "this computer's side (P%d) is played by %s", localPlayer + 1,
                g_labels[index].c_str());
        g_world.SetShown(true);
    } else {
        g_net = Side();
    }
    return true;
}

void NetplayAgentStop()
{
    if (g_netScene == 3) // (a fight going on; one over has said already)
        LogRoutes("this computer's agent", g_net);
    g_net = Side();
    g_netLocal = -1;
    g_netScene = -1;
    g_shownValid = false;
    g_world.SetShown(false);
}

bool NetplayAgentInput(int scene, int menuDelay, unsigned char* input)
{
    if (!g_net.player || g_netLocal < 0)
        return false;
    if (scene != g_netScene) {
        if (g_netScene == 3)
            LogRoutes("this computer's agent", g_net);
        if (scene == 3)
            g_world.NewFight();
        g_net.player->Reset(); // (its plan dropped: another scene)
        g_net.wait = 0;
        g_shownValid = false;
        g_netScene = scene;
    }
    if (scene == 1) {
        if (!Choosing(g_netLocal))
            return false;
        *input = SelectInput(g_net, g_netLocal, kSelectWait + std::max(0, menuDelay));
        return true;
    }
    if (scene == 3) {
        *input = ToScreen(g_net.player->Step(g_shown, g_shownValid && g_shownActionable),
                          g_shownFacing);
        return true;
    }
    return false;
}

void NetplayAgentShown()
{
    if (!g_net.player || g_netLocal < 0 || *Objects().scene != 3)
        return;
    g_shownValid = View(g_netLocal, g_shown, &g_shownActionable, &g_shownFacing);
    // Its hit, perhaps: a plan would start from this frame, the one the player sees.
    if (g_shownValid && g_net.planner && nearbyintf(g_shown[30] * 30) > 0)
        g_world.CaptureShown();
}

const char* NetplayAgentName()
{
    return g_net.player ? g_net.name.c_str() : nullptr;
}

} // namespace efz
