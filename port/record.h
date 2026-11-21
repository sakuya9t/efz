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
#include <stdint.h>
#include <string>
#include <vector>

class CGame;
class CScene;
struct SDL_Renderer;

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
// true once a replay is over; a record played from the REPLAY menu sets *scene to the
// menu's when the fight is left.
void RecorderFrameStart(long frame, int scene);
bool RecorderFrameEnd(unsigned char* scene);

// --- Records played in the game, from the REPLAY menu's RECORDS page (port/records.cpp).

// A record's facts, from its first and last lines.
struct RecordSummary {
    std::string path;    // its fight-NNN.jsonl
    std::string session; // its session's id
    std::string started; // when the fight began, as the header has it
    std::string revision, os; // the game that recorded it: git's revision, its system
    bool dirty = false;       // and whether it was built with changes
    int fight = 0;
    int mode = -1;       // CGame::m_gameMode
    int replayMode = 0;
    int roundsToWin = 2;
    int chars[2] = {-1, -1};
    bool cpu[2] = {false, false};
    std::string agent[2]; // the agent that played the side ("": a person or the CPU)
    std::string cpuCombos[2]; // the file that played the CPU's combos ("": none)
    bool unknown[2] = {false, false}; // a person or an agent: the record doesn't say
    bool replayed = false; // the record of a replayed fight (replay_of)
    // The end: why ("" none: the record stops short, as after a crash), the winner (-1
    // none), the rounds won; how long the fight was.
    std::string reason;
    int winner = -1;
    int roundsWon[2] = {0, 0};
    long ticks = 0, frames = 0;
};
bool ReadRecordSummary(const char* path, RecordSummary* out);
// Plays a record in the game: the match set up as --replay-fight sets it up (scene 2
// next), the recorded state and inputs at the first tick, the record's F-keys. The
// game's files go to a scratch folder meanwhile. Esc or the record's end leaves the
// fight for the REPLAY menu, with the game's settings as they were. False (and *error)
// if it can't be read.
bool PlayRecord(const char* path, std::string* error);
// Saves a record as a replay in the REPLAY menu's slot (page, slot from 0): the record is
// replayed with the game recording a replay of it, as the menu's RECORD item records one
// (fast, not drawn, not heard), then that replay is played back as the menu's PLAY item
// plays one and compared with the record tick by tick; the slot gets it only if every
// tick is the record's. A record whose fight played a replay gets that one. Not a record
// with the CPU in it (a replay can't hold the CPU's decisions), nor one played to other
// than 2 rounds won (a replay is played to 2). True when the game goes to match setup
// for it; false when it is done already or can't be (*error says why, "" when done).
// How it went: TakeRecordNote, back on the menu.
bool SaveRecordAsReplay(const char* path, int page, int slot, std::string* error);
// Conversions, for the command line (--record-to-rep, --rep-to-record, --export-mp4) and
// the replay tool (port/tool.cpp):
// - kToRep: a record to a .rep in outDir (<session>-fight-NNN.rep), as
//   SaveRecordAsReplay makes one;
// - kToRecord: a .rep (the game's, or EfzRevival's extended, played to Revival's rules)
//   played as the menu plays one, its fight recorded: in outDir as <replay's name>.jsonl
//   (.state, .rep), or without outDir in this run's session folder;
// - kToVideo: either played (a record as watched) into a video, outDir/<name>.mp4, its
//   pictures 640x480 times videoScale (1 or 2).
// Each says how it went on stdout (not `stay`) and in the log. True when the game runs
// the first (scene 2 next); the command line's run is over when RecorderFrameEnd says
// so; with `stay` (the tool) the game waits for more (scene 0, not run). Conversions:
// how each went; Progress: the one going. ConversionResult: 0 all converted, 3 a replay
// played otherwise than its record, 4 one not converted.
struct Conversion {
    enum Kind { kToRep, kToRecord, kToVideo };
    Kind kind = kToRep;
    std::string in;
    std::string outDir;
    int videoScale = 2;
};
bool StartConversions(const std::vector<Conversion>& list, unsigned char* scene,
                      bool stay = false);
int ConversionResult();
struct ConversionState {
    std::string in, out; // out: what it made
    std::string said;    // how it went ("" not yet)
    int status;          // -1 not yet, 0 done, 3 played otherwise, 4 not converted
};
std::vector<ConversionState> Conversions();
struct ConversionProgress {
    bool running = false;
    size_t job = 0, jobs = 0;
    bool checking = false; // a replay made of a record, played back against it
    bool video = false;
    float done = 0;        // of the fight
};
ConversionProgress Progress();
// The tool's Stop: the conversion going is left, the rest not started.
void CancelConversions();
// video.cpp, each frame shown (0x00RRGGBB, before what is drawn over it): a video's.
void FrameShown(const uint32_t* pixels, int width, int height);
// The record being played from the menu, or saved as a replay, for what the page shows
// over it; null when none.
struct RecordView {
    const char* path;
    long tick, ticks; // played, and in all
    long firstDiff;   // the first tick that played otherwise than recorded; -1 none
    bool paused;
    bool done;        // its last tick played, or left
    bool saving;      // being saved as a replay: written, then
    bool checking;    // played back to be compared
};
const RecordView* ViewingRecord();
// How the last record played or saved from the menu went ("" nothing to say), once;
// *done: it was saved.
std::string TakeRecordNote(bool* done = nullptr);
// main.cpp: while a replay is written, checked or recorded, or a video made, frames
// aren't waited for (RecordHurry); nor drawn but for a video (RecordUndrawn: the page
// shows how far it is now and then). RecordTasksRunning: any of it, or a record watched.
bool RecordHurry();
bool RecordUndrawn();
bool RecordTasksRunning();
// main.cpp, each frame: F8 pauses a record being played and goes on with it (the game's
// own F8 is the record's); true while paused: the frame is then shown again, not run.
bool RecordPaused(int scene);
// port/records.cpp: the RECORDS page (efz::RecordsHooks, main.cpp once the game exists,
// out of the compatibility harness); video.cpp, over each frame shown: the page's list,
// and a record's information as it plays.
void InitRecords();
void DrawRecords(SDL_Renderer* renderer);
// Ends a fight in progress, and says how a replay went.
void StopRecorder();
// No records and no per-tick checks while set: a network match runs frames again on
// rollback (port/netplay/), which a record can't follow; it writes a replay of its own.
void SuspendRecorder(bool suspend);
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
