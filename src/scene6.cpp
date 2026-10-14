// CScene6 (0x759f30-0x75db6f), scene 6: the config menu (system\config_bg, config_ob,
// score), which writes its settings back with WriteConfigByte.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene6::CScene6(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    *(int*)((char*)this + 0x43c) = 0;
    *(int*)((char*)this + 0x444) = 0;
    if (1) {
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x434), "system\\config_bg.dat", 0, 1);
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x438), "system\\config_ob.dat", 0, 0xa1);
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x440), "system\\score.dat", 0, 0xa1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_bg.dat", 0, 1, 0xa1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_ob.dat", 0, 0xa2, 0x20);
    } else {
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x434), "system\\config_bg.bmp", 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x438), "system\\config_ob.bmp", 0xa1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x440), "system\\score.bmp", 0xa1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_bg.bmp", 0, 1, 0xa1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_ob.bmp", 0, 0xa1, 0x20);
    }
    *((char*)this + 0x42e) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x438));
    *((char*)this + 0x741) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x440));
    *((char*)this + 0x448) = 0;
    *((char*)this + 0x449) = 0;
    *((char*)this + 0x44a) = 0;
    *((char*)this + 0x44b) = 0;
    *((char*)this + 0x44c) = 0;
    *((char*)this + 0x44d) = 0;
    *((char*)this + 0x2c) = 1;
    *((char*)this + 0x2d) = 0;
    *(double*)((char*)this + 0x748) = 0.0;
    *(int*)((char*)this + 0x750) = 0;
    *(int*)((char*)this + 0x754) = 0;
    *(int*)((char*)this + 0x758) = 0;
    strcpy((char*)this + 0x470, "nanase");
    strcpy((char*)this + 0x48e, "ayu");
    strcpy((char*)this + 0x4ac, "mai");
    strcpy((char*)this + 0x4ca, "makoto");
    strcpy((char*)this + 0x4e8, "akane");
    strcpy((char*)this + 0x506, "mayu");
    strcpy((char*)this + 0x524, "nagamori");
    strcpy((char*)this + 0x542, "misaki");
    strcpy((char*)this + 0x560, "shiori");
    strcpy((char*)this + 0x57e, "sayuri");
    strcpy((char*)this + 0x59c, "nayuki");
    strcpy((char*)this + 0x5ba, "mio");
    strcpy((char*)this + 0x5d8, "misuzu");
    strcpy((char*)this + 0x5f6, "minagi");
    strcpy((char*)this + 0x614, "kano");
    strcpy((char*)this + 0x632, "mizukab");
    strcpy((char*)this + 0x650, "EXnanase");
    strcpy((char*)this + 0x66e, "kaori");
    strcpy((char*)this + 0x68c, "ikumi");
    strcpy((char*)this + 0x6aa, "mishio");
    strcpy((char*)this + 0x6c8, "nayukiB");
    strcpy((char*)this + 0x6e6, "akiko");
    strcpy((char*)this + 0x704, "kanna");
}

CScene6::~CScene6()
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
}

