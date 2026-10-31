// CNagamori (0x4add90-0x4c04af).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNagamori::CNagamori(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "nagamori");
    lastSurface = 0x2d7;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_shotState = 0;
    m_encasedBreakOut = 0;
    m_keepBombs = 0;
    m_lv4Time = 0;
    unk3158 = 0;
    m_bombsPlaced = 0;
    unk315c = 0;
    m_bouncerDrops = 0;
    m_bouncerOut = 0;
    m_pointX[0] = -2;
    m_pointY[0] = -0x3d;
    m_pointX[1] = 0x15;
    m_pointY[1] = 0;
    m_pointX[2] = 0xc;
    m_pointY[2] = -5;
    m_pointX[3] = 0x16;
    m_pointY[3] = -0x12;
    m_pointX[4] = 0x19;
    m_pointY[4] = -0x17;
    m_resultPictures = 5;
    m_rivals[0] = 0;
    m_rivals[1] = 5;
    m_rivals[2] = 0xa;
    m_rivals[3] = 1;
    m_rivals[0xa] = 6;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectTriggered[v4] = 0;
        m_objectState[v4] = 0;
        m_objectTimer[v4] = 0;
        m_objectPhase[v4] = 0;
    }
}

void CNagamori::Reset()
{
    int v4;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_shotState = 0;
    m_encasedBreakOut = 0;
    m_keepBombs = 0;
    m_lv4Time = 0;
    unk3158 = 0;
    m_bombsPlaced = 0;
    unk315c = 0;
    m_bouncerDrops = 0;
    m_bouncerOut = 0;
    m_pointX[0] = -2;
    m_pointY[0] = -0x3d;
    m_pointX[1] = 0x15;
    m_pointY[1] = 0;
    m_pointX[2] = 0xc;
    m_pointY[2] = -5;
    m_pointX[3] = 0x16;
    m_pointY[3] = -0x12;
    m_pointX[4] = 0x19;
    m_pointY[4] = -0x17;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectTriggered[v4] = 0;
        m_objectState[v4] = 0;
        m_objectTimer[v4] = 0;
        m_objectPhase[v4] = 0;
    }
    CPlayer::Reset();
}

