// CScene6 (0x759f30-0x75db6f), scene 6: the config menu (system\config_bg, config_ob,
// score), which writes its settings back with WriteConfigByte.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene6::CScene6(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    m_portraitSurface = 0;
    m_loadingSurface = 0;
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\config_bg.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\config_ob.dat", 0, 0xa1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_scoreSurface, "system\\score.dat", 0, 0xa1);
        m_graphics->LoadPaletteDat(m_palette, "system\\config_bg.dat", 0, 1, 0xa1);
        m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 0xa2, 0x20);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\config_bg.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\config_ob.bmp", 0xa1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_scoreSurface, "system\\score.bmp", 0xa1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\config_bg.bmp", 0, 1, 0xa1);
        m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 0xa1, 0x20);
    }
    m_colorKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_menuSurface));
    m_scoreKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_scoreSurface));
    m_cursor = 0;
    m_recordChar = 0;
    unk44a = 0;
    m_held[0] = 0;
    m_held[1] = 0;
    m_held[2] = 0;
    m_enter = 1;
    m_leave = 0;
    unk748 = 0.0;
    m_portraitX = 0;
    m_pageY = 0;
    m_loadingScreen = 0;
    strcpy(m_names[0], "nanase");
    strcpy(m_names[1], "ayu");
    strcpy(m_names[2], "mai");
    strcpy(m_names[3], "makoto");
    strcpy(m_names[4], "akane");
    strcpy(m_names[5], "mayu");
    strcpy(m_names[6], "nagamori");
    strcpy(m_names[7], "misaki");
    strcpy(m_names[8], "shiori");
    strcpy(m_names[9], "sayuri");
    strcpy(m_names[0xa], "nayuki");
    strcpy(m_names[0xb], "mio");
    strcpy(m_names[0xc], "misuzu");
    strcpy(m_names[0xd], "minagi");
    strcpy(m_names[0xe], "kano");
    strcpy(m_names[0xf], "mizukab");
    strcpy(m_names[0x10], "EXnanase");
    strcpy(m_names[0x11], "kaori");
    strcpy(m_names[0x12], "ikumi");
    strcpy(m_names[0x13], "mishio");
    strcpy(m_names[0x14], "nayukiB");
    strcpy(m_names[0x15], "akiko");
    strcpy(m_names[0x16], "kanna");
}

CScene6::~CScene6()
{
    if (m_bgSurface != 0) {
        (TOPTR(IUnknown*, m_bgSurface))->Release();
        m_bgSurface = 0;
    }
    if (m_menuSurface != 0) {
        (TOPTR(IUnknown*, m_menuSurface))->Release();
        m_menuSurface = 0;
    }
    if (m_scoreSurface != 0) {
        (TOPTR(IUnknown*, m_scoreSurface))->Release();
        m_scoreSurface = 0;
    }
    if (m_portraitSurface != 0) {
        (TOPTR(IUnknown*, m_portraitSurface))->Release();
        m_portraitSurface = 0;
    }
    if (m_loadingSurface != 0) {
        (TOPTR(IUnknown*, m_loadingSurface))->Release();
        m_loadingSurface = 0;
    }
}

