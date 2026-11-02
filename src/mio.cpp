// CMio (0x588310-0x59c49f): the character class whose files are in mio\ in the game
// folder (mio.dat sprites, mio.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMio::CMio(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "mio");
    lastSurface = 0x354;
    m_patternVar1 = 0;
    m_patternVar2 = 0.0;
    m_patternVar3 = 0.0;
    m_stance = 0;
    m_encasedBreakOut = 0;
    m_pointX[0] = -0x16;
    m_pointY[0] = -0x38;
    m_pointX[1] = 0x11;
    m_pointY[1] = 0;
    m_pointX[2] = 0xf;
    m_pointY[2] = -0x17;
    m_pointX[3] = 0x16;
    m_pointY[3] = -0x1a;
    m_pointX[4] = 0x21;
    m_pointY[4] = -0x34;
    m_resultPictures = 5;
    m_rivals[0] = 4;
    m_rivals[1] = 7;
    m_rivals[2] = 1;
    m_rivals[0xa] = 0xb;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
}

void CMio::Reset()
{
    int v4;

    m_patternVar1 = 0;
    m_patternVar2 = 0.0;
    m_patternVar3 = 0.0;
    m_stance = 0;
    m_encasedBreakOut = 0;
    m_pointX[0] = -0x16;
    m_pointY[0] = -0x38;
    m_pointX[1] = 0x11;
    m_pointY[1] = 0;
    m_pointX[2] = 0xf;
    m_pointY[2] = -0x17;
    m_pointX[3] = 0x16;
    m_pointY[3] = -0x1a;
    m_pointX[4] = 0x21;
    m_pointY[4] = -0x34;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
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

void CMio::RemoveObject(short p1)
{
    m_objectVar1[p1] = 0;
    m_objectVar2[p1] = 0;
    m_objectVar3[p1] = 0;
    CPlayer::RemoveObject(p1);
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
            if (m_hp < 0xd05 && m_command == kCmd641236C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kLv4;
                return;
            }
            if (m_command == kCmd214214C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k214214C;
                return;
            }
            if ((m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k214214B;
                return;
            }
            if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k214214A;
                return;
            }
            if (m_command == kCmd236236C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k236236C;
                return;
            }
            if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k236236B;
                return;
            }
            if ((m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level) {
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
        if (m_pressA == 1 || (m_bufferedPress & 0x10) != 0 || (m_dashBufferedPress & 0x10) != 0) {
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
            if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k2A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k2A;
                return;
            }
            if ((m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) && m_patterns[pattern].cancelLevel <= m_patterns[k5A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k5A;
                return;
            }
        }
        if (m_pressB == 1 || (m_bufferedPress & 0x20) != 0 || (m_dashBufferedPress & 0x20) != 0) {
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
            if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k2B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k2B;
                return;
            }
            if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
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
        if (m_pressC == 1 || (m_bufferedPress & 0x40) != 0 || (m_dashBufferedPress & 0x40) != 0) {
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
            if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k2C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k2C;
                return;
            }
            if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
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
            if (m_hp < 0xd05 && m_command == kCmdB5A2AB && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_attackResult != 6 && m_patterns[pattern].cancelLevel <= m_patterns[kFloatLv4].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloatLv4;
                return;
            }
            if (m_command == kCmd214214C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat214214C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat214214C;
                return;
            }
            if ((m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat214214B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat214214B;
                return;
            }
            if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat214214A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat214214A;
                return;
            }
            if (m_command == kCmd236236C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat236236C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat236236C;
                if (y < 0.0) {
                    frame = 3;
                }
                return;
            }
            if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat236236B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat236236B;
                if (y < 0.0) {
                    frame = 3;
                }
                return;
            }
            if ((m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat236236A].level) {
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
                    m_patternVar1 = 0x64;
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
        if (m_pressA == 1 || (m_bufferedPress & 0x10) != 0 || (m_dashBufferedPress & 0x10) != 0) {
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
            if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat2AClose].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && x - (*m_opponent)->x > -60.0 && x - (*m_opponent)->x < 60.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat2AClose;
                return;
            }
            if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat2A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat2A;
                return;
            }
            if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
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
        if (m_pressB == 1 || (m_bufferedPress & 0x20) != 0 || (m_dashBufferedPress & 0x20) != 0) {
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
            if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat2B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat2B;
                return;
            }
            if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
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
        if (m_pressC == 1 || (m_bufferedPress & 0x40) != 0 || (m_dashBufferedPress & 0x40) != 0) {
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
            if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[kFloat2C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kFloat2C;
                return;
            }
            if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
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
    if (m_sealLevel < 2 && (m_pressD == 1 || (m_bufferedPress & 0x80) != 0 || (m_dashBufferedPress & 0x80) != 0)) {
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
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (m_stance == 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x2d - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x113 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_stance == 1) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x2d - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x113 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CMio::PreUpdate()
{
}

void CMio::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CMio::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = kCmdNone;
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x20) != 0 && x6 == 5) {
            m_command = kCmdB5A2AB;
            return;
        }
        if ((v5 & 0x10) != 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xe0) != 0 && x6 == 4) {
            break;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xe0) != 0 && x6 == 2) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 2) {
            x6 = 3;
        }
        if (v5 == 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xd0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x20) != 0 && x6 == 0 && m_gauge == 0xbb8 && m_stance == 1) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x69;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 4) {
            m_command = ((v5 & 0xe0) > 0) + kCmd641236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 3) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd641236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 4;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && m_gauge == 0xbb8 && m_stance == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            m_command = ((v5 & 0xe0) > 0) + kCmd214214A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd214214A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 6) {
            m_command = ((v5 & 0xe0) > 0) + kCmd236236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd236236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 6;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x78;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + kCmd623A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd623A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && m_stance == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + kCmd236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + kCmd412A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd412A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0 && m_stance == 1) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + kCmd214A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd214A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0xaf;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 8) != 0 && x6 == 1) {
            m_command = kCmdUp;
            return;
        }
        if ((v5 & 8) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x80) != 0 && x6 == 4) {
            m_command = kCmd22D;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0 && pattern == kWakeUp) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 4) {
            m_command = kCmd22C;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x20) != 0 && x6 == 4) {
            m_command = kCmd22B;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x10) != 0 && x6 == 4) {
            m_command = kCmd22A;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf) == 1 && x6 == 3) {
            m_command = kCmdDashRight;
            return;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x87;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf) == 2 && x6 == 3) {
            m_command = kCmdDashLeft;
            break;
        }
        if ((v5 & 0xf) == 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xf) == 2 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 0 && x6 == 0) {
            x6 = 1;
        }
    }
}

