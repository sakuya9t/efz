// CNanase (0x48a720-0x49d60f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNanase::CNanase(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy((char*)this + 0x94, "nanase");
    *(short*)((char*)this + 0x18) = 0x29c;
    *(int*)((char*)this + 0x345c) = (int)(char*)new EffectAnim[0x1f9];
    *(int*)((char*)this + 0x3460) = (int)(char*)new PatternData[0x1f9];
    *((char*)this + 0x3458) = 0;
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x344c) = 0;
    *(int*)((char*)this + 0x3450) = 0;
    *(int*)((char*)this + 0x3454) = 0;
    Unk48e140(0);
    *(short*)((char*)this + 0x2ad0) = -0xc;
    *(short*)((char*)this + 0x2af8) = -0x3a;
    *(short*)((char*)this + 0x2ad2) = 0x12;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0x10;
    *(short*)((char*)this + 0x2afc) = -9;
    *(short*)((char*)this + 0x2ad6) = 0x15;
    *(short*)((char*)this + 0x2afe) = -0xe;
    *(short*)((char*)this + 0x2ad8) = 0x21;
    *(short*)((char*)this + 0x2b00) = -0x1a;
    *((char*)this + 0x30f4) = 5;
    *((char*)this + 0x30f5) = 6;
    *((char*)this + 0x30f6) = 2;
    *((char*)this + 0x30f7) = 5;
    *((char*)this + 0x30f8) = 0xc;
    *((char*)this + 0x30ff) = 0;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x314c) = 0;
        *(int*)((char*)this + v4 * 4 + 0x324c) = 0;
        *(int*)((char*)this + v4 * 4 + 0x334c) = 0;
    }
}

void CNanase::Vf12()
{
    int v4;

    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x344c) = 0;
    *(int*)((char*)this + 0x3450) = 0;
    *(int*)((char*)this + 0x3454) = 0;
    Unk48e140(0);
    *(short*)((char*)this + 0x2ad0) = -0xc;
    *(short*)((char*)this + 0x2af8) = -0x3a;
    *(short*)((char*)this + 0x2ad2) = 0x12;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0x10;
    *(short*)((char*)this + 0x2afc) = -9;
    *(short*)((char*)this + 0x2ad6) = 0x15;
    *(short*)((char*)this + 0x2afe) = -0xe;
    *(short*)((char*)this + 0x2ad8) = 0x21;
    *(short*)((char*)this + 0x2b00) = -0x1a;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x314c) = 0;
        *(int*)((char*)this + v4 * 4 + 0x324c) = 0;
        *(int*)((char*)this + v4 * 4 + 0x334c) = 0;
    }
    CPlayer::Vf12();
}

CNanase::~CNanase()
{
    *(int*)((char*)this + 0x10) = *(int*)((char*)this + 0x3464);
    *(int*)((char*)this + 0x164) = *(int*)((char*)this + 0x3468);
    delete[] (EffectAnim*)*(int*)((char*)this + 0x345c);
    delete[] (PatternData*)*(int*)((char*)this + 0x3460);
    CPlayer::~CPlayer();
}

void CNanase::Vf11()
{
    Unk48d940();
    CPlayer::Vf11();
    *(int*)((char*)this + 0x3464) = *(int*)((char*)this + 0x10);
    *(int*)((char*)this + 0x3468) = *(int*)((char*)this + 0x164);
}

void CNanase::Vf0()
{
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    CPlayer::Vf0();
}

void CNanase::Vf10(short p1)
{
    *(int*)((char*)this + p1 * 4 + 0x314c) = 0;
    *(int*)((char*)this + p1 * 4 + 0x324c) = 0;
    *(int*)((char*)this + p1 * 4 + 0x334c) = 0;
    CPlayer::Vf10(p1);
}

void CNanase::Vf3()
{
    CPlayer::Unk40e740();
}

