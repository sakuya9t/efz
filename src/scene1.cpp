// CScene1 (0x753260-0x759f2f), scene 1: character and stage select
// (system\chr_sel_bg, chr_sel_ob, system\stage\). The inline methods of CScene follow
// it: its constructor and the two palette fades (0x759c10-0x759f2f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene1::CScene1(HWND hwnd, PTR32(CPlayer)* player1Ref, PTR32(CPlayer)* player2Ref, CGame* game, CGraphics* graphics, CInput* input, CSound* sound)
    : CScene(hwnd, player1Ref, player2Ref, game, graphics, input, sound)
{
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\chr_sel_bg.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_obSurface, "system\\chr_sel_ob.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_stageNames, "system\\stage\\all.dat", 0, 175);
        m_graphics->LoadPaletteDat(m_palette, "system\\chr_sel_ob.dat", 0, 1, 174);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\chr_sel_bg.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_obSurface, "system\\chr_sel_ob.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_stageNames, "system\\stage\\all.bmp", 175);
        m_graphics->LoadPaletteBmp(m_palette, "system\\chr_sel_ob.bmp", 0, 1, 174);
    }
    m_colorKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_obSurface));
    m_colorKeys[2] = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_stageNames));
    m_portraits[0] = 0;
    m_portraits[1] = 0;
    m_stagePicture = 0;
    m_enter = 1;
    m_leave = 0;
    m_held[0] = 0;
    m_held[1] = 0;
    m_bgScroll = 0.0;
    m_bgSlideTime = 60;
    m_p1BarOffset = 50.0;
    m_anim[0] = 0;
    m_p2BarOffset = 50.0;
    m_anim[1] = 0;
    m_barScroll = 0.0;
    m_anim[2] = 0;
    m_gridY = -240.0;
    m_anim[3] = 60;
    m_anim[4] = 0;
    m_anim[5] = 0;
    m_portraitOffset[0] = 300;
    m_portraitOffset[1] = 300;
    m_portraitAngle[0] = 180;
    m_portraitAngle[1] = 180;
    m_state[0] = 5;
    m_state[1] = 5;
    m_charId[0] = 2;
    m_charId[1] = 9;
    m_paletteIndex[0] = 0;
    m_paletteIndex[1] = 0;
    m_randomTime[0] = 0;
    m_randomTime[1] = 0;
    m_cursorX[0] = 0;
    m_cursorY[0] = 0;
    m_cursorX[1] = 2;
    m_cursorY[1] = 0;
    m_grid[0] = 6;
    m_grid[1] = 0;
    m_grid[2] = 4;
    m_grid[3] = 7;
    m_grid[4] = 5;
    m_grid[5] = 11;
    m_grid[6] = 1;
    m_grid[7] = 10;
    m_grid[8] = 3;
    m_grid[9] = 8;
    m_grid[10] = 2;
    m_grid[11] = 9;
    m_grid[12] = 23;
    m_grid[13] = 20;
    m_grid[14] = 21;
    m_grid[15] = 14;
    m_grid[16] = 12;
    m_grid[17] = 18;
    m_grid[18] = 17;
    m_grid[19] = 15;
    m_grid[20] = 13;
    m_grid[21] = 16;
    m_grid[22] = -1;
    m_grid[23] = 19;
    m_portraitShift[0] = -40;
    m_portraitShift[1] = -10;
    m_portraitShift[2] = -5;
    m_portraitShift[3] = 0;
    m_portraitShift[4] = -5;
    m_portraitShift[5] = -5;
    m_portraitShift[6] = -30;
    m_portraitShift[7] = -30;
    m_portraitShift[8] = -20;
    m_portraitShift[9] = -10;
    m_portraitShift[10] = -40;
    m_portraitShift[11] = -5;
    m_portraitShift[12] = -50;
    m_portraitShift[13] = 0;
    m_portraitShift[14] = -15;
    m_portraitShift[15] = -15;
    m_portraitShift[16] = -20;
    m_portraitShift[17] = -20;
    m_portraitShift[18] = -45;
    m_portraitShift[19] = 10;
    m_portraitShift[20] = -20;
    m_portraitShift[21] = 0;
    m_portraitShift[22] = 0;
    m_portraitShift[23] = -20;
    m_namePlate[0] = 5;
    m_namePlate[1] = 7;
    m_namePlate[2] = 11;
    m_namePlate[3] = 9;
    m_namePlate[4] = 0;
    m_namePlate[5] = 4;
    m_namePlate[6] = 2;
    m_namePlate[7] = 1;
    m_namePlate[8] = 10;
    m_namePlate[9] = 12;
    m_namePlate[10] = 8;
    m_namePlate[11] = 3;
    m_namePlate[12] = 21;
    m_namePlate[13] = 13;
    m_namePlate[14] = 20;
    m_namePlate[15] = 14;
    m_namePlate[16] = 15;
    m_namePlate[17] = 8;
    m_namePlate[18] = 6;
    m_namePlate[19] = 19;
    m_namePlate[20] = 17;
    m_namePlate[21] = 18;
    m_namePlate[22] = -1;
    m_namePlate[23] = 16;
    m_namePlate[24] = 6;
}

