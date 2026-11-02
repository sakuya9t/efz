// CScene5 (0x7712f0-0x7758af), scene 5: the result screen after a match (system\result,
// system\winner). The <math.h> overload pow(int, int) it calls follows it:
// FUNCTION: 0x775810 ?pow@@YANHH@Z
// FUNCTION: 0x775830 ??$_Pow_int@H@@YAHHH@Z
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene5::CScene5(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_winnerSurface, "system\\winner.dat", 0, 0xaf);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_resultSurface, "system\\result.dat", 0, 0xaf);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_winnerSurface, "system\\winner.bmp", 0xaf);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_resultSurface, "system\\result.bmp", 0xaf);
    }
    m_winPicture = 0;
    m_portrait = 0;
    m_enter = 1;
    m_leave = 0;
    m_continueChoice = 0;
}

CScene5::~CScene5()
{
    if (m_winnerSurface != 0) {
        (TOPTR(IUnknown*, m_winnerSurface))->Release();
        m_winnerSurface = 0;
    }
    if (m_resultSurface != 0) {
        (TOPTR(IUnknown*, m_resultSurface))->Release();
        m_resultSurface = 0;
    }
    if (m_winPicture != 0) {
        (TOPTR(IUnknown*, m_winPicture))->Release();
        m_winPicture = 0;
    }
    if (m_portrait != 0) {
        (TOPTR(IUnknown*, m_portrait))->Release();
        m_portrait = 0;
    }
}

