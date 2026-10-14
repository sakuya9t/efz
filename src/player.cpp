// Sixth object of efz.exe (0x40e630-0x412b0f): CPlayer, the base of the character
// classes. Movement and facing, guard and damage, the per-character .pal/.dat/.pat/.wav
// loaders and the state reset at the start of a round. The inline methods of
// PatternData and Afterimages it uses follow it (0x412820-0x412b0f), with
// FUNCTION: 0x412870 ??_EPatternData@@QAEPAXI@Z
//   PatternData's vector deleting destructor, for `delete[]` in ~CPlayer
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

int CPlayer::Unk40e630()
{
    char v1;

    v1 = *((char*)this + 0x50);
    if (*(double*)((char*)this + 0x20) < *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
        *((char*)this + 0x50) = 1;
        return *((char*)this + 0x50) != v1;
    }
    if (*(double*)((char*)this + 0x20) > *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20)) {
        *((char*)this + 0x50) = -1;
        return *((char*)this + 0x50) != v1;
    }
    return 0;
}

int CPlayer::Unk40e6c0(double p1)
{
    char v1;

    v1 = *((char*)this + 0x50);
    if (*(double*)((char*)this + 0x20) < p1) {
        *((char*)this + 0x50) = 1;
        return *((char*)this + 0x50) != v1;
    }
    if (*(double*)((char*)this + 0x20) > p1) {
        *((char*)this + 0x50) = -1;
        return *((char*)this + 0x50) != v1;
    }
    return 0;
}

void CPlayer::Unk40e740()
{
    if (*(double*)((char*)this + 0x28) == 0.0) {
        *((char*)this + 0x159) = 0;
        *((char*)this + 0x15a) = 0;
    }
    if (*(double*)((char*)this + 0x28) >= 0.0 && *(WORD*)((char*)this + 8) != 4 && *(WORD*)((char*)this + 8) != 5 && *(WORD*)((char*)this + 8) != 6 && *(WORD*)((char*)this + 8) != 0xa && *(WORD*)((char*)this + 8) != 0xb && *(WORD*)((char*)this + 8) != 0xc) {
        if (*(int*)((char*)this + 0x15c) < 3 && *((char*)this + 0x189) == -1) {
            Unk40e630();
            if (*(short*)((char*)this + 0x262) >= 3 && *(short*)((char*)this + 0x262) <= 5) {
                if (*(short*)((char*)this + 0x262) == 3) {
                    if (*(WORD*)((char*)this + 8) != 0xa) {
                        Vf0();
                    }
                    *(short*)((char*)this + 8) = 0xa;
                    return;
                }
                if (*(short*)((char*)this + 0x262) == 4) {
                    if (*(WORD*)((char*)this + 8) != 0xb) {
                        Vf0();
                    }
                    *(short*)((char*)this + 8) = 0xb;
                    return;
                }
                if (*(short*)((char*)this + 0x262) == 5) {
                    if (*(WORD*)((char*)this + 8) != 0xc) {
                        Vf0();
                    }
                    *(short*)((char*)this + 8) = 0xc;
                    return;
                }
            } else {
                if (*((char*)this + 0x188) == 0) {
                    if (*(WORD*)((char*)this + 8) != 4) {
                        Vf0();
                    }
                    *(short*)((char*)this + 8) = 4;
                    return;
                }
                if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                    if (*(WORD*)((char*)this + 8) != 5) {
                        Vf0();
                    }
                    *(short*)((char*)this + 8) = 5;
                    return;
                }
                if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
                    if (*(WORD*)((char*)this + 8) != 6) {
                        Vf0();
                    }
                    *(short*)((char*)this + 8) = 6;
                    return;
                }
            }
        }
        if (*((char*)this + 0x189) == 1) {
            if (*(WORD*)((char*)this + 8) != 8 && *(WORD*)((char*)this + 8) != 3) {
                *(short*)((char*)this + 8) = 8;
                Vf0();
                Unk40e630();
                return;
            }
            if (*(WORD*)((char*)this + 8) != 8) {
                *(short*)((char*)this + 8) = 3;
                Unk40e630();
                return;
            }
            return;
        }
        if (*((char*)this + 0x188) != 0) {
            Unk40e630();
            if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
                if (*(WORD*)((char*)this + 8) != 1) {
                    Vf0();
                }
                *(short*)((char*)this + 8) = 1;
                return;
            }
            if (*(WORD*)((char*)this + 8) != 2) {
                Vf0();
            }
            *(short*)((char*)this + 8) = 2;
            return;
        }
        if (*(WORD*)((char*)this + 8) == 3 || *(WORD*)((char*)this + 8) == 8) {
            *(short*)((char*)this + 8) = 7;
            Unk40e630();
            Vf0();
            return;
        }
        if (*(WORD*)((char*)this + 8) == 7 || *(WORD*)((char*)this + 8) == 0xd) {
            Unk40e630();
            return;
        }
        if (*(WORD*)((char*)this + 8) != 0) {
            Vf0();
        }
        *(short*)((char*)this + 8) = 0;
        Unk40e630();
    }
}

CPlayer::CPlayer(int p1, int p2, int p3, int p4, int p5, char p6)
    : unk78(p1)
{
    int v4;

    *(int*)((char*)this + 0x7c) = p2;
    *(int*)((char*)this + 0x80) = p3;
    *(int*)((char*)this + 0x84) = p4;
    *(int*)((char*)this + 0x88) = p5;
    *((char*)this + 0x8c) = p6;
    *((char*)this + 0x8d) = 0;
    *((char*)this + 0x8e) = 0;
    v4 = 0;
    for (; v4 < 0x32; v4++) {
        *(short*)((char*)this + v4 * 2 + 0x264) = 0x96;
    }
    v4 = 0;
    for (; v4 < 0x14; v4++) {
        *((char*)this + v4 + 0x30f5) = -1;
    }
    *(int*)((char*)this + 0x14) = 0;
    *(int*)((char*)this + 0x10) = (int)(char*)new EffectAnim[0x1f9];
    *(int*)((char*)this + 0x164) = (int)(char*)new PatternData[0x1f9];
    *(int*)((char*)this + 0x30c8) = 0;
    *(int*)((char*)this + 0x30cc) = 0;
    *(int*)((char*)this + 0x30d0) = 0;
    *(int*)((char*)this + 0x30d4) = 0;
    *(int*)((char*)this + 0x30d8) = 0;
    *(int*)((char*)this + 0x30e8) = 0;
}

CPlayer::~CPlayer()
{
    int v8;
    int v4;

    if (*(int*)((char*)this + 0x14) != 0) {
        v4 = 0;
        for (; v4 < *(WORD*)((char*)this + 0x18) + 1; v4++) {
            if (*(int*)(*(char**)((char*)this + 0x14) + v4 * 4) != 0) {
                ((IUnknown*)*(int*)(*(char**)((char*)this + 0x14) + v4 * 4))->Release();
                *(int*)(*(char**)((char*)this + 0x14) + v4 * 4) = 0;
            }
        }
        v8 = *(int*)((char*)this + 0x14);
        operator delete((void*)v8);
    }
    v4 = 0;
    for (; v4 < 0x32; v4++) {
        if (*(WORD*)((char*)this + v4 * 2 + 0x264) != 0x96) {
            ((CSound*)*(int*)((char*)this + 0x88))->Release(*(short*)((char*)this + v4 * 2 + 0x264));
        }
    }
    delete[] (EffectAnim*)*(int*)((char*)this + 0x10);
    delete[] (PatternData*)*(int*)((char*)this + 0x164);
}