BYTE CScene6::Update()
{
    int xc;
    int v8;
    int v4;

    HandleKeys();
    if (m_enter == 1) {
        m_cursor = 0;
        m_recordChar = 0;
        unk44a = 0;
        m_enter = 0;
        m_held[2] = 0;
        if (1) {
            m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 0xa1, 0x20);
        } else {
            m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 0xa1, 0x20);
        }
        if (m_game->m_extraChars == 0) {
            m_game->PlayMusic(6);
        } else {
            m_game->PlayMusic(7);
        }
        CScene::FadeIn(m_palette, 1);
    }
    if (m_leave == 1) {
        CScene::FadeOut(m_palette, 1, 0, 0x64);
        m_game->StopMusic();
        m_enter = 1;
        m_leave = 0;
        m_held[2] = 0;
        return 0;
    }
    if ((char)m_held[2] == 0) {
        m_game->UpdateInput();
        v4 = 0;
        for (; v4 < 2; v4++) {
            if (m_game->m_inputY[v4] != 0 && m_held[v4] == 0) {
                m_cursor += m_game->m_inputY[v4];
                if (m_cursor > 7) {
                    m_cursor = 0;
                }
                if (m_cursor < 0) {
                    m_cursor = 7;
                }
                m_game->PlaySE(8);
                m_held[v4] = 1;
            }
            if (m_game->m_inputX[v4] == 0 && m_game->m_inputY[v4] == 0) {
                m_held[v4] = 0;
            }
            switch (m_cursor) {
            case 0:
                if (m_game->m_inputX[v4] != 0 && m_held[v4] == 0) {
                    m_game->m_drawEveryFrame += m_game->m_inputX[v4];
                    if (m_game->m_drawEveryFrame > 1) {
                        m_game->m_drawEveryFrame = 0;
                    }
                    if (m_game->m_drawEveryFrame < 0) {
                        m_game->m_drawEveryFrame = 1;
                    }
                    WriteConfigByte(0x22, m_game->m_drawEveryFrame + 1);
                    m_game->PlaySE(8);
                    m_held[v4] = 1;
                }
                break;
            case 1:
                if (m_game->m_inputX[v4] != 0 && m_held[v4] == 0) {
                    *(char*)&m_game->m_damageLevel += m_game->m_inputX[v4];
                    if (m_game->m_damageLevel > 3) {
                        m_game->m_damageLevel = 1;
                    }
                    if (m_game->m_damageLevel < 1) {
                        m_game->m_damageLevel = 3;
                    }
                    WriteConfigByte(0x24, m_game->m_damageLevel);
                    m_game->PlaySE(8);
                    m_held[v4] = 1;
                }
                break;
            case 2:
                if (m_game->m_inputX[v4] != 0 && m_held[v4] == 0) {
                    m_game->m_fullEffects += m_game->m_inputX[v4];
                    if (m_game->m_fullEffects > 1) {
                        m_game->m_fullEffects = 0;
                    }
                    if (m_game->m_fullEffects < 0) {
                        m_game->m_fullEffects = 1;
                    }
                    WriteConfigByte(0x23, m_game->m_fullEffects + 1);
                    m_game->PlaySE(8);
                    m_held[v4] = 1;
                }
                break;
            case 3:
                if (m_game->m_inputX[v4] != 0 && m_held[v4] == 0) {
                    *(char*)&m_game->m_cpuLevel += m_game->m_inputX[v4];
                    if (m_game->m_cpuLevel > 4) {
                        m_game->m_cpuLevel = 1;
                    }
                    if (m_game->m_cpuLevel < 1) {
                        m_game->m_cpuLevel = 4;
                    }
                    WriteConfigByte(0x21, m_game->m_cpuLevel);
                    m_game->PlaySE(8);
                    m_held[v4] = 1;
                }
                break;
            case 4:
                if (m_game->m_inputX[v4] != 0 && m_held[v4] == 0) {
                    *(char*)&m_game->m_roundsSetting += m_game->m_inputX[v4];
                    if (m_game->m_roundsSetting > 3) {
                        m_game->m_roundsSetting = 1;
                    }
                    if (m_game->m_roundsSetting < 1) {
                        m_game->m_roundsSetting = 3;
                    }
                    WriteConfigByte(0x26, m_game->m_roundsSetting);
                    m_game->PlaySE(8);
                    m_held[v4] = 1;
                }
                break;
            case 5:
                if (m_game->m_pressA[v4] == 1) {
                    m_game->PlaySE(6);
                    ShowLoadingScreen();
                }
                break;
            case 6:
                if (m_game->m_pressA[v4] == 1) {
                    m_game->PlaySE(6);
                    SlidePage(0);
                    if (1) {
                        m_graphics->LoadPaletteDat(m_palette, "system\\score.dat", 0, 0xa1, 0x20);
                    } else {
                        m_graphics->LoadPaletteBmp(m_palette, "system\\score.bmp", 0, 0xa1, 0x20);
                    }
                    m_held[2] = 1;
                    LoadRecord();
                    m_graphics->SetPalette(m_palette);
                    SlidePage(1);
                }
                break;
            case 7:
                if (m_game->m_pressA[v4] == 1) {
                    m_leave = 1;
                }
            }
            if (m_game->m_pressB[v4] == 1) {
                m_leave = 1;
            }
        }
    } else if ((char)m_held[2] == 1) {
        m_game->UpdateInput();
        v8 = 0;
        for (; v8 < 2; v8++) {
            if (m_game->m_inputX[v8] != 0 && m_held[v8] == 0) {
                m_game->PlaySE(8);
                m_recordChar += m_game->m_inputX[v8];
                if (m_game->m_extraChars == 0) {
                    if (m_recordChar == 0xc) {
                        m_recordChar = 0xf;
                    }
                    if (m_recordChar == 0xe) {
                        m_recordChar = 0xb;
                    }
                }
                if (m_game->m_extraChars == -1) {
                    if (m_recordChar == 0x10) {
                        m_recordChar = 0x14;
                    }
                    if (m_recordChar == 0x13) {
                        m_recordChar = 0xf;
                    }
                    if (m_recordChar == 0x16) {
                        if (m_game->m_inputX[v8] > 0) {
                            m_recordChar = 0;
                        } else {
                            m_recordChar = 0x14;
                        }
                    }
                }
                if (m_recordChar > 0x16) {
                    m_recordChar = 0;
                }
                if (m_recordChar < 0) {
                    m_recordChar = 0x16;
                }
                SwitchRecord();
                m_held[v8] = 1;
            }
            if (m_game->m_inputX[v8] == 0 && m_game->m_inputY[v8] == 0) {
                m_held[v8] = 0;
            }
            if (m_game->m_pressA[v8] != 0 || m_game->m_pressB[v8] != 0) {
                if (m_game->m_pressA[v8] != 0) {
                    m_game->PlaySE(6);
                }
                SlidePage(0);
                if (1) {
                    m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 0xa1, 0x20);
                } else {
                    m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 0xa1, 0x20);
                }
                m_graphics->SetPalette(m_palette);
                m_held[2] = 0;
                SlidePage(1);
            }
        }
    } else if ((char)m_held[2] == 2) {
        m_game->UpdateInput();
        xc = 0;
        for (; xc < 2; xc++) {
            if (m_game->m_inputX[xc] != 0 || m_game->m_inputY[xc] != 0) {
                m_game->PlaySE(8);
                m_loadingScreen = m_game->m_inputX[xc] + m_game->m_inputY[xc] * 0xa + m_loadingScreen;
                if (m_loadingScreen > 0xae) {
                    m_loadingScreen = 0;
                }
                if (m_loadingScreen < 0) {
                    m_loadingScreen = 0xae;
                }
                ShowLoadingScreen();
            }
            if (m_game->m_pressA[xc] != 0 || m_game->m_pressB[xc] != 0) {
                if (m_game->m_pressA[xc] != 0) {
                    m_game->PlaySE(6);
                }
                FadeToBlack(1);
                if (1) {
                    m_graphics->LoadPaletteDat(m_palette, "system\\config_bg.dat", 0, 1, 0xa0);
                    m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 0xa1, 0x20);
                } else {
                    m_graphics->LoadPaletteBmp(m_palette, "system\\config_bg.bmp", 0, 1, 0xa0);
                    m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 0xa1, 0x20);
                }
                m_held[2] = 0;
                FadeFromBlack(0);
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

    if ((char)m_held[2] == 0) {
        v10 = MakeRect(0, 0, 0x140, 0xf0);
        v20 = MakeRect(0, 0, 0x140, 0xf0);
        m_graphics->Blit(v20, TOPTR(IDirectDrawSurface*, m_bgSurface), v10, 0xff, 0);
        m_graphics->Blit(MakeRect(0, 0 - m_pageY, 0x140, 0x28), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0, 0x140, 0x28), m_colorKey, 0);
        m_graphics->Blit(MakeRect(0, m_pageY + 0x28, 0x140, 0xc8), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0x28, 0x140, 0xc8), m_colorKey, 0);
        switch (m_cursor) {
        case 0:
            m_graphics->Blit(MakeRect(0, m_pageY + 0x5f, 0x70, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0x105, 0x70, 0xe), m_colorKey, 0);
            break;
        case 1:
            m_graphics->Blit(MakeRect(0, m_pageY + 0x71, 0x70, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0x117, 0x70, 0xe), m_colorKey, 0);
            break;
        case 2:
            m_graphics->Blit(MakeRect(0, m_pageY + 0x83, 0x70, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0x129, 0x70, 0xe), m_colorKey, 0);
            break;
        case 3:
            m_graphics->Blit(MakeRect(0, m_pageY + 0x95, 0x70, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0x13b, 0x70, 0xe), m_colorKey, 0);
            break;
        case 4:
            m_graphics->Blit(MakeRect(0, m_pageY + 0xa7, 0x70, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0x14d, 0x70, 0xe), m_colorKey, 0);
            break;
        case 5:
            m_graphics->Blit(MakeRect(0, m_pageY + 0xb9, 0x140, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0x15f, 0x140, 0xe), m_colorKey, 0);
            break;
        case 6:
            m_graphics->Blit(MakeRect(0, m_pageY + 0xcb, 0x140, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0x171, 0x140, 0xe), m_colorKey, 0);
            break;
        case 7:
            m_graphics->Blit(MakeRect(0, m_pageY + 0xdd, 0x140, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0x183, 0x140, 0xe), m_colorKey, 0);
        }
        if (m_game->m_drawEveryFrame == 0) {
            m_graphics->Blit(MakeRect(0x70, m_pageY + 0x5f, 0x50, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0x70, 0x105, 0x50, 0xe), m_colorKey, 0);
        } else if (m_game->m_drawEveryFrame == 1) {
            m_graphics->Blit(MakeRect(0xc0, m_pageY + 0x5f, 0x50, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0xc0, 0x105, 0x50, 0xe), m_colorKey, 0);
        }
        if (m_game->m_damageLevel == 1) {
            m_graphics->Blit(MakeRect(0x70, m_pageY + 0x71, 0x40, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0x70, 0x117, 0x40, 0xe), m_colorKey, 0);
        } else if (m_game->m_damageLevel == 2) {
            m_graphics->Blit(MakeRect(0xb0, m_pageY + 0x71, 0x40, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0xb0, 0x117, 0x40, 0xe), m_colorKey, 0);
        } else if (m_game->m_damageLevel == 3) {
            m_graphics->Blit(MakeRect(0xf0, m_pageY + 0x71, 0x40, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0xf0, 0x117, 0x40, 0xe), m_colorKey, 0);
        }
        if (m_game->m_fullEffects == 0) {
            m_graphics->Blit(MakeRect(0x70, m_pageY + 0x83, 0x30, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0x70, 0x129, 0x30, 0xe), m_colorKey, 0);
        } else if (m_game->m_fullEffects == 1) {
            m_graphics->Blit(MakeRect(0xa0, m_pageY + 0x83, 0x30, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0xa0, 0x129, 0x30, 0xe), m_colorKey, 0);
        }
        if (m_game->m_cpuLevel == 1) {
            m_graphics->Blit(MakeRect(0x80, m_pageY + 0x95, 0x18, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0x80, 0x13b, 0x18, 0xe), m_colorKey, 0);
        } else if (m_game->m_cpuLevel == 2) {
            m_graphics->Blit(MakeRect(0x98, m_pageY + 0x95, 0x18, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0x98, 0x13b, 0x18, 0xe), m_colorKey, 0);
        } else if (m_game->m_cpuLevel == 3) {
            m_graphics->Blit(MakeRect(0xb0, m_pageY + 0x95, 0x18, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0xb0, 0x13b, 0x18, 0xe), m_colorKey, 0);
        } else if (m_game->m_cpuLevel == 4) {
            m_graphics->Blit(MakeRect(0xc8, m_pageY + 0x95, 0x18, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0xc8, 0x13b, 0x18, 0xe), m_colorKey, 0);
        }
        if (m_game->m_roundsSetting == 1) {
            m_graphics->Blit(MakeRect(0x80, m_pageY + 0xa7, 0x18, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0x80, 0x14d, 0x18, 0xe), m_colorKey, 0);
        } else if (m_game->m_roundsSetting == 2) {
            m_graphics->Blit(MakeRect(0x98, m_pageY + 0xa7, 0x18, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0x98, 0x14d, 0x18, 0xe), m_colorKey, 0);
        } else if (m_game->m_roundsSetting == 3) {
            m_graphics->Blit(MakeRect(0xb0, m_pageY + 0xa7, 0x18, 0xe), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0xb0, 0x14d, 0x18, 0xe), m_colorKey, 0);
        }
    } else if ((char)m_held[2] == 1) {
        v10 = MakeRect(0, 0, 0x140, 0xf0);
        v20 = MakeRect(0, 0, 0x140, 0xf0);
        m_graphics->Blit(v20, TOPTR(IDirectDrawSurface*, m_bgSurface), v10, 0xff, 0);
        m_graphics->Blit(MakeRect(0, 0 - m_pageY, 0x140, 0x28), TOPTR(IDirectDrawSurface*, m_scoreSurface), MakeRect(0, 0, 0x140, 0x28), m_scoreKey, 0);
        m_graphics->Blit(MakeRect(0, m_pageY + 0x28, 0x140, 0xc8), TOPTR(IDirectDrawSurface*, m_scoreSurface), MakeRect(0, 0x28, 0x140, 0xc8), m_scoreKey, 0);
        m_graphics->Blit(MakeRect(m_portraitX + 0x50, m_pageY, 0x140, 0xf0), TOPTR(IDirectDrawSurface*, m_portraitSurface), MakeRect(0, 0, 0x140, 0xf0), m_portraitKey, 0);
        DrawNumber(0xa0, m_pageY + 0x8f, m_record.uses);
        DrawNumber(0xa0, m_pageY + 0xa1, m_record.vsWins);
        DrawNumber(0xa0, m_pageY + 0xb3, m_record.vsLosses);
        DrawNumber(0xa0, m_pageY + 0xc5, m_record.maxDamage);
        DrawNumber(0xa0, m_pageY + 0xd7, m_record.maxCombo);
    } else if ((char)m_held[2] == 2) {
        m_graphics->Blit(MakeRect(0, 0, 0x140, 0xf0), TOPTR(IDirectDrawSurface*, m_loadingSurface), MakeRect(0, 0, 0x140, 0xf0), 0, 0);
    }
    m_graphics->Flip();
}