void CNanase::Vf4()
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
    if (*(short*)((char*)this + 0x262) == 0x34 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && *(int*)((char*)this + 0x168) > 1 && *(int*)((char*)this + 0x168) != 6 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x538)) {
        Vf0();
        CPlayer::Unk40f170();
        *(short*)((char*)this + 8) = 0xa7;
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(short*)((char*)this + 8) = 0xab;
        }
        return;
    }
    if (*(int*)((char*)this + 0x15c) < 2) {
        if (*(short*)((char*)this + 0x262) == 0x99 && *(int*)((char*)this + 0x108) < 0xd05 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x998)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x133;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x98 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9b0) || *(WORD*)((char*)this + 8) > 0xfc && *(WORD*)((char*)this + 8) < 0x100 && *(int*)((char*)this + 0x168) == 3)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x136;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x97 || *(short*)((char*)this + 0x262) == 0x98) && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a8) || *(WORD*)((char*)this + 8) > 0xfc && *(WORD*)((char*)this + 8) < 0x100 && *(int*)((char*)this + 0x168) == 3)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x135;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x96 || *(short*)((char*)this + 0x262) == 0x97 || *(short*)((char*)this + 0x262) == 0x98) && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a0) || *(WORD*)((char*)this + 8) > 0xfc && *(WORD*)((char*)this + 8) < 0x100 && *(int*)((char*)this + 0x168) == 3)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x134;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x66 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x344c) == 1 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x988)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x131;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x344c) == 1 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x980)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x130;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x64 || *(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x344c) == 1 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x978)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12f;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x70 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x970) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12e;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x968) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12d;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6e || *(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x960) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12c;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x16 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x810) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x102;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 0xa) = 9;
                *(int*)((char*)this + 0x3140) = 1;
                *(int*)((char*)this + 0x168) = 3;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x15 || *(short*)((char*)this + 0x262) == 0x16) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x808) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x101;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 0xa) = 9;
                *(int*)((char*)this + 0x168) = 3;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x14 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x800) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x100;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 0xa) = 9;
                *(int*)((char*)this + 0x168) = 3;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x20 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x828) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x105;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x1f || *(short*)((char*)this + 0x262) == 0x20) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x820) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x104;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x1e && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x818) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x103;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x48 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfa;
            if (*(int*)((char*)this + 0x344c) == 0) {
                *(short*)((char*)this + 8) = 0x108;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x47 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfa;
            if (*(int*)((char*)this + 0x344c) == 0) {
                *(short*)((char*)this + 8) = 0x107;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x46 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfa;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xc && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f8) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xff;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0xb || *(short*)((char*)this + 0x262) == 0xc) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f0) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfe;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x344c) == 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7e8) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfd;
            return;
        }
    }
    if (*(int*)((char*)this + 0x15c) < 1 && (*(short*)((char*)this + 0x262) == 0 || *(short*)((char*)this + 0x262) == 1)) {
        if (*(double*)((char*)this + 0x28) < 0.0 && *(BYTE*)((char*)this + 0x159) < 1) {
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
                *((char*)this + 0x1a8) = 0;
                return;
            }
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
    if (*((char*)this + 0x18a) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x10) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x10) != 0) {
        if (*(WORD*)((char*)this + 8) == 0xa3 && *((char*)this + 0x188) != -*((char*)this + 0x50)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xe6;
            if (*((char*)this + 0x189) == 1) {
                *(short*)((char*)this + 8) = 0xe9;
            }
            return;
        }
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
        if (*(WORD*)((char*)this + 8) == 0xa3 && *((char*)this + 0x188) != -*((char*)this + 0x50)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xe7;
            if (*((char*)this + 0x189) == 1) {
                *(short*)((char*)this + 8) = 0xea;
            }
            return;
        }
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
        if (*(WORD*)((char*)this + 8) == 0xa3 && *((char*)this + 0x188) != -*((char*)this + 0x50)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xe8;
            if (*((char*)this + 0x189) == 1) {
                *(short*)((char*)this + 8) = 0xeb;
            }
            return;
        }
        if (*(double*)((char*)this + 0x28) < 0.0) {
            if (*((char*)this + 0x188) == *((char*)this + 0x50) && *((char*)this + 0x189) == 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -100.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 100.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7c0) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xf8;
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
        if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
            if (*((char*)this + 0x188) != 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -30.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 30.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6e0) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xdc;
                return;
            }
            if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x658) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xcb;
            }
        }
    }
}

