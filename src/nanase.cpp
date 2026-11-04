// CNanase (0x48a720-0x49d60f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNanase::CNanase(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

    strcpy(m_name, "nanase");
    lastSurface = 0x29c;
    m_anims2 = new EffectAnim[0x1f9];
    m_patterns2 = new PatternData[0x1f9];
    m_usingPatterns2 = 0;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_lv4Time = 0;
    m_swordThrown = 0;
    m_superSwordX = 0;
    m_superSwordY = 0;
    UsePatterns2(0);
    m_pointX[0] = -0xc;
    m_pointY[0] = -0x3a;
    m_pointX[1] = 0x12;
    m_pointY[1] = 0;
    m_pointX[2] = 0x10;
    m_pointY[2] = -9;
    m_pointX[3] = 0x15;
    m_pointY[3] = -0xe;
    m_pointX[4] = 0x21;
    m_pointY[4] = -0x1a;
    m_resultPictures = 5;
    m_rivals[0] = 6;
    m_rivals[1] = 2;
    m_rivals[2] = 5;
    m_rivals[3] = 0xc;
    m_rivals[0xa] = 0;
    i = 0;
    for (; i < 0x40; i++) {
        m_objectState[i] = 0;
        m_objectTimer[i] = 0;
        unk334c[i] = 0;
    }
}

void CNanase::Reset()
{
    int i;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_lv4Time = 0;
    m_swordThrown = 0;
    m_superSwordX = 0;
    m_superSwordY = 0;
    UsePatterns2(0);
    m_pointX[0] = -0xc;
    m_pointY[0] = -0x3a;
    m_pointX[1] = 0x12;
    m_pointY[1] = 0;
    m_pointX[2] = 0x10;
    m_pointY[2] = -9;
    m_pointX[3] = 0x15;
    m_pointY[3] = -0xe;
    m_pointX[4] = 0x21;
    m_pointY[4] = -0x1a;
    i = 0;
    for (; i < 0x40; i++) {
        m_objectState[i] = 0;
        m_objectTimer[i] = 0;
        unk334c[i] = 0;
    }
    CPlayer::Reset();
}

CNanase::~CNanase()
{
    anims = TOPTR(EffectAnim*, m_anims1);
    m_patterns = TOPTR(PatternData*, m_patterns1);
    delete[] m_anims2;
    delete[] m_patterns2;
    CPlayer::~CPlayer();
}

void CNanase::Load()
{
    LoadPatterns2();
    CPlayer::Load();
    m_anims1 = (int)anims;
    m_patterns1 = (int)m_patterns;
}

void CNanase::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CNanase::RemoveObject(short slot)
{
    m_objectState[slot] = 0;
    m_objectTimer[slot] = 0;
    unk334c[slot] = 0;
    CPlayer::RemoveObject(slot);
}

void CNanase::Move()
{
    MoveOnGround();
}