CScene1::~CScene1()
{
    if (m_bgSurface != 0) {
        (TOPTR(IUnknown*, m_bgSurface))->Release();
        m_bgSurface = 0;
    }
    if (m_obSurface != 0) {
        (TOPTR(IUnknown*, m_obSurface))->Release();
        m_obSurface = 0;
    }
    if (m_stageNames != 0) {
        (TOPTR(IUnknown*, m_stageNames))->Release();
        m_stageNames = 0;
    }
    if (m_stagePicture != 0) {
        (TOPTR(IUnknown*, m_stagePicture))->Release();
        m_stagePicture = 0;
    }
    if (m_portraits[0] != 0) {
        (TOPTR(IUnknown*, m_portraits[0]))->Release();
        m_portraits[0] = 0;
    }
    if (m_portraits[1] != 0) {
        (TOPTR(IUnknown*, m_portraits[1]))->Release();
        m_portraits[1] = 0;
    }
}

BYTE CScene1::Update()
{
    char digits[8];
    char path[40];
    int side;

    if (m_enter > 0) {
        Enter();
    }
    if (m_leave > 0) {
        CScene::FadeOut(m_palette, 0, 0, 100);
        m_enter = 1;
        m_game->m_stage = 0;
        m_leave = 0;
        m_game->StopMusic();
        if (m_game->m_gameMode == 5) {
            return 8;
        }
        return 0;
    }
    HandleKeys();
    m_game->UpdateInput();
    side = 0;
    for (; side < 2; side++) {
        if (m_game->m_gameMode == 0 && m_game->m_isCpu[side] == 1) {
            m_game->m_inputX[side] = 0;
            m_game->m_inputY[side] = 0;
            m_game->m_pressA[side] = 0;
            m_game->m_pressB[side] = 0;
            m_game->m_pressC[side] = 0;
            m_game->m_pressD[side] = 0;
        }
        if (m_game->m_isCpu[side] == 1 && (m_game->m_gameMode == 1 || m_game->m_gameMode == 3 || m_game->m_gameMode == 5)) {
            if (m_state[side] < 4 && m_state[(1 - side)] == 6) {
                m_game->m_inputX[side] = m_game->m_inputX[(1 - side)];
                m_game->m_inputY[side] = m_game->m_inputY[(1 - side)];
                m_game->m_pressA[side] = m_game->m_pressA[(1 - side)];
                m_game->m_pressC[side] = m_game->m_pressC[(1 - side)];
                m_game->m_pressD[side] = m_game->m_pressD[(1 - side)];
                m_game->m_inputX[(1 - side)] = 0;
                m_game->m_inputY[(1 - side)] = 0;
                m_game->m_pressA[(1 - side)] = 0;
                m_game->m_pressC[(1 - side)] = 0;
                m_game->m_pressD[(1 - side)] = 0;
            }
            m_game->m_pressB[side] = m_game->m_pressB[(1 - side)];
        }
    }
    side = 0;
    for (; side < 2; side++) {
        switch (m_state[side]) {
        case 0:
            m_game->m_editColor[side] = 0;
            m_anim[side] = 2;
            if (m_game->m_pressC[side] != 0 && m_randomTime[side] == 0 || m_game->m_pressA[side] != 0 && m_cursorX[side] == 1 && m_cursorY[side] == 7) {
                m_randomTime[side] = 60;
            }
            if (m_randomTime[side] > 0) {
                m_randomTime[side]--;
                m_game->m_inputX[side] = rand() % 3 - 1;
                m_game->m_inputY[side] = rand() % 2;
                m_game->m_pressA[side] = 0;
                m_held[side] = 0;
                if (m_randomTime[side] == 0) {
                    m_charId[side] = m_grid[(m_cursorX[side] + m_cursorY[side] * 3)];
                    if (m_charId[side] < 0) {
                        m_randomTime[side]++;
                    }
                    if (m_game->m_extraChars == 0 && (m_charId[side] == 19 || m_charId[side] == 20 || m_charId[side] == 21 || m_charId[side] == 23)) {
                        m_randomTime[side]++;
                    }
                    if (m_game->m_extraChars == -1 && (m_charId[side] == 12 || m_charId[side] == 13 || m_charId[side] == 14 || m_charId[side] == 15)) {
                        m_randomTime[side]++;
                    }
                }
                if (m_randomTime[side] == 0) {
                    m_game->m_inputX[side] = 0;
                    m_game->m_inputY[side] = 0;
                    m_game->m_pressA[side] = 1;
                }
            }
            if (m_held[side] == 0) {
                if (m_game->m_inputY[side] < 0) {
                    m_cursorY[side] = (m_cursorY[side] + 7) % 8;
                    m_game->PlaySE(8);
                    m_held[side] = 1;
                } else if (m_game->m_inputY[side] > 0) {
                    m_cursorY[side] = (m_cursorY[side] + 1) % 8;
                    m_game->PlaySE(8);
                    m_portraitAngle[side] = 40;
                    m_held[side] = 1;
                } else if (m_game->m_inputX[side] < 0) {
                    m_cursorX[side] = (m_cursorX[side] + 2) % 3;
                    m_game->PlaySE(8);
                    m_portraitAngle[side] = 40;
                    m_held[side] = 1;
                } else if (m_game->m_inputX[side] > 0) {
                    m_cursorX[side] = (m_cursorX[side] + 1) % 3;
                    m_game->PlaySE(8);
                    m_portraitAngle[side] = 40;
                    m_held[side] = 1;
                }
                m_charId[side] = m_grid[(m_cursorX[side] + m_cursorY[side] * 3)];
            } else if (m_game->m_inputX[side] == 0 && m_game->m_inputY[side] == 0) {
                m_held[side] = 0;
            }
            if (m_game->m_extraChars == 0 && (m_charId[side] == 19 || m_charId[side] == 20 || m_charId[side] == 21 || m_charId[side] == 23)) {
                m_game->m_pressA[side] = 0;
            }
            if (m_game->m_extraChars == -1 && (m_charId[side] == 12 || m_charId[side] == 13 || m_charId[side] == 14 || m_charId[side] == 15)) {
                m_game->m_pressA[side] = 0;
            }
            if (m_game->m_pressA[side] != 0 && m_game->m_inputY[side] == 0 && m_game->m_inputX[side] == 0) {
                if (m_state[(1 - side)] < 7 && m_state[(1 - side)] > 0 && m_paletteIndex[0] == m_paletteIndex[1] && m_charId[0] == m_charId[1]) {
                    m_paletteIndex[side]++;
                    if (m_paletteIndex[side] >= 6) {
                        m_paletteIndex[side] = 0;
                    }
                }
                m_game->PlaySE(6);
                if (side == 0) {
                    CreateCharacter(m_player1Ref, m_player2Ref, 0);
                } else {
                    CreateCharacter(m_player2Ref, m_player1Ref, 1);
                }
                m_state[side] = 1;
                m_portraitAngle[side] = 90;
            }
            break;
        case 1:
            m_anim[side] = -2;
            m_portraitOffset[side] = (int)((cos(m_portraitAngle[side] / 57.29579143313326) + 1.0) * 300.0);
            m_portraitAngle[side] = m_portraitAngle[side] + 5;
            if (m_portraitAngle[side] > 180) {
                m_state[side] = 3;
                m_game->PlaySE(m_charId[side] + 40);
            }
            if (m_game->m_pressB[side] != 0) {
                m_state[side] = 2;
                m_randomTime[side] = 0;
            }
            break;
        case 2:
            if (m_portraitAngle[side] >= 90) {
                m_portraitOffset[side] = (int)((cos(m_portraitAngle[side] / 57.29579143313326) + 1.0) * 300.0);
                m_portraitAngle[side] = m_portraitAngle[side] - 5;
            } else {
                m_state[side] = 0;
            }
            break;
        case 3:
            m_game->m_editColor[side] = m_game->m_inputY[side] > 0;
            if (m_held[side] == 0 && m_game->m_inputX[side] != 0) {
                m_game->PlaySE(8);
                m_paletteIndex[side] += m_game->m_inputX[side];
                if (m_paletteIndex[side] >= 6) {
                    m_paletteIndex[side] = 0;
                } else if (m_paletteIndex[side] < 0) {
                    m_paletteIndex[side] = 5;
                }
                if (m_state[(1 - side)] > 0 && m_paletteIndex[0] == m_paletteIndex[1] && m_charId[0] == m_charId[1]) {
                    m_paletteIndex[side] += m_game->m_inputX[side];
                    if (m_paletteIndex[side] >= 6) {
                        m_paletteIndex[side] = 0;
                    } else if (m_paletteIndex[side] < 0) {
                        m_paletteIndex[side] = 5;
                    }
                }
                SetPortraitPalette(side);
            }
            if (m_game->m_pressA[side] != 0 || m_game->m_pressD[side] != 0) {
                if (m_game->m_pressD[side] != 0) {
                    m_game->m_editColor[side] = 1;
                }
                m_players[side]->m_paletteIndex = m_paletteIndex[side];
                m_game->PlaySE(6);
                m_state[side] = 6;
                if (m_game->m_gameMode == 0 || m_game->m_gameMode == 2) {
                    CScene::FadeOut(m_palette, 0, 0, 50);
                    m_enter = 2;
                    m_game->m_arcadeMatch = 1;
                    m_game->m_beatenChars = 0;
                    m_game->m_playedStages = 0;
                    return 2;
                }
            }
            if (m_game->m_pressB[side] != 0) {
                m_state[side] = 2;
            }
            break;
        case 4:
            if (m_state[(1 - side)] == 4) {
                if (m_randomTime[0] > 0) {
                    m_randomTime[0]--;
                    if (m_randomTime[0] == 0) {
                        if (m_game->m_extraChars == 0 && m_game->m_stage >= 13 && m_game->m_stage <= 16) {
                            m_randomTime[0] = rand() % 23 + 1;
                        }
                        if (m_game->m_extraChars == -1 && m_game->m_stage >= 18 && m_game->m_stage <= 22) {
                            m_randomTime[0] = rand() % 23 + 1;
                        }
                    }
                    if (m_randomTime[0] == 0) {
                        m_game->PlaySE(6);
                        LoadStagePicture();
                        CScene::FadeOut(m_palette, 0, 0, 50);
                        m_enter = 2;
                        m_game->m_arcadeMatch = 1;
                        m_game->m_beatenChars = 0;
                        m_game->m_playedStages = 0;
                        return 2;
                    }
                    m_game->m_stage++;
                    if (m_game->m_stage >= 23) {
                        m_game->m_stage = 0;
                    }
                } else {
                    if (m_game->m_inputY[side] > 0 || m_game->m_inputX[side] > 0) {
                        m_game->PlaySE(8);
                        m_state[0] = 10;
                        m_state[1] = 10;
                    } else if (m_game->m_inputX[side] < 0 || m_game->m_inputY[side] < 0) {
                        m_game->PlaySE(8);
                        m_state[0] = 9;
                        m_state[1] = 9;
                    }
                    if (m_game->m_extraChars == 0 && m_game->m_stage >= 13 && m_game->m_stage <= 16) {
                        m_game->m_pressA[side] = 0;
                    }
                    if (m_game->m_extraChars == -1 && m_game->m_stage >= 18 && m_game->m_stage <= 22) {
                        m_game->m_pressA[side] = 0;
                    }
                    if (m_game->m_pressA[side] != 0) {
                        m_game->PlaySE(6);
                        CScene::FadeOut(m_palette, 0, 0, 50);
                        m_enter = 2;
                        m_game->m_arcadeMatch = 1;
                        m_game->m_beatenChars = 0;
                        m_game->m_playedStages = 0;
                        return 2;
                    }
                }
                if (m_game->m_pressC[side] != 0 && m_randomTime[0] == 0 && 1) {
                    m_randomTime[0] = rand() % 23 + 60;
                }
            }
            if (m_game->m_pressB[side] != 0) {
                m_state[side] = 8;
                m_state[(1 - side)] = 8;
                m_randomTime[0] = 0;
                m_randomTime[1] = 0;
            }
        }
        if (m_state[0] == 0 && m_game->m_pressB[0] != 0 && m_game->m_isCpu[0] == 0 || m_state[1] == 0 && m_game->m_pressB[1] != 0 && m_game->m_isCpu[1] == 0) {
#ifdef EFZ_NATIVE
            // In a network match B doesn't go back to the title: EfzRevival stores 0 here
            // instead (efz.exe 0x754c1a).
            m_leave = !efz::g_netplay.active;
#else
            m_leave = 1;
#endif
        }
        *(char*)&m_held[side] = m_game->m_inputX[side] != 0 || m_game->m_inputY[side] != 0;
    }
    if (m_state[0] == 6 && m_state[1] == 6) {
        if (m_portraitAngle[0] >= 90) {
            m_portraitOffset[0] = (int)((cos(m_portraitAngle[0] / 57.29579143313326) + 1.0) * 300.0);
            m_portraitOffset[1] = (int)((cos(m_portraitAngle[1] / 57.29579143313326) + 1.0) * 300.0);
            m_portraitAngle[0] = m_portraitAngle[0] - 5;
            m_portraitAngle[1] = m_portraitAngle[1] - 5;
        } else if (m_anim[3] < 60) {
            m_gridY = (int)(((cos(m_anim[3] / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            m_anim[3] += 3;
        } else {
            m_state[0] = 7;
            m_state[1] = 7;
            if (m_game->m_stage < 10) {
                strcpy(path, "system\\stage\\0");
            } else {
                strcpy(path, "system\\stage\\");
            }
            _itoa(m_game->m_stage, digits, 10);
            strcat(path, (const char*)digits);
            if (1) {
                strcat(path, ".dat");
                m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)path, 0, 191);
                m_graphics->LoadPaletteDat(m_palette, "system\\stage\\all.dat", 0, 175, 16);
                m_graphics->LoadPaletteDat(m_palette, (const char*)path, 0, 191, 64);
            } else {
                strcat(path, ".bmp");
                m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)path, 191);
                m_graphics->LoadPaletteBmp(m_palette, "system\\stage\\all.bmp", 0, 175, 80);
                m_graphics->LoadPaletteBmp(m_palette, (const char*)path, 0, 191, 64);
            }
            m_colorKeys[3] = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_stagePicture));
            m_graphics->SetPaletteRange(m_palette, 0xaf, 0x50);
        }
    } else if (m_state[0] == 6) {
        if (m_game->m_pressB[0] != 0) {
            m_state[0] = 2;
        }
    } else if (m_state[1] == 6) {
        if (m_game->m_pressB[1] != 0) {
            m_state[1] = 2;
        }
    } else if (m_state[0] == 7) {
        if (m_anim[4] < 85) {
            m_anim[4] += 5;
        } else {
            m_anim[4] = 90;
            m_state[0] = 4;
            m_state[1] = 4;
        }
    } else if (m_state[0] == 8 || m_state[1] == 8) {
        if (m_anim[4] > 0) {
            m_anim[4] -= 4;
        } else if (m_anim[3] > 0) {
            m_gridY = (int)(((cos(m_anim[3] / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            m_anim[3] -= 3;
        } else {
            m_state[0] = 0;
            m_state[1] = 0;
        }
    }
    if (m_state[0] == 5 || m_state[1] == 5) {
        if (m_bgSlideTime > 0) {
            m_bgScroll = (int)(cos(m_bgSlideTime * 1.5 / 57.29579143313326) * 240.0);
            m_bgSlideTime--;
        }
        if (m_anim[3] > 0) {
            m_gridY = (int)(((cos(m_anim[3] / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            m_anim[3]--;
            if (m_anim[3] == 0) {
                m_state[0] = 0;
                m_state[1] = 0;
            }
        }
    }
    m_p1BarOffset = m_p1BarOffset - m_anim[0];
    if (m_p1BarOffset < 0.0) {
        m_p1BarOffset = 0.0;
    }
    if (m_p1BarOffset > 50.0) {
        m_p1BarOffset = 50.0;
    }
    m_p2BarOffset = m_p2BarOffset - m_anim[1];
    if (m_p2BarOffset < 0.0) {
        m_p2BarOffset = 0.0;
    }
    if (m_p2BarOffset > 50.0) {
        m_p2BarOffset = 50.0;
    }
    m_barScroll++;
    if (m_barScroll >= 240.0) {
        m_barScroll -= 240.0;
    }
    Draw();
    if (m_state[0] == 9) {
        if (m_anim[5] < 90) {
            m_anim[5] += 10;
        } else {
            m_anim[5] = 0;
            m_state[0] = 4;
            m_state[1] = 4;
            m_game->m_stage++;
            if (m_game->m_extraChars == 0 && m_game->m_stage == 13) {
                m_game->m_stage = 17;
            }
            if (m_game->m_extraChars == -1 && m_game->m_stage == 18) {
                m_game->m_stage = 0;
            }
            if (m_game->m_stage >= 23) {
                m_game->m_stage = 0;
            }
            LoadStagePicture();
        }
    } else if (m_state[0] == 10) {
        if (m_anim[5] < 90) {
            m_anim[5] += 10;
        } else {
            m_anim[5] = 0;
            m_state[0] = 4;
            m_state[1] = 4;
            m_game->m_stage--;
            if (m_game->m_stage < 0) {
                m_game->m_stage = 22;
            }
            if (m_game->m_extraChars == 0 && m_game->m_stage == 16) {
                m_game->m_stage = 12;
            }
            if (m_game->m_extraChars == -1 && m_game->m_stage == 22) {
                m_game->m_stage = 17;
            }
            LoadStagePicture();
        }
    }
    return 1;
}

void CScene1::Draw()
{
    int prevRow; // the same while it scrolls to the previous one (row -1 comes in)
    int prevSkipped;
    int nextRow; // the same while the list scrolls to the next stage
    int nextSkipped;
    int randomRow; // the same while the random stage spins
    int randomSkipped;
    int row; // row of the stage list: 0 the chosen stage, then the ones after it
    int skipped; // hidden stages passed over so far
    RECT dst;
    RECT src;

    src = MakeRect(0, (int)m_bgScroll, 320, 240);
    dst = MakeRect(0, 0, 320, 240);
    m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_bgSurface), src, 0, 0);
    if (m_game->m_isCpu[0] != 1 || m_game->m_gameMode != 0) {
        src = MakeRect(133, 128, 22, 240);
        dst = MakeRect(5 - (int)m_p1BarOffset, (int)m_barScroll, 22, 240);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(5 - (int)m_p1BarOffset, (int)m_barScroll - 240, 22, 240);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    }
    if (m_game->m_isCpu[1] != 1 || m_game->m_gameMode != 0) {
        src = MakeRect(165, 128, 22, 240);
        dst = MakeRect((int)m_p2BarOffset + 292, 0 - (int)m_barScroll, 22, 240);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect((int)m_p2BarOffset + 292, 0 - (int)m_barScroll + 240, 22, 240);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    }
    if (m_state[0] > 0) {
        if (m_game->m_gameMode != 0 && m_game->m_gameMode != 2 || m_game->m_isCpu[0] != 1) {
            src = MakeRect(0, 0, 320, 240);
            dst = MakeRect(-80 - m_portraitOffset[0] + m_portraitShift[(m_cursorX[0] + m_cursorY[0] * 3)], 0, 320, 240);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_portraits[0]), src, m_colorKeys[0], 1);
            src = MakeRect(192, 9, 122, 95);
            dst = MakeRect(0 - m_portraitOffset[0] / 2, 137, 122, 95);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
            src = MakeRect(0, (m_namePlate[m_charId[0]] << 5) + 256, 122, 32);
            dst = MakeRect(0 - m_portraitOffset[0] / 2, 192, 122, 32);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
        if (m_game->m_editColor[0] != 0) {
            src = MakeRect(0, 224, 128, 32);
            dst = MakeRect(-16 - m_portraitOffset[0] / 2, 5, 128, 32);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
    }
    if (m_state[1] > 0) {
        if (m_game->m_gameMode != 0 && m_game->m_gameMode != 2 || m_game->m_isCpu[1] != 1) {
            src = MakeRect(0, 0, 320, 240);
            dst = MakeRect(m_portraitOffset[1] + 80 - m_portraitShift[(m_cursorX[1] + m_cursorY[1] * 3)], 0, 320, 240);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_portraits[1]), src, m_colorKeys[1], 0);
            src = MakeRect(198, 137, 122, 95);
            dst = MakeRect(m_portraitOffset[1] / 2 + 198, 137, 122, 95);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
            src = MakeRect(198, (m_namePlate[m_charId[1]] << 5) + 256, 122, 32);
            dst = MakeRect(m_portraitOffset[1] / 2 + 198, 192, 122, 32);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
        if (m_game->m_editColor[1] != 0) {
            src = MakeRect(0, 224, 128, 32);
            dst = MakeRect(m_portraitOffset[1] / 2 + 207, 5, 128, 32);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
    }
    src = MakeRect(0, 0, 128, 217);
    dst = MakeRect(96, (int)m_gridY, 128, 217);
    m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    src = MakeRect(138, 96, 41, 25);
    if (m_game->m_extraChars == 0) {
        dst = MakeRect(103, (int)m_gridY + 114, 41, 25);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(143, (int)m_gridY + 114, 41, 25);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(183, (int)m_gridY + 114, 41, 25);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(177, (int)m_gridY + 192, 41, 25);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    }
    if (m_game->m_extraChars == -1) {
        dst = MakeRect(97, (int)m_gridY + 140, 41, 25);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(137, (int)m_gridY + 140, 41, 25);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(143, (int)m_gridY + 166, 41, 25);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(183, (int)m_gridY + 166, 41, 25);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    }
    if (m_gridY == 0.0) {
        if (m_charId[0] == m_charId[1] && (m_game->m_isCpu[0] != 1 || m_game->m_gameMode != 0) && (m_game->m_isCpu[1] != 1 || m_game->m_gameMode != 0)) {
            src = MakeRect(129, 64, 63, 24);
            dst = MakeRect(m_cursorX[0] * 40 + 88 + (m_cursorY[0] % 2 == 0) * 6, m_cursorY[0] * 26 + 10, 63, 24);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        } else {
            if (m_game->m_isCpu[1] != 1 || m_game->m_gameMode != 0) {
                src = MakeRect(129, 32, 63, 24);
                dst = MakeRect(m_cursorX[1] * 40 + 88 + (m_cursorY[1] % 2 == 0) * 6, m_cursorY[1] * 26 + 10, 63, 24);
                m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
            }
            if (m_game->m_isCpu[0] != 1 || m_game->m_gameMode != 0) {
                src = MakeRect(129, 0, 63, 24);
                dst = MakeRect(m_cursorX[0] * 40 + 88 + (m_cursorY[0] % 2 == 0) * 6, m_cursorY[0] * 26 + 10, 63, 24);
                m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
            }
        }
    }
    if ((m_state[0] == 7 || m_state[0] == 8 || m_state[0] == 4) && m_game->m_gameMode != 0 && m_game->m_gameMode != 2) {
        if (m_randomTime[0] == 0) {
            skipped = 0;
            row = 1;
            for (; row <= 7; row++) {
                while (m_stageHidden[(m_game->m_stage + row + skipped) % 23] != 0) {
                    skipped++;
                }
                src = MakeRect(0, (m_game->m_stage + row + skipped) % 0x17 << 5, 160, 32);
                dst = MakeRect(row * 11 + 170, 205 - row * 33 + (int)((double)(row * 33 + 190) * cos(m_anim[4] / 57.29579143313326)), 160, 32);
                m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
            }
            src = MakeRect(160, m_game->m_stage << 5, 160, 32);
            dst = MakeRect(170, (int)(cos(m_anim[4] / 57.29579143313326) * 190.0) + 205, 160, 32);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
            src = MakeRect(1, 0, 195, 222);
            dst = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 195, 222);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stagePicture), src, m_colorKeys[3], 0);
        } else {
            randomSkipped = 0;
            randomRow = 0;
            for (; randomRow <= 8; randomRow++) {
                while (m_stageHidden[(m_game->m_stage + randomRow + randomSkipped) % 23] != 0) {
                    randomSkipped++;
                }
                src = MakeRect(0, (m_game->m_stage + randomRow + randomSkipped) % 0x17 << 5, 160, 32);
                dst = MakeRect(randomRow * 11 + 170, 205 - randomRow * 33 + (int)((double)(randomRow * 33 + 190) * cos(m_anim[4] / 57.29579143313326)), 160, 32);
                m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
            }
            src = MakeRect(0, 985, 195, 222);
            dst = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 195, 222);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
    } else if (m_state[0] == 9) {
        nextSkipped = 0;
        nextRow = 0;
        for (; nextRow <= 8; nextRow++) {
            while (m_stageHidden[(m_game->m_stage + nextRow + nextSkipped) % 23] != 0) {
                nextSkipped++;
            }
            src = MakeRect(0, (m_game->m_stage + nextRow + nextSkipped) % 0x17 << 5, 160, 32);
            dst = MakeRect(nextRow * 11 + 170 - (int)(sin(m_anim[5] / 57.29579143313326) * 11.0), 205 - nextRow * 33 + (int)((double)(nextRow * 33 + 190) * cos(m_anim[4] / 57.29579143313326)) + (int)(sin(m_anim[5] / 57.29579143313326) * 33.0), 160, 32);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
        }
        src = MakeRect(1, 0, 195, 222);
        dst = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 195, 222);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stagePicture), src, m_colorKeys[3], 0);
    } else if (m_state[0] == 10) {
        prevSkipped = 0;
        prevRow = 0;
        for (; prevRow <= 8; prevRow++) {
            while (m_stageHidden[(m_game->m_stage + prevRow + 23 + prevSkipped) % 23] != 0) {
                prevSkipped++;
            }
            src = MakeRect(0, (m_game->m_stage + prevRow + 23 + prevSkipped) % 0x17 << 5, 160, 32);
            dst = MakeRect(prevRow * 11 + 170 + (int)(sin(m_anim[5] / 57.29579143313326) * 11.0), 205 - prevRow * 33 + (int)((double)(prevRow * 33 + 190) * cos(m_anim[4] / 57.29579143313326)) - (int)(sin(m_anim[5] / 57.29579143313326) * 33.0), 160, 32);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
        }
        prevRow = -1;
        prevSkipped = 0;
        while (m_stageHidden[(m_game->m_stage + prevRow + 23 + prevSkipped) % 23] != 0) {
            prevSkipped--;
        }
        src = MakeRect(0, (m_game->m_stage + prevRow + 23 + prevSkipped) % 0x17 << 5, 160, 32);
        dst = MakeRect(prevRow * 11 + 170 + (int)(sin(m_anim[5] / 57.29579143313326) * 11.0), 205 - prevRow * 33 + (int)((double)(prevRow * 33 + 190) * cos(m_anim[4] / 57.29579143313326)) - (int)(sin(m_anim[5] / 57.29579143313326) * 33.0), 160, 32);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
        src = MakeRect(1, 0, 195, 222);
        dst = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 195, 222);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stagePicture), src, m_colorKeys[3], 0);
    }
    m_graphics->Flip();
}

