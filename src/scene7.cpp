// CScene7 (0x7758b0-0x775d5f), scene 7: the staff roll (system\stfr), one tall image
// scrolled up the screen.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene7::CScene7(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x434), "system\\stfr.dat", 0, 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\stfr.dat", 0, 1, 0xfe);
    } else {
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x434), "system\\stfr.bmp", 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\stfr.bmp", 0, 1, 0xfe);
    }
    *(double*)((char*)this + 0x438) = 0.0;
    *(int*)((char*)this + 0x440) = 0;
}

CScene7::~CScene7()
{
    if (*(int*)((char*)this + 0x434) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x434))->Release();
        *(int*)((char*)this + 0x434) = 0;
    }
}

BYTE CScene7::Update()
{
    if (*(double*)((char*)this + 0x438) == 0.0) {
        ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(5);
        Draw();
        CScene::Unk759e20((PALETTEENTRY*)((char*)this + 0x2e), 0);
        *(double*)((char*)this + 0x438) += 0.5;
        return 7;
    }
    if (*(double*)((char*)this + 0x438) > 2800.0 || *(int*)((char*)this + 0x440) != 0) {
        CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 0, -0x1f4, 0xc8);
        ((CGame*)*(int*)((char*)this + 0x1c))->StopMusic();
        *(double*)((char*)this + 0x438) = 0.0;
        *(int*)((char*)this + 0x440) = 0;
        return 0;
    }
    ((CGame*)*(int*)((char*)this + 0x1c))->UpdateInput();
    if (*(*(char**)((char*)this + 0x1c) + 0x10) != 0 || *(*(char**)((char*)this + 0x1c) + 0x12) != 0 || *(*(char**)((char*)this + 0x1c) + 0x14) != 0 || *(*(char**)((char*)this + 0x1c) + 0x16) != 0) {
        *(int*)((char*)this + 0x440) = 1;
    } else if (*(*(char**)((char*)this + 0x1c) + 0x11) != 0 || *(*(char**)((char*)this + 0x1c) + 0x13) != 0 || *(*(char**)((char*)this + 0x1c) + 0x15) != 0 || *(*(char**)((char*)this + 0x1c) + 0x17) != 0) {
        *(int*)((char*)this + 0x440) = 1;
    }
    *(double*)((char*)this + 0x438) += 0.3;
    Draw();
    return 7;
}

void CScene7::Draw()
{
    if (*(double*)((char*)this + 0x438) > 2280.0) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, 0, 0x140, 0xf0), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(0, 0x8e8, 0x140, 0xf0), 0, 0);
    } else {
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, 0, 0x140, 0xf0), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(0, (int)*(double*)((char*)this + 0x438), 0x140, 0xf0), 0, 0);
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->Flip();
}

void CScene7::Vf2()
{
}
