// The drawing helpers CScene3::Draw calls (0x75db70-0x76339f): numbers from digit
// sprites, the gauges and the rest of the fight's overlay. They are a file of their own,
// as in the original: their floating-point constants precede the string section the
// rest of CScene3 (scene3.cpp) starts with.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

void CScene3::Unk75db70(int p1, int p2, int p3, BYTE p4, BYTE p5, int p6)
{
    RECT v2c;
    int v1c;
    RECT l18;
    DWORD x8;
    int l4;

    x8 = p3;
    l4 = p1;
    do {
        v1c = x8 % 0xa;
        v2c.top = *(int*)((char*)this + (p4 << 4) + 0x468);
        v2c.bottom = *(int*)((char*)this + (p4 << 4) + 0x470);
        v2c.left = *(int*)((char*)this + (p4 << 4) + 0x46c) * v1c;
        v2c.right = *(int*)((char*)this + (p4 << 4) + 0x46c) * (v1c + 1);
        l18.top = p2;
        l18.bottom = *(int*)((char*)this + (p4 << 4) + 0x470) - *(int*)((char*)this + (p4 << 4) + 0x468) + p2;
        l18.right = l4;
        l18.left = l4 - *(int*)((char*)this + (p4 << 4) + 0x46c);
        if (p6 != 0) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->BlitEx(l18, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v2c, *(*(char**)((char*)this + 0x1c) + 0xf34), 0, 0);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(l18, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v2c, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        }
        l4 -= *(int*)((char*)this + (p4 << 4) + 0x46c) + p5;
        x8 = x8 / 0xa;
    } while (x8 > 0);
}

void CScene3::Unk75dd50()
{
    RECT v30;
    int v20;
    RECT x1c;
    int vc;
    int x8;
    int l4;

    vc = (int)(-*(int*)((char*)this + 0x45c) * *(double*)(*(char**)((char*)this + 0x1c) + 0x14258) + (160.0 - 160.0 * *(double*)(*(char**)((char*)this + 0x1c) + 0x14258)));
    x8 = (int)((0xf0 - *(int*)((char*)this + 0x460)) * *(double*)(*(char**)((char*)this + 0x1c) + 0x14258) + (120.0 - 120.0 * *(double*)(*(char**)((char*)this + 0x1c) + 0x14258)));
    l4 = 0;
    v20 = 0;
    if (vc > 0x140) {
        l4 = 0x140 - vc;
        vc = 0x140;
    } else if (vc < 0) {
        l4 = -vc;
        vc = 0;
    }
    if (x8 > 0xf0) {
        v20 = 0xf0 - x8;
        x8 = 0xf0;
    } else if (x8 < 0) {
        v20 = -x8;
        x8 = 0;
    }
    v30 = MakeRect(vc, x8, 0x140, 0xf0);
    x1c = MakeRect(l4, v20, 0x140, 0xf0);
    if (*(int*)(*(char**)((char*)this + 0xc) + 0x30c4) > 0 && *(int*)(*(char**)((char*)this + 0x10) + 0x30c4) > 0) {
        if (*(*(char**)((char*)this + 0x1c) + 0xf33) == 0) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(x1c, *(*(char**)((char*)this + 0xc) + 0x30c0));
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(x1c, *(*(char**)((char*)this + 0x10) + 0x30c0));
        }
        if (*(short*)(*(char**)((char*)this + 0xc) + 0x14c) == 0 && *(short*)(*(char**)((char*)this + 0x10) + 0x14c) == 0) {
            (*(int*)(*(char**)((char*)this + 0xc) + 0x30c4))--;
            (*(int*)(*(char**)((char*)this + 0x10) + 0x30c4))--;
        }
        return;
    }
    if (*(int*)(*(char**)((char*)this + 0xc) + 0x30c4) > 0) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(x1c, *(*(char**)((char*)this + 0xc) + 0x30c0));
        if (*(short*)(*(char**)((char*)this + 0xc) + 0x14c) == 0 && *(short*)(*(char**)((char*)this + 0x10) + 0x14c) == 0) {
            (*(int*)(*(char**)((char*)this + 0xc) + 0x30c4))--;
        }
        return;
    }
    if (*(int*)(*(char**)((char*)this + 0x10) + 0x30c4) > 0) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(x1c, *(*(char**)((char*)this + 0x10) + 0x30c0));
        if (*(short*)(*(char**)((char*)this + 0xc) + 0x14c) == 0 && *(short*)(*(char**)((char*)this + 0x10) + 0x14c) == 0) {
            (*(int*)(*(char**)((char*)this + 0x10) + 0x30c4))--;
        }
        return;
    }
    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x14278) > 0) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x1c, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xe9c), v30, 0, 0);
        if (*(short*)(*(char**)((char*)this + 0xc) + 0x14c) == 0 && *(short*)(*(char**)((char*)this + 0x10) + 0x14c) == 0) {
            (*(int*)(*(char**)((char*)this + 0x1c) + 0x14278))--;
        }
        return;
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x1c, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xe98), v30, 0, 0);
    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x137c) != 0) {
        ((CAnimBg*)*(int*)(*(char**)((char*)this + 0x1c) + 0x137c))->Vf1(*(int*)((char*)this + 0x45c), *(int*)((char*)this + 0x460), 0);
    }
}

