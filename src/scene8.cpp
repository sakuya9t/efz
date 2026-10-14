// CScene8 (0x76e480-0x7712ef), scene 8: the replay browser (system\replay_bg,
// replay\dataNNN.rep). Two of its functions are never called (0x771170, 0x771230).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene8::CScene8(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x434), "system\\replay_bg.dat", 0, 1);
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x438), "system\\replay.dat", 0, 0xc1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\replay_bg.dat", 0, 1, 0xc0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\replay.dat", 0, 0xc1, 0x3e);
    } else {
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x434), "system\\replay_bg.bmp", 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x438), "system\\replay.bmp", 0xc1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\replay_bg.bmp", 0, 1, 0xc0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\replay.bmp", 0, 0xc1, 0x3e);
    }
    *((char*)this + 0x42e) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x438));
    *(int*)((char*)this + 0x43c) = 0;
    *(int*)((char*)this + 0x440) = 0;
    *((char*)this + 0x2c) = 1;
    *((char*)this + 0x2d) = 0;
    *((char*)this + 0x44e) = 0;
    *((char*)this + 0x44f) = 0;
    *(short*)((char*)this + 0x44a) = 0x12c;
    *(short*)((char*)this + 0x44c) = 0x12c;
    *(short*)((char*)this + 0x446) = 0xb4;
    *(short*)((char*)this + 0x448) = 0xb4;
    *((char*)this + 0x469) = 0;
    *((char*)this + 0x46a) = 0;
    *((char*)this + 0x46b) = 0;
    *((char*)this + 0x46c) = 0;
    *((char*)this + 0x46d) = 0;
    *(double*)((char*)this + 0x748) = 0.0;
    *(double*)((char*)this + 0x750) = 0.0;
    *((char*)this + 0x450) = 1;
    *((char*)this + 0x451) = 7;
    *((char*)this + 0x452) = 9;
    *((char*)this + 0x453) = 0xd;
    *((char*)this + 0x454) = 4;
    *((char*)this + 0x455) = 2;
    *((char*)this + 0x456) = 0;
    *((char*)this + 0x457) = 3;
    *((char*)this + 0x458) = 0xb;
    *((char*)this + 0x459) = 0xa;
    *((char*)this + 0x45a) = 8;
    *((char*)this + 0x45b) = 5;
    *((char*)this + 0x45c) = 0x14;
    *((char*)this + 0x45d) = 0xc;
    *((char*)this + 0x45e) = 0x13;
    *((char*)this + 0x45f) = 0xe;
    *((char*)this + 0x460) = 0x12;
    *((char*)this + 0x462) = 6;
    *((char*)this + 0x463) = 0x15;
    *((char*)this + 0x464) = 0x10;
    *((char*)this + 0x465) = 0x11;
    *((char*)this + 0x467) = 0xf;
    *(RECT*)((char*)this + 0x564) = MakeRect(0, 0x2f, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x574) = MakeRect(0, 0x47, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x584) = MakeRect(0, 0x5f, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x594) = MakeRect(0, 0x77, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x5a4) = MakeRect(0, 0x8f, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x5b4) = MakeRect(0, 0xa7, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x5c4) = MakeRect(0, 0xbf, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x5d4) = MakeRect(0, 0xd7, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x5e4) = MakeRect(0, 0xef, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x5f4) = MakeRect(0, 0x107, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x604) = MakeRect(0, 0x11f, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x614) = MakeRect(0, 0x137, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x624) = MakeRect(0, 0x14f, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x634) = MakeRect(0, 0xef, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x684) = MakeRect(0, 0x1df, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x694) = MakeRect(0, 0x1f7, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x6a4) = MakeRect(0, 0x20f, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x6b4) = MakeRect(0, 0x227, 0x5a, 0x18);
    *(RECT*)((char*)this + 0x6d4) = MakeRect(0, 0x257, 0x5a, 0x18);
}

CScene8::~CScene8()
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

