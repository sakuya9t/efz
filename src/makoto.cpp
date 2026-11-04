// CMakoto (0x5f6d90-0x60792f): the character class whose files are in makoto\ in the game
// folder (makoto.dat sprites, makoto.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMakoto::CMakoto(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

    strcpy(m_name, "makoto");
    lastSurface = 459;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_bounceDebrisOut = 0;
    m_bouncerOut = 0;
    m_pointX[0] = -7;
    m_pointY[0] = -51;
    m_pointX[1] = 6;
    m_pointY[1] = 0;
    m_pointX[2] = 17;
    m_pointY[2] = -15;
    m_pointX[3] = 19;
    m_pointY[3] = -11;
    m_pointX[4] = 22;
    m_pointY[4] = -30;
    m_resultPictures = 5;
    m_rivals[0] = 1;
    m_rivals[1] = 5;
    m_rivals[10] = 3;
    i = 0;
    for (; i < 64; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
}

void CMakoto::Reset()
{
    int i;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_bounceDebrisOut = 0;
    m_bouncerOut = 0;
    m_pointX[0] = -7;
    m_pointY[0] = -51;
    m_pointX[1] = 6;
    m_pointY[1] = 0;
    m_pointX[2] = 17;
    m_pointY[2] = -15;
    m_pointX[3] = 19;
    m_pointY[3] = -11;
    m_pointX[4] = 22;
    m_pointY[4] = -30;
    i = 0;
    for (; i < 64; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
    CPlayer::Reset();
}

void CMakoto::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CMakoto::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
}

void CMakoto::Move()
{
    MoveOnGround();
}

