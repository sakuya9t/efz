// The characters' palettes in a network match (EfzRevival 1.02h's EfzPalettes.cpp): the
// game's own six of each character, from <folder>\<folder>.dat, and the custom ones made
// with EDIT COLOR, <folder>\<folder>1.pal to 6.pal. The session keeps one store a player:
// this side's has its own custom palettes, which it sends to the other side
// (MessagePalette); the other's gets the ones that come, so that each side shows the
// palette the other chose.
#ifndef EFZ_NETPLAY_PALETTES_H
#define EFZ_NETPLAY_PALETTES_H

#include <map>
#include <string>

#include "protocol.h"

namespace efz {
namespace netplay {

// PaletteId: bits 0-7 the number (0-5), 16-19 custom, 24-31 the character.
int PaletteKey(int character, bool custom, int number);

class Palettes {
public:
    // The custom palettes of this computer (Palettes::loadAll).
    void LoadCustom();
    // The palette asked for, or false with the character's first (an invalid number) or
    // the game's own of that number (a custom one missing) in *out; false and *out
    // unchanged when not even that is there.
    bool Find(int character, bool custom, int number, ColorPalette* out);
    void Add(const ColorPalette& palette);
    bool Has(int key) const { return palettes_.count(key) != 0; }
    void Clear()
    {
        palettes_.clear();
        tried_.clear();
    }

private:
    bool LoadDat(int character, int number);
    bool LoadPal(int character, int number);
    std::map<int, ColorPalette> palettes_;
    std::map<int, bool> tried_; // .dat palettes read (or not there)
};

// Revival's folder of a character's files (Palettes::folderName).
const char* PaletteFolder(int character);

} // namespace netplay
} // namespace efz

#endif