BYTE CScene6::Update()
{
    int xc;
    int v8;
    int v4;

    Vf2();
    if (*((char*)this + 0x2c) == 1) {
        *((char*)this + 0x448) = 0;
        *((char*)this + 0x449) = 0;
        *((char*)this + 0x44a) = 0;
        *((char*)this + 0x2c) = 0;
        *((char*)this + 0x44d) = 0;
        if (1) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_ob.dat", 0, 0xa1, 0x20);
        } else {
            ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_ob.bmp", 0, 0xa1, 0x20);
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0) {
            ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(6);
        } else {
            ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(7);
        }
        CScene::Unk759e20((PALETTEENTRY*)((char*)this + 0x2e), 1);
    }
    if (*((char*)this + 0x2d) == 1) {
        CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 1, 0, 0x64);
        ((CGame*)*(int*)((char*)this + 0x1c))->StopMusic();
        *((char*)this + 0x2c) = 1;
        *((char*)this + 0x2d) = 0;
        *((char*)this + 0x44d) = 0;
        return 0;
    }
    if (*((char*)this + 0x44d) == 0) {
        ((CGame*)*(int*)((char*)this + 0x1c))->UpdateInput();
        v4 = 0;
        for (; v4 < 2; v4++) {
            if (*(*(char**)((char*)this + 0x1c) + 0xe + v4) != 0 && *(BYTE*)((char*)this + v4 + 0x44b) == 0) {
                *((char*)this + 0x448) += *(*(char**)((char*)this + 0x1c) + 0xe + v4);
                if (*((char*)this + 0x448) > 7) {
                    *((char*)this + 0x448) = 0;
                }
                if (*((char*)this + 0x448) < 0) {
                    *((char*)this + 0x448) = 7;
                }
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                *((char*)this + v4 + 0x44b) = 1;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) == 0 && *(*(char**)((char*)this + 0x1c) + 0xe + v4) == 0) {
                *((char*)this + v4 + 0x44b) = 0;
            }
            switch (*((char*)this + 0x448)) {
            case 0:
                if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0 && *(BYTE*)((char*)this + v4 + 0x44b) == 0) {
                    *(int*)(*(char**)((char*)this + 0x1c) + 0x136c) += *(*(char**)((char*)this + 0x1c) + 0xc + v4);
                    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x136c) > 1) {
                        *(int*)(*(char**)((char*)this + 0x1c) + 0x136c) = 0;
                    }
                    if (*(int*)(*(char**)((char*)this + 0x1c) + 0x136c) < 0) {
                        *(int*)(*(char**)((char*)this + 0x1c) + 0x136c) = 1;
                    }
                    WriteConfigByte(0x22, *(int*)(*(char**)((char*)this + 0x1c) + 0x136c) + 1);
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                    *((char*)this + v4 + 0x44b) = 1;
                }
                break;
            case 1:
                if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0 && *(BYTE*)((char*)this + v4 + 0x44b) == 0) {
                    *(*(char**)((char*)this + 0x1c) + 0x1370) += *(*(char**)((char*)this + 0x1c) + 0xc + v4);
                    if (*(*(char**)((char*)this + 0x1c) + 0x1370) > 3) {
                        *(*(char**)((char*)this + 0x1c) + 0x1370) = 1;
                    }
                    if (*(*(char**)((char*)this + 0x1c) + 0x1370) < 1) {
                        *(*(char**)((char*)this + 0x1c) + 0x1370) = 3;
                    }
                    WriteConfigByte(0x24, *(*(char**)((char*)this + 0x1c) + 0x1370));
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                    *((char*)this + v4 + 0x44b) = 1;
                }
                break;
            case 2:
                if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0 && *(BYTE*)((char*)this + v4 + 0x44b) == 0) {
                    *(*(char**)((char*)this + 0x1c) + 0x1366) += *(*(char**)((char*)this + 0x1c) + 0xc + v4);
                    if (*(*(char**)((char*)this + 0x1c) + 0x1366) > 1) {
                        *(*(char**)((char*)this + 0x1c) + 0x1366) = 0;
                    }
                    if (*(*(char**)((char*)this + 0x1c) + 0x1366) < 0) {
                        *(*(char**)((char*)this + 0x1c) + 0x1366) = 1;
                    }
                    WriteConfigByte(0x23, *(*(char**)((char*)this + 0x1c) + 0x1366) + 1);
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                    *((char*)this + v4 + 0x44b) = 1;
                }
                break;
            case 3:
                if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0 && *(BYTE*)((char*)this + v4 + 0x44b) == 0) {
                    *(*(char**)((char*)this + 0x1c) + 0x1365) += *(*(char**)((char*)this + 0x1c) + 0xc + v4);
                    if (*(*(char**)((char*)this + 0x1c) + 0x1365) > 4) {
                        *(*(char**)((char*)this + 0x1c) + 0x1365) = 1;
                    }
                    if (*(*(char**)((char*)this + 0x1c) + 0x1365) < 1) {
                        *(*(char**)((char*)this + 0x1c) + 0x1365) = 4;
                    }
                    WriteConfigByte(0x21, *(*(char**)((char*)this + 0x1c) + 0x1365));
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                    *((char*)this + v4 + 0x44b) = 1;
                }
                break;
            case 4:
                if (*(*(char**)((char*)this + 0x1c) + 0xc + v4) != 0 && *(BYTE*)((char*)this + v4 + 0x44b) == 0) {
                    *(*(char**)((char*)this + 0x1c) + 0x134f) += *(*(char**)((char*)this + 0x1c) + 0xc + v4);
                    if (*(*(char**)((char*)this + 0x1c) + 0x134f) > 3) {
                        *(*(char**)((char*)this + 0x1c) + 0x134f) = 1;
                    }
                    if (*(*(char**)((char*)this + 0x1c) + 0x134f) < 1) {
                        *(*(char**)((char*)this + 0x1c) + 0x134f) = 3;
                    }
                    WriteConfigByte(0x26, *(*(char**)((char*)this + 0x1c) + 0x134f));
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                    *((char*)this + v4 + 0x44b) = 1;
                }
                break;
            case 5:
                if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) == 1) {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                    Unk75d660();
                }
                break;
            case 6:
                if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) == 1) {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                    Unk75da30(0);
                    if (1) {
                        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\score.dat", 0, 0xa1, 0x20);
                    } else {
                        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\score.bmp", 0, 0xa1, 0x20);
                    }
                    *((char*)this + 0x44d) = 1;
                    Unk75d400();
                    ((CGraphics*)*(int*)((char*)this + 0x20))->SetPalette((PALETTEENTRY*)((char*)this + 0x2e));
                    Unk75da30(1);
                }
                break;
            case 7:
                if (*(*(char**)((char*)this + 0x1c) + 0x10 + v4) == 1) {
                    *((char*)this + 0x2d) = 1;
                }
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x12 + v4) == 1) {
                *((char*)this + 0x2d) = 1;
            }
        }
    } else if (*((char*)this + 0x44d) == 1) {
        ((CGame*)*(int*)((char*)this + 0x1c))->UpdateInput();
        v8 = 0;
        for (; v8 < 2; v8++) {
            if (*(*(char**)((char*)this + 0x1c) + 0xc + v8) != 0 && *(BYTE*)((char*)this + v8 + 0x44b) == 0) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                *((char*)this + 0x449) += *(*(char**)((char*)this + 0x1c) + 0xc + v8);
                if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0) {
                    if (*((char*)this + 0x449) == 0xc) {
                        *((char*)this + 0x449) = 0xf;
                    }
                    if (*((char*)this + 0x449) == 0xe) {
                        *((char*)this + 0x449) = 0xb;
                    }
                }
                if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1) {
                    if (*((char*)this + 0x449) == 0x10) {
                        *((char*)this + 0x449) = 0x14;
                    }
                    if (*((char*)this + 0x449) == 0x13) {
                        *((char*)this + 0x449) = 0xf;
                    }
                    if (*((char*)this + 0x449) == 0x16) {
                        if (*(*(char**)((char*)this + 0x1c) + 0xc + v8) > 0) {
                            *((char*)this + 0x449) = 0;
                        } else {
                            *((char*)this + 0x449) = 0x14;
                        }
                    }
                }
                if (*((char*)this + 0x449) > 0x16) {
                    *((char*)this + 0x449) = 0;
                }
                if (*((char*)this + 0x449) < 0) {
                    *((char*)this + 0x449) = 0x16;
                }
                Unk75d580();
                *((char*)this + v8 + 0x44b) = 1;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0xc + v8) == 0 && *(*(char**)((char*)this + 0x1c) + 0xe + v8) == 0) {
                *((char*)this + v8 + 0x44b) = 0;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x10 + v8) != 0 || *(*(char**)((char*)this + 0x1c) + 0x12 + v8) != 0) {
                if (*(*(char**)((char*)this + 0x1c) + 0x10 + v8) != 0) {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                }
                Unk75da30(0);
                if (1) {
                    ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_ob.dat", 0, 0xa1, 0x20);
                } else {
                    ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_ob.bmp", 0, 0xa1, 0x20);
                }
                ((CGraphics*)*(int*)((char*)this + 0x20))->SetPalette((PALETTEENTRY*)((char*)this + 0x2e));
                *((char*)this + 0x44d) = 0;
                Unk75da30(1);
            }
        }
    } else if (*((char*)this + 0x44d) == 2) {
        ((CGame*)*(int*)((char*)this + 0x1c))->UpdateInput();
        xc = 0;
        for (; xc < 2; xc++) {
            if (*(*(char**)((char*)this + 0x1c) + 0xc + xc) != 0 || *(*(char**)((char*)this + 0x1c) + 0xe + xc) != 0) {
                ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(8);
                *(int*)((char*)this + 0x758) = *(*(char**)((char*)this + 0x1c) + 0xc + xc) + *(*(char**)((char*)this + 0x1c) + 0xe + xc) * 0xa + *(int*)((char*)this + 0x758);
                if (*(int*)((char*)this + 0x758) > 0xae) {
                    *(int*)((char*)this + 0x758) = 0;
                }
                if (*(int*)((char*)this + 0x758) < 0) {
                    *(int*)((char*)this + 0x758) = 0xae;
                }
                Unk75d660();
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x10 + xc) != 0 || *(*(char**)((char*)this + 0x1c) + 0x12 + xc) != 0) {
                if (*(*(char**)((char*)this + 0x1c) + 0x10 + xc) != 0) {
                    ((CGame*)*(int*)((char*)this + 0x1c))->PlaySE(6);
                }
                Unk75d8d0(1);
                if (1) {
                    ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_bg.dat", 0, 1, 0xa0);
                    ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_ob.dat", 0, 0xa1, 0x20);
                } else {
                    ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_bg.bmp", 0, 1, 0xa0);
                    ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), "system\\config_ob.bmp", 0, 0xa1, 0x20);
                }
                *((char*)this + 0x44d) = 0;
                Unk75d970(0);
            }
        }
    }
    Draw();
    return 6;
}

