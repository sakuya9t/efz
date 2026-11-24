// OPTIONS' pages (src/scene6.cpp, efz::OptionsHooks) and the native game's own settings
// file, options.ini in the save folder.
//
//   1 GAME     the game's own page, as the original has it (key.ini's settings)
//   2 REVIVAL  EfzRevival's settings offline (docs/revival-features.md): its features on
//              or off, and each of them; the music
//   3 NETPLAY  EfzRevival's netplay settings: the hole-punching server, the rollback and
//              the rest
//   4 NATIVE   the native game's: the CPU's combos (docs/agents.md); the fight records
//              of the modes but VS HUMAN (docs/logging.md); the language, the
//              resolution and HD output, to come
//
// Tab, or either side's C (D back), turns the page. Pages 2 on look as the game's own:
// over its background and title, its black bands a row, its greys and white, the choices
// side by side; in SDL's font (the game's pictures have no letters for them). A page has
// seven rows at most, the eighth band says what the one chosen does: settings that don't
// fit take another page, as EfzRevival's do. What Revival has a key for is written to
// EfzRevival.ini (port/revival/config.h: the file's other lines and its encoding kept, so
// Revival reads it as ever); what it hasn't, to options.ini.
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
    bool cpuRecords = true; // the fight records of the modes but VS HUMAN
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
    fprintf(f, "cpu_combos=%d\nrecord_cpu_fights=%d\nrevival=%d\npractice_tools=%d\n"
               "replay_tools=%d\ninput_display=%d\nhole_punching_server=%s\n",
            CpuCombos() ? 1 : 0, g_set.cpuRecords, g_set.revival, g_set.practice, g_set.replay,
            g_set.inputs, g_set.server.c_str());
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
        else if (key == "record_cpu_fights")
            g_set.cpuRecords = on;
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
    // The choices, side by side as the game's page has them; none: an action (BACK).
    std::vector<std::string> choices;
    std::function<int()> chosen;     // the choice in force
    std::function<void(int)> change; // by a step left (-1) or right, or A (+1)
    std::function<bool()> enabled;   // null: always
    std::string help;
    bool coming = false;             // not built yet: shown, not changed
};

struct Page {
    std::string tab;
    std::vector<Row> rows;
    int cursor = 0;
};

std::vector<Page> g_pages; // pages 2 on
int g_shown = -1;          // the page shown last, and when (SDL_GetTicks)
Uint64 g_shownAt = 0;

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

// A setting that is on or off: OFF, ON, as the game's page has its two-way settings.
Row Switch(const char* label, std::function<bool()> on, std::function<void()> flip,
           std::function<bool()> enabled, const char* help)
{
    Row r;
    r.label = label;
    r.choices = {"OFF", "ON"};
    r.chosen = [on] { return on() ? 1 : 0; };
    r.change = [flip](int) { flip(); };
    r.enabled = std::move(enabled);
    r.help = help;
    return r;
}

Row Coming(const char* label, const char* value, const char* help)
{
    Row r;
    r.label = label;
    r.choices = {value};
    r.chosen = [] { return 0; };
    r.help = help;
    r.coming = true;
    return r;
}

Row Back()
{
    Row r;
    r.label = "BACK";
    r.help = "Leave OPTIONS (B or Esc too).";
    return r;
}

int Rollback()
{
    return std::min(abs(Ini().maxRollback), 9);
}

// The game's page has eight rows; these have seven at most, the eighth band the chosen
// row's help.
const int kRows = 7;