void CPlayer::Vf12()
{
    int v4;

    *(double*)((char*)this + 0x20) = (double)(*((char*)this + 0x8c) * 0xa0 + 0xf0);
    *(double*)((char*)this + 0x28) = 0.0;
    *((char*)this + 0x50) = 1 - (*((char*)this + 0x8c) << 1);
    Unk40f1e0();
    *(double*)((char*)this + 0xb0) = 0.0;
    *(int*)((char*)this + 0xd0) = 0;
    *(short*)((char*)this + 8) = 0;
    *(short*)((char*)this + 0xa) = 0;
    *(short*)((char*)this + 0xc) = 0;
    *(int*)((char*)this + 0x30bc) = 0;
    *(int*)((char*)this + 0x30c4) = 0;
    *(int*)((char*)this + 0x108) = 0x270f;
    *(int*)((char*)this + 0x10c) = 0x270f;
    *(int*)((char*)this + 0x110) = 0x270f;
    *(short*)((char*)this + 0x148) = 0;
    *(double*)((char*)this + 0x118) = 0.0;
    *((char*)this + 0x120) = 0;
    *(short*)((char*)this + 0x14c) = 0;
    *((char*)this + 0x159) = 0;
    *((char*)this + 0x158) = 0;
    *((char*)this + 0x15a) = 0;
    *(short*)((char*)this + 0x14e) = 0;
    *(int*)((char*)this + 0x150) = 0;
    *((char*)this + 0xac) = 0;
    *(short*)((char*)this + 0x138) = 0;
    *(short*)((char*)this + 0x13a) = 0;
    *(short*)((char*)this + 0x13c) = 0;
    *(short*)((char*)this + 0x13e) = 0;
    *(short*)((char*)this + 0x140) = 0;
    *(int*)((char*)this + 0x15c) = 0;
    *(int*)((char*)this + 0x160) = 0;
    *(int*)((char*)this + 0x168) = 0;
    *(short*)((char*)this + 0x14a) = 0;
    *(int*)((char*)this + 0x134) = 0;
    *(short*)((char*)this + 0x174) = 0;
    *(short*)((char*)this + 0xf4) = 0;
    *(short*)((char*)this + 0x104) = 0;
    *(double*)((char*)this + 0x178) = 10000.0;
    *(double*)((char*)this + 0xf8) = 10000.0;
    *(int*)((char*)this + 0x170) = 0;
    *(double*)((char*)this + 0x180) = 1.0;
    *((char*)this + 0x1a8) = 0;
    *((char*)this + 0x1a9) = 0;
    *(short*)((char*)this + 0x262) = 0x63;
    *(short*)((char*)this + 0x260) = 0;
    v4 = 0;
    for (; v4 < 0xb4; v4++) {
        *((char*)this + v4 + 0x1ab) = 0;
    }
    *((char*)this + 0x2c8) = -1;
    *((char*)this + 0x2c9) = -1;
    *(short*)((char*)this + 0x2ca) = 0;
    *(short*)((char*)this + 0x2cc) = 0;
    Unk413040();
    *(short*)((char*)this + 0x30b4) = 0;
    *((char*)this + 0x2bc0) = 0;
    *((char*)this + 0x2bc2) = 0;
    *(int*)((char*)this + 0x30f0) = 0;
    *(short*)((char*)this + 0x30ec) = 0;
    *((char*)this + 0x58) = 0;
    *(int*)((char*)this + 0x60) = 1;
    *(int*)((char*)this + 0x30dc) = 0;
    *(int*)((char*)this + 0x30d4) = 0;
    *(int*)((char*)this + 0x30d8) = 0;
}

void CPlayer::Vf0()
{
    *(short*)((char*)this + 0xa) = 0;
    *(short*)((char*)this + 0xc) = 0;
    *(double*)((char*)this + 0xb8) = 0.0;
    *(int*)((char*)this + 0x168) = 0;
    *(int*)((char*)this + 0x170) = 0;
    ((Afterimages*)((char*)this + 0x2bc0))->Unk412910();
}

void CPlayer::Unk40f170()
{
    *((char*)this + 0x1a8) = 0;
    *((char*)this + 0x1a9) = 0;
}

void CPlayer::Unk40f190()
{
    int v4;

    v4 = 0;
    for (; v4 < 0xb4; v4++) {
        *((char*)this + v4 + 0x1ab) = 0;
    }
    *(short*)((char*)this + 0x262) = 0x63;
}

void CPlayer::Unk40f1e0()
{
    *(double*)((char*)this + 0x30) = 0.0;
    *(double*)((char*)this + 0x38) = 0.0;
    *(double*)((char*)this + 0x40) = 0.0;
    *(double*)((char*)this + 0x48) = 0.0;
    *(double*)((char*)this + 0xb8) = 0.0;
}

void CPlayer::Unk40f230()
{
    if (*(short*)((char*)this + 0x14a) == 0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        if (*(WORD*)((char*)this + 8) < 0x32 || *(WORD*)((char*)this + 8) > 0x96 || *(WORD*)((char*)this + 8) == 0x60) {
            *(short*)((char*)this + 0x124) = 0;
            *(int*)((char*)this + 0x12c) = 0;
            *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x174) = 0;
            if (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) > 10000.0) {
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) -= 20.0;
            } else {
                *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x178) = 10000.0;
            }
        }
        if (*(WORD*)((char*)this + 8) < 0x32) {
            Vf3();
            *(double*)((char*)this + 0xb8) = 0.0;
            *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xb8) = 0.0;
            if (*(short*)((char*)this + 0x30ec) != 0 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32) {
                *(short*)((char*)this + 0x148) = 0xbb8;
                *(int*)((char*)this + 0x108) = *(short*)((char*)this + 0x30ee);
                if (*(short*)((char*)this + 0x30ec) > 0) {
                    if (*(short*)((char*)this + 0x30ec) < 0x3e8) {
                        *(double*)((char*)this + 0x118) = (double)*(short*)((char*)this + 0x30ec);
                        *((char*)this + 0x120) = 0;
                    } else {
                        *(double*)((char*)this + 0x118) = (double)(0x7d0 - *(short*)((char*)this + 0x30ec));
                        *((char*)this + 0x120) = 1;
                    }
                }
            }
        }
        if (*(WORD*)((char*)this + 8) >= 0x32 && *(WORD*)((char*)this + 8) < 0x96 && *(float*)((char*)this + 0x134) <= 0.0f && (*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xaa) & 0x400) == 0) {
            Unk40f470();
        }
        Vf4();
    }
}

void CPlayer::Unk40f470()
{
    if (*(short*)((char*)this + 0x124) > 0) {
        (*(short*)((char*)this + 0x124))--;
        return;
    }
    if (*(double*)((char*)this + 0x28) < 0.0 && *(int*)((char*)this + 0x128) == 0 && (*((char*)this + 0x18a) != 0 || *((char*)this + 0x18b) != 0 || *((char*)this + 0x18c) != 0 || *((char*)this + 0x18d) != 0)) {
        if (*((char*)this + 0x188) == *((char*)this + 0x50)) {
            if (*(WORD*)((char*)this + 8) != 0x9d) {
                Vf0();
            }
            *(short*)((char*)this + 8) = 0x9d;
            return;
        }
        if (*((char*)this + 0x188) == -*((char*)this + 0x50)) {
            if (*(WORD*)((char*)this + 8) != 0x9e) {
                Vf0();
            }
            *(short*)((char*)this + 8) = 0x9e;
        }
    }
}

