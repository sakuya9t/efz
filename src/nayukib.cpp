// CNayukiB (0x73e790-0x750d2f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNayukiB::CNayukiB(int p1, int p2, int p3, int p4, int p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy((char*)this + 0x94, "nayukiB");
    *(short*)((char*)this + 0x18) = 0x281;
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    *(short*)((char*)this + 0x2ad0) = -5;
    *(short*)((char*)this + 0x2af8) = -0x3d;
    *(short*)((char*)this + 0x2ad2) = 8;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0x11;
    *(short*)((char*)this + 0x2afc) = -0xf;
    *(short*)((char*)this + 0x2ad6) = 0x13;
    *(short*)((char*)this + 0x2afe) = -0xb;
    *(short*)((char*)this + 0x2ad8) = 0x16;
    *(short*)((char*)this + 0x2b00) = -0x1e;
    *((char*)this + 0x30f4) = 7;
    *((char*)this + 0x30f5) = 0x11;
    *((char*)this + 0x30f6) = 1;
    *((char*)this + 0x30f7) = 0xd;
    *((char*)this + 0x30f8) = 0x10;
    *((char*)this + 0x30f9) = 0xa;
    *((char*)this + 0x30fa) = 3;
    *((char*)this + 0x30fb) = 6;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3358) = 0;
    }
}

void CNayukiB::Vf12()
{
    int v4;

    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    *(int*)((char*)this + 0x3144) = 0;
    *(int*)((char*)this + 0x3148) = 0;
    *(int*)((char*)this + 0x314c) = 0;
    *(int*)((char*)this + 0x3150) = 0;
    *(int*)((char*)this + 0x3154) = 0;
    *(short*)((char*)this + 0x2ad0) = -5;
    *(short*)((char*)this + 0x2af8) = -0x3d;
    *(short*)((char*)this + 0x2ad2) = 8;
    *(short*)((char*)this + 0x2afa) = 0;
    *(short*)((char*)this + 0x2ad4) = 0x11;
    *(short*)((char*)this + 0x2afc) = -0xf;
    *(short*)((char*)this + 0x2ad6) = 0x13;
    *(short*)((char*)this + 0x2afe) = -0xb;
    *(short*)((char*)this + 0x2ad8) = 0x16;
    *(short*)((char*)this + 0x2b00) = -0x1e;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
        *(int*)((char*)this + v4 * 4 + 0x3358) = 0;
    }
    CPlayer::Vf12();
}

void CNayukiB::Vf0()
{
    *(int*)((char*)this + 0x3138) = 0;
    *(int*)((char*)this + 0x313c) = 0;
    *(int*)((char*)this + 0x3140) = 0;
    CPlayer::Vf0();
}

void CNayukiB::Vf10(short p1)
{
    *(int*)((char*)this + p1 * 4 + 0x3158) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3258) = 0;
    *(int*)((char*)this + p1 * 4 + 0x3358) = 0;
    CPlayer::Vf10(p1);
}

void CNayukiB::Vf3()
{
    CPlayer::Unk40e740();
}

void CNayukiB::Vf4()
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
        if (*(int*)((char*)this + 0x108) < 0xd05 && *(short*)((char*)this + 0x262) == 0x67 && *(short*)((char*)this + 0x148) >= 0xbb8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x135;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x7a && *(short*)((char*)this + 0x148) >= 0xbb8 && *(int*)((char*)this + 0x3150) <= 0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x9a0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x134;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x79 || *(short*)((char*)this + 0x262) == 0x7a) && *(short*)((char*)this + 0x148) >= 0x7d0 && *(int*)((char*)this + 0x3150) <= 0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x998)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x133;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x78 || *(short*)((char*)this + 0x262) == 0x79 || *(short*)((char*)this + 0x262) == 0x7a) && *(short*)((char*)this + 0x148) >= 0x3e8 && *(int*)((char*)this + 0x3150) <= 0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x990)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x132;
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
        if (*(short*)((char*)this + 0x262) == 0x70 && *(short*)((char*)this + 0x148) >= 0xbb8 && *(double*)((char*)this + 0x28) < 0.0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x970)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12e;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(double*)((char*)this + 0x28) < 0.0 && *(short*)((char*)this + 0x148) >= 0x7d0 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x968)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12d;
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x6e || *(short*)((char*)this + 0x262) == 0x6f || *(short*)((char*)this + 0x262) == 0x70) && *(double*)((char*)this + 0x28) < 0.0 && *(short*)((char*)this + 0x148) >= 0x3e8 && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x960)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x12c;
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
        if ((*(short*)((char*)this + 0x262) == 0x14 || *(short*)((char*)this + 0x262) == 0x15 || *(short*)((char*)this + 0x262) == 0x16) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7d0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfa;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x2a && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x818)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x102;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 0xa) = 2;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x29 || *(short*)((char*)this + 0x262) == 0x2a) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x808)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x101;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 0xa) = 2;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x28 || *(short*)((char*)this + 0x262) == 0x29 || *(short*)((char*)this + 0x262) == 0x2a) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x800)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x100;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 0xa) = 2;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0x20 && (*(double*)((char*)this + 0x118) >= 500.0 || *((char*)this + 0x120) > 0) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x828)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x105;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x108;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x1f || *(short*)((char*)this + 0x262) == 0x20) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x820)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x104;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x107;
            }
            return;
        }
        if ((*(short*)((char*)this + 0x262) == 0x1e || *(short*)((char*)this + 0x262) == 0x1f || *(short*)((char*)this + 0x262) == 0x20) && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x818)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0x103;
            if (*(double*)((char*)this + 0x28) < 0.0) {
                *(short*)((char*)this + 8) = 0x106;
            }
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xc && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f8)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xff;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xb && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7f0)) {
            Vf0();
            CPlayer::Unk40f170();
            *(short*)((char*)this + 8) = 0xfe;
            return;
        }
        if (*(short*)((char*)this + 0x262) == 0xa && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 8) > 0 && *(double*)((char*)this + 0x28) == 0.0 && (*(WORD*)((char*)this + 8) >= 0xc8 && *(int*)((char*)this + 0x168) >= 2 && *(int*)((char*)this + 0x168) != 6 || *(WORD*)((char*)this + 8) < 0xc8) && *(short*)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 2) <= *(short*)(*(char**)((char*)this + 0x164) + 0x7e8)) {
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

void CNayukiB::Vf1()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (*(int*)((char*)this + 0x314c) > 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x15c);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
    if (*(int*)((char*)this + 0x314c) > 0) {
        x1c = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x164);
        v2c = MakeRect(0, 0, *(int*)((char*)this + 0x3150) * x1c.width / 0xbb8, x1c.height);
        if (*((char*)this + 0x8c) == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, *(int*)((char*)this + 0x3150) * x1c.width / 0xbb8, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - *(int*)((char*)this + 0x3150) * x1c.width / 0xbb8, 0x1f - x1c.y, *(int*)((char*)this + 0x3150) * x1c.width / 0xbb8, x1c.height);
        }
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + x1c.surface * 4), v2c, *((char*)this + 0x1a), 0);
    }
}

