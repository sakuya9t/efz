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
        m_game->LoadDat((IDirectDrawSurface**)&unk434, "system\\replay_bg.dat", 0, 1);
        m_game->LoadDat((IDirectDrawSurface**)&unk438, "system\\replay.dat", 0, 0xc1);
        m_graphics->LoadPaletteDat(m_palette, "system\\replay_bg.dat", 0, 1, 0xc0);
        m_graphics->LoadPaletteDat(m_palette, "system\\replay.dat", 0, 0xc1, 0x3e);
    } else {
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk434, "system\\replay_bg.bmp", 1);
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk438, "system\\replay.bmp", 0xc1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\replay_bg.bmp", 0, 1, 0xc0);
        m_graphics->LoadPaletteBmp(m_palette, "system\\replay.bmp", 0, 0xc1, 0x3e);
    }
    m_colorKey = m_graphics->GetColorKey((IDirectDrawSurface*)unk438);
    unk43c = 0;
    unk440 = 0;
    unk2c = 1;
    unk2d = 0;
    unk44e[0] = 0;
    unk44e[1] = 0;
    unk44a = 0x12c;
    unk44c = 0x12c;
    unk446 = 0xb4;
    unk448 = 0xb4;
    unk469 = 0;
    unk46a = 0;
    unk46b = 0;
    unk46c = 0;
    unk46d = 0;
    unk748 = 0.0;
    unk750 = 0.0;
    unk44e[2] = 1;
    unk44e[3] = 7;
    unk44e[4] = 9;
    unk44e[5] = 0xd;
    unk44e[6] = 4;
    unk44e[7] = 2;
    unk44e[8] = 0;
    unk44e[9] = 3;
    unk44e[0xa] = 0xb;
    unk44e[0xb] = 0xa;
    unk44e[0xc] = 8;
    unk44e[0xd] = 5;
    unk44e[0xe] = 0x14;
    unk44e[0xf] = 0xc;
    unk44e[0x10] = 0x13;
    unk44e[0x11] = 0xe;
    unk44e[0x12] = 0x12;
    unk462 = 6;
    unk463 = 0x15;
    unk464 = 0x10;
    unk465 = 0x11;
    unk467 = 0xf;
    *(tagRECT*)&unk46e[0xf6] = MakeRect(0, 0x2f, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x106] = MakeRect(0, 0x47, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x116] = MakeRect(0, 0x5f, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x126] = MakeRect(0, 0x77, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x136] = MakeRect(0, 0x8f, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x146] = MakeRect(0, 0xa7, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x156] = MakeRect(0, 0xbf, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x166] = MakeRect(0, 0xd7, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x176] = MakeRect(0, 0xef, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x186] = MakeRect(0, 0x107, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x196] = MakeRect(0, 0x11f, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x1a6] = MakeRect(0, 0x137, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x1b6] = MakeRect(0, 0x14f, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x1c6] = MakeRect(0, 0xef, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x216] = MakeRect(0, 0x1df, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x226] = MakeRect(0, 0x1f7, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x236] = MakeRect(0, 0x20f, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x246] = MakeRect(0, 0x227, 0x5a, 0x18);
    *(tagRECT*)&unk46e[0x266] = MakeRect(0, 0x257, 0x5a, 0x18);
}

CScene8::~CScene8()
{
    if (unk434 != 0) {
        ((IUnknown*)unk434)->Release();
        unk434 = 0;
    }
    if (unk438 != 0) {
        ((IUnknown*)unk438)->Release();
        unk438 = 0;
    }
}