void CScene3::Unk75e240()
{
    RECT v24;
    int v14;
    RECT n10;

    if (*(int*)(*(char**)((char*)this + 0xc) + 0x110) > *(int*)(*(char**)((char*)this + 0xc) + 0x108)) {
        *(int*)(*(char**)((char*)this + 0xc) + 0x110) -= 0xc8;
        if (*(int*)(*(char**)((char*)this + 0xc) + 0x110) < *(int*)(*(char**)((char*)this + 0xc) + 0x108)) {
            *(int*)(*(char**)((char*)this + 0xc) + 0x110) = *(int*)(*(char**)((char*)this + 0xc) + 0x108);
        }
    }
    if (*(int*)(*(char**)((char*)this + 0xc) + 0x110) < *(int*)(*(char**)((char*)this + 0xc) + 0x108)) {
        *(int*)(*(char**)((char*)this + 0xc) + 0x110) += 0xc8;
        if (*(int*)(*(char**)((char*)this + 0xc) + 0x110) > *(int*)(*(char**)((char*)this + 0xc) + 0x108)) {
            *(int*)(*(char**)((char*)this + 0xc) + 0x110) = *(int*)(*(char**)((char*)this + 0xc) + 0x108);
        }
    }
    if (*(short*)(*(char**)((char*)this + 0x10) + 0x174) == 0) {
        *(int*)(*(char**)((char*)this + 0xc) + 0x10c) -= (*(int*)(*(char**)((char*)this + 0xc) + 0x10c) > *(int*)(*(char**)((char*)this + 0xc) + 0x108)) * 0x64;
        if (*(int*)(*(char**)((char*)this + 0xc) + 0x10c) < *(int*)(*(char**)((char*)this + 0xc) + 0x108)) {
            *(int*)(*(char**)((char*)this + 0xc) + 0x10c) = *(int*)(*(char**)((char*)this + 0xc) + 0x108);
        }
    }
    if (*(int*)(*(char**)((char*)this + 0x10) + 0x110) > *(int*)(*(char**)((char*)this + 0x10) + 0x108)) {
        *(int*)(*(char**)((char*)this + 0x10) + 0x110) -= 0xc8;
        if (*(int*)(*(char**)((char*)this + 0x10) + 0x110) < *(int*)(*(char**)((char*)this + 0x10) + 0x108)) {
            *(int*)(*(char**)((char*)this + 0x10) + 0x110) = *(int*)(*(char**)((char*)this + 0x10) + 0x108);
        }
    }
    if (*(int*)(*(char**)((char*)this + 0x10) + 0x110) < *(int*)(*(char**)((char*)this + 0x10) + 0x108)) {
        *(int*)(*(char**)((char*)this + 0x10) + 0x110) += 0xc8;
        if (*(int*)(*(char**)((char*)this + 0x10) + 0x110) > *(int*)(*(char**)((char*)this + 0x10) + 0x108)) {
            *(int*)(*(char**)((char*)this + 0x10) + 0x110) = *(int*)(*(char**)((char*)this + 0x10) + 0x108);
        }
    }
    if (*(short*)(*(char**)((char*)this + 0xc) + 0x174) == 0) {
        *(int*)(*(char**)((char*)this + 0x10) + 0x10c) -= (*(int*)(*(char**)((char*)this + 0x10) + 0x10c) > *(int*)(*(char**)((char*)this + 0x10) + 0x108)) * 0x64;
        if (*(int*)(*(char**)((char*)this + 0x10) + 0x10c) < *(int*)(*(char**)((char*)this + 0x10) + 0x108)) {
            *(int*)(*(char**)((char*)this + 0x10) + 0x10c) = *(int*)(*(char**)((char*)this + 0x10) + 0x108);
        }
    }
    if (*(short*)(*(char**)((char*)this + 0x1c) + 0x1420c) > 0) {
        return;
    }
    v24 = MakeRect(0, 0, *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x184) + 8), *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x184) + 0xa));
    n10 = MakeRect(0, 0xe, *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x184) + 8), *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x184) + 0xa));
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)(*(char**)((char*)this + 0xc) + 0x14) + *(WORD*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x184) + 2) * 4), v24, *(*(char**)((char*)this + 0xc) + 0x1a), 0);
    v24 = MakeRect(0, 0, *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x184) + 8), *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x184) + 0xa));
    n10 = MakeRect(0x140 - *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x184) + 8), 0xe, *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x184) + 8), *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x184) + 0xa));
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)(*(char**)((char*)this + 0x10) + 0x14) + *(WORD*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x184) + 2) * 4), v24, *(*(char**)((char*)this + 0x10) + 0x1a), 1);
    v24 = MakeRect(0, 0, 0x140, 0x2c);
    n10 = MakeRect(0, 0, 0x140, 0x2c);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    v24 = MakeRect(0, 0, *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x16c) + 8), *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x16c) + 0xa));
    n10 = MakeRect(1, 0x28, *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x16c) + 8), *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x16c) + 0xa));
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)(*(char**)((char*)this + 0xc) + 0x14) + *(WORD*)(*(char**)(*(char**)(*(char**)((char*)this + 0xc) + 0x10) + 0x16c) + 2) * 4), v24, *(*(char**)((char*)this + 0xc) + 0x1a), 0);
    v24 = MakeRect(0, 0, *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x16c) + 8), *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x16c) + 0xa));
    n10 = MakeRect(0x13f - *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x16c) + 8), 0x28, *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x16c) + 8), *(short*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x16c) + 0xa));
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)(*(char**)((char*)this + 0x10) + 0x14) + *(WORD*)(*(char**)(*(char**)(*(char**)((char*)this + 0x10) + 0x10) + 0x16c) + 2) * 4), v24, *(*(char**)((char*)this + 0x10) + 0x1a), 0);
    v14 = (int)(*(int*)(*(char**)((char*)this + 0xc) + 0x10c) * 120.0 / 9999.0);
    if (v14 > 0) {
        v24 = MakeRect(0x78 - v14, 0x5b, v14, 6);
        n10 = MakeRect(0x8a - v14, 0x12, v14, 6);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    v14 = (int)(*(int*)(*(char**)((char*)this + 0xc) + 0x110) * 120.0 / 9999.0);
    if (v14 >= 0x28) {
        v24 = MakeRect(0x78 - v14, 0x49, v14, 6);
        n10 = MakeRect(0x8a - v14, 0x12, v14, 6);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    } else if (v14 > 0) {
        v24 = MakeRect(0x78 - v14, *(int*)(*(char**)((char*)this + 0xc) + 0x30f0) % 0x24 / 0x12 * 6 + 0x4f, v14, 6);
        n10 = MakeRect(0x8a - v14, 0x12, v14, 6);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    v14 = (int)(*(int*)(*(char**)((char*)this + 0x10) + 0x10c) * 120.0 / 9999.0);
    if (v14 > 0) {
        v24 = MakeRect(0x78, 0x5b, v14, 6);
        n10 = MakeRect(0xb6, 0x12, v14, 6);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    v14 = (int)(*(int*)(*(char**)((char*)this + 0x10) + 0x110) * 120.0 / 9999.0);
    if (v14 >= 0x28) {
        v24 = MakeRect(0x78, 0x49, v14, 6);
        n10 = MakeRect(0xb6, 0x12, v14, 6);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    } else if (v14 > 0) {
        v24 = MakeRect(0x78, *(int*)(*(char**)((char*)this + 0x10) + 0x30f0) % 0x24 / 0x12 * 6 + 0x4f, v14, 8);
        n10 = MakeRect(0xb6, 0x12, v14, 6);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    v24 = MakeRect(0x53, 0x93, 7, 0xd);
    if (*(*(char**)((char*)this + 0x1c) + 0x134e) >= 1) {
        n10 = MakeRect(0x7b, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        n10 = MakeRect(0xbe, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x134e) >= 2) {
        n10 = MakeRect(0x83, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        n10 = MakeRect(0xb6, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x134e) >= 3) {
        n10 = MakeRect(0x8b, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        n10 = MakeRect(0xae, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    v24 = MakeRect(0x4c, 0x93, 7, 0xd);
    if (*(*(char**)((char*)this + 0xc) + 0xac) >= 1) {
        n10 = MakeRect(0x7b, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    if (*(*(char**)((char*)this + 0xc) + 0xac) >= 2) {
        n10 = MakeRect(0x83, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    if (*(*(char**)((char*)this + 0xc) + 0xac) >= 3) {
        n10 = MakeRect(0x8b, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    if (*(*(char**)((char*)this + 0x10) + 0xac) >= 1) {
        n10 = MakeRect(0xbe, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    if (*(*(char**)((char*)this + 0x10) + 0xac) >= 2) {
        n10 = MakeRect(0xb6, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    if (*(*(char**)((char*)this + 0x10) + 0xac) >= 3) {
        n10 = MakeRect(0xae, 0x21, 7, 0xd);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    Unk75db70(0xa9, 9, *(int*)((char*)this + 0x43c), 0, 2, 0);
}

void CScene3::Unk760060()
{
    int v2c;
    RECT l28;
    int l18;
    RECT v14;
    int l4;

    if (*(short*)(*(char**)((char*)this + 0x1c) + 0x1420c) > 0) {
        return;
    }
    l28 = MakeRect(0, 0x28, 0x140, 0x21);
    v14 = MakeRect(0, 0xce, 0x140, 0x21);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    l18 = *(short*)(*(char**)((char*)this + 0xc) + 0x148) * 0x6c / 0xbb8;
    if (*(short*)(*(char**)((char*)this + 0xc) + 0x148) < 0x3e8) {
        l28 = MakeRect(0x6c - l18, 0x73, l18, 4);
        v14 = MakeRect(0x8c - l18, 0xe0, l18, 4);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    } else if (*(short*)(*(char**)((char*)this + 0xc) + 0x148) < 0x7d0) {
        l28 = MakeRect(0, 0x94, 0x18, 0x18);
        v14 = MakeRect(6, 0xd1, 0x18, 0x18);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        l28 = MakeRect(0x6c - l18, 0x77, l18, 4);
        v14 = MakeRect(0x8c - l18, 0xe0, l18, 4);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    } else if (*(short*)(*(char**)((char*)this + 0xc) + 0x148) < 0xbb8) {
        l28 = MakeRect(0x18, 0x94, 0x18, 0x18);
        v14 = MakeRect(6, 0xd1, 0x18, 0x18);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        l28 = MakeRect(0x6c - l18, 0x7b, l18, 4);
        v14 = MakeRect(0x8c - l18, 0xe0, l18, 4);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    } else {
        l28 = MakeRect(0x30, 0x94, 0x18, 0x18);
        v14 = MakeRect(6, 0xd1, 0x18, 0x18);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        l28 = MakeRect(0x6c - l18, *(int*)(*(char**)((char*)this + 0xc) + 0x30f0) % 0x5a / 0x12 * 4 + 0x7f, l18, 4);
        v14 = MakeRect(0x8c - l18, 0xe0, l18, 4);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    l18 = *(short*)(*(char**)((char*)this + 0x10) + 0x148) * 0x6c / 0xbb8;
    if (*(short*)(*(char**)((char*)this + 0x10) + 0x148) < 0x3e8) {
        l28 = MakeRect(0x6c, 0x73, l18, 4);
        v14 = MakeRect(0xb4, 0xe0, l18, 4);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    } else if (*(short*)(*(char**)((char*)this + 0x10) + 0x148) < 0x7d0) {
        l28 = MakeRect(0, 0x94, 0x18, 0x18);
        v14 = MakeRect(0x122, 0xd1, 0x18, 0x18);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        l28 = MakeRect(0x6c, 0x77, l18, 4);
        v14 = MakeRect(0xb4, 0xe0, l18, 4);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    } else if (*(short*)(*(char**)((char*)this + 0x10) + 0x148) < 0xbb8) {
        l28 = MakeRect(0x18, 0x94, 0x18, 0x18);
        v14 = MakeRect(0x122, 0xd1, 0x18, 0x18);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        l28 = MakeRect(0x6c, 0x7b, l18, 4);
        v14 = MakeRect(0xb4, 0xe0, l18, 4);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    } else {
        l28 = MakeRect(0x30, 0x94, 0x18, 0x18);
        v14 = MakeRect(0x122, 0xd1, 0x18, 0x18);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        l28 = MakeRect(0x6c, *(int*)(*(char**)((char*)this + 0x10) + 0x30f0) % 0x5a / 0x12 * 4 + 0x7f, l18, 4);
        v14 = MakeRect(0xb4, 0xe0, l18, 4);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    if (*(*(char**)((char*)this + 0xc) + 0x120) == 0) {
        if (*(double*)(*(char**)((char*)this + 0xc) + 0x118) < 500.0) {
            l18 = (int)(60.0 * *(double*)(*(char**)((char*)this + 0xc) + 0x118) * 2 / 1000.0);
            l28 = MakeRect(0x3c - l18, 0x66, l18, 2);
        } else {
            l28 = MakeRect(0, 0x66, 0x3c, 2);
            v14 = MakeRect(0x4f, 0xe8, 0x3c, 2);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            l18 = (int)((*(double*)(*(char**)((char*)this + 0xc) + 0x118) - 500.0) * 60.0 * 2 / 1000.0);
            l28 = MakeRect(0x3c - l18, 0x64, l18, 2);
        }
    } else {
        l18 = (int)(60.0 * *(double*)(*(char**)((char*)this + 0xc) + 0x118) / 1000.0);
        l28 = MakeRect(0x3c - l18, *(int*)(*(char**)((char*)this + 0xc) + 0x30f0) % 0x5a / 0x12 * 2 + 0x68, l18, 2);
    }
    v14 = MakeRect(0x8b - l18, 0xe8, l18, 2);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    if (*(*(char**)((char*)this + 0x10) + 0x120) == 0) {
        if (*(double*)(*(char**)((char*)this + 0x10) + 0x118) < 500.0) {
            l18 = (int)(60.0 * *(double*)(*(char**)((char*)this + 0x10) + 0x118) * 2 / 1000.0);
            l28 = MakeRect(0x3c, 0x66, l18, 2);
        } else {
            l28 = MakeRect(0x3c, 0x66, 0x3c, 2);
            v14 = MakeRect(0xb5, 0xe8, 0x3c, 2);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
            l18 = (int)((*(double*)(*(char**)((char*)this + 0x10) + 0x118) - 500.0) * 60.0 * 2 / 1000.0);
            l28 = MakeRect(0x3c, 0x64, l18, 2);
        }
    } else {
        l18 = (int)(60.0 * *(double*)(*(char**)((char*)this + 0x10) + 0x118) / 1000.0);
        l28 = MakeRect(0x3c, *(int*)(*(char**)((char*)this + 0x10) + 0x30f0) % 0x5a / 0x12 * 2 + 0x68, l18, 2);
    }
    v14 = MakeRect(0xb5, 0xe8, l18, 2);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v14, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), l28, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x1354) == 0) {
        v2c = 0;
        for (; v2c < 2; v2c++) {
            if (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) > 0 && *(int*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x128) == 0 && *(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x28) < 0.0 && *(WORD*)(*(char**)((char*)this + v2c * 4 + 0xc) + 8) >= 0x32 && *(WORD*)(*(char**)((char*)this + v2c * 4 + 0xc) + 8) < 0x96 && (*(WORD*)(*(char**)(*(char**)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x164) + *(WORD*)(*(char**)((char*)this + v2c * 4 + 0xc) + 8) * 8 + 4) + *(WORD*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0xa) * 0xc8 + 0xaa) & 0x400) == 0) {
                if (*(*(char**)((char*)this + v2c * 4 + 0xc) + 0x50) == 1) {
                    l4 = 0;
                    for (; l4 < 3; l4++) {
                        v14.left = (int)*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x20) + *(int*)((char*)this + 0x45c) + l4;
                        v14.top = *(int*)((char*)this + 0x460) + 0xd2 + (int)*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x28) - (*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x28) < 0.0) + l4;
                        v14.right = *(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) * (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) < 0x64) + v14.left + (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) >= 0x64) * 0x64;
                        v14.bottom = v14.top + 1;
                        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(v14, 0xd3 - (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) > 0x1e) * 3 - (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) > 0x3c) * 7);
                        v14.top += 2;
                        v14.bottom = v14.top + 1;
                        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(v14, 0xc2);
                    }
                } else {
                    l4 = 0;
                    for (; l4 < 3; l4++) {
                        v14.left = (int)*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x20) + *(int*)((char*)this + 0x45c) - (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) * (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) < 0x64) + (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) >= 0x64) * 0x64) - l4;
                        v14.top = *(int*)((char*)this + 0x460) + 0xd2 + (int)*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x28) - (*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x28) < 0.0) + l4;
                        v14.right = *(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) * (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) < 0x64) + v14.left + (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) >= 0x64) * 0x64;
                        v14.bottom = v14.top + 1;
                        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(v14, 0xd3 - (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) > 0x1e) * 3 - (*(short*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x124) > 0x3c) * 7);
                        v14.top += 2;
                        v14.bottom = v14.top + 1;
                        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(v14, 0xc2);
                    }
                }
            }
            if (*(float*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x134) != 0.0f && ((CPlayer*)*(int*)((char*)this + v2c * 4 + 0xc))->Unk410340() != 0) {
                if (*(*(char**)((char*)this + v2c * 4 + 0xc) + 0x50) == 1) {
                    l4 = 0;
                    for (; l4 < 3; l4++) {
                        v14.left = (int)*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x20) + *(int*)((char*)this + 0x45c) + l4;
                        v14.top = *(int*)((char*)this + 0x460) + 0xd2 + (int)*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x28) - (*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x28) < 0.0) + l4;
                        v14.right = (int)(v14.left + *(float*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x134) * 1e+02f / 3.6e+02f);
                        v14.bottom = v14.top + 1;
                        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(v14, 0xdc);
                        v14.top += 2;
                        v14.bottom = v14.top + 1;
                        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(v14, 0xc2);
                    }
                } else {
                    l4 = 0;
                    for (; l4 < 3; l4++) {
                        v14.left = (int)((int)*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x20) + *(int*)((char*)this + 0x45c) - *(float*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x134) * 1e+02f / 3.6e+02f - l4);
                        v14.top = *(int*)((char*)this + 0x460) + 0xd2 + (int)*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x28) - (*(double*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x28) < 0.0) + l4;
                        v14.right = (int)(v14.left + *(float*)(*(char**)((char*)this + v2c * 4 + 0xc) + 0x134) * 1e+02f / 3.6e+02f);
                        v14.bottom = v14.top + 1;
                        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(v14, 0xdc);
                        v14.top += 2;
                        v14.bottom = v14.top + 1;
                        ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(v14, 0xc2);
                    }
                }
            }
        }
    }
}

