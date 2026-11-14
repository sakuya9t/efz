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
#include <SDL3/SDL.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>
#include <memory>
#include <string>
#include <vector>

#include "efz.h"
#include "agents.h"
#include "log.h"
#include "platform.h"
#include "agent/observe.h"
#include "agent/policy.h"

namespace efz {

namespace {

const unsigned char kRight = 0x01, kLeft = 0x02, kDown = 0x04, kUp = 0x08, kA = 0x10, kC = 0x40;
const int kDikF5 = 0x3f, kDikF6 = 0x40;
const int kVsHuman = 4;   // CGame::m_gameMode
const int kSelectWait = 3; // frames between character select presses, at the least

struct Entry {
    std::string path; // UTF-8
    std::string file; // its file name
    std::string name;
    int character = -1;
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

bool Peek(Entry* e)
{
    std::string error;
    if (!agent::Policy::Peek(e->path.c_str(), &e->name, &e->character, &error)) {
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
        g_labels.push_back(e.name + " (" + CharacterLabel(e.character) + ")");
}

int IndexOf(const std::string& path)
{
    for (size_t i = 0; i < g_agents.size(); i++) {
        if (g_agents[i].path == path)
            return (int)i;
    }
    return -1;
}

// Has the side played by the agent at `path` (empty: a person); false with *error.
bool Choose(Side* s, const std::string& path, std::string* error)
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
        LogInfo("agent", "%s: \"%s\", %s, deciding every %d frame(s), %d frames late, %d "
                         "inputs of history",
                e.path.c_str(), p->name.c_str(), CharacterLabel(p->character).c_str(),
                p->frameSkip, p->delay, p->history);
    }
    s->path = e.path;
    s->name = e.name;
    s->policy = e.policy;
    s->player.reset(new agent::Player(s->policy.get(), Seed()));
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

void Cycle(int side)
{
    Scan();
    Side& s = g_sides[side];
    int at = s.path.empty() ? -1 : IndexOf(s.path);
    std::string error;
    for (int next = at + 1;; next++) {
        if (next >= (int)g_agents.size()) {
            Choose(&s, "", &error);
            Note(std::string(side ? "P2" : "P1") + ": a person");
            return;
        }
        if (Choose(&s, g_agents[next].path, &error)) {
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
    Scan();
    LogInfo("agent", "%d agent(s) in the agents folders", (int)g_agents.size());
    const char* given[2] = {options.p1, options.p2};
    for (int side = 0; side < 2; side++) {
        if (!given[side])
            continue;
        int at = FindAgent(given[side]);
        std::string error = std::string("no agent file ") + given[side];
        if (at < 0 || !Choose(&g_sides[side], g_agents[at].path, &error))
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
    for (int k = 0; k < 2; k++) {
        bool down = (keys[k ? kDikF6 : kDikF5] & 0x80) != 0;
        if (down && !g_keyDown[k] && scene == 1 && vs)
            Cycle(k);
        g_keyDown[k] = down;
    }
    for (int side = 0; side < 2; side++) {
        Side& s = g_sides[side];
        s.playing = false;
        s.input = 0;
        if (!s.player || !vs)
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
                               (s.player ? "AGENT " + s.name : std::string("PLAYER"));
            // Character select: at the bottom; a fight: at the top, over the life bars
            // (where netplay writes the names).
            float x = side ? 634 - Width(text, 1) : 6;
            Text(r, x, scene == 1 ? 456 : 3, text, 1, s.player ? kTeal : kGrey);
        }
        if (scene == 1) {
            std::string hint = g_agents.empty()
                                   ? "Agents: put .efzagent files in the game's agents folder"
                                   : "F5 / F6: P1 / P2 played by an agent";
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
    g_labels.push_back(e.name + " (" + CharacterLabel(e.character) + ")");
    return (int)g_agents.size() - 1;
}

bool NetplayAgentStart(int index, int localPlayer, const char** error)
{
    static std::string why;
    NetplayAgentStop();
    if (index < 0)
        return true;
    if (index >= (int)g_agents.size() || !Choose(&g_net, g_agents[index].path, &why)) {
        if (index >= (int)g_agents.size())
            why = "no such agent";
        *error = why.c_str();
        return false;
    }
    g_netLocal = localPlayer;
    if (localPlayer >= 0)
        LogInfo("agent", "this computer's side (P%d) is played by %s", localPlayer + 1,
                g_labels[index].c_str());
    return true;
}

void NetplayAgentStop()
{
    g_net = Side();
    g_netLocal = -1;
    g_netScene = -1;
    g_shownValid = false;
}

bool NetplayAgentInput(int scene, int menuDelay, unsigned char* input)
{
    if (!g_net.player || g_netLocal < 0)
        return false;
    if (scene != g_netScene) {
        if (scene == 3)
            g_net.player->Reset();
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
}

const char* NetplayAgentName()
{
    return g_net.player ? g_net.name.c_str() : nullptr;
}

} // namespace efz