void CScene6::Draw()
{
    RECT v20;
    RECT v10;

    if (*((char*)this + 0x44d) == 0) {
        v10 = MakeRect(0, 0, 0x140, 0xf0);
        v20 = MakeRect(0, 0, 0x140, 0xf0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v20, (IDirectDrawSurface*)*(int*)((char*)this + 0x434), v10, 0xff, 0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, 0 - *(int*)((char*)this + 0x754), 0x140, 0x28), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0, 0x140, 0x28), *((char*)this + 0x42e), 0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0x28, 0x140, 0xc8), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x28, 0x140, 0xc8), *((char*)this + 0x42e), 0);
        switch (*((char*)this + 0x448)) {
        case 0:
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0x5f, 0x70, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x105, 0x70, 0xe), *((char*)this + 0x42e), 0);
            break;
        case 1:
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0x71, 0x70, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x117, 0x70, 0xe), *((char*)this + 0x42e), 0);
            break;
        case 2:
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0x83, 0x70, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x129, 0x70, 0xe), *((char*)this + 0x42e), 0);
            break;
        case 3:
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0x95, 0x70, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x13b, 0x70, 0xe), *((char*)this + 0x42e), 0);
            break;
        case 4:
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0xa7, 0x70, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x14d, 0x70, 0xe), *((char*)this + 0x42e), 0);
            break;
        case 5:
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0xb9, 0x140, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x15f, 0x140, 0xe), *((char*)this + 0x42e), 0);
            break;
        case 6:
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0xcb, 0x140, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x171, 0x140, 0xe), *((char*)this + 0x42e), 0);
            break;
        case 7:
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0xdd, 0x140, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0, 0x183, 0x140, 0xe), *((char*)this + 0x42e), 0);
        }
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0x136c) == 0) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x70, *(int*)((char*)this + 0x754) + 0x5f, 0x50, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x70, 0x105, 0x50, 0xe), *((char*)this + 0x42e), 0);
        } else if (*(int*)(*(char**)((char*)this + 0x1c) + 0x136c) == 1) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xc0, *(int*)((char*)this + 0x754) + 0x5f, 0x50, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0xc0, 0x105, 0x50, 0xe), *((char*)this + 0x42e), 0);
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1370) == 1) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x70, *(int*)((char*)this + 0x754) + 0x71, 0x40, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x70, 0x117, 0x40, 0xe), *((char*)this + 0x42e), 0);
        } else if (*(*(char**)((char*)this + 0x1c) + 0x1370) == 2) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xb0, *(int*)((char*)this + 0x754) + 0x71, 0x40, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0xb0, 0x117, 0x40, 0xe), *((char*)this + 0x42e), 0);
        } else if (*(*(char**)((char*)this + 0x1c) + 0x1370) == 3) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xf0, *(int*)((char*)this + 0x754) + 0x71, 0x40, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0xf0, 0x117, 0x40, 0xe), *((char*)this + 0x42e), 0);
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1366) == 0) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x70, *(int*)((char*)this + 0x754) + 0x83, 0x30, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x70, 0x129, 0x30, 0xe), *((char*)this + 0x42e), 0);
        } else if (*(*(char**)((char*)this + 0x1c) + 0x1366) == 1) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xa0, *(int*)((char*)this + 0x754) + 0x83, 0x30, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0xa0, 0x129, 0x30, 0xe), *((char*)this + 0x42e), 0);
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1365) == 1) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x80, *(int*)((char*)this + 0x754) + 0x95, 0x18, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x80, 0x13b, 0x18, 0xe), *((char*)this + 0x42e), 0);
        } else if (*(*(char**)((char*)this + 0x1c) + 0x1365) == 2) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x98, *(int*)((char*)this + 0x754) + 0x95, 0x18, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x98, 0x13b, 0x18, 0xe), *((char*)this + 0x42e), 0);
        } else if (*(*(char**)((char*)this + 0x1c) + 0x1365) == 3) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xb0, *(int*)((char*)this + 0x754) + 0x95, 0x18, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0xb0, 0x13b, 0x18, 0xe), *((char*)this + 0x42e), 0);
        } else if (*(*(char**)((char*)this + 0x1c) + 0x1365) == 4) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xc8, *(int*)((char*)this + 0x754) + 0x95, 0x18, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0xc8, 0x13b, 0x18, 0xe), *((char*)this + 0x42e), 0);
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x134f) == 1) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x80, *(int*)((char*)this + 0x754) + 0xa7, 0x18, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x80, 0x14d, 0x18, 0xe), *((char*)this + 0x42e), 0);
        } else if (*(*(char**)((char*)this + 0x1c) + 0x134f) == 2) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0x98, *(int*)((char*)this + 0x754) + 0xa7, 0x18, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0x98, 0x14d, 0x18, 0xe), *((char*)this + 0x42e), 0);
        } else if (*(*(char**)((char*)this + 0x1c) + 0x134f) == 3) {
            ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0xb0, *(int*)((char*)this + 0x754) + 0xa7, 0x18, 0xe), (IDirectDrawSurface*)*(int*)((char*)this + 0x438), MakeRect(0xb0, 0x14d, 0x18, 0xe), *((char*)this + 0x42e), 0);
        }
    } else if (*((char*)this + 0x44d) == 1) {
        v10 = MakeRect(0, 0, 0x140, 0xf0);
        v20 = MakeRect(0, 0, 0x140, 0xf0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(v20, (IDirectDrawSurface*)*(int*)((char*)this + 0x434), v10, 0xff, 0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, 0 - *(int*)((char*)this + 0x754), 0x140, 0x28), (IDirectDrawSurface*)*(int*)((char*)this + 0x440), MakeRect(0, 0, 0x140, 0x28), *((char*)this + 0x741), 0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, *(int*)((char*)this + 0x754) + 0x28, 0x140, 0xc8), (IDirectDrawSurface*)*(int*)((char*)this + 0x440), MakeRect(0, 0x28, 0x140, 0xc8), *((char*)this + 0x741), 0);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(*(int*)((char*)this + 0x750) + 0x50, *(int*)((char*)this + 0x754), 0x140, 0xf0), (IDirectDrawSurface*)*(int*)((char*)this + 0x43c), MakeRect(0, 0, 0x140, 0xf0), *((char*)this + 0x740), 0);
        Unk75d260(0xa0, *(int*)((char*)this + 0x754) + 0x8f, *(int*)((char*)this + 0x450));
        Unk75d260(0xa0, *(int*)((char*)this + 0x754) + 0xa1, *(int*)((char*)this + 0x454));
        Unk75d260(0xa0, *(int*)((char*)this + 0x754) + 0xb3, *(int*)((char*)this + 0x458));
        Unk75d260(0xa0, *(int*)((char*)this + 0x754) + 0xc5, *(int*)((char*)this + 0x46c));
        Unk75d260(0xa0, *(int*)((char*)this + 0x754) + 0xd7, *(int*)((char*)this + 0x468));
    } else if (*((char*)this + 0x44d) == 2) {
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, 0, 0x140, 0xf0), (IDirectDrawSurface*)*(int*)((char*)this + 0x444), MakeRect(0, 0, 0x140, 0xf0), 0, 0);
    }
    ((CGraphics*)*(int*)((char*)this + 0x20))->Flip();
}

