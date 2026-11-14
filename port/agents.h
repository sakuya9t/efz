// Trained agents in the native game (port/agent/play.cpp, docs/agents.md): an agent file
// (.efzagent, python/examples/export_agent.py) in the `agents` folder of the game's
// folder or of its save folder plays a side of VS HUMAN, chosen on character select
// (F5 for P1, F6 for P2), or this computer's side of a network match (NET PLAY's PLAYED
// BY). It plays through the controls only, a control byte a frame as a person's, so the
// game, its replays and the other side of a network match see nothing else.
#ifndef EFZ_AGENTS_H
#define EFZ_AGENTS_H

struct SDL_Renderer;

namespace efz {

// main.cpp, once the game exists (not under the compatibility harness or a replayed
// fight): the agents folders are read. p1, p2: agent files to play those sides of VS
// HUMAN from the start (--agent-p1, --agent-p2).
struct AgentOptions {
    const char* p1 = nullptr;
    const char* p2 = nullptr;
};
void InitAgents(const AgentOptions& options);
// main.cpp, each frame before the scene's update, out of netplay: the agents' inputs of
// the frame, and F5/F6 on character select.
void AgentsFrame();
// input.cpp's CInput::GetInput out of netplay: an agent's side gets its input instead of
// the controls'; with one side an agent, the other side's player may use P1's controls.
void AgentInput(int player, unsigned char* input);
// video.cpp, over each frame shown: who plays each side.
void DrawAgents(SDL_Renderer* renderer);

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
