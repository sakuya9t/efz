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

void CPlayer::MoveOnGround()
{
    if (y == 0.0) {
        m_airDashes = 0;
        m_airActions = 0;
    }
    if (y >= 0.0 && pattern != kJump && pattern != kJumpForward && pattern != kJumpBack && pattern != kSuperJump && pattern != kSuperJumpForward && pattern != kSuperJumpBack) {
        if (m_sealLevel < 3 && m_inputY == -1) {
            FaceOpponent();
            if (m_command >= 3 && m_command <= 5) {
                if (m_command == 3) {
                    if (pattern != kSuperJump) {
                        StartPattern();
                    }
                    pattern = kSuperJump;
                    return;
                }
                if (m_command == 4) {
                    if (pattern != kSuperJumpForward) {
                        StartPattern();
                    }
                    pattern = kSuperJumpForward;
                    return;
                }
                if (m_command == 5) {
                    if (pattern != kSuperJumpBack) {
                        StartPattern();
                    }
                    pattern = kSuperJumpBack;
                    return;
                }
            } else {
                if (m_inputX == 0) {
                    if (pattern != kJump) {
                        StartPattern();
                    }
                    pattern = kJump;
                    return;
                }
                if (m_inputX == facing) {
                    if (pattern != kJumpForward) {
                        StartPattern();
                    }
                    pattern = kJumpForward;
                    return;
                }
                if (m_inputX == -facing) {
                    if (pattern != kJumpBack) {
                        StartPattern();
                    }
                    pattern = kJumpBack;
                    return;
                }
            }
        }
        if (m_inputY == 1) {
            if (pattern != kCrouchDown && pattern != kCrouch) {
                pattern = kCrouchDown;
                StartPattern();
                FaceOpponent();
                return;
            }
            if (pattern != kCrouchDown) {
                pattern = kCrouch;
                FaceOpponent();
                return;
            }
            return;
        }
        if (m_inputX != 0) {
            FaceOpponent();
            if (m_inputX == facing) {
                if (pattern != kWalkForward) {
                    StartPattern();
                }
                pattern = kWalkForward;
                return;
            }
            if (pattern != kWalkBack) {
                StartPattern();
            }
            pattern = kWalkBack;
            return;
        }
        if (pattern == kCrouch || pattern == kCrouchDown) {
            pattern = kStandUp;
            FaceOpponent();
            StartPattern();
            return;
        }
        if (pattern == kStandUp || pattern == kLand) {
            FaceOpponent();
            return;
        }
        if (pattern != kStand) {
            StartPattern();
        }
        pattern = kStand;
        FaceOpponent();
    }
}

CPlayer::CPlayer(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
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
    surfaces = (PTR32(IDirectDrawSurface)*)0;
    anims = new EffectAnim[0x1f9];
    m_patterns = new PatternData[0x1f9];
    m_score = 0;
    m_scoreHigh = 0;
    m_hitsLanded = 0;
    m_maxHits = 0;
    m_maxDamage = 0;
    m_loaded = 0;
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
    m_pushVx = 0.0;
    m_hitByBody = 0;
    pattern = kStand;
    frame = 0;
    timer = 0;
    m_tintTime = 0;
    m_fillTime = 0;
    m_hp = 0x270f;
    m_comboStartHp = 0x270f;
    m_shownHp = 0x270f;
    m_gauge = 0;
    m_rfGauge = 0.0;
    m_rfBlue = 0;
    m_freezeTime = 0;
    m_airDashes = 0;
    m_dashMomentum = 0;
    m_airActions = 0;
    m_recoilGuardWindow = 0;
    m_heldDirection = 0;
    m_roundsWon = 0;
    m_armorTime = 0;
    m_noGuardTime = 0;
    m_invulTime = 0;
    m_hideOffscreenMarker = 0;
    m_koDelay = 0;
    m_sealLevel = 0;
    m_timerSuper = 0;
    m_attackResult = 0;
    m_hitstop = 0;
    *(int*)&m_guardGauge = 0;
    m_comboHits = 0;
    m_shownHits = 0;
    m_comboTimer = 0;
    m_proration = 10000.0;
    m_shownProration = 10000.0;
    m_canRecoilCounter = 0;
    m_defense = 1.0;
    m_bufferedPress = 0;
    m_dashBufferedPress = 0;
    m_command = kCmdNone;
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
    m_afterimages.spacing = 0;
    m_afterimages.fadeLength = 0;
    m_blinkTimer = 0;
    m_refillMeter = 0;
    m_drawMode = 0;
    m_drawShadow = 1;
    m_wonHpTotal = 0;
    m_maxHits = 0;
    m_maxDamage = 0;
}