void CMakoto::StartCommand()
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
        if (m_hp < 3333 && m_command == kCmd263D && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4Heal].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4Heal;
            return;
        }
        if (m_command == kCmd641236C && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236Lv3].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236Lv3;
            return;
        }
        if ((m_command == kCmd641236B || m_command == kCmd641236C) && m_gauge >= 2000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236Lv2].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236Lv2;
            return;
        }
        if ((m_command == kCmd641236A || m_command == kCmd641236B || m_command == kCmd641236C) && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236Lv1].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236Lv1;
            return;
        }
        if (m_command == kCmd236236C && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236C;
            return;
        }
        if (m_command == kCmd236236B && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236B;
            return;
        }
        if (m_command == kCmd236236A && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236A;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv3].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv3;
            if (y < 0.0) {
                frame = 3;
            }
            return;
        }
        if ((m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 2000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv2].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv2;
            if (y < 0.0) {
                frame = 3;
            }
            return;
        }
        if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv1].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv1;
            if (y < 0.0) {
                frame = 3;
            }
            return;
        }
        if (m_command == kCmd623C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623C;
            return;
        }
        if ((m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623B;
            return;
        }
        if ((m_command == kCmd623A || m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
            return;
        }
        if (m_command == kCmd412C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_bouncerOut == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k412C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412C;
            return;
        }
        if ((m_command == kCmd412B || m_command == kCmd412C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_bouncerOut == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k412B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412B;
            return;
        }
        if ((m_command == kCmd412A || m_command == kCmd412B || m_command == kCmd412C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_bouncerOut == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k412A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412A;
            return;
        }
        if (m_command == kCmd214C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            return;
        }
        if ((m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            return;
        }
        if ((m_command == kCmd214A || m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            if (y < 0.0) {
                pattern = kAir214A;
            }
            return;
        }
        if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            return;
        }
        if ((m_command == kCmd236B || m_command == kCmd236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236B;
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236A].level) {
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
        if ((m_inputY == 0 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k6B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k6B;
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
                if (m_inputY > 0) {
                    pattern = kJump2C;
                }
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

void CMakoto::DrawGauge()
{
}

void CMakoto::PreUpdate()
{
}

void CMakoto::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CMakoto::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 75);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 4) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd641236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 3) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd641236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 4;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 0 && m_gauge >= 1000) {
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
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 1000) {
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
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 1000) {
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
    pos = m_inputPos + (kInputHistoryLength - 60);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputD) != 0 && step == 3) {
            m_command = kCmd263D;
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 2) {
            if ((input & kInputD) != 0) {
                m_command = kCmd263D;
                return;
            }
            step = 3;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge == 3000) {
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

void CMakoto::CpuInput()
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
    if ((WORD)Random(0, 1000) < 25.0f * m_cpuSkill + (y < 0.0) * 30 * m_cpuSkill + (m_cpuAction == 3) * 400 + (pattern == kRecoilGuardAir) * 300) {
        m_recoilGuardWindow = 60;
    }
    if ((WORD)Random(0, 2000) < ((m_throwProtect > 0) * 4.0 + 1.0) * 8.0 * m_cpuSkill * ((pattern > kLastHitReaction && pattern < kAirRecoveryForward) * 2 + 1)) {
        m_recoilGuardWindow = 60;
    }
    if ((WORD)Random(0, 1000) < 4e+01f * m_cpuSkill && pattern > kLastSharedAction) {
        m_recoilGuardWindow = 60;
    }
    if (m_canRecoilCounter == 1 && m_cpuAction == 2) {
        m_recoilGuardWindow = 30;
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
        if ((WORD)Random(0, 100) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        m_inputX = 1 - (((WORD)Random(0, 100) < 0x32) << 1);
        m_pressD = (WORD)Random(0, 240) < dy;
        m_pressD = (WORD)Random(0, 320) < dx;
        if ((*m_opponent)->pattern > kLastSharedAction && (*m_opponent)->pattern < 0xfa && (*m_opponent)->frame < 3 && dy < 100.0 && dx < 150.0) {
            m_pressD = 0;
        }
        return;
    }
    if ((pattern >= kJump && pattern <= kJumpBack || pattern >= kSuperJump && pattern <= kSuperJumpBack) && y == 0.0) {
        return;
    }
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == 0x108 && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 45.0 && (WORD)Random(0, 100) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && dx > 60.0 && dx < 70.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
            m_pressB = 1;
            m_inputY = 1;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (dx < 100.0) {
            if ((WORD)Random(0, 100) < m_cpuSkill * 5.0f && m_rfGauge > 500.0) {
                m_command = kCmd623A;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd623C;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 2 && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_gauge >= 2000) {
                m_command = (WORD)Random(0, 2) + kCmd641236B;
                return;
            }
        }
        if (dx < 150.0 && dx > 100.0) {
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if (dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 2 && m_gauge >= 2000) {
                m_command = (WORD)Random(0, 2) + kCmd641236B;
                return;
            }
        }
        if (dx > 150.0) {
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
                m_command = (WORD)Random(0, 2) + kCmd236B;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > 0.0 && y - (*m_opponent)->y < 50.0 && dx < 100.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < -20.0 && y - (*m_opponent)->y > -90.0 && dx < 110.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (dy < 100.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
            m_command = (WORD)Random(0, 2) + kCmd214214A;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 100);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0 && dx < 80.0) {
            m_command = kCmd623A;
            return;
        }
        if (m_cpuRoll < 5 && m_rfGauge > 500.0 && dx < 80.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 10 && m_cpuRoll > 5 && m_rfGauge > 500.0 && dx < 150.0) {
            m_command = kCmd412C;
            return;
        }
        if (m_cpuRoll < 17 && m_cpuRoll > 12 && m_gauge >= 1000 && dx < 100.0) {
            m_command = (WORD)Random(0, 3) + kCmd641236A;
            return;
        }
        if (m_cpuRoll < 17 && m_cpuRoll > 12 && m_gauge >= 1000 && dx > 90.0) {
            m_command = (WORD)Random(0, 3) + kCmd214214A;
            return;
        }
        if (m_cpuRoll > 65) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 100);
        if (m_cpuRoll < 17 && m_cpuRoll > 12 && m_gauge >= 1000 && dx > 50.0) {
            m_command = (WORD)Random(0, 3) + kCmd214214A;
            return;
        }
        if (m_cpuRoll > 60) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 100) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k623A || pattern == kDashC && (WORD)Random(0, 10) == 0 || pattern == k623B || pattern == 0xee)) {
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
        m_pressB = 1;
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
        m_pressC = 1;
        if (pattern == kDashC) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xc && pattern < kFirstHitReaction) {
        m_command = facing == 1;
        if (pattern == kDashForward) {
            m_cpuAction = 0xd;
        }
        return;
    }
    if (m_cpuAction == 0xd && pattern == kDashForward) {
        m_pressA = 1;
        m_inputY = 1;
        if (pattern == kDashA) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xe && pattern < kFirstHitReaction) {
        m_command = facing == 1;
        if (pattern == kDashForward) {
            m_cpuAction = 0xf;
        }
        return;
    }
    if (m_cpuAction == 0xf && pattern == kDashForward) {
        m_pressB = 1;
        m_inputY = 1;
        if (pattern == kDashB) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0x10 && pattern < kFirstHitReaction) {
        m_command = facing == 1;
        if (pattern == kDashForward) {
            m_cpuAction = 0x11;
        }
        return;
    }
    if (m_cpuAction == 0x11 && pattern == kDashForward) {
        m_pressC = 1;
        m_inputY = 1;
        if (pattern == kDashC) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0x14 && pattern < kFirstHitReaction) {
        m_pressA = 1;
        m_inputY = 1;
        if (pattern == k2A) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 100) < m_cpuSkill * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 1000);
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 45.0 && m_cpuRoll > 0 && m_cpuRoll < 300) {
                m_pressA = 1;
                m_inputY = Random(0, 2);
                return;
            }
            if (dx < 80.0 && m_cpuRoll > 0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 70.0 && m_cpuRoll > 300 && m_cpuRoll < 600) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 970) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 600) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 300 && m_cpuRoll < 550) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 550 && m_cpuRoll < 600 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 600 && m_cpuRoll < 750) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll < 100) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 100 && m_cpuRoll < 350 && dx < 130.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 450 && m_cpuRoll < 600 && dx < 70.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 600 && m_cpuRoll < 750) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 980) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 500) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 150 && m_cpuRoll < 200 && m_gauge >= 1000 && dx < 120.0) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 500) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 500) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                return;
            }
        }
        if (pattern == k5C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 300) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 600) {
                m_command = kCmd236A;
                if (dx > 160.0) {
                    m_command = kCmd236B;
                    if ((WORD)Random(0, 3) == 0) {
                        m_command = kCmd236C;
                    }
                }
                return;
            }
            if (m_cpuRoll > 600 && m_cpuRoll < 650) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 650 && m_cpuRoll < 670 && m_gauge >= 1000) {
                m_command = kCmd236236B;
                return;
            }
            if (m_cpuRoll > 900) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == k2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 45.0 && m_cpuRoll > 0 && m_cpuRoll < 300) {
                m_pressA = 1;
                m_inputY = Random(0, 2);
                return;
            }
            if (dx < 90.0 && m_cpuRoll > 0 && m_cpuRoll < 400) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 100.0 && m_cpuRoll > 300 && m_cpuRoll < 600) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 970) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 600) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 300 && m_cpuRoll < 550) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 550 && m_cpuRoll < 600 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 600 && m_cpuRoll < 750) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll < 100) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 100 && m_cpuRoll < 350 && dx < 130.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 450 && m_cpuRoll < 600 && dx < 70.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 600 && m_cpuRoll < 750) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 980) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 500) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 600 - (m_attackResult == 3) * 400 && m_cpuRoll < 650) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 300) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 600) {
                m_command = kCmd236A;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if (dx > 160.0) {
                    m_command = kCmd236B;
                    if ((WORD)Random(0, 3) == 0) {
                        m_command = kCmd236C;
                    }
                }
                return;
            }
            if (m_cpuRoll > 650 && m_cpuRoll < 670 && m_gauge >= 1000) {
                m_command = kCmd236236B;
                return;
            }
            if (m_cpuRoll > 900) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                return;
            }
            if (dx < 60.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                return;
            }
            if (dx < 125.0 && m_cpuRoll > 399 && m_cpuRoll < 700) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 699) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 3;
                }
                return;
            }
        }
        if (pattern == kJumpB) {
            if (m_cpuRoll > 20 && m_cpuRoll < 60 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 80 && m_cpuRoll < 300) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 950) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kJump2C) {
            if (m_cpuRoll > 950) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kDashB) {
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 210 && m_rfGauge > 350.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 220 && m_cpuRoll < 300) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 340) {
                m_command = kCmd412B;
                return;
            }
            if (m_cpuRoll > 400) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == kDash2B) {
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 210 && m_rfGauge > 350.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 220 && m_cpuRoll < 300) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 340) {
                m_command = kCmd412B;
                return;
            }
            if (m_cpuRoll > 400) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == kDash2C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 210 && m_rfGauge > 350.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 220 && m_cpuRoll < 300) {
                m_command = kCmd214A;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 340) {
                m_command = kCmd412B;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                return;
            }
            if (m_cpuRoll > 900) {
                m_cpuAction = 1;
            }
        }
        if (pattern == kDash2A && m_cpuRoll > 500) {
            m_cpuAction = 1;
            if (dx < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
    }
    if ((WORD)Random(0, 100) < 25.0f * m_cpuSkill) {
        m_cpuRoll = (WORD)Random(0, 1000);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown) {
                if (dx < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (dx < 60.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 15 + 20) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (dx < 45.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 15 + 20) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (dx > 50.0 && dx < 80.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 15 + 65 && m_cpuRoll > 40) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (70 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 70 < dx && dx < 95.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 20 + 80 && m_cpuRoll > 70) {
                        m_cpuAction = 0xc;
                        return;
                    }
                }
                if (80 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 70 < dx && dx < 110.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 15 + 128 && m_cpuRoll > 120) {
                        m_cpuAction = 8;
                        return;
                    }
                }
                if (dx < 180.0 && dx > 150.0 && m_cpuRoll < 170 && m_cpuRoll > 150) {
                    m_cpuAction = 0x10;
                    return;
                }
                if (dx < 130.0 && dx > 100.0 && m_cpuRoll < 195 && m_cpuRoll > 170) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (80 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 80 < dx && dx < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 25 + 185 && m_cpuRoll > 170) {
                        m_cpuAction = 0xe;
                        return;
                    }
                }
                if (90 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 90 < dx && dx < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 25 + 225 && m_cpuRoll > 210) {
                        m_cpuAction = 0xa;
                        return;
                    }
                }
                if (dx > 130.0 && dx < 170.0 && m_cpuRoll < 260 && m_cpuRoll > 250) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 275 && m_cpuRoll > 260 && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd623C;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 280 && m_cpuRoll > 275 && m_gauge >= 1000 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 3) + kCmd236236B;
                    return;
                }
                if (dx > 160.0 && m_cpuRoll < 310 && m_cpuRoll > 300) {
                    m_command = kCmd412A;
                    return;
                }
                if (dx > 100.0 && dx < 160.0 && m_cpuRoll < 320 && m_cpuRoll > 310) {
                    m_command = kCmd412B;
                    return;
                }
                if (dx > 100.0 && dx < 160.0 && m_cpuRoll < 325 && m_cpuRoll > 320) {
                    m_command = kCmd412C;
                    return;
                }
                if (dx > 100.0 && dx < 160.0 && m_cpuRoll < 340 && m_cpuRoll > 330) {
                    m_command = kCmd236A;
                    return;
                }
                if (dx > 160.0 && m_cpuRoll < 360 && m_cpuRoll > 340) {
                    m_command = kCmd236B;
                    return;
                }
                if (dx > 160.0 && m_cpuRoll < 360 && m_cpuRoll > 340) {
                    m_command = (WORD)Random(0, 2) + kCmd214A;
                    return;
                }
                if (m_cpuRoll < 800 && m_cpuRoll > 700 && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir && dx > 100.0) {
                    m_cpuAction = 5;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0) {
                    if (dx < 80.0 && dy < 120.0 && m_cpuRoll < 10) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx < 90.0 && dy < 140.0 && dy > 80.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623B;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 90.0 && dy < 140.0 && dy > 80.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623C;
                        return;
                    }
                    if (dx < 90.0 && dy < 140.0 && dy > 80.0 && m_cpuRoll < 15) {
                        m_command = kCmd623B;
                        return;
                    }
                    if (dx < 120.0 && dx > 80.0 && dy < 140.0 && dy > 80.0 && m_cpuRoll < 25 && m_cpuRoll > 15 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd412C;
                        return;
                    }
                    if (dx < 160.0 && dx > 120.0 && dy < 300.0 && dy > 160.0 && m_cpuRoll < 40 && m_cpuRoll > 30) {
                        m_command = kCmd412A;
                        return;
                    }
                    if (dx > 130.0 && dx < 150.0 && dy < 150.0 && dy > 120.0 && m_cpuRoll < 110 && m_cpuRoll > 80) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 70.0 && m_cpuRoll < 220 && m_cpuRoll > 200 && (*m_opponent)->y < -50.0 && dy < 90.0 && m_gauge >= 2000) {
                        m_command = (WORD)Random(0, 2) + kCmd641236B;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 80.0 && dy < 100.0 && m_cpuRoll < 100) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 60.0 && dx < 100.0 && dy > 60.0 && dy < 120.0 && m_cpuRoll > 180 && m_cpuRoll < 240) {
                    m_pressC = 1;
                    return;
                }
                if (dx > 150.0 && m_cpuRoll > 240 && m_cpuRoll < 245 && dy > 80.0) {
                    m_command = (WORD)Random(0, 3) + kCmd214214A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 80.0 && dy < 100.0 && m_cpuRoll < 20) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 20.0 && dx < 100.0 && dy > 0.0 && dy < 90.0 && (*m_opponent)->y < y && m_cpuRoll > 20 && m_cpuRoll < 60) {
                    m_pressB = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 100) < 5.0f * m_cpuSkill && dx > 120.0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && dx > 800.0 && dx < 80.0 && (WORD)Random(0, 100) < 3.0f * m_cpuSkill && x > 150.0 && x < 490.0) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if ((WORD)Random(0, 1000) < 2) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 100) < 2) {
        if ((WORD)Random(0, 100) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (dx > 180.0 && y == 0.0 && (WORD)Random(0, 100) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx < 170.0 && dx > 140.0 && y == 0.0 && (*m_opponent)->pattern < kFirstHitReaction) {
            m_inputX = facing;
            m_inputY = -1;
            return;
        }
    }
    if (m_cpuWalkRight > 0) {
        if ((char)AtScreenEdge() != 0 && m_cpuWalkRight > 15) {
            m_cpuWalkRight = 15;
        }
        m_inputX = 1;
        return;
    }
    if (m_cpuWalkLeft > 0) {
        if ((char)AtScreenEdge() != 0 && m_cpuWalkLeft > 15) {
            m_cpuWalkLeft = 15;
        }
        m_inputX = -1;
        return;
    }
    if ((WORD)Random(0, 100) < 50 && dx < 120.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 200) + 60;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 200) + 60;
        }
    }
    if ((WORD)Random(0, 100) < 50) {
        if (facing == 1) {
            m_cpuWalkRight = (WORD)Random(0, 200) + 60;
        } else {
            m_cpuWalkLeft = (WORD)Random(0, 200) + 60;
        }
        return;
    }
    if (facing == -1) {
        m_cpuWalkRight = (WORD)Random(0, 200) + 60;
        return;
    }
    m_cpuWalkLeft = (WORD)Random(0, 200) + 60;
}

