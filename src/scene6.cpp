// CScene6 (0x759f30-0x75db6f), scene 6: the config menu (system\config_bg, config_ob,
// score), which writes its settings back with WriteConfigByte.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

// The top of an item's row on the page (before it slides: m_pageY).
static int OptionY(int item)
{
    return 95 + 18 * item;
}

#ifdef EFZ_NATIVE
// The native game's OPTIONS has pages (efz::OptionsHooks, port/options.cpp): this one,
// the game's own, first; then EfzRevival's settings and the native game's, whose rows the
// hooks write over the page's background. Tab, or either side's C (D back), turns the
// page; the page is the game's own again each time OPTIONS opens.
static int s_page;
static bool s_tab;     // Tab went down on this frame (HandleKeys)
static bool s_tabDown;

static int OptionPages()
{
    return efz::g_options.pages ? efz::g_options.pages() : 1;
}

// A frame of the main page's state on the native pages: turning the page, and the pages
// after the game's own. True when the frame was theirs (the game's page doesn't run).
static bool NativePage(CScene6* scene)
{
    int pages = OptionPages();
    if (pages < 2)
        return false;
    CGame* game = scene->m_game;
    int turn = s_tab ? 1 : 0;
    for (int side = 0; side < 2; side++) {
        if (game->m_pressC[side] == 1)
            turn = 1;
        if (game->m_pressD[side] == 1)
            turn = -1;
    }
    if (turn != 0) {
        s_page = (s_page + turn + pages) % pages;
        game->PlaySE(8);
        return true;
    }
    if (s_page == 0)
        return false;
    for (int side = 0; side < 2; side++) {
        int dx = 0, dy = 0;
        if (scene->m_held[side] == 0) {
            dy = game->m_inputY[side];
            dx = dy == 0 ? game->m_inputX[side] : 0;
        }
        if (game->m_inputX[side] == 0 && game->m_inputY[side] == 0)
            scene->m_held[side] = 0;
        else
            scene->m_held[side] = 1;
        switch (efz::g_options.update(s_page, side, dx, dy, game->m_pressA[side] == 1,
                                      game->m_pressB[side] == 1)) {
        case efz::kOptionsMoved:
        case efz::kOptionsChanged:
            game->PlaySE(8);
            break;
        case efz::kOptionsBack:
            scene->m_leave = 1;
            break;
        default:
            break;
        }
    }
    return true;
}
#endif

CScene6::CScene6(HWND hwnd, PTR32(CPlayer)* player1Ref, PTR32(CPlayer)* player2Ref, CGame* game, CGraphics* graphics, CInput* input, CSound* sound)
    : CScene(hwnd, player1Ref, player2Ref, game, graphics, input, sound)
{
    m_portraitSurface = 0;
    m_loadingSurface = 0;
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\config_bg.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\config_ob.dat", 0, 161);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_scoreSurface, "system\\score.dat", 0, 161);
        m_graphics->LoadPaletteDat(m_palette, "system\\config_bg.dat", 0, 1, 161);
        m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 162, 32);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\config_bg.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_menuSurface, "system\\config_ob.bmp", 161);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_scoreSurface, "system\\score.bmp", 161);
        m_graphics->LoadPaletteBmp(m_palette, "system\\config_bg.bmp", 0, 1, 161);
        m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 161, 32);
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
    strcpy(m_names[10], "nayuki");
    strcpy(m_names[11], "mio");
    strcpy(m_names[12], "misuzu");
    strcpy(m_names[13], "minagi");
    strcpy(m_names[14], "kano");
    strcpy(m_names[15], "mizukab");
    strcpy(m_names[16], "EXnanase");
    strcpy(m_names[17], "kaori");
    strcpy(m_names[18], "ikumi");
    strcpy(m_names[19], "mishio");
    strcpy(m_names[20], "nayukiB");
    strcpy(m_names[21], "akiko");
    strcpy(m_names[22], "kanna");
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
#ifdef EFZ_NATIVE
        s_page = 0;
