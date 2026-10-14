// Stage 16's animated background, CBg16 (0x752900-0x75325f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CBg16::CBg16(int p1)
    : CAnimBg()
{
    int xc;
    int v8;
    int v4;

    *(int*)((char*)this + 8) = p1;
    *(short*)((char*)this + 4) = 0x10;
    *(short*)((char*)this + 6) = 3;
    v8 = (int)operator new(0x10);
    *(int*)((char*)this + 0xc) = v8;
    xc = (int)operator new(0x1c0);
    *(int*)((char*)this + 0x10) = xc;
    *(int*)((char*)this + 0x14) = (int)(char*)new EffectAnim[4];
    CAnimBg::Load();
    CAnimBg::Unk751030();
    v4 = 0;
    for (; v4 < 4; v4++) {
        *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70) = v4;
        *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) = 0.0;
        *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x20) = -450.0;
        *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) = 0;
        *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 4) = 0;
        *(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x48) = 1;
        *(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x50) = 2;
        *(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x51) = v4 > 1;
    }
}

CBg16::~CBg16()
{
    int v4;

    v4 = 0;
    for (; v4 < 4; v4++) {
        if (*(int*)(*(char**)((char*)this + 0xc) + v4 * 4) != 0) {
            ((IUnknown*)*(int*)(*(char**)((char*)this + 0xc) + v4 * 4))->Release();
            *(int*)(*(char**)((char*)this + 0xc) + v4 * 4) = 0;
        }
    }
    delete (char*)*(int*)((char*)this + 0xc);
    delete (char*)*(int*)((char*)this + 0x10);
    delete (EffectAnim*)*(int*)((char*)this + 0x14);
}

void CBg16::Vf0()
{
    short xc;
    short v8;
    int v4;

    v4 = 0;
    for (; v4 < 4; v4++) {
        v8 = *(short*)(*(char**)(*(char**)((char*)this + 0x14) + *(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) * 0xc);
        xc = *(BYTE*)(*(char**)((char*)this + 0x14) + *(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70) * 8);
        switch (*(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70)) {
        case 0:
            (*(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18))++;
            if (*(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) >= 850.0) {
                *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) -= 850.0;
            }
            break;
        case 1:
            *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) += 1.4;
            if (*(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) >= 806.0) {
                *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) -= 806.0;
            }
            break;
        case 2:
            *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) += 1.8;
            if (*(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) >= 789.0) {
                *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) -= 789.0;
            }
            break;
        case 3:
            *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) += 2.2;
            if (*(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) >= 947.0) {
                *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) = 947.0;
            }
        }
    }
}

void CBg16::Vf1(int p1, int p2, char p3)
{
    int l40;
    RECT v3c;
    EffectFrame v2c;
    RECT v20;
    RECT v10;

    l40 = 0;
    for (; l40 < 4; l40++) {
        if (p3 != *(BYTE*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x51)) {
            continue;
        }
        v2c = *(EffectFrame*)(char*)(*(int*)(*(char**)((char*)this + 0x14) + *(WORD*)(*(char**)((char*)this + 0x10) + l40 * 0x70) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 2) * 0xc);
        v3c = MakeRect(0, 0, v2c.width, v2c.height);
        if (*(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x48) == -1) {
            v20.left = (int)*(double*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x18) + p1 - (v2c.width - v2c.x);
            v20.top = p2 + (int)*(double*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x20) + 0xd2 - v2c.y;
            v20.right = v2c.width + v20.left;
            v20.bottom = v2c.height + v20.top;
            v10.left = (int)*(double*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x18) + p1 - (v2c.width - v2c.x) - v2c.width;
            v10.top = p2 + (int)*(double*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x20) + 0xd2 - v2c.y;
            v10.right = v2c.width + v10.left;
            v10.bottom = v2c.height + v10.top;
        } else {
            v20.left = (int)*(double*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x18) + p1 - v2c.x;
            v20.top = p2 + (int)*(double*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x20) + 0xd2 - v2c.y;
            v20.right = v2c.width + v20.left;
            v20.bottom = v2c.height + v20.top;
            v10.left = (int)*(double*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x18) + p1 - v2c.x - v2c.width;
            v10.top = p2 + (int)*(double*)(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x20) + 0xd2 - v2c.y;
            v10.right = v2c.width + v10.left;
            v10.bottom = v2c.height + v10.top;
        }
        if (*(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x50) > 0) {
            ((CGraphics*)*(int*)((char*)this + 8))->BlitEx(v20, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0xc) + v2c.surface * 4), v3c, *((char*)this + 0x18), *(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x48) == -1, *(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x50) - 1);
            ((CGraphics*)*(int*)((char*)this + 8))->BlitEx(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0xc) + v2c.surface * 4), v3c, *((char*)this + 0x18), *(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x48) == -1, *(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x50) - 1);
        } else {
            ((CGraphics*)*(int*)((char*)this + 8))->Blit(v20, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0xc) + v2c.surface * 4), v3c, *((char*)this + 0x18), *(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x48) == -1);
            ((CGraphics*)*(int*)((char*)this + 8))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0xc) + v2c.surface * 4), v3c, *((char*)this + 0x18), *(*(char**)((char*)this + 0x10) + l40 * 0x70 + 0x48) == -1);
        }
    }
}
