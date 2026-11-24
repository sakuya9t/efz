// OPTIONS' pages (port/options.cpp, src/scene6.cpp) and the native game's own settings,
// options.ini in the save folder: what key.ini (the game's page) and EfzRevival.ini
// (EfzRevival's) don't hold.
#ifndef EFZ_OPTIONS_H
#define EFZ_OPTIONS_H

struct SDL_Renderer;

namespace efz {

// main.cpp, once the game exists (not under the compatibility harness or a replayed
// fight): options.ini read, and OPTIONS given its pages.
void InitOptions();
// video.cpp, over each frame shown: the pages after the game's own, and the page tabs.
void DrawOptions(SDL_Renderer* renderer);

// The settings of the REVIVAL page that are the native game's, not Revival's (all on
// unless options.ini says otherwise; port/revival/ asks them):
// EfzRevival's features offline (the practice and replay tools, the music); without it
// the game offline is the original (the tournament, asked for, still runs).
bool RevivalFeatures();
bool PracticeTools(); // VS PLAYER's and PRACTICE's keys and overlay
bool ReplayTools();   // the REPLAY menu's
bool InputDisplay();  // the input display in those

// NATIVE's RECORD CPU FIGHTS (on unless options.ini says otherwise; port/record.cpp asks
// it): the fight records of every mode; off, only VS HUMAN's fights get theirs of the
// game's own accord (the records asked for, a .rep's, are made either way).
bool RecordCpuFights();

} // namespace efz

#endif