void CNanase::Unk48d940()
{
    int k2c;
    char* v28;
    char* x24;
    int x20;
    int n1c;
    int a18;
    int k14;
    int l4;

    CFile v10("nanase\\nanase2.pat", 1);
    l4 = v10.ReadInt();
    n1c = 0;
    for (; n1c < l4; n1c++) {
        k14 = v10.ReadInt();
        *(short*)(*(char**)((char*)this + 0x3460) + k14 * 8) = v10.ReadInt();
        *(short*)(*(char**)((char*)this + 0x3460) + 2 + k14 * 8) = v10.ReadInt();
        *(*(char**)((char*)this + 0x345c) + k14 * 8) = v10.ReadInt();
        a18 = *(BYTE*)(*(char**)((char*)this + 0x345c) + k14 * 8);
        ((PatternData*)(*(int*)((char*)this + 0x3460) + k14 * 8))->Alloc(a18);
        ((EffectAnim*)(*(int*)((char*)this + 0x345c) + k14 * 8))->Alloc(a18);
        x20 = 0;
        for (; x20 < a18; x20++) {
            x24 = (char*)(*(int*)(*(char**)((char*)this + 0x345c) + 4 + k14 * 8) + x20 * 0xc);
            v28 = (char*)(*(int*)(*(char**)((char*)this + 0x3460) + 4 + k14 * 8) + x20 * 0xc8);
            *(short*)x24 = (short)v10.ReadInt() * 3;
            *(short*)(x24 + 2) = v10.ReadInt();
            *(short*)(x24 + 8) = v10.ReadInt();
            *(short*)(x24 + 0xa) = v10.ReadInt();
            *(short*)(x24 + 4) = v10.ReadInt();
            *(short*)(x24 + 6) = v10.ReadInt();
            *(short*)(v28 + 0xa0) = v10.ReadInt();
            *(short*)(v28 + 0xaa) = v10.ReadInt();
            *(short*)(v28 + 0xac) = v10.ReadInt();
            *(short*)(v28 + 0xb0) = v10.ReadInt();
            *(short*)(v28 + 0xb2) = v10.ReadInt();
            *(short*)(v28 + 0xa8) = v10.ReadInt();
            *(short*)(v28 + 0xb4) = v10.ReadInt();
            *(short*)(v28 + 0xb6) = v10.ReadInt();
            *(float*)(v28 + 0xbc) = (short)v10.ReadShort();
            *(float*)(v28 + 0xbc) = *(float*)(v28 + 0xbc) / 1e+02f;
            *(float*)(v28 + 0xb8) = (short)v10.ReadShort();
            *(float*)(v28 + 0xb8) = *(float*)(v28 + 0xb8) / -1e+02f;
            *(v28 + 0xc1) = v10.ReadShort();
            *(v28 + 0xc0) = v10.ReadShort();
            *(short*)(v28 + 0xc2) = v10.ReadInt();
            *(short*)(v28 + 0xc4) = v10.ReadInt();
            *(float*)(v28 + 0xa4) = v10.ReadInt();
            *(short*)(v28 + 0xae) = v10.ReadInt();
            v10.Read((void*)(v28 + 0x90), 0x10);
            k2c = 0;
            for (; k2c < 2; k2c++) {
                v10.Read((void*)((k2c << 4) + v28), 0x10);
            }
            v10.Read((void*)(v28 + 0x50), 0x10);
            k2c = 2;
            for (; k2c < 5; k2c++) {
                v10.Read((void*)((k2c << 4) + v28), 0x10);
            }
            k2c = 1;
            for (; k2c < 4; k2c++) {
                v10.Read((void*)(v28 + (k2c << 4) + 0x50), 0x10);
            }
        }
    }
}

void CNanase::Vf1()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (*(int*)((char*)this + 0x3148) > 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x15c);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3148) > 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x164);
        v2c = MakeRect(0, 0, *(int*)((char*)this + 0x3148) * x1c.width / 0xbb8, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, *(int*)((char*)this + 0x3148) * x1c.width / 0xbb8, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - *(int*)((char*)this + 0x3148) * x1c.width / 0xbb8, 0x1f - x1c.y, *(int*)((char*)this + 0x3148) * x1c.width / 0xbb8, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
}

void CNanase::Unk48e140(char p1)
{
    int v8;
    int v4;

    if (p1 == 1 && *((char*)this + 0x3458) == 0) {
        *(int*)((char*)this + 0x10) = *(int*)((char*)this + 0x345c);
        v4 = 0;
        for (; v4 < 0x40; v4++) {
            *(int*)((char*)this + v4 * 0x98 + 0x4d8) = *(int*)((char*)this + 0x345c);
        }
        *(int*)((char*)this + 0x164) = *(int*)((char*)this + 0x3460);
        *((char*)this + 0x3458) = 1;
        return;
    }
    if (p1 == 0 && *((char*)this + 0x3458) == 1) {
        *(int*)((char*)this + 0x10) = *(int*)((char*)this + 0x3464);
        v8 = 0;
        for (; v8 < 0x40; v8++) {
            *(int*)((char*)this + v8 * 0x98 + 0x4d8) = *(int*)((char*)this + 0x3464);
        }
        *(int*)((char*)this + 0x164) = *(int*)((char*)this + 0x3468);
        *((char*)this + 0x3458) = 0;
    }
}

