// CScene1 (0x753260-0x759f2f), scene 1: character and stage select
// (system\chr_sel_bg, chr_sel_ob, system\stage\). The inline methods of CScene follow
// it: its constructor and the two palette fades (0x759c10-0x759f2f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene1::CScene1(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        m_game->LoadDat((IDirectDrawSurface**)&unk434, "system\\chr_sel_bg.dat", 0, 1);
        m_game->LoadDat((IDirectDrawSurface**)&unk438, "system\\chr_sel_ob.dat", 0, 1);
        m_game->LoadDat((IDirectDrawSurface**)&unk440, "system\\stage\\all.dat", 0, 0xaf);
        m_graphics->LoadPaletteDat(m_palette, "system\\chr_sel_ob.dat", 0, 1, 0xae);
    } else {
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk434, "system\\chr_sel_bg.bmp", 1);
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk438, "system\\chr_sel_ob.bmp", 1);
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk440, "system\\stage\\all.bmp", 0xaf);
        m_graphics->LoadPaletteBmp(m_palette, "system\\chr_sel_ob.bmp", 0, 1, 0xae);
    }
    m_colorKey = m_graphics->GetColorKey((IDirectDrawSurface*)unk438);
    unk44c[2] = m_graphics->GetColorKey((IDirectDrawSurface*)unk440);
    unk444[0] = 0;
    unk444[1] = 0;
    unk43c = 0;
    unk2c = 1;
    unk2d = 0;
    unk49c[0] = 0;
    unk49c[1] = 0;
    unk450 = 0.0;
    unk478 = 0x3c;
    unk458 = 50.0;
    unk47c[0] = 0;
    unk460 = 50.0;
    unk47c[1] = 0;
    unk468 = 0.0;
    unk47c[2] = 0;
    unk470 = -240.0;
    unk47c[3] = 0x3c;
    unk47c[4] = 0;
    unk47c[5] = 0;
    unk498[0] = 0x12c;
    unk498[1] = 0x12c;
    unk494[0] = 0xb4;
    unk494[1] = 0xb4;
    unk49e[0] = 5;
    unk49e[1] = 5;
    unk53c[0] = 2;
    unk53c[1] = 9;
    unk53e[0] = 0;
    unk53e[1] = 0;
    unk540[0] = 0;
    unk540[1] = 0;
    unk538[0] = 0;
    unk53a[0] = 0;
    unk538[1] = 2;
    unk53a[1] = 0;
    unk4b9[0] = 6;
    unk4b9[1] = 0;
    unk4b9[2] = 4;
    unk4b9[3] = 7;
    unk4b9[4] = 5;
    unk4b9[5] = 0xb;
    unk4b9[6] = 1;
    unk4b9[7] = 0xa;
    unk4b9[8] = 3;
    unk4b9[9] = 8;
    unk4b9[0xa] = 2;
    unk4b9[0xb] = 9;
    unk4b9[0xc] = 0x17;
    unk4b9[0xd] = 0x14;
    unk4b9[0xe] = 0x15;
    unk4b9[0xf] = 0xe;
    unk4b9[0x10] = 0xc;
    unk4b9[0x11] = 0x12;
    unk4b9[0x12] = 0x11;
    unk4b9[0x13] = 0xf;
    unk4b9[0x14] = 0xd;
    unk4b9[0x15] = 0x10;
    unk4b9[0x16] = -1;
    unk4b9[0x17] = 0x13;
    unk4d4[0] = -0x28;
    unk4d4[1] = -0xa;
    unk4d4[2] = -5;
    unk4d4[3] = 0;
    unk4d4[4] = -5;
    unk4d4[5] = -5;
    unk4d4[6] = -0x1e;
    unk4d4[7] = -0x1e;
    unk4d4[8] = -0x14;
    unk4d4[9] = -0xa;
    unk4d4[0xa] = -0x28;
    unk4d4[0xb] = -5;
    unk4d4[0xc] = -0x32;
    unk4d4[0xd] = 0;
    unk4d4[0xe] = -0xf;
    unk4d4[0xf] = -0xf;
    unk4d4[0x10] = -0x14;
    unk4d4[0x11] = -0x14;
    unk4d4[0x12] = -0x2d;
    unk4d4[0x13] = 0xa;
    unk4d4[0x14] = -0x14;
    unk4d4[0x15] = 0;
    unk4d4[0x16] = 0;
    unk4d4[0x17] = -0x14;
    unk4a0[0] = 5;
    unk4a0[1] = 7;
    unk4a0[2] = 0xb;
    unk4a0[3] = 9;
    unk4a0[4] = 0;
    unk4a0[5] = 4;
    unk4a0[6] = 2;
    unk4a0[7] = 1;
    unk4a0[8] = 0xa;
    unk4a0[9] = 0xc;
    unk4a0[0xa] = 8;
    unk4a0[0xb] = 3;
    unk4a0[0xc] = 0x15;
    unk4a0[0xd] = 0xd;
    unk4a0[0xe] = 0x14;
    unk4a0[0xf] = 0xe;
    unk4a0[0x10] = 0xf;
    unk4a0[0x11] = 8;
    unk4a0[0x12] = 6;
    unk4a0[0x13] = 0x13;
    unk4a0[0x14] = 0x11;
    unk4a0[0x15] = 0x12;
    unk4a0[0x16] = -1;
    unk4a0[0x17] = 0x10;
    unk4a0[0x18] = 6;
}

