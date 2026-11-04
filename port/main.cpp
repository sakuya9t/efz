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
// The log and the fight records (docs/logging.md), in a folder per run under the logs
// folder:
//   --log-dir DIR     the logs folder (default $EFZ_LOG_DIR, else the save folder's
//                     logs); "none": no files
//   --log-level L     what efz.log gets: debug, info (the default), warn or error
//   --log-keep N      the sessions kept, the newest (default 20); 0 keeps all
//   --log-max-mb N    and no more than N MB of them, the newest (default 2048); 0: any
//   --verbose         stderr gets every line too (else warnings and errors)
//   --record, --no-record
//                     a record of each fight: on, except under the compatibility test's
//                     harness (EFZ_TRACE)
//   --replay-fight FILE
//                     replays a recorded fight (fight-NNN.jsonl) instead of the menus,
//                     comparing each tick with the record, and quits: exit code 0 if
//                     every tick is as recorded, 3 if not, 4 if it couldn't replay
//   --seed N          rand()'s seed (default: the clock), logged either way
//   --crash-test KIND crash on purpose (segv, abort or fatal) to test the crash report
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
#include "crash.h"
#include "log.h"
#include "record.h"

namespace {

SDL_Window* g_window;
bool g_quit;
const char* g_quitWhy = "the window was closed";
// PumpEvents's calls: more than one in a frame's Update means the game waited in a loop
// of its own (a fade), so the frame was meant to be slow.
long g_pumps;

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
    if (!g_quit)
        g_quitWhy = "the game asked to quit";
    g_quit = true;
}

bool QuitRequested()
{
    return g_quit;
}

void PumpEvents()
{
    SDL_Event e;
    Heartbeat(); // the watchdog's: the game's own waits pump events too
    g_pumps++;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
        case SDL_EVENT_QUIT:
            if (!g_quit)
                g_quitWhy = "the window was closed";
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

// The Win32 functions of the game code that go to the window system.
// The game's error messages: a file it couldn't load, a device it couldn't open. Logged,
// and the watchdog left out of the wait for the player.
int MessageBoxA(HWND, LPCSTR text, LPCSTR caption, UINT)
{
    efz::LogError("game", "message box \"%s\": %s", caption ? caption : "", text ? text : "");
    efz::PauseWatchdog(true);
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, caption ? caption : "",
                             text ? text : "", efz::Window());
    efz::PauseWatchdog(false);
    return 1;
}

BOOL PostMessageA(HWND, UINT msg, WPARAM, LPARAM)
{
    if (msg == WM_CLOSE)
        efz::RequestQuit();
    return TRUE;
}

DWORD timeGetTime()
{
    return (DWORD)SDL_GetTicks();
}

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

static const char* SceneName(int scene)
{
    static const char* const names[9] = {"title", "character select", "match setup", "fight",
                                         "?", "results", "config", "staff roll", "replays"};
    return scene >= 0 && scene < 9 ? names[scene] : "?";
}

// SDL's own messages, into the log.
static void SDLCALL SdlLog(void*, int, SDL_LogPriority priority, const char* message)
{
    efz::LogLevel level = priority >= SDL_LOG_PRIORITY_ERROR  ? efz::kLogError
                          : priority == SDL_LOG_PRIORITY_WARN ? efz::kLogWarn
                          : priority == SDL_LOG_PRIORITY_INFO ? efz::kLogInfo
                                                              : efz::kLogDebug;
    efz::Log(level, "sdl", "%s", message);
}

// The command line as a JSON array, for session.json.
static std::string JsonArgs(int argc, char** argv)
{
    std::string json = "[";
    for (int i = 0; i < argc; i++) {
        char arg[1100];
        efz::JsonString(argv[i], arg, sizeof(arg));
        json += (i ? ", " : "") + std::string(arg);
    }
    return json + "]";
}

static void Usage(const char* name)
{
    fprintf(stderr,
            "usage: %s [--data DIR] [--save DIR] [--fullscreen] [--log-dir DIR] "
            "[--log-level L] [--log-keep N] [--log-max-mb N] [--verbose] "
            "[--record | --no-record] "
            "[--replay-fight FILE] [--seed N] [--crash-test KIND] [--frames N] [--fast] "
            "[--keys SCRIPT] [--dump DIR] [--dump-every N]\n",
            name);
}