void CPlayer::Unk40f580()
{
    int v4;

    v4 = *(short*)((char*)this + 0x2cc);
    if (*(short*)((char*)this + 0x14a) == 0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        if ((double)((char)Unk40ff70() * *((char*)this + 0x50)) * (*(double*)((char*)this + 0x30) + *(double*)((char*)this + 0xb0) + *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xb8) * (double)(*(int*)(*(char**)*(char**)((char*)this + 0x78) + 0xd0) != 0 && *(short*)((char*)this + 0x14c) == 0)) >= 0.0) {
            *(double*)((char*)this + 0x20) = (*(double*)((char*)this + 0x30) + *(double*)((char*)this + 0xb0) + *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0xb8) * (double)(*(int*)(*(char**)*(char**)((char*)this + 0x78) + 0xd0) != 0 && *(short*)((char*)this + 0x14c) == 0)) * (double)*((char*)this + 0x50) + *(double*)((char*)this + 0x20);
        }
        if ((double)(((char)((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40ff70() == 1 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) <= 20.0) + 0x14) > *(double*)((char*)this + 0x20)) {
            *(double*)((char*)this + 0x20) = (double)(((char)((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40ff70() == 1 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) <= 20.0) + 0x14);
        } else if ((double)(0x26b - ((char)((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40ff70() == -1 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) >= 619.0)) < *(double*)((char*)this + 0x20)) {
            *(double*)((char*)this + 0x20) = (double)(0x26b - ((char)((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk40ff70() == -1 && *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) >= 619.0));
        }
        *(double*)((char*)this + 0x28) += *(double*)((char*)this + 0x38);
        if (*(double*)((char*)this + 0x28) > 0.0) {
            *(double*)((char*)this + 0x28) = 0.0;
        }
    }
    while (v4 != *(short*)((char*)this + 0x2ca)) {
        if (*(int*)((char*)this + v4 * 4 + 0x3d0) != 0 && (*(short*)((char*)this + 0x14c) <= 0 || *(int*)((char*)this + v4 * 0x98 + 0x558) != 0) && *(short*)((char*)this + v4 * 0x98 + 0x556) == 0 && *(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
            *(double*)((char*)this + v4 * 0x98 + 0x4e8) += (*(double*)((char*)this + v4 * 0x98 + 0x4f8) + 0.0 * *(double*)((char*)this + v4 * 0x98 + 0x540)) * (double)*((char*)this + v4 * 0x98 + 0x518);
            *(double*)((char*)this + v4 * 0x98 + 0x4f0) += *(double*)((char*)this + v4 * 0x98 + 0x500);
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}

void CPlayer::Unk40f980()
{
    int v4;

    if (*(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) > 0) {
    } else {
        if (*(short*)((char*)this + 0x14a) > 0) {
            (*(short*)((char*)this + 0x14a))--;
        } else {
            *(short*)((char*)this + 0x14a) = 0;
        }
        if (Unk410340() == 0) {
            if (Unk4103a0() != 0) {
                *(float*)((char*)this + 0x134) -= (float)(1.0 / (double)((*(double*)((char*)this + 0x28) == 0.0) * 4 + 1));
            } else {
                *(float*)((char*)this + 0x134) -= 0.075f;
            }
            if (*(float*)((char*)this + 0x134) < 0.0f) {
                *(int*)((char*)this + 0x134) = 0;
            }
        }
        if (*((char*)this + 0x130) > 0) {
            (*((char*)this + 0x130))--;
        } else {
            *((char*)this + 0x130) = 0;
        }
        if ((*(WORD*)(*(char**)(*(char**)((char*)this + 0x164) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc8 + 0xb0) & 0x40) > 0) {
            *((char*)this + 0x130) = 0x1b;
        }
        if (*(short*)((char*)this + 0x138) > 0) {
            (*(short*)((char*)this + 0x138))--;
        } else {
            *(short*)((char*)this + 0x138) = 0;
        }
        if (*(short*)((char*)this + 0x13a) > 0) {
            (*(short*)((char*)this + 0x13a))--;
        } else {
            *(short*)((char*)this + 0x13a) = 0;
        }
        if (*(short*)((char*)this + 0x13c) > 0) {
            (*(short*)((char*)this + 0x13c))--;
        } else {
            *(short*)((char*)this + 0x13c) = 0;
        }
        if (*(short*)((char*)this + 0x13e) > 0) {
            (*(short*)((char*)this + 0x13e))--;
        } else {
            *(short*)((char*)this + 0x13e) = 0;
        }
        if (*(short*)((char*)this + 0x140) > 0) {
            (*(short*)((char*)this + 0x140))--;
        } else {
            *(short*)((char*)this + 0x140) = 0;
        }
        *(double*)((char*)this + 0x118) = (double)((Unk410340() + 1) * (Unk4103a0() == 0 && *((char*)this + 0x120) == 0) * ((*(double*)((char*)this + 0x118) < 500.0) * 2 + 1)) / 10.0 + *(double*)((char*)this + 0x118);
        if (*(double*)((char*)this + 0x118) >= 1000.0 && *((char*)this + 0x120) == 0) {
            *((char*)this + 0x120) = 1;
            *(double*)((char*)this + 0x118) = 1000.0;
        } else if (*(double*)((char*)this + 0x118) <= 0.0) {
            *((char*)this + 0x120) = 0;
            *(double*)((char*)this + 0x118) = 0.0;
        }
        v4 = *(short*)((char*)this + 0x2cc);
        while (v4 != *(short*)((char*)this + 0x2ca)) {
            if (*(int*)((char*)this + v4 * 4 + 0x3d0) != 0) {
                if (*(short*)((char*)this + v4 * 0x98 + 0x556) > 0) {
                    (*(short*)((char*)this + v4 * 0x98 + 0x556))--;
                } else {
                    *(short*)((char*)this + v4 * 0x98 + 0x556) = 0;
                }
            }
            v4++;
            if (v4 >= 0x40) {
                v4 = 0;
            }
        }
        if (((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk4103a0() != 0) {
            *(int*)((char*)this + 0x30e4) = 0x384;
            *(int*)((char*)this + 0x30e0) = 0xc;
        }
        if ((*(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) < 0x32 || *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) >= 0xc8) && *(*(char**)((char*)this + 0x7c) + 0x1350) == 0 && *(int*)(*(char**)((char*)this + 0x7c) + 0x1354) == 0) {
            if (*(DWORD*)((char*)this + 0x30e4) > 0) {
                (*(int*)((char*)this + 0x30e4))--;
            } else {
                if (*(DWORD*)((char*)this + 0x30e0) > 1) {
                    (*(int*)((char*)this + 0x30e0))--;
                }
                if (*(DWORD*)((char*)this + 0x30d0) > 0) {
                    (*(int*)((char*)this + 0x30d0))--;
                }
                *(int*)((char*)this + 0x30e4) = *(int*)((char*)this + 0x30e0) * 5 * 3;
            }
        }
    }
    if (*(short*)((char*)this + 0x148) < 0) {
        *(short*)((char*)this + 0x148) = 0;
    } else if (*(short*)((char*)this + 0x148) > 0xbb8) {
        *(short*)((char*)this + 0x148) = 0xbb8;
    }
    if (*(double*)((char*)this + 0x118) < 0.0) {
        *(double*)((char*)this + 0x118) = 0.0;
    } else if (*(double*)((char*)this + 0x118) > 1000.0) {
        *(double*)((char*)this + 0x118) = 1000.0;
    }
    (*(int*)((char*)this + 0x30f0))--;
    if (*(int*)((char*)this + 0x30f0) <= 0) {
        *(int*)((char*)this + 0x30f0) = 0x3138;
    }
    if (*(short*)((char*)this + 0x104) > 0 && *(short*)((char*)this + 0x174) == 0) {
        (*(short*)((char*)this + 0x104))--;
    }
}

char CPlayer::Unk40ff70()
{
    if (*(double*)((char*)this + 0x20) - 20.0 <= (double)(*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) <= 20.0) || *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) > 280.0) {
        return 1;
    }
    if (*(double*)((char*)this + 0x20) + 20.0 >= (double)(0x27f - (*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) >= 619.0)) || *(double*)((char*)this + 0x20) - *(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) > 280.0) {
        return -1;
    }
    return 0;
}

int CPlayer::Unk410050(int p1, int p2)
{
    if (*(short*)((char*)this + 0x13a) > 0) {
        return 0;
    }
    if ((*(WORD*)((char*)p1 + 0xaa) & 0x80) > 0) {
        return 0;
    }
    if ((*(WORD*)((char*)p2 + 0xb0) & 0x10) == 0) {
        return 0;
    }
    if ((*(WORD*)((char*)p1 + 0xaa) & 4) == 0 && *(double*)((char*)this + 0x28) < 0.0 && *(short*)((char*)this + 0x14e) < 0x1e) {
        return 0;
    }
    if (Unk4100f0(p1) == 0) {
        return 0;
    }
    return 1;
}

int CPlayer::Unk4100f0(int p1)
{
    if (*(int*)((char*)this + 0xa4) != 0) {
        if (*(*(char**)((char*)this + 0x7c) + 0x1364) == 1) {
            if (*(int*)(*(char**)((char*)this + 0x7c) + 0x1348) == 0) {
                return 0;
            }
        } else {
            if ((double)rand() > *(float*)((char*)this + 0xa8) * 1e+04f) {
                return 0;
            }
            if ((*(WORD*)((char*)p1 + 0xaa) & 1) == 0) {
                *((char*)this + 0x189) = 1;
            } else if ((*(WORD*)((char*)p1 + 0xaa) & 2) == 0) {
                *((char*)this + 0x189) = 0;
            }
        }
        if ((*(WORD*)((char*)p1 + 0xaa) & 2) == 0 && *((char*)this + 0x189) == 1 && *(double*)((char*)this + 0x28) == 0.0 || (*(WORD*)((char*)p1 + 0xaa) & 1) == 0 && *((char*)this + 0x189) != 1 && *(double*)((char*)this + 0x28) == 0.0) {
            return 0;
        }
    } else {
        if (*((char*)this + 0x188) != 1 - ((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) > 0.0) << 1) && (Unk410340() == 0 || *((char*)this + 0x188) == 0)) {
            return 0;
        }
        if ((*(WORD*)((char*)p1 + 0xaa) & 2) == 0 && *((char*)this + 0x189) == 1 && *(double*)((char*)this + 0x28) == 0.0 || (*(WORD*)((char*)p1 + 0xaa) & 1) == 0 && *((char*)this + 0x189) != 1 && *(double*)((char*)this + 0x28) == 0.0) {
            return 0;
        }
    }
    return 1;
}

int CPlayer::Unk4102e0()
{
    return *(short*)((char*)this + 0x124) <= 0 && *(double*)((char*)this + 0x28) < 0.0 && *(int*)((char*)this + 0x128) == 0 && Unk4103a0() != 0;
}

int CPlayer::Unk410340()
{
    return *(WORD*)((char*)this + 8) >= 0x96 && *(WORD*)((char*)this + 8) <= 0x9c || *(WORD*)((char*)this + 8) >= 0xa8 && *(WORD*)((char*)this + 8) <= 0xab;
}

int CPlayer::Unk4103a0()
{
    return *(WORD*)((char*)this + 8) >= 0x32 && *(WORD*)((char*)this + 8) < 0x96 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x61 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x62 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x63 && *(WORD*)(*(char**)*(char**)((char*)this + 0x78) + 8) != 0x60;
}

int CPlayer::Unk410420()
{
    return *(WORD*)((char*)this + 8) == 0xa3 || *(WORD*)((char*)this + 8) == 0xa4 || *(WORD*)((char*)this + 8) == 0xa5 || *(WORD*)((char*)this + 8) == 0xa6;
}

double CPlayer::Unk410480()
{
    if (*(*(char**)((char*)this + 0x7c) + 0x1364) == 2) {
        return *(double*)((char*)this + 0x118) / 10000.0 + 1.0;
    }
    if (*(*(char**)((char*)this + 0x7c) + 0x1370) == 1) {
        return (*(double*)((char*)this + 0x118) / 10000.0 + 1.0) / 2.0;
    }
    if (*(*(char**)((char*)this + 0x7c) + 0x1370) == 2) {
        return *(double*)((char*)this + 0x118) / 10000.0 + 1.0;
    }
    return (*(double*)((char*)this + 0x118) / 10000.0 + 1.0) * 2.0;
}

double CPlayer::Unk410530()
{
    return ((double)*(int*)((char*)this + 0x108) * 0.5 / 10000.0 + 0.5) * *(double*)((char*)this + 0x180);
}

double CPlayer::Unk410560()
{
    if (*(double*)((char*)this + 0x178) / 10000.0 > 1.0) {
        return 1.0;
    }
    return *(double*)((char*)this + 0x178) / 10000.0;
}

void CPlayer::Unk4105a0(int p1, double p2)
{
    if (*(short*)((char*)this + 0x174) == 0) {
        *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x10c) = *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108);
    }
    *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108) -= (int)((double)p1 * this->Unk410480() * ((CPlayer*)*(int*)*(char**)((char*)this + 0x78))->Unk410530() * this->Unk410560());
    *(double*)((char*)this + 0xf8) = *(double*)((char*)this + 0x178) / 100.0;
    *(double*)((char*)this + 0x178) = p2 / 1000.0 * *(double*)((char*)this + 0x178);
    if (*(double*)((char*)this + 0x178) > 10000.0) {
        *(double*)((char*)this + 0x178) = p2 / 1000.0 * *(double*)((char*)this + 0x178);
    }
    (*(short*)((char*)this + 0x174))++;
    *(short*)((char*)this + 0xf4) = *(short*)((char*)this + 0x174);
    *(short*)((char*)this + 0x104) = 0xb4;
    *(int*)((char*)this + 0x100) = *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x10c) - *(int*)(*(char**)*(char**)((char*)this + 0x78) + 0x108);
    if ((DWORD)*(short*)((char*)this + 0x174) > *(int*)((char*)this + 0x30d4)) {
        *(int*)((char*)this + 0x30d4) = *(short*)((char*)this + 0x174);
    }
    if (*(DWORD*)((char*)this + 0x100) > *(int*)((char*)this + 0x30d8)) {
        *(int*)((char*)this + 0x30d8) = *(int*)((char*)this + 0x100);
    }
    (*(int*)((char*)this + 0x30d0))++;
    Unk410840(p1 / 0x64 * *(int*)((char*)this + 0x30d0) * *(int*)((char*)this + 0x30d4) * *(short*)((char*)this + 0x174));
}