BYTE CScene8::Update()
{
    int v4;

    if (*((char*)this + 0x2c) > 0) {
        ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(6);
        Unk770e30();
    }
    if (*((char*)this + 0x2d) > 0) {
        CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 1, 0, 0);
        if (*((char*)this + 0x2d) == 2) {
            *((char*)this + 0x2c) = 2;
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0;
            *((char*)this + 0x2d) = 0;
            ((CGame*)*(int*)((char*)this + 0x1c))->StopMusic();
            return 1;
        }
        *((char*)this + 0x2c) = 1;
        *(*(char**)((char*)this + 0x1c) + 0xf32) = 0;
        *((char*)this + 0x2d) = 0;
        ((CGame*)*(int*)((char*)this + 0x1c))->StopMusic();
        return 0;
    }
    Vf2();
    ((CGame*)*(int*)((char*)this + 0x1c))->UpdateInput();
    v4 = 0;
    for (; v4 < 2; v4++) {
        switch (*((char*)this + 0x469)) {
        case 0:
            if (*(BYTE*)((char*)this + v4 + 0x44e) == 0 && *(*(char**)((char*)this + 0x1c) + 0xe + v4) != 0) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                *((char*)this + 0x46a) += *(*(char**)((char*)this + 0x1c) + 0xe + v4);
                if (*((char*)this + 0x46a) > 8) {
                    *((char*)this + 0x46a) = 0;
                } else if (*((char*)this + 0x46a) < 0) {
                    *((char*)this + 0x46a) = 8;
                }
            }
            if (*(BYTE*)((char*)this + v4 + 0x44e) == 0 && *(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                *((char*)this + 0x46d) += *(*(char**)((char*)this + 0x1c) + 0xc + v4);
                if (*((char*)this + 0x46d) > 9) {
                    *((char*)this + 0x46d) = 0;
                } else if (*((char*)this + 0x46d) < 0) {
                    *((char*)this + 0x46d) = 9;
                }
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) != 0) {
                if (*((char*)this + 0x46d) == 9) {
                    *((char*)this + 0x2d) = 1;
                } else {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                    *((char*)this + 0x469) = 1;
                }
            }
            if (*((char*)this + 0x469) == 0 && (*(*(char**)((char*)this + 0x1c) + 0x12) != 0 || *(*(char**)((char*)this + 0x1c) + 0x13) != 0)) {
                *((char*)this + 0x2d) = 1;
            }
            break;
        case 1:
            *(double*)((char*)this + 0x748) += 2.0;
            *(double*)((char*)this + 0x750) = *((char*)this + 0x46a) * 16.0 / 90.0 + *(double*)((char*)this + 0x750);
            if (*(double*)((char*)this + 0x748) > 180.0) {
                *(double*)((char*)this + 0x748) = 180.0;
                *((char*)this + 0x469) = 2;
            }
            break;
        case 2:
            if (*(BYTE*)((char*)this + v4 + 0x44e) == 0 && *(*(char**)((char*)this + 0x1c) + 0xe + v4) != 0) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                *((char*)this + 0x46b) += *(*(char**)((char*)this + 0x1c) + 0xe + v4);
                if (*((char*)this + 0x46b) >= 3) {
                    *((char*)this + 0x46b) = 0;
                } else if (*((char*)this + 0x46b) < 0) {
                    *((char*)this + 0x46b) = 2;
                }
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) != 0) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                if (((char(*)[9])((char*)this + 0x46e))[*((char*)this + 0x46d)][*((char*)this + 0x46a)] != 0 && *((char*)this + 0x46b) == 0) {
                    *(*(char**)((char*)this + 0x1c) + 0x14281) = *((char*)this + 0x46a);
                    *(*(char**)((char*)this + 0x1c) + 0x14282) = *((char*)this + 0x46d);
                    *(*(char**)((char*)this + 0x1c) + 0x14283) = 1;
                    CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 0, 0, 0x32);
                    *((char*)this + 0x2c) = 2;
                    return 2;
                }
                if (*((char*)this + 0x46b) == 1) {
                    if (((char(*)[9])((char*)this + 0x46e))[*((char*)this + 0x46d)][*((char*)this + 0x46a)] != 0) {
                        *((char*)this + 0x469) = 4;
                    } else {
                        *(*(char**)((char*)this + 0x1c) + 0x14281) = *((char*)this + 0x46a);
                        *(*(char**)((char*)this + 0x1c) + 0x14282) = *((char*)this + 0x46d);
                        *(*(char**)((char*)this + 0x1c) + 0x14283) = 2;
                        *((char*)this + 0x2d) = 2;
                    }
                } else {
                    *((char*)this + 0x469) = 3;
                }
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x12 + v4) != 0 && *(BYTE*)((char*)this + v4 + 0x44e) == 0) {
                *((char*)this + 0x469) = 3;
                *((char*)this + v4 + 0x44e) = 1;
            }
            break;
        case 3:
            *(double*)((char*)this + 0x748) -= 2.0;
            *(double*)((char*)this + 0x750) = *(double*)((char*)this + 0x750) - *((char*)this + 0x46a) * 16.0 / 90.0;
            if (*(double*)((char*)this + 0x748) < 0.0) {
                *(double*)((char*)this + 0x748) = 0.0;
                *((char*)this + 0x469) = 0;
            }
            break;
        case 4:
            if (*(BYTE*)((char*)this + v4 + 0x44e) == 0 && *(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                *((char*)this + 0x46c) += *(*(char**)((char*)this + 0x1c) + 0xc + v4);
                if (*((char*)this + 0x46c) > 1) {
                    *((char*)this + 0x46c) = 0;
                } else if (*((char*)this + 0x46c) < 0) {
                    *((char*)this + 0x46c) = 1;
                }
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) != 0) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                *((char*)this + 0x469) = 2;
                if (*((char*)this + 0x46c) == 0) {
                    *(*(char**)((char*)this + 0x1c) + 0x14281) = *((char*)this + 0x46a);
                    *(*(char**)((char*)this + 0x1c) + 0x14282) = *((char*)this + 0x46d);
                    *(*(char**)((char*)this + 0x1c) + 0x14283) = 2;
                    *((char*)this + 0x2d) = 2;
                }
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x12 + v4) != 0) {
                *((char*)this + 0x469) = 2;
                *((char*)this + v4 + 0x44e) = 1;
            }
        }
        *((char*)this + v4 + 0x44e) = *(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0 || *(*(char**)((char*)this + 0x1c) + 0xe + v4) != 0 || *(*(char**)((char*)this + 0x1c) + 0x12 + v4) != 0;
    }
    Draw();
    return 8;
}