void CPlayer::StartPattern()
{
    frame = 0;
    timer = 0;
    m_cornerPushback = 0.0;
    m_attackResult = 0;
    m_canRecoilCounter = 0;
    m_afterimages.Stop();
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
    m_command = kCmdNone;
}

void CPlayer::StopMoving()
{
    vx = 0.0;
    vy = 0.0;
    ax = 0.0;
    ay = 0.0;
    m_cornerPushback = 0.0;
}

void CPlayer::ProcessInput()
{
    if (m_hitstop == 0 && (*m_opponent)->m_freezeTime == 0) {
        if (pattern < kFirstHitReaction || pattern > kFirstGuard || pattern == kWakeUp) {
            m_untechTime = 0;
            m_landHittable = 0;
            (*m_opponent)->m_comboHits = 0;
            if ((*m_opponent)->m_proration > 10000.0) {
                (*m_opponent)->m_proration -= 20.0;
            } else {
                (*m_opponent)->m_proration = 10000.0;
            }
        }
        if (pattern < kFirstHitReaction) {
            Move();
            m_cornerPushback = 0.0;
            (*m_opponent)->m_cornerPushback = 0.0;
            if (m_refillMeter != 0 && (*m_opponent)->pattern < kFirstHitReaction) {
                m_gauge = 0xbb8;
                m_hp = m_refillHp;
                if (m_refillMeter > 0) {
                    if (m_refillMeter < 0x3e8) {
                        m_rfGauge = m_refillMeter;
                        m_rfBlue = 0;
                    } else {
                        m_rfGauge = 0x7d0 - m_refillMeter;
                        m_rfBlue = 1;
                    }
                }
            }
        }
        if (pattern >= kFirstHitReaction && pattern < kFirstGuard && m_guardGauge <= 0.0f && (m_patterns[pattern].frames[frame].flagsAA & kAttackNoAirRecovery) == 0) {
            TryAirRecovery();
        }
        StartCommand();
    }
}

void CPlayer::TryAirRecovery()
{
    if (m_untechTime > 0) {
        m_untechTime--;
        return;
    }
    if (y < 0.0 && m_noAirRecovery == 0 && (m_pressA != 0 || m_pressB != 0 || m_pressC != 0 || m_pressD != 0)) {
        if (m_inputX == facing) {
            if (pattern != kAirRecoveryForward) {
                StartPattern();
            }
            pattern = kAirRecoveryForward;
            return;
        }
        if (m_inputX == -facing) {
            if (pattern != kAirRecoveryBack) {
                StartPattern();
            }
            pattern = kAirRecoveryBack;
        }
    }
}