void CScene6::Unk75d260(int p1, int p2, int p3)
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
        v2c.top = 0xf0;
        v2c.bottom = 0xfe;
        v2c.left = (v1c << 4) + 2;
        v2c.right = (v1c << 4) + 0xe;
        l18.top = p2;
        l18.bottom = p2 + 0xe;
        l18.right = l4 - 2;
        l18.left = l4 - 0xe;
        ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(l18, (IDirectDrawSurface*)*(int*)((char*)this + 0x440), v2c, *((char*)this + 0x741), 0);
        l4 -= 0xa;
        x8 = x8 / 0xa;
    } while (x8 > 0);
}

void CScene6::Vf2()
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

void CScene6::Unk75d400()
{
    char v38[52];

    strcpy(v38, "system\\");
    strcat(v38, (const char*)((char*)this + *((char*)this + 0x449) * 0x1e + 0x470));
    strcat(v38, "\\");
    strcat(v38, (const char*)((char*)this + *((char*)this + 0x449) * 0x1e + 0x470));
    if (1) {
        strcat(v38, ".dat");
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x43c), (const char*)v38, 0, 0xd6);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v38, 0, 0xd6, 0x28);
    } else {
        strcat(v38, ".bmp");
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x43c), (const char*)v38, 0xd6);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v38, 0, 0xd6, 0x28);
    }
    *((char*)this + 0x740) = ((CGraphics*)*(int*)((char*)this + 0x20))->GetColorKey((IDirectDrawSurface*)*(int*)((char*)this + 0x43c));
    ((CharRecord*)((char*)this + 0x450))->Load((const char*)((char*)this + *((char*)this + 0x449) * 0x1e + 0x470));
}

