// CMai (0x6163b0-0x62a5df): the character class whose files are in mai\ in the game
// folder (mai.dat sprites, mai.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; the VfN methods override
// the CPlayer virtual slots of the same number (see shiori.cpp for what they do).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMai::CMai(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy((char*)this + 0x94, "mai");
    *(short*)((char*)this + 0x18) = 0x3a0;
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(short*)((char*)this + 0x2ad0) = -0x14;
    *(short*)((char*)this + 0x2af8) = -0x3a;
    *(short*)((char*)this + 0x2ad2) = -0x18;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 4;
    *(short*)((char*)this + 0x2afc) = -8;
    *(short*)((char*)this + 0x2ad6) = 7;
    *(short*)((char*)this + 0x2afe) = -0xc;
    *(short*)((char*)this + 0x2ad8) = 0x1e;
    *(short*)((char*)this + 0x2b00) = -0x16;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    *((char*)this + 0x30f4) = 3;
    *((char*)this + 0x30f5) = 0;
    *((char*)this + 0x30f6) = 1;
    *((char*)this + 0x30f7) = 9;
    *((char*)this + 0x30f8) = 2;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3358) = 0;
    }
}

void CMai::Vf12()
{
    int v4;

    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(short*)((char*)this + 0x2ad0) = -0x17;
    *(short*)((char*)this + 0x2af8) = -0x3a;
    *(short*)((char*)this + 0x2ad2) = -0x18;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 4;
    *(short*)((char*)this + 0x2afc) = -8;
    *(short*)((char*)this + 0x2ad6) = 7;
    *(short*)((char*)this + 0x2afe) = -0xc;
    *(short*)((char*)this + 0x2ad8) = 0x1e;
    *(short*)((char*)this + 0x2b00) = -0x16;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3358) = 0;
    }
    CPlayer::Vf12();
}

void CMai::Vf0()
{
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    CPlayer::Vf0();
}

void CMai::Vf10(short p1)
{
    *(int*)((char*)this + p1 * 4 + 0x3158) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3258) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3358) = 0;
    CPlayer::Vf10(p1);
}

void CMai::Vf3()
{
    CPlayer::Unk40e740();
}

void CMai::Vf4()
{
    if (*(WORD*)((char*)this + 8) < 0xc8) {
        *((char*)this + 0x1a8) = 0;
    }
    if (*(BYTE*)((char*)this + 0x1aa) <= 0) {
        *((char*)this + 0x1a9) = 0;
    } else {
        (*((char*)this + 0x1aa))--;
    }
    if (*(BYTE*)((char*)this + 0x1a9) == 0) {
        *((char*)this + 0x1aa) = 0;
    }
    if (*(short*)((char*)this + 0x262) == 0x34 && (*(double*)((char*)this + 0x118) >= 500.0 && *(int*)((char*)this + 0x168) > 1 && *(int*)((char*)this + 0x168) != 6 || *((char*)this + 0x120) > 0 && *(int*)((char*)this + 0x168) > 1) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x538)) {
        Vf0();
        CPlayer::Unk40f170();
        *(short*)((char*)this + 8) = 0xa7;
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(short*)((char*)this + 8) = 0xab;
        }
        return;
    }
    if (*(int*)((char*)this + 0x15c) < 2) {
        if (*(int*)((char*)this + 0x3148) > 0 && *(int*)((char*)this + 0x108) < 0xd05 && *(short*)((char*)this + 0x262) == 0x67 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 4 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0xa20)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x144;
            return;
        }
        if (*(int*)((char*)this + 0x108) < 0xd05 && *(short*)((char*)this + 0x262) == 0x67 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x135;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x70 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(int*)((char*)this + 0x3144) == 0 || *(int*)((char*)this + 0x3144) == 1) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0xa10)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x142;
            if (*(int*)((char*)this + 0x3144) == 1) {
                *(short*)((char*)this + 8) = 0x143;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(int*)((char*)this + 0x3144) == 0 || *(int*)((char*)this + 0x3144) == 1) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0xa00) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x140;
            if (*(int*)((char*)this + 0x3144) == 1) {
                *(short*)((char*)this + 8) = 0x141;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6e || *(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(int*)((char*)this + 0x3144) == 0 || *(int*)((char*)this + 0x3144) == 1) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9f0) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13e;
            if (*(int*)((char*)this + 0x3144) == 1) {
                *(short*)((char*)this + 8) = 0x13f;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x66 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x988) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x131;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x980) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x130;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x64 || *(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x978) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12f;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x16 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x860) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10c;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x15 || *(short*)((char*)this + 0x262) == 0x16) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x858) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10b;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x14 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x850) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10a;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x16 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0 || *(int*)((char*)this + 0x3144) == 4) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) < 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7e0) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfc;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x15 || *(short*)((char*)this + 0x262) == 0x16) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) < 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d8) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfb;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x14 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) < 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfa;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x20 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(int*)((char*)this + 0x3144) == 0 || *(int*)((char*)this + 0x3144) == 4) && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x818) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x103;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x1f || *(short*)((char*)this + 0x262) == 0x20) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(int*)((char*)this + 0x3144) == 0 || *(int*)((char*)this + 0x3144) == 4) && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x810) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x102;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x1e && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(int*)((char*)this + 0x3144) == 0 || *(int*)((char*)this + 0x3144) == 4) && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x808) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x101;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xc && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x848) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x109;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0xc || *(short*)((char*)this + 0x262) == 0xb) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x840) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x108;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x838) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x107;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x2a && (*(int*)((char*)this + 0x3144) == 4 || *(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x800) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x100;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x29 || *(short*)((char*)this + 0x262) == 0x2a) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f8) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xff;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x28 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f0) || *(WORD*)((char*)this + 8) == 0xd4) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfe;
            return;
        }
    }
    if (*(int*)((char*)this + 0x15c) < 3 && *(short*)((char*)this + 0x262) == 6 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) < 0.0 && *(BYTE*)((char*)this + 0x15a) < 1 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x70) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
        Vf0();
        CPlayer::Unk40f170();
        (*((char*)this + 0x15a))++;
        *(short*)((char*)this + 8) = 0xe;
        if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
            *(short*)((char*)this + 8) = 0xf;
        }
        if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
            *(short*)((char*)this + 8) = 0x10;
        }
        return;
    }
    if (*(int*)((char*)this + 0x15c) < 1 && (*(short*)((char*)this + 0x262) == 0 || *(short*)((char*)this + 0x262) == 1)) {
        if (*(double*)((char*)this + 0x28) < 0.0 && *(BYTE*)((char*)this + 0x159) < 1) {
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) < 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == (1 - (*(short*)((char*)this + 0x262) << 1)) * -1) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x528) && *(WORD*)((char*)this + 8) != 0xaa && *(double*)((char*)this + 0x28) < -30.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                if (*(WORD*)((char*)this + 8) != 0xa5) {
                    Vf0();
                }
                *(short*)((char*)this + 8) = 0xa5;
                CPlayer::Unk40e630();
                (*((char*)this + 0x159))++;
                (*((char*)this + 0x15a))++;
                *((char*)this + 0x1a8) = 0;
                return;
            }
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) > 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == 1 - (*(short*)((char*)this + 0x262) << 1)) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x530) && *(WORD*)((char*)this + 8) != 0xaa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                if (*(WORD*)((char*)this + 8) != 0xa6) {
                    Vf0();
                }
                *(short*)((char*)this + 8) = 0xa6;
                CPlayer::Unk40e630();
                (*((char*)this + 0x159))++;
                (*((char*)this + 0x15a))++;
                *((char*)this + 0x1a8) = 0;
                return;
            }
        }
        if (*(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0) {
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) < 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == (1 - (*(short*)((char*)this + 0x262) << 1)) * -1) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x518) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                if (*(WORD*)((char*)this + 8) != 0xa3) {
                    Vf0();
                }
                *(short*)((char*)this + 8) = 0xa3;
                CPlayer::Unk40e630();
                (*((char*)this + 0x158))++;
                *((char*)this + 0x1a8) = 0;
                return;
            }
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) > 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == 1 - (*(short*)((char*)this + 0x262) << 1)) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x520) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                if (*(WORD*)((char*)this + 8) != 0xa4) {
                    Vf0();
                }
                *(short*)((char*)this + 8) = 0xa4;
                CPlayer::Unk40e630();
                (*((char*)this + 0x158))++;
                *((char*)this + 0x1a8) = 0;
                return;
            }
        }
    }
    if (*((char*)this + 0x18a) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x10) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x10) != 0) {
        if (*(double*)((char*)this + 0x28) < 0.0) {
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x678) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xcf;
            }
            return;
        }
        if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x660) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xcc;
            return;
        }
        if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
            if (*(int*)((char*)this + 0x3144) == 4 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6a8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd5;
                return;
            }
            if (*(WORD*)((char*)this + 8) != 0xd4 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x690) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd2;
                if (*(int*)((char*)this + 0x3144) == 4) {
                    *(short*)((char*)this + 8) = 0xd5;
                }
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x640) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xc8;
                return;
            }
        }
    }
    if (*((char*)this + 0x18b) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x20) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x20) != 0) {
        if (*(double*)((char*)this + 0x28) < 0.0) {
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x680) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd0;
            }
            return;
        }
        if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x668) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xcd;
            return;
        }
        if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
            if (*(int*)((char*)this + 0x3144) == 4 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6b0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd6;
                return;
            }
            if (*(WORD*)((char*)this + 8) != 0xd4 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x698) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd3;
                if (*(int*)((char*)this + 0x3144) == 4) {
                    *(short*)((char*)this + 8) = 0xd6;
                }
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x648) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -70.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 70.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xc9;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x650) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xca;
                return;
            }
        }
    }
    if (*((char*)this + 0x18c) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x40) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x40) != 0) {
        if (*(double*)((char*)this + 0x28) < -10.0 && *(WORD*)((char*)this + 8) == 0xa3) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xe8;
            return;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            if (*((char*)this + 0x188) == *((char*)this + 0x50) && *((char*)this + 0x189) == 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -100.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 100.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x780) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xf0;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x688) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd1;
            }
            return;
        }
        if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x670) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xce;
            return;
        }
        if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6c0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *((char*)this + 0x188) == *((char*)this + 0x50)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xd8;
            return;
        }
        if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
            if (*((char*)this + 0x188) != 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -30.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 30.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6e0) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xdc;
                return;
            }
            if (*(int*)((char*)this + 0x3144) == 4 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6b8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd7;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6a0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd4;
                if (*(int*)((char*)this + 0x3144) == 4) {
                    *(short*)((char*)this + 8) = 0xd7;
                }
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6c0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == -*((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd8;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x658) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xcb;
                return;
            }
        }
    }
    if (*(int*)((char*)this + 0x15c) < 2 && *((char*)this + 0x189) == 0 && *((char*)this + 0x18d) == 1) {
        if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x820) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x104;
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                *(int*)((char*)this + 0x3140) = 1;
            }
            if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                *(int*)((char*)this + 0x3140) = 2;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x63 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x868) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x3144) == 1 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10d;
        }
    }
}

