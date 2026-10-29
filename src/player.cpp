// Sixth object of efz.exe (0x40e630-0x412b0f): CPlayer, the base of the character
// classes. Movement and facing, guard and damage, the per-character .pal/.dat/.pat/.wav
// loaders and the state reset at the start of a round. The inline methods of
// PatternData and Afterimages it uses follow it (0x412820-0x412b0f), with
// FUNCTION: 0x412870 ??_EPatternData@@QAEPAXI@Z
//   PatternData's vector deleting destructor, for `delete[]` in ~CPlayer
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

int CPlayer::FaceOpponent()
{
    char v1;

    v1 = facing;
    if (x < (*m_opponent)->x) {
        facing = 1;
        return facing != v1;
    }
    if (x > (*m_opponent)->x) {
        facing = -1;
        return facing != v1;
    }
    return 0;
}

int CPlayer::FaceX(double p1)
{
    char v1;

    v1 = facing;
    if (x < p1) {
        facing = 1;
        return facing != v1;
    }
    if (x > p1) {
        facing = -1;
        return facing != v1;
    }
    return 0;
}

void CPlayer::Unk40e740()
{
    if (y == 0.0) {
        unk159 = 0;
        unk15a = 0;
    }
    if (y >= 0.0 && pattern != 4 && pattern != 5 && pattern != 6 && pattern != 0xa && pattern != 0xb && pattern != 0xc) {
        if (unk15c < 3 && m_inputY == -1) {
            FaceOpponent();
            if (m_command >= 3 && m_command <= 5) {
                if (m_command == 3) {
                    if (pattern != 0xa) {
                        StartPattern();
                    }
                    pattern = 0xa;
                    return;
                }
                if (m_command == 4) {
                    if (pattern != 0xb) {
                        StartPattern();
                    }
                    pattern = 0xb;
                    return;
                }
                if (m_command == 5) {
                    if (pattern != 0xc) {
                        StartPattern();
                    }
                    pattern = 0xc;
                    return;
                }
            } else {
                if (m_inputX == 0) {
                    if (pattern != 4) {
                        StartPattern();
                    }
                    pattern = 4;
                    return;
                }
                if (m_inputX == facing) {
                    if (pattern != 5) {
                        StartPattern();
                    }
                    pattern = 5;
                    return;
                }
                if (m_inputX == -facing) {
                    if (pattern != 6) {
                        StartPattern();
                    }
                    pattern = 6;
                    return;
                }
            }
        }
        if (m_inputY == 1) {
            if (pattern != 8 && pattern != 3) {
                pattern = 8;
                StartPattern();
                FaceOpponent();
                return;
            }
            if (pattern != 8) {
                pattern = 3;
                FaceOpponent();
                return;
            }
            return;
        }
        if (m_inputX != 0) {
            FaceOpponent();
            if (m_inputX == facing) {
                if (pattern != 1) {
                    StartPattern();
                }
                pattern = 1;
                return;
            }
            if (pattern != 2) {
                StartPattern();
            }
            pattern = 2;
            return;
        }
        if (pattern == 3 || pattern == 8) {
            pattern = 7;
            FaceOpponent();
            StartPattern();
            return;
        }
        if (pattern == 7 || pattern == 0xd) {
            FaceOpponent();
            return;
        }
        if (pattern != 0) {
            StartPattern();
        }
        pattern = 0;
        FaceOpponent();
    }
}

