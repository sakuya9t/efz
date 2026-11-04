// CMio (0x588310-0x59c49f): the character class whose files are in mio\ in the game
// folder (mio.dat sprites, mio.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMio::CMio(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

    strcpy(m_name, "mio");
    lastSurface = 852;
    m_patternVar1 = 0;
    m_patternVar2 = 0.0;
    m_patternVar3 = 0.0;
    m_stance = 0;
    m_encasedBreakOut = 0;
    m_pointX[0] = -22;
    m_pointY[0] = -56;
    m_pointX[1] = 17;
    m_pointY[1] = 0;
    m_pointX[2] = 15;
    m_pointY[2] = -23;
    m_pointX[3] = 22;
    m_pointY[3] = -26;
    m_pointX[4] = 33;
    m_pointY[4] = -52;
    m_resultPictures = 5;
    m_rivals[0] = 4;
    m_rivals[1] = 7;
    m_rivals[2] = 1;
    m_rivals[10] = 11;
    i = 0;
    for (; i < 64; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
}

void CMio::Reset()
{
    int i;

    m_patternVar1 = 0;
    m_patternVar2 = 0.0;
    m_patternVar3 = 0.0;
    m_stance = 0;
    m_encasedBreakOut = 0;
    m_pointX[0] = -22;
    m_pointY[0] = -56;
    m_pointX[1] = 17;
    m_pointY[1] = 0;
    m_pointX[2] = 15;
    m_pointY[2] = -23;
    m_pointX[3] = 22;
    m_pointY[3] = -26;
    m_pointX[4] = 33;
    m_pointY[4] = -52;
    i = 0;
    for (; i < 64; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
    CPlayer::Reset();
}

void CMio::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0.0;
    m_patternVar3 = 0.0;
    CPlayer::StartPattern();
}

void CMio::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
}

void CMio::Move()
{
    MoveOnGround();
}

