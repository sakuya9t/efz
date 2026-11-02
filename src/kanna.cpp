// CKanna (0x675c80-0x68354f): the character class whose files are in kanna\ in the game
// folder (kanna.dat sprites, kanna.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CKanna::CKanna(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "kanna");
    lastSurface = 0x4db;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_airMoveDelay = 0x3c;
    m_pointX[0] = -4;
    m_pointY[0] = -0x3b;
    m_pointX[1] = 0x1b;
    m_pointY[1] = 0;
    m_pointX[2] = 0xb;
    m_pointY[2] = -0x12;
    m_pointX[3] = 0xb;
    m_pointY[3] = -0xd;
    m_pointX[4] = 0x21;
    m_pointY[4] = -0x23;
    m_resultPictures = 4;
    m_rivals[0] = 1;
    m_rivals[1] = 6;
    m_rivals[2] = 0x17;
    m_rivals[3] = 0x10;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
}

void CKanna::Reset()
{
    int v4;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_airMoveDelay = 0x3c;
    m_pointX[0] = -0xd;
    m_pointY[0] = -0x3c;
    m_pointX[1] = 0xe;
    m_pointY[1] = 0;
    m_pointX[2] = 0x11;
    m_pointY[2] = -6;
    m_pointX[3] = 7;
    m_pointY[3] = -0x19;
    m_pointX[4] = 0x1b;
    m_pointY[4] = -0x19;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
    CPlayer::Reset();
}