void BuildPages()
{
    auto features = [] { return g_set.revival; };
    Row rollback;
    rollback.label = "MAX ROLLBACK";
    for (int n = 0; n <= 9; n++)
        rollback.choices.push_back(std::to_string(n));
    rollback.chosen = Rollback;
    rollback.change = [](int d) {
        int n = Rollback() + d;
        n = n < 0 ? 9 : n > 9 ? 0 : n;
        SetIni("Network", "MaxRollback", std::to_string(n));
    };
    rollback.help = "Netplay: the most frames run again when the other side's input comes late "
                    "(Revival's 4). More: less input delay, more rollback seen. EfzRevival.ini.";

    Page revivalPage;
    revivalPage.tab = "REVIVAL";
    revivalPage.rows = {
        Switch("REVIVAL FEATURES", [] { return g_set.revival; },
               [] {
                   Toggle(&g_set.revival, "EfzRevival's features offline");
                   revival::ApplyMusicSettings();
               },
               nullptr,
               "EfzRevival's tools and music offline. OFF: the game offline is the original's "
               "(netplay is Revival's either way). options.ini."),
        Switch("PRACTICE TOOLS", [] { return g_set.practice; },
               [] { Toggle(&g_set.practice, "the practice tools"); }, features,
               "VS PLAYER and PRACTICE: pause, frame step, save and load, boxes, the dummy's "
               "recording and replay, game speed (EfzRevival.ini's keys). options.ini."),
        Switch("REPLAY TOOLS", [] { return g_set.replay; },
               [] { Toggle(&g_set.replay, "the replay tools"); }, features,
               "REPLAY: pause, step, seek, speed, boxes; Revival's replays played from their "
               "own inputs, a character taken over. options.ini."),
        Switch("INPUT DISPLAY", [] { return g_set.inputs; },
               [] { Toggle(&g_set.inputs, "the input display"); }, features,
               "The last inputs on screen with the practice and replay tools. options.ini."),
        Switch("MUSIC", [] { return !Ini().muteBGM; },
               [] {
                   SetIni("Global", "MuteBGM", Ini().muteBGM ? "0" : "1");
                   revival::ApplyMusicSettings();
               },
               features,
               "The music (EfzRevival.ini's MuteBGM; ToggleBGM, F12, switches it anywhere). "
               "Its BGMFolder plays in place of the game's."),
        Back(),
    };

    Page netplayPage;
    netplayPage.tab = "NETPLAY";
    netplayPage.rows = {
        Switch("HOLE PUNCHING", [] { return !Ini().holePunchingServer.empty(); },
               [] {
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
               nullptr, ""), // (its help names the server: DrawPage)
        rollback,
        Switch("PRACTICE KEYS ONLINE", [] { return Ini().allowPracticeKeys; },
               [] { SetIni("Network", "AllowPracticeKeys", Ini().allowPracticeKeys ? "0" : "1"); },
               nullptr,
               "Netplay: F4 and F5 in a fight, when both sides allow them. EfzRevival.ini."),
        Switch("WINS ONLINE", [] { return Ini().displayScore; },
               [] { SetIni("Network", "DisplayScore", Ini().displayScore ? "0" : "1"); },
               nullptr, "Netplay: both players' wins at the top of the screen. EfzRevival.ini."),
        Switch("SAVE EVERY REPLAY", [] { return Ini().saveAllReplays; },
               [] { SetIni("Network", "SaveAllReplays", Ini().saveAllReplays ? "0" : "1"); },
               nullptr,
               "Netplay: every match's replay saved. OFF: only when S is pressed on character "
               "select or the results. EfzRevival.ini."),
        Switch("BATTLE LOG", [] { return Ini().saveBattleLog; },
               [] { SetIni("Network", "SaveBattleLog", Ini().saveBattleLog ? "0" : "1"); },
               nullptr, "Netplay: each game's result in BattleLog.txt. EfzRevival.ini."),
        Back(),
    };

    Page nativePage;
    nativePage.tab = "NATIVE";
    nativePage.rows = {
        Switch("CPU COMBO", CpuCombos,
               [] {
                   SetCpuCombos(!CpuCombos());
                   Save();
                   LogInfo("options", "CPU COMBO %s", CpuCombos() ? "on" : "off");
               },
               nullptr,
               "ARCADE and VS CPU: the CPU plays its combos from its character's file in "
               "agents/cpu, at its level's share of the best. options.ini."),
        Switch("RECORD CPU FIGHTS", [] { return g_set.cpuRecords; },
               [] { Toggle(&g_set.cpuRecords, "the records of the fights but VS HUMAN's"); },
               nullptr,
               "The fight records (logs, the REPLAY menu's) of ARCADE, VS CPU, PRACTICE, the "
               "demo and the replays played. OFF: only VS HUMAN's fights are recorded, a "
               "person's or an agent's. options.ini."),
        Coming("LANGUAGE", "JAPANESE", "The game's text in another language: to come."),
        Coming("RESOLUTION", "640 X 480",
               "The picture's size: to come (the window scales it now; Alt+Enter, F11: full "
               "screen)."),
        Coming("HD MODE", "OFF", "Higher-resolution pictures: to come."),
        Back(),
    };
    g_pages = {revivalPage, netplayPage, nativePage};
    for (const Page& p : g_pages) {
        if ((int)p.rows.size() > kRows)
            LogError("options", "OPTIONS' %s page has %d rows, %d fit: the rest aren't shown",
                     p.tab.c_str(), (int)p.rows.size(), kRows);
    }
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
    if (r.choices.empty() && a)
        return kOptionsBack;
    if ((dx != 0 || a) && Usable(r)) {
        r.change(dx != 0 ? dx : 1);
        return kOptionsChanged;
    }
    return kOptionsNothing;
}

// --- Drawing: the game's own page as it looks (src/scene6.cpp, system\config_ob), in SDL's
// 8x8 font over the 640x480 window, twice the game's 320x240. The page's background and
// title are the game's (CScene6::Draw); over them a black band a row, 28 high every 36
// from y 190, the label in the picture's grey and white on the row chosen, the setting's
// choices side by side, the one in force white.

struct Color {
    Uint8 r, g, b, a;
};
const Color kWhite = {255, 255, 255, 255};
const Color kGrey = {102, 102, 102, 255};  // config_ob's letters, not chosen
const Color kDim = {51, 51, 51, 255};      // a row that can't be changed
const Color kLight = {153, 153, 153, 255}; // the help, the keys
const Color kBlack = {0, 0, 0, 255};

const float kBandTop = 190, kBandPitch = 36, kBandHeight = 28;
const float kLabelX = 36;   // config_ob's letters begin at x 18
const float kChoicesX = 384; // past the longest label

void Text(SDL_Renderer* r, float x, float y, const std::string& s, float scale, Color c)
{
    SDL_SetRenderScale(r, scale, scale);
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

// The title's bar (black, the game's ゲーム設定 in the middle): how to turn the page on the
// left, the pages on the right (their names alone: numbered, four don't fit beside the
// title), the one shown in white.
void DrawTabs(SDL_Renderer* r, int page)
{
    std::vector<std::string> tabs = {"GAME"};
    for (const Page& p : g_pages)
        tabs.push_back(p.tab);
    float x = 632;
    for (int i = (int)tabs.size() - 1; i >= 0; i--) {
        const std::string& t = tabs[i];
        x -= Width(t, 1) + (i + 1 < (int)tabs.size() ? 14 : 0);
        Text(r, x, 9, t, 1, i == page ? kWhite : kGrey);
        if (i == page)
            Box(r, x, 20, Width(t, 1), 1, kWhite);
    }
    Text(r, 8, 9, "TAB, C: NEXT PAGE", 1, kGrey);
    Text(r, 8, 22, "D: PAGE BEFORE", 1, kGrey);
}

void DrawPage(SDL_Renderer* r, const Page& p)
{
    for (int i = 0; i < kRows && i < (int)p.rows.size(); i++) {
        const Row& row = p.rows[i];
        float y = kBandTop + kBandPitch * i;
        Box(r, 0, y, 640, kBandHeight, kBlack);
        bool at = i == p.cursor;
        bool usable = row.choices.empty() || Usable(row);
        float ty = y + (kBandHeight - 16) / 2;
        Text(r, kLabelX, ty, row.label, 2, at ? (usable ? kWhite : kLight) : usable ? kGrey : kDim);
        if (row.coming)
            Text(r, kLabelX + Width(row.label, 2) + 10, ty + 5, "(TO COME)", 1,
                 at ? kGrey : kDim);
        int chosen = row.chosen ? row.chosen() : -1;
        // Choices: OFF, ON as far apart as the game's; ten digits closer.
        float gap = row.choices.size() > 4 ? 8 : 32;
        float x = kChoicesX;
        for (int c = 0; c < (int)row.choices.size(); c++) {
            Color color = c == chosen ? (usable ? kWhite : kGrey) : usable ? kGrey : kDim;
            Text(r, x, ty, row.choices[c], 2, color);
            x += Width(row.choices[c], 2) + gap;
        }
    }

    // The eighth band: what the row chosen does.
    const Row& sel = p.rows[p.cursor];
    std::string help = sel.help;
    if (sel.label == "HOLE PUNCHING") {
        std::string server = Ini().holePunchingServer;
        help = "Netplay: a host behind a router, no port forwarded, is joined through a "
               "hole-punching server: " +
               (server.empty() ? std::string("none (EfzRevival.ini: HolePunchingServer = None)")
                               : server + " (EfzRevival.ini).");
    }
    if (sel.enabled && !sel.enabled())
        help = "(REVIVAL FEATURES is off.) " + help;
    float y = kBandTop + kBandPitch * kRows;
    Box(r, 0, y, 640, kBandHeight, kBlack);
    std::vector<std::string> lines = Wrap(help, (size_t)((640 - 2 * kLabelX) / 8));
    float pitch = lines.size() > 2 ? 9 : 11;
    float ly = y + (kBandHeight - (pitch * (lines.size() - 1) + 8)) / 2;
    for (const std::string& line : lines) {
        Text(r, kLabelX, ly, line, 1, kLight);
        ly += pitch;
    }
}

} // namespace

void InitOptions()
{
    Load();
    BuildPages();
    g_options.pages = Pages;
    g_options.shown = Shown;
    g_options.update = Update;
    LogInfo("options", "options.ini: CPU COMBO %s, RECORD CPU FIGHTS %s, EfzRevival's "
                       "features %s (practice %s, replay %s, input display %s)",
            CpuCombos() ? "on" : "off", g_set.cpuRecords ? "on" : "off",
            g_set.revival ? "on" : "off",
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

bool RecordCpuFights()
{
    return g_set.cpuRecords;
}

} // namespace efz
