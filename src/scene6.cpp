// CScene6 (0x759f30-0x75db6f), scene 6: the config menu (system\config_bg, config_ob,
// score), which writes its settings back with WriteConfigByte.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene6::CScene6(HWND hwnd, PTR32(CPlayer)* player1Ref, PTR32(CPlayer)* player2Ref, CGame* game, CGraphics* graphics, CInput* input, CSound* sound)
    : CScene(hwnd, player1Ref, player2Ref, game, graphics, input, sound)
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
    int gallerySide;
    int recordSide;
    int menuSide;

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
        menuSide = 0;
        for (; menuSide < 2; menuSide++) {
            if (m_game->m_inputY[menuSide] != 0 && m_held[menuSide] == 0) {
                m_cursor += m_game->m_inputY[menuSide];
                if (m_cursor > 7) {
                    m_cursor = 0;
                }
                if (m_cursor < 0) {
                    m_cursor = 7;
                }
                m_game->PlaySE(8);
                m_held[menuSide] = 1;
            }
            if (m_game->m_inputX[menuSide] == 0 && m_game->m_inputY[menuSide] == 0) {
                m_held[menuSide] = 0;
            }
            switch (m_cursor) {
            case 0:
                if (m_game->m_inputX[menuSide] != 0 && m_held[menuSide] == 0) {
                    m_game->m_drawEveryFrame += m_game->m_inputX[menuSide];
                    if (m_game->m_drawEveryFrame > 1) {
                        m_game->m_drawEveryFrame = 0;
                    }
                    if (m_game->m_drawEveryFrame < 0) {
                        m_game->m_drawEveryFrame = 1;
                    }
                    WriteConfigByte(0x22, m_game->m_drawEveryFrame + 1);
                    m_game->PlaySE(8);
                    m_held[menuSide] = 1;
                }
                break;
            case 1:
                if (m_game->m_inputX[menuSide] != 0 && m_held[menuSide] == 0) {
                    *(char*)&m_game->m_damageLevel += m_game->m_inputX[menuSide];
                    if (m_game->m_damageLevel > 3) {
                        m_game->m_damageLevel = 1;
                    }
                    if (m_game->m_damageLevel < 1) {
                        m_game->m_damageLevel = 3;
                    }
                    WriteConfigByte(0x24, m_game->m_damageLevel);
                    m_game->PlaySE(8);
                    m_held[menuSide] = 1;
                }
                break;
            case 2:
                if (m_game->m_inputX[menuSide] != 0 && m_held[menuSide] == 0) {
                    m_game->m_fullEffects += m_game->m_inputX[menuSide];
                    if (m_game->m_fullEffects > 1) {
                        m_game->m_fullEffects = 0;
                    }
                    if (m_game->m_fullEffects < 0) {
                        m_game->m_fullEffects = 1;
                    }
                    WriteConfigByte(0x23, m_game->m_fullEffects + 1);
                    m_game->PlaySE(8);
                    m_held[menuSide] = 1;
                }
                break;
            case 3:
                if (m_game->m_inputX[menuSide] != 0 && m_held[menuSide] == 0) {
                    *(char*)&m_game->m_cpuLevel += m_game->m_inputX[menuSide];
                    if (m_game->m_cpuLevel > 4) {
                        m_game->m_cpuLevel = 1;
                    }
                    if (m_game->m_cpuLevel < 1) {
                        m_game->m_cpuLevel = 4;
                    }
                    WriteConfigByte(0x21, m_game->m_cpuLevel);
                    m_game->PlaySE(8);
                    m_held[menuSide] = 1;
                }
                break;
            case 4:
                if (m_game->m_inputX[menuSide] != 0 && m_held[menuSide] == 0) {
                    *(char*)&m_game->m_roundsSetting += m_game->m_inputX[menuSide];
                    if (m_game->m_roundsSetting > 3) {
                        m_game->m_roundsSetting = 1;
                    }
                    if (m_game->m_roundsSetting < 1) {
                        m_game->m_roundsSetting = 3;
                    }
                    WriteConfigByte(0x26, m_game->m_roundsSetting);
                    m_game->PlaySE(8);
                    m_held[menuSide] = 1;
                }
                break;
            case 5:
                if (m_game->m_pressA[menuSide] == 1) {
                    m_game->PlaySE(6);
                    ShowLoadingScreen();
                }
                break;
            case 6:
                if (m_game->m_pressA[menuSide] == 1) {
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
                if (m_game->m_pressA[menuSide] == 1) {
                    m_leave = 1;
                }
            }
            if (m_game->m_pressB[menuSide] == 1) {
                m_leave = 1;
            }
        }
    } else if ((char)m_held[2] == 1) {
        m_game->UpdateInput();
        recordSide = 0;
        for (; recordSide < 2; recordSide++) {
            if (m_game->m_inputX[recordSide] != 0 && m_held[recordSide] == 0) {
                m_game->PlaySE(8);
                m_recordChar += m_game->m_inputX[recordSide];
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
                        if (m_game->m_inputX[recordSide] > 0) {
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
                m_held[recordSide] = 1;
            }
            if (m_game->m_inputX[recordSide] == 0 && m_game->m_inputY[recordSide] == 0) {
                m_held[recordSide] = 0;
            }
            if (m_game->m_pressA[recordSide] != 0 || m_game->m_pressB[recordSide] != 0) {
                if (m_game->m_pressA[recordSide] != 0) {
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
        gallerySide = 0;
        for (; gallerySide < 2; gallerySide++) {
            if (m_game->m_inputX[gallerySide] != 0 || m_game->m_inputY[gallerySide] != 0) {
                m_game->PlaySE(8);
                m_loadingScreen = m_game->m_inputX[gallerySide] + m_game->m_inputY[gallerySide] * 0xa + m_loadingScreen;
                if (m_loadingScreen > 0xae) {
                    m_loadingScreen = 0;
                }
                if (m_loadingScreen < 0) {
                    m_loadingScreen = 0xae;
                }
                ShowLoadingScreen();
            }
            if (m_game->m_pressA[gallerySide] != 0 || m_game->m_pressB[gallerySide] != 0) {
                if (m_game->m_pressA[gallerySide] != 0) {
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
    RECT dst;
    RECT src;

    if ((char)m_held[2] == 0) {
        src = MakeRect(0, 0, 0x140, 0xf0);
        dst = MakeRect(0, 0, 0x140, 0xf0);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_bgSurface), src, 0xff, 0);
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
        src = MakeRect(0, 0, 0x140, 0xf0);
        dst = MakeRect(0, 0, 0x140, 0xf0);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_bgSurface), src, 0xff, 0);
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

void CScene6::DrawNumber(int right, int top, int value)
{
    RECT src;
    int digit;
    RECT dst;
    DWORD rest; // the digits not drawn yet
    int x; // right edge of the digit drawn

    rest = value;
    x = right;
    do {
        digit = rest % 0xa;
        src.top = 0xf0;
        src.bottom = 0xfe;
        src.left = (digit << 4) + 2;
        src.right = (digit << 4) + 0xe;
        dst.top = top;
        dst.bottom = top + 0xe;
        dst.right = x - 2;
        dst.left = x - 0xe;
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_scoreSurface), src, m_scoreKey, 0);
        x -= 0xa;
        rest = rest / 0xa;
    } while (rest > 0);
}

void CScene6::HandleKeys()
{
    int hr;
    char keys[256]; // one byte per DIK_ code, bit 7 down

    hr = m_input->m_keyboard->GetDeviceState(0x100, keys);
    if (hr < 0 && hr == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if ((keys[1] & 0x80) != 0) {
        m_leave = 1;
    }
}

void CScene6::LoadRecord()
{
    char path[52];

    strcpy(path, "system\\");
    strcat(path, m_names[m_recordChar]);
    strcat(path, "\\");
    strcat(path, m_names[m_recordChar]);
    if (1) {
        strcat(path, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_portraitSurface, (const char*)path, 0, 0xd6);
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, 0, 0xd6, 0x28);
    } else {
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_portraitSurface, (const char*)path, 0xd6);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, 0, 0xd6, 0x28);
    }
    m_portraitKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_portraitSurface));
    m_record.Load(m_names[m_recordChar]);
}