void CScene3::Unk7623b0(int p1)
{
    RECT v24;
    int v14;
    RECT n10;

    v14 = *(short*)((char*)p1 + 0xf4);
    if (v14 > 0x63) {
        v14 = 0x63;
    }
    if (*((char*)p1 + 0x8c) > 0) {
        v24 = MakeRect(0, 0xac, 0x3d, 0x26);
        n10 = MakeRect(0x102, 0x3f, 0x3d, 0x26);
        if (*(short*)((char*)p1 + 0x104) <= 6) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->BlitEx(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0, 0);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        }
        if (v14 > 9) {
            Unk75db70(0x11e, 0x3b, v14, 1, 0, *(short*)((char*)p1 + 0x104) <= 6);
        } else {
            Unk75db70(0x11e, 0x3b, v14, 1, 0, *(short*)((char*)p1 + 0x104) <= 6);
        }
        Unk75db70(0x11d, 0x52, *(int*)((char*)p1 + 0x100), 2, 0, *(short*)((char*)p1 + 0x104) <= 6);
        Unk75db70(0x113, 0x5c, (int)*(double*)((char*)p1 + 0xf8), 2, 0, *(short*)((char*)p1 + 0x104) <= 6);
        Unk75db70(0x11d, 0x5c, (int)(*(double*)((char*)p1 + 0xf8) * 10.0) % 0xa, 2, 0, *(short*)((char*)p1 + 0x104) <= 6);
        v24 = MakeRect(0x46, 0xe1, 3, 9);
        n10 = MakeRect(0x113, 0x5c, 3, 9);
        if (*(short*)((char*)p1 + 0x104) <= 6) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->BlitEx(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0, 0);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
        }
        return;
    }
    v24 = MakeRect(0, 0xac, 0x3d, 0x26);
    n10 = MakeRect(6, 0x3f, 0x3d, 0x26);
    if (*(short*)((char*)p1 + 0x104) <= 6) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->BlitEx(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0, 0);
    } else {
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
    }
    if (v14 > 9) {
        Unk75db70(0x22, 0x3b, v14, 1, 0, *(short*)((char*)p1 + 0x104) <= 6);
    } else {
        Unk75db70(0x22, 0x3b, v14, 1, 0, *(short*)((char*)p1 + 0x104) <= 6);
    }
    Unk75db70(0x21, 0x52, *(int*)((char*)p1 + 0x100), 2, 0, *(short*)((char*)p1 + 0x104) <= 6);
    Unk75db70(0x17, 0x5c, (int)*(double*)((char*)p1 + 0xf8), 2, 0, *(short*)((char*)p1 + 0x104) <= 6);
    Unk75db70(0x21, 0x5c, (int)(*(double*)((char*)p1 + 0xf8) * 10.0) % 0xa, 2, 0, *(short*)((char*)p1 + 0x104) <= 6);
    v24 = MakeRect(0x46, 0xe1, 3, 9);
    n10 = MakeRect(0x17, 0x5c, 3, 9);
    if (*(short*)((char*)p1 + 0x104) <= 6) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->BlitEx(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0, 0);
        return;
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(n10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xea0), v24, *(*(char**)((char*)this + 0x1c) + 0xf34), 0);
}

