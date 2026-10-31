// CNayukiB (0x73e790-0x750d2f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNayukiB::CNayukiB(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "nayukiB");
    lastSurface = 0x281;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_orbitAngle = 0;
    m_orbitLevel = 0;
    m_orbitTime = 0;
    m_orbitDirection = 0;
    m_pointX[0] = -5;
    m_pointY[0] = -0x3d;
    m_pointX[1] = 8;
    m_pointY[1] = 0;
    m_pointX[2] = 0x11;
    m_pointY[2] = -0xf;
    m_pointX[3] = 0x13;
    m_pointY[3] = -0xb;
    m_pointX[4] = 0x16;
    m_pointY[4] = -0x1e;
    m_resultPictures = 7;
    m_rivals[0] = 0x11;
    m_rivals[1] = 1;
    m_rivals[2] = 0xd;
    m_rivals[3] = 0x10;
    m_rivals[4] = 0xa;
    m_rivals[5] = 3;
    m_rivals[6] = 6;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
}

void CNayukiB::Reset()
{
    int v4;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_orbitAngle = 0;
    m_orbitLevel = 0;
    m_orbitTime = 0;
    m_orbitDirection = 0;
    m_pointX[0] = -5;
    m_pointY[0] = -0x3d;
    m_pointX[1] = 8;
    m_pointY[1] = 0;
    m_pointX[2] = 0x11;
    m_pointY[2] = -0xf;
    m_pointX[3] = 0x13;
    m_pointY[3] = -0xb;
    m_pointX[4] = 0x16;
    m_pointY[4] = -0x1e;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
    CPlayer::Reset();
}

