// CScene5 (0x7712f0-0x7758af), scene 5: the result screen after a match (system\result,
// system\winner). The <math.h> overload pow(int, int) it calls follows it:
// FUNCTION: 0x775810 ?pow@@YANHH@Z
// FUNCTION: 0x775830 ??$_Pow_int@H@@YAHHH@Z
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CScene5::CScene5(HWND hwnd, PTR32(CPlayer)* player1Ref, PTR32(CPlayer)* player2Ref, CGame* game, CGraphics* graphics, CInput* input, CSound* sound)
    : CScene(hwnd, player1Ref, player2Ref, game, graphics, input, sound)
{
    if (1) {
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_winnerSurface, "system\\winner.dat", 0, 175);
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_resultSurface, "system\\result.dat", 0, 175);
    } else {
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_winnerSurface, "system\\winner.bmp", 175);
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_resultSurface, "system\\result.bmp", 175);
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
        CScene::FadeOut(m_game->m_palette, m_game->m_gameMode != 0, 0, 100);
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
    if (m_entranceTime < 60) {
        m_entranceTime++;
        if (m_game->m_winner == 1) {
            m_players[0]->UpdatePattern();
            m_players[0]->ApplyVelocity();
            m_players[0]->UpdatePattern();
            m_players[0]->ApplyVelocity();
            m_players[0]->UpdatePattern();
            m_players[0]->ApplyVelocity();
            if (m_players[0]->m_playSound >= 0 && m_players[0]->m_playSound < 65) {
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
            if (m_players[1]->m_playSound >= 0 && m_players[1]->m_playSound < 65) {
                m_sound->Play((short)m_game->m_sounds[m_players[1]->m_playSound], 0);
                m_players[1]->m_playSound = -1;
            }
        }
        if (m_entranceTime == 60) {
            if (m_players[m_game->m_winner]->m_charId == 19 || m_players[m_game->m_winner]->m_charId == 20 || m_players[m_game->m_winner]->m_charId == 21 || m_players[m_game->m_winner]->m_charId == 23) {
                m_game->PlayMusic(4);
            } else if (m_players[m_game->m_winner]->m_charId == 14) {
                m_game->PlayMusic(9);
            } else if (m_players[m_game->m_winner]->m_charId == 1 || m_players[m_game->m_winner]->m_charId == 16 || m_players[m_game->m_winner]->m_charId == 17 || m_players[m_game->m_winner]->m_charId == 13 || m_players[m_game->m_winner]->m_charId == 15 || m_players[m_game->m_winner]->m_charId == 2 || m_players[m_game->m_winner]->m_charId == 3 || m_players[m_game->m_winner]->m_charId == 8 || m_players[m_game->m_winner]->m_charId == 9 || m_players[m_game->m_winner]->m_charId == 10) {
                m_game->PlayMusic(2);
            } else {
                m_game->PlayMusic(3);
            }
            m_state = 1;
        }
    }
    if (m_panX > 40 && m_entranceTime >= 60) {
        m_panX -= m_panSpeed / 3;
        if (m_panX < 120 && m_panSpeed > 1) {
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
                if (m_players[m_game->m_winner]->m_charId == 19 || m_players[m_game->m_winner]->m_charId == 20 || m_players[m_game->m_winner]->m_charId == 21 || m_players[m_game->m_winner]->m_charId == 23) {
                    m_game->PlayMusic(4);
                } else if (m_players[m_game->m_winner]->m_charId == 1 || m_players[m_game->m_winner]->m_charId == 2 || m_players[m_game->m_winner]->m_charId == 3 || m_players[m_game->m_winner]->m_charId == 8 || m_players[m_game->m_winner]->m_charId == 9 || m_players[m_game->m_winner]->m_charId == 10) {
                    m_game->PlayMusic(2);
                } else {
                    m_game->PlayMusic(3);
                }
            }
            m_state = 2;
            m_portraitX = -160;
            m_pictureY = 0;
            m_panX = 40;
            m_curtain = 160;
            m_entranceTime = 60;
        } else if (m_game->m_gameMode == 2 && m_state < 2) {
            if (m_state == 0) {
                if (m_players[m_game->m_winner]->m_charId == 19 || m_players[m_game->m_winner]->m_charId == 20 || m_players[m_game->m_winner]->m_charId == 21 || m_players[m_game->m_winner]->m_charId == 23) {
                    m_game->PlayMusic(4);
                } else if (m_players[m_game->m_winner]->m_charId == 1 || m_players[m_game->m_winner]->m_charId == 2 || m_players[m_game->m_winner]->m_charId == 3 || m_players[m_game->m_winner]->m_charId == 8 || m_players[m_game->m_winner]->m_charId == 9 || m_players[m_game->m_winner]->m_charId == 10) {
                    m_game->PlayMusic(2);
                } else {
                    m_game->PlayMusic(3);
                }
            }
            m_state = 3;
            m_portraitX = -160;
            m_pictureY = 0;
            m_panX = 40;
            m_curtain = 160;
            m_entranceTime = 60;
        } else {
            m_leave = 1;
        }
    }
    m_band1X = m_band1X + 2;
    if (m_band1X >= 320) {
        m_band1X = 0;
    }
    m_band1Y = m_band1Y + 1;
    if (m_band1Y >= 240) {
        m_band1Y = 0;
    }
    m_band2X = m_band2X - 2;
    if (m_band2X < 0) {
        m_band2X = 320;
    }
    m_band2Y = m_band2Y - 1;
    if (m_band2Y < 0) {
        m_band2Y = 240;
    }
    if (m_curtain < 160 && m_portraitX <= -80) {
        m_curtain += m_curtainSpeed;
        if (m_curtain > 115) {
            m_curtainSpeed--;
        }
    }
    if (m_portraitX > -160 && m_panX < 160) {
        m_portraitX -= m_portraitSpeed;
        if (m_portraitX < -40) {
            m_portraitSpeed--;
        }
    }
    if (m_pictureY < 0 && m_curtain > 120) {
        m_pictureY += m_pictureSpeed;
        if (m_pictureY >= 0 && m_game->m_gameMode == 6) {
            m_leave = 1;
        }
        if (m_pictureY > -120) {
            m_pictureSpeed--;
        }
    }
    Draw();
    return 5;
}