void CScene6::Unk75d580()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0;
    for (; xc <= 0x168; xc += 0xa) {
        Draw();
        *(int*)((char*)this + 0x750) = (int)(160.0 - cos(xc / 57.29579143313326) * 160.0);
        if (xc == 0xb4) {
            Unk75d400();
            ((CGraphics*)*(int*)((char*)this + 0x20))->SetPalette((PALETTEENTRY*)((char*)this + 0x2e));
        }
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
    *(int*)((char*)this + 0x750) = 0;
}

void CScene6::Unk75d660()
{
    int v58;
    char v54[20];
    int l40;
    int x3c;
    char v38[52];

    v58 = timeGetTime();
    x3c = 0;
    l40 = 0xa;
    for (; l40 >= 0; l40--) {
        Draw();
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 0, 0xff, l40 * 0xa);
        while ((DWORD)(timeGetTime() - v58) < (BYTE)(0x10 - x3c)) {
        }
        v58 = timeGetTime();
        x3c = x3c == 0;
    }
    strcpy(v38, "system\\nl\\nl");
    if (*(int*)((char*)this + 0x758) < 0x64) {
        strcat(v38, "0");
    }
    if (*(int*)((char*)this + 0x758) < 0xa) {
        strcat(v38, "0");
    }
    _itoa(*(int*)((char*)this + 0x758), v54, 0xa);
    strcat(v38, (const char*)v54);
    if (*(int*)((char*)this + 0x444) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x444))->Release();
        *(int*)((char*)this + 0x444) = 0;
    }
    if (1) {
        strcat(v38, ".dat");
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x444), (const char*)v38, 0, 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v38, 0, 1, 0xfe);
    } else {
        strcat(v38, ".bmp");
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x444), (const char*)v38, 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v38, 0, 1, 0xfe);
    }
    *((char*)this + 0x44d) = 2;
    l40 = 0;
    for (; l40 <= 0xa; l40++) {
        Draw();
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 0, 0xff, l40 * 0xa);
        while ((DWORD)(timeGetTime() - v58) < (BYTE)(0x10 - x3c)) {
        }
        v58 = timeGetTime();
        x3c = x3c == 0;
    }
}

