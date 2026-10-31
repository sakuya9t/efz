// CAkiko (0x7219a0-0x73070f): the character class whose files are in akiko\ in the game
// folder (akiko.dat sprites, akiko.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CAkiko::CAkiko(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "akiko");
    lastSurface = 0x25b;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_sealTime = 0;
    m_slowTick = 0;
    m_nextShot = 0;
    m_slowCountOnes = 0;
    m_slowCountTens = 0;
    m_slowCountHundreds = 0;
    m_slowEndTime = 0;
    m_pointX[0] = -6;
    m_pointY[0] = -0x48;
    m_pointX[1] = -0x16;
    m_pointY[1] = 0;
    m_pointX[2] = 0xc;
    m_pointY[2] = -0xe;
    m_pointX[3] = 0x16;
    m_pointY[3] = -0x13;
    m_pointX[4] = 0x1b;
    m_pointY[4] = -0x29;
    m_resultPictures = 4;
    m_rivals[0] = 0x10;
    m_rivals[1] = 1;
    m_rivals[2] = 0xa;
    m_rivals[3] = 3;
    m_rivals[4] = 0x17;
    m_rivals[5] = 0x13;
    m_rivals[6] = 0x11;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
}

void CAkiko::Reset()
{
    int v4;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_sealTime = 0;
    m_slowTick = 0;
    m_nextShot = 0;
    m_slowCountOnes = 0;
    m_slowCountTens = 0;
    m_slowCountHundreds = 0;
    m_slowEndTime = 0;
    m_pointX[0] = -6;
    m_pointY[0] = -0x48;
    m_pointX[1] = -0x16;
    m_pointY[1] = 0;
    m_pointX[2] = 0xc;
    m_pointY[2] = -0xe;
    m_pointX[3] = 0x16;
    m_pointY[3] = -0x13;
    m_pointX[4] = 0x1b;
    m_pointY[4] = -0x29;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
    CPlayer::Reset();
}