void CNanase::Vf8()
{
}

void CNanase::Vf9(EffectDesc* p1)
{
    Vf10(*(short*)((char*)this + 0x2ca));
    CPlayer::Vf9(p1);
}

void CNanase::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    *(short*)((char*)this + 0x262) = 0x63;
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x2d;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 7) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x96 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x96 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 8;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 6) {
            x6 = 7;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 2) {
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
        if ((v5 & 0xf) == 4 && x6 == 0 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(int*)((char*)this + 0x344c) == 0) {
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
        if ((v5 & 0xf) == 4 && x6 == 0 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(int*)((char*)this + 0x344c) == 1) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x5a;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x46 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x46 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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

void CNanase::Vf5()
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
    if (*(WORD*)((char*)this + 8) == 0xfb && *(int*)((char*)this + 0x344c) == 0) {
        if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) > 0.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -280.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -20.0 && (WORD)CPlayer::Unk4108a0(0, 0x3e8) < 2) {
            *(short*)((char*)this + 0x262) = 0xa;
            return;
        }
        if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) > 0.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -220.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -20.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 0x1e) {
                *(short*)((char*)this + 0x262) = 0xb;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < 0xa && *(short*)((char*)this + 0x148) == 0xbb8 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -100.0) {
                *(short*)((char*)this + 0x262) = 0xc;
            }
            return;
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 && *(WORD*)((char*)this + 0xc) < 6) {
        if (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0xc8 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0xcc && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0) {
            if (v10 < 40.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x262) = 0x46;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(int*)((char*)this + 0x344c) == 0) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(int*)((char*)this + 0x344c) == 1) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
        }
        if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xc9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xca || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xcd) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0) {
            if (v10 > 40.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x188) = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 || *(WORD*)((char*)this + 8) == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && v10 < 40.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x262) = 0x46;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x344c) == 0) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f + ((*(double*)((char*)this + 0x118) > 500.0) << 1) && *(int*)((char*)this + 0x344c) == 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x262) = 0xc;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f + ((*(double*)((char*)this + 0x118) > 500.0) << 1) && *(int*)((char*)this + 0x344c) == 0) {
                *(short*)((char*)this + 0x262) = ((WORD)CPlayer::Unk4108a0(0, 1) == 1) + 0x1f;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(short*)((char*)this + 0x148) >= 0x3e8 && *(int*)((char*)this + 0x344c) == 0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x262) = 0x6e;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && v10 < 150.0 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(int*)((char*)this + 0x344c) == 1 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x262) = 0x64;
                return;
            }
        }
        if (v10 < 160.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0xc;
            return;
        }
        if (v10 < 220.0 && v10 > 160.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
            return;
        }
        if (v10 > 220.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
            return;
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xaa && *(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *(int*)((char*)this + 0x3114) = 3;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -60.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18a) = 1;
            return;
        }
        if (x8 < 80.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f && *(int*)((char*)this + 0x344c) == 0) {
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
        if (*(int*)((char*)this + 0x3110) < 3 && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x344c) == 0) {
            *(short*)((char*)this + 0x262) = 0x14;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 7 && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x344c) == 0) {
            *(short*)((char*)this + 0x262) = 0xc;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0xa && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x344c) == 0) {
            *(short*)((char*)this + 0x262) = 0x20;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0xd && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x344c) == 0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x3e8 && *(int*)((char*)this + 0x344c) == 0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x12 && *(int*)((char*)this + 0x3110) > 0x16 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(int*)((char*)this + 0x344c) == 1) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x64;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 0x14) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
        if (v10 < 200.0 && *(int*)((char*)this + 0x3110) < 0x20 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && v10 * 0.5 > x8 && v10 * 0.3 < x8) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
    }
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d && (*(WORD*)((char*)this + 8) == 0x100 || *(WORD*)((char*)this + 8) == 0x101 || *(WORD*)((char*)this + 8) == 0x103 || *(WORD*)((char*)this + 8) == 0x12c || *(WORD*)((char*)this + 8) == 0x12d || *(WORD*)((char*)this + 8) == 0x12e)) {
        *(short*)((char*)this + 0x262) = 0x34;
        return;
    }
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 1.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x168) == 3 && (*(WORD*)((char*)this + 8) == 0xfd && *(WORD*)((char*)this + 0xa) == 0xd || *(WORD*)((char*)this + 8) == 0xfe && *(WORD*)((char*)this + 0xa) == 0xd)) {
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
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 6 && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 7;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 7 && *(WORD*)((char*)this + 8) == 0xa3) {
        *((char*)this + 0x18a) = 1;
        if (*(WORD*)((char*)this + 8) == 0xe6) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 8 && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 9;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 9 && *(WORD*)((char*)this + 8) == 0xa3) {
        *((char*)this + 0x18a) = 2;
        if (*(WORD*)((char*)this + 8) == 0xe7) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xa && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 0xb;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xb && *(WORD*)((char*)this + 8) == 0xa3) {
        *((char*)this + 0x18a) = 3;
        if (*(WORD*)((char*)this + 8) == 0xe8) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xc && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = 0x46;
        if (*(WORD*)((char*)this + 8) == 0xfa) {
            *(int*)((char*)this + 0x3114) = 0;
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
            if (v10 < 40.0 && *(int*)((char*)this + 0x3110) < 0xa) {
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
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                if (*(int*)((char*)this + 0x168) == 3 && (WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xc;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xc9) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x140 && *(int*)((char*)this + 0x3110) < 0x258 && v10 < 100.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && v10 < 80.0) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x190 && *(int*)((char*)this + 0x168) == 3 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && v10 < 80.0) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x15e && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x226 && v10 < 90.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x226 && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = (WORD)CPlayer::Unk4108a0(0, 1) == 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x398) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if (v10 > 110.0) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xca) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x64) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = (WORD)CPlayer::Unk4108a0(0, 1) == 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x190 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if (v10 > 110.0) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcb) {
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x190 && *(int*)((char*)this + 0x344c) == 1) {
                *(short*)((char*)this + 0x262) = 0x46;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcc) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 40.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 50.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                if (*(int*)((char*)this + 0x168) == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                }
                return;
            }
            if (v10 < 135.0 && *(int*)((char*)this + 0x3110) < 0x258) {
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
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 5;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcd) {
            if (*(int*)((char*)this + 0x3110) < 0x190 && v10 < 80.0 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x64 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x258) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xce) {
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x190 && *(int*)((char*)this + 0x344c) == 1) {
                *(short*)((char*)this + 0x262) = 0x46;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1c2 && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 < 90.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
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
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
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
        if (*(WORD*)((char*)this + 8) == 0xe7) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x190 && *(int*)((char*)this + 0x344c) == 1) {
                *(short*)((char*)this + 0x262) = 0x46;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289 && (WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                *(int*)((char*)this + 0x3114) = 6;
                if (v10 > 110.0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
            }
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 25.0f * *(float*)((char*)this + 0xa8)) {
        if (*(int*)((char*)this + 0x344c) == 1) {
            *((char*)this + 0x18d) = 1;
        }
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (*(double*)((char*)this + 0x28) == 0.0) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x63) {
                if (v10 < 40.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(int*)((char*)this + 0x3110) < 3) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x188) = -*((char*)this + 0x50);
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(int*)((char*)this + 0x3110) < 8) {
                    *(short*)((char*)this + 0x262) = 0x46;
                    return;
                }
                if (0x64 - (*(int*)((char*)this + 0x344c) == 1) * 0x1e > v10 && *(int*)((char*)this + 0x3110) < 0x14) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x1e) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if ((*(int*)((char*)this + 0x344c) == 1) * 0xa + 0x64 > v10 && v10 > 70.0 && *(int*)((char*)this + 0x3110) < 0xf) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (0x8c - (*(int*)((char*)this + 0x344c) == 1) * 0x28 > v10 && *(int*)((char*)this + 0x3110) < 0x14) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 > 160.0 && *(int*)((char*)this + 0x3110) < 0x1a) {
                    *(int*)((char*)this + 0x3114) = 8;
                    return;
                }
                if (v10 > 160.0 && *(int*)((char*)this + 0x3110) < 0x20) {
                    *(int*)((char*)this + 0x3114) = 0xa;
                    return;
                }
                if (0xaa - (*(int*)((char*)this + 0x344c) == 1) * 0x3c > v10 && 0x78 - (*(int*)((char*)this + 0x344c) == 1) * 0x28 < v10 && *(int*)((char*)this + 0x3110) < 0x25) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 220.0 && v10 > 70.0 && *(int*)((char*)this + 0x3110) < 0x28) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x2a && *(int*)((char*)this + 0x3110) > 0x28) {
                    *(short*)((char*)this + 0x262) = 0x14;
                    return;
                }
                if (*(int*)((char*)this + 0x3110) < 0x2a && *(int*)((char*)this + 0x3110) > 0x32) {
                    *(short*)((char*)this + 0x262) = *((char*)this + 0x50);
                    *(int*)((char*)this + 0x3114) = 5;
                    return;
                }
                if (v10 > 180.0 && *(int*)((char*)this + 0x3110) > 0xfa && *(int*)((char*)this + 0x3110) < 0xfc && *(short*)((char*)this + 0x148) >= 0x3e8) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
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
                    if (v10 < 120.0 && *(int*)((char*)this + 0x3110) < 0x1e && *(int*)((char*)this + 0x344c) == 0) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                    if (v10 > 80.0 && v10 < 120.0 && x8 > 70.0 && *(int*)((char*)this + 0x3110) < 0x1e && *(int*)((char*)this + 0x344c) == 1) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                    if (v10 > 120.0 && v10 < 180.0 && x8 > 90.0 && *(int*)((char*)this + 0x3110) < 0x1e && *(int*)((char*)this + 0x344c) == 1) {
                        *(int*)((char*)this + 0x3114) = 0xa;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) < 0x23) {
                        *(short*)((char*)this + 0x262) = 0x15;
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
                    if (v10 < 90.0 && x8 < 120.0 && x8 > 90.0 && *(int*)((char*)this + 0x3110) < 0xf) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                    if (v10 < 120.0 && x8 < 100.0 && *(int*)((char*)this + 0x3110) < 0x11 && *(short*)((char*)this + 0x148) == 0xbb8) {
                        *(short*)((char*)this + 0x262) = 0x99;
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
                if (v10 < 120.0 && x8 < 100.0 && *(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x104) {
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
                if (v10 < 120.0 && x8 < 90.0 && *(int*)((char*)this + 0x3110) < 0x136) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 100.0 && x8 < 90.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
            }
        }
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 3.0f * *(float*)((char*)this + 0xa8)) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        return;
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 && v10 > 60.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 1.0f * *(float*)((char*)this + 0xa8)) {
        *(short*)((char*)this + 0x262) = -((*((char*)this + 0x50) == 1) - 1);
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
        if (v10 > 160.0 && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
            *((char*)this + 0x188) = 0;
            *((char*)this + 0x189) = -1;
            return;
        }
        if (v10 < 100.0 && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32 && v10 < 120.0) {
        if (*((char*)this + 0x50) == 1) {
            *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
        } else {
            *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x3c) {
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

void CNanase::Vf7()
{
    WORD v58;
    WORD v54;
    int v4;

    if (*((char*)this + 0x3458) == 1) {
        Unk497540();
        return;
    }
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
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.8;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    Vf10(v4);
                    l50.type = 0x192;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    *((char*)this + 0x2c8) = 2;
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                }
                break;
            case 0x191:
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.8;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    Vf10(v4);
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
            case 0x192:
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
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.0 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if ((*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 1) && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 1;
                    Vf10(v4);
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
            case 0x196:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 5) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.3 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if ((*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 1) && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 1;
                    Vf10(v4);
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
            case 0x197:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 4) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if ((*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 1) && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    Vf10(v4);
                    *((char*)this + 0x2c8) = 1;
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
            case 0x198:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xd) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.7 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if ((*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 1) && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 1;
                    Vf10(v4);
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
            case 0x199:
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 2;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 2) {
                    Vf10(v4);
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
            case 0x19a:
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xf) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0 - (WORD)CPlayer::Unk4108a0(0, 0xf) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.045;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 2;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 2) {
                    Vf10(v4);
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
            case 0x19b:
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
                *(int*)((char*)this + 0x3450) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *(int*)((char*)this + 0x3454) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.0;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 1) {
                    l50.type = 0x1a6;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    *(int*)((char*)this + 0x3454) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -8.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.035;
                    *((char*)this + v4 * 0x98 + 0x520) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1a4:
                *(int*)((char*)this + 0x3450) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *(int*)((char*)this + 0x3454) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.4;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.8;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 1) {
                    *((char*)this + 0x2c9) = 0x16;
                    l50.type = 0x1a9;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x50);
                    l50.y = 15.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0x50);
                    l50.y = 15.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    *(int*)((char*)this + 0x3454) = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -5.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    *((char*)this + v4 * 0x98 + 0x520) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1ac:
                *(int*)((char*)this + 0x3450) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *(int*)((char*)this + 0x3454) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.4;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.4;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 1) {
                    *((char*)this + 0x2c9) = 0x16;
                    l50.type = 0x1aa;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x50);
                    l50.y = 15.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0x50);
                    l50.y = 15.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x28);
                    l50.y = -80.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0x28);
                    l50.y = -80.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    *(int*)((char*)this + 0x3454) = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -5.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    *((char*)this + v4 * 0x98 + 0x520) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1a7:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(int*)((char*)this + 0x3450);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(int*)((char*)this + 0x3454);
                if (*(int*)((char*)this + 0x3454) == 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1ab:
                if (*(int*)((char*)this + v4 * 4 + 0x314c) <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + (0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28)) * *((char*)this + 0x50));
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28));
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 2;
                }
                (*(int*)((char*)this + v4 * 4 + 0x314c))--;
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
            case 0x1ad:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                    *((char*)this + 0x2c8) = 0;
                    l50.type = 0x19b;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x195;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x195;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x195;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x195;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x314c) < 3) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                            (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                            break;
                        }
                        Vf10(v4);
                    }
                }
                break;
            case 0x1af:
                *(short*)((char*)this + 0x138) = 2;
                *(short*)((char*)this + 0x13a) = 2;
                (*(int*)((char*)this + 0x3148))--;
                CPlayer::Unk4109d0(1);
                *(double*)((char*)this + 0x180) = 0.5;
                if (*(int*)((char*)this + 0x3148) <= 0) {
                    *(int*)((char*)this + 0x3148) = 0;
                    Vf10(v4);
                    *(short*)((char*)this + 0x138) = 0;
                    *(short*)((char*)this + 0x13a) = 0;
                    *(double*)((char*)this + 0x180) = 1.0;
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + (0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28)) * *((char*)this + 0x50));
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - (WORD)CPlayer::Unk4108a0(0, 0x5a));
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 2;
                }
                (*(int*)((char*)this + v4 * 4 + 0x314c))--;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x324c) = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x324c))--;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x324c) = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.03;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x324c))--;
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

