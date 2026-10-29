// CScene5 (0x7712f0-0x7758af), scene 5: the result screen after a match (system\result,
// system\winner). The <math.h> overload pow(int, int) it calls follows it:
// FUNCTION: 0x775810 ?pow@@YANHH@Z
// FUNCTION: 0x775830 ??$_Pow_int@H@@YAHHH@Z
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene5::CScene5(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        m_game->LoadDat((IDirectDrawSurface**)&unk434, "system\\winner.dat", 0, 0xaf);
        m_game->LoadDat((IDirectDrawSurface**)&unk438, "system\\result.dat", 0, 0xaf);
    } else {
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk434, "system\\winner.bmp", 0xaf);
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk438, "system\\result.bmp", 0xaf);
    }
    unk43c = 0;
    unk440 = 0;
    unk2c = 1;
    unk2d = 0;
    unk45f = 0;
}

CScene5::~CScene5()
{
    if (unk434 != 0) {
        ((IUnknown*)unk434)->Release();
        unk434 = 0;
    }
    if (unk438 != 0) {
        ((IUnknown*)unk438)->Release();
        unk438 = 0;
    }
    if (unk43c != 0) {
        ((IUnknown*)unk43c)->Release();
        unk43c = 0;
    }
    if (unk440 != 0) {
        ((IUnknown*)unk440)->Release();
        unk440 = 0;
    }
}