BYTE CScene5::Update()
{
    if (m_enter == 1) {
        m_state = 0;
        m_continueChoice = 0;
        m_players[0] = *m_player1Ref;
        m_players[1] = *m_player2Ref;
        Enter();
        m_game->StopMusic();
        CScene::FadeIn(m_game->m_palette, 1);
        m_enter = 0;
    } else if (m_leave == 1) {
        CScene::FadeOut(m_game->m_palette, m_game->m_gameMode != 0, 0, 0x64);
        m_game->m_playedStages |= 1 << m_game->m_stage;
        if ((int)m_game->m_background != 0) {
            delete (char*)m_game->m_background;
            m_game->m_background = (CAnimBg*)0;
        }
        if (m_game->m_replayMode > 0) {
            m_game->m_replay.Close();
        }
        if (m_game->m_gameMode == 0) {
            if (m_game->m_winner == m_game->m_humanSide) {
                if (m_game->m_arcadeMatch == 8) {
                    delete *m_player1Ref;
                    delete *m_player2Ref;
                    *m_player1Ref = (CPlayer*)0;
                    *m_player2Ref = (CPlayer*)0;
                    m_leave = 0;
                    m_enter = 1;
                    return 7;
                }
                if (m_game->m_humanSide == 1) {
                    m_game->m_beatenChars |= 1 << (*m_player1Ref)->m_charId;
                    delete *m_player1Ref;
                    *m_player1Ref = (CPlayer*)0;
                } else {
                    m_game->m_beatenChars |= 1 << (*m_player2Ref)->m_charId;
                    delete *m_player2Ref;
                    *m_player2Ref = (CPlayer*)0;
                }
                m_game->m_arcadeMatch++;
                m_game->m_continued = 0;
                m_leave = 0;
                m_enter = 1;
                return 2;
            }
            if ((unsigned char)m_game->m_continued > 0) {
                m_leave = 0;
                m_enter = 1;
                return 2;
            }
            delete *m_player1Ref;
            delete *m_player2Ref;
            *m_player1Ref = (CPlayer*)0;
            *m_player2Ref = (CPlayer*)0;
            m_leave = 0;
            m_enter = 1;
            return 1;
        }
        if (m_game->m_gameMode == 2 && m_game->m_winner == m_game->m_humanSide && m_game->m_arcadeMatch < 8) {
            if (m_game->m_humanSide == 1) {
                m_game->m_beatenChars |= 1 << (*m_player1Ref)->m_charId;
                delete *m_player1Ref;
                *m_player1Ref = (CPlayer*)0;
            } else {
                m_game->m_beatenChars |= 1 << (*m_player2Ref)->m_charId;
                delete *m_player2Ref;
                *m_player2Ref = (CPlayer*)0;
            }
            m_game->m_arcadeMatch++;
            m_leave = 0;
            m_enter = 1;
            return 2;
        }
        if (m_game->m_gameMode == 6) {
            delete *m_player1Ref;
            delete *m_player2Ref;
            *m_player1Ref = (CPlayer*)0;
            *m_player2Ref = (CPlayer*)0;
            m_leave = 0;
            m_enter = 1;
            return 0;
        }
        delete *m_player1Ref;
        delete *m_player2Ref;
        *m_player1Ref = (CPlayer*)0;
        *m_player2Ref = (CPlayer*)0;
        m_leave = 0;
        m_enter = 1;
        return 1;
    }
    HandleKeys();
    if (m_entranceTime < 0x3c) {
        m_entranceTime++;
        if (m_game->m_winner == 1) {
            m_players[0]->UpdatePattern();
            m_players[0]->ApplyVelocity();
            m_players[0]->UpdatePattern();
            m_players[0]->ApplyVelocity();
            m_players[0]->UpdatePattern();
            m_players[0]->ApplyVelocity();
            if (m_players[0]->m_playSound >= 0 && m_players[0]->m_playSound < 0x41) {
                m_sound->Play((short)m_game->m_sounds[m_players[0]->m_playSound], 0);
                m_players[0]->m_playSound = -1;
            }
        } else {
            m_players[1]->UpdatePattern();
            m_players[1]->ApplyVelocity();
            m_players[1]->UpdatePattern();
            m_players[1]->ApplyVelocity();
            m_players[1]->UpdatePattern();
            m_players[1]->ApplyVelocity();
            if (m_players[1]->m_playSound >= 0 && m_players[1]->m_playSound < 0x41) {
                m_sound->Play((short)m_game->m_sounds[m_players[1]->m_playSound], 0);
                m_players[1]->m_playSound = -1;
            }
        }
        if (m_entranceTime == 0x3c) {
            if (m_players[m_game->m_winner]->m_charId == 0x13 || m_players[m_game->m_winner]->m_charId == 0x14 || m_players[m_game->m_winner]->m_charId == 0x15 || m_players[m_game->m_winner]->m_charId == 0x17) {
                m_game->PlayMusic(4);
            } else if (m_players[m_game->m_winner]->m_charId == 0xe) {
                m_game->PlayMusic(9);
            } else if (m_players[m_game->m_winner]->m_charId == 1 || m_players[m_game->m_winner]->m_charId == 0x10 || m_players[m_game->m_winner]->m_charId == 0x11 || m_players[m_game->m_winner]->m_charId == 0xd || m_players[m_game->m_winner]->m_charId == 0xf || m_players[m_game->m_winner]->m_charId == 2 || m_players[m_game->m_winner]->m_charId == 3 || m_players[m_game->m_winner]->m_charId == 8 || m_players[m_game->m_winner]->m_charId == 9 || m_players[m_game->m_winner]->m_charId == 0xa) {
                m_game->PlayMusic(2);
            } else {
                m_game->PlayMusic(3);
            }
            m_state = 1;
        }
    }
    if (m_panX > 0x28 && m_entranceTime >= 0x3c) {
        m_panX -= m_panSpeed / 3;
        if (m_panX < 0x78 && m_panSpeed > 1) {
            m_panSpeed--;
        }
    }
    m_game->UpdateInput();
    if (m_state == 2) {
        if (m_game->m_inputX[m_game->m_humanSide] != 0 && m_held == 0) {
            m_continueChoice++;
            m_game->PlaySE(8);
            if (m_continueChoice > 1) {
                m_continueChoice = 0;
            }
            m_held = 1;
        }
        if (m_game->m_inputX[m_game->m_humanSide] == 0) {
            m_held = 0;
        }
        if (m_game->m_pressA[m_game->m_humanSide] != 0) {
            m_game->PlaySE(6);
            if (m_continueChoice == 0) {
                if (m_game->m_arcadeMatch < 8) {
                    m_game->m_continuedAt = m_game->m_arcadeMatch;
                } else {
                    m_game->m_continuedAt = 0;
                }
                m_game->m_continued = 1;
                m_leave = 1;
            } else {
                m_game->m_continued = 0;
                m_leave = 1;
            }
        }
    } else if (m_game->m_pressA[0] != 0 || m_game->m_pressB[0] != 0 || m_game->m_pressC[0] != 0 || m_game->m_pressD[0] != 0 || m_game->m_pressA[1] != 0 || m_game->m_pressB[1] != 0 || m_game->m_pressC[1] != 0 || m_game->m_pressD[1] != 0) {
        if (m_game->m_gameMode == 0 && m_game->m_winner != m_game->m_humanSide && m_state < 2) {
            if (m_state == 0) {
                if (m_players[m_game->m_winner]->m_charId == 0x13 || m_players[m_game->m_winner]->m_charId == 0x14 || m_players[m_game->m_winner]->m_charId == 0x15 || m_players[m_game->m_winner]->m_charId == 0x17) {
                    m_game->PlayMusic(4);
                } else if (m_players[m_game->m_winner]->m_charId == 1 || m_players[m_game->m_winner]->m_charId == 2 || m_players[m_game->m_winner]->m_charId == 3 || m_players[m_game->m_winner]->m_charId == 8 || m_players[m_game->m_winner]->m_charId == 9 || m_players[m_game->m_winner]->m_charId == 0xa) {
                    m_game->PlayMusic(2);
                } else {
                    m_game->PlayMusic(3);
                }
            }
            m_state = 2;
            m_portraitX = -0xa0;
            m_pictureY = 0;
            m_panX = 0x28;
            m_curtain = 0xa0;
            m_entranceTime = 0x3c;
        } else if (m_game->m_gameMode == 2 && m_state < 2) {
            if (m_state == 0) {
                if (m_players[m_game->m_winner]->m_charId == 0x13 || m_players[m_game->m_winner]->m_charId == 0x14 || m_players[m_game->m_winner]->m_charId == 0x15 || m_players[m_game->m_winner]->m_charId == 0x17) {
                    m_game->PlayMusic(4);
                } else if (m_players[m_game->m_winner]->m_charId == 1 || m_players[m_game->m_winner]->m_charId == 2 || m_players[m_game->m_winner]->m_charId == 3 || m_players[m_game->m_winner]->m_charId == 8 || m_players[m_game->m_winner]->m_charId == 9 || m_players[m_game->m_winner]->m_charId == 0xa) {
                    m_game->PlayMusic(2);
                } else {
                    m_game->PlayMusic(3);
                }
            }
            m_state = 3;
            m_portraitX = -0xa0;
            m_pictureY = 0;
            m_panX = 0x28;
            m_curtain = 0xa0;
            m_entranceTime = 0x3c;
        } else {
            m_leave = 1;
        }
    }
    m_band1X = m_band1X + 2;
    if (m_band1X >= 0x140) {
        m_band1X = 0;
    }
    m_band1Y = m_band1Y + 1;
    if (m_band1Y >= 0xf0) {
        m_band1Y = 0;
    }
    m_band2X = m_band2X - 2;
    if (m_band2X < 0) {
        m_band2X = 0x140;
    }
    m_band2Y = m_band2Y - 1;
    if (m_band2Y < 0) {
        m_band2Y = 0xf0;
    }
    if (m_curtain < 0xa0 && m_portraitX <= -0x50) {
        m_curtain += m_curtainSpeed;
        if (m_curtain > 0x73) {
            m_curtainSpeed--;
        }
    }
    if (m_portraitX > -0xa0 && m_panX < 0xa0) {
        m_portraitX -= m_portraitSpeed;
        if (m_portraitX < -0x28) {
            m_portraitSpeed--;
        }
    }
    if (m_pictureY < 0 && m_curtain > 0x78) {
        m_pictureY += m_pictureSpeed;
        if (m_pictureY >= 0 && m_game->m_gameMode == 6) {
            m_leave = 1;
        }
        if (m_pictureY > -0x78) {
            m_pictureSpeed--;
        }
    }
    Draw();
    return 5;
}