void CNayukiB::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CNayukiB::RemoveObject(short p1)
{
    m_objectVar1[p1] = 0;
    m_objectVar2[p1] = 0;
    m_objectVar3[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CNayukiB::Move()
{
    MoveOnGround();
}

void CNayukiB::StartCommand()
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
        if (m_hp < 0xd05 && m_command == kCmd236236D && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd641236C && m_gauge >= 0xbb8 && m_orbitTime <= 0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236C;
            return;
        }
        if ((m_command == kCmd641236B || m_command == kCmd641236C) && m_gauge >= 0x7d0 && m_orbitTime <= 0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236B;
            return;
        }
        if ((m_command == kCmd641236A || m_command == kCmd641236B || m_command == kCmd641236C) && m_gauge >= 0x3e8 && m_orbitTime <= 0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236A;
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
        if (m_command == kCmd214214C && m_gauge >= 0xbb8 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir214214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir214214C;
            return;
        }
        if ((m_command == kCmd214214B || m_command == kCmd214214C) && y < 0.0 && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir214214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir214214B;
            return;
        }
        if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && y < 0.0 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir214214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir214214A;
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
        if (m_command == kCmd412C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412C;
            if (y < 0.0) {
                frame = 2;
            }
            return;
        }
        if ((m_command == kCmd412B || m_command == kCmd412C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k412B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412B;
            if (y < 0.0) {
                frame = 2;
            }
            return;
        }
        if ((m_command == kCmd412A || m_command == kCmd412B || m_command == kCmd412C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k412A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412A;
            if (y < 0.0) {
                frame = 2;
            }
            return;
        }
        if (m_command == kCmd214C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            if (y < 0.0) {
                pattern = kAir214C;
            }
            return;
        }
        if ((m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            if (y < 0.0) {
                pattern = kAir214B;
            }
            return;
        }
        if ((m_command == kCmd214A || m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            if (y < 0.0) {
                pattern = kAir214A;
            }
            return;
        }
        if (m_command == kCmd236C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            return;
        }
        if (m_command == kCmd236B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236B].level) {
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
            if (m_patterns[pattern].cancelLevel <= m_patterns[k5C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k5C;
            }
        }
    }
}

void CNayukiB::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (m_orbitLevel > 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_orbitLevel > 0) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, m_orbitTime * x1c.width / 0xbb8, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, m_orbitTime * x1c.width / 0xbb8, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - m_orbitTime * x1c.width / 0xbb8, 0x1f - x1c.y, m_orbitTime * x1c.width / 0xbb8, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CNayukiB::PreUpdate()
{
    if (m_orbitTime <= 0 || m_hp <= 0 || (*m_opponent)->m_hp <= 0 || pattern > kLastFreeAction && pattern < kFirstGuard) {
        m_orbitTime = 0;
        m_orbitLevel = 0;
    }
    if (m_orbitTime > 0) {
        m_orbitAngle += m_orbitDirection;
        if (m_orbitAngle > 0x167) {
            m_orbitAngle -= 0x168;
        }
        m_orbitTime -= 2;
        if (m_orbitTime <= 0) {
            m_orbitTime = 0;
            m_orbitLevel = 0;
        }
    }
}

void CNayukiB::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CNayukiB::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = kCmdNone;
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && m_gauge >= 0x3e8) {
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0) {
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
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0) {
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
    v4 = m_inputPos + 0x78;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 3) {
            m_command = kCmd263C;
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0x40) != 0) {
                m_command = kCmd263C;
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge == 0xbb8) {
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

void CNayukiB::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == kAir214C && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 45.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 60.0 && v10 < 70.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
            m_pressB = 1;
            m_inputY = 1;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f && m_rfGauge > 500.0) {
                m_command = kCmd623A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd623C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd236236A;
                return;
            }
        }
        if (v10 < 150.0 && v10 > 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if (v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_gauge >= 0x7d0) {
                m_command = (WORD)Random(0, 2) + kCmd214214B;
                return;
            }
        }
        if (v10 > 150.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if (y - (*m_opponent)->y < -20.0 && y - (*m_opponent)->y > -80.0 && v10 < 150.0 && (WORD)Random(0, 0xc8) < m_cpuSkill * 5.0f && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 3) + kCmd214214A;
            return;
        }
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > 0.0 && y - (*m_opponent)->y < 50.0 && v10 < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < 90.0 && y - (*m_opponent)->y > 20.0 && v10 < 110.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0 && v10 < 80.0) {
            m_command = kCmd623A;
            return;
        }
        if (m_cpuRoll < 5 && m_rfGauge > 500.0 && v10 < 80.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 0xa && m_cpuRoll > 5 && m_rfGauge > 500.0 && v10 < 100.0) {
            m_command = kCmd412C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && v10 < 100.0) {
            m_command = (WORD)Random(0, 3) + kCmd641236A;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && v10 > 90.0) {
            m_command = (WORD)Random(0, 3) + kCmd214214A;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && v10 > 50.0) {
            m_command = (WORD)Random(0, 3) + kCmd214214A;
            return;
        }
        if (m_cpuRoll > 0x3c) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k412A || pattern == kDashC && (WORD)Random(0, 0xa) == 0 || pattern == k412B || pattern == 0xee)) {
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
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 0x64) < m_cpuSkill * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 45.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressA = 1;
                m_inputY = Random(0, 2);
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 70.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
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
            if (m_cpuRoll > 0x258) {
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
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0xa && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x190) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x190 && m_cpuRoll < 0x1c2 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 150.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && v10 < 70.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 0x3d4) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
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
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x96 && m_cpuRoll < 0xc8 && m_gauge >= 0x3e8 && v10 < 120.0) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x190) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x226) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x2bc) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
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
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x1c2) {
                m_command = ((WORD)Random(0, 2) == 0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && m_gauge >= 0x3e8) {
                m_command = kCmd641236A;
                return;
            }
            if (m_cpuRoll > 0x384) {
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
            if (v10 < 45.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressA = 1;
                m_inputY = Random(0, 2);
                return;
            }
            if (v10 < 90.0 && m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 100.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
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
            if (m_cpuRoll > 0x258) {
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
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x226) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x64) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0xc8) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && v10 < 140.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && v10 < 70.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 0x3d4) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
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
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x15e) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x28a && m_cpuRoll < 0x29e && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd641236A;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                return;
            }
            if (v10 < 60.0 && m_cpuRoll < 0x190) {
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
            if (m_cpuRoll > 0 && m_cpuRoll < 0x15e) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1f4) {
                m_command = kCmd412A;
                return;
            }
            if (m_cpuRoll > 0x190) {
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
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == kDash2B) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x15e) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1f4) {
                m_command = kCmd412A;
                return;
            }
            if (m_cpuRoll > 0x190) {
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
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == kDash2C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xd2 && m_rfGauge > 350.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x15e) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
            }
        }
        if (pattern == kDash2A && m_cpuRoll > 0x1f4) {
            m_cpuAction = 1;
            if (v10 < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
    }
    if ((WORD)Random(0, 0x64) < 25.0f * m_cpuSkill) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 60.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 45.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 > 50.0 && v10 < 80.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x41 && m_cpuRoll > 0x28) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x46 < v10 && v10 < 95.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x14 + 0x50 && m_cpuRoll > 0x46) {
                        m_cpuAction = 0xc;
                        return;
                    }
                }
                if (0x50 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x46 < v10 && v10 < 110.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x80 && m_cpuRoll > 0x78) {
                        m_cpuAction = 8;
                        return;
                    }
                }
                if (v10 < 180.0 && v10 > 200.0 && m_cpuRoll < 0xfa && m_cpuRoll > 0x96) {
                    m_cpuAction = 0x10;
                    return;
                }
                if (v10 < 130.0 && v10 > 100.0 && m_cpuRoll < 0xc3 && m_cpuRoll > 0xaa) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (0x50 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x50 < v10 && v10 < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x19 + 0xb9 && m_cpuRoll > 0xaa) {
                        m_cpuAction = 0xe;
                        return;
                    }
                }
                if (0x5a - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x5a < v10 && v10 < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x19 + 0xe1 && m_cpuRoll > 0xd2) {
                        m_cpuAction = 0xa;
                        return;
                    }
                }
                if (v10 > 130.0 && v10 < 170.0 && m_cpuRoll < 0x104 && m_cpuRoll > 0xfa) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x113 && m_cpuRoll > 0x104 && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd623C;
                    return;
                }
                if (v10 < 150.0 && m_cpuRoll < 0x118 && m_cpuRoll > 0x113 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 2) + kCmd236236B;
                    return;
                }
                if (v10 > 150.0 && m_cpuRoll < 0x11d && m_cpuRoll > 0x118 && m_gauge >= 0xbb8) {
                    m_command = kCmd236236D;
                    return;
                }
                if (v10 > 160.0 && m_cpuRoll < 0x136 && m_cpuRoll > 0x12c) {
                    m_command = kCmd412A;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && m_cpuRoll < 0x140 && m_cpuRoll > 0x136) {
                    m_command = kCmd412B;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && m_cpuRoll < 0x145 && m_cpuRoll > 0x140) {
                    m_command = kCmd412C;
                    return;
                }
                if (v10 > 100.0 && v10 < 160.0 && m_cpuRoll < 0x154 && m_cpuRoll > 0x14a) {
                    m_command = kCmd236A;
                    return;
                }
                if (v10 > 160.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x154) {
                    m_command = kCmd236B;
                    return;
                }
                if (v10 > 40.0 && v10 < 120.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x154) {
                    m_command = kCmd214A;
                    return;
                }
                if (v10 > 140.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x154) {
                    m_command = kCmd214B;
                    return;
                }
                if (m_cpuRoll < 0x320 && m_cpuRoll > 0x2bc && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir && v10 > 100.0) {
                    m_cpuAction = 5;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0) {
                    if (v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623B;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623C;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && m_cpuRoll < 0xf) {
                        m_command = kCmd623B;
                        return;
                    }
                    if (v10 < 160.0 && v10 > 80.0 && x8 < 300.0 && x8 > 160.0 && m_cpuRoll < 0x28 && m_cpuRoll > 0x1e) {
                        m_command = kCmd236C;
                        return;
                    }
                    if (v10 < 150.0 && m_cpuRoll < 0xdc && m_cpuRoll > 0xc8 && (*m_opponent)->y < -50.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + kCmd236236A;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x64) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 100.0 && x8 > 60.0 && x8 < 120.0 && m_cpuRoll > 0xb4 && m_cpuRoll < 0xf0) {
                    m_pressC = 1;
                    return;
                }
                if (m_cpuRoll > 0xf0 && m_cpuRoll < 0xfa) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                    return;
                }
                if (m_cpuRoll > 0xfa && m_cpuRoll < 0x104) {
                    m_command = kCmd412A;
                    return;
                }
                if (v10 > 150.0 && m_cpuRoll > 0x104 && m_cpuRoll < 0x109 && x8 > 150.0) {
                    m_command = (WORD)Random(0, 3) + kCmd214214A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 100.0 && x8 > 0.0 && x8 < 90.0 && (*m_opponent)->y < y && m_cpuRoll > 0x14 && m_cpuRoll < 0x3c) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 50.0 && v10 < 130.0 && x8 > 0.0 && x8 < 90.0 && (*m_opponent)->y < y && m_cpuRoll > 0x3c && m_cpuRoll < 0x64) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 5.0f * m_cpuSkill && v10 > 120.0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && v10 > 800.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < 3.0f * m_cpuSkill && x > 150.0 && x < 490.0) {
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
        if (v10 > 180.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 170.0 && v10 > 140.0 && y == 0.0 && (*m_opponent)->pattern < kFirstHitReaction) {
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
    if ((WORD)Random(0, 0x64) < 0x32 && v10 < 120.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x3c;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x32) {
        if (facing == 1) {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x3c;
        } else {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x3c;
        }
        return;
    }
    if (facing == -1) {
        m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x3c;
        return;
    }
    m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x3c;
}

void CNayukiB::UpdateObjects()
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
            case kObj236236A:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 1.2;
                    m_objects[v4].vy = -2.1;
                    m_objects[v4].hitsLeft = 3;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].y < -600.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 0xa) {
                        m_objects[v4].attackResult = 0;
                    }
                }
                break;
            case kObj236236B:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 1.2;
                    m_objects[v4].vy = -2.1;
                    m_objects[v4].hitsLeft = 6;
                    m_objectVar1[v4]++;
                    m_objectVar2[v4] = 0;
                }
                m_objectVar2[v4]++;
                if (m_objectVar2[v4] > 0xa) {
                    m_objectVar2[v4] = 0;
                    l50.type = kObj236236Spark;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].y < -600.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 5 || m_objects[v4].frame == 0xa || m_objects[v4].frame == 0xf) {
                        m_objects[v4].attackResult = 0;
                    }
                }
                break;
            case kObj236236C:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 1.2;
                    m_objects[v4].vy = -2.1;
                    m_objects[v4].hitsLeft = 0xf;
                    m_objectVar1[v4]++;
                    m_objectVar2[v4] = 0;
                }
                m_objectVar2[v4]++;
                if (m_objectVar2[v4] > 3) {
                    m_objectVar2[v4] = 0;
                    l50.type = kObj236236Spark;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].y < -600.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame == 0 || m_objects[v4].frame == 4 || m_objects[v4].frame == 8 || m_objects[v4].frame == 0xc || m_objects[v4].frame == 0x10) {
                        m_objects[v4].attackResult = 0;
                    }
                }
                break;
            case kObj236236Spark:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 1.0;
                    m_objects[v4].vy = -2.2;
                    m_objects[v4].hitsLeft = 0;
                    m_objectVar1[v4]++;
