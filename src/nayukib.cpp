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
    int i;

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
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
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

void CNayukiB::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
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
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    if (m_orbitLevel > 0) {
        sprite = *anims[0x2b].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(0x31 - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 0x10f - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_orbitLevel > 0) {
        sprite = *anims[0x2c].frames;
        src = MakeRect(0, 0, m_orbitTime * sprite.width / 0xbb8, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(0x31 - sprite.x, 0x1f - sprite.y, m_orbitTime * sprite.width / 0xbb8, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 0x10f - m_orbitTime * sprite.width / 0xbb8, 0x1f - sprite.y, m_orbitTime * sprite.width / 0xbb8, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
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

void CNayukiB::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CNayukiB::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + 0x69;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0xf0) != 0 && step == 4) {
            m_command = ((input & 0xe0) > 0) + kCmd641236A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
            return;
        }
        if ((input & 0xf) == (facing == -1) + 5 && step == 3) {
            if ((input & 0xf0) != 0) {
                m_command = ((input & 0xe0) > 0) + kCmd641236A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
                return;
            }
            step = 4;
        }
        if ((input & 0xf) == 6 - (facing == -1) && step == 2) {
            step = 3;
        }
        if ((input & 0xf) == 2 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == (facing == -1) + 1 && step == 0 && m_gauge >= 0x3e8) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x5a;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0xf0) != 0 && step == 6) {
            m_command = ((input & 0xe0) > 0) + kCmd214214A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
            return;
        }
        if ((input & 0xf) == 2 - (facing == -1) && step == 5) {
            if ((input & 0xf0) != 0) {
                m_command = ((input & 0xe0) > 0) + kCmd214214A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
                return;
            }
            step = 6;
        }
        if ((input & 0xf) == 6 - (facing == -1) && step == 4) {
            step = 5;
        }
        if ((input & 0xf) == 4 && step == 3) {
            step = 4;
        }
        if ((input & 0xf) == 2 - (facing == -1) && step == 2) {
            step = 3;
        }
        if ((input & 0xf) == 6 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 4 && step == 0 && m_gauge >= 0x3e8) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x5a;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0xf0) != 0 && step == 6) {
            m_command = ((input & 0xe0) > 0) + kCmd236236A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
            return;
        }
        if ((input & 0xf) == (facing == -1) + 1 && step == 5) {
            if ((input & 0xf0) != 0) {
                m_command = ((input & 0xe0) > 0) + kCmd236236A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
                return;
            }
            step = 6;
        }
        if ((input & 0xf) == (facing == -1) + 5 && step == 4) {
            step = 5;
        }
        if ((input & 0xf) == 4 && step == 3) {
            step = 4;
        }
        if ((input & 0xf) == (facing == -1) + 1 && step == 2) {
            step = 3;
        }
        if ((input & 0xf) == (facing == -1) + 5 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 4 && step == 0 && m_gauge >= 0x3e8) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x78;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0xf0) != 0 && step == 3) {
            m_command = ((input & 0xe0) > 0) + kCmd623A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
            return;
        }
        if ((input & 0xf) == (facing == -1) + 5 && step == 2) {
            if ((input & 0xf0) != 0) {
                m_command = ((input & 0xe0) > 0) + kCmd623A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
                return;
            }
            step = 3;
        }
        if ((input & 0xf) == 4 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == (facing == -1) + 1 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x87;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0xf0) != 0 && step == 3) {
            m_command = ((input & 0xe0) > 0) + kCmd236A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
            return;
        }
        if ((input & 0xf) == (facing == -1) + 1 && step == 2) {
            if ((input & 0xf0) != 0) {
                m_command = ((input & 0xe0) > 0) + kCmd236A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
                return;
            }
            step = 3;
        }
        if ((input & 0xf) == (facing == -1) + 5 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 4 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x87;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0xf0) != 0 && step == 3) {
            m_command = ((input & 0xe0) > 0) + kCmd412A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
            return;
        }
        if ((input & 0xf) == 4 && step == 2) {
            if ((input & 0xf0) != 0) {
                m_command = ((input & 0xe0) > 0) + kCmd412A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
                return;
            }
            step = 3;
        }
        if ((input & 0xf) == 6 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 2 - (facing == -1) && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x87;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0xf0) != 0 && step == 3) {
            m_command = ((input & 0xe0) > 0) + kCmd214A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
            return;
        }
        if ((input & 0xf) == 2 - (facing == -1) && step == 2) {
            if ((input & 0xf0) != 0) {
                m_command = ((input & 0xe0) > 0) + kCmd214A + ((input & 0xc0) > 0) + ((input & 0x80) > 0);
                return;
            }
            step = 3;
        }
        if ((input & 0xf) == 6 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 4 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x78;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0x40) != 0 && step == 3) {
            m_command = kCmd263C;
            return;
        }
        if ((input & 0xf) == (facing == -1) + 5 && step == 2) {
            if ((input & 0x40) != 0) {
                m_command = kCmd263C;
                return;
            }
            step = 3;
        }
        if ((input & 0xf) == (facing == -1) + 1 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 4 && step == 0 && m_gauge == 0xbb8) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0xaf;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 8) != 0 && step == 1) {
            m_command = kCmdUp;
            return;
        }
        if ((input & 8) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x5a;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0x80) != 0 && step == 4) {
            m_command = kCmd22D;
            return;
        }
        if ((input & 0xf) == 4 && step == 3) {
            step = 4;
        }
        if ((input & 0xf) == 0 && step == 2) {
            step = 3;
        }
        if ((input & 0xf) == 4 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 0 && step == 0 && pattern == kWakeUp) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x5a;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0x40) != 0 && step == 4) {
            m_command = kCmd22C;
            return;
        }
        if ((input & 0xf) == 4 && step == 3) {
            step = 4;
        }
        if ((input & 0xf) == 0 && step == 2) {
            step = 3;
        }
        if ((input & 0xf) == 4 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x87;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0x20) != 0 && step == 4) {
            m_command = kCmd22B;
            return;
        }
        if ((input & 0xf) == 4 && step == 3) {
            step = 4;
        }
        if ((input & 0xf) == 0 && step == 2) {
            step = 3;
        }
        if ((input & 0xf) == 4 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x87;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0x10) != 0 && step == 4) {
            m_command = kCmd22A;
            return;
        }
        if ((input & 0xf) == 4 && step == 3) {
            step = 4;
        }
        if ((input & 0xf) == 0 && step == 2) {
            step = 3;
        }
        if ((input & 0xf) == 4 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x87;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0xf) == 1 && step == 3) {
            m_command = kCmdDashRight;
            return;
        }
        if ((input & 0xf) == 0 && step == 2) {
            step = 3;
        }
        if ((input & 0xf) == 1 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 0 && step == 0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + 0x87;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0xf) == 2 && step == 3) {
            m_command = kCmdDashLeft;
            break;
        }
        if ((input & 0xf) == 0 && step == 2) {
            step = 3;
        }
        if ((input & 0xf) == 2 && step == 1) {
            step = 2;
        }
        if ((input & 0xf) == 0 && step == 0) {
            step = 1;
        }
    }
}