CScene1::~CScene1()
{
    if (unk434 != 0) {
        ((IUnknown*)unk434)->Release();
        unk434 = 0;
    }
    if (unk438 != 0) {
        ((IUnknown*)unk438)->Release();
        unk438 = 0;
    }
    if (unk440 != 0) {
        ((IUnknown*)unk440)->Release();
        unk440 = 0;
    }
    if (unk43c != 0) {
        ((IUnknown*)unk43c)->Release();
        unk43c = 0;
    }
    if (unk444[0] != 0) {
        ((IUnknown*)unk444[0])->Release();
        unk444[0] = 0;
    }
    if (unk444[1] != 0) {
        ((IUnknown*)unk444[1])->Release();
        unk444[1] = 0;
    }
}

BYTE CScene1::Update()
{
    char v38[8];
    char v30[40];
    int v4;

    if (unk2c > 0) {
        Unk7598d0();
    }
    if (unk2d > 0) {
        CScene::Unk759c90(m_palette, 0, 0, 0x64);
        unk2c = 1;
        m_game->unkf32 = 0;
        unk2d = 0;
        m_game->StopMusic();
        if (m_game->unk1364 == 5) {
            return 8;
        }
        return 0;
    }
    Vf2();
    m_game->UpdateInput();
    v4 = 0;
    for (; v4 < 2; v4++) {
        if (m_game->unk1364 == 0 && m_game->unk1343[v4] == 1) {
            m_game->m_inputX[v4] = 0;
            m_game->m_inputY[v4] = 0;
            m_game->m_pressA[v4] = 0;
            m_game->m_pressB[v4] = 0;
            m_game->m_pressC[v4] = 0;
            m_game->m_pressD[v4] = 0;
        }
        if (m_game->unk1343[v4] == 1 && (m_game->unk1364 == 1 || m_game->unk1364 == 3 || m_game->unk1364 == 5)) {
            if (unk49e[v4] < 4 && unk49e[(1 - v4)] == 6) {
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
        switch (unk49e[v4]) {
        case 0:
            m_game->unk1338[v4] = 0;
            unk47c[v4] = 2;
            if (m_game->m_pressC[v4] != 0 && unk540[v4] == 0 || m_game->m_pressA[v4] != 0 && unk538[v4] == 1 && unk53a[v4] == 7) {
                unk540[v4] = 0x3c;
            }
            if (unk540[v4] > 0) {
                unk540[v4]--;
                m_game->m_inputX[v4] = rand() % 3 - 1;
                m_game->m_inputY[v4] = rand() % 2;
                m_game->m_pressA[v4] = 0;
                unk49c[v4] = 0;
                if (unk540[v4] == 0) {
                    unk53c[v4] = unk4b9[(unk538[v4] + unk53a[v4] * 3)];
                    if (unk53c[v4] < 0) {
                        unk540[v4]++;
                    }
                    if (m_game->m_extraChars == 0 && (unk53c[v4] == 0x13 || unk53c[v4] == 0x14 || unk53c[v4] == 0x15 || unk53c[v4] == 0x17)) {
                        unk540[v4]++;
                    }
                    if (m_game->m_extraChars == -1 && (unk53c[v4] == 0xc || unk53c[v4] == 0xd || unk53c[v4] == 0xe || unk53c[v4] == 0xf)) {
                        unk540[v4]++;
                    }
                }
                if (unk540[v4] == 0) {
                    m_game->m_inputX[v4] = 0;
                    m_game->m_inputY[v4] = 0;
                    m_game->m_pressA[v4] = 1;
                }
            }
            if (unk49c[v4] == 0) {
                if (m_game->m_inputY[v4] < 0) {
                    unk53a[v4] = (unk53a[v4] + 7) % 8;
                    m_game->PlaySE(8);
                    unk49c[v4] = 1;
                } else if (m_game->m_inputY[v4] > 0) {
                    unk53a[v4] = (unk53a[v4] + 1) % 8;
                    m_game->PlaySE(8);
                    unk494[v4] = 0x28;
                    unk49c[v4] = 1;
                } else if (m_game->m_inputX[v4] < 0) {
                    unk538[v4] = (unk538[v4] + 2) % 3;
                    m_game->PlaySE(8);
                    unk494[v4] = 0x28;
                    unk49c[v4] = 1;
                } else if (m_game->m_inputX[v4] > 0) {
                    unk538[v4] = (unk538[v4] + 1) % 3;
                    m_game->PlaySE(8);
                    unk494[v4] = 0x28;
                    unk49c[v4] = 1;
                }
                unk53c[v4] = unk4b9[(unk538[v4] + unk53a[v4] * 3)];
            } else if (m_game->m_inputX[v4] == 0 && m_game->m_inputY[v4] == 0) {
                unk49c[v4] = 0;
            }
            if (m_game->m_extraChars == 0 && (unk53c[v4] == 0x13 || unk53c[v4] == 0x14 || unk53c[v4] == 0x15 || unk53c[v4] == 0x17)) {
                m_game->m_pressA[v4] = 0;
            }
            if (m_game->m_extraChars == -1 && (unk53c[v4] == 0xc || unk53c[v4] == 0xd || unk53c[v4] == 0xe || unk53c[v4] == 0xf)) {
                m_game->m_pressA[v4] = 0;
            }
            if (m_game->m_pressA[v4] != 0 && m_game->m_inputY[v4] == 0 && m_game->m_inputX[v4] == 0) {
                if (unk49e[(1 - v4)] < 7 && unk49e[(1 - v4)] > 0 && unk53e[0] == unk53e[1] && unk53c[0] == unk53c[1]) {
                    unk53e[v4]++;
                    if (unk53e[v4] >= 6) {
                        unk53e[v4] = 0;
                    }
                }
                m_game->PlaySE(6);
                if (v4 == 0) {
                    Unk7586b0(m_player1Ref, m_player2Ref, 0);
                } else {
                    Unk7586b0(m_player2Ref, m_player1Ref, 1);
                }
                unk49e[v4] = 1;
                unk494[v4] = 0x5a;
            }
            break;
        case 1:
            unk47c[v4] = -2;
            unk498[v4] = (int)((cos(unk494[v4] / 57.29579143313326) + 1.0) * 300.0);
            unk494[v4] = unk494[v4] + 5;
            if (unk494[v4] > 0xb4) {
                unk49e[v4] = 3;
                m_game->PlaySE(unk53c[v4] + 0x28);
            }
            if (m_game->m_pressB[v4] != 0) {
                unk49e[v4] = 2;
                unk540[v4] = 0;
            }
            break;
        case 2:
            if (unk494[v4] >= 0x5a) {
                unk498[v4] = (int)((cos(unk494[v4] / 57.29579143313326) + 1.0) * 300.0);
                unk494[v4] = unk494[v4] - 5;
            } else {
                unk49e[v4] = 0;
            }
            break;
        case 3:
            m_game->unk1338[v4] = m_game->m_inputY[v4] > 0;
            if (unk49c[v4] == 0 && m_game->m_inputX[v4] != 0) {
                m_game->PlaySE(8);
                unk53e[v4] += m_game->m_inputX[v4];
                if (unk53e[v4] >= 6) {
                    unk53e[v4] = 0;
                } else if (unk53e[v4] < 0) {
                    unk53e[v4] = 5;
                }
                if (unk49e[(1 - v4)] > 0 && unk53e[0] == unk53e[1] && unk53c[0] == unk53c[1]) {
                    unk53e[v4] += m_game->m_inputX[v4];
                    if (unk53e[v4] >= 6) {
                        unk53e[v4] = 0;
                    } else if (unk53e[v4] < 0) {
                        unk53e[v4] = 5;
                    }
                }
                Unk7595d0(v4);
            }
            if (m_game->m_pressA[v4] != 0 || m_game->m_pressD[v4] != 0) {
                if (m_game->m_pressD[v4] != 0) {
                    m_game->unk1338[v4] = 1;
                }
                m_players[v4]->m_paletteIndex = unk53e[v4];
                m_game->PlaySE(6);
                unk49e[v4] = 6;
                if (m_game->unk1364 == 0 || m_game->unk1364 == 2) {
                    CScene::Unk759c90(m_palette, 0, 0, 0x32);
                    unk2c = 2;
                    m_game->unk1358 = 1;
                    m_game->unk135c = 0;
                    m_game->unk1360 = 0;
                    return 2;
                }
            }
            if (m_game->m_pressB[v4] != 0) {
                unk49e[v4] = 2;
            }
            break;
        case 4:
            if (unk49e[(1 - v4)] == 4) {
                if (unk540[0] > 0) {
                    unk540[0]--;
                    if (unk540[0] == 0) {
                        if (m_game->m_extraChars == 0 && m_game->unkf32 >= 0xd && m_game->unkf32 <= 0x10) {
                            unk540[0] = rand() % 0x17 + 1;
                        }
                        if (m_game->m_extraChars == -1 && m_game->unkf32 >= 0x12 && m_game->unkf32 <= 0x16) {
                            unk540[0] = rand() % 0x17 + 1;
                        }
                    }
                    if (unk540[0] == 0) {
                        m_game->PlaySE(6);
                        Unk759460();
                        CScene::Unk759c90(m_palette, 0, 0, 0x32);
                        unk2c = 2;
                        m_game->unk1358 = 1;
                        m_game->unk135c = 0;
                        m_game->unk1360 = 0;
                        return 2;
                    }
                    m_game->unkf32++;
                    if (m_game->unkf32 >= 0x17) {
                        m_game->unkf32 = 0;
                    }
                } else {
                    if (m_game->m_inputY[v4] > 0 || m_game->m_inputX[v4] > 0) {
                        m_game->PlaySE(8);
                        unk49e[0] = 0xa;
                        unk49e[1] = 0xa;
                    } else if (m_game->m_inputX[v4] < 0 || m_game->m_inputY[v4] < 0) {
                        m_game->PlaySE(8);
                        unk49e[0] = 9;
                        unk49e[1] = 9;
                    }
                    if (m_game->m_extraChars == 0 && m_game->unkf32 >= 0xd && m_game->unkf32 <= 0x10) {
                        m_game->m_pressA[v4] = 0;
                    }
                    if (m_game->m_extraChars == -1 && m_game->unkf32 >= 0x12 && m_game->unkf32 <= 0x16) {
                        m_game->m_pressA[v4] = 0;
                    }
                    if (m_game->m_pressA[v4] != 0) {
                        m_game->PlaySE(6);
                        CScene::Unk759c90(m_palette, 0, 0, 0x32);
                        unk2c = 2;
                        m_game->unk1358 = 1;
                        m_game->unk135c = 0;
                        m_game->unk1360 = 0;
                        return 2;
                    }
                }
                if (m_game->m_pressC[v4] != 0 && unk540[0] == 0 && 1) {
                    unk540[0] = rand() % 0x17 + 0x3c;
                }
            }
            if (m_game->m_pressB[v4] != 0) {
                unk49e[v4] = 8;
                unk49e[(1 - v4)] = 8;
                unk540[0] = 0;
                unk540[1] = 0;
            }
        }
        if (unk49e[0] == 0 && m_game->m_pressB[0] != 0 && m_game->unk1343[0] == 0 || unk49e[1] == 0 && m_game->m_pressB[1] != 0 && m_game->unk1343[1] == 0) {
            unk2d = 1;
        }
        *(char*)&unk49c[v4] = m_game->m_inputX[v4] != 0 || m_game->m_inputY[v4] != 0;
    }
    if (unk49e[0] == 6 && unk49e[1] == 6) {
        if (unk494[0] >= 0x5a) {
            unk498[0] = (int)((cos(unk494[0] / 57.29579143313326) + 1.0) * 300.0);
            unk498[1] = (int)((cos(unk494[1] / 57.29579143313326) + 1.0) * 300.0);
            unk494[0] = unk494[0] - 5;
            unk494[1] = unk494[1] - 5;
        } else if (unk47c[3] < 0x3c) {
            unk470 = (int)(((cos(unk47c[3] / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            unk47c[3] += 3;
        } else {
            unk49e[0] = 7;
            unk49e[1] = 7;
            if (m_game->unkf32 < 0xa) {
                strcpy(v30, "system\\stage\\0");
            } else {
                strcpy(v30, "system\\stage\\");
            }
            _itoa(m_game->unkf32, v38, 0xa);
            strcat(v30, (const char*)v38);
            if (1) {
                strcat(v30, ".dat");
                m_game->LoadDat((IDirectDrawSurface**)&unk43c, (const char*)v30, 0, 0xbf);
                m_graphics->LoadPaletteDat(m_palette, "system\\stage\\all.dat", 0, 0xaf, 0x10);
                m_graphics->LoadPaletteDat(m_palette, (const char*)v30, 0, 0xbf, 0x40);
            } else {
                strcat(v30, ".bmp");
                m_graphics->LoadBmp((IDirectDrawSurface**)&unk43c, (const char*)v30, 0xbf);
                m_graphics->LoadPaletteBmp(m_palette, "system\\stage\\all.bmp", 0, 0xaf, 0x50);
                m_graphics->LoadPaletteBmp(m_palette, (const char*)v30, 0, 0xbf, 0x40);
            }
            unk44c[3] = m_graphics->GetColorKey((IDirectDrawSurface*)unk43c);
            m_graphics->SetPaletteRange(m_palette, 0xaf, 0x50);
        }
    } else if (unk49e[0] == 6) {
        if (m_game->m_pressB[0] != 0) {
            unk49e[0] = 2;
        }
    } else if (unk49e[1] == 6) {
        if (m_game->m_pressB[1] != 0) {
            unk49e[1] = 2;
        }
    } else if (unk49e[0] == 7) {
        if (unk47c[4] < 0x55) {
            unk47c[4] += 5;
        } else {
            unk47c[4] = 0x5a;
            unk49e[0] = 4;
            unk49e[1] = 4;
        }
    } else if (unk49e[0] == 8 || unk49e[1] == 8) {
        if (unk47c[4] > 0) {
            unk47c[4] -= 4;
        } else if (unk47c[3] > 0) {
            unk470 = (int)(((cos(unk47c[3] / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            unk47c[3] -= 3;
        } else {
            unk49e[0] = 0;
            unk49e[1] = 0;
        }
    }
    if (unk49e[0] == 5 || unk49e[1] == 5) {
        if (unk478 > 0) {
            unk450 = (int)(cos(unk478 * 1.5 / 57.29579143313326) * 240.0);
            unk478--;
        }
        if (unk47c[3] > 0) {
            unk470 = (int)(((cos(unk47c[3] / 57.29579143313326) - 0.5) * 2 - 1.0) * 240.0);
            unk47c[3]--;
            if (unk47c[3] == 0) {
                unk49e[0] = 0;
                unk49e[1] = 0;
            }
        }
    }
    unk458 = unk458 - unk47c[0];
    if (unk458 < 0.0) {
        unk458 = 0.0;
    }
    if (unk458 > 50.0) {
        unk458 = 50.0;
    }
    unk460 = unk460 - unk47c[1];
    if (unk460 < 0.0) {
        unk460 = 0.0;
    }
    if (unk460 > 50.0) {
        unk460 = 50.0;
    }
    unk468++;
    if (unk468 >= 240.0) {
        unk468 -= 240.0;
    }
    Draw();
    if (unk49e[0] == 9) {
        if (unk47c[5] < 0x5a) {
            unk47c[5] += 0xa;
        } else {
            unk47c[5] = 0;
            unk49e[0] = 4;
            unk49e[1] = 4;
            m_game->unkf32++;
            if (m_game->m_extraChars == 0 && m_game->unkf32 == 0xd) {
                m_game->unkf32 = 0x11;
            }
            if (m_game->m_extraChars == -1 && m_game->unkf32 == 0x12) {
                m_game->unkf32 = 0;
            }
            if (m_game->unkf32 >= 0x17) {
                m_game->unkf32 = 0;
            }
            Unk759460();
        }
    } else if (unk49e[0] == 0xa) {
        if (unk47c[5] < 0x5a) {
            unk47c[5] += 0xa;
        } else {
            unk47c[5] = 0;
            unk49e[0] = 4;
            unk49e[1] = 4;
            m_game->unkf32--;
            if (m_game->unkf32 < 0) {
                m_game->unkf32 = 0x16;
            }
            if (m_game->m_extraChars == 0 && m_game->unkf32 == 0x10) {
                m_game->unkf32 = 0xc;
            }
            if (m_game->m_extraChars == -1 && m_game->unkf32 == 0x16) {
                m_game->unkf32 = 0x11;
            }
            Unk759460();
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

    v10 = MakeRect(0, (int)unk450, 0x140, 0xf0);
    x20 = MakeRect(0, 0, 0x140, 0xf0);
    m_graphics->Blit(x20, (IDirectDrawSurface*)unk434, v10, 0, 0);
    if (m_game->unk1343[0] != 1 || m_game->unk1364 != 0) {
        v10 = MakeRect(0x85, 0x80, 0x16, 0xf0);
        x20 = MakeRect(5 - (int)unk458, (int)unk468, 0x16, 0xf0);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        x20 = MakeRect(5 - (int)unk458, (int)unk468 - 0xf0, 0x16, 0xf0);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
    }
    if (m_game->unk1343[1] != 1 || m_game->unk1364 != 0) {
        v10 = MakeRect(0xa5, 0x80, 0x16, 0xf0);
        x20 = MakeRect((int)unk460 + 0x124, 0 - (int)unk468, 0x16, 0xf0);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        x20 = MakeRect((int)unk460 + 0x124, 0 - (int)unk468 + 0xf0, 0x16, 0xf0);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
    }
    if (unk49e[0] > 0) {
        if (m_game->unk1364 != 0 && m_game->unk1364 != 2 || m_game->unk1343[0] != 1) {
            v10 = MakeRect(0, 0, 0x140, 0xf0);
            x20 = MakeRect(-0x50 - unk498[0] + unk4d4[(unk538[0] + unk53a[0] * 3)], 0, 0x140, 0xf0);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk444[0], v10, unk44c[0], 1);
            v10 = MakeRect(0xc0, 9, 0x7a, 0x5f);
            x20 = MakeRect(0 - unk498[0] / 2, 0x89, 0x7a, 0x5f);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
            v10 = MakeRect(0, (unk4a0[unk53c[0]] << 5) + 0x100, 0x7a, 0x20);
            x20 = MakeRect(0 - unk498[0] / 2, 0xc0, 0x7a, 0x20);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        }
        if (m_game->unk1338[0] != 0) {
            v10 = MakeRect(0, 0xe0, 0x80, 0x20);
            x20 = MakeRect(-0x10 - unk498[0] / 2, 5, 0x80, 0x20);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        }
    }
    if (unk49e[1] > 0) {
        if (m_game->unk1364 != 0 && m_game->unk1364 != 2 || m_game->unk1343[1] != 1) {
            v10 = MakeRect(0, 0, 0x140, 0xf0);
            x20 = MakeRect(unk498[1] + 0x50 - unk4d4[(unk538[1] + unk53a[1] * 3)], 0, 0x140, 0xf0);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk444[1], v10, unk44c[1], 0);
            v10 = MakeRect(0xc6, 0x89, 0x7a, 0x5f);
            x20 = MakeRect(unk498[1] / 2 + 0xc6, 0x89, 0x7a, 0x5f);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
            v10 = MakeRect(0xc6, (unk4a0[unk53c[1]] << 5) + 0x100, 0x7a, 0x20);
            x20 = MakeRect(unk498[1] / 2 + 0xc6, 0xc0, 0x7a, 0x20);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        }
        if (m_game->unk1338[1] != 0) {
            v10 = MakeRect(0, 0xe0, 0x80, 0x20);
            x20 = MakeRect(unk498[1] / 2 + 0xcf, 5, 0x80, 0x20);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        }
    }
    v10 = MakeRect(0, 0, 0x80, 0xd9);
    x20 = MakeRect(0x60, (int)unk470, 0x80, 0xd9);
    m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
    v10 = MakeRect(0x8a, 0x60, 0x29, 0x19);
    if (m_game->m_extraChars == 0) {
        x20 = MakeRect(0x67, (int)unk470 + 0x72, 0x29, 0x19);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        x20 = MakeRect(0x8f, (int)unk470 + 0x72, 0x29, 0x19);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        x20 = MakeRect(0xb7, (int)unk470 + 0x72, 0x29, 0x19);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        x20 = MakeRect(0xb1, (int)unk470 + 0xc0, 0x29, 0x19);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
    }
    if (m_game->m_extraChars == -1) {
        x20 = MakeRect(0x61, (int)unk470 + 0x8c, 0x29, 0x19);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        x20 = MakeRect(0x89, (int)unk470 + 0x8c, 0x29, 0x19);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        x20 = MakeRect(0x8f, (int)unk470 + 0xa6, 0x29, 0x19);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        x20 = MakeRect(0xb7, (int)unk470 + 0xa6, 0x29, 0x19);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
    }
    if (unk470 == 0.0) {
        if (unk53c[0] == unk53c[1] && (m_game->unk1343[0] != 1 || m_game->unk1364 != 0) && (m_game->unk1343[1] != 1 || m_game->unk1364 != 0)) {
            v10 = MakeRect(0x81, 0x40, 0x3f, 0x18);
            x20 = MakeRect(unk538[0] * 0x28 + 0x58 + (unk53a[0] % 2 == 0) * 6, unk53a[0] * 0x1a + 0xa, 0x3f, 0x18);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        } else {
            if (m_game->unk1343[1] != 1 || m_game->unk1364 != 0) {
                v10 = MakeRect(0x81, 0x20, 0x3f, 0x18);
                x20 = MakeRect(unk538[1] * 0x28 + 0x58 + (unk53a[1] % 2 == 0) * 6, unk53a[1] * 0x1a + 0xa, 0x3f, 0x18);
                m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
            }
            if (m_game->unk1343[0] != 1 || m_game->unk1364 != 0) {
                v10 = MakeRect(0x81, 0, 0x3f, 0x18);
                x20 = MakeRect(unk538[0] * 0x28 + 0x58 + (unk53a[0] % 2 == 0) * 6, unk53a[0] * 0x1a + 0xa, 0x3f, 0x18);
                m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
            }
        }
    }
    if ((unk49e[0] == 7 || unk49e[0] == 8 || unk49e[0] == 4) && m_game->unk1364 != 0 && m_game->unk1364 != 2) {
        if (unk540[0] == 0) {
            x24 = 0;
            a28 = 1;
            for (; a28 <= 7; a28++) {
                while (unk544[(m_game->unkf32 + a28 + x24) % 0x17] != 0) {
                    x24++;
                }
                v10 = MakeRect(0, (m_game->unkf32 + a28 + x24) % 0x17 << 5, 0xa0, 0x20);
                x20 = MakeRect(a28 * 0xb + 0xaa, 0xcd - a28 * 0x21 + (int)((double)(a28 * 0x21 + 0xbe) * cos(unk47c[4] / 57.29579143313326)), 0xa0, 0x20);
                m_graphics->Blit(x20, (IDirectDrawSurface*)unk440, v10, unk44c[2], 0);
            }
            v10 = MakeRect(0xa0, m_game->unkf32 << 5, 0xa0, 0x20);
            x20 = MakeRect(0xaa, (int)(cos(unk47c[4] / 57.29579143313326) * 190.0) + 0xcd, 0xa0, 0x20);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk440, v10, unk44c[2], 0);
            v10 = MakeRect(1, 0, 0xc3, 0xde);
            x20 = MakeRect(0 - (int)(cos(unk47c[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk43c, v10, unk44c[3], 0);
        } else {
            v2c = 0;
            v30 = 0;
            for (; v30 <= 8; v30++) {
                while (unk544[(m_game->unkf32 + v30 + v2c) % 0x17] != 0) {
                    v2c++;
                }
                v10 = MakeRect(0, (m_game->unkf32 + v30 + v2c) % 0x17 << 5, 0xa0, 0x20);
                x20 = MakeRect(v30 * 0xb + 0xaa, 0xcd - v30 * 0x21 + (int)((double)(v30 * 0x21 + 0xbe) * cos(unk47c[4] / 57.29579143313326)), 0xa0, 0x20);
                m_graphics->Blit(x20, (IDirectDrawSurface*)unk440, v10, unk44c[2], 0);
            }
            v10 = MakeRect(0, 0x3d9, 0xc3, 0xde);
            x20 = MakeRect(0 - (int)(cos(unk47c[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk438, v10, m_colorKey, 0);
        }
    } else if (unk49e[0] == 9) {
        v34 = 0;
        v38 = 0;
        for (; v38 <= 8; v38++) {
            while (unk544[(m_game->unkf32 + v38 + v34) % 0x17] != 0) {
                v34++;
            }
            v10 = MakeRect(0, (m_game->unkf32 + v38 + v34) % 0x17 << 5, 0xa0, 0x20);
            x20 = MakeRect(v38 * 0xb + 0xaa - (int)(sin(unk47c[5] / 57.29579143313326) * 11.0), 0xcd - v38 * 0x21 + (int)((double)(v38 * 0x21 + 0xbe) * cos(unk47c[4] / 57.29579143313326)) + (int)(sin(unk47c[5] / 57.29579143313326) * 33.0), 0xa0, 0x20);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk440, v10, unk44c[2], 0);
        }
        v10 = MakeRect(1, 0, 0xc3, 0xde);
        x20 = MakeRect(0 - (int)(cos(unk47c[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk43c, v10, unk44c[3], 0);
    } else if (unk49e[0] == 0xa) {
        x3c = 0;
        l40 = 0;
        for (; l40 <= 8; l40++) {
            while (unk544[(m_game->unkf32 + l40 + 0x17 + x3c) % 0x17] != 0) {
                x3c++;
            }
            v10 = MakeRect(0, (m_game->unkf32 + l40 + 0x17 + x3c) % 0x17 << 5, 0xa0, 0x20);
            x20 = MakeRect(l40 * 0xb + 0xaa + (int)(sin(unk47c[5] / 57.29579143313326) * 11.0), 0xcd - l40 * 0x21 + (int)((double)(l40 * 0x21 + 0xbe) * cos(unk47c[4] / 57.29579143313326)) - (int)(sin(unk47c[5] / 57.29579143313326) * 33.0), 0xa0, 0x20);
            m_graphics->Blit(x20, (IDirectDrawSurface*)unk440, v10, unk44c[2], 0);
        }
        l40 = -1;
        x3c = 0;
        while (unk544[(m_game->unkf32 + l40 + 0x17 + x3c) % 0x17] != 0) {
            x3c--;
        }
        v10 = MakeRect(0, (m_game->unkf32 + l40 + 0x17 + x3c) % 0x17 << 5, 0xa0, 0x20);
        x20 = MakeRect(l40 * 0xb + 0xaa + (int)(sin(unk47c[5] / 57.29579143313326) * 11.0), 0xcd - l40 * 0x21 + (int)((double)(l40 * 0x21 + 0xbe) * cos(unk47c[4] / 57.29579143313326)) - (int)(sin(unk47c[5] / 57.29579143313326) * 33.0), 0xa0, 0x20);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk440, v10, unk44c[2], 0);
        v10 = MakeRect(1, 0, 0xc3, 0xde);
        x20 = MakeRect(0 - (int)(cos(unk47c[4] / 57.29579143313326) * 230.0), 0, 0xc3, 0xde);
        m_graphics->Blit(x20, (IDirectDrawSurface*)unk43c, v10, unk44c[3], 0);
    }
    m_graphics->Flip();
}

void CScene1::Unk7586b0(CPlayer** p1, CPlayer** p2, char p3)
{
    char v2c[40];

    switch (unk53c[p3]) {
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
    (*p1)->m_charId = unk53c[p3];
    m_players[p3] = *p1;
    (*p1)->m_cpu = m_game->unk1343[p3];
    if (1) {
        strcpy(v2c, "system\\");
        strcat(v2c, (*p1)->m_name);
        strcat(v2c, "\\");
        strcat(v2c, (*p1)->m_name);
        strcat(v2c, ".dat");
        m_game->LoadDat((IDirectDrawSurface**)&unk444[p3], (const char*)v2c, 0, p3 * 0x28 + 0xaf);
        m_graphics->LoadPaletteDat(m_palette, (const char*)v2c, unk53e[p3] * 0x28, p3 * 0x28 + 0xaf, 0x28);
    } else {
        strcpy(v2c, "system\\");
        strcat(v2c, (*p1)->m_name);
        strcat(v2c, "\\");
        strcat(v2c, (*p1)->m_name);
        strcat(v2c, ".bmp");
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk444[p3], (const char*)v2c, p3 * 0x28 + 0xaf);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v2c, unk53e[p3] * 0x28, p3 * 0x28 + 0xaf, 0x28);
    }
    m_graphics->SetPalette(m_palette);
    unk44c[p3] = m_graphics->GetColorKey((IDirectDrawSurface*)unk444[p3]);
}

void CScene1::Unk759460()
{
    char v34[8];
    char v2c[40];

    if (m_game->unkf32 < 0xa) {
        strcpy(v2c, "system\\stage\\0");
    } else {
        strcpy(v2c, "system\\stage\\");
    }
    _itoa(m_game->unkf32, v34, 0xa);
    strcat(v2c, (const char*)v34);
    if (1) {
        strcat(v2c, ".dat");
        m_game->LoadDat((IDirectDrawSurface**)&unk43c, (const char*)v2c, 0, 0xbf);
        m_graphics->LoadPaletteDat(m_palette, (const char*)v2c, 0, 0xbf, 0x40);
    } else {
        strcat(v2c, ".bmp");
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk43c, (const char*)v2c, 0xbf);
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v2c, 0, 0xbf, 0x40);
    }
    unk44c[3] = m_graphics->GetColorKey((IDirectDrawSurface*)unk43c);
    m_graphics->SetPaletteRange(m_palette, 0xaf, 0x50);
}

void CScene1::Unk7595d0(char p1)
{
    char v2c[40];

    if (1) {
        strcpy(v2c, "system\\");
        strcat(v2c, m_players[p1]->m_name);
        strcat(v2c, "\\");
        strcat(v2c, m_players[p1]->m_name);
        strcat(v2c, ".dat");
        m_graphics->LoadPaletteDat(m_palette, (const char*)v2c, unk53e[p1] * 0x28, p1 * 0x28 + 0xaf, 0x28);
    } else {
        strcpy(v2c, "system\\");
        strcat(v2c, m_players[p1]->m_name);
        strcat(v2c, "\\");
        strcat(v2c, m_players[p1]->m_name);
        strcat(v2c, ".bmp");
        m_graphics->LoadPaletteBmp(m_palette, (const char*)v2c, unk53e[p1] * 0x28, p1 * 0x28 + 0xaf, 0x28);
    }
    m_graphics->SetPaletteRange(m_palette, p1 * 0x28 + 0xaf, 0x28);
}

void CScene1::Vf2()
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

void CScene1::Unk7598d0()
{
    unk49c[0] = 0;
    unk49c[1] = 0;
    unk450 = 0.0;
    unk478 = 0x3c;
    unk458 = 50.0;
    unk47c[0] = 0;
    unk460 = 50.0;
    unk47c[1] = 0;
    unk468 = 0.0;
    unk47c[2] = 0;
    unk470 = -480.0;
    unk47c[3] = 0x3c;
    unk47c[4] = 0;
    unk47c[5] = 0;
    unk498[0] = 0x12c;
    unk498[1] = 0x12c;
    unk494[0] = 0xb4;
    unk494[1] = 0xb4;
    unk49e[0] = 5;
    unk49e[1] = 5;
    unk540[0] = 0;
    unk540[1] = 0;
    unk53e[0] = 0;
    unk53e[1] = 0;
    m_game->unk1378 = 0;
    m_game->unk1379 = 0;
    m_game->unk1338[0] = 0;
    m_game->unk1338[1] = 0;
    if (m_game->unk1364 < 5) {
        if (1) {
            m_graphics->LoadPaletteDat(m_palette, "system\\chr_sel_bg.dat", 0, 1, 0x30);
        } else {
            m_graphics->LoadPaletteBmp(m_palette, "system\\chr_sel_bg.bmp", 0, 1, 0x30);
        }
        if (m_game->unk1364 == 0 || m_game->unk1364 == 2) {
            if (m_game->unk1343[0] == 1) {
                unk49e[0] = 4;
                unk53e[0] = -1;
            } else {
                unk49e[1] = 4;
                unk53e[1] = -1;
            }
        }
        m_game->m_replayMode = 0;
    }
    memset((void*)&unk544[0], 0, 0x17);
    if (m_game->m_extraChars == 0) {
        unk551 = 1;
        unk552 = 1;
        unk553 = 1;
        unk554 = 1;
    } else if (m_game->m_extraChars == -1) {
        unk556 = 1;
        unk557 = 1;
        unk558 = 1;
        unk559 = 1;
        unk55a = 1;
    }
    if ((m_game->unk1364 == 5 || m_game->unk1364 == 1) && m_game->m_extraChars != 0) {
        m_game->PlayMusic(1);
    } else {
        m_game->PlayMusic(0);
    }
    Draw();
    CScene::Unk759e20(m_palette, 1);
    unk2c = 0;
}