// Called by sdlmain.cpp's main, which SDL turns into what the platform starts.
int EfzMain(int argc, char** argv)
{
    int stackMark;
    efz::SetStack(&stackMark);
    efz::InstallCrashHandler();
    std::string data, save, dump, logDir, replay, crashTest;
    bool fullscreen = false, fast = false, verbose = false, seeded = false;
    long frames = -1, dumpEvery = 60;
    int record = -1, keep = 20;
    long maxMb = 2048;
    unsigned seed = 0;
    efz::LogLevel fileLevel = efz::kLogInfo;
    if (const char* env = getenv("EFZ_LOG_LEVEL"))
        efz::ParseLogLevel(env, &fileLevel);
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
        else if (a == "--log-dir" && more)
            logDir = argv[++i];
        else if (a == "--log-level" && more && efz::ParseLogLevel(argv[i + 1], &fileLevel))
            i++;
        else if (a == "--log-max-mb" && more)
            maxMb = atol(argv[++i]);
        else if (a == "--log-keep" && more)
            keep = atoi(argv[++i]);
        else if (a == "--verbose")
            verbose = true;
        else if (a == "--record")
            record = 1;
        else if (a == "--no-record")
            record = 0;
        else if (a == "--replay-fight" && more)
            replay = argv[++i];
        else if (a == "--seed" && more) {
            seed = (unsigned)strtoul(argv[++i], nullptr, 0);
            seeded = true;
        } else if (a == "--crash-test" && more)
            crashTest = argv[++i];
        else {
            Usage(argv[0]);
            return 2;
        }
    }
    if (logDir.empty() && getenv("EFZ_LOG_DIR"))
        logDir = getenv("EFZ_LOG_DIR");
    efz::LogOptions logOptions;
    logOptions.fileLevel = fileLevel;
    logOptions.stderrLevel = verbose ? efz::kLogDebug : efz::kLogWarn;
    logOptions.keep = keep;
    logOptions.maxBytes = maxMb > 0 ? (unsigned long long)maxMb << 20 : 0;
    if (!crashTest.empty()) {
        // Needs no game: the log, and the crash.
        logOptions.dir = logDir.empty() ? "." : logDir.c_str();
        efz::StartLog(logOptions);
        efz::SetCrashDialog(false);
        efz::CrashTest(crashTest.c_str());
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

    // The log, in the save folder's logs unless told otherwise.
    if (logDir.empty())
        logDir = save + "/logs";
    logOptions.dir = logDir == "none" ? nullptr : logDir.c_str();
    efz::StartLog(logOptions);
    SDL_SetLogOutputFunction(SdlLog, nullptr);
    efz::SetSessionValue("args", JsonArgs(argc, argv).c_str());
    efz::SetSessionString("data", data.c_str());
    efz::SetSessionString("save", save.c_str());
    efz::LogInfo("main", "game data %s, saves %s", data.c_str(), save.c_str());
    // A replay leaves the player's files alone: its game saves to a scratch folder.
    std::string gameSave = save;
    if (!replay.empty()) {
        char scratch[1100];
        if (!efz::SessionPath("scratch", scratch, sizeof(scratch))) {
            efz::LogError("main", "--replay-fight needs a log folder (not --log-dir none)");
            efz::EndLog(4);
            return 4;
        }
        SDL_CreateDirectory(scratch);
        gameSave = scratch;
    }
    efz::SetDataDir(data.c_str(), gameSave.c_str());

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMEPAD)) {
        efz::LogError("main", "SDL: %s", SDL_GetError());
        efz::EndLog(1);
        return 1;
    }
    int sdl = SDL_GetVersion();
    char sdlVersion[64];
    snprintf(sdlVersion, sizeof(sdlVersion), "%d.%d.%d", SDL_VERSIONNUM_MAJOR(sdl),
             SDL_VERSIONNUM_MINOR(sdl), SDL_VERSIONNUM_MICRO(sdl));
    const char* video = SDL_GetCurrentVideoDriver();
    const char* audio = SDL_GetCurrentAudioDriver();
    efz::LogInfo("main", "SDL %s (%s), video %s, audio %s, %s", sdlVersion, SDL_GetRevision(),
                 video ? video : "none", audio ? audio : "none", SDL_GetPlatform());
    efz::SetSessionString("sdl", sdlVersion);
    efz::SetSessionString("video", video ? video : "none");
    efz::SetSessionString("audio", audio ? audio : "none");
    SDL_SetHint(SDL_HINT_RENDER_VSYNC, "0");
    g_window = SDL_CreateWindow("ETENAL FIGHTER ZERO", 640, 480,
                                SDL_WINDOW_RESIZABLE | (fullscreen ? SDL_WINDOW_FULLSCREEN : 0));
    if (!g_window) {
        efz::LogError("main", "cannot open the window: %s", SDL_GetError());
        efz::EndLog(1);
        return 1;
    }
    SDL_HideCursor();

    // rand() seeded from the clock, as the original did, unless --seed says.
    if (!seeded)
        seed = (unsigned)time(NULL);
    srand(seed);
    char seedText[16];
    snprintf(seedText, sizeof(seedText), "%u", seed);
    efz::SetSessionValue("seed", seedText);
    efz::LogInfo("main", "rand() seeded with %u%s", seed, seeded ? " (--seed)" : "");
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
    efz::LogInfo("main", "key.ini: screen mode %d, key preset %d", ReadConfigByte(0x20),
                 ReadConfigByte(0x9c));

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

    // The fight records: on, but not under the compatibility test's harness, which runs
    // hundreds of fights.
    bool harness = getenv("EFZ_TRACE") != nullptr;
    efz::RecordOptions recordOptions;
    recordOptions.record = record < 0 ? !harness : record != 0;
    recordOptions.replay = replay.empty() ? nullptr : replay.c_str();
    efz::StartRecorder(recordOptions, g_game, g_scenes);
    int code = 0;
    if (!replay.empty()) {
        if (getenv("EFZ_TRACE_PLAY") || getenv("EFZ_TRACE_RECORD")) {
            efz::LogError("main", "--replay-fight can't go with EFZ_TRACE_PLAY or "
                                  "EFZ_TRACE_RECORD");
            g_quit = true;
            code = 2;
        } else if (!efz::StartReplay(&g_scene)) {
            g_quit = true;
            code = 4;
        }
    }
    efz::StartWatchdog(15);

    // 64 frames a second, which the original's timer thread approached by adjusting its
    // sleep; here each frame starts 1/64 s after the last.
    const Uint64 frame = SDL_NS_PER_SECOND / 64;
    Uint64 next = SDL_GetTicksNS();
    // The scene's visit, for the log: frames, and the time Update took.
    long visitFrames = 0, slowFrames = 0;
    Uint64 visitTime = 0, worstFrame = 0;
    const char* why = nullptr;
    long n = 0;
    for (; !g_quit && n != frames; n++) {
        for (const ScriptedKey& k : keys) {
            if (k.frame == n)
                efz::KeyEvent(k.key, k.down);
        }
        efz::PumpEvents();
        if (g_quit)
            break;
        if (TraceQuit(g_scene)) {
            why = "the harness's fight ended";
            break;
        }
        efz::SetLogFrame(n, g_scene);
        efz::RecorderFrameStart(n, g_scene);
        g_game->m_oddFrame = !g_game->m_oddFrame;
        BYTE scene = g_scene;
        Uint64 start = SDL_GetTicksNS();
        long pumps = g_pumps;
        if (g_scenes[g_scene] != NULL) {
            g_sound->UpdateLoop(g_game->m_music);
            g_scene = g_scenes[g_scene]->Update();
        }
        Uint64 spent = SDL_GetTicksNS() - start;
        bool replayed = efz::RecorderFrameEnd(g_scene);
        visitFrames++;
        visitTime += spent;
        worstFrame = spent > worstFrame ? spent : worstFrame;
        slowFrames += spent > 2 * frame;
        if (scene == 3 && g_scene == 3 && visitFrames > 1 && g_pumps - pumps <= 1 &&
            spent > SDL_NS_PER_SECOND / 4)
            efz::LogWarn("main", "a frame of the fight took %.0f ms",
                         (double)spent / SDL_NS_PER_MS);
        if (g_scene != scene) {
            efz::LogInfo("main", "scene %d (%s) to %d (%s) after %ld frames; Update took "
                                 "%.2f ms a frame, at most %.1f ms, %ld frames over 1/32 s",
                         scene, SceneName(scene), g_scene, SceneName(g_scene), visitFrames,
                         (double)visitTime / visitFrames / SDL_NS_PER_MS,
                         (double)worstFrame / SDL_NS_PER_MS, slowFrames);
            visitFrames = slowFrames = 0;
            visitTime = worstFrame = 0;
        }
        if (!dump.empty() && n % dumpEvery == 0) {
            char path[64];
            snprintf(path, sizeof(path), "/%06ld.bmp", n);
            efz::SaveFrame((dump + path).c_str());
        }
        if (replayed) {
            why = "the replay is over";
            break;
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
    if (!why)
        why = n == frames ? "--frames" : g_quitWhy;
    efz::LogInfo("main", "quitting after %ld frames: %s", n, why);
    efz::StopWatchdog();
    efz::StopRecorder();
    if (!replay.empty() && code == 0)
        code = efz::ReplayResult();

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
    efz::EndLog(code);
    SDL_Quit();
    return code;
}
