// The characters' palettes (EfzPalettes.h).
#include "EfzPalettes.h"
#include "Log.h"
#include <fstream>
#include <sstream>

// FUNCTION: 0x1006d5b0
// TODO: differs: the original pushes readColors' index (always 0) as a real argument;
// this build propagates the 0 into readColors and pushes a dummy ecx instead.
bool Palettes::loadDat(unsigned int character, unsigned int number)
{
    if (!validPalette(character, number))
        return false;
    std::stringstream path;
    path << folderName(character) << "\\" << folderName(character) << ".dat";
    ColorPalette palette;
    if (readColors((PALETTEENTRY *)(palette.data + 4), number * 40, 0, path.str())) {
        *(int *)palette.data = makePalette(character, false, number).value;
        palettes_[*(int *)palette.data] = palette;
        return true;
    }
    return false;
}

// FUNCTION: 0x1006d710
void Palettes::log(const ColorPalette *palette)
{
    int value = *(int *)palette->data;
    int character = value >> 24;
    bool custom = (value >> 16 & 0xf) != 0;
    int id = value & 0xff;
    g_log << folderName(character) << " id " << id << " custom " << custom << "\n";
    g_log.flush();
}

// The files' colours are blue, green, red.
// FUNCTION: 0x1006d7e0
void Palettes::toColors(const BYTE *rgb, PALETTEENTRY *colors)
{
    for (int i = 0; i < 40; i++) {
        colors[i].peRed = rgb[i * 3 + 2];
        colors[i].peGreen = rgb[i * 3 + 1];
        colors[i].peBlue = rgb[i * 3];
        colors[i].peFlags = 0;
    }
}

// FUNCTION: 0x1006d820
PaletteId Palettes::makePalette(unsigned int character, bool custom, unsigned int number)
{
    if (validPalette(character, number))
        return PaletteId(character, custom, number);
    throw "wtf";
}

// FUNCTION: 0x1006d870
bool Palettes::validPalette(unsigned int character, unsigned int number)
{
    if (character > 24)
        throw "wtf";
    if (number > 5)
        return false;
    return true;
}

// FUNCTION: 0x1006d8a0
bool Palettes::find(unsigned int character, bool custom, unsigned int number, ColorPalette *out)
{
    if (!validPalette(character, number)) {
        g_log << "Garbage palette\n";
        g_log.flush();
        find(character, false, 0, out);
        return false;
    }
    int key = makePalette(character, custom, number).value;
    std::map<int, ColorPalette>::iterator it = palettes_.find(key);
    if (it == palettes_.end()) {
        g_log << "Not Found\n";
        g_log.flush();
        find(character, false, number, out);
        return false;
    }
    *out = it->second;
    log(out);
    return true;
}

// The folders the game's character files are in, by character number.
// FUNCTION: 0x1006d980
std::string Palettes::folderName(int character)
{
    switch (character) {
    case 0:
        return "Nanase";
    case 1:
        return "Ayu";
    case 2:
        return "Mai";
    case 3:
        return "Makoto";
    case 4:
        return "Akane";
    case 5:
        return "Mayu";
    case 6:
        return "Nagamori";
    case 7:
        return "Misaki";
    case 8:
        return "Shiori";
    case 9:
        return "Sayuri";
    case 10:
        return "Nayuki";
    case 11:
        return "Mio";
    case 12:
        return "ExNanase";
    case 13:
        return "Kaori";
    case 14:
        return "Ikumi";
    case 15:
        return "Mishio";
    case 16:
        return "Akiko";
    case 17:
        return "NayukiB";
    case 18:
        return "MizukaB";
    case 19:
        return "Kanna";
    case 20:
        return "Kano";
    case 21:
        return "Minagi";
    case 22:
        return "NayukiA";
    case 23:
        return "Misuzu";
    case 24:
        return "Mizuka";
    default:
        return "error";
    }
}

// 40 colours (120 bytes) from index first of a file's palette, after its first byte.
// FUNCTION: 0x1006dc60
// TODO: differs: index is 0 at both calls; the original still reads it (size - index,
// colors + index), while this build propagates the constant and drops it. The rest
// (call targets aside) is the same.
bool Palettes::readColors(PALETTEENTRY *colors, int first, int index, std::string file)
{
    BYTE rgb[120];
    std::ifstream in;
    in.open(file, std::ios::binary | std::ios::ate);
    if (in.is_open()) {
        unsigned int size = (int)in.tellg();
        if (size - index >= 120) {
            in.seekg(first * 3 + 1);
            in.read((char *)rgb, sizeof(rgb));
            in.close();
            toColors(rgb, colors + index);
            return true;
        }
    }
    in.close();
    return false;
}

// FUNCTION: 0x1006dd70
// TODO: differs: as in loadDat, the original pushes readColors' index (0) where this
// build pushes a dummy ecx.
bool Palettes::loadPal(unsigned int character, unsigned int number)
{
    if (!validPalette(character, number))
        return false;
    std::stringstream path;
    path << folderName(character) << "\\" << folderName(character) << number + 1 << ".pal";
    ColorPalette palette;
    if (readColors((PALETTEENTRY *)(palette.data + 4), 0, 0, path.str())) {
        *(int *)palette.data = makePalette(character, true, number).value;
        palettes_[*(int *)palette.data] = palette;
        return true;
    }
    return false;
}

// FUNCTION: 0x1006dec0
void Palettes::loadAll()
{
    for (int character = 0; character <= 24; character++)
        for (int number = 0; number < 6; number++)
            loadPal(character, number);
}

// FUNCTION: 0x1006def0
void Palettes::add(const ColorPalette &palette, bool replace)
{
    palettes_[*(int *)palette.data] = palette;
}

// FUNCTION: 0x1006df30
Palettes::~Palettes()
{
}

// FUNCTION: 0x1006df40 ??0Palettes@@QAE@XZ
Palettes::Palettes()
{
    for (int character = 0; character <= 24; character++)
        for (int number = 0; number < 6; number++)
            loadDat(character, number);
}
