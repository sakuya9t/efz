// Netplay in the native game (netplay.h): the NET PLAY screens over the title, the
// protocol and the session tied to the game's loop, and what the screen shows during a
// match.
//
// The screens, drawn over the title with SDL's own small font:
//   setup    host or join, the address to join, the UDP port, the name; START
//   connect  waiting for a player, or for the host; then measuring the connection
//   delay    the input delay to start with (the recommended one chosen)
//   match    the game runs the match; the screen shows the names, wins, ping and delay
//   ended    why the match ended; back to setup
// The keyboard drives them (arrows, Enter, Esc, typing), or P1's controls (A, B).
#include <SDL3/SDL.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <algorithm>
#include <string>
#include <vector>

#include "efz.h"
#include "../netplay.h"
#include "../platform.h"
#include "../log.h"
#include "../record.h"
#include "protocol.h"
#include "session.h"

namespace efz {
namespace netplay {
bool DrawTitleItem(CGraphics* graphics, IDirectDrawSurface* menu, BYTE key, bool selected, int x,
                   int y);
} // namespace netplay

namespace {

using netplay::Protocol;
using netplay::Session;
using netplay::Settings;

enum Screen { kOff, kSetup, kConnect, kDelay, kMatch, kEnded };
// The setup screen's rows.
enum Row { kRowMode, kRowAddress, kRowPort, kRowName, kRowSide, kRowStart, kRowBack, kRowCount };

struct Menu {
    Screen screen = kOff;
    int row = kRowStart;
    bool host = true;
    std::string address;
    std::string port = "10800";
    std::string name = "Player";
    int side = 0; // 0 P1, 1 P2, 2 random
    std::string error;
    std::string ended;
    int delay = 0;
    std::vector<std::string> addresses; // this computer's, for the host
    unsigned char pad = 0;              // P1's controls on the last frame
    bool escDown = false;
    // From the command line: start at once, choose this delay (-1 the recommended).
    bool automatic = false;
    int autoDelay = -1;
    int lagMs = 0;
    int jitterMs = 0;
    bool paletteSet = false;
    // NET PLAY written over the title when its letters couldn't make the row.
    bool titleText = false;
    bool titleSelected = false;
    int titleX = 0, titleY = 0; // where the row goes, on the title's 320x240
    int replayNote = 0; // frames left to show the saved replay's name
    std::string replayShown;
};

Menu g_menu;
Protocol g_protocol;
Session g_session;

// --- Settings, kept in netplay.ini in the save folder between runs.

void LoadSettings()
{
    FILE* f = OpenGameFile("netplay.ini", "rb");
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
        if (key == "mode")
            g_menu.host = value != "join";
        else if (key == "address")
            g_menu.address = value;
        else if (key == "port")
            g_menu.port = value;
        else if (key == "name" && !value.empty())
            g_menu.name = value;
        else if (key == "side")
            g_menu.side = std::max(0, std::min(atoi(value.c_str()), 2));
    }
    fclose(f);
}

void SaveSettings()
{
    FILE* f = OpenGameFile("netplay.ini", "wb");
    if (!f)
        return;
    fprintf(f, "mode=%s\naddress=%s\nport=%s\nname=%s\nside=%d\n", g_menu.host ? "host" : "join",
            g_menu.address.c_str(), g_menu.port.c_str(), g_menu.name.c_str(), g_menu.side);
    fclose(f);
}

// --- The game

void DrawTitle()
{
    GameObjects o = Objects();
    CScene0* title = (CScene0*)o.scenes[0];
    if (!title || *o.scene != 0)
        return;
    if (!g_menu.paletteSet) {
        // A title made anew sets its palette on its first update, which it hasn't had.
        o.graphics->SetPalette(title->m_palette);
        g_menu.paletteSet = true;
    }
    title->Draw();
}

void SetHooks(bool active)
{
    g_netplay.active = active;
}

void StartMatch()
{
    SDL_StopTextInput(Window());
    SuspendRecorder(true);
    RestartGame();
    SetHooks(true);
    g_session.Start(&g_protocol);
    g_menu.screen = kMatch;
    g_menu.escDown = (KeyboardState()[1] & 0x80) != 0;
    g_menu.replayNote = 0;
}

// After a match, or when it couldn't start: the game as at startup again.
void EndMatch(const std::string& why)
{
    bool wasRunning = g_session.Running();
    if (g_protocol.phase != Protocol::kIdle && g_protocol.phase != Protocol::kEnded)
        g_protocol.Quit(why);
    if (wasRunning) {
        g_session.Stop();
        SetHooks(false);
        RestartGame();
        SuspendRecorder(false);
        g_menu.paletteSet = false;
    }
    g_protocol.Close();
    g_menu.ended = why;
    if (g_protocol.desyncFrame >= 0)
        g_menu.ended += " (the games went out of sync at frame " +
                        std::to_string(g_protocol.desyncFrame) + ": see the log)";
    g_menu.screen = kEnded;
    if (g_menu.automatic) {
        LogInfo("net", "%s; quitting (--host/--join)", g_menu.ended.c_str());
        RequestQuit();
    }
}

void Begin()
{
    g_menu.error.clear();
    long port = atol(g_menu.port.c_str());
    if (port < 1 || port > 65535) {
        g_menu.error = "The port must be a number from 1 to 65535";
        return;
    }
    if (!g_menu.host && g_menu.address.empty()) {
        g_menu.error = "Type the address of the computer to join";
        return;
    }
    Settings s;
    s.host = g_menu.host;
    s.address = g_menu.address;
    s.port = (uint16_t)port;
    s.name = g_menu.name.empty() ? "Player" : g_menu.name;
    s.side = g_menu.side;
    s.lagMs = g_menu.lagMs;
    s.jitterMs = g_menu.jitterMs;
    if (!g_menu.automatic)
        SaveSettings();
    std::string error;
    if (!g_protocol.Start(s, &error)) {
        g_menu.error = error;
        LogWarn("net", "can't start: %s", error.c_str());
        if (g_menu.automatic) {
            LogError("net", "%s", error.c_str());
            RequestQuit();
        }
        return;
    }
    g_menu.addresses = s.host ? net::LocalAddresses() : std::vector<std::string>();
    g_menu.screen = kConnect;
}

void CloseMenu()
{
    g_menu.screen = kOff;
    SDL_StopTextInput(Window());
}

void OpenMenu()
{
    g_menu.screen = kSetup;
    g_menu.row = kRowStart;
    g_menu.error.clear();
    g_menu.pad = LocalControls();
    SDL_StartTextInput(Window());
}

bool RowShown(int row)
{
    if (row == kRowAddress)
        return !g_menu.host;
    if (row == kRowSide)
        return g_menu.host;
    return true;
}

std::string* RowText(int row)
{
    switch (row) {
    case kRowAddress: return &g_menu.address;
    case kRowPort: return &g_menu.port;
    case kRowName: return &g_menu.name;
    default: return nullptr;
    }
}

// --- What the player does on the screens: a key, or P1's controls.

enum Action { kNone, kUp, kDown, kLeft, kRight, kOk, kBack, kErase };

void Act(Action a)
{
    switch (g_menu.screen) {
    case kSetup:
        if (a == kUp || a == kDown) {
            int step = a == kUp ? -1 : 1;
            do
                g_menu.row = (g_menu.row + step + kRowCount) % kRowCount;
            while (!RowShown(g_menu.row));
        } else if ((a == kLeft || a == kRight) && g_menu.row == kRowMode) {
            g_menu.host = !g_menu.host;
        } else if ((a == kLeft || a == kRight) && g_menu.row == kRowSide) {
            g_menu.side = (g_menu.side + (a == kLeft ? 2 : 1)) % 3;
        } else if (a == kErase) {
            if (std::string* text = RowText(g_menu.row)) {
                if (!text->empty())
                    text->pop_back();
            }
        } else if (a == kOk) {
            if (g_menu.row == kRowStart)
                Begin();
            else if (g_menu.row == kRowBack)
                CloseMenu();
            else if (g_menu.row == kRowMode)
                g_menu.host = !g_menu.host;
            else
                Act(kDown);
        } else if (a == kBack) {
            CloseMenu();
        }
        break;
    case kConnect:
        if (a == kBack) {
            g_protocol.Quit("Cancelled");
            g_protocol.Close();
            g_menu.screen = kSetup;
        }
        break;
    case kDelay:
        if (a == kLeft)
            g_menu.delay = std::max(g_protocol.minimumDelay, g_menu.delay - 1);
        else if (a == kRight)
            g_menu.delay = std::min(20, g_menu.delay + 1);
        else if (a == kOk) {
            g_protocol.ChooseDelay(g_menu.delay);
            g_menu.screen = kConnect;
        } else if (a == kBack) {
            g_protocol.Quit("Cancelled");
            g_protocol.Close();
            g_menu.screen = kSetup;
        }
        break;
    case kEnded:
        if (a == kOk || a == kBack) {
            g_menu.screen = kSetup;
            g_menu.row = kRowStart;
            SDL_StartTextInput(Window());
        }
        break;
    default:
        break;
    }
}

void PadActions()
{
    unsigned char now = LocalControls();
    unsigned char pressed = now & ~g_menu.pad;
    g_menu.pad = now;
    if (pressed & 8)
        Act(kUp);
    if (pressed & 4)
        Act(kDown);
    if (pressed & 2)
        Act(kLeft);
    if (pressed & 1)
        Act(kRight);
    if (pressed & 0x10)
        Act(kOk);
    if (pressed & 0x20)
        Act(kBack);
}

// --- The match, each real frame

void MatchFrame()
{
    g_protocol.Poll();
    if (g_protocol.phase == Protocol::kEnded) {
        EndMatch(g_protocol.message);
        return;
    }
    GameObjects o = Objects();
    bool esc = (KeyboardState()[1] & 0x80) != 0;
    bool escPressed = esc && !g_menu.escDown;
    g_menu.escDown = esc;
    // Esc leaves the match, except in a fight, where it is the players' input (back to
    // character select for both); there it leaves only when the opponent has gone quiet.
    if (escPressed && (*o.scene != 3 || g_session.stalled > 3 * 64)) {
        EndMatch("You left the match");
        return;
    }
    // WinMain's, once a real frame: the flag of odd frames and the music's loop.
    o.game->m_oddFrame = !o.game->m_oddFrame;
    o.sound->UpdateLoop(o.game->m_music);
    g_session.Update();
    if (g_session.Frame() > 64 && *Objects().scene == 0) {
        EndMatch("The match went back to the title");
        return;
    }
    if (!g_session.savedReplay.empty() && g_session.savedReplay != g_menu.replayShown) {
        g_menu.replayShown = g_session.savedReplay;
        g_menu.replayNote = 4 * 64;
    }
    if (g_menu.replayNote > 0)
        g_menu.replayNote--;
    // While no frame runs, the last one is shown again with what the wait is for.
    if (g_session.stalled >= 16) {
        if (IDirectDrawSurface* back = o.graphics->m_back)
            Present(back, ScreenPalette(o.graphics));
    }
}

// --- Drawing (SDL's 8x8 font, over the 640x480 screen)

struct Color {
    Uint8 r, g, b, a;
};
const Color kWhite = {255, 255, 255, 255};
const Color kGrey = {150, 150, 150, 255};
const Color kTeal = {80, 210, 190, 255};
const Color kRed = {255, 90, 80, 255};
const Color kYellow = {255, 220, 110, 255};

// Text at (x, y), each 8x8 letter `scale` times as large, with a shadow.
void Text(SDL_Renderer* r, float x, float y, const std::string& utf8, float scale, Color c)
{
    std::string s;
    for (size_t i = 0; i < utf8.size(); i++) {
        unsigned char ch = (unsigned char)utf8[i];
        if (ch < 0x80) {
            s.push_back((char)ch);
        } else if ((ch & 0xc0) == 0xc0) {
            s.push_back('?'); // the font has ASCII only
        }
    }
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

// The lines of text that fit `width` at `scale`, broken at spaces.
std::vector<std::string> Wrap(const std::string& text, float width, float scale)
{
    std::vector<std::string> lines;
    size_t per = (size_t)std::max(8.0f, width / (SDL_DEBUG_TEXT_FONT_CHARACTER_SIZE * scale));
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

const float kPanelX = 40, kPanelY = 96, kPanelW = 560, kPanelH = 320;

void Panel(SDL_Renderer* r, const char* title)
{
    Box(r, 0, 0, 640, 480, Color{0, 0, 0, 120});
    Box(r, kPanelX, kPanelY, kPanelW, kPanelH, Color{8, 20, 32, 220});
    Box(r, kPanelX, kPanelY, kPanelW, 2, kTeal);
    Box(r, kPanelX, kPanelY + kPanelH - 2, kPanelW, 2, kTeal);
    Text(r, 320 - Width(title, 3) / 2, kPanelY + 16, title, 3, kWhite);
}

void Footer(SDL_Renderer* r, const std::string& text)
{
    Text(r, 320 - Width(text, 1) / 2, kPanelY + kPanelH - 22, text, 1, kGrey);
}

void DrawSetup(SDL_Renderer* r)
{
    Panel(r, "NET PLAY");
    static const char* const labels[kRowCount] = {"MODE", "ADDRESS", "PORT", "NAME",
                                                  "YOUR SIDE", "START", "BACK"};
    float y = kPanelY + 64;
    bool blink = (SDL_GetTicks() / 400) % 2 == 0;
    for (int row = 0; row < kRowCount; row++) {
        if (!RowShown(row))
            continue;
        bool at = row == g_menu.row;
        if (at)
            Box(r, kPanelX + 12, y - 5, kPanelW - 24, 26, Color{40, 120, 110, 150});
        Color c = at ? kWhite : kGrey;
        if (row == kRowStart || row == kRowBack) {
            Text(r, 320 - Width(labels[row], 2) / 2, y, labels[row], 2, at ? kTeal : c);
            y += row == kRowStart ? 30 : 34;
            continue;
        }
        Text(r, kPanelX + 24, y, labels[row], 2, c);
        std::string value;
        switch (row) {
        case kRowMode:
            value = g_menu.host ? "< HOST >" : "< JOIN >";
            break;
        case kRowSide:
            value = g_menu.side == 0 ? "< P1 >" : g_menu.side == 1 ? "< P2 >" : "< RANDOM >";
            break;
        default:
            value = *RowText(row);
            if (at && blink)
                value += "_";
            break;
        }
        Text(r, kPanelX + 200, y, value, 2, at ? kWhite : Color{200, 200, 200, 255});
        y += 30;
    }
    if (!g_menu.error.empty()) {
        std::vector<std::string> lines = Wrap(g_menu.error, kPanelW - 40, 1);
        for (size_t i = 0; i < lines.size(); i++)
            Text(r, kPanelX + 20, kPanelY + kPanelH - 52 + 10 * (float)i, lines[i], 1, kRed);
    }
    Footer(r, g_menu.host ? "Up/Down  Left/Right: change  Enter: host  Esc: back"
                          : "Up/Down  type the host's address  Enter: join  Esc: back");
}

void DrawConnect(SDL_Renderer* r)
{
    Panel(r, "NET PLAY");
    float y = kPanelY + 70;
    for (const std::string& line : Wrap(g_protocol.message, kPanelW - 48, 2)) {
        Text(r, kPanelX + 24, y, line, 2, kWhite);
        y += 22;
    }
    y += 8;
    if (g_protocol.phase == Protocol::kHosting) {
        Text(r, kPanelX + 24, y, "Give the other player this computer's address", 1, kGrey);
        y += 14;
        Text(r, kPanelX + 24, y, "and the port (open it on your router to play over the", 1,
             kGrey);
        y += 12;
        Text(r, kPanelX + 24, y, "internet; UDP):", 1, kGrey);
        y += 18;
        std::string port = std::to_string(g_protocol.LocalPort());
        if (g_menu.addresses.empty())
            Text(r, kPanelX + 40, y, "(this computer's address):" + port, 2, kTeal);
        for (size_t i = 0; i < g_menu.addresses.size() && i < 4; i++) {
            Text(r, kPanelX + 40, y, g_menu.addresses[i] + ":" + port, 2, kTeal);
            y += 22;
        }
    } else if (g_protocol.phase >= Protocol::kMeasuring) {
        const char* side = g_protocol.localPlayer == 0 ? "P1" : "P2";
        Text(r, kPanelX + 24, y,
             std::string("You are ") + side + ", against " + g_protocol.names[g_protocol.remotePlayer],
             2, kTeal);
        y += 26;
        if (g_protocol.ping.last > 0 || g_protocol.ping.average > 0)
            Text(r, kPanelX + 24, y, "Ping " + std::to_string(g_protocol.ping.last) + " ms", 2,
                 kGrey);
    }
    Footer(r, "Esc: cancel");
}

void DrawDelay(SDL_Renderer* r)
{
    Panel(r, "INPUT DELAY");
    float y = kPanelY + 70;
    const char* side = g_protocol.localPlayer == 0 ? "P1" : "P2";
    Text(r, kPanelX + 24, y,
         std::string("You are ") + side + ", against " + g_protocol.names[g_protocol.remotePlayer], 2,
         kTeal);
    y += 32;
    char line[160];
    snprintf(line, sizeof(line), "Ping: %d ms (lowest %d, worst %d)", g_protocol.ping.average,
             g_protocol.ping.minimum, g_protocol.ping.maximum);
    Text(r, kPanelX + 24, y, line, 2, kWhite);
    y += 40;
    snprintf(line, sizeof(line), "Delay  < %d >", g_menu.delay);
    Text(r, 320 - Width(line, 3) / 2, y, line, 3, kWhite);
    y += 40;
    snprintf(line, sizeof(line), "frames; %d recommended. It can be changed in a fight",
             g_protocol.recommendedDelay);
    Text(r, 320 - Width(line, 1) / 2, y, line, 1, kGrey);
    y += 12;
    Text(r, 320 - Width("with the keypad's + and - (or F10 and F9).", 1) / 2, y,
         "with the keypad's + and - (or F10 and F9).", 1, kGrey);
    Footer(r, "Left/Right: change  Enter: start  Esc: cancel");
}

void DrawEnded(SDL_Renderer* r)
{
    Panel(r, "NET PLAY");
    float y = kPanelY + 80;
    for (const std::string& line : Wrap(g_menu.ended, kPanelW - 48, 2)) {
        Text(r, kPanelX + 24, y, line, 2, kWhite);
        y += 24;
    }
    if (!g_menu.replayShown.empty()) {
        y += 10;
        for (const std::string& line : Wrap("Last replay: " + g_menu.replayShown, kPanelW - 48, 1)) {
            Text(r, kPanelX + 24, y, line, 1, kGrey);
            y += 12;
        }
    }
    Footer(r, "Enter: back");
}

// The match: names and wins at the top, as Revival shows them, ping and delay at the
// bottom, and what is wrong when something is.
void DrawMatch(SDL_Renderer* r)
{
    if (g_session.ShowInfo()) {
        for (int p = 0; p < 2; p++) {
            std::string name = g_protocol.names[p];
            std::string text = p == 0 ? "Wins: " + std::to_string(g_session.Wins(0)) + "  " + name
                                      : name + "  Wins: " + std::to_string(g_session.Wins(1));
            float x = p == 0 ? 10 : 630 - Width(text, 1);
            Text(r, x, 3, text, 1, p == g_protocol.localPlayer ? kTeal : kWhite);
        }
        char line[96];
        snprintf(line, sizeof(line), "Delay %d  Ping %d ms", g_session.InputDelay(),
                 g_protocol.sessionPing.last);
        Text(r, 630 - Width(line, 1), 468, line, 1, kWhite);
    }
    if (g_protocol.desyncFrame >= 0) {
        std::string text = "Out of sync since frame " + std::to_string(g_protocol.desyncFrame);
        Text(r, 320 - Width(text, 1) / 2, 16, text, 1, kRed);
    }
    if (g_menu.replayNote > 0) {
        std::string text = "Replay saved: " + g_menu.replayShown;
        if (text.size() > 76)
            text = "..." + text.substr(text.size() - 73);
        Text(r, 320 - Width(text, 1) / 2, 452, text, 1, kYellow);
    }
    if (g_session.stalled >= 16) {
        std::string text = "Waiting for " + g_protocol.names[g_protocol.remotePlayer] + "...";
        Box(r, 0, 220, 640, 40, Color{0, 0, 0, 160});
        Text(r, 320 - Width(text, 2) / 2, 228, text, 2, kWhite);
        if (g_session.stalled > 3 * 64)
            Text(r, 320 - Width("Esc: leave the match", 1) / 2, 248, "Esc: leave the match", 1,
                 kGrey);
    }
}

} // namespace

// --- netplay.h

void InitNetplay(const NetplayOptions& options)
{
    LoadSettings();
    g_netplay.drawTitleItem = [](CGraphics* graphics, IDirectDrawSurface* menu, BYTE key,
                                 bool selected, int x, int y) {
        bool drawn = netplay::DrawTitleItem(graphics, menu, key, selected, x, y);
        g_menu.titleText = !drawn;
        g_menu.titleSelected = selected;
        g_menu.titleX = x;
        g_menu.titleY = y;
    };
    g_netplay.openMenu = [] { OpenMenu(); };
    g_netplay.fightKeys = [](char* keys) { g_session.FightKeys(keys); };
    g_netplay.matchLeft = [] { g_session.MatchLeft(); };
    g_netplay.replayOpen = [] { g_session.ReplayOpen(); };
    g_netplay.replayWrite = [](short value) { g_session.ReplayWrite(value); };
    g_netplay.replayClose = [] { g_session.ReplayClose(); };
    if (const char* lag = getenv("EFZ_NET_LAG")) {
        // "MS" or "MS:JITTER": every datagram this side sends waits that long (tests).
        g_menu.lagMs = atoi(lag);
        if (const char* colon = strchr(lag, ':'))
            g_menu.jitterMs = atoi(colon + 1);
        LogInfo("net", "EFZ_NET_LAG: datagrams wait %d ms, plus up to %d", g_menu.lagMs,
                g_menu.jitterMs);
    }
    if (options.host || options.join) {
        g_menu.automatic = true;
        g_menu.autoDelay = options.delay;
        g_menu.host = options.host;
        if (options.join)
            g_menu.address = options.join;
        if (options.port > 0)
            g_menu.port = std::to_string(options.port);
        if (options.name)
            g_menu.name = options.name;
        g_menu.side = 0;
        Begin();
    }
}

bool NetplayRunning()
{
    return g_menu.screen != kOff;
}

void NetplayFrame()
{
    switch (g_menu.screen) {
    case kSetup:
    case kEnded:
        PadActions();
        if (g_menu.screen != kOff)
            DrawTitle();
        break;
    case kConnect:
    case kDelay:
        g_protocol.Poll();
        if (g_protocol.phase == Protocol::kChoosing && g_menu.screen != kDelay) {
            g_menu.delay = g_protocol.recommendedDelay;
            g_menu.screen = kDelay;
            if (g_menu.automatic) {
                g_protocol.ChooseDelay(g_menu.autoDelay >= 0 ? g_menu.autoDelay
                                                             : g_protocol.recommendedDelay);
                g_menu.screen = kConnect;
            }
        }
        if (g_protocol.phase == Protocol::kPlaying) {
            StartMatch();
            MatchFrame();
            break;
        }
        if (g_protocol.phase == Protocol::kEnded) {
            EndMatch(g_protocol.message);
            DrawTitle();
            break;
        }
        PadActions();
        if (g_menu.screen != kOff)
            DrawTitle();
        break;
    case kMatch:
        MatchFrame();
        break;
    default:
        break;
    }
}

void ShutdownNetplay()
{
    if (g_protocol.phase != Protocol::kIdle && g_protocol.phase != Protocol::kEnded)
        g_protocol.Quit("The game was closed");
    if (g_session.Running()) {
        g_session.Stop();
        SetHooks(false);
    }
    g_protocol.Close();
}

bool NetplayEvent(const SDL_Event& e)
{
    Screen s = g_menu.screen;
    if (s == kOff || s == kMatch)
        return false;
    if (e.type == SDL_EVENT_TEXT_INPUT) {
        if (s != kSetup)
            return true;
        std::string* text = RowText(g_menu.row);
        if (!text)
            return true;
        for (const char* c = e.text.text; *c; c++) {
            char ch = *c;
            bool ok = g_menu.row == kRowPort    ? (ch >= '0' && ch <= '9')
                      : g_menu.row == kRowAddress ? (isalnum((unsigned char)ch) || strchr(".:-[]", ch))
                                                  : (ch >= 0x20 && ch < 0x7f);
            size_t limit = g_menu.row == kRowPort ? 5 : g_menu.row == kRowName ? 20 : 64;
            if (ok && text->size() < limit)
                text->push_back(ch);
        }
        return true;
    }
    if (e.type != SDL_EVENT_KEY_DOWN)
        return false;
    SDL_Scancode k = e.key.scancode;
    if (k == SDL_SCANCODE_F11 || (k == SDL_SCANCODE_RETURN && (e.key.mod & SDL_KMOD_ALT)))
        return false; // full screen, as ever
    switch (k) {
    case SDL_SCANCODE_UP: Act(kUp); break;
    case SDL_SCANCODE_DOWN: Act(kDown); break;
    case SDL_SCANCODE_LEFT: Act(kLeft); break;
    case SDL_SCANCODE_RIGHT: Act(kRight); break;
    case SDL_SCANCODE_RETURN:
    case SDL_SCANCODE_KP_ENTER: Act(kOk); break;
    case SDL_SCANCODE_ESCAPE: Act(kBack); break;
    case SDL_SCANCODE_BACKSPACE: Act(kErase); break;
    case SDL_SCANCODE_V:
        // Ctrl+V: an address copied from a chat.
        if ((e.key.mod & SDL_KMOD_CTRL) && s == kSetup && RowText(g_menu.row)) {
            if (char* clip = SDL_GetClipboardText()) {
                for (char* c = clip; *c && RowText(g_menu.row)->size() < 64; c++)
                    if ((unsigned char)*c > 0x20 && (unsigned char)*c < 0x7f)
                        RowText(g_menu.row)->push_back(*c);
                SDL_free(clip);
            }
        }
        break;
    default: break;
    }
    return true;
}

void NetplayInput(int player, unsigned char* input)
{
    if (g_session.Running())
        g_session.Input(player, input);
}

bool NetplaySound(unsigned short id, int loop)
{
    return g_session.Running() && g_session.Sound(id, loop);
}

void DrawNetplay(SDL_Renderer* r)
{
    SDL_SetRenderDrawBlendMode(r, SDL_BLENDMODE_BLEND);
    if (g_menu.titleText) {
        // The title's NET PLAY row, written where its letters would be (the title's
        // 320x240, doubled).
        g_menu.titleText = false;
        float x = 2.0f * g_menu.titleX, y = 2.0f * g_menu.titleY;
        if (g_menu.titleSelected)
            Box(r, x, y, 240, 28, Color{40, 120, 110, 200});
        Text(r, x + 42, y + 6, "NET PLAY", 2, g_menu.titleSelected ? kWhite : Color{190, 190, 190, 255});
    }
    switch (g_menu.screen) {
    case kSetup: DrawSetup(r); break;
    case kConnect: DrawConnect(r); break;
    case kDelay: DrawDelay(r); break;
    case kEnded: DrawEnded(r); break;
    case kMatch: DrawMatch(r); break;
    default: break;
    }
}

} // namespace efz