void CMai::Vf1()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (*(int*)((char*)this + 0x3148) > 0 && *(int*)((char*)this + 0x3144) != 3) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x14c);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3144) == 3) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x154);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3148) > 0 && *(int*)((char*)this + 0x3144) != 3) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x15c);
        v2c = MakeRect(0, 0, x1c.width * *(int*)((char*)this + 0x3148) / 0x2710, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, *(int*)((char*)this + 0x3148) * x1c.width / 0x2710, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - *(int*)((char*)this + 0x3148) * x1c.width / 0x2710, 0x1f - x1c.y, *(int*)((char*)this + 0x3148) * x1c.width / 0x2710, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3144) == 3) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x164);
        v2c = MakeRect(0, 0, *(int*)((char*)this + 0x3148) * x1c.width / 0x4b0, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, *(int*)((char*)this + 0x3148) * x1c.width / 0x4b0, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - *(int*)((char*)this + 0x3148) * x1c.width / 0x4b0, 0x1f - x1c.y, *(int*)((char*)this + 0x3148) * x1c.width / 0x4b0, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
}

void CMai::Vf8()
{
    EffectDesc v48;
    CPlayer::Unk413090((EffectDesc*)&v48);
    if (*(int*)((char*)this + 0x3148) > 0) {
        (*(int*)((char*)this + 0x3148))--;
        if (*(int*)((char*)this + 0x3144) == 3) {
            (*(int*)((char*)this + 0x3148))--;
        }
        if (*(int*)((char*)this + 0x3150) == 1) {
            *(int*)((char*)this + 0x3148) -= 4;
        }
        if (*(int*)((char*)this + 0x3150) == 2) {
            (*(int*)((char*)this + 0x3148))++;
        }
        if (*(int*)((char*)this + 0x3150) == 3) {
            (*(int*)((char*)this + 0x3148))--;
        }
        if (*(int*)((char*)this + 0x3150) == 4) {
            (*(int*)((char*)this + 0x3148))--;
        }
    }
    if (*(int*)((char*)this + 0x3144) == 4) {
        *(short*)((char*)this + 0x148) = 0;
        ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(3);
    }
    if (*(int*)((char*)this + 0x3148) <= 0) {
        if (*(int*)((char*)this + 0x3144) == 3) {
            v48.type = 1;
            v48.unk2c = 0xb;
            v48.x = (double)(int)*(double*)((char*)this + 0x20);
            v48.y = (double)(int)(*(double*)((char*)this + 0x28) - 40.0);
            v48.unk20 = 2;
            v48.unk21 = 1;
            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&v48);
            *(int*)((char*)this + 0x3144) = 0;
            *(int*)((char*)this + 0x3148) = 0;
            *(int*)((char*)this + 0x314c) = 0;
            *(int*)((char*)this + 0x3150) = 0;
        }
        if (*(int*)((char*)this + 0x3144) == 4 && *(WORD*)((char*)this + 8) != 0x144 && *(WORD*)((char*)this + 8) != 0x145) {
            *(int*)((char*)this + 0x3148) = 0x4b0;
            *(int*)((char*)this + 0x3144) = 3;
            *(int*)((char*)this + 0x314c) = 0;
            *(int*)((char*)this + 0x3150) = 2;
        }
    }
}

