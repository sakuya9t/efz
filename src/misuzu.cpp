// CMisuzu (0x519e00-0x530bbf): the character class whose files are in misuzu\ in the game
// folder (misuzu.dat sprites, misuzu.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; the VfN methods override
// the CPlayer virtual slots of the same number (see shiori.cpp for what they do).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMisuzu::CMisuzu(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy((char*)this + 0x94, "misuzu");
    *(short*)((char*)this + 0x18) = 0x368;
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(int*)((char*)this + 0x3460) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3458) = 0;
    *(int*)((char*)this + 0x345c) = 0;
    *(int*)((char*)this + 0x3464) = 0;
    *(int*)((char*)this + 0x3468) = 0;
    *(int*)((char*)this + 0x346c) = 0;
    *(int*)((char*)this + 0x3470) = 0;
    *(int*)((char*)this + 0x3474) = 0;
    *(int*)((char*)this + 0x3478) = 0;
    *(int*)((char*)this + 0x347c) = 0;
    *(int*)((char*)this + 0x3480) = 0;
    *(short*)((char*)this + 0x2ad0) = -2;
    *(short*)((char*)this + 0x2af8) = -0x3e;
    *(short*)((char*)this + 0x2ad2) = 1;
    *(short*)((char*)this + 0x2afa) = -0xa;
    *(short*)((char*)this + 0x2ad4) = 0x18;
    *(short*)((char*)this + 0x2afc) = -0x12;
    *(short*)((char*)this + 0x2ad6) = -0xb;
    *(short*)((char*)this + 0x2afe) = -0x17;
    *(short*)((char*)this + 0x2ad8) = 0x15;
    *(short*)((char*)this + 0x2b00) = -0x16;
    *((char*)this + 0x30f4) = 5;
    *((char*)this + 0x30f5) = 1;
    *((char*)this + 0x30f6) = 0x13;
    *((char*)this + 0x30f7) = 2;
    *((char*)this + 0x30f8) = 0;
    *((char*)this + 0x30f9) = 1;
    *((char*)this + 0x30fa) = 6;
    *((char*)this + 0x30ff) = 0x17;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3358) = 0;
    }
}

void CMisuzu::Vf12()
{
    int l4c;

    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(int*)((char*)this + 0x3460) = 0;
    *(int*)((char*)this + 0x3458) = 0;
    *(int*)((char*)this + 0x345c) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3464) = 0;
    *(int*)((char*)this + 0x3468) = 0;
    *(int*)((char*)this + 0x346c) = 0;
    *(int*)((char*)this + 0x3470) = 0;
    *(int*)((char*)this + 0x3474) = 0;
    *(int*)((char*)this + 0x3478) = 0;
    *(int*)((char*)this + 0x347c) = 0;
    *(int*)((char*)this + 0x3480) = 0;
    *(short*)((char*)this + 0x2ad0) = -0xd;
    *(short*)((char*)this + 0x2af8) = -0x3c;
    *(short*)((char*)this + 0x2ad2) = 0xe;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0x11;
    *(short*)((char*)this + 0x2afc) = -6;
    *(short*)((char*)this + 0x2ad6) = 7;
    *(short*)((char*)this + 0x2afe) = -0x19;
    *(short*)((char*)this + 0x2ad8) = 0x1b;
    *(short*)((char*)this + 0x2b00) = -0x19;
    l4c = 0;
    for (; l4c < 0x40; l4c++) {
        *(int*)((char*)this + l4c * 4 + 0x3158) = 0;
        *(int*)((char*)this + l4c * 4 + 0x3258) = 0;
        *(int*)((char*)this + l4c * 4 + 0x3358) = 0;
    }
    CPlayer::Vf12();
    EffectDesc l48;
    CPlayer::Unk413090((EffectDesc*)&l48);
    l48.type = 0x190;
    l48.x = 320.0;
    l48.y = -320.0;
    l48.unk20 = 0;
    l48.unk21 = 1;
    l48.unk28 = 1;
    l48.unk0 = 1;
    l48.unk18 = *((char*)this + 0x50);
    Vf9(&l48);
}

void CMisuzu::Vf0()
{
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    CPlayer::Vf0();
}

void CMisuzu::Vf10(short p1)
{
    *(int*)((char*)this + p1 * 4 + 0x3158) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3258) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3358) = 0;
    CPlayer::Vf10(p1);
}

void CMisuzu::Vf3()
{
    CPlayer::Unk40e740();
}