BYTE CScene5::Update()
{
    if (unk2c == 1) {
        unk45e = 0;
        unk45f = 0;
        m_players[0] = *m_player1Ref;
        m_players[1] = *m_player2Ref;
        Unk774b00();
        m_game->StopMusic();
        CScene::Unk759e20(m_game->m_palette, 1);
        unk2c = 0;
    } else if (unk2d == 1) {
        CScene::Unk759c90(m_game->m_palette, m_game->unk1364 != 0, 0, 0x64);
        m_game->unk1360 |= 1 << (char)m_game->unkf32;
        if ((int)m_game->m_background != 0) {
            delete (char*)m_game->m_background;
            m_game->m_background = (CAnimBg*)0;
        }
        if (m_game->m_replayMode > 0) {
            (&m_game->m_replay)->Close();
        }
        if (m_game->unk1364 == 0) {
            if (m_game->unk134c == m_game->unk1342) {
                if (m_game->unk1358 == 8) {
                    delete *m_player1Ref;
                    delete *m_player2Ref;
                    *m_player1Ref = (CPlayer*)0;
                    *m_player2Ref = (CPlayer*)0;
                    unk2d = 0;
                    unk2c = 1;
                    return 7;
                }
                if (m_game->unk1342 == 1) {
                    m_game->unk135c |= 1 << (*m_player1Ref)->unk8d;
                    delete *m_player1Ref;
                    *m_player1Ref = (CPlayer*)0;
                } else {
                    m_game->unk135c |= 1 << (*m_player2Ref)->unk8d;
                    delete *m_player2Ref;
                    *m_player2Ref = (CPlayer*)0;
                }
                m_game->unk1358++;
                m_game->unk1378 = 0;
                unk2d = 0;
                unk2c = 1;
                return 2;
            }
            if ((unsigned char)m_game->unk1378 > 0) {
                unk2d = 0;
                unk2c = 1;
                return 2;
            }
            delete *m_player1Ref;
            delete *m_player2Ref;
            *m_player1Ref = (CPlayer*)0;
            *m_player2Ref = (CPlayer*)0;
            unk2d = 0;
            unk2c = 1;
            return 1;
        }
        if (m_game->unk1364 == 2 && m_game->unk134c == m_game->unk1342 && m_game->unk1358 < 8) {
            if (m_game->unk1342 == 1) {
                m_game->unk135c |= 1 << (*m_player1Ref)->unk8d;
                delete *m_player1Ref;
                *m_player1Ref = (CPlayer*)0;
            } else {
                m_game->unk135c |= 1 << (*m_player2Ref)->unk8d;
                delete *m_player2Ref;
                *m_player2Ref = (CPlayer*)0;
            }
            m_game->unk1358++;
            unk2d = 0;
            unk2c = 1;
            return 2;
        }
        if (m_game->unk1364 == 6) {
            delete *m_player1Ref;
            delete *m_player2Ref;
            *m_player1Ref = (CPlayer*)0;
            *m_player2Ref = (CPlayer*)0;
            unk2d = 0;
            unk2c = 1;
            return 0;
        }
        delete *m_player1Ref;
        delete *m_player2Ref;
        *m_player1Ref = (CPlayer*)0;
        *m_player2Ref = (CPlayer*)0;
        unk2d = 0;
        unk2c = 1;
        return 1;
    }
    Vf2();
    if (unk45c < 0x3c) {
        unk45c++;
        if (m_game->unk134c == 1) {
            m_players[0]->Vf6();
            m_players[0]->Unk40f580();
            m_players[0]->Vf6();
            m_players[0]->Unk40f580();
            m_players[0]->Vf6();
            m_players[0]->Unk40f580();
            if (m_players[0]->unk2c9 >= 0 && m_players[0]->unk2c9 < 0x41) {
                m_sound->Play((short)m_game->m_sounds[m_players[0]->unk2c9], 0);
                m_players[0]->unk2c9 = -1;
            }
        } else {
            m_players[1]->Vf6();
            m_players[1]->Unk40f580();
            m_players[1]->Vf6();
            m_players[1]->Unk40f580();
            m_players[1]->Vf6();
            m_players[1]->Unk40f580();
            if (m_players[1]->unk2c9 >= 0 && m_players[1]->unk2c9 < 0x41) {
                m_sound->Play((short)m_game->m_sounds[m_players[1]->unk2c9], 0);
                m_players[1]->unk2c9 = -1;
            }
        }
        if (unk45c == 0x3c) {
            if (m_players[m_game->unk134c]->unk8d == 0x13 || m_players[m_game->unk134c]->unk8d == 0x14 || m_players[m_game->unk134c]->unk8d == 0x15 || m_players[m_game->unk134c]->unk8d == 0x17) {
                m_game->PlayMusic(4);
            } else if (m_players[m_game->unk134c]->unk8d == 0xe) {
                m_game->PlayMusic(9);
            } else if (m_players[m_game->unk134c]->unk8d == 1 || m_players[m_game->unk134c]->unk8d == 0x10 || m_players[m_game->unk134c]->unk8d == 0x11 || m_players[m_game->unk134c]->unk8d == 0xd || m_players[m_game->unk134c]->unk8d == 0xf || m_players[m_game->unk134c]->unk8d == 2 || m_players[m_game->unk134c]->unk8d == 3 || m_players[m_game->unk134c]->unk8d == 8 || m_players[m_game->unk134c]->unk8d == 9 || m_players[m_game->unk134c]->unk8d == 0xa) {
                m_game->PlayMusic(2);
            } else {
                m_game->PlayMusic(3);
            }
            unk45e = 1;
        }
    }
    if (unk444 > 0x28 && unk45c >= 0x3c) {
        unk444 -= unk446 / 3;
        if (unk444 < 0x78 && unk446 > 1) {
            unk446--;
        }
    }
    m_game->UpdateInput();
    if (unk45e == 2) {
        if (m_game->m_inputX[m_game->unk1342] != 0 && unk460 == 0) {
            unk45f++;
            m_game->PlaySE(8);
            if (unk45f > 1) {
                unk45f = 0;
            }
            unk460 = 1;
        }
        if (m_game->m_inputX[m_game->unk1342] == 0) {
            unk460 = 0;
        }
        if ((char)m_game->m_pressA[m_game->unk1342] != 0) {
            m_game->PlaySE(6);
            if (unk45f == 0) {
                if (m_game->unk1358 < 8) {
                    m_game->unk1379 = m_game->unk1358;
                } else {
                    m_game->unk1379 = 0;
                }
                m_game->unk1378 = 1;
                unk2d = 1;
            } else {
                m_game->unk1378 = 0;
                unk2d = 1;
            }
        }
    } else if ((char)m_game->m_pressA[0] != 0 || (char)m_game->m_pressB[0] != 0 || (char)m_game->m_pressC[0] != 0 || (char)m_game->m_pressD[0] != 0 || (char)m_game->m_pressA[1] != 0 || (char)m_game->m_pressB[1] != 0 || (char)m_game->m_pressC[1] != 0 || (char)m_game->m_pressD[1] != 0) {
        if (m_game->unk1364 == 0 && m_game->unk134c != m_game->unk1342 && unk45e < 2) {
            if (unk45e == 0) {
                if (m_players[m_game->unk134c]->unk8d == 0x13 || m_players[m_game->unk134c]->unk8d == 0x14 || m_players[m_game->unk134c]->unk8d == 0x15 || m_players[m_game->unk134c]->unk8d == 0x17) {
                    m_game->PlayMusic(4);
                } else if (m_players[m_game->unk134c]->unk8d == 1 || m_players[m_game->unk134c]->unk8d == 2 || m_players[m_game->unk134c]->unk8d == 3 || m_players[m_game->unk134c]->unk8d == 8 || m_players[m_game->unk134c]->unk8d == 9 || m_players[m_game->unk134c]->unk8d == 0xa) {
                    m_game->PlayMusic(2);
                } else {
                    m_game->PlayMusic(3);
                }
            }
            unk45e = 2;
            unk454 = -0xa0;
            unk458 = 0;
            unk444 = 0x28;
            unk450 = 0xa0;
            unk45c = 0x3c;
        } else if (m_game->unk1364 == 2 && unk45e < 2) {
            if (unk45e == 0) {
                if (m_players[m_game->unk134c]->unk8d == 0x13 || m_players[m_game->unk134c]->unk8d == 0x14 || m_players[m_game->unk134c]->unk8d == 0x15 || m_players[m_game->unk134c]->unk8d == 0x17) {
                    m_game->PlayMusic(4);
                } else if (m_players[m_game->unk134c]->unk8d == 1 || m_players[m_game->unk134c]->unk8d == 2 || m_players[m_game->unk134c]->unk8d == 3 || m_players[m_game->unk134c]->unk8d == 8 || m_players[m_game->unk134c]->unk8d == 9 || m_players[m_game->unk134c]->unk8d == 0xa) {
                    m_game->PlayMusic(2);
                } else {
                    m_game->PlayMusic(3);
                }
            }
            unk45e = 3;
            unk454 = -0xa0;
            unk458 = 0;
            unk444 = 0x28;
            unk450 = 0xa0;
            unk45c = 0x3c;
        } else {
            unk2d = 1;
        }
    }
    unk448 = unk448 + 2;
    if (unk448 >= 0x140) {
        unk448 = 0;
    }
    unk44a = unk44a + 1;
    if (unk44a >= 0xf0) {
        unk44a = 0;
    }
    unk44c = unk44c - 2;
    if (unk44c < 0) {
        unk44c = 0x140;
    }
    unk44e = unk44e - 1;
    if (unk44e < 0) {
        unk44e = 0xf0;
    }
    if (unk450 < 0xa0 && unk454 <= -0x50) {
        unk450 += unk452;
        if (unk450 > 0x73) {
            unk452--;
        }
    }
    if (unk454 > -0xa0 && unk444 < 0xa0) {
        unk454 -= unk456;
        if (unk454 < -0x28) {
            unk456--;
        }
    }
    if (unk458 < 0 && unk450 > 0x78) {
        unk458 += unk45a;
        if (unk458 >= 0 && m_game->unk1364 == 6) {
            unk2d = 1;
        }
        if (unk458 > -0x78) {
            unk45a--;
        }
    }
    Draw();
    return 5;
}