CPlayer::CPlayer(CPlayer** p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : m_opponent(p1)
{
    int v4;

    m_game = p2;
    m_graphics = p3;
    m_input = p4;
    m_sound = p5;
    m_side = p6;
    m_charId = 0;
    m_paletteIndex = 0;
    v4 = 0;
    for (; v4 < 0x32; v4++) {
        m_voices[v4] = 0x96;
    }
    v4 = 0;
    for (; v4 < 0x14; v4++) {
        m_rivals[v4] = -1;
    }
    surfaces = (IDirectDrawSurface**)0;
    anims = new EffectAnim[0x1f9];
    m_patterns = new PatternData[0x1f9];
    m_score = 0;
    m_scoreHigh = 0;
    m_hitsLanded = 0;
    m_maxHits = 0;
    m_maxDamage = 0;
    unk30e8 = 0;
}

CPlayer::~CPlayer()
{
    int v4;

    if ((int)surfaces != 0) {
        v4 = 0;
        for (; v4 < lastSurface + 1; v4++) {
            if ((int)surfaces[v4] != 0) {
                surfaces[v4]->Release();
                surfaces[v4] = (IDirectDrawSurface*)0;
            }
        }
        delete (char*)surfaces;
    }
    v4 = 0;
    for (; v4 < 0x32; v4++) {
        if ((unsigned short)m_voices[v4] != 0x96) {
            m_sound->Release(m_voices[v4]);
        }
    }
    delete[] anims;
    delete[] m_patterns;
}

void CPlayer::Reset()
{
    int v4;

    x = m_side * 0xa0 + 0xf0;
    y = 0.0;
    facing = 1 - (m_side << 1);
    StopMoving();
    unkb0 = 0.0;
    unkd0 = 0;
    pattern = 0;
    frame = 0;
    timer = 0;
    m_tintTime = 0;
    m_fillTime = 0;
    m_hp = 0x270f;
    m_comboStartHp = 0x270f;
    unk110 = 0x270f;
    m_gauge = 0;
    unk118 = 0.0;
    unk120 = 0;
    unk14c = 0;
    unk159 = 0;
    unk158 = 0;
    unk15a = 0;
    unk14e = 0;
    unk150 = 0;
    unkac = 0;
    unk138 = 0;
    unk13a = 0;
    unk13c = 0;
    unk13e = 0;
    unk140 = 0;
    unk15c = 0;
    unk160 = 0;
    m_attackResult = 0;
    unk14a = 0;
    *(int*)&unk134 = 0;
    m_comboHits = 0;
    m_shownHits = 0;
    m_comboTimer = 0;
    m_proration = 10000.0;
    m_shownProration = 10000.0;
    unk170 = 0;
    m_defense = 1.0;
    m_bufferedPress = 0;
    m_dashBufferedPress = 0;
    m_command = 0x63;
    m_inputPos = 0;
    v4 = 0;
    for (; v4 < 0xb4; v4++) {
        m_inputHistory[v4] = 0;
    }
    m_playVoice = -1;
    m_playSound = -1;
    m_objectHead = 0;
    m_objectTail = 0;
    ClearObjects();
    m_afterimages.pos = 0;
    m_afterimages.unk0 = 0;
    m_afterimages.unk2 = 0;
    unk30f0 = 0;
    unk30ec = 0;
    unk58 = 0;
    unk60 = 1;
    unk30dc = 0;
    m_maxHits = 0;
    m_maxDamage = 0;
}

void CPlayer::StartPattern()
{
    frame = 0;
    timer = 0;
    unkb8 = 0.0;
    m_attackResult = 0;
    unk170 = 0;
    m_afterimages.Unk412910();
}

void CPlayer::ClearBufferedPress()
{
    m_bufferedPress = 0;
    m_dashBufferedPress = 0;
}

void CPlayer::ClearInput()
{
    int v4;

    v4 = 0;
    for (; v4 < 0xb4; v4++) {
        m_inputHistory[v4] = 0;
    }
    m_command = 0x63;
}

void CPlayer::StopMoving()
{
    vx = 0.0;
    vy = 0.0;
    ax = 0.0;
    ay = 0.0;
    unkb8 = 0.0;
}

void CPlayer::Unk40f230()
{
    if (unk14a == 0 && (*m_opponent)->unk14c == 0) {
        if (pattern < 0x32 || pattern > 0x96 || pattern == 0x60) {
            unk124 = 0;
            unk12c = 0;
            (*m_opponent)->m_comboHits = 0;
            if ((*m_opponent)->m_proration > 10000.0) {
                (*m_opponent)->m_proration -= 20.0;
            } else {
                (*m_opponent)->m_proration = 10000.0;
            }
        }
        if (pattern < 0x32) {
            Move();
            unkb8 = 0.0;
            (*m_opponent)->unkb8 = 0.0;
            if (unk30ec != 0 && (*m_opponent)->pattern < 0x32) {
                m_gauge = 0xbb8;
                m_hp = unk30ee;
                if (unk30ec > 0) {
                    if (unk30ec < 0x3e8) {
                        unk118 = unk30ec;
                        unk120 = 0;
                    } else {
                        unk118 = 0x7d0 - unk30ec;
                        unk120 = 1;
                    }
                }
            }
        }
        if (pattern >= 0x32 && pattern < 0x96 && unk134 <= 0.0f && (m_patterns[pattern].frames[frame].flagsAA & 0x400) == 0) {
            Unk40f470();
        }
        StartCommand();
    }
}

void CPlayer::Unk40f470()
{
    if (unk124 > 0) {
        unk124--;
        return;
    }
    if (y < 0.0 && unk128 == 0 && (m_pressA != 0 || m_pressB != 0 || m_pressC != 0 || m_pressD != 0)) {
        if (m_inputX == facing) {
            if (pattern != 0x9d) {
                StartPattern();
            }
            pattern = 0x9d;
            return;
        }
        if (m_inputX == -facing) {
            if (pattern != 0x9e) {
                StartPattern();
            }
            pattern = 0x9e;
        }
    }
}

void CPlayer::Unk40f580()
{
    int v4;

    v4 = m_objectTail;
    if (unk14a == 0 && (*m_opponent)->unk14c == 0) {
        if ((char)Unk40ff70() * facing * (vx + unkb0 + (*m_opponent)->unkb8 * ((*m_opponent)->unkd0 != 0 && unk14c == 0)) >= 0.0) {
            x = (vx + unkb0 + (*m_opponent)->unkb8 * ((*m_opponent)->unkd0 != 0 && unk14c == 0)) * facing + x;
        }
        if (((char)(*m_opponent)->Unk40ff70() == 1 && (*m_opponent)->x <= 20.0) + 0x14 > x) {
            x = ((char)(*m_opponent)->Unk40ff70() == 1 && (*m_opponent)->x <= 20.0) + 0x14;
        } else if (0x26b - ((char)(*m_opponent)->Unk40ff70() == -1 && (*m_opponent)->x >= 619.0) < x) {
            x = 0x26b - ((char)(*m_opponent)->Unk40ff70() == -1 && (*m_opponent)->x >= 619.0);
        }
        y = y + vy;
        if (y > 0.0) {
            y = 0.0;
        }
    }
    while (v4 != m_objectHead) {
        if (m_objectActive[v4] != 0 && (unk14c <= 0 || m_objects[v4].unk88 != 0) && m_objects[v4].unk86 == 0 && (*m_opponent)->unk14c == 0) {
            m_objects[v4].x += (m_objects[v4].vx + 0.0 * m_objects[v4].unk70) * m_objects[v4].facing;
            m_objects[v4].y = m_objects[v4].y + m_objects[v4].vy;
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}

void CPlayer::Unk40f980()
{
    int v4;

    if ((*m_opponent)->unk14c > 0) {
    } else {
        if (unk14a > 0) {
            unk14a--;
        } else {
            unk14a = 0;
        }
        if (Unk410340() == 0) {
            if (Unk4103a0() != 0) {
                unk134 = unk134 - (float)(1.0 / ((y == 0.0) * 4 + 1));
            } else {
                unk134 -= 0.075f;
            }
            if (unk134 < 0.0f) {
                *(int*)&unk134 = 0;
            }
        }
        if (unk130 > 0) {
            unk130--;
        } else {
            unk130 = 0;
        }
        if ((m_patterns[pattern].frames[frame].flagsB0 & 0x40) > 0) {
            unk130 = 0x1b;
        }
        if (unk138 > 0) {
            unk138--;
        } else {
            unk138 = 0;
        }
        if (unk13a > 0) {
            unk13a--;
        } else {
            unk13a = 0;
        }
        if (unk13c > 0) {
            unk13c--;
        } else {
            unk13c = 0;
        }
        if (unk13e > 0) {
            unk13e--;
        } else {
            unk13e = 0;
        }
        if (unk140 > 0) {
            unk140--;
        } else {
            unk140 = 0;
        }
        unk118 = (Unk410340() + 1) * (Unk4103a0() == 0 && unk120 == 0) * ((unk118 < 500.0) * 2 + 1) / 10.0 + unk118;
        if (unk118 >= 1000.0 && unk120 == 0) {
            unk120 = 1;
            unk118 = 1000.0;
        } else if (unk118 <= 0.0) {
            unk120 = 0;
            unk118 = 0.0;
        }
        v4 = m_objectTail;
        while (v4 != m_objectHead) {
            if (m_objectActive[v4] != 0) {
                if (m_objects[v4].unk86 > 0) {
                    m_objects[v4].unk86--;
                } else {
                    m_objects[v4].unk86 = 0;
                }
            }
            v4++;
            if (v4 >= 0x40) {
                v4 = 0;
            }
        }
        if ((*m_opponent)->Unk4103a0() != 0) {
            unk30e4 = 0x384;
            unk30e0 = 0xc;
        }
        if (((*m_opponent)->pattern < 0x32 || (*m_opponent)->pattern >= 0xc8) && m_game->unk1350 == 0 && m_game->unk1354 == 0) {
            if ((unsigned long)unk30e4 > 0) {
                unk30e4--;
            } else {
                if ((unsigned long)unk30e0 > 1) {
                    unk30e0--;
                }
                if ((unsigned long)m_hitsLanded > 0) {
                    m_hitsLanded--;
                }
                unk30e4 = unk30e0 * 5 * 3;
            }
        }
    }
    if (m_gauge < 0) {
        m_gauge = 0;
    } else if (m_gauge > 0xbb8) {
        m_gauge = 0xbb8;
    }
    if (unk118 < 0.0) {
        unk118 = 0.0;
    } else if (unk118 > 1000.0) {
        unk118 = 1000.0;
    }
    unk30f0--;
    if (unk30f0 <= 0) {
        unk30f0 = 0x3138;
    }
    if (m_comboTimer > 0 && m_comboHits == 0) {
        m_comboTimer--;
    }
}

char CPlayer::Unk40ff70()
{
    if (x - 20.0 <= ((*m_opponent)->x <= 20.0) || (*m_opponent)->x - x > 280.0) {
        return 1;
    }
    if (x + 20.0 >= 0x27f - ((*m_opponent)->x >= 619.0) || x - (*m_opponent)->x > 280.0) {
        return -1;
    }
    return 0;
}

int CPlayer::Unk410050(PatternFrame* p1, PatternFrame* p2)
{
    if (unk13a > 0) {
        return 0;
    }
    if ((p1->flagsAA & 0x80) > 0) {
        return 0;
    }
    if ((p2->flagsB0 & 0x10) == 0) {
        return 0;
    }
    if ((p1->flagsAA & 4) == 0 && y < 0.0 && unk14e < 0x1e) {
        return 0;
    }
    if (Unk4100f0(p1) == 0) {
        return 0;
    }
    return 1;
}

int CPlayer::Unk4100f0(PatternFrame* p1)
{
    if (m_cpu != 0) {
        if (m_game->unk1364 == 1) {
            if (m_game->unk1348 == 0) {
                return 0;
            }
        } else {
            if (rand() > unka8 * 1e+04f) {
                return 0;
            }
            if ((p1->flagsAA & 1) == 0) {
                m_inputY = 1;
            } else if ((p1->flagsAA & 2) == 0) {
                m_inputY = 0;
            }
        }
        if ((p1->flagsAA & 2) == 0 && m_inputY == 1 && y == 0.0 || (p1->flagsAA & 1) == 0 && m_inputY != 1 && y == 0.0) {
            return 0;
        }
    } else {
        if (m_inputX != 1 - (((*m_opponent)->x - x > 0.0) << 1) && (Unk410340() == 0 || m_inputX == 0)) {
            return 0;
        }
        if ((p1->flagsAA & 2) == 0 && m_inputY == 1 && y == 0.0 || (p1->flagsAA & 1) == 0 && m_inputY != 1 && y == 0.0) {
            return 0;
        }
    }
    return 1;
}

int CPlayer::Unk4102e0()
{
    return unk124 <= 0 && y < 0.0 && unk128 == 0 && Unk4103a0() != 0;
}

int CPlayer::Unk410340()
{
    return pattern >= 0x96 && pattern <= 0x9c || pattern >= 0xa8 && pattern <= 0xab;
}

int CPlayer::Unk4103a0()
{
    return pattern >= 0x32 && pattern < 0x96 && (*m_opponent)->pattern != 0x61 && (*m_opponent)->pattern != 0x62 && (*m_opponent)->pattern != 0x63 && (*m_opponent)->pattern != 0x60;
}

int CPlayer::Unk410420()
{
    return pattern == 0xa3 || pattern == 0xa4 || pattern == 0xa5 || pattern == 0xa6;
}

double CPlayer::AttackFactor()
{
    if (m_game->unk1364 == 2) {
        return unk118 / 10000.0 + 1.0;
    }
    if (m_game->unk1370 == 1) {
        return (unk118 / 10000.0 + 1.0) / 2.0;
    }
    if (m_game->unk1370 == 2) {
        return unk118 / 10000.0 + 1.0;
    }
    return (unk118 / 10000.0 + 1.0) * 2;
}

double CPlayer::DefenseFactor()
{
    return (m_hp * 0.5 / 10000.0 + 0.5) * m_defense;
}

double CPlayer::ProrationFactor()
{
    if (m_proration / 10000.0 > 1.0) {
        return 1.0;
    }
    return m_proration / 10000.0;
}

void CPlayer::DealDamage(int p1, double p2)
{
    if (m_comboHits == 0) {
        (*m_opponent)->m_comboStartHp = (*m_opponent)->m_hp;
    }
    (*m_opponent)->m_hp -= (int)((double)p1 * this->AttackFactor() * (*m_opponent)->DefenseFactor() * this->ProrationFactor());
    m_shownProration = m_proration / 100.0;
    m_proration = p2 / 1000.0 * m_proration;
    if (m_proration > 10000.0) {
        m_proration = p2 / 1000.0 * m_proration;
    }
    m_comboHits++;
    m_shownHits = m_comboHits;
    m_comboTimer = 0xb4;
    m_comboDamage = (*m_opponent)->m_comboStartHp - (*m_opponent)->m_hp;
    if ((DWORD)m_comboHits > m_maxHits) {
        m_maxHits = m_comboHits;
    }
    if ((unsigned long)m_comboDamage > m_maxDamage) {
        m_maxDamage = m_comboDamage;
    }
    m_hitsLanded++;
    AddScore(p1 / 0x64 * m_hitsLanded * m_maxHits * m_comboHits);
}

void CPlayer::Unk410790(PatternFrame* p1)
{
    if ((DWORD)m_comboHits > m_maxHits) {
        m_maxHits = m_comboHits;
    }
    if ((unsigned long)m_comboDamage > m_maxDamage) {
        m_maxDamage = m_comboDamage;
    }
    m_hitsLanded++;
    AddScore(p1->unka0 / 0x64 * m_hitsLanded * m_maxHits * m_comboHits);
}

void CPlayer::AddScore(int p1)
{
    m_score += p1;
    while ((unsigned long)m_score >= 0x5f5e100) {
        m_score -= 0x5f5e100;
        m_scoreHigh++;
    }
}

short CPlayer::Random(short p1, short p2)
{
    WORD v8;
    short v4;

    v8 = rand();
    if (m_game->m_replayMode == 1) {
        v8 = m_game->m_replay.Read();
    } else if (m_game->m_replayMode == 2) {
        m_game->m_replay.Write(v8);
    }
    v4 = p1 + (p2 - p1) * v8 / 0x8000;
    return v4;
}

void CPlayer::Unk410940()
{
    if ((*m_opponent)->unk14c == 0) {
        if (m_afterimages.unk0 > 0) {
            m_afterimages.Unk412930((ObjBase*)this);
            m_afterimages.unk2 = 0;
            return;
        }
        if (m_afterimages.unk2 > 0) {
            m_afterimages.unk2--;
        }
    }
}

void CPlayer::StartAfterimages(BYTE p1)
{
    m_afterimages.Unk412a10((ObjBase*)this, p1);
}

void CPlayer::ShakeScreen(int p1, int p2)
{
    m_game->m_shake = p1;
    m_game->m_shakeHold = p2;
}

void CPlayer::Unk410a40(int p1, int p2)
{
    m_game->unk14238 = (1 - (m_side << 1)) * p1;
    m_game->unk14240 = p2;
}

void CPlayer::Unk410a80(int p1, int p2)
{
    m_game->unk1423c = (1 - (m_side << 1)) * p1;
    m_game->unk14244 = p2;
}

void CPlayer::Tint(BYTE p1, int p2)
{
    m_tintColor = p1;
    m_tintTime = p2;
    if (m_game->unk136c == 0) {
        m_tintTime = m_tintTime / 2;
    }
}

void CPlayer::FillBackground(BYTE p1, int p2)
{
    m_fillColor = p1;
    m_fillTime = p2;
    if (m_game->unk136c == 0) {
        m_fillTime = m_fillTime / 2;
    }
    m_game->m_fillSide = m_side;
}

void CPlayer::Load()
{
    char v2c[32];
    char vc[8];

    if (unk30e8 == 0) {
        LoadSprites();
        LoadPatterns();
        LoadVoices();
        unk30e8 = 1;
    } else if (1) {
        if (m_game->unk1338[m_side] != 0) {
            strcpy(v2c, m_name);
            strcat(v2c, "\\");
            strcat(v2c, m_name);
            _itoa(m_paletteIndex + 1, vc, 0xa);
            strcat(v2c, (const char*)vc);
            strcat(v2c, ".pal");
            if (m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v2c, 0, m_side * 0x28 + 0x5f, 0x28) == 0) {
                strcpy(v2c, m_name);
                strcat(v2c, "\\");
                strcat(v2c, m_name);
                strcat(v2c, ".dat");
                m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
            }
        } else {
            strcpy(v2c, m_name);
            strcat(v2c, "\\");
            strcat(v2c, m_name);
            strcat(v2c, ".dat");
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
        }
    } else if (m_game->unk1338[m_side] != 0) {
        strcpy(v2c, m_name);
        strcat(v2c, "\\");
        strcat(v2c, m_name);
        _itoa(m_paletteIndex + 1, vc, 0xa);
        strcat(v2c, (const char*)vc);
        strcat(v2c, ".pal");
        if (m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)v2c, 0, m_side * 0x28 + 0x5f, 0x28) == 0) {
            strcpy(v2c, m_name);
            strcat(v2c, "\\000.bmp");
            m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)v2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
        }
    } else {
        strcpy(v2c, m_name);
        strcat(v2c, "\\000.bmp");
        m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)v2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
    }
    Reset();
    if (m_cpu == 0) {
        if ((m_game->unk1364 == 0 || m_game->unk1364 == 2) && m_game->unk1358 == 1) {
            ((CharRecord*)&unk3118)->Load(m_name);
            unk3118++;
            ((CharRecord*)&unk3118)->Save(m_name);
            return;
        }
        if (m_game->unk1364 == 1 || m_game->unk1364 == 3 || m_game->unk1364 == 4) {
            ((CharRecord*)&unk3118)->Load(m_name);
            unk3118++;
            ((CharRecord*)&unk3118)->Save(m_name);
        }
    }
}

