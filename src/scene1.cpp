// CScene1 (0x753260-0x759f2f), scene 1: character and stage select
// (system\chr_sel_bg, chr_sel_ob, system\stage\). The inline methods of CScene follow
// it: its constructor and the two palette fades (0x759c10-0x759f2f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene1::CScene1(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x434), "system\\chr_sel_bg.dat", 0, 1);
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x438), "system\\chr_sel_ob.dat", 0, 1);
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x440), "system\\stage\\all.dat", 0, 0xaf);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\chr_sel_ob.dat", 0, 1, 0xae);
    } else {
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x434), "system\\chr_sel_bg.bmp", 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x438), "system\\chr_sel_ob.bmp", 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x440), "system\\stage\\all.bmp", 0xaf);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\chr_sel_ob.bmp", 0, 1, 0xae);
    }
    *((char*)this + 0x42e) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x438));
    *((char*)this + 0x44e) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x440));
    *(int*)((char*)this + 0x444) = 0;
    *(int*)((char*)this + 0x448) = 0;
    *(int*)((char*)this + 0x43c) = 0;
    *((char*)this + 0x2c) = 1;
    *((char*)this + 0x2d) = 0;
    *((char*)this + 0x49c) = 0;
    *((char*)this + 0x49d) = 0;
    *(double*)((char*)this + 0x450) = 0.0;
    *(int*)((char*)this + 0x478) = 0x3c;
    *(double*)((char*)this + 0x458) = 50.0;
    *(int*)((char*)this + 0x47c) = 0;
    *(double*)((char*)this + 0x460) = 50.0;
    *(int*)((char*)this + 0x480) = 0;
    *(double*)((char*)this + 0x468) = 0.0;
    *(int*)((char*)this + 0x484) = 0;
    *(double*)((char*)this + 0x470) = -240.0;
    *(int*)((char*)this + 0x488) = 0x3c;
    *(int*)((char*)this + 0x48c) = 0;
    *(int*)((char*)this + 0x490) = 0;
    *(short*)((char*)this + 0x498) = 0x12c;
    *(short*)((char*)this + 0x49a) = 0x12c;
    *(short*)((char*)this + 0x494) = 0xb4;
    *(short*)((char*)this + 0x496) = 0xb4;
    *((char*)this + 0x49e) = 5;
    *((char*)this + 0x49f) = 5;
    *((char*)this + 0x53c) = 2;
    *((char*)this + 0x53d) = 9;
    *((char*)this + 0x53e) = 0;
    *((char*)this + 0x53f) = 0;
    *(short*)((char*)this + 0x540) = 0;
    *(short*)((char*)this + 0x542) = 0;
    *((char*)this + 0x538) = 0;
    *((char*)this + 0x53a) = 0;
    *((char*)this + 0x539) = 2;
    *((char*)this + 0x53b) = 0;
    *((char*)this + 0x4b9) = 6;
    *((char*)this + 0x4ba) = 0;
    *((char*)this + 0x4bb) = 4;
    *((char*)this + 0x4bc) = 7;
    *((char*)this + 0x4bd) = 5;
    *((char*)this + 0x4be) = 0xb;
    *((char*)this + 0x4bf) = 1;
    *((char*)this + 0x4c0) = 0xa;
    *((char*)this + 0x4c1) = 3;
    *((char*)this + 0x4c2) = 8;
    *((char*)this + 0x4c3) = 2;
    *((char*)this + 0x4c4) = 9;
    *((char*)this + 0x4c5) = 0x17;
    *((char*)this + 0x4c6) = 0x14;
    *((char*)this + 0x4c7) = 0x15;
    *((char*)this + 0x4c8) = 0xe;
    *((char*)this + 0x4c9) = 0xc;
    *((char*)this + 0x4ca) = 0x12;
    *((char*)this + 0x4cb) = 0x11;
    *((char*)this + 0x4cc) = 0xf;
    *((char*)this + 0x4cd) = 0xd;
    *((char*)this + 0x4ce) = 0x10;
    *((char*)this + 0x4cf) = -1;
    *((char*)this + 0x4d0) = 0x13;
    *(int*)((char*)this + 0x4d4) = -0x28;
    *(int*)((char*)this + 0x4d8) = -0xa;
    *(int*)((char*)this + 0x4dc) = -5;
    *(int*)((char*)this + 0x4e0) = 0;
    *(int*)((char*)this + 0x4e4) = -5;
    *(int*)((char*)this + 0x4e8) = -5;
    *(int*)((char*)this + 0x4ec) = -0x1e;
    *(int*)((char*)this + 0x4f0) = -0x1e;
    *(int*)((char*)this + 0x4f4) = -0x14;
    *(int*)((char*)this + 0x4f8) = -0xa;
    *(int*)((char*)this + 0x4fc) = -0x28;
    *(int*)((char*)this + 0x500) = -5;
    *(int*)((char*)this + 0x504) = -0x32;
    *(int*)((char*)this + 0x508) = 0;
    *(int*)((char*)this + 0x50c) = -0xf;
    *(int*)((char*)this + 0x510) = -0xf;
    *(int*)((char*)this + 0x514) = -0x14;
    *(int*)((char*)this + 0x518) = -0x14;
    *(int*)((char*)this + 0x51c) = -0x2d;
    *(int*)((char*)this + 0x520) = 0xa;
    *(int*)((char*)this + 0x524) = -0x14;
    *(int*)((char*)this + 0x528) = 0;
    *(int*)((char*)this + 0x52c) = 0;
    *(int*)((char*)this + 0x530) = -0x14;
    *((char*)this + 0x4a0) = 5;
    *((char*)this + 0x4a1) = 7;
    *((char*)this + 0x4a2) = 0xb;
    *((char*)this + 0x4a3) = 9;
    *((char*)this + 0x4a4) = 0;
    *((char*)this + 0x4a5) = 4;
    *((char*)this + 0x4a6) = 2;
    *((char*)this + 0x4a7) = 1;
    *((char*)this + 0x4a8) = 0xa;
    *((char*)this + 0x4a9) = 0xc;
    *((char*)this + 0x4aa) = 8;
    *((char*)this + 0x4ab) = 3;
    *((char*)this + 0x4ac) = 0x15;
    *((char*)this + 0x4ad) = 0xd;
    *((char*)this + 0x4ae) = 0x14;
    *((char*)this + 0x4af) = 0xe;
    *((char*)this + 0x4b0) = 0xf;
    *((char*)this + 0x4b1) = 8;
    *((char*)this + 0x4b2) = 6;
    *((char*)this + 0x4b3) = 0x13;
    *((char*)this + 0x4b4) = 0x11;
    *((char*)this + 0x4b5) = 0x12;
    *((char*)this + 0x4b6) = -1;
    *((char*)this + 0x4b7) = 0x10;
    *((char*)this + 0x4b8) = 6;
}

