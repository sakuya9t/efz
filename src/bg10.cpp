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

    unk8 = p1;
    unk4 = 0xa;
    unk6 = 4;
    v8 = (int)operator new(0x14);
    unkc = (char*)v8;
    xc = (int)operator new(0x70);
    unk10 = (char*)xc;
    unk14 = (char*)new EffectAnim[1];
    CAnimBg::Load();
    CAnimBg::Unk751030();
    v4 = 0;
    for (; v4 < 1; v4++) {
        *(short*)(unk10 + v4 * 0x70) = v4;
        *(double*)(unk10 + v4 * 0x70 + 0x18) = 0.0;
        *(double*)(unk10 + v4 * 0x70 + 0x20) = -450.0;
        *(short*)(unk10 + v4 * 0x70 + 2) = 0;
        *(short*)(unk10 + v4 * 0x70 + 4) = 0;
        *(unk10 + v4 * 0x70 + 0x48) = 1;
        *(unk10 + v4 * 0x70 + 0x50) = 2;
        *(unk10 + v4 * 0x70 + 0x51) = 1;
    }
}

CBg10::~CBg10()
{
    int v4;

    v4 = 0;
    for (; v4 < 5; v4++) {
        if (*(int*)(unkc + v4 * 4) != 0) {
            ((IUnknown*)*(int*)(unkc + v4 * 4))->Release();
            *(int*)(unkc + v4 * 4) = 0;
        }
    }
    delete unkc;
    delete unk10;
    delete (EffectAnim*)unk14;
}

void CBg10::Vf0()
{
    WORD xc;
    WORD v8;
    int v4;

    v4 = 0;
    for (; v4 < 1; v4++) {
        v8 = *(short*)(*(char**)(unk14 + *(WORD*)(unk10 + v4 * 0x70) * 8 + 4) + *(WORD*)(unk10 + v4 * 0x70 + 2) * 0xc);
        xc = *(BYTE*)(unk14 + *(WORD*)(unk10 + v4 * 0x70) * 8);
        switch (*(WORD*)(unk10 + v4 * 0x70)) {
        case 0:
        case 1:
            (*(short*)(unk10 + v4 * 0x70 + 4))++;
            if (*(WORD*)(unk10 + v4 * 0x70 + 4) >= v8) {
                *(short*)(unk10 + v4 * 0x70 + 4) = 0;
                (*(short*)(unk10 + v4 * 0x70 + 2))++;
                if (*(WORD*)(unk10 + v4 * 0x70 + 2) >= xc) {
                    *(short*)(unk10 + v4 * 0x70 + 2) = 0;
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
        x1c = *(EffectFrame*)(char*)(*(int*)(unk14 + *(WORD*)(unk10 + v30 * 0x70) * 8 + 4) + *(WORD*)(unk10 + v30 * 0x70 + 2) * 0xc);
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (*(unk10 + v30 * 0x70 + 0x48) == -1) {
            v10.left = (int)*(double*)(unk10 + v30 * 0x70 + 0x18) + p1 - (x1c.width - x1c.x);
            v10.top = p2 + (int)*(double*)(unk10 + v30 * 0x70 + 0x20) + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        } else {
            v10.left = (int)*(double*)(unk10 + v30 * 0x70 + 0x18) + p1 - x1c.x;
            v10.top = p2 + (int)*(double*)(unk10 + v30 * 0x70 + 0x20) + 0xd2 - x1c.y;
            v10.right = x1c.width + v10.left;
            v10.bottom = x1c.height + v10.top;
        }
        if (*(unk10 + v30 * 0x70 + 0x50) > 0) {
            ((CGraphics*)unk8)->BlitEx(v10, (IDirectDrawSurface*)*(int*)(unkc + x1c.surface * 4), v2c, unk18, *(unk10 + v30 * 0x70 + 0x48) == -1, *(unk10 + v30 * 0x70 + 0x50) - 1);
        } else {
            ((CGraphics*)unk8)->Blit(v10, (IDirectDrawSurface*)*(int*)(unkc + x1c.surface * 4), v2c, unk18, *(unk10 + v30 * 0x70 + 0x48) == -1);
        }
    }
}
