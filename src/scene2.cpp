// CScene2 (0x76c6f0-0x76e47f), scene 2: setting up a match. It picks random characters
// and stages where asked, makes the stage's animated background, loads the stage and
// the "now loading" screen (system\nl), and opens the replay file to record or play.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene2::CScene2(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    *(int*)((char*)this + 0x434) = 0;
}

CScene2::~CScene2()
{
    if (*(int*)((char*)this + 0x434) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x434))->Release();
        *(int*)((char*)this + 0x434) = 0;
    }
}

BYTE CScene2::Update()
{
    int v38;
    char v34[8];
    char v2c[40];

    v38 = rand() % 0xaf;
    if (0) {
        v38 = 0x70;
    }
    *(int*)((char*)this + 0xc) = *(int*)*(char**)((char*)this + 0x14);
    *(int*)((char*)this + 0x10) = *(int*)*(char**)((char*)this + 0x18);
    strcpy(v2c, "system\\nl\\nl");
    if (v38 < 0x64) {
        strcat(v2c, "0");
    }
    if (v38 < 0xa) {
        strcat(v2c, "0");
    }
    _itoa(v38, v34, 0xa);
    strcat(v2c, (const char*)v34);
    if (1) {
        strcat(v2c, ".dat");
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)((char*)this + 0x434), (const char*)v2c, 0, 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v2c, 0, 1, 0xfe);
    } else {
        strcat(v2c, ".bmp");
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)((char*)this + 0x434), (const char*)v2c, 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)((char*)this + 0x2e), (const char*)v2c, 0, 1, 0xfe);
    }
    Draw();
    CScene::Unk759e20((PALETTEENTRY*)((char*)this + 0x2e), 0);
    Unk76ca50();
    CScene::Unk759c90((PALETTEENTRY*)((char*)this + 0x2e), 0, -0x1f4, 0xc8);
    if (*(int*)((char*)this + 0x434) != 0) {
        ((IUnknown*)*(int*)((char*)this + 0x434))->Release();
        *(int*)((char*)this + 0x434) = 0;
    }
    ((CGame*)*(int*)((char*)this + 0x1c))->PlayMusic(*(*(char**)((char*)this + 0x1c) + 0xf32) + 0xa);
    return 3;
}

void CScene2::Draw()
{
    ((CGraphics*)*(int*)((char*)this + 0x20))->Blit(MakeRect(0, 0, 0x140, 0xf0), (IDirectDrawSurface*)*(int*)((char*)this + 0x434), MakeRect(0, 0, 0x140, 0xf0), 0, 0);
    ((CGraphics*)*(int*)((char*)this + 0x20))->Flip();
}