void CScene5::Draw()
{
    int v8;
    int v4;

    m_graphics->Blit(MakeRect(0, 0, 0x140, 0xa0), m_game->m_stageSurface, MakeRect(m_panX, 0x140, 0x140, 0xa0), 0, 0);
    m_graphics->FillRect(MakeRect(0, 0xa0, 0x140, 0x50), 0xb0);
    if (m_game->m_winner == 1) {
        m_players[0]->DrawSprite(-m_panX, -0x50);
    } else {
        m_players[1]->DrawSprite(-m_panX, -0x50);
    }
    m_graphics->FillRect(MakeRect(0x140 - m_curtain, 0, m_curtain, 0xf0), 0xe7);
    m_graphics->FillRect(MakeRect(0, 0, m_curtain, 0xf0), 0xe7);
    v4 = -0xf0;
    for (; v4 <= 0xf0; v4 += 0x50) {
        if (m_band2X <= 0xa0) {
            m_graphics->Blit(MakeRect(m_curtain - 0xa0, m_band2Y + v4, 0xa0, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band2X, 0x30, 0xa0, 0x30), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - m_curtain + 0xa0, m_band2Y + v4, 0xa0 - m_band2X, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band2X + 0xa0, 0x30, 0xa0 - m_band2X, 0x30), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - m_curtain + 0x140 - m_band2X, m_band2Y + v4, m_band2X, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(0, 0x30, m_band2X, 0x30), m_game->m_colorKey, 0);
        } else {
            m_graphics->Blit(MakeRect(m_curtain - 0xa0, m_band2Y + v4, 0x140 - m_band2X, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band2X, 0x30, 0x140 - m_band2X, 0x30), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(m_curtain + 0xa0 - m_band2X, m_band2Y + v4, m_band2X - 0xa0, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(0, 0x30, m_band2X - 0xa0, 0x30), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - m_curtain + 0xa0, m_band2Y + v4, 0xa0, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band2X - 0xa0, 0x30, 0xa0, 0x30), m_game->m_colorKey, 0);
        }
    }
    v4 = -0xf0;
    for (; v4 <= 0xf0; v4 += 0x50) {
        if (m_band1X <= 0xa0) {
            m_graphics->Blit(MakeRect(m_curtain - 0xa0, m_band1Y + v4, 0xa0, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band1X, 0, 0xa0, 0x30), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - m_curtain + 0xa0, m_band1Y + v4, 0xa0 - m_band1X, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band1X + 0xa0, 0, 0xa0 - m_band1X, 0x30), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - m_curtain + 0x140 - m_band1X, m_band1Y + v4, m_band1X, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(0, 0, m_band1X, 0x30), m_game->m_colorKey, 0);
        } else {
            m_graphics->Blit(MakeRect(m_curtain - 0xa0, m_band1Y + v4, 0x140 - m_band1X, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band1X, 0, 0x140 - m_band1X, 0x30), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(m_curtain + 0xa0 - m_band1X, m_band1Y + v4, m_band1X - 0xa0, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(0, 0, m_band1X - 0xa0, 0x30), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xa0 - m_curtain + 0xa0, m_band1Y + v4, 0xa0, 0x30), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band1X - 0xa0, 0, 0xa0, 0x30), m_game->m_colorKey, 0);
        }
    }
    m_graphics->Blit(MakeRect(m_portraitX + 0x50, 0, 0x140, 0xf0), TOPTR(IDirectDrawSurface*, m_portrait), MakeRect(0, 0, 0x140, 0xf0), m_colorKey, 0);
    if (m_state < 2) {
        m_graphics->Blit(MakeRect(0, m_pictureY, 0x140, 0xf0), TOPTR(IDirectDrawSurface*, m_winPicture), MakeRect(0, 0, 0x140, 0xf0), m_game->m_colorKey, 0);
    } else if (m_state == 2) {
        m_graphics->Blit(MakeRect(0x57, 0x5a, 0x99, 0x19), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 0x1da, 0x99, 0x19), m_game->m_colorKey, 0);
        if (m_continueChoice == 0) {
            m_graphics->Blit(MakeRect(0x68, 0x7c, 0x33, 0x15), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 0x1f3, 0x33, 0x15), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xb4, 0x7e, 0x1e, 0x10), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0x26, 0x208, 0x1e, 0x10), m_game->m_colorKey, 0);
        } else {
            m_graphics->Blit(MakeRect(0x6e, 0x7e, 0x26, 0xf), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 0x208, 0x26, 0xf), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(0xaf, 0x7c, 0x27, 0x14), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0x33, 0x1f4, 0x27, 0x14), m_game->m_colorKey, 0);
        }
    } else if (m_state == 3) {
        m_graphics->Blit(MakeRect(0x49, 9, 0xd6, 0x2a), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, (m_game->m_arcadeMatch - 1) * 0x2a, 0xd6, 0x2a), m_game->m_colorKey, 0);
        m_graphics->Blit(MakeRect(9, 0x3b, 0x34, 0x12), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 0x161, 0x34, 0x12), m_game->m_colorKey, 0);
        DrawNumber(0x136, 0x3a, m_lifeBonus);
        m_graphics->Blit(MakeRect(9, 0x56, 0x6a, 0x1d), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 0x173, 0x6a, 0x1d), m_game->m_colorKey, 0);
        DrawNumber(0x136, 0x5b, m_comboBonus);
        m_graphics->Blit(MakeRect(9, 0x75, 0x75, 0x21), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 0x190, 0x75, 0x21), m_game->m_colorKey, 0);
        DrawNumber(0x136, 0x7c, m_damageBonus);
        m_graphics->Blit(MakeRect(9, 0x9c, 0x7e, 0x16), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 0x1b1, 0x7e, 0x16), m_game->m_colorKey, 0);
        DrawNumber(0x136, 0x9d, m_straightBonus);
        m_graphics->Blit(MakeRect(9, 0xbe, 0x4a, 0x12), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0x34, 0x161, 0x4a, 0x12), m_game->m_colorKey, 0);
        m_graphics->Blit(MakeRect(0x12a, 0xbb, 0xb, 0x11), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0xb2, 0x1c8, 0xb, 0x11), m_game->m_colorKey, 0);
        DrawNumber(0x128, 0xba, m_players[m_game->m_humanSide]->m_hitsLanded);
        DrawNumber(0x136, 0xd7, m_players[m_game->m_humanSide]->m_score);
        if ((unsigned long)m_players[m_game->m_humanSide]->m_scoreHigh > 0) {
            DrawNumber(0xc6, 0xd7, m_players[m_game->m_humanSide]->m_scoreHigh);
            v8 = 1;
            for (; v8 < 8; v8++) {
                if ((double)(unsigned long)m_players[m_game->m_humanSide]->m_score / pow(0xa, 8 - v8) < 1.0) {
                    DrawNumber(v8 * 0xe + 0xc6, 0xd7, 0);
                }
            }
        }
    }
    m_graphics->Flip();
}

