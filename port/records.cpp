// The REPLAY menu's RECORDS page (efz::RecordsHooks, docs/logging.md): the page after
// EXIT lists the fight records of the logs folder, newest first, and plays the one
// chosen as the game plays a replay (record.h's PlayRecord): from the record's state at
// its first tick, with its inputs and F-keys, the CPU deciding again as it did.
//
// The menu's picture (system\replay.dat) has no letters for the page, so the page draws
// its label, its list and a record's information as it plays over the frame, with SDL's
// 8x8 font, as netplay's screens and the agents' labels do.
#include <SDL3/SDL.h>
#include <algorithm>
#include <string>
#include <vector>

#include "efz.h"
#include "platform.h"
#include "log.h"
#include "record.h"

namespace efz {

namespace {

const int kRows = 18; // the list's rows on the screen

struct Color {
    Uint8 r, g, b, a;
};
const Color kWhite = {255, 255, 255, 255};
const Color kGrey = {160, 160, 160, 255};
const Color kDim = {110, 110, 110, 255};
const Color kTeal = {80, 210, 190, 255};
const Color kYellow = {255, 220, 110, 255};

std::vector<RecordSummary> g_list;
std::string g_logs;  // the logs folder; empty: none
int g_cursor = 0;    // the record chosen, in g_list
int g_top = 0;       // the first row shown
std::string g_chosen; // its path: still the one chosen when the list is read again
int g_heldDy[2];     // per side: the direction held, and for how many frames
int g_heldFor[2];
std::string g_note; // a line about the last record played, or why it wasn't
Uint64 g_noteUntil = 0;
RecordView g_last;  // the record last played, as it was when last seen
bool g_watched = false;

void Note(const std::string& text)
{
    g_note = text;
    g_noteUntil = SDL_GetTicks() + 6000;
}

// The characters by the names EfzRevival gives them (its replays' file names).
const char* CharName(int c)
{
    static const char* const names[25] = {
        "Rumi",    "Ayu",     "Mai",     "Makoto",     "Akane",  "Mayu",       "Nagamori",
        "Misaki",  "Shiori",  "Sayuri",  "NayukiS",    "Mio",    "Doppel",     "Kaori",
        "Ikumi",   "Mishio",  "Akiko",   "NayukiA",    "Unknown", "Kanna",     "Kano",
        "Minagi",  "NayukiS", "Misuzu",  "BossUnknown"};
    return c >= 0 && c < 25 ? names[c] : "?";
}

const char* ModeLabel(int mode)
{
    static const char* const names[7] = {"ARCADE",  "PRACTICE", "ARCADE", "VS CPU",
                                         "VS HUMAN", "REPLAY",  "DEMO"};
    return mode >= 0 && mode < 7 ? names[mode] : "?";
}

// "11-16 20:05" from the header's "2026-11-16T20:05:26.114-08:00".
std::string When(const RecordSummary& s)
{
    if (s.started.size() < 16)
        return "?";
    return s.started.substr(5, 5) + " " + s.started.substr(11, 5);
}

// m:ss of 64 frames a second.
std::string Clock(long frames)
{
    long seconds = frames / 64;
    char text[16];
    snprintf(text, sizeof(text), "%ld:%02ld", seconds / 60, seconds % 60);
    return text;
}

std::string Side(const RecordSummary& s, int side)
{
    std::string name = CharName(s.chars[side]);
    if (!s.agent[side].empty())
        return name + " (AI)";
    if (s.cpu[side])
        return name + " (CPU)";
    return name;
}

std::string Who(const RecordSummary& s, int side)
{
    if (!s.agent[side].empty())
        return "agent " + s.agent[side];
    if (s.unknown[side])
        return "a person or an agent (older records don't say)";
    return s.cpu[side] ? "the CPU" : "a person";
}

std::string Padded(std::string s, size_t width, bool right)
{
    if (s.size() > width)
        s = s.substr(0, width);
    std::string pad(width - s.size(), ' ');
    return right ? pad + s : s + pad;
}

// --- Reading the logs folder.

struct Found {
    std::vector<std::string>* names;
    bool dirs;
    std::string base;
};

SDL_EnumerationResult Collect(void* context, const char* dirname, const char* fname)
{
    Found* f = (Found*)context;
    std::string path = std::string(dirname) + fname;
    SDL_PathInfo info;
    if (!SDL_GetPathInfo(path.c_str(), &info))
        return SDL_ENUM_CONTINUE;
    std::string name = fname;
    if (f->dirs ? info.type == SDL_PATHTYPE_DIRECTORY
                : info.type == SDL_PATHTYPE_FILE && name.size() > 12 &&
                      name.compare(0, 6, "fight-") == 0 &&
                      name.compare(name.size() - 6, 6, ".jsonl") == 0)
        f->names->push_back(name);
    return SDL_ENUM_CONTINUE;
}

void Scan()
{
    g_list.clear();
    g_logs.clear();
    std::string session = SessionDir();
    size_t slash = session.find_last_of("/\\");
    if (session.empty() || slash == std::string::npos)
        return;
    g_logs = session.substr(0, slash);
    std::vector<std::string> sessions;
    Found dirs = {&sessions, true, g_logs};
    SDL_EnumerateDirectory(g_logs.c_str(), Collect, &dirs);
    for (const std::string& dir : sessions) {
        std::vector<std::string> fights;
        std::string base = g_logs + "/" + dir;
        Found files = {&fights, false, base};
        SDL_EnumerateDirectory(base.c_str(), Collect, &files);
        for (const std::string& name : fights) {
            RecordSummary s;
            // A replayed fight's record is the record it replayed, again.
            if (ReadRecordSummary((base + "/" + name).c_str(), &s) && !s.replayed &&
                s.ticks > 0)
                g_list.push_back(s);
        }
    }
    // Newest first: session folders are named for when they started, and fight-NNN.
    std::sort(g_list.begin(), g_list.end(),
              [](const RecordSummary& a, const RecordSummary& b) { return a.path > b.path; });
    g_cursor = 0;
    for (size_t i = 0; i < g_list.size(); i++) {
        if (g_list[i].path == g_chosen)
            g_cursor = (int)i;
    }
    g_top = std::max(0, std::min(g_cursor - kRows / 2, (int)g_list.size() - kRows));
}

// --- The hooks.

void Enter()
{
    Scan();
    std::string why = TakeRecordError();
    if (!why.empty()) {
        Note("The record couldn't be played: " + why + ".");
    } else if (g_watched && g_last.firstDiff >= 0) {
        // (the tick's frame, about: 3 ticks a frame)
        Note("This game played it otherwise than it was recorded, from " +
             Clock(g_last.firstDiff / 3) + ".");
    }
    g_watched = false;
    LogInfo("replay", "the REPLAY menu: %d fight records in %s", (int)g_list.size(),
            g_logs.empty() ? "no logs folder" : g_logs.c_str());
}

bool Move(int side, int dy)
{
    if (side < 0 || side > 1)
        return false;
    bool step = false;
    if (dy == 0) {
        g_heldFor[side] = 0;
    } else if (dy != g_heldDy[side]) {
        g_heldFor[side] = 0;
        step = true;
    } else {
        // Held: on after a third of a second, 16 rows a second.
        g_heldFor[side]++;
        step = g_heldFor[side] >= 20 && (g_heldFor[side] - 20) % 4 == 0;
    }
    g_heldDy[side] = dy;
    if (!step || g_list.empty())
        return false;
    int n = (int)g_list.size();
    g_cursor = (g_cursor + dy + n) % n;
    if (g_cursor < g_top)
        g_top = g_cursor;
    if (g_cursor >= g_top + kRows)
        g_top = g_cursor - kRows + 1;
    g_chosen = g_list[g_cursor].path;
    return true;
}

bool Play()
{
    if (g_list.empty())
        return false;
    const RecordSummary& s = g_list[g_cursor];
    std::string error;
    if (!PlayRecord(s.path.c_str(), &error)) {
        Note("This record can't be played: " + error + ".");
        return false;
    }
    g_chosen = s.path;
    g_watched = true;
    g_last = RecordView();
    g_last.firstDiff = -1;
    return true;
}

// --- Drawing, over the 640x480 screen.

void Text(SDL_Renderer* r, float x, float y, const std::string& text, float scale, Color c)
{
    std::string s;
    for (char ch : text)
        s.push_back((unsigned char)ch < 0x80 ? ch : '?'); // the font has ASCII only
    SDL_SetRenderScale(r, scale, scale);
    SDL_SetRenderDrawColor(r, 0, 0, 0, (Uint8)(c.a * 3 / 4));
    SDL_RenderDebugText(r, x / scale + 1, y / scale + 1, s.c_str());
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderDebugText(r, x / scale, y / scale, s.c_str());
    SDL_SetRenderScale(r, 1, 1);
}

float Width(const std::string& s, float scale)
{
    return (float)s.size() * SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * scale;
}

void Box(SDL_Renderer* r, float x, float y, float w, float h, Color c)
{
    SDL_FRect rect = {x, y, w, h};
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(r, &rect);
}

// A line centred at y, on a dark bar: over a fight, whatever is behind it.
void Caption(SDL_Renderer* r, float y, const std::string& text, Color c)
{
    float w = Width(text, 1);
    Box(r, 320 - w / 2 - 6, y - 4, w + 12, 16, Color{0, 0, 0, 170});
    Text(r, 320 - w / 2, y, text, 1, c);
}

const float kListX = 36, kListY = 60, kRowH = 18;

void DrawList(SDL_Renderer* r)
{
    Box(r, 24, 52, 592, 400, Color{6, 14, 24, 225});
    if (g_list.empty()) {
        std::string line = g_logs.empty() ? "No logs folder (--log-dir none): no records."
                                          : "No fight records yet.";
        Text(r, 320 - Width(line, 2) / 2, 200, line, 2, kWhite);
        std::string where = g_logs.empty() ? "" : "Each fight played is recorded in";
        Text(r, 320 - Width(where, 1) / 2, 236, where, 1, kGrey);
        Text(r, 320 - Width(g_logs, 1) / 2, 250, g_logs, 1, kGrey);
        return;
    }
    for (int row = 0; row < kRows && g_top + row < (int)g_list.size(); row++) {
        int i = g_top + row;
        const RecordSummary& s = g_list[i];
        float y = kListY + row * kRowH;
        bool at = i == g_cursor;
        if (at)
            Box(r, 28, y - 4, 584, kRowH - 1, Color{40, 110, 100, 170});
        // date mode   P1 (right-aligned) score P2   length
        float x = kListX;
        Text(r, x, y, When(s), 1, at ? kWhite : kGrey);
        x += 13 * 8;
        Text(r, x, y, ModeLabel(s.mode), 1, at ? kWhite : kGrey);
        x += 10 * 8;
        bool ended = !s.reason.empty();
        Color win = kTeal, plain = at ? kWhite : Color{220, 220, 220, 255};
        Text(r, x, y, Padded(Side(s, 0), 17, true), 1, ended && s.winner == 0 ? win : plain);
        x += 18 * 8;
        std::string score = ended ? std::to_string(s.roundsWon[0]) + "-" +
                                        std::to_string(s.roundsWon[1])
                                  : "--";
        Text(r, x, y, Padded(score, 3, false), 1, plain);
        x += 4 * 8;
        Text(r, x, y, Padded(Side(s, 1), 17, false), 1, ended && s.winner == 1 ? win : plain);
        std::string length = Clock(s.frames);
        Text(r, 604 - Width(length, 1), y, length, 1, at ? kWhite : kGrey);
    }
    // Where the list is, when it doesn't all fit.
    if ((int)g_list.size() > kRows) {
        float h = 18.0f * kRows;
        float bar = std::max(12.0f, h * kRows / g_list.size());
        float at = (h - bar) * g_top / (float)(g_list.size() - kRows);
        Box(r, 612, kListY - 4 + at, 3, bar, kGrey);
    }
    // The one chosen, at length.
    const RecordSummary& s = g_list[g_cursor];
    float y = kListY + kRows * kRowH + 6;
    Text(r, kListX, y, "P1 " + std::string(CharName(s.chars[0])) + ": " + Who(s, 0), 1, kWhite);
    Text(r, kListX, y + 12, "P2 " + std::string(CharName(s.chars[1])) + ": " + Who(s, 1), 1,
         kWhite);
    std::string end = s.reason.empty() ? "the record stops short"
                      : s.reason == "match_end"
                          ? (s.winner >= 0 ? std::string("P") + std::to_string(s.winner + 1) +
                                                 " won"
                                           : std::string("a draw"))
                          : "left (" + s.reason + ")";
    std::string facts = "Session " + s.session + " #" + std::to_string(s.fight) + ", " + end +
                        ", by build " + (s.revision.empty() ? "?" : s.revision.substr(0, 7)) +
                        (s.dirty ? "+" : "") + " " + s.os;
    Text(r, kListX, y + 24, facts, 1, kGrey);
}

void DrawMenu(SDL_Renderer* r, CScene8* menu)
{
    bool on = menu->m_page == kRecordsPage;
    // The page's label, after EXIT in the row of pages, as large as theirs.
    Text(r, 524, 16, "RECORDS", 2, on ? kWhite : Color{100, 100, 100, 255});
    if (on && menu->m_state == 0) {
        DrawList(r);
        std::string keys = "Up/Down: choose   A: play   Left/Right: pages   B: back";
        Text(r, 320 - Width(keys, 1) / 2, 458, keys, 1, kGrey);
    }
    if (on && !g_note.empty() && SDL_GetTicks() < g_noteUntil)
        Text(r, 320 - Width(g_note, 1) / 2, 40, g_note, 1, kYellow);
}

void DrawPlaying(SDL_Renderer* r, const RecordView& v)
{
    const RecordSummary* s = nullptr;
    for (const RecordSummary& e : g_list) {
        if (e.path == v.path)
            s = &e;
    }
    // An agent's side, at the top over the life bars, as in the fights it played.
    for (int side = 0; s && side < 2; side++) {
        if (s->agent[side].empty())
            continue;
        std::string text = std::string(side ? "P2 " : "P1 ") + "AGENT " + s->agent[side];
        Text(r, side ? 634 - Width(text, 1) : 6, 3, text, 1, kTeal);
    }
    // The keys, for the first seconds and while paused (they cover the gauges).
    if (v.tick < 192 * 4 || v.paused) {
        std::string line = "RECORD" +
                           (s ? " " + When(*s) + " #" + std::to_string(s->fight) : "") +
                           "   Esc: back   F8: " + (v.paused ? "go on" : "pause");
        Caption(r, 464, line, kWhite);
    }
    if (v.firstDiff >= 0)
        Caption(r, 104, "This game plays the record otherwise from here on", kYellow);
    if (v.paused)
        Text(r, 320 - Width("PAUSED", 3) / 2, 220, "PAUSED", 3, kWhite);
}

} // namespace

void InitRecords()
{
    g_records.enter = Enter;
    g_records.move = Move;
    g_records.play = Play;
}

void DrawRecords(SDL_Renderer* r)
{
    if (!g_records.play)
        return;
    GameObjects o = Objects();
    if (const RecordView* v = ViewingRecord()) {
        g_last = *v;
        if (*o.scene == 3)
            DrawPlaying(r, *v);
        return;
    }
    CScene8* menu = (CScene8*)o.scenes[8];
    // The menu, not while it fades in or out.
    if (*o.scene == 8 && menu && menu->m_enter == 0 && menu->m_leave == 0)
        DrawMenu(r, menu);
}

} // namespace efz
