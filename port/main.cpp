// The native game's entry point, in place of src/main.cpp's WinMain: it sets up what
// WinMain did, in the same order, and runs the scenes 64 times a second.
//
//   efz [--data DIR] [--save DIR] [--fullscreen]
//
// --data is the game's folder (with its system folder); without it, $EFZ_DATA, the
// current folder, the executable's folder or, for a macOS app, the folder holding the
// app, whichever has the game. --save is where key.ini, the records, replays and
// screenshots go; without it, the game's folder if it can be written, else the user's
// preferences folder. Alt+Enter or F11 switches between a window and full screen.
//
// For tests, which run it without a display (SDL_VIDEO_DRIVER=offscreen):
//   --frames N        quit after N frames
//   --fast            don't wait between frames
//   --keys SCRIPT     press and release keys at given frames: "F:+NAME,F:-NAME,...",
//                     NAME an SDL scancode name (Return, Z, Up...)
//   --dump DIR        write the frame shown every --dump-every frames (default 60)
//                     to DIR/NNNNNN.bmp
#include <SDL3/SDL.h>
#include <string>
#include <vector>

#include "efz.h"
#include "platform.h"

namespace {

SDL_Window* g_window;
bool g_quit;

// What WinMain kept in globals. The scenes keep pointers to the two player pointers,
// so those live in the arena like everything else the game points at.
PTR32(CPlayer)* g_players;
CGame* g_game;
CScene* g_scenes[9];
BYTE g_scene;
CGraphics* g_graphics;
CInput* g_inputDev;
CSound* g_sound;

// The game window's HWND, as the game passes it around: any nonzero value.
const HWND kWindow = 1;

bool HasGameData(const std::string& dir)
{
    std::string probe = dir + "/system";
    SDL_PathInfo info;
    return SDL_GetPathInfo(probe.c_str(), &info) && info.type == SDL_PATHTYPE_DIRECTORY;
}

bool Writable(const std::string& dir)
{
    std::string probe = dir + "/.efz-write-test";
    FILE* f = fopen(probe.c_str(), "wb");
    if (!f)
        return false;
    fclose(f);
    remove(probe.c_str());
    return true;
}

void ToggleFullscreen()
{
    bool full = (SDL_GetWindowFlags(g_window) & SDL_WINDOW_FULLSCREEN) != 0;
    SDL_SetWindowFullscreen(g_window, !full);
}

} // namespace

namespace efz {

SDL_Window* Window()
{
    return g_window;
}

void RequestQuit()
{
    g_quit = true;
}

bool QuitRequested()
{
    return g_quit;
}

void PumpEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_EVENT_QUIT:
            g_quit = true;
            break;
        case SDL_EVENT_KEY_DOWN:
            if ((e.key.scancode == SDL_SCANCODE_RETURN && (e.key.mod & SDL_KMOD_ALT)) ||
                e.key.scancode == SDL_SCANCODE_F11) {
                if (!e.key.repeat)
                    ToggleFullscreen();
                break;
            }
            KeyEvent(e.key.scancode, true);
            break;
        case SDL_EVENT_KEY_UP:
            KeyEvent(e.key.scancode, false);
            break;
        case SDL_EVENT_WINDOW_FOCUS_LOST:
            ResetInput();
            break;
        case SDL_EVENT_GAMEPAD_ADDED:
        case SDL_EVENT_GAMEPAD_REMOVED:
            UpdateJoysticks();
            break;
        }
    }
}

} // namespace efz

// --keys: the key events scripted for a frame.
struct ScriptedKey {
    long frame;
    SDL_Scancode key;
    bool down;
};

static bool ParseKeys(const std::string& script, std::vector<ScriptedKey>& out)
{
    size_t pos = 0;
    while (pos < script.size()) {
        size_t end = script.find(',', pos);
        std::string item = script.substr(pos, end == std::string::npos ? std::string::npos : end - pos);
        pos = end == std::string::npos ? script.size() : end + 1;
        size_t colon = item.find(':');
        if (colon == std::string::npos || colon + 2 > item.size())
            return false;
        ScriptedKey k;
        k.frame = atol(item.substr(0, colon).c_str());
        k.down = item[colon + 1] == '+';
        k.key = SDL_GetScancodeFromName(item.substr(colon + 2).c_str());
        if (k.key == SDL_SCANCODE_UNKNOWN)
            return false;
        out.push_back(k);
    }
    return true;
}

