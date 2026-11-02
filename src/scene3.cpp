// CScene3 (0x7633a0-0x76c6ef), scene 3: the fight itself. Each frame it runs both
// players and their objects, checks every pair of boxes (CollisionInfo snapshots of
// the current frame, position and facing), pushes the players apart, scrolls the
// camera and draws the gauges, timer and background (with the helpers in
// scene3_draw.cpp). A replay's inputs are written here, or read back when one is
// playing.
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

// GLOBAL: 0x7b1290
// Set while one of F5-F8 is held, so that each press acts once (Vf2).
int g_fkeyHeld = 0;

CScene3::CScene3(HWND p1, PTR32(CPlayer)* p2, PTR32(CPlayer)* p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    m_focusXDefault = 0;
    m_focusYHigh = -0x32;
    m_focusX = m_focusXDefault;
    m_focusY = m_focusYHigh;
    m_focusYStep = 5;
    m_scrollX = -0xa0;
    m_scrollY = 0;
    m_enter = 1;
    m_leave = 0;
    m_refillMeter = 0;
    m_refillHp = 0x270f;
    m_speed = 3;
    m_paused = 0;
    m_endFade = 0.0;
    m_capturing = 0;
    m_captureFrame = 0;
    m_frameCount = 0;
    m_secondStart = 0;
    m_fps = 0;
    m_game->m_roundOver = 0;
    m_game->m_intro = 1;
    m_digitFonts[0] = MakeRect(0, 0xea, 8, 0xa);
    m_digitFonts[1] = MakeRect(0, 0xd2, 0x10, 0xf);
    m_digitFonts[2] = MakeRect(0, 0xe1, 7, 9);
    m_digitFonts[3] = MakeRect(0, 0x11a, 0xe, 0x16);
    m_digitFonts[4] = MakeRect(0, 0x160, 8, 0xc);
    m_digitFonts[5] = MakeRect(0, 0x154, 8, 0xc);
    m_digitFonts[6] = MakeRect(0, 0x148, 8, 0xc);
    m_digitFonts[7] = MakeRect(0, 0x13c, 8, 0xc);
    m_digitFonts[8] = MakeRect(0, 0x130, 8, 0xc);
    m_digitFonts[9] = MakeRect(0, 0x16c, 7, 0xa);
    m_digitFonts[0xa] = MakeRect(0, 0x176, 7, 0xa);
    m_digitFonts[0xb] = MakeRect(0, 0x180, 7, 0xa);
    m_digitFonts[0xc] = MakeRect(0, 0x18a, 7, 0xa);
    m_digitFonts[0xd] = MakeRect(0, 0x194, 7, 0xa);
    m_digitFonts[0xe] = MakeRect(0, 0x19e, 7, 0xa);
    m_digitFonts[0xf] = MakeRect(0, 0x1a8, 7, 0xa);
    m_digitFonts[0x10] = MakeRect(0, 0x1b2, 7, 0xa);
}

CScene3::~CScene3()
{
}

BYTE CScene3::Update()
{
    int v4;

    if ((DWORD)(timeGetTime() - m_secondStart) >= 0x3e8) {
        m_secondStart = timeGetTime();
        m_fps = m_frameCount;
        m_frameCount = 0;
    }
    m_frameCount++;
    if (m_enter == 1) {
        m_game->m_intro = 1;
        m_players[0] = *m_player1Ref;
        m_players[1] = *m_player2Ref;
        m_focusXDefault = 0;
        m_focusYHigh = -0x32;
        m_focusX = m_focusXDefault;
        m_focusY = m_focusYHigh;
        m_focusYStep = 5;
        m_scrollX = -0xa0;
        m_scrollY = 0;
        m_speed = 3;
        m_refillMeter = 0;
        m_refillHp = 0x270f;
        UpdateCamera();
        Draw();
        CScene::FadeIn(m_game->m_palette, 0);
        m_enter = 0;
    } else if (m_leave == 1) {
        CScene::FadeOut(m_game->m_palette, 1, 0, 0x64);
        delete *m_player1Ref;
        *m_player1Ref = (CPlayer*)0;
        delete *m_player2Ref;
        *m_player2Ref = (CPlayer*)0;
        if ((int)m_game->m_background != 0) {
            delete (char*)m_game->m_background;
            m_game->m_background = (CAnimBg*)0;
        }
        m_leave = 0;
        m_enter = 1;
        if (m_game->m_replayMode > 0) {
            m_game->m_replay.Close();
            m_game->m_replayMode = 0;
            m_game->StopMusic();
            return 8;
        }
        if (m_game->m_gameMode == 6) {
            return 0;
        }
        return 1;
    }
    HandleKeys();
    if (m_paused != 0) {
        return 3;
    }
    if (m_leave == 2) {
        m_speed = 1;
        if (UpdateEndFade() != 0) {
            m_leave = 0;
            m_enter = 1;
            if (m_game->m_replayMode > 0) {
                m_game->m_replay.Close();
                m_game->m_replayMode = 0;
                m_game->StopMusic();
                delete *m_player1Ref;
                *m_player1Ref = (CPlayer*)0;
                delete *m_player2Ref;
                *m_player2Ref = (CPlayer*)0;
                if ((int)m_game->m_background != 0) {
                    delete (char*)m_game->m_background;
                    m_game->m_background = (CAnimBg*)0;
                }
                return 8;
            }
            return 5;
        }
    } else if (m_game->m_speedRequested != 0) {
        m_speed = m_game->m_requestedSpeed;
        m_game->m_speedRequested = 0;
    }
    v4 = 0;
    for (; v4 < m_speed; v4++) {
        m_players[0]->ReadInput();
        m_players[1]->ReadInput();
        StartIntro();
        m_players[0]->ProcessInput();
        m_players[1]->ProcessInput();
        m_players[0]->PreUpdate();
        m_players[1]->PreUpdate();
        m_players[0]->UpdatePattern();
        m_players[1]->UpdatePattern();
        m_players[0]->UpdateObjects();
        m_players[1]->UpdateObjects();
        if (m_game->m_roundOver == 0 && m_game->m_intro == 0) {
            CheckHits();
        }
        PushApart();
        m_players[0]->ApplyVelocity();
        m_players[1]->ApplyVelocity();
        if (m_players[0]->m_freezeTime > 0) {
            m_players[0]->m_freezeTime--;
        } else {
            m_players[0]->m_freezeTime = 0;
        }
        if (m_players[1]->m_freezeTime > 0) {
            m_players[1]->m_freezeTime--;
        } else {
            m_players[1]->m_freezeTime = 0;
        }
        m_players[0]->UpdateGaugesAndTimers();
        m_players[1]->UpdateGaugesAndTimers();
        PlayPlayerSounds();
        PlayEffectSounds();
        CheckKo();
#ifdef EFZ_TRACE
        TraceTick(this);
#endif
    }
    m_game->UpdateFade();
    m_game->UpdateTimers();
    UpdateCamera();
    if (m_game->m_drawEveryFrame != 0 || m_game->m_drawEveryFrame == 0 && m_game->m_oddFrame != 0) {
        Draw();
    }
    m_game->UpdateEffects();
    if ((int)m_game->m_background != 0) {
        m_game->m_background->Update();
    }
    return 3;
}

void CScene3::Draw()
{
    m_players[0]->UpdateAfterimages();
    m_players[1]->UpdateAfterimages();
    DrawBackground();
    DrawLifeBars();
    DrawShadows();
    m_game->DrawEffects(m_drawX, m_drawY, 0);
    m_players[0]->DrawObjects(m_drawX, m_drawY, 0);
    m_players[1]->DrawObjects(m_drawX, m_drawY, 0);
    if (m_players[1]->pattern >= kFirstCharacterAction) {
        m_players[0]->DrawSprite(m_drawX + m_players[0]->IsInHitstun() * (m_players[0]->m_hitstop % 2) * 2, m_drawY);
        m_players[1]->DrawSprite(m_drawX + m_players[1]->IsInHitstun() * (m_players[1]->m_hitstop % 2) * 2, m_drawY);
    } else {
        m_players[1]->DrawSprite(m_drawX + m_players[1]->IsInHitstun() * (m_players[1]->m_hitstop % 2) * 2, m_drawY);
        m_players[0]->DrawSprite(m_drawX + m_players[0]->IsInHitstun() * (m_players[0]->m_hitstop % 2) * 2, m_drawY);
    }
    m_players[0]->DrawObjects(m_drawX, m_drawY, 1);
    m_players[1]->DrawObjects(m_drawX, m_drawY, 1);
    m_game->DrawEffects(m_drawX, m_drawY, 1);
    m_game->DrawEffects(m_drawX, m_drawY, 2);
    m_game->DrawEffects(m_drawX, m_drawY, 3);
    if ((int)m_game->m_background != 0 && m_players[0]->m_fillTime == 0 && m_players[1]->m_fillTime == 0 && m_game->m_negativeTime == 0) {
        m_game->m_background->Draw(m_drawX, m_drawY, 1);
    }
    if (m_game->m_hideHudTime == 0) {
        m_players[0]->DrawGauge();
        m_players[1]->DrawGauge();
    }
    DrawGauges();
    if (m_players[0]->m_shownHits > 1 && m_players[0]->m_comboTimer > 0) {
        DrawComboCount(m_players[0]);
    }
    if (m_players[1]->m_shownHits > 1 && m_players[1]->m_comboTimer > 0) {
        DrawComboCount(m_players[1]);
    }
    if (m_capturing != 0) {
        if (m_captureFrame % 2 == 0) {
            m_graphics->Screenshot(m_captureFrame / 2, m_game->m_palette);
        }
        m_captureFrame++;
    }
    if (0) {
        DrawNumber(0x50, 0x64, m_players[0]->m_hp, 2, 0, 0);
        DrawNumber(0x50, 0x6e, m_players[0]->pattern, 2, 0, 0);
        DrawNumber(0x50, 0x78, m_players[0]->frame, 2, 0, 0);
        DrawNumber(0x50, 0x82, m_players[0]->timer, 2, 0, 0);
        DrawNumber(0x118, 0x64, m_players[1]->m_hp, 2, 0, 0);
        DrawNumber(0x118, 0x6e, m_players[1]->pattern, 2, 0, 0);
        DrawNumber(0x118, 0x78, m_players[1]->frame, 2, 0, 0);
        DrawNumber(0x118, 0x82, m_players[1]->timer, 2, 0, 0);
    }
    DrawBordersAndFlip();
}

