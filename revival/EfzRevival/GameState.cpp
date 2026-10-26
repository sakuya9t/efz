// Save states (GameState.h).
#include "GameState.h"
#include <stdlib.h>
#include <sstream>
#include "EfzRevival.h"

// FUNCTION: 0x1006f260
void SaveState::clear()
{
    buffer_->reset();
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

// FUNCTION: 0x1006f340
void SaveState::addPlayer(CPlayer *player)
{
    int size = g_characterSizes[player->character];
    buffer_->add(player, size);
}

// FUNCTION: 0x1006f370
void SaveState::addInt(int *value, int size)
{
    buffer_->add(value, size);
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

// FUNCTION: 0x1006f580
SaveState::~SaveState()
{
}

// FUNCTION: 0x1006f5a0 ??0SaveState@@QAE@XZ
SaveState::SaveState()
{
    random_ = "";
    buffer_ = new StateBuffer(500000);
}

// FUNCTION: 0x1006f640
StateBuffer::StateBuffer(int capacity)
{
    capacity_ = capacity;
    buffer_ = (char *)malloc(capacity);
    cursor_ = buffer_;
    maxUsed_ = 0;
    memset(fpu_, 0, sizeof(fpu_));
}

// FUNCTION: 0x1006f690
void StateBuffer::reset()
{
    unsigned int used = cursor_ - buffer_;
    maxUsed_ = maxUsed_ > used ? maxUsed_ : used;
    cursor_ = buffer_;
    regions_.clear();
}

// FUNCTION: 0x1006f6d0
__declspec(naked) void StateBuffer::saveFpu()
{
    __asm {
        fsave [ecx]
        frstor [ecx]
        ret
    }
}

// FUNCTION: 0x1006f6e0
void StateBuffer::add(void *address, int size)
{
    if (address != 0 && size != 0) {
        Region region;
        region.copy = cursor_;
        region.address = address;
        region.size = size;
        memcpy(cursor_, address, size);
        cursor_ += size;
        regions_.push_back(region);
    }
}

// FUNCTION: 0x1006f730
void StateBuffer::restore()
{
    for (std::list<Region>::iterator it = regions_.begin(); it != regions_.end(); ++it)
        memcpy(it->address, it->copy, it->size);
}
