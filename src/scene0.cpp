// Last object of the game's code: CScene0 (0x775d60-0x77697d), scene 0, the title screen
// (system\title, title_ob). 0x776820 and 0x7768d0 are never called.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene0::CScene0(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x434), "system\\title.dat", 0, 1);
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x438), "system\\title_ob.dat", 0, 0xc1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\title.dat", 0, 1, 0xc0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\title_ob.dat", 0, 0xc1, 0x30);
    } else {
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x434), "system\\title.bmp", 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x438), "system\\title_ob.bmp", 0xc1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\title.bmp", 0, 1, 0xc0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\title_ob.bmp", 0, 0xc1, 0x30);
    }
    *((char*)this + 0x42e) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x438));
    *((char*)this + 0x43c) = 0;
    *(short*)((char*)this + 0x43e) = 0;
    *((char*)this + 0x442) = 0;
    *((char*)this + 0x440) = 0;
    *((char*)this + 0x441) = 0;
    *((char*)this + 0x2c) = 1;
    *((char*)this + 0x2d) = 0;
    *(int*)((char*)this + 0x448) = 0;
    *(int*)((char*)this + 0x444) = 0;
}

CScene0::~CScene0()
{
    if (*(int*)((char*)this + 0x434) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x434))->Release();
        *(int*)((char*)this + 0x434) = 0;
    }
    if (*(int*)((char*)this + 0x438) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x438))->Release();
        *(int*)((char*)this + 0x438) = 0;
    }
}

BYTE CScene0::Update()
{
    int v4;

    if (*((char*)this + 0x2c) == 1) {
        *((char*)this + 0x442) = 0;
        *((char*)this + 0x2c) = 0;
        ((CGraphics*)*(int*)((char*)this + 0x20))->SetPalette((PALETTEENTRY*)((char*)this + 0x2e));
    } else if (*((char*)this + 0x2c) == 2) {
        CScene::Unk759e20((PALETTEENTRY*)((char*)this + 0x2e), 1);
        *((char*)this + 0x2c) = 0;
    } else if (*((char*)this + 0x2c) == 3) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->SetPalette((PALETTEENTRY*)((char*)this + 0x2e));
        CScene::Unk759e20((PALETTEENTRY*)((char*)this + 0x2e), 1);
        *((char*)this + 0x2c) = 0;
    }
    if (*(DWORD*)((char*)this + 0x444) > 0x708 && 1) {
        *(int*)((char*)this + 0x444) = 0;
        *(*(char**)((char*)this + 0x1c) + 0x1364) = 6;
        CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 1, 0, 0);
        *((char*)this + 0x2c) = 2;
        return 2;
    }
    Vf2();
    ((CGame*)*(int*)((char*)this + 0x1c))->UpdateInput();
    v4 = 0;
    for (; v4 < 2; v4++) {
        if (*(BYTE*)((char*)this + v4 + 0x440) == 0 && *(*(char**)((char*)this + 0x1c) + 0xe + v4) != 0) {
            ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
            *((char*)this + 0x43c) += *(*(char**)((char*)this + 0x1c) + 0xe + v4);
            if (*((char*)this + 0x43c) > 6) {
                *((char*)this + 0x43c) = 0;
            }
            if (*((char*)this + 0x43c) < 0) {
                *((char*)this + 0x43c) = 6;
            }
            *(short*)((char*)this + 0x43e) = 0;
            *((char*)this + v4 + 0x440) = 1;
        }
        if (*(*(char**)((char*)this + 0x1c) + 0xe + v4) == 0) {
            *((char*)this + v4 + 0x440) = 0;
            (*(int*)((char*)this + 0x444))++;
        } else {
            *(int*)((char*)this + 0x444) = 0;
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) == 1) {
            switch (*((char*)this + 0x43c)) {
            case 0:
                *(*(char**)((char*)this + 0x1c) + 0x1343) = v4 == 1;
                *(*(char**)((char*)this + 0x1c) + 0x1344) = v4 == 0;
                *(*(char**)((char*)this + 0x1c) + 0x1342) = v4;
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                *(*(char**)((char*)this + 0x1c) + 0x1364) = 0;
                *(*(char**)((char*)this + 0x1c) + 0x134e) = 2;
                CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 1, 0, 0);
                *((char*)this + 0x2c) = 2;
                return 1;
            case 1:
                *(*(char**)((char*)this + 0x1c) + 0x1343) = v4 == 1;
                *(*(char**)((char*)this + 0x1c) + 0x1344) = v4 == 0;
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                *(*(char**)((char*)this + 0x1c) + 0x1364) = 3;
                *(*(char**)((char*)this + 0x1c) + 0x134e) = *(*(char**)((char*)this + 0x1c) + 0x134f);
                CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 1, 0, 0);
                *((char*)this + 0x2c) = 2;
                return 1;
            case 2:
                *(*(char**)((char*)this + 0x1c) + 0x1343) = 0;
                *(*(char**)((char*)this + 0x1c) + 0x1344) = 0;
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                *(*(char**)((char*)this + 0x1c) + 0x1364) = 4;
                *(*(char**)((char*)this + 0x1c) + 0x134e) = *(*(char**)((char*)this + 0x1c) + 0x134f);
                CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 1, 0, 0);
                *((char*)this + 0x2c) = 2;
                return 1;
            case 3:
                *(*(char**)((char*)this + 0x1c) + 0x1343) = v4 == 1;
                *(*(char**)((char*)this + 0x1c) + 0x1344) = v4 == 0;
                *(*(char**)((char*)this + 0x1c) + 0x1342) = v4;
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                *(*(char**)((char*)this + 0x1c) + 0x1364) = 1;
                *(*(char**)((char*)this + 0x1c) + 0x134e) = 2;
                CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 1, 0, 0);
                *((char*)this + 0x2c) = 2;
                return 1;
            case 4:
                *(*(char**)((char*)this + 0x1c) + 0x1343) = 0;
                *(*(char**)((char*)this + 0x1c) + 0x1344) = 0;
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                *(*(char**)((char*)this + 0x1c) + 0x1364) = 5;
                *(*(char**)((char*)this + 0x1c) + 0x134e) = 2;
                CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 1, 0, 0);
                *((char*)this + 0x2c) = 3;
                return 8;
            case 5:
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 1, 0, 0);
                *((char*)this + 0x2c) = 3;
                return 6;
            case 6:
                PostMessageA((HWND)*(int*)((char*)this + 8), 0x10, 0, 0);
            }
        }
    }
    Draw();
    return 0;
}

