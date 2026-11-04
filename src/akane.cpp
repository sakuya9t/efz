// CAkane (0x7039d0-0x7124ff): the character class whose files are in akane\ in the game
// folder (akane.dat sprites, akane.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CAkane::CAkane(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "akane");
    lastSurface = 0x26b;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_helperState = 0;
    m_encasedBreakOut = 0;
    m_pointX[0] = -8;
    m_pointY[0] = -0x35;
    m_pointX[1] = 0x15;
    m_pointY[1] = 0;
    m_pointX[2] = 0;
    m_pointY[2] = -5;
    m_pointX[3] = 2;
    m_pointY[3] = -0xd;
    m_pointX[4] = 0x1f;
    m_pointY[4] = -0x1d;
    m_resultPictures = 4;
    m_rivals[0] = 2;
    m_rivals[1] = 0xb;
    m_rivals[2] = 1;
    m_rivals[3] = 0x12;
    m_rivals[4] = 4;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
}

void CAkane::Reset()
{
    int i;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_helperState = 0;
    m_encasedBreakOut = 0;
    m_pointX[0] = -8;
    m_pointY[0] = -0x35;
    m_pointX[1] = 0x15;
    m_pointY[1] = 0;
    m_pointX[2] = 0;
    m_pointY[2] = -5;
    m_pointX[3] = 2;
    m_pointY[3] = -0xd;
    m_pointX[4] = 0x1f;
    m_pointY[4] = -0x1d;
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
    CPlayer::Reset();
}

void CAkane::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CAkane::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
}

void CAkane::Move()
{
    MoveOnGround();
}