void CMai::Vf9(EffectDesc* p1)
{
    Vf10(*(short*)((char*)this + 0x2ca));
    CPlayer::Vf9(p1);
}

void CMai::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    *(short*)((char*)this + 0x262) = 0x63;
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x6e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x6e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x64 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x64 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x78;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x14 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x14 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x28 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x28 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x1e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x1e + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0xa + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0xaf;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 8) != 0 && x6 == 1) {
            *(short*)((char*)this + 0x262) = 6;
            return;
        }
        if ((v5 & 8) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x80) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = 0x35;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x40) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = 0x34;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x20) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = 0x33;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x10) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = 0x32;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf) == 1 && x6 == 3) {
            *(short*)((char*)this + 0x262) = 1;
            return;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf) == 2 && x6 == 3) {
            *(short*)((char*)this + 0x262) = 0;
            break;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 2 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
}

void CMai::Vf5()
{
    double v10;
    double x8;

    *(short*)((char*)this + 0x262) = 0x63;
    if (*(int*)((char*)this + 0x1a0) > 0) {
        (*(int*)((char*)this + 0x1a0))--;
    }
    if (*(int*)((char*)this + 0x1a4) > 0) {
        (*(int*)((char*)this + 0x1a4))--;
    }
    *((char*)this + 0x188) = 0;
    *((char*)this + 0x189) = 0;
    *((char*)this + 0x18a) = 0;
    *((char*)this + 0x18b) = 0;
    *((char*)this + 0x18c) = 0;
    *((char*)this + 0x18d) = 0;
    *(short*)((char*)this + 0x14e) = 0;
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 25.0f * *(float*)((char*)this + 0xa8) + (*(double*)((char*)this + 0x28) < 0.0) * 0x1e * *(float*)((char*)this + 0xa8) + (*(int*)((char*)this + 0x3114) == 3) * 0x190 + (*(WORD*)((char*)this + 8) == 0xaa) * 0x12c) {
        *(short*)((char*)this + 0x14e) = 0x3c;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x7d0) < ((*((char*)this + 0x130) > 0) * 4.0 + 1.0) * 8.0 * *(float*)((char*)this + 0xa8) * ((*(WORD*)((char*)this + 8) > 0x95 && *(WORD*)((char*)this + 8) < 0x9d) * 2 + 1)) {
        *(short*)((char*)this + 0x14e) = 0x3c;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 4e+01f * *(float*)((char*)this + 0xa8) && *(WORD*)((char*)this + 8) > 0xc7) {
        *(short*)((char*)this + 0x14e) = 0x3c;
    }
    if (*(int*)((char*)this + 0x170) == 1 && *(int*)((char*)this + 0x3114) == 2) {
        *(short*)((char*)this + 0x14e) = 0x1e;
        if (*(WORD*)((char*)this + 8) < 0xc8) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0x60) {
        return;
    }
    v10 = (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * *((char*)this + 0x50);
    x8 = fabs(*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28));
    if (*(WORD*)((char*)this + 8) >= 0x32 && *(WORD*)((char*)this + 8) <= 0x96 && *(WORD*)((char*)this + 0xc) == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8)) {
            *(int*)((char*)this + 0x3114) = 3;
        } else {
            *(int*)((char*)this + 0x3114) = 0;
        }
        *((char*)this + 0x188) = 1 - (((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32) << 1);
        *((char*)this + 0x18d) = (WORD)CPlayer::Unk4108a0(0, 0xf0) < x8;
        *((char*)this + 0x18d) = (WORD)CPlayer::Unk4108a0(0, 0x140) < v10;
        if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 0xa) < 3 && x8 < 100.0 && v10 < 150.0) {
            *((char*)this + 0x18d) = 0;
        }
        return;
    }
    if ((*(WORD*)((char*)this + 8) >= 4 && *(WORD*)((char*)this + 8) <= 6 || *(WORD*)((char*)this + 8) >= 0xa && *(WORD*)((char*)this + 8) <= 0xc) && *(double*)((char*)this + 0x28) == 0.0) {
        return;
    }
    if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) >= 0x32 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x96 && *(WORD*)((char*)this + 8) == 0x108 && *(short*)((char*)this + 0x16c) > 1) {
        return;
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 && *(WORD*)((char*)this + 0xc) < 6) {
        if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0xc8 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0xcc && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0) {
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
        }
        if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xc9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xca || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xcd) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0) {
            if (v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x2a;
                return;
            }
            if (v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 || *(WORD*)((char*)this + 8) == 0xa9) {
        if (v10 < 120.0) {
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = 0x6e;
                return;
            }
            if (v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x2a;
                return;
            }
            if (v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                return;
            }
        }
        if (v10 < 160.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = 0x6e;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x2a;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x20;
                return;
            }
        }
        if (v10 < 220.0 && v10 > 160.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2 && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x66;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
                *(short*)((char*)this + 0x262) = 0x28;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x28) == 0.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x28) == 0.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                return;
            }
        }
        if (v10 > 220.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
            *(short*)((char*)this + 0x262) = 0x28;
            return;
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xaa && *(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *(int*)((char*)this + 0x3114) = 3;
            return;
        }
        if (x8 < 70.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
        if (x8 < 60.0 && v10 < 70.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *(short*)((char*)this + 0x262) = 0x14;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -60.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18a) = 1;
            return;
        }
        if (x8 < 40.0 && v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18b) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -60.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18c) = 1;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 3 && *(double*)((char*)this + 0x118) > 500.0 && v10 < 90.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
            *(short*)((char*)this + 0x262) = 0x48;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 7 && *(double*)((char*)this + 0x118) > 500.0 && v10 < 70.0) {
            *(short*)((char*)this + 0x262) = 0x20;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 < 140.0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x12 && *(int*)((char*)this + 0x3110) > 0x16 && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 < 100.0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x1e) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 0x1e) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
        if (v10 < 100.0 && *(int*)((char*)this + 0x3110) < 0x16 && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
        if (v10 < 100.0 && *(int*)((char*)this + 0x3110) < 0x2a) {
            *(short*)((char*)this + 0x262) = 0x14;
            return;
        }
    }
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d && (*(WORD*)((char*)this + 8) == 0xfa || *(WORD*)((char*)this + 8) == 0xfb || *(WORD*)((char*)this + 8) == 0xfc || *(WORD*)((char*)this + 8) == 0x100 || *(WORD*)((char*)this + 8) == 0x12f || *(WORD*)((char*)this + 8) == 0x130 || *(WORD*)((char*)this + 8) == 0x131)) {
        *(short*)((char*)this + 0x262) = 0x34;
        return;
    }
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 1.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x168) == 3 && (*(WORD*)((char*)this + 8) == 0x100 || *(WORD*)((char*)this + 8) == 0xd4 && v10 < 60.0)) {
        *(short*)((char*)this + 0x262) = 0x34;
        return;
    }
    if ((*(WORD*)((char*)this + 8) == 0xfe || *(WORD*)((char*)this + 8) == 0xff) && *(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 5.0f * *(float*)((char*)this + 0xa8)) {
        *((char*)this + 0x18d) = 1;
        *((char*)this + 0x188) = *((char*)this + 0x50);
        return;
    }
    if (*(WORD*)((char*)this + 8) == 0x60 && v10 < 120.0 && *(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 5.0f * *(float*)((char*)this + 0xa8)) {
        *((char*)this + 0x18d) = 1;
        *((char*)this + 0x188) = *((char*)this + 0x50);
        return;
    }
    if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x3a && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d && *(int*)((char*)this + 0x314c) == 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 5.0f * *(float*)((char*)this + 0xa8)) {
        *((char*)this + 0x18d) = 1;
        *((char*)this + 0x188) = 0;
        *((char*)this + 0x189) = 0;
        return;
    }
    if (*(int*)((char*)this + 0x3114) > 0 && *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x9e) {
        *(int*)((char*)this + 0x3114) = 0;
    }
    if (*(int*)((char*)this + 0x3114) == 1 && *(WORD*)((char*)this + 8) < 0xc8) {
        *(int*)((char*)this + 0x3114) = 0;
    }
    if (*(int*)((char*)this + 0x3114) == 2 && *(int*)((char*)this + 0x170) != 1) {
        *(int*)((char*)this + 0x3114) = 0;
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 4) {
        *((char*)this + 0x189) = -1;
        *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
        if (*(WORD*)((char*)this + 8) == 4 || *(WORD*)((char*)this + 8) == 5 || *(WORD*)((char*)this + 8) == 6) {
            *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
            if (*(WORD*)((char*)this + 8) == 0xa5) {
                *(int*)((char*)this + 0x3114) = 0;
            }
            *((char*)this + 0x189) = 0;
            *((char*)this + 0x188) = 0;
            return;
        }
    }
    if (*(int*)((char*)this + 0x3114) == 5 && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 6) {
        if (*(double*)((char*)this + 0x28) == 0.0) {
            *((char*)this + 0x189) = -1;
            *((char*)this + 0x188) = *((char*)this + 0x50);
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(short*)((char*)this + 0x262) = 0x14;
        }
        if (*(WORD*)((char*)this + 8) == 0xfa) {
            *(int*)((char*)this + 0x3114) = 0;
            if (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x188) = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * *((char*)this + 0x50);
            }
        }
        return;
    }
    if (*(int*)((char*)this + 0x168) > 1 && *(short*)((char*)this + 0x14a) == 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 25.0f && *(int*)((char*)this + 0x3114) != 1 && *(int*)((char*)this + 0x3114) != 2) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (*(WORD*)((char*)this + 8) == 0xc8) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (v10 < 160.0 && *(int*)((char*)this + 0x3110) < 0xa) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 125.0 && *(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1b8) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384 - (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 0) * 0xc8) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb - (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) * 0x12c) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xc9) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                return;
            }
            if (v10 < 50.0 && *(int*)((char*)this + 0x168) == 2 && *(int*)((char*)this + 0x3110) < 0x96 && (WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                *(int*)((char*)this + 0x3114) = 6;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x18a) = 0;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x1f4) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x82 && *(int*)((char*)this + 0x314c) == 0) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x188) = 0;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x82 && *(int*)((char*)this + 0x3110) < 0x190 && v10 < 140.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1cc && v10 < 140.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x23a - (*(int*)((char*)this + 0x314c) == 1) * 0x96 && *(int*)((char*)this + 0x3110) < 0x2a8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                if (*(int*)((char*)this + 0x168) == 3 && *(double*)((char*)this + 0x118) > 500.0) {
                    *(short*)((char*)this + 0x262) = 0x2a;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1cc && *(int*)((char*)this + 0x3110) < 0x230 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && v10 < 100.0 && *(int*)((char*)this + 0x314c) == 0) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384 - (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 0) * 0xc8) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                if (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) {
                    *((char*)this + 0x18d) = 1;
                    *((char*)this + 0x188) = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * *((char*)this + 0x50);
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc - (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 0) * 0xc8) {
                *(int*)((char*)this + 0x3114) = 1;
                if (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) {
                    *((char*)this + 0x18d) = 1;
                    *((char*)this + 0x188) = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * *((char*)this + 0x50);
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xca) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && v10 < 90.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x1f4 && v10 > 150.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x1f4 && *(int*)((char*)this + 0x3110) < 0x258 && *(int*)((char*)this + 0x314c) == 0) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x188) = 0;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x64 && v10 < 110.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x1c2 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x262) = 0x1e;
                if (v10 > 120.0) {
                    *(short*)((char*)this + 0x262) = 0x1f;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x23a && *(int*)((char*)this + 0x3110) < 0x26c) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 1) + 0x28;
                if (*(int*)((char*)this + 0x168) == 3 && *(double*)((char*)this + 0x118) > 500.0) {
                    *(short*)((char*)this + 0x262) = 0x2a;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384 - (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 0) * 0xc8) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                if (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) {
                    *((char*)this + 0x18d) = 1;
                    *((char*)this + 0x188) = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * *((char*)this + 0x50);
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) {
                    *((char*)this + 0x18d) = 1;
                    *((char*)this + 0x188) = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * *((char*)this + 0x50);
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcb) {
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x1f4 && *(int*)((char*)this + 0x314c) == 0) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x188) = 0;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x12c && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1f4 && *(int*)((char*)this + 0x3110) < 0x226 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x262) = 0x1e;
                if (v10 > 120.0) {
                    *(short*)((char*)this + 0x262) = 0x1f;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x28a && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 1) + 0x28;
                if (*(int*)((char*)this + 0x168) == 3 && *(double*)((char*)this + 0x118) > 500.0) {
                    *(short*)((char*)this + 0x262) = 0x2a;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x28a && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                if (*(int*)((char*)this + 0x168) == 3 && *(double*)((char*)this + 0x118) > 500.0) {
                    *(short*)((char*)this + 0x262) = 0x2a;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) {
                    *((char*)this + 0x18d) = 1;
                    *((char*)this + 0x188) = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * *((char*)this + 0x50);
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcc) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && v10 < 50.0) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    *((char*)this + 0x189) = 0;
                    *((char*)this + 0x18a) = 0;
                }
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 50.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384 - (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 0) * 0x64) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                if (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) {
                    *((char*)this + 0x18d) = 1;
                    *((char*)this + 0x188) = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * *((char*)this + 0x50);
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x320) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcd) {
            if (*(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x190 && v10 > 140.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x190 && *(int*)((char*)this + 0x3110) < 0x1f4 && v10 < 100.0) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x226 - (*(int*)((char*)this + 0x314c) == 1) * 0x96 && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                if (*(int*)((char*)this + 0x168) == 3 && *(double*)((char*)this + 0x118) > 500.0) {
                    *(short*)((char*)this + 0x262) = 0x2a;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384 - (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 0) * 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384 - (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 0) * 0xc8) {
                *(int*)((char*)this + 0x3114) = 1;
                if (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) {
                    *((char*)this + 0x18d) = 1;
                    *((char*)this + 0x188) = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) * *((char*)this + 0x50);
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xce) {
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x1f4 && *(int*)((char*)this + 0x314c) == 0) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x188) = 0;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x226 - (*(int*)((char*)this + 0x314c) == 1) * 0x96 && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                if (*(int*)((char*)this + 0x168) == 3 && *(double*)((char*)this + 0x118) > 500.0) {
                    *(short*)((char*)this + 0x262) = 0x2a;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcf) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                return;
            }
            if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                return;
            }
            if (v10 < 125.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb - (*(int*)((char*)this + 0x3144) == 0 && *(int*)((char*)this + 0x314c) == 1) * 0x12c) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 3;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd0) {
            if (*(int*)((char*)this + 0x3110) > 0x50 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 3;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd1) {
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 3;
                return;
            }
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 25.0f * *(float*)((char*)this + 0xa8)) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (*(double*)((char*)this + 0x28) == 0.0) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x63) {
                if (v10 < 40.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(int*)((char*)this + 0x3110) < 3) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x188) = -*((char*)this + 0x50);
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 60.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xa8 && *(int*)((char*)this + 0x3110) < 5) {
                    *(int*)((char*)this + 0x3114) = 6;
                    return;
                }
                if (v10 < 50.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d) * 0x32 + 0x19 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xc8) {
                        *((char*)this + 0x18a) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0xa && *(short*)((char*)this + 0x148) >= 0x3e8 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && *(int*)((char*)this + 0x3110) < 0x14) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 130.0 && v10 > 80.0 && *(int*)((char*)this + 0x3110) < 0x1e && *(int*)((char*)this + 0x3110) > 0xf) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 90.0 && *(int*)((char*)this + 0x3110) < 0x1e && *(int*)((char*)this + 0x3110) > 0x14) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 200.0 && v10 > 160.0 && *(int*)((char*)this + 0x3110) < 0x2d && *(int*)((char*)this + 0x3110) > 0x1e) {
                    *((char*)this + 0x18b) = 1;
                    if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                        *((char*)this + 0x18b) = 0;
                        *((char*)this + 0x18c) = 1;
                    }
                    *((char*)this + 0x189) = 0;
                    *((char*)this + 0x188) = *((char*)this + 0x50);
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) < 0.0) {
                    if (v10 < 80.0 && x8 < 180.0 && x8 > 90.0 && *(int*)((char*)this + 0x3110) < 0x1e) {
                        *((char*)this + 0x189) = -1;
                        *((char*)this + 0x188) = -*((char*)this + 0x50);
                        return;
                    }
                    if (v10 > 130.0 && x8 < 180.0 && x8 > 90.0 && *(int*)((char*)this + 0x3110) > 0x1e && *(int*)((char*)this + 0x3110) < 0x46) {
                        *((char*)this + 0x189) = -1;
                        *((char*)this + 0x188) = -*((char*)this + 0x50);
                        return;
                    }
                    if (v10 < 150.0 && v10 > 60.0 && *(int*)((char*)this + 0x3110) > 0x46 && *(int*)((char*)this + 0x3110) < 0x6e) {
                        *((char*)this + 0x18a) = 1;
                        *((char*)this + 0x188) = *((char*)this + 0x50);
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) > 0.0) {
                    if (v10 < 80.0 && x8 < 180.0 && x8 > 90.0 && *(int*)((char*)this + 0x3110) < 0x1e) {
                        *((char*)this + 0x189) = -1;
                        *((char*)this + 0x188) = -*((char*)this + 0x50);
                        return;
                    }
                    if (v10 > 130.0 && x8 < 180.0 && x8 > 90.0 && *(int*)((char*)this + 0x3110) > 0x1e && *(int*)((char*)this + 0x3110) < 0x46) {
                        *((char*)this + 0x189) = -1;
                        *((char*)this + 0x188) = -*((char*)this + 0x50);
                        return;
                    }
                    if (v10 < 150.0 && v10 > 60.0 && x8 > 130.0 && *(int*)((char*)this + 0x3110) > 0x46 && *(int*)((char*)this + 0x3110) < 0x6e) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                    if (v10 < 100.0 && x8 > 160.0 && x8 < 240.0 && *(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x8c) {
                        *((char*)this + 0x18c) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 < 140.0 && v10 > 90.0 && x8 > 90.0 && *(int*)((char*)this + 0x3110) > 0xa0 && *(int*)((char*)this + 0x3110) < 0xdc) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 < 130.0 && x8 < 80.0 && *(int*)((char*)this + 0x3110) > 0xdc && *(int*)((char*)this + 0x3110) < 0x12c && *(double*)((char*)this + 0x118) > 500.0) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                }
            }
        }
        if (*(double*)((char*)this + 0x28) < 0.0 && *(int*)((char*)this + 0x3114) != 3) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                if (v10 < 100.0 && x8 < 100.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) * 0x64 + 0x64) {
                        *((char*)this + 0x18a) = 1;
                        return;
                    }
                }
                if (v10 < 140.0 && x8 < 80.0 && *(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x104) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 < 140.0 && v10 > 80.0 && x8 > 40.0 && x8 < 80.0 && *(int*)((char*)this + 0x3110) > 0x104 && *(int*)((char*)this + 0x3110) < 0x109) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (v10 < 120.0 && x8 < 90.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) < 0x6e) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 < 140.0 && x8 < 90.0 && *(int*)((char*)this + 0x3110) < 0xd2) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 100.0 && x8 < 90.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) < 0x9c4) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
            }
        }
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b) && *(double*)((char*)this + 0x28) == 0.0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < ((*(int*)((char*)this + 0x3144) == 1 && *(int*)((char*)this + 0x314c) == 1 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b)) * 2 + ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0x63) << 2) + 1) * *(float*)((char*)this + 0xa8) && v10 > 80.0) {
            *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
            return;
        }
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 && v10 > 60.0 && v10 < 140.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2.0f * *(float*)((char*)this + 0xa8) && *(double*)((char*)this + 0x20) > 120.0 && *(double*)((char*)this + 0x20) < 520.0 && *(int*)((char*)this + 0x314c) == 0) {
        *(short*)((char*)this + 0x262) = -((*((char*)this + 0x50) == 1) - 1);
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < (*(int*)((char*)this + 0x314c) == 1) + 2) {
        *(int*)((char*)this + 0x3114) = 4;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8)) {
            *(int*)((char*)this + 0x3114) = 3;
        } else {
            *(int*)((char*)this + 0x3114) = 0;
        }
        if (v10 > 160.0 && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 3) {
            *((char*)this + 0x188) = 0;
            *((char*)this + 0x189) = -1;
            return;
        }
        if (v10 < 100.0 && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xa8) {
            *((char*)this + 0x188) = 0;
            *((char*)this + 0x189) = -1;
            return;
        }
        if (v10 < 170.0 && v10 > 120.0 && *(double*)((char*)this + 0x28) == 0.0) {
            *((char*)this + 0x188) = *((char*)this + 0x50);
            *((char*)this + 0x189) = -1;
            return;
        }
    }
    if (*(int*)((char*)this + 0x1a0) > 0) {
        if ((char)CPlayer::Unk40ff70() != 0 && *(int*)((char*)this + 0x1a0) > 0xf) {
            *(int*)((char*)this + 0x1a0) = 0xf;
        }
        *((char*)this + 0x188) = 1;
        return;
    }
    if (*(int*)((char*)this + 0x1a4) > 0) {
        if ((char)CPlayer::Unk40ff70() != 0 && *(int*)((char*)this + 0x1a4) > 0xf) {
            *(int*)((char*)this + 0x1a4) = 0xf;
        }
        *((char*)this + 0x188) = -1;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x3c && v10 < 150.0) {
        if (*((char*)this + 0x50) == 1) {
            *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
        } else {
            *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28) {
        if (*((char*)this + 0x50) == 1) {
            *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        } else {
            *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        }
        return;
    }
    if (*((char*)this + 0x50) == -1) {
        *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        return;
    }
    *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
}