void CPlayer::Unk410790(int p1)
{
    if ((DWORD)*(short*)((char*)this + 0x174) > *(int*)((char*)this + 0x30d4)) {
        *(int*)((char*)this + 0x30d4) = *(short*)((char*)this + 0x174);
    }
    if (*(DWORD*)((char*)this + 0x100) > *(int*)((char*)this + 0x30d8)) {
        *(int*)((char*)this + 0x30d8) = *(int*)((char*)this + 0x100);
    }
    (*(int*)((char*)this + 0x30d0))++;
    Unk410840(*(short*)((char*)p1 + 0xa0) / 0x64 * *(int*)((char*)this + 0x30d0) * *(int*)((char*)this + 0x30d4) * *(short*)((char*)this + 0x174));
}

void CPlayer::Unk410840(int p1)
{
    *(int*)((char*)this + 0x30c8) += p1;
    while (*(DWORD*)((char*)this + 0x30c8) >= 0x5f5e100) {
        *(int*)((char*)this + 0x30c8) -= 0x5f5e100;
        (*(int*)((char*)this + 0x30cc))++;
    }
}

short CPlayer::Unk4108a0(short p1, short p2)
{
    WORD v8;
    short v4;

    v8 = rand();
    if (*(*(char**)((char*)this + 0x7c) + 0x14283) == 1) {
        v8 = ((CReplayFile*)(*(int*)((char*)this + 0x7c) + 0x14284))->Read();
    } else if (*(*(char**)((char*)this + 0x7c) + 0x14283) == 2) {
        ((CReplayFile*)(*(int*)((char*)this + 0x7c) + 0x14284))->Write(v8);
    }
    v4 = p1 + (p2 - p1) * v8 / 0x8000;
    return v4;
}