void CAkane::StartCommand()
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
    if (m_command == kCmd22C && (m_rfGauge >= 500.0 && m_attackResult > 1 && m_attackResult != 6 || m_rfBlue > 0 && m_attackResult > 1) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[kInstantCharge].level) {
        StartPattern();
        ClearBufferedPress();
        pattern = kInstantCharge;
        if (y < 0.0) {
            pattern = kAirInstantCharge;
        }
        return;
    }
    if (m_sealLevel < 2) {
        if (m_hp < 0xd05 && m_command == kCmdA5A6BC && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_attackResult != 6 && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd641236C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_helperState == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236C;
            return;
        }
        if ((m_command == kCmd641236B || m_command == kCmd641236C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_helperState == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236B;
            return;
        }
        if ((m_command == kCmd641236A || m_command == kCmd641236B || m_command == kCmd641236C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_helperState == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236A;
            return;
        }
        if (m_command == kCmd236236C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k236236C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236C;
            return;
        }
        if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236B;
            return;
        }
        if ((m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236A;
            return;
        }
        if (m_command == kCmd214214A && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214A;
            return;
        }
        if (m_command == kCmd214214B && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214B;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214C;
            return;
        }
        if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kAir236C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236C;
            return;
        }
        if ((m_command == kCmd236B || m_command == kCmd236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kAir236B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236B;
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kAir236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236A;
            return;
        }
        if (m_command == kCmd623C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k623C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623C;
            return;
        }
        if ((m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k623B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623B;
            return;
        }
        if (m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
            return;
        }
        if (m_command == kCmd214C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            return;
        }
        if (m_command == kCmd214B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            return;
        }
        if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            return;
        }
        if (m_command == kCmd412C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k412C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412C;
            return;
        }
        if (m_command == kCmd412B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k412B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412B;
            return;
        }
        if (m_command == kCmd412A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k412A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412A;
            return;
        }
        if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && m_helperState == 0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k236C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            return;
        }
        if ((m_command == kCmd236B || m_command == kCmd236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_helperState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236B;
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_helperState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236A;
            return;
        }
    }
    if (m_sealLevel < 1 && (m_command == kCmdDashLeft || m_command == kCmdDashRight)) {
        if (y < 0.0 && m_airDashes < 1) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].cancelLevel <= m_patterns[kAirDashForward].level && pattern != kRecoilGuardAir && y < -30.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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
            if (m_patterns[pattern].cancelLevel <= m_patterns[kJump6C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && m_inputY != 1 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kJump6C;
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
            if (m_inputX != 0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && (*m_opponent)->y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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

void CAkane::DrawGauge()
{
}

void CAkane::PreUpdate()
{
}

void CAkane::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CAkane::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + 0x2d;
    for (; pos < m_inputPos + 0xb4; pos++) {
        input = m_inputHistory[(pos - (pos >= 0xb4) * 0xb4)];
        if ((input & 0x40) != 0 && step == 5) {
            m_command = kCmdA5A6BC;
            return;
        }
        if ((input & 0x20) != 0 && step == 4) {
            step = 5;
        }
        if ((input & 0xd0) != 0 && step == 4) {
            break;
        }
        if ((input & 0xf) == (facing == -1) + 1 && step == 3) {
            step = 4;
        }
        if ((input & 0xe0) != 0 && step == 2) {
            break;
        }
        if ((input & 0x10) != 0 && step == 2) {
            step = 3;
        }
        if (input == 0 && step == 1) {
            step = 2;
        }
        if ((input & 0xe0) != 0 && step == 1) {
            break;
        }
        if ((input & 0x10) != 0 && step == 0 && m_gauge == 0xbb8 && y == 0.0) {
            step = 1;
        }
    }
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
        if ((input & 0xf) == (facing == -1) + 1 && step == 0 && m_gauge >= 0x3e8 && y == 0.0) {
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
        if ((input & 0xf) == 4 && step == 0 && m_gauge >= 0x3e8 && y == 0.0) {
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
        if ((input & 0xf) == 4 && step == 0 && m_gauge >= 0x3e8 && y == 0.0) {
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
        if ((input & 0xf) == (facing == -1) + 1 && step == 0 && y == 0.0) {
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

void CAkane::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == kLeap236C && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 35.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 50.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && dx > 60.0 && dx < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
            m_pressB = 1;
            m_inputY = 0;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (dx < 90.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd623A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_rfGauge > 500.0) {
                m_command = kCmd623C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_command = kCmd236B;
                return;
            }
            if (dx < 40.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0x7d0) {
                m_command = kCmd641236B;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && dx < 30.0 && m_gauge == 0xbb8) {
                m_command = kCmdA5A6BC;
                return;
            }
        }
        if (dx < 130.0 && dx > 90.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = kCmd623C;
                return;
            }
            if (dx < 110.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_command = kCmd412C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_command = kCmd236B;
                return;
            }
        }
        if (dx > 130.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_command = kCmd412C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_command = kCmd236B;
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
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < 50.0 && dx < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -30.0 && y - (*m_opponent)->y < 90.0 && dx < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            m_inputX = facing;
            return;
        }
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 2) {
            m_command = kCmd412C;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 2 && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 5 && m_cpuRoll > 2 && m_rfGauge > 500.0) {
            m_command = kCmd623A;
            return;
        }
        if (m_cpuRoll < 8 && m_cpuRoll > 5) {
            m_command = kCmd236A;
            return;
        }
        if (m_cpuRoll < 0xc && m_cpuRoll > 8 && dx < 50.0) {
            m_command = kCmd412C;
            return;
        }
        if (m_cpuRoll < 0x12 && m_cpuRoll > 0x14 && dx < 30.0 && m_gauge == 0xbb8) {
            m_command = kCmdA5A6BC;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 2) {
            m_command = kCmd412C;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k623A || pattern == k623B || pattern == k623C || pattern == kLeapC && y < -110.0 || pattern == kAir236A || pattern == kAir236B || pattern == kAir236C)) {
        m_command = kCmd22C;
        return;
    }
    if (pattern > 0xff && pattern < 0x106 && (WORD)Random(0, 0x64) > 1e+01f * m_cpuSkill) {
        if (dy * 0.5 > dx) {
            m_pressC = 1;
            return;
        }
        if (dx < 30.0 && dy < 50.0) {
            m_pressC = 1;
            m_inputX = -facing;
            return;
        }
        if (dx < 20.0 && dy > 80.0) {
            m_pressC = 1;
            m_inputY = 1;
            return;
        }
        if (dx > 120.0 && dy < dx) {
            m_command = (WORD)Random(0, 2) + kCmd236B;
            return;
        }
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
            if (dx < 60.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 80.0 && m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 70.0 && m_cpuRoll > 0x190 && m_cpuRoll < 0x2bc) {
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
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x226) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                }
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
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && dx < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                }
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee && dx < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2ee) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xa;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = kCmd236B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x1f4) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                }
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x258) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x258) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0xe;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0x10;
                }
                return;
            }
        }
        if (pattern == k5C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = kCmd236B;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                }
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
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                }
                return;
            }
            if (dx < 70.0 && m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 80.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x3ca) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if (dx < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0xfa && dx < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0xfa && m_cpuRoll < 0x1c2 && dx < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x226) {
                m_command = kCmd236B;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x28a) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                }
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x320) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                }
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x258) {
                m_command = kCmd236B;
                return;
            }
            if (m_cpuRoll > 0x320 && m_cpuRoll < 0x352 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
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
            if (m_cpuRoll > 0x50 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputX = facing * ((WORD)Random(0, 2) == 0);
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
            if (m_cpuRoll < 0xc8) {
                m_command = kCmd412C;
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
        if (pattern == kDashB || pattern == kDashA || pattern == kDashC || pattern == kDash2A || pattern == kDash2B) {
            if (m_cpuRoll < 0x1c2) {
                m_command = (WORD)Random(0, 3) + kCmd412A;
                if ((WORD)Random(0, 0x64) < 0x14) {
                    m_command = (WORD)Random(0, 3) + kCmd214A;
                }
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x28a) {
                m_command = kCmd236B;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xa;
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
        if (pattern == kLeapC && m_cpuRoll > 0x258 && y == 0.0) {
            m_cpuAction = 1;
            if (dx < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
        if (pattern == kDash2C && m_cpuRoll > 0x258 && y == 0.0) {
            m_cpuAction = 1;
            if (dx < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
        if (pattern == k236B && m_cpuRoll > 0x2bb) {
            if ((WORD)Random(0, 2) == 0) {
                m_cpuAction = 6;
            }
            if ((WORD)Random(0, 4) == 0) {
                m_cpuAction = 8;
            }
            if ((WORD)Random(0, 3) == 0) {
                m_cpuAction = 0xa;
            }
            if ((WORD)Random(0, 4) == 0) {
                m_cpuAction = 0xc;
            }
            if ((WORD)Random(0, 4) == 0) {
                m_cpuAction = 0xe;
            }
            if ((WORD)Random(0, 3) == 0) {
                m_cpuAction = 0x10;
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
                if (dx < 40.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x19 + 0x41) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (dx < 55.0 && m_cpuRoll > 0x5a) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x19 + 0x8c) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (dx > 80.0 && dx < 100.0 && m_cpuRoll < 0xa0 && m_cpuRoll > 0x8c) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (0x46 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x46 < dx && dx < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x28 + 0xc8 && m_cpuRoll > 0xa0) {
                        m_cpuAction = 8;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x46 < dx && dx < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x28 + 0x118 && m_cpuRoll > 0xf0) {
                        m_cpuAction = 0xc;
                        return;
                    }
                }
                if (dx < 120.0 && dx > 60.0 && m_cpuRoll < 0x168 && m_cpuRoll > 0x140) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 120.0 && dx > 80.0 && m_cpuRoll < 0x17c && m_cpuRoll > 0x168) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx > 100.0 && dx < 150.0 && m_cpuRoll < 0x1ae && m_cpuRoll > 0x17c) {
                    m_cpuAction = 0xe;
                    return;
                }
                if (0x5a - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x5a < dx && dx < 130.0 && m_cpuRoll < 0x1d6 && m_cpuRoll > 0x1ae) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (dx > 90.0 && dx < 150.0 && m_cpuRoll < 0x212 && m_cpuRoll > 0x1d6) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (dx > 180.0 && m_cpuRoll < 0x230 && m_cpuRoll > 0x226) {
                    m_command = kCmd236A;
                    return;
                }
                if (dx < 100.0 && m_cpuRoll < 0x23a && m_cpuRoll > 0x230) {
                    m_command = (WORD)Random(0, 3) + kCmd236236B;
                    return;
                }
                if (dx > 100.0 && m_cpuRoll < 0x24e && m_cpuRoll > 0x23a) {
                    m_command = kCmd236A;
                    return;
                }
                if (dx > 100.0 && m_cpuRoll < 0x262 && m_cpuRoll > 0x24e) {
                    m_command = kCmd236B;
                    return;
                }
                if (m_cpuRoll < 0x2ee && m_cpuRoll > 0x2bc && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir && dx > 100.0) {
                    m_cpuAction = 5;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0 && dx < 80.0 && dy < 120.0 && m_cpuRoll < 0xa) {
                    m_inputY = -1;
                    m_inputX = -facing;
                    return;
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 80.0 && dy < 90.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623C;
                        return;
                    }
                    if (dx < 80.0 && dy < 90.0) {
                        if (m_cpuRoll < (m_rfGauge > 500.0 || m_rfBlue > 0) * 8 + 0xa) {
                            m_command = kCmd623A;
                            return;
                        }
                    }
                    if (dx < 60.0 && m_cpuRoll < 0x136 && m_cpuRoll > 0x12c && dy > 100.0 && m_gauge == 0xbb8) {
                        m_command = kCmd236236C;
                        return;
                    }
                    if (dx < 60.0 && m_cpuRoll < 0x140 && m_cpuRoll > 0x136 && dy > 200.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 2) + kCmd236236A;
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
                if (dx < 80.0 && dy > 90.0 && dy < 80.0 && (*m_opponent)->y < y && m_cpuRoll > 0x64 && m_cpuRoll < 0xb4) {
                    m_pressB = 1;
                    return;
                }
                if (dx > 80.0 && dx < 110.0 && dy > 100.0 && dy < 130.0 && m_cpuRoll > 0xb4 && m_cpuRoll < 0xf0) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 80.0 && dy < 100.0 && y < (*m_opponent)->y && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 20.0 && dx < 90.0 && dy > 90.0 && m_cpuRoll > 0x14 && m_cpuRoll < 0x28) {
                    m_pressB = 1;
                    return;
                }
                if (dx > 80.0 && dx < 100.0 && dy > 70.0 && dy < 100.0 && y < (*m_opponent)->y && m_cpuRoll > 0x28 && m_cpuRoll < 0x32) {
                    m_pressC = 1;
                    return;
                }
                if (dx > 90.0 && dx < 130.0 && dy > 40.0 && dy < 120.0 && y > (*m_opponent)->y && m_cpuRoll > 0x32 && m_cpuRoll < 0x41) {
                    m_pressC = 1;
                    m_inputX = facing;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 5.0f * m_cpuSkill && dx > 120.0) {
        m_command = facing == 1;
        return;
    }
    if ((WORD)Random(0, 0x3e8) < 2 && dx > 90.0) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 0x64) < 4) {
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
    if ((WORD)Random(0, 0x64) < 0x28 && dx < 120.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x1e;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x46) {
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

void CAkane::UpdateObjects()
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
            case kObjLeapShotA:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 2.0;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].timer++;
                if ((m_objects[slot].attackResult == 3 || m_objects[slot].y >= 0.0) && m_objectVar1[slot] == 0) {
                    m_objects[slot].frame = 1;
                    m_objectVar1[slot] = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].attackResult == 2 || m_objects[slot].attackResult == 4) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -1.0;
                    m_objects[slot].vy = -2.0;
                    m_objects[slot].pattern = kObjLeapShotKnocked;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y < -480.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjLeapShotB:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 1.3;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].timer++;
                if ((m_objects[slot].attackResult == 3 || m_objects[slot].y >= 0.0) && m_objectVar1[slot] == 0) {
                    m_objects[slot].frame = 1;
                    m_objectVar1[slot] = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].attackResult == 2 || m_objects[slot].attackResult == 4) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -1.0;
                    m_objects[slot].vy = -2.0;
                    m_objects[slot].pattern = kObjLeapShotKnocked;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y < -480.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjLeapShotC:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 2.0;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].timer++;
                if ((m_objects[slot].attackResult == 3 || m_objects[slot].y >= 0.0) && m_objectVar1[slot] == 0) {
                    m_objects[slot].frame = 1;
                    m_objectVar1[slot] = 1;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].attackResult == 4) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vy = -2.0;
                    m_objects[slot].vx = -1.0;
                    m_objects[slot].pattern = kObjLeapShotKnocked;
                }
                if (m_objects[slot].attackResult == 2) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = 0.2;
                    m_objects[slot].vy = -3.5;
                    m_objects[slot].pattern = kObjLeapShotPopped;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y < -480.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjLeapShotPopped:
                m_objects[slot].vy += 0.04;
                if (m_objects[slot].vy > 0.0) {
                    m_objects[slot].hitsLeft = 1;
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
                if (m_objects[slot].attackResult > 1 || m_objects[slot].y > 0.0) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vy = -2.0;
                    m_objects[slot].pattern = kObjLeapShotKnocked;
                }
                break;
            case kObjLeapShotKnocked:
                m_objects[slot].vy += 0.05;
                m_objects[slot].scale = 1;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y > 0.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj236236Rise:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = -8.0;
                if (m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].y < -1000.0) {
                    m_objects[slot].scale = 0;
                    if ((WORD)Random(0, 0x64) < 0x32) {
                        m_objects[slot].attackResult = 0;
                        m_objects[slot].pattern = kObj236236FallMid;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].x = (int)((*m_opponent)->x + m_objects[slot].facing * ((m_objects[slot].y - (*m_opponent)->y) / 2.0) + ((WORD)Random(0, 0x8c) - 0x46));
                        break;
                    }
                    if ((WORD)Random(0, 2) == 0) {
                        m_objects[slot].pattern = kObj236236FallFast;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].x = (int)((*m_opponent)->x + m_objects[slot].facing * 0x64 + m_objects[slot].facing * (m_objects[slot].y - (*m_opponent)->y * 0.5) + ((WORD)Random(0, 0x8c) - 0x46));
                        break;
                    }
                    m_objects[slot].pattern = kObj236236FallSlow;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].x = (int)((*m_opponent)->x + m_objects[slot].facing * ((m_objects[slot].y - (*m_opponent)->y) / 4.0) + ((WORD)Random(0, 0x8c) - 0x46));
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
            case kObj236236FallSlow:
                m_objects[slot].vx = 2.0;
                m_objects[slot].vy = 8.0;
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot] = (WORD)Random(1, 0x14);
                }
                if (m_objects[slot].frame >= 1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].y >= m_objectVar1[slot] - 0xf && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
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
            case kObj236236FallMid:
                m_objects[slot].vx = 4.0;
                m_objects[slot].vy = 8.0;
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot] = (WORD)Random(1, 0x14);
                }
                if (m_objects[slot].frame >= 1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].y >= m_objectVar1[slot] - 0xf && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
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
            case kObj236236FallFast:
                m_objects[slot].vx = 7.0;
                m_objects[slot].vy = 8.0;
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot] = (WORD)Random(1, 0x14);
                }
                if (m_objects[slot].frame >= 1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].y >= m_objectVar1[slot] - 0xf && m_objects[slot].frame == 0) {
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
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
            case kObjHelper236C:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 1.5;
                    if (m_objectVar1[slot] == 0) {
                        m_objects[slot].hitsLeft = 1;
                        m_objectVar1[slot]++;
                    }
                    effect.type = 0x1f;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.side = m_objects[slot].facing == -1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    effect.type = 0x19b;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.scale = 0;
                    effect.keep = 1;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -3.0;
                    m_objects[slot].pattern = kObjHelperHit;
                    break;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                if ((m_objects[slot].x < -100.0 || m_objects[slot].x > 740.0) && pattern != k236C) {
                    RemoveObject(slot);
                    m_helperState = 0;
                }
                break;
            case kObjHelperHit:
                if (m_objects[slot].frame < 6) {
                    m_objects[slot].vy += 0.04;
                }
                if (m_objects[slot].y + m_objects[slot].vy >= 0.0 && m_objects[slot].frame < 6) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 6;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].y = 0.0;
                    unke8 = 1.5;
                    effect.type = 3;
                    effect.sound = 7;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].pattern = kObjHelperFlee;
                        break;
                    }
                }
                break;
            case kObjHelperDrop:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -0.7;
                    m_objects[slot].vy = -1.5;
                }
                m_objects[slot].vy += 0.03;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                if (m_objects[slot].y > 100.0) {
                    RemoveObject(slot);
                }
                break;
            case kObj214214:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objectVar1[slot] = 0;
                    m_objectVar2[slot] = 0;
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vx -= 0.05;
                if (m_objects[slot].vx < 0.1) {
                    m_objects[slot].vx = 0.1;
                }
                if (m_objects[slot].frame < 0x1a && m_objects[slot].hitsLeft == 0) {
                    m_objects[slot].frame = 0x1a;
                    m_objects[slot].timer = 0;
                    if (m_objects[slot].attackResult == 3) {
                        (*m_opponent)->m_hitstop = 0x5a;
                    }
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objectVar2[slot] < 3 && m_objects[slot].frame == 0x19) {
                        m_objectVar2[slot]++;
                        m_objects[slot].frame = 0xa;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjHelperFlee:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 3) {
                        m_objects[slot].vx = -6.0;
                        m_objects[slot].vy = -4.0;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                if (m_objects[slot].x < -80.0 || m_objects[slot].x > 720.0) {
                    RemoveObject(slot);
                    m_helperState = 0;
                }
                break;
            case kObjHelper236A:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 2.3;
                    m_objects[slot].vy = 0.8;
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
                }
                m_objects[slot].vy -= 0.015;
                m_objects[slot].timer++;
                if (m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -3.0;
                    m_objects[slot].pattern = kObjHelperHit;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                if ((m_objects[slot].x < -150.0 || m_objects[slot].x > 790.0) && pattern != k236236A) {
                    RemoveObject(slot);
                    m_helperState = 0;
                }
                break;
            case kObjHelper236B:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 3.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 0;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].x - (*m_opponent)->x < 60.0 && m_objects[slot].x - (*m_opponent)->x > -60.0 && m_objects[slot].frame < 3) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjHelper236BAttack;
                    break;
                }
                if (m_objects[slot].frame > 2) {
                    m_objects[slot].vx -= 0.033;
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -3.0;
                    m_objects[slot].pattern = kObjHelperHit;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 3 && m_objectVar1[slot] < 0xa) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjHelperFlee;
                        break;
                    }
                }
                break;
            case kObjHelper236BAttack:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vx -= 0.04;
                if (m_objects[slot].vx < 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -3.0;
                    m_objects[slot].pattern = kObjHelperHit;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjHelperFlee;
                        break;
                    }
                }
                break;
            case kObjHelper641236A:
                if (m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -3.0;
                    m_objects[slot].pattern = kObjHelperHit;
                    m_helperState = 1;
                    break;
                }
                if (m_objects[slot].frame > 4) {
                    m_objects[slot].movesInFreeze = 0;
                }
                if (pattern != k641236A && m_objects[slot].frame < 0x12) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x12;
                    break;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 0xb;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].frame < 2 && m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 2;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].y = 0.0;
                    break;
                }
                if (m_objects[slot].frame == 4 && m_freezeTime == 0) {
                    m_objects[slot].frame = 5;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].timer == 0 && (m_objects[slot].frame == 6 || m_objects[slot].frame == 0xa || m_objects[slot].frame == 0xe)) {
                    m_objects[slot].vx = 0.0;
                    m_playSound = 0x14;
                }
                if (m_objects[slot].vx < 0.0 && m_objects[slot].frame < 0x14) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].frame < 2) {
                    m_objects[slot].vy += 0.085;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 0xc && m_objectVar2[slot] < 3) {
                        m_objects[slot].frame = 5;
                        if (m_objectVar2[slot] > 1) {
                            m_helperState = 1;
                        }
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame == 0x15) {
                        m_objects[slot].vx = -4.4;
                        m_objects[slot].vy = -3.8;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                if ((m_objects[slot].x < m_game->m_view.left - 0x32 && m_objects[slot].facing == 1 || m_objects[slot].x > m_game->m_view.right + 0x32 && m_objects[slot].facing == -1) && m_objects[slot].frame > 0x14) {
                    RemoveObject(slot);
                    m_helperState = 0;
                }
                break;
            case kObjHelper641236B:
                if (m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -3.0;
                    m_objects[slot].pattern = kObjHelperHit;
                    m_helperState = 1;
                    break;
                }
                if (m_objects[slot].frame > 4) {
                    m_objects[slot].movesInFreeze = 0;
                }
                if (pattern != k641236B && m_objects[slot].frame < 0x19) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x19;
                    break;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 0x63;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].frame < 2 && m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 2;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].y = 0.0;
                    break;
                }
                if (m_objects[slot].frame == 4 && m_freezeTime == 0) {
                    m_objects[slot].frame = 5;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].timer == 0 && m_objects[slot].frame == 0x15) {
                    m_objects[slot].vx = 2.2;
                    m_playSound = 0x14;
                }
                if (m_objects[slot].timer == 0 && m_objects[slot].frame == 7 && m_objects[slot].frame == 0xc) {
                    m_playSound = 0x14;
                }
                if (m_objects[slot].vx > 0.0 && m_objects[slot].frame > 4) {
                    m_objects[slot].vx -= 0.105;
                }
                if (m_objects[slot].vx < 0.0 && m_objects[slot].frame < 0x14) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].frame < 2) {
                    m_objects[slot].vy += 0.085;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 0x14 && m_objectVar2[slot] < 6) {
                        m_objects[slot].frame = 5;
                        if (m_objectVar2[slot] > 4) {
                            m_helperState = 1;
                        }
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame == 0x1c) {
                        m_objects[slot].vx = -4.4;
                        m_objects[slot].vy = -3.8;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                if ((m_objects[slot].x < m_game->m_view.left - 0x32 && m_objects[slot].facing == 1 || m_objects[slot].x > m_game->m_view.right + 0x32 && m_objects[slot].facing == -1) && m_objects[slot].frame > 0x14) {
                    RemoveObject(slot);
                    m_helperState = 0;
                }
                break;
            case kObjHelper641236C:
                if (m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -3.0;
                    m_objects[slot].pattern = kObjHelperHit;
                    break;
                }
                m_game->FlashNegative(0xf);
                if (m_objects[slot].frame > 4) {
                    m_objects[slot].movesInFreeze = 0;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].frame < 2 && m_objects[slot].y + m_objects[slot].vy > 0.0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 2;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].y = 0.0;
                    break;
                }
                if (m_objects[slot].frame == 4 && m_freezeTime == 0) {
                    m_objects[slot].frame = 5;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].timer == 0 && m_objects[slot].frame == 7 && m_objects[slot].frame == 0xc) {
                    m_playSound = 0x14;
                }
                if (m_objects[slot].frame == 0x16 && m_objects[slot].attackResult == 3) {
                    m_objects[slot].vx = 0.05;
                    m_objects[slot].vy = -0.2;
                    (*m_opponent)->m_hitstop = 0x78;
                    m_objects[slot].attackResult = 0;
                    effect.type = 0x1a4;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.keep = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].frame == 0x16 && (*m_opponent)->m_hitstop == 0) {
                    m_objects[slot].vx = 1.5;
                    m_objects[slot].vy = -6.0;
                }
                if (m_objects[slot].frame < 2) {
                    m_objects[slot].vy += 0.085;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 0x14 && m_objectVar2[slot] < 0xa) {
                        m_objects[slot].frame = 5;
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame == 0x16) {
                        m_objects[slot].vx = 1.5;
                        m_objects[slot].vy = -6.0;
                        m_playSound = 0x14;
                    }
                    if (m_objects[slot].frame == 0x17) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                if (m_objects[slot].y < -640.0 && m_objects[slot].frame > 0x14) {
                    RemoveObject(slot);
                    m_helperState = 0;
                }
                break;
            case kObjHelper641236CHold:
                m_objects[slot].vx = 0.05;
                m_objects[slot].vy = -0.2;
                if ((*m_opponent)->m_hitstop == 0) {
                    RemoveObject(slot);
                    break;
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
            case kObjRushFront:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -10.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].x > m_game->m_view.right + 0x3c && m_objects[slot].facing == -1 || m_objects[slot].x < m_game->m_view.left - 0x3c && m_objects[slot].facing == 1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].timer > 0xb4) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].timer > 0xc3) {
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
            case kObjRushFrontMid:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -9.0;
                    m_objects[slot].vy = -1.8;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].x > m_game->m_view.right + 0x3c && m_objects[slot].facing == -1 || m_objects[slot].x < m_game->m_view.left - 0x3c && m_objects[slot].facing == 1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].timer > 0xb4) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].timer > 0xc3) {
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
            case kObjRushFrontHigh:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -9.6;
                    m_objects[slot].vy = -3.8;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].x > m_game->m_view.right + 0x3c && m_objects[slot].facing == -1 || m_objects[slot].x < m_game->m_view.left - 0x3c && m_objects[slot].facing == 1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].timer > 0xb4) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].timer > 0xc3) {
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
            case kObjRushBack:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 10.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].x > m_game->m_view.right + 0x3c && m_objects[slot].facing == 1 || m_objects[slot].x < m_game->m_view.left - 0x3c && m_objects[slot].facing == -1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].timer > 0xb4) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].timer > 0xc3) {
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
            case kObjRushBackMid:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 9.8;
                    m_objects[slot].vy = -2.46;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].x > m_game->m_view.right + 0x3c && m_objects[slot].facing == 1 || m_objects[slot].x < m_game->m_view.left - 0x3c && m_objects[slot].facing == -1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].timer > 0xb4) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].timer > 0xc3) {
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
            case kObjRushBackHigh:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 10.0;
                    m_objects[slot].vy = -4.0;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].x > m_game->m_view.right + 0x3c && m_objects[slot].facing == 1 || m_objects[slot].x < m_game->m_view.left - 0x3c && m_objects[slot].facing == -1) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].timer > 0xb4) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].timer > 0xc3) {
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
            case kObjRushBelow:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = -10.0;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].y < (*m_opponent)->y - 180.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].timer > 0xb4) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].timer > 0xc3) {
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
            case kObjLv4Finish:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 0x38 && (*m_opponent)->m_koDelay > 0) {
                        m_game->FlashWhite(0x14, 0x78, 0x14);
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_roundsWon + 1 != m_game->m_roundsToWin) {
                            RemoveObject(slot);
                            m_patternVar3 = 0xa;
                        }
                        if (m_roundsWon + 1 == m_game->m_roundsToWin) {
                            m_objects[slot].frame = m_objects[slot].frame - 1;
                            (*m_opponent)->m_koDelay = 0;
                        }
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