#ifdef EFZ_NATIVE
                    // The original computes the arguments right to left, so the speed draws first.
                    {
                        double speed = (double)((WORD)Random(0, 3) + 2);
                        m_objects[v4].SetVelocity((double)(WORD)Random(0, 0x168), speed);
                    }
#else
                    m_objects[v4].SetVelocity((double)(WORD)Random(0, 0x168), (double)((WORD)Random(0, 3) + 2));
#endif
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjSatellite:
                if (m_orbitTime <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].facing = facing;
                m_objects[v4].SetVelocity((double)m_orbitAngle, 50.0);
                m_objects[v4].x = m_objects[v4].vx * m_orbitDirection + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                }
                if (m_objects[v4].frame == 1 && m_objects[v4].hitsLeft == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].pattern = kObjSatelliteSpent;
                    m_objects[v4].scale = 2;
                    m_orbitTime -= 0x3e8 - m_orbitLevel * 0x15e;
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
            case kObjSatelliteOpposite:
                if (m_orbitTime <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].facing = facing;
                m_objects[v4].SetVelocity((double)(m_orbitAngle + 0xb4), 50.0);
                m_objects[v4].x = m_objects[v4].vx * m_orbitDirection + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                }
                if (m_objects[v4].frame == 1 && m_objects[v4].hitsLeft == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].pattern = kObjSatelliteOppositeSpent;
                    m_objects[v4].scale = 2;
                    m_orbitTime -= 0x3e8 - m_orbitLevel * 0x15e;
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
            case kObjSatelliteSpent:
                if (m_orbitTime <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].facing = facing;
                m_objects[v4].SetVelocity((double)m_orbitAngle, 50.0);
                m_objects[v4].x = m_objects[v4].vx * m_orbitDirection + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = kObjSatelliteForming;
                        m_objects[v4].scale = 2;
                    }
                }
                break;
            case kObjSatelliteOppositeSpent:
                if (m_orbitTime <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].facing = facing;
                m_objects[v4].SetVelocity((double)(m_orbitAngle + 0xb4), 50.0);
                m_objects[v4].x = m_objects[v4].vx * m_orbitDirection + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = kObjSatelliteOppositeForming;
                        m_objects[v4].scale = 2;
                    }
                }
                break;
            case kObjSatelliteForming:
                if (m_orbitTime <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].SetVelocity((double)m_orbitAngle, 50.0);
                m_objects[v4].x = m_objects[v4].vx * m_orbitDirection + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = kObjSatellite;
                        m_objects[v4].scale = 0;
                        m_objects[v4].facing = facing;
                        l50.type = kObjSatelliteSparkle;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_playVoice = 8;
                    }
                }
                break;
            case kObjSatelliteOppositeForming:
                if (m_orbitTime <= 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].SetVelocity((double)(m_orbitAngle + 0xb4), 50.0);
                m_objects[v4].x = m_objects[v4].vx * m_orbitDirection + x;
                m_objects[v4].y = y - 50.0 + m_objects[v4].vy * 0.25;
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].layer = 0;
                } else {
                    m_objects[v4].layer = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = kObjSatelliteOpposite;
                        m_objects[v4].scale = 0;
                        m_objects[v4].facing = facing;
                        l50.type = kObjSatelliteSparkle;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_playVoice = 8;
                    }
                }
                break;
            case kObjSatelliteSparkle:
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
            case kObjLv4Summon1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = kObjLv4Popup5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 9;
                    }
                    if (m_objects[v4].frame == 0xd && m_objectVar1[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].hitsLeft = 1;
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = kObjLv4Popup5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xa;
                    }
                    if (m_objects[v4].frame == 0xd && m_objectVar1[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].hitsLeft = 1;
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = kObjLv4Popup5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xb;
                    }
                    if (m_objects[v4].frame == 0xd && m_objectVar1[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].hitsLeft = 1;
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Bomb:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                    m_objectVar3[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    if (m_objectVar3[v4] == 6) {
                        m_objectVar2[v4] = 0;
                        m_objectVar3[v4] = 0;
                        m_objects[v4].frame = 7;
                        m_objects[v4].timer = 0;
                        l50.type = kObjLv4Smoke;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 25.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.keep = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        l50.type = kObjLv4Spark;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        m_objects[v4].hitsLeft = 1;
                        m_objects[v4].attackResult = 0;
                        m_playSound = 0x16;
                        ShakeScreen(5, 5);
                        break;
                    }
                    if (m_objectVar2[v4] == 0xf) {
                        if (m_objectVar3[v4] < 5) {
                            l50.type = m_objectVar3[v4] + 0x1b1;
                            l50.x = m_objects[v4].x;
                            l50.y = m_objects[v4].y - 50.0;
                            l50.scale = 0;
                            l50.layer = 1;
                            l50.facing = 1;
                            SpawnObject(&l50);
                        }
                        m_objectVar3[v4]++;
                        m_objectVar2[v4] = 0;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].frame = 5;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon4:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].frame == 0xb || m_objects[v4].frame == 0xc) {
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = kObjLv4Popup5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xc;
                        m_objects[v4].vx = 2.0;
                    }
                    if (m_objects[v4].frame == 0xd && m_objectVar1[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].hitsLeft = 1;
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 0xd) {
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon5:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                    m_objects[v4].hitsLeft = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = kObjLv4Popup5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_playVoice = 0x10;
                        l50.type = kObjLv4Summon5Wave;
                        l50.x = m_objects[v4].x;
                        l50.y = 0.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0x10 && m_objectVar1[v4] < 0xa) {
                        m_objects[v4].frame = 0xf;
                        m_objects[v4].hitsLeft = 1;
                        m_objects[v4].attackResult = 0;
                        m_objectVar1[v4]++;
                        l50.type = kObjLv4Summon5Wave;
                        l50.x = m_objects[v4].x;
                        l50.y = 0.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon6:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0) {
                    l50.type = kObjLv4Summon6Hit;
                    l50.x = m_objects[v4].x + (m_objects[v4].facing << 2);
                    l50.y = m_objects[v4].y - 38.0;
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = kObjLv4Popup5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xf;
                    }
                    if (m_objects[v4].frame == 0xd && m_objectVar1[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].hitsLeft = 0;
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon6Left:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -((WORD)Random(0, 0x14) * 0.1 + 0.25);
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0) {
                    l50.type = kObjLv4Summon6Hit;
                    l50.x = m_objects[v4].x - (m_objects[v4].facing << 2);
                    l50.y = m_objects[v4].y - 38.0;
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = -m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * -1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = kObjLv4Popup5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xf;
                    }
                    if (m_objects[v4].frame == 0xd && m_objectVar1[v4] < 0x14) {
                        m_objects[v4].frame = 0xb;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].hitsLeft = 0;
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon7:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 * facing + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                    m_objects[v4].hitsLeft = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = -m_objects[v4].vx;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = kObjLv4Popup5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xb) {
                        m_playVoice = 0xe;
                        l50.type = kObjLv4Summon7Attack;
                        l50.x = m_objects[v4].x;
                        l50.y = 0.0;
                        l50.keep = 1;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon7Attack:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = -0.5;
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                    m_objects[v4].attackResult = 0;
                    m_objects[v4].hitsLeft = 1;
                }
                m_objectVar1[v4]++;
                if (m_objectVar1[v4] == 2) {
                    l50.type = kObjLv4Puff;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y - 10.0;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                    m_objectVar1[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    m_objects[v4].hitsLeft = 1;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar2[v4] < 0xa) {
                            m_objectVar2[v4]++;
                            m_objects[v4].frame = m_objects[v4].frame - 4;
                            break;
                        }
                        l50.type = kObjLv4Smoke;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 25.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.keep = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        l50.type = kObjLv4Spark;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        m_playSound = 0x16;
                        ShakeScreen(5, 5);
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon8:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0x10) {
                        l50.type = kObjLv4Shot;
                        l50.keep = 1;
                        l50.x = m_objects[v4].x + m_objects[v4].facing * 5;
                        l50.y = m_objects[v4].y - 10.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_playVoice = 0x12;
                    }
                    if (m_objects[v4].frame == 0x10 && m_objectVar1[v4] < 8) {
                        m_objects[v4].frame = 0xf;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Shot:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                    m_objects[v4].vx = 0.5;
                    m_objects[v4].vy = -1.0;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.025;
                }
                if (m_objects[v4].y >= 0.0) {
                    if (m_objects[v4].frame < 2) {
                        m_objects[v4].frame = m_objects[v4].frame + 2;
                    }
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 1.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].x > 650.0 || m_objects[v4].x < -10.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case kObjLv4Summon9:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame < 5) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].x > 600.0 && m_objects[v4].facing * m_objects[v4].vx > 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].x < 40.0 && m_objects[v4].facing * m_objects[v4].vx < 0.0) {
                        m_objects[v4].facing = -m_objects[v4].facing;
                    }
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[v4].attackResult == 5) {
                    m_objects[v4].frame = (WORD)Random(0, 3) + 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = m_objects[v4].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].attackResult = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 5) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame == 6) {
                        l50.type = kObjLv4Popup1;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 7) {
                        l50.type = kObjLv4Popup2;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 8) {
                        l50.type = kObjLv4Popup3;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 9) {
                        l50.type = kObjLv4Popup4;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0xa) {
                        l50.type = kObjLv4Popup5;
                        l50.x = m_objects[v4].x;
                        l50.y = m_objects[v4].y - 50.0;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 0x10 && m_objectVar1[v4] < 0xf) {
                        m_objects[v4].frame = 0xc;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].hitsLeft = 1;
                        m_objects[v4].attackResult = 0;
                        m_playVoice = 0x11;
                    }
                    if (m_objects[v4].frame == v58 - 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Smoke:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = (WORD)Random(0, 0x168);
                    m_objectVar2[v4] = (WORD)Random(0, 0x64);
                }
                m_objectVar2[v4] -= 3;
                if (m_objectVar2[v4] < 0xa) {
                    m_objectVar2[v4] = 0xa;
                }
                m_objects[v4].SetVelocity((double)m_objectVar1[v4], m_objectVar2[v4] * 0.1);
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Puff:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = (WORD)Random(0, 0x168);
                    m_objectVar2[v4] = (WORD)Random(0, 0x1e);
                }
                m_objectVar2[v4] -= 4;
                if (m_objectVar2[v4] < 5) {
                    m_objectVar2[v4] = 5;
                }
                m_objects[v4].SetVelocity((double)m_objectVar1[v4], m_objectVar2[v4] * 0.1);
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Spark:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0xa0) * 0.1 + -8.0;
                    m_objects[v4].vy = -8.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar1[v4] < 0x10) {
                            m_objectVar1[v4]++;
                            m_objects[v4].frame--;
                            l50.type = kObjLv4Puff;
                            l50.x = m_objects[v4].x;
                            l50.y = m_objects[v4].y;
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.facing = m_objects[v4].facing;
                            SpawnObject(&l50);
                            break;
                        }
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Summon5Wave:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
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
            case kObjLv4Summon6Hit:
                m_objects[v4].vx = 2.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
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
            case kObjLv4Popup1:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Popup2:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Popup3:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Popup4:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Popup5:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = -0.15;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
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
                    l50.type = kObjShardSmall;
                    l50.x = (double)((int)x + facing * 0x17);
                    l50.y = (double)((int)y - 4);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = kObjShardSmall;
                    l50.x = (double)((int)x - (facing << 2));
                    l50.y = (double)((int)y - 6);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = kObjShardSmall;
                    l50.x = (double)((int)x - facing * 0xe);
                    l50.y = (double)((int)y - 0x1a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = kObjShardSmall;
                    l50.x = (double)(int)x;
                    l50.y = (double)(int)y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = kObjShardSmall;
                    l50.x = (double)((int)x + facing * 0x1e);
                    l50.y = (double)((int)y - 0x28);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = kObjShardSmall;
                    l50.x = (double)((int)x - facing * 0x19);
                    l50.y = (double)((int)y - 0x50);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = kObjShardLarge;
                    l50.x = (double)((int)x - facing * 0x23);
                    l50.y = (double)((int)y - 0x2a);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = kObjShardLarge;
                    l50.x = (double)((int)x - facing * 0x12);
                    l50.y = (double)((int)y - 0x14);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = kObjShardLarge;
                    l50.x = (double)((int)x + facing * 2);
                    l50.y = (double)((int)y - 0x41);
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = kObjShardLarge;
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
