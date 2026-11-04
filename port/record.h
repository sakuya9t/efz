// The fight recorder (docs/logging.md): each fight's record in the session folder, the
// checks of the game's state after every tick, and replaying a recorded fight.
//
// A fight is one visit of the fight scene, from its first tick to leaving it. Its
// record is fight-NNN.jsonl: a header (characters, stage, mode, rand()'s state...), then
// a line per tick (each player's input and status, the hash of each block of the state,
// as the compatibility test's log has them), and lines for events (rounds, pauses, the
// F-keys, anomalies) and the end. fight-NNN.state has the state's bytes at the first
// tick. That is all a replay needs: it loads the state, feeds the recorded input, and
// compares every tick's hashes with the record's.
#ifndef EFZ_RECORD_H
#define EFZ_RECORD_H

#include <stddef.h>

class CGame;
class CScene;

namespace efz {

struct RecordOptions {
    bool record = true;           // write the fight records
    const char* replay = nullptr; // a fight-NNN.jsonl to replay instead of the menus
};

// Once the game's objects exist: hooks the harness's tick (g_traceHooks).
void StartRecorder(const RecordOptions& options, CGame* game, CScene** scenes);
// With options.replay: sets the replayed fight's match up in place of the menus, and
// the scene to start from. False if the record can't be read.
bool StartReplay(unsigned char* scene);
// The main loop's frames, before and after the scene's Update. RecorderFrameEnd returns
// true once a replay is over.
void RecorderFrameStart(long frame, int scene);
bool RecorderFrameEnd(int scene);
// Ends a fight in progress, and says how a replay went.
void StopRecorder();
// A replay's exit code: 0 every tick as recorded, 3 a difference, 4 not replayed.
int ReplayResult();

// The input layer (port/input.cpp): the keyboard as the game reads it, which a replay
// supplies, and what GetInput returns, recorded outside the ticks.
void FilterKeyboard(unsigned char* keys, size_t size);
void NoteInput(int player, unsigned char input);

// For the crash and hang reports: the game as the recorder last saw it, written
// without allocating; and the fight record's end, at a crash.
void DescribeGame(char* out, size_t size);
void RecorderCrashed();

} // namespace efz

#endif