void CScene3::UpdateCamera()
{
    int v8;
    int v4;

    m_focusX = m_focusXDefault;
    if (m_game->m_cameraFocusXTime > 0) {
        m_focusX = m_game->m_cameraFocusX;
        if (m_players[0]->m_hitstop == 0 && m_players[1]->m_hitstop == 0 && m_players[0]->m_freezeTime == 0 && m_players[1]->m_freezeTime == 0) {
            m_game->m_cameraFocusXTime--;
        }
    }
    v4 = 0xa0 - (int)((m_players[0]->x * (m_focusX + 0x32) + m_players[1]->x * (0x32 - m_focusX)) / 100.0);
    if (v4 < -0x13f) {
        v4 = -0x13f;
    } else if (v4 > 0) {
        v4 = 0;
    }
    if (m_scrollX < v4) {
        m_scrollX -= (m_scrollX - v4) / 0xf - 1;
        if (m_scrollX > v4) {
            m_scrollX = v4;
        }
    } else {
        m_scrollX -= (m_scrollX - v4) / 0xf + 1;
        if (m_scrollX < v4) {
            m_scrollX = v4;
        }
    }
    if (m_focusY < m_focusYHigh) {
        m_focusY += m_focusYStep;
        if (m_focusY > m_focusYHigh) {
            m_focusY = m_focusYHigh;
        }
    } else {
        m_focusY += m_focusYStep;
        if (m_focusY > m_focusYHigh) {
            m_focusY = m_focusYHigh;
        }
    }
    if (m_players[0]->y < -240.0 || m_players[1]->y < -240.0) {
        m_focusY = m_focusYHigh;
    } else {
        m_focusY = 0x14;
    }
    if (m_game->m_cameraFocusYTime > 0) {
        m_focusY = m_game->m_cameraFocusY * (1 - ((m_players[0]->y < m_players[1]->y) << 1));
        if (m_players[0]->m_hitstop == 0 && m_players[1]->m_hitstop == 0 && m_players[0]->m_freezeTime == 0 && m_players[1]->m_freezeTime == 0) {
            m_game->m_cameraFocusYTime--;
        }
    }
    if ((v8 = -(((int)m_players[0]->y - (m_players[0]->y < 0.0) + (int)m_players[1]->y - (m_players[1]->y < 0.0)) / 2) + ((int)m_players[0]->y - (m_players[0]->y < 0.0) - (int)m_players[1]->y + (m_players[1]->y < 0.0)) * m_focusY / 0x64 * ((m_players[0]->y - m_players[1]->y < 0.0) * 2 + -1)) < 0) {
        v8 = 0;
    } else if (v8 > 0xf0) {
        v8 = 0xf0;
    }
    if (m_scrollY < v8) {
        m_scrollY -= (m_scrollY - v8) / 0xa - 1;
        if (m_scrollY > v8) {
            m_scrollY = v8;
        }
    } else {
        m_scrollY -= (m_scrollY - v8) / 0xa + 1;
        if (m_scrollY < v8) {
            m_scrollY = v8;
        }
    }
    m_game->UpdateShake();
    m_game->m_view = MakeRect(-m_scrollX, -m_scrollY - 0xd2, 0x140, 0xf0);
    m_drawX = m_scrollX + m_game->m_shakeX;
    m_drawY = m_scrollY + m_game->m_shakeY;
}

void CScene3::PlayPlayerSounds()
{
    int v8;
    int v4;

    if (m_leave == 2) {
        v4 = 0;
        for (; v4 < 2; v4++) {
            m_players[v4]->m_playSound = -1;
            m_players[v4]->m_playVoice = -1;
        }
        return;
    }
    v8 = 0;
    for (; v8 < 2; v8++) {
        if (m_players[v8]->m_playSound >= 0 && m_players[v8]->m_playSound < 0x41) {
            m_sound->Play((short)m_game->m_sounds[m_players[v8]->m_playSound], 0);
            m_players[v8]->m_playSound = -1;
        }
        if (m_players[v8]->m_playVoice >= 0 && m_players[v8]->m_playVoice < 0x32) {
            m_sound->Play(m_players[v8]->m_voices[m_players[v8]->m_playVoice], 0);
            m_players[v8]->m_playVoice = -1;
        }
    }
}

void CScene3::PlayEffectSounds()
{
    int v8;
    int v4;

    if (m_leave == 2) {
        v8 = m_game->m_effectTail;
        while (v8 != m_game->m_effectHead) {
            m_game->m_effects[v8].sound = -1;
            v8++;
            if (v8 >= 0x280) {
                v8 = 0;
            }
        }
        return;
    }
    v4 = m_game->m_effectTail;
    while (v4 != m_game->m_effectHead) {
        if ((char)m_game->m_effects[v4].sound >= 0 && (char)m_game->m_effects[v4].sound < 0x41) {
            m_sound->Play((short)m_game->m_sounds[(char)m_game->m_effects[v4].sound], 0);
            m_game->m_effects[v4].sound = -1;
        }
        v4++;
        if (v4 >= 0x280) {
            v4 = 0;
        }
    }
}

void CScene3::CheckKo()
{
    if (m_refillMeter != 0) {
        return;
    }
    if (m_game->m_gameMode == 1) {
        return;
    }
    if (m_game->m_roundOver != 0) {
        m_players[0]->m_pressA = 0;
        m_players[0]->m_pressB = 0;
        m_players[0]->m_pressC = 0;
        m_players[0]->m_pressD = 0;
        m_players[1]->m_pressA = 0;
        m_players[1]->m_pressB = 0;
        m_players[1]->m_pressC = 0;
        m_players[1]->m_pressD = 0;
        if (m_players[0]->pattern >= kFirstHitReaction && m_players[0]->IsDashing() == 0 || m_players[1]->pattern >= kFirstHitReaction && m_players[1]->IsDashing() == 0 || m_leave == 2) {
            return;
        }
        m_game->m_roundOver = 0;
        m_players[0]->m_hp = 0x270f;
        m_players[1]->m_hp = 0x270f;
        m_game->m_intro = 2;
        return;
    }
    EffectDesc v48;
    if (m_players[0]->m_hp <= 0 && m_players[1]->m_hp <= 0) {
        m_players[0]->m_roundsWon++;
        m_players[1]->m_roundsWon++;
        if (m_players[0]->m_roundsWon >= m_game->m_roundsToWin) {
            m_players[0]->m_roundsWon--;
        }
        if (m_players[1]->m_roundsWon >= m_game->m_roundsToWin) {
            m_players[1]->m_roundsWon--;
        }
        m_players[0]->pattern = kHitAir;
        m_players[0]->StartPattern();
        m_players[1]->pattern = kHitAir;
        m_players[1]->StartPattern();
        m_game->m_roundOver = 1;
        if (m_game->m_round < 9) {
            m_game->m_round++;
        }
        return;
    }
    if (m_players[0]->m_hp <= 0 && m_players[0]->m_koDelay == 0) {
        m_players[1]->m_wonHpTotal += m_players[1]->m_hp;
        if (m_players[1]->m_roundsWon < m_game->m_roundsToWin - 1) {
            m_players[1]->m_roundsWon++;
            m_players[0]->m_freezeTime = m_players[0]->m_freezeTime + 0xb4;
            m_players[1]->m_freezeTime = m_players[1]->m_freezeTime + 0xb4;
            m_players[0]->StartPattern();
            v48.keep = 0;
            v48.x = 80.0;
            v48.y = 100.0;
            v48.side = 0;
            v48.scale = 0;
            v48.layer = 2;
            v48.screen = 1;
            v48.type = kEffectDown;
            v48.sound = 0x1d;
            m_game->CreateEffect((EffectDesc*)&v48);
            m_game->m_roundOver = 1;
            if (m_game->m_round < 9) {
                m_game->m_round++;
            }
        } else {
            m_players[1]->m_roundsWon++;
            m_players[0]->StartPattern();
            m_game->m_roundOver = 1;
            m_leave = 2;
            m_endFade = 0.0;
            m_game->m_winner = 1;
        }
        return;
    }
    if (m_players[1]->m_hp <= 0 && m_players[1]->m_koDelay == 0) {
        m_players[0]->m_wonHpTotal += m_players[0]->m_hp;
        if (m_players[0]->m_roundsWon < m_game->m_roundsToWin - 1) {
            m_players[0]->m_roundsWon++;
            m_players[0]->m_freezeTime = m_players[0]->m_freezeTime + 0xb4;
            m_players[1]->m_freezeTime = m_players[1]->m_freezeTime + 0xb4;
            v48.keep = 0;
            v48.x = 240.0;
            v48.y = 100.0;
            v48.side = 0;
            v48.scale = 0;
            v48.layer = 2;
            v48.screen = 1;
            v48.type = kEffectDown;
            v48.sound = 0x1d;
            m_game->CreateEffect((EffectDesc*)&v48);
            m_players[1]->StartPattern();
            m_game->m_roundOver = 1;
            if (m_game->m_round < 9) {
                m_game->m_round++;
            }
            return;
        }
        m_players[0]->m_roundsWon++;
        m_players[1]->StartPattern();
        m_game->m_roundOver = 1;
        m_leave = 2;
        m_endFade = 0.0;
        m_game->m_winner = 0;
    }
}