void CNanase::StartCommand()
{
    if (pattern < kFirstCharacterAction) {
        m_bufferedPress = 0;
    }
    if (m_dashBufferTime <= 0) {
        m_dashBufferedPress = 0;
    } else {
        m_dashBufferTime--;
    }
    if (m_dashBufferedPress == 0) {
        m_dashBufferTime = 0;
    }
    if (m_command == kCmd22C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && m_attackResult > 1 && m_attackResult != 6 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[kInstantCharge].level) {
        StartPattern();
        ClearBufferedPress();
        pattern = kInstantCharge;
        if (y < 0.0) {
            pattern = kAirInstantCharge;
        }
        return;
    }
    if (m_sealLevel < 2) {
        if (m_command == kCmd4123641236D && m_hp < 0xd05 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd4123641236C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && (m_patterns[pattern].cancelLevel <= m_patterns[k41364136Lv3].level || pattern > 0xfc && pattern < 0x100 && m_attackResult == 3)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41364136Lv3;
            return;
        }
        if ((m_command == kCmd4123641236B || m_command == kCmd4123641236C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && (m_patterns[pattern].cancelLevel <= m_patterns[k41364136Lv2].level || pattern > 0xfc && pattern < 0x100 && m_attackResult == 3)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41364136Lv2;
            return;
        }
        if ((m_command == kCmd4123641236A || m_command == kCmd4123641236B || m_command == kCmd4123641236C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && (m_patterns[pattern].cancelLevel <= m_patterns[k41364136Lv1].level || pattern > 0xfc && pattern < 0x100 && m_attackResult == 3)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41364136Lv1;
            return;
        }
        if (m_command == kCmd236236C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_swordThrown == 1 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236Lv3].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236Lv3;
            return;
        }
        if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_swordThrown == 1 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236Lv2].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236Lv2;
            return;
        }
        if ((m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_swordThrown == 1 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236Lv1].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236Lv1;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv3].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv3;
            return;
        }
        if ((m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv2].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv2;
            return;
        }
        if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv1].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv1;
            return;
        }
        if (m_command == kCmd623C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k623C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623C;
            if (y < 0.0) {
                frame = 9;
                m_patternVar3 = 1;
                m_attackResult = 3;
            }
            return;
        }
        if ((m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k623B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623B;
            if (y < 0.0) {
                frame = 9;
                m_attackResult = 3;
            }
            return;
        }
        if (m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
            if (y < 0.0) {
                frame = 9;
                m_attackResult = 3;
            }
            return;
        }
        if (m_command == kCmd214C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            return;
        }
        if ((m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            return;
        }
        if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            return;
        }
        if (m_command == kCmd41236C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k41236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236A;
            if (m_swordThrown == 0) {
                pattern = k41236C;
            }
            return;
        }
        if (m_command == kCmd41236B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k41236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236A;
            if (m_swordThrown == 0) {
                pattern = k41236B;
            }
            return;
        }
        if (m_command == kCmd41236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k41236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236A;
            return;
        }
        if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            return;
        }
        if ((m_command == kCmd236B || m_command == kCmd236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236B;
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_swordThrown == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236A;
            return;
        }
    }
    if (m_sealLevel < 1 && (m_command == kCmdDashLeft || m_command == kCmdDashRight)) {
        if (y < 0.0 && m_airDashes < 1) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].cancelLevel <= m_patterns[kAirDashForward].level && pattern != kRecoilGuardAir && y < -40.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                if (pattern != kAirDashForward) {
                    StartPattern();
                }
                pattern = kAirDashForward;
                FaceOpponent();
                m_airDashes++;
                m_airActions++;
                m_bufferedPress = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].cancelLevel <= m_patterns[kAirDashBack].level && pattern != kRecoilGuardAir && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                if (pattern != kAirDashBack) {
                    StartPattern();
                }
                pattern = kAirDashBack;
                FaceOpponent();
                m_airDashes++;
                m_airActions++;
                m_bufferedPress = 0;
                return;
            }
        }
        if (y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].cancelLevel <= m_patterns[kDashForward].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                if (pattern != kDashForward) {
                    StartPattern();
                }
                pattern = kDashForward;
                FaceOpponent();
                m_dashMomentum++;
                m_bufferedPress = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].cancelLevel <= m_patterns[kDashBack].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                if (pattern != kDashBack) {
                    StartPattern();
                }
                pattern = kDashBack;
                FaceOpponent();
                m_bufferedPress = 0;
                return;
            }
        }
    }
    if (m_sealLevel < 3 && m_command == kCmdUp && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_airActions < 1 && m_patterns[pattern].cancelLevel <= m_patterns[kAirJump].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
        StartPattern();
        ClearBufferedPress();
        m_airActions++;
        pattern = kAirJump;
        if (m_inputX == facing) {
            pattern = kAirJumpForward;
        }
        if (m_inputX == -facing) {
            pattern = kAirJumpBack;
        }
        return;
    }
    if (m_pressA == 1 || (m_bufferedPress & kInputA) != 0 || (m_dashBufferedPress & kInputA) != 0) {
        if (pattern == kDashForward && m_inputX != -facing) {
            StartPattern();
            ClearBufferedPress();
            pattern = kDashA;
            if (m_inputY == 1) {
                pattern = kDash2A;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].cancelLevel <= m_patterns[kJumpA].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kJumpA;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k2A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k2A;
            return;
        }
        if ((m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) && m_patterns[pattern].cancelLevel <= m_patterns[k5A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k5A;
            return;
        }
    }
    if (m_pressB == 1 || (m_bufferedPress & kInputB) != 0 || (m_dashBufferedPress & kInputB) != 0) {
        if (pattern == kDashForward && m_inputX != -facing) {
            StartPattern();
            ClearBufferedPress();
            pattern = kDashB;
            if (m_inputY == 1) {
                pattern = kDash2B;
            }
            return;
        }
        if (y < 0.0) {
            if (m_patterns[pattern].cancelLevel <= m_patterns[kJumpB].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kJumpB;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k2B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k2B;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) {
            if (m_patterns[pattern].cancelLevel <= m_patterns[k5BClose].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && x - (*m_opponent)->x > -70.0 && x - (*m_opponent)->x < 70.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k5BClose;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[k5BFar].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k5BFar;
                return;
            }
        }
    }
    if (m_pressC == 1 || (m_bufferedPress & kInputC) != 0 || (m_dashBufferedPress & kInputC) != 0) {
        if (pattern == kDashForward && m_inputX != -facing) {
            StartPattern();
            ClearBufferedPress();
            pattern = kDashC;
            if (m_inputY == 1) {
                pattern = kDash2C;
            }
            return;
        }
        if (y < 0.0) {
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kAirThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kAirThrow;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[kJumpC].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kJumpC;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k2C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k2C;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) {
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kThrow;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[k5C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k5C;
            }
        }
    }
}

void CNanase::LoadPatterns2()
{
    int k2c;
    PatternFrame* v28;
    EffectFrame* x24;
    int x20;
    int n1c;
    int a18;
    int k14;
    int l4;

    CFile v10("nanase\\nanase2.pat", 1);
    l4 = v10.ReadInt();
    n1c = 0;
    for (; n1c < l4; n1c++) {
        k14 = v10.ReadInt();
        m_patterns2[k14].level = v10.ReadInt();
        m_patterns2[k14].cancelLevel = v10.ReadInt();
        m_anims2[k14].frameCount = v10.ReadInt();
        a18 = m_anims2[k14].frameCount;
        (TOPTR(PatternData*, TOINT(int, (char*)m_patterns2) + k14 * 8))->Alloc(a18);
        (TOPTR(EffectAnim*, TOINT(int, (char*)m_anims2) + k14 * 8))->Alloc(a18);
        x20 = 0;
        for (; x20 < a18; x20++) {
            x24 = &m_anims2[k14].frames[x20];
            v28 = &m_patterns2[k14].frames[x20];
            x24->duration = (short)v10.ReadInt() * 3;
            x24->surface = v10.ReadInt();
            x24->width = v10.ReadInt();
            x24->height = v10.ReadInt();
            x24->x = v10.ReadInt();
            x24->y = v10.ReadInt();
            v28->damage = v10.ReadInt();
            v28->flagsAA = v10.ReadInt();
            v28->airHitPattern = v10.ReadInt();
            v28->flagsB0 = v10.ReadInt();
            v28->untechTime = v10.ReadInt();
            v28->chipDamage = v10.ReadInt();
            v28->gaugeOnHit = v10.ReadInt();
            v28->gaugeOnGuard = v10.ReadInt();
            v28->hitVy = (short)v10.ReadShort();
            v28->hitVy = v28->hitVy / 1e+02f;
            v28->hitVx = (short)v10.ReadShort();
            v28->hitVx = v28->hitVx / -1e+02f;
            v28->hitSound = v10.ReadShort();
            v28->hitEffect = v10.ReadShort();
            v28->attackerHitstop = v10.ReadInt();
            v28->defenderHitstop = v10.ReadInt();
            v28->proration = v10.ReadInt();
            v28->groundHitPattern = v10.ReadInt();
            v10.Read((void*)&v28->pushBox.left, 0x10);
            k2c = 0;
            for (; k2c < 2; k2c++) {
                v10.Read((void*)((k2c << 4) + (char*)v28), 0x10);
            }
            v10.Read((void*)&v28->attackBoxes[0].left, 0x10);
            k2c = 2;
            for (; k2c < 5; k2c++) {
                v10.Read((void*)((k2c << 4) + (char*)v28), 0x10);
            }
            k2c = 1;
            for (; k2c < 4; k2c++) {
                v10.Read((void*)&v28->attackBoxes[k2c].left, 0x10);
            }
        }
    }
}

void CNanase::DrawGauge()
{
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    if (m_lv4Time > 0) {
        sprite = *anims[0x2b].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(0x31 - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 0x10f - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_lv4Time > 0) {
        sprite = *anims[0x2c].frames;
        src = MakeRect(0, 0, m_lv4Time * sprite.width / 0xbb8, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(0x31 - sprite.x, 0x1f - sprite.y, m_lv4Time * sprite.width / 0xbb8, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 0x10f - m_lv4Time * sprite.width / 0xbb8, 0x1f - sprite.y, m_lv4Time * sprite.width / 0xbb8, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
}

void CNanase::UsePatterns2(char p1)
{
    int v8;
    int v4;

    if (p1 == 1 && m_usingPatterns2 == 0) {
        anims = TOPTR(EffectAnim*, (int)m_anims2);
        v4 = 0;
        for (; v4 < 0x40; v4++) {
            m_objects[v4].anims = TOPTR(EffectAnim*, (int)m_anims2);
        }
        m_patterns = TOPTR(PatternData*, (int)m_patterns2);
        m_usingPatterns2 = 1;
        return;
    }
    if (p1 == 0 && m_usingPatterns2 == 1) {
        anims = TOPTR(EffectAnim*, m_anims1);
        v8 = 0;
        for (; v8 < 0x40; v8++) {
            m_objects[v8].anims = TOPTR(EffectAnim*, m_anims1);
        }
        m_patterns = TOPTR(PatternData*, m_patterns1);
        m_usingPatterns2 = 0;
    }
}

void CNanase::PreUpdate()
{
}

void CNanase::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CNanase::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 135);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 7) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd4123641236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 5) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd4123641236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 8;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 6) {
            step = 7;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 5) {
            step = 6;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 4) {
            step = 5;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 6) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd214214A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 5) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd214214A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 6;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 4) {
            step = 5;
        }
        if ((input & kInputDirections) == kInputDown && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 0x3e8 && m_swordThrown == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 6) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd236236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 5) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd236236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 6;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 4) {
            step = 5;
        }
        if ((input & kInputDirections) == kInputDown && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 0x3e8 && m_swordThrown == 1) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 3) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd41236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 2) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd41236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 3;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 60);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 3) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd623A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 2) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd623A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 3;
        }
        if ((input & kInputDirections) == kInputDown && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 45);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 3) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 2) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 3;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputDown && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 45);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 3) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd412A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == kInputDown && step == 2) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd412A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 3;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 45);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 3) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd214A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 2) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd214A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 3;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputDown && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 5);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputUp) != 0 && step == 1) {
            m_command = kCmdUp;
            return;
        }
        if ((input & kInputUp) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputD) != 0 && step == 4) {
            m_command = kCmd22D;
            return;
        }
        if ((input & kInputDirections) == kInputDown && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == 0 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == kInputDown && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == 0 && step == 0 && pattern == kWakeUp) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputC) != 0 && step == 4) {
            m_command = kCmd22C;
            return;
        }
        if ((input & kInputDirections) == kInputDown && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == 0 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == kInputDown && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 45);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputB) != 0 && step == 4) {
            m_command = kCmd22B;
            return;
        }
        if ((input & kInputDirections) == kInputDown && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == 0 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == kInputDown && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 45);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputA) != 0 && step == 4) {
            m_command = kCmd22A;
            return;
        }
        if ((input & kInputDirections) == kInputDown && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == 0 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == kInputDown && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 45);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputDirections) == kInputRight && step == 3) {
            m_command = kCmdDashRight;
            return;
        }
        if ((input & kInputDirections) == 0 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == kInputRight && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 45);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputDirections) == kInputLeft && step == 3) {
            m_command = kCmdDashLeft;
            break;
        }
        if ((input & kInputDirections) == 0 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == kInputLeft && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == 0 && step == 0) {
            step = 1;
        }
    }
}

