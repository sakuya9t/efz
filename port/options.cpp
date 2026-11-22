// OPTIONS' pages (src/scene6.cpp, efz::OptionsHooks) and the native game's own settings
// file, options.ini in the save folder.
//
//   1 GAME     the game's own page, as the original has it (key.ini's settings)
//   2 REVIVAL  EfzRevival's settings (docs/revival-features.md): its features offline on
//              or off, and each of them; the music; the hole-punching server, the
//              rollback and the rest of its netplay settings
//   3 NATIVE   the native game's: the CPU's combos (docs/agents.md); the language, the
//              resolution and HD output, to come
//
// Tab, or either side's C (D back), turns the page. Pages 2 and 3 are written over the
// page's background in SDL's font (the game's pictures have no letters for them). What
// Revival has a key for is written to EfzRevival.ini (port/revival/config.h: the file's
// other lines and its encoding kept, so Revival reads it as ever); what it hasn't, to
// options.ini.
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>

#include "efz.h"
#include "agents.h"
#include "log.h"
#include "options.h"
#include "platform.h"
#include "revival/config.h"
#include "revival/music.h"

namespace efz {

namespace {

const char kDefaultServer[] = "128.199.38.97:10800"; // EfzRevival.ini as Revival ships it

// options.ini's settings.
struct Settings {
    bool revival = true;
    bool practice = true;
    bool replay = true;
    bool inputs = true;
    std::string server; // the hole-punching server last on, while it is off
};
Settings g_set;

void Save()
{
    FILE* f = OpenGameFile("options.ini", "wb");
    if (!f) {
        LogWarn("options", "cannot write options.ini");
        return;
    }
    fprintf(f, "cpu_combos=%d\nrevival=%d\npractice_tools=%d\nreplay_tools=%d\ninput_display=%d\n"
               "hole_punching_server=%s\n",
            CpuCombos() ? 1 : 0, g_set.revival, g_set.practice, g_set.replay, g_set.inputs,
            g_set.server.c_str());
    fclose(f);
}

void Load()
{
    FILE* f = OpenGameFile("options.ini", "rb");
    if (!f)
        return;
    char line[512];
    while (fgets(line, sizeof(line), f)) {
        std::string s = line;
        while (!s.empty() && (s.back() == '\n' || s.back() == '\r'))
            s.pop_back();
        size_t eq = s.find('=');
        if (eq == std::string::npos)
            continue;
        std::string key = s.substr(0, eq), value = s.substr(eq + 1);
        bool on = value == "1";
        if (key == "cpu_combos")
            SetCpuCombos(on);
        else if (key == "revival")
            g_set.revival = on;
        else if (key == "practice_tools")
            g_set.practice = on;
        else if (key == "replay_tools")
            g_set.replay = on;
        else if (key == "input_display")
            g_set.inputs = on;
        else if (key == "hole_punching_server")
            g_set.server = value;
    }
    fclose(f);
}

// --- The pages after the game's own

struct Row {
    std::string label;
    std::function<std::string()> value; // null: an action (BACK)
    std::function<void(int)> change;    // by a step left (-1) or right, or A (+1)
    std::function<bool()> enabled;      // null: always
    std::string help;
    bool coming = false;                // not built yet: shown, not changed
};

struct Page {
    std::string tab, title;
    std::vector<Row> rows;
    int cursor = 0;
};

std::vector<Page> g_pages; // pages 2 on
int g_shown = -1;          // the page shown last, and when (SDL_GetTicks)
Uint64 g_shownAt = 0;

std::string OnOff(bool on)
{
    return on ? "ON" : "OFF";
}

const revival::Config& Ini()
{
    return revival::GetConfig();
}

void SetIni(const char* section, const char* key, const std::string& value)
{
    revival::SetConfigValue(section, key, value);
}

void Toggle(bool* flag, const char* what)
{
    *flag = !*flag;
    Save();
    LogInfo("options", "%s %s", what, *flag ? "on" : "off");
}

Row Back()
{
    Row r;
    r.label = "BACK";
    r.help = "Leave OPTIONS (B or Esc too).";
    return r;
}

void BuildPages()
{
    auto features = [] { return g_set.revival; };
    Page revivalPage;
    revivalPage.tab = "REVIVAL";
    revivalPage.title = "EFZREVIVAL";
    revivalPage.rows = {
        {"REVIVAL FEATURES", [] { return OnOff(g_set.revival); },
         [](int) {
             Toggle(&g_set.revival, "EfzRevival's features offline");
             revival::ApplyMusicSettings();
         },
         nullptr,
         "EfzRevival's tools and music offline. OFF: the game offline is the original's "
         "(netplay is Revival's either way). options.ini."},
        {"PRACTICE TOOLS", [] { return OnOff(g_set.practice); },
         [](int) { Toggle(&g_set.practice, "the practice tools"); }, features,
         "VS PLAYER and PRACTICE: pause, frame step, save and load, boxes, the dummy's "
         "recording and replay, game speed (the keys of EfzRevival.ini). options.ini."},
        {"REPLAY TOOLS", [] { return OnOff(g_set.replay); },
         [](int) { Toggle(&g_set.replay, "the replay tools"); }, features,
         "REPLAY: pause, step, seek, speed, boxes; Revival's replays played from their own "
         "inputs, a character taken over. options.ini."},
        {"INPUT DISPLAY", [] { return OnOff(g_set.inputs); },
         [](int) { Toggle(&g_set.inputs, "the input display"); }, features,
         "The last inputs on screen with the practice and replay tools. options.ini."},
        {"MUSIC", [] { return OnOff(!Ini().muteBGM); },
         [](int) {
             SetIni("Global", "MuteBGM", Ini().muteBGM ? "0" : "1");
             revival::ApplyMusicSettings();
         },
         features,
         "The music (EfzRevival.ini's MuteBGM; ToggleBGM, F12, switches it anywhere). Its "
         "BGMFolder plays in place of the game's."},
        {"HOLE PUNCHING", [] { return OnOff(!Ini().holePunchingServer.empty()); },
         [](int) {
             std::string server = Ini().holePunchingServer;
             if (!server.empty()) {
                 g_set.server = server;
                 Save();
                 SetIni("Network", "HolePunchingServer", "None");
             } else {
                 SetIni("Network", "HolePunchingServer",
                        g_set.server.empty() ? std::string(kDefaultServer) : g_set.server);
             }
         },
         nullptr, ""},
        {"MAX ROLLBACK", [] { return std::to_string(std::min(abs(Ini().maxRollback), 9)); },
         [](int d) {
             int n = std::min(abs(Ini().maxRollback), 9) + d;
             n = n < 0 ? 9 : n > 9 ? 0 : n;
             SetIni("Network", "MaxRollback", std::to_string(n));
         },
         nullptr,
         "Netplay: the most frames run again when the other side's input comes late "
         "(Revival's 4). More: less input delay, more visible rollback. EfzRevival.ini."},
        {"PRACTICE KEYS ONLINE", [] { return OnOff(Ini().allowPracticeKeys); },
         [](int) { SetIni("Network", "AllowPracticeKeys", Ini().allowPracticeKeys ? "0" : "1"); },
         nullptr,
         "Netplay: F4 and F5 in a fight, when both sides allow them. EfzRevival.ini."},
        {"WINS ONLINE", [] { return OnOff(Ini().displayScore); },
         [](int) { SetIni("Network", "DisplayScore", Ini().displayScore ? "0" : "1"); },
         nullptr, "Netplay: both players' wins at the top of the screen. EfzRevival.ini."},
        {"SAVE EVERY REPLAY", [] { return OnOff(Ini().saveAllReplays); },
         [](int) { SetIni("Network", "SaveAllReplays", Ini().saveAllReplays ? "0" : "1"); },
         nullptr,
         "Netplay: every match's replay saved. OFF: only when S is pressed on character "
         "select or the results. EfzRevival.ini."},
        {"BATTLE LOG", [] { return OnOff(Ini().saveBattleLog); },
         [](int) { SetIni("Network", "SaveBattleLog", Ini().saveBattleLog ? "0" : "1"); },
         nullptr, "Netplay: each game's result in BattleLog.txt. EfzRevival.ini."},
        Back(),
    };
    Page nativePage;
    nativePage.tab = "NATIVE";
    nativePage.title = "NATIVE GAME";
    nativePage.rows = {
        {"CPU COMBO", [] { return OnOff(CpuCombos()); },
         [](int) {
             SetCpuCombos(!CpuCombos());
             Save();
             LogInfo("options", "CPU COMBO %s", CpuCombos() ? "on" : "off");
         },
         nullptr,
         "ARCADE and VS CPU: the CPU plays its combos from its character's file in "
         "agents/cpu, at its level's share of the best. options.ini."},
        {"LANGUAGE", [] { return std::string("JAPANESE"); }, nullptr, nullptr,
         "The game's text in another language: to come.", true},
        {"RESOLUTION", [] { return std::string("640 X 480"); }, nullptr, nullptr,
         "The picture's size: to come (the window scales it now; Alt+Enter, F11: full "
         "screen).",
         true},
        {"HD MODE", [] { return std::string("OFF"); }, nullptr, nullptr,
         "Higher-resolution pictures: to come.", true},
        Back(),
    };
    g_pages = {revivalPage, nativePage};
}

int Pages()
{
    return 1 + (int)g_pages.size();
}

void Shown(int page)
{
    g_shown = page;
    g_shownAt = SDL_GetTicks();
}

bool Usable(const Row& r)
{
    return r.change && !r.coming && (!r.enabled || r.enabled());
}

int Update(int page, int, int dx, int dy, bool a, bool b)
{
    if (page < 1 || page > (int)g_pages.size())
        return kOptionsNothing;
    Page& p = g_pages[page - 1];
    if (b)
        return kOptionsBack;
    int n = (int)p.rows.size();
    if (dy != 0) {
        p.cursor = (p.cursor + dy + n) % n;
        return kOptionsMoved;
    }
    const Row& r = p.rows[p.cursor];
    if (!r.value && a)
        return kOptionsBack;
    if ((dx != 0 || a) && Usable(r)) {
        r.change(dx != 0 ? dx : 1);
        return kOptionsChanged;
    }
    return kOptionsNothing;
}

// --- Drawing (SDL's 8x8 font, over the 640x480 screen)

struct Color {
    Uint8 r, g, b, a;
};
const Color kWhite = {255, 255, 255, 255};
const Color kGrey = {150, 150, 150, 255};
const Color kDim = {95, 95, 95, 255};
const Color kTeal = {80, 210, 190, 255};

void Text(SDL_Renderer* r, float x, float y, const std::string& s, float scale, Color c)
{
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
    SDL_SetRenderDrawColor(r, c.r, c.g, c.b, c.a);
    SDL_RenderFillRect(r, &rect);
}

std::vector<std::string> Wrap(const std::string& text, size_t per)
{
    std::vector<std::string> lines;
    std::string rest = text;
    while (rest.size() > per) {
        size_t cut = rest.rfind(' ', per);
        if (cut == std::string::npos || cut == 0)
            cut = per;
        lines.push_back(rest.substr(0, cut));
        rest = rest.substr(cut + (rest[cut] == ' ' ? 1 : 0));
    }
    lines.push_back(rest);
    return lines;
}

// The page tabs, at the top right: which page this is, and how to turn it.
void DrawTabs(SDL_Renderer* r, int page)
{
    std::vector<std::string> tabs = {"GAME"};
    for (const Page& p : g_pages)
        tabs.push_back(p.tab);
    float x = 632;
    for (int i = (int)tabs.size() - 1; i >= 0; i--) {
        std::string t = std::to_string(i + 1) + " " + tabs[i];
        x -= Width(t, 1) + 14;
        if (i == page)
            Box(r, x - 4, 6, Width(t, 1) + 8, 14, Color{40, 120, 110, 200});
        Text(r, x, 9, t, 1, i == page ? kWhite : kGrey);
    }
    // (on the left: the page's title is in the middle)
    Text(r, 8, 9, "TAB, C: NEXT PAGE", 1, kGrey);
    Text(r, 8, 22, "D: PAGE BEFORE", 1, kGrey);
}

void DrawPage(SDL_Renderer* r, const Page& p)
{
    const float x0 = 24, y0 = 84, w = 592, h = 388;
    Box(r, x0, y0, w, h, Color{8, 20, 32, 225});
    Box(r, x0, y0, w, 2, kTeal);
    Box(r, x0, y0 + h - 2, w, 2, kTeal);
    Text(r, 320 - Width(p.title, 2) / 2, y0 + 12, p.title, 2, kWhite);
    float y = y0 + 44;
    for (int i = 0; i < (int)p.rows.size(); i++) {
        const Row& row = p.rows[i];
        bool at = i == p.cursor;
        bool usable = !row.value || Usable(row);
        if (at)
            Box(r, x0 + 10, y - 4, w - 20, 22, Color{40, 120, 110, 150});
        Color c = !usable ? kDim : at ? kWhite : kGrey;
        if (!row.value) {
            Text(r, 320 - Width(row.label, 2) / 2, y, row.label, 2, at ? kTeal : c);
        } else {
            Text(r, x0 + 20, y, row.label, 2, c);
            std::string v = row.value();
            if (row.coming) {
                Text(r, x0 + 20 + Width(row.label, 2) + 10, y + 5, "(TO COME)", 1, kDim);
                Text(r, 400, y, "  " + v, 2, kDim);
            } else {
                Text(r, 400, y, at && usable ? "< " + v + " >" : "  " + v, 2, c);
            }
        }
        y += 24;
    }
    const Row& sel = p.rows[p.cursor];
    std::string help = sel.help;
    if (sel.label == "HOLE PUNCHING") {
        std::string server = Ini().holePunchingServer;
        help = "Netplay: a host behind a router, no port forwarded, joined through a "
               "hole-punching server: " +
               (server.empty() ? std::string("none (EfzRevival.ini: HolePunchingServer = None)")
                               : server + " (EfzRevival.ini), which hosting and joining then contact") +
               ".";
    }
    if (sel.enabled && !sel.enabled())
        help = "(REVIVAL FEATURES is off.) " + help;
    float hy = y + 4;
    for (const std::string& line : Wrap(help, 70)) {
        Text(r, x0 + 20, hy, line, 1, kGrey);
        hy += 11;
    }
    std::string footer = "Up/Down  Left/Right, A: change  B: leave";
    Text(r, 320 - Width(footer, 1) / 2, y0 + h - 16, footer, 1, kGrey);
}

} // namespace

void InitOptions()
{
    Load();
    BuildPages();
    g_options.pages = Pages;
    g_options.shown = Shown;
    g_options.update = Update;
    LogInfo("options", "options.ini: CPU COMBO %s, EfzRevival's features %s (practice %s, "
                       "replay %s, input display %s)",
            CpuCombos() ? "on" : "off", g_set.revival ? "on" : "off",
            g_set.practice ? "on" : "off", g_set.replay ? "on" : "off",
            g_set.inputs ? "on" : "off");
}

void DrawOptions(SDL_Renderer* r)
{
    // While the page is drawn (not its fades, nor the record and gallery pages).
    if (g_shown < 0 || SDL_GetTicks() - g_shownAt > 100 || *Objects().scene != 6)
        return;
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    DrawTabs(r, g_shown);
    if (g_shown >= 1 && g_shown <= (int)g_pages.size())
        DrawPage(r, g_pages[g_shown - 1]);
}

bool RevivalFeatures()
{
    return g_set.revival;
}

bool PracticeTools()
{
    return g_set.revival && g_set.practice;
}

bool ReplayTools()
{
    return g_set.revival && g_set.replay;
}

bool InputDisplay()
{
    return g_set.inputs;
}

} // namespace efz