void CPlayer::LoadSprites()
{
    int x74;
    int v70;
    int a6c;
    char v68[32];
    int l48;
    char* x44;
    int v40;
    int h3c;
    int n38;
    int a34;
    int d30;
    char x2c[32];
    char bc[8];

    v70 = (int)operator new(lastSurface * 4 + 4);
    surfaces = (IDirectDrawSurface**)v70;
    if (1) {
        n38 = 0;
        strcpy(x2c, m_name);
        strcat(x2c, "\\");
        strcat(x2c, m_name);
        strcat(x2c, ".dat");
        d30 = (int)CreateFileA((LPCSTR)x2c, 0x80000000, 0, 0, 3, 0x80, 0);
        h3c = GetFileSize((HANDLE)d30, 0);
        x74 = (int)operator new(h3c);
        x44 = (char*)x74;
        ReadFile((HANDLE)d30, (LPVOID)x44, h3c, (LPDWORD)&v40, 0);
        n38 = *(BYTE*)x44 * 3 + 1;
        l48 = 0;
        for (; l48 <= lastSurface; l48++) {
            a34 = m_graphics->LoadSurfaceHigh(&surfaces[l48], (BYTE*)(x44 + n38), 0x80, m_side * 0x28 + 0x5f);
            if (a34 == 0) {
                _itoa(l48, v68, 0xa);
                MessageBoxA(0, (LPCSTR)v68, 0, 0);
            } else {
                n38 += a34;
            }
        }
        CloseHandle((HANDLE)d30);
        delete (char*)x44;
        if (m_game->unk1338[m_side] != 0) {
            strcpy(x2c, m_name);
            strcat(x2c, "\\");
            strcat(x2c, m_name);
            _itoa(m_paletteIndex + 1, bc, 0xa);
            strcat(x2c, (const char*)bc);
            strcat(x2c, ".pal");
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)x2c, 0, m_side * 0x28 + 0x5f, 0x28);
        } else {
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)x2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
        }
    } else {
        a6c = 0;
        for (; a6c <= lastSurface; a6c++) {
            strcpy(x2c, m_name);
            strcat(x2c, "\\");
            if (a6c >= 0x3e8) {
                strcat(x2c, "A");
                _itoa(a6c, bc, 0xa);
                strcat(x2c, (const char*)bc);
                strcat(x2c, ".bmp");
                m_graphics->LoadBmpHigh(&surfaces[a6c], (const char*)x2c, m_side * 0x28 + 0x5f);
            } else {
                if (a6c < 0x64) {
                    strcat(x2c, "0");
                }
                if (a6c < 0xa) {
                    strcat(x2c, "0");
                }
                _itoa(a6c, bc, 0xa);
                strcat(x2c, (const char*)bc);
                strcat(x2c, ".bmp");
                m_graphics->LoadBmpHigh(&surfaces[a6c], (const char*)x2c, m_side * 0x28 + 0x5f);
            }
        }
        if (m_game->unk1338[m_side] != 0) {
            strcpy(x2c, m_name);
            strcat(x2c, "\\");
            strcat(x2c, m_name);
            _itoa(m_paletteIndex + 1, bc, 0xa);
            strcat(x2c, (const char*)bc);
            strcat(x2c, ".pal");
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)x2c, 0, m_side * 0x28 + 0x5f, 0x28);
        } else {
            strcpy(x2c, m_name);
            strcat(x2c, "\\000.bmp");
            m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)x2c, m_paletteIndex * 0x28, m_side * 0x28 + 0x5f, 0x28);
        }
    }
    colorKey = m_graphics->GetColorKey(*surfaces);
}

