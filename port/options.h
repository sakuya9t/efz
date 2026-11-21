// The native game's own settings (options.ini in the save folder) and OPTIONS' CPU COMBO
// row (port/options.cpp, src/scene6.cpp).
#ifndef EFZ_OPTIONS_H
#define EFZ_OPTIONS_H

struct SDL_Renderer;

namespace efz {

// main.cpp, once the game exists (not under the compatibility harness or a replayed
// fight): options.ini read, and the OPTIONS page given its CPU COMBO row.
void InitOptions();
// video.cpp, over each frame shown: CPU COMBO's text, when its row couldn't be made from
// the page's pictures (a translation patch's).
void DrawOptions(SDL_Renderer* renderer);

} // namespace efz

#endif
