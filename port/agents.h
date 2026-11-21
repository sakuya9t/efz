// Trained agents in the native game (port/agent/play.cpp, docs/agents.md): an agent file
// (.efzagent, python/examples/export_agent.py) in the `agents` folder of the game's
// folder or of its save folder plays a side of VS HUMAN, chosen on character select
// (F5 for P1, F6 for P2; with Shift, back), or this computer's side of a network match
// (NET PLAY's PLAYED BY). It plays through the controls only, a control byte a frame as
// a person's, so the game, its replays and the other side of a network match see
// nothing else. An agent file with routes (a combo library) plans its combos on copies
// of the fight in the time between frames (agent/routes.h), as play.py --assist does;
// the copies' frames are heard, drawn, recorded and sent nowhere.
//
// With OPTIONS' CPU COMBO on, the game's CPU in ARCADE and VS CPU plays its combos from
// an agent file of its character in the agents folders' `cpu` folder: the CPU hands the
// file its side while its opponent is in a hit reaction (port/agent/play.cpp).
#ifndef EFZ_AGENTS_H
#define EFZ_AGENTS_H

#include <stdint.h>

struct SDL_Renderer;

namespace efz {

// main.cpp, once the game exists (not under the compatibility harness or a replayed
// fight): the agents folders are read. p1, p2: agent files to play those sides of VS
// HUMAN from the start (--agent-p1, --agent-p2).
struct AgentOptions {
    const char* p1 = nullptr;
    const char* p2 = nullptr;
    // --fast: no time between frames, so a plan is waited for until it is done.
    bool fast = false;
    // --cpu-combos on|off: the CPU's combos for this run, whatever OPTIONS says (-1: as it
    // says).
    int cpuCombos = -1;
};
void InitAgents(const AgentOptions& options);
// main.cpp, each frame before the scene's update, out of netplay: the agents' inputs of
// the frame, and F5/F6 (Shift+F5/F6) on character select. Nothing while a record plays
// from the REPLAY menu (record.h): its inputs are the record's.
void AgentsFrame();
// input.cpp's CInput::GetInput out of netplay: an agent's side gets its input instead of
// the controls'; with one side an agent, the other side's player may use P1's controls.
void AgentInput(int player, unsigned char* input);
// video.cpp, over each frame shown: who plays each side.
void DrawAgents(SDL_Renderer* renderer);
// main.cpp, once a frame is done and before it waits for the next: the agents' plans
// worked on until `deadlineNs` (SDL_GetTicksNS's clock).
void AgentsIdle(uint64_t deadlineNs);
// main.cpp, quitting: what the agents' routes did in the fight going on, in the log.
void StopAgents();
// While set, the game is running frames of an agent's plan on a copy of the fight:
// sound.cpp, input.cpp and netplay leave those frames out.
bool AgentPlanning();
// The fight recorder (record.cpp), as a fight of VS HUMAN begins: the agent playing a
// side, its name (with its version) and its file's name; null for a person's side.
const char* AgentName(int side);
const char* AgentFileName(int side);

// --- The game's CPU with combos (docs/agents.md, "The CPU's combos").

// OPTIONS' CPU COMBO (port/options.cpp keeps it in options.ini): whether the CPU plays
// its combos from its character's file.
void SetCpuCombos(bool on);
bool CpuCombos();
// The fight recorder, as a fight begins: the file that plays side's combos for the CPU
// (its file name; null: none) and the share of the most damaging combo its level aims
// at (1 at level 4).
const char* CpuComboFile(int side);
float CpuComboShare(int side);

// --- Netplay (port/netplay/): this computer's side played by an agent.

// The agents found (read again from the folders), and each one's label ("name (Ayu)").
int AgentCount();
const char* AgentLabel(int index);
const char* AgentFile(int index); // its file's name, as netplay.ini keeps it
void RescanAgents();
// The agent with this file name (in the folders) or path (added); -1 if none.
int FindAgent(const char* nameOrPath);
// A match starts with this agent (an index; -1: the person) playing `localPlayer` (-1:
// only to see that it can be read), or ends. false (and *error) if it can't be read.
bool NetplayAgentStart(int index, int localPlayer, const char** error);
void NetplayAgentStop();
// The session's local input of a frame (Session::ReadInput, once a frame): the agent's on
// character select until its character is chosen, and in a fight. menuDelay: frames
// before a menu input takes effect. false: the person's controls stand.
bool NetplayAgentInput(int scene, int menuDelay, unsigned char* input);
// The fight's frame just shown (Session, after running the frame it draws): what the
// agent sees for its next input, as a person sees the screen.
void NetplayAgentShown();
// The agent playing this computer's side of the match; nullptr none.
const char* NetplayAgentName();

} // namespace efz

#endif
