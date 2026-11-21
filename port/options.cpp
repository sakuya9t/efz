// OPTIONS' CPU COMBO row (src/scene6.cpp, efz::OptionsHooks) and the native game's own
// settings file, options.ini in the save folder: what key.ini doesn't hold. key.ini is
// the original's (157 bytes: four presets of key bindings with the page's settings in
// the first, and the preset chosen), which config.exe and EfzRevival read and write too.
//
// CPU COMBO: whether the game's CPU plays its combos from its character's agent file
// (port/agent/play.cpp, docs/agents.md), aimed at its level's share of the most damaging
// combo found at each hit. Off by default.
//
// The row is made from the page's own pictures, as NET PLAY's title row is
// (port/netplay/titleitem.cpp): CPU from CPU LEVEL's label (ＣＰＵ難易度), コンボ from the
// character record page's 最大コンボ数 (system\score.dat, which the page loads too, with
// the same 32 colours), its bar from the page's. Its values, なし (off) and あり (on), are
// in no picture of the game: they are the glyphs below, drawn with the colours the
// page's letters use, white and grey. If the pictures aren't 4.02's (a translation
// patch), the row is the page's bar with its text written over it in SDL's font.
#include <SDL3/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <map>
#include <string>
#include <vector>

#include "efz.h"
#include "agents.h"
#include "log.h"
#include "options.h"
#include "platform.h"

