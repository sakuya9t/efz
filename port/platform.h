// What the native platform layer's parts share: the window, the frame loop's controls
// and the game's folders.
#ifndef EFZ_PLATFORM_H
#define EFZ_PLATFORM_H

#include <stdio.h>

struct SDL_Window;

namespace efz {

// main.cpp
SDL_Window* Window();
// Asks the frame loop to stop, as WM_CLOSE did.
void RequestQuit();
bool QuitRequested();
// Handles window and input events; the game's busy-waits call it through timeGetTime's
// callers' drawing (CGraphics::Flip).
void PumpEvents();

// graphics.cpp: writes the last frame shown as a .bmp.
bool SaveFrame(const char* path);

// win32.cpp: where the game's files are read from and written to.
void SetDataDir(const char* data, const char* save);
FILE* OpenGameFile(const char* name, const char* mode);
FILE* OpenForUpdate(const char* name, bool create);

// input.cpp
void KeyEvent(int scancode, bool down);
void ResetInput();
// Opens newly connected controllers and closes unplugged ones.
void UpdateJoysticks();

} // namespace efz

#endif