void CScene6::DrawNumber(int p1, int p2, int p3)
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
        m_graphics->Blit(l18, TOPTR(IDirectDrawSurface*, m_scoreSurface), v2c, m_scoreKey, 0);
        l4 -= 0xa;
        x8 = x8 / 0xa;
    } while (x8 > 0);
}

void CScene6::HandleKeys()
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

void CScene6::LoadRecord()
{
    char v38[52];

    strcpy(v38, "system\\");
    strcat(v38, m_names[m_recordChar]);
    strcat(v38, "\\");
    strcat(v38, m_names[m_recordChar]);
    if (1) {
        strcat(v38, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_portraitSurface, (const char*)v38, 0, 0xd6);
        m_graphics->LoadPaletteDat(m_palette, (const char*)v38, 0, 0xd6, 0x28);
    } else {
        strcat(v38, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_portraitSurface, (const char*)v38, 0xd6);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v38, 0, 0xd6, 0x28);
    }
    m_portraitKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_portraitSurface));
    m_record.Load(m_names[m_recordChar]);
}

void CScene6::SwitchRecord()
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0;
    for (; xc <= 0x168; xc += 0xa) {
        Draw();
        m_portraitX = (int)(160.0 - cos(xc / 57.29579143313326) * 160.0);
        if (xc == 0xb4) {
            LoadRecord();
            m_graphics->SetPalette(m_palette);
        }
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
    m_portraitX = 0;
}