void CPlayer::LoadPatterns()
{
    int c50;
    PatternFrame* l4c;
    EffectFrame* l48;
    int x44;
    int v40;
    int f3c;
    int x38;
    char x34[32];
    int l4;

    strcpy(x34, m_name);
    strcat(x34, "\\");
    strcat(x34, m_name);
    strcat(x34, ".pat");
    CFile k10(x34, 1);
    l4 = k10.ReadInt();
    v40 = 0;
    for (; v40 < l4; v40++) {
        x38 = k10.ReadInt();
        m_patterns[x38].unk0 = k10.ReadInt();
        m_patterns[x38].unk2 = k10.ReadInt();
        anims[x38].frameCount = k10.ReadInt();
        f3c = anims[x38].frameCount;
        m_patterns[x38].Alloc(f3c);
        anims[x38].Alloc(f3c);
        x44 = 0;
        for (; x44 < f3c; x44++) {
            l48 = &anims[x38].frames[x44];
            l4c = &m_patterns[x38].frames[x44];
            l48->duration = (short)k10.ReadInt() * 3;
            l48->surface = k10.ReadInt();
            l48->width = k10.ReadInt();
            l48->height = k10.ReadInt();
            l48->x = k10.ReadInt();
            l48->y = k10.ReadInt();
            l4c->unka0 = k10.ReadInt();
            l4c->flagsAA = k10.ReadInt();
            l4c->unkac = k10.ReadInt();
            l4c->flagsB0 = k10.ReadInt();
            l4c->unkb2 = k10.ReadInt();
            l4c->unka8 = k10.ReadInt();
            l4c->unkb4 = k10.ReadInt();
            l4c->unkb6 = k10.ReadInt();
            l4c->unkbc = (short)k10.ReadShort();
            l4c->unkbc = l4c->unkbc / 1e+02f;
            l4c->unkb8 = (short)k10.ReadShort();
            l4c->unkb8 = l4c->unkb8 / -1e+02f;
            l4c->unkc1 = k10.ReadShort();
            l4c->unkc0 = k10.ReadShort();
            l4c->unkc2 = k10.ReadInt();
            l4c->unkc4 = k10.ReadInt();
            l4c->unka4 = k10.ReadInt();
            l4c->unkae = k10.ReadInt();
            k10.Read((void*)&l4c->box90.left, 0x10);
            c50 = 0;
            for (; c50 < 2; c50++) {
                k10.Read((void*)((c50 << 4) + (char*)l4c), 0x10);
            }
            k10.Read((void*)&l4c->attackBoxes[0].left, 0x10);
            c50 = 2;
            for (; c50 < 5; c50++) {
                k10.Read((void*)((c50 << 4) + (char*)l4c), 0x10);
            }
            c50 = 1;
            for (; c50 < 4; c50++) {
                k10.Read((void*)&l4c->attackBoxes[c50].left, 0x10);
            }
        }
    }
    v40 = 0;
    for (; v40 < 0x40; v40++) {
        m_objects[v40].anims = anims;
    }
}

