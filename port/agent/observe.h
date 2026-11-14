// What an agent sees of a fight: each player's view, 168 numbers, as the training
// library (port/headless/env.cpp, efz_env_obs_name) gives them and the game gives its
// agents (port/agent/play.cpp). One file for both, so that an agent plays in the game on
// the view it was trained on.
#ifndef EFZ_AGENT_OBSERVE_H
#define EFZ_AGENT_OBSERVE_H

class CGame;
class CScene3;

namespace efz {
namespace agent {

const int kGlobalFeatures = 8;
const int kPlayerFeatures = 32;
const int kObjects = 8; // per player: the active ones nearest the viewer
const int kObjectFeatures = 6;
const int kObsDim = kGlobalFeatures + 2 * kPlayerFeatures + 2 * kObjects * kObjectFeatures;
const int kCharacters = 25;

// Player `viewer`'s view of the fight (0 or 1), self first, into out[kObsDim]. `frame`:
// frames into the match, written as frame / maxFrames (or / 10000 if maxFrames is 0).
void WriteView(float* out, CScene3* fight, CGame* game, int viewer, int frame, int maxFrames);
// The name of feature i ("self_hp", "opp_obj3_x"...); nullptr out of range.
const char* ObservationName(int i);
// The game's character numbers' names (0 "nanase" .. 24 "mizuka"); nullptr out of range.
const char* CharacterName(int c);

} // namespace agent
} // namespace efz

#endif