void CScene0::Draw()
{
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, 0, 0x140, 0xf0), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(0, 0, 0x140, 0xf0), 0, 0);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xc3, 0x82, 0x78, 0x62), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0, 0x78, 0x62), *((char*)this + 0x42e), 0);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xc3, *((char*)this + 0x43c) * 0xe + 0x82, 0x78, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, *((char*)this + 0x43c) * 0xe + 0x62, 0x78, 0xe), *((char*)this + 0x42e), 0);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Flip();
}

void CScene0::Vf2()
{
    int l10c;
    char v108[256];

    l10c = ((IDirectInputDevice7*)*(int*)(*(char**)((char*)this + 0x24) + 0x1e8))->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        ((IDirectInputDevice7*)*(int*)(*(char**)((char*)this + 0x24) + 0x1e8))->Acquire();
    }
    if ((v108[1] & 0x80) != 0) {
        PostMessageA((HWND)*(int*)((char*)this + 8), 0x10, 0, 0);
    }
}

void CScene0::Unk776820()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    *(int*)((char*)this + 0x448) = 1;
    xc = 0x14;
    for (; xc >= 0; xc--) {
        Draw();
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 1, 0xc1, xc * 3 + 0x28);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
    *(int*)((char*)this + 0x448) = 0;
}

void CScene0::Unk7768d0()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    *(int*)((char*)this + 0x448) = 1;
    xc = 0;
    for (; xc <= 0x14; xc++) {
        Draw();
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 1, 0xc1, xc * 3 + 0x28);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
    *(int*)((char*)this + 0x448) = 0;
}