// Called by sdlmain.cpp's main, which SDL turns into what the platform starts.
int EfzMain(int argc, char** argv)
{
    int stackMark;
    efz::SetStack(&stackMark);
    std::string data, save, dump;
    bool fullscreen = false, fast = false;
    long frames = -1, dumpEvery = 60;
    std::vector<ScriptedKey> keys;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        bool more = i + 1 < argc;
        if (a == "--data" && more)
            data = argv[++i];
        else if (a == "--save" && more)
            save = argv[++i];
        else if (a == "--fullscreen")
            fullscreen = true;
        else if (a == "--frames" && more)
            frames = atol(argv[++i]);
        else if (a == "--fast")
            fast = true;
        else if (a == "--dump" && more)
            dump = argv[++i];
        else if (a == "--dump-every" && more)
            dumpEvery = atol(argv[++i]);
        else if (a == "--keys" && more && ParseKeys(argv[i + 1], keys))
            i++;
        else {
            fprintf(stderr, "usage: %s [--data DIR] [--save DIR] [--fullscreen] [--frames N] "
                            "[--fast] [--keys SCRIPT] [--dump DIR] [--dump-every N]\n", argv[0]);
            return 2;
        }
    }
    if (data.empty()) {
        std::vector<std::string> places;
        if (const char* env = getenv("EFZ_DATA"))
            places.push_back(env);
        places.push_back(".");
        if (const char* base = SDL_GetBasePath()) {
            places.push_back(base);
            places.push_back(std::string(base) + "../../.."); // the .app's folder
        }
        for (const std::string& p : places) {
            if (HasGameData(p)) {
                data = p;
                break;
            }
        }
    }
    if (data.empty() || !HasGameData(data)) {
        fprintf(stderr, "efz: no game data (EFZ's folder, with its system folder) found; "
                        "pass --data DIR\n");
        return 1;
    }
    if (save.empty()) {
        save = data;
        if (!Writable(save)) {
            if (char* pref = SDL_GetPrefPath("efz-decomp", "efz")) {
                save = pref;
                SDL_free(pref);
            }
        }
    }
    efz::SetDataDir(data.c_str(), save.c_str());

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD)) {
        fprintf(stderr, "efz: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    g_window = SDL_CreateWindow("ETENAL FIGHTER ZERO", 640, 480,
                                SDL_WINDOW_RESIZABLE | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
    if (!g_window) {
        fprintf(stderr, "efz: %s\n", SDL_GetError());
        return 1;
    }
    SDL_HideCursor();

    srand(time(NULL));
    g_graphics = new CGraphics;
    g_inputDev = new CInput;
    g_sound = new CSound;
    g_graphics->Init(kWindow, ReadConfigByte(0x20));
    g_inputDev->Init(kWindow);
    g_sound->Init(kWindow);
    if (ReadConfigByte(0x9c) > 0)
        g_inputDev->LoadPreset(ReadConfigByte(0x9c));
    else
        g_inputDev->LoadBindings();

    g_game = new CGame(g_graphics, g_inputDev, g_sound);
    g_game->LoadSounds();
    g_game->LoadEffectAnims();
    g_game->LoadEffects();

    g_players = new PTR32(CPlayer)[2];
    PTR32(CPlayer)* p1 = &g_players[0];
    PTR32(CPlayer)* p2 = &g_players[1];
    g_scenes[0] = new CScene0(kWindow, p1, p2, g_game, g_graphics, g_inputDev, g_sound);
    g_scenes[1] = new CScene1(kWindow, p1, p2, g_game, g_graphics, g_inputDev, g_sound);
    g_scenes[2] = new CScene2(kWindow, p1, p2, g_game, g_graphics, g_inputDev, g_sound);
    g_scenes[3] = new CScene3(kWindow, p1, p2, g_game, g_graphics, g_inputDev, g_sound);
    g_scenes[4] = NULL;
    g_scenes[5] = new CScene5(kWindow, p1, p2, g_game, g_graphics, g_inputDev, g_sound);
    g_scenes[6] = new CScene6(kWindow, p1, p2, g_game, g_graphics, g_inputDev, g_sound);
    g_scenes[7] = new CScene7(kWindow, p1, p2, g_game, g_graphics, g_inputDev, g_sound);
    g_scenes[8] = new CScene8(kWindow, p1, p2, g_game, g_graphics, g_inputDev, g_sound);
    TraceStart(g_game, g_scenes, &g_scene);
    fast |= TraceFast() != 0;

    // 64 frames a second, which the original's timer thread approached by adjusting its
    // sleep; here each frame starts 1/64 s after the last.
    const Uint64 frame = SDL_NS_PER_SECOND / 64;
    Uint64 next = SDL_GetTicksNS();
    for (long n = 0; !g_quit && n != frames; n++) {
        for (const ScriptedKey& k : keys) {
            if (k.frame == n)
                efz::KeyEvent(k.key, k.down);
        }
        efz::PumpEvents();
        if (g_quit || TraceQuit(g_scene))
            break;
        g_game->m_oddFrame = !g_game->m_oddFrame;
        if (g_scenes[g_scene] != NULL) {
            g_sound->UpdateLoop(g_game->m_music);
            g_scene = g_scenes[g_scene]->Update();
        }
        if (!dump.empty() && n % dumpEvery == 0) {
            char path[64];
            snprintf(path, sizeof(path), "/%06ld.bmp", n);
            efz::SaveFrame((dump + path).c_str());
        }
        next += frame;
        if (fast)
            continue;
        Uint64 now = SDL_GetTicksNS();
        if (now < next)
            SDL_DelayPrecise(next - now);
        else if (now - next > frame * 4)
            next = now; // fell far behind (loading): don't race to catch up
    }

    // What WM_DESTROY did.
    for (int i = 0; i < 9; i++) {
        delete g_scenes[i];
        g_scenes[i] = NULL;
    }
    delete g_game;
    if (g_players[0])
        delete (CPlayer*)g_players[0];
    if (g_players[1])
        delete (CPlayer*)g_players[1];
    g_sound->Shutdown();
    g_inputDev->Shutdown();
    g_graphics->Shutdown();
    SDL_DestroyWindow(g_window);
    SDL_Quit();
    return 0;
}
