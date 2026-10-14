// CMio (0x588310-0x59c49f): the character class whose files are in mio\ in the game
// folder (mio.dat sprites, mio.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; the VfN methods override
// the CPlayer virtual slots of the same number (see shiori.cpp for what they do).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMio::CMio(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy((char*)this + 0x94, "mio");
    *(short*)((char*)this + 0x18) = 0x354;
    *(int*)((char*)this + 0x3138) = 0;
    *(double*)((char*)this + 0x3140) = 0.0;
    *(double*)((char*)this + 0x3148) = 0.0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    *(short*)((char*)this + 0x2ad0) = -0x16;
    *(short*)((char*)this + 0x2af8) = -0x38;
    *(short*)((char*)this + 0x2ad2) = 0x11;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0xf;
    *(short*)((char*)this + 0x2afc) = -0x17;
    *(short*)((char*)this + 0x2ad6) = 0x16;
    *(short*)((char*)this + 0x2afe) = -0x1a;
    *(short*)((char*)this + 0x2ad8) = 0x21;
    *(short*)((char*)this + 0x2b00) = -0x34;
    *((char*)this + 0x30f4) = 5;
    *((char*)this + 0x30f5) = 4;
    *((char*)this + 0x30f6) = 7;
    *((char*)this + 0x30f7) = 1;
    *((char*)this + 0x30ff) = 0xb;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3358) = 0;
    }
}

void CMio::Vf12()
{
    int v4;

    *(int*)((char*)this + 0x3138) = 0;
    *(double*)((char*)this + 0x3140) = 0.0;
    *(double*)((char*)this + 0x3148) = 0.0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    *(short*)((char*)this + 0x2ad0) = -0x16;
    *(short*)((char*)this + 0x2af8) = -0x38;
    *(short*)((char*)this + 0x2ad2) = 0x11;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0xf;
    *(short*)((char*)this + 0x2afc) = -0x17;
    *(short*)((char*)this + 0x2ad6) = 0x16;
    *(short*)((char*)this + 0x2afe) = -0x1a;
    *(short*)((char*)this + 0x2ad8) = 0x21;
    *(short*)((char*)this + 0x2b00) = -0x34;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3358) = 0;
    }
    CPlayer::Vf12();
}

void CMio::Vf0()
{
    *(int*)((char*)this + 0x3138) = 0;
    *(double*)((char*)this + 0x3140) = 0.0;
    *(double*)((char*)this + 0x3148) = 0.0;
    CPlayer::Vf0();
}

void CMio::Vf10(short p1)
{
    *(int*)((char*)this + p1 * 4 + 0x3158) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3258) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3358) = 0;
    CPlayer::Vf10(p1);
}

void CMio::Vf3()
{
    CPlayer::Unk40e740();
}

