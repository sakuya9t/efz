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
    char digits[8];
    char path[40];
    int side;

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
                m_randomTime[side] = 0x3c;
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
                    if (m_game->m_extraChars == 0 && (m_charId[side] == 0x13 || m_charId[side] == 0x14 || m_charId[side] == 0x15 || m_charId[side] == 0x17)) {
                        m_randomTime[side]++;
                    }
                    if (m_game->m_extraChars == -1 && (m_charId[side] == 0xc || m_charId[side] == 0xd || m_charId[side] == 0xe || m_charId[side] == 0xf)) {
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
                    m_portraitAngle[side] = 0x28;
                    m_held[side] = 1;
                } else if (m_game->m_inputX[side] < 0) {
                    m_cursorX[side] = (m_cursorX[side] + 2) % 3;
                    m_game->PlaySE(8);
                    m_portraitAngle[side] = 0x28;
                    m_held[side] = 1;
                } else if (m_game->m_inputX[side] > 0) {
                    m_cursorX[side] = (m_cursorX[side] + 1) % 3;
                    m_game->PlaySE(8);
                    m_portraitAngle[side] = 0x28;
                    m_held[side] = 1;
                }
                m_charId[side] = m_grid[(m_cursorX[side] + m_cursorY[side] * 3)];
            } else if (m_game->m_inputX[side] == 0 && m_game->m_inputY[side] == 0) {
                m_held[side] = 0;
            }
            if (m_game->m_extraChars == 0 && (m_charId[side] == 0x13 || m_charId[side] == 0x14 || m_charId[side] == 0x15 || m_charId[side] == 0x17)) {
                m_game->m_pressA[side] = 0;
            }
            if (m_game->m_extraChars == -1 && (m_charId[side] == 0xc || m_charId[side] == 0xd || m_charId[side] == 0xe || m_charId[side] == 0xf)) {
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
                m_portraitAngle[side] = 0x5a;
            }
            break;
        case 1:
            m_anim[side] = -2;
            m_portraitOffset[side] = (int)((cos(m_portraitAngle[side] / 57.29579143313326) + 1.0) * 300.0);
            m_portraitAngle[side] = m_portraitAngle[side] + 5;
            if (m_portraitAngle[side] > 0xb4) {
                m_state[side] = 3;
                m_game->PlaySE(m_charId[side] + 0x28);
            }
            if (m_game->m_pressB[side] != 0) {
                m_state[side] = 2;
                m_randomTime[side] = 0;
            }
            break;
        case 2:
            if (m_portraitAngle[side] >= 0x5a) {
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
                    CScene::FadeOut(m_palette, 0, 0, 0x32);
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
                    if (m_game->m_inputY[side] > 0 || m_game->m_inputX[side] > 0) {
                        m_game->PlaySE(8);
                        m_state[0] = 0xa;
                        m_state[1] = 0xa;
                    } else if (m_game->m_inputX[side] < 0 || m_game->m_inputY[side] < 0) {
                        m_game->PlaySE(8);
                        m_state[0] = 9;
                        m_state[1] = 9;
                    }
                    if (m_game->m_extraChars == 0 && m_game->m_stage >= 0xd && m_game->m_stage <= 0x10) {
                        m_game->m_pressA[side] = 0;
                    }
                    if (m_game->m_extraChars == -1 && m_game->m_stage >= 0x12 && m_game->m_stage <= 0x16) {
                        m_game->m_pressA[side] = 0;
                    }
                    if (m_game->m_pressA[side] != 0) {
                        m_game->PlaySE(6);
                        CScene::FadeOut(m_palette, 0, 0, 0x32);
                        m_enter = 2;
                        m_game->m_arcadeMatch = 1;
                        m_game->m_beatenChars = 0;
                        m_game->m_playedStages = 0;
                        return 2;
                    }
                }
                if (m_game->m_pressC[side] != 0 && m_randomTime[0] == 0 && 1) {
                    m_randomTime[0] = rand() % 0x17 + 0x3c;
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
            m_leave = 1;
        }
        *(char*)&m_held[side] = m_game->m_inputX[side] != 0 || m_game->m_inputY[side] != 0;
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
                strcpy(path, "system\\stage\\0");
            } else {
                strcpy(path, "system\\stage\\");
            }
            _itoa(m_game->m_stage, digits, 0xa);
            strcat(path, (const char*)digits);
            if (1) {
                strcat(path, ".dat");
                m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)path, 0, 0xbf);
                m_graphics->LoadPaletteDat(m_palette, "system\\stage\\all.dat", 0, 0xaf, 0x10);
                m_graphics->LoadPaletteDat(m_palette, (const char*)path, 0, 0xbf, 0x40);
            } else {
                strcat(path, ".bmp");
                m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)path, 0xbf);
                m_graphics->LoadPaletteBmp(m_palette, "system\\stage\\all.bmp", 0, 0xaf, 0x50);
                m_graphics->LoadPaletteBmp(m_palette, (const char*)path, 0, 0xbf, 0x40);
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

    src = MakeRect(0, (int)m_bgScroll, 0x140, 0xf0);
    dst = MakeRect(0, 0, 0x140, 0xf0);
    m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_bgSurface), src, 0, 0);
    if (m_game->m_isCpu[0] != 1 || m_game->m_gameMode != 0) {
        src = MakeRect(0x85, 0x80, 0x16, 0xf0);
        dst = MakeRect(5 - (int)m_p1BarOffset, (int)m_barScroll, 0x16, 0xf0);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(5 - (int)m_p1BarOffset, (int)m_barScroll - 0xf0, 0x16, 0xf0);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    }
    if (m_game->m_isCpu[1] != 1 || m_game->m_gameMode != 0) {
        src = MakeRect(0xa5, 0x80, 0x16, 0xf0);
        dst = MakeRect((int)m_p2BarOffset + 0x124, 0 - (int)m_barScroll, 0x16, 0xf0);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect((int)m_p2BarOffset + 0x124, 0 - (int)m_barScroll + 0xf0, 0x16, 0xf0);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    }
    if (m_state[0] > 0) {
        if (m_game->m_gameMode != 0 && m_game->m_gameMode != 2 || m_game->m_isCpu[0] != 1) {
            src = MakeRect(0, 0, 0x140, 0xf0);
            dst = MakeRect(-0x50 - m_portraitOffset[0] + m_portraitShift[(m_cursorX[0] + m_cursorY[0] * 3)], 0, 0x140, 0xf0);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_portraits[0]), src, m_colorKeys[0], 1);
            src = MakeRect(0xc0, 9, 0x7a, 0x5f);
            dst = MakeRect(0 - m_portraitOffset[0] / 2, 0x89, 0x7a, 0x5f);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
            src = MakeRect(0, (m_namePlate[m_charId[0]] << 5) + 0x100, 0x7a, 0x20);
            dst = MakeRect(0 - m_portraitOffset[0] / 2, 0xc0, 0x7a, 0x20);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
        if (m_game->m_editColor[0] != 0) {
            src = MakeRect(0, 0xe0, 0x80, 0x20);
            dst = MakeRect(-0x10 - m_portraitOffset[0] / 2, 5, 0x80, 0x20);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
    }
    if (m_state[1] > 0) {
        if (m_game->m_gameMode != 0 && m_game->m_gameMode != 2 || m_game->m_isCpu[1] != 1) {
            src = MakeRect(0, 0, 0x140, 0xf0);
            dst = MakeRect(m_portraitOffset[1] + 0x50 - m_portraitShift[(m_cursorX[1] + m_cursorY[1] * 3)], 0, 0x140, 0xf0);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_portraits[1]), src, m_colorKeys[1], 0);
            src = MakeRect(0xc6, 0x89, 0x7a, 0x5f);
            dst = MakeRect(m_portraitOffset[1] / 2 + 0xc6, 0x89, 0x7a, 0x5f);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
            src = MakeRect(0xc6, (m_namePlate[m_charId[1]] << 5) + 0x100, 0x7a, 0x20);
            dst = MakeRect(m_portraitOffset[1] / 2 + 0xc6, 0xc0, 0x7a, 0x20);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
        if (m_game->m_editColor[1] != 0) {
            src = MakeRect(0, 0xe0, 0x80, 0x20);
            dst = MakeRect(m_portraitOffset[1] / 2 + 0xcf, 5, 0x80, 0x20);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
    }
    src = MakeRect(0, 0, 0x80, 0xd9);
    dst = MakeRect(0x60, (int)m_gridY, 0x80, 0xd9);
    m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    src = MakeRect(0x8a, 0x60, 0x29, 0x19);
    if (m_game->m_extraChars == 0) {
        dst = MakeRect(0x67, (int)m_gridY + 0x72, 0x29, 0x19);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(0x8f, (int)m_gridY + 0x72, 0x29, 0x19);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(0xb7, (int)m_gridY + 0x72, 0x29, 0x19);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(0xb1, (int)m_gridY + 0xc0, 0x29, 0x19);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    }
    if (m_game->m_extraChars == -1) {
        dst = MakeRect(0x61, (int)m_gridY + 0x8c, 0x29, 0x19);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(0x89, (int)m_gridY + 0x8c, 0x29, 0x19);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(0x8f, (int)m_gridY + 0xa6, 0x29, 0x19);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        dst = MakeRect(0xb7, (int)m_gridY + 0xa6, 0x29, 0x19);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
    }
    if (m_gridY == 0.0) {
        if (m_charId[0] == m_charId[1] && (m_game->m_isCpu[0] != 1 || m_game->m_gameMode != 0) && (m_game->m_isCpu[1] != 1 || m_game->m_gameMode != 0)) {
            src = MakeRect(0x81, 0x40, 0x3f, 0x18);
            dst = MakeRect(m_cursorX[0] * 0x28 + 0x58 + (m_cursorY[0] % 2 == 0) * 6, m_cursorY[0] * 0x1a + 0xa, 0x3f, 0x18);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        } else {
            if (m_game->m_isCpu[1] != 1 || m_game->m_gameMode != 0) {
                src = MakeRect(0x81, 0x20, 0x3f, 0x18);
                dst = MakeRect(m_cursorX[1] * 0x28 + 0x58 + (m_cursorY[1] % 2 == 0) * 6, m_cursorY[1] * 0x1a + 0xa, 0x3f, 0x18);
                m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
            }
            if (m_game->m_isCpu[0] != 1 || m_game->m_gameMode != 0) {
                src = MakeRect(0x81, 0, 0x3f, 0x18);
                dst = MakeRect(m_cursorX[0] * 0x28 + 0x58 + (m_cursorY[0] % 2 == 0) * 6, m_cursorY[0] * 0x1a + 0xa, 0x3f, 0x18);
                m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
            }
        }
    }
    if ((m_state[0] == 7 || m_state[0] == 8 || m_state[0] == 4) && m_game->m_gameMode != 0 && m_game->m_gameMode != 2) {
        if (m_randomTime[0] == 0) {
            skipped = 0;
            row = 1;
            for (; row <= 7; row++) {
                while (m_stageHidden[(m_game->m_stage + row + skipped) % 0x17] != 0) {
                    skipped++;
                }
                src = MakeRect(0, (m_game->m_stage + row + skipped) % 0x17 << 5, 0xa0, 0x20);
                dst = MakeRect(row * 0xb + 0xaa, 0xcd - row * 0x21 + (int)((double)(row * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)), 0xa0, 0x20);
                m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
            }
            src = MakeRect(0xa0, m_game->m_stage << 5, 0xa0, 0x20);
            dst = MakeRect(0xaa, (int)(cos(m_anim[4] / 57.29579143313326) * 190.0) + 0xcd, 0xa0, 0x20);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
            src = MakeRect(1, 0, 0xc3, 0xde);
            dst = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stagePicture), src, m_colorKeys[3], 0);
        } else {
            randomSkipped = 0;
            randomRow = 0;
            for (; randomRow <= 8; randomRow++) {
                while (m_stageHidden[(m_game->m_stage + randomRow + randomSkipped) % 0x17] != 0) {
                    randomSkipped++;
                }
                src = MakeRect(0, (m_game->m_stage + randomRow + randomSkipped) % 0x17 << 5, 0xa0, 0x20);
                dst = MakeRect(randomRow * 0xb + 0xaa, 0xcd - randomRow * 0x21 + (int)((double)(randomRow * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)), 0xa0, 0x20);
                m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
            }
            src = MakeRect(0, 0x3d9, 0xc3, 0xde);
            dst = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_obSurface), src, m_colorKey, 0);
        }
    } else if (m_state[0] == 9) {
        nextSkipped = 0;
        nextRow = 0;
        for (; nextRow <= 8; nextRow++) {
            while (m_stageHidden[(m_game->m_stage + nextRow + nextSkipped) % 0x17] != 0) {
                nextSkipped++;
            }
            src = MakeRect(0, (m_game->m_stage + nextRow + nextSkipped) % 0x17 << 5, 0xa0, 0x20);
            dst = MakeRect(nextRow * 0xb + 0xaa - (int)(sin(m_anim[5] / 57.29579143313326) * 11.0), 0xcd - nextRow * 0x21 + (int)((double)(nextRow * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)) + (int)(sin(m_anim[5] / 57.29579143313326) * 33.0), 0xa0, 0x20);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
        }
        src = MakeRect(1, 0, 0xc3, 0xde);
        dst = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stagePicture), src, m_colorKeys[3], 0);
    } else if (m_state[0] == 0xa) {
        prevSkipped = 0;
        prevRow = 0;
        for (; prevRow <= 8; prevRow++) {
            while (m_stageHidden[(m_game->m_stage + prevRow + 0x17 + prevSkipped) % 0x17] != 0) {
                prevSkipped++;
            }
            src = MakeRect(0, (m_game->m_stage + prevRow + 0x17 + prevSkipped) % 0x17 << 5, 0xa0, 0x20);
            dst = MakeRect(prevRow * 0xb + 0xaa + (int)(sin(m_anim[5] / 57.29579143313326) * 11.0), 0xcd - prevRow * 0x21 + (int)((double)(prevRow * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)) - (int)(sin(m_anim[5] / 57.29579143313326) * 33.0), 0xa0, 0x20);
            m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
        }
        prevRow = -1;
        prevSkipped = 0;
        while (m_stageHidden[(m_game->m_stage + prevRow + 0x17 + prevSkipped) % 0x17] != 0) {
            prevSkipped--;
        }
        src = MakeRect(0, (m_game->m_stage + prevRow + 0x17 + prevSkipped) % 0x17 << 5, 0xa0, 0x20);
        dst = MakeRect(prevRow * 0xb + 0xaa + (int)(sin(m_anim[5] / 57.29579143313326) * 11.0), 0xcd - prevRow * 0x21 + (int)((double)(prevRow * 0x21 + 0xbe) * cos(m_anim[4] / 57.29579143313326)) - (int)(sin(m_anim[5] / 57.29579143313326) * 33.0), 0xa0, 0x20);
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_stageNames), src, m_colorKeys[2], 0);
        src = MakeRect(1, 0, 0xc3, 0xde);
        dst = MakeRect(0 - (int)(cos(m_anim[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
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
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_portraits[side], (const char*)path, 0, side * 0x28 + 0xaf);
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, m_paletteIndex[side] * 0x28, side * 0x28 + 0xaf, 0x28);
    } else {
        strcpy(path, "system\\");
        strcat(path, (*player)->m_name);
        strcat(path, "\\");
        strcat(path, (*player)->m_name);
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_portraits[side], (const char*)path, side * 0x28 + 0xaf);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, m_paletteIndex[side] * 0x28, side * 0x28 + 0xaf, 0x28);
    }
    m_graphics->SetPalette(m_palette);
    m_colorKeys[side] = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_portraits[side]));
}

void CScene1::LoadStagePicture()
{
    char digits[8];
    char path[40];

    if (m_game->m_stage < 0xa) {
        strcpy(path, "system\\stage\\0");
    } else {
        strcpy(path, "system\\stage\\");
    }
    _itoa(m_game->m_stage, digits, 0xa);
    strcat(path, (const char*)digits);
    if (1) {
        strcat(path, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)path, 0, 0xbf);
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, 0, 0xbf, 0x40);
    } else {
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_stagePicture, (const char*)path, 0xbf);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, 0, 0xbf, 0x40);
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
        m_graphics->LoadPaletteDat(m_palette, (const char*)path, m_paletteIndex[side] * 0x28, side * 0x28 + 0xaf, 0x28);
    } else {
        strcpy(path, "system\\");
        strcat(path, m_players[side]->m_name);
        strcat(path, "\\");
        strcat(path, m_players[side]->m_name);
        strcat(path, ".bmp");
        m_graphics->LoadPaletteBmp(m_palette, (const char*)path, m_paletteIndex[side] * 0x28, side * 0x28 + 0xaf, 0x28);
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