void CPlayer::LoadVoices()
{
    int v30;
    char v2c[32];
    char vc[8];

    v30 = 0;
    for (; v30 < 0x32; v30++) {
        strcpy(v2c, m_name);
        strcat(v2c, "\\wave\\");
        if (v30 < 0xa) {
            strcat(v2c, "0");
        }
        _itoa(v30, vc, 0xa);
        strcat(v2c, (const char*)vc);
        strcat(v2c, ".wav");
        m_voices[v30] = m_sound->Load((const char*)v2c);
        m_sound->SetVolume(m_voices[v30], -0x1f4);
    }
}

void CPlayer::ReadInput()
{
    BYTE v1;

    if (m_cpu != 0) {
        if (m_game->unk1364 == 1) {
            m_pressA = 0;
            m_pressB = 0;
            m_pressC = 0;
            m_pressD = 0;
            m_inputX = 0;
            if ((char)m_game->unk1346 == 1) {
                m_inputY = -1;
            } else if ((char)m_game->unk1346 == 2) {
                m_inputY = 1;
            } else {
                m_inputY = 0;
            }
            return;
        }
        CpuInput();
        if (m_game->unk1350 != 0 || m_game->unk1354 != 0) {
            m_pressA = 0;
            m_pressB = 0;
            m_pressC = 0;
            m_pressD = 0;
            m_command = 0x63;
        }
        return;
    }
    v1 = m_input->GetInput(m_side);
    if (m_game->m_replayMode == 1) {
        v1 = m_game->m_replay.Read();
    } else if (m_game->m_replayMode == 2) {
        m_game->m_replay.Write(v1);
    }
    m_inputX = 0;
    m_inputY = 0;
    m_pressA = 0;
    m_pressB = 0;
    m_pressC = 0;
    m_pressD = 0;
    if ((v1 & 8) > 0) {
        m_inputY = -1;
    } else if ((v1 & 4) > 0) {
        m_inputY = 1;
    }
    if (facing > 0) {
        if ((v1 & 2) > 0) {
            m_inputX = -1;
        } else if ((v1 & 1) > 0) {
            m_inputX = 1;
        }
    } else if ((v1 & 1) > 0) {
        m_inputX = 1;
    } else if ((v1 & 2) > 0) {
        m_inputX = -1;
    }
    if ((v1 & 0x10) > 0) {
        m_pressA = m_holdA == 0;
        m_holdA = 1;
    } else {
        m_holdA = 0;
    }
    if ((v1 & 0x20) > 0) {
        m_pressB = m_holdB == 0;
        m_holdB = 1;
    } else {
        m_holdB = 0;
    }
    if ((v1 & 0x40) > 0) {
        m_pressC = m_holdC == 0;
        m_holdC = 1;
    } else {
        m_holdC = 0;
    }
    if ((v1 & 0x80) > 0) {
        m_pressD = m_holdD == 0;
        m_holdD = 1;
    } else {
        m_holdD = 0;
    }
    if (m_game->unk1350 != 0 || m_game->unk1354 != 0) {
        m_pressA = 0;
        m_pressB = 0;
        m_pressC = 0;
        m_pressD = 0;
        m_command = 0x63;
    }
    m_inputHistory[m_inputPos] = (m_inputX == 1) + (m_inputX == -1) * 2 + (m_inputY == 1) * 4 + (m_inputY == -1) * 8 + (m_pressA << 4) + (m_pressB << 5) + (m_pressC << 6) + (m_pressD << 7);
    if ((unsigned char)m_inputHistory[m_inputPos] >= 0x10) {
        if (pattern >= 0xc8) {
            m_bufferedPress = m_inputHistory[m_inputPos];
        }
        if (pattern >= 0xa3 && pattern <= 0xa6) {
            m_dashBufferedPress = m_inputHistory[m_inputPos];
            m_dashBufferTime = 0xf;
        }
    }
    m_inputPos++;
    if (m_inputPos >= 0xb4) {
        m_inputPos = 0;
    }
    if (m_inputX == 1 - (((*m_opponent)->x - x > 0.0) << 1) && unk14e == 0 && unk150 == 0) {
        unk14e = 0x3c;
    }
    if ((*m_opponent)->unk14a == 0 && unk14e > 0) {
        unk14e--;
    }
    if (m_inputX == 0) {
        unk150 = 0;
    } else {
        unk150 = 1;
    }
    ReadCommand();
}

