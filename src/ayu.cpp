// CAyu (0x6e8130-0x6f2f1f): the character class whose files are in ayu\ in the game
// folder (ayu.dat sprites, ayu.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; the VfN methods override
// the CPlayer virtual slots of the same number (see shiori.cpp for what they do).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CAyu::CAyu(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy((char*)this + 0x94, "ayu");
    *(short*)((char*)this + 0x18) = 0x2ca;
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(short*)((char*)this + 0x2ad0) = -0x11;
    *(short*)((char*)this + 0x2af8) = -0x33;
    *(short*)((char*)this + 0x2ad2) = 0xd;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0xc;
    *(short*)((char*)this + 0x2afc) = -0xe;
    *(short*)((char*)this + 0x2ad6) = 0x16;
    *(short*)((char*)this + 0x2afe) = -0x13;
    *(short*)((char*)this + 0x2ad8) = 0x1b;
    *(short*)((char*)this + 0x2b00) = -0x29;
    *((char*)this + 0x30f4) = 4;
    *((char*)this + 0x30f5) = 1;
    *((char*)this + 0x30f7) = 2;
    *((char*)this + 0x30f8) = 3;
    *((char*)this + 0x30f9) = 4;
    *((char*)this + 0x30fa) = 0xa;
    *((char*)this + 0x30fb) = 0x10;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3150) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3250) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3350) = 0;
    }
}

void CAyu::Vf12()
{
    int v4;

    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(short*)((char*)this + 0x2ad0) = -0x11;
    *(short*)((char*)this + 0x2af8) = -0x33;
    *(short*)((char*)this + 0x2ad2) = 0xd;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0xc;
    *(short*)((char*)this + 0x2afc) = -0xe;
    *(short*)((char*)this + 0x2ad6) = 0x16;
    *(short*)((char*)this + 0x2afe) = -0x13;
    *(short*)((char*)this + 0x2ad8) = 0x1b;
    *(short*)((char*)this + 0x2b00) = -0x29;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3150) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3250) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3350) = 0;
    }
    CPlayer::Vf12();
}

void CAyu::Vf0()
{
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    CPlayer::Vf0();
}

void CAyu::Vf10(short p1)
{
    *(int*)((char*)this + p1 * 4 + 0x3150) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3250) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3350) = 0;
    CPlayer::Vf10(p1);
}

void CAyu::Vf3()
{
    CPlayer::Unk40e740();
}

void CAyu::Vf4()
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
        if (*(int*)((char*)this + 0x108) < 0xd05 && *(short*)((char*)this + 0x262) == 0x5d && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x168) != 6 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9f0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13e;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x7a && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x134;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x79 || *(short*)((char*)this + 0x262) == 0x7a) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x998)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x133;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x78 || *(short*)((char*)this + 0x262) == 0x79 || *(short*)((char*)this + 0x262) == 0x7a) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x990)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x132;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x70 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x970)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12e;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x131;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x968)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12d;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x130;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6e || *(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x960)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12c;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x12f;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x66 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9e8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13d;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9e0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13c;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x64 || *(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9d8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13b;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x78 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x990)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x132;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x16 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfb;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x10b;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x15 || *(short*)((char*)this + 0x262) == 0x16) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7e0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfc;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x14 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfa;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x20 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x810)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x102;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x1f || *(short*)((char*)this + 0x262) == 0x20) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x808)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x101;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x1e && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x800)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x100;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xc && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x830)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x106;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0xb || *(short*)((char*)this + 0x262) == 0xc) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x828)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x105;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x820)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x104;
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
        if (*(double*)((char*)this + 0x28) < 0.0 && *(BYTE*)((char*)this + 0x159) < 2) {
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) < 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == (1 - (*(short*)((char*)this + 0x262) << 1)) * -1) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x528) && *(WORD*)((char*)this + 8) != 0xaa && *(double*)((char*)this + 0x28) < -40.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
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
        if ((*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x640) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xc8;
            return;
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
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x690) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd2;
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
        if (*(double*)((char*)this + 0x28) < 0.0) {
            if (*((char*)this + 0x188) == *((char*)this + 0x50) && *((char*)this + 0x189) == 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -100.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 100.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x780) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xf0;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6a0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x189) == 1 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd4;
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
        if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
            if (*((char*)this + 0x188) != 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -30.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 30.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6e0) && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xdc;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x698) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd3;
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
    if (*(int*)((char*)this + 0x15c) < 1 && (*((char*)this + 0x18d) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x80) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x80) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x140) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) < 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
        Vf0();
        CPlayer::Unk40f170();
        *(short*)((char*)this + 8) = 0x28;
    }
}

