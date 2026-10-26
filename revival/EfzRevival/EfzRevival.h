// EfzRevival.cpp: the DLL's entry (init), the hooks it installs into efz.exe on the
// first frame, and the state they share.
#pragma once
#include <winsock2.h>
#include <windows.h>
#include <random>

// The launcher's mode (init's args[0]): 0 online, 1 spectator, 2 practice, 3 tournament
extern int g_mode;
// Keys (DIK_*) and the joystick's 32 buttons, updated every frame: held, and went down
// or up this frame.
extern bool g_keyHeld[0x100];
extern bool g_keyPressed[0x100];
extern bool g_keyReleased[0x100];
extern bool g_buttonPressed[0x20];
extern bool g_buttonReleased[0x20];

// In place of the game's rand (EfzRevival.cpp's random), so that both sides of a
// netplay match draw the same numbers; save states and extended replays keep its state.
extern std::minstd_rand g_rng;

// The netplay session's end of match: closes the fight's replay and leaves netplay
// (patched over efz.exe's own handling at 0x763f04 and 0x763e50).
void onReplayDone();