void CPlayer::Unk4121a0(int p1, int p2)
{
    int v34;
    RECT v30;
    EffectFrame v20;
    RECT v14;
    int l4;

    if (m_afterimages.unk0 > 0 || m_afterimages.unk2 > 0) {
        v34 = m_afterimages.pos - (m_afterimages.unk0 * 3 + m_afterimages.unk2);
        l4 = 0;
        for (; l4 < m_afterimages.unk2 + m_afterimages.unk0 * 3; l4 = m_afterimages.unk1 + l4) {
            if (v34 >= 0x3c) {
                v34 -= 0x3c;
            }
            if (v34 < 0) {
                v34 += 0x3c;
            }
            v20 = anims[m_afterimages.pattern[v34]].frames[m_afterimages.frame[v34]];
            v30.left = 0;
            v30.top = 0;
            v30.right = v20.width;
            v30.bottom = v20.height;
            v14.left = (int)m_afterimages.x[v34] + p1 - v20.x * (m_afterimages.facing[v34] == 1) - (v20.width - v20.x) * (m_afterimages.facing[v34] == -1);
            v14.top = (int)m_afterimages.y[v34] + 0xd2 - (m_afterimages.y[v34] < 0.0) - v20.y + p2;
            v14.right = v20.width + v14.left;
            v14.bottom = v20.height + v14.top;
            m_graphics->BlitEx(v14, surfaces[v20.surface], v30, colorKey, m_afterimages.facing[v34] == -1, 0);
            v34 = m_afterimages.unk1 + v34;
        }
    }
    v20 = anims[pattern].frames[frame];
    v30.left = 0;
    v30.top = 0;
    v30.right = v20.width;
    v30.bottom = v20.height;
    v14.left = (int)x + p1 - v20.x * (facing == 1) - (v20.width - v20.x) * (facing == -1);
    v14.top = (int)y + 0xd2 - (y < 0.0) - v20.y + p2;
    v14.right = v20.width + v14.left;
    v14.bottom = v20.height + v14.top;
    if (v14.top < 0xf0) {
        if (m_tintTime == 0) {
            if (unk58 == 3) {
                m_graphics->BlitSmear(v14, surfaces[v20.surface], v30, colorKey, facing == -1);
            } else if (unk58 > 0) {
                m_graphics->BlitEx(v14, surfaces[v20.surface], v30, colorKey, facing == -1, unk58 - 1);
            } else {
                m_graphics->Blit(v14, surfaces[v20.surface], v30, colorKey, facing == -1);
            }
        } else {
            m_graphics->BlitTint(v14, surfaces[v20.surface], v30, colorKey, facing == -1, m_tintColor);
            m_tintTime--;
        }
        return;
    }
    if (unk13e == 0) {
        v20 = *anims[0x31].frames;
        v30.left = 0;
        v30.top = 0;
        v30.right = v20.width;
        v30.bottom = v20.height;
        v14.left = (int)x + p1 - v20.x * (facing == 1) - (v20.width - v20.x) * (facing == -1);
        v14.top = 0xef - v20.y;
        v14.right = v20.width + v14.left;
        v14.bottom = v20.height + v14.top;
        m_graphics->Blit(v14, surfaces[v20.surface], v30, colorKey, facing == -1);
    }
}