void CScene6::Unk75d8d0(int p1)
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0x14;
    for (; xc >= 0; xc--) {
        Draw();
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 1, 0xff, xc * 5);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
}

void CScene6::Unk75d970(BYTE p1)
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0;
    for (; xc <= 0x14; xc++) {
        Draw();
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), 1, p1, xc << 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->Darken((PALETTEENTRY*)((char*)this + 0x2e), p1, 0xff, xc * 5);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
}

void CScene6::Unk75da30(BYTE p1)
{
    int l10;
    int vc;
    int x8;
    int l4;

    x8 = timeGetTime();
    l4 = 0;
    if (p1 == 0) {
        vc = 0;
        for (; vc <= 0x5a; vc += 5) {
            Draw();
            *(int*)((char*)this + 0x754) = (short)(int)((1.0 - cos(vc / 57.29579143313326)) * 320.0);
            while ((DWORD)(timeGetTime() - x8) < (BYTE)(0x10 - l4)) {
            }
            x8 = timeGetTime();
            l4 = l4 == 0;
        }
        return;
    }
    l10 = 0x5a;
    for (; l10 >= 0; l10 -= 5) {
        Draw();
        *(int*)((char*)this + 0x754) = (short)(int)((1.0 - cos(l10 / 57.29579143313326)) * 320.0);
        while ((DWORD)(timeGetTime() - x8) < (BYTE)(0x10 - l4)) {
        }
        x8 = timeGetTime();
        l4 = l4 == 0;
    }
}