void CNayukiB::Vf8()
{
    if (*(int*)((char*)this + 0x3150) <= 0 || *(int*)((char*)this + 0x108) <= 0 || *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) <= 0 || *(WORD*)((char*)this + 8) > 0x31 && *(WORD*)((char*)this + 8) < 0x96) {
        *(int*)((char*)this + 0x3150) = 0;
        *(int*)((char*)this + 0x314c) = 0;
    }
    if (*(int*)((char*)this + 0x3150) > 0) {
        *(int*)((char*)this + 0x3148) += *(int*)((char*)this + 0x3154);
        if (*(int*)((char*)this + 0x3148) > 0x167) {
            *(int*)((char*)this + 0x3148) -= 0x168;
        }
        *(int*)((char*)this + 0x3150) -= 2;
        if (*(int*)((char*)this + 0x3150) <= 0) {
            *(int*)((char*)this + 0x3150) = 0;
            *(int*)((char*)this + 0x314c) = 0;
        }
    }
}

void CNayukiB::Vf9(EffectDesc* p1)
{
    Vf10(*(short*)((char*)this + 0x2ca));
    CPlayer::Vf9(p1);
}

void CNayukiB::Vf2()
{
    BYTE x6;
    BYTE v5;
    int v4;

    *(short*)((char*)this + 0x262) = 0x63;
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
    v4 = *(short*)((char*)this + 0x260) + 0x78;
    for (; v4 < *(short*)((char*)this + 0x260) + 0xb4; v4++) {
        v5 = *((char*)this + (v4 - (v4 >= 0xb4) * 0xb4) + 0x1ab);
        if ((v5 & 0x40) != 0 && x6 == 3) {
            *(short*)((char*)this + 0x262) = 0x60;
            return;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 5 && x6 == 2) {
            if ((v5 & 0x40) != 0) {
                *(short*)((char*)this + 0x262) = 0x60;
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (*((char*)this + 0x50) == -1) + 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && *(short*)((char*)this + 0x148) == 0xbb8) {
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

void CNayukiB::Vf5()
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
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
        }
        if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xc9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xca || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xcd) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0xfa && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) == 0.0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x16c) == 0 && v10 > 60.0 && v10 < 70.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
            *((char*)this + 0x18b) = 1;
            *((char*)this + 0x189) = 1;
            *((char*)this + 0x188) = 0;
            return;
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xa8 || *(WORD*)((char*)this + 8) == 0xa9) {
        if (v10 < 100.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x14;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x16;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x2a;
                return;
            }
            if (v10 < 60.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x64;
                return;
            }
        }
        if (v10 < 150.0 && v10 > 100.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 3.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x2a;
                return;
            }
            if (v10 < 120.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
                *((char*)this + 0x18a) = 2;
                *((char*)this + 0x189) = 0;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 2 && *(short*)((char*)this + 0x148) >= 0x7d0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6f;
                return;
            }
        }
        if (v10 > 150.0) {
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x2a;
                return;
            }
            if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 1.0f) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
                return;
            }
        }
    }
    if (*(WORD*)((char*)this + 8) == 0xaa && *(WORD*)((char*)this + 0xa) == 1 && *(WORD*)((char*)this + 0xc) == 0) {
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -20.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -80.0 && v10 < 150.0 && (WORD)CPlayer::Unk4108a0(0, 0xc8) < *(float*)((char*)this + 0xa8) * 5.0f && *(short*)((char*)this + 0x148) >= 0x3e8) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x6e;
            return;
        }
        if ((WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *(int*)((char*)this + 0x3114) = 3;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > -40.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18a) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > 0.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 50.0 && v10 < 100.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18b) = 1;
            return;
        }
        if (*(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 90.0 && *(double*)((char*)this + 0x28) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) > 20.0 && v10 < 110.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < *(float*)((char*)this + 0xa8) * 5.0f) {
            *((char*)this + 0x18c) = 1;
            *((char*)this + 0x189) = 0;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 3 && *(double*)((char*)this + 0x118) > 500.0 && v10 < 80.0) {
            *(short*)((char*)this + 0x262) = 0x14;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 5 && *(double*)((char*)this + 0x118) > 500.0 && v10 < 80.0) {
            *(short*)((char*)this + 0x262) = 0x16;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0xa && *(int*)((char*)this + 0x3110) > 5 && *(double*)((char*)this + 0x118) > 500.0 && v10 < 100.0) {
            *(short*)((char*)this + 0x262) = 0x2a;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 < 100.0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
            return;
        }
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 > 90.0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x6e;
            return;
        }
        if (*(int*)((char*)this + 0x3110) > 0x41) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
    }
    if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa8 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xa9 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) == 0xaa) && *(double*)((char*)this + 0x28) < 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 15.0f * *(float*)((char*)this + 0xa8) && *(int*)((char*)this + 0x3114) != 2 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        *(int*)((char*)this + 0x3110) = (WORD)CPlayer::Unk4108a0(0, 0x64);
        if (*(int*)((char*)this + 0x3110) < 0x11 && *(int*)((char*)this + 0x3110) > 0xc && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 > 50.0) {
            *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x6e;
            return;
        }
        if (*(int*)((char*)this + 0x3110) > 0x3c) {
            *(int*)((char*)this + 0x3114) = 2;
            return;
        }
    }
    if ((*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0) && (WORD)CPlayer::Unk4108a0(0, 0x64) < 8.0f * *(float*)((char*)this + 0xa8) && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9d && (*(WORD*)((char*)this + 8) == 0x100 || *(WORD*)((char*)this + 8) == 0xe8 && (WORD)CPlayer::Unk4108a0(0, 0xa) == 0 || *(WORD*)((char*)this + 8) == 0x101 || *(WORD*)((char*)this + 8) == 0xee)) {
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
            if (v10 < 45.0 && *(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = CPlayer::Unk4108a0(0, 2);
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
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0xa && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x6e;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) < 0x12c && *(int*)((char*)this + 0x168) == 3) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x15;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x190) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x28;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1c2 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
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
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0x15e && v10 < 150.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x258 && v10 < 70.0) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x2ee) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3d4) {
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
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x96 && *(int*)((char*)this + 0x3110) < 0xc8 && *(short*)((char*)this + 0x148) >= 0x3e8 && v10 < 120.0) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x78;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x226) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x226 && *(int*)((char*)this + 0x3110) < 0x2bc) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x1e;
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
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x1c2) {
                *(short*)((char*)this + 0x262) = ((WORD)CPlayer::Unk4108a0(0, 2) == 0) + 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x28a && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = 0x78;
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
            if (v10 < 45.0 && *(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18a) = 1;
                *((char*)this + 0x189) = CPlayer::Unk4108a0(0, 2);
                return;
            }
            if (v10 < 90.0 && *(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x190) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (v10 < 100.0 && *(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x258) {
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
        if (*(WORD*)((char*)this + 8) == 0xcd) {
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x226) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x2ee) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x64) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x64 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x12c) {
                *((char*)this + 0x18c) = 1;
                *((char*)this + 0x189) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x1c2 && v10 < 140.0) {
                *((char*)this + 0x18b) = 1;
                *((char*)this + 0x189) = 0;
                return;
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0 && *(int*)((char*)this + 0x3110) > 0x1c2 && *(int*)((char*)this + 0x3110) < 0x258 && v10 < 70.0) {
                *((char*)this + 0x18c) = 1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x258 && *(int*)((char*)this + 0x3110) < 0x2ee) {
                *((char*)this + 0x188) = *((char*)this + 0x50);
                *((char*)this + 0x189) = -1;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x3d4) {
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
        if (*(WORD*)((char*)this + 8) == 0xce) {
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0x15e) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x28;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x258) {
                *(short*)((char*)this + 0x262) = 0xa;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x28a && *(int*)((char*)this + 0x3110) < 0x29e && *(short*)((char*)this + 0x148) >= 0x3e8) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x78;
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
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x15e) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1f4) {
                *(short*)((char*)this + 0x262) = 0x28;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190) {
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
        if (*(WORD*)((char*)this + 8) == 0xea) {
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0x15e) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x15e && *(int*)((char*)this + 0x3110) < 0x190 && *(double*)((char*)this + 0x118) > 500.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190 && *(int*)((char*)this + 0x3110) < 0x1f4) {
                *(short*)((char*)this + 0x262) = 0x28;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x190) {
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
        if (*(WORD*)((char*)this + 8) == 0xeb) {
            if (*(int*)((char*)this + 0x3110) > 0 && *(int*)((char*)this + 0x3110) < 0xc8) {
                *(short*)((char*)this + 0x262) = 0x1e;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0xc8 && *(int*)((char*)this + 0x3110) < 0xd2 && *(double*)((char*)this + 0x118) > 350.0) {
                *(short*)((char*)this + 0x262) = 0x34;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x12c && *(int*)((char*)this + 0x3110) < 0x15e) {
                *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x28;
                return;
            }
            if (*(int*)((char*)this + 0x3110) > 0x384) {
                *(int*)((char*)this + 0x3114) = 1;
            }
        }
        if (*(WORD*)((char*)this + 8) == 0xe9 && *(int*)((char*)this + 0x3110) > 0x1f4) {
            *(int*)((char*)this + 0x3114) = 1;
            if (v10 < 50.0) {
                *(int*)((char*)this + 0x3114) = 0x14;
            }
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
                if (v10 < 60.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0x14) {
                        *((char*)this + 0x18a) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                }
                if (v10 < 45.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0x14) {
                        *((char*)this + 0x18a) = 1;
                        *((char*)this + 0x189) = 0;
                        return;
                    }
                }
                if (v10 > 50.0 && v10 < 80.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0x41 && *(int*)((char*)this + 0x3110) > 0x28) {
                        *((char*)this + 0x18b) = 1;
                        *((char*)this + 0x189) = 1;
                        return;
                    }
                }
                if (0x46 - (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x46 < v10 && v10 < 95.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x14 + 0x50 && *(int*)((char*)this + 0x3110) > 0x46) {
                        *(int*)((char*)this + 0x3114) = 0xc;
                        return;
                    }
                }
                if (0x50 - (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x46 < v10 && v10 < 110.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0xf + 0x80 && *(int*)((char*)this + 0x3110) > 0x78) {
                        *(int*)((char*)this + 0x3114) = 8;
                        return;
                    }
                }
                if (v10 < 180.0 && v10 > 200.0 && *(int*)((char*)this + 0x3110) < 0xfa && *(int*)((char*)this + 0x3110) > 0x96) {
                    *(int*)((char*)this + 0x3114) = 0x10;
                    return;
                }
                if (v10 < 130.0 && v10 > 100.0 && *(int*)((char*)this + 0x3110) < 0xc3 && *(int*)((char*)this + 0x3110) > 0xaa) {
                    *((char*)this + 0x18b) = 1;
                    *((char*)this + 0x189) = 0;
                    return;
                }
                if (0x50 - (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x50 < v10 && v10 < 120.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x19 + 0xb9 && *(int*)((char*)this + 0x3110) > 0xaa) {
                        *(int*)((char*)this + 0x3114) = 0xe;
                        return;
                    }
                }
                if (0x5a - (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x5a < v10 && v10 < 120.0) {
                    if (*(int*)((char*)this + 0x3110) < (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c) * 0x19 + 0xe1 && *(int*)((char*)this + 0x3110) > 0xd2) {
                        *(int*)((char*)this + 0x3114) = 0xa;
                        return;
                    }
                }
                if (v10 > 130.0 && v10 < 170.0 && *(int*)((char*)this + 0x3110) < 0x104 && *(int*)((char*)this + 0x3110) > 0xfa) {
                    *(int*)((char*)this + 0x3114) = 0xa;
                    return;
                }
                if (v10 < 80.0 && *(int*)((char*)this + 0x3110) < 0x113 && *(int*)((char*)this + 0x3110) > 0x104 && *(double*)((char*)this + 0x118) > 500.0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7) {
                    *(short*)((char*)this + 0x262) = 0x16;
                    return;
                }
                if (v10 < 150.0 && *(int*)((char*)this + 0x3110) < 0x118 && *(int*)((char*)this + 0x3110) > 0x113 && *(short*)((char*)this + 0x148) >= 0x3e8 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0xc7) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 2) + 0x65;
                    return;
                }
                if (v10 > 150.0 && *(int*)((char*)this + 0x3110) < 0x11d && *(int*)((char*)this + 0x3110) > 0x118 && *(short*)((char*)this + 0x148) >= 0xbb8) {
                    *(short*)((char*)this + 0x262) = 0x67;
                    return;
                }
                if (v10 > 160.0 && *(int*)((char*)this + 0x3110) < 0x136 && *(int*)((char*)this + 0x3110) > 0x12c) {
                    *(short*)((char*)this + 0x262) = 0x28;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && *(int*)((char*)this + 0x3110) < 0x140 && *(int*)((char*)this + 0x3110) > 0x136) {
                    *(short*)((char*)this + 0x262) = 0x29;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && *(int*)((char*)this + 0x3110) < 0x145 && *(int*)((char*)this + 0x3110) > 0x140) {
                    *(short*)((char*)this + 0x262) = 0x2a;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && *(int*)((char*)this + 0x3110) < 0x154 && *(int*)((char*)this + 0x3110) > 0x14a) {
                    *(short*)((char*)this + 0x262) = 0xa;
                    return;
                }
                if (v10 > 160.0 && *(int*)((char*)this + 0x3110) < 0x168 && *(int*)((char*)this + 0x3110) > 0x154) {
                    *(short*)((char*)this + 0x262) = 0xb;
                    return;
                }
                if (v10 > 40.0 && v10 < 120.0 && *(int*)((char*)this + 0x3110) < 0x168 && *(int*)((char*)this + 0x3110) > 0x154) {
                    *(short*)((char*)this + 0x262) = 0x1e;
                    return;
                }
                if (v10 > 140.0 && *(int*)((char*)this + 0x3110) < 0x168 && *(int*)((char*)this + 0x3110) > 0x154) {
                    *(short*)((char*)this + 0x262) = 0x1f;
                    return;
                }
                if (*(int*)((char*)this + 0x3110) < 0x320 && *(int*)((char*)this + 0x3110) > 0x2bc && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c && v10 > 100.0) {
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
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && *(int*)((char*)this + 0x3110) < 6 && (*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0)) {
                        *(short*)((char*)this + 0x262) = 0x15;
                        return;
                    }
                }
                if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x38) > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && *(int*)((char*)this + 0x3110) < 6 && (*(double*)((char*)this + 0x118) > 500.0 || *((char*)this + 0x120) > 0)) {
                        *(short*)((char*)this + 0x262) = 0x16;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && *(int*)((char*)this + 0x3110) < 0xf) {
                        *(short*)((char*)this + 0x262) = 0x15;
                        return;
                    }
                    if (v10 < 160.0 && v10 > 80.0 && x8 < 300.0 && x8 > 160.0 && *(int*)((char*)this + 0x3110) < 0x28 && *(int*)((char*)this + 0x3110) > 0x1e) {
                        *(short*)((char*)this + 0x262) = 0xc;
                        return;
                    }
                    if (v10 < 150.0 && *(int*)((char*)this + 0x3110) < 0xdc && *(int*)((char*)this + 0x3110) > 0xc8 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < -50.0 && *(short*)((char*)this + 0x148) >= 0x3e8) {
                        *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x64;
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
                if (v10 > 60.0 && v10 < 100.0 && x8 > 60.0 && x8 < 120.0 && *(int*)((char*)this + 0x3110) > 0xb4 && *(int*)((char*)this + 0x3110) < 0xf0) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
                if (*(int*)((char*)this + 0x3110) > 0xf0 && *(int*)((char*)this + 0x3110) < 0xfa) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x1e;
                    return;
                }
                if (*(int*)((char*)this + 0x3110) > 0xfa && *(int*)((char*)this + 0x3110) < 0x104) {
                    *(short*)((char*)this + 0x262) = 0x28;
                    return;
                }
                if (v10 > 150.0 && *(int*)((char*)this + 0x3110) > 0x104 && *(int*)((char*)this + 0x3110) < 0x109 && x8 > 150.0) {
                    *(short*)((char*)this + 0x262) = (WORD)CPlayer::Unk4108a0(0, 3) + 0x6e;
                    return;
                }
            }
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && *(int*)((char*)this + 0x3110) < 0x14) {
                    *((char*)this + 0x18a) = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 100.0 && x8 > 0.0 && x8 < 90.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) > 0x14 && *(int*)((char*)this + 0x3110) < 0x3c) {
                    *((char*)this + 0x18b) = 1;
                    return;
                }
                if (v10 > 50.0 && v10 < 130.0 && x8 > 0.0 && x8 < 90.0 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x28) < *(double*)((char*)this + 0x28) && *(int*)((char*)this + 0x3110) > 0x3c && *(int*)((char*)this + 0x3110) < 0x64) {
                    *((char*)this + 0x18c) = 1;
                    return;
                }
            }
        }
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && (*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x95 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x9c || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) > 0x31 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x3b) && *(double*)((char*)this + 0x28) == 0.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 5.0f * *(float*)((char*)this + 0xa8) && v10 > 120.0) {
        *(short*)((char*)this + 0x262) = *((char*)this + 0x50) == 1;
        return;
    }
    if (*(WORD*)((char*)this + 8) < 0x32 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 && v10 > 800.0 && v10 < 80.0 && (WORD)CPlayer::Unk4108a0(0, 0x64) < 3.0f * *(float*)((char*)this + 0xa8) && *(double*)((char*)this + 0x20) > 150.0 && *(double*)((char*)this + 0x20) < 490.0) {
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

void CNayukiB::Vf7()
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.2;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 3;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -600.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                }
                break;
            case 0x191:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.2;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 6;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(int*)((char*)this + v4 * 4 + 0x3258) > 0xa) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                    l50.type = 0x193;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -600.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xf) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                }
                break;
            case 0x192:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.2;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.1;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0xf;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                if (*(int*)((char*)this + v4 * 4 + 0x3258) > 3) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                    l50.type = 0x193;
                    l50.x = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = (double)(int)*(double*)((char*)this + v4 * 0x98 + 0x4f0);
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < -600.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 4 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8 || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x10) {
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                }
                break;
            case 0x193:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -2.2;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)(WORD)CPlayer::Unk4108a0(0, 0x168), (double)((WORD)CPlayer::Unk4108a0(0, 3) + 2));
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x194:
                if (*(int*)((char*)this + 0x3150) <= 0) {
                    Vf10(v4);
                    break;
                }
                *((char*)this + v4 * 0x98 + 0x518) = *((char*)this + 0x50);
                ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)*(int*)((char*)this + 0x3148), 50.0);
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) * *(int*)((char*)this + 0x3154) + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 50.0 + *(double*)((char*)this + v4 * 0x98 + 0x500) * 0.25;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *((char*)this + v4 * 0x98 + 0x521) = 0;
                } else {
                    *((char*)this + v4 * 0x98 + 0x521) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x196;
                    *((char*)this + v4 * 0x98 + 0x520) = 2;
                    *(int*)((char*)this + 0x3150) -= 0x3e8 - *(int*)((char*)this + 0x314c) * 0x15e;
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
            case 0x195:
                if (*(int*)((char*)this + 0x3150) <= 0) {
                    Vf10(v4);
                    break;
                }
                *((char*)this + v4 * 0x98 + 0x518) = *((char*)this + 0x50);
                ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)(*(int*)((char*)this + 0x3148) + 0xb4), 50.0);
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) * *(int*)((char*)this + 0x3154) + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 50.0 + *(double*)((char*)this + v4 * 0x98 + 0x500) * 0.25;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *((char*)this + v4 * 0x98 + 0x521) = 0;
                } else {
                    *((char*)this + v4 * 0x98 + 0x521) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1 && *(short*)((char*)this + v4 * 0x98 + 0x554) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x197;
                    *((char*)this + v4 * 0x98 + 0x520) = 2;
                    *(int*)((char*)this + 0x3150) -= 0x3e8 - *(int*)((char*)this + 0x314c) * 0x15e;
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
            case 0x196:
                if (*(int*)((char*)this + 0x3150) <= 0) {
                    Vf10(v4);
                    break;
                }
                *((char*)this + v4 * 0x98 + 0x518) = *((char*)this + 0x50);
                ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)*(int*)((char*)this + 0x3148), 50.0);
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) * *(int*)((char*)this + 0x3154) + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 50.0 + *(double*)((char*)this + v4 * 0x98 + 0x500) * 0.25;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *((char*)this + v4 * 0x98 + 0x521) = 0;
                } else {
                    *((char*)this + v4 * 0x98 + 0x521) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x198;
                        *((char*)this + v4 * 0x98 + 0x520) = 2;
                    }
                }
                break;
            case 0x197:
                if (*(int*)((char*)this + 0x3150) <= 0) {
                    Vf10(v4);
                    break;
                }
                *((char*)this + v4 * 0x98 + 0x518) = *((char*)this + 0x50);
                ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)(*(int*)((char*)this + 0x3148) + 0xb4), 50.0);
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) * *(int*)((char*)this + 0x3154) + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 50.0 + *(double*)((char*)this + v4 * 0x98 + 0x500) * 0.25;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *((char*)this + v4 * 0x98 + 0x521) = 0;
                } else {
                    *((char*)this + v4 * 0x98 + 0x521) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x199;
                        *((char*)this + v4 * 0x98 + 0x520) = 2;
                    }
                }
                break;
            case 0x198:
                if (*(int*)((char*)this + 0x3150) <= 0) {
                    Vf10(v4);
                    break;
                }
                ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)*(int*)((char*)this + 0x3148), 50.0);
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) * *(int*)((char*)this + 0x3154) + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 50.0 + *(double*)((char*)this + v4 * 0x98 + 0x500) * 0.25;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *((char*)this + v4 * 0x98 + 0x521) = 0;
                } else {
                    *((char*)this + v4 * 0x98 + 0x521) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x194;
                        *((char*)this + v4 * 0x98 + 0x520) = 0;
                        *((char*)this + v4 * 0x98 + 0x518) = *((char*)this + 0x50);
                        l50.type = 0x19b;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                        Vf9(&l50);
                        *((char*)this + 0x2c8) = 8;
                    }
                }
                break;
            case 0x199:
                if (*(int*)((char*)this + 0x3150) <= 0) {
                    Vf10(v4);
                    break;
                }
                ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)(*(int*)((char*)this + 0x3148) + 0xb4), 50.0);
                *(double*)((char*)this + v4 * 0x98 + 0x4e8) = *(double*)((char*)this + v4 * 0x98 + 0x4f8) * *(int*)((char*)this + 0x3154) + *(double*)((char*)this + 0x20);
                *(double*)((char*)this + v4 * 0x98 + 0x4f0) = *(double*)((char*)this + 0x28) - 50.0 + *(double*)((char*)this + v4 * 0x98 + 0x500) * 0.25;
                if (*(double*)((char*)this + v4 * 0x98 + 0x500) < 0.0) {
                    *((char*)this + v4 * 0x98 + 0x521) = 0;
                } else {
                    *((char*)this + v4 * 0x98 + 0x521) = 1;
                }
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d0) = 0x195;
                        *((char*)this + v4 * 0x98 + 0x520) = 0;
                        *((char*)this + v4 * 0x98 + 0x518) = *((char*)this + 0x50);
                        l50.type = 0x19b;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                        Vf9(&l50);
                        *((char*)this + 0x2c8) = 8;
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
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *((char*)this + 0x2c8) = 9;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xd && *(int*)((char*)this + v4 * 4 + 0x3158) < 0x14) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19d:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *((char*)this + 0x2c8) = 0xa;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xd && *(int*)((char*)this + v4 * 4 + 0x3158) < 0x14) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19e:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *((char*)this + 0x2c8) = 0xb;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xd && *(int*)((char*)this + v4 * 4 + 0x3158) < 0x14) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x19f:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                    *(int*)((char*)this + v4 * 4 + 0x3358) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    if (*(int*)((char*)this + v4 * 4 + 0x3358) == 6) {
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                        *(int*)((char*)this + v4 * 4 + 0x3358) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 7;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        l50.type = 0x1ab;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 25.0;
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk0 = 1;
                        l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        l50.type = 0x1ad;
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                        *((char*)this + 0x2c9) = 0x16;
                        CPlayer::Unk410a10(5, 5);
                        break;
                    }
                    if (*(int*)((char*)this + v4 * 4 + 0x3258) == 0xf) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3358) < 5) {
                            l50.type = *(int*)((char*)this + v4 * 4 + 0x3358) + 0x1b1;
                            l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                            l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                            l50.unk20 = 0;
                            l50.unk21 = 1;
                            l50.unk18 = 1;
                            Vf9(&l50);
                        }
                        (*(int*)((char*)this + v4 * 4 + 0x3358))++;
                        *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                    }
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 5;
                        (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a1:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb || *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc) {
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *((char*)this + 0x2c8) = 0xc;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xd && *(int*)((char*)this + v4 * 4 + 0x3158) < 0x14) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xd) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a2:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xf) {
                        *((char*)this + 0x2c8) = 0x10;
                        l50.type = 0x1ae;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = 0.0;
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x10 && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xa) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xf;
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                        l50.type = 0x1ae;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = 0.0;
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a3:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) + (*((char*)this + v4 * 0x98 + 0x518) << 2);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 38.0;
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *((char*)this + 0x2c8) = 0xf;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xd && *(int*)((char*)this + v4 * 4 + 0x3158) < 0x14) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a4:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -((WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    l50.type = 0x1af;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) - (*((char*)this + v4 * 0x98 + 0x518) << 2);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 38.0;
                    l50.unk0 = 1;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = -*((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * -1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *((char*)this + 0x2c8) = 0xf;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xd && *(int*)((char*)this + v4 * 4 + 0x3158) < 0x14) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xb;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a5:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 * *((char*)this + 0x50) + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = -*(double*)((char*)this + v4 * 0x98 + 0x4f8);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xb) {
                        *((char*)this + 0x2c8) = 0xe;
                        l50.type = 0x1a6;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = 0.0;
                        l50.unk0 = 1;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a6:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                }
                (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                if (*(int*)((char*)this + v4 * 4 + 0x3158) == 2) {
                    l50.type = 0x1ac;
                    l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                    l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0;
                    l50.unk20 = 2;
                    l50.unk21 = 1;
                    l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                    Vf9(&l50);
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0xa) {
                            (*(int*)((char*)this + v4 * 4 + 0x3258))++;
                            *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 4;
                            break;
                        }
                        l50.type = 0x1ab;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 25.0;
                        l50.unk20 = 2;
                        l50.unk21 = 1;
                        l50.unk0 = 1;
                        l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        l50.type = 0x1ad;
                        Vf9(&l50);
                        Vf9(&l50);
                        Vf9(&l50);
                        *((char*)this + 0x2c9) = 0x16;
                        CPlayer::Unk410a10(5, 5);
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a7:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x10) {
                        l50.type = 0x1a8;
                        l50.unk0 = 1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8) + *((char*)this + v4 * 0x98 + 0x518) * 5;
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 10.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                        Vf9(&l50);
                        *((char*)this + 0x2c8) = 0x12;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x10 && *(int*)((char*)this + v4 * 4 + 0x3158) < 8) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xf;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1a8:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0 && *(int*)((char*)this + v4 * 4 + 0x3158) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.5;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) < 0.0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) >= 0.0) {
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 2) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) + 2;
                    }
                    *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 1.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                }
                if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 650.0 || *(double*)((char*)this + v4 * 0x98 + 0x4e8) < -10.0) {
                    Vf10(v4);
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 2) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = *(WORD*)((char*)this + v4 * 0x98 + 0x4d2) - 2;
                    }
                }
                break;
            case 0x1a9:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0x14) * 0.1 + 0.25;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.5 - (WORD)CPlayer::Unk4108a0(0, 0xa) * 0.05;
                    *(int*)((char*)this + v4 * 4 + 0x3158) = 0;
                }
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) < 5) {
                    *(double*)((char*)this + v4 * 0x98 + 0x500) += 0.025;
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) > 600.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) > 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4e8) < 40.0 && *((char*)this + v4 * 0x98 + 0x518) * *(double*)((char*)this + v4 * 0x98 + 0x4f8) < 0.0) {
                        *((char*)this + v4 * 0x98 + 0x518) = -*((char*)this + v4 * 0x98 + 0x518);
                    }
                    if (*(double*)((char*)this + v4 * 0x98 + 0x4f0) + *(double*)((char*)this + v4 * 0x98 + 0x500) >= 0.0) {
                        *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                        *(double*)((char*)this + v4 * 0x98 + 0x4f0) = 0.0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 5;
                    }
                }
                if (*(int*)((char*)this + v4 * 0x98 + 0x550) == 5) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d2) = (WORD)CPlayer::Unk4108a0(0, 3) + 1;
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = *((char*)this + v4 * 0x98 + 0x518) * 1.0 * *(*(char**)*(char**)((char*)this + 0x78) + 0x50);
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -1.0;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    break;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 5) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 6) {
                        l50.type = 0x1b1;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 7) {
                        l50.type = 0x1b2;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 8) {
                        l50.type = 0x1b3;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 9) {
                        l50.type = 0x1b4;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xa) {
                        l50.type = 0x1b5;
                        l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                        l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0) - 50.0;
                        l50.unk20 = 0;
                        l50.unk21 = 1;
                        l50.unk18 = 1;
                        Vf9(&l50);
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0x10 && *(int*)((char*)this + v4 * 4 + 0x3158) < 0xf) {
                        *(short*)((char*)this + v4 * 0x98 + 0x4d2) = 0xc;
                        (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0xc) {
                        *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                        *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                        *((char*)this + 0x2c8) = 0x11;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == v58 - 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ab:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = (WORD)CPlayer::Unk4108a0(0, 0x168);
                    *(int*)((char*)this + v4 * 4 + 0x3258) = (WORD)CPlayer::Unk4108a0(0, 0x64);
                }
                *(int*)((char*)this + v4 * 4 + 0x3258) -= 3;
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 0xa) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 0xa;
                }
                ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)*(int*)((char*)this + v4 * 4 + 0x3158), *(int*)((char*)this + v4 * 4 + 0x3258) * 0.1);
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ac:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(int*)((char*)this + v4 * 4 + 0x3158) = (WORD)CPlayer::Unk4108a0(0, 0x168);
                    *(int*)((char*)this + v4 * 4 + 0x3258) = (WORD)CPlayer::Unk4108a0(0, 0x1e);
                }
                *(int*)((char*)this + v4 * 4 + 0x3258) -= 4;
                if (*(int*)((char*)this + v4 * 4 + 0x3258) < 5) {
                    *(int*)((char*)this + v4 * 4 + 0x3258) = 5;
                }
                ((ObjBase*)((char*)this + v4 * 0x98 + 0x4d0))->SetVelocity((double)*(int*)((char*)this + v4 * 4 + 0x3158), *(int*)((char*)this + v4 * 4 + 0x3258) * 0.1);
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ad:
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(double*)((char*)this + v4 * 0x98 + 0x4f8) = (WORD)CPlayer::Unk4108a0(0, 0xa0) * 0.1 + -8.0;
                    *(double*)((char*)this + v4 * 0x98 + 0x500) = -8.0;
                }
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        if (*(int*)((char*)this + v4 * 4 + 0x3158) < 0x10) {
                            (*(int*)((char*)this + v4 * 4 + 0x3158))++;
                            (*(short*)((char*)this + v4 * 0x98 + 0x4d2))--;
                            l50.type = 0x1ac;
                            l50.x = *(double*)((char*)this + v4 * 0x98 + 0x4e8);
                            l50.y = *(double*)((char*)this + v4 * 0x98 + 0x4f0);
                            l50.unk20 = 2;
                            l50.unk21 = 1;
                            l50.unk18 = *((char*)this + v4 * 0x98 + 0x518);
                            Vf9(&l50);
                            break;
                        }
                        Vf10(v4);
                    }
                }
                break;
            case 0x1ae:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
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
            case 0x1af:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 2.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = 0.0;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 0 && *(WORD*)((char*)this + v4 * 0x98 + 0x4d4) == 0) {
                    *(short*)((char*)this + v4 * 0x98 + 0x554) = 1;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
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
            case 0x1b1:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.15;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b2:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.15;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b3:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.15;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b4:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.15;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
                    }
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) >= v58) {
                        Vf10(v4);
                    }
                }
                break;
            case 0x1b5:
                *(double*)((char*)this + v4 * 0x98 + 0x4f8) = 0.0;
                *(double*)((char*)this + v4 * 0x98 + 0x500) = -0.15;
                (*(short*)((char*)this + v4 * 0x98 + 0x4d4))++;
                if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d4) >= v54) {
                    *(short*)((char*)this + v4 * 0x98 + 0x4d4) = 0;
                    (*(short*)((char*)this + v4 * 0x98 + 0x4d2))++;
                    *(int*)((char*)this + v4 * 0x98 + 0x550) = 0;
                    if (*(WORD*)((char*)this + v4 * 0x98 + 0x4d2) == 1) {
                        *((char*)this + v4 * 0x98 + 0x520) = 1;
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
