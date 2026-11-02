// CKano (0x653a20-0x66756f).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CKano::CKano(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "kano");
    lastSurface = 0x434;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    unk3148 = 0;
    unk314c = 0;
    m_chargeGauge = 0;
    m_gaugeRegenTimer = 0;
    m_idleTimer = 0;
    m_meteorsPending = 0;
    m_meteorTimer = 0;
    m_meteorFacing = 0;
    m_orbsOut = 0;
    m_shotsOut = 0;
    m_eruptionsOut = 0;
    m_pointX[0] = -0xd;
    m_pointY[0] = -0x38;
    m_pointX[1] = 0x13;
    m_pointY[1] = 0;
    m_pointX[2] = 0xb;
    m_pointY[2] = -7;
    m_pointX[3] = -3;
    m_pointY[3] = -0x13;
    m_pointX[4] = -0x16;
    m_pointY[4] = -0x26;
    m_resultPictures = 5;
    m_rivals[0] = 0x17;
    m_rivals[1] = 0x18;
    m_rivals[0xa] = 0x14;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
}

void CKano::Reset()
{
    int v4;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    unk3148 = 0;
    unk314c = 0;
    m_chargeGauge = 0;
    m_gaugeRegenTimer = 0;
    m_idleTimer = 0;
    m_meteorsPending = 0;
    m_meteorTimer = 0;
    m_meteorFacing = 0;
    m_orbsOut = 0;
    m_shotsOut = 0;
    m_eruptionsOut = 0;
    m_pointX[0] = -4;
    m_pointY[0] = -0x39;
    m_pointX[1] = 0x12;
    m_pointY[1] = 0;
    m_pointX[2] = 0x15;
    m_pointY[2] = -0xc;
    m_pointX[3] = 0x12;
    m_pointY[3] = -0xf;
    m_pointX[4] = 0x26;
    m_pointY[4] = -0x27;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
    CPlayer::Reset();
}