void CPlayer::Unk410940()
{
    if (*(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14c) == 0) {
        if (*(BYTE*)((char*)this + 0x2bc0) > 0) {
            ((Afterimages*)((char*)this + 0x2bc0))->Unk412930((ObjBase*)this);
            *((char*)this + 0x2bc2) = 0;
            return;
        }
        if (*(BYTE*)((char*)this + 0x2bc2) > 0) {
            (*((char*)this + 0x2bc2))--;
        }
    }
}

void CPlayer::Unk4109d0(char p1)
{
    ((Afterimages*)((char*)this + 0x2bc0))->Unk412a10((ObjBase*)this, p1);
}

void CPlayer::Unk410a10(int p1, int p2)
{
    *(double*)(*(char**)((char*)this + 0x7c) + 0x14210) = (double)p1;
    *(int*)(*(char**)((char*)this + 0x7c) + 0x14218) = p2;
}

void CPlayer::Unk410a40(int p1, int p2)
{
    *(int*)(*(char**)((char*)this + 0x7c) + 0x14238) = (1 - (*((char*)this + 0x8c) << 1)) * p1;
    *(int*)(*(char**)((char*)this + 0x7c) + 0x14240) = p2;
}

void CPlayer::Unk410a80(int p1, int p2)
{
    *(int*)(*(char**)((char*)this + 0x7c) + 0x1423c) = (1 - (*((char*)this + 0x8c) << 1)) * p1;
    *(int*)(*(char**)((char*)this + 0x7c) + 0x14244) = p2;
}

void CPlayer::Unk410ac0(char p1, int p2)
{
    *((char*)this + 0x30b8) = p1;
    *(int*)((char*)this + 0x30bc) = p2;
    if (*(int*)(*(char**)((char*)this + 0x7c) + 0x136c) == 0) {
        *(int*)((char*)this + 0x30bc) = *(int*)((char*)this + 0x30bc) / 2;
    }
}

void CPlayer::Unk410b10(char p1, int p2)
{
    *((char*)this + 0x30c0) = p1;
    *(int*)((char*)this + 0x30c4) = p2;
    if (*(int*)(*(char**)((char*)this + 0x7c) + 0x136c) == 0) {
        *(int*)((char*)this + 0x30c4) = *(int*)((char*)this + 0x30c4) / 2;
    }
    *(*(char**)((char*)this + 0x7c) + 0xf33) = *((char*)this + 0x8c);
}