void CScene8::Draw()
{
    int k2c;
    int v28;
    int x24;
    RECT x20;
    RECT v10;

    v10 = MakeRect(0, 0, 0x140, 0xf0);
    x20 = MakeRect(0, 0, 0x140, 0xf0);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x434), v10, 0, 0);
    v10 = MakeRect(0, 0x19, 0x140, 0x10);
    x20 = MakeRect(0, 4, 0x140, 0x10);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
    if (*((char*)this + 0x46d) == 9) {
        v10 = MakeRect((*((char*)this + 0x46d) << 4) + 0x50, 6, 0x28, 0xf);
        x20 = MakeRect((*((char*)this + 0x46d) << 4) + 0x50, 4, 0x28, 0xf);
    } else {
        v10 = MakeRect((*((char*)this + 0x46d) << 4) + 0x50, 6, 0x10, 0xf);
        x20 = MakeRect((*((char*)this + 0x46d) << 4) + 0x50, 4, 0x10, 0xf);
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
    if (*((char*)this + 0x469) != 4) {
        x24 = 0x13f - (int)(160.0 - cos(*(double*)((char*)this + 0x748) / 57.29579143313326) * 160.0);
        if (*((char*)this + 0x46b) == 0) {
            v10 = MakeRect(0, 0x354, 0x140, 0x10);
        } else {
            v10 = MakeRect(0, 0x2cc, 0x140, 0x10);
        }
        x20 = MakeRect(0, x24 + 0x70, 0x140, 0x10);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        if (*((char*)this + 0x46b) == 1) {
            v10 = MakeRect(0, 0x364, 0x140, 0x10);
        } else {
            v10 = MakeRect(0, 0x2dc, 0x140, 0x10);
        }
        x20 = MakeRect(0, x24 + 0x80, 0x140, 0x10);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        if (*((char*)this + 0x46b) == 2) {
            v10 = MakeRect(0, 0x374, 0x140, 0x10);
        } else {
            v10 = MakeRect(0, 0x2ec, 0x140, 0x10);
        }
        x20 = MakeRect(0, x24 + 0x90, 0x140, 0x10);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
    } else if (*((char*)this + 0x469) == 4) {
        v10 = MakeRect(0, 0x300, 0x140, 0x2c);
        x20 = MakeRect(0, 0x70, 0x140, 0x2c);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
        v10 = MakeRect(0, (*((char*)this + 0x46c) << 4) + 0x334, 0x140, 0x10);
        x20 = MakeRect(0, 0xa0, 0x140, 0x10);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
    }
    v28 = 0;
    for (; v28 < 9; v28++) {
        if (*((char*)this + 0x46a) == v28 && v28 < 9) {
            v10 = MakeRect(0, (v28 << 4) + 0x5c, 0x140, 0x10);
            x20 = MakeRect(0, (v28 << 4) + 0x60 - (int)*(double*)((char*)this + 0x750), 0x140, 0x10);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
            if (*((char*)this + 0x46d) < 9 && *((char*)this + (*((char*)this + 0x46d) * 9 + v28) + 0x46e) > 0) {
                v10 = MakeRect(((char(*)[0x12])((char*)this + 0x4bf))[*((char*)this + 0x46d)][v28 * 2] / 0xa * 0x50 + 0x40, (((char(*)[0x12])((char*)this + 0x4bf))[*((char*)this + 0x46d)][v28 * 2] % 0xa << 4) + 0x18c, 0x50, 0x10);
                x20 = MakeRect(0x5a, (v28 << 4) + 0x60 - (int)*(double*)((char*)this + 0x750), 0x50, 0x10);
                ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
                v10 = MakeRect(((char(*)[0x12])((char*)this + 0x4bf))[*((char*)this + 0x46d)][v28 * 2 + 1] / 0xa * 0x50 + 0x40, (((char(*)[0x12])((char*)this + 0x4bf))[*((char*)this + 0x46d)][v28 * 2 + 1] % 0xa << 4) + 0x18c, 0x50, 0x10);
                x20 = MakeRect(0xcd, (v28 << 4) + 0x60 - (int)*(double*)((char*)this + 0x750), 0x50, 0x10);
                ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
            }
        } else {
            k2c = (int)(160.0 - cos(*(double*)((char*)this + 0x748) / 57.29579143313326) * 160.0);
            v10 = MakeRect(0, (v28 << 4) + 0xfc, 0x140, 0x10);
            x20 = MakeRect(0, (v28 << 4) + 0x60 + k2c, 0x140, 0x10);
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
            if (*((char*)this + 0x46d) < 9 && *((char*)this + (*((char*)this + 0x46d) * 9 + v28) + 0x46e) > 0) {
                v10 = MakeRect(((char(*)[0x12])((char*)this + 0x4bf))[*((char*)this + 0x46d)][v28 * 2] / 0xa * 0x50 + 0x40, (((char(*)[0x12])((char*)this + 0x4bf))[*((char*)this + 0x46d)][v28 * 2] % 0xa << 4) + 0x22c, 0x50, 0x10);
                x20 = MakeRect(0x5a, (v28 << 4) + 0x60 + k2c, 0x50, 0x10);
                ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
                v10 = MakeRect(((char(*)[0x12])((char*)this + 0x4bf))[*((char*)this + 0x46d)][v28 * 2 + 1] / 0xa * 0x50 + 0x40, (((char(*)[0x12])((char*)this + 0x4bf))[*((char*)this + 0x46d)][v28 * 2 + 1] % 0xa << 4) + 0x22c, 0x50, 0x10);
                x20 = MakeRect(0xcd, (v28 << 4) + 0x60 + k2c, 0x50, 0x10);
                ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(x20, (IDirectDrawSurface*)*(int*)((char*)this + 0x438), v10, *((char*)this + 0x42e), 0);
            }
        }
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->Flip();
}

void CScene8::Vf2()
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
}