void CMio::Vf4()
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
    if (*(short*)((char*)this + 0x262) == 0x34 && (*(double*)((char*)this + 0x118) >= 500.0 && *(int*)((char*)this + 0x168) > 1 || *((char*)this + 0x120) > 0 && *(int*)((char*)this + 0x168) > 1 && *(int*)((char*)this + 0x168) != 6) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x538)) {
        Vf0();
        CPlayer::Unk40f170();
        *(short*)((char*)this + 8) = 0xa7;
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *(short*)((char*)this + 8) = 0xab;
        }
        return;
    }
    if (*(int*)((char*)this + 0x3150) == 0) {
        if (*(int*)((char*)this + 0x15c) < 2) {
            if (*(int*)((char*)this + 0x108) < 0xd05 && *(short*)((char*)this + 0x262) == 0x7a && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9d8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x13b;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x70 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9b8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x137;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9b0)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x136;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x6e || *(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x135;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x66 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x988)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x131;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x980)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x130;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x64 || *(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x978)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x12f;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x16 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7e0)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xfc;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x15 || *(short*)((char*)this + 0x262) == 0x16) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xfb;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x14 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xfa;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x20 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(double*)((char*)this + 0x28) == 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x820)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x104;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x1f || *(short*)((char*)this + 0x262) == 0x20) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(double*)((char*)this + 0x28) == 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x818)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x103;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x1e && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(double*)((char*)this + 0x28) == 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x810)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x102;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0xc && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xff;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0xb || *(short*)((char*)this + 0x262) == 0xc) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x878)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10f;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0xa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f0)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xfe;
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
                    *(short*)((char*)this + 0xa) = 3;
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
                    *(short*)((char*)this + 0xa) = 3;
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
        if (*(int*)((char*)this + 0x15c) < 3 && *(short*)((char*)this + 0x262) == 6 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) < 0.0 && *(BYTE*)((char*)this + 0x15a) < 1 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x70)) {
            Vf0();
            CPlayer::Unk40f170();
            CPlayer::Unk40e630();
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
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6f8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *((char*)this + 0x189) == 1) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xdf;
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
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x708) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *((char*)this + 0x188) == *((char*)this + 0x50) && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xe1;
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
    }
    if (*(int*)((char*)this + 0x3150) == 1) {
        if (*(int*)((char*)this + 0x15c) < 2) {
            if (*(int*)((char*)this + 0x108) < 0xd05 && *(short*)((char*)this + 0x262) == 0x5e && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && *(int*)((char*)this + 0x168) != 6 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0xa50)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x14a;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x70 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9d0)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x13a;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9c8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x139;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x6e || *(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9c0)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x138;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x66 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a0)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x134;
                if (*(double*)((char*)this + 0x28) < 0.0) {
                    *(short*)((char*)this + 0xa) = 3;
                }
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x998)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x133;
                if (*(double*)((char*)this + 0x28) < 0.0) {
                    *(short*)((char*)this + 0xa) = 3;
                }
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x64 || *(short*)((char*)this + 0x262) == 0x65 || *(short*)((char*)this + 0x262) == 0x66) && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x990)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x132;
                if (*(double*)((char*)this + 0x28) < 0.0) {
                    *(short*)((char*)this + 0xa) = 3;
                }
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x20 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x868)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10d;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x1f && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x860)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10c;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x1e && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x858)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10b;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0xc && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x850)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x10a;
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0xb || *(short*)((char*)this + 0x262) == 0xc) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x848)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x109;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0xa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x840)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x108;
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x2a && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x838)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x107;
                if (*(double*)((char*)this + 0x28) < 0.0) {
                    *(short*)((char*)this + 0xa) = 3;
                    *(int*)((char*)this + 0x3138) = 0x64;
                }
                return;
            }
            if ((*(short*)((char*)this + 0x262) == 0x29 || *(short*)((char*)this + 0x262) == 0x2a) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x830)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x106;
                if (*(double*)((char*)this + 0x28) < 0.0) {
                    *(short*)((char*)this + 0xa) = 3;
                }
                return;
            }
            if (*(short*)((char*)this + 0x262) == 0x28 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x828)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0x105;
                if (*(double*)((char*)this + 0x28) < 0.0) {
                    *(short*)((char*)this + 0xa) = 3;
                }
                return;
            }
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
                    *((char*)this + 0x1a8) = 0;
                    return;
                }
            }
        }
        if (*(int*)((char*)this + 0x15c) < 3 && *(short*)((char*)this + 0x262) == 6 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) < 0.0 && *(BYTE*)((char*)this + 0x15a) < 1 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x70)) {
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
                *(short*)((char*)this + 8) = 0xec;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0xef;
                }
                return;
            }
            if (*(double*)((char*)this + 0x28) < 0.0) {
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6c8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xd9;
                }
                return;
            }
            if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x798) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -60.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 60.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xf3;
                return;
            }
            if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6b0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd6;
                return;
            }
            if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x790) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -60.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 60.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xf2;
                    return;
                }
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x690) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xd2;
                    return;
                }
            }
        }
        if (*((char*)this + 0x18b) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x20) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x20) != 0) {
            if (*(WORD*)((char*)this + 8) == 0xa3 && *((char*)this + 0x188) != -*((char*)this + 0x50)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xed;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0xf0;
                }
                return;
            }
            if (*(double*)((char*)this + 0x28) < 0.0) {
                if (*((char*)this + 0x189) == 1 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x718) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xe3;
                    return;
                }
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6d0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xda;
                }
                return;
            }
            if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6b8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xd7;
                return;
            }
            if (*((char*)this + 0x189) == 0 || (*(BYTE*)((char*)this + 0x1a8) & 4) == 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) == 0) {
                if (*((char*)this + 0x188) == -*((char*)this + 0x50) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x720) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xe4;
                    return;
                }
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x698) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -70.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 70.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xd3;
                    return;
                }
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x698) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xd3;
                    return;
                }
            }
        }
        if (*((char*)this + 0x18c) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x40) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x40) != 0) {
            if (*(WORD*)((char*)this + 8) == 0xa3 && *((char*)this + 0x188) != -*((char*)this + 0x50)) {
                Vf0();
                CPlayer::Unk40f170();
                *(short*)((char*)this + 8) = 0xee;
                if (*((char*)this + 0x189) == 1) {
                    *(short*)((char*)this + 8) = 0xf1;
                }
                return;
            }
            if (*(double*)((char*)this + 0x28) < 0.0) {
                if (*((char*)this + 0x188) == *((char*)this + 0x50) && *((char*)this + 0x189) == 0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > -100.0 && *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) < 100.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7c0) && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x9c) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xf7;
                    return;
                }
                if (*((char*)this + 0x189) == 1 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x728) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xe5;
                }
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6d8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xdb;
                }
                return;
            }
            if ((*((char*)this + 0x189) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 4) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 4) != 0) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6c0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
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
                if (*(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x6a8) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
                    Vf0();
                    CPlayer::Unk40f170();
                    *(short*)((char*)this + 8) = 0xd5;
                    return;
                }
            }
        }
    }
    if (*(int*)((char*)this + 0x15c) < 2 && (*((char*)this + 0x18d) == 1 || (*(BYTE*)((char*)this + 0x1a8) & 0x80) != 0 || (*(BYTE*)((char*)this + 0x1a9) & 0x80) != 0)) {
        if (*(WORD*)((char*)this + 8) != 0xe0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x870) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x10e;
            return;
        }
        if (*(int*)((char*)this + 0x3150) == 1 && *(double*)((char*)this + 0x28) < -30.0 && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x88) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) < 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x11;
        }
    }
}

void CMio::Vf1()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (*(int*)((char*)this + 0x3150) == 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x15c);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x2d - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x113 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x3150) == 1) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x164);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x2d - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x113 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
}