void CScene6::SwitchRecord()
{
    int angle; // degrees, 0-360: the portrait slides out and back
    int frameStart;
    int shortFrame; // 1 every other frame, which waits 15 ms instead of 16

    frameStart = timeGetTime();
    shortFrame = 0;
    angle = 0;
    for (; angle <= 0x168; angle += 0xa) {
        Draw();
        m_portraitX = (int)(160.0 - cos(angle / 57.29579143313326) * 160.0);
        if (angle == 0xb4) {
            LoadRecord();
            m_graphics->SetPalette(m_palette);
        }
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(0x10 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
    m_portraitX = 0;
}

void CScene6::ShowLoadingScreen()
{
    int frameStart;
    char digits[20];
    int level; // brightness in 10% steps
    int shortFrame; // 1 every other frame, which waits 15 ms instead of 16
    char path[52];

    frameStart = timeGetTime();
    shortFrame = 0;
    level = 0xa;
    for (; level >= 0; level--) {
        Draw();
        m_graphics->Darken(m_palette, 0, 0xff, level * 0xa);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(0x10 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
    strcpy(path, "system\\nl\\nl");
    if (m_loadingScreen < 0x64) {
        strcat(path, "0");
    }
    if (m_loadingScreen < 0xa) {
        strcat(path, "0");
    }
    _itoa(m_loadingScreen, digits, 0xa);
    strcat(path, (const char*)digits);
    if (m_loadingSurface != 0) {
        (TOPTR(IUnknown*, m_loadingSurface))->Release();
        m_loadingSurface = 0;
    }
    if (1) {
        strcat(path, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_loadingSurface, (const char*)path, 0, 1);
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, 0, 1, 0xfe);
    } else {
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_loadingSurface, (const char*)path, 1);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, 0, 1, 0xfe);
    }
    m_held[2] = 2;
    level = 0;
    for (; level <= 0xa; level++) {
        Draw();
        m_graphics->Darken(m_palette, 0, 0xff, level * 0xa);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(0x10 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
}

void CScene6::FadeToBlack(int unused)
{
    int level; // brightness in 5% steps
    int frameStart;
    int shortFrame; // 1 every other frame, which waits 15 ms instead of 16

    frameStart = timeGetTime();
    shortFrame = 0;
    level = 0x14;
    for (; level >= 0; level--) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xff, level * 5);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(0x10 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
}

void CScene6::FadeFromBlack(BYTE dimTo)
{
    int level;
    int frameStart;
    int shortFrame; // 1 every other frame, which waits 15 ms instead of 16

    frameStart = timeGetTime();
    shortFrame = 0;
    level = 0;
    for (; level <= 0x14; level++) {
        Draw();
        m_graphics->Darken(m_palette, 1, dimTo, level << 1);
        m_graphics->Darken(m_palette, dimTo, 0xff, level * 5);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(0x10 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
}

void CScene6::SlidePage(BYTE slideIn)
{
    int inAngle; // degrees, 90-0
    int outAngle; // degrees, 0-90
    int frameStart;
    int shortFrame; // 1 every other frame, which waits 15 ms instead of 16

    frameStart = timeGetTime();
    shortFrame = 0;
    if (slideIn == 0) {
        outAngle = 0;
        for (; outAngle <= 0x5a; outAngle += 5) {
            Draw();
            m_pageY = (short)(int)((1.0 - cos(outAngle / 57.29579143313326)) * 320.0);
            while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(0x10 - shortFrame)) {
            }
            frameStart = timeGetTime();
            shortFrame = shortFrame == 0;
        }
        return;
    }
    inAngle = 0x5a;
    for (; inAngle >= 0; inAngle -= 5) {
        Draw();
        m_pageY = (short)(int)((1.0 - cos(inAngle / 57.29579143313326)) * 320.0);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(0x10 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
}
