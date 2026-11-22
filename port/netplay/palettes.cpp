// The characters' palettes (palettes.h), from revival/EfzRevival/EfzPalettes.cpp.
#include "palettes.h"

#include <stdio.h>
#include <string.h>

#include "efz.h"
#include "../platform.h"
#include "../log.h"

namespace efz {
namespace netplay {

namespace {

bool Valid(int character, int number)
{
    return character >= 0 && character <= 24 && number >= 0 && number <= 5;
}

// 40 colours from colour `first` of a file's palette, after its first byte; the files'
// colours are blue, green, red (readColors, toColors).
bool ReadColors(const std::string& file, int first, PALETTEENTRY* colors)
{
    FILE* f = OpenGameFile(file.c_str(), "rb");
    if (!f)
        return false;
    unsigned char rgb[120];
    bool ok = fseek(f, first * 3 + 1, SEEK_SET) == 0 && fread(rgb, 1, sizeof(rgb), f) == sizeof(rgb);
    fclose(f);
    if (!ok)
        return false;
    for (int i = 0; i < 40; i++) {
        colors[i].peRed = rgb[i * 3 + 2];
        colors[i].peGreen = rgb[i * 3 + 1];
        colors[i].peBlue = rgb[i * 3];
        colors[i].peFlags = 0;
    }
    return true;
}

} // namespace

const char* PaletteFolder(int character)
{
    static const char* const names[25] = {
        "Nanase", "Ayu",     "Mai",     "Makoto", "Akane",   "Mayu",    "Nagamori",
        "Misaki", "Shiori",  "Sayuri",  "Nayuki", "Mio",     "ExNanase", "Kaori",
        "Ikumi",  "Mishio",  "Akiko",   "NayukiB", "MizukaB", "Kanna",  "Kano",
        "Minagi", "NayukiA", "Misuzu",  "Mizuka"};
    return character >= 0 && character < 25 ? names[character] : "error";
}

int PaletteKey(int character, bool custom, int number)
{
    return (((character << 8) | (custom ? 1 : 0)) << 16) | (number & 0xff);
}

bool Palettes::LoadDat(int character, int number)
{
    int key = PaletteKey(character, false, number);
    if (tried_.count(key))
        return palettes_.count(key) != 0;
    tried_[key] = true;
    std::string folder = PaletteFolder(character);
    ColorPalette p;
    memset(&p, 0, sizeof(p));
    if (!ReadColors(folder + "\\" + folder + ".dat", number * 40, (PALETTEENTRY*)(p.data + 4)))
        return false;
    memcpy(p.data, &key, 4);
    palettes_[key] = p;
    return true;
}

bool Palettes::LoadPal(int character, int number)
{
    std::string folder = PaletteFolder(character);
    ColorPalette p;
    memset(&p, 0, sizeof(p));
    if (!ReadColors(folder + "\\" + folder + std::to_string(number + 1) + ".pal", 0,
                    (PALETTEENTRY*)(p.data + 4)))
        return false;
    int key = PaletteKey(character, true, number);
    memcpy(p.data, &key, 4);
    palettes_[key] = p;
    return true;
}

void Palettes::LoadCustom()
{
    int found = 0;
    for (int character = 0; character <= 24; character++)
        for (int number = 0; number < 6; number++)
            found += LoadPal(character, number);
    LogInfo("net", "%d custom palettes of EDIT COLOR here", found);
}

bool Palettes::Find(int character, bool custom, int number, ColorPalette* out)
{
    if (character < 0 || character > 24)
        return false;
    if (!Valid(character, number)) {
        Find(character, false, 0, out);
        return false;
    }
    if (!custom)
        LoadDat(character, number);
    auto it = palettes_.find(PaletteKey(character, custom, number));
    if (it == palettes_.end()) {
        if (custom)
            Find(character, false, number, out);
        return false;
    }
    *out = it->second;
    return true;
}

void Palettes::Add(const ColorPalette& palette)
{
    int key;
    memcpy(&key, palette.data, 4);
    palettes_[key] = palette;
}

} // namespace netplay
} // namespace efz
