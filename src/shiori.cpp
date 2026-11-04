// CShiori (0x422d70-0x43405f), the first of the character classes (its constructor
// copies "shiori" into the name CPlayer's loaders use). Its other methods override
// CPlayer's virtual ones: the per-state update (UpdatePattern, in shiori_vf6.cpp), its
// objects' (UpdateObjects), its gauge (DrawGauge), command recognition from the
// 180-entry input history (ReadCommand) and the CPU player's input (CpuInput).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CShiori::CShiori(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

    strcpy(m_name, "shiori");
    lastSurface = 0x30e;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_summonOut = 0;
    m_dObjectTime = 0;
    m_lv4HoldX = 0;
    m_lv4HoldY = 0;
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
    m_resultPictures = 5;
    m_rivals[0] = 1;
    m_rivals[1] = 7;
    m_rivals[1] = 0xb;
    m_rivals[2] = 0;
    m_rivals[3] = 0xd;
    m_rivals[0xa] = 8;
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
}

void CShiori::Reset()
{
    int i;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_summonOut = 0;
    m_dObjectTime = 0;
    m_lv4HoldX = 0;
    m_lv4HoldY = 0;
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
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
    CPlayer::Reset();
}

void CShiori::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CShiori::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
}

void CShiori::Move()
{
    MoveOnGround();
}

