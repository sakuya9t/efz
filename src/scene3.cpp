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

CScene3::CScene3(HWND p1, CPlayer** p2, CPlayer** p3, CGame* p4, CGraphics* p5, CInput* p6, CSound* p7)
    : CScene(p1, p2, p3, p4, p5, p6, p7)
{
    unk440 = 0;
    unk444 = -0x32;
    unk448 = unk440;
    unk44c = unk444;
    unk450 = 5;
    unk454 = -0xa0;
    unk458 = 0;
    unk2c = 1;
    unk2d = 0;
    unk574 = 0;
    unk576 = 0x270f;
    unk578 = 3;
    unk588 = 0;
    unk580 = 0.0;
    unk58c = 0;
    unk590 = 0;
    unk434 = 0;
    unk438 = 0;
    unk43c = 0;
    m_game->unk1354 = 0;
    m_game->unk1350 = 1;
    unk464[0] = MakeRect(0, 0xea, 8, 0xa);
    unk464[1] = MakeRect(0, 0xd2, 0x10, 0xf);
    unk464[2] = MakeRect(0, 0xe1, 7, 9);
    unk464[3] = MakeRect(0, 0x11a, 0xe, 0x16);
    unk464[4] = MakeRect(0, 0x160, 8, 0xc);
    unk464[5] = MakeRect(0, 0x154, 8, 0xc);
    unk464[6] = MakeRect(0, 0x148, 8, 0xc);
    unk464[7] = MakeRect(0, 0x13c, 8, 0xc);
    unk464[8] = MakeRect(0, 0x130, 8, 0xc);
    unk464[9] = MakeRect(0, 0x16c, 7, 0xa);
    unk464[0xa] = MakeRect(0, 0x176, 7, 0xa);
    unk464[0xb] = MakeRect(0, 0x180, 7, 0xa);
    unk464[0xc] = MakeRect(0, 0x18a, 7, 0xa);
    unk464[0xd] = MakeRect(0, 0x194, 7, 0xa);
    unk464[0xe] = MakeRect(0, 0x19e, 7, 0xa);
    unk464[0xf] = MakeRect(0, 0x1a8, 7, 0xa);
    unk464[0x10] = MakeRect(0, 0x1b2, 7, 0xa);
}

CScene3::~CScene3()
{
}

