// The replay tool (efz-convert, docs/logging.md): the game in a small window of its own,
// which converts records (fight-NNN.jsonl) and replays (.rep) into each other and makes
// videos (.mp4) of either, through record.h's conversions. Files are dropped on the
// window or picked with the system's file dialog; what is made goes to a folder of the
// player's (by default `converted` in the logs folder, which the game's RECORDS page
// lists). The game's scenes run only while a file is converted.
#ifndef EFZ_TOOL_H
#define EFZ_TOOL_H

#include <string>
#include <vector>

union SDL_Event;
struct SDL_Renderer;

namespace efz {

// main.cpp, once the game exists, with --tool (port/toolmain.cpp): the files to start
// with (the command line's, or dropped on the program).
void InitTool(const std::vector<std::string>& files);
bool ToolOn();
// main.cpp's PumpEvents: the mouse, files dropped; true when the tool took the event.
bool ToolEvent(const SDL_Event& event);
// main.cpp, each frame while nothing is converted: what the dialogs picked and the
// buttons asked for; a conversion started sets *scene.
void ToolFrame(unsigned char* scene);
// video.cpp, over each frame shown.
void DrawTool(SDL_Renderer* renderer);

} // namespace efz

#endif