void CShiori::StartCommand()
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
        if (m_hp < 0xd05 && m_command == kCmd236236C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_attackResult != 6 && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd21436C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436C;
            if (y < 0.0) {
                pattern = kAir21436C;
            }
            return;
        }
        if ((m_command == kCmd21436B || m_command == kCmd21436C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436B;
            if (y < 0.0) {
                pattern = kAir21436B;
            }
            return;
        }
        if ((m_command == kCmd21436A || m_command == kCmd21436B || m_command == kCmd21436C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436A;
            if (y < 0.0) {
                pattern = kAir21436A;
            }
            return;
        }
        if (m_command == kCmd641236C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236C;
            return;
        }
        if ((m_command == kCmd641236C || m_command == kCmd641236B) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236B;
            return;
        }
        if ((m_command == kCmd641236A || m_command == kCmd641236B || m_command == kCmd641236C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k641236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k641236A;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214C;
            return;
        }
        if ((m_command == kCmd214214C || m_command == kCmd214214B) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level) {
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
        if (m_command == kCmd412C && (m_rfGauge >= 500.0 || m_rfBlue > 0 || y == 0.0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir412C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir412C;
            if (y == 0.0) {
                pattern = k412C;
            }
            return;
        }
        if ((m_command == kCmd412B || m_command == kCmd412C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir412B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir412B;
            if (y == 0.0) {
                pattern = k412B;
            }
            return;
        }
        if (m_command == kCmd412A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir412A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir412A;
            if (y == 0.0) {
                pattern = k412A;
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
        if (m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
            return;
        }
        if (m_command == kCmd214C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_summonOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            if (y < 0.0) {
                pattern = kAir214C;
            }
            return;
        }
        if ((m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_summonOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            if (y < 0.0) {
                pattern = kAir214B;
            }
            return;
        }
        if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_summonOut == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            if (y < 0.0) {
                pattern = kAir214A;
            }
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
    if (m_sealLevel == 0 && (m_command == kCmdDashLeft || m_command == kCmdDashRight)) {
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
                return;
            }
        }
    }
    if (m_sealLevel < 2 && (m_pressD == 1 || (m_bufferedPress & kInputD) != 0 || (m_dashBufferedPress & kInputD) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k5D].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_dObjectTime == 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
        StartPattern();
        ClearBufferedPress();
        pattern = k5D;
    }
}

void CShiori::DrawGauge()
{
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    if (m_dObjectTime > 0) {
        sprite = *anims[0x2b].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(0x31 - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 0x10f - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_dObjectTime > 0) {
        sprite = *anims[0x2c].frames;
        src = MakeRect(0, 0, m_dObjectTime * sprite.width / 0xe10, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(0x31 - sprite.x, 0x1f - sprite.y, m_dObjectTime * sprite.width / 0xe10, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 0x10f - m_dObjectTime * sprite.width / 0xe10, 0x1f - sprite.y, m_dObjectTime * sprite.width / 0xe10, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
}

void CShiori::PreUpdate()
{
}

void CShiori::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CShiori::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputC) != 0 && step == 7) {
            m_command = kCmd236236C;
            return;
        }
        if ((input & kInputB) != 0 && step == 6) {
            step = 7;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 5) {
            if ((input & kInputB) != 0) {
                step = 7;
            } else {
                step = 6;
            }
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
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge == 0xbb8) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 5) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd21436A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 4) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + 0xa0 + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 5;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 0x3e8) {
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
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 0 && m_gauge >= 0x3e8) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputB) != 0 && step == 6) {
            m_command = kCmd236236B;
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 5) {
            if ((input & kInputB) != 0) {
                m_command = kCmd236236B;
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
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge == 0xbb8) {
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
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 0x3e8) {
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

void CShiori::CpuInput()
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
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd623C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && dx < 80.0 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd641236A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && dx < 150.0 && m_gauge == 0xbb8) {
                m_command = kCmd236236C;
                return;
            }
        }
        if (dx < 220.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = kCmd236236C;
                return;
            }
        }
        if (dx > 220.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = kCmd236236C;
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
            return;
        }
        if (dy < 50.0 && dx < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
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
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k236A || pattern == k236B || pattern == k236C || pattern == kAir214C || pattern == 0x10f || pattern == 0x110)) {
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
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8 && dx < 90.0) {
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
                m_command = kCmd236236C;
                return;
            }
            if (m_cpuRoll > 0x1ae && m_cpuRoll < 0x21c && m_attackResult != 3) {
                m_command = kCmd412A;
                if (dx > 120.0) {
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
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8 && dx < 90.0) {
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
                if (dx > 120.0) {
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
                m_command = (WORD)Random(0, 3) + kCmd641236A;
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
                m_command = kCmd236236C;
                return;
            }
            if (m_cpuRoll > 0x1ae && m_cpuRoll < 0x21c && m_attackResult != 3) {
                m_command = kCmd412A;
                if (dx > 120.0) {
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
                if (dx < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (dx < 50.0 && m_cpuRoll < 0x17) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 75.0 && m_cpuRoll < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 0x28 && m_cpuRoll > 0x1e) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 0x34 && m_cpuRoll > 0x28 || dx > 80.0 && dx < 130.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x34) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx > 80.0 && dx < 140.0 && m_cpuRoll < 0x64 && m_cpuRoll > 0x50) {
                    m_cpuAction = 8;
                    return;
                }
                if (dx > 70.0 && dx < 120.0 && m_cpuRoll < 0x78 && m_cpuRoll > 0x64) {
                    m_cpuAction = 8;
                    return;
                }
                if (dx < 90.0 && dx > 70.0 && m_cpuRoll < 0x82 && m_cpuRoll > 0x78) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 120.0 && dx > 70.0 && m_cpuRoll < 0x91 && m_cpuRoll > 0x82) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx > 100.0 && dx < 140.0 && m_cpuRoll < 0x98 && m_cpuRoll > 0x91) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 0xa5 && m_cpuRoll > 0x91 && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd623C;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 0xaa && m_cpuRoll > 0xa5 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 3) + kCmd641236A;
                    return;
                }
                if (dx > 200.0 && m_cpuRoll < 0xaa && m_cpuRoll > 0xa5 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 3) + 0x82;
                    return;
                }
                if (dx > 200.0 && m_cpuRoll < 0xbe && m_cpuRoll > 0xaa) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (dx > 80.0 && dx < 120.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = kCmd412A;
                    return;
                }
                if (dx > 140.0 && dx < 180.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = kCmd412B;
                    return;
                }
                if (dx > 200.0 && dx < 240.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = kCmd412C;
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
                    if (dx < 80.0 && m_cpuRoll < 0xf && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + kCmd641236A;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 90.0 && dy < 140.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623C;
                        return;
                    }
                    if (dx < 90.0 && dy < 140.0 && dy > 100.0 && m_cpuRoll < 0x23 && m_cpuRoll > 0xa) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx > 100.0 && dx < 140.0 && dy < 180.0 && dy > 140.0 && m_cpuRoll < 0x3c && m_cpuRoll > 0x23) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx > 100.0 && dx < 140.0 && dy < 140.0 && dy > 100.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x3c) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 80.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x50 && (*m_opponent)->y < -50.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + kCmd641236A;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 80.0 && dy < 100.0 && m_cpuRoll < 0x32) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 60.0 && dx < 120.0 && dy > 90.0 && dy < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x32 && m_cpuRoll < 0x78) {
                    m_pressB = 1;
                    return;
                }
                if (dx > 80.0 && dx < 140.0 && dy > 100.0 && dy < 180.0 && m_cpuRoll > 0x78 && m_cpuRoll < 0xaa) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 0x140) < dx - 100.0 && dy < 90.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xdc) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (dx > 100.0 && m_cpuRoll > 0xf0 && m_cpuRoll < 0x14a && dy + 40.0 > dx && dy - 40.0 < dx) {
                    m_command = (WORD)Random(0, 3) + kCmd412A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 80.0 && dy < 100.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 60.0 && dx < 120.0 && dy > 90.0 && dy < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x14 && m_cpuRoll < 0x28) {
                    m_pressB = 1;
                    return;
                }
                if (dx > 80.0 && dx < 140.0 && dy > 100.0 && dy < 180.0 && m_cpuRoll > 0x28 && m_cpuRoll < 0x32) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 0x140) < dx - 100.0 && dy < 180.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xf0) {
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
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && dx > 60.0 && dx < 140.0 && (WORD)Random(0, 0x64) < 2.0f * m_cpuSkill && x > 120.0 && x < 520.0) {
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

void CShiori::UpdateObjects()
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
            case kObj5CEffect:
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
            case kObj236AB:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 3;
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
            case kObjAir412AB:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = 2.0;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0x5f) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 1;
                    m_playSound = 4;
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
            case kObjAir412C:
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = 2.0;
                    m_objects[slot].hitsLeft = 4;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0x5f) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 1;
                    m_playSound = 4;
                    m_objects[slot].timer = 0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjUnusedSummon:
                m_summonOut = 1;
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    RemoveObject(slot);
                    m_summonOut = 0;
                    break;
                }
                if (m_objectVar1[slot] >= 0x208) {
                    m_objects[slot].pattern = kObj214BAttack;
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].scale = 2;
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 5;
                    m_summonOut = 0;
                    break;
                }
                m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objects[slot].vx < -0.7) {
                    m_objects[slot].vx = -0.7;
                } else if (m_objects[slot].vx > 0.7) {
                    m_objects[slot].vx = 0.7;
                }
                if (m_objects[slot].vy < -0.4) {
                    m_objects[slot].vy = -0.4;
                } else if (m_objects[slot].vy > 0.4) {
                    m_objects[slot].vy = 0.4;
                }
                m_objectVar1[slot]++;
                if (m_objects[slot].facing != facing) {
                    m_objects[slot].vx = -m_objects[slot].vx;
                    m_objects[slot].facing = facing;
                }
                if (m_objects[slot].x <= x) {
                    m_objects[slot].ax = facing * 0.01;
                }
                if (m_objects[slot].x > x) {
                    m_objects[slot].ax = facing * -0.01;
                }
                if (m_objects[slot].y <= y - 40.0) {
                    m_objects[slot].ay = 0.01;
                }
                if (m_objects[slot].y > y - 40.0) {
                    m_objects[slot].ay = -0.01;
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
            case kObj214AAppear:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = 0x1b1;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
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
            case kObjAir236AB:
                if (pattern == kAir236A || pattern == kAir236B || pattern == kAir236C) {
                    m_objects[slot].x = facing * 0x24 + x;
                    m_objects[slot].y = y - 48.0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 3;
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
            case kObj214BAttack:
                if (m_objects[slot].frame == 0) {
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
            case kObj214BAppear:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = 0x1b2;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
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
            case 0x19b:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar2[slot] = 0xa0;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = -0.8;
                    m_objects[slot].vy = -2.5;
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy * 0.5;
                }
                if (m_objectVar2[slot] < 0x3c) {
                    m_game->SetGameSpeed(2);
                }
                if (m_objectVar2[slot] < 0x37) {
                    m_game->SetGameSpeed(3);
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
            case kObjSummonDebris1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar2[slot] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = -0.5 - ((rand() > 0x3e80) * 1.2 - (rand() > 0x3e80) * 0.7 - (rand() > 0x3e80) * 1.7);
                    m_objects[slot].vy = -1.2 - ((rand() > 0x3e80) * 0.6 - (rand() > 0x3e80) * 0.5 - (rand() > 0x3e80) * 0.8);
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
            case kObjSummonDebris2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar2[slot] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = -0.5 - ((rand() > 0x3e80) * 1.2 - (rand() > 0x3e80) * 0.7 - (rand() > 0x3e80) * 1.7);
                    m_objects[slot].vy = -1.2 - ((rand() > 0x3e80) * 0.6 - (rand() > 0x3e80) * 0.5 - (rand() > 0x3e80) * 0.8);
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
            case kObjSummonDebris3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar2[slot] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = -0.5 - ((rand() > 0x3e80) * 1.2 - (rand() > 0x3e80) * 0.7 - (rand() > 0x3e80) * 1.7);
                    m_objects[slot].vy = -1.2 - ((rand() > 0x3e80) * 0.6 - (rand() > 0x3e80) * 0.5 - (rand() > 0x3e80) * 0.8);
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
            case kObjSummonDebris4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar2[slot] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = -0.5 - ((rand() > 0x3e80) * 1.2 - (rand() > 0x3e80) * 0.7 - (rand() > 0x3e80) * 1.7);
                    m_objects[slot].vy = -1.2 - ((rand() > 0x3e80) * 0.6 - (rand() > 0x3e80) * 0.5 - (rand() > 0x3e80) * 0.8);
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
            case kObjSummonDebris5:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar2[slot] = (rand() > 0x3e80) * 0x28 + 0x50 + (rand() > 0x3e80) * 0x14;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = -0.5 - ((rand() > 0x3e80) * 1.2 - (rand() > 0x3e80) * 0.7 - (rand() > 0x3e80) * 1.7);
                    m_objects[slot].vy = -1.2 - ((rand() > 0x3e80) * 0.6 - (rand() > 0x3e80) * 0.5 - (rand() > 0x3e80) * 0.8);
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
            case kObj623CEffect:
                if (pattern == k623C) {
                    m_objects[slot].x = facing * 0x17 + x;
                    m_objects[slot].y = y - 48.0;
                }
                if (pattern != k623C) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x18 && frame < 7) {
                        m_objects[slot].frame = 0;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj412Drop:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 2.0;
                    m_objects[slot].ay = 0.035;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                    if (m_objects[slot].attackResult > 1 || m_objects[slot].y >= 0.0) {
                        m_objects[slot].frame = 1;
                        ShakeScreen(3, 0);
                        m_objects[slot].timer = 0;
                        m_playSound = 0x22;
                        m_objects[slot].vy = 0.0;
                    }
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
            case kObjLv4Start:
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 0.5;
                    m_objects[slot].vy = -0.4;
                    m_objectVar1[slot]++;
                }
                m_objects[slot].vy += 0.005;
                if (m_objectVar1[slot] > 0xa) {
                    m_objects[slot].scale = 1;
                }
                if (m_objectVar1[slot] > 0xf) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                }
                break;
            case kObj214214AHit:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0xe && m_objects[slot].timer == 0) {
                    m_playVoice = 7;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObj214214HitEnd;
                    }
                }
                break;
            case kObj214214BHit:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0xe && m_objects[slot].timer == 0) {
                    m_playVoice = 7;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObj214214HitEnd;
                    }
                }
                break;
            case kObj214214CHit:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0xe && m_objects[slot].timer == 0) {
                    m_playVoice = 7;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObj214214HitEnd;
                    }
                }
                break;
            case kObj5D:
                m_objects[slot].x = x;
                m_objects[slot].y = y - 50.0;
                m_objects[slot].hitsLeft = 1;
                if (m_dObjectTime < 0 && m_objects[slot].frame < 0x1c) {
                    m_objects[slot].frame = 0x1c;
                    m_objects[slot].timer = 0;
                    m_dObjectTime = 0;
                    break;
                }
                m_objects[slot].facing = facing;
                m_objects[slot].attackResult = 0;
                m_dObjectTime -= 4;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x1c) {
                        m_objects[slot].frame = 8;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_dObjectTime = 0;
                        break;
                    }
                }
                break;
            case kObjUnused5DLv2:
                m_objects[slot].x = x;
                m_objects[slot].y = y - 50.0;
                m_objects[slot].hitsLeft = 1;
                if (m_dObjectTime < 0 && m_objects[slot].frame < 0x1c) {
                    m_objects[slot].frame = 0x1c;
                    m_objects[slot].timer = 0;
                    m_dObjectTime = 0;
                    break;
                }
                m_objects[slot].facing = facing;
                m_objects[slot].attackResult = 0;
                m_dObjectTime -= 3;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x1c) {
                        m_objects[slot].frame = 8;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_dObjectTime = 0;
                        break;
                    }
                }
                break;
            case kObjUnused5DLv3:
                m_objects[slot].x = x;
                m_objects[slot].y = y - 50.0;
                m_objects[slot].hitsLeft = 1;
                if (m_dObjectTime < 0 && m_objects[slot].frame < 0x1c) {
                    m_objects[slot].frame = 0x1c;
                    m_objects[slot].timer = 0;
                    m_dObjectTime = 0;
                    break;
                }
                m_objects[slot].facing = facing;
                m_objects[slot].attackResult = 0;
                m_dObjectTime -= 2;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x1c) {
                        m_objects[slot].frame = 8;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_dObjectTime = 0;
                        break;
                    }
                }
                break;
            case kObj236C:
                if (m_objects[slot].frame == 0) {
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
            case kObjAir236C:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    if (m_patternVar3 == 0) {
                        m_objectVar1[slot] = 0x1d;
                        m_objectVar2[slot] = -0x34;
                    }
                    if (m_patternVar3 == 1) {
                        m_objectVar1[slot] = 0x24;
                        m_objectVar2[slot] = -0x26;
                    }
                    if (m_patternVar3 == 2) {
                        m_objectVar1[slot] = 0x24;
                        m_objectVar2[slot] = -0x48;
                    }
                }
                if (pattern == kAir236A || pattern == kAir236B || pattern == kAir236C) {
                    m_objects[slot].x = facing * m_objectVar1[slot] + x;
                    m_objects[slot].y = m_objectVar2[slot] + y;
                }
                if (m_objects[slot].frame == 0) {
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
            case kObj641236Column:
                if (m_objects[slot].frame == 0x1c && m_objects[slot].timer == 0 && frame < 0x10 && pattern > kFirstCharacterAction) {
                    effect.keep = 1;
                    effect.type = 0x1ad;
                    effect.x = (double)((int)x - facing * 0xf);
                    effect.y = m_objects[slot].y;
                    effect.facing = facing;
                    effect.scale = 2;
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
                break;
            case kObj641236Foot:
                if (m_objects[slot].frame == 8 && m_objects[slot].timer == 0 && frame < 0x10 && pattern > kFirstCharacterAction) {
                    effect.keep = 1;
                    effect.type = 0x1ae;
                    effect.x = (double)((int)x - facing * 0xf);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.scale = 2;
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
                break;
            case kObj641236CFoot:
                if (m_objects[slot].frame == 8 && m_objects[slot].timer == 0 && frame < 0x10 && pattern > kFirstCharacterAction) {
                    effect.keep = 1;
                    effect.type = 0x1af;
                    effect.x = (double)((int)x - facing * 0xf);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.scale = 2;
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
                break;
            case kObj214214HitEnd:
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
            case kObj214A:
                m_summonOut = 1;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    effect.type = 0x19c;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x19d;
                    SpawnObject(&effect);
                    effect.type = 0x19e;
                    SpawnObject(&effect);
                    effect.type = 0x19f;
                    SpawnObject(&effect);
                    effect.type = 0x1a0;
                    SpawnObject(&effect);
                    RemoveObject(slot);
                    m_summonOut = 0;
                    break;
                }
                if (m_objects[slot].frame < 4) {
                    m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                    if (m_objects[slot].vx < -0.7) {
                        m_objects[slot].vx = -0.7;
                    } else if (m_objects[slot].vx > 0.7) {
                        m_objects[slot].vx = 0.7;
                    }
                    if (m_objects[slot].vy < -0.4) {
                        m_objects[slot].vy = -0.4;
                    } else if (m_objects[slot].vy > 0.4) {
                        m_objects[slot].vy = 0.4;
                    }
                    if (m_objects[slot].facing != facing) {
                        m_objects[slot].vx = -m_objects[slot].vx;
                        m_objects[slot].facing = facing;
                    }
                    if (m_objects[slot].x <= x) {
                        m_objects[slot].ax = facing * 0.01;
                    }
                    if (m_objects[slot].x > x) {
                        m_objects[slot].ax = facing * -0.01;
                    }
                    if (m_objects[slot].y <= y - 40.0) {
                        m_objects[slot].ay = 0.01;
                    }
                    if (m_objects[slot].y > y - 40.0) {
                        m_objects[slot].ay = -0.01;
                    }
                }
                if (m_objects[slot].frame > 3) {
                    m_objects[slot].vx -= 0.15;
                    if (m_objects[slot].vx < 0.1) {
                        m_objects[slot].vx = 0.1;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 4 && m_objectVar1[slot] < 1) {
                        m_objects[slot].frame = 0;
                        m_objectVar1[slot]++;
                        return;
                    }
                    if (m_objects[slot].frame == 4) {
                        m_objects[slot].hitsLeft = 1;
                        m_objects[slot].vx = 4.0;
                        m_objects[slot].vy = 0.0;
                        m_playSound = 0x14;
                        return;
                    }
                    if (m_objects[slot].frame == 7 && m_objectVar1[slot] < 3) {
                        m_objects[slot].frame = 3;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 8) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_summonOut = 0;
                    }
                }
                break;
            case kObj214B:
                m_summonOut = 1;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    effect.type = 0x19c;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x19d;
                    SpawnObject(&effect);
                    effect.type = 0x19e;
                    SpawnObject(&effect);
                    effect.type = 0x19f;
                    SpawnObject(&effect);
                    effect.type = 0x1a0;
                    SpawnObject(&effect);
                    RemoveObject(slot);
                    m_summonOut = 0;
                    break;
                }
                if (m_objects[slot].frame < 4) {
                    m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                    if (m_objects[slot].vx < -0.8) {
                        m_objects[slot].vx = -0.8;
                    } else if (m_objects[slot].vx > 0.8) {
                        m_objects[slot].vx = 0.8;
                    }
                    if (m_objects[slot].vy < -0.4) {
                        m_objects[slot].vy = -0.4;
                    } else if (m_objects[slot].vy > 0.4) {
                        m_objects[slot].vy = 0.4;
                    }
                    if (m_objects[slot].facing != facing) {
                        m_objects[slot].vx = -m_objects[slot].vx;
                        m_objects[slot].facing = facing;
                    }
                    if (m_objects[slot].x <= x) {
                        m_objects[slot].ax = facing * 0.01;
                    }
                    if (m_objects[slot].x > x) {
                        m_objects[slot].ax = facing * -0.01;
                    }
                    if (m_objects[slot].y <= y - 40.0) {
                        m_objects[slot].ay = 0.01;
                    }
                    if (m_objects[slot].y > y - 40.0) {
                        m_objects[slot].ay = -0.01;
                    }
                }
                if (m_objects[slot].frame > 3) {
                    m_objects[slot].vx -= 0.15;
                    if (m_objects[slot].vx < 0.1) {
                        m_objects[slot].vx = 0.1;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 4 && m_objectVar1[slot] < 2) {
                        m_objects[slot].frame = 0;
                        m_objectVar1[slot]++;
                        return;
                    }
                    if (m_objects[slot].frame == 5 && m_objectVar1[slot] < 3) {
                        m_objects[slot].frame--;
                        m_objectVar1[slot]++;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        effect.type = 0x199;
                        effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 0x13);
                        effect.y = (double)((int)m_objects[slot].y + 2);
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.facing = facing;
                        SpawnObject(&effect);
                        m_playVoice = 5;
                    }
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_summonOut = 0;
                    }
                }
                break;
            case kObj21436Shot:
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
#ifdef EFZ_NATIVE
                    // The original computes the arguments right to left, so the speed draws first.
                    {
                        double speed = (WORD)Random(0x1e, 0x19) * 0.1;
                        m_objects[slot].SetVelocity((double)((WORD)Random(0, 0x5a) - 0x2d), speed);
                    }
