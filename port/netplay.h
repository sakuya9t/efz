// Netplay in the native game (port/netplay/, docs/netplay.md): EfzRevival 1.02h's
// rollback netplay, built in. The title menu's NET PLAY hosts or joins a match; the
// match then runs from the title, as EfzRevival runs one, with one player at this
// computer and the other over the network.
//
// What the rest of the SDL3 game calls. The game code itself only sees
// efz::NetplayHooks (efz_native.h).
#ifndef EFZ_NETPLAY_H
#define EFZ_NETPLAY_H

union SDL_Event;
struct SDL_Renderer;

namespace efz {

// main.cpp, once the game exists: the title menu gets its NET PLAY row. `options` are
// the command line's netplay options (--host, --join), which skip the menu.
struct NetplayOptions {
    bool host = false;
    const char* join = nullptr; // address
    int port = 0;               // 0: Revival's 10800
    const char* name = nullptr;
    int delay = -1;             // -1: the recommended
};
void InitNetplay(const NetplayOptions& options);
// Whether netplay's screens or a match have this frame instead of the game's own loop,
// and that frame (main.cpp).
bool NetplayRunning();
void NetplayFrame();
// The window is closing: the opponent is told.
void ShutdownNetplay();
// main.cpp's PumpEvents: an event netplay's screens take (true) rather than the game.
bool NetplayEvent(const SDL_Event& event);
// video.cpp, over each frame shown: netplay's screens and the match's information.
void DrawNetplay(SDL_Renderer* renderer);
// input.cpp's CInput::GetInput in a match: the frame's input for that player.
void NetplayInput(int player, unsigned char* input);
// sound.cpp's CSound::Play: true when netplay played the sound or chose not to.
bool NetplaySound(unsigned short id, int loop);

} // namespace efz

#endif