#endif
        m_cursor = 0;
        m_recordChar = 0;
        unk44a = 0;
        m_enter = 0;
        m_held[2] = 0;
        if (1) {
            m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 161, 32);
        } else {
            m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 161, 32);
        }
        if (m_game->m_extraChars == 0) {
            m_game->PlayMusic(6);
        } else {
            m_game->PlayMusic(7);
        }
        CScene::FadeIn(m_palette, 1);
    }
    if (m_leave == 1) {
        CScene::FadeOut(m_palette, 1, 0, 100);
        m_game->StopMusic();
        m_enter = 1;
        m_leave = 0;
        m_held[2] = 0;
        return 0;
    }
    if ((char)m_held[2] == 0) {
        m_game->UpdateInput();
        menuSide = 0;
#ifdef EFZ_NATIVE
        if (NativePage(this))
            menuSide = 2; // the native pages' frame: not the game's page's
#endif
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
                        m_graphics->LoadPaletteDat(m_palette, "system\\score.dat", 0, 161, 32);
                    } else {
                        m_graphics->LoadPaletteBmp(m_palette, "system\\score.bmp", 0, 161, 32);
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
                    if (m_recordChar == 12) {
                        m_recordChar = 15;
                    }
                    if (m_recordChar == 14) {
                        m_recordChar = 11;
                    }
                }
                if (m_game->m_extraChars == -1) {
                    if (m_recordChar == 16) {
                        m_recordChar = 20;
                    }
                    if (m_recordChar == 19) {
                        m_recordChar = 15;
                    }
                    if (m_recordChar == 22) {
                        if (m_game->m_inputX[recordSide] > 0) {
                            m_recordChar = 0;
                        } else {
                            m_recordChar = 20;
                        }
                    }
                }
                if (m_recordChar > 22) {
                    m_recordChar = 0;
                }
                if (m_recordChar < 0) {
                    m_recordChar = 22;
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
                    m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 161, 32);
                } else {
                    m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 161, 32);
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
                m_loadingScreen = m_game->m_inputX[gallerySide] + m_game->m_inputY[gallerySide] * 10 + m_loadingScreen;
                if (m_loadingScreen > 174) {
                    m_loadingScreen = 0;
                }
                if (m_loadingScreen < 0) {
                    m_loadingScreen = 174;
                }
                ShowLoadingScreen();
            }
            if (m_game->m_pressA[gallerySide] != 0 || m_game->m_pressB[gallerySide] != 0) {
                if (m_game->m_pressA[gallerySide] != 0) {
                    m_game->PlaySE(6);
                }
                FadeToBlack(1);
                if (1) {
                    m_graphics->LoadPaletteDat(m_palette, "system\\config_bg.dat", 0, 1, 160);
                    m_graphics->LoadPaletteDat(m_palette, "system\\config_ob.dat", 0, 161, 32);
                } else {
                    m_graphics->LoadPaletteBmp(m_palette, "system\\config_bg.bmp", 0, 1, 160);
                    m_graphics->LoadPaletteBmp(m_palette, "system\\config_ob.bmp", 0, 161, 32);
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
        src = MakeRect(0, 0, 320, 240);
        dst = MakeRect(0, 0, 320, 240);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_bgSurface), src, 255, 0);
        m_graphics->Blit(MakeRect(0, 0 - m_pageY, 320, 40), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 0, 320, 40), m_colorKey, 0);
#ifdef EFZ_NATIVE
        // The native pages: the background and the title; the hooks write the rest.
        if (efz::g_options.shown)
            efz::g_options.shown(s_page);
        if (s_page != 0) {
            m_graphics->Flip();
            return;
        }
