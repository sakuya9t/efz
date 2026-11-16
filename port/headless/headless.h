// The headless platform: the game without a window, sound or keyboard, several games
// to a process, each in an arena of its own (port/guest.h, EFZ_MULTI_INSTANCE). It is
// what the training library (env.cpp, efz_env.h) and the headless runner (runner.cpp)
// are built on. See docs/headless.md.
#ifndef EFZ_HEADLESS_H
#define EFZ_HEADLESS_H

#include "efz.h"

namespace efz {
namespace headless {

// What WinMain kept in globals, as handles in the game's Globals (guest.h), so that
// they are part of the arena: every game made the same way has the same ones.
enum Root {
    kRootGraphics,
    kRootInput,
    kRootSound,
    kRootGame,
    kRootPlayers, // the two player pointers, PTR32(CPlayer)[2]
    kRootScene,   // the scene running (CScene index), not a handle
    kRootPalette, // the palette of the last frame drawn (Present)
    kRootScenes,  // CScene* [9], from here
    kRootCount = kRootScenes + 9
};
static_assert(kRootCount <= 16, "Globals::root");

inline CGraphics* Graphics() { return (CGraphics*)Ptr(G()->root[kRootGraphics]); }
inline CInput* Input() { return (CInput*)Ptr(G()->root[kRootInput]); }
inline CSound* Sound() { return (CSound*)Ptr(G()->root[kRootSound]); }
inline CGame* Game() { return (CGame*)Ptr(G()->root[kRootGame]); }
inline PTR32(CPlayer)* Players() { return (PTR32(CPlayer)*)Ptr(G()->root[kRootPlayers]); }
inline CScene* Scene(int i) { return (CScene*)Ptr(G()->root[kRootScenes + i]); }
inline uint32_t& SceneIndex() { return G()->root[kRootScene]; }

// Sets up a game in the bound arena as WinMain did, in the same order: the platform's
// objects, CGame and its sounds and effects, the player slots and the scenes. `mode` is
// the screen mode (0: 320x240, 1: 640x480). The bound arena must be new.
void CreateGame(bool drawing, BYTE mode);

// Runs one frame, as WinMain's loop did: the scene running updates, and the next one
// is what it returns.
void RunFrame();

// The last frame drawn, as 8-bit RGB triples, `width` x `height` (320x240, or 640x480 in
// mode 1); `out` must hold 640 * 480 * 3 bytes. False when the game doesn't draw.
bool FrameRGB(uint8_t* out, int* width, int* height);

// The game's messages (MessageBox) go to stderr; set false to keep them quiet.
void SetMessages(bool show);

// The sounds a game asked for, for a program that plays them itself (efz_env_sound_events):
// nothing plays here, but while the log is on (for every game of the process, off by
// default) each Play, Stop and SetVolume of a game is kept, with the file it is of.
enum SoundKind { kSoundPlay, kSoundStop, kSoundVolume };
struct SoundEvent {
    int32_t kind;   // SoundKind
    int32_t slot;   // the sound slot (CSound's ID)
    int32_t value;  // play: 1 when it loops; volume: hundredths of a decibel
    char file[48];  // the .wav, relative to the game's folder, or "" if not known
};
void SetSoundLog(bool on);
// Moves up to `max` events of the bound arena's game, oldest first, into `out`; returns
// how many. A game keeps its last 256 until they are taken.
int TakeSoundEvents(SoundEvent* out, int max);

} // namespace headless
} // namespace efz

#endif
