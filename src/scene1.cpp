// CScene1 (0x753260-0x759f2f), scene 1: character and stage select
// (system\chr_sel_bg, chr_sel_ob, system\stage\). The inline methods of CScene follow
// it: its constructor and the two palette fades (0x759c10-0x759f2f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene1::CScene1(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\chr_sel_bg.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_obSurface, "system\\chr_sel_ob.dat", 0, 1);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_stageNames, "system\\stage\\all.dat", 0, 0xaf);
        m_graphics->LoadPaletteDat(m_palette, "system\\chr_sel_ob.dat", 0, 1, 0xae);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_bgSurface, "system\\chr_sel_bg.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_obSurface, "system\\chr_sel_ob.bmp", 1);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_stageNames, "system\\stage\\all.bmp", 0xaf);
        m_graphics->LoadPaletteBmp(m_palette, "system\\chr_sel_ob.bmp", 0, 1, 0xae);
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
    m_bgSlideTime = 0x3c;
    m_p1BarOffset = 50.0;
    m_anim[0] = 0;
    m_p2BarOffset = 50.0;
    m_anim[1] = 0;
    m_barScroll = 0.0;
    m_anim[2] = 0;
    m_gridY = -240.0;
    m_anim[3] = 0x3c;
    m_anim[4] = 0;
    m_anim[5] = 0;
    m_portraitOffset[0] = 0x12c;
    m_portraitOffset[1] = 0x12c;
    m_portraitAngle[0] = 0xb4;
    m_portraitAngle[1] = 0xb4;
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
    m_grid[5] = 0xb;
    m_grid[6] = 1;
    m_grid[7] = 0xa;
    m_grid[8] = 3;
    m_grid[9] = 8;
    m_grid[0xa] = 2;
    m_grid[0xb] = 9;
    m_grid[0xc] = 0x17;
    m_grid[0xd] = 0x14;
    m_grid[0xe] = 0x15;
    m_grid[0xf] = 0xe;
    m_grid[0x10] = 0xc;
    m_grid[0x11] = 0x12;
    m_grid[0x12] = 0x11;
    m_grid[0x13] = 0xf;
    m_grid[0x14] = 0xd;
    m_grid[0x15] = 0x10;
    m_grid[0x16] = -1;
    m_grid[0x17] = 0x13;
    m_portraitShift[0] = -0x28;
    m_portraitShift[1] = -0xa;
    m_portraitShift[2] = -5;
    m_portraitShift[3] = 0;
    m_portraitShift[4] = -5;
    m_portraitShift[5] = -5;
    m_portraitShift[6] = -0x1e;
    m_portraitShift[7] = -0x1e;
    m_portraitShift[8] = -0x14;
    m_portraitShift[9] = -0xa;
    m_portraitShift[0xa] = -0x28;
    m_portraitShift[0xb] = -5;
    m_portraitShift[0xc] = -0x32;
    m_portraitShift[0xd] = 0;
    m_portraitShift[0xe] = -0xf;
    m_portraitShift[0xf] = -0xf;
    m_portraitShift[0x10] = -0x14;
    m_portraitShift[0x11] = -0x14;
    m_portraitShift[0x12] = -0x2d;
    m_portraitShift[0x13] = 0xa;
    m_portraitShift[0x14] = -0x14;
    m_portraitShift[0x15] = 0;
    m_portraitShift[0x16] = 0;
    m_portraitShift[0x17] = -0x14;
    m_namePlate[0] = 5;
    m_namePlate[1] = 7;
    m_namePlate[2] = 0xb;
    m_namePlate[3] = 9;
    m_namePlate[4] = 0;
    m_namePlate[5] = 4;
    m_namePlate[6] = 2;
    m_namePlate[7] = 1;
    m_namePlate[8] = 0xa;
    m_namePlate[9] = 0xc;
    m_namePlate[0xa] = 8;
    m_namePlate[0xb] = 3;
    m_namePlate[0xc] = 0x15;
    m_namePlate[0xd] = 0xd;
    m_namePlate[0xe] = 0x14;
    m_namePlate[0xf] = 0xe;
    m_namePlate[0x10] = 0xf;
    m_namePlate[0x11] = 8;
    m_namePlate[0x12] = 6;
    m_namePlate[0x13] = 0x13;
    m_namePlate[0x14] = 0x11;
    m_namePlate[0x15] = 0x12;
    m_namePlate[0x16] = -1;
    m_namePlate[0x17] = 0x10;
    m_namePlate[0x18] = 6;
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
    char v38[8];
    char v30[40];
    int v4;

    if (m_enter > 0) {
        Enter();
    }
    if (m_leave > 0) {
        CScene::FadeOut(m_palette, 0, 0, 0x64);
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
    v4 = 0;
    for (; v4 < 2; v4++) {
        if (m_game->m_gameMode == 0 && m_game->m_isCpu[v4] == 1) {
            m_game->m_inputX[v4] = 0;
            m_game->m_inputY[v4] = 0;
            m_game->m_pressA[v4] = 0;
            m_game->m_pressB[v4] = 0;
            m_game->m_pressC[v4] = 0;
            m_game->m_pressD[v4] = 0;
        }
        if (m_game->m_isCpu[v4] == 1 && (m_game->m_gameMode == 1 || m_game->m_gameMode == 3 || m_game->m_gameMode == 5)) {
            if (m_state[v4] < 4 && m_state[(1 - v4)] == 6) {
                m_game->m_inputX[v4] = m_game->m_inputX[(1 - v4)];
                m_game->m_inputY[v4] = m_game->m_inputY[(1 - v4)];
                m_game->m_pressA[v4] = m_game->m_pressA[(1 - v4)];
                m_game->m_pressC[v4] = m_game->m_pressC[(1 - v4)];
                m_game->m_pressD[v4] = m_game->m_pressD[(1 - v4)];
                m_game->m_inputX[(1 - v4)] = 0;
                m_game->m_inputY[(1 - v4)] = 0;
                m_game->m_pressA[(1 - v4)] = 0;
                m_game->m_pressC[(1 - v4)] = 0;
                m_game->m_pressD[(1 - v4)] = 0;
            }
            m_game->m_pressB[v4] = m_game->m_pressB[(1 - v4)];
        }
    }
    v4 = 0;
    for (; v4 < 2; v4++) {
        switch (m_state[v4]) {
        case 0:
            m_game->m_editColor[v4] = 0;
            m_anim[v4] = 2;
            if (m_game->m_pressC[v4] != 0 && m_randomTime[v4] == 0 || m_game->m_pressA[v4] != 0 && m_cursorX[v4] == 1 && m_cursorY[v4] == 7) {
                m_randomTime[v4] = 0x3c;
            }
            if (m_randomTime[v4] > 0) {
                m_randomTime[v4]--;
                m_game->m_inputX[v4] = rand() % 3 - 1;
                m_game->m_inputY[v4] = rand() % 2;
                m_game->m_pressA[v4] = 0;
                m_held[v4] = 0;
                if (m_randomTime[v4] == 0) {
                    m_charId[v4] = m_grid[(m_cursorX[v4] + m_cursorY[v4] * 3)];
                    if (m_charId[v4] < 0) {
                        m_randomTime[v4]++;
                    }
                    if (m_game->m_extraChars == 0 && (m_charId[v4] == 0x13 || m_charId[v4] == 0x14 || m_charId[v4] == 0x15 || m_charId[v4] == 0x17)) {
                        m_randomTime[v4]++;
                    }
                    if (m_game->m_extraChars == -1 && (m_charId[v4] == 0xc || m_charId[v4] == 0xd || m_charId[v4] == 0xe || m_charId[v4] == 0xf)) {
                        m_randomTime[v4]++;
                    }
                }
                if (m_randomTime[v4] == 0) {
                    m_game->m_inputX[v4] = 0;
                    m_game->m_inputY[v4] = 0;
                    m_game->m_pressA[v4] = 1;
                }
            }
            if (m_held[v4] == 0) {
                if (m_game->m_inputY[v4] < 0) {
                    m_cursorY[v4] = (m_cursorY[v4] + 7) % 8;
                    m_game->PlaySE(8);
                    m_held[v4] = 1;
                } else if (m_game->m_inputY[v4] > 0) {
                    m_cursorY[v4] = (m_cursorY[v4] + 1) % 8;
                    m_game->PlaySE(8);
                    m_portraitAngle[v4] = 0x28;
                    m_held[v4] = 1;
                } else if (m_game->m_inputX[v4] < 0) {
                    m_cursorX[v4] = (m_cursorX[v4] + 2) % 3;
                    m_game->PlaySE(8);
                    m_portraitAngle[v4] = 0x28;
                    m_held[v4] = 1;
                } else if (m_game->m_inputX[v4] > 0) {
                    m_cursorX[v4] = (m_cursorX[v4] + 1) % 3;
                    m_game->PlaySE(8);
                    m_portraitAngle[v4] = 0x28;
                    m_held[v4] = 1;
                }
                m_charId[v4] = m_grid[(m_cursorX[v4] + m_cursorY[v4] * 3)];
            } else if (m_game->m_inputX[v4] == 0 && m_game->m_inputY[v4] == 0) {
                m_held[v4] = 0;
            }
            if (m_game->m_extraChars == 0 && (m_charId[v4] == 0x13 || m_charId[v4] == 0x14 || m_charId[v4] == 0x15 || m_charId[v4] == 0x17)) {
                m_game->m_pressA[v4] = 0;
            }
            if (m_game->m_extraChars == -1 && (m_charId[v4] == 0xc || m_charId[v4] == 0xd || m_charId[v4] == 0xe || m_charId[v4] == 0xf)) {
                m_game->m_pressA[v4] = 0;
            }
            if (m_game->m_pressA[v4] != 0 && m_game->m_inputY[v4] == 0 && m_game->m_inputX[v4] == 0) {
                if (m_state[(1 - v4)] < 7 && m_state[(1 - v4)] > 0 && m_paletteIndex[0] == m_paletteIndex[1] && m_charId[0] == m_charId[1]) {
                    m_paletteIndex[v4]++;
                    if (m_paletteIndex[v4] >= 6) {
                        m_paletteIndex[v4] = 0;
                    }
                }
                m_game->PlaySE(6);
                if (v4 == 0) {
                    CreateCharacter(m_player1Ref, m_player2Ref, 0);
                } else {
                    CreateCharacter(m_player2Ref, m_player1Ref, 1);
                }
                m_state[v4] = 1;
                m_portraitAngle[v4] = 0x5a;
            }
            break;
        case 1:
            m_anim[v4] = -2;
            m_portraitOffset[v4] = (int)((cos(m_portraitAngle[v4] / 57.29579143313326) + 1.0) * 300.0);
            m_portraitAngle[v4] = m_portraitAngle[v4] + 5;
            if (m_portraitAngle[v4] > 0xb4) {
                m_state[v4] = 3;
                m_game->PlaySE(m_charId[v4] + 0x28);
            }
            if (m_game->m_pressB[v4] != 0) {
                m_state[v4] = 2;
                m_randomTime[v4] = 0;
            }
            break;
        case 2:
            if (m_portraitAngle[v4] >= 0x5a) {
                m_portraitOffset[v4] = (int)((cos(m_portraitAngle[v4] / 57.29579143313326) + 1.0) * 300.0);
                m_portraitAngle[v4] = m_portraitAngle[v4] - 5;
            } else {
                m_state[v4] = 0;
            }
            break;
        case 3:
            m_game->m_editColor[v4] = m_game->m_inputY[v4] > 0;
            if (m_held[v4] == 0 && m_game->m_inputX[v4] != 0) {
                m_game->PlaySE(8);
                m_paletteIndex[v4] += m_game->m_inputX[v4];
                if (m_paletteIndex[v4] >= 6) {
                    m_paletteIndex[v4] = 0;
                } else if (m_paletteIndex[v4] < 0) {
                    m_paletteIndex[v4] = 5;
                }
                if (m_state[(1 - v4)] > 0 && m_paletteIndex[0] == m_paletteIndex[1] && m_charId[0] == m_charId[1]) {
                    m_paletteIndex[v4] += m_game->m_inputX[v4];
                    if (m_paletteIndex[v4] >= 6) {
                        m_paletteIndex[v4] = 0;
                    } else if (m_paletteIndex[v4] < 0) {
                        m_paletteIndex[v4] = 5;
                    }
                }
                SetPortraitPalette(v4);
            }
            if (m_game->m_pressA[v4] != 0 || m_game->m_pressD[v4] != 0) {
                if (m_game->m_pressD[v4] != 0) {
                    m_game->m_editColor[v4] = 1;
                }
                m_players[v4]->m_paletteIndex = m_paletteIndex[v4];
                m_game->PlaySE(6);
                m_state[v4] = 6;
                if (m_game->m_gameMode == 0 || m_game->m_gameMode == 2) {
                    CScene::FadeOut(m_palette, 0, 0, 0x32);
                    m_enter = 2;
                    m_game->m_arcadeMatch = 1;
                    m_game->m_beatenChars = 0;
                    m_game->m_playedStages = 0;
                    return 2;
                }
            }
            if (m_game->m_pressB[v4] != 0) {
                m_state[v4] = 2;
            }
            break;
        case 4:
            if (m_state[(1 - v4)] == 4) {
                if (m_randomTime[0] > 0) {
                    m_randomTime[0]--;
                    if (m_randomTime[0] == 0) {
                        if (m_game->m_extraChars == 0 && m_game->m_stage >= 0xd && m_game->m_stage <= 0x10) {
                            m_randomTime[0] = rand() % 0x17 + 1;
                        }
                        if (m_game->m_extraChars == -1 && m_game->m_stage >= 0x12 && m_game->m_stage <= 0x16) {
                            m_randomTime[0] = rand() % 0x17 + 1;
                        }
                    }
                    if (m_randomTime[0] == 0) {
                        m_game->PlaySE(6);
                        LoadStagePicture();
                        CScene::FadeOut(m_palette, 0, 0, 0x32);
                        m_enter = 2;
                        m_game->m_arcadeMatch = 1;
                        m_game->m_beatenChars = 0;
                        m_game->m_playedStages = 0;
                        return 2;
                    }
                    m_game->m_stage++;
                    if (m_game->m_stage >= 0x17) {
                        m_game->m_stage = 0;
                    }
                } else {
                    if (m_game->m_inputY[v4] > 0 || m_game->m_inputX[v4] > 0) {
                        m_game->PlaySE(8);
                        m_state[0] = 0xa;
                        m_state[1] = 0xa;
                    } else if (m_game->m_inputX[v4] < 0 || m_game->m_inputY[v4] < 0) {
                        m_game->PlaySE(8);
                        m_state[0] = 9;
                        m_state[1] = 9;
                    }
                    if (m_game->m_extraChars == 0 && m_game->m_stage >= 0xd && m_game->m_stage <= 0x10) {
                        m_game->m_pressA[v4] = 0;
                    }
                    if (m_game->m_extraChars == -1 && m_game->m_stage >= 0x12 && m_game->m_stage <= 0x16) {
                        m_game->m_pressA[v4] = 0;
                    }
                    if (m_game->m_pressA[v4] != 0) {
                        m_game->PlaySE(6);
                        CScene::FadeOut(m_palette, 0, 0, 0x32);
                        m_enter = 2;
                        m_game->m_arcadeMatch = 1;
                        m_game->m_beatenChars = 0;
                        m_game->m_playedStages = 0;
                        return 2;
                    }
                }
                if (m_game->m_pressC[v4] != 0 && m_randomTime[0] == 0 && 1) {
                    m_randomTime[0] = rand() % 0x17 + 0x3c;
                }
            }
            if (m_game->m_pressB[v4] != 0) {
                m_state[v4] = 8;
                m_state[(1 - v4)] = 8;
                m_randomTime[0] = 0;
                m_randomTime[1] = 0;
            }
        }
        if (m_state[0] == 0 && m_game->m_pressB[0] != 0 && m_game->m_isCpu[0] == 0 || m_state[1] == 0 && m_game->m_pressB[1] != 0 && m_game->m_isCpu[1] == 0) {
            m_leave = 1;
        }
        *(char*)&m_held[v4] = m_game->m_inputX[v4] != 0 || m_game->m_inputY[v4] != 0;
    }
    if (m_state[0] == 6 && m_state[1] == 6) {
        if (m_portraitAngle[0] >= 0x5a) {
            m_portraitOffset[0] = (int)((cos(m_portraitAngle[0] / 57.29579143313326) + 1.0) * 300.0);
            m_portraitOffset[1] = (int)((cos(m_portraitAngle[1] / 57.29579143313326) + 1.0) * 300.0);
            m_portraitAngle[0] = m_portraitAngle[0] - 5;
            m_portraitAngle[1] = m_portraitAngle[1] - 5;
        } else if (m_anim[3] < 0x3c) {
            m_gridY = (int)(((cos(m_anim[3] / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            m_anim[3] += 3;
        } else {
            m_state[0] = 7;
            m_state[1] = 7;
            if (m_game->m_stage < 0xa) {
                strcpy(v30, "system\\stage\\0");
            } else {
                strcpy(v30, "system\\stage\\");
            }
            _itoa(m_game->m_stage, v38, 0xa);
            strcat(v30, (const char*)v38);
            if (1) {
                strcat(v30, ".dat");
                m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)v30, 0, 0xbf);
                m_graphics->LoadPaletteDat(m_palette, "system\\stage\\all.dat", 0, 0xaf, 0x10);
                m_graphics->LoadPaletteDat(m_palette, (const char*)v30, 0, 0xbf, 0x40);
            } else {
                strcat(v30, ".bmp");
                m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)v30, 0xbf);
                m_graphics->LoadPaletteBmp(m_palette, "system\\stage\\all.bmp", 0, 0xaf, 0x50);
                m_graphics->LoadPaletteBmp(m_palette, (const char*)v30, 0, 0xbf, 0x40);
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
        if (m_anim[4] < 0x55) {
            m_anim[4] += 5;
        } else {
            m_anim[4] = 0x5a;
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
        if (m_anim[5] < 0x5a) {
            m_anim[5] += 0xa;
        } else {
            m_anim[5] = 0;
            m_state[0] = 4;
            m_state[1] = 4;
            m_game->m_stage++;
            if (m_game->m_extraChars == 0 && m_game->m_stage == 0xd) {
                m_game->m_stage = 0x11;
            }
            if (m_game->m_extraChars == -1 && m_game->m_stage == 0x12) {
                m_game->m_stage = 0;
            }
            if (m_game->m_stage >= 0x17) {
                m_game->m_stage = 0;
            }
            LoadStagePicture();
        }
    } else if (m_state[0] == 0xa) {
        if (m_anim[5] < 0x5a) {
            m_anim[5] += 0xa;
        } else {
            m_anim[5] = 0;
            m_state[0] = 4;
            m_state[1] = 4;
            m_game->m_stage--;
            if (m_game->m_stage < 0) {
                m_game->m_stage = 0x16;
            }
            if (m_game->m_extraChars == 0 && m_game->m_stage == 0x10) {
                m_game->m_stage = 0xc;
            }
            if (m_game->m_extraChars == -1 && m_game->m_stage == 0x16) {
                m_game->m_stage = 0x11;
            }
            LoadStagePicture();
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

    v10 = MakeRect(0, (int)m_bgScroll, 0x140, 0xf0);
    x20 = MakeRect(0, 0, 0x140, 0xf0);
    m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_bgSurface), v10, 0, 0);
    if (m_game->m_isCpu[0] != 1 || m_game->m_gameMode != 0) {
        v10 = MakeRect(0x85, 0x80, 0x16, 0xf0);
        x20 = MakeRect(5 - (int)m_p1BarOffset, (int)m_barScroll, 0x16, 0xf0);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        x20 = MakeRect(5 - (int)m_p1BarOffset, (int)m_barScroll - 0xf0, 0x16, 0xf0);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
    }
    if (m_game->m_isCpu[1] != 1 || m_game->m_gameMode != 0) {
        v10 = MakeRect(0xa5, 0x80, 0x16, 0xf0);
        x20 = MakeRect((int)m_p2BarOffset + 0x124, 0 - (int)m_barScroll, 0x16, 0xf0);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        x20 = MakeRect((int)m_p2BarOffset + 0x124, 0 - (int)m_barScroll + 0xf0, 0x16, 0xf0);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
    }
    if (m_state[0] > 0) {
        if (m_game->m_gameMode != 0 && m_game->m_gameMode != 2 || m_game->m_isCpu[0] != 1) {
            v10 = MakeRect(0, 0, 0x140, 0xf0);
            x20 = MakeRect(-0x50 - m_portraitOffset[0] + m_portraitShift[(m_cursorX[0] + m_cursorY[0] * 3)], 0, 0x140, 0xf0);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_portraits[0]), v10, m_colorKeys[0], 1);
            v10 = MakeRect(0xc0, 9, 0x7a, 0x5f);
            x20 = MakeRect(0 - m_portraitOffset[0] / 2, 0x89, 0x7a, 0x5f);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
            v10 = MakeRect(0, (m_namePlate[m_charId[0]] << 5) + 0x100, 0x7a, 0x20);
            x20 = MakeRect(0 - m_portraitOffset[0] / 2, 0xc0, 0x7a, 0x20);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        }
        if (m_game->m_editColor[0] != 0) {
            v10 = MakeRect(0, 0xe0, 0x80, 0x20);
            x20 = MakeRect(-0x10 - m_portraitOffset[0] / 2, 5, 0x80, 0x20);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        }
    }
    if (m_state[1] > 0) {
        if (m_game->m_gameMode != 0 && m_game->m_gameMode != 2 || m_game->m_isCpu[1] != 1) {
            v10 = MakeRect(0, 0, 0x140, 0xf0);
            x20 = MakeRect(m_portraitOffset[1] + 0x50 - m_portraitShift[(m_cursorX[1] + m_cursorY[1] * 3)], 0, 0x140, 0xf0);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_portraits[1]), v10, m_colorKeys[1], 0);
            v10 = MakeRect(0xc6, 0x89, 0x7a, 0x5f);
            x20 = MakeRect(m_portraitOffset[1] / 2 + 0xc6, 0x89, 0x7a, 0x5f);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
            v10 = MakeRect(0xc6, (m_namePlate[m_charId[1]] << 5) + 0x100, 0x7a, 0x20);
            x20 = MakeRect(m_portraitOffset[1] / 2 + 0xc6, 0xc0, 0x7a, 0x20);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        }
        if (m_game->m_editColor[1] != 0) {
            v10 = MakeRect(0, 0xe0, 0x80, 0x20);
            x20 = MakeRect(m_portraitOffset[1] / 2 + 0xcf, 5, 0x80, 0x20);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        }
    }
    v10 = MakeRect(0, 0, 0x80, 0xd9);
    x20 = MakeRect(0x60, (int)m_gridY, 0x80, 0xd9);
    m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
    v10 = MakeRect(0x8a, 0x60, 0x29, 0x19);
    if (m_game->m_extraChars == 0) {
        x20 = MakeRect(0x67, (int)m_gridY + 0x72, 0x29, 0x19);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        x20 = MakeRect(0x8f, (int)m_gridY + 0x72, 0x29, 0x19);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        x20 = MakeRect(0xb7, (int)m_gridY + 0x72, 0x29, 0x19);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        x20 = MakeRect(0xb1, (int)m_gridY + 0xc0, 0x29, 0x19);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
    }
    if (m_game->m_extraChars == -1) {
        x20 = MakeRect(0x61, (int)m_gridY + 0x8c, 0x29, 0x19);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        x20 = MakeRect(0x89, (int)m_gridY + 0x8c, 0x29, 0x19);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        x20 = MakeRect(0x8f, (int)m_gridY + 0xa6, 0x29, 0x19);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        x20 = MakeRect(0xb7, (int)m_gridY + 0xa6, 0x29, 0x19);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
    }
    if (m_gridY == 0.0) {
        if (m_charId[0] == m_charId[1] && (m_game->m_isCpu[0] != 1 || m_game->m_gameMode != 0) && (m_game->m_isCpu[1] != 1 || m_game->m_gameMode != 0)) {
            v10 = MakeRect(0x81, 0x40, 0x3f, 0x18);
            x20 = MakeRect(m_cursorX[0] * 0x28 + 0x58 + (m_cursorY[0] % 2 == 0) * 6, m_cursorY[0] * 0x1a + 0xa, 0x3f, 0x18);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        } else {
            if (m_game->m_isCpu[1] != 1 || m_game->m_gameMode != 0) {
                v10 = MakeRect(0x81, 0x20, 0x3f, 0x18);
                x20 = MakeRect(m_cursorX[1] * 0x28 + 0x58 + (m_cursorY[1] % 2 == 0) * 6, m_cursorY[1] * 0x1a + 0xa, 0x3f, 0x18);
                m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
            }
            if (m_game->m_isCpu[0] != 1 || m_game->m_gameMode != 0) {
                v10 = MakeRect(0x81, 0, 0x3f, 0x18);
                x20 = MakeRect(m_cursorX[0] * 0x28 + 0x58 + (m_cursorY[0] % 2 == 0) * 6, m_cursorY[0] * 0x1a + 0xa, 0x3f, 0x18);
                m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
            }
        }
    }
    if ((m_state[0] == 7 || m_state[0] == 8 || m_state[0] == 4) && m_game->m_gameMode != 0 && m_game->m_gameMode != 2) {
        if (m_randomTime[0] == 0) {
            x24 = 0;
            a28 = 1;
            for (; a28 <= 7; a28++) {
                while (m_stageHidden[(m_game->m_stage + a28 + x24) % 0x17] != 0) {
                    x24++;
                }
                v10 = MakeRect(0, (m_game->m_stage + a28 + x24) % 0x17 << 5, 0xa0, 0x20);
                x20 = MakeRect(a28 * 0xb + 0xaa, 0xcd - a28 * 0x21 + (int)((double)(a28 * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)), 0xa0, 0x20);
                m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_stageNames), v10, m_colorKeys[2], 0);
            }
            v10 = MakeRect(0xa0, m_game->m_stage << 5, 0xa0, 0x20);
            x20 = MakeRect(0xaa, (int)(cos(m_anim[4] / 57.29579143313326) * 190.0) + 0xcd, 0xa0, 0x20);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_stageNames), v10, m_colorKeys[2], 0);
            v10 = MakeRect(1, 0, 0xc3, 0xde);
            x20 = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_stagePicture), v10, m_colorKeys[3], 0);
        } else {
            v2c = 0;
            v30 = 0;
            for (; v30 <= 8; v30++) {
                while (m_stageHidden[(m_game->m_stage + v30 + v2c) % 0x17] != 0) {
                    v2c++;
                }
                v10 = MakeRect(0, (m_game->m_stage + v30 + v2c) % 0x17 << 5, 0xa0, 0x20);
                x20 = MakeRect(v30 * 0xb + 0xaa, 0xcd - v30 * 0x21 + (int)((double)(v30 * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)), 0xa0, 0x20);
                m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_stageNames), v10, m_colorKeys[2], 0);
            }
            v10 = MakeRect(0, 0x3d9, 0xc3, 0xde);
            x20 = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_obSurface), v10, m_colorKey, 0);
        }
    } else if (m_state[0] == 9) {
        v34 = 0;
        v38 = 0;
        for (; v38 <= 8; v38++) {
            while (m_stageHidden[(m_game->m_stage + v38 + v34) % 0x17] != 0) {
                v34++;
            }
            v10 = MakeRect(0, (m_game->m_stage + v38 + v34) % 0x17 << 5, 0xa0, 0x20);
            x20 = MakeRect(v38 * 0xb + 0xaa - (int)(sin(m_anim[5] / 57.29579143313326) * 11.0), 0xcd - v38 * 0x21 + (int)((double)(v38 * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)) + (int)(sin(m_anim[5] / 57.29579143313326) * 33.0), 0xa0, 0x20);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_stageNames), v10, m_colorKeys[2], 0);
        }
        v10 = MakeRect(1, 0, 0xc3, 0xde);
        x20 = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_stagePicture), v10, m_colorKeys[3], 0);
    } else if (m_state[0] == 0xa) {
        x3c = 0;
        l40 = 0;
        for (; l40 <= 8; l40++) {
            while (m_stageHidden[(m_game->m_stage + l40 + 0x17 + x3c) % 0x17] != 0) {
                x3c++;
            }
            v10 = MakeRect(0, (m_game->m_stage + l40 + 0x17 + x3c) % 0x17 << 5, 0xa0, 0x20);
            x20 = MakeRect(l40 * 0xb + 0xaa + (int)(sin(m_anim[5] / 57.29579143313326) * 11.0), 0xcd - l40 * 0x21 + (int)((double)(l40 * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)) - (int)(sin(m_anim[5] / 57.29579143313326) * 33.0), 0xa0, 0x20);
            m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_stageNames), v10, m_colorKeys[2], 0);
        }
        l40 = -1;
        x3c = 0;
        while (m_stageHidden[(m_game->m_stage + l40 + 0x17 + x3c) % 0x17] != 0) {
            x3c--;
        }
        v10 = MakeRect(0, (m_game->m_stage + l40 + 0x17 + x3c) % 0x17 << 5, 0xa0, 0x20);
        x20 = MakeRect(l40 * 0xb + 0xaa + (int)(sin(m_anim[5] / 57.29579143313326) * 11.0), 0xcd - l40 * 0x21 + (int)((double)(l40 * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)) - (int)(sin(m_anim[5] / 57.29579143313326) * 33.0), 0xa0, 0x20);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_stageNames), v10, m_colorKeys[2], 0);
        v10 = MakeRect(1, 0, 0xc3, 0xde);
        x20 = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
        m_graphics->Blit(x20, TOPTR(IDirectDrawSurface*, m_stagePicture), v10, m_colorKeys[3], 0);
    }
    m_graphics->Flip();
}

