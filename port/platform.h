// What the native platform layer's parts share: the window, the frame loop's controls
// and the game's folders.
//
// graphics.cpp, win32.cpp, arena.cpp, x87.cpp and layout.cpp are the same in every
// build. The rest is a platform's own: SDL3's (main.cpp, video.cpp, input.cpp,
// sound.cpp) for the game, or the headless library's (port/headless/), which runs
// games without a window or sound, for programs that play it.
#ifndef EFZ_PLATFORM_H
#define EFZ_PLATFORM_H

#include <stdint.h>
#include <stdio.h>

struct SDL_Window;
struct IDirectDrawSurface;
struct tagPALETTEENTRY;
class CGame;
class CScene;
class CGraphics;
class CInput;
class CSound;

namespace efz {

// --- The platform's own.

// Asks the frame loop to stop, as WM_CLOSE did.
void RequestQuit();
bool QuitRequested();
// Handles window and input events; the game's busy-waits call it through timeGetTime's
// callers' drawing (CGraphics::Flip).
void PumpEvents();

// The screen: OpenScreen makes what shows a picture of `width` x `height` (the back
// buffer's size), Present shows the back buffer through the palette's 256 entries, and
// CloseScreen undoes OpenScreen.
bool OpenScreen(int width, int height);
void Present(IDirectDrawSurface* back, const tagPALETTEENTRY* palette);
void CloseScreen();
// Whether the game's pictures are drawn at all. A headless game can run without: its
// sprites are then not decoded and the blitters do nothing, which leaves the game
// itself as it is (nothing the game reads comes from a picture).
bool Drawing();

// --- SDL3's.

// main.cpp
SDL_Window* Window();
// The game's objects, which WinMain kept in globals: for netplay (port/netplay/), which
// runs the scenes itself.
struct GameObjects {
    CGame* game;
    CScene** scenes;      // the nine scenes
    unsigned char* scene; // the current one's number
    CGraphics* graphics;
    CInput* input;
    CSound* sound;
};
GameObjects Objects();
// Deletes the game and its scenes and makes them anew, as at startup: the state the game
// starts in, which a network match starts from (as EfzRevival starts efz.exe).
void RestartGame();
// video.cpp: writes the last frame shown as a .bmp.
bool SaveFrame(const char* path);
// input.cpp
void KeyEvent(int scancode, bool down);
void ResetInput();
// Opens newly connected controllers and closes unplugged ones.
void UpdateJoysticks();
// The keyboard as it is, by DIK_ code (0x80: down), whatever the game is shown of it.
const unsigned char* KeyboardState();
// What P1's controls give (CInput::GetInput's bits, left and right together as left),
// read from the keyboard and controllers whatever the game is shown: the local player's
// input in a network match, which is played with P1's controls on either side.
unsigned char LocalControls();

// --- Every build's.

// graphics.cpp: while set, the game's drawing on the screen is skipped and Flip shows
// nothing (netplay's rollback runs frames again without drawing them, as Revival's
// setRendering(false) does). The screen's palette, as Flip shows it.
extern bool g_skipDrawing;
tagPALETTEENTRY* ScreenPalette(CGraphics* graphics);

// win32.cpp: where the game's files are read from and written to.
void SetDataDir(const char* data, const char* save);
FILE* OpenGameFile(const char* name, const char* mode);
FILE* OpenForUpdate(const char* name, bool create);
// A file opened elsewhere as a handle of the game's (CreateFile's), which CloseHandle
// closes: a replayed fight's replay file (port/record.cpp). INVALID_HANDLE_VALUE's
// number when the table is full.
uint32_t AdoptFile(FILE* f);
// While set (a UTF-8 path; nullptr: none), the replay slot's file the game opens for
// reading on this thread is this one instead: a headless environment playing a replay
// file (efz_env_play) through the replay menu's own path.
void SetReplayFile(const char* path);
// fopen by UTF-8 path, on Windows too (where fopen takes the ANSI code page's).
FILE* OpenPath(const char* path, const char* mode);

} // namespace efz

#endif