void CScene5::Draw()
{
    int v8;
    int v4;

    m_graphics->Blit(MakeRect(0, 0, 0x140, 0xa0), m_game->unke98, MakeRect(unk444, 0x140, 0x140, 0xa0), 0, 0);
    m_graphics->FillRect(MakeRect(0, 0xa0, 0x140, 0x50), 0xb0);
    if (m_game->unk134c == 1) {
        m_players[0]->Unk4121a0(-unk444, -0x50);
    } else {
        m_players[1]->Unk4121a0(-unk444, -0x50);
    }
    m_graphics->FillRect(MakeRect(0x140 - unk450, 0, unk450, 0xf0), 0xe7);
    m_graphics->FillRect(MakeRect(0, 0, unk450, 0xf0), 0xe7);
    v4 = -0xf0;
    for (; v4 <= 0xf0; v4 += 0x50) {
        if (unk44c <= 0xa0) {
            m_graphics->Blit(MakeRect(unk450 - 0xa0, unk44e + v4, 0xa0, 0x30), (IDirectDrawSurface*)unk434, MakeRect(unk44c, 0x30, 0xa0, 0x30), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - unk450 + 0xa0, unk44e + v4, 0xa0 - unk44c, 0x30), (IDirectDrawSurface*)unk434, MakeRect(unk44c + 0xa0, 0x30, 0xa0 - unk44c, 0x30), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - unk450 + 0x140 - unk44c, unk44e + v4, unk44c, 0x30), (IDirectDrawSurface*)unk434, MakeRect(0, 0x30, unk44c, 0x30), (char)m_game->m_colorKey, 0);
        } else {
            m_graphics->Blit(MakeRect(unk450 - 0xa0, unk44e + v4, 0x140 - unk44c, 0x30), (IDirectDrawSurface*)unk434, MakeRect(unk44c, 0x30, 0x140 - unk44c, 0x30), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(unk450 + 0xa0 - unk44c, unk44e + v4, unk44c - 0xa0, 0x30), (IDirectDrawSurface*)unk434, MakeRect(0, 0x30, unk44c - 0xa0, 0x30), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - unk450 + 0xa0, unk44e + v4, 0xa0, 0x30), (IDirectDrawSurface*)unk434, MakeRect(unk44c - 0xa0, 0x30, 0xa0, 0x30), (char)m_game->m_colorKey, 0);
        }
    }
    v4 = -0xf0;
    for (; v4 <= 0xf0; v4 += 0x50) {
        if (unk448 <= 0xa0) {
            m_graphics->Blit(MakeRect(unk450 - 0xa0, unk44a + v4, 0xa0, 0x30), (IDirectDrawSurface*)unk434, MakeRect(unk448, 0, 0xa0, 0x30), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - unk450 + 0xa0, unk44a + v4, 0xa0 - unk448, 0x30), (IDirectDrawSurface*)unk434, MakeRect(unk448 + 0xa0, 0, 0xa0 - unk448, 0x30), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - unk450 + 0x140 - unk448, unk44a + v4, unk448, 0x30), (IDirectDrawSurface*)unk434, MakeRect(0, 0, unk448, 0x30), (char)m_game->m_colorKey, 0);
        } else {
            m_graphics->Blit(MakeRect(unk450 - 0xa0, unk44a + v4, 0x140 - unk448, 0x30), (IDirectDrawSurface*)unk434, MakeRect(unk448, 0, 0x140 - unk448, 0x30), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(unk450 + 0xa0 - unk448, unk44a + v4, unk448 - 0xa0, 0x30), (IDirectDrawSurface*)unk434, MakeRect(0, 0, unk448 - 0xa0, 0x30), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - unk450 + 0xa0, unk44a + v4, 0xa0, 0x30), (IDirectDrawSurface*)unk434, MakeRect(unk448 - 0xa0, 0, 0xa0, 0x30), (char)m_game->m_colorKey, 0);
        }
    }
    m_graphics->Blit(MakeRect(unk454 + 0x50, 0, 0x140, 0xf0), (IDirectDrawSurface*)unk440, MakeRect(0, 0, 0x140, 0xf0), m_colorKey, 0);
    if (unk45e < 2) {
        m_graphics->Blit(MakeRect(0, unk458, 0x140, 0xf0), (IDirectDrawSurface*)unk43c, MakeRect(0, 0, 0x140, 0xf0), (char)m_game->m_colorKey, 0);
    } else if (unk45e == 2) {
        m_graphics->Blit(MakeRect(0x57, 0x5a, 0x99, 0x19), (IDirectDrawSurface*)unk438, MakeRect(0, 0x1da, 0x99, 0x19), (char)m_game->m_colorKey, 0);
        if (unk45f == 0) {
            m_graphics->Blit(MakeRect(0x68, 0x7c, 0x33, 0x15), (IDirectDrawSurface*)unk438, MakeRect(0, 0x1f3, 0x33, 0x15), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xb4, 0x7e, 0x1e, 0x10), (IDirectDrawSurface*)unk438, MakeRect(0x26, 0x208, 0x1e, 0x10), (char)m_game->m_colorKey, 0);
        } else {
            m_graphics->Blit(MakeRect(0x6e, 0x7e, 0x26, 0xf), (IDirectDrawSurface*)unk438, MakeRect(0, 0x208, 0x26, 0xf), (char)m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xaf, 0x7c, 0x27, 0x14), (IDirectDrawSurface*)unk438, MakeRect(0x33, 0x1f4, 0x27, 0x14), (char)m_game->m_colorKey, 0);
        }
    } else if (unk45e == 3) {
        m_graphics->Blit(MakeRect(0x49, 9, 0xd6, 0x2a), (IDirectDrawSurface*)unk438, MakeRect(0, (m_game->unk1358 - 1) * 0x2a, 0xd6, 0x2a), (char)m_game->m_colorKey, 0);
        m_graphics->Blit(MakeRect(9, 0x3b, 0x34, 0x12), (IDirectDrawSurface*)unk438, MakeRect(0, 0x161, 0x34, 0x12), (char)m_game->m_colorKey, 0);
        Unk774a10(0x136, 0x3a, unk464);
        m_graphics->Blit(MakeRect(9, 0x56, 0x6a, 0x1d), (IDirectDrawSurface*)unk438, MakeRect(0, 0x173, 0x6a, 0x1d), (char)m_game->m_colorKey, 0);
        Unk774a10(0x136, 0x5b, unk468);
        m_graphics->Blit(MakeRect(9, 0x75, 0x75, 0x21), (IDirectDrawSurface*)unk438, MakeRect(0, 0x190, 0x75, 0x21), (char)m_game->m_colorKey, 0);
        Unk774a10(0x136, 0x7c, unk46c);
        m_graphics->Blit(MakeRect(9, 0x9c, 0x7e, 0x16), (IDirectDrawSurface*)unk438, MakeRect(0, 0x1b1, 0x7e, 0x16), (char)m_game->m_colorKey, 0);
        Unk774a10(0x136, 0x9d, unk470);
        m_graphics->Blit(MakeRect(9, 0xbe, 0x4a, 0x12), (IDirectDrawSurface*)unk438, MakeRect(0x34, 0x161, 0x4a, 0x12), (char)m_game->m_colorKey, 0);
        m_graphics->Blit(MakeRect(0x12a, 0xbb, 0xb, 0x11), (IDirectDrawSurface*)unk438, MakeRect(0xb2, 0x1c8, 0xb, 0x11), (char)m_game->m_colorKey, 0);
        Unk774a10(0x128, 0xba, m_players[m_game->unk1342]->m_hitsLanded);
        Unk774a10(0x136, 0xd7, m_players[m_game->unk1342]->m_score);
        if ((unsigned long)m_players[m_game->unk1342]->m_scoreHigh > 0) {
            Unk774a10(0xc6, 0xd7, m_players[m_game->unk1342]->m_scoreHigh);
            v8 = 1;
            for (; v8 < 8; v8++) {
                if ((double)(unsigned long)m_players[m_game->unk1342]->m_score / pow(0xa, 8 - v8) < 1.0) {
                    Unk774a10(v8 * 0xe + 0xc6, 0xd7, 0);
                }
            }
        }
    }
    m_graphics->Flip();
}