void CNanase::Unk497540()
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
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) >= 0xf) {
                    *(int*)((char*)this + v4 * 4 + 0x324c) = 0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                (*(int*)((char*)this + v4 * 4 + 0x324c))++;
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.8;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x193;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.8;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.02;
                    l50.type = 0x192;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    *((char*)this + 0x2c8) = 2;
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                }
                break;
            case 0x191:
                l50.type = 0x22;
                l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + 0x28 - (WORD)CPlayer::Unk4108a0(0, 0x50));
                l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28));
                l50.unk20 = 2;
                l50.unk21 = 1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.8;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    Vf10(v4);
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                }
                break;
            case 0x192:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xc && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0xa) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk20 = 2;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    Vf9(&l50);
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
            case 0x193:
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x194;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
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
            case 0x194:
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)((char*)this + 0x20) < 30.0 && *(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)((char*)this + 0x20) > -30.0 && *((char*)this + 0x18d) == 1 && *(WORD*)((char*)this + 8) < 3) {
                    Vf10(v4);
                    *(short*)((char*)this + 8) = 0x12b;
                    Vf0();
                    Unk48e140(0);
                    *(int*)((char*)this + 0x344c) = 0;
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
            case 0x195:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.0 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 1;
                    Vf10(v4);
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
            case 0x196:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 5) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.3 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 1;
                    Vf10(v4);
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
            case 0x197:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 4) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    Vf9(&l50);
                    Vf10(v4);
                    *((char*)this + 0x2c8) = 1;
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
            case 0x198:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xd) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.7 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 1;
                    Vf10(v4);
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
            case 0x199:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *((char*)this + v4 * 0x98 + 0x520) == 1) {
                    Vf10(v4);
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
            case 0x19a:
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *((char*)this + v4 * 0x98 + 0x520) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500) * 0.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *((char*)this + v4 * 0x98 + 0x520) == 1) {
                    Vf10(v4);
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
            case 0x19b:
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
            case 0x19d:
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) >= 0xf) {
                    *(int*)((char*)this + v4 * 4 + 0x324c) = 0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                (*(int*)((char*)this + v4 * 4 + 0x324c))++;
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.8;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x193;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.8;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.02;
                    l50.type = 0x19e;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    *((char*)this + 0x2c8) = 2;
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                }
                break;
            case 0x19e:
                *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(double*)((char*)this + v4 * 0x98 + 0x4f0) > -10.0) {
                    l50.type = 0x19e;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + 60.0 - (WORD)CPlayer::Unk4108a0(0, 0x78));
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 4.0);
                    l50.unk18 = *((char*)this + 0x50);
                    *((char*)this + 0x2c8) = 2;
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xc && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0xa) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk20 = 2;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    Vf9(&l50);
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
                *(int*)((char*)this + 0x3450) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *(int*)((char*)this + 0x3454) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.2;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 1) {
                    *((char*)this + 0x2c9) = 0x16;
                    l50.type = 0x1a6;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    *(int*)((char*)this + 0x3454) = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    *((char*)this + v4 * 0x98 + 0x520) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1a4:
                *(int*)((char*)this + 0x3450) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *(int*)((char*)this + 0x3454) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.4;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.8;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 1) {
                    *((char*)this + 0x2c9) = 0x16;
                    l50.type = 0x1a9;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x28);
                    l50.y = 15.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0x28);
                    l50.y = 15.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    *(int*)((char*)this + 0x3454) = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    *((char*)this + v4 * 0x98 + 0x520) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1ac:
                *(int*)((char*)this + 0x3450) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *(int*)((char*)this + 0x3454) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                if (*(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.4;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.4;
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 1) {
                    *((char*)this + 0x2c9) = 0x16;
                    l50.type = 0x1aa;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x3c);
                    l50.y = 15.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0x3c);
                    l50.y = 15.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x1e);
                    l50.y = -30.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    l50.type = 0x1a5;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + 0x50) * 0x1e);
                    l50.y = -30.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    *(int*)((char*)this + 0x3454) = 0;
                    CPlayer::Unk410a10(0xa, 0);
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    *((char*)this + v4 * 0x98 + 0x520) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1a5:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xc && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0xa) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk20 = 2;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    Vf9(&l50);
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
            case 0x1a6:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xc && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk20 = 2;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    Vf9(&l50);
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xc && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk20 = 2;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    Vf9(&l50);
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
            case 0x1aa:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xc && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                    l50.type = 0x1ab;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.y = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4f0) - (WORD)CPlayer::Unk4108a0(0, 0x64));
                    l50.unk20 = 2;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    Vf9(&l50);
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
            case 0x1a7:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(int*)((char*)this + 0x3450);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(int*)((char*)this + 0x3454);
                l50.type = 0x22;
                l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + 0x28 - (WORD)CPlayer::Unk4108a0(0, 0x50));
                l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28));
                l50.unk20 = 2;
                l50.unk21 = 1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                if (*(int*)((char*)this + 0x3454) == 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                break;
            case 0x1a8:
                *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x194;
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 620.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 620.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 20.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = 20.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
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
            case 0x1ab:
                if (*(int*)((char*)this + v4 * 4 + 0x314c) <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + (0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28)) * *((char*)this + 0x50));
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28));
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 2;
                }
                (*(int*)((char*)this + v4 * 4 + 0x314c))--;
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
            case 0x1ad:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                    *((char*)this + 0x2c8) = 0;
                    l50.type = 0x19b;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 0;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 1) + 0x199;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x195;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x195;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x195;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x195;
                    l50.x = (double)(int)(*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * (0x28 - (WORD)CPlayer::Unk4108a0(0, 0x46)));
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x314c) < 3) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                            (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                            break;
                        }
                        Vf10(v4);
                    }
                }
                break;
            case 0x1af:
                *(short*)((char*)this + 0x138) = 2;
                *(short*)((char*)this + 0x13a) = 2;
                (*(int*)((char*)this + 0x3148))--;
                CPlayer::Unk4109d0(1);
                *(double*)((char*)this + 0x180) = 0.5;
                if (*(int*)((char*)this + 0x3148) <= 0) {
                    *(double*)((char*)this + 0x180) = 1.0;
                    *(int*)((char*)this + 0x3148) = 0;
                    Vf10(v4);
                    *(short*)((char*)this + 0x138) = 0;
                    *(short*)((char*)this + 0x13a) = 0;
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x314c) <= 0) {
                    l50.type = 0x22;
                    l50.x = (double)((int)*(double*)((char*)this + 0x20) + (0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28)) * *((char*)this + 0x50));
                    l50.y = (double)((int)*(double*)((char*)this + 0x28) - (WORD)CPlayer::Unk4108a0(0, 0x5a));
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                    *(int*)((char*)this + v4 * 4 + 0x314c) = 2;
                }
                (*(int*)((char*)this + v4 * 4 + 0x314c))--;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x324c) = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x324c))--;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x314c) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x324c) = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    (*(int*)((char*)this + v4 * 4 + 0x314c))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.03;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -*(double*)((char*)this + v4 * 0x98 + 0x500);
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) < 0xa) {
                    *((char*)this + v4 * 0x98 + 0x520) = 1;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x324c) < 0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                (*(int*)((char*)this + v4 * 4 + 0x324c))--;
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