void CMakoto::UpdateObjects()
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
            case kObjCStrike:
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
            case kObjJump2CStrike:
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
            case kObjBouncerLaunch:
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
            case kObjHopper236A:
                m_objectVar2[slot]--;
                if (m_objects[slot].frame < 6 && m_objectVar2[slot] <= 0) {
                    effect.type = 0x22;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objectVar2[slot] = 3;
                }
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 0.5;
                    m_objects[slot].vy = -2.7;
                    m_objects[slot].ax = 0.18;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0 && m_objects[slot].frame < 3) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 3;
                    break;
                }
                if (((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastSharedAction) && m_objects[slot].frame > 2 && m_objects[slot].frame < 6 && (m_objects[slot].x - (*m_opponent)->x < 25.0 && m_objects[slot].x - (*m_opponent)->x > -25.0 && (*m_opponent)->y > -20.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kFirstGuard) || pattern > 0xf9 && pattern < 0xfd)) {
                    m_objects[slot].scale = 2;
                    m_playVoice = 0;
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].frame = 6;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                if (m_objects[slot].frame > 2 && m_objects[slot].frame < 6) {
                    if (m_objects[slot].vx > 2.0) {
                        m_objects[slot].ax = -0.18;
                    }
                    if (m_objects[slot].vx < -2.0) {
                        m_objects[slot].ax = 0.18;
                    }
                    m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 3) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                    }
                    if (m_objects[slot].frame == 6 && m_objectVar1[slot] < 6) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].scale = 2;
                        m_playVoice = 0;
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].vx = 0.0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjHopper236B:
                m_objectVar2[slot]--;
                if (m_objects[slot].frame < 6 && m_objectVar2[slot] <= 0) {
                    effect.type = 0x22;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objectVar2[slot] = 3;
                }
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 1.1;
                    m_objects[slot].vy = -2.2;
                    m_objects[slot].ax = 0.18;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0 && m_objects[slot].frame < 3) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 3;
                    break;
                }
                if (((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastSharedAction) && m_objects[slot].frame > 2 && m_objects[slot].frame < 6 && (m_objects[slot].x - (*m_opponent)->x < 25.0 && m_objects[slot].x - (*m_opponent)->x > -25.0 && (*m_opponent)->y > -20.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kFirstGuard) || pattern > 0xf9 && pattern < 0xfd)) {
                    m_objects[slot].scale = 2;
                    m_objects[slot].scale = 2;
                    m_playVoice = 0;
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].frame = 6;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                if (m_objects[slot].frame > 2 && m_objects[slot].frame < 6) {
                    if (m_objects[slot].vx > 2.0) {
                        m_objects[slot].ax = -0.18;
                    }
                    if (m_objects[slot].vx < -2.0) {
                        m_objects[slot].ax = 0.18;
                    }
                    m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 3) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                    }
                    if (m_objects[slot].frame == 6 && m_objectVar1[slot] < 8) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].scale = 2;
                        m_playVoice = 0;
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].vx = 0.0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjHopper236C:
                m_objectVar2[slot]--;
                if (m_objects[slot].frame < 6 && m_objectVar2[slot] <= 0) {
                    effect.type = 0x22;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objectVar2[slot] = 3;
                }
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 15) * 0.1 + 0.5;
                    m_objects[slot].vy = -1.5 - (WORD)Random(0, 10) * 0.1;
                    m_objects[slot].ax = 0.18;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0 && m_objects[slot].frame < 3) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 3;
                    break;
                }
                if (((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kLastSharedAction) && m_objects[slot].frame > 2 && m_objects[slot].frame < 6 && (m_objects[slot].x - (*m_opponent)->x < 25.0 && m_objects[slot].x - (*m_opponent)->x > -25.0 && (*m_opponent)->y > -20.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kFirstGuard) || pattern > 0xf9 && pattern < 0xfd)) {
                    m_objects[slot].scale = 2;
                    m_objects[slot].scale = 2;
                    m_playVoice = 0;
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].frame = 6;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                if (m_objects[slot].frame > 2 && m_objects[slot].frame < 6) {
                    if (m_objects[slot].vx > 2.0) {
                        m_objects[slot].ax = -0.18;
                    }
                    if (m_objects[slot].vx < -2.0) {
                        m_objects[slot].ax = 0.18;
                    }
                    m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 3) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                    }
                    if (m_objects[slot].frame == 6 && m_objectVar1[slot] < 30) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].scale = 2;
                        m_playVoice = 0;
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].vx = 0.0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFirecracker214A:
                m_objectVar2[slot]--;
                if ((m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5 || pattern < 0x100 && pattern > 0xfc && frame == 0) && m_objects[slot].frame < 3) {
                    m_objects[slot].frame = 3;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].scale = 1;
                    break;
                }
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 0.2;
                    m_objects[slot].vy = -0.5;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].frame == 2 && m_objectVar2[slot] <= 0) {
                    effect.type = 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_objectVar2[slot] = 15;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 1;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 3) {
                        if (m_objectVar1[slot] < 3) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                        } else {
                            effect.type = 0x199;
                            effect.x = (double)(int)m_objects[slot].x;
                            effect.y = 5.0;
                            effect.scale = 2;
                            effect.layer = 1;
                            effect.facing = facing;
                            SpawnObject(&effect);
                            effect.x = (double)((int)m_objects[slot].x - 5);
                            effect.y = 0.0;
                            SpawnObject(&effect);
                            effect.x = (double)((int)m_objects[slot].x + 5);
                            effect.y = 0.0;
                            SpawnObject(&effect);
                            effect.x = (double)(int)m_objects[slot].x;
                            effect.y = -5.0;
                            SpawnObject(&effect);
                            RemoveObject(slot);
                        }
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFirecracker214B:
                m_objectVar2[slot]--;
                if ((m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5 || pattern < 0x100 && pattern > 0xfc && frame == 0) && m_objects[slot].frame < 3) {
                    m_objects[slot].frame = 3;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].scale = 1;
                    break;
                }
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 0.4;
                    m_objects[slot].vy = -0.5;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].frame == 2 && m_objectVar2[slot] <= 0) {
                    effect.type = 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_objectVar2[slot] = 21;
                }
                m_objectVar2[slot]--;
                if (m_objects[slot].y + m_objects[slot].vy > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFirecracker214C:
                m_objectVar2[slot]--;
                if ((m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5 || pattern < 0x100 && pattern > 0xfc && frame == 0) && m_objects[slot].frame < 3) {
                    m_objects[slot].frame = 3;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].scale = 1;
                    break;
                }
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 0.3;
                    m_objects[slot].vy = -0.5;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].frame == 2 && m_objectVar2[slot] <= 0) {
                    effect.type = 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_objectVar2[slot] = 15;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 1;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 3) {
                        if (m_objectVar1[slot] < 6) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                        } else {
                            effect.type = 0x199;
                            effect.x = (double)(int)m_objects[slot].x;
                            effect.y = 5.0;
                            effect.scale = 2;
                            effect.layer = 1;
                            effect.facing = facing;
                            SpawnObject(&effect);
                            effect.x = (double)((int)m_objects[slot].x - 5);
                            effect.y = 0.0;
                            SpawnObject(&effect);
                            effect.x = (double)((int)m_objects[slot].x + 5);
                            effect.y = 0.0;
                            SpawnObject(&effect);
                            effect.x = (double)(int)m_objects[slot].x;
                            effect.y = -5.0;
                            SpawnObject(&effect);
                            RemoveObject(slot);
                        }
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFirecrackerSpark:
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vy = -1.5;
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
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
            case kObjBouncer412A:
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = 1;
                }
                if (m_objects[slot].hitsLeft == 0) {
                    RemoveObject(slot);
                    m_bouncerOut = 0;
                }
                if (m_objects[slot].facing == 1) {
                    if (m_objects[slot].frame == 0 || m_objects[slot].frame == 1) {
                        m_objects[slot].vx = 1.5;
                        m_objects[slot].vy = -1.5;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            m_playVoice = 1;
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame + 6;
                            m_objectVar1[slot]++;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            m_playVoice = 1;
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 3) {
                        m_objects[slot].vx = 1.5;
                        m_objects[slot].vy = 1.5;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 5) {
                        m_objects[slot].vx = -1.5;
                        m_objects[slot].vy = 1.5;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 6 || m_objects[slot].frame == 7) {
                        m_objects[slot].vx = -1.5;
                        m_objects[slot].vy = -1.5;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame - 6;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                }
                if (m_objects[slot].facing == -1) {
                    if (m_objects[slot].frame == 0 || m_objects[slot].frame == 1) {
                        m_objects[slot].vx = 1.5;
                        m_objects[slot].vy = -1.5;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame + 6;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 3) {
                        m_objects[slot].vx = 1.5;
                        m_objects[slot].vy = 1.5;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 5) {
                        m_objects[slot].vx = -1.5;
                        m_objects[slot].vy = 1.5;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 6 || m_objects[slot].frame == 7) {
                        m_objects[slot].vx = -1.5;
                        m_objects[slot].vy = -1.5;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame - 6;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 4 || m_objects[slot].frame == 6 || m_objects[slot].frame == 8) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_bouncerOut = 0;
                    }
                }
                break;
            case kObjBouncer412B:
                if (m_objects[slot].frame == 0 && m_objectVar2[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar2[slot] = 1;
                    m_objects[slot].frame = 6;
                }
                if (m_objects[slot].hitsLeft == 0) {
                    RemoveObject(slot);
                    m_bouncerOut = 0;
                }
                if (m_objects[slot].facing == 1) {
                    if (m_objects[slot].frame == 0 || m_objects[slot].frame == 1) {
                        m_objects[slot].vx = 1.5;
                        m_objects[slot].vy = -1.5;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame + 6;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 3) {
                        m_objects[slot].vx = 1.5;
                        m_objects[slot].vy = 1.5;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 5) {
                        m_objects[slot].vx = -1.5;
                        m_objects[slot].vy = 1.5;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 6 || m_objects[slot].frame == 7) {
                        m_objects[slot].vx = -1.5;
                        m_objects[slot].vy = -1.5;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame - 6;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                }
                if (m_objects[slot].facing == -1) {
                    if (m_objects[slot].frame == 0 || m_objects[slot].frame == 1) {
                        m_objects[slot].vx = 1.5;
                        m_objects[slot].vy = -1.5;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame + 6;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 3) {
                        m_objects[slot].vx = 1.5;
                        m_objects[slot].vy = 1.5;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 5) {
                        m_objects[slot].vx = -1.5;
                        m_objects[slot].vy = 1.5;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 6 || m_objects[slot].frame == 7) {
                        m_objects[slot].vx = -1.5;
                        m_objects[slot].vy = -1.5;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame - 6;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 3) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 4 || m_objects[slot].frame == 6 || m_objects[slot].frame == 8) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_bouncerOut = 0;
                    }
                }
                break;
            case kObjBouncer412C:
                if (m_objects[slot].frame == 0 && m_objectVar2[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar2[slot] = 1;
                }
                if (m_objects[slot].facing == 1) {
                    if (m_objects[slot].frame == 0 || m_objects[slot].frame == 1) {
                        m_objects[slot].vx = 3.0;
                        m_objects[slot].vy = -3.0;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame + 6;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 3) {
                        m_objects[slot].vx = 3.0;
                        m_objects[slot].vy = 3.0;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 5) {
                        m_objects[slot].vx = -3.0;
                        m_objects[slot].vy = 3.0;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_objects[slot].hitsLeft = 1;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 6 || m_objects[slot].frame == 7) {
                        m_objects[slot].vx = -3.0;
                        m_objects[slot].vy = -3.0;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame - 6;
                            m_objectVar1[slot]++;
                            m_objects[slot].hitsLeft = 1;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                }
                if (m_objects[slot].facing == -1) {
                    if (m_objects[slot].frame == 0 || m_objects[slot].frame == 1) {
                        m_objects[slot].vx = 3.0;
                        m_objects[slot].vy = -3.0;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame + 6;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 3) {
                        m_objects[slot].vx = 3.0;
                        m_objects[slot].vy = 3.0;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x < m_game->m_view.left) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 5) {
                        m_objects[slot].vx = -3.0;
                        m_objects[slot].vy = 3.0;
                        if (m_objects[slot].y > m_game->m_view.bottom) {
                            m_objects[slot].frame = m_objects[slot].frame + 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                    if (m_objects[slot].frame == 6 || m_objects[slot].frame == 7) {
                        m_objects[slot].vx = -3.0;
                        m_objects[slot].vy = -3.0;
                        if (m_objects[slot].y < m_game->m_view.top) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar1[slot]++;
                            m_playVoice = 1;
                            m_objects[slot].hitsLeft = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                        if (m_objects[slot].x > m_game->m_view.right) {
                            m_objects[slot].frame = m_objects[slot].frame - 6;
                            m_objectVar1[slot]++;
                            m_objects[slot].hitsLeft = 1;
                            m_playVoice = 1;
                            if (m_objectVar1[slot] > 7) {
                                RemoveObject(slot);
                                m_bouncerOut = 0;
                            }
                            break;
                        }
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 4 || m_objects[slot].frame == 6 || m_objects[slot].frame == 8) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_bouncerOut = 0;
                    }
                }
                break;
            case kObj5BFar:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        effect.type = 0x19e;
                        effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 60);
                        effect.y = 5.0;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.facing = facing;
                        SpawnObject(&effect);
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj5BFarGround:
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
            case kObj214214HitLv1:
                m_objects[slot].hitsLeft = 99;
                if (pattern != k214214Lv1 || pattern == k214214Lv1 && frame > 19) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObj214214HitLv2:
                m_objects[slot].hitsLeft = 99;
                if (pattern != k214214Lv2 || pattern == k214214Lv2 && frame > 19) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObj214214HitLv3:
                m_objects[slot].hitsLeft = 99;
                if (pattern != k214214Lv3 || pattern == k214214Lv3 && frame > 19) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObj236236A:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 5;
                    m_objects[slot].vy = -0.45;
                    m_objects[slot].vx = 0.02;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].hitsLeft == 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].vy += 0.0012;
                m_objects[slot].vx -= 1e-05;
                if (m_objects[slot].vx < 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objectVar2[slot] > 90) {
                    m_objects[slot].attackResult = 0;
                    m_objectVar2[slot] = 0;
                }
                m_objectVar2[slot]++;
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObj236236B:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 5;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].ay = 0.005;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].hitsLeft == 0) {
                    RemoveObject(slot);
                    break;
                }
                if (m_objectVar2[slot] > 90) {
                    m_objects[slot].attackResult = 0;
                    m_objectVar2[slot] = 0;
                }
                m_objectVar2[slot]++;
                if (m_objects[slot].vy > 0.3) {
                    m_objects[slot].ay = -0.005;
                }
                if (m_objects[slot].vy < -0.3) {
                    m_objects[slot].ay = 0.005;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar3[slot] < 12) {
                            m_objects[slot].frame = 0;
                            m_objectVar3[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObj236236C:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 5;
                    m_objects[slot].vy = -0.5;
                    m_objects[slot].vx = 0.3;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].hitsLeft == 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].vy += 0.0015;
                if (m_objectVar2[slot] > 90) {
                    m_objects[slot].attackResult = 0;
                    m_objectVar2[slot] = 0;
                }
                m_objectVar2[slot]++;
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObj214214Debris:
                if (m_objectVar1[slot] == 0) {
                    m_objects[slot].vy = (WORD)Random(0, 20) * 0.01 + -2.6;
                    m_objects[slot].vx = -1.0 - (WORD)Random(0, 20) * 0.01;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_playVoice = 2;
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                    if (m_objects[slot].vy > -1.0) {
                        RemoveObject(slot);
                        break;
                    }
                }
                m_objectVar1[slot]++;
                m_objects[slot].vy += 0.05;
                if (m_objectVar1[slot] > 180) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjLv4Thrown:
                if (m_objectVar1[slot] == 0) {
                    m_objects[slot].vy = -3.2;
                    m_objects[slot].vx = -0.07;
                }
                if (m_objects[slot].attackResult == 5 && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_patternVar2 = 2;
                    m_objects[slot].vx = facing * 1.5 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.5;
                    break;
                }
                if (m_objects[slot].y + m_objects[slot].vy > -70.0 && m_objects[slot].frame == 0) {
                    m_patternVar2 = 1;
                    RemoveObject(slot);
                    break;
                }
                m_objectVar1[slot]++;
                m_objects[slot].vy += 0.035;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj641236Aura:
                if (m_objects[slot].frame < 29) {
                    m_objects[slot].x = facing * 12 + x;
                    m_objects[slot].y = y - 50.0;
                }
                if (m_objects[slot].frame < 29 && m_objectVar2[slot] <= 0) {
                    effect.type = 0x22;
                    effect.x = (double)((int)m_objects[slot].x + -m_objects[slot].facing * 47 + (WORD)Random(0, 10));
                    effect.y = (double)((int)m_objects[slot].y + 12 + (WORD)Random(0, 10));
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objectVar2[slot] = 2;
                }
                if (m_objects[slot].frame < 29 && (WORD)Random(0, 100 - (pattern == k641236Lv3) * 50) < 10 && pattern > 0x132) {
                    effect.type = 0x1a8;
                    effect.x = (double)((int)m_objects[slot].x + -m_objects[slot].facing * 60 + (WORD)Random(0, 40));
                    effect.y = (double)((int)m_objects[slot].y + -32 + (WORD)Random(0, 60));
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objectVar2[slot]--;
                if (y + vy >= 0.0 && frame > 5 && m_objectVar1[slot] == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 29;
                    m_objectVar1[slot]++;
                }
                if ((pattern < 0x132 || pattern > 0x134) && m_objects[slot].frame < 29) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 29) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj641236Spark:
                m_objects[slot].timer++;
                if (m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFallInDarkness:
                m_objects[slot].vx = -0.02;
                m_objects[slot].drawnWhileHidden = 30000;
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
                    effect.x = (double)((int)x + facing * 23);
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
                    effect.x = (double)((int)x - facing * 14);
                    effect.y = (double)((int)y - 26);
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
                    effect.x = (double)((int)x + facing * 30);
                    effect.y = (double)((int)y - 40);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x - facing * 25);
                    effect.y = (double)((int)y - 80);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x - facing * 35);
                    effect.y = (double)((int)y - 42);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x - facing * 18);
                    effect.y = (double)((int)y - 20);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x + facing * 2);
                    effect.y = (double)((int)y - 65);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x + (facing << 4));
                    effect.y = (double)((int)y - 80);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_playSound = 34;
                    RemoveObject(slot);
                    m_bounceDebrisOut = 0;
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
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar2[slot] = (rand() > 16000) * 40 + 80 + (rand() > 16000) * 20;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = (rand() > 16000) * 1.2 + (rand() > 16000) * 0.7 + (rand() > 16000) * 1.7 + -1.8;
                    m_objects[slot].vy = -1.2 - ((rand() > 16000) * 0.6 + (rand() > 16000) * 0.9 + (rand() > 16000) * 1.4);
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectVar2[slot] < 10) {
                    m_objects[slot].scale = 1;
                }
                if (m_objectVar2[slot] < 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                m_objectVar2[slot]--;
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
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar2[slot] = (rand() > 16000) * 60 + 120 + (rand() > 16000) * 40;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = (double)(rand() > 16000) + (rand() > 16000) * 0.5 + (rand() > 16000) * 1.5 + -1.5;
                    m_objects[slot].vy = -1.0 - ((rand() > 16000) * 0.5 + (rand() > 16000) * 0.8 + (rand() > 16000) * 1.2);
                }
                m_objects[slot].vy += 0.03;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectVar2[slot] < 10) {
                    m_objects[slot].scale = 1;
                }
                if (m_objectVar2[slot] < 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                m_objectVar2[slot]--;
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
        if (slot >= 64) {
            slot = 0;
        }
    }
}