void CNagamori::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CNagamori::RemoveObject(short p1)
{
    m_objectTriggered[p1] = 0;
    m_objectState[p1] = 0;
    m_objectTimer[p1] = 0;
    m_objectPhase[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CNagamori::TriggerObjectsNear(short p1, short p2, short p3, short p4)
{
    int v4;

    v4 = m_objectTail;
    while (v4 != m_objectHead) {
        if (m_objectActive[v4] != 0 && fabs(p1 - m_objects[v4].x) < p3 && fabs(p2 - m_objects[v4].y) < p4) {
            m_objectTriggered[v4] = 1;
        }
        v4++;
        if (v4 >= 0x40) {
            v4 = 0;
        }
    }
}

void CNagamori::Move()
{
    MoveOnGround();
}

void CNagamori::StartCommand()
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
    if (m_command == kCmd22C && (m_rfGauge >= 500.0 && m_attackResult > 1 && m_attackResult != 6 || m_rfBlue > 0 && m_attackResult > 1) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_lv4Time == 0 && m_patterns[pattern].cancelLevel <= m_patterns[kInstantCharge].level) {
        StartPattern();
        ClearBufferedPress();
        pattern = kInstantCharge;
        if (y < 0.0) {
            pattern = kAirInstantCharge;
        }
        return;
    }
    if (m_sealLevel < 2) {
        if (m_hp < 0xd05 && m_command == kCmd6BA65A && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_attackResult != 6 && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd641236C && m_gauge >= 0xbb8 && m_shotState == 0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k6413Lv3].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k6413Lv3;
            return;
        }
        if ((m_command == kCmd641236B || m_command == kCmd641236C) && m_shotState == 0 && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k6413Lv2].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k6413Lv2;
            return;
        }
        if ((m_command == kCmd641236A || m_command == kCmd641236B || m_command == kCmd641236C) && m_shotState == 0 && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k6413Lv1].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k6413Lv1;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_bouncerOut == 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214C;
            if (y < 0.0) {
                pattern = kAir214214C;
            }
            return;
        }
        if (m_command == kCmd214214B && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214B;
            if (y < 0.0) {
                pattern = kAir214214B;
            }
            return;
        }
        if (m_command == kCmd214214A && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214A;
            if (y < 0.0) {
                pattern = kAir214214A;
            }
            return;
        }
        if (m_command == kCmd236236C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236236Lv3].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236Lv3;
            return;
        }
        if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236236Lv2].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236Lv2;
            return;
        }
        if ((m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236236Lv1].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236Lv1;
            return;
        }
        if (m_command == kCmd412C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k412C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412C;
            return;
        }
        if ((m_command == kCmd412B || m_command == kCmd412C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k412B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412B;
            return;
        }
        if (m_command == kCmd412A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k412A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412A;
            return;
        }
        if (m_command == kCmd623C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k623C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623C;
            return;
        }
        if ((m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k623B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623B;
            return;
        }
        if (m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
            return;
        }
        if (m_command == kCmd214C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_gauge > 0x32 && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            if (y < 0.0) {
                pattern = kAir214C;
            }
            return;
        }
        if (m_command == kCmd214B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_gauge > 0x32 && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            if (y < 0.0) {
                pattern = kAir214B;
            }
            return;
        }
        if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_gauge > 0x32 && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            if (y < 0.0) {
                pattern = kAir214A;
            }
            return;
        }
        if (m_command == kCmd236C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_shotState == 0 && m_gauge > 0x32 && m_patterns[pattern].cancelLevel <= m_patterns[kAir236C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236C;
            return;
        }
        if (m_command == kCmd236B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_shotState == 0 && m_gauge > 0x32 && m_patterns[pattern].cancelLevel <= m_patterns[kAir236B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236B;
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_shotState == 0 && m_gauge > 0x32 && m_patterns[pattern].cancelLevel <= m_patterns[kAir236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236A;
            return;
        }
        if (m_command == kCmd236C && m_shotState == 0 && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k236C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            return;
        }
        if (m_command == kCmd236C && m_shotState != 0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k236CShotForward].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236CShotForward;
            return;
        }
        if ((m_command == kCmd236B || m_command == kCmd236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k236B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236B;
            if (m_shotState != 0) {
                pattern = k236BShotDown;
            }
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236A;
            if (m_shotState != 0) {
                pattern = k236AShotUp;
            }
            return;
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
            if (m_patterns[pattern].cancelLevel <= m_patterns[k6B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing) {
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
            if (m_shotState > 0) {
                pattern = k2CShotOut;
            }
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

void CNagamori::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (m_lv4Time > 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_lv4Time > 0) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, m_lv4Time * x1c.width / 0x4b0, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, m_lv4Time * x1c.width / 0x4b0, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - m_lv4Time * x1c.width / 0x4b0, 0x1f - x1c.y, m_lv4Time * x1c.width / 0x4b0, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CNagamori::PreUpdate()
{
    if (unk315c > 0) {
        unk315c--;
    }
}

void CNagamori::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CNagamori::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = kCmdNone;
    x6 = 0;
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xe0) != 0 && x6 == 5) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 5) {
            m_command = kCmd6BA65A;
            return;
        }
        if (v5 == 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xe0) != 0 && x6 == 2) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 2) {
            x6 = 3;
        }
        if ((v5 & 0xd0) != 0 && x6 == 1) {
            break;
        }
        if ((v5 & 0x20) != 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0 && m_gauge == 0xbb8 && y == 0.0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x64;
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
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 0) {
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
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge >= 0x3e8 && y == 0.0) {
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

void CNagamori::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == 0x108 && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 40.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 > 40.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f + ((m_rfGauge > 500.0) << 1)) {
                m_command = 0x48;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f + ((m_rfGauge > 500.0) << 1)) {
                m_command = ((WORD)Random(0, 1) == 1) * 2 + kCmd623A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && v10 < 60.0 && m_gauge >= 0x7d0) {
                m_command = kCmd236236B;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && v10 < 150.0 && m_gauge == 0xbb8) {
                m_command = kCmd236236C;
                return;
            }
        }
        if (v10 < 160.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (v10 < 220.0 && v10 > 160.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
            m_command = (WORD)Random(0, 2) + 0x46;
            return;
        }
        if (v10 > 220.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
            m_command = (WORD)Random(0, 2) + kCmd236A;
            return;
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
        if (m_cpuRoll < 3 && m_rfGauge > 500.0) {
            m_command = 0x48;
            return;
        }
        if (m_cpuRoll < 7 && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 0xa && m_rfGauge > 500.0) {
            m_command = kCmd623A;
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
        if (m_cpuRoll < 0x14) {
            m_cpuAction = 2;
            return;
        }
        if (v10 < 100.0 && m_cpuRoll < 0x16) {
            m_command = kCmd623C;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k623A || pattern == k623B || pattern == k623C || pattern == k412A || pattern == k412B || pattern == k412C)) {
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
            if (v10 < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1b8 && m_attackResult == 2) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
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
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_command = kCmd214B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x258 && v10 < 100.0) {
                m_pressC = 1;
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
                    if (v10 > 110.0) {
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
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_command = kCmd214B;
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
            if (m_cpuRoll > 0x1f3 && m_cpuRoll < 0x226) {
                m_command = (((WORD)Random(0, 2) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x225 && m_cpuRoll < 0x2a8) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
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
                    if (v10 > 110.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
            }
        }
        if (pattern == k5C) {
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
            if (m_cpuRoll > 0xfa && m_cpuRoll < 0x15e && v10 < 120.0 && m_rfGauge > 500.0) {
                m_command = 0x48;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1ae && m_attackResult == 3 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
            if (m_cpuRoll > 0x1ae && m_cpuRoll < 0x21c) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x21c && m_cpuRoll < 0x23a && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
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
            if (v10 < 40.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
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
                    m_cpuAction = 5;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140) {
                m_command = kCmd214B;
                return;
            }
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
            if (m_cpuRoll > 0 && m_cpuRoll < 0x96) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x96 && m_cpuRoll < 0x15e && v10 < 90.0 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1c2 && m_attackResult == 3 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x280) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x280 && m_cpuRoll < 0x2bc && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
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
            if (m_cpuRoll < 0x14 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 0x14 && m_cpuRoll < 0x3c && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0x3c && m_cpuRoll < 0x50 && m_gauge >= 0x3e8 && (*m_opponent)->y < 0.0) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
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
            if (m_cpuRoll < 0x14 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 0x14 && m_cpuRoll < 0x5a && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd214B;
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
            if (m_cpuRoll > 0xfa && m_cpuRoll < 0x15e && v10 < 120.0 && m_rfGauge > 500.0) {
                m_command = 0x48;
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
            if (m_cpuRoll > 0x2bc && m_cpuRoll < 0x2da && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if (m_cpuRoll > 0x289 && (WORD)Random(0, 3) == 0) {
                m_cpuAction = 6;
                if (v10 > 110.0) {
                    m_cpuAction = 8;
                }
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
                if (v10 < 55.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 70.0 && m_cpuRoll < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 100.0 && v10 > 70.0 && m_cpuRoll < 0xf) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 120.0 && m_cpuRoll < 0x14) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 120.0 && m_cpuRoll < 0x1e) {
                    m_cpuAction = 8;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x25 && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kAirRecoveryForward) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 90.0 && v10 > 60.0 && m_cpuRoll < 0x25) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 100.0 && v10 > 70.0 && m_cpuRoll < 0x28) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x2a && m_cpuRoll > 0x28) {
                    m_command = kCmd623A;
                    return;
                }
                if (m_cpuRoll < 0x2a && m_cpuRoll > 0x32) {
                    m_command = facing;
                    m_cpuAction = 5;
                    return;
                }
                if ((WORD)Random(0, 0x140) < v10 - 70.0 && vy > 0.0 && (*m_opponent)->y > y && m_cpuRoll > 0xeb && m_cpuRoll < 0xfa) {
                    m_command = (WORD)Random(0, 2) + kCmd214A;
                    return;
                }
                if (v10 > 180.0 && m_cpuRoll > 0xfa && m_cpuRoll < 0xfc && m_gauge >= 0x3e8) {
                    m_command = (WORD)Random(0, 2) + kCmd214214A;
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
                    if (v10 < 80.0 && m_cpuRoll < 0xf) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0x11) {
                        m_command = kCmd623B;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 80.0 && x8 < 120.0) {
                        if (m_cpuRoll < (m_rfGauge > 500.0 || m_rfBlue > 0) * 5 + 6) {
                            m_command = kCmd623B;
                            return;
                        }
                    }
                    if (v10 < 90.0 && x8 < 120.0 && x8 > 90.0 && m_cpuRoll < 0xf) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 120.0 && x8 < 100.0 && m_cpuRoll < 0x11 && m_gauge >= 0x7d0) {
                        m_command = (WORD)Random(0, 1) + kCmd236236B;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 70.0 && x8 < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->y == 0.0) * 0x64 + 0x64) {
                        m_pressA = 1;
                        return;
                    }
                }
                if (v10 < 120.0 && x8 > 50.0 && x8 < 60.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x104) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 130.0 && x8 > 40.0 && x8 < 80.0 && m_cpuRoll > 0x104 && m_cpuRoll < 0x109) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 0x140) < v10 - 70.0 && m_cpuRoll > 0x10e && m_cpuRoll < 0x15e) {
                    m_command = (WORD)Random(0, 2) + kCmd214A;
                    return;
                }
                if (v10 > 180.0 && m_cpuRoll > 0x15e && m_cpuRoll < 0x160 && m_gauge >= 0x3e8) {
                    m_command = (WORD)Random(0, 2) + kCmd214214A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 80.0 && (*m_opponent)->y < y) {
                    if (m_cpuRoll < (m_rfGauge > 500.0 || m_rfBlue > 0) * 0x14 + 6) {
                        m_command = kCmd623A;
                        return;
                    }
                }
                if (v10 < 140.0 && x8 > 90.0 && m_cpuRoll < 0x6e) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 150.0 && x8 < 90.0 && m_cpuRoll < 0xc8) {
                    m_pressC = 1;
                    return;
                }
                if (v10 > 180.0 && m_cpuRoll > 0xeb && m_cpuRoll < 0xfa) {
                    m_command = (WORD)Random(0, 2) + kCmd214A;
                    return;
                }
                if (v10 > 180.0 && m_cpuRoll > 0xfa && m_cpuRoll < 0xfc && m_gauge >= 0x3e8) {
                    m_command = (WORD)Random(0, 2) + kCmd214214A;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 3.0f * m_cpuSkill) {
        m_command = facing == 1;
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
        if (v10 > 160.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 100.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
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
    if ((WORD)Random(0, 0x64) < 0x32 && v10 < 100.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x1e;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x1e;
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

void CNagamori::UpdateObjects()
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
            case kObjBomb:
                if (m_objectPhase[v4] == 0) {
                    m_objectPhase[v4] = unk3158 + 0xa;
                }
                if (m_objects[v4].ay == 0.0) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy > 0.7) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy < -0.7) {
                    m_objects[v4].ay = 0.015;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objectTriggered[v4] == 1 && m_objectTimer[v4] <= 0) {
                    l50.keep = 0;
                    l50.type = kObjExplosion;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectTriggered[v4] = 0;
                    m_objectTimer[v4] = 0x78;
                    if (m_keepBombs == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                m_objectTriggered[v4] = 0;
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectState[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            m_objectState[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjBouncer:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.75;
                    m_objects[v4].vy = -2.5;
                    m_bouncerDrops = 0;
                    m_bouncerOut = 1;
                }
                m_objects[v4].vy += 0.045;
                if (m_objects[v4].vy + m_objects[v4].y >= 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                    m_objects[v4].y = 0.0;
                }
                if (m_objects[v4].timer == 0 && m_objectPhase[v4] >= 0x14) {
                    l50.keep = 0;
                    l50.type = kObjBouncerDrop;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    m_objectPhase[v4] = 0;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].x > 680.0 || m_objects[v4].x < -40.0) {
                    RemoveObject(v4);
                    m_bouncerOut = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objectPhase[v4]++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 9;
                    }
                }
                break;
            case kObjSuperBomb:
                m_objectTimer[v4]--;
                if (m_objects[v4].ay == 0.0) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy > 0.7) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy < -0.7) {
                    m_objects[v4].ay = 0.015;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objectTriggered[v4] == 1 && m_objectTimer[v4] <= 0) {
                    l50.keep = 0;
                    l50.type = kObjExplosion;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectTriggered[v4] = 0;
                    m_objectTimer[v4] = 0x78;
                    break;
                }
                m_objectTriggered[v4] = 0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectState[v4] < 0xc) {
                            m_objects[v4].frame = 0;
                            m_objectState[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjSuperBombBig:
                if (m_objectPhase[v4] == 0) {
                    m_objectPhase[v4] = unk3158 + 0xa;
                }
                if (m_objects[v4].ay == 0.0) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy > 0.7) {
                    m_objects[v4].ay = -0.015;
                }
                if (m_objects[v4].vy < -0.7) {
                    m_objects[v4].ay = 0.015;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objectTriggered[v4] == 1 && m_objectTimer[v4] <= 0) {
                    l50.keep = 0;
                    l50.type = kObjExplosionBig;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectTriggered[v4] = 0;
                    m_objectTimer[v4] = 0x78;
                    if (m_keepBombs == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                m_objectTriggered[v4] = 0;
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectState[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            m_objectState[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObj2CFx:
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
            case kObjExplosion:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_playVoice = 1;
                }
                if (m_objects[v4].frame == 0xe && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    TriggerObjectsNear((int)m_objects[v4].x, (int)m_objects[v4].y, 0x5a, 0x5a);
                    m_objectTriggered[v4] = 0;
                }
                if (m_objects[v4].attackResult == 3) {
                    m_objectState[v4] = (int)AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y - 50.0);
                    (*m_opponent)->SetVelocity((double)m_objectState[v4], 2.2);
                    if ((*m_opponent)->facing == 1) {
                        (*m_opponent)->vx *= -1.0;
                    }
                    m_objects[v4].attackResult = 1;
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
            case kObjBombB:
                if (m_objectPhase[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objectPhase[v4] == 0) {
                    m_objects[v4].vx = 1.8;
                    m_objectPhase[v4] = 1;
                }
                if (m_objectPhase[v4] == 1) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                }
                if (m_objectTriggered[v4] == 1 && m_objectTimer[v4] <= 0 && m_objectPhase[v4] == 2) {
                    l50.keep = 0;
                    l50.type = kObjExplosion;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectTriggered[v4] = 0;
                    m_objectTimer[v4] = 0x78;
                    if (m_keepBombs == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                m_objectTriggered[v4] = 0;
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectState[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            m_objectState[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjBombC:
                if (m_objectPhase[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objectPhase[v4] == 0) {
                    m_objects[v4].vx = 1.8;
                    m_objects[v4].vy = -1.8;
                    m_objectPhase[v4] = 1;
                }
                if (m_objectPhase[v4] == 1) {
                    m_objects[v4].vx -= 0.015;
                    m_objects[v4].vy += 0.015;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                }
                if (m_objectTriggered[v4] == 1 && m_objectTimer[v4] <= 0 && m_objectPhase[v4] == 2) {
                    l50.keep = 0;
                    l50.type = kObjExplosion;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectTriggered[v4] = 0;
                    m_objectTimer[v4] = 0x78;
                    if (m_keepBombs == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                m_objectTriggered[v4] = 0;
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectState[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            m_objectState[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjBombAirC:
                if (m_objectPhase[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objectPhase[v4] == 0) {
                    m_objects[v4].vx = 1.8;
                    m_objects[v4].vy = 1.8;
                    m_objectPhase[v4] = 1;
                }
                if (m_objectPhase[v4] == 1) {
                    m_objects[v4].vx -= 0.015;
                    m_objects[v4].vy -= 0.015;
                    if (m_objects[v4].y > -10.0) {
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                }
                if (m_objectTriggered[v4] == 1 && m_objectTimer[v4] <= 0 && m_objectPhase[v4] == 2) {
                    l50.keep = 0;
                    l50.type = kObjExplosion;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectTriggered[v4] = 0;
                    m_objectTimer[v4] = 0x78;
                    if (m_keepBombs == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                m_objectTriggered[v4] = 0;
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectState[v4] < 0x10) {
                            m_objects[v4].frame = 0;
                            m_objectState[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjBombRise:
                if (m_objectPhase[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objectPhase[v4] == 0) {
                    m_objects[v4].vy = -1.2;
                    m_objectPhase[v4] = 1;
                }
                if (m_objectPhase[v4] == 1) {
                    m_objects[v4].vy += 0.015;
                    if (m_objects[v4].y > -10.0) {
                        m_objects[v4].vy = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                }
                if (m_objectTriggered[v4] == 1 && m_objectTimer[v4] <= 0 && m_objectPhase[v4] == 2) {
                    l50.keep = 0;
                    l50.type = kObjExplosion;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectTriggered[v4] = 0;
                    m_objectTimer[v4] = 0x78;
                    if (m_keepBombs == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                m_objectTriggered[v4] = 0;
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectState[v4] < 0xa) {
                            m_objects[v4].frame = 0;
                            m_objectState[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjBouncerDrop:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_playVoice = 1;
                }
                if (m_objects[v4].frame == 6 && m_objects[v4].timer == 0) {
                    m_bouncerDrops++;
                    if (m_bouncerDrops > 2) {
                        m_bouncerDrops = 0;
                    }
                    l50.keep = 0;
                    l50.type = kObjBombFwd;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    l50.type = kObjBombBack;
                    SpawnObject(&l50);
                    l50.type = kObjBombRise;
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
            case kObjShotA:
                TriggerObjectsNear((int)m_objects[v4].x, (int)m_objects[v4].y, 0x1e, 0x1e);
                if (m_shotOrder == 1) {
                    m_objects[v4].vy -= 2.5;
                    if (m_objectState[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == -1) {
                    m_objects[v4].vy += 2.5;
                    if (m_objectState[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == 2) {
                    m_shotState = 1;
                    m_objectState[v4] = 1;
                    m_objects[v4].vx = 3.0;
                    if (facing != m_objects[v4].facing) {
                        m_objects[v4].facing = facing;
                    }
                    m_shotOrder = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectState[v4] == 0) {
                    m_objects[v4].vx = 4.2;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].hitsLeft = 1;
                    m_objectState[v4] = 1;
                }
                if (m_objectState[v4] == 1) {
                    m_objects[v4].vx -= 0.045;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].vx == 0.0 && m_objectState[v4] == 1) {
                    m_objectState[v4] = 2;
                    m_shotState = 2;
                    m_objects[v4].hitsLeft = 0;
                }
                if (m_objectState[v4] >= 2) {
                    if (m_objects[v4].y < y - 50.0) {
                        m_objects[v4].vy += 0.06;
                    }
                    if (m_objects[v4].y > y - 70.0) {
                        m_objects[v4].vy -= 0.06;
                    }
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx += m_objects[v4].facing * 0.04;
                    }
                    if (m_objects[v4].x > x) {
                        m_objects[v4].vx = m_objects[v4].vx - m_objects[v4].facing * 0.04;
                    }
                    if (m_objects[v4].vy < -2.0) {
                        m_objects[v4].vy = -2.0;
                    } else if (m_objects[v4].vy > 2.0) {
                        m_objects[v4].vy = 2.0;
                    }
                    if (m_objects[v4].vx < -2.0) {
                        m_objects[v4].vx = -2.0;
                    } else if (m_objects[v4].vx > 2.0) {
                        m_objects[v4].vx = 2.0;
                    }
                    if (m_objects[v4].y > y - 70.0 && m_objects[v4].y < y - 20.0 && m_objects[v4].x > x - 10.0 && m_objects[v4].x < x + 10.0 && m_shotState >= 2) {
                        RemoveObject(v4);
                        m_shotState = 0;
                        m_playSound = 0x1a;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case kObjShotB:
                TriggerObjectsNear((int)m_objects[v4].x, (int)m_objects[v4].y, 0x1e, 0x1e);
                if (m_shotOrder == 1) {
                    m_objects[v4].vy -= 2.5;
                    if (m_objectState[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == -1) {
                    m_objects[v4].vy += 2.5;
                    if (m_objectState[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == 2) {
                    m_shotState = 1;
                    m_objectState[v4] = 1;
                    m_objects[v4].vx = 3.0;
                    if (facing != m_objects[v4].facing) {
                        m_objects[v4].facing = facing;
                    }
                    m_shotOrder = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectState[v4] == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -2.3;
                    m_objects[v4].hitsLeft = 1;
                    m_objectState[v4] = 1;
                }
                if (m_objectState[v4] == 1) {
                    m_objects[v4].vx -= 0.03;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].vx == 0.0 && m_objectState[v4] == 1) {
                    m_objectState[v4] = 2;
                    m_shotState = 2;
                    m_objects[v4].hitsLeft = 0;
                }
                if (m_objectState[v4] >= 2) {
                    if (m_objects[v4].y < y - 50.0) {
                        m_objects[v4].vy += 0.06;
                    }
                    if (m_objects[v4].y > y - 70.0) {
                        m_objects[v4].vy -= 0.06;
                    }
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx += m_objects[v4].facing * 0.06;
                    }
                    if (m_objects[v4].x > x) {
                        m_objects[v4].vx = m_objects[v4].vx - m_objects[v4].facing * 0.06;
                    }
                    if (m_objects[v4].vy < -2.0) {
                        m_objects[v4].vy = -2.0;
                    } else if (m_objects[v4].vy > 2.0) {
                        m_objects[v4].vy = 2.0;
                    }
                    if (m_objects[v4].vx < -2.0) {
                        m_objects[v4].vx = -2.0;
                    } else if (m_objects[v4].vx > 2.0) {
                        m_objects[v4].vx = 2.0;
                    }
                    if (m_objects[v4].y > y - 70.0 && m_objects[v4].y < y - 20.0 && m_objects[v4].x > x - 10.0 && m_objects[v4].x < x + 10.0 && m_shotState >= 2) {
                        RemoveObject(v4);
                        m_shotState = 0;
                        m_playSound = 0x1a;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case kObjShotC:
                if (m_shotOrder == 1) {
                    m_objects[v4].vy -= 2.5;
                    if (m_objectState[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == -1) {
                    m_objects[v4].vy += 2.5;
                    if (m_objectState[v4] > 1) {
                        m_objects[v4].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == 2) {
                    m_shotState = 1;
                    m_objectState[v4] = 1;
                    m_objects[v4].vx = 3.0;
                    if (facing != m_objects[v4].facing) {
                        m_objects[v4].facing = facing;
                    }
                    m_shotOrder = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectState[v4] == 0) {
                    m_objects[v4].vx = 2.7;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].hitsLeft = 1;
                    m_objectState[v4] = 1;
                }
                if (m_objectState[v4] == 1) {
                    m_objects[v4].vx -= 0.02;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].vx == 0.0 && m_objectState[v4] == 1) {
                    m_objectState[v4] = 2;
                    m_shotState = 2;
                    m_objects[v4].hitsLeft = 0;
                }
                if (m_objectState[v4] >= 2) {
                    if (m_objects[v4].y < y - 50.0) {
                        m_objects[v4].vy += 0.06;
                    }
                    if (m_objects[v4].y > y - 70.0) {
                        m_objects[v4].vy -= 0.06;
                    }
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx += m_objects[v4].facing * 0.04;
                    }
                    if (m_objects[v4].x > x) {
                        m_objects[v4].vx = m_objects[v4].vx - m_objects[v4].facing * 0.04;
                    }
                    if (m_objects[v4].vy < -2.0) {
                        m_objects[v4].vy = -2.0;
                    } else if (m_objects[v4].vy > 2.0) {
                        m_objects[v4].vy = 2.0;
                    }
                    if (m_objects[v4].vx < -2.0) {
                        m_objects[v4].vx = -2.0;
                    } else if (m_objects[v4].vx > 2.0) {
                        m_objects[v4].vx = 2.0;
                    }
                    if (m_objectState[v4] > 1 && m_objectTimer[v4] > 0x59 && m_objectPhase[v4] < 5) {
                        l50.keep = 0;
                        l50.type = kObjBomb;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.facing = m_objects[v4].facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        SpawnObject(&l50);
                        l50.type = kObjPlaceFx;
                        SpawnObject(&l50);
                        m_objectTimer[v4] = 0;
                        m_objectPhase[v4]++;
                    }
                    if (m_objects[v4].y > y - 70.0 && m_objects[v4].y < y - 20.0 && m_objects[v4].x > x - 10.0 && m_objects[v4].x < x + 10.0 && m_shotState >= 2) {
                        RemoveObject(v4);
                        m_shotState = 0;
                        m_playSound = 0x1a;
                        break;
                    }
                }
                m_objects[v4].timer++;
                m_objectTimer[v4]++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                }
                break;
            case kObjPlaceFx:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_playVoice = 1;
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
            case kObjBombBack:
                if (m_objectPhase[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objectPhase[v4] == 0) {
                    m_objects[v4].vx = -1.2;
                    m_objects[v4].vy = 1.2;
                    m_objectPhase[v4] = 1;
                }
                if (m_objectPhase[v4] == 1) {
                    m_objects[v4].vx += 0.015;
                    m_objects[v4].vy -= 0.015;
                    if (m_objects[v4].y > -10.0) {
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                    if (m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                }
                if (m_objectTriggered[v4] == 1 && m_objectTimer[v4] <= 0 && m_objectPhase[v4] == 2) {
                    l50.keep = 0;
                    l50.type = kObjExplosion;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectTriggered[v4] = 0;
                    m_objectTimer[v4] = 0x78;
                    if (m_keepBombs == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                m_objectTriggered[v4] = 0;
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectState[v4] < 0xa) {
                            m_objects[v4].frame = 0;
                            m_objectState[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjUnused1a0:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_playVoice = 1;
                    m_keepBombs = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                        m_keepBombs = 0;
                    }
                }
                break;
            case kObjLv4Director:
                m_lv4Time--;
                m_freezeTime = 0x4b0;
                (*m_opponent)->m_noGuardTime = 1;
                m_invulTime = 1;
                m_gauge = 0;
                (*m_opponent)->m_koDelay = 2;
                if (m_lv4Time == 0) {
                    m_freezeTime = 0;
                    (*m_opponent)->m_noGuardTime = 0;
                    RemoveObject(v4);
                    m_playSound = 0x16;
                    (*m_opponent)->pattern = kHitAir;
                    (*m_opponent)->m_koDelay = 0;
                    m_invulTime = 0;
                    (*m_opponent)->m_noAirRecovery = 1;
                    if ((*m_opponent)->m_hp == 1) {
                        (*m_opponent)->m_hp = 0;
                    }
                    (*m_opponent)->m_hitVx = -4.0;
                    (*m_opponent)->m_hitVy = -1.0;
                    break;
                }
                if (m_lv4Time == 0x47e) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene01;
                    l50.x = 0.0;
                    l50.y = 80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x474) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene02;
                    l50.x = 190.0;
                    l50.y = 320.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x46a) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene03;
                    l50.x = 320.0;
                    l50.y = 170.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x460) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene04;
                    l50.x = 0.0;
                    l50.y = 120.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x456) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene05;
                    l50.x = 60.0;
                    l50.y = -80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x44c) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene06;
                    l50.x = 320.0;
                    l50.y = 40.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x438) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene07;
                    l50.x = 240.0;
                    l50.y = 320.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x424) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene08;
                    l50.x = 180.0;
                    l50.y = -80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x410) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene09;
                    l50.x = 0.0;
                    l50.y = 80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x3fc) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene10;
                    l50.x = 180.0;
                    l50.y = -80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x3e8) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene11;
                    l50.x = 320.0;
                    l50.y = 210.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x3d4) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene12;
                    l50.x = 80.0;
                    l50.y = 320.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x3ca) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene13;
                    l50.x = 240.0;
                    l50.y = 320.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x3b6) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene14;
                    l50.x = 0.0;
                    l50.y = 60.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x3a2) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene15;
                    l50.x = 160.0;
                    l50.y = -80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x38e) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene16;
                    l50.x = 320.0;
                    l50.y = 80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x37a) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene17;
                    l50.x = 180.0;
                    l50.y = 320.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x366) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene18;
                    l50.x = 0.0;
                    l50.y = 160.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x352) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene19;
                    l50.x = 60.0;
                    l50.y = -80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x33e) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene20;
                    l50.x = 320.0;
                    l50.y = 50.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x32a) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene21;
                    l50.x = 0.0;
                    l50.y = 170.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x316) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene22;
                    l50.x = 320.0;
                    l50.y = 160.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x302) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene23;
                    l50.x = 160.0;
                    l50.y = 320.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x2ee) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene24;
                    l50.x = 60.0;
                    l50.y = -80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x2da) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene25;
                    l50.x = 0.0;
                    l50.y = 120.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x2c6) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene26;
                    l50.x = 190.0;
                    l50.y = 320.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x2b2) {
                    l50.keep = 0;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene27;
                    l50.x = 120.0;
                    l50.y = -80.0;
                    l50.facing = 1;
                    l50.scale = 1;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x21c) {
                    l50.keep = 1;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene28;
                    l50.x = 0.0;
                    l50.y = 120.0;
                    l50.facing = 1;
                    l50.scale = 0;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_lv4Time == 0x12c) {
                    l50.keep = 1;
                    l50.screen = 1;
                    l50.type = kObjLv4Scene29;
                    l50.x = 320.0;
                    l50.y = 160.0;
                    l50.facing = 1;
                    l50.scale = 0;
                    l50.layer = 0;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
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
            case kObjLv4Scene01:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene02:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene03:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene04:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene05:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene06:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene07:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene08:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene09:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene10:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene11:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene12:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene13:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene14:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene15:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene16:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene17:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene18:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene19:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene20:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene21:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene22:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene23:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene24:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene25:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x5a) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x82) {
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
            case kObjLv4Scene26:
                m_objects[v4].vy = -10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = -0.3;
                }
                if (m_objects[v4].timer > 0x96) {
                    m_objects[v4].vy = -10.0;
                }
                if (m_objects[v4].timer > 0xb4) {
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
            case kObjLv4Scene27:
                m_objects[v4].vy = 10.0;
                if (m_objects[v4].timer > 0x1c) {
                    m_objects[v4].vy = 0.3;
                }
                if (m_objects[v4].timer > 0x96) {
                    m_objects[v4].vy = 10.0;
                }
                if (m_objects[v4].timer > 0xb4) {
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
            case kObjLv4Scene28:
                m_objects[v4].vx = 10.0;
                if (m_objects[v4].timer > 0x17) {
                    m_objects[v4].vx = 0.3;
                }
                if (m_objects[v4].timer > 0x1fe) {
                    m_objects[v4].vx = 10.0;
                }
                if (m_objects[v4].timer > 0x21c) {
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
            case kObjLv4Scene29:
                m_objects[v4].vx = -10.0;
                if (m_objects[v4].timer > 0x1a) {
                    m_objects[v4].vx = -0.3;
                }
                if (m_objects[v4].timer > 0x10e) {
                    m_objects[v4].vx = -10.0;
                }
                if (m_objects[v4].timer > 0x12c) {
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
            case kObjLv4Start:
                if (pattern != kLv4) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].frame == 0x19) {
                    if (m_patternVar1 == 0) {
                        m_playVoice = 3;
                        TriggerObjectsNear((int)x, (int)y, 0x140, 0x140);
                        m_game->FlashWhite(3, 6, 9);
                    }
                    m_patternVar1 = 1;
                }
                if (m_objects[v4].frame == 0x28) {
                    if (m_patternVar1 == 1) {
                        m_playVoice = 4;
                    }
                    m_patternVar1 = 2;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = kObjLv4StartEnd;
                    }
                }
                break;
            case kObjLv4StartEnd:
                if (pattern != kLv4) {
                    RemoveObject(v4);
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
            case kObjBombFwd:
                if (m_objectPhase[v4] == 2) {
                    if (m_objects[v4].ay == 0.0) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy > 0.7) {
                        m_objects[v4].ay = -0.015;
                    }
                    if (m_objects[v4].vy < -0.7) {
                        m_objects[v4].ay = 0.015;
                    }
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                }
                if (m_objectPhase[v4] == 0) {
                    m_objects[v4].vx = 1.2;
                    m_objects[v4].vy = 1.2;
                    m_objectPhase[v4] = 1;
                }
                if (m_objectPhase[v4] == 1) {
                    m_objects[v4].vx -= 0.015;
                    m_objects[v4].vy -= 0.015;
                    if (m_objects[v4].y > -10.0) {
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objectPhase[v4] = 2;
                    }
                }
                if (m_objectTriggered[v4] == 1 && m_objectTimer[v4] <= 0 && m_objectPhase[v4] == 2) {
                    l50.keep = 0;
                    l50.type = kObjExplosion;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    m_objectTriggered[v4] = 0;
                    m_objectTimer[v4] = 0x78;
                    if (m_keepBombs == 0) {
                        RemoveObject(v4);
                    }
                    break;
                }
                m_objectTriggered[v4] = 0;
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectState[v4] < 0xa) {
                            m_objects[v4].frame = 0;
                            m_objectState[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObj6413Lv1Blast:
                m_objects[v4].x = x;
                m_objects[v4].y = y - 55.0;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    l50.keep = 1;
                    l50.type = kObj6413Flash;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
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
                break;
            case kObj6413Lv2Blast:
                m_objects[v4].x = x;
                m_objects[v4].y = y - 55.0;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    l50.keep = 1;
                    l50.type = kObj6413Flash;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
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
                break;
            case kObj6413Lv3Blast:
                m_objects[v4].x = x;
                m_objects[v4].y = y - 55.0;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    l50.keep = 1;
                    l50.type = kObj6413Flash;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
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
                break;
            case kObj6413Flash:
                m_objects[v4].x = x;
                m_objects[v4].y = y - 55.0;
                if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0) {
                    m_keepBombs = 0;
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
            case kObjExplosionBig:
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_playVoice = 1;
                }
                if (m_objects[v4].frame == 0xd && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    TriggerObjectsNear((int)m_objects[v4].x, (int)m_objects[v4].y, 0x78, 0x78);
                    m_objectTriggered[v4] = 0;
                }
                if (m_objects[v4].attackResult == 3) {
                    m_objectState[v4] = (int)AngleTo(m_objects[v4].x - (*m_opponent)->x, m_objects[v4].y - (*m_opponent)->y - 50.0);
                    (*m_opponent)->SetVelocity((double)m_objectState[v4], 2.2);
                    if ((*m_opponent)->facing == 1) {
                        (*m_opponent)->vx *= -1.0;
                    }
                    m_objects[v4].attackResult = 1;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectState[v4] == 0) {
                    m_objectTimer[v4] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectState[v4]++;
                    m_objects[v4].vx = (rand() > 0x3e80) * 1.2 + (rand() > 0x3e80) * 0.7 + (rand() > 0x3e80) * 1.7 + -1.8;
                    m_objects[v4].vy = -1.2 - ((rand() > 0x3e80) * 0.6 + (rand() > 0x3e80) * 0.9 + (rand() > 0x3e80) * 1.4);
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (m_objectTimer[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (m_objectTimer[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
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
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectState[v4] == 0) {
                    m_objectTimer[v4] = (rand() > 0x3e80) * 0x3c + 0x78 + (rand() > 0x3e80) * 0x28;
                    m_objectState[v4]++;
                    m_objects[v4].vx = (double)(rand() > 0x3e80) + (rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 1.5 + -1.5;
                    m_objects[v4].vy = -1.0 - ((rand() > 0x3e80) * 0.5 + (rand() > 0x3e80) * 0.8 + (rand() > 0x3e80) * 1.2);
                }
                m_objects[v4].vy += 0.03;
                if (m_objects[v4].y > 0.0 && m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = -m_objects[v4].vy;
                }
                if (m_objectTimer[v4] < 0xa) {
                    m_objects[v4].scale = 1;
                }
                if (m_objectTimer[v4] < 0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                m_objectTimer[v4]--;
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