void CNayukiB::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == kAir214C && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 45.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
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
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && dx > 60.0 && dx < 70.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
            m_pressB = 1;
            m_inputY = 1;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (dx < 100.0) {
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
            if (dx < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd236236A;
                return;
            }
        }
        if (dx < 150.0 && dx > 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if (dx < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_gauge >= 0x7d0) {
                m_command = (WORD)Random(0, 2) + kCmd214214B;
                return;
            }
        }
        if (dx > 150.0) {
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
        if (y - (*m_opponent)->y < -20.0 && y - (*m_opponent)->y > -80.0 && dx < 150.0 && (WORD)Random(0, 0xc8) < m_cpuSkill * 5.0f && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 3) + kCmd214214A;
            return;
        }
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && dx < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > 0.0 && y - (*m_opponent)->y < 50.0 && dx < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < 90.0 && y - (*m_opponent)->y > 20.0 && dx < 110.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0 && dx < 80.0) {
            m_command = kCmd623A;
            return;
        }
        if (m_cpuRoll < 5 && m_rfGauge > 500.0 && dx < 80.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 0xa && m_cpuRoll > 5 && m_rfGauge > 500.0 && dx < 100.0) {
            m_command = kCmd412C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && dx < 100.0) {
            m_command = (WORD)Random(0, 3) + kCmd641236A;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && dx > 90.0) {
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
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && dx > 50.0) {
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
            if (dx < 45.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressA = 1;
                m_inputY = Random(0, 2);
                return;
            }
            if (dx < 80.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 70.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
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
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
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
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && dx < 150.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && dx < 70.0) {
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
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x96 && m_cpuRoll < 0xc8 && m_gauge >= 0x3e8 && dx < 120.0) {
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
            if (dx < 45.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressA = 1;
                m_inputY = Random(0, 2);
                return;
            }
            if (dx < 90.0 && m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 100.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
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
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
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
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && dx < 140.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && dx < 70.0) {
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
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
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
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
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
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
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
            if (dx < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
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
                if (dx < 60.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (dx < 45.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (dx > 50.0 && dx < 80.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x41 && m_cpuRoll > 0x28) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x46 < dx && dx < 95.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x14 + 0x50 && m_cpuRoll > 0x46) {
                        m_cpuAction = 0xc;
                        return;
                    }
                }
                if (0x50 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x46 < dx && dx < 110.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x80 && m_cpuRoll > 0x78) {
                        m_cpuAction = 8;
                        return;
                    }
                }
                if (dx < 180.0 && dx > 200.0 && m_cpuRoll < 0xfa && m_cpuRoll > 0x96) {
                    m_cpuAction = 0x10;
                    return;
                }
                if (dx < 130.0 && dx > 100.0 && m_cpuRoll < 0xc3 && m_cpuRoll > 0xaa) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (0x50 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x50 < dx && dx < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x19 + 0xb9 && m_cpuRoll > 0xaa) {
                        m_cpuAction = 0xe;
                        return;
                    }
                }
                if (0x5a - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x5a < dx && dx < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x19 + 0xe1 && m_cpuRoll > 0xd2) {
                        m_cpuAction = 0xa;
                        return;
                    }
                }
                if (dx > 130.0 && dx < 170.0 && m_cpuRoll < 0x104 && m_cpuRoll > 0xfa) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 0x113 && m_cpuRoll > 0x104 && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd623C;
                    return;
                }
                if (dx < 150.0 && m_cpuRoll < 0x118 && m_cpuRoll > 0x113 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 2) + kCmd236236B;
                    return;
                }
                if (dx > 150.0 && m_cpuRoll < 0x11d && m_cpuRoll > 0x118 && m_gauge >= 0xbb8) {
                    m_command = kCmd236236D;
                    return;
                }
                if (dx > 160.0 && m_cpuRoll < 0x136 && m_cpuRoll > 0x12c) {
                    m_command = kCmd412A;
                    return;
                }
                if (dx > 100.0 && dx < 160.0 && m_cpuRoll < 0x140 && m_cpuRoll > 0x136) {
                    m_command = kCmd412B;
                    return;
                }
                if (dx > 100.0 && dx < 160.0 && m_cpuRoll < 0x145 && m_cpuRoll > 0x140) {
                    m_command = kCmd412C;
                    return;
                }
                if (dx > 100.0 && dx < 160.0 && m_cpuRoll < 0x154 && m_cpuRoll > 0x14a) {
                    m_command = kCmd236A;
                    return;
                }
                if (dx > 160.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x154) {
                    m_command = kCmd236B;
                    return;
                }
                if (dx > 40.0 && dx < 120.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x154) {
                    m_command = kCmd214A;
                    return;
                }
                if (dx > 140.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x154) {
                    m_command = kCmd214B;
                    return;
                }
                if (m_cpuRoll < 0x320 && m_cpuRoll > 0x2bc && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir && dx > 100.0) {
                    m_cpuAction = 5;
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
                    if (dx < 90.0 && dy < 140.0 && dy > 80.0 && m_cpuRoll < 0xf) {
                        m_command = kCmd623B;
                        return;
                    }
                    if (dx < 160.0 && dx > 80.0 && dy < 300.0 && dy > 160.0 && m_cpuRoll < 0x28 && m_cpuRoll > 0x1e) {
                        m_command = kCmd236C;
                        return;
                    }
                    if (dx < 150.0 && m_cpuRoll < 0xdc && m_cpuRoll > 0xc8 && (*m_opponent)->y < -50.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + kCmd236236A;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 80.0 && dy < 100.0 && m_cpuRoll < 0x64) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 60.0 && dx < 100.0 && dy > 60.0 && dy < 120.0 && m_cpuRoll > 0xb4 && m_cpuRoll < 0xf0) {
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
                if (dx > 150.0 && m_cpuRoll > 0x104 && m_cpuRoll < 0x109 && dy > 150.0) {
                    m_command = (WORD)Random(0, 3) + kCmd214214A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 80.0 && dy < 100.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 20.0 && dx < 100.0 && dy > 0.0 && dy < 90.0 && (*m_opponent)->y < y && m_cpuRoll > 0x14 && m_cpuRoll < 0x3c) {
                    m_pressB = 1;
                    return;
                }
                if (dx > 50.0 && dx < 130.0 && dy > 0.0 && dy < 90.0 && (*m_opponent)->y < y && m_cpuRoll > 0x3c && m_cpuRoll < 0x64) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 5.0f * m_cpuSkill && dx > 120.0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && dx > 800.0 && dx < 80.0 && (WORD)Random(0, 0x64) < 3.0f * m_cpuSkill && x > 150.0 && x < 490.0) {
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
            case kObj236236A:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 1.2;
                    m_objects[slot].vy = -2.1;
                    m_objects[slot].hitsLeft = 3;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].y < -600.0) {
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
                    if (m_objects[slot].frame == 0 || m_objects[slot].frame == 0xa) {
                        m_objects[slot].attackResult = 0;
                    }
                }
                break;
            case kObj236236B:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 1.2;
                    m_objects[slot].vy = -2.1;
                    m_objects[slot].hitsLeft = 6;
                    m_objectVar1[slot]++;
                    m_objectVar2[slot] = 0;
                }
                m_objectVar2[slot]++;
                if (m_objectVar2[slot] > 0xa) {
                    m_objectVar2[slot] = 0;
                    effect.type = kObj236236Spark;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].y < -600.0) {
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
                    if (m_objects[slot].frame == 0 || m_objects[slot].frame == 5 || m_objects[slot].frame == 0xa || m_objects[slot].frame == 0xf) {
                        m_objects[slot].attackResult = 0;
                    }
                }
                break;
            case kObj236236C:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 1.2;
                    m_objects[slot].vy = -2.1;
                    m_objects[slot].hitsLeft = 0xf;
                    m_objectVar1[slot]++;
                    m_objectVar2[slot] = 0;
                }
                m_objectVar2[slot]++;
                if (m_objectVar2[slot] > 3) {
                    m_objectVar2[slot] = 0;
                    effect.type = kObj236236Spark;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].y < -600.0) {
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
                    if (m_objects[slot].frame == 0 || m_objects[slot].frame == 4 || m_objects[slot].frame == 8 || m_objects[slot].frame == 0xc || m_objects[slot].frame == 0x10) {
                        m_objects[slot].attackResult = 0;
                    }
                }
                break;
            case kObj236236Spark:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 1.0;
                    m_objects[slot].vy = -2.2;
                    m_objects[slot].hitsLeft = 0;
                    m_objectVar1[slot]++;