CScene1::~CScene1()
{
    if (*(int*)((char*)this + 0x434) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x434))->Release();
        *(int*)((char*)this + 0x434) = 0;
    }
    if (*(int*)((char*)this + 0x438) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x438))->Release();
        *(int*)((char*)this + 0x438) = 0;
    }
    if (*(int*)((char*)this + 0x440) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x440))->Release();
        *(int*)((char*)this + 0x440) = 0;
    }
    if (*(int*)((char*)this + 0x43c) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x43c))->Release();
        *(int*)((char*)this + 0x43c) = 0;
    }
    if (*(int*)((char*)this + 0x444) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x444))->Release();
        *(int*)((char*)this + 0x444) = 0;
    }
    if (*(int*)((char*)this + 0x448) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x448))->Release();
        *(int*)((char*)this + 0x448) = 0;
    }
}

BYTE CScene1::Update()
{
    char v38[8];
    char v30[40];
    int v4;

    if (*((char*)this + 0x2c) > 0) {
        Unk7598d0();
    }
    if (*((char*)this + 0x2d) > 0) {
        CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 0, 0, 0x64);
        *((char*)this + 0x2c) = 1;
        *(*(char**)((char*)this + 0x1c) + 0xf32) = 0;
        *((char*)this + 0x2d) = 0;
        ((CGame*)*(int*)((char*)this + 0x1c))->StopMusic();
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 5) {
            return 8;
        }
        return 0;
    }
    Vf2();
    ((CGame*)*(int*)((char*)this + 0x1c))->UpdateInput();
    v4 = 0;
    for (; v4 < 2; v4++) {
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 0 && *(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343 + v4) == 1) {
            *(*(char**)((char*)this + 0x1c) + 0xc + v4) = 0;
            *(*(char**)((char*)this + 0x1c) + 0xe + v4) = 0;
            *(*(char**)((char*)this + 0x1c) + 0x10 + v4) = 0;
            *(*(char**)((char*)this + 0x1c) + 0x12 + v4) = 0;
            *(*(char**)((char*)this + 0x1c) + 0x14 + v4) = 0;
            *(*(char**)((char*)this + 0x1c) + 0x16 + v4) = 0;
        }
        if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343 + v4) == 1 && (*(*(char**)((char*)this + 0x1c) + 0x1364) == 1 || *(*(char**)((char*)this + 0x1c) + 0x1364) == 3 || *(*(char**)((char*)this + 0x1c) + 0x1364) == 5)) {
            if (*((char*)this + v4 + 0x49e) < 4 && *((char*)this + (1 - v4) + 0x49e) == 6) {
                *(*(char**)((char*)this + 0x1c) + 0xc + v4) = *(*(char**)((char*)this + 0x1c) + 0xc + (1 - v4));
                *(*(char**)((char*)this + 0x1c) + 0xe + v4) = *(*(char**)((char*)this + 0x1c) + 0xe + (1 - v4));
                *(*(char**)((char*)this + 0x1c) + 0x10 + v4) = *(*(char**)((char*)this + 0x1c) + 0x10 + (1 - v4));
                *(*(char**)((char*)this + 0x1c) + 0x14 + v4) = *(*(char**)((char*)this + 0x1c) + 0x14 + (1 - v4));
                *(*(char**)((char*)this + 0x1c) + 0x16 + v4) = *(*(char**)((char*)this + 0x1c) + 0x16 + (1 - v4));
                *(*(char**)((char*)this + 0x1c) + 0xc + (1 - v4)) = 0;
                *(*(char**)((char*)this + 0x1c) + 0xe + (1 - v4)) = 0;
                *(*(char**)((char*)this + 0x1c) + 0x10 + (1 - v4)) = 0;
                *(*(char**)((char*)this + 0x1c) + 0x14 + (1 - v4)) = 0;
                *(*(char**)((char*)this + 0x1c) + 0x16 + (1 - v4)) = 0;
            }
            *(*(char**)((char*)this + 0x1c) + 0x12 + v4) = *(*(char**)((char*)this + 0x1c) + 0x12 + (1 - v4));
        }
    }
    v4 = 0;
    for (; v4 < 2; v4++) {
        switch (*((char*)this + v4 + 0x49e)) {
        case 0:
            *(int*)(*(char**)((char*)this + 0x1c) + 0x1338 + v4 * 4) = 0;
            *(int*)((char*)this + v4 * 4 + 0x47c) = 2;
            if (*(*(char**)((char*)this + 0x1c) + 0x14 + v4) != 0 && *(short*)((char*)this + v4 * 2 + 0x540) == 0 || *(*(char**)((char*)this + 0x1c) + 0x10 + v4) != 0 && *((char*)this + v4 + 0x538) == 1 && *((char*)this + v4 + 0x53a) == 7) {
                *(short*)((char*)this + v4 * 2 + 0x540) = 0x3c;
            }
            if (*(short*)((char*)this + v4 * 2 + 0x540) > 0) {
                (*(short*)((char*)this + v4 * 2 + 0x540))--;
                *(*(char**)((char*)this + 0x1c) + 0xc + v4) = rand() % 3 - 1;
                *(*(char**)((char*)this + 0x1c) + 0xe + v4) = rand() % 2;
                *(*(char**)((char*)this + 0x1c) + 0x10 + v4) = 0;
                *((char*)this + v4 + 0x49c) = 0;
                if (*(short*)((char*)this + v4 * 2 + 0x540) == 0) {
                    *((char*)this + v4 + 0x53c) = *((char*)this + (*((char*)this + v4 + 0x538) + *((char*)this + v4 + 0x53a) * 3) + 0x4b9);
                    if (*((char*)this + v4 + 0x53c) < 0) {
                        (*(short*)((char*)this + v4 * 2 + 0x540))++;
                    }
                    if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && (*((char*)this + v4 + 0x53c) == 0x13 || *((char*)this + v4 + 0x53c) == 0x14 || *((char*)this + v4 + 0x53c) == 0x15 || *((char*)this + v4 + 0x53c) == 0x17)) {
                        (*(short*)((char*)this + v4 * 2 + 0x540))++;
                    }
                    if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && (*((char*)this + v4 + 0x53c) == 0xc || *((char*)this + v4 + 0x53c) == 0xd || *((char*)this + v4 + 0x53c) == 0xe || *((char*)this + v4 + 0x53c) == 0xf)) {
                        (*(short*)((char*)this + v4 * 2 + 0x540))++;
                    }
                }
                if (*(short*)((char*)this + v4 * 2 + 0x540) == 0) {
                    *(*(char**)((char*)this + 0x1c) + 0xc + v4) = 0;
                    *(*(char**)((char*)this + 0x1c) + 0xe + v4) = 0;
                    *(*(char**)((char*)this + 0x1c) + 0x10 + v4) = 1;
                }
            }
            if (*(BYTE*)((char*)this + v4 + 0x49c) == 0) {
                if (*(*(char**)((char*)this + 0x1c) + 0xe + v4) < 0) {
                    *((char*)this + v4 + 0x53a) = (*((char*)this + v4 + 0x53a) + 7) % 8;
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                    *((char*)this + v4 + 0x49c) = 1;
                } else if (*(*(char**)((char*)this + 0x1c) + 0xe + v4) > 0) {
                    *((char*)this + v4 + 0x53a) = (*((char*)this + v4 + 0x53a) + 1) % 8;
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                    *(short*)((char*)this + v4 * 2 + 0x494) = 0x28;
                    *((char*)this + v4 + 0x49c) = 1;
                } else if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) < 0) {
                    *((char*)this + v4 + 0x538) = (*((char*)this + v4 + 0x538) + 2) % 3;
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                    *(short*)((char*)this + v4 * 2 + 0x494) = 0x28;
                    *((char*)this + v4 + 0x49c) = 1;
                } else if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) > 0) {
                    *((char*)this + v4 + 0x538) = (*((char*)this + v4 + 0x538) + 1) % 3;
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                    *(short*)((char*)this + v4 * 2 + 0x494) = 0x28;
                    *((char*)this + v4 + 0x49c) = 1;
                }
                *((char*)this + v4 + 0x53c) = *((char*)this + (*((char*)this + v4 + 0x538) + *((char*)this + v4 + 0x53a) * 3) + 0x4b9);
            } else if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) == 0 && *(*(char**)((char*)this + 0x1c) + 0xe + v4) == 0) {
                *((char*)this + v4 + 0x49c) = 0;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && (*((char*)this + v4 + 0x53c) == 0x13 || *((char*)this + v4 + 0x53c) == 0x14 || *((char*)this + v4 + 0x53c) == 0x15 || *((char*)this + v4 + 0x53c) == 0x17)) {
                *(*(char**)((char*)this + 0x1c) + 0x10 + v4) = 0;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && (*((char*)this + v4 + 0x53c) == 0xc || *((char*)this + v4 + 0x53c) == 0xd || *((char*)this + v4 + 0x53c) == 0xe || *((char*)this + v4 + 0x53c) == 0xf)) {
                *(*(char**)((char*)this + 0x1c) + 0x10 + v4) = 0;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) != 0 && *(*(char**)((char*)this + 0x1c) + 0xe + v4) == 0 && *(*(char**)((char*)this + 0x1c) + 0xc + v4) == 0) {
                if (*((char*)this + (1 - v4) + 0x49e) < 7 && *((char*)this + (1 - v4) + 0x49e) > 0 && *((char*)this + 0x53e) == *((char*)this + 0x53f) && *((char*)this + 0x53c) == *((char*)this + 0x53d)) {
                    (*((char*)this + v4 + 0x53e))++;
                    if (*((char*)this + v4 + 0x53e) >= 6) {
                        *((char*)this + v4 + 0x53e) = 0;
                    }
                }
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                if (v4 == 0) {
                    Unk7586b0(*(int*)((char*)this + 0x14), *(int*)((char*)this + 0x18), 0);
                } else {
                    Unk7586b0(*(int*)((char*)this + 0x18), *(int*)((char*)this + 0x14), 1);
                }
                *((char*)this + v4 + 0x49e) = 1;
                *(short*)((char*)this + v4 * 2 + 0x494) = 0x5a;
            }
            break;
        case 1:
            *(int*)((char*)this + v4 * 4 + 0x47c) = -2;
            *(short*)((char*)this + v4 * 2 + 0x498) = (int)((cos(*(short*)((char*)this + v4 * 2 + 0x494) / 57.29579143313326) + 1.0) * 300.0);
            *(short*)((char*)this + v4 * 2 + 0x494) = *(short*)((char*)this + v4 * 2 + 0x494) + 5;
            if (*(short*)((char*)this + v4 * 2 + 0x494) > 0xb4) {
                *((char*)this + v4 + 0x49e) = 3;
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(*((char*)this + v4 + 0x53c) + 0x28);
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x12 + v4) != 0) {
                *((char*)this + v4 + 0x49e) = 2;
                *(short*)((char*)this + v4 * 2 + 0x540) = 0;
            }
            break;
        case 2:
            if (*(short*)((char*)this + v4 * 2 + 0x494) >= 0x5a) {
                *(short*)((char*)this + v4 * 2 + 0x498) = (int)((cos(*(short*)((char*)this + v4 * 2 + 0x494) / 57.29579143313326) + 1.0) * 300.0);
                *(short*)((char*)this + v4 * 2 + 0x494) = *(short*)((char*)this + v4 * 2 + 0x494) - 5;
            } else {
                *((char*)this + v4 + 0x49e) = 0;
            }
            break;
        case 3:
            *(int*)(*(char**)((char*)this + 0x1c) + 0x1338 + v4 * 4) = *(*(char**)((char*)this + 0x1c) + 0xe + v4) > 0;
            if (*(BYTE*)((char*)this + v4 + 0x49c) == 0 && *(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                *((char*)this + v4 + 0x53e) += *(*(char**)((char*)this + 0x1c) + 0xc + v4);
                if (*((char*)this + v4 + 0x53e) >= 6) {
                    *((char*)this + v4 + 0x53e) = 0;
                } else if (*((char*)this + v4 + 0x53e) < 0) {
                    *((char*)this + v4 + 0x53e) = 5;
                }
                if (*((char*)this + (1 - v4) + 0x49e) > 0 && *((char*)this + 0x53e) == *((char*)this + 0x53f) && *((char*)this + 0x53c) == *((char*)this + 0x53d)) {
                    *((char*)this + v4 + 0x53e) += *(*(char**)((char*)this + 0x1c) + 0xc + v4);
                    if (*((char*)this + v4 + 0x53e) >= 6) {
                        *((char*)this + v4 + 0x53e) = 0;
                    } else if (*((char*)this + v4 + 0x53e) < 0) {
                        *((char*)this + v4 + 0x53e) = 5;
                    }
                }
                Unk7595d0(v4);
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) != 0 || *(*(char**)((char*)this + 0x1c) + 0x16 + v4) != 0) {
                if (*(*(char**)((char*)this + 0x1c) + 0x16 + v4) != 0) {
                    *(int*)(*(char**)((char*)this + 0x1c) + 0x1338 + v4 * 4) = 1;
                }
                *(*(char**)((char*)this + v4 * 4 + 0xc) + 0x8e) = *((char*)this + v4 + 0x53e);
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                *((char*)this + v4 + 0x49e) = 6;
                if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 0 || *(*(char**)((char*)this + 0x1c) + 0x1364) == 2) {
                    CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 0, 0, 0x32);
                    *((char*)this + 0x2c) = 2;
                    *(*(char**)((char*)this + 0x1c) + 0x1358) = 1;
                    *(int*)(*(char**)((char*)this + 0x1c) + 0x135c) = 0;
                    *(int*)(*(char**)((char*)this + 0x1c) + 0x1360) = 0;
                    return 2;
                }
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x12 + v4) != 0) {
                *((char*)this + v4 + 0x49e) = 2;
            }
            break;
        case 4:
            if (*((char*)this + (1 - v4) + 0x49e) == 4) {
                if (*(short*)((char*)this + 0x540) > 0) {
                    (*(short*)((char*)this + 0x540))--;
                    if (*(short*)((char*)this + 0x540) == 0) {
                        if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && *(*(char**)((char*)this + 0x1c) + 0xf32) >= 0xd && *(*(char**)((char*)this + 0x1c) + 0xf32) <= 0x10) {
                            *(short*)((char*)this + 0x540) = rand() % 0x17 + 1;
                        }
                        if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && *(*(char**)((char*)this + 0x1c) + 0xf32) >= 0x12 && *(*(char**)((char*)this + 0x1c) + 0xf32) <= 0x16) {
                            *(short*)((char*)this + 0x540) = rand() % 0x17 + 1;
                        }
                    }
                    if (*(short*)((char*)this + 0x540) == 0) {
                        ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                        Unk759460();
                        CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 0, 0, 0x32);
                        *((char*)this + 0x2c) = 2;
                        *(*(char**)((char*)this + 0x1c) + 0x1358) = 1;
                        *(int*)(*(char**)((char*)this + 0x1c) + 0x135c) = 0;
                        *(int*)(*(char**)((char*)this + 0x1c) + 0x1360) = 0;
                        return 2;
                    }
                    (*(*(char**)((char*)this + 0x1c) + 0xf32))++;
                    if (*(*(char**)((char*)this + 0x1c) + 0xf32) >= 0x17) {
                        *(*(char**)((char*)this + 0x1c) + 0xf32) = 0;
                    }
                } else {
                    if (*(*(char**)((char*)this + 0x1c) + 0xe + v4) > 0 || *(*(char**)((char*)this + 0x1c) + 0xc + v4) > 0) {
                        ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                        *((char*)this + 0x49e) = 0xa;
                        *((char*)this + 0x49f) = 0xa;
                    } else if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) < 0 || *(*(char**)((char*)this + 0x1c) + 0xe + v4) < 0) {
                        ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                        *((char*)this + 0x49e) = 9;
                        *((char*)this + 0x49f) = 9;
                    }
                    if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && *(*(char**)((char*)this + 0x1c) + 0xf32) >= 0xd && *(*(char**)((char*)this + 0x1c) + 0xf32) <= 0x10) {
                        *(*(char**)((char*)this + 0x1c) + 0x10 + v4) = 0;
                    }
                    if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && *(*(char**)((char*)this + 0x1c) + 0xf32) >= 0x12 && *(*(char**)((char*)this + 0x1c) + 0xf32) <= 0x16) {
                        *(*(char**)((char*)this + 0x1c) + 0x10 + v4) = 0;
                    }
                    if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) != 0) {
                        ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                        CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 0, 0, 0x32);
                        *((char*)this + 0x2c) = 2;
                        *(*(char**)((char*)this + 0x1c) + 0x1358) = 1;
                        *(int*)(*(char**)((char*)this + 0x1c) + 0x135c) = 0;
                        *(int*)(*(char**)((char*)this + 0x1c) + 0x1360) = 0;
                        return 2;
                    }
                }
                if (*(*(char**)((char*)this + 0x1c) + 0x14 + v4) != 0 && *(short*)((char*)this + 0x540) == 0 && 1) {
                    *(short*)((char*)this + 0x540) = rand() % 0x17 + 0x3c;
                }
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x12 + v4) != 0) {
                *((char*)this + v4 + 0x49e) = 8;
                *((char*)this + (1 - v4) + 0x49e) = 8;
                *(short*)((char*)this + 0x540) = 0;
                *(short*)((char*)this + 0x542) = 0;
            }
        }
        if (*((char*)this + 0x49e) == 0 && *(*(char**)((char*)this + 0x1c) + 0x12) != 0 && *(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343) == 0 || *((char*)this + 0x49f) == 0 && *(*(char**)((char*)this + 0x1c) + 0x13) != 0 && *(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1344) == 0) {
            *((char*)this + 0x2d) = 1;
        }
        *((char*)this + v4 + 0x49c) = *(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0 || *(*(char**)((char*)this + 0x1c) + 0xe + v4) != 0;
    }
    if (*((char*)this + 0x49e) == 6 && *((char*)this + 0x49f) == 6) {
        if (*(short*)((char*)this + 0x494) >= 0x5a) {
            *(short*)((char*)this + 0x498) = (int)((cos(*(short*)((char*)this + 0x494) / 57.29579143313326) + 1.0) * 300.0);
            *(short*)((char*)this + 0x49a) = (int)((cos(*(short*)((char*)this + 0x496) / 57.29579143313326) + 1.0) * 300.0);
            *(short*)((char*)this + 0x494) = *(short*)((char*)this + 0x494) - 5;
            *(short*)((char*)this + 0x496) = *(short*)((char*)this + 0x496) - 5;
        } else if (*(int*)((char*)this + 0x488) < 0x3c) {
            *(double*)((char*)this + 0x470) = (int)(((cos(*(int*)((char*)this + 0x488) / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            *(int*)((char*)this + 0x488) += 3;
        } else {
            *((char*)this + 0x49e) = 7;
            *((char*)this + 0x49f) = 7;
            if (*(*(char**)((char*)this + 0x1c) + 0xf32) < 0xa) {
                strcpy(v30, "system\\stage\\0");
            } else {
                strcpy(v30, "system\\stage\\");
            }
            _itoa(*(*(char**)((char*)this + 0x1c) + 0xf32), v38, 0xa);
            strcat(v30, (const char*)v38);
            if (1) {
                strcat(v30, ".dat");
                ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x43c), (const char*)v30, 0, 0xbf);
                ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\stage\\all.dat", 0, 0xaf, 0x10);
                ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v30, 0, 0xbf, 0x40);
            } else {
                strcat(v30, ".bmp");
                ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x43c), (const char*)v30, 0xbf);
                ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\stage\\all.bmp", 0, 0xaf, 0x50);
                ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v30, 0, 0xbf, 0x40);
            }
            *((char*)this + 0x44f) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x43c));
            ((CGraphics*)*(int*)((char*)this + 0x20))->SetPaletteRange((PALETTEENTRY*)((char*)this + 0x2e), 0xaf, 0x50);
        }
    } else if (*((char*)this + 0x49e) == 6) {
        if (*(*(char**)((char*)this + 0x1c) + 0x12) != 0) {
            *((char*)this + 0x49e) = 2;
        }
    } else if (*((char*)this + 0x49f) == 6) {
        if (*(*(char**)((char*)this + 0x1c) + 0x13) != 0) {
            *((char*)this + 0x49f) = 2;
        }
    } else if (*((char*)this + 0x49e) == 7) {
        if (*(int*)((char*)this + 0x48c) < 0x55) {
            *(int*)((char*)this + 0x48c) += 5;
        } else {
            *(int*)((char*)this + 0x48c) = 0x5a;
            *((char*)this + 0x49e) = 4;
            *((char*)this + 0x49f) = 4;
        }
    } else if (*((char*)this + 0x49e) == 8 || *((char*)this + 0x49f) == 8) {
        if (*(int*)((char*)this + 0x48c) > 0) {
            *(int*)((char*)this + 0x48c) -= 4;
        } else if (*(int*)((char*)this + 0x488) > 0) {
            *(double*)((char*)this + 0x470) = (int)(((cos(*(int*)((char*)this + 0x488) / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            *(int*)((char*)this + 0x488) -= 3;
        } else {
            *((char*)this + 0x49e) = 0;
            *((char*)this + 0x49f) = 0;
        }
    }
    if (*((char*)this + 0x49e) == 5 || *((char*)this + 0x49f) == 5) {
        if (*(int*)((char*)this + 0x478) > 0) {
            *(double*)((char*)this + 0x450) = (int)(cos(*(int*)((char*)this + 0x478) * 1.5 / 57.29579143313326) * 240.0);
            (*(int*)((char*)this + 0x478))--;
        }
        if (*(int*)((char*)this + 0x488) > 0) {
            *(double*)((char*)this + 0x470) = (int)(((cos(*(int*)((char*)this + 0x488) / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            (*(int*)((char*)this + 0x488))--;
            if (*(int*)((char*)this + 0x488) == 0) {
                *((char*)this + 0x49e) = 0;
                *((char*)this + 0x49f) = 0;
            }
        }
    }
    *(double*)((char*)this + 0x458) = *(double*)((char*)this + 0x458) - *(int*)((char*)this + 0x47c);
    if (*(double*)((char*)this + 0x458) < 0.0) {
        *(double*)((char*)this + 0x458) = 0.0;
    }
    if (*(double*)((char*)this + 0x458) > 50.0) {
        *(double*)((char*)this + 0x458) = 50.0;
    }
    *(double*)((char*)this + 0x460) = *(double*)((char*)this + 0x460) - *(int*)((char*)this + 0x480);
    if (*(double*)((char*)this + 0x460) < 0.0) {
        *(double*)((char*)this + 0x460) = 0.0;
    }
    if (*(double*)((char*)this + 0x460) > 50.0) {
        *(double*)((char*)this + 0x460) = 50.0;
    }
    (*(double*)((char*)this + 0x468))++;
    if (*(double*)((char*)this + 0x468) >= 240.0) {
        *(double*)((char*)this + 0x468) -= 240.0;
    }
    Draw();
    if (*((char*)this + 0x49e) == 9) {
        if (*(int*)((char*)this + 0x490) < 0x5a) {
            *(int*)((char*)this + 0x490) += 0xa;
        } else {
            *(int*)((char*)this + 0x490) = 0;
            *((char*)this + 0x49e) = 4;
            *((char*)this + 0x49f) = 4;
            (*(*(char**)((char*)this + 0x1c) + 0xf32))++;
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && *(*(char**)((char*)this + 0x1c) + 0xf32) == 0xd) {
                *(*(char**)((char*)this + 0x1c) + 0xf32) = 0x11;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && *(*(char**)((char*)this + 0x1c) + 0xf32) == 0x12) {
                *(*(char**)((char*)this + 0x1c) + 0xf32) = 0;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0xf32) >= 0x17) {
                *(*(char**)((char*)this + 0x1c) + 0xf32) = 0;
            }
            Unk759460();
        }
    } else if (*((char*)this + 0x49e) == 0xa) {
        if (*(int*)((char*)this + 0x490) < 0x5a) {
            *(int*)((char*)this + 0x490) += 0xa;
        } else {
            *(int*)((char*)this + 0x490) = 0;
            *((char*)this + 0x49e) = 4;
            *((char*)this + 0x49f) = 4;
            (*(*(char**)((char*)this + 0x1c) + 0xf32))--;
            if (*(*(char**)((char*)this + 0x1c) + 0xf32) < 0) {
                *(*(char**)((char*)this + 0x1c) + 0xf32) = 0x16;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && *(*(char**)((char*)this + 0x1c) + 0xf32) == 0x10) {
                *(*(char**)((char*)this + 0x1c) + 0xf32) = 0xc;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && *(*(char**)((char*)this + 0x1c) + 0xf32) == 0x16) {
                *(*(char**)((char*)this + 0x1c) + 0xf32) = 0x11;
            }
            Unk759460();
        }
    }
    return 1;
}

void CScene1::Draw()
{
    int l40;
    int x3c;
    int v38;
    int v34;
    int v30;
    int v2c;
    int a28;
    int x24;
    RECT x20;
    RECT v10;

    v10 = MakeRect(0, (int)*(double*)((char*)this + 0x450), 0x140, 0xf0);
    x20 = MakeRect(0, 0, 0x140, 0xf0);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x434), v10, 0, 0);
    if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343) != 1 || *(*(char**)((char*)this + 0x1c) + 0x1364) != 0) {
        v10 = MakeRect(0x85, 0x80, 0x16, 0xf0);
        x20 = MakeRect(5 - (int)*(double*)((char*)this + 0x458), (int)*(double*)((char*)this + 0x468), 0x16, 0xf0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        x20 = MakeRect(5 - (int)*(double*)((char*)this + 0x458), (int)*(double*)((char*)this + 0x468) - 0xf0, 0x16, 0xf0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
    }
    if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1344) != 1 || *(*(char**)((char*)this + 0x1c) + 0x1364) != 0) {
        v10 = MakeRect(0xa5, 0x80, 0x16, 0xf0);
        x20 = MakeRect((int)*(double*)((char*)this + 0x460) + 0x124, 0 - (int)*(double*)((char*)this + 0x468), 0x16, 0xf0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        x20 = MakeRect((int)*(double*)((char*)this + 0x460) + 0x124, 0 - (int)*(double*)((char*)this + 0x468) + 0xf0, 0x16, 0xf0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
    }
    if (*((char*)this + 0x49e) > 0) {
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) != 0 && *(*(char**)((char*)this + 0x1c) + 0x1364) != 2 || *(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343) != 1) {
            v10 = MakeRect(0, 0, 0x140, 0xf0);
            x20 = MakeRect(-0x50 - *(short*)((char*)this + 0x498) + *(int*)((char*)this + (*((char*)this + 0x538) + *((char*)this + 0x53a) * 3) * 4 + 0x4d4), 0, 0x140, 0xf0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x444), v10, *((char*)this + 0x44c), 1);
            v10 = MakeRect(0xc0, 9, 0x7a, 0x5f);
            x20 = MakeRect(0 - *(short*)((char*)this + 0x498) / 2, 0x89, 0x7a, 0x5f);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
            v10 = MakeRect(0, (*((char*)this + *((char*)this + 0x53c) + 0x4a0) << 5) + 0x100, 0x7a, 0x20);
            x20 = MakeRect(0 - *(short*)((char*)this + 0x498) / 2, 0xc0, 0x7a, 0x20);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        }
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0x1338) != 0) {
            v10 = MakeRect(0, 0xe0, 0x80, 0x20);
            x20 = MakeRect(-0x10 - *(short*)((char*)this + 0x498) / 2, 5, 0x80, 0x20);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        }
    }
    if (*((char*)this + 0x49f) > 0) {
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) != 0 && *(*(char**)((char*)this + 0x1c) + 0x1364) != 2 || *(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1344) != 1) {
            v10 = MakeRect(0, 0, 0x140, 0xf0);
            x20 = MakeRect(*(short*)((char*)this + 0x49a) + 0x50 - *(int*)((char*)this + (*((char*)this + 0x539) + *((char*)this + 0x53b) * 3) * 4 + 0x4d4), 0, 0x140, 0xf0);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x448), v10, *((char*)this + 0x44d), 0);
            v10 = MakeRect(0xc6, 0x89, 0x7a, 0x5f);
            x20 = MakeRect(*(short*)((char*)this + 0x49a) / 2 + 0xc6, 0x89, 0x7a, 0x5f);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
            v10 = MakeRect(0xc6, (*((char*)this + *((char*)this + 0x53d) + 0x4a0) << 5) + 0x100, 0x7a, 0x20);
            x20 = MakeRect(*(short*)((char*)this + 0x49a) / 2 + 0xc6, 0xc0, 0x7a, 0x20);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        }
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0x133c) != 0) {
            v10 = MakeRect(0, 0xe0, 0x80, 0x20);
            x20 = MakeRect(*(short*)((char*)this + 0x49a) / 2 + 0xcf, 5, 0x80, 0x20);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        }
    }
    v10 = MakeRect(0, 0, 0x80, 0xd9);
    x20 = MakeRect(0x60, (int)*(double*)((char*)this + 0x470), 0x80, 0xd9);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
    v10 = MakeRect(0x8a, 0x60, 0x29, 0x19);
    if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0) {
        x20 = MakeRect(0x67, (int)*(double*)((char*)this + 0x470) + 0x72, 0x29, 0x19);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        x20 = MakeRect(0x8f, (int)*(double*)((char*)this + 0x470) + 0x72, 0x29, 0x19);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        x20 = MakeRect(0xb7, (int)*(double*)((char*)this + 0x470) + 0x72, 0x29, 0x19);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        x20 = MakeRect(0xb1, (int)*(double*)((char*)this + 0x470) + 0xc0, 0x29, 0x19);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
    }
    if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1) {
        x20 = MakeRect(0x61, (int)*(double*)((char*)this + 0x470) + 0x8c, 0x29, 0x19);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        x20 = MakeRect(0x89, (int)*(double*)((char*)this + 0x470) + 0x8c, 0x29, 0x19);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        x20 = MakeRect(0x8f, (int)*(double*)((char*)this + 0x470) + 0xa6, 0x29, 0x19);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        x20 = MakeRect(0xb7, (int)*(double*)((char*)this + 0x470) + 0xa6, 0x29, 0x19);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
    }
    if (*(double*)((char*)this + 0x470) == 0.0) {
        if (*((char*)this + 0x53c) == *((char*)this + 0x53d) && (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343) != 1 || *(*(char**)((char*)this + 0x1c) + 0x1364) != 0) && (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1344) != 1 || *(*(char**)((char*)this + 0x1c) + 0x1364) != 0)) {
            v10 = MakeRect(0x81, 0x40, 0x3f, 0x18);
            x20 = MakeRect(*((char*)this + 0x538) * 0x28 + 0x58 + (*((char*)this + 0x53a) % 2 == 0) * 6, *((char*)this + 0x53a) * 0x1a + 0xa, 0x3f, 0x18);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        } else {
            if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1344) != 1 || *(*(char**)((char*)this + 0x1c) + 0x1364) != 0) {
                v10 = MakeRect(0x81, 0x20, 0x3f, 0x18);
                x20 = MakeRect(*((char*)this + 0x539) * 0x28 + 0x58 + (*((char*)this + 0x53b) % 2 == 0) * 6, *((char*)this + 0x53b) * 0x1a + 0xa, 0x3f, 0x18);
                ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
            }
            if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343) != 1 || *(*(char**)((char*)this + 0x1c) + 0x1364) != 0) {
                v10 = MakeRect(0x81, 0, 0x3f, 0x18);
                x20 = MakeRect(*((char*)this + 0x538) * 0x28 + 0x58 + (*((char*)this + 0x53a) % 2 == 0) * 6, *((char*)this + 0x53a) * 0x1a + 0xa, 0x3f, 0x18);
                ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
            }
        }
    }
    if ((*((char*)this + 0x49e) == 7 || *((char*)this + 0x49e) == 8 || *((char*)this + 0x49e) == 4) && *(*(char**)((char*)this + 0x1c) + 0x1364) != 0 && *(*(char**)((char*)this + 0x1c) + 0x1364) != 2) {
        if (*(short*)((char*)this + 0x540) == 0) {
            x24 = 0;
            a28 = 1;
            for (; a28 <= 7; a28++) {
                while (*(BYTE*)((char*)this + (*(*(char**)((char*)this + 0x1c) + 0xf32) + a28 + x24) % 0x17 + 0x544) != 0) {
                    x24++;
                }
                v10 = MakeRect(0, (*(*(char**)((char*)this + 0x1c) + 0xf32) + a28 + x24) % 0x17 << 5, 0xa0, 0x20);
                x20 = MakeRect(a28 * 0xb + 0xaa, 0xcd - a28 * 0x21 + (int)((double)(a28 * 0x21 + 0xbe) * cos(*(int*)((char*)this + 0x48c) / 57.29579143313326)), 0xa0, 0x20);
                ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x440), v10, *((char*)this + 0x44e), 0);
            }
            v10 = MakeRect(0xa0, *(*(char**)((char*)this + 0x1c) + 0xf32) << 5, 0xa0, 0x20);
            x20 = MakeRect(0xaa, (int)(cos(*(int*)((char*)this + 0x48c) / 57.29579143313326) * 190.0) + 0xcd, 0xa0, 0x20);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x440), v10, *((char*)this + 0x44e), 0);
            v10 = MakeRect(1, 0, 0xc3, 0xde);
            x20 = MakeRect(0 - (int)(cos(*(int*)((char*)this + 0x48c) / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x43c), v10, *((char*)this + 0x44f), 0);
        } else {
            v2c = 0;
            v30 = 0;
            for (; v30 <= 8; v30++) {
                while (*(BYTE*)((char*)this + (*(*(char**)((char*)this + 0x1c) + 0xf32) + v30 + v2c) % 0x17 + 0x544) != 0) {
                    v2c++;
                }
                v10 = MakeRect(0, (*(*(char**)((char*)this + 0x1c) + 0xf32) + v30 + v2c) % 0x17 << 5, 0xa0, 0x20);
                x20 = MakeRect(v30 * 0xb + 0xaa, 0xcd - v30 * 0x21 + (int)((double)(v30 * 0x21 + 0xbe) * cos(*(int*)((char*)this + 0x48c) / 57.29579143313326)), 0xa0, 0x20);
                ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x440), v10, *((char*)this + 0x44e), 0);
            }
            v10 = MakeRect(0, 0x3d9, 0xc3, 0xde);
            x20 = MakeRect(0 - (int)(cos(*(int*)((char*)this + 0x48c) / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        }
    } else if (*((char*)this + 0x49e) == 9) {
        v34 = 0;
        v38 = 0;
        for (; v38 <= 8; v38++) {
            while (*(BYTE*)((char*)this + (*(*(char**)((char*)this + 0x1c) + 0xf32) + v38 + v34) % 0x17 + 0x544) != 0) {
                v34++;
            }
            v10 = MakeRect(0, (*(*(char**)((char*)this + 0x1c) + 0xf32) + v38 + v34) % 0x17 << 5, 0xa0, 0x20);
            x20 = MakeRect(v38 * 0xb + 0xaa - (int)(sin(*(int*)((char*)this + 0x490) / 57.29579143313326) * 11.0), 0xcd - v38 * 0x21 + (int)((double)(v38 * 0x21 + 0xbe) * cos(*(int*)((char*)this + 0x48c) / 57.29579143313326)) + (int)(sin(*(int*)((char*)this + 0x490) / 57.29579143313326) * 33.0), 0xa0, 0x20);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x440), v10, *((char*)this + 0x44e), 0);
        }
        v10 = MakeRect(1, 0, 0xc3, 0xde);
        x20 = MakeRect(0 - (int)(cos(*(int*)((char*)this + 0x48c) / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x43c), v10, *((char*)this + 0x44f), 0);
    } else if (*((char*)this + 0x49e) == 0xa) {
        x3c = 0;
        l40 = 0;
        for (; l40 <= 8; l40++) {
            while (*(BYTE*)((char*)this + (*(*(char**)((char*)this + 0x1c) + 0xf32) + l40 + 0x17 + x3c) % 0x17 + 0x544) != 0) {
                x3c++;
            }
            v10 = MakeRect(0, (*(*(char**)((char*)this + 0x1c) + 0xf32) + l40 + 0x17 + x3c) % 0x17 << 5, 0xa0, 0x20);
            x20 = MakeRect(l40 * 0xb + 0xaa + (int)(sin(*(int*)((char*)this + 0x490) / 57.29579143313326) * 11.0), 0xcd - l40 * 0x21 + (int)((double)(l40 * 0x21 + 0xbe) * cos(*(int*)((char*)this + 0x48c) / 57.29579143313326)) - (int)(sin(*(int*)((char*)this + 0x490) / 57.29579143313326) * 33.0), 0xa0, 0x20);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x440), v10, *((char*)this + 0x44e), 0);
        }
        l40 = -1;
        x3c = 0;
        while (*(BYTE*)((char*)this + (*(*(char**)((char*)this + 0x1c) + 0xf32) + l40 + 0x17 + x3c) % 0x17 + 0x544) != 0) {
            x3c--;
        }
        v10 = MakeRect(0, (*(*(char**)((char*)this + 0x1c) + 0xf32) + l40 + 0x17 + x3c) % 0x17 << 5, 0xa0, 0x20);
        x20 = MakeRect(l40 * 0xb + 0xaa + (int)(sin(*(int*)((char*)this + 0x490) / 57.29579143313326) * 11.0), 0xcd - l40 * 0x21 + (int)((double)(l40 * 0x21 + 0xbe) * cos(*(int*)((char*)this + 0x48c) / 57.29579143313326)) - (int)(sin(*(int*)((char*)this + 0x490) / 57.29579143313326) * 33.0), 0xa0, 0x20);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x440), v10, *((char*)this + 0x44e), 0);
        v10 = MakeRect(1, 0, 0xc3, 0xde);
        x20 = MakeRect(0 - (int)(cos(*(int*)((char*)this + 0x48c) / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x43c), v10, *((char*)this + 0x44f), 0);
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->Flip();
}