void CMisuzu::Vf4()
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
        if (*(int*)((char*)this + 0x108) < 0xd05 && *(short*)((char*)this + 0x262) == 0x5d && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x168) != 6 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9e0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x13c;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x70 && *(double*)((char*)this + 0x28) == 0.0 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x970)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12e;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x132;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(double*)((char*)this + 0x28) == 0.0 && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x968)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12d;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x131;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6e || *(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(double*)((char*)this + 0x28) == 0.0 && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x960)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12c;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x130;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x84 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9b0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x136;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x83 || *(short*)((char*)this + 0x262) == 0x84) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9b0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x136;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x82 || *(short*)((char*)this + 0x262) == 0x83 || *(short*)((char*)this + 0x262) == 0x84) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9b0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x136;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x66 && *(double*)((char*)this + 0x28) == 0.0 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x135;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(double*)((char*)this + 0x28) == 0.0 && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x134;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x64 || *(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(double*)((char*)this + 0x28) == 0.0 && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x998)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x133;
            return;
        }
        if (*(int*)((char*)this + 0x3150) == 0 && *(short*)((char*)this + 0x262) == 0x48 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0 || *(int*)((char*)this + 0x3464) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x810) && (*(int*)((char*)this + 0x3148) - 0x32 < *(double*)((char*)this + 0x20) && *(int*)((char*)this + 0x3148) + 0x32 > *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == 1 || *(int*)((char*)this + 0x3148) + 0x32 > *(double*)((char*)this + 0x20) && *(int*)((char*)this + 0x3148) - 0x32 < *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == -1)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x102;
            if (*(int*)((char*)this + 0x3464) > 0) {
                *(short*)((char*)this + 8) = 0x13b;
            }
            return;
        }
        if (*(int*)((char*)this + 0x3150) == 0 && (*(short*)((char*)this + 0x262) == 0x47 || *(short*)((char*)this + 0x262) == 0x48) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x808) && (*(int*)((char*)this + 0x3148) - 0x32 < *(double*)((char*)this + 0x20) && *(int*)((char*)this + 0x3148) + 0x32 > *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == 1 || *(int*)((char*)this + 0x3148) + 0x32 > *(double*)((char*)this + 0x20) && *(int*)((char*)this + 0x3148) - 0x32 < *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == -1)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x101;
            if (*(int*)((char*)this + 0x3464) > 0) {
                *(short*)((char*)this + 8) = 0x13a;
            }
            return;
        }
        if (*(int*)((char*)this + 0x3150) == 0 && *(short*)((char*)this + 0x262) == 0x46 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x800) && (*(int*)((char*)this + 0x3148) - 0x32 < *(double*)((char*)this + 0x20) && *(int*)((char*)this + 0x3148) + 0x32 > *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == 1 || *(int*)((char*)this + 0x3148) + 0x32 > *(double*)((char*)this + 0x20) && *(int*)((char*)this + 0x3148) - 0x32 < *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == -1)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x100;
            if (*(int*)((char*)this + 0x3464) > 0) {
                *(short*)((char*)this + 8) = 0x139;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x16 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x828)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x105;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x108;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x15 || *(short*)((char*)this + 0x262) == 0x16) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x820)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x104;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x107;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x14 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x818)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x103;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x106;
            }
            return;
        }
        if (*(int*)((char*)this + 0x3474) == 0 && *(short*)((char*)this + 0x262) == 0x20 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7e0) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfc;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x3e && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x858) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10b;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x3d || *(short*)((char*)this + 0x262) == 0x3e) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x850) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10a;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x3c && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x848) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x109;
            return;
        }
        if (*(int*)((char*)this + 0x3470) == 0 && (*(short*)((char*)this + 0x262) == 0x1f || *(short*)((char*)this + 0x262) == 0x20) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d8) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfb;
            return;
        }
        if (*(int*)((char*)this + 0x346c) == 0 && *(short*)((char*)this + 0x262) == 0x1e && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0) && *(double*)((char*)this + 0x28) == 0.0) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfa;
            return;
        }
        if (*(int*)((char*)this + 0x3480) == 0 && *(short*)((char*)this + 0x262) == 0xc && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xff;
            return;
        }
        if (*(int*)((char*)this + 0x347c) == 0 && (*(short*)((char*)this + 0x262) == 0xb || *(short*)((char*)this + 0x262) == 0xc) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfe;
            return;
        }
        if (*(int*)((char*)this + 0x3478) == 0 && *(short*)((char*)this + 0x262) == 0xa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7e8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfd;
            return;
        }
    }
    if (*(int*)((char*)this + 0x15c) < 1 && (*(short*)((char*)this + 0x262) == 0 || *(short*)((char*)this + 0x262) == 1)) {
        if (*(double*)((char*)this + 0x28) < 0.0 && *(BYTE*)((char*)this + 0x159) < 1) {
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) < 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == (1 - (*(short*)((char*)this + 0x262) << 1)) * -1) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x528) && *(WORD*)((char*)this + 8) != 0xaa && *(double*)((char*)this + 0x28) < -30.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(WORD*)((char*)this + 8) != 0xfd) {
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
            if (((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20)) * (1 - (*(short*)((char*)this + 0x262) << 1)) > 0.0 || 0.0 == *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) && *((char*)this + 0x50) == 1 - (*(short*)((char*)this + 0x262) << 1)) && *(WORD*)((char*)this + 8) != 0xaa && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x530) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
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
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *((char*)this + 0x188) != 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -30.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 30.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6e0) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
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
            }
        }
    }
}

void CMisuzu::Vf1()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (*(int*)((char*)this + 0x3464) > 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x154);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x20 - x1c.x, 0xda - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x115 - x1c.width, 0xda - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3464) > 1) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x154);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x2a - x1c.x, 0xda - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10b - x1c.width, 0xda - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3464) > 2) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x154);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x34 - x1c.x, 0xda - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x101 - x1c.width, 0xda - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3460) > 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x15c);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3460) > 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x164);
        v2c = MakeRect(0, 0, *(int*)((char*)this + 0x345c) * x1c.width / 0xbb8, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, *(int*)((char*)this + 0x345c) * x1c.width / 0xbb8, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - *(int*)((char*)this + 0x345c) * x1c.width / 0xbb8, 0x1f - x1c.y, *(int*)((char*)this + 0x345c) * x1c.width / 0xbb8, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
}

void CMisuzu::Vf8()
{
    if (*(int*)((char*)this + 0x345c) > 0) {
        (*(int*)((char*)this + 0x345c))--;
    }
    if (*(int*)((char*)this + 0x3460) > 0) {
        ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk410ac0(0xcb, 3);
        (*(int*)((char*)this + 0x3458))++;
        if (*(int*)((char*)this + 0x3458) > 0x2d - *(int*)((char*)this + 0x3460) * 7) {
            *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) -= 0xa;
            if (*(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) <= 0) {
                *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) = 1;
            }
            *(int*)((char*)this + 0x3458) = 0;
        }
        if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
            *(int*)((char*)this + 0x3460) = 0;
            *(int*)((char*)this + 0x345c) = 0;
        }
    }
    if (*(int*)((char*)this + 0x345c) <= 0 && *(int*)((char*)this + 0x3460) > 0 || *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) <= 0) {
        *(int*)((char*)this + 0x3460) = 0;
        *(int*)((char*)this + 0x345c) = 0;
    }
}

void CMisuzu::Vf9(EffectDesc* p1)
{
    Vf10(*(short*)((char*)this + 0x2ca));
    CPlayer::Vf9(p1);
}

