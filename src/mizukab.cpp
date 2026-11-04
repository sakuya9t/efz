// CMizukaB (0x4d2850-0x4e7ebf): the character class whose files are in mizukaB\ in the game
// folder (mizukaB.dat sprites, mizukaB.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMizukaB::CMizukaB(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

    strcpy(m_name, "mizukaB");
    lastSurface = 0x353;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_pointX[0] = -0xd;
    m_pointY[0] = -0x3c;
    m_pointX[1] = 0xe;
    m_pointY[1] = 0;
    m_catchState = 0;
    m_throwArrived = 0;
    m_throwHelperFacing = 0;
    m_homingOrbHit = 0;
    m_flying = 0;
    m_flightDrainTimer = 0;
    m_resultPictures = 6;
    m_rivals[0] = 6;
    m_rivals[1] = 1;
    m_rivals[2] = 7;
    m_rivals[0xa] = 0x12;
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
}

void CMizukaB::Reset()
{
    int i;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_pointX[0] = -0xd;
    m_pointY[0] = -0x3c;
    m_pointX[1] = 0xe;
    m_pointY[1] = 0;
    m_catchState = 0;
    m_throwArrived = 0;
    m_throwHelperFacing = 0;
    m_homingOrbHit = 0;
    m_flying = 0;
    m_flightDrainTimer = 0;
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
    CPlayer::Reset();
}

void CMizukaB::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CMizukaB::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
}

void CMizukaB::Move()
{
    MoveOnGround();
}

void CMizukaB::StartCommand()
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
    if (y == 0.0) {
        m_flying = 0;
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
        if (m_hp <= 0xd05 && m_command == kCmdC5B6A5A && m_gauge >= 0xbb8 && y == 0.0 && m_attackResult != 6 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd236236C && m_gauge >= 0xbb8 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir236236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236236C;
            return;
        }
        if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x7d0 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir236236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236236B;
            return;
        }
        if (m_command == kCmd236236B && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236B;
            return;
        }
        if (m_command == kCmd236236A && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236A;
            if (y < 0.0) {
                pattern = kAir236236A;
            }
            return;
        }
        if (m_command == kCmd4631C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k463214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k463214C;
            return;
        }
        if ((m_command == kCmd4631B || m_command == kCmd4631C) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k463214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k463214B;
            return;
        }
        if ((m_command == kCmd4631A || m_command == kCmd4631B || m_command == kCmd4631C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k463214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k463214A;
            return;
        }
        if (m_command == kCmd421C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            if (m_patterns[pattern].cancelLevel <= m_patterns[k421C].level && y == 0.0) {
                StartPattern();
                ClearBufferedPress();
                pattern = k421C;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[k421C].level && y < 0.0 && m_airDashes == 0) {
                StartPattern();
                ClearBufferedPress();
                pattern = kAir421C;
                return;
            }
        }
        if (m_command == kCmd421B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            if (m_patterns[pattern].cancelLevel <= m_patterns[k421B].level && y == 0.0) {
                StartPattern();
                ClearBufferedPress();
                pattern = k421B;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[k421B].level && y < 0.0 && m_airDashes == 0) {
                StartPattern();
                ClearBufferedPress();
                pattern = kAir421B;
                return;
            }
        }
        if (m_command == kCmd421A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            if (m_patterns[pattern].cancelLevel <= m_patterns[k421A].level && y == 0.0) {
                StartPattern();
                ClearBufferedPress();
                pattern = k421A;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[kAir421A].level && y < 0.0 && m_airDashes == 0) {
                StartPattern();
                ClearBufferedPress();
                pattern = kAir421A;
                return;
            }
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
        if (m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
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
        if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            return;
        }
        if (m_command == kCmd41236C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236C;
            return;
        }
        if (m_command == kCmd41236B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236B;
            return;
        }
        if (m_command == kCmd41236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236A;
            return;
        }
        if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            if (y < 0.0) {
                pattern = kAir236C;
            }
            return;
        }
        if ((m_command == kCmd236B || m_command == kCmd236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236B;
            if (y < 0.0) {
                pattern = kAir236B;
            }
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236A;
            if (y < 0.0) {
                pattern = kAir236A;
            }
            return;
        }
    }
    if (m_sealLevel < 1 && (m_command == kCmdDashLeft || m_command == kCmdDashRight)) {
        if (y < 0.0 && m_airDashes < 1) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].cancelLevel <= m_patterns[kAirDashForward].level && pattern != kRecoilGuardAir && (y < -40.0 || m_flying > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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
                m_dashMomentum++;
                m_bufferedPress = 0;
                return;
            }
        }
    }
    if (m_sealLevel < 3 && m_command == kCmdUp && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_airActions < 1 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAirJump].level) {
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
            if (m_patterns[pattern].cancelLevel <= m_patterns[kJump6C].level && m_inputX == facing && m_inputY == 0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kJump6C;
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
            if (m_inputX != 0 && x - (*m_opponent)->x > -40.0 && x - (*m_opponent)->x < 40.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kThrow;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[k5C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k5C;
                return;
            }
        }
    }
    if (m_sealLevel < 2 && (m_pressD == 1 || (m_bufferedPress & kInputD) != 0 || (m_dashBufferedPress & kInputD) != 0) && m_airActions == 0 && m_patterns[pattern].cancelLevel <= m_patterns[0xb3].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_flying <= 0) {
        StartPattern();
        ClearBufferedPress();
        pattern = 0xb3;
    }
}

void CMizukaB::DrawGauge()
{
}

void CMizukaB::PreUpdate()
{
    if (m_flying > 0) {
        m_flightDrainTimer++;
        if (m_flightDrainTimer > 0) {
            m_rfGauge--;
            m_flightDrainTimer = 0;
        }
        if (m_rfGauge <= 0.0 || pattern < kLastFreeAction && pattern < kFirstGuard || y == 0.0) {
            m_flying = 0;
        }
    }
}

