// Seventh object of efz.exe (0x412b10-0x4136cf): CPlayer's table of 64 objects
// (projectiles and other things a character spawns), with the slots used and freed in
// a ring, and drawing them.
#include <stdlib.h>
#include <string.h>
#include "efz.h"

void CPlayer::Vf9(int p1)
{
    *(int*)((char*)this + *(short*)((char*)this + 0x2ca) * 4 + 0x3d0) = 1;
    *(int*)((char*)this + *(short*)((char*)this + 0x2ca) * 4 + 0x2d0) = *(int*)(char*)p1;
    *(short*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x4d0) = *(short*)((char*)p1 + 4);
    *(short*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x4d2) = 0;
    *(short*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x4d4) = 0;
    *(double*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x4e8) = *(double*)((char*)p1 + 8);
    *(double*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x4f0) = *(double*)((char*)p1 + 0x10);
    *(double*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x4f8) = 0.0;
    *(double*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x500) = 0.0;
    *(double*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x508) = 0.0;
    *(double*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x510) = 0.0;
    *((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x518) = *((char*)p1 + 0x18);
    *(int*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x51c) = *(int*)((char*)p1 + 0x1c);
    *((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x520) = *((char*)p1 + 0x20);
    *((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x53c) = *((char*)p1 + 0x2c);
    *(int*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x524) = *(int*)((char*)p1 + 0x24);
    *((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x521) = *((char*)p1 + 0x21);
    *(int*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x528) = *(int*)((char*)p1 + 0x28);
    *(int*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x558) = *(int*)((char*)p1 + 0x30);
    *(int*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x55c) = 0;
    *(RECT*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x52c) = *(RECT*)(char*)(p1 + 0x34);
    *(int*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x550) = 0;
    *(short*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x554) = 0;
    *(short*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x556) = 0;
    *(double*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x540) = 0.0;
    *(double*)((char*)this + *(short*)((char*)this + 0x2ca) * 0x98 + 0x548) = 0.0;
    Unk412f10();
}

void CPlayer::Vf10(short p1)
{
    *(int*)((char*)this + p1 * 4 + 0x3d0) = 0;
    *(int*)((char*)this + p1 * 4 + 0x2d0) = 0;
    if (p1 == *(short*)((char*)this + 0x2cc)) {
        while (*(short*)((char*)this + 0x2cc) != *(short*)((char*)this + 0x2ca) && *(int*)((char*)this + *(short*)((char*)this + 0x2cc) * 4 + 0x3d0) == 0) {
            (*(short*)((char*)this + 0x2cc))++;
            if (*(short*)((char*)this + 0x2cc) >= 0x40) {
                *(short*)((char*)this + 0x2cc) = 0;
            }
        }
    }
}

void CPlayer::Unk412f10()
{
    int v4;

    v4 = 0;
    do {
        (*(short*)((char*)this + 0x2ca))++;
        if (*(short*)((char*)this + 0x2ca) >= 0x40) {
            *(short*)((char*)this + 0x2ca) = 0;
        }
        if (*(short*)((char*)this + 0x2ca) == *(short*)((char*)this + 0x2cc)) {
            (*(short*)((char*)this + 0x2cc))++;
            if (*(short*)((char*)this + 0x2cc) >= 0x40) {
                *(short*)((char*)this + 0x2cc) = 0;
            }
            while (*(short*)((char*)this + 0x2cc) != *(short*)((char*)this + 0x2ca) && *(int*)((char*)this + *(short*)((char*)this + 0x2cc) * 4 + 0x3d0) == 0) {
                (*(short*)((char*)this + 0x2cc))++;
                if (*(short*)((char*)this + 0x2cc) >= 0x40) {
                    *(short*)((char*)this + 0x2cc) = 0;
                }
            }
        }
        v4++;
    } while (*(int*)((char*)this + *(short*)((char*)this + 0x2ca) * 4 + 0x2d0) != 0 && v4 < 0x3f);
}

void CPlayer::Unk413040()
{
    int v4;

    v4 = 0;
    for (; v4 < 0x40; v4++) {
        *(int*)((char*)this + v4 * 4 + 0x3d0) = 0;
        *(int*)((char*)this + v4 * 4 + 0x2d0) = 0;
    }
}

void CPlayer::Unk413090(int p1)
{
    *(int*)(char*)p1 = 0;
    *((char*)p1 + 0x20) = 0;
    *((char*)p1 + 0x2c) = -1;
    *(int*)((char*)p1 + 0x24) = 0;
    *(int*)((char*)p1 + 0x28) = 0;
    *(int*)((char*)p1 + 0x30) = 0;
    *(int*)((char*)p1 + 0x38) = 0;
    *(int*)((char*)p1 + 0x40) = 0;
    *(int*)((char*)p1 + 0x34) = 0;
    *(int*)((char*)p1 + 0x3c) = 0;
}

void CPlayer::Unk413100(int p1, int p2, BYTE p3)
{
    RECT v28;
    char* v18;
    RECT v14;
    int l4;

    l4 = *(short*)((char*)this + 0x2cc);
    while (l4 != *(short*)((char*)this + 0x2ca)) {
        if (*(int*)((char*)this + l4 * 4 + 0x3d0) != 0 && p3 == *(BYTE*)((char*)this + l4 * 0x98 + 0x521) && (*(int*)((char*)this + l4 * 0x98 + 0x55c) != 0 || *(short*)(*(char**)((char*)this + 0x7c) + 0x1420e) == 0)) {
            v18 = (char*)(*(int*)(*(char**)((char*)this + 0x10) + *(WORD*)((char*)this + l4 * 0x98 + 0x4d0) * 8 + 4) + *(WORD*)((char*)this + l4 * 0x98 + 0x4d2) * 0xc);
            v28 = MakeRect(0, 0, *(short*)(v18 + 8), *(short*)(v18 + 0xa));
            if (*((char*)this + l4 * 0x98 + 0x518) == -1) {
                v14.left = (int)*(double*)((char*)this + l4 * 0x98 + 0x4e8) + (*(int*)((char*)this + l4 * 0x98 + 0x524) == 0) * p1 - (*(short*)(v18 + 8) - *(short*)(v18 + 4));
                v14.top = (p2 + 0xd2) * (*(int*)((char*)this + l4 * 0x98 + 0x524) == 0) + (int)*(double*)((char*)this + l4 * 0x98 + 0x4f0) - *(short*)(v18 + 6);
                v14.right = *(short*)(v18 + 8) + v14.left;
                v14.bottom = *(short*)(v18 + 0xa) + v14.top;
            } else {
                v14.left = (int)*(double*)((char*)this + l4 * 0x98 + 0x4e8) + (*(int*)((char*)this + l4 * 0x98 + 0x524) == 0) * p1 - *(short*)(v18 + 4);
                v14.top = (p2 + 0xd2) * (*(int*)((char*)this + l4 * 0x98 + 0x524) == 0) + (int)*(double*)((char*)this + l4 * 0x98 + 0x4f0) - *(short*)(v18 + 6);
                v14.right = *(short*)(v18 + 8) + v14.left;
                v14.bottom = *(short*)(v18 + 0xa) + v14.top;
            }
            if (*(int*)((char*)this + l4 * 0x98 + 0x530) != *(int*)((char*)this + l4 * 0x98 + 0x538)) {
                if (v14.left < *(int*)((char*)this + l4 * 0x98 + 0x52c)) {
                    v28.left = *(int*)((char*)this + l4 * 0x98 + 0x52c) - v14.left + v28.left;
                    v14.left = *(int*)((char*)this + l4 * 0x98 + 0x52c);
                }
                if (v14.right > *(int*)((char*)this + l4 * 0x98 + 0x534)) {
                    v28.right -= v14.right - *(int*)((char*)this + l4 * 0x98 + 0x534);
                    v14.right = *(int*)((char*)this + l4 * 0x98 + 0x534);
                }
                if (v14.top < *(int*)((char*)this + l4 * 0x98 + 0x530)) {
                    v28.top = *(int*)((char*)this + l4 * 0x98 + 0x530) - v14.top + v28.top;
                    v14.top = *(int*)((char*)this + l4 * 0x98 + 0x530);
                }
                if (v14.bottom > *(int*)((char*)this + l4 * 0x98 + 0x538)) {
                    v28.bottom -= v14.bottom - *(int*)((char*)this + l4 * 0x98 + 0x538);
                    v14.bottom = *(int*)((char*)this + l4 * 0x98 + 0x538);
                }
            }
            if (*((char*)this + l4 * 0x98 + 0x520) == 3) {
                ((CGraphics*)*(int*)((char*)this + 0x80))->BlitSmear(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + *(WORD*)(v18 + 2) * 4), v28, *((char*)this + 0x1a), *((char*)this + l4 * 0x98 + 0x518) == -1);
            } else if (*((char*)this + l4 * 0x98 + 0x520) > 0) {
                ((CGraphics*)*(int*)((char*)this + 0x80))->BlitEx(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + *(WORD*)(v18 + 2) * 4), v28, *((char*)this + 0x1a), *((char*)this + l4 * 0x98 + 0x518) == -1, *((char*)this + l4 * 0x98 + 0x520) - 1);
            } else {
                ((CGraphics*)*(int*)((char*)this + 0x80))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x14) + *(WORD*)(v18 + 2) * 4), v28, *((char*)this + 0x1a), *((char*)this + l4 * 0x98 + 0x518) == -1);
            }
        }
        l4++;
        if (l4 >= 0x40) {
            l4 = 0;
        }
    }
}
