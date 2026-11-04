// What the native platform layer's parts share: the window, the frame loop's controls
// and the game's folders.
//
// graphics.cpp, win32.cpp, arena.cpp, x87.cpp and layout.cpp are the same in every
// build. The rest is a platform's own: SDL3's (main.cpp, video.cpp, input.cpp,
// sound.cpp) for the game, or the headless library's (port/headless/), which runs
// games without a window or sound, for programs that play it.
#ifndef EFZ_PLATFORM_H
#define EFZ_PLATFORM_H

#include <stdio.h>

struct SDL_Window;
struct IDirectDrawSurface;
struct tagPALETTEENTRY;

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
// video.cpp: writes the last frame shown as a .bmp.
bool SaveFrame(const char* path);
// input.cpp
void KeyEvent(int scancode, bool down);
void ResetInput();
// Opens newly connected controllers and closes unplugged ones.
void UpdateJoysticks();

// --- Every build's.

// win32.cpp: where the game's files are read from and written to.
void SetDataDir(const char* data, const char* save);
FILE* OpenGameFile(const char* name, const char* mode);
FILE* OpenForUpdate(const char* name, bool create);

} // namespace efz

#endif
