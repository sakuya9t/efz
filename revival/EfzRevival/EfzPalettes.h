// The characters' palettes (EfzPalettes.cpp, 0x1006d5b0-0x1006df40): the game's own six
// of each character, from <name>\<name>.dat, and the custom ones the player made,
// <name>\<name>1.pal to 6.pal. The online and spectator sessions keep one per player
// to apply the palette the other side chose (MessagePalette).
#pragma once
#include <winsock2.h>
#include <windows.h>
#include <map>
#include <string>
#include "../EfzRevivalLauncher/SharedData.h"

// Which palette: a character, its number 0-5, and whether it is a custom one, packed
// into an int: bits 0-7 the number, 16-19 custom, 24-31 the character. It is
// ColorPalette's first field, and the map's key.
struct PaletteId {
    // FUNCTION: 0x10016a70
    PaletteId(char character_, bool custom_, char id_)
    {
        value = (((character_ << 8) | (unsigned char)custom_) << 16) | id_;
    }

    int value;
};

class Palettes {
public:
    // Loads the game's palettes.
    Palettes();
    ~Palettes();
    // Loads the custom palettes.
    void loadAll();
    // The palette asked for, or false with the character's first (an invalid number) or
    // the game's own (a missing custom one) in *out.
    bool find(unsigned int character, bool custom, unsigned int number, ColorPalette *out);
    void add(const ColorPalette &palette, bool replace = true);

private:
    bool loadDat(unsigned int character, unsigned int number);
    bool loadPal(unsigned int character, unsigned int number);
    bool readColors(PALETTEENTRY *colors, int first, int index, std::string file);
    void toColors(const BYTE *rgb, PALETTEENTRY *colors);
    void log(const ColorPalette *palette);
    std::string folderName(int character);
    PaletteId makePalette(unsigned int character, bool custom, unsigned int number);
    bool validPalette(unsigned int character, unsigned int number);

    std::map<int, ColorPalette> palettes_;
};