void CScene5::Draw()
{
    int column; // a digit of the score's low eight, from the left
    int offset; // the band repeats every 80 rows

    m_graphics->Blit(MakeRect(0, 0, 320, 160), m_game->m_stageSurface, MakeRect(m_panX, 320, 320, 160), 0, 0);
    m_graphics->FillRect(MakeRect(0, 160, 320, 80), 176);
    if (m_game->m_winner == 1) {
        m_players[0]->DrawSprite(-m_panX, -80);
    } else {
        m_players[1]->DrawSprite(-m_panX, -80);
    }
    m_graphics->FillRect(MakeRect(320 - m_curtain, 0, m_curtain, 240), 231);
    m_graphics->FillRect(MakeRect(0, 0, m_curtain, 240), 231);
    offset = -240;
    for (; offset <= 240; offset += 80) {
        if (m_band2X <= 160) {
            m_graphics->Blit(MakeRect(m_curtain - 160, m_band2Y + offset, 160, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band2X, 48, 160, 48), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(160 - m_curtain + 160, m_band2Y + offset, 160 - m_band2X, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band2X + 160, 48, 160 - m_band2X, 48), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(160 - m_curtain + 320 - m_band2X, m_band2Y + offset, m_band2X, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(0, 48, m_band2X, 48), m_game->m_colorKey, 0);
        } else {
            m_graphics->Blit(MakeRect(m_curtain - 160, m_band2Y + offset, 320 - m_band2X, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band2X, 48, 320 - m_band2X, 48), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(m_curtain + 160 - m_band2X, m_band2Y + offset, m_band2X - 160, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(0, 48, m_band2X - 160, 48), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(160 - m_curtain + 160, m_band2Y + offset, 160, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band2X - 160, 48, 160, 48), m_game->m_colorKey, 0);
        }
    }
    offset = -240;
    for (; offset <= 240; offset += 80) {
        if (m_band1X <= 160) {
            m_graphics->Blit(MakeRect(m_curtain - 160, m_band1Y + offset, 160, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band1X, 0, 160, 48), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(160 - m_curtain + 160, m_band1Y + offset, 160 - m_band1X, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band1X + 160, 0, 160 - m_band1X, 48), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(160 - m_curtain + 320 - m_band1X, m_band1Y + offset, m_band1X, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(0, 0, m_band1X, 48), m_game->m_colorKey, 0);
        } else {
            m_graphics->Blit(MakeRect(m_curtain - 160, m_band1Y + offset, 320 - m_band1X, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band1X, 0, 320 - m_band1X, 48), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(m_curtain + 160 - m_band1X, m_band1Y + offset, m_band1X - 160, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(0, 0, m_band1X - 160, 48), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(160 - m_curtain + 160, m_band1Y + offset, 160, 48), TOPTR(IDirectDrawSurface*, m_winnerSurface), MakeRect(m_band1X - 160, 0, 160, 48), m_game->m_colorKey, 0);
        }
    }
    m_graphics->Blit(MakeRect(m_portraitX + 80, 0, 320, 240), TOPTR(IDirectDrawSurface*, m_portrait), MakeRect(0, 0, 320, 240), m_colorKey, 0);
    if (m_state < 2) {
        m_graphics->Blit(MakeRect(0, m_pictureY, 320, 240), TOPTR(IDirectDrawSurface*, m_winPicture), MakeRect(0, 0, 320, 240), m_game->m_colorKey, 0);
    } else if (m_state == 2) {
        m_graphics->Blit(MakeRect(87, 90, 153, 25), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 474, 153, 25), m_game->m_colorKey, 0);
        if (m_continueChoice == 0) {
            m_graphics->Blit(MakeRect(104, 124, 51, 21), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 499, 51, 21), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(180, 126, 30, 16), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(38, 520, 30, 16), m_game->m_colorKey, 0);
        } else {
            m_graphics->Blit(MakeRect(110, 126, 38, 15), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 520, 38, 15), m_game->m_colorKey, 0);
            m_graphics->Blit(MakeRect(175, 124, 39, 20), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(51, 500, 39, 20), m_game->m_colorKey, 0);
        }
    } else if (m_state == 3) {
        m_graphics->Blit(MakeRect(73, 9, 214, 42), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, (m_game->m_arcadeMatch - 1) * 42, 214, 42), m_game->m_colorKey, 0);
        m_graphics->Blit(MakeRect(9, 59, 52, 18), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 353, 52, 18), m_game->m_colorKey, 0);
        DrawNumber(310, 58, m_lifeBonus);
        m_graphics->Blit(MakeRect(9, 86, 106, 29), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 371, 106, 29), m_game->m_colorKey, 0);
        DrawNumber(310, 91, m_comboBonus);
        m_graphics->Blit(MakeRect(9, 117, 117, 33), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 400, 117, 33), m_game->m_colorKey, 0);
        DrawNumber(310, 124, m_damageBonus);
        m_graphics->Blit(MakeRect(9, 156, 126, 22), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(0, 433, 126, 22), m_game->m_colorKey, 0);
        DrawNumber(310, 157, m_straightBonus);
        m_graphics->Blit(MakeRect(9, 190, 74, 18), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(52, 353, 74, 18), m_game->m_colorKey, 0);
        m_graphics->Blit(MakeRect(298, 187, 11, 17), TOPTR(IDirectDrawSurface*, m_resultSurface), MakeRect(178, 456, 11, 17), m_game->m_colorKey, 0);
        DrawNumber(296, 186, m_players[m_game->m_humanSide]->m_hitsLanded);
        DrawNumber(310, 215, m_players[m_game->m_humanSide]->m_score);
        if ((unsigned long)m_players[m_game->m_humanSide]->m_scoreHigh > 0) {
            DrawNumber(198, 215, m_players[m_game->m_humanSide]->m_scoreHigh);
            column = 1;
            for (; column < 8; column++) {
                if ((double)(unsigned long)m_players[m_game->m_humanSide]->m_score / pow(10, 8 - column) < 1.0) {
                    DrawNumber(column * 14 + 198, 215, 0);
                }
            }
        }
    }
    m_graphics->Flip();
}