void CMio::CpuInput()
{
    double v10;
    double x8;

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
    v10 = ((*m_opponent)->x - x) * facing;
    x8 = fabs(y - (*m_opponent)->y);
    if (pattern >= kFirstHitReaction && pattern <= kFirstGuard && timer == 0) {
        if ((WORD)Random(0, 0x64) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        m_inputX = 1 - (((WORD)Random(0, 0x64) < 0x32) << 1);
        m_pressD = (WORD)Random(0, 0xf0) < x8;
        m_pressD = (WORD)Random(0, 0x140) < v10;
        if ((*m_opponent)->pattern > kLastSharedAction && (*m_opponent)->pattern < 0xfa && (*m_opponent)->frame < 3 && x8 < 100.0 && v10 < 150.0) {
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
            if (v10 < 40.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_stance == 0) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_stance == 0) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 > 40.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_stance == 0) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_stance == 0) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (v10 < 100.0) {
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_stance == 1 && m_gauge == 0xbb8) {
                m_command = kCmdB5A2AB;
                return;
            }
            if (v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_stance == 1 && m_gauge >= 0x7d0) {
                m_command = (WORD)Random(0, 2) + kCmd236236B;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0 && m_stance == 0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0 && m_stance == 1) {
                m_command = kCmd412C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0 && m_stance == 0) {
                m_command = kCmd214C;
                return;
            }
        }
        if (v10 < 160.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (v10 < 80.0 && v10 > 160.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_stance == 0 && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_stance == 1) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_stance == 1 && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
        }
        if (v10 > 160.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_stance == 1) {
            m_command = kCmd236A;
            return;
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (x8 < 50.0 && y > (*m_opponent)->y && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -30.0 && y - (*m_opponent)->y < 0.0 && v10 < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < 50.0 && x8 < 60.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
            m_command = kCmd623C;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0 && m_stance == 0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 7 && m_rfGauge > 500.0 && m_stance == 0) {
            m_command = (WORD)Random(0, 2) + kCmd623A;
            return;
        }
        if (m_cpuRoll < 0xa && m_rfGauge > 500.0 && m_stance == 1) {
            m_command = 0x48;
            return;
        }
        if (m_cpuRoll < 0xd && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x7d0) {
            m_command = (WORD)Random(0, 1) + kCmd236236B;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < (m_stance == 1) * 0x14 + 0x14) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == kJump2C || pattern == k623A || pattern == k623B || pattern == k623C || pattern == kStanceChange || pattern == k236B || pattern == k236BFollowupA)) {
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
    if (pattern == k236A && m_attackResult > 0 && (WORD)Random(0, 0x64) < 24.0f * m_cpuSkill) {
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
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 0x64) < m_cpuSkill * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 40.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x1e) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x1f4) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x226) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x230) {
                m_cpuAction = 0xc;
                return;
            }
            if (m_cpuRoll > 0x3d4) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x3c0) {
                m_inputY = -1;
                m_inputX = facing;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x1a4 && v10 < 100.0) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 80.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x15e && m_cpuRoll < 0x2bc) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x2bc && m_cpuRoll < 0x2ee) {
                m_cpuAction = 0x12;
                return;
            }
            if (m_cpuRoll > 0x3d4) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 0x64) < 0x14) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 0x64) < 0x28) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x2bc && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 0x1c2 && v10 < 110.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x225 && m_cpuRoll < 0x258) {
                m_command = ((WORD)Random(0, 3) == 0 && m_rfGauge > 500.0) * 2 + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x2bc) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x3d4) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 0x64) < 0x14) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 0x64) < 0x28) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == k5C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x113) {
                m_command = ((WORD)Random(0, 4) == 0 && m_rfGauge > 500.0) * 2 + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x226) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == k2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 40.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x1e) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x1f4) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x226) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x230) {
                m_cpuAction = 0xc;
                return;
            }
            if (m_cpuRoll > 0x2bc && m_cpuRoll < 0x2ee) {
                m_cpuAction = 0x12;
                return;
            }
            if (m_cpuRoll > 0x3d4) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x3c0) {
                m_inputY = -1;
                m_inputX = facing;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x64 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x64 && m_cpuRoll < 0x78) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x78 && m_cpuRoll < 0x8c && v10 < 100.0) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll < 0x28) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x28 && m_cpuRoll < 0x32 && v10 < 80.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x32 && m_cpuRoll < 0x3c) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x2bc && m_cpuRoll < 0x2ee) {
                m_cpuAction = 0x12;
                return;
            }
            if (m_cpuRoll > 0x3e3) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x3ca) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 0x64) < 0x14) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 0x64) < 0x28) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == k2C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 3) + kCmd623A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x28a) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                return;
            }
            if (v10 < 60.0 && m_cpuRoll < 0x1f4) {
                m_pressA = 1;
                return;
            }
            if (v10 < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
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
        if (pattern == kDashA) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xfa && v10 < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 0x38e) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 0x64) < 0x14) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 0x64) < 0x28) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == kDashB) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xfa && v10 < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x38e) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 0x64) < 0x14) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 0x64) < 0x28) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == kDash2C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x15e && v10 < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
        }
        if (pattern == kFloat5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 40.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x1e) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x1c2) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x3c0) {
                m_inputY = -1;
                m_inputX = facing;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                return;
            }
        }
        if (pattern == kFloat5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x32 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x1a4 && v10 < 100.0) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll < 0x64 && v10 < 90.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 120.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && v10 > 100.0) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x3de) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 0x64) < 0x14) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 0x64) < 0x28) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == kFloat5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x113) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x28a) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kFloat5C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 40.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x1e) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x1c2) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x3c0) {
                m_inputY = -1;
                m_inputX = facing;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                return;
            }
        }
        if (pattern == kFloat2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x32 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                m_inputY = 0;
                m_inputX = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x1a4 && v10 < 100.0) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x12;
                }
                return;
            }
            if (m_cpuRoll < 0x64 && v10 < 90.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 120.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && v10 > 100.0) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x3de) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if ((WORD)Random(0, 0x64) < 0x14) {
                        m_cpuAction = 8;
                    }
                    if ((WORD)Random(0, 0x64) < 0x28) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
            }
        }
        if (pattern == kFloat2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x113) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x28a) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                return;
            }
            if (v10 < 60.0 && m_cpuRoll < 0x1f4) {
                m_pressA = 1;
                return;
            }
            if (v10 < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
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
        if (pattern == kFloatDashB) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xfa && v10 < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x38e) {
                m_cpuAction = 1;
            }
        }
        if (pattern == kFloatDashC) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x113) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x28a) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kFloatDash2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xfa && v10 < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x38e) {
                m_cpuAction = 1;
            }
        }
        if (pattern == kFloatDash2C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x113) {
                m_command = 0x46;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 450.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x28a) {
                m_pressD = 1;
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
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown && m_stance == 0) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 45.0 && m_cpuRoll < 0x19) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 60.0 && m_cpuRoll < 0x23) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 80.0 && v10 > 40.0 && m_cpuRoll < 0x3c && m_cpuRoll > 0x23) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 100.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x3c) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 90.0 && v10 > 50.0 && m_cpuRoll > 0x50 && m_cpuRoll < 0x57) {
                    m_cpuAction = 6;
                    return;
                }
                if (v10 < 110.0 && v10 > 70.0 && m_cpuRoll > 0x57 && m_cpuRoll < 0x5f) {
                    m_cpuAction = 8;
                    if ((WORD)Random(0, 0x1e) < 0xf) {
                        m_cpuAction = 0xe;
                    }
                    return;
                }
                if (v10 > 120.0 && v10 < 190.0 && m_cpuRoll > 0x5f && m_cpuRoll < 0x62) {
                    m_cpuAction = 0x10;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && m_cpuRoll > 0x64 && m_cpuRoll < 0x67) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x78 && m_cpuRoll > 0x69) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 60.0 && m_cpuRoll < 0x7d && m_cpuRoll > 0x78 && (*m_opponent)->pattern > kLastSharedAction && m_rfGauge > 500.0) {
                    m_command = kCmd623C;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x82 && m_cpuRoll > 0x7d && (*m_opponent)->pattern > kLastSharedAction && m_gauge >= 0x3e8) {
                    m_command = (WORD)Random(0, 3) + kCmd236236A;
                    return;
                }
                if (m_cpuRoll < 0x87 && m_cpuRoll > 0x82) {
                    m_command = facing;
                    m_cpuAction = 5;
                    return;
                }
            }
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown && m_stance == 1) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 55.0 && m_cpuRoll < 0xa) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 70.0 && m_cpuRoll < 0xf) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 150.0 && v10 > 80.0 && m_cpuRoll < 0x3c && m_cpuRoll > 0x23) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 180.0 && v10 > 100.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x3c && (*m_opponent)->m_inputY != 1) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 100.0 && v10 > 0.0 && m_cpuRoll < 0x5f && m_cpuRoll > 0x50) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 120.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x5f) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 80.0 && v10 < 130.0 && m_cpuRoll > 0x6e && m_cpuRoll < 0x73) {
                    m_cpuAction = 0x10;
                    return;
                }
                if (v10 > 100.0 && v10 < 180.0 && m_cpuRoll > 0x73 && m_cpuRoll < 0x7d) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 < 60.0 && m_cpuRoll < 0x82 && m_cpuRoll > 0x7d && (*m_opponent)->pattern > kLastSharedAction && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x85 && m_cpuRoll > 0x82 && (*m_opponent)->pattern > kLastSharedAction && m_gauge == 0xbb8) {
                    m_command = kCmdB5A2AB;
                    return;
                }
                if (v10 > 100.0 && m_cpuRoll < v10 * 0.1 + 140.0 && m_cpuRoll > 0x87) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (v10 > 120.0 && m_cpuRoll < 0xc8 && m_cpuRoll > 0xc1) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (v10 > 80.0 && m_cpuRoll < 0xd0 && m_cpuRoll > 0xc8) {
                    m_command = (WORD)Random(0, 3) + kCmd412A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0 && m_stance == 0) {
                if ((*m_opponent)->vy < 0.0 && v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                    m_inputY = -1;
                    m_inputX = -facing;
                    return;
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 60.0 && x8 < 120.0) {
                        if (m_cpuRoll < (m_rfGauge > 500.0 || m_rfBlue > 0) * 5 + 6) {
                            m_command = ((WORD)Random(0, 3) == 0) * 2 + kCmd623A;
                            return;
                        }
                    }
                    if (v10 < 60.0 && x8 < 120.0 && x8 > 80.0 && m_cpuRoll < 0xf) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 150.0 && x8 > 100.0 && m_cpuRoll < 0x1e) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                }
            }
            if ((*m_opponent)->y < 0.0 && m_stance == 1) {
                if ((*m_opponent)->vy < 0.0) {
                    if (v10 < 100.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 100.0 && x8 < 120.0 && m_cpuRoll < 0xf && x > 80.0 && x < 560.0) {
                        m_command = facing == -1;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 110.0 && x8 < 210.0 && m_cpuRoll < 0xa) {
                        m_command = (WORD)Random(0, 3) + kCmd214214A;
                        return;
                    }
                    if (v10 < 100.0 && x8 < 120.0 && m_cpuRoll < 4) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 100.0 && v10 < 180.0 && x8 < 140.0 && m_cpuRoll < 0x14) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 100.0 && x8 < 140.0 && x8 > 80.0 && m_cpuRoll < 0x28) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3 && m_stance == 0) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 60.0 && x8 < 70.0 && m_cpuRoll < 0x64) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 50.0 && x8 < 90.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x104) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 70.0 && x8 > 60.0 && x8 < 110.0 && m_cpuRoll > 0x104 && m_cpuRoll < 0x11d) {
                    m_pressC = 1;
                    return;
                }
                if (x8 + 30.0 > v10 && x8 - 30.0 < v10 && x8 < 110.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x136) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 80.0 && y > (*m_opponent)->y && m_cpuRoll < 0x136) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 90.0 && x8 < 100.0 && y < (*m_opponent)->y && m_cpuRoll > 0x136 && m_cpuRoll < 0x190) {
                    m_pressB = 1;
                    return;
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3 && m_stance == 1) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 60.0 && x8 < 70.0 && m_cpuRoll < 0x64) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 160.0 && v10 > 110.0 && x8 > 20.0 && x8 < 50.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x104) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 90.0 && x8 < 150.0 && m_cpuRoll > 0x104) {
                    if (m_cpuRoll < (x8 > 100.0) * 0x28 + 0x122) {
                        m_pressC = 1;
                        return;
                    }
                }
                if (v10 < 130.0 && v10 > 80.0 && x8 < 80.0 && m_cpuRoll > 0x17c && m_cpuRoll < 0x190) {
                    m_command = (WORD)Random(0, 3) + kCmd412A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && v10 > 60.0 && x8 < 60.0 && y > (*m_opponent)->y && m_cpuRoll < 0xd2) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 180.0 && v10 > 100.0 && x8 < 70.0 && y > (*m_opponent)->y && m_cpuRoll < 0x136) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 90.0 && x8 > 100.0 && x8 < 150.0 && y < (*m_opponent)->y && m_cpuRoll > 0x136 && m_cpuRoll < 0x1c2) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 140.0 && v10 > 80.0 && x8 < 80.0 && m_cpuRoll > 0x17c && m_cpuRoll < 0x190) {
                    m_command = (WORD)Random(0, 3) + kCmd412A;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < (m_stance == 0) * 3 * m_cpuSkill + 1.0f) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir || (*m_opponent)->pattern < kFirstHitReaction) && y == 0.0 && v10 < 90.0 && (WORD)Random(0, 0x64) < ((m_stance == 1) << 2) * m_cpuSkill) {
        m_command = facing == -1;
        return;
    }
    if ((WORD)Random(0, 0x3e8) < (m_stance == 0) + 1) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 0x64) < 2) {
        if ((WORD)Random(0, 0x64) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (v10 > 160.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 100.0 && y == 0.0 && (WORD)Random(0, 0x64) < 1 && (*m_opponent)->pattern < kFirstHitReaction) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 170.0 && v10 > 120.0 && y == 0.0) {
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
    if ((WORD)Random(0, 0x64) < (m_stance == 1) * 0x1e + 0x28 && v10 < 110.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x1e;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)Random(0, 0x64) < (m_stance == 0) * 0x1e + 0x28) {
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

void CMio::UpdateObjects()
{
    WORD v58;
    WORD v54;
    int v4;

    if ((*m_opponent)->m_freezeTime > 0) {
        return;
    }
    v4 = m_objectTail;
    EffectDesc l50;
    while (v4 != m_objectHead) {
        if (m_objectActive[v4] != 0 && m_objects[v4].hitstop == 0 && (m_freezeTime == 0 || m_freezeTime > 0 && m_objects[v4].movesInFreeze != 0)) {
            v54 = (short)anims[m_objects[v4].pattern].frames[m_objects[v4].frame].duration;
            v58 = anims[m_objects[v4].pattern].frameCount;
            InitEffectDesc((EffectDesc*)&l50);
            switch (m_objects[v4].pattern) {
            case kObjUnusedHopper:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 0.5;
                    m_objects[v4].vy = -2.8;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0 || m_objects[v4].attackResult > 1) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].vy = -1.5;
                    l50.type = 0x191;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x192;
                    SpawnObject(&l50);
                    l50.type = 0x193;
                    SpawnObject(&l50);
                    m_playVoice = 2;
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnusedHopperPiece1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.0 - (rand() < 0x3e80) * 0.5 - (rand() < 0x3e80) * 1.0;
                    m_objects[v4].vy = -1.5;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnusedHopperPiece2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (rand() < 0x3e80) * 0.5 + 1.0 + (rand() < 0x3e80) * 1.0;
                    m_objects[v4].vy = -1.1;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnusedHopperPiece3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (rand() < 0x3e80) * 0.5 - (rand() < 0x3e80) * 1.0;
                    m_objects[v4].vy = -1.3;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFloat412Throw:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vy = (WORD)Random(0, 0xa) * 0.1 + 1.5;
                    m_objects[v4].vx = 2.1 - (WORD)Random(0, 5) * 0.1;
                }
                m_objects[v4].vx -= 0.02;
                if (m_objects[v4].vx < 0.1) {
                    m_objects[v4].vx = 0.1;
                }
                m_objects[v4].vy -= 0.02;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFloat236Shot:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 6.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 1) {
                    m_objects[v4].vy += 0.04;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].attackResult == 3 && m_objects[v4].frame == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    m_playVoice = 5;
                    (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 0x3c;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                if (m_objects[v4].attackResult > 1) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -2.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y > 30.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloat236CShot:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 6.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 0 && (m_objects[v4].x < -960.0 || m_objects[v4].x > 1640.0)) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].x = -m_objects[v4].x;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vy += 0.04;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].attackResult == 3 && m_objects[v4].frame <= 1) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 3;
                    m_objects[v4].timer = 0;
                    m_playVoice = 5;
                    (*m_opponent)->m_hitstop = (*m_opponent)->m_hitstop + 0x3c;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                if (m_objects[v4].attackResult > 1) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -2.0;
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].frame > 0 && (m_objects[v4].x < -2000.0 || m_objects[v4].x > 2000.0 || m_objects[v4].y > 30.0)) {
                    RemoveObject(v4);
                }
                break;
            case kObj236FollowupStrike:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj236FollowupRiser:
                m_objects[v4].vx -= 0.05;
                m_objects[v4].vy -= 0.02;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y > 0.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloat214ColumnBase:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFloat214Column:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    if (m_objects[v4].y < -190.0) {
                        l50.type = 0x19a;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)((int)m_objects[v4].y + 0xa0);
                        l50.facing = facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.keep = 1;
                        SpawnObject(&l50);
                    } else {
                        l50.type = 0x199;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = 0.0;
                        l50.facing = facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.keep = 1;
                        SpawnObject(&l50);
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjSuperDrop:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                m_objects[v4].vy += 0.045;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjSuperDropBounce:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                m_objects[v4].vy += 0.035;
                if ((m_objects[v4].attackResult > 1 || m_objects[v4].y > 0.0) && m_objectVar1[v4] == 0) {
                    m_playVoice = 7;
                    m_objects[v4].hitsLeft = 0;
                    m_objectVar1[v4]++;
                    m_objects[v4].vy = -1.5;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjSuperDropBreak:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                m_objects[v4].vy += 0.04;
                if ((m_objects[v4].attackResult > 1 || m_objects[v4].y > 0.0) && m_objects[v4].frame == 0) {
                    m_playSound = 1;
                    m_objects[v4].hitsLeft = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].vy = -1.5;
                    l50.type = 0x19e;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y - 0xf);
                    l50.facing = facing;
                    l50.scale = 0;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    l50.type = 0x19f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y + 0xf);
                    l50.facing = facing;
                    l50.scale = 0;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    l50.type = 0x1a0;
                    l50.x = (double)((int)m_objects[v4].x + 0xf);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = facing;
                    l50.scale = 0;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    l50.type = 0x1a1;
                    l50.x = (double)((int)m_objects[v4].x - 0xf);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = facing;
                    l50.scale = 0;
                    l50.layer = 1;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjSuperDropPiece1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = (WORD)Random(0, 0xa) * 0.1 + -1.0;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 0.5;
                }
                m_objects[v4].vy += 0.04;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjSuperDropPiece2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = (WORD)Random(0, 0xa) * 0.1 + -1.3;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 0.9;
                }
                m_objects[v4].vy += 0.04;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjSuperDropPiece3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = (WORD)Random(0, 0xa) * 0.1 + -1.0;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + -0.5;
                }
                m_objects[v4].vy += 0.04;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjSuperDropPiece4:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = (WORD)Random(0, 0xa) * 0.1 + -0.8;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + -0.9;
                }
                m_objects[v4].vy += 0.04;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloatSuperShotA:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 7;
                    m_objects[v4].vx = 1.0;
                    m_objectVar1[v4]++;
                }
                m_objects[v4].vx += 0.02;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 5 || m_objects[v4].frame == 8 || m_objects[v4].frame == 0xb || m_objects[v4].frame == 0xe || m_objects[v4].frame == 0x11 || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x17) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y > 0.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloatSuperShotTrail:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnusedShotSlow:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 2.3;
                    m_objectVar1[v4]++;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].x < -420.0 || m_objects[v4].x > 1060.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjUnusedShotMid:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 2.6;
                    m_objectVar1[v4]++;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].x < -420.0 || m_objects[v4].x > 1060.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloat214Summoner:
                if (m_objects[v4].frame == 3 && m_objects[v4].timer == 0x1e && m_objects[v4].y == 0.0) {
                    l50.type = 0x19a;
                    l50.x = (double)((int)m_objects[v4].x - m_objects[v4].facing * 0xf);
                    l50.y = -556.0;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    m_playVoice = 6;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame == 3 && m_objects[v4].timer == 0x27 && m_objects[v4].y == 0.0) {
                    l50.type = 0x19a;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 6);
                    l50.y = -564.0;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    m_playVoice = 6;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame == 3 && m_objects[v4].timer == 0x30 && m_objects[v4].y == 0.0) {
                    l50.type = 0x19a;
                    l50.x = (double)((int)m_objects[v4].x - m_objects[v4].facing * 0x24);
                    l50.y = -560.0;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    m_playVoice = 6;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnusedShotFast:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 3.0;
                    m_objectVar1[v4]++;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].x < -420.0 || m_objects[v4].x > 1060.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloatSuperShotB:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 7;
                    m_objects[v4].vx = 1.0;
                    m_objectVar1[v4]++;
                }
                if (m_objectVar2[v4] < 0) {
                    l50.type = 0x1a3;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x28);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectVar2[v4] = 0x12;
                }
                m_objectVar2[v4]--;
                m_objects[v4].vx += 0.03;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 5 || m_objects[v4].frame == 8 || m_objects[v4].frame == 0xb || m_objects[v4].frame == 0xe || m_objects[v4].frame == 0x11 || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x17) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y > 0.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloatSuperShotC:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 7;
                    m_objects[v4].vx = 1.0;
                    m_objectVar1[v4]++;
                }
                l50.type = 0x24;
                l50.x = (double)((int)m_objects[v4].x + 0x28 - (WORD)Random(0, 0x50));
                l50.y = (double)((int)m_objects[v4].y + 0x28 - (WORD)Random(0, 0x50));
                l50.scale = 2;
                l50.layer = 1;
                m_game->CreateEffect((EffectDesc*)&l50);
                if (m_objectVar2[v4] < 0) {
                    l50.type = 0x1a3;
                    l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x28);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectVar2[v4] = 6;
                    if (m_objects[v4].y > -80.0 && m_objectVar3[v4] < 0) {
                        l50.type = 0x1f;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = 0.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.side = m_objects[v4].facing == -1;
                        m_game->CreateEffect((EffectDesc*)&l50);
                        m_objectVar3[v4] = 3;
                    }
                    m_objectVar3[v4]--;
                }
                m_objectVar2[v4]--;
                m_objects[v4].vx += 0.04;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 5 || m_objects[v4].frame == 8 || m_objects[v4].frame == 0xb || m_objects[v4].frame == 0xe || m_objects[v4].frame == 0x11 || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x17) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y > 0.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloat214214Shot:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 6.0;
                    m_objects[v4].vy = -4.5;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y < -640.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloatLv4Far1:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far2:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far3:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far4:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far5:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Far6:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar2 == 1.0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjFloatLv4FarRise;
                }
                break;
            case kObjFloatLv4FarRise:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -15.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y < -640.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloatLv4Near1:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near2:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near3:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near4:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near5:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kThrownHidden;
                }
                break;
            case kObjFloatLv4Near6:
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_playVoice = 0xa;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        l50.type = 0x1bb;
                        l50.x = (double)(int)(*m_opponent)->x;
                        l50.y = 0.0;
                        l50.facing = facing;
                        l50.layer = 1;
                        l50.scale = 2;
                        SpawnObject(&l50);
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = kObjFloatLv4NearRise;
                        m_objects[v4].vy = -15.0;
                        m_patternVar2 = 1.0;
                        m_playVoice = 8;
                    }
                }
                break;
            case kObjFloatLv4NearRise:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y < -640.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloatLv4Floor:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_patternVar3 == 1.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjFloatLv4Lift:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].y < -640.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjThrowHold:
                m_objects[v4].frame = 0;
                if (frame == 4) {
                    m_objects[v4].frame = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (pattern != kThrowHold || frame > 4) {
                    RemoveObject(v4);
                }
                break;
            case kObjLv4Finish236C:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 2;
                }
                if (pattern != kLv4Finish236C || pattern == kLv4Finish236C && frame > 5) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case kObjFloat412CThrow:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vy = m_patternVar3;
                    m_objects[v4].vx = 2.8 - m_patternVar3 / 2.0;
                }
                m_objects[v4].vx -= 0.02;
                if (m_objects[v4].vx < 0.1) {
                    m_objects[v4].vx = 0.1;
                }
                m_objects[v4].vy -= 0.02;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj623CAura:
                m_objects[v4].x = x;
                m_objects[v4].y = y - 50.0;
                if (pattern != k623C || pattern == k623C && frame > 5) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 7;
                    }
                }
                break;
            case kObj214214Strike:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214214CHit:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj236CWallA:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj236CWallB:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjAirThrowImpact1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = 0.5;
                    m_objects[v4].vy = -1.8;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case kObjAirThrowImpact2:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjAirThrowImpact3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = 0.4;
                    m_objects[v4].vy = -1.7;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 100.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case kObjFloat214Marker:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = 0x1a6;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = -3.0;
                    l50.facing = facing;
                    l50.layer = 0;
                    l50.scale = 0;
                    l50.keep = 1;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    l50.type = 0x1a6;
                    l50.x = (double)((int)m_objects[v4].x + facing * 0x1b);
                    l50.y = 0.0;
                    l50.facing = facing;
                    l50.layer = 0;
                    l50.scale = 0;
                    l50.keep = 1;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1a6;
                    l50.x = (double)((int)m_objects[v4].x + facing * 9);
                    l50.y = 4.0;
                    l50.facing = facing;
                    l50.layer = 0;
                    l50.scale = 0;
                    l50.keep = 1;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj236FollowupBSpark:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj236FollowupBShot:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objectVar1[v4] = 0;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    l50.type = 0x1c7;
                    l50.x = (double)((int)m_objects[v4].x + 0x1e - (WORD)Random(0, 0x50));
                    l50.y = (double)((int)m_objects[v4].y + 0x14 - (WORD)Random(0, 0x28));
                    l50.facing = facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                    m_playSound = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar1[v4] < 6) {
                            m_objectVar1[v4]++;
                            m_objects[v4].frame = 1;
                            m_objects[v4].hitsLeft = 1;
                            m_objects[v4].attackResult = 0;
                            break;
                        }
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFallInDarkness:
                m_objects[v4].vx = -0.02;
                m_objects[v4].drawnWhileHidden = 0x7530;
                m_objects[v4].timer++;
                if (pattern != kFallInDarkness) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case kObjEncasedBreak:
                if (pattern != kEncased && pattern != kEncased2 && pattern != kEncasedAir && pattern != kEncasedSpin || pattern == kEncased && frame > 1 || pattern == kEncased2 && frame > 1) {
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x + facing * 0x17);
                    l50.y = (double)((int)y - 4);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - (facing << 2));
                    l50.y = (double)((int)y - 6);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0xe);
                    l50.y = (double)((int)y - 0x1a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x + facing * 0x1e);
                    l50.y = (double)((int)y - 0x28);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f1;
                    l50.x = (double)((int)x - facing * 0x19);
                    l50.y = (double)((int)y - 0x50);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x23);
                    l50.y = (double)((int)y - 0x2a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x - facing * 0x12);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + facing * 2);
                    l50.y = (double)((int)y - 0x41);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1f2;
                    l50.x = (double)((int)x + (facing << 4));
                    l50.y = (double)((int)y - 0x50);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    m_playSound = 0x22;
                    RemoveObject(v4);
                    m_encasedBreakOut = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case kObjShardSmall:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objectVar2[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (m_objectVar2[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (m_objectVar2[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                m_objectVar2[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case kObjShardLarge:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objectVar2[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (m_objectVar2[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (m_objectVar2[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                m_objectVar2[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case kObjBurnFlames:
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
            }
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}