void CMizukaB::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CMizukaB::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 135);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputA) != 0 && step == 6) {
            m_command = kCmdC5B6A5A;
            return;
        }
        if (input == 0 && step == 5) {
            step = 6;
        }
        if ((input & (kInputB | kInputC | kInputD)) != 0 && step == 5) {
            break;
        }
        if ((input & kInputA) != 0 && step == 4) {
            step = 5;
        }
        if ((input & (kInputB | kInputC | kInputD)) != 0 && step == 4) {
            break;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 3) {
            step = 4;
        }
        if ((input & (kInputA | kInputC | kInputD)) != 0 && step == 2) {
            break;
        }
        if ((input & kInputB) != 0 && step == 2) {
            step = 3;
        }
        if (input == 0 && step == 1) {
            step = 2;
        }
        if ((input & (kInputA | kInputB | kInputD)) != 0 && step == 1) {
            break;
        }
        if ((input & kInputC) != 0 && step == 0 && y == 0.0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 75);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 4) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd4631A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 3) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd4631A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 4;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 0 && y == 0.0) {
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
        if ((input & kInputDirections) == kInputDown && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 60);
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
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 0 && y == 0.0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 60);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 3) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd421A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 2) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd623A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 3;
        }
        if ((input & kInputDirections) == kInputDown && step == 1) {
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
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 0 && y == 0.0) {
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
        if ((input & kInputDirections) == kInputDown && step == 0 && y == 0.0) {
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
    pos = m_inputPos + (kInputHistoryLength - 55);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 4) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd66A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 3) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd66A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 4;
        }
        if ((input & kInputDirections) == 0 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 1) {
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

void CMizukaB::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == kAir236C && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 40.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx > 20.0 && dx < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (dx > 60.0 && dx < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (dx < 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_command = kCmd623A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = kCmd623C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && dx < 80.0 && m_gauge >= 0xbb8) {
                m_command = 0x70;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && dx < 150.0 && m_gauge == 0xbb8) {
                m_command = kCmd4631C;
                return;
            }
        }
        if (dx < 320.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd214C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = kCmd4631C;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && dx < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && dx < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && dx < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            m_inputX = facing;
            return;
        }
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 2) {
            m_command = kCmd236C;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0) {
            m_command = kCmd623A;
            return;
        }
        if (m_cpuRoll < 4 && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0xbb8) {
            m_command = 0x70;
            return;
        }
        if (m_cpuRoll < 0x1e && m_cpuRoll > 0x11 && m_gauge >= 0xbb8) {
            m_command = kCmd4631C;
            return;
        }
        if (m_cpuRoll > 0x32) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 3) + 0x78;
            return;
        }
        if (m_cpuRoll > 0x55) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k623A || pattern == k623B || pattern == k623C || pattern == kLv4)) {
        m_command = kCmd22C;
        return;
    }
    if (m_flying > 0) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if ((*m_opponent)->y == 0.0) {
            if (dx < 110.0 && dy < 60.0 && m_cpuRoll < 0x32) {
                m_pressA = 1;
                return;
            }
            if (dx > 50.0 && dx < 100.0 && dy < 80.0 && m_cpuRoll > 0x32 && m_cpuRoll < 0x78) {
                m_pressB = 1;
                return;
            }
            if (dx < 70.0 && dy > 60.0 && dy < 90.0 && m_cpuRoll > 0x78 && m_cpuRoll < 0xaa) {
                m_pressC = 1;
                return;
            }
            if ((WORD)Random(0, 0x140) < dx - 100.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xdc) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if (dx > 100.0 && m_cpuRoll > 0xf0 && m_cpuRoll < 0x14a && dy < 40.0) {
                m_command = (WORD)Random(0, 3) + kCmd214A;
                return;
            }
        }
        if ((*m_opponent)->y < 0.0) {
            if (dx < 110.0 && dy < 100.0 && m_cpuRoll < 0x32) {
                m_pressA = 1;
                return;
            }
            if (dx > 50.0 && dx < 100.0 && dy < 100.0 && m_cpuRoll > 0x32 && m_cpuRoll < 0x78) {
                m_pressB = 1;
                return;
            }
            if (dx < 90.0 && dy > 100.0 && dy < 180.0 && m_cpuRoll > 0x78 && m_cpuRoll < 0xaa) {
                m_pressC = 1;
                return;
            }
            if ((WORD)Random(0, 0x140) < dx - 100.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xdc) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if (dx > 100.0 && m_cpuRoll > 0xf0 && m_cpuRoll < 0x14a && dy < 60.0) {
                m_command = (WORD)Random(0, 3) + kCmd214A;
                return;
            }
        }
        if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 3.0f * m_cpuSkill) {
            m_command = facing == 1;
            return;
        }
        if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && dx > 60.0 && dx < 140.0 && (WORD)Random(0, 0x64) < 2.0f * m_cpuSkill && x > 120.0 && x < 520.0) {
            m_command = -((facing == 1) - 1);
            return;
        }
        if ((WORD)Random(0, 0x3e8) < 1) {
            m_cpuAction = 4;
            return;
        }
        m_inputY = 1;
        if ((WORD)Random(0, 0x64) < 0x32) {
            m_inputY = -1;
        }
        if (dy > 200.0) {
            m_inputY = 1;
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
                m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x2d;
            } else {
                m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x2d;
            }
        }
        if ((WORD)Random(0, 0x64) < 0x32) {
            if (facing == 1) {
                m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x2d;
            } else {
                m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x2d;
            }
        } else if (facing == -1) {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x2d;
        } else {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x2d;
        }
        return;
    }
    if (m_cpuAction == 0 && (WORD)Random(0, 0x64) < m_cpuSkill && (pattern > kLastHitReaction && pattern < kAirRecoveryForward || pattern == kWakeUp)) {
        m_cpuAction = 0xd;
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
        m_pressA = 1;
        m_inputY = 1;
        if (pattern == k2A) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xd) {
        m_command = kCmd623A;
        if (pattern == k623A) {
            m_cpuAction = 0;
        }
    }
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 0x64) < m_cpuSkill * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x1e) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (dx < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x3ca) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + 0x78;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x258 && m_attackResult == 3) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll < 0xc8) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x1c2 && dx < 90.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x2bc) {
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
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if (dx > 80.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x258 && dx < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 0x1f4 && m_attackResult == 3 && dx < 80.0) {
                m_pressC = 1;
                m_inputY = 0;
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
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x131 && m_gauge >= 0xbb8 && dx < 90.0 && m_attackResult == 3) {
                m_command = kCmd4631C;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x15e) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x1f4) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 3) + kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0x29e && m_cpuRoll < 0x2bc) {
                m_pressD = 1;
                return;
            }
        }
        if (pattern == k2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
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
                    m_cpuAction = 6;
                    if (dx > 110.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x258 && dx < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x12c && dx < 100.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
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
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if (dx > 110.0) {
                        m_cpuAction = 8;
                    }
                }
                return;
            }
        }
        if (pattern == k2C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x131 && m_gauge >= 0xbb8 && dx < 90.0 && m_attackResult == 3) {
                m_command = kCmd4631C;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x131 && m_cpuRoll < 0x15e && m_gauge >= 0x3e8 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 3) + kCmd236236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x15e) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x1f4) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 3) + kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0x29e && m_cpuRoll < 0x2bc) {
                m_pressD = 1;
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
            if (m_cpuRoll > 0x14 && m_cpuRoll < 0x3c && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd236A;
                return;
            }
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
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xdc && dx < 90.0 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + 0x78;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x289 && (WORD)Random(0, 2) == 0) {
                m_cpuAction = 0xc;
                if (dx > 110.0) {
                    m_cpuAction = 8;
                }
            }
        }
        if (pattern == kDashC) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8 && dx < 90.0) {
                m_command = (WORD)Random(0, 3) + 0x78;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xfa) {
                m_command = (WORD)Random(0, 3) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1ae && m_attackResult == 3 && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
            if (m_cpuRoll > 0x1ae && m_cpuRoll < 0x21c && m_attackResult != 3) {
                m_command = 0x28;
                if (dx > 120.0) {
                    m_command = 0x29;
                }
                return;
            }
            if (m_cpuRoll > 0x38e && m_attackResult == 3) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 1;
                return;
            }
        }
    }
    if ((WORD)Random(0, 0x64) < 25.0f * m_cpuSkill) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown) {
                if (dx < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (dx < 50.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 75.0 && m_cpuRoll < 0x19) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 120.0 && m_cpuRoll < 0x3c && m_cpuRoll > 0x1e) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 0x34 && m_cpuRoll > 0x28 || dx > 90.0 && dx < 150.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x34) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx > 80.0 && dx < 120.0 && m_cpuRoll < 0x55 && m_cpuRoll > 0x50) {
                    m_cpuAction = 8;
                    return;
                }
                if (dx > 70.0 && dx < 120.0 && m_cpuRoll < 0x78 && m_cpuRoll > 0x5a) {
                    m_cpuAction = 8;
                    return;
                }
                if (dx < 160.0 && dx > 70.0 && m_cpuRoll < 0x82 && m_cpuRoll > 0x78) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 100.0 && dx > 70.0 && m_cpuRoll < 0x91 && m_cpuRoll > 0x82) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx > 100.0 && dx < 140.0 && m_cpuRoll < 0x98 && m_cpuRoll > 0x91) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (dx < 70.0 && m_cpuRoll < 0xb9 && m_cpuRoll > 0x91 && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd623A;
                    return;
                }
                if (dx < 100.0 && dx > 40.0 && m_cpuRoll < 0xbe && m_cpuRoll > 0xb9 && m_gauge >= 0xbb8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd4631C;
                    return;
                }
                if (dx > 120.0 && m_cpuRoll < 0xc8 && m_cpuRoll > 0xbe && m_gauge >= 0xbb8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = 0x70;
                    return;
                }
                if (dx > 200.0 && m_cpuRoll < 0xbe && m_cpuRoll > 0xaa) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (dx > 180.0 && m_cpuRoll < 0xc8 && m_cpuRoll > 0xbe) {
                    m_command = kCmd41236A;
                    return;
                }
                if (dx > 180.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xc8) {
                    m_command = kCmd41236B;
                    return;
                }
                if (dx > 80.0 && dx < 120.0 && m_cpuRoll < 0xdc && m_cpuRoll > 0xd2) {
                    m_command = kCmd214A;
                    return;
                }
                if (dx > 140.0 && dx < 180.0 && m_cpuRoll < 0xf0 && m_cpuRoll > 0xe6) {
                    m_command = kCmd214B;
                    return;
                }
                if ((m_rfGauge > 500.0 || m_rfBlue == 1) && m_cpuRoll < 0xf5 && m_cpuRoll > 0xf0) {
                    m_command = kCmd214C;
                    return;
                }
                if (dx > 140.0 && m_cpuRoll < 0x104 && m_cpuRoll > 0xfa && m_gauge >= 0x3e8) {
                    m_command = (WORD)Random(0, 3) + 0x78;
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
                    if (dx < 150.0 && dx > 50.0 && m_cpuRoll < 0x28 && m_gauge >= 0xbb8) {
                        m_command = kCmd4631C;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 90.0 && dy < 140.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623C;
                        return;
                    }
                    if (dx < 90.0 && dy < 140.0 && m_cpuRoll < 0x1e) {
                        m_command = kCmd623C;
                        return;
                    }
                    if (dx < 80.0 && dx > 30.0 && dy < 140.0 && dy > 100.0 && m_cpuRoll < 0x41 && m_cpuRoll > 0x1e) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx > 100.0 && dx < 140.0 && dy < 140.0 && dy > 100.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x3c) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 160.0 && dx > 30.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x50 && (*m_opponent)->y < -50.0 && m_gauge >= 0xbb8) {
                        m_command = kCmd4631C;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 110.0 && dy < 100.0 && m_cpuRoll < 0x32) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 50.0 && dx < 100.0 && dy < 100.0 && m_cpuRoll > 0x32 && m_cpuRoll < 0x78) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 90.0 && dy > 100.0 && dy < 180.0 && m_cpuRoll > 0x78 && m_cpuRoll < 0xaa) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 0x140) < dx - 100.0 && dy < 90.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xdc) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (dx > 100.0 && m_cpuRoll > 0xf0 && m_cpuRoll < 0x14a && dy + 40.0 > dx && dy - 40.0 < dx) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 110.0 && dy < 100.0 && m_cpuRoll < 0x32) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 50.0 && dx < 100.0 && dy < 100.0 && m_cpuRoll > 0x32 && m_cpuRoll < 0x78) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 90.0 && dy > 100.0 && dy < 180.0 && m_cpuRoll > 0x78 && m_cpuRoll < 0xaa) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 0x140) < dx - 100.0 && dy < 90.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xdc) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (dx > 100.0 && m_cpuRoll > 0xf0 && m_cpuRoll < 0x14a && dy + 40.0 > dx && dy - 40.0 < dx) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 3.0f * m_cpuSkill) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && dx > 60.0 && dx < 140.0 && (WORD)Random(0, 0x64) < 2.0f * m_cpuSkill && x > 120.0 && x < 520.0) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if ((WORD)Random(0, 0x3e8) < 1) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 0x64) < 2) {
        if ((WORD)Random(0, 0x64) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (dx > 180.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
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
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x2d;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x2d;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x32) {
        if (facing == 1) {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x2d;
        } else {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x2d;
        }
        return;
    }
    if (facing == -1) {
        m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x2d;
        return;
    }
    m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x2d;
}

void CMizukaB::UpdateObjects()
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
            case kObj5BCloseEffect:
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
            case kObj5BFarEffect:
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
            case kObj2BEffect:
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
            case kObjUnused193:
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
            case kObjJumpBEffect:
                if (pattern != kJumpB) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = facing * 0x25 + x;
                m_objects[slot].y = y - 72.0;
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
            case kObjJumpCEffect:
                m_objects[slot].x = (facing << 2) + x;
                m_objects[slot].y = y + 5.0;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 4 && pattern == kJumpC && frame < 8) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214CChain1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 0;
                }
                if (m_objects[slot].frame == 9 && m_objects[slot].timer == 0 && m_objects[slot].x > 0.0 && m_objects[slot].x < 640.0) {
                    effect.type = 0x199;
                    effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 0x3c);
                    effect.y = 0.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214CChain2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 0;
                }
                if (m_objects[slot].frame == 9 && m_objects[slot].timer == 0 && m_objects[slot].x > 0.0 && m_objects[slot].x < 640.0) {
                    effect.type = 0x19a;
                    effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 0x3c);
                    effect.y = 0.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214CChain3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 0;
                }
                if (m_objects[slot].frame == 9 && m_objects[slot].timer == 0 && m_objects[slot].x > 0.0 && m_objects[slot].x < 640.0) {
                    effect.type = 0x198;
                    effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 0x3c);
                    effect.y = 0.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjWalker1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.01 + 0.7;
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
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
                if (m_objects[slot].x < -30.0 && m_objects[slot].facing == -1 || m_objects[slot].x > 670.0 && m_objects[slot].facing == 1) {
                    RemoveObject(slot);
                }
                break;
            case kObjWalker2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.01 + 0.7;
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
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
                if (m_objects[slot].x < -30.0 && m_objects[slot].facing == -1 || m_objects[slot].x > 670.0 && m_objects[slot].facing == 1) {
                    RemoveObject(slot);
                }
                break;
            case kObjWalker3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.01 + 0.7;
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
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
                if (m_objects[slot].x < -30.0 && m_objects[slot].facing == -1 || m_objects[slot].x > 670.0 && m_objects[slot].facing == 1) {
                    RemoveObject(slot);
                }
                break;
            case kObjWalker4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.01 + 0.7;
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
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
                if (m_objects[slot].x < -30.0 && m_objects[slot].facing == -1 || m_objects[slot].x > 670.0 && m_objects[slot].facing == 1) {
                    RemoveObject(slot);
                }
                break;
            case kObjWalker5:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.01 + 0.7;
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
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
                if (m_objects[slot].x < -30.0 && m_objects[slot].facing == -1 || m_objects[slot].x > 670.0 && m_objects[slot].facing == 1) {
                    RemoveObject(slot);
                }
                break;
            case kObjWalker6:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.01 + 0.7;
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
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
                if (m_objects[slot].x < -30.0 && m_objects[slot].facing == -1 || m_objects[slot].x > 670.0 && m_objects[slot].facing == 1) {
                    RemoveObject(slot);
                }
                break;
            case kObj236A:
                if (m_objects[slot].frame == 3 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 5;
                }
                if (m_objects[slot].frame > 4 && m_objects[slot].frame < 0x26 && (pattern == k236A || pattern == k236B) && frame == 0xd || (pattern == kAir236A || pattern == kAir236B) && frame == 0xe) {
                    m_objects[slot].vx = 3.0;
                    m_objects[slot].ax = -0.05;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 3;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].pattern = kObj236Launched;
                    break;
                }
                if (m_objects[slot].frame > 3 && m_objects[slot].frame < 0x26 && m_objects[slot].hitsLeft == 0 || pattern > kLastFreeAction && pattern < kFirstGuard && m_objects[slot].frame < 0x26 || pattern > 0xf9 && pattern < 0xfc && m_objects[slot].frame < 0x26 && frame == 0 || pattern > 0x105 && pattern < 0x108 && m_objects[slot].frame < 0x26 && frame == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x26;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objectVar3[slot]++;
                    if (m_objectVar3[slot] > 5) {
                        m_objects[slot].attackResult = 0;
                        m_objectVar3[slot] = 0;
                    }
                    if (m_objects[slot].frame == 0x25) {
                        if (m_objectVar1[slot] < 0 || m_objectVar1[slot] < 1 && m_objects[slot].y < -38.0) {
                            m_objects[slot].frame = 4;
                            m_objectVar1[slot]++;
                        } else {
                            m_objects[slot].vx = 0.0;
                            m_objects[slot].frame = 0x29;
                        }
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj236B:
                if (m_objects[slot].frame == 3 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 5;
                }
                if (m_objects[slot].frame > 4 && m_objects[slot].frame < 0x26 && (pattern == k236A || pattern == k236B) && frame == 0xd || (pattern == kAir236A || pattern == kAir236B) && frame == 0xe) {
                    m_objects[slot].vx = 3.5;
                    m_objects[slot].ax = -0.04;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 5;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].pattern = kObj236Launched;
                    break;
                }
                if (m_objects[slot].frame > 3 && m_objects[slot].frame < 0x26 && m_objects[slot].hitsLeft == 0 || pattern > kLastFreeAction && pattern < kFirstGuard && m_objects[slot].frame < 0x26 || pattern > 0xf9 && pattern < 0xfc && m_objects[slot].frame < 0x26 && frame == 0 || pattern > 0x105 && pattern < 0x108 && m_objects[slot].frame < 0x26 && frame == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x26;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objectVar3[slot]++;
                    if (m_objectVar3[slot] > 5) {
                        m_objects[slot].attackResult = 0;
                        m_objectVar3[slot] = 0;
                    }
                    if (m_objects[slot].frame == 0x25) {
                        if (m_objectVar1[slot] < 0 || m_objectVar1[slot] < 1 && m_objects[slot].y < -38.0) {
                            m_objects[slot].frame = 4;
                            m_objectVar1[slot]++;
                        } else {
                            m_objects[slot].vx = 0.0;
                            m_objects[slot].frame = 0x29;
                        }
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj236C:
                if (m_objects[slot].frame == 3 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.35;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vx += 0.005;
                if (m_objects[slot].attackResult == 3 && m_objects[slot].frame < 0x25) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x25;
                    m_objects[slot].vx = 0.0;
                    m_playVoice = 0xc;
                    break;
                }
                if (m_objects[slot].attackResult > 1 && m_objects[slot].frame < 0x25) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x28;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                if (m_objects[slot].frame == 0x25 && m_objects[slot].attackResult == 3) {
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                    m_objects[slot].attackResult = 0;
                }
                if (m_objects[slot].frame > 3 && m_objects[slot].frame < 0x26 && m_objects[slot].hitsLeft == 0 || pattern > kLastFreeAction && pattern < kFirstGuard && m_objects[slot].frame < 0x26) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x26;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 0x25) {
                        if (m_objectVar1[slot] < 6) {
                            m_objects[slot].frame = 4;
                            m_objectVar1[slot]++;
                        } else {
                            m_objects[slot].vx = 0.0;
                            m_objects[slot].frame = 0x28;
                        }
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        if ((*m_opponent)->pattern == kThrownHidden) {
                            (*m_opponent)->StartPattern();
                            (*m_opponent)->StopMoving();
                            (*m_opponent)->y = -480.0;
                            (*m_opponent)->x = x;
                            (*m_opponent)->pattern = kHitAir;
                        }
                    }
                }
                break;
            case kObj236Launched:
                m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                if (m_objects[slot].vx < 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objectVar3[slot]++;
                    if (m_objectVar3[slot] > 5) {
                        m_objects[slot].attackResult = 0;
                        m_objectVar3[slot] = 0;
                    }
                    if (m_objects[slot].frame == 0x25 && m_objects[slot].vx > 0.0) {
                        m_objects[slot].frame = 4;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj623Effect:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 1;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjRiser1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    if (m_objectVar1[slot] == 0) {
                        m_objects[slot].vy = -1.1;
                        m_objects[slot].vx = 0.3;
                        m_objectVar1[slot]++;
                    }
                }
                if (frame == 1 && m_patternVar1 == 0x1e) {
                    RemoveObject(slot);
                }
                m_objects[slot].vx -= 0.002;
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
            case kObjRiser2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    if (m_objectVar1[slot] == 0) {
                        m_objects[slot].vy = -1.1;
                        m_objects[slot].vx = 0.3;
                        m_objectVar1[slot]++;
                    }
                }
                if (frame == 1 && m_patternVar1 == 0x1e) {
                    RemoveObject(slot);
                }
                m_objects[slot].vx -= 0.002;
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
            case kObjRiser3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    if (m_objectVar1[slot] == 0) {
                        m_objects[slot].vy = -1.1;
                        m_objects[slot].vx = 0.3;
                        m_objectVar1[slot]++;
                    }
                }
                if (frame == 1 && m_patternVar1 == 0x1e) {
                    RemoveObject(slot);
                }
                m_objects[slot].vx -= 0.002;
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
            case kObjRiser4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    if (m_objectVar1[slot] == 0) {
                        m_objects[slot].vy = -1.1;
                        m_objects[slot].vx = 0.3;
                        m_objectVar1[slot]++;
                    }
                }
                if (frame == 1 && m_patternVar1 == 0x1e) {
                    RemoveObject(slot);
                }
                m_objects[slot].vx -= 0.002;
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
            case kObjRiser5:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    if (m_objectVar1[slot] == 0) {
                        m_objects[slot].vy = -1.1;
                        m_objects[slot].vx = 0.3;
                        m_objectVar1[slot]++;
                    }
                }
                if (frame == 1 && m_patternVar1 == 0x1e) {
                    RemoveObject(slot);
                }
                m_objects[slot].vx -= 0.002;
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
            case kObjRiser6:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    if (m_objectVar1[slot] == 0) {
                        m_objects[slot].vy = -1.1;
                        m_objects[slot].vx = 0.3;
                        m_objectVar1[slot]++;
                    }
                }
                if (frame == 1 && m_patternVar1 == 0x1e) {
                    RemoveObject(slot);
                }
                m_objects[slot].vx -= 0.002;
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
            case kObjSweeper1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = 0.5;
                    m_objects[slot].vx = 2.5;
                }
                if (m_patternVar3 == 1 && m_objectVar3[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = (int)(m_objects[slot].vx * 100.0);
                    m_objectVar2[slot] = (int)(m_objects[slot].vy * 100.0);
                    m_objectVar3[slot] = 1;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_patternVar3 == 0 && m_objectVar3[slot] == 1) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = m_objectVar1[slot] * 0.01;
                    m_objects[slot].vy = m_objectVar2[slot] * 0.01;
                    m_objectVar3[slot] = 2;
                }
                if (frame > 1) {
                    RemoveObject(slot);
                }
                if (m_patternVar3 != 1) {
                    m_objects[slot].vy -= 0.01;
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
            case kObjSweeper2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = 0.5;
                    m_objects[slot].vx = 2.5;
                }
                if (m_patternVar3 == 1 && m_objectVar3[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = (int)(m_objects[slot].vx * 100.0);
                    m_objectVar2[slot] = (int)(m_objects[slot].vy * 100.0);
                    m_objectVar3[slot] = 1;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_patternVar3 == 0 && m_objectVar3[slot] == 1) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = m_objectVar1[slot] * 0.01;
                    m_objects[slot].vy = m_objectVar2[slot] * 0.01;
                    m_objectVar3[slot] = 2;
                }
                if (frame > 1) {
                    RemoveObject(slot);
                }
                if (m_patternVar3 != 1) {
                    m_objects[slot].vy -= 0.01;
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
            case kObjSweeper3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = 0.5;
                    m_objects[slot].vx = 2.5;
                }
                if (m_patternVar3 == 1 && m_objectVar3[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = (int)(m_objects[slot].vx * 100.0);
                    m_objectVar2[slot] = (int)(m_objects[slot].vy * 100.0);
                    m_objectVar3[slot] = 1;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_patternVar3 == 0 && m_objectVar3[slot] == 1) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = m_objectVar1[slot] * 0.01;
                    m_objects[slot].vy = m_objectVar2[slot] * 0.01;
                    m_objectVar3[slot] = 2;
                }
                if (frame > 1) {
                    RemoveObject(slot);
                }
                if (m_patternVar3 != 1) {
                    m_objects[slot].vy -= 0.01;
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
            case kObjSweeper4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = 0.5;
                    m_objects[slot].vx = 2.5;
                }
                if (m_patternVar3 == 1 && m_objectVar3[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = (int)(m_objects[slot].vx * 100.0);
                    m_objectVar2[slot] = (int)(m_objects[slot].vy * 100.0);
                    m_objectVar3[slot] = 1;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_patternVar3 == 0 && m_objectVar3[slot] == 1) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = m_objectVar1[slot] * 0.01;
                    m_objects[slot].vy = m_objectVar2[slot] * 0.01;
                    m_objectVar3[slot] = 2;
                }
                if (frame > 1) {
                    RemoveObject(slot);
                }
                if (m_patternVar3 != 1) {
                    m_objects[slot].vy -= 0.01;
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
            case kObjSweeper5:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = 0.5;
                    m_objects[slot].vx = 2.5;
                }
                if (m_patternVar3 == 1 && m_objectVar3[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = (int)(m_objects[slot].vx * 100.0);
                    m_objectVar2[slot] = (int)(m_objects[slot].vy * 100.0);
                    m_objectVar3[slot] = 1;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_patternVar3 == 0 && m_objectVar3[slot] == 1) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = m_objectVar1[slot] * 0.01;
                    m_objects[slot].vy = m_objectVar2[slot] * 0.01;
                    m_objectVar3[slot] = 2;
                }
                if (frame > 1) {
                    RemoveObject(slot);
                }
                if (m_patternVar3 != 1) {
                    m_objects[slot].vy -= 0.01;
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
            case kObjFinaleBackdrop:
                if (frame == 1) {
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
            case kObjGrabber:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = 0.5;
                    m_objects[slot].vx = 2.5;
                }
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = (int)(m_objects[slot].vx * 100.0);
                    m_objectVar2[slot] = (int)(m_objects[slot].vy * 100.0);
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    (*m_opponent)->pattern = kHitBlownAway;
                    (*m_opponent)->y = m_objects[slot].y - 81.0;
                    (*m_opponent)->x = m_objects[slot].x;
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->StopMoving();
                    (*m_opponent)->m_hitVx = -6.0;
                    (*m_opponent)->m_hitVy = 4.0;
                    (*m_opponent)->facing = -m_objects[slot].facing;
                }
                if (m_objects[slot].frame == 2 || m_objects[slot].frame == 3) {
                    m_patternVar1--;
                }
                if ((*m_opponent)->y == 0.0 && m_objectVar3[slot] == 0 && m_objects[slot].frame == 2) {
                    DealDamage(0x170c, 500.0);
                    m_objectVar3[slot]++;
                    m_playSound = 0x16;
                }
                if ((*m_opponent)->pattern == kLyingDown) {
                    (*m_opponent)->timer = 0;
                }
                if (m_objects[slot].frame == 4 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = m_objectVar1[slot] * 0.01;
                    m_objects[slot].vy = m_objectVar2[slot] * 0.01;
                }
                if (m_objects[slot].frame == 4 && m_objects[slot].timer == duration - 0xc && (m_roundsWon == 0 || m_roundsWon == 1 && (*m_opponent)->m_hp > 0)) {
                    m_game->FlashWhite(9, 3, 0xc);
                }
                if (m_objects[slot].frame != 2) {
                    m_objects[slot].vy -= 0.01;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2) {
                        m_patternVar3 = 1;
                    }
                    if (m_objects[slot].frame == 4) {
                        m_patternVar3 = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_patternVar2 = (int)m_objects[slot].x;
                        m_patternVar3 = (int)(m_objects[slot].y - 130.0);
                    }
                }
                break;
            case kObjCatchProp:
                if (pattern == k463214AHit || pattern == k463214BHit || pattern == k463214CHit) {
                    if (frame == 0x1c) {
                        m_objects[slot].frame = 2;
                    }
                    if (frame != 0x1c && m_objects[slot].frame == 2) {
                        m_objects[slot].frame = 1;
                    }
                }
                if ((pattern < 0x132 || pattern > 0x134) && m_objects[slot].frame < 4) {
                    m_objects[slot].frame = 4;
                    m_objects[slot].timer = 0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjCatcher:
                if (pattern < 0x132 || pattern > 0x134) {
                    m_catchState = 0;
                }
                if (m_objects[slot].frame == 9) {
                    (*m_opponent)->frame = 1;
                }
                if (m_objects[slot].frame == 0xa) {
                    (*m_opponent)->frame = 2;
                }
                if (m_objects[slot].frame == 0xc) {
                    (*m_opponent)->frame = 3;
                }
                if (m_objects[slot].frame == 0xd) {
                    (*m_opponent)->frame = 4;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vy = 1.5;
                    m_playVoice = 5;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vy += 0.035;
                    if (m_objects[slot].attackResult == 3 && (*m_opponent)->m_hp > 0) {
                        m_objects[slot].layer = 0;
                        m_catchState = 1;
                        m_objects[slot].hitstop = 0x3c;
                        (*m_opponent)->m_hitstop = 0x3c;
                        m_objects[slot].attackResult = 0;
                        break;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].frame = 1;
                        m_objects[slot].timer = 0;
                    }
                }
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = -0.8;
                }
                if (m_objects[slot].frame == 2 || m_objects[slot].frame == 3) {
                    m_objects[slot].vy += 0.035;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].frame = 4;
                        m_objects[slot].timer = 0;
                    }
                }
                if (pattern == k463214AHit || pattern == k463214BHit || pattern == k463214CHit) {
                    if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                        m_objects[slot].x = 420.0;
                        m_objects[slot].frame = 7;
                        m_objects[slot].timer = 0;
                        m_objects[slot].facing = facing;
                    }
                    if (m_objects[slot].frame == 7 && m_throwArrived == 1) {
                        m_objects[slot].frame = 8;
                        m_objects[slot].timer = 0;
                        break;
                    }
                    if (m_objects[slot].frame == 0xa && m_throwArrived == 1) {
                        m_objects[slot].frame = 0xb;
                        m_objects[slot].timer = 0;
                        break;
                    }
                    if (m_objects[slot].frame == 0xd && m_throwArrived == 1) {
                        m_objects[slot].frame = 0xe;
                        m_objects[slot].timer = 0;
                        break;
                    }
                    if (m_throwArrived == 1 && (m_objects[slot].frame == 8 || m_objects[slot].frame == 0xb || m_objects[slot].frame == 0xe)) {
                        m_objects[slot].hitstop = 0x1e;
                        (*m_opponent)->m_hitstop = 0x1e;
                        m_throwArrived = 0;
                        if (m_objects[slot].frame == 0xe) {
                            m_playVoice = 9;
                        }
                    }
                    if ((m_objects[slot].frame == 8 || m_objects[slot].frame == 0xb) && m_objects[slot].timer == 0xd2 || m_objects[slot].frame == 0xe && m_objects[slot].timer == 0x294) {
                        if ((WORD)Random(0, 9) < 5) {
                            m_playVoice = 6;
                            m_catchState = 3;
                            m_objects[slot].timer++;
                            break;
                        }
                        m_playVoice = 7;
                        m_catchState = 4;
                    }
                    if ((m_objects[slot].frame == 8 || m_objects[slot].frame == 0xb) && m_objects[slot].timer == 0x14a || m_objects[slot].frame == 0xe && m_objects[slot].timer == 0x30c) {
                        if (m_catchState == 4) {
                            effect.type = 0;
                            effect.x = (double)(int)(*m_opponent)->x;
                            effect.y = -80.0;
                            effect.scale = 2;
                            effect.layer = 1;
                            effect.sound = 0x16;
                            m_game->CreateEffect((EffectDesc*)&effect);
                            m_catchState = 5;
                            m_objects[slot].layer = 1;
                            (*m_opponent)->pattern = kHitAirHeavy;
                            (*m_opponent)->StartPattern();
                            (*m_opponent)->m_hitVy = -13.0;
                            (*m_opponent)->m_hitVx = 0.0;
                            if (m_objects[slot].frame == 8) {
                                DealDamage(0x708, 50.0);
                                m_objects[slot].frame = 0xf;
                            }
                            if (m_objects[slot].frame == 0xb) {
                                DealDamage(0xdac, 50.0);
                                m_objects[slot].frame = 0x12;
                            }
                            if (m_objects[slot].frame == 0xe) {
                                DealDamage(0x1964, 50.0);
                                m_objects[slot].frame = 0x15;
                            }
                            m_objects[slot].timer = 0;
                            m_patternVar2 = 0xb;
                        }
                        if (m_catchState == 3 && (pattern == k463214AHit || pattern == k463214BHit && m_patternVar1 == 1 || pattern == k463214CHit && m_patternVar1 == 2)) {
                            m_objects[slot].scale = 1;
                            (*m_opponent)->pattern = kHitAir;
                            (*m_opponent)->StartPattern();
                            (*m_opponent)->m_hitVy = -2.0;
                            (*m_opponent)->m_hitVx = 0.0;
                        }
                    }
                    if (((m_objects[slot].frame == 8 || m_objects[slot].frame == 0xb) && m_objects[slot].timer == 0x159 || m_objects[slot].frame == 0xe && m_objects[slot].timer == 0x31b) && m_objects[slot].scale == 1) {
                        RemoveObject(slot);
                        break;
                    }
                    if ((pattern == k463214BHit || pattern == k463214CHit) && frame == 0x1c && timer == 0) {
                        m_playVoice = 8;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame++;
                    }
                }
                m_objects[slot].timer++;
                if ((m_objects[slot].frame == 0x11 || m_objects[slot].frame == 0x14 || m_objects[slot].frame == 0x17) && m_objects[slot].timer == duration - 0xf) {
                    m_objects[slot].scale = 1;
                }
                if ((m_objects[slot].frame == 0x11 || m_objects[slot].frame == 0x14 || m_objects[slot].frame == 0x17) && m_objects[slot].timer == duration) {
                    RemoveObject(slot);
                    m_catchState = 5;
                    break;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame == 7) {
                        RemoveObject(slot);
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj5AEffect:
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
            case kObj2AEffect:
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
            case kObjJumpAEffect:
                m_objects[slot].x = x - facing * 7;
                m_objects[slot].y = y - 41.0;
                if (pattern != kJumpA) {
                    RemoveObject(slot);
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
            case kObj41236Flat1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].SetVelocity(0.0, 3.6);
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = -0.9;
                    m_objects[slot].vy = -2.7;
                    break;
                }
                if (m_objects[slot].frame > 0) {
                    m_objects[slot].vy += 0.045;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = -0.5 * m_objects[slot].vy;
                    if (m_objects[slot].scale == 0) {
                        m_objects[slot].scale = 1;
                    } else {
                        RemoveObject(slot);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0 || m_objects[slot].y < -510.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj41236Flat2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].SetVelocity(0.0, 3.6);
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = -0.9;
                    m_objects[slot].vy = -2.7;
                    break;
                }
                if (m_objects[slot].frame > 0) {
                    m_objects[slot].vy += 0.045;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = -0.5 * m_objects[slot].vy;
                    if (m_objects[slot].scale == 0) {
                        m_objects[slot].scale = 1;
                    } else {
                        RemoveObject(slot);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0 || m_objects[slot].y < -510.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj41236Flat3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].SetVelocity(0.0, 3.6);
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = -0.9;
                    m_objects[slot].vy = -2.7;
                    break;
                }
                if (m_objects[slot].frame > 0) {
                    m_objects[slot].vy += 0.045;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = -0.5 * m_objects[slot].vy;
                    if (m_objects[slot].scale == 0) {
                        m_objects[slot].scale = 1;
                    } else {
                        RemoveObject(slot);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0 || m_objects[slot].y < -510.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj41236Flat4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].SetVelocity(0.0, 3.6);
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = -0.9;
                    m_objects[slot].vy = -2.7;
                    break;
                }
                if (m_objects[slot].frame > 0) {
                    m_objects[slot].vy += 0.045;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = -0.5 * m_objects[slot].vy;
                    if (m_objects[slot].scale == 0) {
                        m_objects[slot].scale = 1;
                    } else {
                        RemoveObject(slot);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0 || m_objects[slot].y < -510.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj41236Up35:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].SetVelocity(-35.0, 3.6);
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = -0.9;
                    m_objects[slot].vy = -2.7;
                    break;
                }
                if (m_objects[slot].frame > 0) {
                    m_objects[slot].vy += 0.045;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = -0.5 * m_objects[slot].vy;
                    if (m_objects[slot].scale == 0) {
                        m_objects[slot].scale = 1;
                    } else {
                        RemoveObject(slot);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0 || m_objects[slot].y < -510.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj41236Up60:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].SetVelocity(-60.0, 3.6);
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = -0.9;
                    m_objects[slot].vy = -2.7;
                    break;
                }
                if (m_objects[slot].frame > 0) {
                    m_objects[slot].vy += 0.045;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = -0.5 * m_objects[slot].vy;
                    if (m_objects[slot].scale == 0) {
                        m_objects[slot].scale = 1;
                    } else {
                        RemoveObject(slot);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0 || m_objects[slot].y < -510.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj41236Up60b:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].SetVelocity(-60.0, 3.6);
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = -0.9;
                    m_objects[slot].vy = -2.7;
                    break;
                }
                if (m_objects[slot].frame > 0) {
                    m_objects[slot].vy += 0.045;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = -0.5 * m_objects[slot].vy;
                    if (m_objects[slot].scale == 0) {
                        m_objects[slot].scale = 1;
                    } else {
                        RemoveObject(slot);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0 || m_objects[slot].y < -510.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj41236Up85:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].SetVelocity(-85.0, 3.6);
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = -0.9;
                    m_objects[slot].vy = -2.7;
                    break;
                }
                if (m_objects[slot].frame > 0) {
                    m_objects[slot].vy += 0.045;
                }
                if (m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = -0.5 * m_objects[slot].vy;
                    if (m_objects[slot].scale == 0) {
                        m_objects[slot].scale = 1;
                    } else {
                        RemoveObject(slot);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0 || m_objects[slot].y < -510.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj463214C:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 4;
                }
                if (m_objects[slot].frame == 4 && m_objects[slot].timer == 0 && frame < 0xc && m_objectVar1[slot] == 2) {
                    effect.type = 0x1c4;
                    effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 0x3c);
                    effect.y = m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5 && m_objectVar1[slot] < 4) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjCatchThrow3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].SetVelocity(0.0, 3.6);
                }
                if (m_objects[slot].x > 370.0) {
                    effect.type = 0;
                    effect.x = (double)((int)x + facing * 0x14);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.sound = 2;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    RemoveObject(slot);
                    m_throwArrived = 1;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjCatchThrow1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].SetVelocity(0.0, 3.6);
                }
                if (m_objects[slot].x > 370.0) {
                    effect.type = 0;
                    effect.x = (double)((int)x + facing * 0x14);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.sound = 2;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    RemoveObject(slot);
                    m_throwArrived = 1;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjCatchThrow2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].SetVelocity(0.0, 3.6);
                }
                if (m_objects[slot].x > 370.0) {
                    effect.type = 0;
                    effect.x = (double)((int)x + facing * 0x14);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.sound = 2;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    RemoveObject(slot);
                    m_throwArrived = 1;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjThrowHelperBack:
                m_objects[slot].facing = *(char*)&m_throwHelperFacing;
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 1.5;
                    m_objects[slot].vy = -2.3;
                }
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                }
                if (m_objects[slot].frame == 1 && (*m_opponent)->pattern == kThrownLying2) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].frame == 2 && m_objects[slot].vy + m_objects[slot].y > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 3;
                    m_objects[slot].timer = 0;
                }
                if (m_objects[slot].frame > 2 && m_objects[slot].frame < 6 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 2.1;
                    if ((*m_opponent)->pattern == kHitAirWallBounce) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].frame = 6;
                        m_objects[slot].timer = 0;
                    }
                }
                if (m_objects[slot].frame > 7) {
                    m_objects[slot].vx = 3.1;
                }
                if ((m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0) && m_objects[slot].frame > 7) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                    }
                }
                break;
            case kObjThrowCarrier:
                m_throwHelperFacing = m_objects[slot].facing;
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = -2.3;
                }
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                }
                if (m_objects[slot].frame == 1 && (*m_opponent)->y - m_objects[slot].y > 0.0) {
                    effect.type = 0;
                    effect.x = (double)((int)x + facing * 0x25);
                    effect.y = (double)((int)y - 0x2a);
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_playSound = 0x1a;
                    (*m_opponent)->pattern = kThrownLying2;
                    (*m_opponent)->timer = 0;
                    (*m_opponent)->frame = 0;
                    (*m_opponent)->StopMoving();
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                }
                if (m_objects[slot].frame == 2) {
                    (*m_opponent)->y = m_objects[slot].y - 50.0;
                    (*m_opponent)->x = m_objects[slot].x;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].frame = 3;
                        m_objects[slot].timer = 0;
                        m_objects[slot].facing = 1;
                        m_throwHelperFacing = 1;
                        if (m_objects[slot].x > 320.0) {
                            m_objects[slot].facing = -1;
                            m_throwHelperFacing = -1;
                        }
                    }
                }
                if (m_objects[slot].frame > 2 && m_objects[slot].frame < 6 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 2.1;
                    (*m_opponent)->y = m_objects[slot].y - 50.0;
                    (*m_opponent)->x = m_objects[slot].x;
                    if (m_objects[slot].x - x > 160.0 || m_objects[slot].x - x < -160.0) {
                        m_objects[slot].frame = 6;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].timer = 0;
                        (*m_opponent)->frame = 0;
                        (*m_opponent)->timer = 0;
                        (*m_opponent)->facing = -m_objects[slot].facing;
                        (*m_opponent)->m_hitVx = -2.1;
                        (*m_opponent)->m_hitVy = -1.5;
                        (*m_opponent)->pattern = kHitAirWallBounce;
                        DealDamage(0x320, 750.0);
                        (*m_opponent)->m_noAirRecovery = 0;
                        (*m_opponent)->m_untechTime = 0x78;
                    }
                }
                if (m_objects[slot].frame > 7) {
                    m_objects[slot].vx = 3.1;
                }
                if ((m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0) && m_objects[slot].frame > 7) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                    }
                }
                break;
            case kObjThrowHelperFront:
                m_objects[slot].facing = *(char*)&m_throwHelperFacing;
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -1.5;
                    m_objects[slot].vy = -2.3;
                }
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                }
                if (m_objects[slot].frame == 1 && (*m_opponent)->pattern == kThrownLying2) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].frame == 2 && m_objects[slot].vy + m_objects[slot].y > 0.0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 3;
                    m_objects[slot].timer = 0;
                }
                if (m_objects[slot].frame > 2 && m_objects[slot].frame < 6 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 2.1;
                    if ((*m_opponent)->pattern == kHitAirWallBounce) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].frame = 6;
                        m_objects[slot].timer = 0;
                    }
                }
                if (m_objects[slot].frame > 7) {
                    m_objects[slot].vx = 3.1;
                }
                if ((m_objects[slot].x < -30.0 || m_objects[slot].x > 670.0) && m_objects[slot].frame > 7) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 3;
                    }
                }
                break;
            case kObjAir214:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 0x63;
                    m_playVoice = 0xd;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjJump6CEffect:
                m_objects[slot].x = facing * 0x38 + x;
                m_objects[slot].y = y - 44.0;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 4 && pattern == kJump6C && frame < 9) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjWalkerSourceFront:
                if (m_objects[slot].timer == 0) {
                    effect.keep = 1;
                    effect.type = m_objectVar1[slot] + 0x19b;
                    if (m_objects[slot].facing == -1) {
                        effect.x = (double)(m_game->m_view.left - 0x14 - (WORD)Random(0, 0x14) - (m_patternVar2 << 3));
                    }
                    if (m_objects[slot].facing == 1) {
                        effect.x = (double)(m_game->m_view.right + 0x14 + (WORD)Random(0, 0x14) + m_patternVar2 * 8);
                    }
                    effect.y = (double)(4 - (WORD)Random(0, 4));
                    effect.shadow = 1;
                    effect.facing = -m_objects[slot].facing;
                    effect.scale = 0;
                    effect.layer = 1;
                    m_objectVar1[slot]++;
                    if (m_objectVar1[slot] > 5) {
                        m_objectVar1[slot] = 0;
                    }
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar2[slot] < 0xd) {
                            m_objects[slot].frame = 0;
                            m_objectVar2[slot]++;
                            break;
                        }
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjWalkerSourceBack:
                if (m_objects[slot].timer == 0) {
                    effect.keep = 1;
                    effect.type = m_objectVar1[slot] + 0x19b;
                    if (m_objects[slot].facing == 1) {
                        effect.x = (double)(m_game->m_view.left - 0x14 - (WORD)Random(0, 0x14) - (m_patternVar2 << 3));
                    }
                    if (m_objects[slot].facing == -1) {
                        effect.x = (double)(m_game->m_view.right + 0x14 + (WORD)Random(0, 0x14) + m_patternVar2 * 8);
                    }
                    effect.y = (double)(4 - (WORD)Random(0, 4));
                    effect.shadow = 1;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 0;
                    effect.layer = 1;
                    m_objectVar1[slot]++;
                    if (m_objectVar1[slot] > 5) {
                        m_objectVar1[slot] = 0;
                    }
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar2[slot] < 0xd) {
                            m_objects[slot].frame = 0;
                            m_objectVar2[slot]++;
                            break;
                        }
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjWalkerSourceNear:
                if (m_objects[slot].timer == 0) {
                    effect.keep = 1;
                    effect.type = m_objectVar1[slot] + 0x19b;
                    effect.x = (double)((int)x - ((WORD)Random(0, 0x14) + 0x154 + m_patternVar2 * 8) * facing);
                    effect.y = (double)(4 - (WORD)Random(0, 4));
                    effect.shadow = 1;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 0;
                    effect.layer = 1;
                    m_objectVar1[slot]++;
                    if (m_objectVar1[slot] > 5) {
                        m_objectVar1[slot] = 0;
                    }
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar2[slot] < 0x23) {
                            m_objects[slot].frame = 0;
                            m_objectVar2[slot]++;
                            break;
                        }
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjAir236236A:
                m_objects[slot].hitsLeft = 0x63;
                if (frame > 0x31 && frame < 0x96) {
                    RemoveObject(slot);
                    break;
                }
                if (pattern == kAir236236A) {
                    if (frame == 7) {
                        m_objects[slot].x = (facing << 5) + x;
                        m_objects[slot].y = y - 21.0;
                    }
                    if (frame == 8) {
                        m_objects[slot].x = facing * 0x17 + x;
                        m_objects[slot].y = y - 60.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 9) {
                        m_objects[slot].x = facing * 0x13 + x;
                        m_objects[slot].y = y - 78.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xa) {
                        m_objects[slot].x = (facing << 4) + x;
                        m_objects[slot].y = y - 80.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xb) {
                        m_objects[slot].x = facing * 0xf + x;
                        m_objects[slot].y = y - 81.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xc) {
                        m_objects[slot].frame = 5;
                        m_objects[slot].x = x - facing * 3;
                        m_objects[slot].y = y - 96.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xd) {
                        m_objects[slot].x = x - facing * 0x21;
                        m_objects[slot].y = y - 84.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xe) {
                        m_objects[slot].x = x - facing * 0x23;
                        m_objects[slot].y = y - 81.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xf) {
                        m_objects[slot].x = x - facing * 0x24;
                        m_objects[slot].y = y - 76.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0x10) {
                        m_objects[slot].x = facing * 0x34 + x;
                        m_objects[slot].y = y - 38.0;
                        m_objects[slot].layer = 1;
                    }
                    if (frame == 0x11 && m_objects[slot].frame < 0x27) {
                        m_objects[slot].x = facing * 0x14 + x;
                        m_objects[slot].y = y + 2.0;
                        m_objects[slot].layer = 1;
                        m_objects[slot].frame = 0x27;
                        m_objects[slot].timer = 0;
                    }
                }
                if (m_objects[slot].frame >= 0x27) {
                    if (m_objectVar1[slot] == 0) {
                        effect.keep = 1;
                        effect.type = 0x1d4;
                        effect.movesInFreeze = 1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y;
                        effect.keep = 1;
                        effect.facing = facing;
                        effect.scale = 2;
                        effect.layer = 1;
                        SpawnObject(&effect);
                        m_objects[slot].vx = 2.0;
                        m_objects[slot].vy = 2.0;
                        m_objects[slot].hitsLeft = 5;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].y + vy > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].pattern = kObjAir236236AImpact;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].hitsLeft = 0;
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 0x31 || m_objects[slot].frame == 0x2c || m_objects[slot].frame == 0x36) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == 0x27) {
                        m_objects[slot].frame = m_objects[slot].frame - 0x14;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 0x14;
                        m_objects[slot].attackResult = 0;
                    }
                }
                break;
            case kObjAir236236AImpact:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].attackResult = 0;
                    m_playVoice = 4;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjAir236236B:
                m_objects[slot].hitsLeft = 0x63;
                if (frame > 0x31 && frame < 0x96) {
                    RemoveObject(slot);
                    break;
                }
                if (pattern == kAir236236B) {
                    if (frame == 7) {
                        m_objects[slot].x = (facing << 5) + x;
                        m_objects[slot].y = y - 21.0;
                    }
                    if (frame == 8) {
                        m_objects[slot].x = facing * 0x17 + x;
                        m_objects[slot].y = y - 60.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 9) {
                        m_objects[slot].x = facing * 0x13 + x;
                        m_objects[slot].y = y - 78.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xa) {
                        m_objects[slot].x = (facing << 4) + x;
                        m_objects[slot].y = y - 80.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xb) {
                        m_objects[slot].x = facing * 0xf + x;
                        m_objects[slot].y = y - 81.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xc) {
                        m_objects[slot].frame = 5;
                        m_objects[slot].x = x - facing * 3;
                        m_objects[slot].y = y - 96.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xd) {
                        m_objects[slot].x = x - facing * 0x21;
                        m_objects[slot].y = y - 84.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xe) {
                        m_objects[slot].x = x - facing * 0x23;
                        m_objects[slot].y = y - 81.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xf) {
                        m_objects[slot].x = x - facing * 0x24;
                        m_objects[slot].y = y - 76.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0x10) {
                        m_objects[slot].x = facing * 0x34 + x;
                        m_objects[slot].y = y - 38.0;
                        m_objects[slot].layer = 1;
                    }
                    if (frame == 0x11 && m_objects[slot].frame < 0x27) {
                        m_objects[slot].x = facing * 0x14 + x;
                        m_objects[slot].y = y + 2.0;
                        m_objects[slot].layer = 1;
                        m_objects[slot].frame = 0x27;
                        m_objects[slot].timer = 0;
                    }
                }
                if (m_objects[slot].frame >= 0x27) {
                    if (m_objectVar1[slot] == 0) {
                        effect.keep = 1;
                        effect.type = 0x1d4;
                        effect.movesInFreeze = 1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y;
                        effect.keep = 1;
                        effect.facing = facing;
                        effect.scale = 2;
                        effect.layer = 1;
                        SpawnObject(&effect);
                        m_objects[slot].vx = 2.0;
                        m_objects[slot].vy = 2.0;
                        m_objects[slot].hitsLeft = 5;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].y + vy > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].pattern = kObjAir236236BImpact;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].hitsLeft = 0;
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 0x31 || m_objects[slot].frame == 0x2c || m_objects[slot].frame == 0x36) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == 0x27) {
                        m_objects[slot].frame = m_objects[slot].frame - 0x14;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 0x14;
                        m_objects[slot].attackResult = 0;
                    }
                }
                break;
            case kObjAir236236BImpact:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].attackResult = 0;
                    m_playVoice = 4;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjAir236236Trail:
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
            case kObjAir236236C:
                m_objects[slot].hitsLeft = 0x63;
                if (frame > 0x31 && frame < 0x96) {
                    RemoveObject(slot);
                    break;
                }
                if (pattern == kAir236236C) {
                    if (frame == 7) {
                        m_objects[slot].x = (facing << 5) + x;
                        m_objects[slot].y = y - 21.0;
                    }
                    if (frame == 8) {
                        m_objects[slot].x = facing * 0x17 + x;
                        m_objects[slot].y = y - 60.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 9) {
                        m_objects[slot].x = facing * 0x13 + x;
                        m_objects[slot].y = y - 78.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xa) {
                        m_objects[slot].x = (facing << 4) + x;
                        m_objects[slot].y = y - 80.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xb) {
                        m_objects[slot].x = facing * 0xf + x;
                        m_objects[slot].y = y - 81.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xc) {
                        m_objects[slot].frame = 5;
                        m_objects[slot].x = x - facing * 3;
                        m_objects[slot].y = y - 96.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xd) {
                        m_objects[slot].x = x - facing * 0x21;
                        m_objects[slot].y = y - 84.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xe) {
                        m_objects[slot].x = x - facing * 0x23;
                        m_objects[slot].y = y - 81.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0xf) {
                        m_objects[slot].x = x - facing * 0x24;
                        m_objects[slot].y = y - 76.0;
                        m_objects[slot].layer = 0;
                    }
                    if (frame == 0x10) {
                        m_objects[slot].x = facing * 0x34 + x;
                        m_objects[slot].y = y - 38.0;
                        m_objects[slot].layer = 1;
                    }
                    if (frame == 0x11 && m_objects[slot].frame < 0x27) {
                        m_objects[slot].x = facing * 0x14 + x;
                        m_objects[slot].y = y + 2.0;
                        m_objects[slot].layer = 1;
                        m_objects[slot].frame = 0x27;
                        m_objects[slot].timer = 0;
                    }
                }
                if (m_objects[slot].frame >= 0x27) {
                    if (m_objectVar1[slot] == 0) {
                        effect.keep = 1;
                        effect.type = 0x1d4;
                        effect.movesInFreeze = 1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y;
                        effect.keep = 1;
                        effect.facing = facing;
                        effect.scale = 2;
                        effect.layer = 1;
                        SpawnObject(&effect);
                        m_objects[slot].vx = 2.0;
                        m_objects[slot].vy = 2.0;
                        m_objects[slot].hitsLeft = 5;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].y + vy > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].pattern = kObjAir236236CImpact;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].hitsLeft = 0;
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 0x31 || m_objects[slot].frame == 0x2c || m_objects[slot].frame == 0x36) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == 0x27) {
                        m_objects[slot].frame = m_objects[slot].frame - 0x14;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 0x14;
                        m_objects[slot].attackResult = 0;
                    }
                }
                break;
            case kObjAir236236CImpact:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].attackResult = 0;
                    m_playVoice = 4;
                }
                if (m_objects[slot].frame == 0xf && m_objects[slot].timer == 0 && m_objects[slot].x + m_objects[slot].facing * 0x78 < 720.0 && m_objects[slot].x + m_objects[slot].facing * 0x78 > -80.0) {
                    effect.keep = 1;
                    effect.type = 0x1d6;
                    effect.x = m_objects[slot].x + facing * 0x78;
                    effect.y = 0.0;
                    effect.keep = 1;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
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
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar2[slot] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[slot].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectVar2[slot] < 0xa) {
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
                    m_objectVar2[slot] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[slot].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[slot].vy += 0.03;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectVar2[slot] < 0xa) {
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
        if (slot >= 0x40) {
            slot = 0;
        }
    }
}