void CScene3::HandleKeys()
{
    int l10c;
    char v108[256];

    l10c = m_input->m_keyboard->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if (m_game->m_replayMode == 1 && m_game->m_replay.m_eof != 0) {
        m_game->m_replay.m_eof = 0;
        m_leave = 1;
    }
    if (m_leave == 0 && m_game->m_gameMode == 6) {
        m_game->UpdateInput();
        if (m_game->m_pressA[0] != 0 || m_game->m_pressA[1] != 0 || m_game->m_pressB[0] != 0 || m_game->m_pressB[1] != 0 || (v108[1] & 0x80) != 0) {
            m_leave = 1;
            m_game->StopMusic();
            m_paused = 0;
        }
    }
    if (m_leave == 0 && (v108[1] & 0x80) != 0) {
        m_leave = 1;
        m_paused = 0;
    }
    if ((v108[62] & 0x80) != 0 && m_game->m_intro == 0 && m_game->m_roundOver == 0 && m_game->m_gameMode != 0 && m_game->m_gameMode != 2 && m_game->m_gameMode != 6) {
        m_refillMeter = m_refillMeter + 5;
        if (m_refillMeter > 0x7d0) {
            m_refillMeter = 0;
        }
        m_refillHp = 0x270f;
        m_players[0]->m_refillMeter = m_refillMeter;
        m_players[1]->m_refillMeter = m_refillMeter;
        m_players[0]->m_refillHp = m_refillHp;
        m_players[1]->m_refillHp = m_refillHp;
    } else if ((v108[63] & 0x80) != 0 && g_fkeyHeld == 0 && m_game->m_gameMode != 0 && m_game->m_gameMode != 2 && m_game->m_gameMode != 6) {
        if (m_refillMeter == 0x3e8) {
            if (m_refillHp == 0xd04) {
                m_refillMeter = 0x7d0;
            } else {
                m_refillHp = 0xd04;
            }
        } else {
            m_refillMeter = 0x3e8;
        }
        m_players[0]->m_refillMeter = m_refillMeter;
        m_players[1]->m_refillMeter = m_refillMeter;
        m_players[0]->m_refillHp = m_refillHp;
        m_players[1]->m_refillHp = m_refillHp;
        g_fkeyHeld = 1;
    }
    if (m_game->m_gameMode == 1) {
        if ((v108[64] & 0x80) != 0 && g_fkeyHeld == 0) {
            m_game->m_dummyStance++;
            if ((char)m_game->m_dummyStance > 2) {
                m_game->m_dummyStance = 0;
            }
            g_fkeyHeld = 1;
        } else if ((v108[65] & 0x80) != 0 && g_fkeyHeld == 0) {
            m_game->m_dummyGuard = m_game->m_dummyGuard == 0;
            g_fkeyHeld = 1;
        }
    } else if (m_game->m_gameMode == 5 && m_game->m_replayMode == 2 && (v108[64] & 0x80) != 0) {
        RestartRecording();
    }
    if ((v108[66] & 0x80) != 0 && g_fkeyHeld == 0) {
        m_paused = m_paused == 0;
        g_fkeyHeld = 1;
    }
    if (m_refillMeter == 0x7d0) {
        m_refillMeter = 0;
        m_refillHp = 0x270f;
        m_players[0]->m_refillMeter = m_refillMeter;
        m_players[1]->m_refillMeter = m_refillMeter;
        m_players[0]->m_refillHp = m_refillHp;
        m_players[1]->m_refillHp = m_refillHp;
        m_players[0]->m_hp = 0x270f;
        m_players[1]->m_hp = 0x270f;
    }
    if ((v108[63] & 0x80) != 0 || (v108[64] & 0x80) != 0 || (v108[65] & 0x80) != 0 || (v108[66] & 0x80) != 0) {
        g_fkeyHeld = 1;
    } else {
        g_fkeyHeld = 0;
    }
    if (1) {
    } else {
        if ((v108[59] & 0x80) != 0) {
            m_speed = 1;
        }
        if ((v108[60] & 0x80) != 0) {
            m_speed = 2;
        }
        if ((v108[61] & 0x80) != 0) {
            m_speed = 3;
        }
        if ((v108[67] & 0x80) != 0) {
            m_capturing = 1;
        }
        if ((v108[68] & 0x80) != 0) {
            m_capturing = 0;
        }
        if ((v108[87] & 0x80) != 0) {
            m_captureFrame = 0;
        }
        if ((v108[88] & 0x80) != 0) {
            m_players[0]->m_hp = 1;
            m_players[1]->m_hp = 1;
        }
    }
    if (m_game->m_replayMode == 1 && m_paused == 0) {
        if (m_game->m_replayVersion > 0) {
            m_refillMeter = m_game->m_replay.Read();
            m_refillHp = m_game->m_replay.Read();
        } else {
            m_refillMeter = 0x3e8;
            m_refillHp = 0x270f;
        }
        m_players[0]->m_refillMeter = m_refillMeter;
        m_players[1]->m_refillMeter = m_refillMeter;
        m_players[0]->m_refillHp = m_refillHp;
        m_players[1]->m_refillHp = m_refillHp;
        return;
    }
    if (m_game->m_replayMode == 2 && m_paused == 0) {
        m_game->m_replay.Write(m_refillMeter);
        m_game->m_replay.Write(m_refillHp);
    }
}

int CScene3::UpdateEndFade()
{
    if (m_endFade < 100.0) {
        m_graphics->Brighten(m_game->m_palette, 0, 0xff, (int)(100.0 - m_endFade));
        m_sound->SetVolume((short)m_game->m_music, (int)(-m_endFade * 100.0 / 2.0) + m_game->m_musicVolume);
    }
    m_endFade++;
    if (m_endFade >= 200.0) {
        return 1;
    }
    return 0;
}

void CScene3::StartIntro()
{
    if (m_game->m_intro == 0) {
        return;
    }
    EffectDesc v48;
    switch (m_game->m_intro) {
    case 1:
        v48.keep = 0;
        v48.x = 160.0;
        v48.y = 120.0;
        v48.side = 0;
        v48.scale = 2;
        v48.layer = 2;
        v48.screen = 1;
        v48.type = kEffectMotto;
        v48.sound = -1;
        m_game->CreateEffect((EffectDesc*)&v48);
        m_game->m_intro = 0x63;
        m_game->unk1352 = 0x12c;
        break;
    case 2:
        v48.keep = 0;
        v48.x = 160.0;
        v48.y = 120.0;
        v48.side = 0;
        v48.scale = 2;
        v48.layer = 2;
        v48.screen = 1;
        v48.type = kEffectRoundFlash;
        v48.sound = m_game->m_round + 0xb;
        m_game->CreateEffect((EffectDesc*)&v48);
        m_game->m_intro = 0x63;
        m_game->unk1352 = 0x10e;
    }
}

void CScene3::RestartRecording()
{
    char v34[40];
    char vc[8];

    if (m_game->m_gameMode == 5 && m_game->m_replayMode == 2) {
        CScene::FadeOut(m_game->m_palette, 0, 0, 0);
        m_game->m_replay.Close();
        strcpy(v34, "replay\\data");
        _itoa(m_game->m_replayPage + 1, vc, 0xa);
        strcat(v34, (const char*)vc);
        strcat(v34, "-");
        _itoa(m_game->m_replaySlot + 1, vc, 0xa);
        strcat(v34, (const char*)vc);
        strcat(v34, ".rep");
        m_game->m_replay.OpenWrite((const char*)v34);
        m_game->m_replay.Write((*m_player1Ref)->m_charId);
        m_game->m_replay.Write((*m_player2Ref)->m_charId);
        m_game->m_replay.Write(0x68);
        m_game->m_replay.Write(m_game->m_stage);
        m_game->m_replay.Write((*m_player1Ref)->m_paletteIndex);
        m_game->m_replay.Write((*m_player2Ref)->m_paletteIndex);
        m_game->Reset();
        (*m_player1Ref)->Load();
        (*m_player2Ref)->Load();
        m_players[0]->m_refillMeter = m_refillMeter;
        m_players[1]->m_refillMeter = m_refillMeter;
        m_game->m_intro = 1;
        m_focusXDefault = 0;
        m_focusYHigh = -0x32;
        m_focusX = m_focusXDefault;
        m_focusY = m_focusYHigh;
        m_focusYStep = 5;
        m_scrollX = -0xa0;
        m_scrollY = 0;
        m_speed = 3;
        UpdateCamera();
        Draw();
        CScene::FadeIn(m_game->m_palette, 0);
    }
}