void CAyu::Vf1()
{
}

void CAyu::Vf8()
{
}

void CAyu::Vf9(EffectDesc* p1)
{
    Vf10(*(short*)((char*)this + 0x2ca));
    CPlayer::Vf9(p1);
}

void CAyu::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    *(short*)((char*)this + 0x262) = 0x63;
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x2d;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x40) != 0 && x6 == 5) {
            *(short*)((char*)this + 0x262) = 0x5d;
            return;
        }
        if ((v5 & 0x20) != 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xd0) != 0 && x6 == 4) {
            break;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xe0) != 0 && x6 == 2) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 2) {
            x6 = 3;
        }
        if (v5 == 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xe0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 0 && *(short*)((char*)this + 0x148) == 0xbb8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x69;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 4) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x78 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 3) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x78 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 4;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
            x6 = 1;
        }
    }
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
        if ((v5 & 0xf) == 4 && x6 == 0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
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
        if ((v5 & 0xf) == 0 && x6 == 0 && *(WORD*)((char*)this + 8) == 0x60) {
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

void CAyu::Vf5()
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x7d0) < ((*((char*)this + 0x130) > 0) * 4.0 + 1.0) * 8.0 * *(float*)((char*)this + 0xa8) * ((*(WORD*)((char*)this + 8) > 0x95 && *(WORD*)((char*)this + 8) < 0x9d) * 0x7d0 + 1)) {
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
            if (v10 < 40.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
        }
        if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xc9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xca || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xcd) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0) {
            if (v10 > 40.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (v10 > 80.0 && v10 < 140.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18a) = 2;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 || *(WORD*)((char*)this + 8) == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x20;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f + ((*(double*)((char*)this + 0x118) > 500.0) << 1)) {
                *(short*)((char*)this + 0x262) = 0x16;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 4.0f && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x78;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5d;
                return;
            }
        }
        if (v10 < 160.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0xc;
            return;
        }
        if (v10 < 220.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2 && *(short*)((char*)this + 0x148) >= 0x7d0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 1) + 0x65;
            return;
        }
        if (v10 < 220.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xaa && *(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *(int*)((char*)this + 0x3114) = 3;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > 0.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 40.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18a) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -30.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18b) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -80.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 30.0 && x8 > 30.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18c) = 1;
            *((char*)this + 0x189) = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 4 && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x20;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0xa && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x14;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0xd && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x3e8) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) * 0x78;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x10 && *(int*)((char*)this + 0x3110) > 0x12 && *(short*)((char*)this + 0x148) == 0xbb8) {
            *(short*)((char*)this + 0x262) = 0x5d;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 0x14) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
        if (v10 < 100.0 && *(int*)((char*)this + 0x3110) < 0x16) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
    }
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d && (*(WORD*)((char*)this + 8) == 0xfa || *(WORD*)((char*)this + 8) == 0xfb || *(WORD*)((char*)this + 8) == 0x104 || *(WORD*)((char*)this + 8) == 0x105 || *(WORD*)((char*)this + 8) == 0x106 || *(WORD*)((char*)this + 8) == 0x132 || *(WORD*)((char*)this + 8) == 0x133 || *(WORD*)((char*)this + 8) == 0x134 || *(WORD*)((char*)this + 8) == 0x13b || *(WORD*)((char*)this + 8) == 0x13c || *(WORD*)((char*)this + 8) == 0x13d)) {
        *(short*)((char*)this + 0x262) = 0x34;
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
        *(int*)((char*)this + 0x3114) = 6;
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 6 && *(WORD*)((char*)this + 8) == 9) {
        *(int*)((char*)this + 0x3114) = 0;
        *((char*)this + 0x18b) = 1;
        return;
    }
    if (*(int*)((char*)this + 0x168) > 1 && *(short*)((char*)this + 0x14a) == 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 25.0f && *(int*)((char*)this + 0x3114) != 1 && *(int*)((char*)this + 0x3114) != 2) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (*(WORD*)((char*)this + 8) == 0xc8) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                if (*(int*)((char*)this + 0x168) == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                }
                return;
            }
            if (v10 < 125.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 5;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xc9) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x257 && *(int*)((char*)this + 0x3110) < 0x2bc && v10 < 90.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0xc8) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x1f4 && *(int*)((char*)this + 0x168) == 3) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 2) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x1f4) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x398) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1f3) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 5;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xca) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0xc7 && *(int*)((char*)this + 0x3110) < 0x190) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x1f4 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < (*(int*)((char*)this + 0x168) == 3) * 0xc8 + 0xc8) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x1f4 && *(int*)((char*)this + 0x168) == 3 && v10 < 100.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1f3 && *(int*)((char*)this + 0x3110) < 0x226 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x225 && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x257 && *(int*)((char*)this + 0x3110) < 0x28a) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcb) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < (*(int*)((char*)this + 0x168) == 3) * 0xc8 + 0x64 && (*(double*)((char*)this + 0x118) > 500.0 || *(int*)((char*)this + 0x168) == 3)) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x96) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x96 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xfa && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xfa && *(int*)((char*)this + 0x3110) < 0x190 && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1cc && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x38e) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcc) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                if (*(int*)((char*)this + 0x168) == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                }
                return;
            }
            if (v10 < 125.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 5;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcd) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0xc7 && *(int*)((char*)this + 0x3110) < 0x190) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x1f4 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < (*(int*)((char*)this + 0x168) == 3) * 0xc8 + 0xc8) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x1f4 && *(int*)((char*)this + 0x168) == 3 && v10 < 100.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1f3 && *(int*)((char*)this + 0x3110) < 0x226 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x225 && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x257 && *(int*)((char*)this + 0x3110) < 0x28a) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xce) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < (*(int*)((char*)this + 0x168) == 3) * 0xc8 + 0x64 && (*(double*)((char*)this + 0x118) > 500.0 || *(int*)((char*)this + 0x168) == 3)) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x96) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x96 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xfa && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xfa && *(int*)((char*)this + 0x3110) < 0x190 && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1cc && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
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
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 3;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd0) {
            if (*(int*)((char*)this + 0x3110) < 0x14 && *(int*)((char*)this + 0x168) == 3 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x14 && *(int*)((char*)this + 0x3110) < 0x32 && *(int*)((char*)this + 0x168) == 3 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x32 && *(int*)((char*)this + 0x3110) < 0x3c && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3c && *(int*)((char*)this + 0x3110) < 0x12c) {
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
        if (*(WORD*)((char*)this + 8) == 0xd1 && *(int*)((char*)this + 0x3110) > 0x289) {
            *(int*)((char*)this + 0x3114) = 3;
            return;
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 25.0f * *(float*)((char*)this + 0xa8)) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (*(double*)((char*)this + 0x28) == 0.0) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x63) {
                if (v10 < 40.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(int*)((char*)this + 0x3110) < 5) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x188) = -*((char*)this + 0x50);
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 45.0 && *(int*)((char*)this + 0x3110) < 0x14) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x1e) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 140.0 && v10 > 100.0 && *(int*)((char*)this + 0x3110) < 0xf) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 120.0 && *(int*)((char*)this + 0x3110) < 0x14) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 120.0 && v10 > 80.0 && *(int*)((char*)this + 0x3110) < 0x28 && *(int*)((char*)this + 0x3110) > 0x25) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 100.0 && v10 > 80.0 && *(int*)((char*)this + 0x3110) < 0x25) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 80.0 && *(int*)((char*)this + 0x3110) < 0x2a && *(int*)((char*)this + 0x3110) > 0x28) {
                    *(short*)((char*)this + 0x262) = 0x1e;
                    return;
                }
                if (*(int*)((char*)this + 0x3110) < 0x2a && *(int*)((char*)this + 0x3110) > 0x2f) {
                    *(short*)((char*)this + 0x262) = *((char*)this + 0x50);
                    *(int*)((char*)this + 0x3114) = 5;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) < 0.0) {
                    if (v10 < 80.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) < 0xa) {
                        *((char*)this + 0x189) = -1;
                        *((char*)this + 0x188) = -*((char*)this + 0x50);
                        return;
                    }
                    if (v10 < 120.0 && x8 < 100.0 && *(int*)((char*)this + 0x3110) < 0xf) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) < 0x11 && *(short*)((char*)this + 0x148) >= 0x7d0) {
                        *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 1) + 0x79;
                        return;
                    }
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) > 0.0) {
                    if (v10 < 80.0 && x8 < 120.0) {
                        if (*(int*)((char*)this + 0x3110) < (*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) * 5 + 6) {
                            *(short*)((char*)this + 0x262) = 0x14;
                            return;
                        }
                    }
                    if (v10 < 140.0 && v10 > 80.0 && x8 < 120.0 && x8 > 80.0 && *(int*)((char*)this + 0x3110) < 0xf) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                    if (v10 < 120.0 && x8 < 150.0 && *(int*)((char*)this + 0x3110) < 0x11 && *(short*)((char*)this + 0x148) >= 0x7d0) {
                        *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 1) + 0x79;
                        return;
                    }
                }
            }
        }
        if (*(double*)((char*)this + 0x28) < 0.0 && *(int*)((char*)this + 0x3114) != 3) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                if (v10 < 70.0 && x8 < 100.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) * 0x64 + 0x64) {
                        *((char*)this + 0x18b) = 1;
                        return;
                    }
                }
                if (v10 < 80.0 && x8 > 60.0 && x8 < 80.0 && *(double*)((char*)this + 0x38) > 0.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xdc) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 140.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) < 0xa) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                    *((char*)this + 0x188) = 0;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (v10 < 80.0 && x8 < 80.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < *(double*)((char*)this + 0x28)) {
                    if (*(int*)((char*)this + 0x3110) < (*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) * 0x14 + 6) {
                        *(short*)((char*)this + 0x262) = 0x14;
                        return;
                    }
                }
                if (v10 < 140.0 && x8 > 60.0 && *(int*)((char*)this + 0x3110) < 0x6e) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 < 120.0 && x8 < 90.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) < 0x78) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 140.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) < 0x82) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                    *((char*)this + 0x188) = 0;
                    return;
                }
            }
        }
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 1.0f * *(float*)((char*)this + 0xa8)) {
        if (v10 < 100.0) {
            *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        }
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 2) {
        *(int*)((char*)this + 0x3114) = 4;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8)) {
            *(int*)((char*)this + 0x3114) = 3;
        } else {
            *(int*)((char*)this + 0x3114) = 0;
        }
        if (v10 > 240.0 && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
            *((char*)this + 0x188) = 0;
            *((char*)this + 0x189) = -1;
            return;
        }
        if (v10 < 80.0 && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
            *((char*)this + 0x188) = 0;
            *((char*)this + 0x189) = -1;
            return;
        }
        if (v10 < 140.0 && v10 > 100.0 && *(double*)((char*)this + 0x28) == 0.0) {
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28 && v10 < 60.0) {
        if (*((char*)this + 0x50) == 1) {
            *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        } else {
            *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x50) {
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

void CAyu::Vf7()
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
            case 0x190:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = -4.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3150) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 3;
                    (*(int*)((char*)this + v4 * 4 + 0x3150))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x191:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = rand() * -0.2 / 32768.0 - 0.3;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = rand() * -0.1 / 32768.0 - 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x508) = rand() * -0.005 / 32768.0 - 0.001;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = rand() * 0.005 / 32768.0 + 0.003;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) + *(double*)((char*)this + v4 * 0x98 + 0x508);
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x192:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = rand() * -0.2 / 32768.0 - 0.03;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = rand() * -0.2 / 32768.0 + 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x508) = rand() * -0.03 / 32768.0 - 0.005;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = rand() * 0.005 / 32768.0 + 0.005;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) + *(double*)((char*)this + v4 * 0x98 + 0x508);
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) < -480.0) {
                    Vf10(v4);
                }
                break;
            case 0x193:
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
            case 0x194:
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
            case 0x195:
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) <= 0.3) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.3;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x12) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3150) < 1) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                            (*(int*)((char*)this + v4 * 4 + 0x3150))++;
                            break;
                        }
                        Vf10(v4);
                    }
                }
                break;
            case 0x196:
                if (*(WORD*)((char*)this + 8) == 0x133 || *(WORD*)((char*)this + 8) == 0x134) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + v4 * 0x98 + 0x518) * 0xa + *(double*)((char*)this + 0x20) + 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && (*(WORD*)((char*)this + 8) == 0x133 && *(WORD*)((char*)this + 0xa) < 0xd || *(WORD*)((char*)this + 8) == 0x134 && *(WORD*)((char*)this + 0xa) < 0x1d)) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x197:
                if (*(WORD*)((char*)this + 8) == 0x134) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + v4 * 0x98 + 0x518) * 0xa + *(double*)((char*)this + 0x20) + 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + 0xa) < 0x2d && *(WORD*)((char*)this + 8) == 0x134) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x198:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = -4.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 8;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > -480.0) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -680.0) {
                    Vf10(v4);
                }
                break;
            case 0x199:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 4.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 4;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x19a;
                    *((char*)this + v4 * 0x98 + 0x520) = 2;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    return;
                }
                break;
            case 0x19a:
                *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *((char*)this + 0x2c8) = 3;
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
            case 0x19b:
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                *(int*)((char*)this + 0x3148) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3150) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.6;
                    if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.4;
                    }
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.0;
                    *(int*)((char*)this + v4 * 4 + 0x3150) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 1) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a7;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.0;
                }
                if (*((char*)this + 0x18d) == 1) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a6;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
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
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x19c:
                *(int*)((char*)this + 0x3148) = 1;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 1) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a7;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 1) {
                    Vf10(v4);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3150) > 5) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a7;
                        }
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3150))++;
                    }
                }
                break;
            case 0x19d:
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                *(int*)((char*)this + 0x3148) = 0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 1) {
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                }
                break;
            case 0x19e:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20) - (*((char*)this + 0x50) << 2);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 45.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + 8) != 0x13e) {
                    Vf10(v4);
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x19f;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                }
                break;
            case 0x19f:
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
            case 0x1a0:
                if (*(int*)((char*)this + v4 * 4 + 0x3150) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3150))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x64) * 0.01 + 2.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = (WORD)CPlayer::Unk4108a0(0, 0x64) * 0.00015;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.5;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = CPlayer::Unk4108a0(0, 0xf);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) - *(double*)((char*)this + v4 * 0x98 + 0x510);
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 && *((char*)this + v4 * 0x98 + 0x518) == 1 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -60.0 && *((char*)this + v4 * 0x98 + 0x518) == -1 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) < -320.0) {
                    Vf10(v4);
                    break;
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
            case 0x1a1:
                if (*(int*)((char*)this + v4 * 4 + 0x3150) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3150))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x64) * 0.01 + 1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = (WORD)CPlayer::Unk4108a0(0, 0x64) * 0.0002;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.5;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = CPlayer::Unk4108a0(0, 0xf);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) - *(double*)((char*)this + v4 * 0x98 + 0x510);
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 && *((char*)this + v4 * 0x98 + 0x518) == 1 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -60.0 && *((char*)this + v4 * 0x98 + 0x518) == -1 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) < -320.0) {
                    Vf10(v4);
                    break;
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
            case 0x1a2:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 0x44 + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 63.0;
                if (*(WORD*)((char*)this + 8) == 0x13d) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 0x5c + *(double*)((char*)this + 0x20);
                }
                if ((*(WORD*)((char*)this + 8) == 0x13b || *(WORD*)((char*)this + 8) == 0x13c || *(WORD*)((char*)this + 8) == 0x13d) && *(short*)((char*)this + 0x14a) > 0) {
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d4))--;
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
            case 0x1a3:
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.3;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.04;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) <= 0.3) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.3;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x12) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3150) < 3) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                            (*(int*)((char*)this + v4 * 4 + 0x3150))++;
                            break;
                        }
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a4:
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(int*)((char*)this + 0x314c) * 0.1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) <= 0.3) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.3;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x12) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3150) < 4) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                            (*(int*)((char*)this + v4 * 4 + 0x3150))++;
                            break;
                        }
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a5:
                if (*(WORD*)((char*)this + 8) == 0x132 || *(WORD*)((char*)this + 8) == 0x134) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + v4 * 0x98 + 0x518) * 0xa + *(double*)((char*)this + 0x20) + 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && (*(WORD*)((char*)this + 8) == 0x132 && *(WORD*)((char*)this + 0xa) < 0xd || *(WORD*)((char*)this + 8) == 0x134 && *(WORD*)((char*)this + 0xa) < 0xd)) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
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
                    *(int*)((char*)this + 0x3144) = 0;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3150) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3250) = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    (*(int*)((char*)this + v4 * 4 + 0x3150))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3250) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3250) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x3250))--;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3150) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3250) = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    (*(int*)((char*)this + v4 * 4 + 0x3150))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.03;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3250) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3250) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x3250))--;
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
