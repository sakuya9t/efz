// CScene8 (0x76e480-0x7712ef), scene 8: the replay browser (system\replay_bg,
// replay\dataNNN.rep). Two of its functions are never called (0x771170, 0x771230).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene8::CScene8(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\replay_bg.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\replay.dat", 0, 0xc1);
        m_graphics->LoadPaletteDat(m_palette, "system\\replay_bg.dat", 0, 1, 0xc0);
        m_graphics->LoadPaletteDat(m_palette, "system\\replay.dat", 0, 0xc1, 0x3e);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\replay_bg.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\replay.bmp", 0xc1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\replay_bg.bmp", 0, 1, 0xc0);
        m_graphics->LoadPaletteBmp(m_palette, "system\\replay.bmp", 0, 0xc1, 0x3e);
    }
    m_colorKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_menuSurface));
    unk43c = 0;
    unk440 = 0;
    m_enter = 1;
    m_leave = 0;
    m_held[0] = 0;
    m_held[1] = 0;
    unk44a = 0x12c;
    unk44c = 0x12c;
    unk446 = 0xb4;
    unk448 = 0xb4;
    m_state = 0;
    m_slot = 0;
    m_menuChoice = 0;
    m_overwriteChoice = 0;
    m_page = 0;
    m_menuAngle = 0.0;
    m_listScroll = 0.0;
    m_held[2] = 1;
    m_held[3] = 7;
    m_held[4] = 9;
    m_held[5] = 0xd;
    m_held[6] = 4;
    m_held[7] = 2;
    m_held[8] = 0;
    m_held[9] = 3;
    m_held[0xa] = 0xb;
    m_held[0xb] = 0xa;
    m_held[0xc] = 8;
    m_held[0xd] = 5;
    m_held[0xe] = 0x14;
    m_held[0xf] = 0xc;
    m_held[0x10] = 0x13;
    m_held[0x11] = 0xe;
    m_held[0x12] = 0x12;
    unk462 = 6;
    unk463 = 0x15;
    unk464 = 0x10;
    unk465 = 0x11;
    unk467 = 0xf;
    *(tagRECT*)&m_replays[0xf6] = MakeRect(0, 0x2f, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x106] = MakeRect(0, 0x47, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x116] = MakeRect(0, 0x5f, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x126] = MakeRect(0, 0x77, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x136] = MakeRect(0, 0x8f, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x146] = MakeRect(0, 0xa7, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x156] = MakeRect(0, 0xbf, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x166] = MakeRect(0, 0xd7, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x176] = MakeRect(0, 0xef, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x186] = MakeRect(0, 0x107, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x196] = MakeRect(0, 0x11f, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x1a6] = MakeRect(0, 0x137, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x1b6] = MakeRect(0, 0x14f, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x1c6] = MakeRect(0, 0xef, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x216] = MakeRect(0, 0x1df, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x226] = MakeRect(0, 0x1f7, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x236] = MakeRect(0, 0x20f, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x246] = MakeRect(0, 0x227, 0x5a, 0x18);
    *(tagRECT*)&m_replays[0x266] = MakeRect(0, 0x257, 0x5a, 0x18);
}

CScene8::~CScene8()
{
    if (m_bgSurface != 0) {
        (TOPTR(IUnknown*, m_bgSurface))->Release();
        m_bgSurface = 0;
    }
    if (m_menuSurface != 0) {
        (TOPTR(IUnknown*, m_menuSurface))->Release();
        m_menuSurface = 0;
    }
}

