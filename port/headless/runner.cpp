// efz-headless: the game on the headless platform (platform.cpp), run as port/main.cpp
// runs it on SDL3 but without a window, sound or waiting between frames. It takes the
// compatibility test's EFZ_TRACE variables (src/trace.cpp), so that the test can check
// the headless platform plays the original's game:
//
//   tools/compat.py check --native build/headless/efz-headless
//
//   efz-headless [--data DIR] [--save DIR] [--frames N] [--draw] [--dump DIR]
//                [--dump-every N]
//
// --data and --save as the game's (port/main.cpp). --draw draws the frames, which the
// game doesn't need; --dump writes every --dump-every'th (default 60) to DIR/NNNNNN.bmp
// (and implies --draw).
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "efz.h"
#include "headless.h"
#include "platform.h"

namespace {

bool WriteBmp(const char* path, const uint8_t* rgb, int width, int height)
{
    FILE* f = fopen(path, "wb");
    if (!f)
        return false;
    int row = (width * 3 + 3) & ~3;
    uint32_t size = 54 + row * height;
    uint8_t h[54] = {'B', 'M'};
    auto put32 = [&](int at, uint32_t v) {
        for (int i = 0; i < 4; i++)
            h[at + i] = (uint8_t)(v >> (8 * i));
    };
    put32(2, size);
    put32(10, 54);
    put32(14, 40);
    put32(18, width);
    put32(22, height);
    h[26] = 1;
    h[28] = 24;
    fwrite(h, 1, sizeof(h), f);
    uint8_t pad[3] = {0, 0, 0};
    for (int y = height - 1; y >= 0; y--) {
        const uint8_t* p = rgb + y * width * 3;
        for (int x = 0; x < width; x++) {
            uint8_t bgr[3] = {p[x * 3 + 2], p[x * 3 + 1], p[x * 3]};
            fwrite(bgr, 1, 3, f);
        }
        fwrite(pad, 1, row - width * 3, f);
    }
    fclose(f);
    return true;
}

bool HasGameData(const std::string& dir)
{
    std::string probe = dir + "/system/effect/effect.dat";
    FILE* f = fopen(probe.c_str(), "rb");
    if (f)
        fclose(f);
    return f != nullptr;
}

} // namespace

int main(int argc, char** argv)
{
    int stackMark;
    std::string data, save, dump;
    long frames = -1, dumpEvery = 60;
    bool draw = false;
    for (int i = 1; i < argc; i++) {
        std::string a = argv[i];
        bool more = i + 1 < argc;
        if (a == "--data" && more)
            data = argv[++i];
        else if (a == "--save" && more)
            save = argv[++i];
        else if (a == "--frames" && more)
            frames = atol(argv[++i]);
        else if (a == "--draw")
            draw = true;
        else if (a == "--dump" && more)
            dump = argv[++i], draw = true;
        else if (a == "--dump-every" && more)
            dumpEvery = atol(argv[++i]);
        else if (a == "--fast" || a == "--fullscreen")
            ; // as the game's, which the tests pass: always fast, never a window
        else {
            fprintf(stderr, "usage: %s [--data DIR] [--save DIR] [--frames N] [--draw] "
                            "[--dump DIR] [--dump-every N]\n", argv[0]);
            return 2;
        }
    }
    if (data.empty()) {
        const char* env = getenv("EFZ_DATA");
        data = env ? env : ".";
    }
    if (!HasGameData(data)) {
        fprintf(stderr, "efz-headless: no game data in %s; pass --data DIR, the folder of an "
                        "EFZ 4.02 install\n", data.c_str());
        return 1;
    }
    if (save.empty())
        save = data;
    efz::SetDataDir(data.c_str(), save.c_str());

    // One game, in an arena of its own, as the library runs each.
    efz::BindArena(efz::NewArena());
    efz::SetStack(&stackMark);
    srand(time(NULL));
    efz::headless::CreateGame(draw, ReadConfigByte(0x20));

    CScene* scenes[9];
    for (int i = 0; i < 9; i++)
        scenes[i] = efz::headless::Scene(i);
    BYTE scene = 0;
    TraceStart(efz::headless::Game(), scenes, &scene);
    efz::headless::SceneIndex() = scene;

    static uint8_t rgb[640 * 480 * 3];
    for (long n = 0; n != frames; n++) {
        if (efz::QuitRequested() || TraceQuit((BYTE)efz::headless::SceneIndex()))
            break;
        efz::headless::RunFrame();
        int w, h;
        if (!dump.empty() && n % dumpEvery == 0 && efz::headless::FrameRGB(rgb, &w, &h)) {
            char path[64];
            snprintf(path, sizeof(path), "/%06ld.bmp", n);
            WriteBmp((dump + path).c_str(), rgb, w, h);
        }
    }
    fflush(NULL);
    return 0;
}