void CNanase::CpuInput()
{
    double dx; // how far the opponent is in front
    double dy; // how far the opponent is above or below

    m_command = kCmdNone;
    if (m_cpuWalkRight > 0) {
        m_cpuWalkRight--;
    }
    if (m_cpuWalkLeft > 0) {
        m_cpuWalkLeft--;
    }
    m_inputX = 0;
    m_inputY = 0;
    m_pressA = 0;
    m_pressB = 0;
    m_pressC = 0;
    m_pressD = 0;
    m_recoilGuardWindow = 0;
    if ((WORD)Random(0, 0x3e8) < 25.0f * m_cpuSkill + (y < 0.0) * 0x1e * m_cpuSkill + (m_cpuAction == 3) * 0x190 + (pattern == kRecoilGuardAir) * 0x12c) {
        m_recoilGuardWindow = 0x3c;
    }
    if ((WORD)Random(0, 0x7d0) < ((m_throwProtect > 0) * 4.0 + 1.0) * 8.0 * m_cpuSkill * ((pattern > kLastHitReaction && pattern < kAirRecoveryForward) * 2 + 1)) {
        m_recoilGuardWindow = 0x3c;
    }
    if ((WORD)Random(0, 0x3e8) < 4e+01f * m_cpuSkill && pattern > kLastSharedAction) {
        m_recoilGuardWindow = 0x3c;
    }
    if (m_canRecoilCounter == 1 && m_cpuAction == 2) {
        m_recoilGuardWindow = 0x1e;
        if (pattern < kFirstCharacterAction) {
            m_cpuAction = 0;
        }
        return;
    }
    if ((*m_opponent)->pattern == kWakeUp) {
        return;
    }
    dx = ((*m_opponent)->x - x) * facing;
    dy = fabs(y - (*m_opponent)->y);
    if (pattern >= kFirstHitReaction && pattern <= kFirstGuard && timer == 0) {
        if ((WORD)Random(0, 0x64) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        m_inputX = 1 - (((WORD)Random(0, 0x64) < 0x32) << 1);
        m_pressD = (WORD)Random(0, 0xf0) < dy;
        m_pressD = (WORD)Random(0, 0x140) < dx;
        if ((*m_opponent)->pattern > kLastSharedAction && (*m_opponent)->pattern < 0xfa && (*m_opponent)->frame < 3 && dy < 100.0 && dx < 150.0) {
            m_pressD = 0;
        }
        return;
    }
    if ((pattern >= kJump && pattern <= kJumpBack || pattern >= kSuperJump && pattern <= kSuperJumpBack) && y == 0.0) {
        return;
    }
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == k41236C && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kGrabHold && m_swordThrown == 0) {
        if ((*m_opponent)->vy > 0.0 && (*m_opponent)->y > -280.0 && (*m_opponent)->y < -20.0 && (WORD)Random(0, 0x3e8) < 2) {
            m_command = kCmd236A;
            return;
        }
        if ((*m_opponent)->vy > 0.0 && (*m_opponent)->y > -220.0 && (*m_opponent)->y < -20.0) {
            if ((WORD)Random(0, 0x3e8) < 0x1e) {
                m_command = kCmd236B;
            }
            if ((WORD)Random(0, 0x3e8) < 0xa && m_gauge == 0xbb8 && (*m_opponent)->y < -100.0) {
                m_command = kCmd236C;
            }
            return;
        }
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 40.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && (*m_opponent)->y == 0.0) {
                m_command = kCmd41236A;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_swordThrown == 0) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_swordThrown == 1) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx > 40.0 && dx < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if (dx > 60.0 && dx < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (dx < 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && (*m_opponent)->y == 0.0 && dx < 40.0 && (*m_opponent)->y == 0.0) {
                m_command = kCmd41236A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0 && m_swordThrown == 0) {
                m_command = kCmd623A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f + ((m_rfGauge > 500.0) << 1) && m_swordThrown == 0 && (*m_opponent)->y == 0.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f + ((m_rfGauge > 500.0) << 1) && m_swordThrown == 0) {
                m_command = ((WORD)Random(0, 1) == 1) + kCmd214B;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_gauge >= 0x3e8 && m_swordThrown == 0 && (*m_opponent)->y == 0.0) {
                m_command = kCmd214214A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && dx < 150.0 && m_gauge >= 0x3e8 && m_swordThrown == 1 && (*m_opponent)->y == 0.0) {
                m_command = kCmd236236A;
                return;
            }
        }
        if (dx < 160.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (dx < 220.0 && dx > 160.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
            m_command = (WORD)Random(0, 2) + kCmd236A;
            return;
        }
        if (dx > 220.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
            m_command = (WORD)Random(0, 2) + kCmd236A;
            return;
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && dx < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (dy < 80.0 && dx < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f && m_swordThrown == 0) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && dx < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0 && m_swordThrown == 0) {
            m_command = kCmd623A;
            return;
        }
        if (m_cpuRoll < 7 && m_rfGauge > 500.0 && m_swordThrown == 0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 0xa && m_rfGauge > 500.0 && m_swordThrown == 0) {
            m_command = kCmd214C;
            return;
        }
        if (m_cpuRoll < 0xd && m_rfGauge > 500.0 && m_swordThrown == 0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && m_swordThrown == 0) {
            m_command = (WORD)Random(0, 2) + kCmd214214A;
            return;
        }
        if (m_cpuRoll < 0x12 && m_cpuRoll > 0x16 && m_gauge >= 0x3e8 && m_swordThrown == 1) {
            m_command = (WORD)Random(0, 2) + kCmd236236A;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 0x14) {
            m_cpuAction = 2;
            return;
        }
        if (dx < 200.0 && m_cpuRoll < 0x20 && (*m_opponent)->y == 0.0 && dx * 0.5 > dy && dx * 0.3 < dy) {
            m_command = kCmd623C;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k623A || pattern == k623B || pattern == k214A || pattern == k214214Lv1 || pattern == k214214Lv2 || pattern == k214214Lv3)) {
        m_command = kCmd22C;
        return;
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 1.0f * m_cpuSkill && m_attackResult == 3 && (pattern == k236A && frame == 0xd || pattern == k236B && frame == 0xd)) {
        m_command = kCmd22C;
        return;
    }
    if (m_cpuAction > 0 && pattern > kLastFreeAction && pattern < kAirRecoveryBack) {
        m_cpuAction = 0;
    }
    if (m_cpuAction == 1 && pattern < kFirstCharacterAction) {
        m_cpuAction = 0;
    }
    if (m_cpuAction == 2 && m_canRecoilCounter != 1) {
        m_cpuAction = 0;
        return;
    }
    if (m_cpuAction == 4) {
        m_inputY = -1;
        m_inputX = (WORD)Random(0, 2) - 1;
        if (pattern == kJump || pattern == kJumpForward || pattern == kJumpBack) {
            m_command = facing == 1;
            if (pattern == kAirDashForward) {
                m_cpuAction = 0;
            }
            m_inputY = 0;
            m_inputX = 0;
            return;
        }
    }
    if (m_cpuAction == 5 && pattern < kFirstHitReaction) {
        m_command = facing == 1;
        if (pattern == kDashForward) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 6 && pattern < kFirstHitReaction) {
        m_command = facing == 1;
        if (pattern == kDashForward) {
            m_cpuAction = 7;
        }
        return;
    }
    if (m_cpuAction == 7 && pattern == kDashForward) {
        m_pressA = 1;
        if (pattern == kDashA) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 8 && pattern < kFirstHitReaction) {
        m_command = facing == 1;
        if (pattern == kDashForward) {
            m_cpuAction = 9;
        }
        return;
    }
    if (m_cpuAction == 9 && pattern == kDashForward) {
        m_pressA = 2;
        if (pattern == kDashB) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xa && pattern < kFirstHitReaction) {
        m_command = facing == 1;
        if (pattern == kDashForward) {
            m_cpuAction = 0xb;
        }
        return;
    }
    if (m_cpuAction == 0xb && pattern == kDashForward) {
        m_pressA = 3;
        if (pattern == kDashC) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xc && pattern < kFirstHitReaction) {
        m_command = kCmd41236A;
        if (pattern == k41236A) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 0x64) < m_cpuSkill * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 40.0 && m_cpuRoll < 0xa) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 125.0 && m_cpuRoll > 0x64 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1b8) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                if (m_attackResult == 3 && (WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x258 && dx < 100.0) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll < 0xc8 && m_attackResult == 3 && (*m_opponent)->y == 0.0 && dx < 80.0) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll < 0x190 && m_attackResult == 3 && (*m_opponent)->y == 0.0 && dx < 80.0) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll < 0x15e && (*m_opponent)->y == 0.0) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x226 && dx < 90.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x226 && m_cpuRoll < 0x2bc) {
                m_pressC = 1;
                m_inputY = (WORD)Random(0, 1) == 0;
                return;
            }
            if (m_cpuRoll > 0x398) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if (dx > 110.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = (WORD)Random(0, 1) == 0;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x190 && m_attackResult == 3) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x12c) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if (dx > 110.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == k5C) {
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && m_swordThrown == 1) {
                m_command = kCmd41236A;
                return;
            }
        }
        if (pattern == k2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 40.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x14) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (dx < 135.0 && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 5;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if (m_cpuRoll < 0x190 && dx < 80.0 && m_attackResult == 3) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll < 0x64 && (*m_opponent)->y == 0.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && m_swordThrown == 1) {
                m_command = kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1c2 && m_attackResult == 3 && m_gauge >= 0x3e8 && dx < 90.0) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                return;
            }
            if (dx < 60.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                return;
            }
            if (dx < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 3;
                }
                return;
            }
        }
        if (pattern == kJumpB) {
            if (m_cpuRoll > 0x50 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kJumpC) {
            if (m_cpuRoll > 0x3b6) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kDashB) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && m_swordThrown == 1) {
                m_command = kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x2bc) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x289 && (WORD)Random(0, 3) == 0) {
                m_cpuAction = 6;
                if (dx > 110.0) {
                    m_cpuAction = 8;
                }
            }
        }
    }
    if ((WORD)Random(0, 0x64) < 25.0f * m_cpuSkill) {
        if (m_swordThrown == 1) {
            m_pressD = 1;
        }
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown) {
                if (dx < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 3) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (dx < 50.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 8) {
                    m_command = kCmd41236A;
                    return;
                }
                if (0x64 - (m_swordThrown == 1) * 0x1e > dx && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if ((m_swordThrown == 1) * 0xa + 0x64 > dx && dx > 70.0 && m_cpuRoll < 0xf) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (0x8c - (m_swordThrown == 1) * 0x28 > dx && m_cpuRoll < 0x14) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx > 160.0 && m_cpuRoll < 0x1a) {
                    m_cpuAction = 8;
                    return;
                }
                if (dx > 160.0 && m_cpuRoll < 0x20) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (0xaa - (m_swordThrown == 1) * 0x3c > dx && 0x78 - (m_swordThrown == 1) * 0x28 < dx && m_cpuRoll < 0x25) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 220.0 && dx > 70.0 && m_cpuRoll < 0x28) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 0x2a && m_cpuRoll > 0x28) {
                    m_command = kCmd623A;
                    return;
                }
                if (m_cpuRoll < 0x2a && m_cpuRoll > 0x32) {
                    m_command = facing;
                    m_cpuAction = 5;
                    return;
                }
                if (dx > 180.0 && m_cpuRoll > 0xfa && m_cpuRoll < 0xfc && m_gauge >= 0x3e8) {
                    m_command = (WORD)Random(0, 2) + kCmd214214A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0) {
                    if (dx < 80.0 && dy < 120.0 && m_cpuRoll < 0xa) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx < 120.0 && m_cpuRoll < 0x1e && m_swordThrown == 0) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (dx > 80.0 && dx < 120.0 && dy > 70.0 && m_cpuRoll < 0x1e && m_swordThrown == 1) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (dx > 120.0 && dx < 180.0 && dy > 90.0 && m_cpuRoll < 0x1e && m_swordThrown == 1) {
                        m_cpuAction = 0xa;
                        return;
                    }
                    if (dx < 80.0 && dy < 120.0 && m_cpuRoll < 0x23) {
                        m_command = kCmd623B;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 80.0 && dy < 120.0) {
                        if (m_cpuRoll < (m_rfGauge > 500.0 || m_rfBlue > 0) * 5 + 6) {
                            m_command = kCmd623A;
                            return;
                        }
                    }
                    if (dx < 90.0 && dy < 120.0 && dy > 90.0 && m_cpuRoll < 0xf) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (dx < 120.0 && dy < 100.0 && m_cpuRoll < 0x11 && m_gauge == 0xbb8) {
                        m_command = kCmd4123641236D;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 100.0 && dy < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->y == 0.0) * 0x64 + 0x64) {
                        m_pressA = 1;
                        return;
                    }
                }
                if (dx < 120.0 && dy < 100.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x104) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 140.0 && dx > 80.0 && dy > 40.0 && dy < 80.0 && m_cpuRoll > 0x104 && m_cpuRoll < 0x109) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 120.0 && dy < 90.0 && (*m_opponent)->y > y && m_cpuRoll < 0x6e) {
                    m_pressA = 1;
                    return;
                }
                if (dx < 120.0 && dy < 90.0 && m_cpuRoll < 0x136) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 150.0 && dx > 100.0 && dy < 90.0 && m_cpuRoll < 0x190) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 3.0f * m_cpuSkill) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && dx > 60.0 && dx < 100.0 && (WORD)Random(0, 0x64) < 1.0f * m_cpuSkill) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if ((WORD)Random(0, 0x3e8) < 2) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 0x64) < 2) {
        if ((WORD)Random(0, 0x64) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (dx > 160.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx < 100.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx < 170.0 && dx > 120.0 && y == 0.0) {
            m_inputX = facing;
            m_inputY = -1;
            return;
        }
    }
    if (m_cpuWalkRight > 0) {
        if ((char)AtScreenEdge() != 0 && m_cpuWalkRight > 0xf) {
            m_cpuWalkRight = 0xf;
        }
        m_inputX = 1;
        return;
    }
    if (m_cpuWalkLeft > 0) {
        if ((char)AtScreenEdge() != 0 && m_cpuWalkLeft > 0xf) {
            m_cpuWalkLeft = 0xf;
        }
        m_inputX = -1;
        return;
    }
    if ((WORD)Random(0, 0x64) < 0x32 && dx < 120.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x3c;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x3c) {
        if (facing == 1) {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x1e;
        } else {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x1e;
        }
        return;
    }
    if (facing == -1) {
        m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x1e;
        return;
    }
    m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x1e;
}