void CAkiko::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CAkiko::RemoveObject(short p1)
{
    m_objectVar1[p1] = 0;
    m_objectVar2[p1] = 0;
    m_objectVar3[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CAkiko::Move()
{
    MoveOnGround();
}

void CAkiko::StartCommand()
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
        if (m_hp < 0xd05 && m_command == kCmd25A25BC && m_gauge >= 0xbb8 && y == 0.0 && m_attackResult != 6 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd641236C && m_gauge >= 0xbb8 && m_timerSuper == 0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236C;
            return;
        }
        if ((m_command == kCmd641236B || m_command == kCmd641236C) && m_gauge >= 0x7d0 && m_timerSuper == 0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236B;
            return;
        }
        if ((m_command == kCmd641236A || m_command == kCmd641236B || m_command == kCmd641236C) && m_timerSuper == 0 && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236A;
            return;
        }
        if (m_command == kCmd236236C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236C;
            return;
        }
        if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236B;
            return;
        }
        if ((m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236A;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214C;
            return;
        }
        if ((m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214B;
            return;
        }
        if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214A;
            return;
        }
        if (m_command == kCmd41236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236C;
            return;
        }
        if ((m_command == kCmd41236B || m_command == kCmd41236C) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236B;
            return;
        }
        if (m_command == kCmd41236A && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236A;
            return;
        }
        if (m_command == kCmd623C && y == 0.0 && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623C;
            return;
        }
        if ((m_command == kCmd623B || m_command == kCmd623C) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623B;
            return;
        }
        if (m_command == kCmd623A && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
            return;
        }
        if (m_command == kCmd214C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            return;
        }
        if ((m_command == kCmd214B || m_command == kCmd214C) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            return;
        }
        if (m_command == kCmd214A && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
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
                m_dashMomentum++;
                m_bufferedPress = 0;
                return;
            }
        }
    }
    if (m_pressA == 1 || (m_bufferedPress & 0x10) != 0 || (m_dashBufferedPress & 0x10) != 0) {
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
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && (*m_opponent)->y == 0.0 && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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

void CAkiko::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (m_sealTime > 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_sealTime > 0) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, m_sealTime * x1c.width / 0x3e8, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, m_sealTime * x1c.width / 0x3e8, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - m_sealTime * x1c.width / 0x3e8, 0x1f - x1c.y, m_sealTime * x1c.width / 0x3e8, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_timerSuper > 0) {
        x1c = anims[0x28].frames[m_slowCountOnes];
        if (m_slowEndTime > 0) {
            x1c = anims[0x28].frames[0xa];
        }
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x5c - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(0x10d - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        x1c = anims[0x28].frames[m_slowCountTens];
        if (m_slowEndTime > 0) {
            x1c = anims[0x28].frames[0xa];
        }
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x4a - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(0xfb - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        x1c = anims[0x28].frames[m_slowCountHundreds];
        if (m_slowEndTime > 0) {
            x1c = anims[0x28].frames[0xa];
        }
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x38 - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(0xe9 - x1c.x, 0xc5 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        x1c = *anims[0x29].frames;
        if (m_slowEndTime > 0) {
            x1c = anims[0x29].frames[1];
        }
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x24 - x1c.x, 0xb0 - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(0xd5 - x1c.x, 0xb0 - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        if (m_slowEndTime > 0) {
            x1c = *anims[0x2a].frames;
            v2c = MakeRect(0, 0, x1c.width, x1c.height);
            if (m_side == 0) {
                v10 = MakeRect((int)(m_slowEndTime * 0.1) + 0x1f - x1c.x, 0xb9 - x1c.y, x1c.width, x1c.height);
            } else {
                v10 = MakeRect(0xda - (int)(m_slowEndTime * 0.1) - x1c.x, 0xb9 - x1c.y, x1c.width, x1c.height);
            }
            m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        }
    }
}

void CAkiko::PreUpdate()
{
    if ((m_hp <= 0 || (*m_opponent)->m_hp <= 0) && m_sealTime > 0) {
        m_sealTime = 0;
        (*m_opponent)->m_sealLevel = 0;
    }
    if ((m_hp <= 0 || (*m_opponent)->m_hp <= 0) && m_timerSuper > 0) {
        if (pattern != kLv4Hit) {
            m_game->FadeMusic(0, 0x2710);
        }
        m_timerSuper = 0;
        m_slowEndTime = 0;
        m_slowCountHundreds = 0;
        m_slowCountTens = 0;
        m_slowCountOnes = 0;
    }
    if (m_sealTime > 0) {
        (*m_opponent)->Tint(0xcb, 3);
        m_sealTime--;
        if (m_sealTime <= 0) {
            (*m_opponent)->m_sealLevel = 0;
        }
    }
    if (m_timerSuper > 0) {
        m_slowCountOnes = 4 - m_timerSuper + m_slowCountOnes;
        if (m_slowEndTime == 0) {
            if (m_slowCountOnes > 9) {
                m_slowCountOnes -= 0xa;
                m_slowCountTens++;
            }
            if (m_slowCountTens > 9) {
                m_slowCountTens -= 0xa;
                m_slowCountHundreds++;
            }
            if (m_slowCountHundreds > 9) {
                m_slowCountHundreds -= 0xa;
                m_slowEndTime++;
            }
            m_game->FlashNegative(3);
            if (m_slowTick == 2 || m_slowTick == 4 || m_slowTick == 6 || m_slowTick == 8 || m_slowTick == 0xa || m_slowTick == 0xc || m_slowTick == 0xe || m_slowTick == 0x10 || m_slowTick == 0x12 || m_slowTick == 0x14 || m_slowTick == 0x16 || m_slowTick == 0x18 || m_slowTick == 0x1a || m_slowTick == 0x1c || m_slowTick == 0x1e || m_slowTick == 0x20 || m_slowTick == 0x22 || m_slowTick == 0x24) {
                if (m_slowTick >= 0x24) {
                    m_slowTick = 0;
                    if ((*m_opponent)->m_timerSuper == 0 || (*m_opponent)->m_timerSuper == 4 || (*m_opponent)->m_timerSuper != 0 && m_side == 0) {
                        m_playVoice = 0xf;
                    }
                }
                if ((*m_opponent)->m_timerSuper == 0 || (*m_opponent)->m_timerSuper == 4) {
                    m_freezeTime = 1;
                }
            }
            m_slowTick++;
        }
        if (m_slowEndTime > 0) {
            if (m_slowEndTime == 1) {
                m_timerSuper = 4;
                if ((*m_opponent)->m_timerSuper == 0 || (*m_opponent)->m_timerSuper == 4) {
                    m_game->FadeMusic(0, 0x2710);
                }
                m_playVoice = 0x12;
            }
            m_slowEndTime++;
            if (m_slowEndTime > 0xb4) {
                m_slowEndTime = 0;
                m_slowCountHundreds = 0;
                m_slowCountTens = 0;
                m_slowCountOnes = 0;
                m_timerSuper = 0;
            }
        }
        if (pattern > kLastFreeAction && pattern < kFirstGuard) {
            if ((*m_opponent)->m_timerSuper == 0 || (*m_opponent)->m_timerSuper == 4) {
                m_game->FadeMusic(0, 0x2710);
            }
            m_timerSuper = 0;
            m_slowEndTime = 0;
            m_slowCountHundreds = 0;
            m_slowCountTens = 0;
            m_slowCountOnes = 0;
        }
    }
}

void CAkiko::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CAkiko::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = kCmdNone;
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 6) {
            m_command = kCmd25A25BC;
            return;
        }
        if ((v5 & 0x20) != 0 && x6 == 5) {
            x6 = 6;
        }
        if (v5 == 0 && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == 4 && x6 == 3) {
            x6 = 4;
        }
        if ((v5 & 0xe0) != 0 && x6 == 3) {
            break;
        }
        if ((v5 & 0x10) != 0 && x6 == 2) {
            x6 = 3;
        }
        if (v5 == 0 && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 4 && x6 == 0 && m_gauge == 0xbb8 && y == 0.0) {
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
    v4 = m_inputPos + 0x78;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 3) {
            m_command = ((v5 & 0xe0) > 0) + kCmd41236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd41236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 3;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 1) {
            x6 = 2;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0 && y == 0.0) {
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

void CAkiko::CpuInput()
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
    if ((WORD)Random(0, 0x7d0) < ((m_throwProtect > 0) * 4.0 + 1.0) * 8.0 * m_cpuSkill * ((pattern > kLastHitReaction && pattern < kAirRecoveryForward) * 0x7d0 + 1)) {
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == k41236AHit && m_hitsLeft > 1) {
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
                m_inputY = 0;
                return;
            }
            if (v10 > 80.0 && v10 < 140.0 && (WORD)Random(0, 0x12c) < m_cpuSkill * 3.0f) {
                m_command = kCmd623B;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x12c) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd623A;
                return;
            }
            if ((WORD)Random(0, 0x12c) < m_cpuSkill * 3.0f + ((m_rfGauge > 500.0) << 1)) {
                m_command = kCmd623B;
                return;
            }
            if ((WORD)Random(0, 0x1f4) < m_cpuSkill * 4.0f && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
        }
        if (v10 < 160.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
        if (v10 > 220.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
            m_command = (WORD)Random(0, 3) + kCmd236A;
            return;
        }
        if (v10 > 180.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_command = (WORD)Random(0, 3) + kCmd41236A;
            return;
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y > 0.0 && y - (*m_opponent)->y < 40.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -70.0 && y - (*m_opponent)->y < 70.0 && v10 < 130.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3) {
            m_command = kCmd623B;
            return;
        }
        if (m_cpuRoll < 4) {
            m_command = kCmd623A;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 3) * 0x6e;
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
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k236A || pattern == k236B || pattern == k214A || pattern == k214B || pattern == k214C || pattern == k214214BHit || pattern == k214214C || pattern == k214214CHit || pattern == 0x13b || pattern == 0x13c || pattern == 0x13d)) {
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
        m_cpuAction = 6;
        return;
    }
    if (m_cpuAction == 6 && pattern == kFall) {
        m_cpuAction = 0;
        m_pressB = 1;
        return;
    }
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 0x64) < m_cpuSkill * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (pattern > 0xfc && pattern < 0x103 && m_cpuRoll < 0xfa) {
            m_command = (WORD)Random(0, 3) + kCmd623A;
            return;
        }
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x14) {
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
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 5;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623B;
                return;
            }
            if (m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll < 0x15e) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x398) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x1f3) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 5;
                }
                return;
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x64 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0xc7 && m_cpuRoll < 0x190) {
                m_command = kCmd214B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x1f4 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
            if (m_cpuRoll < (m_attackResult == 3) * 0xc8 + 0xc8) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll < 0x1f4 && m_attackResult == 3 && v10 < 100.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1f3 && m_cpuRoll < 0x226) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x225 && m_cpuRoll < 0x23a && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if (m_cpuRoll > 0x257 && m_cpuRoll < 0x28a) {
                m_command = kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
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
        if (pattern == k5C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x96 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < (m_attackResult == 3) * 0xc8 + 0x64 && (m_rfGauge > 500.0 || m_attackResult == 3)) {
                m_command = (WORD)Random(0, 2) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x78) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x78 && m_cpuRoll < 0x96) {
                m_command = kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0xfa && m_cpuRoll < 0x190 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd236236A;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1cc && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
            if (m_cpuRoll > 0x1cc && m_cpuRoll < 0x1e0 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd641236A;
                return;
            }
            if (m_cpuRoll > 0x38e) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x225) {
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
            if (v10 < 60.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 0x64) < 0x14) {
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
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 5;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if (m_cpuRoll < 0x96 && m_attackResult == 3 && v10 < 100.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll < (m_attackResult == 3) * 0xc8 + 0x12c) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
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
        if (pattern == k2C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_command = kCmd623B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < (m_attackResult == 3) * 0xc8 + 0x64 && (m_rfGauge > 500.0 || m_attackResult == 3)) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x96) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x96 && m_cpuRoll < 0xc8) {
                m_command = (WORD)Random(0, 2) + kCmd214B;
                return;
            }
            if (m_cpuRoll > 0x96 && m_cpuRoll < 0xc8) {
                m_command = (WORD)Random(0, 3) + kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xfa && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (v10 < 100.0 && m_cpuRoll > 0xfa && m_cpuRoll < 0x104 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if (m_cpuRoll < 0x15e) {
                m_pressB = 1;
                return;
            }
            if (v10 < 60.0 && m_cpuRoll < 0x1c2) {
                m_pressA = 1;
                return;
            }
            if (v10 < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x1f4) {
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
            if (m_cpuRoll > 0x3c && m_cpuRoll < 0x64) {
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
        if (pattern == kJumpC && m_cpuRoll > 0x289) {
            m_cpuAction = 3;
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
                if (v10 < 45.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 60.0 && m_cpuRoll < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 140.0 && v10 > 100.0 && m_cpuRoll < 0xf) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 120.0 && m_cpuRoll < 0x14) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 120.0 && v10 > 80.0 && m_cpuRoll < 0x28 && m_cpuRoll > 0x25) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 100.0 && v10 > 80.0 && m_cpuRoll < 0x25) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 80.0 && m_cpuRoll < 0x2a && m_cpuRoll > 0x28) {
                    m_command = kCmd214A;
                    return;
                }
                if (m_cpuRoll < 0x37 && m_cpuRoll > 0x2a) {
                    m_command = facing;
                    m_cpuAction = 5;
                    return;
                }
                if (v10 > 140.0 && m_cpuRoll < 0x3c && m_cpuRoll > 0x37) {
                    m_command = (WORD)Random(0, 3) + kCmd41236A;
                    return;
                }
                if (v10 > 120.0 && m_cpuRoll < 0x42 && m_cpuRoll > 0x3c) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (v10 > 180.0 && m_gauge >= 0xbb8 && m_cpuRoll < 0x44 && m_cpuRoll > 0x42) {
                    m_command = 0xc1;
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
                    if (v10 > 100.0 && v10 < 150.0 && m_cpuRoll < 0xf) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0x11 && m_gauge >= 0x7d0) {
                        m_command = (WORD)Random(0, 1) + kCmd641236B;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 40.0 && x8 < 120.0) {
                        if (m_cpuRoll < (m_rfGauge > 500.0 || m_rfBlue > 0) * 5 + 6) {
                            m_command = kCmd623B;
                            return;
                        }
                    }
                    if (v10 > 100.0 && v10 < 150.0 && (*m_opponent)->y < -60.0 && m_cpuRoll < 0x14) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 50.0 && x8 < 60.0 && m_cpuRoll < 0x11 && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + kCmd214214A;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 70.0 && x8 < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->y == 0.0) * 0x64 + 0x64) {
                        m_pressB = 1;
                        return;
                    }
                }
                if (v10 < 80.0 && x8 > 60.0 && x8 < 80.0 && vy > 0.0 && (*m_opponent)->y > y && m_cpuRoll > 0xc8 && m_cpuRoll < 0xdc) {
                    m_pressC = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 140.0 && (*m_opponent)->y > y && m_cpuRoll < 0xa) {
                    m_pressC = 1;
                    m_inputY = 1;
                    m_inputX = 0;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 140.0 && x8 > 60.0 && m_cpuRoll < 0xfa) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 120.0 && x8 < 90.0 && (*m_opponent)->y > y && m_cpuRoll < 0x10e) {
                    m_pressC = 1;
                    return;
                }
                if (v10 < 140.0 && x8 > 60.0 && m_cpuRoll < 0x15e) {
                    m_pressA = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 1.0f * m_cpuSkill) {
        if (v10 < 100.0) {
            m_command = facing == 1;
        }
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
        if (v10 > 240.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 80.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 140.0 && v10 > 100.0 && y == 0.0) {
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
    if ((WORD)Random(0, 0x64) < 0x28 && v10 < 60.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x1e;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x1e;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x50) {
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

void CAkiko::UpdateObjects()
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
            case kObjShotFlash:
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
            case kObjShotBurst:
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
            case kObjSmallShotStraight:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.05 + 1.25;
                    m_objects[v4].vy = 0.2 - (WORD)Random(0, 8) * 0.05;
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].attackResult != 0) {
                    m_playVoice = 1;
                    m_objects[v4].pattern = kObjShotBurst;
                    m_objects[v4].shadow = 0;
                    m_objects[v4].scale = 2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0) {
                    m_objectVar1[v4]--;
                    if (m_objectVar1[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0xa);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_objectVar1[v4] = 5;
                    }
                }
                m_objects[v4].vx += 0.005;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_playVoice = 1;
                        m_objects[v4].pattern = kObjShotBurst;
                        m_objects[v4].shadow = 0;
                        m_objects[v4].scale = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjSmallShotSpread:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objects[v4].vx = (WORD)Random(0, 5) * 0.05 + 1.4;
                    m_objects[v4].vy = 1.0 - (WORD)Random(0, 0x14) * 0.1;
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].attackResult != 0 || m_objects[v4].y >= 0.0) {
                    m_playVoice = 1;
                    m_objects[v4].pattern = kObjShotBurst;
                    m_objects[v4].shadow = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].scale = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0) {
                    m_objectVar1[v4]--;
                    if (m_objectVar1[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0xa);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_objectVar1[v4] = 5;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_playVoice = 1;
                        m_objects[v4].pattern = kObjShotBurst;
                        m_objects[v4].shadow = 0;
                        m_objects[v4].scale = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjSmallShotAccel:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.05 + 0.0;
                    m_objects[v4].vy = 0.5 - (WORD)Random(0, 0xa) * 0.1;
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].attackResult != 0) {
                    m_playVoice = 1;
                    m_objects[v4].pattern = kObjShotBurst;
                    m_objects[v4].shadow = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].scale = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0) {
                    m_objectVar1[v4]--;
                    if (m_objectVar1[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0xa);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_objectVar1[v4] = 5;
                    }
                }
                m_objects[v4].vx += 0.015;
                if (m_objects[v4].vy < -0.1) {
                    m_objects[v4].vy += 0.01;
                }
                if (m_objects[v4].vy > 0.1) {
                    m_objects[v4].vy -= 0.01;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_playVoice = 1;
                        m_objects[v4].pattern = kObjShotBurst;
                        m_objects[v4].shadow = 0;
                        m_objects[v4].scale = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjBigShotBurst:
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
            case kObjBigShotStraight:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.05 + 1.5;
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                }
                if (m_objects[v4].frame == 1 && m_objects[v4].attackResult != 0) {
                    m_playVoice = 2;
                    m_objects[v4].pattern = kObjBigShotBurst;
                    m_objects[v4].shadow = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].scale = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    ShakeScreen(3, 3);
                    l50.type = 0x1ae;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.scale = 2;
                    l50.type = 0x1af;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1b2;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.keep = 1;
                    l50.layer = 1;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    break;
                }
                if (m_objects[v4].frame == 1) {
                    m_objectVar1[v4]--;
                    if (m_objectVar1[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0x4b);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_objectVar1[v4] = 5;
                    }
                }
                m_objects[v4].vx += 0.005;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2) {
                        m_playVoice = 2;
                        m_objects[v4].pattern = kObjBigShotBurst;
                        m_objects[v4].shadow = 0;
                        m_objects[v4].scale = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        l50.type = 0x1ae;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.keep = 1;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjBigShotSpread:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.05 + 0.0;
                    m_objects[v4].vy = 0.75 - (WORD)Random(0, 0xf) * 0.1;
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].attackResult != 0) {
                    m_playVoice = 2;
                    m_objects[v4].pattern = kObjBigShotBurst;
                    m_objects[v4].shadow = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].scale = 2;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    break;
                }
                if (m_objects[v4].frame == 0) {
                    m_objectVar1[v4]--;
                    if (m_objectVar1[v4] <= 0) {
                        l50.type = 0x19b;
                        l50.x = (double)(int)(m_objects[v4].x - m_objects[v4].facing * 0x14);
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        m_objectVar1[v4] = 5;
                    }
                }
                m_objects[v4].vx += 0.01;
                if (m_objects[v4].vy < -0.1) {
                    m_objects[v4].vy += 0.01;
                }
                if (m_objects[v4].vy > 0.1) {
                    m_objects[v4].vy -= 0.01;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_playVoice = 2;
                        m_objects[v4].pattern = kObjBigShotBurst;
                        m_objects[v4].shadow = 0;
                        m_objects[v4].scale = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjBigShotLob:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                }
                m_objects[v4].vy += 0.015;
                if (m_objects[v4].frame == 0 && (m_objects[v4].attackResult != 0 || m_objects[v4].y + m_objects[v4].vy >= 0.0)) {
                    m_playVoice = 2;
                    m_objects[v4].pattern = kObjLobImpact;
                    m_objects[v4].shadow = 0;
                    m_objects[v4].scale = 2;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    l50.type = 0x1ae;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = 0x1af;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    ShakeScreen(5, 5);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_playVoice = 2;
                        m_objects[v4].scale = 2;
                        m_objects[v4].shadow = 0;
                        m_objects[v4].pattern = kObjLobImpact;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        l50.type = 0x1ae;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.keep = 1;
                        l50.scale = 0;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        ShakeScreen(3, 3);
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjLobImpact:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
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
            case kObjUnused19a:
                m_objects[v4].hitsLeft = 1;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_playVoice = 3;
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
            case kObjShotTrail:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj41236SlamA:
                m_objects[v4].timer++;
                if (m_objects[v4].attackResult == 1) {
                    RemoveObject(v4);
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
            case kObj41236SlamB:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = -2.5;
                }
                m_objects[v4].vy += 0.035;
                m_objects[v4].timer++;
                if (m_objects[v4].attackResult == 1) {
                    RemoveObject(v4);
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
            case kObj214ALauncher:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 5) {
                        l50.type = 0x1a0;
                        l50.keep = 1;
                        l50.x = m_objects[v4].x + m_objects[v4].facing * 0x32;
                        l50.y = m_objects[v4].y + 15.0;
                        l50.facing = m_objects[v4].facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214AField:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 0;
                    m_objectVar1[v4]++;
                }
                if (pattern == k214A && frame == 0) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1a1;
                    l50.x = (double)(int)(m_objects[v4].x + 45.0 - (WORD)Random(0, 0x5a));
                    l50.y = (double)(int)(m_objects[v4].y + 30.0 - (WORD)Random(0, 0x5a));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].x - (*m_opponent)->x > -50.0 && (*m_opponent)->y > -50.0) {
                    if (m_objectVar3[v4] <= 0) {
                        (*m_opponent)->m_rfGauge--;
                        m_objectVar3[v4] = 1;
                    } else {
                        m_objectVar3[v4]--;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].hitsLeft = 0;
                        if (m_objectVar2[v4] < 0xf) {
                            m_objects[v4].frame = 0;
                            m_objectVar2[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObj214Particle:
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
            case kObj214BLauncher:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 5) {
                        l50.type = 0x1a3;
                        l50.keep = 1;
                        l50.x = m_objects[v4].x + m_objects[v4].facing * 0x32;
                        l50.y = m_objects[v4].y + 15.0;
                        l50.facing = m_objects[v4].facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214BField:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 0;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = 0.3;
                }
                if (pattern == k214B && frame == 0) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1a1;
                    l50.x = (double)(int)(m_objects[v4].x + 45.0 - (WORD)Random(0, 0x5a));
                    l50.y = (double)(int)(m_objects[v4].y + 30.0 - (WORD)Random(0, 0x5a));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].x - (*m_opponent)->x > -50.0 && (*m_opponent)->y > -50.0) {
                    if (m_objectVar3[v4] <= 0) {
                        (*m_opponent)->m_rfGauge--;
                        m_objectVar3[v4] = 1;
                    } else {
                        m_objectVar3[v4]--;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].hitsLeft = 0;
                        if (m_objectVar2[v4] < 0x1e) {
                            m_objects[v4].frame = 0;
                            m_objectVar2[v4]++;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObj214CLauncher:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 5) {
                        l50.type = 0x1a5;
                        l50.keep = 1;
                        l50.x = m_objects[v4].x + m_objects[v4].facing * 0x32;
                        l50.y = m_objects[v4].y + 15.0;
                        l50.facing = m_objects[v4].facing;
                        l50.scale = 2;
                        l50.layer = 1;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214CField:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 0xc;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = 1.8;
                }
                if (m_objects[v4].timer == 0) {
                    l50.type = 0x1a1;
                    l50.x = (double)(int)(m_objects[v4].x + 45.0 - (WORD)Random(0, 0x5a));
                    l50.y = (double)-(WORD)Random(0, 0x46);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar2[v4] < 0x1e) {
                            m_objects[v4].frame = 0;
                            m_objectVar2[v4]++;
                            m_objects[v4].attackResult = 0;
                        } else {
                            RemoveObject(v4);
                        }
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case kObj236236ARunIn:
                m_objects[v4].vx = 5.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                }
                if (pattern != k236236A) {
                    m_objectVar1[v4] = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                        RemoveObject(v4);
                        break;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjThrowPusher:
                m_objects[v4].vx = -3.0;
                (*m_opponent)->facing = -m_objects[v4].facing;
                (*m_opponent)->vx = 3.0;
                if ((char)(*m_opponent)->AtScreenEdge() != 0) {
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kHitAir;
                    (*m_opponent)->facing = m_objects[v4].facing;
                    (*m_opponent)->m_hitVx = 0.0;
                    (*m_opponent)->m_hitVy = -2.0;
                    (*m_opponent)->ay = 0.035;
                    (*m_opponent)->y = -59.0;
                    (*m_opponent)->m_noAirRecovery = 1;
                    DealDamage(0x4b0, 500.0);
                    ShakeScreen(3, 3);
                    m_playSound = 2;
                    l50.type = 0x1a1;
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)Random(0, 0x78));
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)Random(0, 0x78));
                    SpawnObject(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)Random(0, 0x78));
                    SpawnObject(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)Random(0, 0x78));
                    SpawnObject(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)Random(0, 0x78));
                    SpawnObject(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)Random(0, 0x78));
                    SpawnObject(&l50);
                    l50.x = (double)(int)(m_objects[v4].x + 60.0 - (WORD)Random(0, 0x78));
                    l50.y = (double)(int)(m_objects[v4].y + 0.0 - (WORD)Random(0, 0x78));
                    SpawnObject(&l50);
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjAirThrowSlam:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 3.0;
                    (*m_opponent)->facing = -m_objects[v4].facing;
                }
                if (m_objects[v4].frame == 0) {
                    (*m_opponent)->pattern = kThrownAirborne;
                    (*m_opponent)->facing = -m_objects[v4].facing;
                    (*m_opponent)->x = m_objects[v4].x + 0.0;
                    (*m_opponent)->y = m_objects[v4].y;
                    (*m_opponent)->m_noAirRecovery = 1;
                    if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 1;
                        (*m_opponent)->x = m_objects[v4].x;
                        (*m_opponent)->y = m_objects[v4].y;
                        (*m_opponent)->StartPattern();
                        (*m_opponent)->pattern = kKnockdown;
                        (*m_opponent)->facing = m_objects[v4].facing;
                        (*m_opponent)->m_noAirRecovery = 1;
                        DealDamage(0x4b0, 750.0);
                        ShakeScreen(3, 3);
                        m_playSound = 2;
                        l50.type = 0;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        m_game->CreateEffect((EffectDesc*)&l50);
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].scale = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Effect:
                m_objects[v4].drawnWhileHidden = 3;
                m_objects[v4].timer++;
                if (pattern == kLv4Hit && frame > 1) {
                    RemoveObject(v4);
                    break;
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
            case kObjLv4Screen:
                m_objects[v4].drawnWhileHidden = 3;
                m_objects[v4].timer++;
                if (pattern == kLv4Hit && frame > 2) {
                    RemoveObject(v4);
                    break;
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
            case kObj236236BRunIn:
                m_objects[v4].vx = 5.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                }
                if (pattern != k236236B) {
                    m_objectVar1[v4] = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                        RemoveObject(v4);
                        break;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj236236CRunIn:
                m_objects[v4].vx = 5.0;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                }
                if (pattern != k236236C) {
                    m_objectVar1[v4] = 1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                        RemoveObject(v4);
                        break;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjDebrisRising:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = -(WORD)Random(0, 0xb4);
                    m_objectVar2[v4] = (WORD)Random(0, 0x14) + 0x1e;
                    m_objectVar3[v4] = 0;
                }
                m_objects[v4].SetVelocity((double)m_objectVar1[v4], m_objectVar2[v4] * 0.1);
                m_objectVar2[v4]--;
                if (m_objectVar2[v4] <= 5) {
                    m_objectVar2[v4] = 5;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjDebrisSparking:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = (WORD)Random(0, 0x168);
                    m_objectVar2[v4] = (WORD)Random(0, 0x28) + 0x32;
                    m_objectVar3[v4] = 0;
                }
                m_objects[v4].SetVelocity((double)m_objectVar1[v4], m_objectVar2[v4] * 0.1);
                m_objectVar2[v4]--;
                if (m_objectVar2[v4] <= 0) {
                    m_objectVar2[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar3[v4] < 6) {
                            m_objectVar3[v4]++;
                            m_objects[v4].frame--;
                            l50.type = 0x191;
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
            case kObjDebris:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = (WORD)Random(0, 0x168);
                    m_objectVar2[v4] = (WORD)Random(0, 0xf) + 0x1e;
                    m_objectVar3[v4] = 0;
                }
                m_objects[v4].SetVelocity((double)m_objectVar1[v4], m_objectVar2[v4] * 0.1);
                m_objectVar2[v4]--;
                if (m_objectVar2[v4] <= 5) {
                    m_objectVar2[v4] = 5;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjDebrisRisingSparking:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = -(WORD)Random(0, 0xb4);
                    m_objectVar2[v4] = (WORD)Random(0, 0x14) + 0x46;
                    m_objectVar3[v4] = 0;
                }
                m_objects[v4].SetVelocity((double)m_objectVar1[v4], m_objectVar2[v4] * 0.1);
                m_objectVar2[v4]--;
                if (m_objectVar2[v4] <= 0) {
                    m_objectVar2[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar3[v4] < 0xa) {
                            m_objectVar3[v4]++;
                            m_objects[v4].frame--;
                            l50.type = 0x191;
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
            case kObjDebrisRisingBursting:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = -(WORD)Random(0, 0xb4);
                    m_objectVar2[v4] = (WORD)Random(0, 0x14) + 0x46;
                    m_objectVar3[v4] = 0;
                }
                m_objects[v4].SetVelocity((double)m_objectVar1[v4], m_objectVar2[v4] * 0.1);
                m_objectVar2[v4]--;
                if (m_objectVar2[v4] <= 0) {
                    m_objectVar2[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar3[v4] < 7) {
                            m_objectVar3[v4]++;
                            m_objects[v4].frame--;
                            l50.type = 0x195;
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
            case kObjDebrisSmall:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = (WORD)Random(0, 0x168);
                    m_objectVar2[v4] = (WORD)Random(0, 0xf) + 0x1e;
                    m_objectVar3[v4] = 0;
                }
                m_objects[v4].SetVelocity((double)m_objectVar1[v4], m_objectVar2[v4] * 0.1);
                m_objectVar2[v4]--;
                if (m_objectVar2[v4] <= 5) {
                    m_objectVar2[v4] = 5;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
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