void CScene5::DrawNumber(int p1, int p2, int p3)
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
        m_graphics->Blit(l18, TOPTR(IDirectDrawSurface*, m_resultSurface), v2c, m_game->m_colorKey, 0);
        l4 -= 0xe;
        x8 = x8 / 0xa;
    } while (x8 > 0);
}

void CScene5::Enter()
{
    int x3c;
    int v38;
    char v34[40];
    char vc[8];

    v38 = rand() % m_players[m_game->m_winner]->m_resultPictures;
    if (m_portrait != 0) {
        (TOPTR(IUnknown*, m_portrait))->Release();
        m_portrait = 0;
    }
    if (m_winPicture != 0) {
        (TOPTR(IUnknown*, m_winPicture))->Release();
        m_winPicture = 0;
    }
    strcpy(v34, "system\\");
    strcat(v34, m_players[m_game->m_winner]->m_name);
    strcat(v34, "\\");
    strcat(v34, m_players[m_game->m_winner]->m_name);
    if (1) {
        strcat(v34, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_portrait, (const char*)v34, 0, m_game->m_winner * 0x28 + 0x5f);
        m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v34, m_players[m_game->m_winner]->m_paletteIndex * 0x28, m_game->m_winner * 0x28 + 0x5f, 0x28);
    } else {
        strcat(v34, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_portrait, (const char*)v34, m_game->m_winner * 0x28 + 0x5f);
        m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)v34, m_players[m_game->m_winner]->m_paletteIndex * 0x28, m_game->m_winner * 0x28 + 0x5f, 0x28);
    }
    m_colorKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_portrait));
    x3c = 0;
    for (; x3c < 0x14; x3c++) {
        if (m_players[(1 - m_game->m_winner)]->m_charId == m_players[m_game->m_winner]->m_rivals[x3c]) {
            v38 = x3c + 0xa;
        }
    }
    strcpy(v34, "system\\");
    strcat(v34, m_players[m_game->m_winner]->m_name);
    strcat(v34, "\\");
    _itoa(v38, vc, 0xa);
    if (v38 < 0xa) {
        strcat(v34, "0");
    }
    strcat(v34, (const char*)vc);
    if (1) {
        strcat(v34, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_winPicture, (const char*)v34, 0, 0xaf);
    } else {
        strcat(v34, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_winPicture, (const char*)v34, 0xaf);
    }
    if (m_game->m_gameMode == 4) {
        if (m_game->m_winner == 0) {
            ((CharRecord*)&m_players[0]->m_recordUses)->Load(m_players[0]->m_name);
            m_players[0]->m_recordVsWins++;
            ((CharRecord*)&m_players[0]->m_recordUses)->Save(m_players[0]->m_name);
            ((CharRecord*)&m_players[1]->m_recordUses)->Load(m_players[1]->m_name);
            m_players[1]->m_recordVsLosses++;
            ((CharRecord*)&m_players[1]->m_recordUses)->Save(m_players[1]->m_name);
        } else {
            ((CharRecord*)&m_players[1]->m_recordUses)->Load(m_players[1]->m_name);
            m_players[1]->m_recordVsWins++;
            ((CharRecord*)&m_players[1]->m_recordUses)->Save(m_players[1]->m_name);
            ((CharRecord*)&m_players[0]->m_recordUses)->Load(m_players[0]->m_name);
            m_players[0]->m_recordVsLosses++;
            ((CharRecord*)&m_players[0]->m_recordUses)->Save(m_players[0]->m_name);
        }
    }
    if (m_game->m_gameMode == 2) {
        m_lifeBonus = (unsigned long)m_players[m_game->m_humanSide]->m_wonHpTotal / 0x64;
        m_players[m_game->m_humanSide]->m_hitsLanded += m_lifeBonus;
        m_comboBonus = m_players[m_game->m_humanSide]->m_maxHits << 1;
        m_players[m_game->m_humanSide]->m_hitsLanded += m_comboBonus;
        m_damageBonus = (unsigned long)m_players[m_game->m_humanSide]->m_maxDamage / 0x64;
        m_players[m_game->m_humanSide]->m_hitsLanded += m_damageBonus;
        m_straightBonus = m_game->m_arcadeMatch * 0x32 * (m_players[(1 - m_game->m_humanSide)]->m_roundsWon == 0);
        m_players[m_game->m_humanSide]->m_hitsLanded += m_straightBonus;
        ((CharRecord*)&m_players[m_game->m_humanSide]->m_recordUses)->Load(m_players[m_game->m_humanSide]->m_name);
        if ((unsigned long)m_players[m_game->m_humanSide]->m_recordBestScoreHigh < m_players[m_game->m_humanSide]->m_scoreHigh) {
            m_players[m_game->m_humanSide]->m_recordBestScore = m_players[m_game->m_humanSide]->m_score;
            m_players[m_game->m_humanSide]->m_recordBestScoreHigh = m_players[m_game->m_humanSide]->m_scoreHigh;
        } else if (m_players[m_game->m_humanSide]->m_recordBestScoreHigh == m_players[m_game->m_humanSide]->m_scoreHigh && m_players[m_game->m_humanSide]->m_recordBestScore < m_players[m_game->m_humanSide]->m_score) {
            m_players[m_game->m_humanSide]->m_recordBestScore = m_players[m_game->m_humanSide]->m_score;
        }
        ((CharRecord*)&m_players[m_game->m_humanSide]->m_recordUses)->Save(m_players[m_game->m_humanSide]->m_name);
    }
    if (m_game->m_damageLevel == 2) {
        if (m_game->m_isCpu[0] == 0) {
            ((CharRecord*)&m_players[0]->m_recordUses)->Load(m_players[0]->m_name);
            if (m_players[0]->m_recordMaxCombo < m_players[0]->m_maxHits) {
                m_players[0]->m_recordMaxCombo = m_players[0]->m_maxHits;
            }
            if (m_players[0]->m_recordMaxDamage < m_players[0]->m_maxDamage) {
                m_players[0]->m_recordMaxDamage = m_players[0]->m_maxDamage;
            }
            ((CharRecord*)&m_players[0]->m_recordUses)->Save(m_players[0]->m_name);
        }
        if (m_game->m_isCpu[1] == 0) {
            ((CharRecord*)&m_players[1]->m_recordUses)->Load(m_players[1]->m_name);
            if (m_players[1]->m_recordMaxCombo < m_players[1]->m_maxHits) {
                m_players[1]->m_recordMaxCombo = m_players[1]->m_maxHits;
            }
            if (m_players[1]->m_recordMaxDamage < m_players[1]->m_maxDamage) {
                m_players[1]->m_recordMaxDamage = m_players[1]->m_maxDamage;
            }
            ((CharRecord*)&m_players[1]->m_recordUses)->Save(m_players[1]->m_name);
        }
    }
    m_panX = 0xf0;
    m_panSpeed = 0x12;
    m_band1X = 0;
    m_band1Y = 0;
    m_band2X = 0;
    m_band2Y = 0;
    m_curtain = -2;
    m_portraitX = 0x140;
    m_pictureY = -0xf0;
    m_curtainSpeed = 9;
    m_portraitSpeed = 0xf;
    m_pictureSpeed = 0xf;
    m_entranceTime = 0;
    if (m_game->m_winner == 1) {
        m_players[0]->x = 480.0;
        m_players[0]->y = -240.0;
        m_players[0]->facing = -1;
        m_players[0]->pattern = kResultLoserFall;
        m_players[0]->StartPattern();
        m_players[0]->StopMoving();
        m_players[0]->m_tintTime = 0;
        m_players[0]->m_afterimages.spacing = 0;
        m_players[0]->m_afterimages.fadeLength = 0;
        m_players[0]->m_drawMode = 0;
        m_players[0]->m_cornerPushback = 0.0;
        m_players[1]->m_cornerPushback = 0.0;
        return;
    }
    m_players[1]->x = 480.0;
    m_players[1]->y = -240.0;
    m_players[1]->facing = -1;
    m_players[1]->pattern = kResultLoserFall;
    m_players[1]->StartPattern();
    m_players[1]->StopMoving();
    m_players[1]->m_tintTime = 0;
    m_players[1]->m_afterimages.spacing = 0;
    m_players[1]->m_afterimages.fadeLength = 0;
    m_players[1]->m_drawMode = 0;
    m_players[0]->m_cornerPushback = 0.0;
    m_players[1]->m_cornerPushback = 0.0;
}

void CScene5::HandleKeys()
{
    int l10c;
    char v108[256];

    l10c = m_input->m_keyboard->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if ((v108[1] & 0x80) != 0) {
        m_leave = 1;
        m_game->m_continued = 0;
    }
}