void CScene1::CreateCharacter(PTR32(CPlayer)* player, PTR32(CPlayer)* opponent, char side)
{
    char path[40];

    switch (m_charId[side]) {
    case 0:
        *player = new CNanase(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 1:
        *player = new CAyu(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 2:
        *player = new CMai(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 3:
        *player = new CMakoto(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 4:
        *player = new CAkane(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 5:
        *player = new CMayu(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 6:
        *player = new CNagamori(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 7:
        *player = new CMisaki(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 8:
        *player = new CShiori(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 9:
        *player = new CSayuri(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xa:
        *player = new CNayuki(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xb:
        *player = new CMio(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xc:
        *player = new CEXNanase(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xd:
        *player = new CKaori(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xe:
        *player = new CIkumi(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0xf:
        *player = new CMishio(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x10:
        *player = new CAkiko(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x11:
        *player = new CNayukiB(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x12:
        *player = new CMizukaB(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x13:
        *player = new CKanna(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x14:
        *player = new CKano(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x15:
        *player = new CMinagi(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x16:
        *player = new CNayuki(opponent, m_game, m_graphics, m_input, m_sound, side);
        break;
    case 0x17:
        *player = new CMisuzu(opponent, m_game, m_graphics, m_input, m_sound, side);
    }
    (*player)->m_charId = m_charId[side];
    m_players[side] = *player;
    (*player)->m_cpu = m_game->m_isCpu[side];
    if (1) {
        strcpy(path, "system\\");
        strcat(path, (*player)->m_name);
        strcat(path, "\\");
        strcat(path, (*player)->m_name);
        strcat(path, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_portraits[side], (const char*)path, 0, side * 40 + 175);
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, m_paletteIndex[side] * 40, side * 40 + 175, 40);
    } else {
        strcpy(path, "system\\");
        strcat(path, (*player)->m_name);
        strcat(path, "\\");
        strcat(path, (*player)->m_name);
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_portraits[side], (const char*)path, side * 40 + 175);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, m_paletteIndex[side] * 40, side * 40 + 175, 40);
    }
    m_graphics->SetPalette(m_palette);
    m_colorKeys[side] = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_portraits[side]));
}

void CScene1::LoadStagePicture()
{
    char digits[8];
    char path[40];

    if (m_game->m_stage < 10) {
        strcpy(path, "system\\stage\\0");
    } else {
        strcpy(path, "system\\stage\\");
    }
    _itoa(m_game->m_stage, digits, 10);
    strcat(path, (const char*)digits);
    if (1) {
        strcat(path, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)path, 0, 191);
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, 0, 191, 64);
    } else {
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)path, 191);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, 0, 191, 64);
    }
    m_colorKeys[3] = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_stagePicture));
    m_graphics->SetPaletteRange(m_palette, 0xaf, 0x50);
}

void CScene1::SetPortraitPalette(char side)
{
    char path[40];

    if (1) {
        strcpy(path, "system\\");
        strcat(path, m_players[side]->m_name);
        strcat(path, "\\");
        strcat(path, m_players[side]->m_name);
        strcat(path, ".dat");
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, m_paletteIndex[side] * 40, side * 40 + 175, 40);
    } else {
        strcpy(path, "system\\");
        strcat(path, m_players[side]->m_name);
        strcat(path, "\\");
        strcat(path, m_players[side]->m_name);
        strcat(path, ".bmp");
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, m_paletteIndex[side] * 40, side * 40 + 175, 40);
    }
    m_graphics->SetPaletteRange(m_palette, side * 0x28 + 0xaf, 0x28);
}

void CScene1::HandleKeys()
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
    if ((keys[59] & 0x80) != 0) {
        m_input->LoadBindings();
    }
    if ((keys[60] & 0x80) != 0 && (BYTE)ReadConfigByte(0x98) > 0) {
        m_input->LoadPreset(1);
    }
    if ((keys[61] & 0x80) != 0 && (BYTE)ReadConfigByte(0x98) > 0) {
        m_input->LoadPreset(2);
    }
    if ((keys[62] & 0x80) != 0 && (BYTE)ReadConfigByte(0x98) > 0) {
        m_input->LoadPreset(3);
    }
}

void CScene1::Enter()
{
    m_held[0] = 0;
    m_held[1] = 0;
    m_bgScroll = 0.0;
    m_bgSlideTime = 60;
    m_p1BarOffset = 50.0;
    m_anim[0] = 0;
    m_p2BarOffset = 50.0;
    m_anim[1] = 0;
    m_barScroll = 0.0;
    m_anim[2] = 0;
    m_gridY = -480.0;
    m_anim[3] = 60;
    m_anim[4] = 0;
    m_anim[5] = 0;
    m_portraitOffset[0] = 300;
    m_portraitOffset[1] = 300;
    m_portraitAngle[0] = 180;
    m_portraitAngle[1] = 180;
    m_state[0] = 5;
    m_state[1] = 5;
    m_randomTime[0] = 0;
    m_randomTime[1] = 0;
#ifdef EFZ_NATIVE
    // In a network match each player's colour stays from one character select to the
    // next: EfzRevival skips these two stores (efz.exe 0x7599ed).
    if (!efz::g_netplay.active) {
        m_paletteIndex[0] = 0;
        m_paletteIndex[1] = 0;
    }
#else
    m_paletteIndex[0] = 0;
    m_paletteIndex[1] = 0;
#endif
    m_game->m_continued = 0;
    m_game->m_continuedAt = 0;
    m_game->m_editColor[0] = 0;
    m_game->m_editColor[1] = 0;
    if (m_game->m_gameMode < 5) {
        if (1) {
            m_graphics->LoadPaletteDat(m_palette, "system\\chr_sel_bg.dat", 0, 1, 48);
        } else {
            m_graphics->LoadPaletteBmp(m_palette, "system\\chr_sel_bg.bmp", 0, 1, 48);
        }
        if (m_game->m_gameMode == 0 || m_game->m_gameMode == 2) {
            if (m_game->m_isCpu[0] == 1) {
                m_state[0] = 4;
                m_paletteIndex[0] = -1;
            } else {
                m_state[1] = 4;
                m_paletteIndex[1] = -1;
            }
        }
        m_game->m_replayMode = 0;
    }
    memset((void*)&m_stageHidden[0], 0, 23);
    if (m_game->m_extraChars == 0) {
        m_stageHidden13 = 1;
        m_stageHidden14 = 1;
        m_stageHidden15 = 1;
        m_stageHidden16 = 1;
    } else if (m_game->m_extraChars == -1) {
        m_stageHidden18 = 1;
        m_stageHidden19 = 1;
        m_stageHidden20 = 1;
        m_stageHidden21 = 1;
        m_stageHidden22 = 1;
    }
    if ((m_game->m_gameMode == 5 || m_game->m_gameMode == 1) && m_game->m_extraChars != 0) {
        m_game->PlayMusic(1);
    } else {
        m_game->PlayMusic(0);
    }
    Draw();
    CScene::FadeIn(m_palette, 1);
    m_enter = 0;
}
