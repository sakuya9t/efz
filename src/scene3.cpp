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

CScene3::CScene3(HWND hwnd, PTR32(CPlayer)* player1Ref, PTR32(CPlayer)* player2Ref, CGame* game, CGraphics* graphics, CInput* input, CSound* sound)
    : CScene(hwnd, player1Ref, player2Ref, game, graphics, input, sound)
{
    m_focusXDefault = 0;
    m_focusYHigh = -50;
    m_focusX = m_focusXDefault;
    m_focusY = m_focusYHigh;
    m_focusYStep = 5;
    m_scrollX = -160;
    m_scrollY = 0;
    m_enter = 1;
    m_leave = 0;
    m_refillMeter = 0;
    m_refillHp = 9999;
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
    m_digitFonts[0] = MakeRect(0, 234, 8, 10);
    m_digitFonts[1] = MakeRect(0, 210, 16, 15);
    m_digitFonts[2] = MakeRect(0, 225, 7, 9);
    m_digitFonts[3] = MakeRect(0, 282, 14, 22);
    m_digitFonts[4] = MakeRect(0, 352, 8, 12);
    m_digitFonts[5] = MakeRect(0, 340, 8, 12);
    m_digitFonts[6] = MakeRect(0, 328, 8, 12);
    m_digitFonts[7] = MakeRect(0, 316, 8, 12);
    m_digitFonts[8] = MakeRect(0, 304, 8, 12);
    m_digitFonts[9] = MakeRect(0, 364, 7, 10);
    m_digitFonts[10] = MakeRect(0, 374, 7, 10);
    m_digitFonts[11] = MakeRect(0, 384, 7, 10);
    m_digitFonts[12] = MakeRect(0, 394, 7, 10);
    m_digitFonts[13] = MakeRect(0, 404, 7, 10);
    m_digitFonts[14] = MakeRect(0, 414, 7, 10);
    m_digitFonts[15] = MakeRect(0, 424, 7, 10);
    m_digitFonts[16] = MakeRect(0, 434, 7, 10);
}

CScene3::~CScene3()
{
}