BYTE CScene8::Update()
{
    int v4;

    if (unk2c > 0) {
        m_game->PlayMusic(6);
        Unk770e30();
    }
    if (unk2d > 0) {
        CScene::Unk759c90(m_palette, 1, 0, 0);
        if (unk2d == 2) {
            unk2c = 2;
            m_game->unkf32 = 0;
            unk2d = 0;
            m_game->StopMusic();
            return 1;
        }
        unk2c = 1;
        m_game->unkf32 = 0;
        unk2d = 0;
        m_game->StopMusic();
        return 0;
    }
    Vf2();
    m_game->UpdateInput();
    v4 = 0;
    for (; v4 < 2; v4++) {
        switch (unk469) {
        case 0:
            if (unk44e[v4] == 0 && m_game->m_inputY[v4] != 0) {
                m_game->PlaySE(8);
                unk46a += m_game->m_inputY[v4];
                if (unk46a > 8) {
                    unk46a = 0;
                } else if (unk46a < 0) {
                    unk46a = 8;
                }
            }
            if (unk44e[v4] == 0 && m_game->m_inputX[v4] != 0) {
                m_game->PlaySE(8);
                unk46d += m_game->m_inputX[v4];
                if (unk46d > 9) {
                    unk46d = 0;
                } else if (unk46d < 0) {
                    unk46d = 9;
                }
            }
            if ((char)m_game->m_pressA[v4] != 0) {
                if (unk46d == 9) {
                    unk2d = 1;
                } else {
                    m_game->PlaySE(6);
                    unk469 = 1;
                }
            }
            if (unk469 == 0 && ((char)m_game->m_pressB[0] != 0 || (char)m_game->m_pressB[1] != 0)) {
                unk2d = 1;
            }
            break;
        case 1:
            unk748 += 2.0;
            unk750 = unk46a * 16.0 / 90.0 + unk750;
            if (unk748 > 180.0) {
                unk748 = 180.0;
                unk469 = 2;
            }
            break;
        case 2:
            if (unk44e[v4] == 0 && m_game->m_inputY[v4] != 0) {
                m_game->PlaySE(8);
                unk46b += m_game->m_inputY[v4];
                if (unk46b >= 3) {
                    unk46b = 0;
                } else if (unk46b < 0) {
                    unk46b = 2;
                }
            }
            if ((char)m_game->m_pressA[v4] != 0) {
                m_game->PlaySE(6);
                if (((char (*)[9])&unk46e[0])[unk46d][unk46a] != 0 && unk46b == 0) {
                    m_game->unk14281 = unk46a;
                    m_game->unk14282 = unk46d;
                    m_game->unk14283 = 1;
                    CScene::Unk759c90(m_palette, 0, 0, 0x32);
                    unk2c = 2;
                    return 2;
                }
                if (unk46b == 1) {
                    if (((char (*)[9])&unk46e[0])[unk46d][unk46a] != 0) {
                        unk469 = 4;
                    } else {
                        m_game->unk14281 = unk46a;
                        m_game->unk14282 = unk46d;
                        m_game->unk14283 = 2;
                        unk2d = 2;
                    }
                } else {
                    unk469 = 3;
                }
            }
            if ((char)m_game->m_pressB[v4] != 0 && unk44e[v4] == 0) {
                unk469 = 3;
                unk44e[v4] = 1;
            }
            break;
        case 3:
            unk748 -= 2.0;
            unk750 = unk750 - unk46a * 16.0 / 90.0;
            if (unk748 < 0.0) {
                unk748 = 0.0;
                unk469 = 0;
            }
            break;
        case 4:
            if (unk44e[v4] == 0 && m_game->m_inputX[v4] != 0) {
                m_game->PlaySE(8);
                unk46c += m_game->m_inputX[v4];
                if (unk46c > 1) {
                    unk46c = 0;
                } else if (unk46c < 0) {
                    unk46c = 1;
                }
            }
            if ((char)m_game->m_pressA[v4] != 0) {
                m_game->PlaySE(6);
                unk469 = 2;
                if (unk46c == 0) {
                    m_game->unk14281 = unk46a;
                    m_game->unk14282 = unk46d;
                    m_game->unk14283 = 2;
                    unk2d = 2;
                }
            }
            if ((char)m_game->m_pressB[v4] != 0) {
                unk469 = 2;
                unk44e[v4] = 1;
            }
        }
        *(char*)&unk44e[v4] = m_game->m_inputX[v4] != 0 || m_game->m_inputY[v4] != 0 || (char)m_game->m_pressB[v4] != 0;
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
    m_graphics->Blit(x20, (IDirectDrawSurface*)unk434, v10, 0, 0);
    v10 = MakeRect(0, 0x19, 0x140, 0x10);
    x20 = MakeRect(0, 4, 0x140, 0x10);
    m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
    if (unk46d == 9) {
        v10 = MakeRect((unk46d << 4) + 0x50, 6, 0x28, 0xf);
        x20 = MakeRect((unk46d << 4) + 0x50, 4, 0x28, 0xf);
    } else {
        v10 = MakeRect((unk46d << 4) + 0x50, 6, 0x10, 0xf);
        x20 = MakeRect((unk46d << 4) + 0x50, 4, 0x10, 0xf);
    }
    m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
    if (unk469 != 4) {
        x24 = 0x13f - (int)(160.0 - cos(unk748 / 57.29579143313326) * 160.0);
        if (unk46b == 0) {
            v10 = MakeRect(0, 0x354, 0x140, 0x10);
        } else {
            v10 = MakeRect(0, 0x2cc, 0x140, 0x10);
        }
        x20 = MakeRect(0, x24 + 0x70, 0x140, 0x10);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        if (unk46b == 1) {
            v10 = MakeRect(0, 0x364, 0x140, 0x10);
        } else {
            v10 = MakeRect(0, 0x2dc, 0x140, 0x10);
        }
        x20 = MakeRect(0, x24 + 0x80, 0x140, 0x10);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        if (unk46b == 2) {
            v10 = MakeRect(0, 0x374, 0x140, 0x10);
        } else {
            v10 = MakeRect(0, 0x2ec, 0x140, 0x10);
        }
        x20 = MakeRect(0, x24 + 0x90, 0x140, 0x10);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
    } else if (unk469 == 4) {
        v10 = MakeRect(0, 0x300, 0x140, 0x2c);
        x20 = MakeRect(0, 0x70, 0x140, 0x2c);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        v10 = MakeRect(0, (unk46c << 4) + 0x334, 0x140, 0x10);
        x20 = MakeRect(0, 0xa0, 0x140, 0x10);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
    }
    v28 = 0;
    for (; v28 < 9; v28++) {
        if (unk46a == v28 && v28 < 9) {
            v10 = MakeRect(0, (v28 << 4) + 0x5c, 0x140, 0x10);
            x20 = MakeRect(0, (v28 << 4) + 0x60 - (int)unk750, 0x140, 0x10);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
            if (unk46d < 9 && unk46e[(unk46d * 9 + v28)] > 0) {
                v10 = MakeRect(((char (*)[18])&unk46e[0x51])[unk46d][v28 * 2] / 0xa * 0x50 + 0x40, (((char (*)[18])&unk46e[0x51])[unk46d][v28 * 2] % 0xa << 4) + 0x18c, 0x50, 0x10);
                x20 = MakeRect(0x5a, (v28 << 4) + 0x60 - (int)unk750, 0x50, 0x10);
                m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
                v10 = MakeRect(((char (*)[18])&unk46e[0x51])[unk46d][v28 * 2 + 1] / 0xa * 0x50 + 0x40, (((char (*)[18])&unk46e[0x51])[unk46d][v28 * 2 + 1] % 0xa << 4) + 0x18c, 0x50, 0x10);
                x20 = MakeRect(0xcd, (v28 << 4) + 0x60 - (int)unk750, 0x50, 0x10);
                m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
            }
        } else {
            k2c = (int)(160.0 - cos(unk748 / 57.29579143313326) * 160.0);
            v10 = MakeRect(0, (v28 << 4) + 0xfc, 0x140, 0x10);
            x20 = MakeRect(0, (v28 << 4) + 0x60 + k2c, 0x140, 0x10);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
            if (unk46d < 9 && unk46e[(unk46d * 9 + v28)] > 0) {
                v10 = MakeRect(((char (*)[18])&unk46e[0x51])[unk46d][v28 * 2] / 0xa * 0x50 + 0x40, (((char (*)[18])&unk46e[0x51])[unk46d][v28 * 2] % 0xa << 4) + 0x22c, 0x50, 0x10);
                x20 = MakeRect(0x5a, (v28 << 4) + 0x60 + k2c, 0x50, 0x10);
                m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
                v10 = MakeRect(((char (*)[18])&unk46e[0x51])[unk46d][v28 * 2 + 1] / 0xa * 0x50 + 0x40, (((char (*)[18])&unk46e[0x51])[unk46d][v28 * 2 + 1] % 0xa << 4) + 0x22c, 0x50, 0x10);
                x20 = MakeRect(0xcd, (v28 << 4) + 0x60 + k2c, 0x50, 0x10);
                m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
            }
        }
    }
    m_graphics->Flip();
}

void CScene8::Vf2()
{
    int l10c;
    char v108[256];

    l10c = m_input->m_keyboard->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if ((v108[1] & 0x80) != 0) {
        unk2d = 1;
    }
}

void CScene8::Unk770e30()
{
    int v38;
    int v34;
    int v30;
    char v2c[32];
    char vc[8];

    unk44e[0] = 0;
    unk44e[1] = 0;
    unk44a = 0x12c;
    unk44c = 0x12c;
    unk446 = 0xb4;
    unk448 = 0xb4;
    unk469 = 0;
    unk46b = 0;
    unk46c = 0;
    unk748 = 0.0;
    unk750 = 0.0;
    m_game->unk1358 = 0;
    m_game->unk1378 = 0;
    m_game->unk1379 = 0;
    m_game->unk1338[0] = 0;
    m_game->unk1338[1] = 0;
    if (1) {
        m_graphics->LoadPaletteDat(m_palette, "system\\replay.dat", 0, 0xc1, 0x3e);
    } else {
        m_graphics->LoadPaletteBmp(m_palette, "system\\replay.bmp", 0, 0xc1, 0x3e);
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
            v30 = (&m_game->m_replay)->OpenRead((const char*)v2c);
            if (v30 == 0) {
                unk46e[(v34 * 9 + v38)] = 0;
            } else {
                ((char (*)[18])&unk46e[0x51])[v34][v38 * 2] = (&m_game->m_replay)->Read();
                ((char (*)[18])&unk46e[0x51])[v34][v38 * 2 + 1] = (&m_game->m_replay)->Read();
                unk46e[(v34 * 9 + v38)] = 1;
            }
            (&m_game->m_replay)->Close();
        }
    }
    if (unk2c == 2) {
        Draw();
        CScene::Unk759e20(m_palette, 1);
    } else {
        if (1) {
            m_graphics->LoadPaletteDat(m_palette, "system\\replay.dat", 0, 0xc1, 0x3e);
        } else {
            m_graphics->LoadPaletteBmp(m_palette, "system\\replay.bmp", 0, 0xc1, 0x3e);
        }
        m_graphics->SetPalette(m_palette);
        CScene::Unk759e20(m_palette, 1);
    }
    unk2c = 0;
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
        m_graphics->Darken(m_palette, 1, 0xc1, xc << 1);
        m_graphics->Darken(m_palette, 0xc2, 0xff, xc * 5);
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
        m_graphics->Darken(m_palette, 1, 0xc1, xc << 1);
        m_graphics->Darken(m_palette, 0xc2, 0xff, xc * 5);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
}
