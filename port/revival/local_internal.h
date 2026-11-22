// What the local sessions (local.h) share: the game as EfzRevival.dll's Game class sees
// it (revival/EfzRevival/EfzGame.cpp), the overlay's text and boxes (DDRAW.dll's text
// and box renderers), and the session base class (Session.h).
#ifndef EFZ_REVIVAL_LOCAL_INTERNAL_H
#define EFZ_REVIVAL_LOCAL_INTERNAL_H

// The standard headers first: efz.h's rand() macro (port/x87.h) breaks theirs.
#include <math.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include <algorithm>
#include <deque>
#include <memory>
#include <queue>
#include <random>
#include <string>
#include <vector>

#include "efz.h"
#include "config.h"
#include "keys.h"
#include "../platform.h"
#include "../log.h"
#include "../options.h"

namespace efz {
namespace revival {

// --- The game (Game's accessors)

int SceneId();
CScene* SceneAt(int index);
CGame* GameObject();
// The title's choice: 0 ARCADE, 1 VS CPU, 2 VS PLAYER, 3 PRACTICE, 4 REPLAY.
int MenuChoice();
// A player of the fight (scene 3), or null.
CPlayer* PlayerOf(int index);
int Character(int player);
int HumanPlayer(); // m_isCpu[0]: 1 when P1 is the CPU
// The game's frame, as the session runs it (Game::runFrame).
void RunGameFrame();
// Swaps the two players' key bindings (Game::swapBindings); SwappedBindings is whether
// they are swapped now, and UnswapBindings puts them back.
void SwapBindings();
bool SwappedBindings();
void UnswapBindings();
bool IsWakingUp(int player);
bool IsTeching(int player);
bool IsGuarding(int player);
bool IsRecoilGuarding(int player);
// The replay mode in match setup and the fight (1 playing, 2 recording), else -1.
int ReplayMode();
bool IsRoundOver();
bool IsMatchOver();
bool PlayerDown(int player); // in a hit reaction, not knocked down: Game::isHit
// F4-F8 and Esc as bits 0-5 (Game::functionKeys), from the keyboard.
unsigned char FunctionKeys();
// Left and right together as left (Game::cleanInput).
unsigned char CleanInput(unsigned char input);
// P1's or P2's controls as CInput::GetInput reads them, without the hooks.
unsigned char ControlsOf(int player);
// The character names of Revival's file names and logs (Game::characterName).
const char* CharacterName(int character);
// Every 32 frames on the title and character select, with the window in front: key.ini
// read again when it was written (Game::keyIniChanged, reloadKeys).
void CheckDevices();

// --- The overlay, over the game's 640x480 (EfzRender's text and boxes)

const int kAlignLeft = 0, kAlignRight = 2;
void ClearText();
void AddText(const std::string& text, int x, int y, int align = kAlignLeft);
void SetTextRender(bool on);
// The boxes to draw over the fight: a player's and its objects' of a kind.
const int kBoxHit = 0, kBoxHurt = 1, kBoxCollision = 2;
void ClearBoxes();
void ShowBoxes(int player, int kind);
// An input byte as the input display shows it: the direction as the keypad's digit (5
// for none), then the buttons.
std::string InputText(unsigned char input);
// The last 15 inputs of `inputs` from y = 200 down, newest first, each with the frames it
// was held (`divisor` entries a frame): InputDisplay.h's drawInputs.
void DrawInputs(const std::vector<char>& inputs, int y, int x, int divisor);

// A state loaded for practice or a replay (netplay::SaveState::Load), without the fight's
// frame-rate count (CScene3::m_frameCount, m_secondStart, m_fps), as Revival's partial save
// leaves them out (SaveState::save(false)).
template <class State> void LoadKeepingFps(State& state)
{
    CScene3* fight = (CScene3*)SceneAt(3);
    int frames = fight ? fight->m_frameCount : 0;
    DWORD second = fight ? fight->m_secondStart : 0;
    int fps = fight ? fight->m_fps : 0;
    state.Load();
    if (fight) {
        fight->m_frameCount = frames;
        fight->m_secondStart = second;
        fight->m_fps = fps;
    }
}

// --- The game's speed (DDRAW.dll's EfzTimer::setFps)

const double kDefaultFps = 64.0;
void SetFps(double fps);

// --- The sessions

class Session {
public:
    virtual ~Session() {}
    virtual void Start() {}
    // Whether OPTIONS has it on (the practice and replay tools); off, the game's frames
    // are the game's own.
    virtual bool Enabled() { return true; }
    // Each real frame, the keys first: one call a key pressed.
    virtual void KeyPressed(int key) { (void)key; }
    // Whether this frame of the game is held back (a fight paused).
    virtual bool Holds() { return false; }
    // The frame: runs the game's (RunGameFrame) or not.
    virtual void Update() { RunGameFrame(); }
    virtual void Input(unsigned char* input, int player) { (void)input; (void)player; }
    virtual void FightKeys(unsigned char* keys) { (void)keys; }
};

Session* NewPracticeSession();
Session* NewReplaySession();
Session* NewTournamentSession();

} // namespace revival
} // namespace efz

#endif
