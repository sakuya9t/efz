// Stage 10's animated background, CBg10 (0x751a40-0x7520af). Like the other three, CScene2
// makes it when the stage needs one.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CBg10::CBg10(int p1)
    : CAnimBg()
{
    int xc;
    int v8;
    int v4;

    *(int*)((char*)this + 8) = p1;
    *(short*)((char*)this + 4) = 0xa;
    *(short*)((char*)this + 6) = 4;
    v8 = (int)operator new(0x14);
    *(int*)((char*)this + 0xc) = v8;
    xc = (int)operator new(0x70);
    *(int*)((char*)this + 0x10) = xc;
    *(int*)((char*)this + 0x14) = (int)(char*)new EffectAnim[1];
    CAnimBg::Load();
    CAnimBg::Unk751030();
    v4 = 0;
    for (; v4 < 1; v4++) {
        *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70) = v4;
        *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x18) = 0.0;
        *(double*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x20) = -450.0;
        *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) = 0;
        *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 4) = 0;
        *(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x48) = 1;
        *(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x50) = 2;
        *(*(char**)((char*)this + 0x10) + v4 * 0x70 + 0x51) = 1;
    }
}

CBg10::~CBg10()
{
    int v4;

    v4 = 0;
    for (; v4 < 5; v4++) {
        if (*(int*)(*(char**)((char*)this + 0xc) + v4 * 4) != 0) {
            ((IUnknown*)*(int*)(*(char**)((char*)this + 0xc) + v4 * 4))->Release();
            *(int*)(*(char**)((char*)this + 0xc) + v4 * 4) = 0;
        }
    }
    delete (char*)*(int*)((char*)this + 0xc);
    delete (char*)*(int*)((char*)this + 0x10);
    delete (EffectAnim*)*(int*)((char*)this + 0x14);
}

void CBg10::Vf0()
{
    WORD xc;
    WORD v8;
    int v4;

    v4 = 0;
    for (; v4 < 1; v4++) {
        v8 = *(short*)(*(char**)(*(char**)((char*)this + 0x14) + *(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) * 0xc);
        xc = *(BYTE*)(*(char**)((char*)this + 0x14) + *(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70) * 8);
        switch (*(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70)) {
        case 0:
        case 1:
            (*(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 4))++;
            if (*(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 4) >= v8) {
                *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 4) = 0;
                (*(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2))++;
                if (*(WORD*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) >= xc) {
                    *(short*)(*(char**)((char*)this + 0x10) + v4 * 0x70 + 2) = 0;
                }
            }
        }
    }
}

void CBg10::Vf1(int p1, int p2, char p3)
{
    int v30;
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (p3 == 0) {
        return;
    }
    v30 = 0;
    for (; v30 < 1; v30++) {
        x1c = *(EffectFrame*)(char*)(*(int*)(*(char**)((char*)this + 0x14) + *(WORD*)(*(char**)((char*)this + 0x10) + v30 * 0x70) * 8 + 4) + *(WORD*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 2) * 0xc);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x48) == -1) {
            v10.left = (int)*(double*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x18) + p1 - (x1c.width - x1c.x);
            v10.top = p2 + (int)*(double*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x20) + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        } else {
            v10.left = (int)*(double*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x18) + p1 - x1c.x;
            v10.top = p2 + (int)*(double*)(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x20) + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        }
        if (*(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x50) > 0) {
            ((CGraphics*)*(int*)((char*)this + 8))->BlitEx(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0xc) + x1c.surface * 4), v2c, *((char*)this + 0x18), *(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x48) == -1, *(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x50) - 1);
        } else {
            ((CGraphics*)*(int*)((char*)this + 8))->Blit(v10, (IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0xc) + x1c.surface * 4), v2c, *((char*)this + 0x18), *(*(char**)((char*)this + 0x10) + v30 * 0x70 + 0x48) == -1);
        }
    }
}