void CNanase::UpdateObjects()
{
    WORD frameCount; // frames in the object's animation
    WORD duration; // ticks the object's current frame lasts
    int slot; // the object being updated, an index into m_objects

    if (m_usingPatterns2 == 1) {
        UpdateObjects2();
        return;
    }
    if ((*m_opponent)->m_freezeTime > 0) {
        return;
    }
    slot = m_objectTail;
    EffectDesc effect; // what CreateEffect or SpawnObject is to make
    while (slot != m_objectHead) {
        if (m_objectActive[slot] != 0 && m_objects[slot].hitstop == 0 && (m_freezeTime == 0 || m_freezeTime > 0 && m_objects[slot].movesInFreeze != 0)) {
            duration = (short)anims[m_objects[slot].pattern].frames[m_objects[slot].frame].duration;
            frameCount = anims[m_objects[slot].pattern].frameCount;
            InitEffectDesc((EffectDesc*)&effect);
            switch (m_objects[slot].pattern) {
            case kObjSwordThrown:
                if (m_objectState[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vx = 3.0;
                m_objects[slot].vy = 1.8;
                if (m_objects[slot].y > 0.0) {
                    RemoveObject(slot);
                    effect.type = 0x192;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    m_playVoice = 2;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjSwordTrail:
                if (m_objectState[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vx = 3.0;
                m_objects[slot].vy = 1.8;
                if (m_objects[slot].y > 0.0) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSwordImpact:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjRock1:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].vy = -2.0 - (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if ((m_objects[slot].vy + m_objects[slot].y > 0.0 || m_objects[slot].attackResult > 1) && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    m_playVoice = 1;
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjRock2:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 5) * 0.1;
                    m_objects[slot].vy = -2.3 - (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if ((m_objects[slot].vy + m_objects[slot].y > 0.0 || m_objects[slot].attackResult > 1) && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    m_playVoice = 1;
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjRock3:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 4) * 0.1;
                    m_objects[slot].vy = -2.5 - (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if ((m_objects[slot].vy + m_objects[slot].y > 0.0 || m_objects[slot].attackResult > 1) && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    RemoveObject(slot);
                    m_playVoice = 1;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjRock4:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0xd) * 0.1;
                    m_objects[slot].vy = -1.7 - (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if ((m_objects[slot].vy + m_objects[slot].y > 0.0 || m_objects[slot].attackResult > 1) && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    m_playVoice = 1;
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjPebble:
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].vy = -1.0 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectState[slot] = 1;
                }
                m_objects[slot].vy += 0.035;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 1) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].scale = 1;
                    m_objectState[slot] = 2;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 2) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjPebble2:
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0xf) * 0.1;
                    m_objects[slot].vy = -1.0 - (WORD)Random(0, 0xf) * 0.05;
                    m_objectState[slot] = 1;
                }
                m_objects[slot].vy += 0.045;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 1) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].scale = 1;
                    m_objectState[slot] = 2;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 2) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObj214Impact:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabLv4Fx:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjSuperSwordLv1:
                m_superSwordX = (int)m_objects[slot].x;
                m_superSwordY = (int)m_objects[slot].y;
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = 1.0;
                    m_objectState[slot] = 1;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 1) {
                    effect.type = 0x1a6;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    m_superSwordY = 0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjSuperSwordBounce;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = -8.5;
                    m_objects[slot].ay = 0.035;
                    m_objects[slot].scale = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 5) {
                        m_objects[slot].hitsLeft = 1;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSuperSwordLv2:
                m_superSwordX = (int)m_objects[slot].x;
                m_superSwordY = (int)m_objects[slot].y;
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = 2.4;
                    m_objects[slot].vy = 0.8;
                    m_objectState[slot] = 1;
                }
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 1) {
                    m_playSound = 0x16;
                    effect.type = 0x1a9;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x + facing * 0x50);
                    effect.y = 15.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x - facing * 0x50);
                    effect.y = 15.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    m_superSwordY = 0;
                    ShakeScreen(0xa, 0);
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjSuperSwordBounce;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vx = 0.1;
                    m_objects[slot].vy = -5.5;
                    m_objects[slot].ay = 0.01;
                    m_objects[slot].scale = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 5) {
                        m_objects[slot].hitsLeft = 1;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSuperSwordLv3:
                m_superSwordX = (int)m_objects[slot].x;
                m_superSwordY = (int)m_objects[slot].y;
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = 2.4;
                    m_objects[slot].vy = 0.4;
                    m_objectState[slot] = 1;
                }
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 1) {
                    m_playSound = 0x16;
                    effect.type = 0x1aa;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x + facing * 0x50);
                    effect.y = 15.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x - facing * 0x50);
                    effect.y = 15.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x + facing * 0x28);
                    effect.y = -80.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x - facing * 0x28);
                    effect.y = -80.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    m_superSwordY = 0;
                    ShakeScreen(0xa, 0);
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjSuperSwordBounce;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vx = 0.1;
                    m_objects[slot].vy = -5.5;
                    m_objects[slot].ay = 0.01;
                    m_objects[slot].scale = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 5) {
                        m_objects[slot].hitsLeft = 1;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSuperSwordTrail:
                m_objects[slot].x = m_superSwordX;
                m_objects[slot].y = m_superSwordY;
                if (m_superSwordY == 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 5) {
                        m_objects[slot].hitsLeft = 1;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSparkle:
                if (m_objectState[slot] <= 0) {
                    effect.type = 0x22;
                    effect.x = (double)((int)m_objects[slot].x + (0x14 - (WORD)Random(0, 0x28)) * facing);
                    effect.y = (double)((int)m_objects[slot].y + 0x14 - (WORD)Random(0, 0x28));
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objectState[slot] = 2;
                }
                m_objectState[slot]--;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214CShockwave:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 2.0;
                    m_playVoice = 0;
                    effect.type = 0x19b;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 4) + 0x195;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 4) + 0x195;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 4) + 0x195;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 4) + 0x195;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 3) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                            break;
                        }
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Aura:
                m_armorTime = 2;
                m_noGuardTime = 2;
                m_lv4Time--;
                StartAfterimages(1);
                m_defense = 0.5;
                if (m_lv4Time <= 0) {
                    m_lv4Time = 0;
                    RemoveObject(slot);
                    m_armorTime = 0;
                    m_noGuardTime = 0;
                    m_defense = 1.0;
                    break;
                }
                if (m_objectState[slot] <= 0) {
                    effect.type = 0x22;
                    effect.x = (double)((int)x + (0x14 - (WORD)Random(0, 0x28)) * facing);
                    effect.y = (double)((int)y - (WORD)Random(0, 0x5a));
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objectState[slot] = 2;
                }
                m_objectState[slot]--;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjFallInDarkness:
                m_objects[slot].vx = -0.02;
                m_objects[slot].drawnWhileHidden = 0x7530;
                m_objects[slot].timer++;
                if (pattern != kFallInDarkness) {
                    RemoveObject(slot);
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjEncasedBreak:
                if (pattern != kEncased && pattern != kEncased2 && pattern != kEncasedAir && pattern != kEncasedSpin || pattern == kEncased && frame > 1 || pattern == kEncased2 && frame > 1) {
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x + facing * 0x17);
                    effect.y = (double)((int)y - 4);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x - (facing << 2));
                    effect.y = (double)((int)y - 6);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x - facing * 0xe);
                    effect.y = (double)((int)y - 0x1a);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)(int)x;
                    effect.y = (double)(int)y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x + facing * 0x1e);
                    effect.y = (double)((int)y - 0x28);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x - facing * 0x19);
                    effect.y = (double)((int)y - 0x50);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x - facing * 0x23);
                    effect.y = (double)((int)y - 0x2a);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x - facing * 0x12);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x + facing * 2);
                    effect.y = (double)((int)y - 0x41);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x + (facing << 4));
                    effect.y = (double)((int)y - 0x50);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_playSound = 0x22;
                    RemoveObject(slot);
                    m_encasedBreakOut = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjShardSmall:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectState[slot] == 0) {
                    m_objectTimer[slot] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectState[slot]++;
                    m_objects[slot].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[slot].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectTimer[slot] < 0xa) {
                    m_objects[slot].scale = 1;
                }
                if (m_objectTimer[slot] < 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjShardLarge:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectState[slot] == 0) {
                    m_objectTimer[slot] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    m_objectState[slot]++;
                    m_objects[slot].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[slot].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[slot].vy += 0.03;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectTimer[slot] < 0xa) {
                    m_objects[slot].scale = 1;
                }
                if (m_objectTimer[slot] < 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjBurnFlames:
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
            }
        }
        slot++;
        if (slot >= 0x40) {
            slot = 0;
        }
    }
}