void CKanna::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CKanna::RemoveObject(short p1)
{
    m_objectVar1[p1] = 0;
    m_objectVar2[p1] = 0;
    m_objectVar3[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CKanna::Move()
{
    if (y == 0.0) {
        m_airDashes = 0;
        m_airActions = 0;
    }
    if (y >= 0.0 && pattern != kJump && pattern != kJumpForward && pattern != kJumpBack && pattern != kSuperJump && pattern != kSuperJumpForward && pattern != kSuperJumpBack) {
        if (m_sealLevel < 3 && m_inputY == -1) {
            FaceOpponent();
            if (m_command >= 3 && m_command <= 5) {
                if (m_command == 3) {
                    if (pattern != kSuperJump) {
                        StartPattern();
                    }
                    pattern = kSuperJump;
                    return;
                }
                if (m_command == 4) {
                    if (pattern != kSuperJumpForward) {
                        StartPattern();
                    }
                    pattern = kSuperJumpForward;
                    return;
                }
                if (m_command == 5) {
                    if (pattern != kSuperJumpBack) {
                        StartPattern();
                    }
                    pattern = kSuperJumpBack;
                    return;
                }
            } else {
                if (m_inputX == 0) {
                    if (pattern != kJump) {
                        StartPattern();
                    }
                    pattern = kJump;
                    return;
                }
                if (m_inputX == facing) {
                    if (pattern != kJumpForward) {
                        StartPattern();
                    }
                    pattern = kJumpForward;
                    return;
                }
                if (m_inputX == -facing) {
                    if (pattern != kJumpBack) {
                        StartPattern();
                    }
                    pattern = kJumpBack;
                    return;
                }
            }
        }
        if (m_inputY == 1) {
            if (pattern != kCrouchDown && pattern != kCrouch) {
                pattern = kCrouchDown;
                StartPattern();
                FaceOpponent();
                return;
            }
            if (pattern != kCrouchDown) {
                pattern = kCrouch;
                FaceOpponent();
                return;
            }
            return;
        }
        if (m_inputX != 0) {
            FaceOpponent();
            if (m_inputX == facing) {
                if (pattern != kStand && pattern != kWalkForward && pattern != kWalkBack) {
                    StartPattern();
                }
                pattern = kWalkForward;
                return;
            }
            if (pattern != kStand && pattern != kWalkForward && pattern != kWalkBack) {
                StartPattern();
            }
            pattern = kWalkBack;
            return;
        }
        if (pattern == kCrouch || pattern == kCrouchDown) {
            pattern = kStandUp;
            FaceOpponent();
            StartPattern();
            return;
        }
        if (pattern == kStandUp || pattern == kLand) {
            FaceOpponent();
            return;
        }
        if (pattern != kStand && pattern != kWalkForward && pattern != kWalkBack) {
            StartPattern();
        }
        pattern = kStand;
        FaceOpponent();
    }
}

void CKanna::StartCommand()
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
        if (m_command == kCmd236236C && m_gauge >= 0xbb8 && m_hp < 0xd05 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd236236B && m_gauge >= 0xbb8 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir236236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236236B;
            return;
        }
        if (m_command == kCmd236236A && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236A;
            return;
        }
        if (m_command == kCmd236236B && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236B;
            return;
        }
        if (m_command == kCmd41236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236C;
            return;
        }
        if ((m_command == kCmd41236B || m_command == kCmd41236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236;
            return;
        }
        if (m_command == kCmd41236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236;
            return;
        }
        if (m_command == kCmd623C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623C;
            return;
        }
        if ((m_command == kCmd623A || m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623;
            return;
        }
        if (m_command == kCmd214C && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            return;
        }
        if (m_command == kCmd214B && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level) {
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
        if ((m_command == kCmd236A || m_command == kCmd236B || m_command == kCmd236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236;
            if (y < 0.0) {
                pattern = kAir236;
            }
            return;
        }
    }
    if (m_sealLevel < 1 && (m_command == kCmdDashLeft || m_command == kCmdDashRight) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0) {
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
            if (m_patterns[pattern].cancelLevel <= m_patterns[k5BClose].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && x - (*m_opponent)->x > -110.0 && x - (*m_opponent)->x < 110.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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
        if ((m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) && m_patterns[pattern].cancelLevel <= m_patterns[k5C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k5C;
        }
    }
}

void CKanna::DrawGauge()
{
}

void CKanna::PreUpdate()
{
}

void CKanna::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CKanna::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = kCmdNone;
    x6 = 0;
    v4 = m_inputPos + 0x6e;
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
    v4 = m_inputPos + 0x7d;
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
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 0) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x7d;
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
    v4 = m_inputPos + 0x7d;
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
    v4 = m_inputPos + 0x7d;
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
        if ((v5 & 0xf) == 0 && x6 == 0) {
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
    v4 = m_inputPos + 0x5a;
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
    v4 = m_inputPos + 0x5a;
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

void CKanna::CpuInput()
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
    m_cpuHitCooldown--;
    m_cpuAirPause--;
    if (m_cpuHitCooldown < 0) {
        m_cpuHitCooldown = 0;
    }
    if (pattern > kLastFreeAction && pattern < 0xa1) {
        m_cpuHitCooldown = 0xb4;
    }
    if (m_cpuAirPause < 0) {
        m_cpuAirPause = 0;
    }
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
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 45.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && v10 > 60.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
            m_pressB = 1;
            m_inputY = 1;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if ((WORD)Random(0, 0x1f40) < m_cpuSkill * m_cpuSkill * 4.0f && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (v10 < 20.0) {
            if ((WORD)Random(0, 0x708) < m_cpuSkill * 4.0f && m_rfGauge > 500.0) {
                m_command = kCmd623A;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5c;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && v10 < 120.0 && m_gauge >= 0x7d0) {
                m_command = kCmd236236B;
                return;
            }
        }
        if (v10 < 150.0 && v10 > 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if (v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8 && (*m_opponent)->pattern < 0xdc) {
                m_command = kCmd236236A;
                return;
            }
        }
        if (v10 > 150.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_command = kCmd236236A;
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
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < -50.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
            m_command = (WORD)Random(0, 2) + kCmd236A;
            return;
        }
        if ((WORD)Random(0, 0x3e8) < m_cpuSkill * 2) {
            m_command = kCmd236236A;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0xbb8) {
            m_command = kCmd236236A;
            return;
        }
        if (m_cpuRoll < 0x12 && m_cpuRoll > 0x14 && m_gauge == 0xbb8) {
            m_command = kCmd236236B;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (m_cpuRoll < 2 && m_gauge >= 0xbb8) {
            m_command = kCmd236236A;
            return;
        }
        if (m_cpuRoll < 4 && m_gauge >= 0xbb8) {
            m_command = kCmd236236B;
            return;
        }
        if (m_cpuRoll > 0x3a) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k623 || pattern == kUnusedDashC && (WORD)Random(0, 0xa) == 0 || pattern == kUnusedDash2C && (WORD)Random(0, 7) == 0)) {
        m_command = kCmd22C;
        return;
    }
    if (y == 0.0 && pattern < kJump && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kFirstGuard && m_cpuAction == 0) {
        if ((*m_opponent)->y < 0.0 && x8 < 100.0 && v10 < 130.0 && ((*m_opponent)->m_untechTime > 0x18 || (*m_opponent)->m_noAirRecovery == 1 || (*m_opponent)->pattern == kHitShock && (*m_opponent)->frame < 4)) {
            m_cpuAction = 0x1f;
            return;
        }
        if ((*m_opponent)->y < 0.0 && x8 < 50.0 && v10 < 70.0 && ((*m_opponent)->m_untechTime > 0x12 || (*m_opponent)->m_noAirRecovery == 1 || (*m_opponent)->pattern == kHitShock && (*m_opponent)->frame < 4)) {
            m_cpuAction = 0x1e;
            return;
        }
        if ((*m_opponent)->pattern == kHitWallBounce && m_gauge >= 0xbb8 && (WORD)Random(0, 0) != 0) {
            if (v10 < 150.0) {
                m_command = kCmd236236B;
                return;
            }
            if (v10 > 150.0) {
                m_command = kCmd236236A;
                return;
            }
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
    if (m_cpuAction == 3 && pattern == kLand) {
        m_cpuAction = 0;
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
        m_inputX = 0;
        m_inputY = -1;
        if (pattern == kJump) {
            m_cpuAction = 8;
        }
        return;
    }
    if (m_cpuAction == 7 && pattern < kFirstHitReaction) {
        m_inputX = facing;
        m_inputY = -1;
        if (pattern == kJumpForward) {
            m_cpuAction = 8;
        }
        return;
    }
    if (m_cpuAction == 8 && pattern < kFirstHitReaction) {
        m_inputX = facing;
        m_inputY = 1;
        if (pattern == 0x12) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 9 && pattern < kFirstHitReaction) {
        m_inputX = facing;
        m_inputY = -1;
        if (pattern == kJumpForward) {
            m_cpuAction = 0xa;
        }
        return;
    }
    if (m_cpuAction == 0xa && pattern < kFirstHitReaction) {
        m_pressB = 1;
        if (pattern == kJumpB || y == 0.0) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xb && pattern < kFirstHitReaction) {
        m_inputX = 0;
        m_inputY = -1;
        if (pattern == kJump) {
            m_cpuAction = 0xc;
        }
        return;
    }
    if (m_cpuAction == 0xc && pattern < kFirstHitReaction) {
        m_pressA = 1;
        if (pattern == kJumpA || y == 0.0) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xd && pattern < kFirstHitReaction) {
        m_pressA = 1;
        if (pattern == kJumpB || y == 0.0) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xe) {
        m_inputY = -1;
        m_inputX = facing;
        if (pattern == kJumpForward) {
            m_cpuAction = 0xf;
        }
        return;
    }
    if (m_cpuAction == 0xf) {
        if ((*m_opponent)->m_untechTime <= 0) {
            m_cpuAction = 0;
        }
        if (x8 < 80.0 && (*m_opponent)->y < y) {
            m_pressA = 1;
            if (pattern == kJumpA) {
                m_cpuAction = 0x10;
                return;
            }
        }
        if (x8 < 100.0) {
            m_pressB = 1;
            if ((*m_opponent)->m_untechTime < 0x18) {
                m_pressA = 1;
            }
            if (pattern == kJumpB || pattern == kJumpA) {
                m_cpuAction = 0x10;
                return;
            }
        }
        return;
    }
    if (m_cpuAction == 0x10) {
        if ((*m_opponent)->m_untechTime <= 0) {
            m_cpuAction = 0;
        }
        if (pattern == kJumpA && m_attackResult == 3) {
            m_pressB = 1;
            return;
        }
        if (pattern == kJumpB) {
            m_cpuAction = 0x11;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x11) {
        if ((*m_opponent)->m_untechTime <= 0 || y == 0.0) {
            m_cpuAction = 0;
        }
        if ((WORD)Random(0, 0xc8) == 1 && m_gauge == 0xbb8) {
            m_command = kCmd236236B;
            return;
        }
        if (pattern == kJumpC) {
            m_cpuAction = 0;
            return;
        }
        if (pattern == kAir236) {
            m_cpuAction = 0;
            return;
        }
        if (pattern == kAirDashForward) {
            m_cpuAction = 0x14;
            return;
        }
        if (pattern == kAirJumpForward) {
            m_cpuAction = 0x14;
            return;
        }
        if (pattern == kJumpB && m_attackResult == 3 && frame > 5) {
            if (v10 > 80.0 && vx < 0.0 && (*m_opponent)->y - y > -40.0) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->m_untechTime < 0x2d && m_airActions > 0 && x8 < 40.0 && (*m_opponent)->y - y < 0.0) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->m_untechTime < 0x2d && vx >= 0.0) {
                m_pressC = 1;
                return;
            }
            if ((x8 < 20.0 && (*m_opponent)->y > y || (*m_opponent)->y < y) && (*m_opponent)->m_untechTime > 0x54 && m_airActions < 2) {
                m_inputX = facing;
                m_inputY = 0;
                return;
            }
            if (x8 > 90.0 && (*m_opponent)->y < y && (*m_opponent)->m_untechTime > 0x2d && m_airActions < 2) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
        }
        return;
    }
    if (m_cpuAction == 0x14) {
        if ((*m_opponent)->m_untechTime <= 0 || y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == kJumpB) {
            m_cpuAction = 0x11;
            return;
        }
        if (v10 < 130.0) {
            m_pressB = 1;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x15) {
        if ((*m_opponent)->m_untechTime <= 0 || y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == kJumpB) {
            m_cpuAction = 0x16;
            return;
        }
        if (v10 < 130.0) {
            m_pressB = 1;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x16) {
        if ((*m_opponent)->m_untechTime <= 0 || y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == kJumpC) {
            m_cpuAction = 0;
            return;
        }
        if (v10 < 130.0) {
            m_pressC = 1;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x1e) {
        if ((*m_opponent)->m_untechTime <= 0 || (*m_opponent)->y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == k5A) {
            m_cpuAction = 0x1f;
            return;
        }
        if (v10 < 130.0) {
            m_pressA = 1;
            return;
        }
        return;
    }
    if (m_cpuAction == 0x1f) {
        if ((*m_opponent)->m_untechTime <= 0 || (*m_opponent)->y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == k5BClose || pattern == k5BFar) {
            m_cpuAction = 0x20;
            return;
        }
        m_pressB = 1;
        return;
    }
    if (m_cpuAction == 0x20) {
        if ((*m_opponent)->m_untechTime <= 0 || (*m_opponent)->y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == k5C) {
            m_cpuAction = 0x21;
            return;
        }
        if ((*m_opponent)->m_untechTime < 0x3c) {
            m_pressC = 1;
            return;
        }
        m_cpuAction = 0xe;
        return;
    }
    if (m_cpuAction == 0x21) {
        if ((*m_opponent)->m_untechTime <= 0 || (*m_opponent)->y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == k236 || pattern == k236C || pattern == k236236B) {
            m_cpuAction = 0;
            return;
        }
        if ((WORD)Random(0, 0x64) < 2 && m_gauge >= 0xbb8) {
            m_command = kCmd236236B;
            return;
        }
        if ((WORD)Random(0, 0x64) < 4 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
            m_command = kCmd236C;
            return;
        }
        if ((WORD)Random(0, 0x64) < 0xa) {
            m_command = kCmd236A;
            return;
        }
    }
    if (m_cpuAction == 0x22) {
        if (pattern > kJump) {
            m_cpuAction = 0;
        }
        if (v10 < 50.0) {
            m_pressA = 1;
            m_inputY = 1;
            return;
        }
        if (v10 < 90.0) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
    }
    if (m_cpuAction == 0x24) {
        if (pattern < kJump) {
            m_cpuAction = 0;
        }
        if (pattern == kAirInstantCharge || pattern == kInstantCharge) {
            m_cpuAction = 0x25;
            return;
        }
        m_command = kCmd22C;
        return;
    }
    if (m_cpuAction == 0x25) {
        if (y == 0.0) {
            m_cpuAction = 0;
        }
        if (pattern == kJumpB) {
            m_cpuAction = 0;
            return;
        }
        m_pressB = 1;
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
            if (v10 < 130.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 100.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3 && (*m_opponent)->m_untechTime > 0x3c) {
                m_cpuAction = 0xe;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3 && (*m_opponent)->m_untechTime <= 0x3c) {
                m_cpuAction = 0x1e;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x2ee) {
                m_inputX = facing;
                m_inputY = -1;
                m_cpuAction = 0xd;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_attackResult == 2 && m_cpuRoll > 0x15e && m_cpuRoll < 0x163) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 0x64) < 0x32) {
                    m_cpuAction = 6;
                }
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x2bc && v10 < 150.0) {
                m_pressC = 1;
                return;
            }
        }
        if (pattern == k5BFar) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0xa) {
                m_command = (WORD)Random(1, 3) + kCmd41236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0xfa && m_cpuRoll < 0xff && m_gauge >= 0xbb8 && m_attackResult == 3) {
                m_command = kCmd236236B;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x258 && v10 < 140.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
        }
        if (pattern == k5C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
                m_command = (WORD)Random(0, 5) + kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258 && m_attackResult == 2) {
                m_command = kCmd214B;
                if (v10 < 120.0) {
                    m_command = kCmd214A;
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
            if (v10 < 70.0 && m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 130.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x258) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0 && m_cpuRoll < 0x1f4) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && v10 < 120.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x28a) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x276) {
                m_command = (WORD)Random(0, 5) + kCmd41236A;
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x32) {
                m_command = (WORD)Random(0, 3) + kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x320 && m_attackResult == 3 && (m_rfGauge > 500.0 || m_rfBlue == 1)) {
                m_command = kCmd623C;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if (m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_cpuAction = 0x10;
                return;
            }
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
            if (m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_cpuAction = 0x11;
                return;
            }
            if (m_cpuRoll > 0x14 && m_cpuRoll < 0x3c && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x50 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6 && m_attackResult != 3) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if ((*m_opponent)->y == 0.0 && m_cpuRoll > 0x15e && m_cpuRoll < 0x28a && y > -40.0 && m_attackResult == 3) {
                m_cpuAction = 0x22;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kJumpC) {
            if (m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd214B;
                return;
            }
            if (m_cpuRoll > 0x384 && m_attackResult != 3) {
                m_inputX = facing;
                return;
            }
            if ((*m_opponent)->y == 0.0 && m_cpuRoll < 0x15e && (m_rfGauge > 500.0 || m_rfBlue > 0) && m_attackResult == 3 && timer < 3 && frame == 4) {
                m_cpuAction = 0x24;
                return;
            }
            if ((*m_opponent)->y == 0.0 && m_cpuRoll > 0x96 && m_cpuRoll < 0x28a && y > -70.0 && m_attackResult == 3) {
                m_cpuAction = 0x22;
                return;
            }
            if (m_cpuRoll > 0x289) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == k236 && v10 < 120.0 && m_rfGauge > 500.0 && frame == 5 && m_cpuRoll < 0x64) {
            m_command = kCmd22C;
            return;
        }
        if (pattern > 0x106 && pattern < 0x10b && (WORD)Random(0, 0x64) < 0x28) {
            m_cpuAction = 5;
            return;
        }
    }
    if ((WORD)Random(0, 0x100) < m_cpuSkill * m_cpuSkill * m_cpuSkill * m_cpuSkill) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (v10 < 40.0 && x8 < 90.0 && (*m_opponent)->pattern > kLastSharedAction && (WORD)Random(0, 0x9c4) < 0xa) {
            m_command = kCmd623A;
            return;
        }
        if (x8 < 90.0 && (*m_opponent)->pattern > kLastSharedAction && (WORD)Random(0, 0x2710) < 0xa && (m_rfGauge > 500.0 || m_rfBlue == 1)) {
            m_command = kCmd236C;
            return;
        }
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown) {
                if (v10 < 80.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0xf && m_cpuHitCooldown == 0) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 75.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x14 && m_cpuHitCooldown == 0) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 > 40.0 && v10 < 140.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x2d && m_cpuRoll > 0x1e && m_cpuHitCooldown == 0) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 140.0 && v10 > 60.0 && m_cpuRoll < 0x82 && m_cpuRoll > 0x50 && m_cpuHitCooldown == 0) {
                    m_pressB = 1;
                    m_inputY = (WORD)Random(0, 0xa) < 5 ? 1 : 0;
                    return;
                }
                if (v10 < 70.0 && m_cpuRoll < 0x87 && m_cpuRoll > 0x82 && m_cpuHitCooldown == 0) {
                    m_cpuAction = 9;
                    return;
                }
                if (v10 < 120.0 && m_cpuRoll < 0x96 && m_cpuRoll > 0x91 && m_cpuHitCooldown == 0) {
                    m_cpuAction = 0xb;
                    return;
                }
                if (v10 > 50.0 && v10 < 180.0 && x8 < 50.0 && m_cpuRoll < 0x12c && m_cpuRoll > 0xfa && m_cpuHitCooldown == 0) {
                    m_command = kCmd236A;
                    return;
                }
                if (x8 < 90.0 && m_cpuRoll < ((*m_opponent)->pattern > kLastSharedAction) * 0xf + 0x131 && m_cpuRoll > 0x12c && m_cpuHitCooldown == 0 && m_rfGauge > 500.0) {
                    m_command = kCmd236C;
                    return;
                }
                if (v10 > 130.0 && m_cpuRoll < 0x145 && m_cpuRoll > 0x136 && m_cpuHitCooldown == 0) {
                    m_command = kCmd41236A;
                    return;
                }
                if (v10 > 130.0 && m_cpuRoll < 0x14a && m_cpuRoll > 0x145 && m_cpuHitCooldown == 0) {
                    m_command = kCmd41236C;
                    return;
                }
                if (v10 < 130.0 && m_cpuRoll < 0x159 && m_cpuRoll > 0x154 && m_cpuHitCooldown == 0 && m_rfGauge > 500.0) {
                    m_command = kCmd41236C;
                    return;
                }
                if (v10 > 200.0 && v10 < 240.0 && m_cpuRoll < 0x172 && m_cpuRoll > 0x16d && m_cpuHitCooldown == 0) {
                    m_command = kCmd214A;
                    return;
                }
                if (v10 > 180.0 && v10 < 320.0 && m_cpuRoll < 0x17c && m_cpuRoll > 0x172 && m_cpuHitCooldown == 0) {
                    m_command = kCmd214B;
                    return;
                }
                if (v10 > 240.0 && v10 < 320.0 && m_cpuRoll < 0x190 && m_cpuRoll > 0x17c && m_cpuHitCooldown == 0) {
                    m_command = kCmd214C;
                    return;
                }
                if (v10 < 120.0 && m_cpuRoll < 0x195 && m_cpuRoll > 0x190 && m_cpuHitCooldown == 0 && m_gauge >= 0xbb8 && (*m_opponent)->m_roundsWon != 0) {
                    m_command = 0x5c;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && m_rfGauge > 500.0 && m_cpuRoll < 2) {
                    m_command = kCmd623C;
                    return;
                }
                if ((*m_opponent)->vy < 0.0) {
                    if (v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 40.0 && x8 < 120.0 && m_cpuRoll < 0x1e) {
                        m_inputY = 0;
                        m_pressB = 1;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && m_cpuRoll < ((*m_opponent)->pattern > kLastSharedAction) * 0x2d + 0xf && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623A;
                        return;
                    }
                    if (v10 < 100.0 && x8 < 170.0 && x8 > 80.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x3c) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 60.0 && x8 < 210.0 && x8 > 120.0 && m_cpuRoll < 0xb4 && m_cpuRoll > 0x64) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if (v10 < 180.0 && x8 < 180.0 && (*m_opponent)->pattern > kFirstCharacterAction && m_cpuRoll < 5 && m_gauge >= 0xbb8) {
                m_command = kCmd236236B;
                return;
            }
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 100.0 && x8 < 100.0 && m_cpuRoll > 0 && m_cpuRoll < 0x258) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 110.0 && x8 < 180.0 && m_cpuRoll > 0x258 && m_cpuRoll < 0x28a) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0xc8 && (*m_opponent)->y < y) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 140.0 && x8 > 60.0 && x8 < 140.0 && (*m_opponent)->y > y && m_cpuRoll > 0xc8 && m_cpuRoll < 0xfa) {
                    m_pressB = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x1388) < 4.0f * m_cpuSkill * m_cpuSkill * m_cpuSkill && m_cpuHitCooldown == 0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && v10 > 80.0 && v10 < 120.0 && (WORD)Random(0, 0x2710) < m_cpuSkill * m_cpuSkill * m_cpuSkill && x > 150.0 && x < 490.0) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if (pattern == kFall || pattern == kSuperJump || pattern > kLand && pattern < 0x15) {
        if (v10 > 100.0) {
            if ((WORD)Random(0, 0x44c) < 2 && m_cpuAirPause == 0) {
                m_cpuAirPause = 0xb4;
            }
            if ((WORD)Random(0, 0x64) < 2 && y > -180.0 && m_cpuAirPause == 0) {
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if ((WORD)Random(0, 0x64) < 4 && m_cpuAirPause == 0) {
                m_inputX = facing;
                return;
            }
            if ((WORD)Random(0, 0x64) < 2 && m_cpuAirPause == 0) {
                m_inputX = facing;
                m_inputY = 1;
                return;
            }
            if ((WORD)Random(0, 0) != 0) {
                m_inputX = facing;
                m_inputY = 1;
                return;
            }
        }
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x3e8) < 2) {
                m_inputY = 1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if ((WORD)Random(0, 0x1f4) < 2 && m_cpuAirPause == 0) {
                m_inputX = -facing;
                return;
            }
            if ((WORD)Random(0, 0x64) < 2 && m_cpuAirPause == 0) {
                m_inputX = facing;
                return;
            }
            if ((WORD)Random(0, 0x64) < 4 && m_cpuAirPause == 0) {
                m_inputX = facing;
                m_inputY = 1;
                return;
            }
        }
    }
    if ((WORD)Random(0, 0x1f4) < 0xa && y == 0.0) {
        if ((WORD)Random(0, 0x64) < 4) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 > 40.0 && v10 < 150.0 && (WORD)Random(0, 0x1f4) < 2) {
            m_cpuAction = 6;
            return;
        }
        if (v10 > 150.0 && (WORD)Random(0, 0x1f4) < 2) {
            m_cpuAction = 7;
            return;
        }
        if (v10 > 200.0 && (WORD)Random(0, 0x1f4) < 2) {
            m_inputX = facing;
            m_inputY = -1;
            return;
        }
        if (v10 < 100.0 && (WORD)Random(0, 0x1f4) < 2) {
            m_inputX = -facing;
            m_inputY = -1;
            return;
        }
    }
    if (y == 0.0) {
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
        if ((WORD)Random(0, 0x3e8) < 2) {
            if (facing == 1) {
                m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x3c;
            } else {
                m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x3c;
            }
        }
        if ((WORD)Random(0, 0x64) < 2) {
            if (facing == 1) {
                m_cpuWalkRight = (WORD)Random(0, 0x190) + 0x3c;
                return;
            }
            m_cpuWalkLeft = (WORD)Random(0, 0x190) + 0x3c;
        }
    }
}