void CMio::Vf8()
{
}

void CMio::Vf9(EffectDesc* p1)
{
    Vf10(*(short*)((char*)this + 0x2ca));
    CPlayer::Vf9(p1);
}

void CMio::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    *(short*)((char*)this + 0x262) = 0x63;
    x6 = 0;
    v4 = *(short*)((char*)this + 0x260) + 0x2d;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x20) != 0 && x6 == 5) {
            *(short*)((char*)this + 0x262) = 0x5e;
            return;
        }
        if ((v5 & 0x10) != 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xe0) != 0 && x6 == 4) {
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
        if ((v5 & 0xd0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x20) != 0 && x6 == 0 && *(short*)((char*)this + 0x148) == 0xbb8 && *(int*)((char*)this + 0x3150) == 1) {
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
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 0 && *(short*)((char*)this + 0x148) == 0xbb8 && *(int*)((char*)this + 0x3150) == 0) {
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
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 0 && *(int*)((char*)this + 0x3150) == 0) {
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
        if ((v5 & 0xf) == 2 - (*((char*)this + 0x50) == -1) && x6 == 0 && *(int*)((char*)this + 0x3150) == 1) {
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

void CMio::Vf5()
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
            if (v10 < 40.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(int*)((char*)this + 0x3150) == 0) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(int*)((char*)this + 0x3150) == 0) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
        }
        if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xc9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xca || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xcd) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0) {
            if (v10 > 40.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(int*)((char*)this + 0x3150) == 0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                *((char*)this + 0x188) = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(int*)((char*)this + 0x3150) == 0) {
                *((char*)this + 0x18a) = 3;
                *((char*)this + 0x189) = 1;
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 || *(WORD*)((char*)this + 8) == 0xa9) {
        if (v10 < 100.0) {
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(int*)((char*)this + 0x3150) == 1 && *(short*)((char*)this + 0x148) == 0xbb8) {
                *(short*)((char*)this + 0x262) = 0x5e;
                return;
            }
            if (v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(int*)((char*)this + 0x3150) == 1 && *(short*)((char*)this + 0x148) >= 0x7d0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x65;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x3150) == 0) {
                *(short*)((char*)this + 0x262) = 0xc;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x3150) == 1) {
                *(short*)((char*)this + 0x262) = 0x2a;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x3150) == 0) {
                *(short*)((char*)this + 0x262) = 0x20;
                return;
            }
        }
        if (v10 < 160.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0xc;
            return;
        }
        if (v10 < 80.0 && v10 > 160.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(int*)((char*)this + 0x3150) == 0 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0xc;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(int*)((char*)this + 0x3150) == 1) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2 && *(int*)((char*)this + 0x3150) == 1 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x2a;
                return;
            }
        }
        if (v10 > 160.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(int*)((char*)this + 0x3150) == 1) {
            *(short*)((char*)this + 0x262) = 0xa;
            return;
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xaa && *(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *(int*)((char*)this + 0x3114) = 3;
            return;
        }
        if (x8 < 50.0 && *(double*)((char*)this + 0x28) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18a) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -30.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18b) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -50.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 50.0 && x8 < 60.0 && v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
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
        if (*(int*)((char*)this + 0x3110) < 3 && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x3150) == 0) {
            *(short*)((char*)this + 0x262) = 0xc;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 7 && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x3150) == 0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0xa && *(double*)((char*)this + 0x118) > 500.0 && *(int*)((char*)this + 0x3150) == 1) {
            *(short*)((char*)this + 0x262) = 0x48;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0xd && *(double*)((char*)this + 0x118) > 500.0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x7d0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 1) + 0x65;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < (*(int*)((char*)this + 0x3150) == 1) * 0x14 + 0x14) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
    }
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d && (*(WORD*)((char*)this + 8) == 0xdf || *(WORD*)((char*)this + 8) == 0xfa || *(WORD*)((char*)this + 8) == 0xfb || *(WORD*)((char*)this + 8) == 0xfc || *(WORD*)((char*)this + 8) == 0x10e || *(WORD*)((char*)this + 8) == 0x10f || *(WORD*)((char*)this + 8) == 0x110)) {
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
    if (*(WORD*)((char*)this + 8) == 0xfe && *(int*)((char*)this + 0x168) > 0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 24.0f * *(float*)((char*)this + 0xa8)) {
        *(short*)((char*)this + 0x262) = 0xa;
        return;
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
    if (*(int*)((char*)this + 0x3114) == 0x12 && *(int*)((char*)this + 0x3150) == 0) {
        *((char*)this + 0x188) = *((char*)this + 0x50);
        *((char*)this + 0x189) = -1;
        if (*(double*)((char*)this + 0x28) < 0.0) {
            *((char*)this + 0x18c) = 1;
            *((char*)this + 0x189) = 1;
            if (*(WORD*)((char*)this + 8) == 0xdf) {
                *(int*)((char*)this + 0x3114) = 0;
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
            if (v10 < 40.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 50.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                if (*(int*)((char*)this + 0x168) == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x1e) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                }
                return;
            }
            if (v10 < 80.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x1f4) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1f4 && *(int*)((char*)this + 0x3110) < 0x226) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x226 && *(int*)((char*)this + 0x3110) < 0x230) {
                *(int*)((char*)this + 0x3114) = 0xc;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3d4) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3c0) {
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x12;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xc9) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x188) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x140 && *(int*)((char*)this + 0x3110) < 0x1a4 && v10 < 100.0) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x12;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x64) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x15e && v10 < 80.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc && *(int*)((char*)this + 0x3110) < 0x2ee) {
                *(int*)((char*)this + 0x3114) = 0x12;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3d4) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xca) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x188) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x140 && *(int*)((char*)this + 0x3110) < 0x2bc && v10 < 100.0) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x1c2 && v10 < 110.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x225 && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = ((WORD)CPlayer::Unk4108a0(0, 3) == 0 && *(double*)((char*)this + 0x118) > 500.0) * 2 + 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x188) = 0;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3d4) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcb) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = (((WORD)CPlayer::Unk4108a0(0, 3) == 0) << 1) * (*(double*)((char*)this + 0x118) > 500.0) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x113) {
                *(short*)((char*)this + 0x262) = ((WORD)CPlayer::Unk4108a0(0, 4) == 0 && *(double*)((char*)this + 0x118) > 500.0) * 2 + 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 450.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x226) {
                *((char*)this + 0x18d) = 1;
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
                *((char*)this + 0x189) = 0;
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
                if (*(int*)((char*)this + 0x168) == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x1e) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                }
                return;
            }
            if (v10 < 80.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x1f4) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1f4 && *(int*)((char*)this + 0x3110) < 0x226) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x226 && *(int*)((char*)this + 0x3110) < 0x230) {
                *(int*)((char*)this + 0x3114) = 0xc;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc && *(int*)((char*)this + 0x3110) < 0x2ee) {
                *(int*)((char*)this + 0x3114) = 0x12;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3d4) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3c0) {
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x12;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcd) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x64 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x78) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x188) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x78 && *(int*)((char*)this + 0x3110) < 0x8c && v10 < 100.0) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x12;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x28) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x28 && *(int*)((char*)this + 0x3110) < 0x32 && v10 < 80.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x32 && *(int*)((char*)this + 0x3110) < 0x3c) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bc && *(int*)((char*)this + 0x3110) < 0x2ee) {
                *(int*)((char*)this + 0x3114) = 0x12;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3e3) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3ca) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xce) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x28a) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcf) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18b) = 1;
                return;
            }
            if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x1f4) {
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
        if (*(WORD*)((char*)this + 8) == 0xe6) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xfa && v10 < 90.0 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x38e) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xe7) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = (((WORD)CPlayer::Unk4108a0(0, 3) == 0) << 1) * (*(double*)((char*)this + 0x118) > 500.0) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xfa && v10 < 90.0 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x38e) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xeb) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x15e && v10 < 90.0 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd2) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
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
                if (*(int*)((char*)this + 0x168) == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x1e) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                }
                return;
            }
            if (v10 < 80.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x1c2) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x258) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3c0) {
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x12;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd3) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x32 && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x188) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x140 && *(int*)((char*)this + 0x3110) < 0x1a4 && v10 < 100.0) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x12;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x64 && v10 < 90.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x15e && v10 < 120.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x28a && v10 > 100.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3de) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd4) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x113) {
                *(short*)((char*)this + 0x262) = 0x46;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 450.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x28a) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd5) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
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
                if (*(int*)((char*)this + 0x168) == 2 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 0x1e) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                }
                return;
            }
            if (v10 < 80.0 && *(int*)((char*)this + 0x3110) > 0x18f && *(int*)((char*)this + 0x3110) < 0x1c2) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x258) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3c0) {
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = *((char*)this + 0x50);
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x12;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x2bb) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                }
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd6) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x32 && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                *((char*)this + 0x189) = 0;
                *((char*)this + 0x188) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x140 && *(int*)((char*)this + 0x3110) < 0x1a4 && v10 < 100.0) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                if ((WORD)CPlayer::Unk4108a0(0, 3) == 0) {
                    *(int*)((char*)this + 0x3114) = 0x12;
                }
                return;
            }
            if (*(int*)((char*)this + 0x3110) < 0x64 && v10 < 90.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x15e && v10 < 120.0) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x28a && v10 > 100.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3de) {
                *(int*)((char*)this + 0x3114) = 4;
                *((char*)this + 0x189) = -1;
                *((char*)this + 0x188) = (WORD)CPlayer::Unk4108a0(0, 2) - 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384) {
                *(int*)((char*)this + 0x3114) = 1;
                if ((WORD)CPlayer::Unk4108a0(0, 1) == 0) {
                    *(int*)((char*)this + 0x3114) = 6;
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x14) {
                        *(int*)((char*)this + 0x3114) = 8;
                    }
                    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 0x28) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                    }
                    return;
                }
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xd7) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140 && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x6e;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x113) {
                *(short*)((char*)this + 0x262) = 0x46;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 450.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x28a) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xcf) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18b) = 1;
                return;
            }
            if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x1f4) {
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
        if (*(WORD*)((char*)this + 8) == 0xed) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = (((WORD)CPlayer::Unk4108a0(0, 3) == 0) << 1) * (*(double*)((char*)this + 0x118) > 500.0) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xfa && v10 < 90.0 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x38e) {
                *(int*)((char*)this + 0x3114) = 1;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xee) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140 && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x6e;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x113) {
                *(short*)((char*)this + 0x262) = 0x46;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 450.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x28a) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xf0) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x14;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *(short*)((char*)this + 0x262) = 0x1f;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = (((WORD)CPlayer::Unk4108a0(0, 3) == 0) << 1) * (*(double*)((char*)this + 0x118) > 500.0) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xfa && v10 < 90.0 && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x38e) {
                *(int*)((char*)this + 0x3114) = 1;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xf1) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140 && *(int*)((char*)this + 0x168) == 3 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x6e;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12b && *(int*)((char*)this + 0x3110) < 0x140) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x113) {
                *(short*)((char*)this + 0x262) = 0x46;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 450.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x28a) {
                *((char*)this + 0x18d) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x289) {
                *(int*)((char*)this + 0x3114) = 1;
                return;
            }
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < 25.0f * *(float*)((char*)this + 0xa8)) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x3e8);
        if (*(double*)((char*)this + 0x28) == 0.0) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x63 && *(int*)((char*)this + 0x3150) == 0) {
                if (v10 < 40.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(int*)((char*)this + 0x3110) < 5) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x188) = -*((char*)this + 0x50);
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 45.0 && *(int*)((char*)this + 0x3110) < 0x19) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x23) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 80.0 && v10 > 40.0 && *(int*)((char*)this + 0x3110) < 0x3c && *(int*)((char*)this + 0x3110) > 0x23) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 100.0 && *(int*)((char*)this + 0x3110) < 0x50 && *(int*)((char*)this + 0x3110) > 0x3c) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 90.0 && v10 > 50.0 && *(int*)((char*)this + 0x3110) > 0x50 && *(int*)((char*)this + 0x3110) < 0x57) {
                    *(int*)((char*)this + 0x3114) = 6;
                    return;
                }
                if (v10 < 110.0 && v10 > 70.0 && *(int*)((char*)this + 0x3110) > 0x57 && *(int*)((char*)this + 0x3110) < 0x5f) {
                    *(int*)((char*)this + 0x3114) = 8;
                    if ((WORD)CPlayer::Unk4108a0(0, 0x1e) < 0xf) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                    }
                    return;
                }
                if (v10 > 120.0 && v10 < 190.0 && *(int*)((char*)this + 0x3110) > 0x5f && *(int*)((char*)this + 0x3110) < 0x62) {
                    *(int*)((char*)this + 0x3114) = 0x10;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && *(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x67) {
                    *(int*)((char*)this + 0x3114) = 0xa;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x78 && *(int*)((char*)this + 0x3110) > 0x69) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x7d && *(int*)((char*)this + 0x3110) > 0x78 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7 && *(double*)((char*)this + 0x118) > 500.0) {
                    *(short*)((char*)this + 0x262) = 0x16;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x82 && *(int*)((char*)this + 0x3110) > 0x7d && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x64;
                    return;
                }
                if (*(int*)((char*)this + 0x3110) < 0x87 && *(int*)((char*)this + 0x3110) > 0x82) {
                    *(short*)((char*)this + 0x262) = *((char*)this + 0x50);
                    *(int*)((char*)this + 0x3114) = 5;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x63 && *(int*)((char*)this + 0x3150) == 1) {
                if (v10 < 40.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(int*)((char*)this + 0x3110) < 5) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x188) = -*((char*)this + 0x50);
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 55.0 && *(int*)((char*)this + 0x3110) < 0xa) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 70.0 && *(int*)((char*)this + 0x3110) < 0xf) {
                    *((char*)this + 0x18a) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 150.0 && v10 > 80.0 && *(int*)((char*)this + 0x3110) < 0x3c && *(int*)((char*)this + 0x3110) > 0x23) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 180.0 && v10 > 100.0 && *(int*)((char*)this + 0x3110) < 0x50 && *(int*)((char*)this + 0x3110) > 0x3c && *(*(char**)*(char**)((char*)this + 0x78) + 0x189) != 1) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 < 100.0 && v10 > 0.0 && *(int*)((char*)this + 0x3110) < 0x5f && *(int*)((char*)this + 0x3110) > 0x50) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 120.0 && *(int*)((char*)this + 0x3110) < 0x6e && *(int*)((char*)this + 0x3110) > 0x5f) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (v10 > 80.0 && v10 < 130.0 && *(int*)((char*)this + 0x3110) > 0x6e && *(int*)((char*)this + 0x3110) < 0x73) {
                    *(int*)((char*)this + 0x3114) = 0x10;
                    return;
                }
                if (v10 > 100.0 && v10 < 180.0 && *(int*)((char*)this + 0x3110) > 0x73 && *(int*)((char*)this + 0x3110) < 0x7d) {
                    *(int*)((char*)this + 0x3114) = 0xa;
                    return;
                }
                if (v10 < 60.0 && *(int*)((char*)this + 0x3110) < 0x82 && *(int*)((char*)this + 0x3110) > 0x7d && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7 && *(double*)((char*)this + 0x118) > 500.0) {
                    *(short*)((char*)this + 0x262) = 0x2a;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x85 && *(int*)((char*)this + 0x3110) > 0x82 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7 && *(short*)((char*)this + 0x148) == 0xbb8) {
                    *(short*)((char*)this + 0x262) = 0x5e;
                    return;
                }
                if (v10 > 100.0 && *(int*)((char*)this + 0x3110) < v10 * 0.1 + 140.0 && *(int*)((char*)this + 0x3110) > 0x87) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                    return;
                }
                if (v10 > 120.0 && *(int*)((char*)this + 0x3110) < 0xc8 && *(int*)((char*)this + 0x3110) > 0xc1) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0xa;
                    return;
                }
                if (v10 > 80.0 && *(int*)((char*)this + 0x3110) < 0xd0 && *(int*)((char*)this + 0x3110) > 0xc8) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x28;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3150) == 0) {
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) < 0.0 && v10 < 80.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) < 0xa) {
                    *((char*)this + 0x189) = -1;
                    *((char*)this + 0x188) = -*((char*)this + 0x50);
                    return;
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) > 0.0) {
                    if (v10 < 60.0 && x8 < 120.0) {
                        if (*(int*)((char*)this + 0x3110) < (*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) * 5 + 6) {
                            *(short*)((char*)this + 0x262) = ((WORD)CPlayer::Unk4108a0(0, 3) == 0) * 2 + 0x14;
                            return;
                        }
                    }
                    if (v10 < 60.0 && x8 < 120.0 && x8 > 80.0 && *(int*)((char*)this + 0x3110) < 0xf) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 150.0 && x8 > 100.0 && *(int*)((char*)this + 0x3110) < 0x1e) {
                        *((char*)this + 0x189) = -1;
                        *((char*)this + 0x188) = -*((char*)this + 0x50);
                        return;
                    }
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3150) == 1) {
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) < 0.0) {
                    if (v10 < 100.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) < 0xa) {
                        *((char*)this + 0x189) = -1;
                        *((char*)this + 0x188) = -*((char*)this + 0x50);
                        return;
                    }
                    if (v10 < 100.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) < 0xf && *(double*)((char*)this + 0x20) > 80.0 && *(double*)((char*)this + 0x20) < 560.0) {
                        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == -1;
                        return;
                    }
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) > 0.0) {
                    if (v10 < 110.0 && x8 < 210.0 && *(int*)((char*)this + 0x3110) < 0xa) {
                        *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x6e;
                        return;
                    }
                    if (v10 < 100.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) < 4) {
                        *((char*)this + 0x189) = -1;
                        *((char*)this + 0x188) = -*((char*)this + 0x50);
                        return;
                    }
                    if (v10 < 100.0 && v10 < 180.0 && x8 < 140.0 && *(int*)((char*)this + 0x3110) < 0x14) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                    if (v10 < 100.0 && x8 < 140.0 && x8 > 80.0 && *(int*)((char*)this + 0x3110) < 0x28) {
                        *((char*)this + 0x18c) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                }
            }
        }
        if (*(double*)((char*)this + 0x28) < 0.0 && *(int*)((char*)this + 0x3114) != 3 && *(int*)((char*)this + 0x3150) == 0) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                if (v10 < 60.0 && x8 < 70.0 && *(int*)((char*)this + 0x3110) < 0x64) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 50.0 && x8 < 90.0 && *(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x104) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 < 70.0 && x8 > 60.0 && x8 < 110.0 && *(int*)((char*)this + 0x3110) > 0x104 && *(int*)((char*)this + 0x3110) < 0x11d) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
                if (x8 + 30.0 > v10 && x8 - 30.0 < v10 && x8 < 110.0 && *(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x136) {
                    *((char*)this + 0x18c) = 1;
                    *((char*)this + 0x189) = 1;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (v10 < 80.0 && x8 < 80.0 && *(double*)((char*)this + 0x28) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) && *(int*)((char*)this + 0x3110) < 0x136) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 < 90.0 && x8 < 100.0 && *(double*)((char*)this + 0x28) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) && *(int*)((char*)this + 0x3110) > 0x136 && *(int*)((char*)this + 0x3110) < 0x190) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
            }
        }
        if (*(double*)((char*)this + 0x28) < 0.0 && *(int*)((char*)this + 0x3114) != 3 && *(int*)((char*)this + 0x3150) == 1) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0) {
                if (v10 < 60.0 && x8 < 70.0 && *(int*)((char*)this + 0x3110) < 0x64) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 < 160.0 && v10 > 110.0 && x8 > 20.0 && x8 < 50.0 && *(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x104) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 < 90.0 && x8 < 150.0 && *(int*)((char*)this + 0x3110) > 0x104) {
                    if (*(int*)((char*)this + 0x3110) < (x8 > 100.0) * 0x28 + 0x122) {
                        *((char*)this + 0x18c) = 1;
                        return;
                    }
                }
                if (v10 < 130.0 && v10 > 80.0 && x8 < 80.0 && *(int*)((char*)this + 0x3110) > 0x17c && *(int*)((char*)this + 0x3110) < 0x190) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x28;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (v10 < 80.0 && v10 > 60.0 && x8 < 60.0 && *(double*)((char*)this + 0x28) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) && *(int*)((char*)this + 0x3110) < 0xd2) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 < 180.0 && v10 > 100.0 && x8 < 70.0 && *(double*)((char*)this + 0x28) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) && *(int*)((char*)this + 0x3110) < 0x136) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 < 90.0 && x8 > 100.0 && x8 < 150.0 && *(double*)((char*)this + 0x28) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) && *(int*)((char*)this + 0x3110) > 0x136 && *(int*)((char*)this + 0x3110) < 0x1c2) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 < 140.0 && v10 > 80.0 && x8 < 80.0 && *(int*)((char*)this + 0x3110) > 0x17c && *(int*)((char*)this + 0x3110) < 0x190) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x28;
                    return;
                }
            }
        }
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < (*(int*)((char*)this + 0x3150) == 0) * 3 * *(float*)((char*)this + 0xa8) + 1.0f) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        return;
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32) && *(double*)((char*)this + 0x28) == 0.0 && v10 < 90.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < ((*(int*)((char*)this + 0x3150) == 1) << 2) * *(float*)((char*)this + 0xa8)) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == -1;
        return;
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x3e8) < (*(int*)((char*)this + 0x3150) == 0) + 1) {
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
        if (v10 < 100.0 && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 1 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32) {
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
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < (*(int*)((char*)this + 0x3150) == 1) * 0x1e + 0x28 && v10 < 110.0) {
        if (*((char*)this + 0x50) == 1) {
            *(int*)((char*)this + 0x1a4) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        } else {
            *(int*)((char*)this + 0x1a0) = (WORD)CPlayer::Unk4108a0(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)CPlayer::Unk4108a0(0, 0x64) < (*(int*)((char*)this + 0x3150) == 0) * 0x1e + 0x28) {
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

void CMio::Vf7()
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.8;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) >= 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0 || *(int*)((char*)this + v4 * 0x98 + 0x550) > 1) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    l50.type = 0x191;
                    l50.x = (double)(int)*(double*)((char*)this + 0x20);
                    l50.y = (double)(int)*(double*)((char*)this + 0x28);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + 0x50);
                    Vf9(&l50);
                    l50.type = 0x192;
                    Vf9(&l50);
                    l50.type = 0x193;
                    Vf9(&l50);
                    *((char*)this + 0x2c8) = 2;
                    Vf10(v4);
                    break;
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
            case 0x191:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -1.0 - (rand() < 0x3e80) * 0.5 - (rand() < 0x3e80) * 1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) >= 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    Vf10(v4);
                    break;
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
            case 0x192:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (rand() < 0x3e80) * 0.5 + 1.0 + (rand() < 0x3e80) * 1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) >= 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    Vf10(v4);
                    break;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (rand() < 0x3e80) * 0.5 - (rand() < 0x3e80) * 1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.3;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) >= 0.0 && *(double*)((char*)this + v4 * 0x98 + 0x500) > 0.0) {
                    Vf10(v4);
                    break;
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
            case 0x194:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + 1.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.1 - (WORD)CPlayer::Unk4108a0(0, 5) * 0.1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.02;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.02;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 6.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 2;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *((char*)this + 0x2c8) = 5;
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) + 0x3c;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 30.0) {
                    Vf10(v4);
                }
                break;
            case 0x196:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 6.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -960.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 1640.0)) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4e8) = -*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 3 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) <= 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 3;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *((char*)this + 0x2c8) = 5;
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) = *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) + 0x3c;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) > 1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 2;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) > 0 && (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -2000.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 2000.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 30.0)) {
                    Vf10(v4);
                }
                break;
            case 0x197:
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
            case 0x198:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.05;
                *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.02;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    Vf10(v4);
                }
                break;
            case 0x199:
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
            case 0x19a:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -190.0) {
                        l50.type = 0x19a;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0xa0);
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk0 = 1;
                        Vf9(&l50);
                    } else {
                        l50.type = 0x199;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = 0.0;
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk0 = 1;
                        Vf9(&l50);
                    }
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                }
                break;
            case 0x19c:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.035;
                if ((*(int*)((char*)this + v4 * 0x98 + 0x550) > 1 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *((char*)this + 0x2c8) = 7;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                }
                break;
            case 0x19d:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                if ((*(int*)((char*)this + v4 * 0x98 + 0x550) > 1 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) && *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0) {
                    *((char*)this + 0x2c9) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.5;
                    l50.type = 0x19e;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) - 0xf);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    l50.type = 0x19f;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0xf);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    l50.type = 0x1a0;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + 0xf);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 0;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    l50.type = 0x1a1;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) - 0xf);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                }
                break;
            case 0x19e:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + -1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + 0.5;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                }
                break;
            case 0x19f:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + -1.3;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + 0.9;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a0:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + -1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + -0.5;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a1:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + -0.8;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.1 + -0.9;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.04;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a2:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 7;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.02;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x11 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x14 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x17) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a3:
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
            case 0x1a4:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.3;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -420.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 1060.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a5:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.6;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -420.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 1060.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a6:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0x1e && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0) {
                    l50.type = 0x19a;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + v4 * 0x98 + 0x518) * 0xf);
                    l50.y = -556.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk0 = 1;
                    *((char*)this + 0x2c8) = 6;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0x27 && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0) {
                    l50.type = 0x19a;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 6);
                    l50.y = -564.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk0 = 1;
                    *((char*)this + 0x2c8) = 6;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 3 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0x30 && *(double*)((char*)this + v4 * 0x98 + 0x4f0) == 0.0) {
                    l50.type = 0x19a;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) - *((char*)this + v4 * 0x98 + 0x518) * 0x24);
                    l50.y = -560.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk0 = 1;
                    *((char*)this + 0x2c8) = 6;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 3.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -420.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 1060.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a8:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 7;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0) {
                    l50.type = 0x1a3;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x28);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0x12;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))--;
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.03;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x11 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x14 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x17) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    Vf10(v4);
                }
                break;
            case 0x1a9:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 7;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                l50.type = 0x24;
                l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + 0x28 - (WORD)CPlayer::Unk4108a0(0, 0x50));
                l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0x28 - (WORD)CPlayer::Unk4108a0(0, 0x50));
                l50.unk20 = 2;
                l50.unk21 = 1;
                ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0) {
                    l50.type = 0x1a3;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 0x28);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    Vf9(&l50);
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 6;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > -80.0 && *(int*)((char*)this + v4 * 4 + 0x3358) < 0) {
                        l50.type = 0x1f;
                        l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = 0.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.side = *((char*)this + v4 * 0x98 + 0x518) == -1;
                        ((CGame*)*(int*)((char*)this + 0x7c))->CreateEffect((EffectDesc*)&l50);
                        *(int*)((char*)this + v4 * 4 + 0x3358) = 3;
                    }
                    (*(int*)((char*)this + v4 * 4 + 0x3358))--;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))--;
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) += 0.04;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xe || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x11 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x14 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x17) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < -100.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) > 800.0 || *(double*)((char*)this + v4 * 0x98 + 0x4f0) > 0.0) {
                    Vf10(v4);
                }
                break;
            case 0x1aa:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 6.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -4.5;
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -640.0) {
                    Vf10(v4);
                }
                break;
            case 0x1ab:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1ac:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1ad:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1ae:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1af:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1b0:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3140) == 1.0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1b1;
                }
                break;
            case 0x1b1:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -15.0;
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
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -640.0) {
                    Vf10(v4);
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
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1b3:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1b4:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1b5:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1b6:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                    ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Vf0();
                    *(short*)(*(char**)*(char**)((char*)this + 0x78) + 8) = 0x79;
                }
                break;
            case 0x1b7:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *((char*)this + 0x2c8) = 0xa;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        l50.type = 0x1bb;
                        l50.x = (double)(int)*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20);
                        l50.y = 0.0;
                        l50.unk18 = *((char*)this + 0x50);
                        l50.unk21 = 1;
                        l50.unk20 = 2;
                        Vf9(&l50);
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x1b8;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = -15.0;
                        *(double*)((char*)this + 0x3140) = 1.0;
                        *((char*)this + 0x2c8) = 8;
                    }
                }
                break;
            case 0x1b8:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -640.0) {
                    Vf10(v4);
                }
                break;
            case 0x1b9:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + 0x3148) == 1.0) {
                    Vf10(v4);
                }
                break;
            case 0x1bb:
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -640.0) {
                    Vf10(v4);
                }
                break;
            case 0x1c6:
                *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                if (*(WORD*)((char*)this + 0xa) == 4) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
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
                if (*(WORD*)((char*)this + 8) != 0xdd || *(WORD*)((char*)this + 0xa) > 4) {
                    Vf10(v4);
                }
                break;
            case 0x1ba:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 2;
                }
                if (*(WORD*)((char*)this + 8) != 0x144 || *(WORD*)((char*)this + 8) == 0x144 && *(WORD*)((char*)this + 0xa) > 5) {
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
            case 0x1bc:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = *(double*)((char*)this + 0x3148);
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.8 - *(double*)((char*)this + 0x3148) / 2.0;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) -= 0.02;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.1) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) -= 0.02;
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
            case 0x1bd:
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 50.0;
                if (*(WORD*)((char*)this + 8) != 0xfc || *(WORD*)((char*)this + 8) == 0xfc && *(WORD*)((char*)this + 0xa) > 5) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 7;
                    }
                }
                break;
            case 0x1be:
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
            case 0x1c2:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.8;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                }
                break;
            case 0x1c3:
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.4;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.7;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.05;
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) > 100.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                    }
                }
                break;
            case 0x1c5:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1a6;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = -3.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 0;
                    l50.unk20 = 0;
                    l50.unk0 = 1;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1a6;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 0x1b);
                    l50.y = 0.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 0;
                    l50.unk20 = 0;
                    l50.unk0 = 1;
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1a6;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + 0x50) * 9);
                    l50.y = 4.0;
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 0;
                    l50.unk20 = 0;
                    l50.unk0 = 1;
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
            case 0x1c7:
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
            case 0x1c8:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.5;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1c7;
                    l50.x = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4e8) + 0x1e - (WORD)CPlayer::Unk4108a0(0, 0x50));
                    l50.y = (double)((int)*(double*)((char*)this + v4 * 0x98 + 0x4f0) + 0x14 - (WORD)CPlayer::Unk4108a0(0, 0x28));
                    l50.unk18 = *((char*)this + 0x50);
                    l50.unk21 = 1;
                    l50.unk20 = 2;
                    Vf9(&l50);
                    *((char*)this + 0x2c9) = 1;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3158) < 6) {
                            (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                            *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                            *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                            break;
                        }
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