void CScene5::Unk774a10(int p1, int p2, int p3)
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
        v2c.top = 0x1c7;
        v2c.bottom = 0x1da;
        v2c.left = v1c << 4;
        v2c.right = v1c + 1 << 4;
        l18.top = p2;
        l18.bottom = p2 + 0x13;
        l18.right = l4;
        l18.left = l4 - 0x10;
        m_graphics->Blit(l18, (IDirectDrawSurface*)unk438, v2c, (char)m_game->m_colorKey, 0);
        l4 -= 0xe;
        x8 = x8 / 0xa;
    } while (x8 > 0);
}

void CScene5::Unk774b00()
{
    int x3c;
    int v38;
    char v34[40];
    char vc[8];

    v38 = rand() % m_players[m_game->unk134c]->unk30f4;
    if (unk440 != 0) {
        ((IUnknown*)unk440)->Release();
        unk440 = 0;
    }
    if (unk43c != 0) {
        ((IUnknown*)unk43c)->Release();
        unk43c = 0;
    }
    strcpy(v34, "system\\");
    strcat(v34, m_players[m_game->unk134c]->m_name);
    strcat(v34, "\\");
    strcat(v34, m_players[m_game->unk134c]->m_name);
    if (1) {
        strcat(v34, ".dat");
        m_game->LoadDat((IDirectDrawSurface**)&unk440, (const char*)v34, 0, m_game->unk134c * 0x28 + 0x5f);
        m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v34, m_players[m_game->unk134c]->m_paletteIndex * 0x28, m_game->unk134c * 0x28 + 0x5f, 0x28);
    } else {
        strcat(v34, ".bmp");
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk440, (const char*)v34, m_game->unk134c * 0x28 + 0x5f);
        m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)v34, m_players[m_game->unk134c]->m_paletteIndex * 0x28, m_game->unk134c * 0x28 + 0x5f, 0x28);
    }
    m_colorKey = m_graphics->GetColorKey((IDirectDrawSurface*)unk440);
    x3c = 0;
    for (; x3c < 0x14; x3c++) {
        if (m_players[(1 - m_game->unk134c)]->unk8d == m_players[m_game->unk134c]->unk30f5[x3c]) {
            v38 = x3c + 0xa;
        }
    }
    strcpy(v34, "system\\");
    strcat(v34, m_players[m_game->unk134c]->m_name);
    strcat(v34, "\\");
    _itoa(v38, vc, 0xa);
    if (v38 < 0xa) {
        strcat(v34, "0");
    }
    strcat(v34, (const char*)vc);
    if (1) {
        strcat(v34, ".dat");
        m_game->LoadDat((IDirectDrawSurface**)&unk43c, (const char*)v34, 0, 0xaf);
    } else {
        strcat(v34, ".bmp");
        m_graphics->LoadBmp((IDirectDrawSurface**)&unk43c, (const char*)v34, 0xaf);
    }
    if (m_game->unk1364 == 4) {
        if (m_game->unk134c == 0) {
            ((CharRecord*)&m_players[0]->unk3118)->Load(m_players[0]->m_name);
            m_players[0]->unk311c++;
            ((CharRecord*)&m_players[0]->unk3118)->Save(m_players[0]->m_name);
            ((CharRecord*)&m_players[1]->unk3118)->Load(m_players[1]->m_name);
            m_players[1]->unk3120++;
            ((CharRecord*)&m_players[1]->unk3118)->Save(m_players[1]->m_name);
        } else {
            ((CharRecord*)&m_players[1]->unk3118)->Load(m_players[1]->m_name);
            m_players[1]->unk311c++;
            ((CharRecord*)&m_players[1]->unk3118)->Save(m_players[1]->m_name);
            ((CharRecord*)&m_players[0]->unk3118)->Load(m_players[0]->m_name);
            m_players[0]->unk3120++;
            ((CharRecord*)&m_players[0]->unk3118)->Save(m_players[0]->m_name);
        }
    }
    if (m_game->unk1364 == 2) {
        unk464 = (unsigned long)m_players[m_game->unk1342]->unk30dc / 0x64;
        m_players[m_game->unk1342]->m_hitsLanded += unk464;
        unk468 = m_players[m_game->unk1342]->m_maxHits << 1;
        m_players[m_game->unk1342]->m_hitsLanded += unk468;
        unk46c = (unsigned long)m_players[m_game->unk1342]->m_maxDamage / 0x64;
        m_players[m_game->unk1342]->m_hitsLanded += unk46c;
        unk470 = m_game->unk1358 * 0x32 * (m_players[(1 - m_game->unk1342)]->unkac == 0);
        m_players[m_game->unk1342]->m_hitsLanded += unk470;
        ((CharRecord*)&m_players[m_game->unk1342]->unk3118)->Load(m_players[m_game->unk1342]->m_name);
        if ((unsigned long)m_players[m_game->unk1342]->unk3128 < m_players[m_game->unk1342]->m_scoreHigh) {
            m_players[m_game->unk1342]->unk3124 = m_players[m_game->unk1342]->m_score;
            m_players[m_game->unk1342]->unk3128 = m_players[m_game->unk1342]->m_scoreHigh;
        } else if (m_players[m_game->unk1342]->unk3128 == m_players[m_game->unk1342]->m_scoreHigh && m_players[m_game->unk1342]->unk3124 < m_players[m_game->unk1342]->m_score) {
            m_players[m_game->unk1342]->unk3124 = m_players[m_game->unk1342]->m_score;
        }
        ((CharRecord*)&m_players[m_game->unk1342]->unk3118)->Save(m_players[m_game->unk1342]->m_name);
    }
    if ((char)m_game->unk1370 == 2) {
        if (m_game->unk1343[0] == 0) {
            ((CharRecord*)&m_players[0]->unk3118)->Load(m_players[0]->m_name);
            if (m_players[0]->unk3130 < m_players[0]->m_maxHits) {
                m_players[0]->unk3130 = m_players[0]->m_maxHits;
            }
            if (m_players[0]->unk3134 < m_players[0]->m_maxDamage) {
                m_players[0]->unk3134 = m_players[0]->m_maxDamage;
            }
            ((CharRecord*)&m_players[0]->unk3118)->Save(m_players[0]->m_name);
        }
        if (m_game->unk1343[1] == 0) {
            ((CharRecord*)&m_players[1]->unk3118)->Load(m_players[1]->m_name);
            if (m_players[1]->unk3130 < m_players[1]->m_maxHits) {
                m_players[1]->unk3130 = m_players[1]->m_maxHits;
            }
            if (m_players[1]->unk3134 < m_players[1]->m_maxDamage) {
                m_players[1]->unk3134 = m_players[1]->m_maxDamage;
            }
            ((CharRecord*)&m_players[1]->unk3118)->Save(m_players[1]->m_name);
        }
    }
    unk444 = 0xf0;
    unk446 = 0x12;
    unk448 = 0;
    unk44a = 0;
    unk44c = 0;
    unk44e = 0;
    unk450 = -2;
    unk454 = 0x140;
    unk458 = -0xf0;
    unk452 = 9;
    unk456 = 0xf;
    unk45a = 0xf;
    unk45c = 0;
    if (m_game->unk134c == 1) {
        m_players[0]->x = 480.0;
        m_players[0]->y = -240.0;
        m_players[0]->facing = -1;
        m_players[0]->pattern = 0x2f;
        m_players[0]->Vf0();
        m_players[0]->StopMoving();
        m_players[0]->unk30bc = 0;
        m_players[0]->m_afterimages.unk0 = 0;
        m_players[0]->m_afterimages.unk2 = 0;
        m_players[0]->unk58 = 0;
        m_players[0]->unkb8 = 0.0;
        m_players[1]->unkb8 = 0.0;
        return;
    }
    m_players[1]->x = 480.0;
    m_players[1]->y = -240.0;
    m_players[1]->facing = -1;
    m_players[1]->pattern = 0x2f;
    m_players[1]->Vf0();
    m_players[1]->StopMoving();
    m_players[1]->unk30bc = 0;
    m_players[1]->m_afterimages.unk0 = 0;
    m_players[1]->m_afterimages.unk2 = 0;
    m_players[1]->unk58 = 0;
    m_players[0]->unkb8 = 0.0;
    m_players[1]->unkb8 = 0.0;
}

void CScene5::Vf2()
{
    int l10c;
    char v108[256];

    l10c = m_input->m_keyboard->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if ((v108[1] & 0x80) != 0) {
        unk2d = 1;
        m_game->unk1378 = 0;
    }
}