#ifdef EFZ_NATIVE
                    // The original computes the arguments right to left, so the speed draws first.
                    {
                        double speed = (double)((WORD)Random(0, 3) + 2);
                        m_objects[slot].SetVelocity((double)(WORD)Random(0, 0x168), speed);
                    }
#else
                    m_objects[slot].SetVelocity((double)(WORD)Random(0, 0x168), (double)((WORD)Random(0, 3) + 2));
#endif
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjSatellite:
                if (m_orbitTime <= 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].facing = facing;
                m_objects[slot].SetVelocity((double)m_orbitAngle, 50.0);
                m_objects[slot].x = m_objects[slot].vx * m_orbitDirection + x;
                m_objects[slot].y = y - 50.0 + m_objects[slot].vy * 0.25;
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].layer = 0;
                } else {
                    m_objects[slot].layer = 1;
                }
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].attackResult = 0;
                }
                if (m_objects[slot].frame == 1 && m_objects[slot].hitsLeft == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].pattern = kObjSatelliteSpent;
                    m_objects[slot].scale = 2;
                    m_orbitTime -= 0x3e8 - m_orbitLevel * 0x15e;
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
            case kObjSatelliteOpposite:
                if (m_orbitTime <= 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].facing = facing;
                m_objects[slot].SetVelocity((double)(m_orbitAngle + 0xb4), 50.0);
                m_objects[slot].x = m_objects[slot].vx * m_orbitDirection + x;
                m_objects[slot].y = y - 50.0 + m_objects[slot].vy * 0.25;
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].layer = 0;
                } else {
                    m_objects[slot].layer = 1;
                }
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].attackResult = 0;
                }
                if (m_objects[slot].frame == 1 && m_objects[slot].hitsLeft == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].pattern = kObjSatelliteOppositeSpent;
                    m_objects[slot].scale = 2;
                    m_orbitTime -= 0x3e8 - m_orbitLevel * 0x15e;
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
            case kObjSatelliteSpent:
                if (m_orbitTime <= 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].facing = facing;
                m_objects[slot].SetVelocity((double)m_orbitAngle, 50.0);
                m_objects[slot].x = m_objects[slot].vx * m_orbitDirection + x;
                m_objects[slot].y = y - 50.0 + m_objects[slot].vy * 0.25;
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].layer = 0;
                } else {
                    m_objects[slot].layer = 1;
                }
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjSatelliteForming;
                        m_objects[slot].scale = 2;
                    }
                }
                break;
            case kObjSatelliteOppositeSpent:
                if (m_orbitTime <= 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].facing = facing;
                m_objects[slot].SetVelocity((double)(m_orbitAngle + 0xb4), 50.0);
                m_objects[slot].x = m_objects[slot].vx * m_orbitDirection + x;
                m_objects[slot].y = y - 50.0 + m_objects[slot].vy * 0.25;
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].layer = 0;
                } else {
                    m_objects[slot].layer = 1;
                }
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjSatelliteOppositeForming;
                        m_objects[slot].scale = 2;
                    }
                }
                break;
            case kObjSatelliteForming:
                if (m_orbitTime <= 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].SetVelocity((double)m_orbitAngle, 50.0);
                m_objects[slot].x = m_objects[slot].vx * m_orbitDirection + x;
                m_objects[slot].y = y - 50.0 + m_objects[slot].vy * 0.25;
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].layer = 0;
                } else {
                    m_objects[slot].layer = 1;
                }
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjSatellite;
                        m_objects[slot].scale = 0;
                        m_objects[slot].facing = facing;
                        effect.type = kObjSatelliteSparkle;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.facing = m_objects[slot].facing;
                        SpawnObject(&effect);
                        m_playVoice = 8;
                    }
                }
                break;
            case kObjSatelliteOppositeForming:
                if (m_orbitTime <= 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].SetVelocity((double)(m_orbitAngle + 0xb4), 50.0);
                m_objects[slot].x = m_objects[slot].vx * m_orbitDirection + x;
                m_objects[slot].y = y - 50.0 + m_objects[slot].vy * 0.25;
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].layer = 0;
                } else {
                    m_objects[slot].layer = 1;
                }
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjSatelliteOpposite;
                        m_objects[slot].scale = 0;
                        m_objects[slot].facing = facing;
                        effect.type = kObjSatelliteSparkle;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.facing = m_objects[slot].facing;
                        SpawnObject(&effect);
                        m_playVoice = 8;
                    }
                }
                break;
            case kObjSatelliteSparkle:
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
            case kObjLv4Summon1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xa) {
                        effect.type = kObjLv4Popup5;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_playVoice = 9;
                    }
                    if (m_objects[slot].frame == 0xd && m_objectVar1[slot] < 0x14) {
                        m_objects[slot].frame = 0xb;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xa) {
                        effect.type = kObjLv4Popup5;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_playVoice = 0xa;
                    }
                    if (m_objects[slot].frame == 0xd && m_objectVar1[slot] < 0x14) {
                        m_objects[slot].frame = 0xb;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xa) {
                        effect.type = kObjLv4Popup5;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_playVoice = 0xb;
                    }
                    if (m_objects[slot].frame == 0xd && m_objectVar1[slot] < 0x14) {
                        m_objects[slot].frame = 0xb;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Bomb:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                    m_objectVar2[slot] = 0;
                    m_objectVar3[slot] = 0;
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0) {
                    if (m_objectVar3[slot] == 6) {
                        m_objectVar2[slot] = 0;
                        m_objectVar3[slot] = 0;
                        m_objects[slot].frame = 7;
                        m_objects[slot].timer = 0;
                        effect.type = kObjLv4Smoke;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 25.0;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.keep = 1;
                        effect.facing = m_objects[slot].facing;
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        effect.type = kObjLv4Spark;
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].attackResult = 0;
                        m_playSound = 0x16;
                        ShakeScreen(5, 5);
                        break;
                    }
                    if (m_objectVar2[slot] == 0xf) {
                        if (m_objectVar3[slot] < 5) {
                            effect.type = m_objectVar3[slot] + 0x1b1;
                            effect.x = m_objects[slot].x;
                            effect.y = m_objects[slot].y - 50.0;
                            effect.scale = 0;
                            effect.layer = 1;
                            effect.facing = 1;
                            SpawnObject(&effect);
                        }
                        m_objectVar3[slot]++;
                        m_objectVar2[slot] = 0;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 7) {
                        m_objects[slot].frame = 5;
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].frame == 0xb || m_objects[slot].frame == 0xc) {
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xa) {
                        effect.type = kObjLv4Popup5;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_playVoice = 0xc;
                        m_objects[slot].vx = 2.0;
                    }
                    if (m_objects[slot].frame == 0xd && m_objectVar1[slot] < 0x14) {
                        m_objects[slot].frame = 0xb;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == 0xd) {
                        m_objects[slot].vx = 0.0;
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon5:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xa) {
                        effect.type = kObjLv4Popup5;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xf) {
                        m_playVoice = 0x10;
                        effect.type = kObjLv4Summon5Wave;
                        effect.x = m_objects[slot].x;
                        effect.y = 0.0;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.facing = m_objects[slot].facing;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0x10 && m_objectVar1[slot] < 0xa) {
                        m_objects[slot].frame = 0xf;
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].attackResult = 0;
                        m_objectVar1[slot]++;
                        effect.type = kObjLv4Summon5Wave;
                        effect.x = m_objects[slot].x;
                        effect.y = 0.0;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.facing = m_objects[slot].facing;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon6:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].frame == 0xb && m_objects[slot].timer == 0) {
                    effect.type = kObjLv4Summon6Hit;
                    effect.x = m_objects[slot].x + (m_objects[slot].facing << 2);
                    effect.y = m_objects[slot].y - 38.0;
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].vx = -m_objects[slot].vx;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = -m_objects[slot].vx;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xa) {
                        effect.type = kObjLv4Popup5;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_playVoice = 0xf;
                    }
                    if (m_objects[slot].frame == 0xd && m_objectVar1[slot] < 0x14) {
                        m_objects[slot].frame = 0xb;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_objects[slot].hitsLeft = 0;
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon6Left:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -((WORD)Random(0, 0x14) * 0.1 + 0.25);
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].frame == 0xb && m_objects[slot].timer == 0) {
                    effect.type = kObjLv4Summon6Hit;
                    effect.x = m_objects[slot].x - (m_objects[slot].facing << 2);
                    effect.y = m_objects[slot].y - 38.0;
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = -m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].vx = -m_objects[slot].vx;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = -m_objects[slot].vx;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * -1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xa) {
                        effect.type = kObjLv4Popup5;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_playVoice = 0xf;
                    }
                    if (m_objects[slot].frame == 0xd && m_objectVar1[slot] < 0x14) {
                        m_objects[slot].frame = 0xb;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_objects[slot].hitsLeft = 0;
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon7:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 * facing + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].vx = -m_objects[slot].vx;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = -m_objects[slot].vx;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xa) {
                        effect.type = kObjLv4Popup5;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xb) {
                        m_playVoice = 0xe;
                        effect.type = kObjLv4Summon7Attack;
                        effect.x = m_objects[slot].x;
                        effect.y = 0.0;
                        effect.keep = 1;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = m_objects[slot].facing;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon7Attack:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = -0.5;
                    m_objectVar1[slot] = 0;
                    m_objectVar2[slot] = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objectVar1[slot]++;
                if (m_objectVar1[slot] == 2) {
                    effect.type = kObjLv4Puff;
                    effect.x = m_objects[slot].x;
                    effect.y = m_objects[slot].y - 10.0;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                    m_objectVar1[slot] = 0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].hitsLeft = 1;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar2[slot] < 0xa) {
                            m_objectVar2[slot]++;
                            m_objects[slot].frame = m_objects[slot].frame - 4;
                            break;
                        }
                        effect.type = kObjLv4Smoke;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 25.0;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.keep = 1;
                        effect.facing = m_objects[slot].facing;
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        effect.type = kObjLv4Spark;
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        m_playSound = 0x16;
                        ShakeScreen(5, 5);
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon8:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0x10) {
                        effect.type = kObjLv4Shot;
                        effect.keep = 1;
                        effect.x = m_objects[slot].x + m_objects[slot].facing * 5;
                        effect.y = m_objects[slot].y - 10.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = m_objects[slot].facing;
                        SpawnObject(&effect);
                        m_playVoice = 0x12;
                    }
                    if (m_objects[slot].frame == 0x10 && m_objectVar1[slot] < 8) {
                        m_objects[slot].frame = 0xf;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Shot:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = 0.5;
                    m_objects[slot].vy = -1.0;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.025;
                }
                if (m_objects[slot].y >= 0.0) {
                    if (m_objects[slot].frame < 2) {
                        m_objects[slot].frame = m_objects[slot].frame + 2;
                    }
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vx = 1.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].x > 650.0 || m_objects[slot].x < -10.0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjLv4Summon9:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0x14) * 0.1 + 0.25;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 0xa) * 0.05;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].frame < 5) {
                    m_objects[slot].vy += 0.025;
                    if (m_objects[slot].x > 600.0 && m_objects[slot].facing * m_objects[slot].vx > 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].x < 40.0 && m_objects[slot].facing * m_objects[slot].vx < 0.0) {
                        m_objects[slot].facing = -m_objects[slot].facing;
                    }
                    if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = (WORD)Random(0, 3) + 5;
                    }
                }
                if (m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = (WORD)Random(0, 3) + 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = m_objects[slot].facing * 1.0 * (*m_opponent)->facing;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].attackResult = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 5) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame == 6) {
                        effect.type = kObjLv4Popup1;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 7) {
                        effect.type = kObjLv4Popup2;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 8) {
                        effect.type = kObjLv4Popup3;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 9) {
                        effect.type = kObjLv4Popup4;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0xa) {
                        effect.type = kObjLv4Popup5;
                        effect.x = m_objects[slot].x;
                        effect.y = m_objects[slot].y - 50.0;
                        effect.scale = 0;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame == 0x10 && m_objectVar1[slot] < 0xf) {
                        m_objects[slot].frame = 0xc;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 0xc) {
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].attackResult = 0;
                        m_playVoice = 0x11;
                    }
                    if (m_objects[slot].frame == frameCount - 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Smoke:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objectVar1[slot] = (WORD)Random(0, 0x168);
                    m_objectVar2[slot] = (WORD)Random(0, 0x64);
                }
                m_objectVar2[slot] -= 3;
                if (m_objectVar2[slot] < 0xa) {
                    m_objectVar2[slot] = 0xa;
                }
                m_objects[slot].SetVelocity((double)m_objectVar1[slot], m_objectVar2[slot] * 0.1);
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Puff:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objectVar1[slot] = (WORD)Random(0, 0x168);
                    m_objectVar2[slot] = (WORD)Random(0, 0x1e);
                }
                m_objectVar2[slot] -= 4;
                if (m_objectVar2[slot] < 5) {
                    m_objectVar2[slot] = 5;
                }
                m_objects[slot].SetVelocity((double)m_objectVar1[slot], m_objectVar2[slot] * 0.1);
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Spark:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 0xa0) * 0.1 + -8.0;
                    m_objects[slot].vy = -8.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] < 0x10) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame--;
                            effect.type = kObjLv4Puff;
                            effect.x = m_objects[slot].x;
                            effect.y = m_objects[slot].y;
                            effect.scale = 2;
                            effect.layer = 1;
                            effect.facing = m_objects[slot].facing;
                            SpawnObject(&effect);
                            break;
                        }
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Summon5Wave:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
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
            case kObjLv4Summon6Hit:
                m_objects[slot].vx = 2.0;
                m_objects[slot].vy = 0.0;
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].attackResult = 0;
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
            case kObjLv4Popup1:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = -0.15;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Popup2:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = -0.15;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Popup3:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = -0.15;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Popup4:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = -0.15;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Popup5:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = -0.15;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].scale = 1;
                    }
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
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x + facing * 0x17);
                    effect.y = (double)((int)y - 4);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x - (facing << 2));
                    effect.y = (double)((int)y - 6);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x - facing * 0xe);
                    effect.y = (double)((int)y - 0x1a);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardSmall;
                    effect.x = (double)(int)x;
                    effect.y = (double)(int)y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x + facing * 0x1e);
                    effect.y = (double)((int)y - 0x28);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x - facing * 0x19);
                    effect.y = (double)((int)y - 0x50);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x - facing * 0x23);
                    effect.y = (double)((int)y - 0x2a);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x - facing * 0x12);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x + facing * 2);
                    effect.y = (double)((int)y - 0x41);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
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