void CPlayer::Vf11()
{
    char v2c[32];
    char vc[8];

    if (*(int*)((char*)this + 0x30e8) == 0) {
        Unk411080();
        Unk4116a0();
        Unk411ae0();
        *(int*)((char*)this + 0x30e8) = 1;
    } else if (1 != 0) {
        if (*(int*)(*(char**)((char*)this + 0x7c) + 0x1338 + *((char*)this + 0x8c) * 4) != 0) {
            strcpy(v2c, (const char*)((char*)this + 0x94));
            strcat(v2c, "\\");
            strcat(v2c, (const char*)((char*)this + 0x94));
            _itoa(*((char*)this + 0x8e) + 1, vc, 0xa);
            strcat(v2c, (const char*)vc);
            strcat(v2c, ".pal");
            if (((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteDat((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)v2c, 0, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28) == 0) {
                strcpy(v2c, (const char*)((char*)this + 0x94));
                strcat(v2c, "\\");
                strcat(v2c, (const char*)((char*)this + 0x94));
                strcat(v2c, ".dat");
                ((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteDat((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)v2c, *((char*)this + 0x8e) * 0x28, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28);
            }
        } else {
            strcpy(v2c, (const char*)((char*)this + 0x94));
            strcat(v2c, "\\");
            strcat(v2c, (const char*)((char*)this + 0x94));
            strcat(v2c, ".dat");
            ((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteDat((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)v2c, *((char*)this + 0x8e) * 0x28, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28);
        }
    } else if (*(int*)(*(char**)((char*)this + 0x7c) + 0x1338 + *((char*)this + 0x8c) * 4) != 0) {
        strcpy(v2c, (const char*)((char*)this + 0x94));
        strcat(v2c, "\\");
        strcat(v2c, (const char*)((char*)this + 0x94));
        _itoa(*((char*)this + 0x8e) + 1, vc, 0xa);
        strcat(v2c, (const char*)vc);
        strcat(v2c, ".pal");
        if (((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteDat((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)v2c, 0, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28) == 0) {
            strcpy(v2c, (const char*)((char*)this + 0x94));
            strcat(v2c, "\\000.bmp");
            ((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteBmp((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)v2c, *((char*)this + 0x8e) * 0x28, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28);
        }
    } else {
        strcpy(v2c, (const char*)((char*)this + 0x94));
        strcat(v2c, "\\000.bmp");
        ((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteBmp((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)v2c, *((char*)this + 0x8e) * 0x28, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28);
    }
    Vf12();
    if (*(int*)((char*)this + 0xa4) == 0) {
        if ((*(*(char**)((char*)this + 0x7c) + 0x1364) == 0 || *(*(char**)((char*)this + 0x7c) + 0x1364) == 2) && *(*(char**)((char*)this + 0x7c) + 0x1358) == 1) {
            ((CharRecord*)((char*)this + 0x3118))->Load((const char*)((char*)this + 0x94));
            (*(int*)((char*)this + 0x3118))++;
            ((CharRecord*)((char*)this + 0x3118))->Save((const char*)((char*)this + 0x94));
            return;
        }
        if (*(*(char**)((char*)this + 0x7c) + 0x1364) == 1 || *(*(char**)((char*)this + 0x7c) + 0x1364) == 3 || *(*(char**)((char*)this + 0x7c) + 0x1364) == 4) {
            ((CharRecord*)((char*)this + 0x3118))->Load((const char*)((char*)this + 0x94));
            (*(int*)((char*)this + 0x3118))++;
            ((CharRecord*)((char*)this + 0x3118))->Save((const char*)((char*)this + 0x94));
        }
    }
}

void CPlayer::Unk411080()
{
    int x78;
    int x74;
    int v70;
    int a6c;
    char v68[32];
    int l48;
    char* x44;
    int v40;
    int h3c;
    int n38;
    int a34;
    int d30;
    char x2c[32];
    char bc[8];

    v70 = (int)operator new(*(WORD*)((char*)this + 0x18) * 4 + 4);
    *(int*)((char*)this + 0x14) = v70;
    if (1 != 0) {
        n38 = 0;
        strcpy(x2c, (const char*)((char*)this + 0x94));
        strcat(x2c, "\\");
        strcat(x2c, (const char*)((char*)this + 0x94));
        strcat(x2c, ".dat");
        d30 = (int)CreateFileA((LPCSTR)x2c, 0x80000000, 0, 0, 3, 0x80, 0);
        h3c = GetFileSize((HANDLE)d30, 0);
        x74 = (int)operator new(h3c);
        x44 = (char*)x74;
        ReadFile((HANDLE)d30, (LPVOID)x44, h3c, (LPDWORD)&v40, 0);
        n38 = *(BYTE*)x44 * 3 + 1;
        l48 = 0;
        for (; l48 <= *(WORD*)((char*)this + 0x18); l48++) {
            a34 = ((CGraphics*)*(int*)((char*)this + 0x80))->LoadSurfaceHigh((IDirectDrawSurface**)(*(int*)((char*)this + 0x14) + l48 * 4), (BYTE*)(x44 + n38), 0x80, *((char*)this + 0x8c) * 0x28 + 0x5f);
            if (a34 == 0) {
                _itoa(l48, v68, 0xa);
                MessageBoxA(0, (LPCSTR)v68, 0, 0);
            } else {
                n38 += a34;
            }
        }
        CloseHandle((HANDLE)d30);
        x78 = (int)x44;
        operator delete((void*)x78);
        if (*(int*)(*(char**)((char*)this + 0x7c) + 0x1338 + *((char*)this + 0x8c) * 4) != 0) {
            strcpy(x2c, (const char*)((char*)this + 0x94));
            strcat(x2c, "\\");
            strcat(x2c, (const char*)((char*)this + 0x94));
            _itoa(*((char*)this + 0x8e) + 1, bc, 0xa);
            strcat(x2c, (const char*)bc);
            strcat(x2c, ".pal");
            ((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteDat((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)x2c, 0, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteDat((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)x2c, *((char*)this + 0x8e) * 0x28, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28);
        }
    } else {
        a6c = 0;
        for (; a6c <= *(WORD*)((char*)this + 0x18); a6c++) {
            strcpy(x2c, (const char*)((char*)this + 0x94));
            strcat(x2c, "\\");
            if (a6c >= 0x3e8) {
                strcat(x2c, "A");
                _itoa(a6c, bc, 0xa);
                strcat(x2c, (const char*)bc);
                strcat(x2c, ".bmp");
                ((CGraphics*)*(int*)((char*)this + 0x80))->LoadBmpHigh((IDirectDrawSurface**)(*(int*)((char*)this + 0x14) + a6c * 4), (const char*)x2c, *((char*)this + 0x8c) * 0x28 + 0x5f);
            } else {
                if (a6c < 0x64) {
                    strcat(x2c, "0");
                }
                if (a6c < 0xa) {
                    strcat(x2c, "0");
                }
                _itoa(a6c, bc, 0xa);
                strcat(x2c, (const char*)bc);
                strcat(x2c, ".bmp");
                ((CGraphics*)*(int*)((char*)this + 0x80))->LoadBmpHigh((IDirectDrawSurface**)(*(int*)((char*)this + 0x14) + a6c * 4), (const char*)x2c, *((char*)this + 0x8c) * 0x28 + 0x5f);
            }
        }
        if (*(int*)(*(char**)((char*)this + 0x7c) + 0x1338 + *((char*)this + 0x8c) * 4) != 0) {
            strcpy(x2c, (const char*)((char*)this + 0x94));
            strcat(x2c, "\\");
            strcat(x2c, (const char*)((char*)this + 0x94));
            _itoa(*((char*)this + 0x8e) + 1, bc, 0xa);
            strcat(x2c, (const char*)bc);
            strcat(x2c, ".pal");
            ((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteDat((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)x2c, 0, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28);
        } else {
            strcpy(x2c, (const char*)((char*)this + 0x94));
            strcat(x2c, "\\000.bmp");
            ((CGraphics*)*(int*)((char*)this + 0x80))->LoadPaletteBmp((PALETTEENTRY*)(*(int*)((char*)this + 0x7c) + 0xf35), (const char*)x2c, *((char*)this + 0x8e) * 0x28, *((char*)this + 0x8c) * 0x28 + 0x5f, 0x28);
        }
    }
    *((char*)this + 0x1a) = ((CGraphics*)*(int*)((char*)this + 0x80))->GetColorKey((IDirectDrawSurface*)*(int*)*(char**)((char*)this + 0x14));
}

void CPlayer::Unk4116a0()
{
    int c50;
    char* l4c;
    char* l48;
    int x44;
    int v40;
    int f3c;
    int x38;
    char x34[32];
    int l4;

    strcpy(x34, (const char*)((char*)this + 0x94));
    strcat(x34, "\\");
    strcat(x34, (const char*)((char*)this + 0x94));
    strcat(x34, ".pat");
    CFile k10(x34, 1);
    l4 = k10.ReadInt();
    v40 = 0;
    for (; v40 < l4; v40++) {
        x38 = k10.ReadInt();
        *(short*)(*(char**)((char*)this + 0x164) + x38 * 8) = k10.ReadInt();
        *(short*)(*(char**)((char*)this + 0x164) + 2 + x38 * 8) = k10.ReadInt();
        *(*(char**)((char*)this + 0x10) + x38 * 8) = k10.ReadInt();
        f3c = *(BYTE*)(*(char**)((char*)this + 0x10) + x38 * 8);
        ((PatternData*)(*(int*)((char*)this + 0x164) + x38 * 8))->Alloc(f3c);
        ((EffectAnim*)(*(int*)((char*)this + 0x10) + x38 * 8))->Alloc(f3c);
        x44 = 0;
        for (; x44 < f3c; x44++) {
            l48 = (char*)(*(int*)(*(char**)((char*)this + 0x10) + 4 + x38 * 8) + x44 * 0xc);
            l4c = (char*)(*(int*)(*(char**)((char*)this + 0x164) + 4 + x38 * 8) + x44 * 0xc8);
            *(short*)l48 = (short)k10.ReadInt() * 3;
            *(short*)(l48 + 2) = k10.ReadInt();
            *(short*)(l48 + 8) = k10.ReadInt();
            *(short*)(l48 + 0xa) = k10.ReadInt();
            *(short*)(l48 + 4) = k10.ReadInt();
            *(short*)(l48 + 6) = k10.ReadInt();
            *(short*)(l4c + 0xa0) = k10.ReadInt();
            *(short*)(l4c + 0xaa) = k10.ReadInt();
            *(short*)(l4c + 0xac) = k10.ReadInt();
            *(short*)(l4c + 0xb0) = k10.ReadInt();
            *(short*)(l4c + 0xb2) = k10.ReadInt();
            *(short*)(l4c + 0xa8) = k10.ReadInt();
            *(short*)(l4c + 0xb4) = k10.ReadInt();
            *(short*)(l4c + 0xb6) = k10.ReadInt();
            *(float*)(l4c + 0xbc) = (double)(short)k10.ReadShort();
            *(float*)(l4c + 0xbc) = *(float*)(l4c + 0xbc) / 1e+02f;
            *(float*)(l4c + 0xb8) = (double)(short)k10.ReadShort();
            *(float*)(l4c + 0xb8) = *(float*)(l4c + 0xb8) / -1e+02f;
            *(l4c + 0xc1) = k10.ReadShort();
            *(l4c + 0xc0) = k10.ReadShort();
            *(short*)(l4c + 0xc2) = k10.ReadInt();
            *(short*)(l4c + 0xc4) = k10.ReadInt();
            *(float*)(l4c + 0xa4) = (double)k10.ReadInt();
            *(short*)(l4c + 0xae) = k10.ReadInt();
            k10.Read((void*)(l4c + 0x90), 0x10);
            c50 = 0;
            for (; c50 < 2; c50++) {
                k10.Read((void*)((c50 << 4) + l4c), 0x10);
            }
            k10.Read((void*)(l4c + 0x50), 0x10);
            c50 = 2;
            for (; c50 < 5; c50++) {
                k10.Read((void*)((c50 << 4) + l4c), 0x10);
            }
            c50 = 1;
            for (; c50 < 4; c50++) {
                k10.Read((void*)(l4c + (c50 << 4) + 0x50), 0x10);
            }
        }
    }
    v40 = 0;
    for (; v40 < 0x40; v40++) {
        *(int*)((char*)this + v40 * 0x98 + 0x4d8) = *(int*)((char*)this + 0x10);
    }
}

void CPlayer::Unk411ae0()
{
    int v30;
    char v2c[32];
    char vc[8];

    v30 = 0;
    for (; v30 < 0x32; v30++) {
        strcpy(v2c, (const char*)((char*)this + 0x94));
        strcat(v2c, "\\wave\\");
        if (v30 < 0xa) {
            strcat(v2c, "0");
        }
        _itoa(v30, vc, 0xa);
        strcat(v2c, (const char*)vc);
        strcat(v2c, ".wav");
        *(short*)((char*)this + v30 * 2 + 0x264) = ((CSound*)*(int*)((char*)this + 0x88))->Load((const char*)v2c);
        ((CSound*)*(int*)((char*)this + 0x88))->SetVolume(*(short*)((char*)this + v30 * 2 + 0x264), -0x1f4);
    }
}

void CPlayer::Unk411be0()
{
    BYTE v1;

    if (*(int*)((char*)this + 0xa4) != 0) {
        if (*(*(char**)((char*)this + 0x7c) + 0x1364) == 1) {
            *((char*)this + 0x18a) = 0;
            *((char*)this + 0x18b) = 0;
            *((char*)this + 0x18c) = 0;
            *((char*)this + 0x18d) = 0;
            *((char*)this + 0x188) = 0;
            if (*(*(char**)((char*)this + 0x7c) + 0x1346) == 1) {
                *((char*)this + 0x189) = -1;
            } else if (*(*(char**)((char*)this + 0x7c) + 0x1346) == 2) {
                *((char*)this + 0x189) = 1;
            } else {
                *((char*)this + 0x189) = 0;
            }
            return;
        }
        Vf5();
        if (*(*(char**)((char*)this + 0x7c) + 0x1350) != 0 || *(int*)(*(char**)((char*)this + 0x7c) + 0x1354) != 0) {
            *((char*)this + 0x18a) = 0;
            *((char*)this + 0x18b) = 0;
            *((char*)this + 0x18c) = 0;
            *((char*)this + 0x18d) = 0;
            *(short*)((char*)this + 0x262) = 0x63;
        }
        return;
    }
    v1 = ((CInput*)*(int*)((char*)this + 0x84))->GetInput(*((char*)this + 0x8c));
    if (*(*(char**)((char*)this + 0x7c) + 0x14283) == 1) {
        v1 = ((CReplayFile*)(*(int*)((char*)this + 0x7c) + 0x14284))->Read();
    } else if (*(*(char**)((char*)this + 0x7c) + 0x14283) == 2) {
        ((CReplayFile*)(*(int*)((char*)this + 0x7c) + 0x14284))->Write(v1);
    }
    *((char*)this + 0x188) = 0;
    *((char*)this + 0x189) = 0;
    *((char*)this + 0x18a) = 0;
    *((char*)this + 0x18b) = 0;
    *((char*)this + 0x18c) = 0;
    *((char*)this + 0x18d) = 0;
    if ((v1 & 8) > 0) {
        *((char*)this + 0x189) = -1;
    } else if ((v1 & 4) > 0) {
        *((char*)this + 0x189) = 1;
    }
    if (*((char*)this + 0x50) > 0) {
        if ((v1 & 2) > 0) {
            *((char*)this + 0x188) = -1;
        } else if ((v1 & 1) > 0) {
            *((char*)this + 0x188) = 1;
        }
    } else if ((v1 & 1) > 0) {
        *((char*)this + 0x188) = 1;
    } else if ((v1 & 2) > 0) {
        *((char*)this + 0x188) = -1;
    }
    if ((v1 & 0x10) > 0) {
        *((char*)this + 0x18a) = *(int*)((char*)this + 0x190) == 0;
        *(int*)((char*)this + 0x190) = 1;
    } else {
        *(int*)((char*)this + 0x190) = 0;
    }
    if ((v1 & 0x20) > 0) {
        *((char*)this + 0x18b) = *(int*)((char*)this + 0x194) == 0;
        *(int*)((char*)this + 0x194) = 1;
    } else {
        *(int*)((char*)this + 0x194) = 0;
    }
    if ((v1 & 0x40) > 0) {
        *((char*)this + 0x18c) = *(int*)((char*)this + 0x198) == 0;
        *(int*)((char*)this + 0x198) = 1;
    } else {
        *(int*)((char*)this + 0x198) = 0;
    }
    if ((v1 & 0x80) > 0) {
        *((char*)this + 0x18d) = *(int*)((char*)this + 0x19c) == 0;
        *(int*)((char*)this + 0x19c) = 1;
    } else {
        *(int*)((char*)this + 0x19c) = 0;
    }
    if (*(*(char**)((char*)this + 0x7c) + 0x1350) != 0 || *(int*)(*(char**)((char*)this + 0x7c) + 0x1354) != 0) {
        *((char*)this + 0x18a) = 0;
        *((char*)this + 0x18b) = 0;
        *((char*)this + 0x18c) = 0;
        *((char*)this + 0x18d) = 0;
        *(short*)((char*)this + 0x262) = 0x63;
    }
    *((char*)this + *(short*)((char*)this + 0x260) + 0x1ab) = (*((char*)this + 0x188) == 1) + (*((char*)this + 0x188) == -1) * 2 + (*((char*)this + 0x189) == 1) * 4 + (*((char*)this + 0x189) == -1) * 8 + (*((char*)this + 0x18a) << 4) + (*((char*)this + 0x18b) << 5) + (*((char*)this + 0x18c) << 6) + (*((char*)this + 0x18d) << 7);
    if (*(BYTE*)((char*)this + *(short*)((char*)this + 0x260) + 0x1ab) >= 0x10) {
        if (*(WORD*)((char*)this + 8) >= 0xc8) {
            *((char*)this + 0x1a8) = *((char*)this + *(short*)((char*)this + 0x260) + 0x1ab);
        }
        if (*(WORD*)((char*)this + 8) >= 0xa3 && *(WORD*)((char*)this + 8) <= 0xa6) {
            *((char*)this + 0x1a9) = *((char*)this + *(short*)((char*)this + 0x260) + 0x1ab);
            *((char*)this + 0x1aa) = 0xf;
        }
    }
    (*(short*)((char*)this + 0x260))++;
    if (*(short*)((char*)this + 0x260) >= 0xb4) {
        *(short*)((char*)this + 0x260) = 0;
    }
    if (*((char*)this + 0x188) == 1 - ((*(double*)(*(char**)*(char**)((char*)this + 0x78) + 0x20) - *(double*)((char*)this + 0x20) > 0.0) << 1) && *(short*)((char*)this + 0x14e) == 0 && *(int*)((char*)this + 0x150) == 0) {
        *(short*)((char*)this + 0x14e) = 0x3c;
    }
    if (*(short*)(*(char**)*(char**)((char*)this + 0x78) + 0x14a) == 0 && *(short*)((char*)this + 0x14e) > 0) {
        (*(short*)((char*)this + 0x14e))--;
    }
    if (*((char*)this + 0x188) == 0) {
        *(int*)((char*)this + 0x150) = 0;
    } else {
        *(int*)((char*)this + 0x150) = 1;
    }
    Vf2();
}

void CPlayer::Unk4121a0(int p1, int p2)
{
    int v34;
    RECT v30;
    EffectFrame v20;
    RECT v14;
    int l4;

    if (*(BYTE*)((char*)this + 0x2bc0) > 0 || *(BYTE*)((char*)this + 0x2bc2) > 0) {
        v34 = *(short*)((char*)this + 0x30b4) - (*(BYTE*)((char*)this + 0x2bc0) * 3 + *(BYTE*)((char*)this + 0x2bc2));
        l4 = 0;
        for (; l4 < *(BYTE*)((char*)this + 0x2bc2) + *(BYTE*)((char*)this + 0x2bc0) * 3; l4 = *(BYTE*)((char*)this + 0x2bc1) + l4) {
            if (v34 >= 0x3c) {
                v34 -= 0x3c;
            }
            if (v34 < 0) {
                v34 += 0x3c;
            }
            v20 = *(EffectFrame*)(char*)(*(int*)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + v34 * 2 + 0x2fc4) * 8 + 4) + *(WORD*)((char*)this + v34 * 2 + 0x303c) * 0xc);
            v30.left = 0;
            v30.top = 0;
            v30.right = v20.width;
            v30.bottom = v20.height;
            v14.left = (int)*(double*)((char*)this + v34 * 8 + 0x2bc8) + p1 - v20.x * (*((char*)this + v34 + 0x2f88) == 1) - (v20.width - v20.x) * (*((char*)this + v34 + 0x2f88) == -1);
            v14.top = (int)*(double*)((char*)this + v34 * 8 + 0x2da8) + 0xd2 - (*(double*)((char*)this + v34 * 8 + 0x2da8) < 0.0) - v20.y + p2;
            v14.right = v20.width + v14.left;
            v14.bottom = v20.height + v14.top;
            ((CGraphics*)*(int*)((char*)this + 0x80))->BlitEx(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + v20.surface * 4), v30, *((char*)this + 0x1a), *((char*)this + v34 + 0x2f88) == -1, 0);
            v34 = *(BYTE*)((char*)this + 0x2bc1) + v34;
        }
    }
    v20 = *(EffectFrame*)(char*)(*(int*)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + 8) * 8 + 4) + *(WORD*)((char*)this + 0xa) * 0xc);
    v30.left = 0;
    v30.top = 0;
    v30.right = v20.width;
    v30.bottom = v20.height;
    v14.left = (int)*(double*)((char*)this + 0x20) + p1 - v20.x * (*((char*)this + 0x50) == 1) - (v20.width - v20.x) * (*((char*)this + 0x50) == -1);
    v14.top = (int)*(double*)((char*)this + 0x28) + 0xd2 - (*(double*)((char*)this + 0x28) < 0.0) - v20.y + p2;
    v14.right = v20.width + v14.left;
    v14.bottom = v20.height + v14.top;
    if (v14.top < 0xf0) {
        if (*(int*)((char*)this + 0x30bc) == 0) {
            if (*((char*)this + 0x58) == 3) {
                ((CGraphics*)*(int*)((char*)this + 0x80))->BlitSmear(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + v20.surface * 4), v30, *((char*)this + 0x1a), *((char*)this + 0x50) == -1);
            } else if (*((char*)this + 0x58) > 0) {
                ((CGraphics*)*(int*)((char*)this + 0x80))->BlitEx(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + v20.surface * 4), v30, *((char*)this + 0x1a), *((char*)this + 0x50) == -1, *((char*)this + 0x58) - 1);
            } else {
                ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + v20.surface * 4), v30, *((char*)this + 0x1a), *((char*)this + 0x50) == -1);
            }
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x80))->BlitTint(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + v20.surface * 4), v30, *((char*)this + 0x1a), *((char*)this + 0x50) == -1, *((char*)this + 0x30b8));
            (*(int*)((char*)this + 0x30bc))--;
        }
        return;
    }
    if (*(short*)((char*)this + 0x13e) == 0) {
        v20 = *(EffectFrame*)*(char**)(*(char**)((char*)this + 0x10) + 0x18c);
        v30.left = 0;
        v30.top = 0;
        v30.right = v20.width;
        v30.bottom = v20.height;
        v14.left = (int)*(double*)((char*)this + 0x20) + p1 - v20.x * (*((char*)this + 0x50) == 1) - (v20.width - v20.x) * (*((char*)this + 0x50) == -1);
        v14.top = 0xef - v20.y;
        v14.right = v20.width + v14.left;
        v14.bottom = v20.height + v14.top;
        ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + v20.surface * 4), v30, *((char*)this + 0x1a), *((char*)this + 0x50) == -1);
    }
}
