// Save states (GameState.h).
#include "stdafx.h"
#include "GameState.h"
#include "GameStateBuffer.h"
#include "Log.h"
#include <stdlib.h>
#include <sstream>
#include "EfzRevival.h"

// FUNCTION: 0x1006f5a0 ??0SaveState@@QAE@XZ
SaveState::SaveState()
{
    random_ = "";
    buffer_ = new StateBuffer(500000);
}

// FUNCTION: 0x1006f580
SaveState::~SaveState()
{
}

// The scene, CGame and both players, the screen palette and back buffer, the
// stage's animation, g_rng and Game's kept boxes.
// FUNCTION: 0x1006f390
void SaveState::save(bool full)
{
    buffer_->reset();
    buffer_->saveFpu();
    buffer_->add(EFZ_FKEY_HELD, 4);
    CScene3 *fight = (CScene3 *)g_game.currentScene();
    if (full) {
        buffer_->add(fight, 0x598);
    } else {
        buffer_->add(fight, 0x434);
        char *rest = (char *)fight + 0x440;
        buffer_->add(rest, 0x158);
    }
    CGame *game = g_game.getGame();
    buffer_->add(game, 0x142f0);
    addPlayer(*fight->players[0]);
    addPlayer(*fight->players[1]);
    std::stringstream stream;
    stream << g_rng;
    random_ = stream.str();
    ProxyPalette *palette = EFZ_DDPALETTE;
    PALETTEENTRY *colors = 0;
    palette->getColors(&colors);
    buffer_->add(colors, 0x400);
    DDSURFACEDESC desc;
    memset(&desc, 0, sizeof(desc));
    IDirectDrawSurface *back = EFZ_BACK_BUFFER;
    back->Lock(0, &desc, 0, 0);
    buffer_->add(desc.lpSurface, desc.lPitch * desc.dwHeight);
    back->Unlock(0);
    rects_.clear();
    rects_.insert(rects_.begin(), g_game.rects_.begin(), g_game.rects_.end());
    char *background = (char *)game->background;
    if (background) {
        void *frames = *(void **)(background + 0x10);
        if (background[4] == 16)
            buffer_->add(frames, 0x1c0);
        else
            buffer_->add(frames, 0xe0);
    }
}

// FUNCTION: 0x1006f370
void SaveState::addInt(int *value, int size)
{
    buffer_->add(value, size);
}

// FUNCTION: 0x1006f340
void SaveState::addPlayer(CPlayer *player)
{
    int size = g_characterSizes[player->character];
    buffer_->add(player, size);
}

// FUNCTION: 0x1006f270
void SaveState::load()
{
    if (random_.size() != 0) {
        std::stringstream stream;
        stream << random_;
        stream >> g_rng;
    }
    buffer_->restore();
    g_game.rects_.clear();
    g_game.rects_.insert(g_game.rects_.begin(), rects_.begin(), rects_.end());
}

// FUNCTION: 0x1006f260
void SaveState::clear()
{
    buffer_->reset();
}

// Unused (only its strings are left, the object's only ones): the bytes in which two
// states' buffers differ, for finding desyncs.
static void compareStates(const char *name, const char *old, const char *other, const char *now,
                          int size)
{
    g_log << "Comparing " << name << " with " << other << "\n";
    for (int i = 0; i < size; i++)
        if (old[i] != now[i])
            g_log << "0x" << std::hex << i << " Old " << (int)old[i] << " New " << (int)now[i]
                  << std::dec << "\n";
    g_log.flush();
}