#endif
        m_graphics->Blit(MakeRect(0, m_pageY + 40, 320, 200), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 40, 320, 200), m_colorKey, 0);
        switch (m_cursor) {
        case 0:
            m_graphics->Blit(MakeRect(0, m_pageY + OptionY(0), 112, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 261, 112, 14), m_colorKey, 0);
            break;
        case 1:
            m_graphics->Blit(MakeRect(0, m_pageY + OptionY(1), 112, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 279, 112, 14), m_colorKey, 0);
            break;
        case 2:
            m_graphics->Blit(MakeRect(0, m_pageY + OptionY(2), 112, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 297, 112, 14), m_colorKey, 0);
            break;
        case 3:
            m_graphics->Blit(MakeRect(0, m_pageY + OptionY(3), 112, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 315, 112, 14), m_colorKey, 0);
            break;
        case 4:
            m_graphics->Blit(MakeRect(0, m_pageY + OptionY(4), 112, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 333, 112, 14), m_colorKey, 0);
            break;
        case 5:
            m_graphics->Blit(MakeRect(0, m_pageY + OptionY(5), 320, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 351, 320, 14), m_colorKey, 0);
            break;
        case 6:
            m_graphics->Blit(MakeRect(0, m_pageY + OptionY(6), 320, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 369, 320, 14), m_colorKey, 0);
            break;
        case 7:
            m_graphics->Blit(MakeRect(0, m_pageY + OptionY(7), 320, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(0, 387, 320, 14), m_colorKey, 0);
        }
        if (m_game->m_drawEveryFrame == 0) {
            m_graphics->Blit(MakeRect(112, m_pageY + OptionY(0), 80, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(112, 261, 80, 14), m_colorKey, 0);
        } else if (m_game->m_drawEveryFrame == 1) {
            m_graphics->Blit(MakeRect(192, m_pageY + OptionY(0), 80, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(192, 261, 80, 14), m_colorKey, 0);
        }
        if (m_game->m_damageLevel == 1) {
            m_graphics->Blit(MakeRect(112, m_pageY + OptionY(1), 64, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(112, 279, 64, 14), m_colorKey, 0);
        } else if (m_game->m_damageLevel == 2) {
            m_graphics->Blit(MakeRect(176, m_pageY + OptionY(1), 64, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(176, 279, 64, 14), m_colorKey, 0);
        } else if (m_game->m_damageLevel == 3) {
            m_graphics->Blit(MakeRect(240, m_pageY + OptionY(1), 64, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(240, 279, 64, 14), m_colorKey, 0);
        }
        if (m_game->m_fullEffects == 0) {
            m_graphics->Blit(MakeRect(112, m_pageY + OptionY(2), 48, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(112, 297, 48, 14), m_colorKey, 0);
        } else if (m_game->m_fullEffects == 1) {
            m_graphics->Blit(MakeRect(160, m_pageY + OptionY(2), 48, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(160, 297, 48, 14), m_colorKey, 0);
        }
        if (m_game->m_cpuLevel == 1) {
            m_graphics->Blit(MakeRect(128, m_pageY + OptionY(3), 24, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(128, 315, 24, 14), m_colorKey, 0);
        } else if (m_game->m_cpuLevel == 2) {
            m_graphics->Blit(MakeRect(152, m_pageY + OptionY(3), 24, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(152, 315, 24, 14), m_colorKey, 0);
        } else if (m_game->m_cpuLevel == 3) {
            m_graphics->Blit(MakeRect(176, m_pageY + OptionY(3), 24, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(176, 315, 24, 14), m_colorKey, 0);
        } else if (m_game->m_cpuLevel == 4) {
            m_graphics->Blit(MakeRect(200, m_pageY + OptionY(3), 24, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(200, 315, 24, 14), m_colorKey, 0);
        }
        if (m_game->m_roundsSetting == 1) {
            m_graphics->Blit(MakeRect(128, m_pageY + OptionY(4), 24, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(128, 333, 24, 14), m_colorKey, 0);
        } else if (m_game->m_roundsSetting == 2) {
            m_graphics->Blit(MakeRect(152, m_pageY + OptionY(4), 24, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(152, 333, 24, 14), m_colorKey, 0);
        } else if (m_game->m_roundsSetting == 3) {
            m_graphics->Blit(MakeRect(176, m_pageY + OptionY(4), 24, 14), TOPTR(IDirectDrawSurface*, m_menuSurface), MakeRect(176, 333, 24, 14), m_colorKey, 0);
        }
    } else if ((char)m_held[2] == 1) {
        src = MakeRect(0, 0, 320, 240);
        dst = MakeRect(0, 0, 320, 240);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_bgSurface), src, 255, 0);
        m_graphics->Blit(MakeRect(0, 0 - m_pageY, 320, 40), TOPTR(IDirectDrawSurface*, m_scoreSurface), MakeRect(0, 0, 320, 40), m_scoreKey, 0);
        m_graphics->Blit(MakeRect(0, m_pageY + 40, 320, 200), TOPTR(IDirectDrawSurface*, m_scoreSurface), MakeRect(0, 40, 320, 200), m_scoreKey, 0);
        m_graphics->Blit(MakeRect(m_portraitX + 80, m_pageY, 320, 240), TOPTR(IDirectDrawSurface*, m_portraitSurface), MakeRect(0, 0, 320, 240), m_portraitKey, 0);
        DrawNumber(160, m_pageY + 143, m_record.uses);
        DrawNumber(160, m_pageY + 161, m_record.vsWins);
        DrawNumber(160, m_pageY + 179, m_record.vsLosses);
        DrawNumber(160, m_pageY + 197, m_record.maxDamage);
        DrawNumber(160, m_pageY + 215, m_record.maxCombo);
    } else if ((char)m_held[2] == 2) {
        m_graphics->Blit(MakeRect(0, 0, 320, 240), TOPTR(IDirectDrawSurface*, m_loadingSurface), MakeRect(0, 0, 320, 240), 0, 0);
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
        digit = rest % 10;
        src.top = 240;
        src.bottom = 254;
        src.left = (digit << 4) + 2;
        src.right = (digit << 4) + 14;
        dst.top = top;
        dst.bottom = top + 14;
        dst.right = x - 2;
        dst.left = x - 14;
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_scoreSurface), src, m_scoreKey, 0);
        x -= 10;
        rest = rest / 10;
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
#ifdef EFZ_NATIVE
    bool tab = (keys[0x0f] & 0x80) != 0;
    s_tab = tab && !s_tabDown;
    s_tabDown = tab;
#endif
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
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_portraitSurface, (const char*)path, 0, 214);
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, 0, 214, 40);
    } else {
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_portraitSurface, (const char*)path, 214);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, 0, 214, 40);
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
    for (; angle <= 360; angle += 10) {
        Draw();
        m_portraitX = (int)(160.0 - cos(angle / 57.29579143313326) * 160.0);
        if (angle == 180) {
            LoadRecord();
            m_graphics->SetPalette(m_palette);
        }
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(16 - shortFrame)) {
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
    level = 10;
    for (; level >= 0; level--) {
        Draw();
        m_graphics->Darken(m_palette, 0, 0xff, level * 0xa);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(16 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
    strcpy(path, "system\\nl\\nl");
    if (m_loadingScreen < 100) {
        strcat(path, "0");
    }
    if (m_loadingScreen < 10) {
        strcat(path, "0");
    }
    _itoa(m_loadingScreen, digits, 10);
    strcat(path, (const char*)digits);
    if (m_loadingSurface != 0) {
        (TOPTR(IUnknown*, m_loadingSurface))->Release();
        m_loadingSurface = 0;
    }
    if (1) {
        strcat(path, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_loadingSurface, (const char*)path, 0, 1);
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, 0, 1, 254);
    } else {
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_loadingSurface, (const char*)path, 1);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, 0, 1, 254);
    }
    m_held[2] = 2;
    level = 0;
    for (; level <= 10; level++) {
        Draw();
        m_graphics->Darken(m_palette, 0, 0xff, level * 0xa);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(16 - shortFrame)) {
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
    level = 20;
    for (; level >= 0; level--) {
        Draw();
        m_graphics->Darken(m_palette, 1, 0xff, level * 5);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(16 - shortFrame)) {
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
    for (; level <= 20; level++) {
        Draw();
        m_graphics->Darken(m_palette, 1, dimTo, level << 1);
        m_graphics->Darken(m_palette, dimTo, 0xff, level * 5);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(16 - shortFrame)) {
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
        for (; outAngle <= 90; outAngle += 5) {
            Draw();
            m_pageY = (short)(int)((1.0 - cos(outAngle / 57.29579143313326)) * 320.0);
            while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(16 - shortFrame)) {
            }
            frameStart = timeGetTime();
            shortFrame = shortFrame == 0;
        }
        return;
    }
    inAngle = 90;
    for (; inAngle >= 0; inAngle -= 5) {
        Draw();
        m_pageY = (short)(int)((1.0 - cos(inAngle / 57.29579143313326)) * 320.0);
        while ((DWORD)(timeGetTime() - frameStart) < (BYTE)(16 - shortFrame)) {
        }
        frameStart = timeGetTime();
        shortFrame = shortFrame == 0;
    }
}