void CScene8::Unk770e30()
{
    int v38;
    int v34;
    int v30;
    char v2c[32];
    char vc[8];

    *((char*)this + 0x44e) = 0;
    *((char*)this + 0x44f) = 0;
    *(short*)((char*)this + 0x44a) = 0x12c;
    *(short*)((char*)this + 0x44c) = 0x12c;
    *(short*)((char*)this + 0x446) = 0xb4;
    *(short*)((char*)this + 0x448) = 0xb4;
    *((char*)this + 0x469) = 0;
    *((char*)this + 0x46b) = 0;
    *((char*)this + 0x46c) = 0;
    *(double*)((char*)this + 0x748) = 0.0;
    *(double*)((char*)this + 0x750) = 0.0;
    *(*(char**)((char*)this + 0x1c) + 0x1358) = 0;
    *(*(char**)((char*)this + 0x1c) + 0x1378) = 0;
    *(*(char**)((char*)this + 0x1c) + 0x1379) = 0;
    *(int*)(*(char**)((char*)this + 0x1c) + 0x1338) = 0;
    *(int*)(*(char**)((char*)this + 0x1c) + 0x133c) = 0;
    if (1) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\replay.dat", 0, 0xc1, 0x3e);
    } else {
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\replay.bmp", 0, 0xc1, 0x3e);
    }
    v34 = 0;
    for (; v34 < 9; v34++) {
        v38 = 0;
        for (; v38 < 9; v38++) {
            strcpy(v2c, "replay\\data");
            _itoa(v34 + 1, vc, 0xa);
            strcat(v2c, (const char*)vc);
            strcat(v2c, "-");
            _itoa(v38 + 1, vc, 0xa);
            strcat(v2c, (const char*)vc);
            strcat(v2c, ".rep");
            v30 = ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->OpenRead((const char*)v2c);
            if (v30 == 0) {
                *((char*)this + (v34 * 9 + v38) + 0x46e) = 0;
            } else {
                ((char(*)[0x12])((char*)this + 0x4bf))[v34][v38 * 2] = ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read();
                ((char(*)[0x12])((char*)this + 0x4bf))[v34][v38 * 2 + 1] = ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read();
                *((char*)this + (v34 * 9 + v38) + 0x46e) = 1;
            }
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Close();
        }
    }
    if (*((char*)this + 0x2c) == 2) {
        Draw();
        CScene::Unk759e20((PALETTEENTRY*)((char*)this + 0x2e), 1);
    } else {
        if (1) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\replay.dat", 0, 0xc1, 0x3e);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\replay.bmp", 0, 0xc1, 0x3e);
        }
        ((CGraphics*)*(int*)((char*)this + 0x20))->SetPalette((PALETTEENTRY*)((char*)this + 0x2e));
        CScene::Unk759e20((PALETTEENTRY*)((char*)this + 0x2e), 1);
    }
    *((char*)this + 0x2c) = 0;
}

void CScene8::Unk771170()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0x14;
    for (; xc >= 0; xc--) {
        Draw();
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 1, 0xc1, xc << 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 0xc2, 0xff, xc * 5);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
}

void CScene8::Unk771230()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0;
    for (; xc <= 0x14; xc++) {
        Draw();
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 1, 0xc1, xc << 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 0xc2, 0xff, xc * 5);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
}