void CMio::StartCommand()
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
    if (m_command == kCmd22C && (m_rfGauge >= 500.0 && m_attackResult > 1 || m_rfBlue > 0 && m_attackResult > 1 && m_attackResult != 6) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[kInstantCharge].level) {
        StartPattern();
        ClearBufferedPress();
        pattern = kInstantCharge;
        if (y < 0.0) {
            pattern = kAirInstantCharge;
        }
        return;
    }
    if (m_stance == 0) {
        if (m_sealLevel < 2) {
            if (m_hp < 3333 && m_command == kCmd641236C && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kLv4;
                return;
            }
            if (m_command == kCmd214214C && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k214214C;
                return;
            }
            if ((m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 2000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k214214B;
                return;
            }
            if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k214214A;
                return;
            }
            if (m_command == kCmd236236C && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k236236C;
                return;
            }
            if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 2000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k236236B;
                return;
            }
            if ((m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k236236A;
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
            if (m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k623A;
                return;
            }
            if (m_command == kCmd214C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k214C;
                return;
            }
            if ((m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k214B;
                return;
            }
            if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k214A;
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
                    frame = 3;
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
                    frame = 3;
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
        if (m_sealLevel < 3 && m_command == kCmdUp && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_airActions < 1 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAirJump].level) {
            StartPattern();
            ClearBufferedPress();
            FaceOpponent();
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
                if (m_patterns[pattern].cancelLevel <= m_patterns[kJump2C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_inputY == 1) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kJump2C;
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
                if (m_patterns[pattern].cancelLevel <= m_patterns[k6C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = k6C;
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
    }
    if (m_stance == 1) {
        if (m_sealLevel < 2) {
            if (m_hp < 3333 && m_command == kCmdB5A2AB && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_attackResult != 6 && m_patterns[pattern].cancelLevel <= m_patterns[kFloatLv4].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloatLv4;
                return;
            }
            if (m_command == kCmd214214C && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat214214C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat214214C;
                return;
            }
            if ((m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 2000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat214214B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat214214B;
                return;
            }
            if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat214214A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat214214A;
                return;
            }
            if (m_command == kCmd236236C && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat236236C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat236236C;
                if (y < 0.0) {
                    frame = 3;
                }
                return;
            }
            if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 2000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat236236B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat236236B;
                if (y < 0.0) {
                    frame = 3;
                }
                return;
            }
            if ((m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat236236A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat236236A;
                if (y < 0.0) {
                    frame = 3;
                }
                return;
            }
            if (m_command == kCmd214C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat214C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat214C;
                return;
            }
            if (m_command == kCmd214B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat214B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat214B;
                return;
            }
            if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat214A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat214A;
                return;
            }
            if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat236C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat236C;
                return;
            }
            if ((m_command == kCmd236B || m_command == kCmd236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat236B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat236B;
                return;
            }
            if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat236A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat236A;
                return;
            }
            if (m_command == kCmd412C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat412C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat412C;
                if (y < 0.0) {
                    frame = 3;
                    m_patternVar1 = 100;
                }
                return;
            }
            if ((m_command == kCmd412B || m_command == kCmd412C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat412B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat412B;
                if (y < 0.0) {
                    frame = 3;
                }
                return;
            }
            if (m_command == kCmd412A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat412A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat412A;
                if (y < 0.0) {
                    frame = 3;
                }
                return;
            }
        }
        if (m_sealLevel < 1 && (m_command == kCmdDashLeft || m_command == kCmdDashRight)) {
            if (y < 0.0 && m_airDashes < 2) {
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
                pattern = kFloatDashA;
                if (m_inputY == 1) {
                    pattern = kFloatDash2A;
                }
                return;
            }
            if (y < 0.0) {
                if (m_patterns[pattern].cancelLevel <= m_patterns[kFloatJumpA].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloatJumpA;
                }
                return;
            }
            if ((m_inputY == 1 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat2AClose].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && x - (*m_opponent)->x > -60.0 && x - (*m_opponent)->x < 60.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat2AClose;
                return;
            }
            if ((m_inputY == 1 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat2A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat2A;
                return;
            }
            if (m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) {
                if (m_patterns[pattern].cancelLevel <= m_patterns[kFloat5AClose].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && x - (*m_opponent)->x > -60.0 && x - (*m_opponent)->x < 60.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloat5AClose;
                    return;
                }
                if (m_patterns[pattern].cancelLevel <= m_patterns[kFloat5A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloat5A;
                    return;
                }
            }
        }
        if (m_pressB == 1 || (m_bufferedPress & kInputB) != 0 || (m_dashBufferedPress & kInputB) != 0) {
            if (pattern == kDashForward && m_inputX != -facing) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloatDashB;
                if (m_inputY == 1) {
                    pattern = kFloatDash2B;
                }
                return;
            }
            if (y < 0.0) {
                if (m_inputY == 1 && m_patterns[pattern].cancelLevel <= m_patterns[kFloatJump2B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloatJump2B;
                    return;
                }
                if (m_patterns[pattern].cancelLevel <= m_patterns[kFloatJumpB].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloatJumpB;
                }
                return;
            }
            if ((m_inputY == 1 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat2B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat2B;
                return;
            }
            if (m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) {
                if (m_inputX == -facing && m_patterns[pattern].cancelLevel <= m_patterns[kFloat4B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloat4B;
                    return;
                }
                if (m_patterns[pattern].cancelLevel <= m_patterns[kFloat5BClose].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && x - (*m_opponent)->x > -70.0 && x - (*m_opponent)->x < 70.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloat5BClose;
                    return;
                }
                if (m_patterns[pattern].cancelLevel <= m_patterns[kFloat5BClose].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloat5BClose;
                    return;
                }
            }
        }
        if (m_pressC == 1 || (m_bufferedPress & kInputC) != 0 || (m_dashBufferedPress & kInputC) != 0) {
            if (pattern == kDashForward && m_inputX != -facing) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloatDashC;
                if (m_inputY == 1) {
                    pattern = kFloatDash2C;
                }
                return;
            }
            if (y < 0.0) {
                if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kAirThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloatAirThrow;
                    return;
                }
                if (m_inputY == 1 && m_patterns[pattern].cancelLevel <= m_patterns[kFloatJump2C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloatJump2C;
                }
                if (m_patterns[pattern].cancelLevel <= m_patterns[kFloatJumpC].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloatJumpC;
                }
                return;
            }
            if ((m_inputY == 1 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat2C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat2C;
                return;
            }
            if (m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) {
                if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kThrow;
                    return;
                }
                if (m_patterns[pattern].cancelLevel <= m_patterns[kFloat5C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                    StartPattern();
                    ClearBufferedPress();
                    pattern = kFloat5C;
                    return;
                }
            }
        }
    }
    if (m_sealLevel < 2 && (m_pressD == 1 || (m_bufferedPress & kInputD) != 0 || (m_dashBufferedPress & kInputD) != 0)) {
        if (pattern != kJump2CLanding && m_patterns[pattern].cancelLevel <= m_patterns[kStanceChange].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kStanceChange;
            return;
        }
        if (m_stance == 1 && y < -30.0 && m_patterns[pattern].cancelLevel <= m_patterns[0x11].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = 0x11;
        }
    }
}

void CMio::DrawGauge()
{
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    if (m_stance == 0) {
        sprite = *anims[0x2b].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(45 - sprite.x, 31 - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 275 - sprite.width, 31 - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_stance == 1) {
        sprite = *anims[0x2c].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(45 - sprite.x, 31 - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 275 - sprite.width, 31 - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
}

void CMio::PreUpdate()
{
}

void CMio::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CMio::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 135);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputB) != 0 && step == 5) {
            m_command = kCmdB5A2AB;
            return;
        }
        if ((input & kInputA) != 0 && step == 4) {
            step = 5;
        }
        if ((input & (kInputB | kInputC | kInputD)) != 0 && step == 4) {
            break;
        }
        if ((input & kInputDirections) == kInputDown && step == 3) {
            step = 4;
        }
        if ((input & (kInputB | kInputC | kInputD)) != 0 && step == 2) {
            break;
        }
        if ((input & kInputA) != 0 && step == 2) {
            step = 3;
        }
        if (input == 0 && step == 1) {
            step = 2;
        }
        if ((input & (kInputA | kInputC | kInputD)) != 0 && step == 1) {
            break;
        }
        if ((input & kInputB) != 0 && step == 0 && m_gauge == 3000 && m_stance == 1) {
            step = 1;
        }
    }
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
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 0 && m_gauge == 3000 && m_stance == 0) {
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
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 0 && m_stance == 0) {
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
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 0 && m_stance == 1) {
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

void CMio::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == kFloat236A && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 40.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_stance == 0) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_stance == 0) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx > 40.0 && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_stance == 0) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (dx > 60.0 && dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_stance == 0) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (dx < 100.0) {
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_stance == 1 && m_gauge == 3000) {
                m_command = kCmdB5A2AB;
                return;
            }
            if (dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_stance == 1 && m_gauge >= 2000) {
                m_command = (WORD)Random(0, 2) + kCmd236236B;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0 && m_stance == 0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_rfGauge > 500.0 && m_stance == 1) {
                m_command = kCmd412C;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0 && m_stance == 0) {
                m_command = kCmd214C;
                return;
            }
        }
        if (dx < 160.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (dx < 80.0 && dx > 160.0) {
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_stance == 0 && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_stance == 1) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 2 && m_stance == 1 && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
        }
        if (dx > 160.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_stance == 1) {
            m_command = kCmd236A;
            return;
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (dy < 50.0 && y > (*m_opponent)->y && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -30.0 && y - (*m_opponent)->y < 0.0 && dx < 100.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < 50.0 && dy < 60.0 && dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (dy < 50.0 && dx < 100.0 && (WORD)Random(0, 100) < m_cpuSkill * 2) {
            m_command = kCmd623C;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 100);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0 && m_stance == 0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 7 && m_rfGauge > 500.0 && m_stance == 0) {
            m_command = (WORD)Random(0, 2) + kCmd623A;
            return;
        }
        if (m_cpuRoll < 10 && m_rfGauge > 500.0 && m_stance == 1) {
            m_command = 0x48;
            return;
        }
        if (m_cpuRoll < 13 && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 17 && m_cpuRoll > 12 && m_gauge >= 2000) {
            m_command = (WORD)Random(0, 1) + kCmd236236B;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 100);
        if (m_cpuRoll < (m_stance == 1) * 20 + 20) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 100) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == kJump2C || pattern == k623A || pattern == k623B || pattern == k623C || pattern == kStanceChange || pattern == k236B || pattern == k236BFollowupA)) {
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
    if (pattern == k236A && m_attackResult > 0 && (WORD)Random(0, 100) < 24.0f * m_cpuSkill) {
        m_command = kCmd236A;
        return;
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
    if (m_cpuAction == 0x12 && m_stance == 0) {
        m_inputX = facing;
        m_inputY = -1;
        if (y < 0.0) {
            m_pressC = 1;
            m_inputY = 1;
            if (pattern == kJump2C) {
                m_cpuAction = 0;
            }
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
            if (dx < 40.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 100) < 30) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (dx < 80.0 && m_cpuRoll > 399 && m_cpuRoll < 500) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 500 && m_cpuRoll < 550) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 550 && m_cpuRoll < 560) {
                m_cpuAction = 0xc;
                return;
            }
            if (m_cpuRoll > 980) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 960) {
                m_inputY = -1;
                m_inputX = facing;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll > 699) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 320 && m_cpuRoll < 420 && dx < 100.0) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll < 100) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 100 && m_cpuRoll < 350 && dx < 80.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 350 && m_cpuRoll < 700) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 700 && m_cpuRoll < 750) {
                m_cpuAction = 0x12;
                return;
            }
            if (m_cpuRoll > 980) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 700) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 100) < 20) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 100) < 40) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 320 && m_cpuRoll < 700 && dx < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 450 && dx < 110.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 549 && m_cpuRoll < 600) {
                m_command = ((WORD)Random(0, 3) == 0 && m_rfGauge > 500.0) * 2 + kCmd214A;
                return;
            }
            if (m_cpuRoll > 600 && m_cpuRoll < 700) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 980) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 700) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 100) < 20) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 100) < 40) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == k5C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 275) {
                m_command = ((WORD)Random(0, 4) == 0 && m_rfGauge > 500.0) * 2 + kCmd214A;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 550) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 649) {
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
            if (dx < 40.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 100) < 30) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (dx < 80.0 && m_cpuRoll > 399 && m_cpuRoll < 500) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 500 && m_cpuRoll < 550) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 550 && m_cpuRoll < 560) {
                m_cpuAction = 0xc;
                return;
            }
            if (m_cpuRoll > 700 && m_cpuRoll < 750) {
                m_cpuAction = 0x12;
                return;
            }
            if (m_cpuRoll > 980) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 960) {
                m_inputY = -1;
                m_inputX = facing;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll > 699) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 100 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 100 && m_cpuRoll < 120) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 120 && m_cpuRoll < 140 && dx < 100.0) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll < 40) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 40 && m_cpuRoll < 50 && dx < 80.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 50 && m_cpuRoll < 60) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 700 && m_cpuRoll < 750) {
                m_cpuAction = 0x12;
                return;
            }
            if (m_cpuRoll > 995) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 970) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 100) < 20) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 100) < 40) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == k2C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 100 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 3) + kCmd623A;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 650) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 400) {
                m_pressB = 1;
                return;
            }
            if (dx < 60.0 && m_cpuRoll < 500) {
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
        if (pattern == kJumpC) {
            if (m_cpuRoll > 950) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kDashA) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 250 && dx < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 910) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 100) < 20) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 100) < 40) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == kDashB) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 250 && dx < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 910) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 100) < 20) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 100) < 40) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == kDash2C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 200 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 300) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 350 && dx < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
        }
        if (pattern == kFloat5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 40.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 100) < 30) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (dx < 80.0 && m_cpuRoll > 399 && m_cpuRoll < 450) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 450 && m_cpuRoll < 600) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 960) {
                m_inputY = -1;
                m_inputX = facing;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll > 699) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                return;
            }
        }
        if (pattern == kFloat5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 50 && m_attackResult == 3 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 320 && m_cpuRoll < 420 && dx < 100.0) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll < 100 && dx < 90.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 100 && m_cpuRoll < 350 && dx < 120.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 600) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 600 && m_cpuRoll < 650 && dx > 100.0) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 990) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 900) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 100) < 20) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 100) < 40) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == kFloat5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 275) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 650) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kFloat5C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 40.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 100) < 30) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (dx < 80.0 && m_cpuRoll > 399 && m_cpuRoll < 450) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 450 && m_cpuRoll < 600) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 960) {
                m_inputY = -1;
                m_inputX = facing;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll > 699) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                return;
            }
        }
        if (pattern == kFloat2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 50 && m_attackResult == 3 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 320 && m_cpuRoll < 420 && dx < 100.0) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll < 100 && dx < 90.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 100 && m_cpuRoll < 350 && dx < 120.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 600) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 600 && m_cpuRoll < 650 && dx > 100.0) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 990) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 900) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 100) < 20) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 100) < 40) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == kFloat2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320 && m_attackResult == 3 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 275) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 650) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 400) {
                m_pressB = 1;
                return;
            }
            if (dx < 60.0 && m_cpuRoll < 500) {
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
        if (pattern == kJumpC) {
            if (m_cpuRoll > 950) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kFloatDashB) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 250 && dx < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 910) {
                m_cpuAction = 1;
            }
        }
        if (pattern == kFloatDashC) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320 && m_attackResult == 3 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 275) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 650) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kFloatDash2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 250 && dx < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 910) {
                m_cpuAction = 1;
            }
        }
        if (pattern == kFloatDash2C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320 && m_attackResult == 3 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 275) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 650) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 1;
                return;
            }
        }
    }
    if ((WORD)Random(0, 100) < 25.0f * m_cpuSkill) {
        m_cpuRoll = (WORD)Random(0, 1000);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown && m_stance == 0) {
                if (dx < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (dx < 45.0 && m_cpuRoll < 25) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 60.0 && m_cpuRoll < 35) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 80.0 && dx > 40.0 && m_cpuRoll < 60 && m_cpuRoll > 35) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 100.0 && m_cpuRoll < 80 && m_cpuRoll > 60) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 90.0 && dx > 50.0 && m_cpuRoll > 80 && m_cpuRoll < 87) {
                    m_cpuAction = 6;
                    return;
                }
                if (dx < 110.0 && dx > 70.0 && m_cpuRoll > 87 && m_cpuRoll < 95) {
                    m_cpuAction = 8;
                    if ((WORD)Random(0, 30) < 15) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
                if (dx > 120.0 && dx < 190.0 && m_cpuRoll > 95 && m_cpuRoll < 98) {
                    m_cpuAction = 0x10;
                    return;
                }
                if (dx > 80.0 && dx < 120.0 && m_cpuRoll > 100 && m_cpuRoll < 103) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 120 && m_cpuRoll > 105) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 60.0 && m_cpuRoll < 125 && m_cpuRoll > 120 && (*m_opponent)->pattern > kLastSharedAction && m_rfGauge > 500.0) {
                    m_command = kCmd623C;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 130 && m_cpuRoll > 125 && (*m_opponent)->pattern > kLastSharedAction && m_gauge >= 1000) {
                    m_command = (WORD)Random(0, 3) + kCmd236236A;
                    return;
                }
                if (m_cpuRoll < 135 && m_cpuRoll > 130) {
                    m_command = facing;
                    m_cpuAction = 5;
                    return;
                }
            }
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown && m_stance == 1) {
                if (dx < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (dx < 55.0 && m_cpuRoll < 10) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 70.0 && m_cpuRoll < 15) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 150.0 && dx > 80.0 && m_cpuRoll < 60 && m_cpuRoll > 35) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 180.0 && dx > 100.0 && m_cpuRoll < 80 && m_cpuRoll > 60 && (*m_opponent)->m_inputY != 1) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 100.0 && dx > 0.0 && m_cpuRoll < 95 && m_cpuRoll > 80) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 150.0 && dx > 120.0 && m_cpuRoll < 110 && m_cpuRoll > 95) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx > 80.0 && dx < 130.0 && m_cpuRoll > 110 && m_cpuRoll < 115) {
                    m_cpuAction = 0x10;
                    return;
                }
                if (dx > 100.0 && dx < 180.0 && m_cpuRoll > 115 && m_cpuRoll < 125) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (dx < 60.0 && m_cpuRoll < 130 && m_cpuRoll > 125 && (*m_opponent)->pattern > kLastSharedAction && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 133 && m_cpuRoll > 130 && (*m_opponent)->pattern > kLastSharedAction && m_gauge == 3000) {
                    m_command = kCmdB5A2AB;
                    return;
                }
                if (dx > 100.0 && m_cpuRoll < dx * 0.1 + 140.0 && m_cpuRoll > 135) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (dx > 120.0 && m_cpuRoll < 200 && m_cpuRoll > 193) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (dx > 80.0 && m_cpuRoll < 208 && m_cpuRoll > 200) {
                    m_command = (WORD)Random(0, 3) + kCmd412A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0 && m_stance == 0) {
                if ((*m_opponent)->vy < 0.0 && dx < 80.0 && dy < 120.0 && m_cpuRoll < 10) {
                    m_inputY = -1;
                    m_inputX = -facing;
                    return;
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 60.0 && dy < 120.0) {
                        if (m_cpuRoll < (m_rfGauge > 500.0 || m_rfBlue > 0) * 5 + 6) {
                            m_command = ((WORD)Random(0, 3) == 0) * 2 + kCmd623A;
                            return;
                        }
                    }
                    if (dx < 60.0 && dy < 120.0 && dy > 80.0 && m_cpuRoll < 15) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 80.0 && dy < 150.0 && dy > 100.0 && m_cpuRoll < 30) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                }
            }
            if ((*m_opponent)->y < 0.0 && m_stance == 1) {
                if ((*m_opponent)->vy < 0.0) {
                    if (dx < 100.0 && dy < 120.0 && m_cpuRoll < 10) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx < 100.0 && dy < 120.0 && m_cpuRoll < 15 && x > 80.0 && x < 560.0) {
                        m_command = facing == -1;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 110.0 && dy < 210.0 && m_cpuRoll < 10) {
                        m_command = (WORD)Random(0, 3) + kCmd214214A;
                        return;
                    }
                    if (dx < 100.0 && dy < 120.0 && m_cpuRoll < 4) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx < 100.0 && dx < 180.0 && dy < 140.0 && m_cpuRoll < 20) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 100.0 && dy < 140.0 && dy > 80.0 && m_cpuRoll < 40) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3 && m_stance == 0) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 60.0 && dy < 70.0 && m_cpuRoll < 100) {
                    m_pressA = 1;
                    return;
                }
                if (dx < 80.0 && dy > 50.0 && dy < 90.0 && m_cpuRoll > 200 && m_cpuRoll < 260) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 70.0 && dy > 60.0 && dy < 110.0 && m_cpuRoll > 260 && m_cpuRoll < 285) {
                    m_pressC = 1;
                    return;
                }
                if (dy + 30.0 > dx && dy - 30.0 < dx && dy < 110.0 && m_cpuRoll > 300 && m_cpuRoll < 310) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 80.0 && dy < 80.0 && y > (*m_opponent)->y && m_cpuRoll < 310) {
                    m_pressA = 1;
                    return;
                }
                if (dx < 90.0 && dy < 100.0 && y < (*m_opponent)->y && m_cpuRoll > 310 && m_cpuRoll < 400) {
                    m_pressB = 1;
                    return;
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3 && m_stance == 1) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 60.0 && dy < 70.0 && m_cpuRoll < 100) {
                    m_pressA = 1;
                    return;
                }
                if (dx < 160.0 && dx > 110.0 && dy > 20.0 && dy < 50.0 && m_cpuRoll > 200 && m_cpuRoll < 260) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 90.0 && dy < 150.0 && m_cpuRoll > 260) {
                    if (m_cpuRoll < (dy > 100.0) * 40 + 290) {
                        m_pressC = 1;
                        return;
                    }
                }
                if (dx < 130.0 && dx > 80.0 && dy < 80.0 && m_cpuRoll > 380 && m_cpuRoll < 400) {
                    m_command = (WORD)Random(0, 3) + kCmd412A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 80.0 && dx > 60.0 && dy < 60.0 && y > (*m_opponent)->y && m_cpuRoll < 210) {
                    m_pressA = 1;
                    return;
                }
                if (dx < 180.0 && dx > 100.0 && dy < 70.0 && y > (*m_opponent)->y && m_cpuRoll < 310) {
                    m_pressA = 1;
                    return;
                }
                if (dx < 90.0 && dy > 100.0 && dy < 150.0 && y < (*m_opponent)->y && m_cpuRoll > 310 && m_cpuRoll < 450) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 140.0 && dx > 80.0 && dy < 80.0 && m_cpuRoll > 380 && m_cpuRoll < 400) {
                    m_command = (WORD)Random(0, 3) + kCmd412A;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 100) < (m_stance == 0) * 3 * m_cpuSkill + 1.0f) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir || (*m_opponent)->pattern < kFirstHitReaction) && y == 0.0 && dx < 90.0 && (WORD)Random(0, 100) < ((m_stance == 1) << 2) * m_cpuSkill) {
        m_command = facing == -1;
        return;
    }
    if ((WORD)Random(0, 1000) < (m_stance == 0) + 1) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 100) < 2) {
        if ((WORD)Random(0, 100) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (dx > 160.0 && y == 0.0 && (WORD)Random(0, 100) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx < 100.0 && y == 0.0 && (WORD)Random(0, 100) < 1 && (*m_opponent)->pattern < kFirstHitReaction) {
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
    if ((WORD)Random(0, 100) < (m_stance == 1) * 30 + 40 && dx < 110.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 200) + 30;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 200) + 30;
        }
    }
    if ((WORD)Random(0, 100) < (m_stance == 0) * 30 + 40) {
        if (facing == 1) {
            m_cpuWalkRight = (WORD)Random(0, 200) + 30;
        } else {
            m_cpuWalkLeft = (WORD)Random(0, 200) + 30;
        }
        return;
    }
    if (facing == -1) {
        m_cpuWalkRight = (WORD)Random(0, 200) + 30;
        return;
    }
    m_cpuWalkLeft = (WORD)Random(0, 200) + 30;
}