void CKano::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CKano::RemoveObject(short p1)
{
    m_objectVar1[p1] = 0;
    m_objectVar2[p1] = 0;
    m_objectVar3[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CKano::Move()
{
    MoveOnGround();
}

void CKano::StartCommand()
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
    if (m_sealLevel < 2) {
        if (m_hp < 0xd05 && (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) && m_command == kCmd21436D && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214C;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd214214B && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214B;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd214214A && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214A;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd236236C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236C;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd236236B && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236B;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd236236A && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236A;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd21436C && y == 0.0 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436C;
            return;
        }
        if ((m_command == kCmd21436B || m_command == kCmd21436C) && y == 0.0 && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436B;
            return;
        }
        if ((m_command == kCmd21436A || m_command == kCmd21436B || m_command == kCmd21436C) && y == 0.0 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436A;
            return;
        }
        if (m_command == kCmd22B && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k22B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k22B;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd641236C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236C;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd641236B && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236B;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd641236A && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236A;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0;
            }
            return;
        }
        if (m_command == kCmd421C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_orbsOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k421C].level && y == 0.0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k421C;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0x9c4;
            }
            return;
        }
        if (m_command == kCmd421B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_orbsOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k421B].level && y == 0.0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k421B;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0x1388;
            }
            return;
        }
        if (m_command == kCmd421A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_orbsOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k421A].level && y == 0.0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k421A;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0x1d4c;
            }
            return;
        }
        if (m_command == kCmd214C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_shotsOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level && y == 0.0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0x9c4;
            }
            return;
        }
        if (m_command == kCmd214B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_shotsOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level && y == 0.0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0x1388;
            }
            return;
        }
        if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_shotsOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level && y == 0.0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0x1d4c;
            }
            return;
        }
        if (m_command == kCmd236C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_eruptionsOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236C].level && y == 0.0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0x9c4;
            }
            return;
        }
        if (m_command == kCmd236B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_eruptionsOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236B].level && y == 0.0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236B;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0x1388;
            }
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_eruptionsOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236A].level && y == 0.0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236A;
            if (m_chargeGauge >= 0x2710) {
                frame = 7;
                timer = 0;
                m_chargeGauge = 0x1d4c;
            }
            return;
        }
        if (m_command == kCmd236D && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236D].level && y == 0.0 && m_chargeGauge < 0x2710) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236D;
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
            if (y < -25.0 && m_inputY == 1 && m_patterns[pattern].cancelLevel <= m_patterns[kJump2A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kJump2A;
                return;
            }
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
            if (y < -30.0 && m_inputY == 1 && m_patterns[pattern].cancelLevel <= m_patterns[kJump2B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kJump2B;
                return;
            }
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
            if (m_patterns[pattern].cancelLevel <= m_patterns[k6B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k6B;
                return;
            }
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
            if (y < -25.0 && m_inputY == 1 && m_patterns[pattern].cancelLevel <= m_patterns[kJump2C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kJump2C;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[kJumpC].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kJumpC;
                return;
            }
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_inputX == facing && m_patterns[pattern].cancelLevel <= m_patterns[k3C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k3C;
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k2C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k2C;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
            if ((*m_opponent)->y == 0.0 && m_inputX != 0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kThrow;
                return;
            }
            if (y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k6C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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
    if (m_sealLevel < 2 && (m_pressD == 1 || (m_bufferedPress & 0x80) != 0 || (m_dashBufferedPress & 0x80) != 0) && m_chargeGauge < 0x2710 && m_patterns[pattern].cancelLevel <= m_patterns[k5D].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
        StartPattern();
        ClearBufferedPress();
        pattern = k5D;
    }
}

void CKano::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (m_chargeGauge == 0x2710) {
        x1c = *anims[0x2a].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_chargeGauge != 0 && m_chargeGauge < 0x2710) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_chargeGauge != 0 && m_chargeGauge < 0x2710) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, m_chargeGauge * x1c.width / 0x2710, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, m_chargeGauge * x1c.width / 0x2710, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - m_chargeGauge * x1c.width / 0x2710, 0x1f - x1c.y, m_chargeGauge * x1c.width / 0x2710, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CKano::PreUpdate()
{
    EffectDesc v48;
    InitEffectDesc((EffectDesc*)&v48);
    if ((*m_opponent)->m_freezeTime == 0 && pattern < 0x12c) {
        m_gaugeRegenTimer++;
    }
    if (m_gaugeRegenTimer > 0x1e - (0x1c - ((int)(m_gauge * 0.001) << 2))) {
        m_gauge++;
        m_gaugeRegenTimer = 0;
    }
    if (0.0 != (m_gaugeRegenTimer > 0x1e - (0x1c - ((int)(m_gauge * 0.001) << 2))) * 0.5 && pattern == kCrouch) {
        m_gauge++;
        m_gaugeRegenTimer = 0;
    }
    if (vx == 0.0 && (*m_opponent)->m_freezeTime == 0 && pattern < 0x12c && (pattern < kFirstHitReaction || pattern > kFirstCharacterAction)) {
        m_idleTimer++;
    } else {
        m_idleTimer = 0;
    }
    if (m_idleTimer > 0x276) {
        m_gauge = m_gauge + 0x12c;
        m_idleTimer = 0;
        v48.type = kObjIdleBonus;
        v48.x = (double)(int)x;
        v48.y = y - 50.0;
        v48.facing = 1;
        v48.scale = 0;
        v48.layer = 1;
        SpawnObject(&v48);
    }
    m_meteorTimer--;
    if (m_meteorsPending > 0 && m_meteorTimer <= 0) {
        v48.type = kObjMeteor;
        v48.x = (double)((int)x + 0x78 - (WORD)Random(0, 0xf0) - (int)(m_meteorFacing * 192.0));
        v48.y = -480.0;
        v48.facing = *(char*)&m_meteorFacing;
        v48.scale = 2;
        v48.layer = 1;
        v48.keep = 1;
        SpawnObject(&v48);
        m_meteorsPending--;
        m_meteorTimer = 0xb4;
    }
}

void CKano::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CKano::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = kCmdNone;
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 5) {
            m_command = ((v5 & 0xe0) > 0) + kCmd21436A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 4) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + 0xa0 + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 3) {
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
            m_command = ((v5 & 0xe0) > 0) + kCmd421A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd623A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 4 && x6 == 1) {
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

void CKano::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == kUnused108 && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 40.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
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
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 > 20.0 && v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd623C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && v10 < 80.0 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && v10 < 150.0 && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
        }
        if (v10 < 220.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
        }
        if (v10 > 220.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
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
        if (m_cpuRoll < 3 && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 4 && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 3) + kCmd641236A;
            return;
        }
        if (m_cpuRoll > 0x55) {
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
            m_command = (WORD)Random(0, 3) + kCmd641236A;
            return;
        }
        if (m_cpuRoll > 0x55) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k5D || pattern == k236D || pattern == 0xfc || pattern == kUnused10e || pattern == 0x10f || pattern == 0x110)) {
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
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x1e) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
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
                m_command = (WORD)Random(0, 3) + kCmd641236A;
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
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x1c2 && v10 < 90.0) {
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
                    if (v10 > 80.0) {
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
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x258 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 0x1f4 && m_attackResult == 3 && v10 < 80.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                    if (v10 > 110.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == k5C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
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
                m_command = kCmd412A;
                if (v10 > 120.0) {
                    m_command = kCmd412B;
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
        if (pattern == k2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x14) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (v10 < 135.0 && m_cpuRoll < 0x258) {
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
                    if (v10 > 110.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x258 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x12c && v10 < 100.0) {
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
                    if (v10 > 110.0) {
                        m_cpuAction = 8;
                    }
                }
                return;
            }
        }
        if (pattern == k2C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
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
            if (m_cpuRoll > 0x1ae && m_cpuRoll < 0x21c && m_attackResult != 3) {
                m_command = kCmd412A;
                if (v10 > 120.0) {
                    m_command = kCmd412B;
                }
                return;
            }
            if (m_cpuRoll > 0x289) {
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
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xdc && v10 < 90.0 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x289 && (WORD)Random(0, 2) == 0) {
                m_cpuAction = 0xc;
                if (v10 > 110.0) {
                    m_cpuAction = 8;
                }
            }
        }
        if (pattern == kDashC) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
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
                m_command = kCmd412A;
                if (v10 > 120.0) {
                    m_command = kCmd412B;
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
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 50.0 && m_cpuRoll < 0x17) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 75.0 && m_cpuRoll < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x28 && m_cpuRoll > 0x1e) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x34 && m_cpuRoll > 0x28 || v10 > 80.0 && v10 < 130.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x34) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && m_cpuRoll < 0x64 && m_cpuRoll > 0x50) {
                    m_cpuAction = 8;
                    return;
                }
                if (v10 > 70.0 && v10 < 120.0 && m_cpuRoll < 0x78 && m_cpuRoll > 0x64) {
                    m_cpuAction = 8;
                    return;
                }
                if (v10 < 90.0 && v10 > 70.0 && m_cpuRoll < 0x82 && m_cpuRoll > 0x78) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 120.0 && v10 > 70.0 && m_cpuRoll < 0x91 && m_cpuRoll > 0x82) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 100.0 && v10 < 140.0 && m_cpuRoll < 0x98 && m_cpuRoll > 0x91) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0xa5 && m_cpuRoll > 0x91 && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd623C;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0xaa && m_cpuRoll > 0xa5 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 3) + kCmd641236A;
                    return;
                }
                if (v10 > 200.0 && m_cpuRoll < 0xaa && m_cpuRoll > 0xa5 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 3) + 0x82;
                    return;
                }
                if (v10 > 200.0 && m_cpuRoll < 0xbe && m_cpuRoll > 0xaa) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = kCmd412A;
                    return;
                }
                if (v10 > 140.0 && v10 < 180.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = kCmd412B;
                    return;
                }
                if (v10 > 200.0 && v10 < 240.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = kCmd412C;
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
                    if (v10 < 80.0 && m_cpuRoll < 0xf && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + kCmd641236A;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623C;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 100.0 && m_cpuRoll < 0x23 && m_cpuRoll > 0xa) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 > 100.0 && v10 < 140.0 && x8 < 180.0 && x8 > 140.0 && m_cpuRoll < 0x3c && m_cpuRoll > 0x23) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 > 100.0 && v10 < 140.0 && x8 < 140.0 && x8 > 100.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x3c) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 80.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x50 && (*m_opponent)->y < -50.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + kCmd641236A;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x32) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 120.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x32 && m_cpuRoll < 0x78) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && x8 > 100.0 && x8 < 180.0 && m_cpuRoll > 0x78 && m_cpuRoll < 0xaa) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 0x140) < v10 - 100.0 && x8 < 90.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xdc) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (v10 > 100.0 && m_cpuRoll > 0xf0 && m_cpuRoll < 0x14a && x8 + 40.0 > v10 && x8 - 40.0 < v10) {
                    m_command = (WORD)Random(0, 3) + kCmd412A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 120.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x14 && m_cpuRoll < 0x28) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && x8 > 100.0 && x8 < 180.0 && m_cpuRoll > 0x28 && m_cpuRoll < 0x32) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 0x140) < v10 - 100.0 && x8 < 180.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xf0) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 3.0f * m_cpuSkill) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && v10 > 60.0 && v10 < 140.0 && (WORD)Random(0, 0x64) < 2.0f * m_cpuSkill && x > 120.0 && x < 520.0) {
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
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x2d;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x2d;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x1e) {
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

void CKano::UpdateObjects()
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
            case kObjEruptionHit:
                if (m_objects[v4].frame == 0) {
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
            case kObjShot:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = 3.0;
                }
                if (m_objects[v4].attackResult > 0) {
                    l50.type = 0x193;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    m_shotsOut--;
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].x > 680.0 || m_objects[v4].x < -40.0) {
                    RemoveObject(v4);
                    m_shotsOut--;
                }
                m_objects[v4].vx -= 0.03;
                if (m_objects[v4].vx < 1.5) {
                    m_objects[v4].vx = 1.5;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 6;
                    }
                }
                break;
            case kObjUnusedShotLauncher:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        l50.type = 0x191;
                        l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x28);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjShotHit:
                m_objects[v4].timer++;
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnusedRisingShot:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vx == 0.0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (m_objects[v4].attackResult > 0 || m_objects[v4].y > 0.0) {
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0x10) {
                        if (m_objectVar1[v4] < 4) {
                            m_objects[v4].frame = 0;
                            m_objectVar1[v4]++;
                            break;
                        }
                        m_objects[v4].vx = 3.0;
                        m_objects[v4].vy = 0.8;
                        m_objects[v4].hitsLeft = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case kObjShotBurst:
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
            case kObjChantFront:
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
            case kObjChantBack:
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
            case kObjRefill:
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
            case kObjRemoteHit:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                }
                if (pattern == k6C) {
                    m_attackResult = m_objects[v4].attackResult;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjControlledEruption:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
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
            case kObjIdleBonus:
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objects[v4].vy = -0.2;
                }
                if (m_objects[v4].frame == 1) {
                    m_objects[v4].scale = 1;
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
            case kObjBomb:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_playVoice = 0xa;
                    m_objects[v4].vx = 3.5;
                    m_objects[v4].vy = 2.0;
                }
                if (m_objects[v4].attackResult > 0 && m_objects[v4].attackResult != 6 || m_objects[v4].y > 0.0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjChainBlast;
                    l50.type = 0x1a5;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
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
            case kObjChainBlast:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    if (pattern == k236236B) {
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objectVar1[v4] == 0) {
                        l50.type = 0x1a5;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objectVar1[v4] == 1) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)m_objects[v4].x + facing * 0x32);
                        l50.y = (double)((int)m_objects[v4].y - 0x28);
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objectVar1[v4] == 2) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)m_objects[v4].x - facing * 0x1e);
                        l50.y = (double)((int)m_objects[v4].y - 0x46);
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objectVar1[v4] == 3) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)m_objects[v4].x + facing * 0x14);
                        l50.y = (double)((int)m_objects[v4].y + 0xa);
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objectVar1[v4] == 4) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)m_objects[v4].x - facing * 0xa);
                        l50.y = (double)((int)m_objects[v4].y - 0x14);
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objectVar1[v4] == 5) {
                        l50.type = 0x1a5;
                        l50.x = (double)((int)m_objects[v4].x + facing * 0x1e);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    m_objectVar2[v4] = (WORD)Random(0, 3);
                    if (m_objectVar2[v4] == 0) {
                        m_playVoice = 0xb;
                    }
                    if (m_objectVar2[v4] == 1) {
                        m_playVoice = 0xc;
                    }
                    if (m_objectVar2[v4] == 2) {
                        m_playVoice = 0xd;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar1[v4] < 6) {
                            m_objects[v4].frame = 0;
                            m_objectVar1[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjHomingShotA:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = -2.5;
                    m_objects[v4].vy = -1.5;
                }
                if (m_objects[v4].frame < 0xe) {
                    m_objects[v4].vx += 0.025;
                    if (m_objects[v4].y < (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy += 0.035;
                    }
                    if (m_objects[v4].y > (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy -= 0.035;
                    }
                    if (m_objects[v4].vy < -1.5) {
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objects[v4].vy > 1.5) {
                        m_objects[v4].vy = 1.5;
                    }
                    m_objectVar2[v4]--;
                    if (m_objectVar2[v4] <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        m_objectVar2[v4] = 6;
                    }
                }
                if ((m_objects[v4].attackResult > 0 && m_objects[v4].attackResult != 6 || m_objects[v4].y > 0.0) && m_objects[v4].frame < 0xe) {
                    m_objects[v4].frame = 0xe;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].x < -80.0 || m_objects[v4].x > 720.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjHomingShotB:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = -2.5;
                    m_objects[v4].vy = -1.5;
                }
                if (m_objects[v4].frame < 0xe) {
                    m_objects[v4].vx += 0.025;
                    if (m_objects[v4].y < (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy += 0.035;
                    }
                    if (m_objects[v4].y > (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy -= 0.035;
                    }
                    if (m_objects[v4].vy < -1.5) {
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objects[v4].vy > 1.5) {
                        m_objects[v4].vy = 1.5;
                    }
                    m_objectVar2[v4]--;
                    if (m_objectVar2[v4] <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        m_objectVar2[v4] = 6;
                    }
                }
                if ((m_objects[v4].attackResult > 0 && m_objects[v4].attackResult != 6 || m_objects[v4].y > 0.0) && m_objects[v4].frame < 0xe) {
                    m_objects[v4].frame = 0xe;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].x < -80.0 || m_objects[v4].x > 720.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjHomingShotC:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = -2.5;
                    m_objects[v4].vy = -1.5;
                }
                if (m_objects[v4].frame < 0xe) {
                    m_objects[v4].vx += 0.025;
                    if (m_objects[v4].y < (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy += 0.035;
                    }
                    if (m_objects[v4].y > (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy -= 0.035;
                    }
                    if (m_objects[v4].vy < -1.5) {
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objects[v4].vy > 1.5) {
                        m_objects[v4].vy = 1.5;
                    }
                    m_objectVar2[v4]--;
                    if (m_objectVar2[v4] <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        m_objectVar2[v4] = 6;
                    }
                }
                if ((m_objects[v4].attackResult > 0 && m_objects[v4].attackResult != 6 || m_objects[v4].y > 0.0) && m_objects[v4].frame < 0xe) {
                    m_objects[v4].frame = 0xe;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].x < -80.0 || m_objects[v4].x > 720.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnusedHomingShot:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = -2.5;
                    m_objects[v4].vy = -1.5;
                }
                if (m_objects[v4].frame < 0xe) {
                    m_objects[v4].vx += 0.025;
                    if (m_objects[v4].y < (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy += 0.035;
                    }
                    if (m_objects[v4].y > (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy -= 0.035;
                    }
                    if (m_objects[v4].vy < -1.5) {
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objects[v4].vy > 1.5) {
                        m_objects[v4].vy = 1.5;
                    }
                    m_objectVar2[v4]--;
                    if (m_objectVar2[v4] <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        m_objectVar2[v4] = 6;
                    }
                }
                if ((m_objects[v4].attackResult > 0 && m_objects[v4].attackResult != 6 || m_objects[v4].y > 0.0) && m_objects[v4].frame < 0xe) {
                    m_objects[v4].frame = 0xe;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].x < -80.0 || m_objects[v4].x > 720.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnusedHomingShot2:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = -2.5;
                    m_objects[v4].vy = -1.5;
                }
                if (m_objects[v4].frame < 0xe) {
                    m_objects[v4].vx += 0.025;
                    if (m_objects[v4].y < (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy += 0.035;
                    }
                    if (m_objects[v4].y > (*m_opponent)->y - 50.0) {
                        m_objects[v4].vy -= 0.035;
                    }
                    if (m_objects[v4].vy < -1.5) {
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objects[v4].vy > 1.5) {
                        m_objects[v4].vy = 1.5;
                    }
                    m_objectVar2[v4]--;
                    if (m_objectVar2[v4] <= 0) {
                        l50.type = 0x1a6;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        m_objectVar2[v4] = 6;
                    }
                }
                if ((m_objects[v4].attackResult > 0 && m_objects[v4].attackResult != 6 || m_objects[v4].y > 0.0) && m_objects[v4].frame < 0xe) {
                    m_objects[v4].frame = 0xe;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].x < -80.0 || m_objects[v4].x > 720.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].frame = 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjRushStart:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_playVoice = 7;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].vx += 0.005;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = kObjRush;
                    }
                }
                break;
            case kObjRush:
                if (m_objectVar2[v4] == 0) {
                    m_objects[v4].hitsLeft = 0x63;
                    m_objectVar2[v4]++;
                    m_objects[v4].vx = 4.0;
                    m_playVoice = 8;
                }
                if (m_objects[v4].attackResult > 0 && m_objectVar3[v4] == 0) {
                    m_playVoice = 9;
                    m_objectVar3[v4]++;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    RemoveObject(v4);
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
            case kObjChainBlastHit:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
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
            case kObjHomingTrail:
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
            case kObjBigShot:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 4.0;
                    m_objectVar1[v4]++;
                }
                m_objectVar2[v4]--;
                if ((m_objects[v4].x > 640.0 || m_objects[v4].x < 0.0) && m_objects[v4].attackResult == 0) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].attackResult > 0) {
                    m_objects[v4].vx = 0.5;
                    m_objects[v4].vy = -2.5;
                    m_objectVar2[v4]--;
                    if (m_objectVar1[v4] < 8 && m_objectVar2[v4] <= 0) {
                        l50.type = 0x195;
                        l50.x = (double)((int)m_objects[v4].x + -0x32 + (WORD)Random(0, 0x64));
                        l50.y = (double)((int)m_objects[v4].y + (WORD)Random(0, 0x14));
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        m_objectVar1[v4]++;
                        m_objectVar2[v4] = 0xf;
                    }
                    if (m_objectVar1[v4] > 7) {
                        RemoveObject(v4);
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (m_objects[v4].attackResult == 0) {
                            l50.type = (WORD)Random(0, 4) + 0x1a8;
                            l50.x = (double)((int)m_objects[v4].x + (WORD)Random(0, 0xa));
                            l50.y = (double)((int)m_objects[v4].y + -5 + (WORD)Random(0, 0xa));
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.facing = facing;
                            SpawnObject(&l50);
                        }
                    }
                }
                break;
            case kObjBigShotSpark1:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
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
            case kObjBigShotSpark2:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
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
            case kObjBigShotSpark3:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
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
            case kObjBigShotSpark4:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
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
            case kObjMultiHitShot:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 7;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = 4.5;
                }
                if (m_objects[v4].attackResult > 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_playVoice = 0x10;
                }
                if (m_objects[v4].x > 680.0 || m_objects[v4].x < -40.0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objectVar3[v4] <= 0) {
                        l50.type = 0x195;
                        l50.x = (double)((int)m_objects[v4].x + -0x32 + (WORD)Random(0, 0x64));
                        l50.y = (double)((int)m_objects[v4].y + -0x32 + (WORD)Random(0, 0x64));
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        m_objectVar3[v4] = 2;
                    }
                    m_objectVar3[v4]--;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLingeringBlast:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 5;
                    m_objectVar1[v4]++;
                }
                m_objectVar2[v4]++;
                if (m_objects[v4].hitsLeft == 0 || m_objectVar2[v4] > 0x4b0) {
                    RemoveObject(v4);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 8 || m_objects[v4].frame == 0xe || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x1a) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 8;
                    }
                }
                break;
            case kObjTrapSummon:
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0) {
                    l50.type = 0x1af;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    m_playVoice = 0x13;
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
            case kObjFloorTrap:
                if (m_objects[v4].attackResult > 1 && (m_objects[v4].frame == 0xa || m_objects[v4].frame == 0xb)) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xc;
                    m_objectVar3[v4] = 2;
                    m_objectVar2[v4]++;
                }
                if (m_objects[v4].frame > 9 && m_objects[v4].frame < 0xe) {
                    if (y == 0.0 && m_objects[v4].x + 30.0 > x && m_objects[v4].x - 30.0 < x && m_objectVar3[v4] <= 0) {
                        if (m_objects[v4].frame > 0xb) {
                            m_objects[v4].timer = 0;
                            m_objects[v4].frame = 0xa;
                            break;
                        }
                    } else if (m_objects[v4].frame != 0xc && m_objects[v4].frame != 0xd) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                m_objectVar1[v4]++;
                if ((m_objectVar1[v4] > 0x960 || m_objectVar2[v4] > 9) && m_objects[v4].frame < 0xe) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xe;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar3[v4]--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjSuperShotTrail:
                m_objects[v4].timer++;
                m_objects[v4].hitsLeft = 1;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xe && (WORD)Random(0, 3) < 2) {
                        l50.type = 0x1b1;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)((int)m_objects[v4].y - (WORD)Random(0, 0x96));
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjSuperShotSpark:
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
            case kObjSuperShot:
                if (m_objectVar1[v4] == 0) {
                    m_playVoice = 0x17;
                    m_objects[v4].hitsLeft = 0x63;
                    m_objectVar1[v4] = 1;
                    m_objects[v4].vx = 3.0;
                    m_objects[v4].vy = -1.2;
                }
                if (m_objectVar1[v4] == 1) {
                    m_objects[v4].vy += 0.05;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                        m_objectVar1[v4] = 2;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 1;
                    }
                }
                if (m_objectVar1[v4] == 2) {
                    m_objects[v4].vx += 0.0;
                }
                if (m_objects[v4].x < -40.0 || m_objects[v4].x > 680.0) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1b0;
                    l50.x = (double)((int)m_objects[v4].x + (WORD)Random(0, 0x28));
                    l50.y = (double)((int)m_objects[v4].y + (WORD)Random(0, 0x14));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].attackResult = 0;
                }
                break;
            case kObjAimedShot70:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].SetVelocity(70.0, 3.0);
                }
                if (m_objects[v4].attackResult > 0 || m_objects[v4].y > 0.0 || pattern > kLastFreeAction && pattern < kFirstGuard) {
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_orbsOut--;
                    break;
                }
                if (m_objects[v4].x > 680.0 || m_objects[v4].x < -40.0) {
                    RemoveObject(v4);
                    m_orbsOut--;
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
            case kObjAimedShot55:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].SetVelocity(55.0, 3.0);
                }
                if (m_objects[v4].attackResult > 0 || m_objects[v4].y > 0.0 || pattern > kLastFreeAction && pattern < kFirstGuard) {
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_orbsOut--;
                    break;
                }
                if (m_objects[v4].x > 680.0 || m_objects[v4].x < -40.0) {
                    RemoveObject(v4);
                    m_orbsOut--;
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
            case kObjAimedShot40:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].SetVelocity(40.0, 3.0);
                }
                if (m_objects[v4].attackResult > 0 || m_objects[v4].y > 0.0 || pattern > kLastFreeAction && pattern < kFirstGuard) {
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_orbsOut--;
                    break;
                }
                if (m_objects[v4].x > 680.0 || m_objects[v4].x < -40.0) {
                    RemoveObject(v4);
                    m_orbsOut--;
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
            case kObjAimedShot25:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].SetVelocity(25.0, 3.0);
                }
                if (m_objects[v4].attackResult > 0 || m_objects[v4].y > 0.0 || pattern > kLastFreeAction && pattern < kFirstGuard) {
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_orbsOut--;
                    break;
                }
                if (m_objects[v4].x > 680.0 || m_objects[v4].x < -40.0) {
                    RemoveObject(v4);
                    m_orbsOut--;
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
            case kObjAimedShot10:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].SetVelocity(10.0, 3.0);
                }
                if (m_objects[v4].attackResult > 0 || m_objects[v4].y > 0.0 || pattern > kLastFreeAction && pattern < kFirstGuard) {
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_orbsOut--;
                    break;
                }
                if (m_objects[v4].x > 680.0 || m_objects[v4].x < -40.0) {
                    RemoveObject(v4);
                    m_orbsOut--;
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
            case kObjOrbA:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vx == 0.0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_orbsOut--;
                    break;
                }
                if (m_objectVar1[v4] > 2 && m_objects[v4].timer == 0) {
                    if (m_objects[v4].facing == 1) {
                        l50.type = 0x1b3;
                        if (m_objects[v4].x > (*m_opponent)->x) {
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (m_objects[v4].x < (*m_opponent)->x) {
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    if (m_objects[v4].facing == -1) {
                        l50.type = 0x1b3;
                        if (m_objects[v4].x > (*m_opponent)->x) {
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (m_objects[v4].x > (*m_opponent)->x) {
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
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
                        m_objectVar1[v4]++;
                    }
                }
                break;
            case kObjOrbB:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vx == 0.0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_orbsOut--;
                    break;
                }
                if (m_objectVar1[v4] > 2 && m_objectVar3[v4] > 0xf) {
                    if (m_objects[v4].facing == 1) {
                        l50.type = 0x1b3;
                        if (m_objects[v4].x > (*m_opponent)->x) {
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (m_objects[v4].x < (*m_opponent)->x) {
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    if (m_objects[v4].facing == -1) {
                        l50.type = 0x1b3;
                        if (m_objects[v4].x > (*m_opponent)->x) {
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (m_objects[v4].x > (*m_opponent)->x) {
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    l50.keep = 1;
                    SpawnObject(&l50);
                    m_orbsOut++;
                    if (m_objectVar2[v4] == 2) {
                        RemoveObject(v4);
                        m_orbsOut--;
                    }
                    m_objectVar2[v4]++;
                    m_objectVar3[v4] = 0;
                    break;
                }
                m_objectVar3[v4]++;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objectVar1[v4]++;
                    }
                }
                break;
            case kObjOrbC:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vy = -3.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vx == 0.0) {
                    m_objects[v4].vy += 0.045;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    l50.type = 0x195;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    m_orbsOut--;
                    break;
                }
                if (m_objectVar1[v4] > 2 && m_objectVar3[v4] > 0xf) {
                    if (m_objects[v4].facing == 1) {
                        l50.type = 0x1b3;
                        if (m_objects[v4].x > (*m_opponent)->x) {
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (m_objects[v4].x < (*m_opponent)->x) {
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 70.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 55.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 40.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) < 25.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    if (m_objects[v4].facing == -1) {
                        l50.type = 0x1b3;
                        if (m_objects[v4].x > (*m_opponent)->x) {
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                        if (m_objects[v4].x > (*m_opponent)->x) {
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 110.0) {
                                l50.type = 0x1b4;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 125.0) {
                                l50.type = 0x1b5;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 140.0) {
                                l50.type = 0x1b6;
                            }
                            if (AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - m_objects[v4].y) > 165.0) {
                                l50.type = 0x1b7;
                            }
                        }
                    }
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    l50.keep = 1;
                    SpawnObject(&l50);
                    m_orbsOut++;
                    if (m_objectVar2[v4] == 4) {
                        RemoveObject(v4);
                        m_orbsOut--;
                    }
                    m_objectVar2[v4]++;
                    m_objectVar3[v4] = 0;
                    break;
                }
                m_objectVar3[v4]++;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objectVar1[v4]++;
                    }
                }
                break;
            case kObjEruptionA:
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x190;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    RemoveObject(v4);
                    m_eruptionsOut--;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar1[v4] < 0) {
                            m_objects[v4].frame--;
                            m_objectVar1[v4]++;
                            break;
                        }
                        RemoveObject(v4);
                        m_eruptionsOut--;
                    }
                }
                break;
            case kObjEruptionC:
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x190;
                    l50.x = (double)((int)m_objects[v4].x + (m_objectVar1[v4] * 0x19 - 0x32) * m_objects[v4].facing);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    RemoveObject(v4);
                    m_eruptionsOut--;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar1[v4] < 4) {
                            m_objects[v4].frame--;
                            m_objectVar1[v4]++;
                            break;
                        }
                        RemoveObject(v4);
                        m_eruptionsOut--;
                    }
                }
                break;
            case kObjEruptionB:
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x190;
                    l50.x = (double)((int)m_objects[v4].x + (m_objectVar1[v4] - 1) * 0x19 * m_objects[v4].facing);
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    RemoveObject(v4);
                    m_eruptionsOut--;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar1[v4] < 2) {
                            m_objects[v4].frame--;
                            m_objectVar1[v4]++;
                            break;
                        }
                        RemoveObject(v4);
                        m_eruptionsOut--;
                    }
                }
                break;
            case kObjPillar:
                if (m_objects[v4].timer == 0 && m_objects[v4].frame == 0) {
                    ShakeScreen(0xa, 0xa);
                    m_playVoice = 0x14;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame > 8 && m_objects[v4].frame < 0xb && m_objectVar1[v4] < 6 && m_objectVar2[v4] <= 0) {
                    l50.type = 0x1c0;
                    l50.x = (double)((int)m_objects[v4].x + -0x50 + (WORD)Random(0, 0xa0));
                    l50.y = (double)((int)m_objects[v4].y + 0xf - (WORD)Random(0, 0x1e));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1bf;
                    SpawnObject(&l50);
                    m_objectVar2[v4] = 0x2d;
                    m_objectVar1[v4]++;
                    ShakeScreen(5, 5);
                    m_playVoice = 0x15;
                }
                m_objectVar2[v4]--;
                m_objects[v4].x = x;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xb && frame == 0xd) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjImpactFlash:
                m_objects[v4].x = x;
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
            case kObjPillarDebris:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2) {
                        l50.type = 0x1c6;
                        l50.x = (double)(int)x;
                        l50.y = 0.0;
                        l50.scale = 2;
                        l50.layer = 0;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjPillarStart:
                if (m_objects[v4].timer == 0 && m_objects[v4].frame == 0) {
                    m_playVoice = 0x16;
                }
                if (m_objects[v4].frame == 0xe && m_objects[v4].timer == 0) {
                    l50.type = 0x1be;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                    l50.type = 0x1bf;
                    SpawnObject(&l50);
                    m_objectVar2[v4] = 0x2d;
                    m_objectVar1[v4]++;
                    ShakeScreen(5, 5);
                }
                m_objects[v4].x = x;
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
            case kObjMeteorLaunch:
                if (m_objectVar1[v4] == 0) {
                    m_playVoice = 0x17;
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = 6.0;
                    m_objects[v4].vy = -6.0;
                }
                if (m_objects[v4].y < -1600.0) {
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
            case kObjMeteor:
                if (m_objectVar1[v4] == 0) {
                    m_playVoice = 0x18;
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].SetVelocity(60.0, 4.0);
                }
                if (m_objects[v4].y > 0.0) {
                    l50.type = 0x1bf;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    l50.scale = 2;
                    l50.layer = 0;
                    l50.facing = *(char*)&m_meteorFacing;
                    SpawnObject(&l50);
                    l50.type = 0x1c4;
                    l50.layer = 1;
                    l50.facing = *(char*)&m_meteorFacing;
                    SpawnObject(&l50);
                    l50.type = 0x1c5;
                    l50.layer = 1;
                    l50.facing = *(char*)&m_meteorFacing;
                    SpawnObject(&l50);
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
            case kObjMeteorCrater:
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
            case kObjMeteorBlast:
                if (m_objects[v4].timer == 0 && m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 0x19;
                    ShakeScreen(0xa, 0);
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
            case kObjPillarDebrisHit:
                if (m_objects[v4].timer == 0 && m_objects[v4].frame == 0) {
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
            case kObjControlledCharge:
                if (m_holdA == 0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].frame = 0xf;
                    m_objects[v4].timer = 0;
                    m_playVoice = 0x1c;
                    m_playVoice = 6;
                }
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame < 0xf) {
                    m_objects[v4].vx += 0.0025;
                } else {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 0xf && m_objects[v4].timer == 0) {
                    l50.type = 0x19a;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = 0.0;
                    if (m_objectVar1[v4] == 1) {
                        l50.x = m_objects[v4].x - facing * 0x2d;
                    }
                    if (m_objectVar1[v4] == 2) {
                        l50.x = m_objects[v4].x + facing * 0x2d;
                    }
                    if (m_objectVar1[v4] == 3) {
                        l50.x = m_objects[v4].x - facing * 0x5a;
                    }
                    if (m_objectVar1[v4] == 4) {
                        l50.x = m_objects[v4].x + facing * 0x5a;
                    }
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar1[v4] < 2) {
                            m_objects[v4].frame--;
                            m_objectVar1[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjLv4Finish:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                        l50.type = 0x34;
                        l50.y = -87.0;
                        l50.x = (double)(int)(facing * 0x1f + x);
                        l50.scale = 2;
                        l50.layer = 1;
                        m_game->CreateEffect((EffectDesc*)&l50);
                        (*m_opponent)->pattern = kThrownStandLow;
                        (*m_opponent)->m_hitstop = 0x270f;
                        m_playVoice = 0x1c;
                        DealDamage(0x1388, 850.0);
                        m_patternVar1 = 1;
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