void CNanase::UpdateObjects2()
{
    WORD frameCount; // frames in the object's animation
    WORD duration; // ticks the object's current frame lasts
    int slot; // the object being updated, an index into m_objects

    if ((*m_opponent)->m_freezeTime > 0) {
        return;
    }
    slot = m_objectTail;
    EffectDesc effect; // what CreateEffect or SpawnObject is to make
    while (slot != m_objectHead) {
        if (m_objectActive[slot] != 0 && m_objects[slot].hitstop == 0 && (m_freezeTime == 0 || m_freezeTime > 0 && m_objects[slot].movesInFreeze != 0)) {
            duration = (short)anims[m_objects[slot].pattern].frames[m_objects[slot].frame].duration;
            frameCount = anims[m_objects[slot].pattern].frameCount;
            InitEffectDesc((EffectDesc*)&effect);
            switch (m_objects[slot].pattern) {
            case kObjSwordThrown:
                if (m_objectState[slot] == 0) {
                    m_objects[slot].hitsLeft = 0x63;
                    m_objectState[slot]++;
                    m_objects[slot].attackResult = 0;
                }
                if (m_objectTimer[slot] >= 0xf) {
                    m_objectTimer[slot] = 0;
                    m_objects[slot].attackResult = 0;
                }
                m_objectTimer[slot]++;
                m_objects[slot].vx = 3.0;
                m_objects[slot].vy = 1.8;
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].y > 0.0) {
                    m_objects[slot].pattern = kObjSwordBounce;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.8;
                    m_objects[slot].vy = -3.1;
                    m_objects[slot].ay = 0.02;
                    effect.type = 0x192;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    m_playVoice = 2;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjSwordTrail:
                effect.type = 0x22;
                effect.x = (double)((int)m_objects[slot].x + 0x28 - (WORD)Random(0, 0x50));
                effect.y = (double)((int)m_objects[slot].y + 0x14 - (WORD)Random(0, 0x28));
                effect.scale = 2;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                if (m_objectState[slot] == 0) {
                    m_objects[slot].hitsLeft = 0x63;
                    m_objectState[slot]++;
                    m_objects[slot].attackResult = 0;
                }
                m_objects[slot].vx = 3.0;
                m_objects[slot].vy = 1.8;
                if (m_objects[slot].y > 0.0) {
                    RemoveObject(slot);
                }
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].attackResult = 0;
                    }
                }
                break;
            case kObjSwordImpact:
                if (m_objects[slot].frame == 1) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame < 0xc && (WORD)Random(0, 0x64) < 0xa) {
                    effect.type = 0x1ab;
                    effect.x = (double)(int)(m_objects[slot].x - 50.0 + (WORD)Random(0, 0x64));
                    effect.y = (double)(int)(m_objects[slot].y - (WORD)Random(0, 0x64));
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjSwordBounce:
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].ay = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjSwordOnFloor;
                    break;
                }
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = -m_objects[slot].vx;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = -m_objects[slot].vx;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSwordOnFloor:
                if (m_objects[slot].x - x < 30.0 && m_objects[slot].x - x > -30.0 && m_pressD == 1 && pattern < kCrouch) {
                    RemoveObject(slot);
                    pattern = kPickUpSword;
                    StartPattern();
                    UsePatterns2(0);
                    m_swordThrown = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjRock1:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].vy = -2.0 - (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    SpawnObject(&effect);
                    m_playVoice = 1;
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjRock2:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 5) * 0.1;
                    m_objects[slot].vy = -2.3 - (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    SpawnObject(&effect);
                    m_playVoice = 1;
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjRock3:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 4) * 0.1;
                    m_objects[slot].vy = -2.5 - (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    SpawnObject(&effect);
                    RemoveObject(slot);
                    m_playVoice = 1;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjRock4:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0xd) * 0.1;
                    m_objects[slot].vy = 1.7 - (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    SpawnObject(&effect);
                    m_playVoice = 1;
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjPebble:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].vy = -1.0 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objects[slot].scale == 1) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjPebble2:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0xa) * 0.1;
                    m_objects[slot].vy = -1.0 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectState[slot]++;
                }
                m_objects[slot].vy += 0.035;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objects[slot].scale == 0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].scale = 1;
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objects[slot].scale == 1) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObj214Impact:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabLv4Fx:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjSwordThrownC:
                if (m_objectState[slot] == 0) {
                    m_objects[slot].hitsLeft = 0x63;
                    m_objectState[slot]++;
                    m_objects[slot].attackResult = 0;
                }
                if (m_objectTimer[slot] >= 0xf) {
                    m_objectTimer[slot] = 0;
                    m_objects[slot].attackResult = 0;
                }
                m_objectTimer[slot]++;
                m_objects[slot].vx = 3.0;
                m_objects[slot].vy = 1.8;
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].y > 0.0) {
                    m_objects[slot].pattern = kObjSwordBounce;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.8;
                    m_objects[slot].vy = -3.1;
                    m_objects[slot].ay = 0.02;
                    effect.type = 0x19e;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    m_playVoice = 2;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjSwordImpactC:
                m_objects[slot].hitsLeft = 1;
                if (m_objects[slot].frame == 4 && m_objects[slot].timer == 0 && m_objects[slot].y > -10.0) {
                    effect.type = 0x19e;
                    effect.x = (double)(int)(m_objects[slot].x + 60.0 - (WORD)Random(0, 0x78));
                    effect.y = (double)(int)(m_objects[slot].y - 4.0);
                    effect.facing = facing;
                    m_playVoice = 2;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].frame < 0xc && (WORD)Random(0, 0x64) < 0xa) {
                    effect.type = 0x1ab;
                    effect.x = (double)(int)(m_objects[slot].x - 50.0 + (WORD)Random(0, 0x64));
                    effect.y = (double)(int)(m_objects[slot].y - (WORD)Random(0, 0x64));
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjSuperSwordLv1:
                m_superSwordX = (int)m_objects[slot].x;
                m_superSwordY = (int)m_objects[slot].y;
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = 1.2;
                    m_objectState[slot] = 1;
                }
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 1) {
                    m_playSound = 0x16;
                    effect.type = 0x1a6;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    m_superSwordY = 0;
                    ShakeScreen(0xa, 0);
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjSuperSwordBounce;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vx = 0.1;
                    m_objects[slot].vy = -3.5;
                    m_objects[slot].ay = 0.01;
                    m_objects[slot].scale = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 5) {
                        m_objects[slot].hitsLeft = 1;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSuperSwordLv2:
                m_superSwordX = (int)m_objects[slot].x;
                m_superSwordY = (int)m_objects[slot].y;
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = 2.4;
                    m_objects[slot].vy = 0.8;
                    m_objectState[slot] = 1;
                }
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 1) {
                    m_playSound = 0x16;
                    effect.type = 0x1a9;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x + facing * 0x28);
                    effect.y = 15.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x - facing * 0x28);
                    effect.y = 15.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    m_superSwordY = 0;
                    ShakeScreen(0xa, 0);
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjSuperSwordBounce;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vx = 0.1;
                    m_objects[slot].vy = -3.5;
                    m_objects[slot].ay = 0.01;
                    m_objects[slot].scale = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 5) {
                        m_objects[slot].hitsLeft = 1;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSuperSwordLv3:
                m_superSwordX = (int)m_objects[slot].x;
                m_superSwordY = (int)m_objects[slot].y;
                if (m_objectState[slot] == 0) {
                    m_objects[slot].vx = 2.4;
                    m_objects[slot].vy = 0.4;
                    m_objectState[slot] = 1;
                }
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy + m_objects[slot].y > 0.0 && m_objectState[slot] == 1) {
                    m_playSound = 0x16;
                    effect.type = 0x1aa;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x + facing * 0x3c);
                    effect.y = 15.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x - facing * 0x3c);
                    effect.y = 15.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x + facing * 0x1e);
                    effect.y = -30.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    effect.type = 0x1a5;
                    effect.x = (double)(int)(m_objects[slot].x - facing * 0x1e);
                    effect.y = -30.0;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    m_superSwordY = 0;
                    ShakeScreen(0xa, 0);
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjSuperSwordBounce;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vx = 0.1;
                    m_objects[slot].vy = -3.5;
                    m_objects[slot].ay = 0.01;
                    m_objects[slot].scale = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 5) {
                        m_objects[slot].hitsLeft = 1;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSuperSwordSplash:
                if (m_objects[slot].frame < 0xc && (WORD)Random(0, 0x64) < 0xa) {
                    effect.type = 0x1ab;
                    effect.x = (double)(int)(m_objects[slot].x - 50.0 + (WORD)Random(0, 0x64));
                    effect.y = (double)(int)(m_objects[slot].y - (WORD)Random(0, 0x64));
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjSuperSwordImpactLv1:
                if (m_objects[slot].frame == 1) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame < 0xc && (WORD)Random(0, 0x64) < 0x14) {
                    effect.type = 0x1ab;
                    effect.x = (double)(int)(m_objects[slot].x - 50.0 + (WORD)Random(0, 0x64));
                    effect.y = (double)(int)(m_objects[slot].y - (WORD)Random(0, 0x64));
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjSuperSwordImpactLv2:
                if (m_objects[slot].frame == 1) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame < 0xc && (WORD)Random(0, 0x64) < 0x14) {
                    effect.type = 0x1ab;
                    effect.x = (double)(int)(m_objects[slot].x - 50.0 + (WORD)Random(0, 0x64));
                    effect.y = (double)(int)(m_objects[slot].y - (WORD)Random(0, 0x64));
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjSuperSwordImpactLv3:
                if (m_objects[slot].frame == 1) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame < 0xc && (WORD)Random(0, 0x64) < 0x14) {
                    effect.type = 0x1ab;
                    effect.x = (double)(int)(m_objects[slot].x - 50.0 + (WORD)Random(0, 0x64));
                    effect.y = (double)(int)(m_objects[slot].y - (WORD)Random(0, 0x64));
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjSuperSwordTrail:
                m_objects[slot].x = m_superSwordX;
                m_objects[slot].y = m_superSwordY;
                effect.type = 0x22;
                effect.x = (double)((int)m_objects[slot].x + 0x28 - (WORD)Random(0, 0x50));
                effect.y = (double)((int)m_objects[slot].y + 0x14 - (WORD)Random(0, 0x28));
                effect.scale = 2;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                if (m_superSwordY == 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 5) {
                        m_objects[slot].hitsLeft = 1;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSuperSwordBounce:
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].ay = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjSwordOnFloor;
                    break;
                }
                if (m_objects[slot].x > 620.0) {
                    m_objects[slot].x = 620.0;
                    m_objects[slot].vx = -m_objects[slot].vx;
                }
                if (m_objects[slot].x < 20.0) {
                    m_objects[slot].x = 20.0;
                    m_objects[slot].vx = -m_objects[slot].vx;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjSparkle:
                if (m_objectState[slot] <= 0) {
                    effect.type = 0x22;
                    effect.x = (double)((int)m_objects[slot].x + (0x14 - (WORD)Random(0, 0x28)) * facing);
                    effect.y = (double)((int)m_objects[slot].y + 0x14 - (WORD)Random(0, 0x28));
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objectState[slot] = 2;
                }
                m_objectState[slot]--;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214CShockwave:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 2.0;
                    m_playVoice = 0;
                    effect.type = 0x19b;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 1) + 0x199;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 4) + 0x195;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 4) + 0x195;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 4) + 0x195;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                    effect.type = (WORD)Random(0, 4) + 0x195;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * (0x28 - (WORD)Random(0, 0x46)));
                    effect.y = (double)(int)m_objects[slot].y;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 3) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                            break;
                        }
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Aura:
                m_armorTime = 2;
                m_noGuardTime = 2;
                m_lv4Time--;
                StartAfterimages(1);
                m_defense = 0.5;
                if (m_lv4Time <= 0) {
                    m_defense = 1.0;
                    m_lv4Time = 0;
                    RemoveObject(slot);
                    m_armorTime = 0;
                    m_noGuardTime = 0;
                    break;
                }
                if (m_objectState[slot] <= 0) {
                    effect.type = 0x22;
                    effect.x = (double)((int)x + (0x14 - (WORD)Random(0, 0x28)) * facing);
                    effect.y = (double)((int)y - (WORD)Random(0, 0x5a));
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objectState[slot] = 2;
                }
                m_objectState[slot]--;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjFallInDarkness:
                m_objects[slot].vx = -0.02;
                m_objects[slot].drawnWhileHidden = 0x7530;
                m_objects[slot].timer++;
                if (pattern != kFallInDarkness) {
                    RemoveObject(slot);
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjEncasedBreak:
                if (pattern != kEncased && pattern != kEncased2 && pattern != kEncasedAir && pattern != kEncasedSpin || pattern == kEncased && frame > 1 || pattern == kEncased2 && frame > 1) {
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x + facing * 0x17);
                    effect.y = (double)((int)y - 4);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x - (facing << 2));
                    effect.y = (double)((int)y - 6);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x - facing * 0xe);
                    effect.y = (double)((int)y - 0x1a);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)(int)x;
                    effect.y = (double)(int)y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x + facing * 0x1e);
                    effect.y = (double)((int)y - 0x28);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x - facing * 0x19);
                    effect.y = (double)((int)y - 0x50);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x - facing * 0x23);
                    effect.y = (double)((int)y - 0x2a);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x - facing * 0x12);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x + facing * 2);
                    effect.y = (double)((int)y - 0x41);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x + (facing << 4));
                    effect.y = (double)((int)y - 0x50);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_playSound = 0x22;
                    RemoveObject(slot);
                    m_encasedBreakOut = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjShardSmall:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectState[slot] == 0) {
                    m_objectTimer[slot] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectState[slot]++;
                    m_objects[slot].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[slot].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectTimer[slot] < 0xa) {
                    m_objects[slot].scale = 1;
                }
                if (m_objectTimer[slot] < 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjShardLarge:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectState[slot] == 0) {
                    m_objectTimer[slot] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    m_objectState[slot]++;
                    m_objects[slot].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[slot].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[slot].vy += 0.03;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectTimer[slot] < 0xa) {
                    m_objects[slot].scale = 1;
                }
                if (m_objectTimer[slot] < 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjBurnFlames:
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
            }
        }
        slot++;
        if (slot >= 0x40) {
            slot = 0;
        }
    }
}