void CMai::Vf7()
{
    WORD v58;
    WORD v54;
    int v4;

    if (*(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) > 0) {
        return;
    }
    v4 = *(short*)((char*)this + 0x2cc);
    EffectDesc l50;
    while (v4 != *(short*)((char*)this + 0x2ca)) {
        if (*(int*)((char*)this + v4 * 4 + 0x3d0) != 0 && *(short*)((char*)this + v4 * 0x98 + 0x556) == 0 && (*(short*)((char*)this + 0x14c) == 0 || *(short*)((char*)this + 0x14c) > 0 && *(int*)((char*)this + v4 * 0x98 + 0x558) != 0)) {
            v54 = *(short*)(*(char**)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + v4 * 0x98 + 0x4d0) * 8 + 4) + *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) * 0xc);
            v58 = *(BYTE*)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + v4 * 0x98 + 0x4d0) * 8);
            CPlayer::Unk413090((EffectDesc*)&l50);
            switch (*(WORD*)((char*)this + v4 * 0x98 + 0x4d0)) {
            case 0x191:
                *(int*)((char*)this + 0x3144) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 2) {
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) >= 0.1) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.02;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) <= -0.1) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.02;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.1) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.02;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) <= -0.1) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.02;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.1 && *(double*)((char*)this + v4 * 0x98 + 0x4f8) > -0.1) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.1 && *(double*)((char*)this + v4 * 0x98 + 0x500) > -0.1) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    }
                    if (*(int*)((char*)this + 0x3150) == 1) {
                        *(int*)((char*)this + 0x3150) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > -30.0) {
                            l50.type = 0x1f;
                            l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                            l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                            l50.unk20 = 0;
                            l50.unk21 = 0;
                            l50.side = *((char*)this + v4 * 0x98 + 0x518) == -1;
                            ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                        }
                    }
                    if (*(int*)((char*)this + 0x3148) <= 0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x193;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(int*)((char*)this + 0x3148) = 0;
                        *(int*)((char*)this + 0x3144) = 2;
                        break;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                        *((char*)this + v4 * 0x98 + 0x518) = -1;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) <= *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
                        *((char*)this + v4 * 0x98 + 0x518) = 1;
                    }
                    if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                        *(int*)((char*)this + 0x3144) = 2;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        break;
                    }
                    if (*(WORD*)((char*)this + 8) == 0x10d) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x194;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(int*)((char*)this + 0x3148) = 0;
                        break;
                    }
                    if (*(WORD*)((char*)this + 8) == 0x143 && *(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1bf;
                        *(int*)((char*)this + 0x3144) = 2;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        break;
                    }
                    if (*(WORD*)((char*)this + 8) == 0x141 && *(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1bb;
                        *(int*)((char*)this + 0x3144) = 2;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        break;
                    }
                    if (*(WORD*)((char*)this + 8) == 0x13f && *(WORD*)((char*)this + 0xa) == 3 && *(WORD*)((char*)this + 0xc) == 0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1b7;
                        *(int*)((char*)this + 0x3144) = 2;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        break;
                    }
                    if ((*(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x9c) && *(WORD*)((char*)this + 8) != 0xa8 && *(WORD*)((char*)this + 8) != 0xa9 && *(WORD*)((char*)this + 8) != 0xaa && *(WORD*)((char*)this + 8) != 0x104 && *(WORD*)((char*)this + 8) != 0x10d) {
                        if (*(short*)((char*)this + 0x262) == 0x21) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1c3;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                            *(int*)((char*)this + 0x3144) = 2;
                            break;
                        }
                        if (*(short*)((char*)this + 0x262) == 0x2b) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1b4;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                            *(int*)((char*)this + 0x3144) = 2;
                            break;
                        }
                        if (*(short*)((char*)this + 0x262) == 0xd) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1af;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                            *(int*)((char*)this + 0x3144) = 2;
                            break;
                        }
                        if (*(short*)((char*)this + 0x262) == 0x35) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x19e;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                            *(int*)((char*)this + 0x3144) = 2;
                            break;
                        }
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 600.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 40.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 3;
                    }
                }
                break;
            case 0x192:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -2.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x508) = 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) + *(double*)((char*)this + v4 * 0x98 + 0x508);
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x508);
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 1) {
                    Vf10(v4);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 && *(int*)((char*)this + v4 * 4 + 0x3258) < 5) {
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x314c) = 0;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x193:
                *(int*)((char*)this + 0x3144) = 2;
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3150) = 0;
                        *(int*)((char*)this + 0x314c) = 0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x194:
                *(int*)((char*)this + 0x3144) = 2;
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3150) = 1;
                        Vf10(v4);
                    }
                }
                break;
            case 0x196:
                (*(int*)((char*)this + 0x3148))--;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) + *(double*)((char*)this + v4 * 0x98 + 0x508);
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 590.0 && *((char*)this + v4 * 0x98 + 0x518) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 50.0 && *((char*)this + v4 * 0x98 + 0x518) == -1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    if (*(int*)((char*)this + 0x3148) > 1) {
                        *(int*)((char*)this + 0x3148) -= 0x1388;
                    } else {
                        *(int*)((char*)this + 0x3148) = 0;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x508) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x508) = -0.015;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 6;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.9;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = -0.035;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb && *(int*)((char*)this + v4 * 4 + 0x3158) > 0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 7;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))--;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x191;
                        *(int*)((char*)this + 0x3144) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x197:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3258) == 0) {
                    *(int*)((char*)this + 0x3148) = 0;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3258) != 1) {
                    l50.type = 0x198;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1d);
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 49.0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 1;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8 && *(int*)((char*)this + v4 * 4 + 0x3158) < 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x193;
                        *(int*)((char*)this + 0x3144) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                    }
                }
                break;
            case 0x198:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) <= 0) {
                    if (*(int*)((char*)this + v4 * 4 + 0x3258) == 0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3258) < 3 && *(short*)((char*)this + v4 * 0x98 + 0x554) > 0) {
                        *(int*)((char*)this + v4 * 4 + 0x3358) = (int)((ObjBase*)((char*)this + 8))->AngleTo(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8), *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 50.0 - *(double*)((char*)this + v4 * 0x98 + 0x4f0));
                        ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)*(int*)((char*)this + v4 * 4 + 0x3358), -0.00875);
                        *(double*)((char*)this + v4 * 0x98 + 0x508) = *(double*)((char*)this + v4 * 0x98 + 0x4f8);
                        *(double*)((char*)this + v4 * 0x98 + 0x510) = *(double*)((char*)this + v4 * 0x98 + 0x500);
                        ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)*(int*)((char*)this + v4 * 4 + 0x3358), 1.4);
                        if (*((char*)this + v4 * 0x98 + 0x518) == -1) {
                            *(double*)((char*)this + v4 * 0x98 + 0x508) = -*(double*)((char*)this + v4 * 0x98 + 0x508);
                            *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
                        }
                        *(int*)((char*)this + v4 * 4 + 0x3358) = 0xa0;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0xf0;
                    }
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3358) > 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) + *(double*)((char*)this + v4 * 0x98 + 0x508);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                    (*(int*)((char*)this + v4 * 4 + 0x3358))--;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3158))--;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        if ((*(int*)((char*)this + v4 * 4 + 0x3258) > 2 || *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) && *(int*)((char*)this + v4 * 4 + 0x3158) <= 0) {
                            Vf10(v4);
                        }
                    }
                }
                break;
            case 0x199:
                *(int*)((char*)this + 0x3144) = 1;
                if (*(WORD*)((char*)this + 8) == 0x13d) {
                    ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 1;
                    if (*(WORD*)((char*)this + 8) == 0x13b) {
                        *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
                    }
                    if (*(WORD*)((char*)this + 8) == 0x13c) {
                        *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
                    }
                    if (*(WORD*)((char*)this + 8) == 0x13d) {
                        *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
                    }
                    *(int*)((char*)this + 0x3140) = 0;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                    *(short*)((char*)this + 0x14c) = 0x78;
                    CPlayer::Unk410b10(0xb0, 3);
                    l50.type = 9;
                    l50.unk2c = 5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1c);
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 52.0);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *((char*)this + 0x2c9) = 0x25;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 4 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xc && *(short*)((char*)this + 0x14c) == 0) {
                    if (*(int*)((char*)this + v4 * 4 + 0x3358) == 0) {
                        *((char*)this + 0x2c8) = 6;
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3258) >= 0xf) {
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        if (*(WORD*)((char*)this + 8) == 0x13b && *(int*)((char*)this + 0x3140) < 3) {
                            l50.type = 0x19a;
                            l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1d);
                            l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 49.0);
                            l50.unk20 = 2;
                            l50.unk21 = 1;
                            l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                            l50.unk18 = l50.unk18;
                            Vf9(&l50);
                            (*(int*)((char*)this + 0x3140))++;
                        }
                        if (*(WORD*)((char*)this + 8) == 0x13c && *(int*)((char*)this + 0x3140) < 5) {
                            l50.type = 0x1a7;
                            l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1d);
                            l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 49.0);
                            l50.unk20 = 2;
                            l50.unk21 = 1;
                            l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                            l50.unk18 = l50.unk18;
                            Vf9(&l50);
                            (*(int*)((char*)this + 0x3140))++;
                        }
                        if (*(WORD*)((char*)this + 8) == 0x13d && *(int*)((char*)this + 0x3140) < 0xa) {
                            l50.type = 0x1a9;
                            l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1d);
                            l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 49.0);
                            l50.unk20 = 2;
                            l50.unk21 = 1;
                            l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                            l50.unk18 = l50.unk18;
                            Vf9(&l50);
                            (*(int*)((char*)this + 0x3140))++;
                        }
                    }
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc && *(int*)((char*)this + v4 * 4 + 0x3158) < 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x193;
                        *(int*)((char*)this + 0x3144) = 0;
                        *(int*)((char*)this + v4 * 0x98 + 0x558) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x19a:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(int*)((char*)this + 0x3140);
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.045;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x19b;
                    *((char*)this + 0x2c9) = 0x12;
                }
                break;
            case 0x19b:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *((char*)this + 0x2c8) = 7;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19c:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 6;
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0xb4;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 5) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) -= 4;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0xf) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0xf;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 4) {
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity(-60.0, *(int*)((char*)this + v4 * 4 + 0x3258) * 0.01);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 8) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8 && *(int*)((char*)this + v4 * 4 + 0x3158) < 8) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        break;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x314c) = 0;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + 0x3150) = 1;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        Vf10(v4);
                        break;
                    }
                }
                break;
            case 0x19d:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 4;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.6;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 && *(int*)((char*)this + v4 * 4 + 0x3158) < 0x14) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.1;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3158) < 0xe) {
                            (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                            break;
                        }
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x19e;
                        break;
                    }
                }
                break;
            case 0x19e:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 6;
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0xb4;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 1) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) -= 2;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0x1e) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0x1e;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 0) {
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity(-30.0, *(int*)((char*)this + v4 * 4 + 0x3258) * 0.01);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xc) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        break;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x314c) = 0;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        Vf10(v4);
                        break;
                    }
                }
                break;
            case 0x19f:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a0:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a1:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a2:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a3:
                if (*(WORD*)((char*)this + 8) != 0x134) {
                    if (*(int*)((char*)this + v4 * 4 + 0x3158) < 9) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        break;
                    }
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                break;
            case 0x1a4:
                if (*(WORD*)((char*)this + 8) != 0x134) {
                    if (*(int*)((char*)this + v4 * 4 + 0x3158) < 9) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        break;
                    }
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                break;
            case 0x1a5:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.04;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 1 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) >= 0.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 1;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a6:
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.8;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.03;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 1;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 50.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a7:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(int*)((char*)this + 0x3140);
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.045;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *((char*)this + 0x2c9) = 0x12;
                }
                break;
            case 0x1a8:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *((char*)this + 0x2c8) = 7;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a9:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(int*)((char*)this + 0x3140) - (*(int*)((char*)this + 0x3140) > 5) * 5;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.045;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1aa;
                }
                break;
            case 0x1aa:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *((char*)this + 0x2c8) = 7;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ab:
                ((CGame*)*(int*)((char*)this + 0x7c))->Unk4080c0(0xf);
                *(short*)((char*)this + 0x14c) = 2;
                CPlayer::Unk410b10(0xb0, 1);
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > -0.1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3158) < 6) {
                            (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                            break;
                        }
                        *((char*)this + 0x2c8) = 4;
                        l50.type = 1;
                        l50.unk2c = 0;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 40.0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                        *(int*)((char*)this + 0x3148) = 0x2710;
                        *(int*)((char*)this + 0x3144) = 4;
                        *(short*)((char*)this + 0x14c) = 0x3c;
                        CPlayer::Unk410b10(0xb0, 0x14);
                        Vf10(v4);
                        break;
                    }
                }
                break;
            case 0x1ac:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 4;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.7;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.035;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 600.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) == -1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 40.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(int*)((char*)this + v4 * 4 + 0x3158) < 3) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 3) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9 && *(int*)((char*)this + v4 * 4 + 0x3258) < 1) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                        break;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x314c) = 0;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + 0x3150) = 1;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ad:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 4;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.7;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.025;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 600.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) == -1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 40.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(int*)((char*)this + v4 * 4 + 0x3158) < 1) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 3) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3258) < 2) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                            (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                            break;
                        }
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x191;
                        *(int*)((char*)this + 0x3144) = 1;
                        *(int*)((char*)this + 0x3148) = 0x2710;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 3;
                    }
                }
                break;
            case 0x1ae:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x10;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.025;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.4;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 600.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 40.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(int*)((char*)this + v4 * 4 + 0x3158) < 7) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 3) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3258) < 5) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                            (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                            break;
                        }
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x191;
                        *(int*)((char*)this + 0x3144) = 1;
                        *(int*)((char*)this + 0x3148) = 0x2710;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 3;
                    }
                }
                break;
            case 0x1af:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.3;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.025;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 600.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 40.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(int*)((char*)this + v4 * 4 + 0x3158) < 3) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9 && *(int*)((char*)this + v4 * 4 + 0x3258) < 2) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                        break;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 3) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b0:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1c5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x3c);
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 600.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 40.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 && *(int*)((char*)this + v4 * 4 + 0x3158) < 4) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 3;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x191;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + 0x3148) = 0x2710;
                        *(int*)((char*)this + 0x3144) = 1;
                    }
                }
                break;
            case 0x1b1:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b2:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b3:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 5.25;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 3) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.4;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.2) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.2;
                    }
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8) < 120.0 && *((char*)this + v4 * 0x98 + 0x518) == 1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 120.0 && *((char*)this + v4 * 0x98 + 0x518) == -1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 600.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 40.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) < 2) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3150) = 1;
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b4:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1c6;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x24);
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 60.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 600.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 40.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(int*)((char*)this + v4 * 4 + 0x3158) < 3) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3150) = 1;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b5:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 3;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.7;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x28) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x28;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 740.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x28 && *(short*)((char*)this + v4 * 0x98 + 0x554) > 1) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x12;
                        (*(short*)((char*)this + v4 * 0x98 + 0x554))--;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b6:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -1.5;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.03;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b8;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1c);
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 57.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xa) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b7:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + 0x14c) = 0x78;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x3e8;
                    CPlayer::Unk410b10(0xb0, 3);
                    l50.type = 0x44;
                    l50.unk2c = 0x13;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 0x32);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 0x78;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1c);
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 57.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3258) < 1) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 5;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xa) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b8:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 5;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.8;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x15) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x15;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 740.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x15) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b9:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.035;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 1.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.0;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xb) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 740.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ba:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -1.5;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.03;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1bc;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1c);
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 57.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xa) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1bb:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + 0x14c) = 0x78;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0x7d0;
                    CPlayer::Unk410b10(0xb0, 3);
                    l50.type = 0x45;
                    l50.unk2c = 5;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 0x32);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 0x78;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1c);
                    if (*(int*)((char*)this + v4 * 4 + 0x3258) == 0) {
                        l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 27.0);
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3258) == 1) {
                        l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 87.0);
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3258) == 2) {
                        l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 27.0);
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3258) == 3) {
                        l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 87.0);
                    }
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3258) < 3) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 5;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xa) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1bc:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 7;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.5;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 740.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                }
                break;
            case 0x1bd:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 2;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.3;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xb) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 740.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1be:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -1.5;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.03;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1c0;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1c);
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 57.0);
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xa) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1bf:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + 0x14c) = 0x78;
                    *(short*)((char*)this + 0x148) = *(short*)((char*)this + 0x148) - 0xbb8;
                    CPlayer::Unk410b10(0xb0, 3);
                    l50.type = 0x46;
                    l50.unk2c = 0x40;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 0x32);
                    l50.unk20 = 2;
                    l50.unk0 = 1;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 0x78;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x1c);
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 107.0 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3258) < 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 5;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xa) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c0:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0xa;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.2;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 740.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                }
                break;
            case 0x1c1:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 3;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.9;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 0 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xb) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 740.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c2:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c3:
                *(int*)((char*)this + 0x3144) = 2;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x192;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 3) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.15;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.2) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.2;
                    }
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + v4 * 0x98 + 0x4e8) < 120.0 && *((char*)this + v4 * 0x98 + 0x518) == 1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 120.0 && *((char*)this + v4 * 0x98 + 0x518) == -1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 600.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 40.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) < 2) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(int*)((char*)this + 0x3144) = 3;
                        *(int*)((char*)this + 0x3150) = 4;
                        *(int*)((char*)this + 0x3148) = 0x4b0;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c5:
                if ((*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + 0x3144) == 3) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0x1e) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x1e;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 2;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x12) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c6:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ef:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -0.02;
                *(int*)((char*)this + v4 * 0x98 + 0x55c) = 0x7530;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + 8) != 0x57) {
                    Vf10(v4);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1f0:
                if (*(WORD*)((char*)this + 8) != 0x53 && *(WORD*)((char*)this + 8) != 0x54 && *(WORD*)((char*)this + 8) != 0x55 && *(WORD*)((char*)this + 8) != 0x56 || *(WORD*)((char*)this + 8) == 0x53 && *(WORD*)((char*)this + 0xa) > 1 || *(WORD*)((char*)this + 8) == 0x54 && *(WORD*)((char*)this + 0xa) > 1) {
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x17);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 4);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - (*((char*)this + 0x50) << 2));
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 6);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0xe);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x1a);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)(int)*(double*)((char*)this + 0x20);
                    l50.y = (double)(int)*(double*)((char*)this + 0x28);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 0x1e);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x28);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x19);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x23);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x2a);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x12);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x14);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + *((char*)this + 0x50) * 2);
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x41);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + (*((char*)this + 0x50) << 4));
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    *((char*)this + 0x2c9) = 0x22;
                    Vf10(v4);
                    *(int*)((char*)this + 0x3154) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1f1:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x3258))--;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1f2:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.03;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x3258))--;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1f3:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
            }
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}