BYTE CScene3::Update()
{
    int v4;

    if ((DWORD)(timeGetTime() - unk438) >= 0x3e8) {
        unk438 = timeGetTime();
        unk43c = unk434;
        unk434 = 0;
    }
    unk434++;
    if (unk2c == 1) {
        m_game->unk1350 = 1;
        m_players[0] = *m_player1Ref;
        m_players[1] = *m_player2Ref;
        unk440 = 0;
        unk444 = -0x32;
        unk448 = unk440;
        unk44c = unk444;
        unk450 = 5;
        unk454 = -0xa0;
        unk458 = 0;
        unk578 = 3;
        unk574 = 0;
        unk576 = 0x270f;
        Unk7647b0();
        Draw();
        CScene::Unk759e20(m_game->m_palette, 0);
        unk2c = 0;
    } else if (unk2d == 1) {
        CScene::Unk759c90(m_game->m_palette, 1, 0, 0x64);
        delete *m_player1Ref;
        *m_player1Ref = (CPlayer*)0;
        delete *m_player2Ref;
        *m_player2Ref = (CPlayer*)0;
        if ((int)m_game->m_background != 0) {
            delete (char*)m_game->m_background;
            m_game->m_background = (CAnimBg*)0;
        }
        unk2d = 0;
        unk2c = 1;
        if (m_game->m_replayMode > 0) {
            m_game->m_replay.Close();
            m_game->m_replayMode = 0;
            m_game->StopMusic();
            return 8;
        }
        if (m_game->unk1364 == 6) {
            return 0;
        }
        return 1;
    }
    Vf2();
    if (unk588 != 0) {
        return 3;
    }
    if (unk2d == 2) {
        unk578 = 1;
        if (Unk765fa0() != 0) {
            unk2d = 0;
            unk2c = 1;
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
    } else if (m_game->unk1427c != 0) {
        unk578 = m_game->unk14280;
        m_game->unk1427c = 0;
    }
    v4 = 0;
    for (; v4 < unk578; v4++) {
        m_players[0]->ReadInput();
        m_players[1]->ReadInput();
        Unk766070();
        m_players[0]->Unk40f230();
        m_players[1]->Unk40f230();
        m_players[0]->Vf8();
        m_players[1]->Vf8();
        m_players[0]->UpdatePattern();
        m_players[1]->UpdatePattern();
        m_players[0]->UpdateObjects();
        m_players[1]->UpdateObjects();
        if (m_game->unk1354 == 0 && m_game->unk1350 == 0) {
            Unk766480();
        }
        Unk766b50();
        m_players[0]->Unk40f580();
        m_players[1]->Unk40f580();
        if (m_players[0]->unk14c > 0) {
            m_players[0]->unk14c--;
        } else {
            m_players[0]->unk14c = 0;
        }
        if (m_players[1]->unk14c > 0) {
            m_players[1]->unk14c--;
        } else {
            m_players[1]->unk14c = 0;
        }
        m_players[0]->Unk40f980();
        m_players[1]->Unk40f980();
        Unk764db0();
        Unk764f10();
        Unk765040();
    }
    m_game->UpdateFade();
    m_game->UpdateTimers();
    Unk7647b0();
    if (m_game->unk136c != 0 || m_game->unk136c == 0 && m_game->unk1368 != 0) {
        Draw();
    }
    m_game->UpdateEffects();
    if ((int)m_game->m_background != 0) {
        m_game->m_background->Vf0();
    }
    return 3;
}

void CScene3::Draw()
{
    m_players[0]->Unk410940();
    m_players[1]->Unk410940();
    Unk75dd50();
    Unk75e240();
    Unk762c50();
    m_game->DrawEffects(unk45c, unk460, 0);
    m_players[0]->DrawObjects(unk45c, unk460, 0);
    m_players[1]->DrawObjects(unk45c, unk460, 0);
    if (m_players[1]->pattern >= 0xc8) {
        m_players[0]->Unk4121a0(unk45c + m_players[0]->Unk4103a0() * (m_players[0]->unk14a % 2) * 2, unk460);
        m_players[1]->Unk4121a0(unk45c + m_players[1]->Unk4103a0() * (m_players[1]->unk14a % 2) * 2, unk460);
    } else {
        m_players[1]->Unk4121a0(unk45c + m_players[1]->Unk4103a0() * (m_players[1]->unk14a % 2) * 2, unk460);
        m_players[0]->Unk4121a0(unk45c + m_players[0]->Unk4103a0() * (m_players[0]->unk14a % 2) * 2, unk460);
    }
    m_players[0]->DrawObjects(unk45c, unk460, 1);
    m_players[1]->DrawObjects(unk45c, unk460, 1);
    m_game->DrawEffects(unk45c, unk460, 1);
    m_game->DrawEffects(unk45c, unk460, 2);
    m_game->DrawEffects(unk45c, unk460, 3);
    if ((int)m_game->m_background != 0 && m_players[0]->unk30c4 == 0 && m_players[1]->unk30c4 == 0 && m_game->unk14278 == 0) {
        m_game->m_background->Vf1(unk45c, unk460, 1);
    }
    if (m_game->unk1420c == 0) {
        m_players[0]->DrawGauge();
        m_players[1]->DrawGauge();
    }
    Unk760060();
    if (m_players[0]->m_shownHits > 1 && m_players[0]->m_comboTimer > 0) {
        Unk7623b0(m_players[0]);
    }
    if (m_players[1]->m_shownHits > 1 && m_players[1]->m_comboTimer > 0) {
        Unk7623b0(m_players[1]);
    }
    if (unk58c != 0) {
        if (unk590 % 2 == 0) {
            m_graphics->Screenshot(unk590 / 2, m_game->m_palette);
        }
        unk590++;
    }
    if (0) {
        Unk75db70(0x50, 0x64, m_players[0]->m_hp, 2, 0, 0);
        Unk75db70(0x50, 0x6e, m_players[0]->pattern, 2, 0, 0);
        Unk75db70(0x50, 0x78, m_players[0]->frame, 2, 0, 0);
        Unk75db70(0x50, 0x82, m_players[0]->timer, 2, 0, 0);
        Unk75db70(0x118, 0x64, m_players[1]->m_hp, 2, 0, 0);
        Unk75db70(0x118, 0x6e, m_players[1]->pattern, 2, 0, 0);
        Unk75db70(0x118, 0x78, m_players[1]->frame, 2, 0, 0);
        Unk75db70(0x118, 0x82, m_players[1]->timer, 2, 0, 0);
    }
    Unk7631f0();
}

void CScene3::Unk7647b0()
{
    int v8;
    int v4;

    unk448 = unk440;
    if (m_game->unk14240 > 0) {
        unk448 = m_game->unk14238;
        if (m_players[0]->unk14a == 0 && m_players[1]->unk14a == 0 && m_players[0]->unk14c == 0 && m_players[1]->unk14c == 0) {
            m_game->unk14240--;
        }
    }
    v4 = 0xa0 - (int)((m_players[0]->x * (unk448 + 0x32) + m_players[1]->x * (0x32 - unk448)) / 100.0);
    if (v4 < -0x13f) {
        v4 = -0x13f;
    } else if (v4 > 0) {
        v4 = 0;
    }
    if (unk454 < v4) {
        unk454 -= (unk454 - v4) / 0xf - 1;
        if (unk454 > v4) {
            unk454 = v4;
        }
    } else {
        unk454 -= (unk454 - v4) / 0xf + 1;
        if (unk454 < v4) {
            unk454 = v4;
        }
    }
    if (unk44c < unk444) {
        unk44c += unk450;
        if (unk44c > unk444) {
            unk44c = unk444;
        }
    } else {
        unk44c += unk450;
        if (unk44c > unk444) {
            unk44c = unk444;
        }
    }
    if (m_players[0]->y < -240.0 || m_players[1]->y < -240.0) {
        unk44c = unk444;
    } else {
        unk44c = 0x14;
    }
    if (m_game->unk14244 > 0) {
        unk44c = m_game->unk1423c * (1 - ((m_players[0]->y < m_players[1]->y) << 1));
        if (m_players[0]->unk14a == 0 && m_players[1]->unk14a == 0 && m_players[0]->unk14c == 0 && m_players[1]->unk14c == 0) {
            m_game->unk14244--;
        }
    }
    if ((v8 = -(((int)m_players[0]->y - (m_players[0]->y < 0.0) + (int)m_players[1]->y - (m_players[1]->y < 0.0)) / 2) + ((int)m_players[0]->y - (m_players[0]->y < 0.0) - (int)m_players[1]->y + (m_players[1]->y < 0.0)) * unk44c / 0x64 * ((m_players[0]->y - m_players[1]->y < 0.0) * 2 + -1)) < 0) {
        v8 = 0;
    } else if (v8 > 0xf0) {
        v8 = 0xf0;
    }
    if (unk458 < v8) {
        unk458 -= (unk458 - v8) / 0xa - 1;
        if (unk458 > v8) {
            unk458 = v8;
        }
    } else {
        unk458 -= (unk458 - v8) / 0xa + 1;
        if (unk458 < v8) {
            unk458 = v8;
        }
    }
    m_game->UpdateShake();
    m_game->m_view = MakeRect(-unk454, -unk458 - 0xd2, 0x140, 0xf0);
    unk45c = unk454 + m_game->m_shakeX;
    unk460 = unk458 + m_game->m_shakeY;
}

void CScene3::Unk764db0()
{
    int v8;
    int v4;

    if (unk2d == 2) {
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

void CScene3::Unk764f10()
{
    int v8;
    int v4;

    if (unk2d == 2) {
        v8 = m_game->m_effectTail;
        while (v8 != m_game->m_effectHead) {
            m_game->m_effects[v8].unk6c = -1;
            v8++;
            if (v8 >= 0x280) {
                v8 = 0;
            }
        }
        return;
    }
    v4 = m_game->m_effectTail;
    while (v4 != m_game->m_effectHead) {
        if ((char)m_game->m_effects[v4].unk6c >= 0 && (char)m_game->m_effects[v4].unk6c < 0x41) {
            m_sound->Play((short)m_game->m_sounds[(char)m_game->m_effects[v4].unk6c], 0);
            m_game->m_effects[v4].unk6c = -1;
        }
        v4++;
        if (v4 >= 0x280) {
            v4 = 0;
        }
    }
}

void CScene3::Unk765040()
{
    if (unk574 != 0) {
        return;
    }
    if (m_game->unk1364 == 1) {
        return;
    }
    if (m_game->unk1354 != 0) {
        m_players[0]->m_pressA = 0;
        m_players[0]->m_pressB = 0;
        m_players[0]->m_pressC = 0;
        m_players[0]->m_pressD = 0;
        m_players[1]->m_pressA = 0;
        m_players[1]->m_pressB = 0;
        m_players[1]->m_pressC = 0;
        m_players[1]->m_pressD = 0;
        if (m_players[0]->pattern >= 0x32 && m_players[0]->Unk410420() == 0 || m_players[1]->pattern >= 0x32 && m_players[1]->Unk410420() == 0 || unk2d == 2) {
            return;
        }
        m_game->unk1354 = 0;
        m_players[0]->m_hp = 0x270f;
        m_players[1]->m_hp = 0x270f;
        m_game->unk1350 = 2;
        return;
    }
    EffectDesc v48;
    if (m_players[0]->m_hp <= 0 && m_players[1]->m_hp <= 0) {
        m_players[0]->unkac++;
        m_players[1]->unkac++;
        if (m_players[0]->unkac >= m_game->unk134e) {
            m_players[0]->unkac--;
        }
        if (m_players[1]->unkac >= m_game->unk134e) {
            m_players[1]->unkac--;
        }
        m_players[0]->pattern = 0x3b;
        m_players[0]->StartPattern();
        m_players[1]->pattern = 0x3b;
        m_players[1]->StartPattern();
        m_game->unk1354 = 1;
        if (m_game->unk134d < 9) {
            m_game->unk134d++;
        }
        return;
    }
    if (m_players[0]->m_hp <= 0 && m_players[0]->unk140 == 0) {
        m_players[1]->unk30dc += m_players[1]->m_hp;
        if (m_players[1]->unkac < m_game->unk134e - 1) {
            m_players[1]->unkac++;
            m_players[0]->unk14c = m_players[0]->unk14c + 0xb4;
            m_players[1]->unk14c = m_players[1]->unk14c + 0xb4;
            m_players[0]->StartPattern();
            v48.unk0 = 0;
            v48.x = 80.0;
            v48.y = 100.0;
            v48.side = 0;
            v48.scale = 0;
            v48.layer = 2;
            v48.screen = 1;
            v48.type = 0x13;
            v48.unk2c = 0x1d;
            m_game->CreateEffect((EffectDesc*)&v48);
            m_game->unk1354 = 1;
            if (m_game->unk134d < 9) {
                m_game->unk134d++;
            }
        } else {
            m_players[1]->unkac++;
            m_players[0]->StartPattern();
            m_game->unk1354 = 1;
            unk2d = 2;
            unk580 = 0.0;
            m_game->unk134c = 1;
        }
        return;
    }
    if (m_players[1]->m_hp <= 0 && m_players[1]->unk140 == 0) {
        m_players[0]->unk30dc += m_players[0]->m_hp;
        if (m_players[0]->unkac < m_game->unk134e - 1) {
            m_players[0]->unkac++;
            m_players[0]->unk14c = m_players[0]->unk14c + 0xb4;
            m_players[1]->unk14c = m_players[1]->unk14c + 0xb4;
            v48.unk0 = 0;
            v48.x = 240.0;
            v48.y = 100.0;
            v48.side = 0;
            v48.scale = 0;
            v48.layer = 2;
            v48.screen = 1;
            v48.type = 0x13;
            v48.unk2c = 0x1d;
            m_game->CreateEffect((EffectDesc*)&v48);
            m_players[1]->StartPattern();
            m_game->unk1354 = 1;
            if (m_game->unk134d < 9) {
                m_game->unk134d++;
            }
            return;
        }
        m_players[0]->unkac++;
        m_players[1]->StartPattern();
        m_game->unk1354 = 1;
        unk2d = 2;
        unk580 = 0.0;
        m_game->unk134c = 0;
    }
}

void CScene3::Vf2()
{
    int l10c;
    char v108[256];

    l10c = m_input->m_keyboard->GetDeviceState(0x100, v108);
    if (l10c < 0 && l10c == 0x8007001e) {
        m_input->m_keyboard->Acquire();
    }
    if (m_game->m_replayMode == 1 && m_game->m_replay.m_eof != 0) {
        m_game->m_replay.m_eof = 0;
        unk2d = 1;
    }
    if (unk2d == 0 && m_game->unk1364 == 6) {
        m_game->UpdateInput();
        if (m_game->m_pressA[0] != 0 || m_game->m_pressA[1] != 0 || m_game->m_pressB[0] != 0 || m_game->m_pressB[1] != 0 || (v108[1] & 0x80) != 0) {
            unk2d = 1;
            m_game->StopMusic();
            unk588 = 0;
        }
    }
    if (unk2d == 0 && (v108[1] & 0x80) != 0) {
        unk2d = 1;
        unk588 = 0;
    }
    if ((v108[62] & 0x80) != 0 && m_game->unk1350 == 0 && m_game->unk1354 == 0 && m_game->unk1364 != 0 && m_game->unk1364 != 2 && m_game->unk1364 != 6) {
        unk574 = unk574 + 5;
        if (unk574 > 0x7d0) {
            unk574 = 0;
        }
        unk576 = 0x270f;
        m_players[0]->unk30ec = unk574;
        m_players[1]->unk30ec = unk574;
        m_players[0]->unk30ee = unk576;
        m_players[1]->unk30ee = unk576;
    } else if ((v108[63] & 0x80) != 0 && g_fkeyHeld == 0 && m_game->unk1364 != 0 && m_game->unk1364 != 2 && m_game->unk1364 != 6) {
        if (unk574 == 0x3e8) {
            if (unk576 == 0xd04) {
                unk574 = 0x7d0;
            } else {
                unk576 = 0xd04;
            }
        } else {
            unk574 = 0x3e8;
        }
        m_players[0]->unk30ec = unk574;
        m_players[1]->unk30ec = unk574;
        m_players[0]->unk30ee = unk576;
        m_players[1]->unk30ee = unk576;
        g_fkeyHeld = 1;
    }
    if (m_game->unk1364 == 1) {
        if ((v108[64] & 0x80) != 0 && g_fkeyHeld == 0) {
            m_game->unk1346++;
            if ((char)m_game->unk1346 > 2) {
                m_game->unk1346 = 0;
            }
            g_fkeyHeld = 1;
        } else if ((v108[65] & 0x80) != 0 && g_fkeyHeld == 0) {
            m_game->unk1348 = m_game->unk1348 == 0;
            g_fkeyHeld = 1;
        }
    } else if (m_game->unk1364 == 5 && m_game->m_replayMode == 2 && (v108[64] & 0x80) != 0) {
        Unk7661a0();
    }
    if ((v108[66] & 0x80) != 0 && g_fkeyHeld == 0) {
        unk588 = unk588 == 0;
        g_fkeyHeld = 1;
    }
    if (unk574 == 0x7d0) {
        unk574 = 0;
        unk576 = 0x270f;
        m_players[0]->unk30ec = unk574;
        m_players[1]->unk30ec = unk574;
        m_players[0]->unk30ee = unk576;
        m_players[1]->unk30ee = unk576;
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
            unk578 = 1;
        }
        if ((v108[60] & 0x80) != 0) {
            unk578 = 2;
        }
        if ((v108[61] & 0x80) != 0) {
            unk578 = 3;
        }
        if ((v108[67] & 0x80) != 0) {
            unk58c = 1;
        }
        if ((v108[68] & 0x80) != 0) {
            unk58c = 0;
        }
        if ((v108[87] & 0x80) != 0) {
            unk590 = 0;
        }
        if ((v108[88] & 0x80) != 0) {
            m_players[0]->m_hp = 1;
            m_players[1]->m_hp = 1;
        }
    }
    if (m_game->m_replayMode == 1 && unk588 == 0) {
        if (m_game->unk1340 > 0) {
            unk574 = m_game->m_replay.Read();
            unk576 = m_game->m_replay.Read();
        } else {
            unk574 = 0x3e8;
            unk576 = 0x270f;
        }
        m_players[0]->unk30ec = unk574;
        m_players[1]->unk30ec = unk574;
        m_players[0]->unk30ee = unk576;
        m_players[1]->unk30ee = unk576;
        return;
    }
    if (m_game->m_replayMode == 2 && unk588 == 0) {
        m_game->m_replay.Write(unk574);
        m_game->m_replay.Write(unk576);
    }
}

int CScene3::Unk765fa0()
{
    if (unk580 < 100.0) {
        m_graphics->Brighten(m_game->m_palette, 0, 0xff, (int)(100.0 - unk580));
        m_sound->SetVolume((short)m_game->m_music, (int)(-unk580 * 100.0 / 2.0) + m_game->m_musicVolume);
    }
    unk580++;
    if (unk580 >= 200.0) {
        return 1;
    }
    return 0;
}

void CScene3::Unk766070()
{
    if (m_game->unk1350 == 0) {
        return;
    }
    EffectDesc v48;
    switch (m_game->unk1350) {
    case 1:
        v48.unk0 = 0;
        v48.x = 160.0;
        v48.y = 120.0;
        v48.side = 0;
        v48.scale = 2;
        v48.layer = 2;
        v48.screen = 1;
        v48.type = 0x1b;
        v48.unk2c = -1;
        m_game->CreateEffect((EffectDesc*)&v48);
        m_game->unk1350 = 0x63;
        m_game->unk1352 = 0x12c;
        break;
    case 2:
        v48.unk0 = 0;
        v48.x = 160.0;
        v48.y = 120.0;
        v48.side = 0;
        v48.scale = 2;
        v48.layer = 2;
        v48.screen = 1;
        v48.type = 5;
        v48.unk2c = m_game->unk134d + 0xb;
        m_game->CreateEffect((EffectDesc*)&v48);
        m_game->unk1350 = 0x63;
        m_game->unk1352 = 0x10e;
    }
}

void CScene3::Unk7661a0()
{
    char v34[40];
    char vc[8];

    if (m_game->unk1364 == 5 && m_game->m_replayMode == 2) {
        CScene::Unk759c90(m_game->m_palette, 0, 0, 0);
        m_game->m_replay.Close();
        strcpy(v34, "replay\\data");
        _itoa(m_game->unk14282 + 1, vc, 0xa);
        strcat(v34, (const char*)vc);
        strcat(v34, "-");
        _itoa(m_game->unk14281 + 1, vc, 0xa);
        strcat(v34, (const char*)vc);
        strcat(v34, ".rep");
        m_game->m_replay.OpenWrite((const char*)v34);
        m_game->m_replay.Write((*m_player1Ref)->unk8d);
        m_game->m_replay.Write((*m_player2Ref)->unk8d);
        m_game->m_replay.Write(0x68);
        m_game->m_replay.Write(m_game->unkf32);
        m_game->m_replay.Write((*m_player1Ref)->m_paletteIndex);
        m_game->m_replay.Write((*m_player2Ref)->m_paletteIndex);
        m_game->Reset();
        (*m_player1Ref)->Load();
        (*m_player2Ref)->Load();
        m_players[0]->unk30ec = unk574;
        m_players[1]->unk30ec = unk574;
        m_game->unk1350 = 1;
        unk440 = 0;
        unk444 = -0x32;
        unk448 = unk440;
        unk44c = unk444;
        unk450 = 5;
        unk454 = -0xa0;
        unk458 = 0;
        unk578 = 3;
        Unk7647b0();
        Draw();
        CScene::Unk759e20(m_game->m_palette, 0);
    }
}

void CScene3::Unk766480()
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
    lf4 = Unk7679b0(m_players[0], m_players[1], (CollisionInfo*)&x1e8, (CollisionInfo*)&vf0);
    v1ec = Unk7679b0(m_players[1], m_players[0], (CollisionInfo*)&vf0, (CollisionInfo*)&x1e8);
    m_players[0]->unk144 = 0;
    m_players[1]->unk144 = 0;
    vf8 = m_players[0]->m_objectTail;
    while (vf8 != m_players[0]->m_objectHead) {
        l1f0 = m_players[1]->m_objectTail;
        while (l1f0 != m_players[1]->m_objectHead) {
            if (m_players[0]->m_objectActive[vf8] != 0 && m_players[1]->m_objectActive[l1f0] != 0) {
                Unk76bab0(m_players[0], m_players[1], vf8, l1f0);
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
                Unk76b090(m_players[0], m_players[1], vf8, l1f0);
                Unk76b090(m_players[1], m_players[0], l1f0, vf8);
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
            Unk7697d0(m_players[1], m_players[0], vf8, (CollisionInfo*)&x1e8);
            Unk76bd40(m_players[0], m_players[1], (CollisionInfo*)&x1e8, (CollisionInfo*)&vf0, vf8);
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    vf8 = m_players[0]->m_objectTail;
    while (vf8 != m_players[0]->m_objectHead) {
        if (m_players[0]->m_objectActive[vf8] != 0) {
            Unk7697d0(m_players[0], m_players[1], vf8, (CollisionInfo*)&vf0);
            Unk76bd40(m_players[1], m_players[0], (CollisionInfo*)&vf0, (CollisionInfo*)&x1e8, vf8);
        }
        vf8++;
        if (vf8 >= 0x40) {
            vf8 = 0;
        }
    }
    x1e8.unke9 = *(char*)&m_players[0]->m_attackResult;
    x1e8.unkea = m_players[0]->m_hitsLeft;
    vf0.unke9 = *(char*)&m_players[1]->m_attackResult;
    vf0.unkea = m_players[1]->m_hitsLeft;
    if (v1ec == 0) {
        Unk767f60(m_players[0], m_players[1], (CollisionInfo*)&x1e8, (CollisionInfo*)&vf0);
    }
    if (lf4 == 0) {
        Unk767f60(m_players[1], m_players[0], (CollisionInfo*)&vf0, (CollisionInfo*)&x1e8);
    }
}

void CScene3::Unk766b50()
{
    int x3c;
    RECT v38;
    RECT v28;
    double n18;
    double v10;
    double x8;

    v10 = m_players[0]->vx;
    n18 = m_players[1]->vx;
    m_players[0]->unkb0 = 0.0;
    m_players[1]->unkb0 = 0.0;
    v38 = this->Unk767600((ObjBase*)m_players[0], &m_players[0]->m_patterns[m_players[0]->pattern].frames[m_players[0]->frame].box90);
    v28 = this->Unk767600((ObjBase*)m_players[1], &m_players[1]->m_patterns[m_players[1]->pattern].frames[m_players[1]->frame].box90);
    if (Unk767930(&v38, &v28) != 0) {
        if (v38.left + v38.right - (v28.left + v28.right) > 0) {
            x3c = v28.right - v38.left;
            (int)(m_players[0]->x <= 160.0);
            m_players[0]->x += x3c / 2.0;
            (int)(m_players[0]->x > 160.0);
            m_players[1]->x = m_players[1]->x - x3c / 2.0;
            if ((char)m_players[0]->Unk40ff70() == -1) {
                v10 = (m_players[0]->facing * v10 < 0.0) * v10;
                n18 = (m_players[0]->facing * v10 + m_players[1]->facing * n18 < 0.0) * n18;
                if (m_players[0]->facing * v10 < m_players[1]->facing * n18) {
                    x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                    n18 = m_players[1]->facing * x8;
                    m_players[0]->unkb0 = v10 - m_players[0]->vx;
                    m_players[1]->unkb0 = n18 - m_players[1]->vx;
                }
                return;
            }
            if ((char)m_players[1]->Unk40ff70() == 1) {
                n18 = (m_players[1]->facing * n18 > 0.0) * n18;
                v10 = (m_players[1]->facing * n18 + m_players[0]->facing * v10 > 0.0) * v10;
                if (m_players[1]->facing * n18 > m_players[0]->facing * v10) {
                    x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                    v10 = m_players[0]->facing * x8;
                    m_players[0]->unkb0 = v10 - m_players[0]->vx;
                    m_players[1]->unkb0 = n18 - m_players[1]->vx;
                }
                return;
            }
            if (m_players[1]->facing * n18 >= 0.0 && m_players[0]->facing * v10 <= 0.0) {
                x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                v10 = m_players[0]->facing * x8;
                n18 = m_players[1]->facing * x8;
                m_players[0]->unkb0 = v10 - m_players[0]->vx;
                m_players[1]->unkb0 = n18 - m_players[1]->vx;
                return;
            }
            return;
        }
        x3c = v28.left - v38.right;
        (int)(m_players[1]->x >= 479.0);
        m_players[0]->x += x3c / 2.0;
        (int)(m_players[1]->x < 479.0);
        m_players[1]->x = m_players[1]->x - x3c / 2.0;
        if ((char)m_players[0]->Unk40ff70() == 1) {
            v10 = (m_players[0]->facing * v10 > 0.0) * v10;
            n18 = (m_players[0]->facing * v10 + m_players[1]->facing * n18 > 0.0) * n18;
            if (m_players[0]->facing * v10 > m_players[1]->facing * n18) {
                x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                n18 = m_players[1]->facing * x8;
                m_players[0]->unkb0 = v10 - m_players[0]->vx;
                m_players[1]->unkb0 = n18 - m_players[1]->vx;
            }
            return;
        }
        if ((char)m_players[1]->Unk40ff70() == -1) {
            n18 = (m_players[1]->facing * n18 < 0.0) * n18;
            v10 = (m_players[1]->facing * n18 + m_players[0]->facing * v10 < 0.0) * v10;
            if (m_players[0]->facing * v10 < m_players[1]->facing * n18) {
                x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
                v10 = m_players[0]->facing * x8;
                m_players[0]->unkb0 = v10 - m_players[0]->vx;
                m_players[1]->unkb0 = n18 - m_players[1]->vx;
            }
            return;
        }
        if (m_players[1]->facing * n18 <= 0.0 && m_players[0]->facing * v10 >= 0.0) {
            x8 = (m_players[0]->facing * v10 + m_players[1]->facing * n18) / 2.0;
            v10 = m_players[0]->facing * x8;
            n18 = m_players[1]->facing * x8;
            m_players[0]->unkb0 = v10 - m_players[0]->vx;
            m_players[1]->unkb0 = n18 - m_players[1]->vx;
        }
    }
}

RECT CScene3::Unk767600(ObjBase* p1, RECT* p2)
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

RECT CScene3::Unk7677a0(CollisionInfo* p1, RECT* p2)
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

int CScene3::Unk767930(RECT* p1, RECT* p2)
{
    if (p1->right <= p1->left || p1->top >= p1->bottom || p2->right <= p2->left || p2->top >= p2->bottom) {
        return 0;
    }
    return ~(p2->right - p1->left | p1->right - p2->left | p2->bottom - p1->top | p1->bottom - p2->top) >> 0x1f;
}

int CScene3::Unk7679b0(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4)
{
    RECT b29c;
    int v28c;
    RECT n288;
    int v278;
    int v274;
    int v270[4][5];
    RECT l220[5];
    PatternFrame b1d0;
    PatternFrame v108;
    RECT x40[4];

    v274 = 0;
    b1d0 = p3->frame;
    v108 = p4->frame;
    v28c = 0;
    for (; v28c < 4; v28c++) {
        x40[v28c] = this->Unk7677a0(p3, &b1d0.attackBoxes[v28c]);
    }
    v28c = 0;
    for (; v28c < 5; v28c++) {
        l220[v28c] = this->Unk7677a0(p4, &v108.boxes[v28c]);
    }
    b29c = this->Unk7677a0(p4, &v108.box90);
    if (p1->m_attackResult == 0 && (v108.flagsB0 & 0x20) == 0 && p1->m_hitsLeft > 0 && (p2->unk130 <= 0 || (b1d0.flagsAA & 0x40) <= 0) && p2->Unk4102e0() == 0 && p2->unk13c == 0) {
        if ((b1d0.flagsAA & 0x40) > 0) {
            v28c = 0;
            for (; v28c < 4; v28c++) {
                v270[v28c][0] = 1;
                v274 = Unk767930(&x40[v28c], &b29c) | v274;
            }
        } else {
            v28c = 0;
            for (; v28c < 4; v28c++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    v270[v28c][v278] = Unk767930(&x40[v28c], &l220[v278]);
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
            if (p2->unk170 != 0 && p2->unk14e >= 0x1e && p2->unk13a == 0 && p2->Unk4100f0(&b1d0) != 0 && (b1d0.flagsAA & 0x80) == 0) {
                return 1;
            }
        }
    }
    return 0;
}

void CScene3::Unk767f60(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4)
{
    RECT v2e4;
    int v2d4;
    RECT v2d0;
    int v278;
    int v274;
    int v270[4][5];
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
        x40[v2d4] = this->Unk7677a0(p3, &b1d0.attackBoxes[v2d4]);
    }
    v2d4 = 0;
    for (; v2d4 < 5; v2d4++) {
        l220[v2d4] = this->Unk7677a0(p4, &v108.boxes[v2d4]);
    }
    v2e4 = this->Unk7677a0(p4, &v108.box90);
    if (p3->unke9 == 0 && (v108.flagsB0 & 0x20) == 0 && p3->unkea > 0 && (p2->unk130 <= 0 || (b1d0.flagsAA & 0x40) <= 0) && p2->Unk4102e0() == 0 && p2->unk13c == 0) {
        if ((b1d0.flagsAA & 0x40) > 0) {
            v2d4 = 0;
            for (; v2d4 < 4; v2d4++) {
                v270[v2d4][0] = 1;
                v274 = Unk767930(&x40[v2d4], &v2e4) | v274;
            }
        } else {
            v2d4 = 0;
            for (; v2d4 < 4; v2d4++) {
                v278 = 0;
                for (; v278 < 5; v278++) {
                    v270[v2d4][v278] = Unk767930(&x40[v2d4], &l220[v278]);
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
            if ((v108.flagsB0 & 0x1000) > 0 && (b1d0.flagsAA & 0x100) == 0 && (b1d0.flagsAA & 1) > 0) {
                p1->m_hitsLeft--;
                p1->m_attackResult = 2;
                p1->m_attackResult = 6;
                p2->m_attackResult = 6;
                return;
            }
            if ((v108.flagsB0 & 0x800) > 0 && (b1d0.flagsAA & 0x100) == 0 && (b1d0.flagsAA & 2) > 0) {
                p1->m_hitsLeft--;
                p1->m_attackResult = 2;
                p1->m_attackResult = 6;
                p2->m_attackResult = 6;
                return;
            }
            if (p2->unk170 != 0 && p2->unk14e >= 0x1e && p2->unk13a == 0 && p2->Unk4100f0(&b1d0) != 0 && (b1d0.flagsAA & 0x80) == 0) {
                p1->m_attackResult = 2;
                p1->m_gauge += b1d0.unkb6;
                p1->m_hitsLeft--;
                p2->unkd0 = 1;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = 0x11;
                k2c0.unk2c = 0xa;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p2->StartPattern();
                p2->FaceOpponent();
                if (p2->y == 0.0) {
                    p2->pattern = (p2->m_inputY == 1) + 0xa8;
                } else {
                    p2->pattern = 0xaa;
                }
                p1->ClearInput();
                p2->ClearInput();
                p2->unk14c = 0x3c;
                p2->unk170 = 0;
                p1->unk170 = 1;
                return;
            }
            if (p2->unk14e >= 0x1e && p2->y < 0.0 && p2->Unk410050(&b1d0, &v108) != 0) {
                p1->m_attackResult = 2;
                p1->m_gauge += b1d0.unkb6;
                p1->m_hitsLeft--;
                p2->unkd0 = 1;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = 0x11;
                k2c0.unk2c = 0xa;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p2->StartPattern();
                p2->FaceOpponent();
                p2->pattern = 0xaa;
                p1->ClearInput();
                p2->ClearInput();
                p2->unk14c = 0x3c;
                p1->unk170 = 1;
                return;
            }
            if (p2->Unk410050(&b1d0, &v108) != 0 && p2->unk14e >= 0x1e && p2->y == 0.0 && p2->pattern != 0xa8 && p2->pattern != 0xa9) {
                p1->m_attackResult = 2;
                p1->m_gauge += b1d0.unkb6;
                p1->m_hitsLeft--;
                p2->unkd0 = 1;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = 0x11;
                k2c0.unk2c = 0xa;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p2->StartPattern();
                p2->FaceOpponent();
                p2->pattern = (p2->m_inputY == 1) + 0xa8;
                p1->ClearInput();
                p2->ClearInput();
                p2->unk14c = 0x3c;
                p1->unk170 = 1;
                return;
            }
            if ((v108.flagsB0 & 0x200) > 0 && (v108.flagsAA & 1) > 0 && (b1d0.flagsAA & 1) > 0) {
                p1->m_hitsLeft--;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = 2;
                k2c0.unk2c = 3;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p1->m_attackResult = 2;
                p1->unk14a = b1d0.unkc2;
                p2->unk14a = b1d0.unkc4;
                p2->m_hp -= b1d0.unka8;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->unk134 = b1d0.unka0 / 0x1e + p2->unk134;
                if (p2->unk134 > 3.6e+02f) {
                    *(int*)&p2->unk134 = 0x43b40000;
                }
                return;
            }
            if ((v108.flagsB0 & 0x200) > 0 && (v108.flagsAA & 2) > 0 && (b1d0.flagsAA & 2) > 0) {
                p1->m_hitsLeft--;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = 2;
                k2c0.unk2c = 3;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p1->m_attackResult = 2;
                p1->unk14a = b1d0.unkc2;
                p2->unk14a = b1d0.unkc4;
                p2->m_hp -= b1d0.unka8;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->unk134 = b1d0.unka0 / 0x1e + p2->unk134;
                if (p2->unk134 > 3.6e+02f) {
                    *(int*)&p2->unk134 = 0x43b40000;
                }
                return;
            }
            if ((v108.flagsB0 & 0x200) > 0 && (v108.flagsAA & 4) > 0 && (b1d0.flagsAA & 4) > 0 && p2->y < 0.0) {
                p1->m_hitsLeft--;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                k2c0.type = 2;
                k2c0.unk2c = 3;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                p1->m_attackResult = 2;
                p1->unk14a = b1d0.unkc2;
                p2->unk14a = b1d0.unkc4;
                p2->m_hp -= b1d0.unka8;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                return;
            }
            if (p2->Unk410050(&b1d0, &v108) != 0) {
                p1->m_attackResult = 2;
                p1->m_gauge += b1d0.unkb6;
                p1->m_hitsLeft--;
                p2->unkd0 = 1;
                k2c0.unk0 = 0;
                k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
                k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
                k2c0.side = p2->facing == -1;
                k2c0.scale = 2;
                k2c0.layer = 1;
                k2c0.screen = 0;
                p2->pattern = (b1d0.flagsAA & 0x10) / 0x10 + 0x96 + (b1d0.flagsAA & 0x20) / 0x20 * 2 + (p2->m_inputY == 1 || (b1d0.flagsAA & v108.flagsB0 & 5) == 0 && p2->m_cpu != 0) * 3;
                if (p2->y < 0.0) {
                    p2->pattern = 0x9c;
                }
                p2->StartPattern();
                p2->FaceOpponent();
                p1->unk14a = b1d0.unkc2;
                p2->unk14a = b1d0.unkc4;
                p2->m_hp -= b1d0.unka8;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                if (p1->unk134 > 0.0f) {
                    p1->unk134 = p1->unk134 - b1d0.unka0 / 0x1e;
                    if (p1->unk134 < 0.0f) {
                        p2->unk134 = p2->unk134 - p1->unk134;
                        *(int*)&p1->unk134 = 0;
                    }
                } else {
                    p2->unk134 = b1d0.unka0 / 0x1e + p2->unk134;
                    if (p2->unk134 > 3.6e+02f) {
                        *(int*)&p2->unk134 = 0x43b40000;
                    }
                }
                p2->unk154 = 0;
                k2c0.type = 2;
                k2c0.unk2c = 3;
                m_game->CreateEffect((EffectDesc*)&k2c0);
                return;
            }
            if ((v108.flagsB0 & 4) == 0 && p2->unk138 == 0 || ((v108.flagsB0 & 4) > 0 || p2->unk138 > 0) && (b1d0.flagsAA & 0x100) > 0 || (b1d0.flagsAA & 0x40) > 0) {
                if (p2->y >= 0.0) {
                    if (b1d0.unkae > 0) {
                        p2->pattern = b1d0.unkae;
                    } else if ((v108.flagsB0 & 3) == 3) {
                        p2->pattern = 0x3b;
                    } else if ((v108.flagsB0 & 1) != 0) {
                        p2->pattern = ((b1d0.flagsAA & 8) > 0) * 3 + 0x32 + ((b1d0.flagsAA & 0x10) > 0) + ((b1d0.flagsAA & 0x20) > 0) * 2;
                    } else if ((v108.flagsB0 & 2) != 0) {
                        p2->pattern = ((b1d0.flagsAA & 0x10) > 0) + 0x38 + ((b1d0.flagsAA & 0x20) > 0) * 2;
                    }
                } else if (b1d0.unkac > 0) {
                    p2->pattern = b1d0.unkac;
                } else {
                    p2->pattern = 0x3b;
                }
                p1->m_attackResult = 3;
                p2->StartPattern();
                p2->FaceOpponent();
            } else {
                p1->m_comboHits = 0;
                p2->Unk410ac0(0xdf, 3);
                p1->m_attackResult = 7;
            }
            if ((v108.flagsB0 & 0x10) > 0) {
                p1->m_comboHits = 0;
                if (p1->m_proration > 10000.0) {
                    p1->m_proration -= 20.0;
                } else {
                    p1->m_proration = 10000.0;
                }
            }
            p2->unkc0 = b1d0.unkb8;
            p2->unkc8 = b1d0.unkbc;
            p2->unkd0 = 1;
            if (p1->m_comboHits == 0) {
                p2->m_comboStartHp = p2->m_hp;
            }
            p1->unk144 = (b1d0.flagsAA & 0x2000) > 0 && (v108.flagsB0 & 0x2000) > 0;
            p2->m_hp -= (int)((double)b1d0.unka0 * p1->AttackFactor() * p2->DefenseFactor() * p1->ProrationFactor());
            p2->unk124 = (int)(b1d0.unkb2 * (p1->m_proration / 10000.0 * 0.8));
            p2->unk128 = (b1d0.flagsAA & 0x400) > 0;
            p2->unk12c = (b1d0.flagsAA & 0x800) > 0;
            p2->unk158 = 0;
            p2->unk159 = 0;
            p2->unk15a = 0;
            p1->m_shownProration = p1->m_proration / 100.0;
            p1->m_proration = b1d0.unka4 / 1e+03f * p1->m_proration;
            if (p1->m_proration > 10000.0) {
                p1->m_proration = b1d0.unka4 / 1e+03f * p1->m_proration;
            }
            p1->m_comboHits++;
            p1->m_shownHits = p1->m_comboHits;
            p1->m_comboTimer = 0xb4;
            p1->m_comboDamage = p2->m_comboStartHp - p2->m_hp;
            p1->m_gauge += b1d0.unkb4;
            p1->unk14a = b1d0.unkc2;
            p2->unk14a = b1d0.unkc4;
            p1->m_hitsLeft--;
            k2c0.unk0 = 0;
            k2c0.type = b1d0.unkc0;
            k2c0.x = (double)((v2d0.right + v2d0.left) / 2);
            k2c0.y = (double)((v2d0.bottom + v2d0.top) / 2);
            k2c0.side = p1->facing < 0;
            k2c0.scale = 2;
            k2c0.layer = 1;
            k2c0.screen = 0;
            k2c0.unk2c = b1d0.unkc1;
            m_game->CreateEffect((EffectDesc*)&k2c0);
            if (p2->m_hp <= 0 && p2->unk140 == 0) {
                p2->pattern = b1d0.unkac;
                p2->StartPattern();
                p2->FaceOpponent();
            }
            p1->Unk410790(&b1d0);
        }
    }
}

void CScene3::Unk7697d0(CPlayer* p1, CPlayer* p2, int p3, CollisionInfo* p4)
{
    RECT v11c;
    RECT l10c;
    int mfc;
    int vf8[4][5];
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
    if (k14->unk80 == 0 && (l4->frame.flagsB0 & 0x20) == 0 && k14->unk84 > 0 && (p2->unk130 <= 0 || (x8->flagsAA & 0x40) <= 0) && p2->Unk4102e0() == 0 && p2->unk13c == 0) {
        mfc = 0;
        v10 = 0;
        for (; v10 < 4; v10++) {
            a58[v10] = this->Unk767600((ObjBase*)k14, &x8->attackBoxes[v10]);
        }
        v10 = 0;
        for (; v10 < 5; v10++) {
            na8[v10] = this->Unk7677a0(p4, (RECT*)((v10 << 4) + (char*)l4));
        }
        v11c = this->Unk7677a0(p4, &l4->frame.box90);
        if ((x8->flagsAA & 0x40) > 0) {
            v10 = 0;
            for (; v10 < 4; v10++) {
                vf8[v10][0] = 1;
                mfc = Unk767930(&a58[v10], &v11c) | mfc;
            }
        } else {
            v10 = 0;
            for (; v10 < 4; v10++) {
                bc = 0;
                for (; bc < 5; bc++) {
                    vf8[v10][bc] = Unk767930(&a58[v10], &na8[bc]);
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
            if ((l4->frame.flagsB0 & 0x400) > 0 && (x8->flagsAA & 0x100) == 0) {
                k14->unk84--;
                k14->unk80 = 2;
                p1->m_attackResult = 6;
                p2->m_attackResult = 6;
                return;
            }
            if (p2->unk170 != 0 && p2->unk14e >= 0x1e && p2->unk13a == 0 && p2->Unk4100f0((PatternFrame*)x8) != 0 && (x8->flagsAA & 0x80) == 0) {
                k14->unk80 = 2;
                p1->m_gauge += x8->unkb6;
                k14->unk84--;
                p2->unkd0 = 1;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = 0x11;
                k168.unk2c = 0xa;
                m_game->CreateEffect((EffectDesc*)&k168);
                p2->StartPattern();
                p2->facing = -k14->facing;
                if (p2->y == 0.0) {
                    p2->pattern = (p2->m_inputY == 1) + 0xa8;
                } else {
                    p2->pattern = 0xaa;
                }
                p1->ClearInput();
                p2->ClearInput();
                p2->unk14c = 0x3c;
                p2->unk170 = 0;
                p1->unk170 = 1;
                return;
            }
            if (p2->unk14e >= 0x1e && p2->y < 0.0 && p2->Unk410050((PatternFrame*)x8, (PatternFrame*)l4) != 0) {
                k14->unk80 = 2;
                p1->m_gauge += x8->unkb6;
                k14->unk84--;
                p2->unkd0 = 1;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = 0x11;
                k168.unk2c = 0xa;
                m_game->CreateEffect((EffectDesc*)&k168);
                p2->StartPattern();
                p2->facing = -k14->facing;
                p2->pattern = 0xaa;
                p1->ClearInput();
                p2->ClearInput();
                p2->unk14c = 0x3c;
                p1->unk170 = 1;
                return;
            }
            if (p2->Unk410050((PatternFrame*)x8, (PatternFrame*)l4) != 0 && p2->unk14e >= 0x1e && p2->y == 0.0 && p2->pattern != 0xa8 && p2->pattern != 0xa9) {
                k14->unk80 = 2;
                p1->m_gauge += x8->unkb6;
                k14->unk84--;
                p2->unkd0 = 1;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = 0x11;
                k168.unk2c = 0xa;
                m_game->CreateEffect((EffectDesc*)&k168);
                p2->StartPattern();
                p2->facing = -k14->facing;
                p2->pattern = (p2->m_inputY == 1) + 0xa8;
                p1->ClearInput();
                p2->ClearInput();
                p2->unk14c = 0x3c;
                p1->unk170 = 1;
                return;
            }
            if ((l4->frame.flagsB0 & 0x200) > 0 && (l4->frame.flagsAA & 1) > 0 && (x8->flagsAA & 1) > 0) {
                k14->unk84--;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = 2;
                k168.unk2c = 3;
                m_game->CreateEffect((EffectDesc*)&k168);
                p1->m_attackResult = 2;
                p1->unk14a = x8->unkc2;
                p2->unk14a = x8->unkc4;
                p2->m_hp -= x8->unka8;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->unk134 = x8->unka0 / 0x1e + p2->unk134;
                if (p2->unk134 > 3.6e+02f) {
                    *(int*)&p2->unk134 = 0x43b40000;
                }
                return;
            }
            if ((l4->frame.flagsB0 & 0x200) > 0 && (l4->frame.flagsAA & 2) > 0 && (x8->flagsAA & 2) > 0) {
                k14->unk84--;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = 2;
                k168.unk2c = 3;
                m_game->CreateEffect((EffectDesc*)&k168);
                p1->m_attackResult = 2;
                p1->unk14a = x8->unkc2;
                p2->unk14a = x8->unkc4;
                p2->m_hp -= x8->unka8;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->unk134 = x8->unka0 / 0x1e + p2->unk134;
                if (p2->unk134 > 3.6e+02f) {
                    *(int*)&p2->unk134 = 0x43b40000;
                }
                return;
            }
            if ((l4->frame.flagsB0 & 0x200) > 0 && (l4->frame.flagsAA & 4) > 0 && (x8->flagsAA & 4) > 0 && p2->y < 0.0) {
                k14->unk84--;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p2->facing == -1;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                k168.type = 2;
                k168.unk2c = 3;
                m_game->CreateEffect((EffectDesc*)&k168);
                p1->m_attackResult = 2;
                p1->unk14a = x8->unkc2;
                p2->unk14a = x8->unkc4;
                p2->m_hp -= x8->unka8;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                p2->unk134 = x8->unka0 / 0x1e + p2->unk134;
                if (p2->unk134 > 3.6e+02f) {
                    *(int*)&p2->unk134 = 0x43b40000;
                }
                return;
            }
            if (p2->Unk410050((PatternFrame*)x8, (PatternFrame*)l4) != 0) {
                p2->pattern = (x8->flagsAA & 0x10) / 0x10 + 0x96 + (x8->flagsAA & 0x20) / 0x20 * 2 + (p2->m_inputY == 1 || (x8->flagsAA & l4->frame.flagsB0 & 5) == 0 && p2->m_cpu != 0) * 3;
                if (p2->y < 0.0) {
                    p2->pattern = 0x9c;
                }
                p2->StartPattern();
                p2->facing = -k14->facing;
                k14->unk80 = 2;
                k14->unk86 = x8->unkc2;
                p2->unk14a = x8->unkc4;
                p1->m_gauge += x8->unkb6;
                k14->unk84--;
                p2->unkd0 = 0;
                k168.unk0 = 0;
                k168.x = (double)((l10c.right + l10c.left) / 2);
                k168.y = (double)((l10c.bottom + l10c.top) / 2);
                k168.side = p1->facing < 0;
                k168.scale = 2;
                k168.layer = 1;
                k168.screen = 0;
                p2->m_hp -= x8->unka8;
                if (p2->m_hp <= 0) {
                    p2->m_hp = 1;
                }
                if (p1->unk134 > 0.0f) {
                    p1->unk134 = p1->unk134 - x8->unka0 / 0x1e;
                    if (p1->unk134 < 0.0f) {
                        p2->unk134 = p2->unk134 - p1->unk134;
                        *(int*)&p1->unk134 = 0;
                    }
                } else {
                    p2->unk134 = x8->unka0 / 0x1e + p2->unk134;
                    if (p2->unk134 > 3.6e+02f) {
                        *(int*)&p2->unk134 = 0x43b40000;
                    }
                }
                p2->unk154 = 1;
                k168.type = 2;
                k168.unk2c = 3;
                m_game->CreateEffect((EffectDesc*)&k168);
                return;
            }
            if ((l4->frame.flagsB0 & 4) == 0 && p2->unk138 == 0 || ((l4->frame.flagsB0 & 4) > 0 || p2->unk138 > 0) && (x8->flagsAA & 0x100) > 0 || (x8->flagsAA & 0x40) > 0) {
                if (p2->y >= 0.0) {
                    if (x8->unkae > 0) {
                        p2->pattern = x8->unkae;
                    } else if ((l4->frame.flagsB0 & 3) == 3) {
                        p2->pattern = 0x3b;
                    } else if ((l4->frame.flagsB0 & 1) != 0) {
                        p2->pattern = ((x8->flagsAA & 8) > 0) * 3 + 0x32 + ((x8->flagsAA & 0x10) > 0) + ((x8->flagsAA & 0x20) > 0) * 2;
                    } else if ((l4->frame.flagsB0 & 2) != 0) {
                        p2->pattern = ((x8->flagsAA & 0x10) > 0) + 0x38 + ((x8->flagsAA & 0x20) > 0) * 2;
                    }
                } else if (x8->unkac > 0) {
                    p2->pattern = x8->unkac;
                } else {
                    p2->pattern = 0x3b;
                }
                k14->unk80 = 3;
                p2->StartPattern();
                p2->facing = -k14->facing;
            } else {
                p1->m_comboHits = 0;
                p2->Unk410ac0(0xe9, 3);
                k14->unk80 = 7;
            }
            if ((l4->frame.flagsB0 & 0x10) > 0) {
                p1->m_comboHits = 0;
                if (p1->m_proration > 10000.0) {
                    p1->m_proration -= 20.0;
                } else {
                    p1->m_proration = 10000.0;
                }
            }
            p2->unkc0 = x8->unkb8;
            p2->unkc8 = x8->unkbc;
            p2->unkd0 = 0;
            if (p1->m_comboHits == 0) {
                p2->m_comboStartHp = p2->m_hp;
            }
            p2->m_hp -= (int)((double)x8->unka0 * p1->AttackFactor() * p2->DefenseFactor() * p1->ProrationFactor());
            p2->unk124 = (int)(x8->unkb2 * (p1->m_proration / 10000.0) * (((x8->flagsAA & 0x2000) > 0 && (l4->frame.flagsB0 & 0x2000) > 0) + 1));
            p2->unk128 = (x8->flagsAA & 0x400) > 0;
            p2->unk12c = (x8->flagsAA & 0x800) > 0;
            p2->unk158 = 0;
            p2->unk159 = 0;
            p2->unk15a = 0;
            p1->m_shownProration = p1->m_proration / 100.0;
            p1->m_proration = x8->unka4 / 1e+03f * p1->m_proration;
            if (p1->m_proration > 10000.0) {
                p1->m_proration = x8->unka4 / 1e+03f * p1->m_proration;
            }
            p1->m_comboHits++;
            p1->m_shownHits = p1->m_comboHits;
            p1->m_comboTimer = 0xb4;
            p1->m_comboDamage = p2->m_comboStartHp - p2->m_hp;
            p1->m_gauge += x8->unkb4;
            k14->unk86 = x8->unkc2;
            p2->unk14a = x8->unkc4;
            k14->unk84--;
            k168.unk0 = 0;
            k168.type = x8->unkc0;
            k168.x = (double)((l10c.right + l10c.left) / 2);
            k168.y = (double)((l10c.bottom + l10c.top) / 2);
            k168.side = p1->facing < 0;
            k168.scale = 2;
            k168.layer = 1;
            k168.screen = 0;
            k168.unk2c = x8->unkc1;
            m_game->CreateEffect((EffectDesc*)&k168);
            if (p2->m_hp <= 0 && p2->unk140 == 0) {
                p2->pattern = x8->unkac;
                p2->StartPattern();
                p2->FaceOpponent();
            }
            p1->Unk410790((PatternFrame*)x8);
        }
    }
}

void CScene3::Unk76b090(CPlayer* p1, CPlayer* p2, int p3, int p4)
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
    if (n10->unk80 == 0 && n10->unk84 > 0 && (x8->flagsAA & 0x40) == 0) {
        xfc = 0;
        v14 = 0;
        for (; v14 < 4; v14++) {
            n58[v14] = this->Unk767600((ObjBase*)n10, &x8->attackBoxes[v14]);
        }
        v14 = 0;
        for (; v14 < 5; v14++) {
            ea8[v14] = this->Unk767600((ObjBase*)l18, (RECT*)((v14 << 4) + (char*)l4));
        }
        v14 = 0;
        for (; v14 < 4; v14++) {
            rc = 0;
            for (; rc < 5; rc++) {
                xf8[v14][rc] = Unk767930(&n58[v14], &ea8[rc]);
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
            if ((l4->flagsB0 & 0x10) == 0) {
                n10->unk84--;
                n10->unk80 = 5;
            }
            l18->unk80 = 5;
            if ((l4->flagsB0 & 0x2000) > 0) {
                *l4 = p2->m_patterns[p2->pattern].frames[p2->frame];
                if ((l4->flagsB0 & 4) == 0 && p2->unk138 == 0 || ((l4->flagsB0 & 4) > 0 || p2->unk138 > 0) && (x8->flagsAA & 0x100) > 0 || (x8->flagsAA & 0x40) > 0) {
                    if (p2->y >= 0.0) {
                        if (x8->unkae > 0) {
                            p2->pattern = x8->unkae;
                        } else if ((l4->flagsB0 & 3) == 3) {
                            p2->pattern = 0x3b;
                        } else if ((l4->flagsB0 & 1) != 0) {
                            p2->pattern = ((x8->flagsAA & 8) > 0) * 3 + 0x32 + ((x8->flagsAA & 0x10) > 0) + ((x8->flagsAA & 0x20) > 0) * 2;
                        } else if ((l4->flagsB0 & 2) != 0) {
                            p2->pattern = ((x8->flagsAA & 0x10) > 0) + 0x38 + ((x8->flagsAA & 0x20) > 0) * 2;
                        }
                    } else if (x8->unkac > 0) {
                        p2->pattern = x8->unkac;
                    } else {
                        p2->pattern = 0x3b;
                    }
                    p2->StartPattern();
                    p2->FaceOpponent();
                } else {
                    p1->m_comboHits = 0;
                    p2->Unk410ac0(0xdf, 2);
                }
                if ((l4->flagsB0 & 0x10) > 0) {
                    p1->m_comboHits = 0;
                    if (p1->m_proration > 10000.0) {
                        p1->m_proration -= 20.0;
                    } else {
                        p1->m_proration = 10000.0;
                    }
                }
                p2->unkc0 = x8->unkb8;
                p2->unkc8 = x8->unkbc;
                p2->unkd0 = 1;
                if (p1->m_comboHits == 0) {
                    p2->m_comboStartHp = p2->m_hp;
                }
                p2->m_hp -= (int)((double)x8->unka0 * p1->AttackFactor() * p2->DefenseFactor() * p1->ProrationFactor());
                p2->unk124 = (int)(x8->unkb2 * (p1->m_proration / 10000.0 * 0.8));
                p2->unk128 = (x8->flagsAA & 0x400) > 0;
                p2->unk12c = (x8->flagsAA & 0x800) > 0;
                p2->unk158 = 0;
                p2->unk159 = 0;
                p2->unk15a = 0;
                p1->m_shownProration = p1->m_proration / 100.0;
                p1->m_proration = x8->unka4 / 1e+03f * p1->m_proration;
                if (p1->m_proration > 10000.0) {
                    p1->m_proration = x8->unka4 / 1e+03f * p1->m_proration;
                }
                p1->m_comboHits++;
                p1->m_shownHits = p1->m_comboHits;
                p1->m_comboTimer = 0xb4;
                p1->m_comboDamage = p2->m_comboStartHp - p2->m_hp;
                p1->m_gauge += x8->unkb4;
                p1->unk14a = x8->unkc2;
                p2->unk14a = x8->unkc4;
                if (p2->m_hp <= 0 && p2->unk140 == 0) {
                    p2->pattern = x8->unkac;
                    p2->StartPattern();
                    p2->FaceOpponent();
                }
                p1->Unk410790((PatternFrame*)x8);
            }
            EffectDesc v158;
            v158.unk0 = 0;
            v158.type = x8->unkc0;
            v158.x = (double)((x10c.right + x10c.left) / 2);
            v158.y = (double)((x10c.bottom + x10c.top) / 2);
            v158.side = p1->facing < 0;
            v158.scale = 2;
            v158.layer = 1;
            v158.screen = 0;
            v158.unk2c = x8->unkc1;
            m_game->CreateEffect((EffectDesc*)&v158);
        }
    }
}

void CScene3::Unk76bab0(CPlayer* p1, CPlayer* p2, int p3, int p4)
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
    if (vc->unk80 == 0 && l10->unk80 == 0 && vc->unk84 > 0 && l10->unk84 > 0 && p1->m_patterns[vc->pattern].unk0 > 0 && p2->m_patterns[l10->pattern].unk0 > 0) {
        v20 = this->Unk767600((ObjBase*)vc, (RECT*)(x8 + 0x90));
        v30 = this->Unk767600((ObjBase*)l10, (RECT*)(l4 + 0x90));
        if (Unk767930(&v20, &v30) != 0) {
            if (p2->m_patterns[l10->pattern].unk0 == p1->m_patterns[vc->pattern].unk0) {
                vc->unk80 = 4;
                l10->unk80 = 4;
            } else if (p2->m_patterns[l10->pattern].unk0 > p1->m_patterns[vc->pattern].unk0) {
                vc->unk80 = 4;
            } else if (p2->m_patterns[l10->pattern].unk0 < p1->m_patterns[vc->pattern].unk0) {
                l10->unk80 = 4;
            }
            if (p2->m_patterns[l10->pattern].unk0 > 1) {
                vc->unk84--;
            }
            if (p1->m_patterns[vc->pattern].unk0 > 1) {
                l10->unk84--;
            }
        }
    }
}

void CScene3::Unk76bd40(CPlayer* p1, CPlayer* p2, CollisionInfo* p3, CollisionInfo* p4, int p5)
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
    if (p1->m_attackResult == 0 && p1->m_hitsLeft > 0 && (l4->frame.flagsAA & 0x40) == 0) {
        n118 = p2->m_patterns[l10->pattern].frames[l10->frame];
        r1bc = 0;
        vc = 0;
        for (; vc < 4; vc++) {
            n50[vc] = this->Unk7677a0(p3, &l4->frame.attackBoxes[vc]);
        }
        vc = 0;
        for (; vc < 5; vc++) {
            v168[vc] = this->Unk767600((ObjBase*)l10, &n118.boxes[vc]);
        }
        vc = 0;
        for (; vc < 4; vc++) {
            x8 = 0;
            for (; x8 < 5; x8++) {
                k1b8[vc][x8] = Unk767930(&n50[vc], &v168[x8]);
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
            if ((n118.flagsB0 & 0x10) == 0) {
                p1->m_hitsLeft--;
                p1->m_attackResult = 5;
            }
            l10->unk80 = 5;
            if ((n118.flagsB0 & 0x2000) > 0) {
                n118 = p4->frame;
                if ((n118.flagsB0 & 4) == 0 && p2->unk138 == 0 || ((n118.flagsB0 & 4) > 0 || p2->unk138 > 0) && (l4->frame.flagsAA & 0x100) > 0 || (l4->frame.flagsAA & 0x40) > 0) {
                    if (p2->y >= 0.0) {
                        if (l4->frame.unkae > 0) {
                            p2->pattern = l4->frame.unkae;
                        } else if ((n118.flagsB0 & 3) == 3) {
                            p2->pattern = 0x3b;
                        } else if ((n118.flagsB0 & 1) != 0) {
                            p2->pattern = ((l4->frame.flagsAA & 8) > 0) * 3 + 0x32 + ((l4->frame.flagsAA & 0x10) > 0) + ((l4->frame.flagsAA & 0x20) > 0) * 2;
                        } else if ((n118.flagsB0 & 2) != 0) {
                            p2->pattern = ((l4->frame.flagsAA & 0x10) > 0) + 0x38 + ((l4->frame.flagsAA & 0x20) > 0) * 2;
                        }
                    } else if (l4->frame.unkac > 0) {
                        p2->pattern = l4->frame.unkac;
                    } else {
                        p2->pattern = 0x3b;
                    }
                    p2->StartPattern();
                    p2->FaceOpponent();
                } else {
                    p1->m_comboHits = 0;
                    p2->Unk410ac0(0xdf, 2);
                }
                if ((n118.flagsB0 & 0x10) > 0) {
                    p1->m_comboHits = 0;
                    if (p1->m_proration > 10000.0) {
                        p1->m_proration -= 20.0;
                    } else {
                        p1->m_proration = 10000.0;
                    }
                }
                p2->unkc0 = l4->frame.unkb8;
                p2->unkc8 = l4->frame.unkbc;
                p2->unkd0 = 1;
                if (p1->m_comboHits == 0) {
                    p2->m_comboStartHp = p2->m_hp;
                }
                p2->m_hp -= (int)((double)l4->frame.unka0 * p1->AttackFactor() * p2->DefenseFactor() * p1->ProrationFactor());
                p2->unk124 = (int)(l4->frame.unkb2 * (p1->m_proration / 10000.0 * 0.8));
                p2->unk128 = (l4->frame.flagsAA & 0x400) > 0;
                p2->unk12c = (l4->frame.flagsAA & 0x800) > 0;
                p2->unk158 = 0;
                p2->unk159 = 0;
                p2->unk15a = 0;
                p1->m_shownProration = p1->m_proration / 100.0;
                p1->m_proration = l4->frame.unka4 / 1e+03f * p1->m_proration;
                if (p1->m_proration > 10000.0) {
                    p1->m_proration = l4->frame.unka4 / 1e+03f * p1->m_proration;
                }
                p1->m_comboHits++;
                p1->m_shownHits = p1->m_comboHits;
                p1->m_comboTimer = 0xb4;
                p1->m_comboDamage = p2->m_comboStartHp - p2->m_hp;
                p1->m_gauge += l4->frame.unkb4;
                p1->unk14a = l4->frame.unkc2;
                p2->unk14a = l4->frame.unkc4;
                if (p2->m_hp <= 0 && p2->unk140 == 0) {
                    p2->pattern = l4->frame.unkac;
                    p2->StartPattern();
                    p2->FaceOpponent();
                }
                p1->Unk410790((PatternFrame*)l4);
            }
            EffectDesc n218;
            n218.unk0 = 0;
            n218.type = l4->frame.unkc0;
            n218.x = (double)((b1cc.right + b1cc.left) / 2);
            n218.y = (double)((b1cc.bottom + b1cc.top) / 2);
            n218.side = p1->facing < 0;
            n218.scale = 2;
            n218.layer = 1;
            n218.screen = 0;
            n218.unk2c = l4->frame.unkc1;
            m_game->CreateEffect((EffectDesc*)&n218);
        }
    }
}