void CScene5::DrawNumber(int right, int top, int value)
{
    RECT src;
    int digit;
    RECT dst;
    DWORD rest; // the digits not drawn yet
    int x; // the next digit's right edge

    rest = value;
    x = right;
    do {
        digit = rest % 10;
        src.top = 455;
        src.bottom = 474;
        src.left = digit << 4;
        src.right = digit + 1 << 4;
        dst.top = top;
        dst.bottom = top + 19;
        dst.right = x;
        dst.left = x - 16;
        m_graphics->Blit(dst, TOPTR(IDirectDrawSurface*, m_resultSurface), src, m_game->m_colorKey, 0);
        x -= 14;
        rest = rest / 10;
    } while (rest > 0);
}

void CScene5::Enter()
{
    int i;
    int picture; // the win picture, system\<name>\NN; 10 + the index of a rival
    char path[40];
    char number[8];

    picture = rand() % m_players[m_game->m_winner]->m_resultPictures;
    if (m_portrait != 0) {
        (TOPTR(IUnknown*, m_portrait))->Release();
        m_portrait = 0;
    }
    if (m_winPicture != 0) {
        (TOPTR(IUnknown*, m_winPicture))->Release();
        m_winPicture = 0;
    }
    strcpy(path, "system\\");
    strcat(path, m_players[m_game->m_winner]->m_name);
    strcat(path, "\\");
    strcat(path, m_players[m_game->m_winner]->m_name);
    if (1) {
        strcat(path, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_portrait, (const char*)path, 0, m_game->m_winner * 40 + 95);
        m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)path, m_players[m_game->m_winner]->m_paletteIndex * 40, m_game->m_winner * 40 + 95, 40);
    } else {
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_portrait, (const char*)path, m_game->m_winner * 40 + 95);
        m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)path, m_players[m_game->m_winner]->m_paletteIndex * 40, m_game->m_winner * 40 + 95, 40);
    }
    m_colorKey = m_graphics->GetColorKey(TOPTR(IDirectDrawSurface*, m_portrait));
    i = 0;
    for (; i < 20; i++) {
        if (m_players[(1 - m_game->m_winner)]->m_charId == m_players[m_game->m_winner]->m_rivals[i]) {
            picture = i + 10;
        }
    }
    strcpy(path, "system\\");
    strcat(path, m_players[m_game->m_winner]->m_name);
    strcat(path, "\\");
    _itoa(picture, number, 10);
    if (picture < 10) {
        strcat(path, "0");
    }
    strcat(path, (const char*)number);
    if (1) {
        strcat(path, ".dat");
        m_game->LoadDat((PTR32(IDirectDrawSurface)*)&m_winPicture, (const char*)path, 0, 175);
    } else {
        strcat(path, ".bmp");
        m_graphics->LoadBmp((PTR32(IDirectDrawSurface)*)&m_winPicture, (const char*)path, 175);
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
        m_lifeBonus = (unsigned long)m_players[m_game->m_humanSide]->m_wonHpTotal / 100;
        m_players[m_game->m_humanSide]->m_hitsLanded += m_lifeBonus;
        m_comboBonus = m_players[m_game->m_humanSide]->m_maxHits << 1;
        m_players[m_game->m_humanSide]->m_hitsLanded += m_comboBonus;
        m_damageBonus = (unsigned long)m_players[m_game->m_humanSide]->m_maxDamage / 100;
        m_players[m_game->m_humanSide]->m_hitsLanded += m_damageBonus;
        m_straightBonus = m_game->m_arcadeMatch * 50 * (m_players[(1 - m_game->m_humanSide)]->m_roundsWon == 0);
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
    m_panX = 240;
    m_panSpeed = 18;
    m_band1X = 0;
    m_band1Y = 0;
    m_band2X = 0;
    m_band2Y = 0;
    m_curtain = -2;
    m_portraitX = 320;
    m_pictureY = -240;
    m_curtainSpeed = 9;
    m_portraitSpeed = 15;
    m_pictureSpeed = 15;
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
    int hr;
    char keys[256];

    hr = m_input->m_keyboard->GetDeviceState(0x100, keys);
    if (hr < 0 && hr == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if ((keys[1] & 0x80) != 0) {
        m_leave = 1;
        m_game->m_continued = 0;
    }
}