void CMio::UpdateObjects()
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
            case kObjUnusedHopper:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 0.5;
                    m_objects[slot].vy = -2.8;
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y >= 0.0 && m_objects[slot].vy > 0.0 || m_objects[slot].attackResult > 1) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].vy = -1.5;
                    effect.type = 0x191;
                    effect.x = (double)(int)x;
                    effect.y = (double)(int)y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x192;
                    SpawnObject(&effect);
                    effect.type = 0x193;
                    SpawnObject(&effect);
                    m_playVoice = 2;
                    RemoveObject(slot);
                    break;
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
            case kObjUnusedHopperPiece1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -1.0 - (rand() < 16000) * 0.5 - (rand() < 16000) * 1.0;
                    m_objects[slot].vy = -1.5;
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y >= 0.0 && m_objects[slot].vy > 0.0) {
                    RemoveObject(slot);
                    break;
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
            case kObjUnusedHopperPiece2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (rand() < 16000) * 0.5 + 1.0 + (rand() < 16000) * 1.0;
                    m_objects[slot].vy = -1.1;
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y >= 0.0 && m_objects[slot].vy > 0.0) {
                    RemoveObject(slot);
                    break;
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
            case kObjUnusedHopperPiece3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (rand() < 16000) * 0.5 - (rand() < 16000) * 1.0;
                    m_objects[slot].vy = -1.3;
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y >= 0.0 && m_objects[slot].vy > 0.0) {
                    RemoveObject(slot);
                    break;
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
            case kObjFloat412Throw:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vy = (WORD)Random(0, 10) * 0.1 + 1.5;
                    m_objects[slot].vx = 2.1 - (WORD)Random(0, 5) * 0.1;
                }
                m_objects[slot].vx -= 0.02;
                if (m_objects[slot].vx < 0.1) {
                    m_objects[slot].vx = 0.1;
                }
                m_objects[slot].vy -= 0.02;
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
            case kObjFloat236Shot:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 6.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].frame == 1) {
                    m_objects[slot].vy += 0.04;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].attackResult == 3 && m_objects[slot].frame == 0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    m_playVoice = 5;
                    (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 60;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                if (m_objects[slot].attackResult > 1) {
                    m_objects[slot].vx = -1.0;
                    m_objects[slot].vy = -2.0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    break;
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
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y > 30.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloat236CShot:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 6.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].frame == 0 && (m_objects[slot].x < -960.0 || m_objects[slot].x > 1640.0)) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].x = -m_objects[slot].x;
                }
                if (m_objects[slot].frame == 2) {
                    m_objects[slot].vy += 0.04;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].attackResult == 3 && m_objects[slot].frame <= 1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 3;
                    m_objects[slot].timer = 0;
                    m_playVoice = 5;
                    (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 60;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                if (m_objects[slot].attackResult > 1) {
                    m_objects[slot].vx = -1.0;
                    m_objects[slot].vy = -2.0;
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    break;
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
                if (m_objects[slot].frame > 0 && (m_objects[slot].x < -2000.0 || m_objects[slot].x > 2000.0 || m_objects[slot].y > 30.0)) {
                    RemoveObject(slot);
                }
                break;
            case kObj236FollowupStrike:
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
            case kObj236FollowupRiser:
                m_objects[slot].vx -= 0.05;
                m_objects[slot].vy -= 0.02;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y > 0.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloat214ColumnBase:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
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
            case kObjFloat214Column:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    if (m_objects[slot].y < -190.0) {
                        effect.type = 0x19a;
                        effect.x = (double)(int)m_objects[slot].x;
                        effect.y = (double)((int)m_objects[slot].y + 160);
                        effect.facing = facing;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.keep = 1;
                        SpawnObject(&effect);
                    } else {
                        effect.type = 0x199;
                        effect.x = (double)(int)m_objects[slot].x;
                        effect.y = 0.0;
                        effect.facing = facing;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.keep = 1;
                        SpawnObject(&effect);
                    }
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
            case kObjSuperDrop:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vy += 0.045;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjSuperDropBounce:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vy += 0.035;
                if ((m_objects[slot].attackResult > 1 || m_objects[slot].y > 0.0) && m_objectVar1[slot] == 0) {
                    m_playVoice = 7;
                    m_objects[slot].hitsLeft = 0;
                    m_objectVar1[slot]++;
                    m_objects[slot].vy = -1.5;
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
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjSuperDropBreak:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vy += 0.04;
                if ((m_objects[slot].attackResult > 1 || m_objects[slot].y > 0.0) && m_objects[slot].frame == 0) {
                    m_playSound = 1;
                    m_objects[slot].hitsLeft = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].vy = -1.5;
                    effect.type = 0x19e;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)((int)m_objects[slot].y - 15);
                    effect.facing = facing;
                    effect.scale = 0;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    effect.type = 0x19f;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)((int)m_objects[slot].y + 15);
                    effect.facing = facing;
                    effect.scale = 0;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    effect.type = 0x1a0;
                    effect.x = (double)((int)m_objects[slot].x + 15);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.scale = 0;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    effect.type = 0x1a1;
                    effect.x = (double)((int)m_objects[slot].x - 15);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.scale = 0;
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
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjSuperDropPiece1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = (WORD)Random(0, 10) * 0.1 + -1.0;
                    m_objects[slot].vx = (WORD)Random(0, 10) * 0.1 + 0.5;
                }
                m_objects[slot].vy += 0.04;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjSuperDropPiece2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = (WORD)Random(0, 10) * 0.1 + -1.3;
                    m_objects[slot].vx = (WORD)Random(0, 10) * 0.1 + 0.9;
                }
                m_objects[slot].vy += 0.04;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjSuperDropPiece3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = (WORD)Random(0, 10) * 0.1 + -1.0;
                    m_objects[slot].vx = (WORD)Random(0, 10) * 0.1 + -0.5;
                }
                m_objects[slot].vy += 0.04;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjSuperDropPiece4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = (WORD)Random(0, 10) * 0.1 + -0.8;
                    m_objects[slot].vx = (WORD)Random(0, 10) * 0.1 + -0.9;
                }
                m_objects[slot].vy += 0.04;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloatSuperShotA:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 7;
                    m_objects[slot].vx = 1.0;
                    m_objectVar1[slot]++;
                }
                m_objects[slot].vx += 0.02;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 5 || m_objects[slot].frame == 8 || m_objects[slot].frame == 11 || m_objects[slot].frame == 14 || m_objects[slot].frame == 17 || m_objects[slot].frame == 20 || m_objects[slot].frame == 23) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y > 0.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloatSuperShotTrail:
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
            case kObjUnusedShotSlow:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 2.3;
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
                if (m_objects[slot].x < -420.0 || m_objects[slot].x > 1060.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjUnusedShotMid:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 2.6;
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
                if (m_objects[slot].x < -420.0 || m_objects[slot].x > 1060.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloat214Summoner:
                if (m_objects[slot].frame == 3 && m_objects[slot].timer == 30 && m_objects[slot].y == 0.0) {
                    effect.type = 0x19a;
                    effect.x = (double)((int)m_objects[slot].x - m_objects[slot].facing * 15);
                    effect.y = -556.0;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    m_playVoice = 6;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].frame == 3 && m_objects[slot].timer == 39 && m_objects[slot].y == 0.0) {
                    effect.type = 0x19a;
                    effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 6);
                    effect.y = -564.0;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    m_playVoice = 6;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].frame == 3 && m_objects[slot].timer == 48 && m_objects[slot].y == 0.0) {
                    effect.type = 0x19a;
                    effect.x = (double)((int)m_objects[slot].x - m_objects[slot].facing * 36);
                    effect.y = -560.0;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    m_playVoice = 6;
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
            case kObjUnusedShotFast:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 3.0;
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
                if (m_objects[slot].x < -420.0 || m_objects[slot].x > 1060.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloatSuperShotB:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 7;
                    m_objects[slot].vx = 1.0;
                    m_objectVar1[slot]++;
                }
                if (m_objectVar2[slot] < 0) {
                    effect.type = 0x1a3;
                    effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 40);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectVar2[slot] = 18;
                }
                m_objectVar2[slot]--;
                m_objects[slot].vx += 0.03;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 5 || m_objects[slot].frame == 8 || m_objects[slot].frame == 11 || m_objects[slot].frame == 14 || m_objects[slot].frame == 17 || m_objects[slot].frame == 20 || m_objects[slot].frame == 23) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y > 0.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloatSuperShotC:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 7;
                    m_objects[slot].vx = 1.0;
                    m_objectVar1[slot]++;
                }
                effect.type = 0x24;
                effect.x = (double)((int)m_objects[slot].x + 40 - (WORD)Random(0, 80));
                effect.y = (double)((int)m_objects[slot].y + 40 - (WORD)Random(0, 80));
                effect.scale = 2;
                effect.layer = 1;
                m_game->CreateEffect((EffectDesc*)&effect);
                if (m_objectVar2[slot] < 0) {
                    effect.type = 0x1a3;
                    effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 40);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectVar2[slot] = 6;
                    if (m_objects[slot].y > -80.0 && m_objectVar3[slot] < 0) {
                        effect.type = 0x1f;
                        effect.x = (double)(int)m_objects[slot].x;
                        effect.y = 0.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.side = m_objects[slot].facing == -1;
                        m_game->CreateEffect((EffectDesc*)&effect);
                        m_objectVar3[slot] = 3;
                    }
                    m_objectVar3[slot]--;
                }
                m_objectVar2[slot]--;
                m_objects[slot].vx += 0.04;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 5 || m_objects[slot].frame == 8 || m_objects[slot].frame == 11 || m_objects[slot].frame == 14 || m_objects[slot].frame == 17 || m_objects[slot].frame == 20 || m_objects[slot].frame == 23) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y > 0.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloat214214Shot:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 6.0;
                    m_objects[slot].vy = -4.5;
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
                if (m_objects[slot].y < -640.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloatLv4Far1:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far2:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far3:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far4:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far5:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far6:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar2 == 1.0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjFloatLv4FarRise;
                }
                break;
            case kObjFloatLv4FarRise:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = -15.0;
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
                if (m_objects[slot].y < -640.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloatLv4Near1:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near2:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near3:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near4:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near5:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near6:
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    m_playVoice = 10;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        effect.type = 0x1bb;
                        effect.x = (double)(int)(*m_opponent)->x;
                        effect.y = 0.0;
                        effect.facing = facing;
                        effect.layer = 1;
                        effect.scale = 2;
                        SpawnObject(&effect);
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjFloatLv4NearRise;
                        m_objects[slot].vy = -15.0;
                        m_patternVar2 = 1.0;
                        m_playVoice = 8;
                    }
                }
                break;
            case kObjFloatLv4NearRise:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].y < -640.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloatLv4Floor:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjFloatLv4Lift:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].y < -640.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjThrowHold:
                m_objects[slot].frame = 0;
                if (frame == 4) {
                    m_objects[slot].frame = 1;
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
                if (pattern != kThrowHold || frame > 4) {
                    RemoveObject(slot);
                }
                break;
            case kObjLv4Finish236C:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 2;
                }
                if (pattern != kLv4Finish236C || pattern == kLv4Finish236C && frame > 5) {
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
            case kObjFloat412CThrow:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vy = m_patternVar3;
                    m_objects[slot].vx = 2.8 - m_patternVar3 / 2.0;
                }
                m_objects[slot].vx -= 0.02;
                if (m_objects[slot].vx < 0.1) {
                    m_objects[slot].vx = 0.1;
                }
                m_objects[slot].vy -= 0.02;
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
            case kObj623CAura:
                m_objects[slot].x = x;
                m_objects[slot].y = y - 50.0;
                if (pattern != k623C || pattern == k623C && frame > 5) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 7;
                    }
                }
                break;
            case kObj214214Strike:
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
            case kObj214214CHit:
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
            case kObj236CWallA:
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
            case kObj236CWallB:
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
            case kObjAirThrowImpact1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = 0.5;
                    m_objects[slot].vy = -1.8;
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                    break;
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
            case kObjAirThrowImpact2:
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
            case kObjAirThrowImpact3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = 0.4;
                    m_objects[slot].vy = -1.7;
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                    break;
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
            case kObjFloat214Marker:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.type = 0x1a6;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = -3.0;
                    effect.facing = facing;
                    effect.layer = 0;
                    effect.scale = 0;
                    effect.keep = 1;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    effect.type = 0x1a6;
                    effect.x = (double)((int)m_objects[slot].x + facing * 27);
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.layer = 0;
                    effect.scale = 0;
                    effect.keep = 1;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = 0x1a6;
                    effect.x = (double)((int)m_objects[slot].x + facing * 9);
                    effect.y = 4.0;
                    effect.facing = facing;
                    effect.layer = 0;
                    effect.scale = 0;
                    effect.keep = 1;
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
            case kObj236FollowupBSpark:
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
            case kObj236FollowupBShot:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 1.5;
                    m_objectVar1[slot] = 0;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    effect.type = 0x1c7;
                    effect.x = (double)((int)m_objects[slot].x + 30 - (WORD)Random(0, 80));
                    effect.y = (double)((int)m_objects[slot].y + 20 - (WORD)Random(0, 40));
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                    m_playSound = 1;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] < 6) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame = 1;
                            m_objects[slot].hitsLeft = 1;
                            m_objects[slot].attackResult = 0;
                            break;
                        }
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
