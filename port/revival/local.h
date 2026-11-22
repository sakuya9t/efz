// EfzRevival's local play in the native game (docs/revival-features.md): what
// EfzRevival.dll does when the launcher starts the game for local play (its mode 2) or a
// tournament (mode 3), from revival/EfzRevival/PracticeSession.cpp, Recorder.cpp,
// ReplaySession.cpp and TournamentSession.cpp.
//
// One session at a time runs the game's frames, as in Revival (EfzRevival.cpp's
// switchSession): the practice session from the start, the replay session once the
// title's REPLAY is chosen, the practice session again once VS PLAYER or PRACTICE is; or
// the tournament's for the whole run (--tournament).
//   practice  VS PLAYER's and PRACTICE's fights: pause, frame step, save and load the
//             state, the text overlay and the input display, hit, hurt and collision
//             boxes, game speed, input delay; in VS PLAYER also the dummy's recording and
//             replay (five buffers, at once or on wake-up, tech, guard, recoil guard),
//             switching and mirroring the players
//   replay    the REPLAY menu's replays: pause, frame step, speed, save and load, seeking,
//             the boxes; an EfzRevival replay (one with its inputs at the end) is played
//             from those, with the input display, and either character can be taken over
//   tournament two named players (EfzRevival.ini's [Tournament]) in VS PLAYER, the score
//             on screen, every match's replay and its result in the tournament's folder;
//             no function keys, Esc only when held
// The keys are EfzRevival.ini's (config.h). None of it runs under the compatibility
// suite's harness, nor while a record is played from the REPLAY menu.
#ifndef EFZ_REVIVAL_LOCAL_H
#define EFZ_REVIVAL_LOCAL_H

#include <stddef.h>

struct SDL_Renderer;

namespace efz {
namespace revival {

// main.cpp, out of the harness, once the game exists.
void InitLocal(bool tournament);
bool LocalOn();
// main.cpp, each real frame out of netplay: whether the game's frame runs (false: the
// fight is paused, the last frame is shown again), then the frame itself, run through
// `run` (the scene's Update) as the session decides.
bool WillRunFrame();
void RunFrame(void (*run)(void* scene), void* scene);
// The frames a second the session asks for (64 unless the game speed was changed).
double FramesPerSecond();
// input.cpp's CInput::GetInput: a player's input for this read (the dummy's recording or
// replay, the input delay, a replay's inputs).
void Input(int player, unsigned char* input);
// input.cpp's keyboard, as the fight reads it: the function keys and Esc as the session
// has them (a replay's, the tournament's).
void FightKeys(unsigned char* keys, size_t size);
// video.cpp, over each frame shown.
void DrawLocal(SDL_Renderer* renderer);

} // namespace revival
} // namespace efz

#endif