void CScene6::ShowLoadingScreen()
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
        m_graphics->Darken(m_palette, 0, 0xff, l40 * 0xa);
        while ((DWORD)(timeGetTime() - v58) < (BYTE)(0x10 - x3c)) {
        }
        v58 = timeGetTime();
        x3c = x3c == 0;
    }
    strcpy(v38, "system\\nl\\nl");
    if (m_loadingScreen < 0x64) {
        strcat(v38, "0");
    }
    if (m_loadingScreen < 0xa) {
        strcat(v38, "0");
    }
    _itoa(m_loadingScreen, v54, 0xa);
    strcat(v38, (const char*)v54);
    if (m_loadingSurface != 0) {
        (TOPTR(IUnknown*, m_loadingSurface))->Release();
        m_loadingSurface = 0;
    }
    if (1) {
        strcat(v38, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_loadingSurface, (const char*)v38, 0, 1);
        m_graphics->LoadPaletteDat(m_palette, (const char*)v38, 0, 1, 0xfe);
    } else {
        strcat(v38, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_loadingSurface, (const char*)v38, 1);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v38, 0, 1, 0xfe);
    }
    m_held[2] = 2;
    l40 = 0;
    for (; l40 <= 0xa; l40++) {
        Draw();
        m_graphics->Darken(m_palette, 0, 0xff, l40 * 0xa);
        while ((DWORD)(timeGetTime() - v58) < (BYTE)(0x10 - x3c)) {
        }
        v58 = timeGetTime();
        x3c = x3c == 0;
    }
}

void CScene6::FadeToBlack(int p1)
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0x14;
    for (; xc >= 0; xc--) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xff, xc * 5);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
}

void CScene6::FadeFromBlack(BYTE p1)
{
    int xc;
    int v8;
    int v4;

    v8 = timeGetTime();
    v4 = 0;
    xc = 0;
    for (; xc <= 0x14; xc++) {
        Draw();
        m_graphics->Darken(m_palette, 1, p1, xc << 1);
        m_graphics->Darken(m_palette, p1, 0xff, xc * 5);
        while ((DWORD)(timeGetTime() - v8) < (BYTE)(0x10 - v4)) {
        }
        v8 = timeGetTime();
        v4 = v4 == 0;
    }
}

void CScene6::SlidePage(BYTE p1)
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
            m_pageY = (short)(int)((1.0 - cos(vc / 57.29579143313326)) * 320.0);
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
        m_pageY = (short)(int)((1.0 - cos(l10 / 57.29579143313326)) * 320.0);
        while ((DWORD)(timeGetTime() - x8) < (BYTE)(0x10 - l4)) {
        }
        x8 = timeGetTime();
        l4 = l4 == 0;
    }
}