void CKanna::UpdateObjects()
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
            case kObj214A:
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objects[v4].vy = -3.0;
                }
                if (m_objects[v4].vy < 0.0 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.105;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (m_objects[v4].frame < 8 && pattern > kLastFreeAction && pattern < kAirRecoveryForward) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 8) {
                    m_objects[v4].vy += 0.055;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 9;
                        l50.type = kObj214Impact;
                        l50.x = (double)((int)m_objects[v4].x + facing * 0x32);
                        l50.y = 0.0;
                        l50.scale = 0;
                        l50.shadow = 1;
                        l50.keep = 1;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 8 && m_objectVar2[v4] < 1) {
                        m_objects[v4].frame = 0;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].vy = 7.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214B:
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objects[v4].vy = -3.0;
                }
                if (m_objects[v4].vy < 0.0 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.105;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (m_objects[v4].frame < 8 && pattern > kLastFreeAction && pattern < kAirRecoveryForward) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 8) {
                    m_objects[v4].vy += 0.055;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 9;
                        l50.type = kObj214Impact;
                        l50.x = (double)((int)m_objects[v4].x + facing * 0x7d);
                        l50.y = 0.0;
                        l50.scale = 0;
                        l50.shadow = 1;
                        l50.keep = 1;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 8 && m_objectVar2[v4] < 1) {
                        m_objects[v4].frame = 0;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].vy = 7.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214C:
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objects[v4].vy = -3.0;
                }
                if (m_objects[v4].vy < 0.0 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.105;
                    if (m_objects[v4].vy > 0.0) {
                        m_objects[v4].vy = 0.0;
                    }
                }
                if (m_objects[v4].frame < 8 && pattern > kLastFreeAction && pattern < kAirRecoveryForward) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].frame == 8) {
                    m_objects[v4].vy += 0.055;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 9;
                        l50.type = kObj214Impact;
                        l50.x = (double)((int)m_objects[v4].x + facing * 0xc8);
                        l50.y = 0.0;
                        l50.scale = 0;
                        l50.shadow = 1;
                        l50.keep = 1;
                        l50.layer = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 8 && m_objectVar2[v4] < 1) {
                        m_objects[v4].frame = 0;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].vy = 7.0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214Impact:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    ShakeScreen(5, 0);
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
            case kObj236Effect:
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
            case kObj41236Flash:
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
            case kObj41236Shot:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 0x63;
                    m_objects[v4].vx = 3.0;
                    m_objects[v4].vy = 0.0;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].attackResult >= 2) {
                    m_objects[v4].pattern = kObj41236ShotEnd;
                    m_objects[v4].hitsLeft = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].frame > 0x2e4) {
                    RemoveObject(v4);
                }
                m_objects[v4].vx -= 0.025;
                if (m_objects[v4].vx < 1.2) {
                    m_objects[v4].vx = 1.2;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case kObjUnused197:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 3.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].attackResult >= 2 || pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[v4].pattern = kObjUnused19a;
                    m_objects[v4].hitsLeft = 0;
                    break;
                }
                m_objects[v4].vx -= 0.015;
                if (m_objects[v4].vx < 0.4) {
                    m_objects[v4].vx = 0.4;
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
            case kObjUnused198:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
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
            case kObj41236ShotEnd:
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
            case kObjUnused19b:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 2.5;
                    m_objects[v4].vy = -1.2 - (WORD)Random(0, 0x14) * 0.1;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0 && m_objects[v4].frame == 1) {
                    RemoveObject(v4);
                    break;
                }
                if ((m_objects[v4].y >= 0.0 || m_objects[v4].attackResult > 1) && m_objects[v4].frame == 0) {
                    m_objects[v4].y--;
                    m_objects[v4].frame = 1;
                    m_objects[v4].vy = -1.5;
                    l50.type = kObjUnused19c;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
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
            case kObjUnused19c:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 1.5;
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
            case kObjUnused19d:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = (WORD)Random(0, 0x14) * 0.1 + 1.7;
                    m_objects[v4].vy = -0.5 - (WORD)Random(0, 0xa) * 0.1;
                }
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].y >= 0.0 && m_objects[v4].vy > 0.0 && m_objects[v4].frame == 1) {
                    RemoveObject(v4);
                    break;
                }
                if ((m_objects[v4].y >= 0.0 || m_objects[v4].attackResult > 1) && m_objects[v4].frame == 0) {
                    m_objects[v4].y--;
                    m_objects[v4].frame = 1;
                    m_objects[v4].vy = -1.5;
                    l50.type = kObjUnused19e;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
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
            case kObjUnused19e:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 1.5;
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
            case kObj236236ALead:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = -3.0;
                    m_objects[v4].vy = 0.5;
                }
                m_objects[v4].vy = m_objects[v4].vy - m_objects[v4].ay;
                m_objects[v4].timer++;
                if (m_objects[v4].x > 680.0 && m_objects[v4].facing == 1 || m_objects[v4].x < -60.0 && m_objects[v4].facing == -1 || m_objects[v4].y < -320.0) {
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
            case kObjFeatherSlow:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = (WORD)Random(0, 0x64) * 0.01 + 1.0;
                    m_objects[v4].ay = (WORD)Random(0, 0x64) * 0.0002;
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].frame = Random(0, 0xf);
                }
                m_objects[v4].vy = m_objects[v4].vy - m_objects[v4].ay;
                m_objects[v4].timer++;
                if (m_objects[v4].x > 680.0 && m_objects[v4].facing == 1 || m_objects[v4].x < -60.0 && m_objects[v4].facing == -1 || m_objects[v4].y < -320.0) {
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
            case kObjFeatherFast:
                if (m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4]++;
                    m_objects[v4].vx = (WORD)Random(0, 0x64) * 0.01 + 3.5;
                    m_objects[v4].ay = (WORD)Random(0, 0x64) * 0.00015;
                    m_objects[v4].vy = 0.5;
                    m_objects[v4].frame = Random(0, 0xf);
                }
                m_objects[v4].vy = m_objects[v4].vy - m_objects[v4].ay;
                m_objects[v4].timer++;
                if (m_objects[v4].x > 680.0 && m_objects[v4].facing == 1 || m_objects[v4].x < -60.0 && m_objects[v4].facing == -1 || m_objects[v4].y < -320.0) {
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
            case kObj236236BBurst:
                if (pattern == k236236B) {
                    m_objects[v4].x = m_objects[v4].facing * 0xa + x + 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 9 && frame < 0xd && pattern == k236236B) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnused1a3:
                m_objects[v4].timer++;
                if (pattern == k623 && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObj5BCloseEffect:
                if (pattern != k5BClose) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == k5BClose && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObj5BFarEffect:
                if (pattern != k5BFar) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == k5BFar && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObj2BEffect:
                if (pattern != k2B) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == k2B && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObjJumpBEffect:
                if (pattern != kJumpB) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == kJumpB && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObj5CEffect:
                if (pattern != k5C) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == k5C && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObjJumpCEffect:
                if (pattern != kJumpC) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == kJumpC && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObjAir236236B:
                m_objects[v4].x = x;
                m_objects[v4].y = y;
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
            case kObj236CFlash:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 4) {
                        l50.type = kObj236CBeam;
                        l50.x = (double)m_game->m_view.left;
                        l50.y = (double)((int)m_objects[v4].y - 0x3c);
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = 1;
                        SpawnObject(&l50);
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj236CBeam:
                m_objects[v4].x = m_game->m_view.left;
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
            case kObj41236CEmitter:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 4) {
                        l50.type = kObj41236CHoming;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.facing = m_objects[v4].facing;
                        l50.keep = 1;
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                        SpawnObject(&l50);
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj41236CHoming:
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objects[v4].hitsLeft = 1;
                    if (m_patternVar1 == 0) {
                        m_objects[v4].SetVelocity(-140.0, 3.0);
                    }
                    if (m_patternVar1 == 1) {
                        m_objects[v4].SetVelocity(-165.0, 3.0);
                    }
                    if (m_patternVar1 == 2) {
                        m_objects[v4].SetVelocity(-170.0, 3.0);
                    }
                    if (m_patternVar1 == 3) {
                        m_objects[v4].SetVelocity(140.0, 3.0);
                    }
                    if (m_patternVar1 == 4) {
                        m_objects[v4].SetVelocity(165.0, 3.0);
                    }
                    if (m_patternVar1 == 5) {
                        m_objects[v4].SetVelocity(170.0, 3.0);
                    }
                    m_patternVar1++;
                    if (m_patternVar1 == 6) {
                        m_patternVar1 = 0;
                    }
                }
                m_objects[v4].vx += 0.025;
                if (m_objects[v4].y > (*m_opponent)->y - 45.0) {
                    m_objects[v4].vy -= 0.015;
                }
                if (m_objects[v4].y < (*m_opponent)->y - 45.0) {
                    m_objects[v4].vy += 0.015;
                }
                if (m_objects[v4].timer == 0) {
                    l50.type = kObj41236CTrail;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].x > 900.0 || m_objects[v4].x < -360.0 || m_objects[v4].attackResult > 0) {
                    m_objects[v4].pattern = kObj41236CTrail;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
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
            case kObj41236CTrail:
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
            case kObjLv4Attached3:
                if (pattern != kLv4) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == kLv4 && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObjLv4Attached4:
                if (pattern != kLv4) {
                    RemoveObject(v4);
                }
                m_objects[v4].drawnWhileHidden = 0x7530;
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (frame == 0x37 && m_objects[v4].frame < 0x50) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x50;
                    break;
                }
                if (frame > 0x37) {
                    RemoveObject(v4);
                    break;
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0x50 && frame < 0x37) {
                        m_objects[v4].frame = 0x38;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0x6c;
                    }
                }
                break;
            case kObjLv4Attached1:
                if (pattern != kLv4) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == kLv4 && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObjLv4Attached2:
                if (pattern != kLv4) {
                    RemoveObject(v4);
                }
                m_objects[v4].x = x;
                m_objects[v4].y = y;
                m_objects[v4].timer++;
                if (pattern == kLv4 && m_hitstop > 0) {
                    m_objects[v4].timer--;
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
            case kObjLv4Screen1:
                m_objects[v4].drawnWhileHidden = 0x7530;
                if (pattern != kLv4 || frame > 0x35) {
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
            case kObjLv4Screen2:
                m_objects[v4].drawnWhileHidden = 0x7530;
                if (pattern != kLv4 || frame > 0x35) {
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
            case kObjLv4Screen3:
                m_objects[v4].drawnWhileHidden = 0x7530;
                if (pattern != kLv4 || frame > 0x35) {
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
            case kObjLv4Sky:
                if (pattern != kLv4 || frame > 0x36) {
                    RemoveObject(v4);
                }
                m_objectVar1[v4]++;
                if (m_objectVar1[v4] == 0x96) {
                    l50.type = kObjLv4Sky1;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    l50.facing = 1;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_objectVar1[v4] == 0xd2) {
                    l50.type = kObjLv4Sky2;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    l50.facing = 1;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_objectVar1[v4] == 0x10e) {
                    l50.type = kObjLv4Sky3;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    l50.facing = 1;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_objectVar1[v4] == 0x12c) {
                    l50.type = kObjLv4Sky4;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    l50.facing = 1;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_objectVar1[v4] == 0x14a) {
                    l50.type = kObjLv4Sky5;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    l50.facing = 1;
                    l50.movesInFreeze = 1;
                    SpawnObject(&l50);
                }
                if (m_objectVar1[v4] == 0x153) {
                    l50.type = kObjLv4Sky6;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    l50.facing = 1;
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
            case kObjLv4Rise:
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
            case kObj623Effect:
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
            case kObjLv4Sky1:
                if (pattern != kLv4 || frame > 0x36) {
                    RemoveObject(v4);
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
            case kObjLv4Sky2:
                if (pattern != kLv4 || frame > 0x36) {
                    RemoveObject(v4);
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
            case kObjLv4Sky3:
                if (pattern != kLv4 || frame > 0x36) {
                    RemoveObject(v4);
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
            case kObjLv4Sky4:
                if (pattern != kLv4 || frame > 0x36) {
                    RemoveObject(v4);
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
            case kObjLv4Sky5:
                if (pattern != kLv4 || frame > 0x36) {
                    RemoveObject(v4);
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
            case kObjLv4Sky6:
                if (pattern != kLv4 || frame > 0x36) {
                    RemoveObject(v4);
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
            case kObjLv4RiseSide:
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
