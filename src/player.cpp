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
    char oldFacing;

    oldFacing = facing;
    if (x < (*m_opponent)->x) {
        facing = 1;
        return facing != oldFacing;
    }
    if (x > (*m_opponent)->x) {
        facing = -1;
        return facing != oldFacing;
    }
    return 0;
}

int CPlayer::FaceX(double targetX)
{
    char oldFacing;

    oldFacing = facing;
    if (x < targetX) {
        facing = 1;
        return facing != oldFacing;
    }
    if (x > targetX) {
        facing = -1;
        return facing != oldFacing;
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

CPlayer::CPlayer(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : m_opponent(opponent)
{
    int i;

    m_game = game;
    m_graphics = graphics;
    m_input = input;
    m_sound = sound;
    m_side = side;
    m_charId = 0;
    m_paletteIndex = 0;
    i = 0;
    for (; i < 50; i++) {
        m_voices[i] = 150;
    }
    i = 0;
    for (; i < 20; i++) {
        m_rivals[i] = -1;
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
    int i;

    if ((int)surfaces != 0) {
        i = 0;
        for (; i < lastSurface + 1; i++) {
            if ((int)surfaces[i] != 0) {
                surfaces[i]->Release();
                surfaces[i] = (IDirectDrawSurface*)0;
            }
        }
        delete (char*)surfaces;
    }
    i = 0;
    for (; i < 50; i++) {
        if ((unsigned short)m_voices[i] != 150) {
            m_sound->Release(m_voices[i]);
        }
    }
    delete[] anims;
    delete[] m_patterns;
}

void CPlayer::Reset()
{
    int i;

    x = m_side * 160 + 240;
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
    m_hp = 9999;
    m_comboStartHp = 9999;
    m_shownHp = 9999;
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
    i = 0;
    for (; i < kInputHistoryLength; i++) {
        m_inputHistory[i] = 0;
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
    int i;

    i = 0;
    for (; i < kInputHistoryLength; i++) {
        m_inputHistory[i] = 0;
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
                m_gauge = 3000;
                m_hp = m_refillHp;
                if (m_refillMeter > 0) {
                    if (m_refillMeter < 1000) {
                        m_rfGauge = m_refillMeter;
                        m_rfBlue = 0;
                    } else {
                        m_rfGauge = 2000 - m_refillMeter;
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
    int slot; // the object being moved, an index into m_objects

    slot = m_objectTail;
    if (m_hitstop == 0 && (*m_opponent)->m_freezeTime == 0) {
        if ((char)AtScreenEdge() * facing * (vx + m_pushVx + (*m_opponent)->m_cornerPushback * ((*m_opponent)->m_hitByBody != 0 && m_freezeTime == 0)) >= 0.0) {
            x = (vx + m_pushVx + (*m_opponent)->m_cornerPushback * ((*m_opponent)->m_hitByBody != 0 && m_freezeTime == 0)) * facing + x;
        }
        if (((char)(*m_opponent)->AtScreenEdge() == 1 && (*m_opponent)->x <= 20.0) + 20 > x) {
            x = ((char)(*m_opponent)->AtScreenEdge() == 1 && (*m_opponent)->x <= 20.0) + 20;
        } else if (619 - ((char)(*m_opponent)->AtScreenEdge() == -1 && (*m_opponent)->x >= 619.0) < x) {
            x = 619 - ((char)(*m_opponent)->AtScreenEdge() == -1 && (*m_opponent)->x >= 619.0);
        }
        y = y + vy;
        if (y > 0.0) {
            y = 0.0;
        }
    }
    while (slot != m_objectHead) {
        if (m_objectActive[slot] != 0 && (m_freezeTime <= 0 || m_objects[slot].movesInFreeze != 0) && m_objects[slot].hitstop == 0 && (*m_opponent)->m_freezeTime == 0) {
            m_objects[slot].x += (m_objects[slot].vx + 0.0 * m_objects[slot].unk70) * m_objects[slot].facing;
            m_objects[slot].y = m_objects[slot].y + m_objects[slot].vy;
        }
        slot++;
        if (slot >= 64) {
            slot = 0;
        }
    }
}

void CPlayer::UpdateGaugesAndTimers()
{
    int slot; // the object whose hitstop counts down, an index into m_objects

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
            m_throwProtect = 27;
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
        slot = m_objectTail;
        while (slot != m_objectHead) {
            if (m_objectActive[slot] != 0) {
                if (m_objects[slot].hitstop > 0) {
                    m_objects[slot].hitstop--;
                } else {
                    m_objects[slot].hitstop = 0;
                }
            }
            slot++;
            if (slot >= 64) {
                slot = 0;
            }
        }
        if ((*m_opponent)->IsInHitstun() != 0) {
            m_hitsDecayTimer = 900;
            m_hitsDecayStep = 12;
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
    } else if (m_gauge > 3000) {
        m_gauge = 3000;
    }
    if (m_rfGauge < 0.0) {
        m_rfGauge = 0.0;
    } else if (m_rfGauge > 1000.0) {
        m_rfGauge = 1000.0;
    }
    m_blinkTimer--;
    if (m_blinkTimer <= 0) {
        m_blinkTimer = 12600;
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
    if (x + 20.0 >= 639 - ((*m_opponent)->x >= 619.0) || x - (*m_opponent)->x > 280.0) {
        return -1;
    }
    return 0;
}

int CPlayer::CanGuard(PatternFrame* attack, PatternFrame* state)
{
    if (m_noGuardTime > 0) {
        return 0;
    }
    if ((attack->flagsAA & kAttackUnblockable) > 0) {
        return 0;
    }
    if ((state->flagsB0 & kStateCanGuard) == 0) {
        return 0;
    }
    if ((attack->flagsAA & kAttackGuardAir) == 0 && y < 0.0 && m_recoilGuardWindow < 30) {
        return 0;
    }
    if (HoldsGuard(attack) == 0) {
        return 0;
    }
    return 1;
}

int CPlayer::HoldsGuard(PatternFrame* attack)
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
            if ((attack->flagsAA & kAttackGuardStand) == 0) {
                m_inputY = 1;
            } else if ((attack->flagsAA & kAttackGuardCrouch) == 0) {
                m_inputY = 0;
            }
        }
        if ((attack->flagsAA & kAttackGuardCrouch) == 0 && m_inputY == 1 && y == 0.0 || (attack->flagsAA & kAttackGuardStand) == 0 && m_inputY != 1 && y == 0.0) {
            return 0;
        }
    } else {
        if (m_inputX != 1 - (((*m_opponent)->x - x > 0.0) << 1) && (IsGuarding() == 0 || m_inputX == 0)) {
            return 0;
        }
        if ((attack->flagsAA & kAttackGuardCrouch) == 0 && m_inputY == 1 && y == 0.0 || (attack->flagsAA & kAttackGuardStand) == 0 && m_inputY != 1 && y == 0.0) {
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

void CPlayer::DealDamage(int damage, double proration)
{
    if (m_comboHits == 0) {
        (*m_opponent)->m_comboStartHp = (*m_opponent)->m_hp;
    }
    (*m_opponent)->m_hp -= (int)((double)damage * this->AttackFactor() * (*m_opponent)->DefenseFactor() * this->ProrationFactor());
    m_shownProration = m_proration / 100.0;
    m_proration = proration / 1000.0 * m_proration;
    if (m_proration > 10000.0) {
        m_proration = proration / 1000.0 * m_proration;
    }
    m_comboHits++;
    m_shownHits = m_comboHits;
    m_comboTimer = 180;
    m_comboDamage = (*m_opponent)->m_comboStartHp - (*m_opponent)->m_hp;
    if ((DWORD)m_comboHits > m_maxHits) {
        m_maxHits = m_comboHits;
    }
    if ((unsigned long)m_comboDamage > m_maxDamage) {
        m_maxDamage = m_comboDamage;
    }
    m_hitsLanded++;
    AddScore(damage / 100 * m_hitsLanded * m_maxHits * m_comboHits);
}

void CPlayer::ScoreHit(PatternFrame* attack)
{
    if ((DWORD)m_comboHits > m_maxHits) {
        m_maxHits = m_comboHits;
    }
    if ((unsigned long)m_comboDamage > m_maxDamage) {
        m_maxDamage = m_comboDamage;
    }
    m_hitsLanded++;
    AddScore(attack->damage / 100 * m_hitsLanded * m_maxHits * m_comboHits);
}

void CPlayer::AddScore(int points)
{
    m_score += points;
    while ((unsigned long)m_score >= 0x5f5e100) {
        m_score -= 0x5f5e100;
        m_scoreHigh++;
    }
}

short CPlayer::Random(short low, short high)
{
    WORD roll; // rand(), or the replay's word
    short result;

    roll = rand();
    if (m_game->m_replayMode == 1) {
        roll = m_game->m_replay.Read();
    } else if (m_game->m_replayMode == 2) {
        m_game->m_replay.Write(roll);
    }
    result = low + (high - low) * roll / 32768;
    return result;
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

void CPlayer::StartAfterimages(BYTE spacing)
{
    m_afterimages.Start((ObjBase*)this, spacing);
}

void CPlayer::ShakeScreen(int amplitude, int hold)
{
    m_game->m_shake = amplitude;
    m_game->m_shakeHold = hold;
}

void CPlayer::FocusCameraX(int percent, int duration)
{
    m_game->m_cameraFocusX = (1 - (m_side << 1)) * percent;
    m_game->m_cameraFocusXTime = duration;
}

void CPlayer::FocusCameraY(int percent, int duration)
{
    m_game->m_cameraFocusY = (1 - (m_side << 1)) * percent;
    m_game->m_cameraFocusYTime = duration;
}

void CPlayer::Tint(BYTE color, int duration)
{
    m_tintColor = color;
    m_tintTime = duration;
    if (m_game->m_drawEveryFrame == 0) {
        m_tintTime = m_tintTime / 2;
    }
}

void CPlayer::FillBackground(BYTE color, int duration)
{
    m_fillColor = color;
    m_fillTime = duration;
    if (m_game->m_drawEveryFrame == 0) {
        m_fillTime = m_fillTime / 2;
    }
    m_game->m_fillSide = m_side;
}

void CPlayer::Load()
{
    char path[32];
    char number[8]; // the palette's number, as text

    if (m_loaded == 0) {
        LoadSprites();
        LoadPatterns();
        LoadVoices();
        m_loaded = 1;
    } else if (1) {
        if (m_game->m_editColor[m_side] != 0) {
            strcpy(path, m_name);
            strcat(path, "\\");
            strcat(path, m_name);
            _itoa(m_paletteIndex + 1, number, 10);
            strcat(path, (const char*)number);
            strcat(path, ".pal");
            if (m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)path, 0, m_side * 40 + 95, 40) == 0) {
                strcpy(path, m_name);
                strcat(path, "\\");
                strcat(path, m_name);
                strcat(path, ".dat");
                m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)path, m_paletteIndex * 40, m_side * 40 + 95, 40);
            }
        } else {
            strcpy(path, m_name);
            strcat(path, "\\");
            strcat(path, m_name);
            strcat(path, ".dat");
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)path, m_paletteIndex * 40, m_side * 40 + 95, 40);
        }
    } else if (m_game->m_editColor[m_side] != 0) {
        strcpy(path, m_name);
        strcat(path, "\\");
        strcat(path, m_name);
        _itoa(m_paletteIndex + 1, number, 10);
        strcat(path, (const char*)number);
        strcat(path, ".pal");
        if (m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)path, 0, m_side * 40 + 95, 40) == 0) {
            strcpy(path, m_name);
            strcat(path, "\\000.bmp");
            m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)path, m_paletteIndex * 40, m_side * 40 + 95, 40);
        }
    } else {
        strcpy(path, m_name);
        strcat(path, "\\000.bmp");
        m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)path, m_paletteIndex * 40, m_side * 40 + 95, 40);
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
    int buffer; // the file buffer from operator new, as an int
    int table; // the surfaces array from operator new, as an int
    int bmp; // the sprite loaded from <name>\NNN.bmp (a branch never taken)
    char message[32]; // the number of the sprite that failed, as text
    int i;
    char* data; // the .dat file: a count of palette entries, the entries, then the sprites
    int bytesRead;
    int size; // the .dat file's size
    int offset; // where in data the next sprite starts
    int spriteSize; // bytes LoadSurfaceHigh read, 0 on a failure
    int file; // the .dat file's handle
    char path[32];
    char number[8]; // the palette's or sprite's number, as text

    table = TOINT(int, operator new(lastSurface * 4 + 4));
    surfaces = TOPTR(PTR32(IDirectDrawSurface)*, table);
    if (1) {
        offset = 0;
        strcpy(path, m_name);
        strcat(path, "\\");
        strcat(path, m_name);
        strcat(path, ".dat");
        file = (int)CreateFileA((LPCSTR)path, 0x80000000, 0, 0, 3, 128, 0);
        size = GetFileSize((HANDLE)file, 0);
        buffer = TOINT(int, operator new(size));
        data = TOPTR(char*, buffer);
        ReadFile((HANDLE)file, (LPVOID)data, size, (LPDWORD)&bytesRead, 0);
        offset = *(BYTE*)data * 3 + 1;
        i = 0;
        for (; i <= lastSurface; i++) {
            spriteSize = m_graphics->LoadSurfaceHigh(&surfaces[i], (BYTE*)(data + offset), 128, m_side * 40 + 95);
            if (spriteSize == 0) {
                _itoa(i, message, 10);
                MessageBoxA(0, (LPCSTR)message, 0, 0);
            } else {
                offset += spriteSize;
            }
        }
        CloseHandle((HANDLE)file);
        delete (char*)data;
        if (m_game->m_editColor[m_side] != 0) {
            strcpy(path, m_name);
            strcat(path, "\\");
            strcat(path, m_name);
            _itoa(m_paletteIndex + 1, number, 10);
            strcat(path, (const char*)number);
            strcat(path, ".pal");
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)path, 0, m_side * 40 + 95, 40);
        } else {
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)path, m_paletteIndex * 40, m_side * 40 + 95, 40);
        }
    } else {
        bmp = 0;
        for (; bmp <= lastSurface; bmp++) {
            strcpy(path, m_name);
            strcat(path, "\\");
            if (bmp >= 1000) {
                strcat(path, "A");
                _itoa(bmp, number, 10);
                strcat(path, (const char*)number);
                strcat(path, ".bmp");
                m_graphics->LoadBmpHigh(&surfaces[bmp], (const char*)path, m_side * 40 + 95);
            } else {
                if (bmp < 100) {
                    strcat(path, "0");
                }
                if (bmp < 10) {
                    strcat(path, "0");
                }
                _itoa(bmp, number, 10);
                strcat(path, (const char*)number);
                strcat(path, ".bmp");
                m_graphics->LoadBmpHigh(&surfaces[bmp], (const char*)path, m_side * 40 + 95);
            }
        }
        if (m_game->m_editColor[m_side] != 0) {
            strcpy(path, m_name);
            strcat(path, "\\");
            strcat(path, m_name);
            _itoa(m_paletteIndex + 1, number, 10);
            strcat(path, (const char*)number);
            strcat(path, ".pal");
            m_graphics->LoadPaletteDat(m_game->m_palette, (const char*)path, 0, m_side * 40 + 95, 40);
        } else {
            strcpy(path, m_name);
            strcat(path, "\\000.bmp");
            m_graphics->LoadPaletteBmp(m_game->m_palette, (const char*)path, m_paletteIndex * 40, m_side * 40 + 95, 40);
        }
    }
    colorKey = m_graphics->GetColorKey(*surfaces);
}