void CScene3::CheckHits()
{
    int l1f0;
    int v1ec;
    CollisionInfo x1e8;
    int vf8;
    int lf4;
    CollisionInfo vf0;

    x1e8.frame = m_players[0]->m_patterns[m_players[0]->pattern].frames[m_players[0]->frame];
    x1e8.anim = m_players[0]->anims[m_players[0]->pattern].frames[m_players[0]->frame];
    x1e8.x = m_players[0]->x;
    x1e8.y = m_players[0]->y;
    x1e8.facing = m_players[0]->facing;
    vf0.frame = m_players[1]->m_patterns[m_players[1]->pattern].frames[m_players[1]->frame];
    vf0.anim = m_players[1]->anims[m_players[1]->pattern].frames[m_players[1]->frame];
    vf0.x = m_players[1]->x;
    vf0.y = m_players[1]->y;
    vf0.facing = m_players[1]->facing;
    lf4 = WillRecoilCounter(m_players[0], m_players[1], (CollisionInfo*)&x1e8, (CollisionInfo*)&vf0);
    v1ec = WillRecoilCounter(m_players[1], m_players[0], (CollisionInfo*)&vf0, (CollisionInfo*)&x1e8);
    m_players[0]->m_counterHit = 0;
    m_players[1]->m_counterHit = 0;
    vf8 = m_players[0]->m_objectTail;
    while (vf8 != m_players[0]->m_objectHead) {
        l1f0 = m_players[1]->m_objectTail;
        while (l1f0 != m_players[1]->m_objectHead) {
            if (m_players[0]->m_objectActive[vf8] != 0 && m_players[1]->m_objectActive[l1f0] != 0) {
                ClashObjects(m_players[0], m_players[1], vf8, l1f0);
            }
            l1f0++;
            if (l1f0 >= 0x40) {
                l1f0 = 0;
            }
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    vf8 = m_players[0]->m_objectTail;
    while (vf8 != m_players[0]->m_objectHead) {
        l1f0 = m_players[1]->m_objectTail;
        while (l1f0 != m_players[1]->m_objectHead) {
            if (m_players[0]->m_objectActive[vf8] != 0 && m_players[1]->m_objectActive[l1f0] != 0) {
                ResolveObjectHitsObject(m_players[0], m_players[1], vf8, l1f0);
                ResolveObjectHitsObject(m_players[1], m_players[0], l1f0, vf8);
            }
            l1f0++;
            if (l1f0 >= 0x40) {
                l1f0 = 0;
            }
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    vf8 = m_players[1]->m_objectTail;
    while (vf8 != m_players[1]->m_objectHead) {
        if (m_players[1]->m_objectActive[vf8] != 0) {
            ResolveObjectAttack(m_players[1], m_players[0], vf8, (CollisionInfo*)&x1e8);
            ResolvePlayerHitsObject(m_players[0], m_players[1], (CollisionInfo*)&x1e8, (CollisionInfo*)&vf0, vf8);
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    vf8 = m_players[0]->m_objectTail;
    while (vf8 != m_players[0]->m_objectHead) {
        if (m_players[0]->m_objectActive[vf8] != 0) {
            ResolveObjectAttack(m_players[0], m_players[1], vf8, (CollisionInfo*)&vf0);
            ResolvePlayerHitsObject(m_players[1], m_players[0], (CollisionInfo*)&vf0, (CollisionInfo*)&x1e8, vf8);
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    x1e8.attackResult = *(char*)&m_players[0]->m_attackResult;
    x1e8.hitsLeft = m_players[0]->m_hitsLeft;
    vf0.attackResult = *(char*)&m_players[1]->m_attackResult;
    vf0.hitsLeft = m_players[1]->m_hitsLeft;
    if (v1ec == 0) {
        ResolvePlayerAttack(m_players[0], m_players[1], (CollisionInfo*)&x1e8, (CollisionInfo*)&vf0);
    }
    if (lf4 == 0) {
        ResolvePlayerAttack(m_players[1], m_players[0], (CollisionInfo*)&vf0, (CollisionInfo*)&x1e8);
    }
}

void CScene3::PushApart()
{
    int x3c;
    RECT v38;
    RECT v28;
    double n18;
    double v10;
    double x8;

    v10 = m_players[0]->vx;
    n18 = m_players[1]->vx;
    m_players[0]->m_pushVx = 0.0;
    m_players[1]->m_pushVx = 0.0;
    v38 = this->BoxOnStage((ObjBase*)m_players[0], &m_players[0]->m_patterns[m_players[0]->pattern].frames[m_players[0]->frame].pushBox);
    v28 = this->BoxOnStage((ObjBase*)m_players[1], &m_players[1]->m_patterns[m_players[1]->pattern].frames[m_players[1]->frame].pushBox);
    if (BoxesOverlap(&v38, &v28) != 0) {
        if (v38.left + v38.right - (v28.left + v28.right) > 0) {
            x3c = v28.right - v38.left;
            (int)(m_players[0]->x <= 160.0);
            m_players[0]->x += x3c / 2.0;
            (int)(m_players[0]->x > 160.0);
            m_players[1]->x = m_players[1]->x - x3c / 2.0;
            if ((char)m_players[0]->AtScreenEdge() == -1) {
                v10 = (m_players[0]->facing * v10 < 0.0) * v10;
                n18 = (m_players[0]->facing * v10 + m_players[1]->facing * n18 < 0.0) * n18;
                if (m_players[0]->facing * v10 < m_players[1]->facing * n18) {
                    x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                    n18 = m_players[1]->facing * x8;
                    m_players[0]->m_pushVx = v10 - m_players[0]->vx;
                    m_players[1]->m_pushVx = n18 - m_players[1]->vx;
                }
                return;
            }
            if ((char)m_players[1]->AtScreenEdge() == 1) {
                n18 = (m_players[1]->facing * n18 > 0.0) * n18;
                v10 = (m_players[1]->facing * n18 + m_players[0]->facing * v10 > 0.0) * v10;
                if (m_players[1]->facing * n18 > m_players[0]->facing * v10) {
                    x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                    v10 = m_players[0]->facing * x8;
                    m_players[0]->m_pushVx = v10 - m_players[0]->vx;
                    m_players[1]->m_pushVx = n18 - m_players[1]->vx;
                }
                return;
            }
            if (m_players[1]->facing * n18 >= 0.0 && m_players[0]->facing * v10 <= 0.0) {
                x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                v10 = m_players[0]->facing * x8;
                n18 = m_players[1]->facing * x8;
                m_players[0]->m_pushVx = v10 - m_players[0]->vx;
                m_players[1]->m_pushVx = n18 - m_players[1]->vx;
                return;
            }
            return;
        }
        x3c = v28.left - v38.right;
        (int)(m_players[1]->x >= 479.0);
        m_players[0]->x += x3c / 2.0;
        (int)(m_players[1]->x < 479.0);
        m_players[1]->x = m_players[1]->x - x3c / 2.0;
        if ((char)m_players[0]->AtScreenEdge() == 1) {
            v10 = (m_players[0]->facing * v10 > 0.0) * v10;
            n18 = (m_players[0]->facing * v10 + m_players[1]->facing * n18 > 0.0) * n18;
            if (m_players[0]->facing * v10 > m_players[1]->facing * n18) {
                x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                n18 = m_players[1]->facing * x8;
                m_players[0]->m_pushVx = v10 - m_players[0]->vx;
                m_players[1]->m_pushVx = n18 - m_players[1]->vx;
            }
            return;
        }
        if ((char)m_players[1]->AtScreenEdge() == -1) {
            n18 = (m_players[1]->facing * n18 < 0.0) * n18;
            v10 = (m_players[1]->facing * n18 + m_players[0]->facing * v10 < 0.0) * v10;
            if (m_players[0]->facing * v10 < m_players[1]->facing * n18) {
                x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                v10 = m_players[0]->facing * x8;
                m_players[0]->m_pushVx = v10 - m_players[0]->vx;
                m_players[1]->m_pushVx = n18 - m_players[1]->vx;
            }
            return;
        }
        if (m_players[1]->facing * n18 <= 0.0 && m_players[0]->facing * v10 >= 0.0) {
            x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
            v10 = m_players[0]->facing * x8;
            n18 = m_players[1]->facing * x8;
            m_players[0]->m_pushVx = v10 - m_players[0]->vx;
            m_players[1]->m_pushVx = n18 - m_players[1]->vx;
        }
    }
}

RECT CScene3::BoxOnStage(ObjBase* p1, RECT* p2)
{
    short v18;
    RECT v14;
    short l4;

    l4 = p1->anims[p1->pattern].frames[p1->frame].x;
    v18 = p1->anims[p1->pattern].frames[p1->frame].y;
    if (p1->facing == 1) {
        v14.top = (int)(p1->y - v18 + p2->top);
        v14.bottom = (int)(p1->y - v18 + p2->bottom);
        v14.left = (int)(p1->x - 0.5 - l4 + p2->left);
        v14.right = (int)(p1->x - 0.5 - l4 + p2->right);
    } else {
        v14.top = (int)(p1->y - v18 + p2->top);
        v14.bottom = (int)(p1->y - v18 + p2->bottom);
        v14.left = (int)(p1->x + 0.5 + l4 - p2->right);
        v14.right = (int)(p1->x + 0.5 + l4 - p2->left);
    }
    return v14;
}

RECT CScene3::InfoBoxOnStage(CollisionInfo* p1, RECT* p2)
{
    short v18;
    RECT v14;
    short l4;

    l4 = p1->anim.x;
    v18 = p1->anim.y;
    if (p1->facing == 1) {
        v14.top = (int)(p1->y - v18 + p2->top);
        v14.bottom = (int)(p1->y - v18 + p2->bottom);
        v14.left = (int)(p1->x - 0.5 - l4 + p2->left);
        v14.right = (int)(p1->x - 0.5 - l4 + p2->right);
    } else {
        v14.top = (int)(p1->y - v18 + p2->top);
        v14.bottom = (int)(p1->y - v18 + p2->bottom);
        v14.left = (int)(p1->x + 0.5 + l4 - p2->right);
        v14.right = (int)(p1->x + 0.5 + l4 - p2->left);
    }
    return v14;
}

int CScene3::BoxesOverlap(RECT* p1, RECT* p2)
{
    if (p1->right <= p1->left || p1->top >= p1->bottom || p2->right <= p2->left || p2->top >= p2->bottom) {
        return 0;
    }
    return ~(p2->right - p1->left | p1->right - p2->left | p2->bottom - p1->top | p1->bottom - p2->top) >> 0x1f;
}

int CScene3::WillRecoilCounter(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4)
{
    RECT b29c;
    int v28c;
    RECT n288;
    int v278;
    int v274;
    int v270[4][5];
#if defined(EFZ_NATIVE) || defined(EFZ_TRACE)
    // Only [i][0] is set for a throw; the rest, read when placing the hit spark, is
    // whatever the stack held (the effect's position varies). Zeroed in the native and
    // test builds.
    memset(v270, 0, sizeof(v270));
#endif
    RECT l220[5];
    PatternFrame b1d0;
    PatternFrame v108;
    RECT x40[4];

    v274 = 0;
    b1d0 = p3->frame;
    v108 = p4->frame;
    v28c = 0;
    for (; v28c < 4; v28c++) {
        x40[v28c] = this->InfoBoxOnStage(p3, &b1d0.attackBoxes[v28c]);
    }
    v28c = 0;
    for (; v28c < 5; v28c++) {
        l220[v28c] = this->InfoBoxOnStage(p4, &v108.boxes[v28c]);
    }
    b29c = this->InfoBoxOnStage(p4, &v108.pushBox);
    if (p1->m_attackResult == 0 && (v108.flagsB0 & kStateInvulnerable) == 0 && p1->m_hitsLeft > 0 && (p2->m_throwProtect <= 0 || (b1d0.flagsAA & kAttackThrow) <= 0) && p2->CanAirRecover() == 0 && p2->m_invulTime == 0) {
        if ((b1d0.flagsAA & kAttackThrow) > 0) {
            v28c = 0;
            for (; v28c < 4; v28c++) {
                v270[v28c][0] = 1;
                v274 = BoxesOverlap(&x40[v28c], &b29c) | v274;
            }
        } else {
            v28c = 0;
            for (; v28c < 4; v28c++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    v270[v28c][v278] = BoxesOverlap(&x40[v28c], &l220[v278]);
                    v274 |= v270[v28c][v278];
                }
            }
        }
        if (v274 != 0) {
            n288 = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            v28c = 0;
            for (; v28c < 4; v28c++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    if (v270[v28c][v278] != 0) {
                        if (n288.left < x40[v28c].left) {
                            n288.left = x40[v28c].left;
                        }
                        if (n288.top < x40[v28c].top) {
                            n288.top = x40[v28c].top;
                        }
                        if (n288.right > x40[v28c].right) {
                            n288.right = x40[v28c].right;
                        }
                        if (n288.bottom > x40[v28c].bottom) {
                            n288.bottom = x40[v28c].bottom;
                        }
                        if (n288.left < l220[v278].left) {
                            n288.left = l220[v278].left;
                        }
                        if (n288.top < l220[v278].top) {
                            n288.top = l220[v278].top;
                        }
                        if (n288.right > l220[v278].right) {
                            n288.right = l220[v278].right;
                        }
                        if (n288.bottom > l220[v278].bottom) {
                            n288.bottom = l220[v278].bottom;
                        }
                    }
                }
            }
            if (p2->m_canRecoilCounter != 0 && p2->m_recoilGuardWindow >= 0x1e && p2->m_noGuardTime == 0 && p2->HoldsGuard(&b1d0) != 0 && (b1d0.flagsAA & kAttackUnblockable) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void CScene3::ResolvePlayerAttack(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4)
{
    RECT v2e4;
    int v2d4;
    RECT v2d0;
    int v278;
    int v274;
    int v270[4][5];
#if defined(EFZ_NATIVE) || defined(EFZ_TRACE)
    // Only [i][0] is set for a throw; the rest, read when placing the hit spark, is
    // whatever the stack held (the effect's position varies). Zeroed in the native and
    // test builds.
    memset(v270, 0, sizeof(v270));
#endif
    RECT l220[5];
    PatternFrame b1d0;
    PatternFrame v108;
    RECT x40[4];

    v274 = 0;
    b1d0 = p3->frame;
    v108 = p4->frame;
    EffectDesc k2c0;
    v2d4 = 0;
    for (; v2d4 < 4; v2d4++) {
        x40[v2d4] = this->InfoBoxOnStage(p3, &b1d0.attackBoxes[v2d4]);
    }
    v2d4 = 0;
    for (; v2d4 < 5; v2d4++) {
        l220[v2d4] = this->InfoBoxOnStage(p4, &v108.boxes[v2d4]);
    }
    v2e4 = this->InfoBoxOnStage(p4, &v108.pushBox);
    if (p3->attackResult == 0 && (v108.flagsB0 & kStateInvulnerable) == 0 && p3->hitsLeft > 0 && (p2->m_throwProtect <= 0 || (b1d0.flagsAA & kAttackThrow) <= 0) && p2->CanAirRecover() == 0 && p2->m_invulTime == 0) {
        if ((b1d0.flagsAA & kAttackThrow) > 0) {
            v2d4 = 0;
            for (; v2d4 < 4; v2d4++) {
                v270[v2d4][0] = 1;
                v274 = BoxesOverlap(&x40[v2d4], &v2e4) | v274;
            }
        } else {
            v2d4 = 0;
            for (; v2d4 < 4; v2d4++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    v270[v2d4][v278] = BoxesOverlap(&x40[v2d4], &l220[v278]);
                    v274 |= v270[v2d4][v278];
                }
            }
        }
        if (v274 != 0) {
            v2d0 = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            v2d4 = 0;
            for (; v2d4 < 4; v2d4++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    if (v270[v2d4][v278] != 0) {
                        if (v2d0.left < x40[v2d4].left) {
                            v2d0.left = x40[v2d4].left;
                        }
                        if (v2d0.top < x40[v2d4].top) {
                            v2d0.top = x40[v2d4].top;
                        }
                        if (v2d0.right > x40[v2d4].right) {
                            v2d0.right = x40[v2d4].right;
                        }
                        if (v2d0.bottom > x40[v2d4].bottom) {
                            v2d0.bottom = x40[v2d4].bottom;
                        }
                        if (v2d0.left < l220[v278].left) {
                            v2d0.left = l220[v278].left;
                        }
                        if (v2d0.top < l220[v278].top) {
                            v2d0.top = l220[v278].top;
                        }
                        if (v2d0.right > l220[v278].right) {
                            v2d0.right = l220[v278].right;
                        }
                        if (v2d0.bottom > l220[v278].bottom) {
                            v2d0.bottom = l220[v278].bottom;
                        }
                    }
                }
            }
            if ((v108.flagsB0 & kStateParryHigh) > 0 && (b1d0.flagsAA & kAttackIgnoresArmor) == 0 && (b1d0.flagsAA & kAttackGuardStand) > 0) {
                p1->m_hitsLeft--;
                p1->m_attackResult = 2;
                p1->m_attackResult = 6;
                p2->m_attackResult = 6;
                return;
            }
            if ((v108.flagsB0 & kStateParryLow) > 0 && (b1d0.flagsAA & kAttackIgnoresArmor) == 0 && (b1d0.flagsAA & kAttackGuardCrouch) > 0) {
                p1->m_hitsLeft--;
                p1->m_attackResult = 2;
                p1->m_attackResult = 6;
                p2->m_attackResult = 6;
                return;
            }
            if (p2->m_canRecoilCounter != 0 && p2->m_recoilGuardWindow >= 0x1e && p2->m_noGuardTime == 0 && p2->HoldsGuard(&b1d0) != 0 && (b1d0.flagsAA & kAttackUnblockable) == 0) {
                p1->m_attackResult = 2;
                p1->m_gauge += b1d0.gaugeOnGuard;
                p1->m_hitsLeft--;
                p2->m_hitByBody = 1;
                k2c0.keep = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = kEffectRecoilGuard;
                k2c0.sound = 0xa;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p2->StartPattern();
                p2->FaceOpponent();
                if (p2->y == 0.0) {
                    p2->pattern = (p2->m_inputY == 1) + 0xa8;
                } else {
                    p2->pattern = kRecoilGuardAir;
                }
                p1->ClearInput();
                p2->ClearInput();
                p2->m_freezeTime = 0x3c;
                p2->m_canRecoilCounter = 0;
                p1->m_canRecoilCounter = 1;
                return;
            }
            if (p2->m_recoilGuardWindow >= 0x1e && p2->y < 0.0 && p2->CanGuard(&b1d0, &v108) != 0) {
                p1->m_attackResult = 2;
                p1->m_gauge += b1d0.gaugeOnGuard;
                p1->m_hitsLeft--;
                p2->m_hitByBody = 1;
                k2c0.keep = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = kEffectRecoilGuard;
                k2c0.sound = 0xa;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p2->StartPattern();
                p2->FaceOpponent();
                p2->pattern = kRecoilGuardAir;
                p1->ClearInput();
                p2->ClearInput();
                p2->m_freezeTime = 0x3c;
                p1->m_canRecoilCounter = 1;
                return;
            }
            if (p2->CanGuard(&b1d0, &v108) != 0 && p2->m_recoilGuardWindow >= 0x1e && p2->y == 0.0 && p2->pattern != kRecoilGuardStand && p2->pattern != kRecoilGuardCrouch) {
                p1->m_attackResult = 2;
                p1->m_gauge += b1d0.gaugeOnGuard;
                p1->m_hitsLeft--;
                p2->m_hitByBody = 1;
                k2c0.keep = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = kEffectRecoilGuard;
                k2c0.sound = 0xa;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p2->StartPattern();
                p2->FaceOpponent();
                p2->pattern = (p2->m_inputY == 1) + 0xa8;
                p1->ClearInput();
                p2->ClearInput();
                p2->m_freezeTime = 0x3c;
                p1->m_canRecoilCounter = 1;
                return;
            }
            if ((v108.flagsB0 & kStateGuardPoint) > 0 && (v108.flagsAA & kAttackGuardStand) > 0 && (b1d0.flagsAA & kAttackGuardStand) > 0) {
                p1->m_hitsLeft--;
                k2c0.keep = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = kEffectGuardSpark;
                k2c0.sound = 3;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p1->m_attackResult = 2;
                p1->m_hitstop = b1d0.attackerHitstop;
                p2->m_hitstop = b1d0.defenderHitstop;
                p2->m_hp -= b1d0.chipDamage;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->m_guardGauge = b1d0.damage / 0x1e + p2->m_guardGauge;
                if (p2->m_guardGauge > 3.6e+02f) {
                    *(int*)&p2->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if ((v108.flagsB0 & kStateGuardPoint) > 0 && (v108.flagsAA & kAttackGuardCrouch) > 0 && (b1d0.flagsAA & kAttackGuardCrouch) > 0) {
                p1->m_hitsLeft--;
                k2c0.keep = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = kEffectGuardSpark;
                k2c0.sound = 3;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p1->m_attackResult = 2;
                p1->m_hitstop = b1d0.attackerHitstop;
                p2->m_hitstop = b1d0.defenderHitstop;
                p2->m_hp -= b1d0.chipDamage;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->m_guardGauge = b1d0.damage / 0x1e + p2->m_guardGauge;
                if (p2->m_guardGauge > 3.6e+02f) {
                    *(int*)&p2->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if ((v108.flagsB0 & kStateGuardPoint) > 0 && (v108.flagsAA & kAttackGuardAir) > 0 && (b1d0.flagsAA & kAttackGuardAir) > 0 && p2->y < 0.0) {
                p1->m_hitsLeft--;
                k2c0.keep = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = kEffectGuardSpark;
                k2c0.sound = 3;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p1->m_attackResult = 2;
                p1->m_hitstop = b1d0.attackerHitstop;
                p2->m_hitstop = b1d0.defenderHitstop;
                p2->m_hp -= b1d0.chipDamage;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                return;
            }
            if (p2->CanGuard(&b1d0, &v108) != 0) {
                p1->m_attackResult = 2;
                p1->m_gauge += b1d0.gaugeOnGuard;
                p1->m_hitsLeft--;
                p2->m_hitByBody = 1;
                k2c0.keep = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                p2->pattern = (b1d0.flagsAA & kAttackMedium) / 0x10 + 0x96 + (b1d0.flagsAA & kAttackHeavy) / 0x20 * 2 + (p2->m_inputY == 1 || (b1d0.flagsAA & v108.flagsB0 & 5) == 0 && p2->m_cpu != 0) * 3;
                if (p2->y < 0.0) {
                    p2->pattern = kGuardAir;
                }
                p2->StartPattern();
                p2->FaceOpponent();
                p1->m_hitstop = b1d0.attackerHitstop;
                p2->m_hitstop = b1d0.defenderHitstop;
                p2->m_hp -= b1d0.chipDamage;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                if (p1->m_guardGauge > 0.0f) {
                    p1->m_guardGauge = p1->m_guardGauge - b1d0.damage / 0x1e;
                    if (p1->m_guardGauge < 0.0f) {
                        p2->m_guardGauge = p2->m_guardGauge - p1->m_guardGauge;
                        *(int*)&p1->m_guardGauge = 0;
                    }
                } else {
                    p2->m_guardGauge = b1d0.damage / 0x1e + p2->m_guardGauge;
                    if (p2->m_guardGauge > 3.6e+02f) {
                        *(int*)&p2->m_guardGauge = 0x43b40000;
                    }
                }
                p2->m_guardedObject = 0;
                k2c0.type = kEffectGuardSpark;
                k2c0.sound = 3;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                return;
            }
            if ((v108.flagsB0 & kStateArmor) == 0 && p2->m_armorTime == 0 || ((v108.flagsB0 & kStateArmor) > 0 || p2->m_armorTime > 0) && (b1d0.flagsAA & kAttackIgnoresArmor) > 0 || (b1d0.flagsAA & kAttackThrow) > 0) {
                if (p2->y >= 0.0) {
                    if (b1d0.groundHitPattern > 0) {
                        p2->pattern = b1d0.groundHitPattern;
                    } else if ((v108.flagsB0 & (kStateStanding | kStateCrouching)) == 3) {
                        p2->pattern = kHitAir;
                    } else if ((v108.flagsB0 & kStateStanding) != 0) {
                        p2->pattern = ((b1d0.flagsAA & kAttackBodyHit) > 0) * 3 + 0x32 + ((b1d0.flagsAA & kAttackMedium) > 0) + ((b1d0.flagsAA & kAttackHeavy) > 0) * 2;
                    } else if ((v108.flagsB0 & kStateCrouching) != 0) {
                        p2->pattern = ((b1d0.flagsAA & kAttackMedium) > 0) + 0x38 + ((b1d0.flagsAA & kAttackHeavy) > 0) * 2;
                    }
                } else if (b1d0.airHitPattern > 0) {
                    p2->pattern = b1d0.airHitPattern;
                } else {
                    p2->pattern = kHitAir;
                }
                p1->m_attackResult = 3;
                p2->StartPattern();
                p2->FaceOpponent();
            } else {
                p1->m_comboHits = 0;
                p2->Tint(0xdf, 3);
                p1->m_attackResult = 7;
            }
            if ((v108.flagsB0 & kStateCanGuard) > 0) {
                p1->m_comboHits = 0;
                if (p1->m_proration > 10000.0) {
                    p1->m_proration -= 20.0;
                } else {
                    p1->m_proration = 10000.0;
                }
            }
            p2->m_hitVx = b1d0.hitVx;
            p2->m_hitVy = b1d0.hitVy;
            p2->m_hitByBody = 1;
            if (p1->m_comboHits == 0) {
                p2->m_comboStartHp = p2->m_hp;
            }
            p1->m_counterHit = (b1d0.flagsAA & kAttackCounterHit) > 0 && (v108.flagsB0 & kStateCounterHittable) > 0;
            p2->m_hp -= (int)((double)b1d0.damage * p1->AttackFactor() * p2->DefenseFactor() * p1->ProrationFactor());
            p2->m_untechTime = (int)(b1d0.untechTime * (p1->m_proration / 10000.0 * 0.8));
            p2->m_noAirRecovery = (b1d0.flagsAA & kAttackNoAirRecovery) > 0;
            p2->m_landHittable = (b1d0.flagsAA & kAttackLandHittable) > 0;
            p2->m_dashMomentum = 0;
            p2->m_airDashes = 0;
            p2->m_airActions = 0;
            p1->m_shownProration = p1->m_proration / 100.0;
            p1->m_proration = b1d0.proration / 1e+03f * p1->m_proration;
            if (p1->m_proration > 10000.0) {
                p1->m_proration = b1d0.proration / 1e+03f * p1->m_proration;
            }
            p1->m_comboHits++;
            p1->m_shownHits = p1->m_comboHits;
            p1->m_comboTimer = 0xb4;
            p1->m_comboDamage = p2->m_comboStartHp - p2->m_hp;
            p1->m_gauge += b1d0.gaugeOnHit;
            p1->m_hitstop = b1d0.attackerHitstop;
            p2->m_hitstop = b1d0.defenderHitstop;
            p1->m_hitsLeft--;
            k2c0.keep = 0;
            k2c0.type = b1d0.hitEffect;
            k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
            k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
            k2c0.side = p1->facing < 0;
            k2c0.scale = 2;
            k2c0.layer = 1;
            k2c0.screen = 0;
            k2c0.sound = b1d0.hitSound;
            m_game->CreateEffect((EffectDesc*)&k2c0);
            if (p2->m_hp <= 0 && p2->m_koDelay == 0) {
                p2->pattern = b1d0.airHitPattern;
                p2->StartPattern();
                p2->FaceOpponent();
            }
            p1->ScoreHit(&b1d0);
        }
    }
}

void CScene3::ResolveObjectAttack(CPlayer* p1, CPlayer* p2, int p3, CollisionInfo* p4)
{
    RECT v11c;
    RECT l10c;
    int mfc;
    int vf8[4][5];
#if defined(EFZ_NATIVE) || defined(EFZ_TRACE)
    // Only [i][0] is set for a throw; the rest, read when placing the hit spark, is
    // whatever the stack held (the effect's position varies). Zeroed in the native and
    // test builds.
    memset(vf8, 0, sizeof(vf8));
#endif
    RECT na8[5];
    RECT a58[4];
    PlayerObject* k14;
    int v10;
    int bc;
    PatternFrame* x8;
    CollisionInfo* l4;

    k14 = &p1->m_objects[p3];
    x8 = &p1->m_patterns[k14->pattern].frames[k14->frame];
    l4 = p4;
    if (k14->attackResult == 0 && (l4->frame.flagsB0 & kStateInvulnerable) == 0 && k14->hitsLeft > 0 && (p2->m_throwProtect <= 0 || (x8->flagsAA & kAttackThrow) <= 0) && p2->CanAirRecover() == 0 && p2->m_invulTime == 0) {
        mfc = 0;
        v10 = 0;
        for (; v10 < 4; v10++) {
            a58[v10] = this->BoxOnStage((ObjBase*)k14, &x8->attackBoxes[v10]);
        }
        v10 = 0;
        for (; v10 < 5; v10++) {
            na8[v10] = this->InfoBoxOnStage(p4, (RECT*)((v10 << 4) + (char*)l4));
        }
        v11c = this->InfoBoxOnStage(p4, &l4->frame.pushBox);
        if ((x8->flagsAA & kAttackThrow) > 0) {
            v10 = 0;
            for (; v10 < 4; v10++) {
                vf8[v10][0] = 1;
                mfc = BoxesOverlap(&a58[v10], &v11c) | mfc;
            }
        } else {
            v10 = 0;
            for (; v10 < 4; v10++) {
                bc = 0;
                for (; bc < 5; bc++) {
                    vf8[v10][bc] = BoxesOverlap(&a58[v10], &na8[bc]);
                    mfc |= vf8[v10][bc];
                }
            }
        }
        if (mfc != 0) {
            EffectDesc k168;
            l10c = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            v10 = 0;
            for (; v10 < 4; v10++) {
                bc = 0;
                for (; bc < 5; bc++) {
                    if (vf8[v10][bc] != 0) {
                        if (l10c.left < a58[v10].left) {
                            l10c.left = a58[v10].left;
                        }
                        if (l10c.top < a58[v10].top) {
                            l10c.top = a58[v10].top;
                        }
                        if (l10c.right > a58[v10].right) {
                            l10c.right = a58[v10].right;
                        }
                        if (l10c.bottom > a58[v10].bottom) {
                            l10c.bottom = a58[v10].bottom;
                        }
                        if (l10c.left < na8[bc].left) {
                            l10c.left = na8[bc].left;
                        }
                        if (l10c.top < na8[bc].top) {
                            l10c.top = na8[bc].top;
                        }
                        if (l10c.right > na8[bc].right) {
                            l10c.right = na8[bc].right;
                        }
                        if (l10c.bottom > na8[bc].bottom) {
                            l10c.bottom = na8[bc].bottom;
                        }
                    }
                }
            }
            if ((l4->frame.flagsB0 & kStateReflect) > 0 && (x8->flagsAA & kAttackIgnoresArmor) == 0) {
                k14->hitsLeft--;
                k14->attackResult = 2;
                p1->m_attackResult = 6;
                p2->m_attackResult = 6;
                return;
            }
            if (p2->m_canRecoilCounter != 0 && p2->m_recoilGuardWindow >= 0x1e && p2->m_noGuardTime == 0 && p2->HoldsGuard((PatternFrame*)x8) != 0 && (x8->flagsAA & kAttackUnblockable) == 0) {
                k14->attackResult = 2;
                p1->m_gauge += x8->gaugeOnGuard;
                k14->hitsLeft--;
                p2->m_hitByBody = 1;
                k168.keep = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = kEffectRecoilGuard;
                k168.sound = 0xa;
                m_game->CreateEffect((EffectDesc*)&k168);
                p2->StartPattern();
                p2->facing = -k14->facing;
                if (p2->y == 0.0) {
                    p2->pattern = (p2->m_inputY == 1) + 0xa8;
                } else {
                    p2->pattern = kRecoilGuardAir;
                }
                p1->ClearInput();
                p2->ClearInput();
                p2->m_freezeTime = 0x3c;
                p2->m_canRecoilCounter = 0;
                p1->m_canRecoilCounter = 1;
                return;
            }
            if (p2->m_recoilGuardWindow >= 0x1e && p2->y < 0.0 && p2->CanGuard((PatternFrame*)x8, (PatternFrame*)l4) != 0) {
                k14->attackResult = 2;
                p1->m_gauge += x8->gaugeOnGuard;
                k14->hitsLeft--;
                p2->m_hitByBody = 1;
                k168.keep = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = kEffectRecoilGuard;
                k168.sound = 0xa;
                m_game->CreateEffect((EffectDesc*)&k168);
                p2->StartPattern();
                p2->facing = -k14->facing;
                p2->pattern = kRecoilGuardAir;
                p1->ClearInput();
                p2->ClearInput();
                p2->m_freezeTime = 0x3c;
                p1->m_canRecoilCounter = 1;
                return;
            }
            if (p2->CanGuard((PatternFrame*)x8, (PatternFrame*)l4) != 0 && p2->m_recoilGuardWindow >= 0x1e && p2->y == 0.0 && p2->pattern != kRecoilGuardStand && p2->pattern != kRecoilGuardCrouch) {
                k14->attackResult = 2;
                p1->m_gauge += x8->gaugeOnGuard;
                k14->hitsLeft--;
                p2->m_hitByBody = 1;
                k168.keep = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = kEffectRecoilGuard;
                k168.sound = 0xa;
                m_game->CreateEffect((EffectDesc*)&k168);
                p2->StartPattern();
                p2->facing = -k14->facing;
                p2->pattern = (p2->m_inputY == 1) + 0xa8;
                p1->ClearInput();
                p2->ClearInput();
                p2->m_freezeTime = 0x3c;
                p1->m_canRecoilCounter = 1;
                return;
            }
            if ((l4->frame.flagsB0 & kStateGuardPoint) > 0 && (l4->frame.flagsAA & kAttackGuardStand) > 0 && (x8->flagsAA & kAttackGuardStand) > 0) {
                k14->hitsLeft--;
                k168.keep = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = kEffectGuardSpark;
                k168.sound = 3;
                m_game->CreateEffect((EffectDesc*)&k168);
                p1->m_attackResult = 2;
                p1->m_hitstop = x8->attackerHitstop;
                p2->m_hitstop = x8->defenderHitstop;
                p2->m_hp -= x8->chipDamage;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->m_guardGauge = x8->damage / 0x1e + p2->m_guardGauge;
                if (p2->m_guardGauge > 3.6e+02f) {
                    *(int*)&p2->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if ((l4->frame.flagsB0 & kStateGuardPoint) > 0 && (l4->frame.flagsAA & kAttackGuardCrouch) > 0 && (x8->flagsAA & kAttackGuardCrouch) > 0) {
                k14->hitsLeft--;
                k168.keep = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = kEffectGuardSpark;
                k168.sound = 3;
                m_game->CreateEffect((EffectDesc*)&k168);
                p1->m_attackResult = 2;
                p1->m_hitstop = x8->attackerHitstop;
                p2->m_hitstop = x8->defenderHitstop;
                p2->m_hp -= x8->chipDamage;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->m_guardGauge = x8->damage / 0x1e + p2->m_guardGauge;
                if (p2->m_guardGauge > 3.6e+02f) {
                    *(int*)&p2->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if ((l4->frame.flagsB0 & kStateGuardPoint) > 0 && (l4->frame.flagsAA & kAttackGuardAir) > 0 && (x8->flagsAA & kAttackGuardAir) > 0 && p2->y < 0.0) {
                k14->hitsLeft--;
                k168.keep = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = kEffectGuardSpark;
                k168.sound = 3;
                m_game->CreateEffect((EffectDesc*)&k168);
                p1->m_attackResult = 2;
                p1->m_hitstop = x8->attackerHitstop;
                p2->m_hitstop = x8->defenderHitstop;
                p2->m_hp -= x8->chipDamage;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->m_guardGauge = x8->damage / 0x1e + p2->m_guardGauge;
                if (p2->m_guardGauge > 3.6e+02f) {
                    *(int*)&p2->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if (p2->CanGuard((PatternFrame*)x8, (PatternFrame*)l4) != 0) {
                p2->pattern = (x8->flagsAA & kAttackMedium) / 0x10 + 0x96 + (x8->flagsAA & kAttackHeavy) / 0x20 * 2 + (p2->m_inputY == 1 || (x8->flagsAA & l4->frame.flagsB0 & 5) == 0 && p2->m_cpu != 0) * 3;
                if (p2->y < 0.0) {
                    p2->pattern = kGuardAir;
                }
                p2->StartPattern();
                p2->facing = -k14->facing;
                k14->attackResult = 2;
                k14->hitstop = x8->attackerHitstop;
                p2->m_hitstop = x8->defenderHitstop;
                p1->m_gauge += x8->gaugeOnGuard;
                k14->hitsLeft--;
                p2->m_hitByBody = 0;
                k168.keep = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p1->facing < 0;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                p2->m_hp -= x8->chipDamage;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                if (p1->m_guardGauge > 0.0f) {
                    p1->m_guardGauge = p1->m_guardGauge - x8->damage / 0x1e;
                    if (p1->m_guardGauge < 0.0f) {
                        p2->m_guardGauge = p2->m_guardGauge - p1->m_guardGauge;
                        *(int*)&p1->m_guardGauge = 0;
                    }
                } else {
                    p2->m_guardGauge = x8->damage / 0x1e + p2->m_guardGauge;
                    if (p2->m_guardGauge > 3.6e+02f) {
                        *(int*)&p2->m_guardGauge = 0x43b40000;
                    }
                }
                p2->m_guardedObject = 1;
                k168.type = kEffectGuardSpark;
                k168.sound = 3;
                m_game->CreateEffect((EffectDesc*)&k168);
                return;
            }
            if ((l4->frame.flagsB0 & kStateArmor) == 0 && p2->m_armorTime == 0 || ((l4->frame.flagsB0 & kStateArmor) > 0 || p2->m_armorTime > 0) && (x8->flagsAA & kAttackIgnoresArmor) > 0 || (x8->flagsAA & kAttackThrow) > 0) {
                if (p2->y >= 0.0) {
                    if (x8->groundHitPattern > 0) {
                        p2->pattern = x8->groundHitPattern;
                    } else if ((l4->frame.flagsB0 & (kStateStanding | kStateCrouching)) == 3) {
                        p2->pattern = kHitAir;
                    } else if ((l4->frame.flagsB0 & kStateStanding) != 0) {
                        p2->pattern = ((x8->flagsAA & kAttackBodyHit) > 0) * 3 + 0x32 + ((x8->flagsAA & kAttackMedium) > 0) + ((x8->flagsAA & kAttackHeavy) > 0) * 2;
                    } else if ((l4->frame.flagsB0 & kStateCrouching) != 0) {
                        p2->pattern = ((x8->flagsAA & kAttackMedium) > 0) + 0x38 + ((x8->flagsAA & kAttackHeavy) > 0) * 2;
                    }
                } else if (x8->airHitPattern > 0) {
                    p2->pattern = x8->airHitPattern;
                } else {
                    p2->pattern = kHitAir;
                }
                k14->attackResult = 3;
                p2->StartPattern();
                p2->facing = -k14->facing;
            } else {
                p1->m_comboHits = 0;
                p2->Tint(0xe9, 3);
                k14->attackResult = 7;
            }
            if ((l4->frame.flagsB0 & kStateCanGuard) > 0) {
                p1->m_comboHits = 0;
                if (p1->m_proration > 10000.0) {
                    p1->m_proration -= 20.0;
                } else {
                    p1->m_proration = 10000.0;
                }
            }
            p2->m_hitVx = x8->hitVx;
            p2->m_hitVy = x8->hitVy;
            p2->m_hitByBody = 0;
            if (p1->m_comboHits == 0) {
                p2->m_comboStartHp = p2->m_hp;
            }
            p2->m_hp -= (int)((double)x8->damage * p1->AttackFactor() * p2->DefenseFactor() * p1->ProrationFactor());
            p2->m_untechTime = (int)(x8->untechTime * (p1->m_proration / 10000.0) * (((x8->flagsAA & kAttackCounterHit) > 0 && (l4->frame.flagsB0 & kStateCounterHittable) > 0) + 1));
            p2->m_noAirRecovery = (x8->flagsAA & kAttackNoAirRecovery) > 0;
            p2->m_landHittable = (x8->flagsAA & kAttackLandHittable) > 0;
            p2->m_dashMomentum = 0;
            p2->m_airDashes = 0;
            p2->m_airActions = 0;
            p1->m_shownProration = p1->m_proration / 100.0;
            p1->m_proration = x8->proration / 1e+03f * p1->m_proration;
            if (p1->m_proration > 10000.0) {
                p1->m_proration = x8->proration / 1e+03f * p1->m_proration;
            }
            p1->m_comboHits++;
            p1->m_shownHits = p1->m_comboHits;
            p1->m_comboTimer = 0xb4;
            p1->m_comboDamage = p2->m_comboStartHp - p2->m_hp;
            p1->m_gauge += x8->gaugeOnHit;
            k14->hitstop = x8->attackerHitstop;
            p2->m_hitstop = x8->defenderHitstop;
            k14->hitsLeft--;
            k168.keep = 0;
            k168.type = x8->hitEffect;
            k168.x = (double)((l10c.right + l10c.left) / 2);
            k168.y = (double)((l10c.bottom + l10c.top) / 2);
            k168.side = p1->facing < 0;
            k168.scale = 2;
            k168.layer = 1;
            k168.screen = 0;
            k168.sound = x8->hitSound;
            m_game->CreateEffect((EffectDesc*)&k168);
            if (p2->m_hp <= 0 && p2->m_koDelay == 0) {
                p2->pattern = x8->airHitPattern;
                p2->StartPattern();
                p2->FaceOpponent();
            }
            p1->ScoreHit((PatternFrame*)x8);
        }
    }
}

void CScene3::ResolveObjectHitsObject(CPlayer* p1, CPlayer* p2, int p3, int p4)
{
    RECT x10c;
    int xfc;
    int xf8[4][5];
    RECT ea8[5];
    RECT n58[4];
    PlayerObject* l18;
    int v14;
    PlayerObject* n10;
    int rc;
    PatternFrame* x8;
    PatternFrame* l4;

    n10 = &p1->m_objects[p3];
    l18 = &p2->m_objects[p4];
    x8 = &p1->m_patterns[n10->pattern].frames[n10->frame];
    l4 = &p2->m_patterns[l18->pattern].frames[l18->frame];
    if (n10->attackResult == 0 && n10->hitsLeft > 0 && (x8->flagsAA & kAttackThrow) == 0) {
        xfc = 0;
        v14 = 0;
        for (; v14 < 4; v14++) {
            n58[v14] = this->BoxOnStage((ObjBase*)n10, &x8->attackBoxes[v14]);
        }
        v14 = 0;
        for (; v14 < 5; v14++) {
            ea8[v14] = this->BoxOnStage((ObjBase*)l18, (RECT*)((v14 << 4) + (char*)l4));
        }
        v14 = 0;
        for (; v14 < 4; v14++) {
            rc = 0;
            for (; rc < 5; rc++) {
                xf8[v14][rc] = BoxesOverlap(&n58[v14], &ea8[rc]);
                xfc |= xf8[v14][rc];
            }
        }
        if (xfc != 0) {
            x10c = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            v14 = 0;
            for (; v14 < 4; v14++) {
                rc = 0;
                for (; rc < 5; rc++) {
                    if (xf8[v14][rc] != 0) {
                        if (x10c.left < n58[v14].left) {
                            x10c.left = n58[v14].left;
                        }
                        if (x10c.top < n58[v14].top) {
                            x10c.top = n58[v14].top;
                        }
                        if (x10c.right > n58[v14].right) {
                            x10c.right = n58[v14].right;
                        }
                        if (x10c.bottom > n58[v14].bottom) {
                            x10c.bottom = n58[v14].bottom;
                        }
                        if (x10c.left < ea8[rc].left) {
                            x10c.left = ea8[rc].left;
                        }
                        if (x10c.top < ea8[rc].top) {
                            x10c.top = ea8[rc].top;
                        }
                        if (x10c.right > ea8[rc].right) {
                            x10c.right = ea8[rc].right;
                        }
                        if (x10c.bottom > ea8[rc].bottom) {
                            x10c.bottom = ea8[rc].bottom;
                        }
                    }
                }
            }
            if ((l4->flagsB0 & kStateCanGuard) == 0) {
                n10->hitsLeft--;
                n10->attackResult = 5;
            }
            l18->attackResult = 5;
            if ((l4->flagsB0 & kStateCounterHittable) > 0) {
                *l4 = p2->m_patterns[p2->pattern].frames[p2->frame];
                if ((l4->flagsB0 & kStateArmor) == 0 && p2->m_armorTime == 0 || ((l4->flagsB0 & kStateArmor) > 0 || p2->m_armorTime > 0) && (x8->flagsAA & kAttackIgnoresArmor) > 0 || (x8->flagsAA & kAttackThrow) > 0) {
                    if (p2->y >= 0.0) {
                        if (x8->groundHitPattern > 0) {
                            p2->pattern = x8->groundHitPattern;
                        } else if ((l4->flagsB0 & (kStateStanding | kStateCrouching)) == 3) {
                            p2->pattern = kHitAir;
                        } else if ((l4->flagsB0 & kStateStanding) != 0) {
                            p2->pattern = ((x8->flagsAA & kAttackBodyHit) > 0) * 3 + 0x32 + ((x8->flagsAA & kAttackMedium) > 0) + ((x8->flagsAA & kAttackHeavy) > 0) * 2;
                        } else if ((l4->flagsB0 & kStateCrouching) != 0) {
                            p2->pattern = ((x8->flagsAA & kAttackMedium) > 0) + 0x38 + ((x8->flagsAA & kAttackHeavy) > 0) * 2;
                        }
                    } else if (x8->airHitPattern > 0) {
                        p2->pattern = x8->airHitPattern;
                    } else {
                        p2->pattern = kHitAir;
                    }
                    p2->StartPattern();
                    p2->FaceOpponent();
                } else {
                    p1->m_comboHits = 0;
                    p2->Tint(0xdf, 2);
                }
                if ((l4->flagsB0 & kStateCanGuard) > 0) {
                    p1->m_comboHits = 0;
                    if (p1->m_proration > 10000.0) {
                        p1->m_proration -= 20.0;
                    } else {
                        p1->m_proration = 10000.0;
                    }
                }
                p2->m_hitVx = x8->hitVx;
                p2->m_hitVy = x8->hitVy;
                p2->m_hitByBody = 1;
                if (p1->m_comboHits == 0) {
                    p2->m_comboStartHp = p2->m_hp;
                }
                p2->m_hp -= (int)((double)x8->damage * p1->AttackFactor() * p2->DefenseFactor() * p1->ProrationFactor());
                p2->m_untechTime = (int)(x8->untechTime * (p1->m_proration / 10000.0 * 0.8));
                p2->m_noAirRecovery = (x8->flagsAA & kAttackNoAirRecovery) > 0;
                p2->m_landHittable = (x8->flagsAA & kAttackLandHittable) > 0;
                p2->m_dashMomentum = 0;
                p2->m_airDashes = 0;
                p2->m_airActions = 0;
                p1->m_shownProration = p1->m_proration / 100.0;
                p1->m_proration = x8->proration / 1e+03f * p1->m_proration;
                if (p1->m_proration > 10000.0) {
                    p1->m_proration = x8->proration / 1e+03f * p1->m_proration;
                }
                p1->m_comboHits++;
                p1->m_shownHits = p1->m_comboHits;
                p1->m_comboTimer = 0xb4;
                p1->m_comboDamage = p2->m_comboStartHp - p2->m_hp;
                p1->m_gauge += x8->gaugeOnHit;
                p1->m_hitstop = x8->attackerHitstop;
                p2->m_hitstop = x8->defenderHitstop;
                if (p2->m_hp <= 0 && p2->m_koDelay == 0) {
                    p2->pattern = x8->airHitPattern;
                    p2->StartPattern();
                    p2->FaceOpponent();
                }
                p1->ScoreHit((PatternFrame*)x8);
            }
            EffectDesc v158;
            v158.keep = 0;
            v158.type = x8->hitEffect;
            v158.x = (double)((x10c.right + x10c.left) / 2);
            v158.y = (double)((x10c.bottom + x10c.top) / 2);
            v158.side = p1->facing < 0;
            v158.scale = 2;
            v158.layer = 1;
            v158.screen = 0;
            v158.sound = x8->hitSound;
            m_game->CreateEffect((EffectDesc*)&v158);
        }
    }
}

void CScene3::ClashObjects(CPlayer* p1, CPlayer* p2, int p3, int p4)
{
    RECT v30;
    RECT v20;
    PlayerObject* l10;
    PlayerObject* vc;
    int x8;
    int l4;

    vc = &p1->m_objects[p3];
    l10 = &p2->m_objects[p4];
    x8 = (int)p1->m_patterns[vc->pattern].frames + vc->frame * 0xc8;
    l4 = (int)p2->m_patterns[l10->pattern].frames + l10->frame * 0xc8;
    if (vc->attackResult == 0 && l10->attackResult == 0 && vc->hitsLeft > 0 && l10->hitsLeft > 0 && p1->m_patterns[vc->pattern].level > 0 && p2->m_patterns[l10->pattern].level > 0) {
        v20 = this->BoxOnStage((ObjBase*)vc, TOPTR(RECT*, x8 + 0x90));
        v30 = this->BoxOnStage((ObjBase*)l10, TOPTR(RECT*, l4 + 0x90));
        if (BoxesOverlap(&v20, &v30) != 0) {
            if (p2->m_patterns[l10->pattern].level == p1->m_patterns[vc->pattern].level) {
                vc->attackResult = 4;
                l10->attackResult = 4;
            } else if (p2->m_patterns[l10->pattern].level > p1->m_patterns[vc->pattern].level) {
                vc->attackResult = 4;
            } else if (p2->m_patterns[l10->pattern].level < p1->m_patterns[vc->pattern].level) {
                l10->attackResult = 4;
            }
            if (p2->m_patterns[l10->pattern].level > 1) {
                vc->hitsLeft--;
            }
            if (p1->m_patterns[vc->pattern].level > 1) {
                l10->hitsLeft--;
            }
        }
    }
}

void CScene3::ResolvePlayerHitsObject(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4, int p5)
{
    RECT b1cc;
    int r1bc;
    int k1b8[4][5];
    RECT v168[5];
    PatternFrame n118;
    RECT n50[4];
    PlayerObject* l10;
    int vc;
    int x8;
    CollisionInfo* l4;

    l10 = &p2->m_objects[p5];
    l4 = p3;
    if (p1->m_attackResult == 0 && p1->m_hitsLeft > 0 && (l4->frame.flagsAA & kAttackThrow) == 0) {
        n118 = p2->m_patterns[l10->pattern].frames[l10->frame];
        r1bc = 0;
        vc = 0;
        for (; vc < 4; vc++) {
            n50[vc] = this->InfoBoxOnStage(p3, &l4->frame.attackBoxes[vc]);
        }
        vc = 0;
        for (; vc < 5; vc++) {
            v168[vc] = this->BoxOnStage((ObjBase*)l10, &n118.boxes[vc]);
        }
        vc = 0;
        for (; vc < 4; vc++) {
            x8 = 0;
            for (; x8 < 5; x8++) {
                k1b8[vc][x8] = BoxesOverlap(&n50[vc], &v168[x8]);
                r1bc |= k1b8[vc][x8];
            }
        }
        if (r1bc != 0) {
            b1cc = MakeRect(-0x2710, -0x2710, 0x4e20, 0x4e20);
            vc = 0;
            for (; vc < 4; vc++) {
                x8 = 0;
                for (; x8 < 5; x8++) {
                    if (k1b8[vc][x8] != 0) {
                        if (b1cc.left < n50[vc].left) {
                            b1cc.left = n50[vc].left;
                        }
                        if (b1cc.top < n50[vc].top) {
                            b1cc.top = n50[vc].top;
                        }
                        if (b1cc.right > n50[vc].right) {
                            b1cc.right = n50[vc].right;
                        }
                        if (b1cc.bottom > n50[vc].bottom) {
                            b1cc.bottom = n50[vc].bottom;
                        }
                        if (b1cc.left < v168[x8].left) {
                            b1cc.left = v168[x8].left;
                        }
                        if (b1cc.top < v168[x8].top) {
                            b1cc.top = v168[x8].top;
                        }
                        if (b1cc.right > v168[x8].right) {
                            b1cc.right = v168[x8].right;
                        }
                        if (b1cc.bottom > v168[x8].bottom) {
                            b1cc.bottom = v168[x8].bottom;
                        }
                    }
                }
            }
            if ((n118.flagsB0 & kStateCanGuard) == 0) {
                p1->m_hitsLeft--;
                p1->m_attackResult = 5;
            }
            l10->attackResult = 5;
            if ((n118.flagsB0 & kStateCounterHittable) > 0) {
                n118 = p4->frame;
                if ((n118.flagsB0 & kStateArmor) == 0 && p2->m_armorTime == 0 || ((n118.flagsB0 & kStateArmor) > 0 || p2->m_armorTime > 0) && (l4->frame.flagsAA & kAttackIgnoresArmor) > 0 || (l4->frame.flagsAA & kAttackThrow) > 0) {
                    if (p2->y >= 0.0) {
                        if (l4->frame.groundHitPattern > 0) {
                            p2->pattern = l4->frame.groundHitPattern;
                        } else if ((n118.flagsB0 & (kStateStanding | kStateCrouching)) == 3) {
                            p2->pattern = kHitAir;
                        } else if ((n118.flagsB0 & kStateStanding) != 0) {
                            p2->pattern = ((l4->frame.flagsAA & kAttackBodyHit) > 0) * 3 + 0x32 + ((l4->frame.flagsAA & kAttackMedium) > 0) + ((l4->frame.flagsAA & kAttackHeavy) > 0) * 2;
                        } else if ((n118.flagsB0 & kStateCrouching) != 0) {
                            p2->pattern = ((l4->frame.flagsAA & kAttackMedium) > 0) + 0x38 + ((l4->frame.flagsAA & kAttackHeavy) > 0) * 2;
                        }
                    } else if (l4->frame.airHitPattern > 0) {
                        p2->pattern = l4->frame.airHitPattern;
                    } else {
                        p2->pattern = kHitAir;
                    }
                    p2->StartPattern();
                    p2->FaceOpponent();
                } else {
                    p1->m_comboHits = 0;
                    p2->Tint(0xdf, 2);
                }
                if ((n118.flagsB0 & kStateCanGuard) > 0) {
                    p1->m_comboHits = 0;
                    if (p1->m_proration > 10000.0) {
                        p1->m_proration -= 20.0;
                    } else {
                        p1->m_proration = 10000.0;
                    }
                }
                p2->m_hitVx = l4->frame.hitVx;
                p2->m_hitVy = l4->frame.hitVy;
                p2->m_hitByBody = 1;
                if (p1->m_comboHits == 0) {
                    p2->m_comboStartHp = p2->m_hp;
                }
                p2->m_hp -= (int)((double)l4->frame.damage * p1->AttackFactor() * p2->DefenseFactor() * p1->ProrationFactor());
                p2->m_untechTime = (int)(l4->frame.untechTime * (p1->m_proration / 10000.0 * 0.8));
                p2->m_noAirRecovery = (l4->frame.flagsAA & kAttackNoAirRecovery) > 0;
                p2->m_landHittable = (l4->frame.flagsAA & kAttackLandHittable) > 0;
                p2->m_dashMomentum = 0;
                p2->m_airDashes = 0;
                p2->m_airActions = 0;
                p1->m_shownProration = p1->m_proration / 100.0;
                p1->m_proration = l4->frame.proration / 1e+03f * p1->m_proration;
                if (p1->m_proration > 10000.0) {
                    p1->m_proration = l4->frame.proration / 1e+03f * p1->m_proration;
                }
                p1->m_comboHits++;
                p1->m_shownHits = p1->m_comboHits;
                p1->m_comboTimer = 0xb4;
                p1->m_comboDamage = p2->m_comboStartHp - p2->m_hp;
                p1->m_gauge += l4->frame.gaugeOnHit;
                p1->m_hitstop = l4->frame.attackerHitstop;
                p2->m_hitstop = l4->frame.defenderHitstop;
                if (p2->m_hp <= 0 && p2->m_koDelay == 0) {
                    p2->pattern = l4->frame.airHitPattern;
                    p2->StartPattern();
                    p2->FaceOpponent();
                }
                p1->ScoreHit((PatternFrame*)l4);
            }
            EffectDesc n218;
            n218.keep = 0;
            n218.type = l4->frame.hitEffect;
            n218.x = (double)((b1cc.right + b1cc.left) / 2);
            n218.y = (double)((b1cc.bottom + b1cc.top) / 2);
            n218.side = p1->facing < 0;
            n218.scale = 2;
            n218.layer = 1;
            n218.screen = 0;
            n218.sound = l4->frame.hitSound;
            m_game->CreateEffect((EffectDesc*)&n218);
        }
    }
}