void CScene1::Unk7586b0(int p1, int p2, char p3)
{
    char v2c[40];

    switch (*((char*)this + p3 + 0x53c)) {
    case 0:
        *(int*)(char*)p1 = (int)new CNanase(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 1:
        *(int*)(char*)p1 = (int)new CAyu(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 2:
        *(int*)(char*)p1 = (int)new CMai(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 3:
        *(int*)(char*)p1 = (int)new CMakoto(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 4:
        *(int*)(char*)p1 = (int)new CAkane(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 5:
        *(int*)(char*)p1 = (int)new CMayu(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 6:
        *(int*)(char*)p1 = (int)new CNagamori(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 7:
        *(int*)(char*)p1 = (int)new CMisaki(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 8:
        *(int*)(char*)p1 = (int)new CShiori(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 9:
        *(int*)(char*)p1 = (int)new CSayuri(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0xa:
        *(int*)(char*)p1 = (int)new CNayuki(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0xb:
        *(int*)(char*)p1 = (int)new CMio(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0xc:
        *(int*)(char*)p1 = (int)new CEXNanase(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0xd:
        *(int*)(char*)p1 = (int)new CKaori(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0xe:
        *(int*)(char*)p1 = (int)new CIkumi(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0xf:
        *(int*)(char*)p1 = (int)new CMishio(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0x10:
        *(int*)(char*)p1 = (int)new CAkiko(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0x11:
        *(int*)(char*)p1 = (int)new CNayukiB(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0x12:
        *(int*)(char*)p1 = (int)new CMizukaB(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0x13:
        *(int*)(char*)p1 = (int)new CKanna(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0x14:
        *(int*)(char*)p1 = (int)new CKano(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0x15:
        *(int*)(char*)p1 = (int)new CMinagi(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0x16:
        *(int*)(char*)p1 = (int)new CNayuki(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
        break;
    case 0x17:
        *(int*)(char*)p1 = (int)new CMisuzu(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
    }
    *(*(char**)(char*)p1 + 0x8d) = *((char*)this + p3 + 0x53c);
    *(int*)((char*)this + p3 * 4 + 0xc) = *(int*)(char*)p1;
    *(int*)(*(char**)(char*)p1 + 0xa4) = *(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343 + p3);
    if (1) {
        strcpy(v2c, "system\\");
        strcat(v2c, (const char*)(*(int*)(char*)p1 + 0x94));
        strcat(v2c, "\\");
        strcat(v2c, (const char*)(*(int*)(char*)p1 + 0x94));
        strcat(v2c, ".dat");
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + p3 * 4 + 0x444), (const char*)v2c, 0, p3 * 0x28 + 0xaf);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v2c, *((char*)this + p3 + 0x53e) * 0x28, p3 * 0x28 + 0xaf, 0x28);
    } else {
        strcpy(v2c, "system\\");
        strcat(v2c, (const char*)(*(int*)(char*)p1 + 0x94));
        strcat(v2c, "\\");
        strcat(v2c, (const char*)(*(int*)(char*)p1 + 0x94));
        strcat(v2c, ".bmp");
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + p3 * 4 + 0x444), (const char*)v2c, p3 * 0x28 + 0xaf);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v2c, *((char*)this + p3 + 0x53e) * 0x28, p3 * 0x28 + 0xaf, 0x28);
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->SetPalette((PALETTEENTRY*)((char*)this + 0x2e));
    *((char*)this + p3 + 0x44c) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + p3 * 4 + 0x444));
}

void CScene1::Unk759460()
{
    char v34[8];
    char v2c[40];

    if (*(*(char**)((char*)this + 0x1c) + 0xf32) < 0xa) {
        strcpy(v2c, "system\\stage\\0");
    } else {
        strcpy(v2c, "system\\stage\\");
    }
    _itoa(*(*(char**)((char*)this + 0x1c) + 0xf32), v34, 0xa);
    strcat(v2c, (const char*)v34);
    if (1) {
        strcat(v2c, ".dat");
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x43c), (const char*)v2c, 0, 0xbf);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v2c, 0, 0xbf, 0x40);
    } else {
        strcat(v2c, ".bmp");
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x43c), (const char*)v2c, 0xbf);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v2c, 0, 0xbf, 0x40);
    }
    *((char*)this + 0x44f) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x43c));
    ((CGraphics*)*(int*)((char*)this + 0x20))->SetPaletteRange((PALETTEENTRY*)((char*)this + 0x2e), 0xaf, 0x50);
}

void CScene1::Unk7595d0(char p1)
{
    char v2c[40];

    if (1) {
        strcpy(v2c, "system\\");
        strcat(v2c, (const char*)(*(int*)((char*)this + p1 * 4 + 0xc) + 0x94));
        strcat(v2c, "\\");
        strcat(v2c, (const char*)(*(int*)((char*)this + p1 * 4 + 0xc) + 0x94));
        strcat(v2c, ".dat");
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v2c, *((char*)this + p1 + 0x53e) * 0x28, p1 * 0x28 + 0xaf, 0x28);
    } else {
        strcpy(v2c, "system\\");
        strcat(v2c, (const char*)(*(int*)((char*)this + p1 * 4 + 0xc) + 0x94));
        strcat(v2c, "\\");
        strcat(v2c, (const char*)(*(int*)((char*)this + p1 * 4 + 0xc) + 0x94));
        strcat(v2c, ".bmp");
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v2c, *((char*)this + p1 + 0x53e) * 0x28, p1 * 0x28 + 0xaf, 0x28);
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->SetPaletteRange((PALETTEENTRY*)((char*)this + 0x2e), p1 * 0x28 + 0xaf, 0x28);
}

void CScene1::Vf2()
{
    int l10c;
    char v108[256];

    l10c = ((IDirectInputDevice7*)*(int*)(*(char**)((char*)this + 0x24) + 0x1e8))->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        ((IDirectInputDevice7*)*(int*)(*(char**)((char*)this + 0x24) + 0x1e8))->Acquire();
    }
    if ((v108[1] & 0x80) != 0) {
        *((char*)this + 0x2d) = 1;
    }
    if ((v108[59] & 0x80) != 0) {
        ((CInput*)*(int*)((char*)this + 0x24))->LoadBindings();
    }
    if ((v108[60] & 0x80) != 0 && (BYTE)ReadConfigByte(0x98) > 0) {
        ((CInput*)*(int*)((char*)this + 0x24))->LoadPreset(1);
    }
    if ((v108[61] & 0x80) != 0 && (BYTE)ReadConfigByte(0x98) > 0) {
        ((CInput*)*(int*)((char*)this + 0x24))->LoadPreset(2);
    }
    if ((v108[62] & 0x80) != 0 && (BYTE)ReadConfigByte(0x98) > 0) {
        ((CInput*)*(int*)((char*)this + 0x24))->LoadPreset(3);
    }
}

void CScene1::Unk7598d0()
{
    *((char*)this + 0x49c) = 0;
    *((char*)this + 0x49d) = 0;
    *(double*)((char*)this + 0x450) = 0.0;
    *(int*)((char*)this + 0x478) = 0x3c;
    *(double*)((char*)this + 0x458) = 50.0;
    *(int*)((char*)this + 0x47c) = 0;
    *(double*)((char*)this + 0x460) = 50.0;
    *(int*)((char*)this + 0x480) = 0;
    *(double*)((char*)this + 0x468) = 0.0;
    *(int*)((char*)this + 0x484) = 0;
    *(double*)((char*)this + 0x470) = -480.0;
    *(int*)((char*)this + 0x488) = 0x3c;
    *(int*)((char*)this + 0x48c) = 0;
    *(int*)((char*)this + 0x490) = 0;
    *(short*)((char*)this + 0x498) = 0x12c;
    *(short*)((char*)this + 0x49a) = 0x12c;
    *(short*)((char*)this + 0x494) = 0xb4;
    *(short*)((char*)this + 0x496) = 0xb4;
    *((char*)this + 0x49e) = 5;
    *((char*)this + 0x49f) = 5;
    *(short*)((char*)this + 0x540) = 0;
    *(short*)((char*)this + 0x542) = 0;
    *((char*)this + 0x53e) = 0;
    *((char*)this + 0x53f) = 0;
    *(*(char**)((char*)this + 0x1c) + 0x1378) = 0;
    *(*(char**)((char*)this + 0x1c) + 0x1379) = 0;
    *(int*)(*(char**)((char*)this + 0x1c) + 0x1338) = 0;
    *(int*)(*(char**)((char*)this + 0x1c) + 0x133c) = 0;
    if (*(*(char**)((char*)this + 0x1c) + 0x1364) < 5) {
        if (1) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\chr_sel_bg.dat", 0, 1, 0x30);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\chr_sel_bg.bmp", 0, 1, 0x30);
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 0 || *(*(char**)((char*)this + 0x1c) + 0x1364) == 2) {
            if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343) == 1) {
                *((char*)this + 0x49e) = 4;
                *((char*)this + 0x53e) = -1;
            } else {
                *((char*)this + 0x49f) = 4;
                *((char*)this + 0x53f) = -1;
            }
        }
        *(*(char**)((char*)this + 0x1c) + 0x14283) = 0;
    }
    memset((void*)((char*)this + 0x544), 0, 0x17);
    if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0) {
        *((char*)this + 0x551) = 1;
        *((char*)this + 0x552) = 1;
        *((char*)this + 0x553) = 1;
        *((char*)this + 0x554) = 1;
    } else if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1) {
        *((char*)this + 0x556) = 1;
        *((char*)this + 0x557) = 1;
        *((char*)this + 0x558) = 1;
        *((char*)this + 0x559) = 1;
        *((char*)this + 0x55a) = 1;
    }
    if ((*(*(char**)((char*)this + 0x1c) + 0x1364) == 5 || *(*(char**)((char*)this + 0x1c) + 0x1364) == 1) && *(*(char**)((char*)this + 0x1c) + 0x1341) != 0) {
        ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(1);
    } else {
        ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(0);
    }
    Draw();
    CScene::Unk759e20((PALETTEENTRY*)((char*)this + 0x2e), 1);
    *((char*)this + 0x2c) = 0;
}