void CMisuzu::Vf2()
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
        if ((v5 & 0xf) == 4 && x6 == 3) {
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
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x82 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 3) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x82 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 4;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 1) {
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
    v4 = *(short*)((char*)this + 0x260) + 0x87;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x3c + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (*((char*)this + 0x50) == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                *(short*)((char*)this + 0x262) = ((v5 & 0xe0) > 0) + 0x3c + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
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

void CMisuzu::Vf5()
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
            if (v10 < 45.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
        }
        if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xc9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xca || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xcd) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0 && v10 > 60.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
            *((char*)this + 0x18b) = 1;
            *((char*)this + 0x189) = 1;
            *((char*)this + 0x188) = 0;
            return;
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 || *(WORD*)((char*)this + 8) == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 4.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x20;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0xc;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5c;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && v10 < 80.0 && *(short*)((char*)this + 0x148) >= 0x7d0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x65;
                return;
            }
        }
        if (v10 < 150.0 && v10 > 100.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0xc;
                return;
            }
            if (v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
                *((char*)this + 0x18a) = 2;
                *((char*)this + 0x189) = 0;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(short*)((char*)this + 0x148) == 0xbb8 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xdc) {
                *(short*)((char*)this + 0x262) = 0x5c;
                return;
            }
        }
        if (v10 > 150.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x1e;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xb;
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xaa && *(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *(int*)((char*)this + 0x3114) = 3;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -40.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18a) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -100.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18b) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -50.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18c) = 1;
            *((char*)this + 0x189) = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x1f;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 3 && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x20;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 5 && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0xc;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x3e8) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x64;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x12 && *(int*)((char*)this + 0x3110) > 0x14 && *(short*)((char*)this + 0x148) == 0xbb8) {
            *(short*)((char*)this + 0x262) = 0x5c;
            return;
        }
        if (*(int*)((char*)this + 0x3110) > 0x41) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 2 && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x20;
            return;
        }
        if (*(int*)((char*)this + 0x3110) > 0x3a) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
    }
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d && (*(WORD*)((char*)this + 8) == 0xfb || *(WORD*)((char*)this + 8) == 0xe8 && (WORD)CPlayer::Unk4108a0(0, 0xa) == 0 || *(WORD*)((char*)this + 8) == 0xfa && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2 || *(WORD*)((char*)this + 8) == 0xeb && (WORD)CPlayer::Unk4108a0(0, 7) == 0)) {
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
        *((char*)this + 0x18b) = 1;
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
        *((char*)this + 0x18c) = 1;
        if (*(WORD*)((char*)this + 8) == 0xe8) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xc && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 0xd;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xd && *(WORD*)((char*)this + 8) == 0xa3) {
        *((char*)this + 0x18a) = 1;
        *((char*)this + 0x189) = 1;
        if (*(WORD*)((char*)this + 8) == 0xe6) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xe && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 0xf;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0xf && *(WORD*)((char*)this + 8) == 0xa3) {
        *((char*)this + 0x18b) = 1;
        *((char*)this + 0x189) = 1;
        if (*(WORD*)((char*)this + 8) == 0xe7) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0x10 && *(WORD*)((char*)this + 8) < 0x32) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        if (*(WORD*)((char*)this + 8) == 0xa3) {
            *(int*)((char*)this + 0x3114) = 0x11;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0x11 && *(WORD*)((char*)this + 8) == 0xa3) {
        *((char*)this + 0x18c) = 1;
        *((char*)this + 0x189) = 1;
        if (*(WORD*)((char*)this + 8) == 0xe8) {
            *(int*)((char*)this + 0x3114) = 0;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3114) == 0x14 && *(WORD*)((char*)this + 8) < 0x32) {
        *((char*)this + 0x18a) = 1;
        *((char*)this + 0x189) = 1;
        if (*(WORD*)((char*)this + 8) == 0xcc) {
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
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && v10 < 90.0 && *(int*)((char*)this + 0x3110) < 0x258 && *(int*)((char*)this + 0x3110) > 0x12c) {
                *(int*)((char*)this + 0x3114) = 6;
                return;
            }
            if (v10 < 80.0 && *(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 70.0 && *(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x258) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3ca) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xc;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x14;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xc9) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x226) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x226 && *(int*)((char*)this + 0x3110) < 0x258 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x64;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x2ee) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x64) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x15e && v10 < 110.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x258 && v10 < 80.0) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xc;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x14;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xca) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x96) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x96 && *(int*)((char*)this + 0x3110) < 0xc8 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x64;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1f4) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xc;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xe;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcb) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x12c && *(double*)((char*)this + 0x118) > 350.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x28a && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcc) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && v10 < 90.0 && *(int*)((char*)this + 0x3110) < 0x258 && *(int*)((char*)this + 0x3110) > 0x12c) {
                *(int*)((char*)this + 0x3114) = 6;
                return;
            }
            if (v10 < 70.0 && *(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (v10 < 80.0 && *(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x258) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3ca) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x320) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xc;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x14;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcd) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x226) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x226 && *(int*)((char*)this + 0x3110) < 0x258 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x64;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x64) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x15e && v10 < 110.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x226 && v10 < 90.0) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x226 && *(int*)((char*)this + 0x3110) < 0x276 && *(int*)((char*)this + 0x168) == 2) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3b6) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1f4) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xc;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x14;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xce) {
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x28a && *(int*)((char*)this + 0x3110) < 0x258 && *(double*)((char*)this + 0x118) > 350.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x28a && *(int*)((char*)this + 0x3110) < 0x320) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x320 && *(int*)((char*)this + 0x3110) < 0x352 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384) {
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
            if (*(int*)((char*)this + 0x3110) > 0x14 && *(int*)((char*)this + 0x3110) < 0x3c && *(int*)((char*)this + 0x168) == 3 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
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
            if (*(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x1f;
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
        if (*(WORD*)((char*)this + 8) == 0xe7) {
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 350.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x28a && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xc;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x14;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xfa && *(int*)((char*)this + 0x3110) > 0x258 && *(double*)((char*)this + 0x28) == 0.0) {
            *(int*)((char*)this + 0x3114) = 1;
            if (v10 < 50.0) {
                *(int*)((char*)this + 0x3114) = 0x14;
            }
            return;
        }
        if (*(WORD*)((char*)this + 8) == 0xe9 && *(int*)((char*)this + 0x3110) > 0x1f4) {
            *(int*)((char*)this + 0x3114) = 1;
            if (v10 < 50.0) {
                *(int*)((char*)this + 0x3114) = 0x14;
            }
            return;
        }
        if (*(WORD*)((char*)this + 8) == 0xea) {
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x190 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 350.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x28a && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 8;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xc;
                }
                if ((WORD)CPlayer::Unk4108a0(0, 4) == 0) {
                    *(int*)((char*)this + 0x3114) = 0xe;
                }
                if (v10 < 50.0 && (WORD)CPlayer::Unk4108a0(0, 2) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x14;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xeb && *(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x258) {
            *(short*)((char*)this + 0x262) = 0x1e;
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
                if (v10 < 50.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0xf) {
                        *((char*)this + 0x18a) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                }
                if (v10 < 65.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0x14) {
                        *((char*)this + 0x18a) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                }
                if (v10 > 60.0 && v10 < 90.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0x23 && *(int*)((char*)this + 0x3110) > 0x1e) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                }
                if (0x46 - (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x46 < v10 && v10 < 100.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 2 + 0x54 && *(int*)((char*)this + 0x3110) > 0x50) {
                        *(int*)((char*)this + 0x3114) = 0xc;
                        return;
                    }
                }
                if (0x46 - (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x46 < v10 && v10 < 120.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0x80 && *(int*)((char*)this + 0x3110) > 0x78) {
                        *(int*)((char*)this + 0x3114) = 8;
                        return;
                    }
                }
                if (v10 < 150.0 && v10 > 120.0 && *(int*)((char*)this + 0x3110) < 0x7e && *(int*)((char*)this + 0x3110) > 0x78) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 120.0 && v10 > 70.0 && *(int*)((char*)this + 0x3110) < 0x91 && *(int*)((char*)this + 0x3110) > 0x82) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (0x50 - (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x50 < v10 && v10 < 130.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0x9b && *(int*)((char*)this + 0x3110) > 0x91) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                        return;
                    }
                }
                if (0x5a - (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x5a < v10 && v10 < 140.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0xb4 && *(int*)((char*)this + 0x3110) > 0xa5) {
                        *(int*)((char*)this + 0x3114) = 0xa;
                        return;
                    }
                }
                if (v10 > 110.0 && v10 < 160.0 && *(int*)((char*)this + 0x3110) < 0xcd && *(int*)((char*)this + 0x3110) > 0xc8) {
                    *(int*)((char*)this + 0x3114) = 0xa;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0xeb && *(int*)((char*)this + 0x3110) > 0xdc && *(double*)((char*)this + 0x118) > 500.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7) {
                    *(short*)((char*)this + 0x262) = 0x20;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0xf0 && *(int*)((char*)this + 0x3110) > 0xeb && *(short*)((char*)this + 0x148) >= 0x7d0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x65;
                    return;
                }
                if (v10 < 100.0 && *(int*)((char*)this + 0x3110) < 0xf2 && *(int*)((char*)this + 0x3110) > 0xf0 && *(short*)((char*)this + 0x148) == 0xbb8 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7) {
                    *(short*)((char*)this + 0x262) = 0x5c;
                    return;
                }
                if (v10 > 100.0 && v10 < 130.0 && *(int*)((char*)this + 0x3110) < 0x136 && *(int*)((char*)this + 0x3110) > 0x12c) {
                    *(short*)((char*)this + 0x262) = 0xa;
                    return;
                }
                if (v10 > 130.0 && v10 < 180.0 && *(int*)((char*)this + 0x3110) < 0x13b && *(int*)((char*)this + 0x3110) > 0x136) {
                    *(short*)((char*)this + 0x262) = 0xb;
                    return;
                }
                if (v10 > 90.0 && v10 < 140.0 && *(int*)((char*)this + 0x3110) < 0x14a && *(int*)((char*)this + 0x3110) > 0x140) {
                    *(short*)((char*)this + 0x262) = 0x1e;
                    return;
                }
                if (v10 > 90.0 && v10 < 140.0 && *(int*)((char*)this + 0x3110) < 0x154 && *(int*)((char*)this + 0x3110) > 0x14a && *(double*)((char*)this + 0x118) > 500.0) {
                    *(short*)((char*)this + 0x262) = 0x1f;
                    return;
                }
                if (*(int*)((char*)this + 0x3110) < 0x2ee && *(int*)((char*)this + 0x3110) > 0x2bc && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c && v10 > 100.0) {
                    *(int*)((char*)this + 0x3114) = 5;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) < 0.0 && v10 < 80.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) < 0xa) {
                    *((char*)this + 0x189) = -1;
                    *((char*)this + 0x188) = -*((char*)this + 0x50);
                    return;
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && *(int*)((char*)this + 0x3110) < 6 && (*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0)) {
                        *(short*)((char*)this + 0x262) = 0x16;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 140.0 && x8 > 100.0 && *(int*)((char*)this + 0x3110) < 0x2d && *(int*)((char*)this + 0x3110) > 0xa) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 170.0 && x8 > 150.0 && *(int*)((char*)this + 0x3110) < 0x50 && *(int*)((char*)this + 0x3110) > 0x2d) {
                        *((char*)this + 0x18c) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 > 120.0 && v10 < 140.0 && x8 < 150.0 && x8 > 120.0 && *(int*)((char*)this + 0x3110) < 0x6e && *(int*)((char*)this + 0x3110) > 0x50) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 < 70.0 && *(int*)((char*)this + 0x3110) < 0xd2 && *(int*)((char*)this + 0x3110) > 0xc8 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && x8 < 90.0 && *(short*)((char*)this + 0x148) >= 0x7d0) {
                        *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x65;
                        return;
                    }
                    if (v10 < 100.0 && *(int*)((char*)this + 0x3110) < 0x12e && *(int*)((char*)this + 0x3110) > 0x12c && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && x8 < 100.0 && *(short*)((char*)this + 0x148) == 0xbb8) {
                        *(short*)((char*)this + 0x262) = 0x5c;
                        return;
                    }
                }
            }
        }
        if (*(double*)((char*)this + 0x28) < 0.0 && *(int*)((char*)this + 0x3114) != 3) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && *(int*)((char*)this + 0x3110) < 0x64) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 90.0 && x8 < 120.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0xb4) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 110.0 && x8 > 0.0 && x8 < 70.0 && *(int*)((char*)this + 0x3110) > 0xb4 && *(int*)((char*)this + 0x3110) < 0xf0) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) > 0xf0 && *(int*)((char*)this + 0x3110) < 0xf2 && x8 > 80.0) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x6e;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && *(int*)((char*)this + 0x3110) < 0x14) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 90.0 && x8 > 90.0 && x8 < 120.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) > 0x14 && *(int*)((char*)this + 0x3110) < 0x28) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 110.0 && x8 > 0.0 && x8 < 50.0 && *(int*)((char*)this + 0x3110) > 0x28 && *(int*)((char*)this + 0x3110) < 0x32) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
            }
        }
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 4.0f * *(float*)((char*)this + 0xa8) && v10 > 120.0) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        return;
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 && v10 > 800.0 && v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2.0f * *(float*)((char*)this + 0xa8) && *(double*)((char*)this + 0x20) > 150.0 && *(double*)((char*)this + 0x20) < 490.0) {
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
        if (v10 > 180.0 && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 2) {
            *((char*)this + 0x188) = 0;
            *((char*)this + 0x189) = -1;
            return;
        }
        if (v10 < 170.0 && v10 > 140.0 && *(double*)((char*)this + 0x28) == 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32) {
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x32) {
        if (*((char*)this + 0x50) == 1) {
            *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
        } else {
            *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
        }
        return;
    }
    if (*((char*)this + 0x50) == -1) {
        *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
        return;
    }
    *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x3c;
}