void CPlayer::LoadPatterns()
{
    int box;
    PatternFrame* frameData; // the frame's boxes and attack values being read
    EffectFrame* sprite; // the frame's sprite and timing being read
    int j;
    int i;
    int frameCount;
    int action; // the pattern the record is for
    char path[32];
    int patternCount;

    strcpy(path, m_name);
    strcat(path, "\\");
    strcat(path, m_name);
    strcat(path, ".pat");
    CFile file(path, 1);
    patternCount = file.ReadInt();
    i = 0;
    for (; i < patternCount; i++) {
        action = file.ReadInt();
        m_patterns[action].level = file.ReadInt();
        m_patterns[action].cancelLevel = file.ReadInt();
        anims[action].frameCount = file.ReadInt();
        frameCount = anims[action].frameCount;
        m_patterns[action].Alloc(frameCount);
        anims[action].Alloc(frameCount);
        j = 0;
        for (; j < frameCount; j++) {
            sprite = &anims[action].frames[j];
            frameData = &m_patterns[action].frames[j];
            sprite->duration = (short)file.ReadInt() * 3;
            sprite->surface = file.ReadInt();
            sprite->width = file.ReadInt();
            sprite->height = file.ReadInt();
            sprite->x = file.ReadInt();
            sprite->y = file.ReadInt();
            frameData->damage = file.ReadInt();
            frameData->flagsAA = file.ReadInt();
            frameData->airHitPattern = file.ReadInt();
            frameData->flagsB0 = file.ReadInt();
            frameData->untechTime = file.ReadInt();
            frameData->chipDamage = file.ReadInt();
            frameData->gaugeOnHit = file.ReadInt();
            frameData->gaugeOnGuard = file.ReadInt();
            frameData->hitVy = (short)file.ReadShort();
            frameData->hitVy = frameData->hitVy / 1e+02f;
            frameData->hitVx = (short)file.ReadShort();
            frameData->hitVx = frameData->hitVx / -1e+02f;
            frameData->hitSound = file.ReadShort();
            frameData->hitEffect = file.ReadShort();
            frameData->attackerHitstop = file.ReadInt();
            frameData->defenderHitstop = file.ReadInt();
            frameData->proration = file.ReadInt();
            frameData->groundHitPattern = file.ReadInt();
            file.Read((void*)&frameData->pushBox.left, 16);
            box = 0;
            for (; box < 2; box++) {
                file.Read((void*)((box << 4) + (char*)frameData), 16);
            }
            file.Read((void*)&frameData->attackBoxes[0].left, 16);
            box = 2;
            for (; box < 5; box++) {
                file.Read((void*)((box << 4) + (char*)frameData), 16);
            }
            box = 1;
            for (; box < 4; box++) {
                file.Read((void*)&frameData->attackBoxes[box].left, 16);
            }
        }
    }
    i = 0;
    for (; i < 64; i++) {
        m_objects[i].anims = anims;
    }
}