void CScene2::Unk76ca50()
{
    char v38[40];
    int l10;
    char vc[8];

    if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 6) {
        l10 = 0x16;
        while (l10 == 0x13 || l10 == 0x16) {
            l10 = rand() % 0x18;
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && (l10 == 0x14 || l10 == 0x15 || l10 == 0x17)) {
                l10 = 0x16;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && (l10 == 0xc || l10 == 0xd || l10 == 0xe || l10 == 0xf)) {
                l10 = 0x16;
            }
        }
        Unk76da20(*(int*)((char*)this + 0x14), *(int*)((char*)this + 0x18), 0, l10);
        l10 = 0x16;
        while (l10 == 0x13 || l10 == 0x16) {
            l10 = rand() % 0x18;
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && (l10 == 0x14 || l10 == 0x15 || l10 == 0x17)) {
                l10 = 0x16;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && (l10 == 0xc || l10 == 0xd || l10 == 0xe || l10 == 0xf)) {
                l10 = 0x16;
            }
        }
        Unk76da20(*(int*)((char*)this + 0x18), *(int*)((char*)this + 0x14), 1, l10);
        *(*(char**)*(char**)((char*)this + 0x14) + 0x8e) = 0;
        *(*(char**)*(char**)((char*)this + 0x18) + 0x8e) = *(*(char**)*(char**)((char*)this + 0x18) + 0x8d) == *(*(char**)*(char**)((char*)this + 0x14) + 0x8d);
        *(int*)(*(char**)*(char**)((char*)this + 0x14) + 0xa4) = 1;
        *(int*)(*(char**)*(char**)((char*)this + 0x18) + 0xa4) = 1;
        l10 = 0x17;
        while (l10 == 0x17) {
            l10 = rand() % 0x17;
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && l10 >= 0xd && l10 <= 0x10) {
                l10 = 0x17;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && l10 >= 0x12 && l10 <= 0x16) {
                l10 = 0x17;
            }
        }
        *(*(char**)((char*)this + 0x1c) + 0xf32) = l10;
        *(int*)(*(char**)((char*)this + 0x1c) + 0x1338) = 0;
        *(int*)(*(char**)((char*)this + 0x1c) + 0x133c) = 0;
    } else if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 5) {
        strcpy(v38, "replay\\data");
        _itoa(*(*(char**)((char*)this + 0x1c) + 0x14282) + 1, vc, 0xa);
        strcat(v38, (const char*)vc);
        strcat(v38, "-");
        _itoa(*(*(char**)((char*)this + 0x1c) + 0x14281) + 1, vc, 0xa);
        strcat(v38, (const char*)vc);
        strcat(v38, ".rep");
        if (*(*(char**)((char*)this + 0x1c) + 0x14283) == 1) {
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->OpenRead((const char*)v38);
            Unk76da20(*(int*)((char*)this + 0x14), *(int*)((char*)this + 0x18), 0, ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read());
            Unk76da20(*(int*)((char*)this + 0x18), *(int*)((char*)this + 0x14), 1, ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read());
            *(*(char**)((char*)this + 0x1c) + 0xf32) = ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read();
            if (*(*(char**)((char*)this + 0x1c) + 0xf32) > 0x64) {
                *(*(char**)((char*)this + 0x1c) + 0x1340) = *(*(char**)((char*)this + 0x1c) + 0xf32);
                *(*(char**)((char*)this + 0x1c) + 0xf32) = ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read();
            } else {
                *(*(char**)((char*)this + 0x1c) + 0x1340) = 0;
            }
            *(*(char**)*(char**)((char*)this + 0x14) + 0x8e) = ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read();
            *(*(char**)*(char**)((char*)this + 0x18) + 0x8e) = ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Read();
        } else if (*(*(char**)((char*)this + 0x1c) + 0x14283) == 2) {
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->OpenWrite((const char*)v38);
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)*(char**)((char*)this + 0x14) + 0x8d));
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)*(char**)((char*)this + 0x18) + 0x8d));
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(0x68);
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)((char*)this + 0x1c) + 0xf32));
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)*(char**)((char*)this + 0x14) + 0x8e));
            ((CReplayFile*)(*(int*)((char*)this + 0x1c) + 0x14284))->Write(*(*(char**)*(char**)((char*)this + 0x18) + 0x8e));
        }
    } else if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 0 && *(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1378) == 0 || *(*(char**)((char*)this + 0x1c) + 0x1364) == 2) {
        l10 = 0x16;
        while ((1 << l10 & *(int*)(*(char**)((char*)this + 0x1c) + 0x135c)) != 0 || l10 == 0x12 || l10 == 0x13 || l10 == 0x16) {
            l10 = rand() % 0x18;
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0 && (l10 == 0x14 || l10 == 0x15 || l10 == 0x17)) {
                l10 = 0x16;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1341) == -1 && (l10 == 0xc || l10 == 0xd || l10 == 0xe || l10 == 0xf)) {
                l10 = 0x16;
            }
        }
        if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 0) {
            if (*(*(char**)((char*)this + 0x1c) + 0x1358) == 8) {
                if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1379) == 0 || *(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1379) == 8) {
                    l10 = 0x13;
                } else {
                    l10 = 0x18;
                }
                if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0) {
                    l10 = 0x18;
                }
            }
        } else if (*(*(char**)((char*)this + 0x1c) + 0x1341) == 0) {
            if (*(*(char**)((char*)this + 0x1c) + 0x1358) == 8) {
                l10 = 0x18;
            }
        } else {
            if (*(*(char**)((char*)this + 0x1c) + 0x1358) == 8) {
                l10 = 0x13;
            }
            if (*(*(char**)((char*)this + 0x1c) + 0x1358) == 7) {
                l10 = 0x18;
            }
        }
        if (*(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343) == 1) {
            Unk76da20(*(int*)((char*)this + 0x14), *(int*)((char*)this + 0x18), 0, l10);
            *(*(char**)*(char**)((char*)this + 0x14) + 0x8e) = 0;
            if (*(*(char**)*(char**)((char*)this + 0x14) + 0x8d) == *(*(char**)*(char**)((char*)this + 0x18) + 0x8d) && *(*(char**)*(char**)((char*)this + 0x18) + 0x8e) == 0) {
                *(*(char**)*(char**)((char*)this + 0x14) + 0x8e) = 1;
            }
        } else {
            Unk76da20(*(int*)((char*)this + 0x18), *(int*)((char*)this + 0x14), 1, l10);
            *(*(char**)*(char**)((char*)this + 0x18) + 0x8e) = 0;
            if (*(*(char**)*(char**)((char*)this + 0x18) + 0x8d) == *(*(char**)*(char**)((char*)this + 0x14) + 0x8d) && *(*(char**)*(char**)((char*)this + 0x14) + 0x8e) == 0) {
                *(*(char**)*(char**)((char*)this + 0x18) + 0x8e) = 1;
            }
        }
        switch (l10) {
        case 0:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 4;
            break;
        case 1:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 7;
            break;
        case 2:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0;
            break;
        case 3:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 6;
            break;
        case 4:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0xa;
            break;
        case 5:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0xb;
            break;
        case 6:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 3;
            break;
        case 7:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 5;
            break;
        case 8:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0x16;
            break;
        case 9:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 2;
            break;
        case 0xa:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 8;
            break;
        case 0xb:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 9;
            break;
        case 0xc:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 4;
            break;
        case 0xd:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 1;
            break;
        case 0xe:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0x13;
            break;
        case 0xf:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0x14;
            break;
        case 0x10:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0x11;
            break;
        case 0x11:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 8;
            break;
        case 0x12:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0xc;
            break;
        case 0x13:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0x10;
            break;
        case 0x14:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0xe;
            break;
        case 0x15:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0xd;
            break;
        case 0x17:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0xf;
            break;
        case 0x18:
            *(*(char**)((char*)this + 0x1c) + 0xf32) = 0xc;
        }
    }
    _itoa(*(*(char**)((char*)this + 0x1c) + 0xf32), vc, 0xa);
    if (*(*(char**)((char*)this + 0x1c) + 0xf32) < 0xa) {
        strcpy(v38, "system\\bg\\bg0");
    } else {
        strcpy(v38, "system\\bg\\bg");
    }
    strcat(v38, (const char*)vc);
    if (1) {
        strcat(v38, ".dat");
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0xe98) != 0) {
            ((IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xe98))->Release();
            *(int*)(*(char**)((char*)this + 0x1c) + 0xe98) = 0;
        }
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)(*(int*)((char*)this + 0x1c) + 0xe98), (const char*)v38, 0, 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteDat((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), (const char*)v38, 0, 1, 0x5e);
        _itoa(*(*(char**)((char*)this + 0x1c) + 0xf32), vc, 0xa);
        if (*(*(char**)((char*)this + 0x1c) + 0xf32) < 0xa) {
            strcpy(v38, "system\\bg\\bg0");
        } else {
            strcpy(v38, "system\\bg\\bg");
        }
        strcat(v38, (const char*)vc);
        strcat(v38, "b.dat");
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0xe9c) != 0) {
            ((IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xe9c))->Release();
            *(int*)(*(char**)((char*)this + 0x1c) + 0xe9c) = 0;
        }
        ((CGame*)*(int*)((char*)this + 0x1c))->LoadDat((IDirectDrawSurface**)(*(int*)((char*)this + 0x1c) + 0xe9c), (const char*)v38, 0, 0xaf);
    } else {
        strcat(v38, ".bmp");
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0xe98) != 0) {
            ((IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xe98))->Release();
            *(int*)(*(char**)((char*)this + 0x1c) + 0xe98) = 0;
        }
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)(*(int*)((char*)this + 0x1c) + 0xe98), (const char*)v38, 1);
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadPaletteBmp((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35), (const char*)v38, 0, 1, 0x5e);
        _itoa(*(*(char**)((char*)this + 0x1c) + 0xf32), vc, 0xa);
        if (*(*(char**)((char*)this + 0x1c) + 0xf32) < 0xa) {
            strcpy(v38, "system\\bg\\bg0");
        } else {
            strcpy(v38, "system\\bg\\bg");
        }
        strcat(v38, (const char*)vc);
        strcat(v38, "b.bmp");
        if (*(int*)(*(char**)((char*)this + 0x1c) + 0xe9c) != 0) {
            ((IDirectDrawSurface*)*(int*)(*(char**)((char*)this + 0x1c) + 0xe9c))->Release();
            *(int*)(*(char**)((char*)this + 0x1c) + 0xe9c) = 0;
        }
        ((CGraphics*)*(int*)((char*)this + 0x20))->LoadBmp((IDirectDrawSurface**)(*(int*)((char*)this + 0x1c) + 0xe9c), (const char*)v38, 0xaf);
    }
    switch (*(*(char**)((char*)this + 0x1c) + 0xf32)) {
    case 1:
        if (0) {}
        if (0) {}
        *(int*)(*(char**)((char*)this + 0x1c) + 0x137c) = (int)new CBg01(*(int*)((char*)this + 0x20));
        break;
    case 0xa:
        *(int*)(*(char**)((char*)this + 0x1c) + 0x137c) = (int)new CBg10(*(int*)((char*)this + 0x20));
        break;
    case 0xc:
        *(int*)(*(char**)((char*)this + 0x1c) + 0x137c) = (int)new CBg12(*(int*)((char*)this + 0x20));
        break;
    case 0x10:
        *(int*)(*(char**)((char*)this + 0x1c) + 0x137c) = (int)new CBg16(*(int*)((char*)this + 0x20));
    }
    if (*(*(char**)((char*)this + 0x1c) + 0xf32) == 0x10) {
        *(double*)(*(char**)((char*)this + 0x1c) + 0x14258) = 0.125;
    } else {
        *(double*)(*(char**)((char*)this + 0x1c) + 0x14258) = 1.0;
    }
    ((CPlayer*)*(int*)*(char**)((char*)this + 0x14))->Vf11();
    ((CPlayer*)*(int*)*(char**)((char*)this + 0x18))->Vf11();
    if (*(*(char**)((char*)this + 0x1c) + 0x1364) == 2) {
        *(float*)(*(char**)*(char**)((char*)this + 0x14) + 0xa8) = *(*(char**)((char*)this + 0x1c) + 0x1358) / 1.5f;
        *(float*)(*(char**)*(char**)((char*)this + 0x18) + 0xa8) = *(*(char**)((char*)this + 0x1c) + 0x1358) / 1.5f;
    } else {
        *(float*)(*(char**)*(char**)((char*)this + 0x14) + 0xa8) = *(*(char**)((char*)this + 0x1c) + 0x1365);
        *(float*)(*(char**)*(char**)((char*)this + 0x18) + 0xa8) = *(*(char**)((char*)this + 0x1c) + 0x1365);
    }
    ((CGame*)*(int*)((char*)this + 0x1c))->Reset();
    ((CGraphics*)*(int*)((char*)this + 0x20))->BuildBlendTables((PALETTEENTRY*)(*(int*)((char*)this + 0x1c) + 0xf35));
}

void CScene2::Vf2()
{
}

void CScene2::Unk76da20(int p1, int p2, char p3, char p4)
{
    switch (p4) {
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
        break;
    case 0x18:
        *(int*)(char*)p1 = (int)new CMizuka(p2, *(int*)((char*)this + 0x1c), *(int*)((char*)this + 0x20), *(int*)((char*)this + 0x24), *(int*)((char*)this + 0x28), p3);
    }
    *(*(char**)(char*)p1 + 0x8d) = p4;
    *(int*)((char*)this + p3 * 4 + 0xc) = *(int*)(char*)p1;
    *(int*)(*(char**)(char*)p1 + 0xa4) = *(BYTE*)(*(char**)((char*)this + 0x1c) + 0x1343 + p3);
}
