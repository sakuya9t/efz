// What DDRAW.dll changes in efz.exe when it runs it alone (dllmain.cpp's initVanilla,
// "Adding EFZ fixes"): its own window, the frame timer, DirectInput and joysticks, and
// a few patches to the game's code (EfzFixes.cpp).
#pragma once
#include <windows.h>

// WinMain's window style: a caption, a system menu and minimizing, no resizing.
#define WS_WINDOW (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_VISIBLE)

void skipWindowCreation();
void createWindow();
void fixGame();
void fixSounds();
void copyInput();
void fixIkumi();
void hookTimer();
void fixScene();
void hookReplays();

// A player's controls through DDRAW.dll's copy of CInput::GetInput (copyInput): the
// game's, with the joystick's hat as a direction.
BYTE efzInput(bool player2);