void CScene1::CreateCharacter(PTR32(CPlayer)* p1, PTR32(CPlayer)* p2, char p3)
{
    char v2c[40];

    switch (m_charId[p3]) {
    case 0:
        *p1 = new CNanase(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 1:
        *p1 = new CAyu(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 2:
        *p1 = new CMai(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 3:
        *p1 = new CMakoto(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 4:
        *p1 = new CAkane(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 5:
        *p1 = new CMayu(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 6:
        *p1 = new CNagamori(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 7:
        *p1 = new CMisaki(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 8:
        *p1 = new CShiori(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 9:
        *p1 = new CSayuri(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xa:
        *p1 = new CNayuki(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xb:
        *p1 = new CMio(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xc:
        *p1 = new CEXNanase(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xd:
        *p1 = new CKaori(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xe:
        *p1 = new CIkumi(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0xf:
        *p1 = new CMishio(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x10:
        *p1 = new CAkiko(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x11:
        *p1 = new CNayukiB(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x12:
        *p1 = new CMizukaB(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x13:
        *p1 = new CKanna(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x14:
        *p1 = new CKano(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x15:
        *p1 = new CMinagi(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x16:
        *p1 = new CNayuki(p2, m_game, m_graphics, m_input, m_sound, p3);
        break;
    case 0x17:
        *p1 = new CMisuzu(p2, m_game, m_graphics, m_input, m_sound, p3);
    }
    (*p1)->m_charId = m_charId[p3];
    m_players[p3] = *p1;
    (*p1)->m_cpu = m_game->m_isCpu[p3];
    if (1) {
        strcpy(v2c, "system\\");
        strcat(v2c, (*p1)->m_name);
        strcat(v2c, "\\");
        strcat(v2c, (*p1)->m_name);
        strcat(v2c, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_portraits[p3], (const char*)v2c, 0, p3 * 0x28 + 0xaf);
        m_graphics->LoadPaletteDat(m_palette, (const char*)v2c, m_paletteIndex[p3] * 0x28, p3 * 0x28 + 0xaf, 0x28);
    } else {
        strcpy(v2c, "system\\");
        strcat(v2c, (*p1)->m_name);
        strcat(v2c, "\\");
        strcat(v2c, (*p1)->m_name);
        strcat(v2c, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_portraits[p3], (const char*)v2c, p3 * 0x28 + 0xaf);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v2c, m_paletteIndex[p3] * 0x28, p3 * 0x28 + 0xaf, 0x28);
    }
    m_graphics->SetPalette(m_palette);
    m_colorKeys[p3] = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_portraits[p3]));
}

void CScene1::LoadStagePicture()
{
    char v34[8];
    char v2c[40];

    if (m_game->m_stage < 0xa) {
        strcpy(v2c, "system\\stage\\0");
    } else {
        strcpy(v2c, "system\\stage\\");
    }
    _itoa(m_game->m_stage, v34, 0xa);
    strcat(v2c, (const char*)v34);
    if (1) {
        strcat(v2c, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)v2c, 0, 0xbf);
        m_graphics->LoadPaletteDat(m_palette, (const char*)v2c, 0, 0xbf, 0x40);
    } else {
        strcat(v2c, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)v2c, 0xbf);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v2c, 0, 0xbf, 0x40);
    }
    m_colorKeys[3] = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_stagePicture));
    m_graphics->SetPaletteRange(m_palette, 0xaf, 0x50);
}

void CScene1::SetPortraitPalette(char p1)
{
    char v2c[40];

    if (1) {
        strcpy(v2c, "system\\");
        strcat(v2c, m_players[p1]->m_name);
        strcat(v2c, "\\");
        strcat(v2c, m_players[p1]->m_name);
        strcat(v2c, ".dat");
        m_graphics->LoadPaletteDat(m_palette, (const char*)v2c, m_paletteIndex[p1] * 0x28, p1 * 0x28 + 0xaf, 0x28);
    } else {
        strcpy(v2c, "system\\");
        strcat(v2c, m_players[p1]->m_name);
        strcat(v2c, "\\");
        strcat(v2c, m_players[p1]->m_name);
        strcat(v2c, ".bmp");
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v2c, m_paletteIndex[p1] * 0x28, p1 * 0x28 + 0xaf, 0x28);
    }
    m_graphics->SetPaletteRange(m_palette, p1 * 0x28 + 0xaf, 0x28);
}

void CScene1::HandleKeys()
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
    if ((v108[59] & 0x80) != 0) {
        m_input->LoadBindings();
    }
    if ((v108[60] & 0x80) != 0 && (BYTE)ReadConfigByte(0x98) > 0) {
        m_input->LoadPreset(1);
    }
    if ((v108[61] & 0x80) != 0 && (BYTE)ReadConfigByte(0x98) > 0) {
        m_input->LoadPreset(2);
    }
    if ((v108[62] & 0x80) != 0 && (BYTE)ReadConfigByte(0x98) > 0) {
        m_input->LoadPreset(3);
    }
}

void CScene1::Enter()
{
    m_held[0] = 0;
    m_held[1] = 0;
    m_bgScroll = 0.0;
    m_bgSlideTime = 0x3c;
    m_p1BarOffset = 50.0;
    m_anim[0] = 0;
    m_p2BarOffset = 50.0;
    m_anim[1] = 0;
    m_barScroll = 0.0;
    m_anim[2] = 0;
    m_gridY = -480.0;
    m_anim[3] = 0x3c;
    m_anim[4] = 0;
    m_anim[5] = 0;
    m_portraitOffset[0] = 0x12c;
    m_portraitOffset[1] = 0x12c;
    m_portraitAngle[0] = 0xb4;
    m_portraitAngle[1] = 0xb4;
    m_state[0] = 5;
    m_state[1] = 5;
    m_randomTime[0] = 0;
    m_randomTime[1] = 0;
    m_paletteIndex[0] = 0;
    m_paletteIndex[1] = 0;
    m_game->m_continued = 0;
    m_game->m_continuedAt = 0;
    m_game->m_editColor[0] = 0;
    m_game->m_editColor[1] = 0;
    if (m_game->m_gameMode < 5) {
        if (1) {
            m_graphics->LoadPaletteDat(m_palette, "system\\chr_sel_bg.dat", 0, 1, 0x30);
        } else {
            m_graphics->LoadPaletteBmp(m_palette, "system\\chr_sel_bg.bmp", 0, 1, 0x30);
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
    memset((void*)&m_stageHidden[0], 0, 0x17);
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