void CMisuzu::Vf7()
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
                *(int*)((char*)this + 0x314c) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                *(int*)((char*)this + 0x3148) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *((char*)this + v4 * 0x98 + 0x518) = *((char*)this + 0x50);
                if (*(WORD*)((char*)this + 8) == 0x100 && *(WORD*)((char*)this + 0xa) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x199;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    break;
                }
                if (*(WORD*)((char*)this + 8) == 0x101 && *(WORD*)((char*)this + 0xa) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x19a;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    break;
                }
                if (*(WORD*)((char*)this + 8) == 0x102 && *(WORD*)((char*)this + 0xa) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x19b;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    break;
                }
                if (*(WORD*)((char*)this + 8) == 0x139 && *(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1bb;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 1;
                    break;
                }
                if (*(WORD*)((char*)this + 8) == 0x13a && *(WORD*)((char*)this + 0xa) == 2 && *(WORD*)((char*)this + 0xc) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1bc;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 1;
                    break;
                }
                if (*(WORD*)((char*)this + 8) == 0x13b) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1bd;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 1;
                    break;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (*(double*)((char*)this + 0x20) - *((char*)this + 0x50) * 0x2d - *(double*)((char*)this + v4 * 0x98 + 0x4e8)) / 640.0 * 12.0 * *((char*)this + v4 * 0x98 + 0x518);
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.02 && *(double*)((char*)this + v4 * 0x98 + 0x4f8) > -0.02) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < -1.6) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -1.6;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) > 1.6) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.6;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) = (*(double*)((char*)this + 0x28) - 100.0 - *(double*)((char*)this + v4 * 0x98 + 0x4f0)) / 480.0 * 12.0;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.002 && *(double*)((char*)this + v4 * 0x98 + 0x500) > -0.002) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.6) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.6;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -0.6) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.6;
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
            case 0x191:
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
            case 0x193:
                *(int*)((char*)this + 0x346c) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3258) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < *(double*)((char*)this + v4 * 0x98 + 0x4e8) + 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 40.0 < *(double*)((char*)this + v4 * 0x98 + 0x4f0) + 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 40.0 > *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x60) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 2;
                        *((char*)this + 0x2c8) = 2;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    }
                    if ((*(WORD*)((char*)this + 8) == 0xfa || *(WORD*)((char*)this + 8) == 0xfc) && *(WORD*)((char*)this + 0xa) <= 1 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x346c) = 0;
                        break;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x3c;
                    *(short*)((char*)this + v4 * 0x98 + 0x556) = 0x3c;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x346c) = 0;
                        break;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x346c) = 0;
                    }
                }
                break;
            case 0x194:
                *(int*)((char*)this + 0x3470) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3258) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < *(double*)((char*)this + v4 * 0x98 + 0x4e8) + 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 40.0 < *(double*)((char*)this + v4 * 0x98 + 0x4f0) + 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 40.0 > *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x60) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 2;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *((char*)this + 0x2c8) = 2;
                    }
                    if ((*(WORD*)((char*)this + 8) == 0xfb || *(WORD*)((char*)this + 8) == 0xfc) && *(WORD*)((char*)this + 0xa) <= 1 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3470) = 0;
                        break;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x3c;
                    *(short*)((char*)this + v4 * 0x98 + 0x556) = 0x3c;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3470) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3470) = 0;
                    }
                }
                break;
            case 0x195:
                *(int*)((char*)this + 0x3474) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3258) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < *(double*)((char*)this + v4 * 0x98 + 0x4e8) + 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 40.0 < *(double*)((char*)this + v4 * 0x98 + 0x4f0) + 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) - 40.0 > *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x60) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 2;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *((char*)this + 0x2c8) = 2;
                    }
                    if (*(WORD*)((char*)this + 8) == 0xfc && *(WORD*)((char*)this + 0xa) <= 1 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3474) = 0;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0x5a;
                    *(short*)((char*)this + v4 * 0x98 + 0x556) = 0x5a;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3474) = 0;
                        break;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3474) = 0;
                    }
                }
                break;
            case 0x196:
                *(int*)((char*)this + 0x3478) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3258) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) > 0x14) {
                    if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < *(double*)((char*)this + v4 * 0x98 + 0x4e8) + 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    }
                    if ((*(WORD*)((char*)this + 8) == 0xfd || *(WORD*)((char*)this + 8) == 0xff) && *(WORD*)((char*)this + 0xa) == 0 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                        l50.type = 0;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                        Vf10(v4);
                        *(int*)((char*)this + 0x3478) = 0;
                        break;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *((char*)this + 0x2c8) = 0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3478) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc && *(int*)((char*)this + v4 * 4 + 0x3258) < 3) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3478) = 0;
                    }
                }
                break;
            case 0x197:
                *(int*)((char*)this + 0x347c) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3258) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) > 0x14) {
                    if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < *(double*)((char*)this + v4 * 0x98 + 0x4e8) + 50.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    }
                    if ((*(WORD*)((char*)this + 8) == 0xfe || *(WORD*)((char*)this + 8) == 0xff) && *(WORD*)((char*)this + 0xa) == 0 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
                        l50.type = 0;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                        Vf10(v4);
                        *(int*)((char*)this + 0x347c) = 0;
                        break;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *((char*)this + 0x2c8) = 0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x347c) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc && *(int*)((char*)this + v4 * 4 + 0x3258) < 3) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x347c) = 0;
                    }
                }
                break;
            case 0x198:
                *(int*)((char*)this + 0x3480) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3258) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) > 0x14) {
                    if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < *(double*)((char*)this + v4 * 0x98 + 0x4e8) + 70.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 70.0) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    }
                    if (*(WORD*)((char*)this + 8) == 0xff && *(WORD*)((char*)this + 0xa) == 0 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 4 || *(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3480) = 0;
                        break;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *((char*)this + 0x2c8) = 0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3480) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3480) = 0;
                    }
                }
                break;
            case 0x199:
                *(int*)((char*)this + 0x3148) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *(int*)((char*)this + 0x314c) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                *(int*)((char*)this + 0x3150) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *((char*)this + 0x2c8) = 4;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *((char*)this + 0x2c8) = 5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.06;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x190;
                        *(int*)((char*)this + 0x3150) = 0;
                    }
                }
                break;
            case 0x19a:
                *(int*)((char*)this + 0x3148) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *(int*)((char*)this + 0x314c) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                *(int*)((char*)this + 0x3150) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *((char*)this + 0x2c8) = 4;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.02;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                    *((char*)this + 0x2c8) = 5;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.06;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x190;
                        *(int*)((char*)this + 0x3150) = 0;
                    }
                }
                break;
            case 0x19b:
                *(int*)((char*)this + 0x3148) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                *(int*)((char*)this + 0x314c) = (int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                *(int*)((char*)this + 0x3150) = 1;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 5;
                    *((char*)this + 0x2c8) = 4;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.015;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 1.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.4;
                        *((char*)this + 0x2c8) = 5;
                        l50.type = 0x19c;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + 0x50);
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 && *(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x190;
                        *(int*)((char*)this + 0x3150) = 0;
                    }
                }
                break;
            case 0x19c:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(int*)((char*)this + 0x3148);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(int*)((char*)this + 0x314c);
                if (*(int*)((char*)this + 0x314c) > 0) {
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
            case 0x19d:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                if (*(WORD*)((char*)this + 0xa) > 0x18 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) != 0x109) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        l50.type = 0x19e;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 55.0;
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        *((char*)this + 0x2c8) = 7;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                }
                break;
            case 0x19e:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) != 1) {
                        l50.type = 0x1c8;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19f:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.125;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.35;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 4 + 0x3358) > 0x14 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(int*)((char*)this + v4 * 4 + 0x3258) > 0x4b0 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 760.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -120.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                        (*(int*)((char*)this + 0x3460))++;
                        if (*(int*)((char*)this + 0x345c) == 0) {
                            *(int*)((char*)this + 0x345c) = 0xbb8;
                        } else {
                            *(int*)((char*)this + 0x345c) += 0x3e8;
                            if (*(int*)((char*)this + 0x345c) > 0xbb8) {
                                *(int*)((char*)this + 0x345c) = 0xbb8;
                            }
                        }
                    }
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.01;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = -0.01;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -0.5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) > 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                    }
                }
                break;
            case 0x1a0:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                if (*(WORD*)((char*)this + 0xa) > 0x18 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) != 0x10a) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        l50.type = 0x1a1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 55.0;
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                        *((char*)this + 0x2c8) = 7;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                }
                break;
            case 0x1a1:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) != 1) {
                        l50.type = 0x1c9;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a2:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.15;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 4 + 0x3358) > 6 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(int*)((char*)this + v4 * 4 + 0x3258) > 0x4b0 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 760.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -120.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                        (*(int*)((char*)this + 0x3460))++;
                        if (*(int*)((char*)this + 0x345c) == 0) {
                            *(int*)((char*)this + 0x345c) = 0xbb8;
                        } else {
                            *(int*)((char*)this + 0x345c) += 0x3e8;
                            if (*(int*)((char*)this + 0x345c) > 0xbb8) {
                                *(int*)((char*)this + 0x345c) = 0xbb8;
                            }
                        }
                    }
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.01;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.7) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = -0.01;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -0.5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) > 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                    }
                }
                break;
            case 0x1a3:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28);
                if (*(WORD*)((char*)this + 0xa) > 0x18 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) != 0x10b) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        l50.type = 0x1a4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 55.0;
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                        *((char*)this + 0x2c8) = 8;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                }
                break;
            case 0x1a4:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) != 1) {
                        l50.type = 0x1ca;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a5:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.2;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 4 + 0x3358) > 0x12 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(int*)((char*)this + v4 * 4 + 0x3258) > 0x4b0 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 760.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -120.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                        (*(int*)((char*)this + 0x3460))++;
                        if (*(int*)((char*)this + 0x345c) == 0) {
                            *(int*)((char*)this + 0x345c) = 0xbb8;
                        } else {
                            *(int*)((char*)this + 0x345c) += 0x3e8;
                            if (*(int*)((char*)this + 0x345c) > 0xbb8) {
                                *(int*)((char*)this + 0x345c) = 0xbb8;
                            }
                        }
                    }
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.01;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.58) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = -0.01;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -0.5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) > 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                    }
                }
                break;
            case 0x1a6:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.4;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.7;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 4 + 0x3358) > 0x12 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(int*)((char*)this + v4 * 4 + 0x3258) > 0x4b0 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 760.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -120.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                        (*(int*)((char*)this + 0x3460))++;
                        if (*(int*)((char*)this + 0x345c) == 0) {
                            *(int*)((char*)this + 0x345c) = 0xbb8;
                        } else {
                            *(int*)((char*)this + 0x345c) += 0x3e8;
                            if (*(int*)((char*)this + 0x345c) > 0xbb8) {
                                *(int*)((char*)this + 0x345c) = 0xbb8;
                            }
                        }
                    }
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.01;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.58) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = -0.01;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -0.5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) > 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                    }
                }
                break;
            case 0x1a7:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.3;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.6;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 4 + 0x3358) > 0x12 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(int*)((char*)this + v4 * 4 + 0x3258) > 0x4b0 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 760.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -120.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                        (*(int*)((char*)this + 0x3460))++;
                        *(int*)((char*)this + 0x345c) = 0xbb8;
                    }
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.01;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.7) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = -0.01;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -0.5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) > 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                    }
                }
                break;
            case 0x1a8:
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
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                    (*(int*)((char*)this + 0x3460))++;
                    *(int*)((char*)this + 0x345c) = 0xbb8;
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
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
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                    *(int*)((char*)this + 0x3460) += 3;
                    *(int*)((char*)this + 0x345c) = 0xbb8;
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
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
            case 0x1ab:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                    *(int*)((char*)this + 0x3460) += 5;
                    *(int*)((char*)this + 0x345c) = 0xbb8;
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0 + (WORD)CPlayer::Unk4108a0(0, 0x64);
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
            case 0x1ac:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x28) * 0.1 + -2.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.8 - (WORD)CPlayer::Unk4108a0(0, 0x28) * 0.1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 0xb;
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
            case 0x1ad:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x28) * 0.1 + -2.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.8 - (WORD)CPlayer::Unk4108a0(0, 0x28) * 0.1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 0xb;
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
            case 0x1ae:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x28) * 0.1 + -2.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.8 - (WORD)CPlayer::Unk4108a0(0, 0x28) * 0.1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    Vf9(&l50);
                    l50.type = (WORD)CPlayer::Unk4108a0(0, 4) + 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0 + (WORD)CPlayer::Unk4108a0(0, 0x14);
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 0xb;
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
            case 0x1af:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + -1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.8 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
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
            case 0x1b0:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + -1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.8 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
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
            case 0x1b1:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + -1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.8 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
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
            case 0x1b2:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + -1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.8 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
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
            case 0x1b3:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                    l50.type = 0x1c0;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 120.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
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
            case 0x1b4:
                if (*(WORD*)((char*)this + 8) != 0x133) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1ba;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b5;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x23;
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 6.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8 && *(int*)((char*)this + v4 * 4 + 0x3158) < 0x14) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1ba;
                    }
                }
                break;
            case 0x1b5:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + 1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -(WORD)CPlayer::Unk4108a0(0, 5) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.007;
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
            case 0x1b6:
                if (*(WORD*)((char*)this + 8) != 0x134) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1ba;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b7;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x14;
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 30.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9 && *(int*)((char*)this + v4 * 4 + 0x3158) < 0x14) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1ba;
                    }
                }
                break;
            case 0x1b7:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + 1.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.01;
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
            case 0x1b8:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -6.8;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.059;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 5.0;
                }
                if (*(WORD*)((char*)this + 8) != 0x135 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 4) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    break;
                }
                if ((*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1b9;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x14;
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) + 55.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 0;
                    Vf9(&l50);
                    (*(int*)((char*)this + 0x3154))++;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3 && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xf) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                        *(int*)((char*)this + 0x3154) = 0;
                    }
                }
                break;
            case 0x1b9:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)(0x2d - (*(int*)((char*)this + 0x3154) << 1)), 4.0);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.03;
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.025;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.5;
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
            case 0x1ba:
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
            case 0x1bb:
                *(int*)((char*)this + 0x3150) = 1;
                if (*(WORD*)((char*)this + 8) != 0x139) {
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.05;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    l50.type = 0x1bf;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk30 = 1;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.7;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 2;
                        break;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe && *(short*)((char*)this + 0x14c) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= 0x1e) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xf;
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 0;
                }
                if (*(int*)((char*)this + 0x3138) > 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 6;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x1b && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1bf;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 40.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x15) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x16 && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xa) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x190;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + 0x3150) = 0;
                    }
                }
                break;
            case 0x1bc:
                *(int*)((char*)this + 0x3150) = 1;
                if (*(WORD*)((char*)this + 8) != 0x13a) {
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.035;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    l50.type = 0x1bf;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk30 = 1;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.7;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 2;
                        break;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3 && *(short*)((char*)this + 0x14c) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1be;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x24;
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 56.0;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + 0x3468) = 1;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x12 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1bf;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 40.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x190;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + 0x3468) = 0;
                        *(int*)((char*)this + 0x3150) = 0;
                    }
                }
                break;
            case 0x1bd:
                *(int*)((char*)this + 0x3150) = 1;
                if (*(WORD*)((char*)this + 8) != 0x13b) {
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.035;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0xa;
                    l50.type = 0x1bf;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk30 = 1;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.7;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 2;
                        break;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3 && *(short*)((char*)this + 0x14c) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 4;
                    *(int*)((char*)this + v4 * 0x98 + 0x558) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.052;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 7 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 0xb) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.015;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1bf;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 40.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9 && *(int*)((char*)this + v4 * 4 + 0x3258) < 4) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x190;
                        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(int*)((char*)this + 0x3468) = 0;
                        *(int*)((char*)this + 0x3150) = 0;
                    }
                }
                break;
            case 0x1be:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.2;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.3;
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                }
                if (*(int*)((char*)this + 0x3468) == 1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0x63;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.5;
                    l50.type = 0;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    *((char*)this + 0x2c9) = 2;
                    l50.unk21 = 1;
                    ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 680.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -40.0) {
                    Vf10(v4);
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
            case 0x1bf:
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
            case 0x1c0:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -3.0;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.045;
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
            case 0x1c1:
                *(int*)((char*)this + v4 * 0x98 + 0x55c) = 0x7530;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x10 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) -= 0x1388;
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x140) = 0x7530;
                    if (*((char*)this + 0xac) + 1 < *(*(char**)((char*)this + 0x7c) + 0x134e) || *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) > 0) {
                        *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x63;
                        *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0xc) = 0;
                        *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0xa) = 0;
                        *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0;
                        *(short*)((char*)this + 0xa) = 0;
                        *(short*)((char*)this + 0xc) = 0;
                        *(short*)((char*)this + 8) = 0x13d;
                    }
                }
                *(short*)((char*)this + 0x14c) = 2;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x10 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0x1c2) {
                    ((CGame*)*(int*)((char*)this + 0x7c))->FlashWhite(0x32, 0x64, 0x64);
                    if (*(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) <= 0 && *((char*)this + 0xac) + 1 == *(*(char**)((char*)this + 0x7c) + 0x134e)) {
                        ((CGame*)*(int*)((char*)this + 0x7c))->FlashWhite(0x32, 0x64, 0x50);
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x11 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0x258) {
                    ((CGame*)*(int*)((char*)this + 0x7c))->FlashWhite(0x32, 0x64, 0x50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x12 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0x384) {
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x140) = 0;
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = 0;
                    *(short*)((char*)this + 0x14c) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) <= 0x1388 && *((char*)this + 0xac) + 1 == *(*(char**)((char*)this + 0x7c) + 0x134e)) {
                        *((char*)this + 0x2c8) = 0xd;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x11) {
                        if (*(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) <= 0 && *((char*)this + 0xac) + 1 == *(*(char**)((char*)this + 0x7c) + 0x134e)) {
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0x11;
                        } else {
                            Vf10(v4);
                            *(short*)(*(char**)((char*)this + 0x7c) + 0x1420e) = 0;
                            *(short*)(*(char**)(*(char**)*(char**)((char*)this + 0x78) + 0x7c) + 0x1420e) = 0;
                            *(short*)(*(char**)((char*)this + 0x7c) + 0x1420c) = 0;
                        }
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c2:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 7 + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 42.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1c3;
                    }
                }
                break;
            case 0x1c3:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 7 + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 42.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *((char*)this + 0x2c8) = 0xc;
                    l50.type = 0x1c4;
                    l50.x = *((char*)this + 0x50) * 9 + *(double*)((char*)this + 0x20);
                    l50.y = *(double*)((char*)this + 0x28) - 53.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 0;
                    l50.unk30 = 1;
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
            case 0x1c4:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *((char*)this + 0x50) * 9 + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 53.0;
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
            case 0x1c5:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.15;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -1.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) >= -75.0 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 4 + 0x3358) > 0x14 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(int*)((char*)this + v4 * 4 + 0x3258) > 0x4b0 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 760.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -120.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                        (*(int*)((char*)this + 0x3460))++;
                        if (*(int*)((char*)this + 0x345c) == 0) {
                            *(int*)((char*)this + 0x345c) = 0xbb8;
                        } else {
                            *(int*)((char*)this + 0x345c) += 0x3e8;
                            if (*(int*)((char*)this + 0x345c) > 0xbb8) {
                                *(int*)((char*)this + 0x345c) = 0xbb8;
                            }
                        }
                    }
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.01;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(double*)((char*)this + v4 * 0x98 + 0x508) = 0.01;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.7) {
                    *(double*)((char*)this + v4 * 0x98 + 0x508) = -0.01;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < -0.7) {
                    *(double*)((char*)this + v4 * 0x98 + 0x508) = 0.01;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) > 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) + *(double*)((char*)this + v4 * 0x98 + 0x508);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                    }
                }
                break;
            case 0x1c6:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -0.3;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 4 + 0x3358) > 6 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(int*)((char*)this + v4 * 4 + 0x3258) > 0x4b0 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 760.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -120.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                        (*(int*)((char*)this + 0x3460))++;
                        if (*(int*)((char*)this + 0x345c) == 0) {
                            *(int*)((char*)this + 0x345c) = 0xbb8;
                        } else {
                            *(int*)((char*)this + 0x345c) += 0x3e8;
                            if (*(int*)((char*)this + 0x345c) > 0xbb8) {
                                *(int*)((char*)this + 0x345c) = 0xbb8;
                            }
                        }
                    }
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    break;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.01;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) > 0.7) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = -0.01;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < -0.7) {
                    *(double*)((char*)this + v4 * 0x98 + 0x510) = 0.01;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) > 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x510);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                    }
                }
                break;
            case 0x1c7:
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.01 + 0.05;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xc8) * 0.01 - 1.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x508) = -0.01;
                    } else {
                        *(double*)((char*)this + v4 * 0x98 + 0x508) = 0.01;
                    }
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) + *(double*)((char*)this + v4 * 0x98 + 0x4f0) >= -75.0 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(int*)((char*)this + v4 * 4 + 0x3358) > 0x14 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 0 || *(int*)((char*)this + v4 * 4 + 0x3258) > 0x4b0 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 760.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -120.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3) {
                        (*(int*)((char*)this + 0x3460))++;
                        if (*(int*)((char*)this + 0x345c) == 0) {
                            *(int*)((char*)this + 0x345c) = 0xbb8;
                        } else {
                            *(int*)((char*)this + 0x345c) += 0x3e8;
                            if (*(int*)((char*)this + 0x345c) > 0xbb8) {
                                *(int*)((char*)this + 0x345c) = 0xbb8;
                            }
                        }
                    }
                    if (*(int*)((char*)this + 0x3460) > 5) {
                        *(int*)((char*)this + 0x3460) = 5;
                    }
                    break;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) > 1.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x508) = -0.01;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < -1.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x508) = 0.01;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3158) > 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) + *(double*)((char*)this + v4 * 0x98 + 0x508);
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                    }
                }
                break;
            case 0x1c8:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.5;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 5.0 && *(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -5.0) {
                    l50.type = 0x1cb;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        l50.type = 0x1cb;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                        Vf10(v4);
                    }
                }
                break;
            case 0x1c9:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && (*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > 0.0 && *((char*)this + v4 * 0x98 + 0x518) == 1 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 0.0 && *((char*)this + v4 * 0x98 + 0x518) == -1)) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 2;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        l50.type = 0x1cc;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                        Vf10(v4);
                        break;
                    }
                }
                break;
            case 0x1ca:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 4.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.5;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 5.0 && *(double*)((char*)this + v4 * 0x98 + 0x4e8) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -5.0) {
                    l50.type = 0x1cd;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    Vf10(v4);
                    break;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1a8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        l50.type = 0x1cd;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                        Vf10(v4);
                    }
                }
                break;
            case 0x1cb:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) != 1) {
                        l50.type = 0x1c5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1cc:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) != 1) {
                        l50.type = 0x1c6;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1cd:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96 || *(WORD*)((char*)this + 8) > 0x108 && *(WORD*)((char*)this + 8) < 0x10c && *(WORD*)((char*)this + 0xa) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa && *(int*)((char*)this + v4 * 4 + 0x3158) != 1) {
                        l50.type = 0x1c7;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        Vf9(&l50);
                        Vf9(&l50);
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