#else
                    m_objects[slot].SetVelocity((double)((WORD)Random(0, 0x5a) - 0x2d), (WORD)Random(0x1e, 0x19) * 0.1);
#endif
                }
                if (m_objects[slot].x > 660.0 || m_objects[slot].x < -20.0) {
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
            case kObj21436Flash:
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
            case kObj214214AMover:
                m_objects[slot].vx = 1.0;
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.keep = 0;
                    effect.type = 0x1a4;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] < 2) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame = 0;
                            break;
                        }
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214214BMover:
                if (m_objectVar3[slot] == 0) {
                    m_objects[slot].vx = 1.5;
                    m_objectVar3[slot]++;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.keep = 0;
                    effect.type = 0x1a5;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 0.0;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] < 5) {
                            m_objectVar1[slot]++;
                            m_objects[slot].vx += 0.5;
                            m_objects[slot].frame = 0;
                            break;
                        }
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214214CMover:
                if (m_objectVar3[slot] == 0) {
                    m_objects[slot].vx = 1.5;
                    m_objectVar3[slot]++;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.keep = 0;
                    effect.type = 0x1a6;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = 10.0;
                    effect.layer = 1;
                    if (m_objectVar2[slot] == 1) {
                        effect.y = -10.0;
                        effect.layer = 0;
                    }
                    effect.facing = facing;
                    effect.scale = 2;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] < 0xe) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame = 0;
                            m_objects[slot].vx += 0.4;
                            if (m_objectVar2[slot] == 0) {
                                m_objectVar2[slot] = 1;
                            } else {
                                m_objectVar2[slot] = 0;
                            }
                            break;
                        }
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4:
                FocusCameraY(0x32, 3);
                m_objects[slot].x = facing * 0x14 + x;
                m_objects[slot].y = y - 52.0;
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 0x63;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjLv4Wait;
                    }
                }
                break;
            case kObjLv4Wait:
                m_objects[slot].x = facing * 0x14 + x;
                m_objects[slot].y = y - 52.0;
                FocusCameraY(0x32, 3);
                FillBackground(0xb0, 3);
                if (pattern != kLv4) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjLv4End;
                    break;
                }
                if (m_objects[slot].attackResult == 3 && pattern == kLv4) {
                    m_objects[slot].pattern = kObjLv4Hold;
                    m_lv4HoldX = (int)(*m_opponent)->x;
                    m_lv4HoldY = (int)(*m_opponent)->y;
                    StartPattern();
                    pattern = kLv4Connected;
                    break;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 0x63;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] == 0) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame = 0;
                            break;
                        }
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjLv4End;
                    }
                }
                break;
            case kObjLv4End:
                m_objects[slot].x = facing * 0x14 + x;
                m_objects[slot].y = y - 52.0;
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
            case kObjLv4Toss:
                m_hideOffscreenMarker = 3;
                if (m_objects[slot].frame > 6) {
                    (*m_opponent)->FocusCameraY(0x32, 3);
                }
                if (m_objects[slot].frame < 7) {
                    (*m_opponent)->StopMoving();
                }
                FillBackground(0xb0, 3);
                if (m_objects[slot].frame > 0xb) {
                    m_objects[slot].vy += 0.055;
                    if (m_objects[slot].vy > 0.0) {
                        m_objects[slot].vy = 0.0;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame < 7) {
                        (*m_opponent)->x = m_lv4HoldX + (WORD)Random(0, 0x50) + -0x28;
                        (*m_opponent)->y = m_lv4HoldY - (WORD)Random(0xa, 0x3c);
                        if ((*m_opponent)->x > 620.0) {
                            (*m_opponent)->x = 620.0;
                        }
                        if ((*m_opponent)->x < 20.0) {
                            (*m_opponent)->x = 20.0;
                        }
                        if ((*m_opponent)->y > -10.0) {
                            (*m_opponent)->y = -10.0;
                        }
                    }
                    if (m_objects[slot].frame == 7) {
                        (*m_opponent)->ay = 0.035;
                        (*m_opponent)->vy = -10.5;
                        (*m_opponent)->vx = 0.5;
                    }
                    if (m_objects[slot].frame == 9) {
                        (*m_opponent)->x = m_objects[slot].x + m_objects[slot].facing * 0xdd;
                        (*m_opponent)->y = m_objects[slot].y - 44.0;
                    }
                    if (m_objects[slot].frame == 0xa) {
                        (*m_opponent)->x = m_objects[slot].x + m_objects[slot].facing * 0xe6;
                        (*m_opponent)->y = m_objects[slot].y - 62.0;
                    }
                    if (m_objects[slot].frame == 0xb) {
                        (*m_opponent)->x = m_objects[slot].x + m_objects[slot].facing * 0xa3;
                        (*m_opponent)->y = m_objects[slot].y - 119.0;
                    }
                    if (m_objects[slot].frame == 0xc) {
                        (*m_opponent)->x = m_objects[slot].x + m_objects[slot].facing * 0x8b;
                        (*m_opponent)->y = m_objects[slot].y - 160.0;
                        m_objects[slot].vy = -3.0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] == 0) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame = 0;
                            break;
                        }
                        RemoveObject(slot);
                        timer = 0x23a;
                    }
                }
                break;
            case kObjLv4Hold:
                FocusCameraY(0x32, 3);
                (*m_opponent)->StopMoving();
                FillBackground(0xb0, 3);
                (*m_opponent)->m_invulTime = 0x1e;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    (*m_opponent)->x = m_lv4HoldX + (WORD)Random(0, 0x50) + -0x28;
                    (*m_opponent)->y = m_lv4HoldY - (WORD)Random(0xa, 0x3c);
                    if ((*m_opponent)->x > 620.0) {
                        (*m_opponent)->x = 620.0;
                    }
                    if ((*m_opponent)->x < 20.0) {
                        (*m_opponent)->x = 20.0;
                    }
                    if ((*m_opponent)->y > -5.0) {
                        (*m_opponent)->y = -5.0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] == 0) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame = 0;
                            break;
                        }
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjLv4Toss;
                    }
                }
                break;
            case kObjLv4Finish:
                m_objects[slot].y = (*m_opponent)->y;
                m_objects[slot].x = (*m_opponent)->x;
                if (pattern == kLv4Connected && frame == 3) {
                    (*m_opponent)->facing = -facing;
                    DealDamage(0x1388, 700.0);
                    ShakeScreen(8, 5);
                    m_game->SetGameSpeed(1);
                    (*m_opponent)->m_hitstop = 0;
                    (*m_opponent)->pattern = kHitAirLaunch;
                    (*m_opponent)->frame = 0;
                    (*m_opponent)->timer = 0;
                    (*m_opponent)->m_hitVx = -0.2;
                    (*m_opponent)->m_hitVy = -1.0;
                    (*m_opponent)->m_noAirRecovery = 1;
                    effect.type = 0x34;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)((int)m_objects[slot].y - 0x28);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.sound = 0x16;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    effect.type = 0x1be;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1bf;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1c0;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1c1;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                m_objectVar2[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObjLv4Piece1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = -1.0;
                    m_objects[slot].vy = -1.0;
                }
                m_objects[slot].vy += 0.035;
                m_objects[slot].timer++;
                m_objectVar2[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        if (m_objects[slot].scale == 1) {
                            RemoveObject(slot);
                            break;
                        }
                        if (m_objects[slot].scale == 0) {
                            m_objects[slot].scale = 1;
                        }
                    }
                }
                break;
            case kObjLv4Piece2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = -0.7;
                    m_objects[slot].vy = -0.5;
                }
                m_objects[slot].vy += 0.035;
                m_objects[slot].timer++;
                m_objectVar2[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        if (m_objects[slot].scale == 1) {
                            RemoveObject(slot);
                            break;
                        }
                        if (m_objects[slot].scale == 0) {
                            m_objects[slot].scale = 1;
                        }
                    }
                }
                break;
            case kObjLv4Piece3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = 0.85;
                    m_objects[slot].vy = -0.7;
                }
                m_objects[slot].vy += 0.035;
                m_objects[slot].timer++;
                m_objectVar2[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        if (m_objects[slot].scale == 1) {
                            RemoveObject(slot);
                            break;
                        }
                        if (m_objects[slot].scale == 0) {
                            m_objects[slot].scale = 1;
                        }
                    }
                }
                break;
            case kObjLv4Piece4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = 0.1;
                    m_objects[slot].vy = -0.9;
                }
                m_objects[slot].vy += 0.035;
                m_objects[slot].timer++;
                m_objectVar2[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        if (m_objects[slot].scale == 1) {
                            RemoveObject(slot);
                            break;
                        }
                        if (m_objects[slot].scale == 0) {
                            m_objects[slot].scale = 1;
                        }
                    }
                }
                break;
            case kObjAir214BAppear:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = 0x1c3;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
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
            case kObjAir214B:
                m_summonOut = 1;
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    effect.type = 0x19c;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                    effect.type = 0x19d;
                    SpawnObject(&effect);
                    effect.type = 0x19e;
                    SpawnObject(&effect);
                    effect.type = 0x19f;
                    SpawnObject(&effect);
                    effect.type = 0x1a0;
                    SpawnObject(&effect);
                    RemoveObject(slot);
                    m_summonOut = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 4 && m_objectVar1[slot] < 2) {
                        m_objects[slot].frame = 0;
                        m_objectVar1[slot]++;
                        return;
                    }
                    if (m_objects[slot].frame == 5 && m_objectVar1[slot] < 3) {
                        m_objects[slot].frame--;
                        m_objectVar1[slot]++;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        effect.type = 0x199;
                        effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 0x13);
                        effect.y = (double)((int)m_objects[slot].y + 2);
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.facing = m_objects[slot].facing;
                        SpawnObject(&effect);
                        m_playVoice = 5;
                    }
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_summonOut = 0;
                    }
                }
                break;
            case kObj214CAppear:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = 0x1c6;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
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
            case kObj214CStop:
                m_summonOut = 1;
                m_objects[slot].hitsLeft = 1;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0xc || m_objects[slot].frame == 0x18) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == 0x18 && m_objectVar1[slot] < 3) {
                        m_objects[slot].frame = 0;
                        m_objectVar1[slot]++;
                        break;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_summonOut = 0;
                    }
                }
                break;
            case kObj214C:
                m_summonOut = 1;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    effect.type = 0x19c;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x19d;
                    SpawnObject(&effect);
                    effect.type = 0x19e;
                    SpawnObject(&effect);
                    effect.type = 0x19f;
                    SpawnObject(&effect);
                    effect.type = 0x1a0;
                    SpawnObject(&effect);
                    RemoveObject(slot);
                    m_summonOut = 0;
                    break;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 1.65;
                    m_objects[slot].vy = 0.5;
                }
                m_objects[slot].vx -= 0.01;
                m_objects[slot].vy -= 0.013;
                if (m_objects[slot].vx < 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] < 0) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame = 0;
                            break;
                        }
                        m_objects[slot].pattern = kObj214CStop;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].scale = 2;
                        m_objects[slot].attackResult = 0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objectVar1[slot] = 0;
                        break;
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