BYTE CScene8::Update()
{
    int v4;

    if (m_enter > 0) {
        m_game->PlayMusic(6);
        Enter();
    }
    if (m_leave > 0) {
        CScene::FadeOut(m_palette, 1, 0, 0);
        if (m_leave == 2) {
            m_enter = 2;
            m_game->m_stage = 0;
            m_leave = 0;
            m_game->StopMusic();
            return 1;
        }
        m_enter = 1;
        m_game->m_stage = 0;
        m_leave = 0;
        m_game->StopMusic();
        return 0;
    }
    HandleKeys();
    m_game->UpdateInput();
    v4 = 0;
    for (; v4 < 2; v4++) {
        switch (m_state) {
        case 0:
            if (m_held[v4] == 0 && m_game->m_inputY[v4] != 0) {
                m_game->PlaySE(8);
                m_slot += m_game->m_inputY[v4];
                if (m_slot > 8) {
                    m_slot = 0;
                } else if (m_slot < 0) {
                    m_slot = 8;
                }
            }
            if (m_held[v4] == 0 && m_game->m_inputX[v4] != 0) {
                m_game->PlaySE(8);
                m_page += m_game->m_inputX[v4];
                if (m_page > 9) {
                    m_page = 0;
                } else if (m_page < 0) {
                    m_page = 9;
                }
            }
            if (m_game->m_pressA[v4] != 0) {
                if (m_page == 9) {
                    m_leave = 1;
                } else {
                    m_game->PlaySE(6);
                    m_state = 1;
                }
            }
            if (m_state == 0 && (m_game->m_pressB[0] != 0 || m_game->m_pressB[1] != 0)) {
                m_leave = 1;
            }
            break;
        case 1:
            m_menuAngle += 2.0;
            m_listScroll = m_slot * 16.0 / 90.0 + m_listScroll;
            if (m_menuAngle > 180.0) {
                m_menuAngle = 180.0;
                m_state = 2;
            }
            break;
        case 2:
            if (m_held[v4] == 0 && m_game->m_inputY[v4] != 0) {
                m_game->PlaySE(8);
                m_menuChoice += m_game->m_inputY[v4];
                if (m_menuChoice >= 3) {
                    m_menuChoice = 0;
                } else if (m_menuChoice < 0) {
                    m_menuChoice = 2;
                }
            }
            if (m_game->m_pressA[v4] != 0) {
                m_game->PlaySE(6);
                if (((char (*)[9])&m_replays[0])[m_page][m_slot] != 0 && m_menuChoice == 0) {
                    m_game->m_replaySlot = m_slot;
                    m_game->m_replayPage = m_page;
                    m_game->m_replayMode = 1;
                    CScene::FadeOut(m_palette, 0, 0, 0x32);
                    m_enter = 2;
                    return 2;
                }
                if (m_menuChoice == 1) {
                    if (((char (*)[9])&m_replays[0])[m_page][m_slot] != 0) {
                        m_state = 4;
                    } else {
                        m_game->m_replaySlot = m_slot;
                        m_game->m_replayPage = m_page;
                        m_game->m_replayMode = 2;
                        m_leave = 2;
                    }
                } else {
                    m_state = 3;
                }
            }
            if (m_game->m_pressB[v4] != 0 && m_held[v4] == 0) {
                m_state = 3;
                m_held[v4] = 1;
            }
            break;
        case 3:
            m_menuAngle -= 2.0;
            m_listScroll = m_listScroll - m_slot * 16.0 / 90.0;
            if (m_menuAngle < 0.0) {
                m_menuAngle = 0.0;
                m_state = 0;
            }
            break;
        case 4:
            if (m_held[v4] == 0 && m_game->m_inputX[v4] != 0) {
                m_game->PlaySE(8);
                m_overwriteChoice += m_game->m_inputX[v4];
                if (m_overwriteChoice > 1) {
                    m_overwriteChoice = 0;
                } else if (m_overwriteChoice < 0) {
                    m_overwriteChoice = 1;
                }
            }
            if (m_game->m_pressA[v4] != 0) {
                m_game->PlaySE(6);
                m_state = 2;
                if (m_overwriteChoice == 0) {
                    m_game->m_replaySlot = m_slot;
                    m_game->m_replayPage = m_page;
                    m_game->m_replayMode = 2;
                    m_leave = 2;
                }
            }
            if (m_game->m_pressB[v4] != 0) {
                m_state = 2;
                m_held[v4] = 1;
            }
        }
        *(char*)&m_held[v4] = m_game->m_inputX[v4] != 0 || m_game->m_inputY[v4] != 0 || m_game->m_pressB[v4] != 0;
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
    m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_bgSurface), v10, 0, 0);
    v10 = MakeRect(0, 0x19, 0x140, 0x10);
    x20 = MakeRect(0, 4, 0x140, 0x10);
    m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
    if (m_page == 9) {
        v10 = MakeRect((m_page << 4) + 0x50, 6, 0x28, 0xf);
        x20 = MakeRect((m_page << 4) + 0x50, 4, 0x28, 0xf);
    } else {
        v10 = MakeRect((m_page << 4) + 0x50, 6, 0x10, 0xf);
        x20 = MakeRect((m_page << 4) + 0x50, 4, 0x10, 0xf);
    }
    m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
    if (m_state != 4) {
        x24 = 0x13f - (int)(160.0 - cos(m_menuAngle / 57.29579143313326) * 160.0);
        if (m_menuChoice == 0) {
            v10 = MakeRect(0, 0x354, 0x140, 0x10);
        } else {
            v10 = MakeRect(0, 0x2cc, 0x140, 0x10);
        }
        x20 = MakeRect(0, x24 + 0x70, 0x140, 0x10);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
        if (m_menuChoice == 1) {
            v10 = MakeRect(0, 0x364, 0x140, 0x10);
        } else {
            v10 = MakeRect(0, 0x2dc, 0x140, 0x10);
        }
        x20 = MakeRect(0, x24 + 0x80, 0x140, 0x10);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
        if (m_menuChoice == 2) {
            v10 = MakeRect(0, 0x374, 0x140, 0x10);
        } else {
            v10 = MakeRect(0, 0x2ec, 0x140, 0x10);
        }
        x20 = MakeRect(0, x24 + 0x90, 0x140, 0x10);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
    } else if (m_state == 4) {
        v10 = MakeRect(0, 0x300, 0x140, 0x2c);
        x20 = MakeRect(0, 0x70, 0x140, 0x2c);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
        v10 = MakeRect(0, (m_overwriteChoice << 4) + 0x334, 0x140, 0x10);
        x20 = MakeRect(0, 0xa0, 0x140, 0x10);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
    }
    v28 = 0;
    for (; v28 < 9; v28++) {
        if (m_slot == v28 && v28 < 9) {
            v10 = MakeRect(0, (v28 << 4) + 0x5c, 0x140, 0x10);
            x20 = MakeRect(0, (v28 << 4) + 0x60 - (int)m_listScroll, 0x140, 0x10);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
            if (m_page < 9 && m_replays[(m_page * 9 + v28)] > 0) {
                v10 = MakeRect(((char (*)[18])&m_replays[0x51])[m_page][v28 * 2] / 0xa * 0x50 + 0x40, (((char (*)[18])&m_replays[0x51])[m_page][v28 * 2] % 0xa << 4) + 0x18c, 0x50, 0x10);
                x20 = MakeRect(0x5a, (v28 << 4) + 0x60 - (int)m_listScroll, 0x50, 0x10);
                m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
                v10 = MakeRect(((char (*)[18])&m_replays[0x51])[m_page][v28 * 2 + 1] / 0xa * 0x50 + 0x40, (((char (*)[18])&m_replays[0x51])[m_page][v28 * 2 + 1] % 0xa << 4) + 0x18c, 0x50, 0x10);
                x20 = MakeRect(0xcd, (v28 << 4) + 0x60 - (int)m_listScroll, 0x50, 0x10);
                m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
            }
        } else {
            k2c = (int)(160.0 - cos(m_menuAngle / 57.29579143313326) * 160.0);
            v10 = MakeRect(0, (v28 << 4) + 0xfc, 0x140, 0x10);
            x20 = MakeRect(0, (v28 << 4) + 0x60 + k2c, 0x140, 0x10);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
            if (m_page < 9 && m_replays[(m_page * 9 + v28)] > 0) {
                v10 = MakeRect(((char (*)[18])&m_replays[0x51])[m_page][v28 * 2] / 0xa * 0x50 + 0x40, (((char (*)[18])&m_replays[0x51])[m_page][v28 * 2] % 0xa << 4) + 0x22c, 0x50, 0x10);
                x20 = MakeRect(0x5a, (v28 << 4) + 0x60 + k2c, 0x50, 0x10);
                m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
                v10 = MakeRect(((char (*)[18])&m_replays[0x51])[m_page][v28 * 2 + 1] / 0xa * 0x50 + 0x40, (((char (*)[18])&m_replays[0x51])[m_page][v28 * 2 + 1] % 0xa << 4) + 0x22c, 0x50, 0x10);
                x20 = MakeRect(0xcd, (v28 << 4) + 0x60 + k2c, 0x50, 0x10);
                m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_menuSurface), v10, m_colorKey, 0);
            }
        }
    }
    m_graphics->Flip();
}