void CPlayer::ApplyVelocity()
{
    int v4;

    v4 = m_objectTail;
    if (m_hitstop == 0 && (*m_opponent)->m_freezeTime == 0) {
        if ((char)AtScreenEdge() * facing * (vx + m_pushVx + (*m_opponent)->m_cornerPushback * ((*m_opponent)->m_hitByBody != 0 && m_freezeTime == 0)) >= 0.0) {
            x = (vx + m_pushVx + (*m_opponent)->m_cornerPushback * ((*m_opponent)->m_hitByBody != 0 && m_freezeTime == 0)) * facing + x;
        }
        if (((char)(*m_opponent)->AtScreenEdge() == 1 && (*m_opponent)->x <= 20.0) + 0x14 > x) {
            x = ((char)(*m_opponent)->AtScreenEdge() == 1 && (*m_opponent)->x <= 20.0) + 0x14;
        } else if (0x26b - ((char)(*m_opponent)->AtScreenEdge() == -1 && (*m_opponent)->x >= 619.0) < x) {
            x = 0x26b - ((char)(*m_opponent)->AtScreenEdge() == -1 && (*m_opponent)->x >= 619.0);
        }
        y = y + vy;
        if (y > 0.0) {
            y = 0.0;
        }
    }
    while (v4 != m_objectHead) {
        if (m_objectActive[v4] != 0 && (m_freezeTime <= 0 || m_objects[v4].movesInFreeze != 0) && m_objects[v4].hitstop == 0 && (*m_opponent)->m_freezeTime == 0) {
            m_objects[v4].x += (m_objects[v4].vx + 0.0 * m_objects[v4].unk70) * m_objects[v4].facing;
            m_objects[v4].y = m_objects[v4].y + m_objects[v4].vy;
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}

void CPlayer::UpdateGaugesAndTimers()
{
    int v4;

    if ((*m_opponent)->m_freezeTime > 0) {
    } else {
        if (m_hitstop > 0) {
            m_hitstop--;
        } else {
            m_hitstop = 0;
        }
        if (IsGuarding() == 0) {
            if (IsInHitstun() != 0) {
                m_guardGauge = m_guardGauge - F32CAST(1.0 / ((y == 0.0) * 4 + 1));
            } else {
                m_guardGauge -= 0.075f;
            }
            if (m_guardGauge < 0.0f) {
                *(int*)&m_guardGauge = 0;
            }
        }
        if (m_throwProtect > 0) {
            m_throwProtect--;
        } else {
            m_throwProtect = 0;
        }
        if ((m_patterns[pattern].frames[frame].flagsB0 & kStateThrowProtect) > 0) {
            m_throwProtect = 0x1b;
        }
        if (m_armorTime > 0) {
            m_armorTime--;
        } else {
            m_armorTime = 0;
        }
        if (m_noGuardTime > 0) {
            m_noGuardTime--;
        } else {
            m_noGuardTime = 0;
        }
        if (m_invulTime > 0) {
            m_invulTime--;
        } else {
            m_invulTime = 0;
        }
        if (m_hideOffscreenMarker > 0) {
            m_hideOffscreenMarker--;
        } else {
            m_hideOffscreenMarker = 0;
        }
        if (m_koDelay > 0) {
            m_koDelay--;
        } else {
            m_koDelay = 0;
        }
        m_rfGauge = (IsGuarding() + 1) * (IsInHitstun() == 0 && m_rfBlue == 0) * ((m_rfGauge < 500.0) * 2 + 1) / 10.0 + m_rfGauge;
        if (m_rfGauge >= 1000.0 && m_rfBlue == 0) {
            m_rfBlue = 1;
            m_rfGauge = 1000.0;
        } else if (m_rfGauge <= 0.0) {
            m_rfBlue = 0;
            m_rfGauge = 0.0;
        }
        v4 = m_objectTail;
        while (v4 != m_objectHead) {
            if (m_objectActive[v4] != 0) {
                if (m_objects[v4].hitstop > 0) {
                    m_objects[v4].hitstop--;
                } else {
                    m_objects[v4].hitstop = 0;
                }
            }
            v4++;
            if (v4 >= 0x40) {
                v4 = 0;
            }
        }
        if ((*m_opponent)->IsInHitstun() != 0) {
            m_hitsDecayTimer = 0x384;
            m_hitsDecayStep = 0xc;
        }
        if (((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern >= kFirstCharacterAction) && m_game->m_intro == 0 && m_game->m_roundOver == 0) {
            if ((unsigned long)m_hitsDecayTimer > 0) {
                m_hitsDecayTimer--;
            } else {
                if ((unsigned long)m_hitsDecayStep > 1) {
                    m_hitsDecayStep--;
                }
                if ((unsigned long)m_hitsLanded > 0) {
                    m_hitsLanded--;
                }
                m_hitsDecayTimer = m_hitsDecayStep * 5 * 3;
            }
        }
    }
    if (m_gauge < 0) {
        m_gauge = 0;
    } else if (m_gauge > 0xbb8) {
        m_gauge = 0xbb8;
    }
    if (m_rfGauge < 0.0) {
        m_rfGauge = 0.0;
    } else if (m_rfGauge > 1000.0) {
        m_rfGauge = 1000.0;
    }
    m_blinkTimer--;
    if (m_blinkTimer <= 0) {
        m_blinkTimer = 0x3138;
    }
    if (m_comboTimer > 0 && m_comboHits == 0) {
        m_comboTimer--;
    }
}

char CPlayer::AtScreenEdge()
{
    if (x - 20.0 <= ((*m_opponent)->x <= 20.0) || (*m_opponent)->x - x > 280.0) {
        return 1;
    }
    if (x + 20.0 >= 0x27f - ((*m_opponent)->x >= 619.0) || x - (*m_opponent)->x > 280.0) {
        return -1;
    }
    return 0;
}

int CPlayer::CanGuard(PatternFrame* p1, PatternFrame* p2)
{
    if (m_noGuardTime > 0) {
        return 0;
    }
    if ((p1->flagsAA & kAttackUnblockable) > 0) {
        return 0;
    }
    if ((p2->flagsB0 & kStateCanGuard) == 0) {
        return 0;
    }
    if ((p1->flagsAA & kAttackGuardAir) == 0 && y < 0.0 && m_recoilGuardWindow < 0x1e) {
        return 0;
    }
    if (HoldsGuard(p1) == 0) {
        return 0;
    }
    return 1;
}

int CPlayer::HoldsGuard(PatternFrame* p1)
{
    if (m_cpu != 0) {
        if (m_game->m_gameMode == 1) {
            if (m_game->m_dummyGuard == 0) {
                return 0;
            }
        } else {
            if (rand() > m_cpuSkill * 1e+04f) {
                return 0;
            }
            if ((p1->flagsAA & kAttackGuardStand) == 0) {
                m_inputY = 1;
            } else if ((p1->flagsAA & kAttackGuardCrouch) == 0) {
                m_inputY = 0;
            }
        }
        if ((p1->flagsAA & kAttackGuardCrouch) == 0 && m_inputY == 1 && y == 0.0 || (p1->flagsAA & kAttackGuardStand) == 0 && m_inputY != 1 && y == 0.0) {
            return 0;
        }
    } else {
        if (m_inputX != 1 - (((*m_opponent)->x - x > 0.0) << 1) && (IsGuarding() == 0 || m_inputX == 0)) {
            return 0;
        }
        if ((p1->flagsAA & kAttackGuardCrouch) == 0 && m_inputY == 1 && y == 0.0 || (p1->flagsAA & kAttackGuardStand) == 0 && m_inputY != 1 && y == 0.0) {
            return 0;
        }
    }
    return 1;
}

int CPlayer::CanAirRecover()
{
    return m_untechTime <= 0 && y < 0.0 && m_noAirRecovery == 0 && IsInHitstun() != 0;
}

int CPlayer::IsGuarding()
{
    return pattern >= kFirstGuard && pattern <= kGuardAir || pattern >= kRecoilGuardStand && pattern <= kAirInstantCharge;
}

int CPlayer::IsInHitstun()
{
    return pattern >= kFirstHitReaction && pattern < kFirstGuard && (*m_opponent)->pattern != kKnockdownHittable && (*m_opponent)->pattern != kKnockdown && (*m_opponent)->pattern != kLyingDown && (*m_opponent)->pattern != kWakeUp;
}

int CPlayer::IsDashing()
{
    return pattern == kDashForward || pattern == kDashBack || pattern == kAirDashForward || pattern == kAirDashBack;
}

double CPlayer::AttackFactor()
{
    if (m_game->m_gameMode == 2) {
        return m_rfGauge / 10000.0 + 1.0;
    }
    if (m_game->m_damageLevel == 1) {
        return (m_rfGauge / 10000.0 + 1.0) / 2.0;
    }
    if (m_game->m_damageLevel == 2) {
        return m_rfGauge / 10000.0 + 1.0;
    }
    return (m_rfGauge / 10000.0 + 1.0) * 2;
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

void CPlayer::ScoreHit(PatternFrame* p1)
{
    if ((DWORD)m_comboHits > m_maxHits) {
        m_maxHits = m_comboHits;
    }
    if ((unsigned long)m_comboDamage > m_maxDamage) {
        m_maxDamage = m_comboDamage;
    }
    m_hitsLanded++;
    AddScore(p1->damage / 0x64 * m_hitsLanded * m_maxHits * m_comboHits);
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

void CPlayer::UpdateAfterimages()
{
    if ((*m_opponent)->m_freezeTime == 0) {
        if (m_afterimages.spacing > 0) {
            m_afterimages.Record((ObjBase*)this);
            m_afterimages.fadeLength = 0;
            return;
        }
        if (m_afterimages.fadeLength > 0) {
            m_afterimages.fadeLength--;
        }
    }
}

void CPlayer::StartAfterimages(BYTE p1)
{
    m_afterimages.Start((ObjBase*)this, p1);
}

void CPlayer::ShakeScreen(int p1, int p2)
{
    m_game->m_shake = p1;
    m_game->m_shakeHold = p2;
}

void CPlayer::FocusCameraX(int p1, int p2)
{
    m_game->m_cameraFocusX = (1 - (m_side << 1)) * p1;
    m_game->m_cameraFocusXTime = p2;
}

void CPlayer::FocusCameraY(int p1, int p2)
{
    m_game->m_cameraFocusY = (1 - (m_side << 1)) * p1;
    m_game->m_cameraFocusYTime = p2;
}

void CPlayer::Tint(BYTE p1, int p2)
{
    m_tintColor = p1;
    m_tintTime = p2;
    if (m_game->m_drawEveryFrame == 0) {
        m_tintTime = m_tintTime / 2;
    }
}

void CPlayer::FillBackground(BYTE p1, int p2)
{
    m_fillColor = p1;
    m_fillTime = p2;
    if (m_game->m_drawEveryFrame == 0) {
        m_fillTime = m_fillTime / 2;
    }
    m_game->m_fillSide = m_side;
}

void CPlayer::Load()
{
    char v2c[32];
    char vc[8];

    if (m_loaded == 0) {
        LoadSprites();
        LoadPatterns();
        LoadVoices();
        m_loaded = 1;
    } else if (1) {
        if (m_game->m_editColor[m_side] != 0) {
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
    } else if (m_game->m_editColor[m_side] != 0) {
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
        if ((m_game->m_gameMode == 0 || m_game->m_gameMode == 2) && m_game->m_arcadeMatch == 1) {
            ((CharRecord*)&m_recordUses)->Load(m_name);
            m_recordUses++;
            ((CharRecord*)&m_recordUses)->Save(m_name);
            return;
        }
        if (m_game->m_gameMode == 1 || m_game->m_gameMode == 3 || m_game->m_gameMode == 4) {
            ((CharRecord*)&m_recordUses)->Load(m_name);
            m_recordUses++;
            ((CharRecord*)&m_recordUses)->Save(m_name);
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

    v70 = TOINT(int, operator new(lastSurface * 4 + 4));
    surfaces = TOPTR(PTR32(IDirectDrawSurface)*, v70);
    if (1) {
        n38 = 0;
        strcpy(x2c, m_name);
        strcat(x2c, "\\");
        strcat(x2c, m_name);
        strcat(x2c, ".dat");
        d30 = (int)CreateFileA((LPCSTR)x2c, 0x80000000, 0, 0, 3, 0x80, 0);
        h3c = GetFileSize((HANDLE)d30, 0);
        x74 = TOINT(int, operator new(h3c));
        x44 = TOPTR(char*, x74);
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
        if (m_game->m_editColor[m_side] != 0) {
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
        if (m_game->m_editColor[m_side] != 0) {
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
        m_patterns[x38].level = k10.ReadInt();
        m_patterns[x38].cancelLevel = k10.ReadInt();
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
            l4c->damage = k10.ReadInt();
            l4c->flagsAA = k10.ReadInt();
            l4c->airHitPattern = k10.ReadInt();
            l4c->flagsB0 = k10.ReadInt();
            l4c->untechTime = k10.ReadInt();
            l4c->chipDamage = k10.ReadInt();
            l4c->gaugeOnHit = k10.ReadInt();
            l4c->gaugeOnGuard = k10.ReadInt();
            l4c->hitVy = (short)k10.ReadShort();
            l4c->hitVy = l4c->hitVy / 1e+02f;
            l4c->hitVx = (short)k10.ReadShort();
            l4c->hitVx = l4c->hitVx / -1e+02f;
            l4c->hitSound = k10.ReadShort();
            l4c->hitEffect = k10.ReadShort();
            l4c->attackerHitstop = k10.ReadInt();
            l4c->defenderHitstop = k10.ReadInt();
            l4c->proration = k10.ReadInt();
            l4c->groundHitPattern = k10.ReadInt();
            k10.Read((void*)&l4c->pushBox.left, 0x10);
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
        if (m_game->m_gameMode == 1) {
            m_pressA = 0;
            m_pressB = 0;
            m_pressC = 0;
            m_pressD = 0;
            m_inputX = 0;
            if ((char)m_game->m_dummyStance == 1) {
                m_inputY = -1;
            } else if ((char)m_game->m_dummyStance == 2) {
                m_inputY = 1;
            } else {
                m_inputY = 0;
            }
            return;
        }
        CpuInput();
        if (m_game->m_intro != 0 || m_game->m_roundOver != 0) {
            m_pressA = 0;
            m_pressB = 0;
            m_pressC = 0;
            m_pressD = 0;
            m_command = kCmdNone;
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
    if (m_game->m_intro != 0 || m_game->m_roundOver != 0) {
        m_pressA = 0;
        m_pressB = 0;
        m_pressC = 0;
        m_pressD = 0;
        m_command = kCmdNone;
    }
    m_inputHistory[m_inputPos] = (m_inputX == 1) + (m_inputX == -1) * 2 + (m_inputY == 1) * 4 + (m_inputY == -1) * 8 + (m_pressA << 4) + (m_pressB << 5) + (m_pressC << 6) + (m_pressD << 7);
    if ((unsigned char)m_inputHistory[m_inputPos] >= 0x10) {
        if (pattern >= kFirstCharacterAction) {
            m_bufferedPress = m_inputHistory[m_inputPos];
        }
        if (pattern >= kDashForward && pattern <= kAirDashBack) {
            m_dashBufferedPress = m_inputHistory[m_inputPos];
            m_dashBufferTime = 0xf;
        }
    }
    m_inputPos++;
    if (m_inputPos >= 0xb4) {
        m_inputPos = 0;
    }
    if (m_inputX == 1 - (((*m_opponent)->x - x > 0.0) << 1) && m_recoilGuardWindow == 0 && m_heldDirection == 0) {
        m_recoilGuardWindow = 0x3c;
    }
    if ((*m_opponent)->m_hitstop == 0 && m_recoilGuardWindow > 0) {
        m_recoilGuardWindow--;
    }
    if (m_inputX == 0) {
        m_heldDirection = 0;
    } else {
        m_heldDirection = 1;
    }
    ReadCommand();
}

void CPlayer::DrawSprite(int p1, int p2)
{
    int v34;
    RECT v30;
    EffectFrame v20;
    RECT v14;
    int l4;

    if (m_afterimages.spacing > 0 || m_afterimages.fadeLength > 0) {
        v34 = m_afterimages.pos - (m_afterimages.spacing * 3 + m_afterimages.fadeLength);
        l4 = 0;
        for (; l4 < m_afterimages.fadeLength + m_afterimages.spacing * 3; l4 = m_afterimages.step + l4) {
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
            v34 = m_afterimages.step + v34;
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
            if (m_drawMode == 3) {
                m_graphics->BlitSmear(v14, surfaces[v20.surface], v30, colorKey, facing == -1);
            } else if (m_drawMode > 0) {
                m_graphics->BlitEx(v14, surfaces[v20.surface], v30, colorKey, facing == -1, m_drawMode - 1);
            } else {
                m_graphics->Blit(v14, surfaces[v20.surface], v30, colorKey, facing == -1);
            }
        } else {
            m_graphics->BlitTint(v14, surfaces[v20.surface], v30, colorKey, facing == -1, m_tintColor);
            m_tintTime--;
        }
        return;
    }
    if (m_hideOffscreenMarker == 0) {
        v20 = *anims[kOffscreenMarker].frames;
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