BYTE CScene3::Update()
{
    int tick;

    if ((DWORD)(timeGetTime() - m_secondStart) >= 1000) {
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
        m_focusYHigh = -50;
        m_focusX = m_focusXDefault;
        m_focusY = m_focusYHigh;
        m_focusYStep = 5;
        m_scrollX = -160;
        m_scrollY = 0;
        m_speed = 3;
        m_refillMeter = 0;
        m_refillHp = 9999;
        UpdateCamera();
        Draw();
        CScene::FadeIn(m_game->m_palette, 0);
        m_enter = 0;
    } else if (m_leave == 1) {
        CScene::FadeOut(m_game->m_palette, 1, 0, 100);
        delete *m_player1Ref;
        *m_player1Ref = (CPlayer*)0;
        delete *m_player2Ref;
        *m_player2Ref = (CPlayer*)0;
        if ((int)m_game->m_background != 0) {
            delete (char*)m_game->m_background;
            m_game->m_background = (CAnimBg*)0;
        }
#ifdef EFZ_NATIVE
        // A network match: its replay is closed and the mode is VS HUMAN again, so that
        // the game goes on to character select (EfzRevival's hook at efz.exe 0x763e50).
        if (efz::g_netplay.active)
            efz::g_netplay.matchLeft();
#endif
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
#ifdef EFZ_NATIVE
            // The match is over; as above (efz.exe 0x763f04): on to the results.
            if (efz::g_netplay.active)
                efz::g_netplay.matchLeft();
#endif
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
    tick = 0;
    for (; tick < m_speed; tick++) {
#ifdef EFZ_TRACE
        TraceTickStart(this);
#endif
        m_players[0]->ReadInput();
        m_players[1]->ReadInput();
#ifdef EFZ_TRACE
        TraceInputsRead(this);
#endif
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
        DrawNumber(80, 100, m_players[0]->m_hp, 2, 0, 0);
        DrawNumber(80, 110, m_players[0]->pattern, 2, 0, 0);
        DrawNumber(80, 120, m_players[0]->frame, 2, 0, 0);
        DrawNumber(80, 130, m_players[0]->timer, 2, 0, 0);
        DrawNumber(280, 100, m_players[1]->m_hp, 2, 0, 0);
        DrawNumber(280, 110, m_players[1]->pattern, 2, 0, 0);
        DrawNumber(280, 120, m_players[1]->frame, 2, 0, 0);
        DrawNumber(280, 130, m_players[1]->timer, 2, 0, 0);
    }
    DrawBordersAndFlip();
}

void CScene3::UpdateCamera()
{
    int targetY; // the m_scrollY the camera eases toward
    int targetX; // the m_scrollX the camera eases toward

    m_focusX = m_focusXDefault;
    if (m_game->m_cameraFocusXTime > 0) {
        m_focusX = m_game->m_cameraFocusX;
        if (m_players[0]->m_hitstop == 0 && m_players[1]->m_hitstop == 0 && m_players[0]->m_freezeTime == 0 && m_players[1]->m_freezeTime == 0) {
            m_game->m_cameraFocusXTime--;
        }
    }
    targetX = 160 - (int)((m_players[0]->x * (m_focusX + 50) + m_players[1]->x * (50 - m_focusX)) / 100.0);
    if (targetX < -319) {
        targetX = -319;
    } else if (targetX > 0) {
        targetX = 0;
    }
    if (m_scrollX < targetX) {
        m_scrollX -= (m_scrollX - targetX) / 15 - 1;
        if (m_scrollX > targetX) {
            m_scrollX = targetX;
        }
    } else {
        m_scrollX -= (m_scrollX - targetX) / 15 + 1;
        if (m_scrollX < targetX) {
            m_scrollX = targetX;
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
        m_focusY = 20;
    }
    if (m_game->m_cameraFocusYTime > 0) {
        m_focusY = m_game->m_cameraFocusY * (1 - ((m_players[0]->y < m_players[1]->y) << 1));
        if (m_players[0]->m_hitstop == 0 && m_players[1]->m_hitstop == 0 && m_players[0]->m_freezeTime == 0 && m_players[1]->m_freezeTime == 0) {
            m_game->m_cameraFocusYTime--;
        }
    }
    if ((targetY = -(((int)m_players[0]->y - (m_players[0]->y < 0.0) + (int)m_players[1]->y - (m_players[1]->y < 0.0)) / 2) + ((int)m_players[0]->y - (m_players[0]->y < 0.0) - (int)m_players[1]->y + (m_players[1]->y < 0.0)) * m_focusY / 100 * ((m_players[0]->y - m_players[1]->y < 0.0) * 2 + -1)) < 0) {
        targetY = 0;
    } else if (targetY > 240) {
        targetY = 240;
    }
    if (m_scrollY < targetY) {
        m_scrollY -= (m_scrollY - targetY) / 10 - 1;
        if (m_scrollY > targetY) {
            m_scrollY = targetY;
        }
    } else {
        m_scrollY -= (m_scrollY - targetY) / 10 + 1;
        if (m_scrollY < targetY) {
            m_scrollY = targetY;
        }
    }
    m_game->UpdateShake();
    m_game->m_view = MakeRect(-m_scrollX, -m_scrollY - 210, 320, 240);
    m_drawX = m_scrollX + m_game->m_shakeX;
    m_drawY = m_scrollY + m_game->m_shakeY;
}

void CScene3::PlayPlayerSounds()
{
    int side;
    int i;

    if (m_leave == 2) {
        i = 0;
        for (; i < 2; i++) {
            m_players[i]->m_playSound = -1;
            m_players[i]->m_playVoice = -1;
        }
        return;
    }
    side = 0;
    for (; side < 2; side++) {
        if (m_players[side]->m_playSound >= 0 && m_players[side]->m_playSound < 65) {
            m_sound->Play((short)m_game->m_sounds[m_players[side]->m_playSound], 0);
            m_players[side]->m_playSound = -1;
        }
        if (m_players[side]->m_playVoice >= 0 && m_players[side]->m_playVoice < 50) {
            m_sound->Play(m_players[side]->m_voices[m_players[side]->m_playVoice], 0);
            m_players[side]->m_playVoice = -1;
        }
    }
}

void CScene3::PlayEffectSounds()
{
    int i;
    int slot;

    if (m_leave == 2) {
        i = m_game->m_effectTail;
        while (i != m_game->m_effectHead) {
            m_game->m_effects[i].sound = -1;
            i++;
            if (i >= 640) {
                i = 0;
            }
        }
        return;
    }
    slot = m_game->m_effectTail;
    while (slot != m_game->m_effectHead) {
        if ((char)m_game->m_effects[slot].sound >= 0 && (char)m_game->m_effects[slot].sound < 65) {
            m_sound->Play((short)m_game->m_sounds[(char)m_game->m_effects[slot].sound], 0);
            m_game->m_effects[slot].sound = -1;
        }
        slot++;
        if (slot >= 640) {
            slot = 0;
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
        m_players[0]->m_hp = 9999;
        m_players[1]->m_hp = 9999;
        m_game->m_intro = 2;
        return;
    }
    EffectDesc effect;
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
            m_players[0]->m_freezeTime = m_players[0]->m_freezeTime + 180;
            m_players[1]->m_freezeTime = m_players[1]->m_freezeTime + 180;
            m_players[0]->StartPattern();
            effect.keep = 0;
            effect.x = 80.0;
            effect.y = 100.0;
            effect.side = 0;
            effect.scale = 0;
            effect.layer = 2;
            effect.screen = 1;
            effect.type = kEffectDown;
            effect.sound = 29;
            m_game->CreateEffect((EffectDesc*)&effect);
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
            m_players[0]->m_freezeTime = m_players[0]->m_freezeTime + 180;
            m_players[1]->m_freezeTime = m_players[1]->m_freezeTime + 180;
            effect.keep = 0;
            effect.x = 240.0;
            effect.y = 100.0;
            effect.side = 0;
            effect.scale = 0;
            effect.layer = 2;
            effect.screen = 1;
            effect.type = kEffectDown;
            effect.sound = 29;
            m_game->CreateEffect((EffectDesc*)&effect);
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
    int hr;
    char keyState[256];

    hr = m_input->m_keyboard->GetDeviceState(0x100, keyState);
#ifdef EFZ_NATIVE
    // A network match: F4-F8 and Esc as either player pressed them on this frame
    // (EfzRevival's hook at efz.exe 0x7656a7).
    if (efz::g_netplay.active)
        efz::g_netplay.fightKeys(keyState);
#endif
    if (hr < 0 && hr == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if (m_game->m_replayMode == 1 && m_game->m_replay.m_eof != 0) {
        m_game->m_replay.m_eof = 0;
        m_leave = 1;
    }
    if (m_leave == 0 && m_game->m_gameMode == 6) {
        m_game->UpdateInput();
        if (m_game->m_pressA[0] != 0 || m_game->m_pressA[1] != 0 || m_game->m_pressB[0] != 0 || m_game->m_pressB[1] != 0 || (keyState[1] & 0x80) != 0) {
            m_leave = 1;
            m_game->StopMusic();
            m_paused = 0;
        }
    }
    if (m_leave == 0 && (keyState[1] & 0x80) != 0) {
        m_leave = 1;
        m_paused = 0;
    }
    if ((keyState[62] & 0x80) != 0 && m_game->m_intro == 0 && m_game->m_roundOver == 0 && m_game->m_gameMode != 0 && m_game->m_gameMode != 2 && m_game->m_gameMode != 6) {
        m_refillMeter = m_refillMeter + 5;
        if (m_refillMeter > 2000) {
            m_refillMeter = 0;
        }
        m_refillHp = 9999;
        m_players[0]->m_refillMeter = m_refillMeter;
        m_players[1]->m_refillMeter = m_refillMeter;
        m_players[0]->m_refillHp = m_refillHp;
        m_players[1]->m_refillHp = m_refillHp;
    } else if ((keyState[63] & 0x80) != 0 && g_fkeyHeld == 0 && m_game->m_gameMode != 0 && m_game->m_gameMode != 2 && m_game->m_gameMode != 6) {
        if (m_refillMeter == 1000) {
            if (m_refillHp == 3332) {
                m_refillMeter = 2000;
            } else {
                m_refillHp = 3332;
            }
        } else {
            m_refillMeter = 1000;
        }
        m_players[0]->m_refillMeter = m_refillMeter;
        m_players[1]->m_refillMeter = m_refillMeter;
        m_players[0]->m_refillHp = m_refillHp;
        m_players[1]->m_refillHp = m_refillHp;
        g_fkeyHeld = 1;
    }
    if (m_game->m_gameMode == 1) {
        if ((keyState[64] & 0x80) != 0 && g_fkeyHeld == 0) {
            m_game->m_dummyStance++;
            if ((char)m_game->m_dummyStance > 2) {
                m_game->m_dummyStance = 0;
            }
            g_fkeyHeld = 1;
        } else if ((keyState[65] & 0x80) != 0 && g_fkeyHeld == 0) {
            m_game->m_dummyGuard = m_game->m_dummyGuard == 0;
            g_fkeyHeld = 1;
        }
    } else if (m_game->m_gameMode == 5 && m_game->m_replayMode == 2 && (keyState[64] & 0x80) != 0) {
        RestartRecording();
    }
    if ((keyState[66] & 0x80) != 0 && g_fkeyHeld == 0) {
        m_paused = m_paused == 0;
        g_fkeyHeld = 1;
    }
    if (m_refillMeter == 2000) {
        m_refillMeter = 0;
        m_refillHp = 9999;
        m_players[0]->m_refillMeter = m_refillMeter;
        m_players[1]->m_refillMeter = m_refillMeter;
        m_players[0]->m_refillHp = m_refillHp;
        m_players[1]->m_refillHp = m_refillHp;
        m_players[0]->m_hp = 9999;
        m_players[1]->m_hp = 9999;
    }
    if ((keyState[63] & 0x80) != 0 || (keyState[64] & 0x80) != 0 || (keyState[65] & 0x80) != 0 || (keyState[66] & 0x80) != 0) {
        g_fkeyHeld = 1;
    } else {
        g_fkeyHeld = 0;
    }
    if (1) {
    } else {
        if ((keyState[59] & 0x80) != 0) {
            m_speed = 1;
        }
        if ((keyState[60] & 0x80) != 0) {
            m_speed = 2;
        }
        if ((keyState[61] & 0x80) != 0) {
            m_speed = 3;
        }
        if ((keyState[67] & 0x80) != 0) {
            m_capturing = 1;
        }
        if ((keyState[68] & 0x80) != 0) {
            m_capturing = 0;
        }
        if ((keyState[87] & 0x80) != 0) {
            m_captureFrame = 0;
        }
        if ((keyState[88] & 0x80) != 0) {
            m_players[0]->m_hp = 1;
            m_players[1]->m_hp = 1;
        }
    }
    if (m_game->m_replayMode == 1 && m_paused == 0) {
        if (m_game->m_replayVersion > 0) {
            m_refillMeter = m_game->m_replay.Read();
            m_refillHp = m_game->m_replay.Read();
        } else {
            m_refillMeter = 1000;
            m_refillHp = 9999;
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
    EffectDesc effect;
    switch (m_game->m_intro) {
    case 1:
        effect.keep = 0;
        effect.x = 160.0;
        effect.y = 120.0;
        effect.side = 0;
        effect.scale = 2;
        effect.layer = 2;
        effect.screen = 1;
        effect.type = kEffectMotto;
        effect.sound = -1;
        m_game->CreateEffect((EffectDesc*)&effect);
        m_game->m_intro = 99;
        m_game->unk1352 = 300;
        break;
    case 2:
        effect.keep = 0;
        effect.x = 160.0;
        effect.y = 120.0;
        effect.side = 0;
        effect.scale = 2;
        effect.layer = 2;
        effect.screen = 1;
        effect.type = kEffectRoundFlash;
        effect.sound = m_game->m_round + 11;
        m_game->CreateEffect((EffectDesc*)&effect);
        m_game->m_intro = 99;
        m_game->unk1352 = 270;
    }
}

void CScene3::RestartRecording()
{
    char path[40];
    char number[8];

    if (m_game->m_gameMode == 5 && m_game->m_replayMode == 2) {
        CScene::FadeOut(m_game->m_palette, 0, 0, 0);
        m_game->m_replay.Close();
        strcpy(path, "replay\\data");
        _itoa(m_game->m_replayPage + 1, number, 10);
        strcat(path, (const char*)number);
        strcat(path, "-");
        _itoa(m_game->m_replaySlot + 1, number, 10);
        strcat(path, (const char*)number);
        strcat(path, ".rep");
        m_game->m_replay.OpenWrite((const char*)path);
        m_game->m_replay.Write((*m_player1Ref)->m_charId);
        m_game->m_replay.Write((*m_player2Ref)->m_charId);
        m_game->m_replay.Write(104);
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
        m_focusYHigh = -50;
        m_focusX = m_focusXDefault;
        m_focusY = m_focusYHigh;
        m_focusYStep = 5;
        m_scrollX = -160;
        m_scrollY = 0;
        m_speed = 3;
        UpdateCamera();
        Draw();
        CScene::FadeIn(m_game->m_palette, 0);
    }
}

void CScene3::CheckHits()
{
    int otherSlot;
    int recoilGuard1; // P1 will recoil-guard P2's attack: P1's own attack is skipped
    CollisionInfo info1;
    int slot;
    int recoilGuard2; // P2 will recoil-guard P1's attack: P2's own attack is skipped
    CollisionInfo info2;

    info1.frame = m_players[0]->m_patterns[m_players[0]->pattern].frames[m_players[0]->frame];
    info1.anim = m_players[0]->anims[m_players[0]->pattern].frames[m_players[0]->frame];
    info1.x = m_players[0]->x;
    info1.y = m_players[0]->y;
    info1.facing = m_players[0]->facing;
    info2.frame = m_players[1]->m_patterns[m_players[1]->pattern].frames[m_players[1]->frame];
    info2.anim = m_players[1]->anims[m_players[1]->pattern].frames[m_players[1]->frame];
    info2.x = m_players[1]->x;
    info2.y = m_players[1]->y;
    info2.facing = m_players[1]->facing;
    recoilGuard2 = WillRecoilCounter(m_players[0], m_players[1], (CollisionInfo*)&info1, (CollisionInfo*)&info2);
    recoilGuard1 = WillRecoilCounter(m_players[1], m_players[0], (CollisionInfo*)&info2, (CollisionInfo*)&info1);
    m_players[0]->m_counterHit = 0;
    m_players[1]->m_counterHit = 0;
    slot = m_players[0]->m_objectTail;
    while (slot != m_players[0]->m_objectHead) {
        otherSlot = m_players[1]->m_objectTail;
        while (otherSlot != m_players[1]->m_objectHead) {
            if (m_players[0]->m_objectActive[slot] != 0 && m_players[1]->m_objectActive[otherSlot] != 0) {
                ClashObjects(m_players[0], m_players[1], slot, otherSlot);
            }
            otherSlot++;
            if (otherSlot >= 64) {
                otherSlot = 0;
            }
        }
        slot++;
        if (slot >= 64) {
            slot = 0;
        }
    }
    slot = m_players[0]->m_objectTail;
    while (slot != m_players[0]->m_objectHead) {
        otherSlot = m_players[1]->m_objectTail;
        while (otherSlot != m_players[1]->m_objectHead) {
            if (m_players[0]->m_objectActive[slot] != 0 && m_players[1]->m_objectActive[otherSlot] != 0) {
                ResolveObjectHitsObject(m_players[0], m_players[1], slot, otherSlot);
                ResolveObjectHitsObject(m_players[1], m_players[0], otherSlot, slot);
            }
            otherSlot++;
            if (otherSlot >= 64) {
                otherSlot = 0;
            }
        }
        slot++;
        if (slot >= 64) {
            slot = 0;
        }
    }
    slot = m_players[1]->m_objectTail;
    while (slot != m_players[1]->m_objectHead) {
        if (m_players[1]->m_objectActive[slot] != 0) {
            ResolveObjectAttack(m_players[1], m_players[0], slot, (CollisionInfo*)&info1);
            ResolvePlayerHitsObject(m_players[0], m_players[1], (CollisionInfo*)&info1, (CollisionInfo*)&info2, slot);
        }
        slot++;
        if (slot >= 64) {
            slot = 0;
        }
    }
    slot = m_players[0]->m_objectTail;
    while (slot != m_players[0]->m_objectHead) {
        if (m_players[0]->m_objectActive[slot] != 0) {
            ResolveObjectAttack(m_players[0], m_players[1], slot, (CollisionInfo*)&info2);
            ResolvePlayerHitsObject(m_players[1], m_players[0], (CollisionInfo*)&info2, (CollisionInfo*)&info1, slot);
        }
        slot++;
        if (slot >= 64) {
            slot = 0;
        }
    }
    info1.attackResult = *(char*)&m_players[0]->m_attackResult;
    info1.hitsLeft = m_players[0]->m_hitsLeft;
    info2.attackResult = *(char*)&m_players[1]->m_attackResult;
    info2.hitsLeft = m_players[1]->m_hitsLeft;
    if (recoilGuard1 == 0) {
        ResolvePlayerAttack(m_players[0], m_players[1], (CollisionInfo*)&info1, (CollisionInfo*)&info2);
    }
    if (recoilGuard2 == 0) {
        ResolvePlayerAttack(m_players[1], m_players[0], (CollisionInfo*)&info2, (CollisionInfo*)&info1);
    }
}

void CScene3::PushApart()
{
    int overlap;
    RECT pushRect1;
    RECT pushRect2;
    double vx2;
    double vx1;
    double average; // the mean of the two forward speeds

    vx1 = m_players[0]->vx;
    vx2 = m_players[1]->vx;
    m_players[0]->m_pushVx = 0.0;
    m_players[1]->m_pushVx = 0.0;
    pushRect1 = this->BoxOnStage((ObjBase*)m_players[0], &m_players[0]->m_patterns[m_players[0]->pattern].frames[m_players[0]->frame].pushBox);
    pushRect2 = this->BoxOnStage((ObjBase*)m_players[1], &m_players[1]->m_patterns[m_players[1]->pattern].frames[m_players[1]->frame].pushBox);
    if (BoxesOverlap(&pushRect1, &pushRect2) != 0) {
        if (pushRect1.left + pushRect1.right - (pushRect2.left + pushRect2.right) > 0) {
            overlap = pushRect2.right - pushRect1.left;
            (int)(m_players[0]->x <= 160.0);
            m_players[0]->x += overlap / 2.0;
            (int)(m_players[0]->x > 160.0);
            m_players[1]->x = m_players[1]->x - overlap / 2.0;
            if ((char)m_players[0]->AtScreenEdge() == -1) {
                vx1 = (m_players[0]->facing * vx1 < 0.0) * vx1;
                vx2 = (m_players[0]->facing * vx1 + m_players[1]->facing * vx2 < 0.0) * vx2;
                if (m_players[0]->facing * vx1 < m_players[1]->facing * vx2) {
                    average = (m_players[0]->facing * vx1 + m_players[1]->facing * vx2) / 2.0;
                    vx2 = m_players[1]->facing * average;
                    m_players[0]->m_pushVx = vx1 - m_players[0]->vx;
                    m_players[1]->m_pushVx = vx2 - m_players[1]->vx;
                }
                return;
            }
            if ((char)m_players[1]->AtScreenEdge() == 1) {
                vx2 = (m_players[1]->facing * vx2 > 0.0) * vx2;
                vx1 = (m_players[1]->facing * vx2 + m_players[0]->facing * vx1 > 0.0) * vx1;
                if (m_players[1]->facing * vx2 > m_players[0]->facing * vx1) {
                    average = (m_players[0]->facing * vx1 + m_players[1]->facing * vx2) / 2.0;
                    vx1 = m_players[0]->facing * average;
                    m_players[0]->m_pushVx = vx1 - m_players[0]->vx;
                    m_players[1]->m_pushVx = vx2 - m_players[1]->vx;
                }
                return;
            }
            if (m_players[1]->facing * vx2 >= 0.0 && m_players[0]->facing * vx1 <= 0.0) {
                average = (m_players[0]->facing * vx1 + m_players[1]->facing * vx2) / 2.0;
                vx1 = m_players[0]->facing * average;
                vx2 = m_players[1]->facing * average;
                m_players[0]->m_pushVx = vx1 - m_players[0]->vx;
                m_players[1]->m_pushVx = vx2 - m_players[1]->vx;
                return;
            }
            return;
        }
        overlap = pushRect2.left - pushRect1.right;
        (int)(m_players[1]->x >= 479.0);
        m_players[0]->x += overlap / 2.0;
        (int)(m_players[1]->x < 479.0);
        m_players[1]->x = m_players[1]->x - overlap / 2.0;
        if ((char)m_players[0]->AtScreenEdge() == 1) {
            vx1 = (m_players[0]->facing * vx1 > 0.0) * vx1;
            vx2 = (m_players[0]->facing * vx1 + m_players[1]->facing * vx2 > 0.0) * vx2;
            if (m_players[0]->facing * vx1 > m_players[1]->facing * vx2) {
                average = (m_players[0]->facing * vx1 + m_players[1]->facing * vx2) / 2.0;
                vx2 = m_players[1]->facing * average;
                m_players[0]->m_pushVx = vx1 - m_players[0]->vx;
                m_players[1]->m_pushVx = vx2 - m_players[1]->vx;
            }
            return;
        }
        if ((char)m_players[1]->AtScreenEdge() == -1) {
            vx2 = (m_players[1]->facing * vx2 < 0.0) * vx2;
            vx1 = (m_players[1]->facing * vx2 + m_players[0]->facing * vx1 < 0.0) * vx1;
            if (m_players[0]->facing * vx1 < m_players[1]->facing * vx2) {
                average = (m_players[0]->facing * vx1 + m_players[1]->facing * vx2) / 2.0;
                vx1 = m_players[0]->facing * average;
                m_players[0]->m_pushVx = vx1 - m_players[0]->vx;
                m_players[1]->m_pushVx = vx2 - m_players[1]->vx;
            }
            return;
        }
        if (m_players[1]->facing * vx2 <= 0.0 && m_players[0]->facing * vx1 >= 0.0) {
            average = (m_players[0]->facing * vx1 + m_players[1]->facing * vx2) / 2.0;
            vx1 = m_players[0]->facing * average;
            vx2 = m_players[1]->facing * average;
            m_players[0]->m_pushVx = vx1 - m_players[0]->vx;
            m_players[1]->m_pushVx = vx2 - m_players[1]->vx;
        }
    }
}

RECT CScene3::BoxOnStage(ObjBase* obj, RECT* box)
{
    short hotY;
    RECT rect;
    short hotX;

    hotX = obj->anims[obj->pattern].frames[obj->frame].x;
    hotY = obj->anims[obj->pattern].frames[obj->frame].y;
    if (obj->facing == 1) {
        rect.top = (int)(obj->y - hotY + box->top);
        rect.bottom = (int)(obj->y - hotY + box->bottom);
        rect.left = (int)(obj->x - 0.5 - hotX + box->left);
        rect.right = (int)(obj->x - 0.5 - hotX + box->right);
    } else {
        rect.top = (int)(obj->y - hotY + box->top);
        rect.bottom = (int)(obj->y - hotY + box->bottom);
        rect.left = (int)(obj->x + 0.5 + hotX - box->right);
        rect.right = (int)(obj->x + 0.5 + hotX - box->left);
    }
    return rect;
}

RECT CScene3::InfoBoxOnStage(CollisionInfo* info, RECT* box)
{
    short hotY;
    RECT rect;
    short hotX;

    hotX = info->anim.x;
    hotY = info->anim.y;
    if (info->facing == 1) {
        rect.top = (int)(info->y - hotY + box->top);
        rect.bottom = (int)(info->y - hotY + box->bottom);
        rect.left = (int)(info->x - 0.5 - hotX + box->left);
        rect.right = (int)(info->x - 0.5 - hotX + box->right);
    } else {
        rect.top = (int)(info->y - hotY + box->top);
        rect.bottom = (int)(info->y - hotY + box->bottom);
        rect.left = (int)(info->x + 0.5 + hotX - box->right);
        rect.right = (int)(info->x + 0.5 + hotX - box->left);
    }
    return rect;
}

int CScene3::BoxesOverlap(RECT* a, RECT* b)
{
    if (a->right <= a->left || a->top >= a->bottom || b->right <= b->left || b->top >= b->bottom) {
        return 0;
    }
    return ~(b->right - a->left | a->right - b->left | b->bottom - a->top | a->bottom - b->top) >> 0x1f;
}

int CScene3::WillRecoilCounter(CPlayer* attacker, CPlayer* defender, CollisionInfo* attackerInfo, CollisionInfo* defenderInfo)
{
    RECT pushRect;
    int i;
    RECT contact; // computed as in ResolvePlayerAttack, never used
    int j;
    int anyOverlap;
    int overlaps[4][5];
#if defined(EFZ_NATIVE) || defined(EFZ_TRACE)
    // Only [i][0] is set for a throw; the rest, read when placing the hit spark, is
    // whatever the stack held (the effect's position varies). Zeroed in the native and
    // test builds.
    memset(overlaps, 0, sizeof(overlaps));
#endif
    RECT hurtRects[5];
    PatternFrame attackerFrame;
    PatternFrame defenderFrame;
    RECT attackRects[4];

    anyOverlap = 0;
    attackerFrame = attackerInfo->frame;
    defenderFrame = defenderInfo->frame;
    i = 0;
    for (; i < 4; i++) {
        attackRects[i] = this->InfoBoxOnStage(attackerInfo, &attackerFrame.attackBoxes[i]);
    }
    i = 0;
    for (; i < 5; i++) {
        hurtRects[i] = this->InfoBoxOnStage(defenderInfo, &defenderFrame.boxes[i]);
    }
    pushRect = this->InfoBoxOnStage(defenderInfo, &defenderFrame.pushBox);
    if (attacker->m_attackResult == 0 && (defenderFrame.flagsB0 & kStateInvulnerable) == 0 && attacker->m_hitsLeft > 0 && (defender->m_throwProtect <= 0 || (attackerFrame.flagsAA & kAttackThrow) <= 0) && defender->CanAirRecover() == 0 && defender->m_invulTime == 0) {
        if ((attackerFrame.flagsAA & kAttackThrow) > 0) {
            i = 0;
            for (; i < 4; i++) {
                overlaps[i][0] = 1;
                anyOverlap = BoxesOverlap(&attackRects[i], &pushRect) | anyOverlap;
            }
        } else {
            i = 0;
            for (; i < 4; i++) {
                j = 0;
                for (; j < 5; j++) {
                    overlaps[i][j] = BoxesOverlap(&attackRects[i], &hurtRects[j]);
                    anyOverlap |= overlaps[i][j];
                }
            }
        }
        if (anyOverlap != 0) {
            contact = MakeRect(-10000, -10000, 20000, 20000);
            i = 0;
            for (; i < 4; i++) {
                j = 0;
                for (; j < 5; j++) {
                    if (overlaps[i][j] != 0) {
                        if (contact.left < attackRects[i].left) {
                            contact.left = attackRects[i].left;
                        }
                        if (contact.top < attackRects[i].top) {
                            contact.top = attackRects[i].top;
                        }
                        if (contact.right > attackRects[i].right) {
                            contact.right = attackRects[i].right;
                        }
                        if (contact.bottom > attackRects[i].bottom) {
                            contact.bottom = attackRects[i].bottom;
                        }
                        if (contact.left < hurtRects[j].left) {
                            contact.left = hurtRects[j].left;
                        }
                        if (contact.top < hurtRects[j].top) {
                            contact.top = hurtRects[j].top;
                        }
                        if (contact.right > hurtRects[j].right) {
                            contact.right = hurtRects[j].right;
                        }
                        if (contact.bottom > hurtRects[j].bottom) {
                            contact.bottom = hurtRects[j].bottom;
                        }
                    }
                }
            }
            if (defender->m_canRecoilCounter != 0 && defender->m_recoilGuardWindow >= 30 && defender->m_noGuardTime == 0 && defender->HoldsGuard(&attackerFrame) != 0 && (attackerFrame.flagsAA & kAttackUnblockable) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void CScene3::ResolvePlayerAttack(CPlayer* attacker, CPlayer* defender, CollisionInfo* attackerInfo, CollisionInfo* defenderInfo)
{
    RECT pushRect;
    int i;
    RECT contact; // where the touching boxes overlap: the spark goes at its centre
    int j;
    int anyOverlap;
    int overlaps[4][5];
#if defined(EFZ_NATIVE) || defined(EFZ_TRACE)
    // Only [i][0] is set for a throw; the rest, read when placing the hit spark, is
    // whatever the stack held (the effect's position varies). Zeroed in the native and
    // test builds.
    memset(overlaps, 0, sizeof(overlaps));
#endif
    RECT hurtRects[5];
    PatternFrame attackerFrame;
    PatternFrame defenderFrame;
    RECT attackRects[4];

    anyOverlap = 0;
    attackerFrame = attackerInfo->frame;
    defenderFrame = defenderInfo->frame;
    EffectDesc effect;
    i = 0;
    for (; i < 4; i++) {
        attackRects[i] = this->InfoBoxOnStage(attackerInfo, &attackerFrame.attackBoxes[i]);
    }
    i = 0;
    for (; i < 5; i++) {
        hurtRects[i] = this->InfoBoxOnStage(defenderInfo, &defenderFrame.boxes[i]);
    }
    pushRect = this->InfoBoxOnStage(defenderInfo, &defenderFrame.pushBox);
    if (attackerInfo->attackResult == 0 && (defenderFrame.flagsB0 & kStateInvulnerable) == 0 && attackerInfo->hitsLeft > 0 && (defender->m_throwProtect <= 0 || (attackerFrame.flagsAA & kAttackThrow) <= 0) && defender->CanAirRecover() == 0 && defender->m_invulTime == 0) {
        if ((attackerFrame.flagsAA & kAttackThrow) > 0) {
            i = 0;
            for (; i < 4; i++) {
                overlaps[i][0] = 1;
                anyOverlap = BoxesOverlap(&attackRects[i], &pushRect) | anyOverlap;
            }
        } else {
            i = 0;
            for (; i < 4; i++) {
                j = 0;
                for (; j < 5; j++) {
                    overlaps[i][j] = BoxesOverlap(&attackRects[i], &hurtRects[j]);
                    anyOverlap |= overlaps[i][j];
                }
            }
        }
        if (anyOverlap != 0) {
            // The headless env's red-team advantage: this guard a recoil guard, as the
            // CPU makes its own (never in the game: RecoilAssistOn is false there)
            if (::efz::RecoilAssistOn(defender->m_side) && defender->m_cpu == 0 && defender->m_recoilGuardWindow < 30 &&
                defender->m_noGuardTime == 0 && (attackerFrame.flagsAA & kAttackUnblockable) == 0 &&
                defender->HoldsGuard(&attackerFrame) != 0 && ::efz::RecoilAssistRoll(defender->m_side)) {
                defender->m_recoilGuardWindow = 60;
            }
            contact = MakeRect(-10000, -10000, 20000, 20000);
            i = 0;
            for (; i < 4; i++) {
                j = 0;
                for (; j < 5; j++) {
                    if (overlaps[i][j] != 0) {
                        if (contact.left < attackRects[i].left) {
                            contact.left = attackRects[i].left;
                        }
                        if (contact.top < attackRects[i].top) {
                            contact.top = attackRects[i].top;
                        }
                        if (contact.right > attackRects[i].right) {
                            contact.right = attackRects[i].right;
                        }
                        if (contact.bottom > attackRects[i].bottom) {
                            contact.bottom = attackRects[i].bottom;
                        }
                        if (contact.left < hurtRects[j].left) {
                            contact.left = hurtRects[j].left;
                        }
                        if (contact.top < hurtRects[j].top) {
                            contact.top = hurtRects[j].top;
                        }
                        if (contact.right > hurtRects[j].right) {
                            contact.right = hurtRects[j].right;
                        }
                        if (contact.bottom > hurtRects[j].bottom) {
                            contact.bottom = hurtRects[j].bottom;
                        }
                    }
                }
            }
            if ((defenderFrame.flagsB0 & kStateParryHigh) > 0 && (attackerFrame.flagsAA & kAttackIgnoresArmor) == 0 && (attackerFrame.flagsAA & kAttackGuardStand) > 0) {
                attacker->m_hitsLeft--;
                attacker->m_attackResult = 2;
                attacker->m_attackResult = 6;
                defender->m_attackResult = 6;
                return;
            }
            if ((defenderFrame.flagsB0 & kStateParryLow) > 0 && (attackerFrame.flagsAA & kAttackIgnoresArmor) == 0 && (attackerFrame.flagsAA & kAttackGuardCrouch) > 0) {
                attacker->m_hitsLeft--;
                attacker->m_attackResult = 2;
                attacker->m_attackResult = 6;
                defender->m_attackResult = 6;
                return;
            }
            if (defender->m_canRecoilCounter != 0 && defender->m_recoilGuardWindow >= 30 && defender->m_noGuardTime == 0 && defender->HoldsGuard(&attackerFrame) != 0 && (attackerFrame.flagsAA & kAttackUnblockable) == 0) {
                attacker->m_attackResult = 2;
                attacker->m_gauge += attackerFrame.gaugeOnGuard;
                attacker->m_hitsLeft--;
                defender->m_hitByBody = 1;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectRecoilGuard;
                effect.sound = 10;
                m_game->CreateEffect((EffectDesc*)&effect);
                defender->StartPattern();
                defender->FaceOpponent();
                if (defender->y == 0.0) {
                    defender->pattern = (defender->m_inputY == 1) + 168;
                } else {
                    defender->pattern = kRecoilGuardAir;
                }
                attacker->ClearInput();
                defender->ClearInput();
                defender->m_freezeTime = 60;
                defender->m_canRecoilCounter = 0;
                attacker->m_canRecoilCounter = 1;
                return;
            }
            if (defender->m_recoilGuardWindow >= 30 && defender->y < 0.0 && defender->CanGuard(&attackerFrame, &defenderFrame) != 0) {
                attacker->m_attackResult = 2;
                attacker->m_gauge += attackerFrame.gaugeOnGuard;
                attacker->m_hitsLeft--;
                defender->m_hitByBody = 1;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectRecoilGuard;
                effect.sound = 10;
                m_game->CreateEffect((EffectDesc*)&effect);
                defender->StartPattern();
                defender->FaceOpponent();
                defender->pattern = kRecoilGuardAir;
                attacker->ClearInput();
                defender->ClearInput();
                defender->m_freezeTime = 60;
                attacker->m_canRecoilCounter = 1;
                return;
            }
            if (defender->CanGuard(&attackerFrame, &defenderFrame) != 0 && defender->m_recoilGuardWindow >= 30 && defender->y == 0.0 && defender->pattern != kRecoilGuardStand && defender->pattern != kRecoilGuardCrouch) {
                attacker->m_attackResult = 2;
                attacker->m_gauge += attackerFrame.gaugeOnGuard;
                attacker->m_hitsLeft--;
                defender->m_hitByBody = 1;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectRecoilGuard;
                effect.sound = 10;
                m_game->CreateEffect((EffectDesc*)&effect);
                defender->StartPattern();
                defender->FaceOpponent();
                defender->pattern = (defender->m_inputY == 1) + 168;
                attacker->ClearInput();
                defender->ClearInput();
                defender->m_freezeTime = 60;
                attacker->m_canRecoilCounter = 1;
                return;
            }
            if ((defenderFrame.flagsB0 & kStateGuardPoint) > 0 && (defenderFrame.flagsAA & kAttackGuardStand) > 0 && (attackerFrame.flagsAA & kAttackGuardStand) > 0) {
                attacker->m_hitsLeft--;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectGuardSpark;
                effect.sound = 3;
                m_game->CreateEffect((EffectDesc*)&effect);
                attacker->m_attackResult = 2;
                attacker->m_hitstop = attackerFrame.attackerHitstop;
                defender->m_hitstop = attackerFrame.defenderHitstop;
                defender->m_hp -= attackerFrame.chipDamage;
                if (defender->m_hp <= 0) {
                    defender->m_hp = 1;
                }
                defender->m_guardGauge = attackerFrame.damage / 30 + defender->m_guardGauge;
                if (defender->m_guardGauge > 3.6e+02f) {
                    *(int*)&defender->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if ((defenderFrame.flagsB0 & kStateGuardPoint) > 0 && (defenderFrame.flagsAA & kAttackGuardCrouch) > 0 && (attackerFrame.flagsAA & kAttackGuardCrouch) > 0) {
                attacker->m_hitsLeft--;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectGuardSpark;
                effect.sound = 3;
                m_game->CreateEffect((EffectDesc*)&effect);
                attacker->m_attackResult = 2;
                attacker->m_hitstop = attackerFrame.attackerHitstop;
                defender->m_hitstop = attackerFrame.defenderHitstop;
                defender->m_hp -= attackerFrame.chipDamage;
                if (defender->m_hp <= 0) {
                    defender->m_hp = 1;
                }
                defender->m_guardGauge = attackerFrame.damage / 30 + defender->m_guardGauge;
                if (defender->m_guardGauge > 3.6e+02f) {
                    *(int*)&defender->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if ((defenderFrame.flagsB0 & kStateGuardPoint) > 0 && (defenderFrame.flagsAA & kAttackGuardAir) > 0 && (attackerFrame.flagsAA & kAttackGuardAir) > 0 && defender->y < 0.0) {
                attacker->m_hitsLeft--;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectGuardSpark;
                effect.sound = 3;
                m_game->CreateEffect((EffectDesc*)&effect);
                attacker->m_attackResult = 2;
                attacker->m_hitstop = attackerFrame.attackerHitstop;
                defender->m_hitstop = attackerFrame.defenderHitstop;
                defender->m_hp -= attackerFrame.chipDamage;
                if (defender->m_hp <= 0) {
                    defender->m_hp = 1;
                }
                return;
            }
            if (defender->CanGuard(&attackerFrame, &defenderFrame) != 0) {
                attacker->m_attackResult = 2;
                attacker->m_gauge += attackerFrame.gaugeOnGuard;
                attacker->m_hitsLeft--;
                defender->m_hitByBody = 1;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                defender->pattern = (attackerFrame.flagsAA & kAttackMedium) / 16 + 150 + (attackerFrame.flagsAA & kAttackHeavy) / 32 * 2 + (defender->m_inputY == 1 || (attackerFrame.flagsAA & defenderFrame.flagsB0 & 5) == 0 && defender->m_cpu != 0) * 3;
                if (defender->y < 0.0) {
                    defender->pattern = kGuardAir;
                }
                defender->StartPattern();
                defender->FaceOpponent();
                attacker->m_hitstop = attackerFrame.attackerHitstop;
                defender->m_hitstop = attackerFrame.defenderHitstop;
                defender->m_hp -= attackerFrame.chipDamage;
                if (defender->m_hp <= 0) {
                    defender->m_hp = 1;
                }
                if (attacker->m_guardGauge > 0.0f) {
                    attacker->m_guardGauge = attacker->m_guardGauge - attackerFrame.damage / 30;
                    if (attacker->m_guardGauge < 0.0f) {
                        defender->m_guardGauge = defender->m_guardGauge - attacker->m_guardGauge;
                        *(int*)&attacker->m_guardGauge = 0;
                    }
                } else {
                    defender->m_guardGauge = attackerFrame.damage / 30 + defender->m_guardGauge;
                    if (defender->m_guardGauge > 3.6e+02f) {
                        *(int*)&defender->m_guardGauge = 0x43b40000;
                    }
                }
                defender->m_guardedObject = 0;
                effect.type = kEffectGuardSpark;
                effect.sound = 3;
                m_game->CreateEffect((EffectDesc*)&effect);
                return;
            }
            if ((defenderFrame.flagsB0 & kStateArmor) == 0 && defender->m_armorTime == 0 || ((defenderFrame.flagsB0 & kStateArmor) > 0 || defender->m_armorTime > 0) && (attackerFrame.flagsAA & kAttackIgnoresArmor) > 0 || (attackerFrame.flagsAA & kAttackThrow) > 0) {
                if (defender->y >= 0.0) {
                    if (attackerFrame.groundHitPattern > 0) {
                        defender->pattern = attackerFrame.groundHitPattern;
                    } else if ((defenderFrame.flagsB0 & (kStateStanding | kStateCrouching)) == 3) {
                        defender->pattern = kHitAir;
                    } else if ((defenderFrame.flagsB0 & kStateStanding) != 0) {
                        defender->pattern = ((attackerFrame.flagsAA & kAttackBodyHit) > 0) * 3 + 50 + ((attackerFrame.flagsAA & kAttackMedium) > 0) + ((attackerFrame.flagsAA & kAttackHeavy) > 0) * 2;
                    } else if ((defenderFrame.flagsB0 & kStateCrouching) != 0) {
                        defender->pattern = ((attackerFrame.flagsAA & kAttackMedium) > 0) + 56 + ((attackerFrame.flagsAA & kAttackHeavy) > 0) * 2;
                    }
                } else if (attackerFrame.airHitPattern > 0) {
                    defender->pattern = attackerFrame.airHitPattern;
                } else {
                    defender->pattern = kHitAir;
                }
                attacker->m_attackResult = 3;
                defender->StartPattern();
                defender->FaceOpponent();
            } else {
                attacker->m_comboHits = 0;
                defender->Tint(223, 3);
                attacker->m_attackResult = 7;
            }
            if ((defenderFrame.flagsB0 & kStateCanGuard) > 0) {
                attacker->m_comboHits = 0;
                if (attacker->m_proration > 10000.0) {
                    attacker->m_proration -= 20.0;
                } else {
                    attacker->m_proration = 10000.0;
                }
            }
            defender->m_hitVx = attackerFrame.hitVx;
            defender->m_hitVy = attackerFrame.hitVy;
            defender->m_hitByBody = 1;
            if (attacker->m_comboHits == 0) {
                defender->m_comboStartHp = defender->m_hp;
            }
            attacker->m_counterHit = (attackerFrame.flagsAA & kAttackCounterHit) > 0 && (defenderFrame.flagsB0 & kStateCounterHittable) > 0;
            defender->m_hp -= (int)((double)attackerFrame.damage * attacker->AttackFactor() * defender->DefenseFactor() * attacker->ProrationFactor());
            defender->m_untechTime = (int)(attackerFrame.untechTime * (attacker->m_proration / 10000.0 * 0.8));
            defender->m_noAirRecovery = (attackerFrame.flagsAA & kAttackNoAirRecovery) > 0;
            defender->m_landHittable = (attackerFrame.flagsAA & kAttackLandHittable) > 0;
            defender->m_dashMomentum = 0;
            defender->m_airDashes = 0;
            defender->m_airActions = 0;
            attacker->m_shownProration = attacker->m_proration / 100.0;
            attacker->m_proration = attackerFrame.proration / 1e+03f * attacker->m_proration;
            if (attacker->m_proration > 10000.0) {
                attacker->m_proration = attackerFrame.proration / 1e+03f * attacker->m_proration;
            }
            attacker->m_comboHits++;
            attacker->m_shownHits = attacker->m_comboHits;
            attacker->m_comboTimer = 180;
            attacker->m_comboDamage = defender->m_comboStartHp - defender->m_hp;
            attacker->m_gauge += attackerFrame.gaugeOnHit;
            attacker->m_hitstop = attackerFrame.attackerHitstop;
            defender->m_hitstop = attackerFrame.defenderHitstop;
            attacker->m_hitsLeft--;
            effect.keep = 0;
            effect.type = attackerFrame.hitEffect;
            effect.x = (double)((contact.right + contact.left) / 2);
            effect.y = (double)((contact.bottom + contact.top) / 2);
            effect.side = attacker->facing < 0;
            effect.scale = 2;
            effect.layer = 1;
            effect.screen = 0;
            effect.sound = attackerFrame.hitSound;
            m_game->CreateEffect((EffectDesc*)&effect);
            if (defender->m_hp <= 0 && defender->m_koDelay == 0) {
                defender->pattern = attackerFrame.airHitPattern;
                defender->StartPattern();
                defender->FaceOpponent();
            }
            attacker->ScoreHit(&attackerFrame);
        }
    }
}

void CScene3::ResolveObjectAttack(CPlayer* attacker, CPlayer* defender, int slot, CollisionInfo* defenderInfo)
{
    RECT pushRect;
    RECT contact; // where the touching boxes overlap: the spark goes at its centre
    int anyOverlap;
    int overlaps[4][5];
#if defined(EFZ_NATIVE) || defined(EFZ_TRACE)
    // Only [i][0] is set for a throw; the rest, read when placing the hit spark, is
    // whatever the stack held (the effect's position varies). Zeroed in the native and
    // test builds.
    memset(overlaps, 0, sizeof(overlaps));
#endif
    RECT hurtRects[5];
    RECT attackRects[4];
    PlayerObject* object;
    int i;
    int j;
    PatternFrame* objectFrame;
    CollisionInfo* info; // the same as defenderInfo

    object = &attacker->m_objects[slot];
    objectFrame = &attacker->m_patterns[object->pattern].frames[object->frame];
    info = defenderInfo;
    if (object->attackResult == 0 && (info->frame.flagsB0 & kStateInvulnerable) == 0 && object->hitsLeft > 0 && (defender->m_throwProtect <= 0 || (objectFrame->flagsAA & kAttackThrow) <= 0) && defender->CanAirRecover() == 0 && defender->m_invulTime == 0) {
        anyOverlap = 0;
        i = 0;
        for (; i < 4; i++) {
            attackRects[i] = this->BoxOnStage((ObjBase*)object, &objectFrame->attackBoxes[i]);
        }
        i = 0;
        for (; i < 5; i++) {
            hurtRects[i] = this->InfoBoxOnStage(defenderInfo, (RECT*)((i << 4) + (char*)info));
        }
        pushRect = this->InfoBoxOnStage(defenderInfo, &info->frame.pushBox);
        if ((objectFrame->flagsAA & kAttackThrow) > 0) {
            i = 0;
            for (; i < 4; i++) {
                overlaps[i][0] = 1;
                anyOverlap = BoxesOverlap(&attackRects[i], &pushRect) | anyOverlap;
            }
        } else {
            i = 0;
            for (; i < 4; i++) {
                j = 0;
                for (; j < 5; j++) {
                    overlaps[i][j] = BoxesOverlap(&attackRects[i], &hurtRects[j]);
                    anyOverlap |= overlaps[i][j];
                }
            }
        }
        if (anyOverlap != 0) {
            // The headless env's red-team advantage: this guard a recoil guard, as the
            // CPU makes its own (never in the game: RecoilAssistOn is false there)
            if (::efz::RecoilAssistOn(defender->m_side) && defender->m_cpu == 0 && defender->m_recoilGuardWindow < 30 &&
                defender->m_noGuardTime == 0 && (objectFrame->flagsAA & kAttackUnblockable) == 0 &&
                defender->HoldsGuard((PatternFrame*)objectFrame) != 0 && ::efz::RecoilAssistRoll(defender->m_side)) {
                defender->m_recoilGuardWindow = 60;
            }
            EffectDesc effect;
            contact = MakeRect(-10000, -10000, 20000, 20000);
            i = 0;
            for (; i < 4; i++) {
                j = 0;
                for (; j < 5; j++) {
                    if (overlaps[i][j] != 0) {
                        if (contact.left < attackRects[i].left) {
                            contact.left = attackRects[i].left;
                        }
                        if (contact.top < attackRects[i].top) {
                            contact.top = attackRects[i].top;
                        }
                        if (contact.right > attackRects[i].right) {
                            contact.right = attackRects[i].right;
                        }
                        if (contact.bottom > attackRects[i].bottom) {
                            contact.bottom = attackRects[i].bottom;
                        }
                        if (contact.left < hurtRects[j].left) {
                            contact.left = hurtRects[j].left;
                        }
                        if (contact.top < hurtRects[j].top) {
                            contact.top = hurtRects[j].top;
                        }
                        if (contact.right > hurtRects[j].right) {
                            contact.right = hurtRects[j].right;
                        }
                        if (contact.bottom > hurtRects[j].bottom) {
                            contact.bottom = hurtRects[j].bottom;
                        }
                    }
                }
            }
            if ((info->frame.flagsB0 & kStateReflect) > 0 && (objectFrame->flagsAA & kAttackIgnoresArmor) == 0) {
                object->hitsLeft--;
                object->attackResult = 2;
                attacker->m_attackResult = 6;
                defender->m_attackResult = 6;
                return;
            }
            if (defender->m_canRecoilCounter != 0 && defender->m_recoilGuardWindow >= 30 && defender->m_noGuardTime == 0 && defender->HoldsGuard((PatternFrame*)objectFrame) != 0 && (objectFrame->flagsAA & kAttackUnblockable) == 0) {
                object->attackResult = 2;
                attacker->m_gauge += objectFrame->gaugeOnGuard;
                object->hitsLeft--;
                defender->m_hitByBody = 1;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectRecoilGuard;
                effect.sound = 10;
                m_game->CreateEffect((EffectDesc*)&effect);
                defender->StartPattern();
                defender->facing = -object->facing;
                if (defender->y == 0.0) {
                    defender->pattern = (defender->m_inputY == 1) + 168;
                } else {
                    defender->pattern = kRecoilGuardAir;
                }
                attacker->ClearInput();
                defender->ClearInput();
                defender->m_freezeTime = 60;
                defender->m_canRecoilCounter = 0;
                attacker->m_canRecoilCounter = 1;
                return;
            }
            if (defender->m_recoilGuardWindow >= 30 && defender->y < 0.0 && defender->CanGuard((PatternFrame*)objectFrame, (PatternFrame*)info) != 0) {
                object->attackResult = 2;
                attacker->m_gauge += objectFrame->gaugeOnGuard;
                object->hitsLeft--;
                defender->m_hitByBody = 1;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectRecoilGuard;
                effect.sound = 10;
                m_game->CreateEffect((EffectDesc*)&effect);
                defender->StartPattern();
                defender->facing = -object->facing;
                defender->pattern = kRecoilGuardAir;
                attacker->ClearInput();
                defender->ClearInput();
                defender->m_freezeTime = 60;
                attacker->m_canRecoilCounter = 1;
                return;
            }
            if (defender->CanGuard((PatternFrame*)objectFrame, (PatternFrame*)info) != 0 && defender->m_recoilGuardWindow >= 30 && defender->y == 0.0 && defender->pattern != kRecoilGuardStand && defender->pattern != kRecoilGuardCrouch) {
                object->attackResult = 2;
                attacker->m_gauge += objectFrame->gaugeOnGuard;
                object->hitsLeft--;
                defender->m_hitByBody = 1;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectRecoilGuard;
                effect.sound = 10;
                m_game->CreateEffect((EffectDesc*)&effect);
                defender->StartPattern();
                defender->facing = -object->facing;
                defender->pattern = (defender->m_inputY == 1) + 168;
                attacker->ClearInput();
                defender->ClearInput();
                defender->m_freezeTime = 60;
                attacker->m_canRecoilCounter = 1;
                return;
            }
            if ((info->frame.flagsB0 & kStateGuardPoint) > 0 && (info->frame.flagsAA & kAttackGuardStand) > 0 && (objectFrame->flagsAA & kAttackGuardStand) > 0) {
                object->hitsLeft--;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectGuardSpark;
                effect.sound = 3;
                m_game->CreateEffect((EffectDesc*)&effect);
                attacker->m_attackResult = 2;
                attacker->m_hitstop = objectFrame->attackerHitstop;
                defender->m_hitstop = objectFrame->defenderHitstop;
                defender->m_hp -= objectFrame->chipDamage;
                if (defender->m_hp <= 0) {
                    defender->m_hp = 1;
                }
                defender->m_guardGauge = objectFrame->damage / 30 + defender->m_guardGauge;
                if (defender->m_guardGauge > 3.6e+02f) {
                    *(int*)&defender->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if ((info->frame.flagsB0 & kStateGuardPoint) > 0 && (info->frame.flagsAA & kAttackGuardCrouch) > 0 && (objectFrame->flagsAA & kAttackGuardCrouch) > 0) {
                object->hitsLeft--;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectGuardSpark;
                effect.sound = 3;
                m_game->CreateEffect((EffectDesc*)&effect);
                attacker->m_attackResult = 2;
                attacker->m_hitstop = objectFrame->attackerHitstop;
                defender->m_hitstop = objectFrame->defenderHitstop;
                defender->m_hp -= objectFrame->chipDamage;
                if (defender->m_hp <= 0) {
                    defender->m_hp = 1;
                }
                defender->m_guardGauge = objectFrame->damage / 30 + defender->m_guardGauge;
                if (defender->m_guardGauge > 3.6e+02f) {
                    *(int*)&defender->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if ((info->frame.flagsB0 & kStateGuardPoint) > 0 && (info->frame.flagsAA & kAttackGuardAir) > 0 && (objectFrame->flagsAA & kAttackGuardAir) > 0 && defender->y < 0.0) {
                object->hitsLeft--;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = defender->facing == -1;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                effect.type = kEffectGuardSpark;
                effect.sound = 3;
                m_game->CreateEffect((EffectDesc*)&effect);
                attacker->m_attackResult = 2;
                attacker->m_hitstop = objectFrame->attackerHitstop;
                defender->m_hitstop = objectFrame->defenderHitstop;
                defender->m_hp -= objectFrame->chipDamage;
                if (defender->m_hp <= 0) {
                    defender->m_hp = 1;
                }
                defender->m_guardGauge = objectFrame->damage / 30 + defender->m_guardGauge;
                if (defender->m_guardGauge > 3.6e+02f) {
                    *(int*)&defender->m_guardGauge = 0x43b40000;
                }
                return;
            }
            if (defender->CanGuard((PatternFrame*)objectFrame, (PatternFrame*)info) != 0) {
                defender->pattern = (objectFrame->flagsAA & kAttackMedium) / 16 + 150 + (objectFrame->flagsAA & kAttackHeavy) / 32 * 2 + (defender->m_inputY == 1 || (objectFrame->flagsAA & info->frame.flagsB0 & 5) == 0 && defender->m_cpu != 0) * 3;
                if (defender->y < 0.0) {
                    defender->pattern = kGuardAir;
                }
                defender->StartPattern();
                defender->facing = -object->facing;
                object->attackResult = 2;
                object->hitstop = objectFrame->attackerHitstop;
                defender->m_hitstop = objectFrame->defenderHitstop;
                attacker->m_gauge += objectFrame->gaugeOnGuard;
                object->hitsLeft--;
                defender->m_hitByBody = 0;
                effect.keep = 0;
                effect.x = (double)((contact.right + contact.left) / 2);
                effect.y = (double)((contact.bottom + contact.top) / 2);
                effect.side = attacker->facing < 0;
                effect.scale = 2;
                effect.layer = 1;
                effect.screen = 0;
                defender->m_hp -= objectFrame->chipDamage;
                if (defender->m_hp <= 0) {
                    defender->m_hp = 1;
                }
                if (attacker->m_guardGauge > 0.0f) {
                    attacker->m_guardGauge = attacker->m_guardGauge - objectFrame->damage / 30;
                    if (attacker->m_guardGauge < 0.0f) {
                        defender->m_guardGauge = defender->m_guardGauge - attacker->m_guardGauge;
                        *(int*)&attacker->m_guardGauge = 0;
                    }
                } else {
                    defender->m_guardGauge = objectFrame->damage / 30 + defender->m_guardGauge;
                    if (defender->m_guardGauge > 3.6e+02f) {
                        *(int*)&defender->m_guardGauge = 0x43b40000;
                    }
                }
                defender->m_guardedObject = 1;
                effect.type = kEffectGuardSpark;
                effect.sound = 3;
                m_game->CreateEffect((EffectDesc*)&effect);
                return;
            }
            if ((info->frame.flagsB0 & kStateArmor) == 0 && defender->m_armorTime == 0 || ((info->frame.flagsB0 & kStateArmor) > 0 || defender->m_armorTime > 0) && (objectFrame->flagsAA & kAttackIgnoresArmor) > 0 || (objectFrame->flagsAA & kAttackThrow) > 0) {
                if (defender->y >= 0.0) {
                    if (objectFrame->groundHitPattern > 0) {
                        defender->pattern = objectFrame->groundHitPattern;
                    } else if ((info->frame.flagsB0 & (kStateStanding | kStateCrouching)) == 3) {
                        defender->pattern = kHitAir;
                    } else if ((info->frame.flagsB0 & kStateStanding) != 0) {
                        defender->pattern = ((objectFrame->flagsAA & kAttackBodyHit) > 0) * 3 + 50 + ((objectFrame->flagsAA & kAttackMedium) > 0) + ((objectFrame->flagsAA & kAttackHeavy) > 0) * 2;
                    } else if ((info->frame.flagsB0 & kStateCrouching) != 0) {
                        defender->pattern = ((objectFrame->flagsAA & kAttackMedium) > 0) + 56 + ((objectFrame->flagsAA & kAttackHeavy) > 0) * 2;
                    }
                } else if (objectFrame->airHitPattern > 0) {
                    defender->pattern = objectFrame->airHitPattern;
                } else {
                    defender->pattern = kHitAir;
                }
                object->attackResult = 3;
                defender->StartPattern();
                defender->facing = -object->facing;
            } else {
                attacker->m_comboHits = 0;
                defender->Tint(233, 3);
                object->attackResult = 7;
            }
            if ((info->frame.flagsB0 & kStateCanGuard) > 0) {
                attacker->m_comboHits = 0;
                if (attacker->m_proration > 10000.0) {
                    attacker->m_proration -= 20.0;
                } else {
                    attacker->m_proration = 10000.0;
                }
            }
            defender->m_hitVx = objectFrame->hitVx;
            defender->m_hitVy = objectFrame->hitVy;
            defender->m_hitByBody = 0;
            if (attacker->m_comboHits == 0) {
                defender->m_comboStartHp = defender->m_hp;
            }
            defender->m_hp -= (int)((double)objectFrame->damage * attacker->AttackFactor() * defender->DefenseFactor() * attacker->ProrationFactor());
            defender->m_untechTime = (int)(objectFrame->untechTime * (attacker->m_proration / 10000.0) * (((objectFrame->flagsAA & kAttackCounterHit) > 0 && (info->frame.flagsB0 & kStateCounterHittable) > 0) + 1));
            defender->m_noAirRecovery = (objectFrame->flagsAA & kAttackNoAirRecovery) > 0;
            defender->m_landHittable = (objectFrame->flagsAA & kAttackLandHittable) > 0;
            defender->m_dashMomentum = 0;
            defender->m_airDashes = 0;
            defender->m_airActions = 0;
            attacker->m_shownProration = attacker->m_proration / 100.0;
            attacker->m_proration = objectFrame->proration / 1e+03f * attacker->m_proration;
            if (attacker->m_proration > 10000.0) {
                attacker->m_proration = objectFrame->proration / 1e+03f * attacker->m_proration;
            }
            attacker->m_comboHits++;
            attacker->m_shownHits = attacker->m_comboHits;
            attacker->m_comboTimer = 180;
            attacker->m_comboDamage = defender->m_comboStartHp - defender->m_hp;
            attacker->m_gauge += objectFrame->gaugeOnHit;
            object->hitstop = objectFrame->attackerHitstop;
            defender->m_hitstop = objectFrame->defenderHitstop;
            object->hitsLeft--;
            effect.keep = 0;
            effect.type = objectFrame->hitEffect;
            effect.x = (double)((contact.right + contact.left) / 2);
            effect.y = (double)((contact.bottom + contact.top) / 2);
            effect.side = attacker->facing < 0;
            effect.scale = 2;
            effect.layer = 1;
            effect.screen = 0;
            effect.sound = objectFrame->hitSound;
            m_game->CreateEffect((EffectDesc*)&effect);
            if (defender->m_hp <= 0 && defender->m_koDelay == 0) {
                defender->pattern = objectFrame->airHitPattern;
                defender->StartPattern();
                defender->FaceOpponent();
            }
            attacker->ScoreHit((PatternFrame*)objectFrame);
        }
    }
}

void CScene3::ResolveObjectHitsObject(CPlayer* attacker, CPlayer* defender, int slot, int targetSlot)
{
    RECT contact;
    int anyOverlap;
    int overlaps[4][5];
    RECT hurtRects[5];
    RECT attackRects[4];
    PlayerObject* target;
    int i;
    PlayerObject* object;
    int j;
    PatternFrame* objectFrame;
    PatternFrame* targetFrame; // points into defender->m_patterns: a hit passed on to the owner writes over that frame for good

    object = &attacker->m_objects[slot];
    target = &defender->m_objects[targetSlot];
    objectFrame = &attacker->m_patterns[object->pattern].frames[object->frame];
    targetFrame = &defender->m_patterns[target->pattern].frames[target->frame];
    if (object->attackResult == 0 && object->hitsLeft > 0 && (objectFrame->flagsAA & kAttackThrow) == 0) {
        anyOverlap = 0;
        i = 0;
        for (; i < 4; i++) {
            attackRects[i] = this->BoxOnStage((ObjBase*)object, &objectFrame->attackBoxes[i]);
        }
        i = 0;
        for (; i < 5; i++) {
            hurtRects[i] = this->BoxOnStage((ObjBase*)target, (RECT*)((i << 4) + (char*)targetFrame));
        }
        i = 0;
        for (; i < 4; i++) {
            j = 0;
            for (; j < 5; j++) {
                overlaps[i][j] = BoxesOverlap(&attackRects[i], &hurtRects[j]);
                anyOverlap |= overlaps[i][j];
            }
        }
        if (anyOverlap != 0) {
            contact = MakeRect(-10000, -10000, 20000, 20000);
            i = 0;
            for (; i < 4; i++) {
                j = 0;
                for (; j < 5; j++) {
                    if (overlaps[i][j] != 0) {
                        if (contact.left < attackRects[i].left) {
                            contact.left = attackRects[i].left;
                        }
                        if (contact.top < attackRects[i].top) {
                            contact.top = attackRects[i].top;
                        }
                        if (contact.right > attackRects[i].right) {
                            contact.right = attackRects[i].right;
                        }
                        if (contact.bottom > attackRects[i].bottom) {
                            contact.bottom = attackRects[i].bottom;
                        }
                        if (contact.left < hurtRects[j].left) {
                            contact.left = hurtRects[j].left;
                        }
                        if (contact.top < hurtRects[j].top) {
                            contact.top = hurtRects[j].top;
                        }
                        if (contact.right > hurtRects[j].right) {
                            contact.right = hurtRects[j].right;
                        }
                        if (contact.bottom > hurtRects[j].bottom) {
                            contact.bottom = hurtRects[j].bottom;
                        }
                    }
                }
            }
            if ((targetFrame->flagsB0 & kStateCanGuard) == 0) {
                object->hitsLeft--;
                object->attackResult = 5;
            }
            target->attackResult = 5;
            if ((targetFrame->flagsB0 & kStateCounterHittable) > 0) {
                *targetFrame = defender->m_patterns[defender->pattern].frames[defender->frame];
                if ((targetFrame->flagsB0 & kStateArmor) == 0 && defender->m_armorTime == 0 || ((targetFrame->flagsB0 & kStateArmor) > 0 || defender->m_armorTime > 0) && (objectFrame->flagsAA & kAttackIgnoresArmor) > 0 || (objectFrame->flagsAA & kAttackThrow) > 0) {
                    if (defender->y >= 0.0) {
                        if (objectFrame->groundHitPattern > 0) {
                            defender->pattern = objectFrame->groundHitPattern;
                        } else if ((targetFrame->flagsB0 & (kStateStanding | kStateCrouching)) == 3) {
                            defender->pattern = kHitAir;
                        } else if ((targetFrame->flagsB0 & kStateStanding) != 0) {
                            defender->pattern = ((objectFrame->flagsAA & kAttackBodyHit) > 0) * 3 + 50 + ((objectFrame->flagsAA & kAttackMedium) > 0) + ((objectFrame->flagsAA & kAttackHeavy) > 0) * 2;
                        } else if ((targetFrame->flagsB0 & kStateCrouching) != 0) {
                            defender->pattern = ((objectFrame->flagsAA & kAttackMedium) > 0) + 56 + ((objectFrame->flagsAA & kAttackHeavy) > 0) * 2;
                        }
                    } else if (objectFrame->airHitPattern > 0) {
                        defender->pattern = objectFrame->airHitPattern;
                    } else {
                        defender->pattern = kHitAir;
                    }
                    defender->StartPattern();
                    defender->FaceOpponent();
                } else {
                    attacker->m_comboHits = 0;
                    defender->Tint(223, 2);
                }
                if ((targetFrame->flagsB0 & kStateCanGuard) > 0) {
                    attacker->m_comboHits = 0;
                    if (attacker->m_proration > 10000.0) {
                        attacker->m_proration -= 20.0;
                    } else {
                        attacker->m_proration = 10000.0;
                    }
                }
                defender->m_hitVx = objectFrame->hitVx;
                defender->m_hitVy = objectFrame->hitVy;
                defender->m_hitByBody = 1;
                if (attacker->m_comboHits == 0) {
                    defender->m_comboStartHp = defender->m_hp;
                }
                defender->m_hp -= (int)((double)objectFrame->damage * attacker->AttackFactor() * defender->DefenseFactor() * attacker->ProrationFactor());
                defender->m_untechTime = (int)(objectFrame->untechTime * (attacker->m_proration / 10000.0 * 0.8));
                defender->m_noAirRecovery = (objectFrame->flagsAA & kAttackNoAirRecovery) > 0;
                defender->m_landHittable = (objectFrame->flagsAA & kAttackLandHittable) > 0;
                defender->m_dashMomentum = 0;
                defender->m_airDashes = 0;
                defender->m_airActions = 0;
                attacker->m_shownProration = attacker->m_proration / 100.0;
                attacker->m_proration = objectFrame->proration / 1e+03f * attacker->m_proration;
                if (attacker->m_proration > 10000.0) {
                    attacker->m_proration = objectFrame->proration / 1e+03f * attacker->m_proration;
                }
                attacker->m_comboHits++;
                attacker->m_shownHits = attacker->m_comboHits;
                attacker->m_comboTimer = 180;
                attacker->m_comboDamage = defender->m_comboStartHp - defender->m_hp;
                attacker->m_gauge += objectFrame->gaugeOnHit;
                attacker->m_hitstop = objectFrame->attackerHitstop;
                defender->m_hitstop = objectFrame->defenderHitstop;
                if (defender->m_hp <= 0 && defender->m_koDelay == 0) {
                    defender->pattern = objectFrame->airHitPattern;
                    defender->StartPattern();
                    defender->FaceOpponent();
                }
                attacker->ScoreHit((PatternFrame*)objectFrame);
            }
            EffectDesc effect;
            effect.keep = 0;
            effect.type = objectFrame->hitEffect;
            effect.x = (double)((contact.right + contact.left) / 2);
            effect.y = (double)((contact.bottom + contact.top) / 2);
            effect.side = attacker->facing < 0;
            effect.scale = 2;
            effect.layer = 1;
            effect.screen = 0;
            effect.sound = objectFrame->hitSound;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
    }
}

void CScene3::ClashObjects(CPlayer* player, CPlayer* other, int slot, int otherSlot)
{
    RECT otherPushRect;
    RECT pushRect;
    PlayerObject* otherObject;
    PlayerObject* object;
    int objectFrame; // the address of the object's PatternFrame
    int otherFrame; // the address of the other object's PatternFrame

    object = &player->m_objects[slot];
    otherObject = &other->m_objects[otherSlot];
    objectFrame = (int)player->m_patterns[object->pattern].frames + object->frame * 200;
    otherFrame = (int)other->m_patterns[otherObject->pattern].frames + otherObject->frame * 200;
    if (object->attackResult == 0 && otherObject->attackResult == 0 && object->hitsLeft > 0 && otherObject->hitsLeft > 0 && player->m_patterns[object->pattern].level > 0 && other->m_patterns[otherObject->pattern].level > 0) {
        pushRect = this->BoxOnStage((ObjBase*)object, TOPTR(RECT*, objectFrame + 144));
        otherPushRect = this->BoxOnStage((ObjBase*)otherObject, TOPTR(RECT*, otherFrame + 144));
        if (BoxesOverlap(&pushRect, &otherPushRect) != 0) {
            if (other->m_patterns[otherObject->pattern].level == player->m_patterns[object->pattern].level) {
                object->attackResult = 4;
                otherObject->attackResult = 4;
            } else if (other->m_patterns[otherObject->pattern].level > player->m_patterns[object->pattern].level) {
                object->attackResult = 4;
            } else if (other->m_patterns[otherObject->pattern].level < player->m_patterns[object->pattern].level) {
                otherObject->attackResult = 4;
            }
            if (other->m_patterns[otherObject->pattern].level > 1) {
                object->hitsLeft--;
            }
            if (player->m_patterns[object->pattern].level > 1) {
                otherObject->hitsLeft--;
            }
        }
    }
}

void CScene3::ResolvePlayerHitsObject(CPlayer* attacker, CPlayer* defender, CollisionInfo* attackerInfo, CollisionInfo* defenderInfo, int slot)
{
    RECT contact;
    int anyOverlap;
    int overlaps[4][5];
    RECT hurtRects[5];
    PatternFrame targetFrame; // the object's frame, then its owner's when the hit passes to the owner
    RECT attackRects[4];
    PlayerObject* target;
    int i;
    int j;
    CollisionInfo* info; // the same as attackerInfo

    target = &defender->m_objects[slot];
    info = attackerInfo;
    if (attacker->m_attackResult == 0 && attacker->m_hitsLeft > 0 && (info->frame.flagsAA & kAttackThrow) == 0) {
        targetFrame = defender->m_patterns[target->pattern].frames[target->frame];
        anyOverlap = 0;
        i = 0;
        for (; i < 4; i++) {
            attackRects[i] = this->InfoBoxOnStage(attackerInfo, &info->frame.attackBoxes[i]);
        }
        i = 0;
        for (; i < 5; i++) {
            hurtRects[i] = this->BoxOnStage((ObjBase*)target, &targetFrame.boxes[i]);
        }
        i = 0;
        for (; i < 4; i++) {
            j = 0;
            for (; j < 5; j++) {
                overlaps[i][j] = BoxesOverlap(&attackRects[i], &hurtRects[j]);
                anyOverlap |= overlaps[i][j];
            }
        }
        if (anyOverlap != 0) {
            contact = MakeRect(-10000, -10000, 20000, 20000);
            i = 0;
            for (; i < 4; i++) {
                j = 0;
                for (; j < 5; j++) {
                    if (overlaps[i][j] != 0) {
                        if (contact.left < attackRects[i].left) {
                            contact.left = attackRects[i].left;
                        }
                        if (contact.top < attackRects[i].top) {
                            contact.top = attackRects[i].top;
                        }
                        if (contact.right > attackRects[i].right) {
                            contact.right = attackRects[i].right;
                        }
                        if (contact.bottom > attackRects[i].bottom) {
                            contact.bottom = attackRects[i].bottom;
                        }
                        if (contact.left < hurtRects[j].left) {
                            contact.left = hurtRects[j].left;
                        }
                        if (contact.top < hurtRects[j].top) {
                            contact.top = hurtRects[j].top;
                        }
                        if (contact.right > hurtRects[j].right) {
                            contact.right = hurtRects[j].right;
                        }
                        if (contact.bottom > hurtRects[j].bottom) {
                            contact.bottom = hurtRects[j].bottom;
                        }
                    }
                }
            }
            if ((targetFrame.flagsB0 & kStateCanGuard) == 0) {
                attacker->m_hitsLeft--;
                attacker->m_attackResult = 5;
            }
            target->attackResult = 5;
            if ((targetFrame.flagsB0 & kStateCounterHittable) > 0) {
                targetFrame = defenderInfo->frame;
                if ((targetFrame.flagsB0 & kStateArmor) == 0 && defender->m_armorTime == 0 || ((targetFrame.flagsB0 & kStateArmor) > 0 || defender->m_armorTime > 0) && (info->frame.flagsAA & kAttackIgnoresArmor) > 0 || (info->frame.flagsAA & kAttackThrow) > 0) {
                    if (defender->y >= 0.0) {
                        if (info->frame.groundHitPattern > 0) {
                            defender->pattern = info->frame.groundHitPattern;
                        } else if ((targetFrame.flagsB0 & (kStateStanding | kStateCrouching)) == 3) {
                            defender->pattern = kHitAir;
                        } else if ((targetFrame.flagsB0 & kStateStanding) != 0) {
                            defender->pattern = ((info->frame.flagsAA & kAttackBodyHit) > 0) * 3 + 50 + ((info->frame.flagsAA & kAttackMedium) > 0) + ((info->frame.flagsAA & kAttackHeavy) > 0) * 2;
                        } else if ((targetFrame.flagsB0 & kStateCrouching) != 0) {
                            defender->pattern = ((info->frame.flagsAA & kAttackMedium) > 0) + 56 + ((info->frame.flagsAA & kAttackHeavy) > 0) * 2;
                        }
                    } else if (info->frame.airHitPattern > 0) {
                        defender->pattern = info->frame.airHitPattern;
                    } else {
                        defender->pattern = kHitAir;
                    }
                    defender->StartPattern();
                    defender->FaceOpponent();
                } else {
                    attacker->m_comboHits = 0;
                    defender->Tint(223, 2);
                }
                if ((targetFrame.flagsB0 & kStateCanGuard) > 0) {
                    attacker->m_comboHits = 0;
                    if (attacker->m_proration > 10000.0) {
                        attacker->m_proration -= 20.0;
                    } else {
                        attacker->m_proration = 10000.0;
                    }
                }
                defender->m_hitVx = info->frame.hitVx;
                defender->m_hitVy = info->frame.hitVy;
                defender->m_hitByBody = 1;
                if (attacker->m_comboHits == 0) {
                    defender->m_comboStartHp = defender->m_hp;
                }
                defender->m_hp -= (int)((double)info->frame.damage * attacker->AttackFactor() * defender->DefenseFactor() * attacker->ProrationFactor());
                defender->m_untechTime = (int)(info->frame.untechTime * (attacker->m_proration / 10000.0 * 0.8));
                defender->m_noAirRecovery = (info->frame.flagsAA & kAttackNoAirRecovery) > 0;
                defender->m_landHittable = (info->frame.flagsAA & kAttackLandHittable) > 0;
                defender->m_dashMomentum = 0;
                defender->m_airDashes = 0;
                defender->m_airActions = 0;
                attacker->m_shownProration = attacker->m_proration / 100.0;
                attacker->m_proration = info->frame.proration / 1e+03f * attacker->m_proration;
                if (attacker->m_proration > 10000.0) {
                    attacker->m_proration = info->frame.proration / 1e+03f * attacker->m_proration;
                }
                attacker->m_comboHits++;
                attacker->m_shownHits = attacker->m_comboHits;
                attacker->m_comboTimer = 180;
                attacker->m_comboDamage = defender->m_comboStartHp - defender->m_hp;
                attacker->m_gauge += info->frame.gaugeOnHit;
                attacker->m_hitstop = info->frame.attackerHitstop;
                defender->m_hitstop = info->frame.defenderHitstop;
                if (defender->m_hp <= 0 && defender->m_koDelay == 0) {
                    defender->pattern = info->frame.airHitPattern;
                    defender->StartPattern();
                    defender->FaceOpponent();
                }
                attacker->ScoreHit((PatternFrame*)info);
            }
            EffectDesc effect;
            effect.keep = 0;
            effect.type = info->frame.hitEffect;
            effect.x = (double)((contact.right + contact.left) / 2);
            effect.y = (double)((contact.bottom + contact.top) / 2);
            effect.side = attacker->facing < 0;
            effect.scale = 2;
            effect.layer = 1;
            effect.screen = 0;
            effect.sound = info->frame.hitSound;
            m_game->CreateEffect((EffectDesc*)&effect);
        }
    }
}