void CScene8::HandleKeys()
{
    int l10c;
    char v108[256];

    l10c = m_input->m_keyboard->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if ((v108[1] & 0x80) != 0) {
        m_leave = 1;
    }
}

void CScene8::Enter()
{
    int v38;
    int v34;
    int v30;
    char v2c[32];
    char vc[8];

    m_held[0] = 0;
    m_held[1] = 0;
    unk44a = 0x12c;
    unk44c = 0x12c;
    unk446 = 0xb4;
    unk448 = 0xb4;
    m_state = 0;
    m_menuChoice = 0;
    m_overwriteChoice = 0;
    m_menuAngle = 0.0;
    m_listScroll = 0.0;
    m_game->m_arcadeMatch = 0;
    m_game->m_continued = 0;
    m_game->m_continuedAt = 0;
    m_game->m_editColor[0] = 0;
    m_game->m_editColor[1] = 0;
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
            v30 = m_game->m_replay.OpenRead((const char*)v2c);
            if (v30 == 0) {
                m_replays[(v34 * 9 + v38)] = 0;
            } else {
                ((char (*)[18])&m_replays[0x51])[v34][v38 * 2] = m_game->m_replay.Read();
                ((char (*)[18])&m_replays[0x51])[v34][v38 * 2 + 1] = m_game->m_replay.Read();
                m_replays[(v34 * 9 + v38)] = 1;
            }
            m_game->m_replay.Close();
        }
    }
    if (m_enter == 2) {
        Draw();
        CScene::FadeIn(m_palette, 1);
    } else {
        if (1) {
            m_graphics->LoadPaletteDat(m_palette, "system\\replay.dat", 0, 0xc1, 0x3e);
        } else {
            m_graphics->LoadPaletteBmp(m_palette, "system\\replay.bmp", 0, 0xc1, 0x3e);
        }
        m_graphics->SetPalette(m_palette);
        CScene::FadeIn(m_palette, 1);
    }
    m_enter = 0;
}

void CScene8::FadeOutDimmed()
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

void CScene8::FadeInDimmed()
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