namespace efz {

namespace {

const int kWidth = 320, kRow = 14;
const int kBase = 161; // the page's pictures' first colour (CScene6 loads them there)
const int kGreyTop = 95, kWhiteTop = 261, kPitch = 18; // config_ob's rows, plain and highlighted
const int kCpuLevelItem = 3, kBarItem = 5;             // CPU LEVEL's row; a row with a short label
const int kCpuX0 = 16, kCpuX1 = 57;                    // its ＣＰＵ: three cells of 14 pixels
const int kScoreComboTop = 215;                        // score.dat's 最大コンボ数 row
const int kComboX0 = 43, kComboX1 = 86;                // its コンボ: three cells (ボ's mark to 85)
const int kOffX = 128, kOnX = 173;                     // the values: two cells each, where
const int kOffSprite = 112, kOnSprite = 160, kSprite = 48; // EFFECT's are, and their sprites

// The values' glyphs: なし and あり, 14 x 14 cells of coverage (hex digits, '.' none) on the
// row's line, rendered from Droid Sans Fallback at 12 pixels (Apache License 2.0,
// docs/third-party.md).
const char* const kGlyphs[4][kRow] = {
    { // な
        "..............",
        "..............",
        "....14........",
        "....5b..1.....",
        "..59cdb77e6...",
        "..47f742.3cb..",
        "...4d...46.4..",
        "...98...7a....",
        "...f2...6a....",
        "..6c.4879b....",
        "..c43e78cfb3..",
        "....3e55c99e1.",
        ".....6bc8.....",
        "..............",
    },
    { // し
        "..............",
        "..............",
        "....41........",
        "....e3........",
        "....e3........",
        "....f2........",
        "....f1........",
        "....f1.....1..",
        "....f.....6b..",
        "....f.....c6..",
        "....e3...8e...",
        "....5e99cd2...",
        ".....2664.....",
        "..............",
    },
    { // あ
        "..............",
        "..............",
        ".....22.......",
        ".....97..11...",
        "..4ffffffeb...",
        ".....c4.4.....",
        "....1dddf7....",
        "...5ef6aaad1..",
        "..3e2c3e1.a8..",
        "..96.ba9..7b..",
        "..a5.bd...c7..",
        "..4ecc158ea...",
        "...23..982....",
        "..............",
    },
    { // り
        "..............",
        "..............",
        "..............",
        "...47..6fd1...",
        "...7a..b2b6...",
        "...98....89...",
        "...a7....7a...",
        "...a7....89...",
        "...97....a7...",
        "...86....e4...",
        "........8d....",
        ".....27dd2....",
        ".....2a6......",
        "..............",
    },
};

IDirectDrawSurface* g_row; // kWidth x 2 rows: the row plain, then highlighted (bar and letters)
bool g_tried = false;
bool g_letters = false;    // the letters made from the pictures (else written over: Fallback)

// The row as drawn last when its letters couldn't be made: what DrawOptions writes.
struct Fallback {
    Uint64 at = 0; // SDL_GetTicks when drawn
    int y = 0;
    bool selected = false, on = false;
} g_fallback;

BYTE At(IDirectDrawSurface* s, int x, int y)
{
    return ((BYTE*)s->pixels)[y * s->pitch + x];
}

BYTE& Out(int x, int y)
{
    return ((BYTE*)g_row->pixels)[y * g_row->pitch + x];
}

// Runs of columns in [x0, x1) of rows [y0, y0 + kRow) with a pixel neither `key` nor `bar`.
std::vector<std::pair<int, int>> Letters(IDirectDrawSurface* s, int x0, int x1, int y0, BYTE key,
                                         BYTE bar)
{
    std::vector<std::pair<int, int>> out;
    int start = -1;
    for (int x = x0; x <= x1; x++) {
        bool ink = false;
        for (int y = y0; x < x1 && y < y0 + kRow && !ink; y++) {
            BYTE v = At(s, x, y);
            ink = v != key && v != bar;
        }
        if (ink && start < 0)
            start = x;
        if (!ink && start >= 0) {
            out.push_back({start, x});
            start = -1;
        }
    }
    return out;
}

bool Build(CGraphics* graphics, IDirectDrawSurface* menu, IDirectDrawSurface* score, BYTE key)
{
    if (!menu || menu->width < kWidth || menu->height < kWhiteTop + 8 * kPitch)
        return false;
    g_row = new IDirectDrawSurface(kWidth, 2 * kRow);
    // The bar: a row's, its letters taken out (the bar's colour where they were).
    const int plain = kGreyTop + kBarItem * kPitch, high = kWhiteTop + kBarItem * kPitch;
    const BYTE bar = At(menu, kWidth - 1, high + kRow / 2);
    for (int y = 0; y < kRow; y++) {
        for (int x = 0; x < kWidth; x++) {
            BYTE a = At(menu, x, plain + y), b = At(menu, x, high + y);
            Out(x, y) = a == key ? key : bar;
            Out(x, kRow + y) = b == key ? key : bar;
        }
    }
    if (!score || score->width < kWidth || score->height < kScoreComboTop + kRow)
        return true;
    // The pictures are 4.02's: CPU LEVEL's label is ＣＰＵ and three cells on, 難易度; the
    // record page's row is 最大コンボ数, コ and ン apart, ボ and 数 run together.
    std::vector<std::pair<int, int>> cpu =
        Letters(menu, 0, 112, kWhiteTop + kCpuLevelItem * kPitch, key, bar);
    std::vector<std::pair<int, int>> combo = Letters(score, 0, 120, kScoreComboTop, key, bar);
    bool expected = cpu.size() == 4 && cpu[0].first >= kCpuX0 && cpu[2].second <= kCpuX1 &&
                    cpu[3].first >= kCpuX1 - 1 && combo.size() == 5 &&
                    combo[2].first >= kComboX0 && combo[2].first <= kComboX0 + 4 &&
                    combo[3].first >= kComboX0 + 14 && combo[3].first <= kComboX0 + 18 &&
                    combo[4].first >= kComboX0 + 28 && combo[4].first <= kComboX0 + 32;
    if (!expected) {
        LogWarn("options", "the OPTIONS page's pictures aren't 4.02's (CPU LEVEL's label in %d "
                           "pieces, the record page's 最大コンボ数 in %d): CPU COMBO is written "
                           "over its row",
                (int)cpu.size(), (int)combo.size());
        return true;
    }
    // The page's two ramps: each colour of the highlighted letters, and the one the plain
    // letters have in its place.
    std::map<BYTE, std::map<BYTE, int>> pairs;
    for (int item = 0; item < 8; item++) {
        for (int y = 0; y < kRow; y++) {
            for (int x = 0; x < 112; x++) {
                BYTE w = At(menu, x, kWhiteTop + item * kPitch + y);
                BYTE g = At(menu, x, kGreyTop + item * kPitch + y);
                if (w != key && w != bar)
                    pairs[w][g]++;
            }
        }
    }
    PALETTEENTRY palette[256];
    memset(palette, 0, sizeof(palette));
    graphics->LoadPaletteDat(palette, "system\\config_ob.dat", 0, kBase, 32);
    auto bright = [&](BYTE c) {
        return (palette[c].peRed + palette[c].peGreen + palette[c].peBlue) / 3;
    };
    std::map<BYTE, BYTE> grey; // highlighted colour -> plain
    for (const auto& p : pairs) {
        int most = 0;
        for (const auto& g : p.second) {
            if (g.second > most) {
                most = g.second;
                grey[p.first] = g.first;
            }
        }
    }
    auto toGrey = [&](BYTE w) {
        if (w == key || w == bar)
            return w;
        auto it = grey.find(w);
        if (it != grey.end())
            return it->second;
        BYTE nearest = bar; // a colour the letters don't have: the nearest that they do
        for (const auto& g : grey) {
            if (nearest == bar || abs(bright(g.first) - bright(w)) < abs(bright(nearest) - bright(w)))
                nearest = g.first;
        }
        return nearest == bar ? w : grey[nearest];
    };
    BYTE level[16]; // a glyph's coverage -> the highlighted colour of that brightness
    for (int l = 0; l < 16; l++) {
        BYTE best = bar;
        for (const auto& g : grey) {
            if (best == bar || abs(bright(g.first) - l * 17) < abs(bright(best) - l * 17))
                best = g.first;
        }
        level[l] = best;
    }
    for (int y = 0; y < kRow; y++) {
        const int row = kWhiteTop + kCpuLevelItem * kPitch + y;
        for (int x = kCpuX0; x < kCpuX1; x++) {
            BYTE w = At(menu, x, row);
            if (w != key && w != bar) {
                Out(x, kRow + y) = w;
                Out(x, y) = At(menu, x, kGreyTop + kCpuLevelItem * kPitch + y);
            }
        }
        for (int x = kComboX0; x < kComboX1; x++) {
            BYTE w = At(score, x, kScoreComboTop + y);
            if (w != key && w != bar) {
                Out(x - kComboX0 + kCpuX1, kRow + y) = w;
                Out(x - kComboX0 + kCpuX1, y) = toGrey(w);
            }
        }
        for (int g = 0; g < 4; g++) {
            int at = (g < 2 ? kOffX : kOnX) + (g % 2) * kRow;
            for (int x = 0; x < kRow; x++) {
                char c = kGlyphs[g][y][x];
                int l = c >= '0' && c <= '9' ? c - '0' : c >= 'a' && c <= 'f' ? c - 'a' + 10 : 0;
                if (l > 0) {
                    Out(at + x, kRow + y) = level[l];
                    Out(at + x, y) = toGrey(level[l]);
                }
            }
        }
    }
    g_letters = true;
    return true;
}

void DrawRow(CGraphics* graphics, IDirectDrawSurface* menu, IDirectDrawSurface* score, BYTE key,
             int y, bool selected, bool on)
{
    if (!g_tried) {
        g_tried = true;
        if (!Build(graphics, menu, score, key)) {
            LogWarn("options", "the OPTIONS page's pictures have no row to make CPU COMBO's from");
            g_row = nullptr;
        }
    }
    if (g_row) {
        graphics->Blit(MakeRect(0, y, kWidth, kRow), g_row, MakeRect(0, 0, kWidth, kRow), key, 0);
        if (selected && g_letters)
            graphics->Blit(MakeRect(0, y, 112, kRow), g_row, MakeRect(0, kRow, 112, kRow), key, 0);
        int sprite = on ? kOnSprite : kOffSprite;
        if (g_letters)
            graphics->Blit(MakeRect(sprite, y, kSprite, kRow), g_row,
                           MakeRect(sprite, kRow, kSprite, kRow), key, 0);
    }
    if (!g_letters) {
        g_fallback.at = SDL_GetTicks();
        g_fallback.y = y;
        g_fallback.selected = selected;
        g_fallback.on = on;
    }
}

// --- options.ini

void Save()
{
    FILE* f = OpenGameFile("options.ini", "wb");
    if (!f) {
        LogWarn("options", "cannot write options.ini");
        return;
    }
    fprintf(f, "cpu_combos=%d\n", CpuCombos() ? 1 : 0);
    fclose(f);
}

void Load()
{
    FILE* f = OpenGameFile("options.ini", "rb");
    if (!f)
        return;
    char line[256];
    while (fgets(line, sizeof(line), f)) {
        std::string s = line;
        while (!s.empty() && (s.back() == '\n' || s.back() == '\r'))
            s.pop_back();
        size_t eq = s.find('=');
        if (eq == std::string::npos)
            continue;
        std::string key = s.substr(0, eq), value = s.substr(eq + 1);
        if (key == "cpu_combos")
            SetCpuCombos(value == "1");
    }
    fclose(f);
}

void Set(bool on)
{
    SetCpuCombos(on);
    Save();
    LogInfo("options", "CPU COMBO %s", on ? "on" : "off");
}

bool Get()
{
    return CpuCombos();
}

} // namespace

void InitOptions()
{
    Load();
    g_options.drawCpuCombo = DrawRow;
    g_options.cpuCombo = Get;
    g_options.setCpuCombo = Set;
    LogInfo("options", "options.ini: CPU COMBO %s", CpuCombos() ? "on" : "off");
}

void DrawOptions(SDL_Renderer* r)
{
    if (g_letters || SDL_GetTicks() - g_fallback.at > 100 || *Objects().scene != 6)
        return;
    // The row's text in SDL's font over the 640 x 480 screen (the page is 320 x 240).
    auto text = [&](float x, const char* s, bool bright) {
        SDL_SetRenderDrawColor(r, bright ? 255 : 150, bright ? 255 : 150, bright ? 255 : 150, 255);
        SDL_SetRenderScale(r, 2, 2);
        SDL_RenderDebugText(r, x / 2, (float)(g_fallback.y * 2 + 6) / 2, s);
        SDL_SetRenderScale(r, 1, 1);
    };
    text(32, "CPU COMBO", g_fallback.selected);
    text(2 * kOffX, "OFF", !g_fallback.on);
    text(2 * kOnX, "ON", g_fallback.on);
}

} // namespace efz