void CScene3::Unk762c50()
{
    int v34;
    RECT v30;
    int v20;
    char* v1c;
    int l18;
    RECT v14;
    int l4;

    l18 = 0;
    for (; l18 < 2; l18++) {
        if (*(int*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x60) != 0) {
            v1c = (char*)(*(int*)(*(char**)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x10) + *(WORD*)(*(char**)((char*)this + l18 * 4 + 0xc) + 8) * 8 + 4) + *(WORD*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0xa) * 0xc);
            if (*(short*)(v1c + 6) < *(short*)(v1c + 0xa)) {
                v20 = *(short*)(v1c + 6);
                l4 = 0;
            } else {
                v20 = *(short*)(v1c + 0xa);
                l4 = *(short*)(v1c + 6) - *(short*)(v1c + 0xa);
            }
            v30.left = 0;
            v30.top = 0;
            v30.right = *(short*)(v1c + 8);
            v30.bottom = v20;
            v14.left = (int)*(double*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x20) + *(int*)((char*)this + 0x45c) - *(short*)(v1c + 4) * (*(*(char**)((char*)this + l18 * 4 + 0xc) + 0x50) == 1) - (*(short*)(v1c + 8) - *(short*)(v1c + 4)) * (*(*(char**)((char*)this + l18 * 4 + 0xc) + 0x50) == -1);
            v14.top = 0xd2 - ((int)*(double*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x28) - (*(double*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x28) < 0.0)) + *(int*)((char*)this + 0x460) + l4;
            v14.right = *(short*)(v1c + 8) + v14.left;
            v14.bottom = v20 / 3 + v14.top;
            if (v14.top < 0xf0 && v14.bottom > 0) {
                ((CGraphics*)*(int*)((char*)this + 0x20))->BlitShadow(v14, (IDirectDrawSurface*)*(int*)(*(char**)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x14) + *(WORD*)(v1c + 2) * 4), v30, *(*(char**)((char*)this + l18 * 4 + 0xc) + 0x1a), *(*(char**)((char*)this + l18 * 4 + 0xc) + 0x50) == -1, 0xb0);
            }
        }
        v34 = *(short*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x2cc);
        while (v34 != *(short*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x2ca)) {
            if (*(int*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x3d0 + v34 * 4) != 0 && *(int*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x528 + v34 * 0x98) != 0 && (*(int*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x55c + v34 * 0x98) != 0 || *(short*)(*(char**)((char*)this + 0x1c) + 0x1420e) == 0)) {
                v1c = (char*)(*(int*)(*(char**)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x10) + *(WORD*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x4d0 + v34 * 0x98) * 8 + 4) + *(WORD*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x4d2 + v34 * 0x98) * 0xc);
                if (*(short*)(v1c + 6) < *(short*)(v1c + 0xa)) {
                    v20 = *(short*)(v1c + 6);
                    l4 = 0;
                } else {
                    v20 = *(short*)(v1c + 0xa);
                    l4 = *(short*)(v1c + 6) - *(short*)(v1c + 0xa);
                }
                v30.left = 0;
                v30.top = 0;
                v30.right = *(short*)(v1c + 8);
                v30.bottom = v20;
                if (*(*(char**)((char*)this + l18 * 4 + 0xc) + 0x518 + v34 * 0x98) == -1) {
                    v14.left = (int)*(double*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x4e8 + v34 * 0x98) + *(int*)((char*)this + 0x45c) - (*(short*)(v1c + 8) - *(short*)(v1c + 4));
                    v14.top = *(int*)((char*)this + 0x460) + 0xd2 - (int)*(double*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x4f0 + v34 * 0x98) + l4;
                    v14.right = *(short*)(v1c + 8) + v14.left;
                    v14.bottom = v20 / 3 + v14.top;
                } else {
                    v14.left = (int)*(double*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x4e8 + v34 * 0x98) + *(int*)((char*)this + 0x45c) - *(short*)(v1c + 4);
                    v14.top = *(int*)((char*)this + 0x460) + 0xd2 - (int)*(double*)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x4f0 + v34 * 0x98) + l4;
                    v14.right = *(short*)(v1c + 8) + v14.left;
                    v14.bottom = v20 / 3 + v14.top;
                }
                if (v14.top < 0xf0 && v14.bottom > 0) {
                    ((CGraphics*)*(int*)((char*)this + 0x20))->BlitShadow(v14, (IDirectDrawSurface*)*(int*)(*(char**)(*(char**)((char*)this + l18 * 4 + 0xc) + 0x14) + *(WORD*)(v1c + 2) * 4), v30, *(*(char**)((char*)this + l18 * 4 + 0xc) + 0x1a), *(*(char**)((char*)this + l18 * 4 + 0xc) + 0x518 + v34 * 0x98) == -1, 0xb0);
                }
            }
            v34++;
            if (v34 >= 0x40) {
                v34 = 0;
            }
        }
    }
}

void CScene3::Unk7631f0()
{
    int l10;
    int vc;
    int x8;
    int l4;

    vc = -*(int*)((char*)this + 0x45c);
    x8 = 0xf0 - *(int*)((char*)this + 0x460);
    l4 = 0;
    l10 = 0;
    if (vc > 0x140) {
        l4 = 0x140 - vc;
        vc = 0x140;
    } else if (vc < 0) {
        l4 = -vc;
        vc = 0;
    }
    if (x8 > 0xf0) {
        l10 = 0xf0 - x8;
        x8 = 0xf0;
    } else if (x8 < 0) {
        l10 = -x8;
        x8 = 0;
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(MakeRect(0, (l10 + 0xf0) * (l10 < 0), 0x140, abs(l10)), 0);
    ((CGraphics*)*(int*)((char*)this + 0x20))->FillRect(MakeRect((l4 + 0x140) * (l4 < 0), (l10 >= 0) * l10, abs(l4), 0xf0 - abs(l10)), 0);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Flip();
}