void CPlayer::LoadVoices()
{
    int i;
    char path[32];
    char number[8]; // the voice's number, as text

    i = 0;
    for (; i < 50; i++) {
        strcpy(path, m_name);
        strcat(path, "\\wave\\");
        if (i < 10) {
            strcat(path, "0");
        }
        _itoa(i, number, 10);
        strcat(path, (const char*)number);
        strcat(path, ".wav");
        m_voices[i] = m_sound->Load((const char*)path);
        m_sound->SetVolume(m_voices[i], -500);
    }
}

void CPlayer::ReadInput()
{
    BYTE input; // this tick's bits (as m_inputHistory's), from GetInput or the replay

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
    input = m_input->GetInput(m_side);
    if (m_game->m_replayMode == 1) {
        input = m_game->m_replay.Read();
    } else if (m_game->m_replayMode == 2) {
        m_game->m_replay.Write(input);
    }
    m_inputX = 0;
    m_inputY = 0;
    m_pressA = 0;
    m_pressB = 0;
    m_pressC = 0;
    m_pressD = 0;
    if ((input & 8) > 0) {
        m_inputY = -1;
    } else if ((input & 4) > 0) {
        m_inputY = 1;
    }
    if (facing > 0) {
        if ((input & 2) > 0) {
            m_inputX = -1;
        } else if ((input & 1) > 0) {
            m_inputX = 1;
        }
    } else if ((input & 1) > 0) {
        m_inputX = 1;
    } else if ((input & 2) > 0) {
        m_inputX = -1;
    }
    if ((input & 0x10) > 0) {
        m_pressA = m_holdA == 0;
        m_holdA = 1;
    } else {
        m_holdA = 0;
    }
    if ((input & 0x20) > 0) {
        m_pressB = m_holdB == 0;
        m_holdB = 1;
    } else {
        m_holdB = 0;
    }
    if ((input & 0x40) > 0) {
        m_pressC = m_holdC == 0;
        m_holdC = 1;
    } else {
        m_holdC = 0;
    }
    if ((input & 0x80) > 0) {
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
    m_inputHistory[m_inputPos] = (m_inputX == 1) + (m_inputX == -1) * kInputLeft + (m_inputY == 1) * kInputDown + (m_inputY == -1) * kInputUp + (m_pressA << 4) + (m_pressB << 5) + (m_pressC << 6) + (m_pressD << 7);
    if ((unsigned char)m_inputHistory[m_inputPos] >= kInputA) { // a button went down
        if (pattern >= kFirstCharacterAction) {
            m_bufferedPress = m_inputHistory[m_inputPos];
        }
        if (pattern >= kDashForward && pattern <= kAirDashBack) {
            m_dashBufferedPress = m_inputHistory[m_inputPos];
            m_dashBufferTime = 15;
        }
    }
    m_inputPos++;
    if (m_inputPos >= kInputHistoryLength) {
        m_inputPos = 0;
    }
    if (m_inputX == 1 - (((*m_opponent)->x - x > 0.0) << 1) && m_recoilGuardWindow == 0 && m_heldDirection == 0) {
        m_recoilGuardWindow = 60;
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

void CPlayer::DrawSprite(int drawX, int drawY)
{
    int pos; // the afterimage drawn, an index into m_afterimages' positions
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen
    int i;

    if (m_afterimages.spacing > 0 || m_afterimages.fadeLength > 0) {
        pos = m_afterimages.pos - (m_afterimages.spacing * 3 + m_afterimages.fadeLength);
        i = 0;
        for (; i < m_afterimages.fadeLength + m_afterimages.spacing * 3; i = m_afterimages.step + i) {
            if (pos >= 60) {
                pos -= 60;
            }
            if (pos < 0) {
                pos += 60;
            }
            sprite = anims[m_afterimages.pattern[pos]].frames[m_afterimages.frame[pos]];
            src.left = 0;
            src.top = 0;
            src.right = sprite.width;
            src.bottom = sprite.height;
            dst.left = (int)m_afterimages.x[pos] + drawX - sprite.x * (m_afterimages.facing[pos] == 1) - (sprite.width - sprite.x) * (m_afterimages.facing[pos] == -1);
            dst.top = (int)m_afterimages.y[pos] + 210 - (m_afterimages.y[pos] < 0.0) - sprite.y + drawY;
            dst.right = sprite.width + dst.left;
            dst.bottom = sprite.height + dst.top;
            m_graphics->BlitEx(dst, surfaces[sprite.surface], src, colorKey, m_afterimages.facing[pos] == -1, 0);
            pos = m_afterimages.step + pos;
        }
    }
    sprite = anims[pattern].frames[frame];
    src.left = 0;
    src.top = 0;
    src.right = sprite.width;
    src.bottom = sprite.height;
    dst.left = (int)x + drawX - sprite.x * (facing == 1) - (sprite.width - sprite.x) * (facing == -1);
    dst.top = (int)y + 210 - (y < 0.0) - sprite.y + drawY;
    dst.right = sprite.width + dst.left;
    dst.bottom = sprite.height + dst.top;
    if (dst.top < 240) {
        if (m_tintTime == 0) {
            if (m_drawMode == 3) {
                m_graphics->BlitSmear(dst, surfaces[sprite.surface], src, colorKey, facing == -1);
            } else if (m_drawMode > 0) {
                m_graphics->BlitEx(dst, surfaces[sprite.surface], src, colorKey, facing == -1, m_drawMode - 1);
            } else {
                m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, facing == -1);
            }
        } else {
            m_graphics->BlitTint(dst, surfaces[sprite.surface], src, colorKey, facing == -1, m_tintColor);
            m_tintTime--;
        }
        return;
    }
    if (m_hideOffscreenMarker == 0) {
        sprite = *anims[kOffscreenMarker].frames;
        src.left = 0;
        src.top = 0;
        src.right = sprite.width;
        src.bottom = sprite.height;
        dst.left = (int)x + drawX - sprite.x * (facing == 1) - (sprite.width - sprite.x) * (facing == -1);
        dst.top = 239 - sprite.y;
        dst.right = sprite.width + dst.left;
        dst.bottom = sprite.height + dst.top;
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, facing == -1);
    }
}
