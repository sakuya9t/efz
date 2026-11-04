// CKanna (0x675c80-0x68354f): the character class whose files are in kanna\ in the game
// folder (kanna.dat sprites, kanna.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CKanna::CKanna(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

    strcpy(m_name, "kanna");
    lastSurface = 1243;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_airMoveDelay = 60;
    m_pointX[0] = -4;
    m_pointY[0] = -59;
    m_pointX[1] = 27;
    m_pointY[1] = 0;
    m_pointX[2] = 11;
    m_pointY[2] = -18;
    m_pointX[3] = 11;
    m_pointY[3] = -13;
    m_pointX[4] = 33;
    m_pointY[4] = -35;
    m_resultPictures = 4;
    m_rivals[0] = 1;
    m_rivals[1] = 6;
    m_rivals[2] = 23;
    m_rivals[3] = 16;
    i = 0;
    for (; i < 64; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
}

void CKanna::Reset()
{
    int i;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_airMoveDelay = 60;
    m_pointX[0] = -13;
    m_pointY[0] = -60;
    m_pointX[1] = 14;
    m_pointY[1] = 0;
    m_pointX[2] = 17;
    m_pointY[2] = -6;
    m_pointX[3] = 7;
    m_pointY[3] = -25;
    m_pointX[4] = 27;
    m_pointY[4] = -25;
    i = 0;
    for (; i < 64; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
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

void CKanna::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
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
        if (m_command == kCmd236236C && m_gauge >= 3000 && m_hp < 3333 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd236236B && m_gauge >= 3000 && y < 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAir236236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236236B;
            return;
        }
        if (m_command == kCmd236236A && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236A;
            return;
        }
        if (m_command == kCmd236236B && m_gauge >= 3000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level) {
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
    if (m_pressA == 1 || (m_bufferedPress & kInputA) != 0 || (m_dashBufferedPress & kInputA) != 0) {
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
    if (m_pressC == 1 || (m_bufferedPress & kInputC) != 0 || (m_dashBufferedPress & kInputC) != 0) {
        if (y < 0.0) {
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
        if ((m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) && m_patterns[pattern].cancelLevel <= m_patterns[k5C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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

void CKanna::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CKanna::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 70);
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
    pos = m_inputPos + (kInputHistoryLength - 55);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 3) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd41236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 2) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd41236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
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
    pos = m_inputPos + (kInputHistoryLength - 55);
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
    pos = m_inputPos + (kInputHistoryLength - 55);
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
    pos = m_inputPos + (kInputHistoryLength - 55);
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
        if ((input & kInputDirections) == 0 && step == 0) {
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
    pos = m_inputPos + (kInputHistoryLength - 90);
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
    pos = m_inputPos + (kInputHistoryLength - 90);
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

void CKanna::CpuInput()
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
    m_cpuHitCooldown--;
    m_cpuAirPause--;
    if (m_cpuHitCooldown < 0) {
        m_cpuHitCooldown = 0;
    }
    if (pattern > kLastFreeAction && pattern < 0xa1) {
        m_cpuHitCooldown = 180;
    }
    if (m_cpuAirPause < 0) {
        m_cpuAirPause = 0;
    }
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
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 45.0 && (WORD)Random(0, 100) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && dx > 60.0 && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
            m_pressB = 1;
            m_inputY = 1;
            m_inputX = 0;
            return;
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if ((WORD)Random(0, 8000) < m_cpuSkill * m_cpuSkill * 4.0f && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (dx < 20.0) {
            if ((WORD)Random(0, 1800) < m_cpuSkill * 4.0f && m_rfGauge > 500.0) {
                m_command = kCmd623A;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_gauge == 3000) {
                m_command = 0x5c;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && dx < 120.0 && m_gauge >= 2000) {
                m_command = kCmd236236B;
                return;
            }
        }
        if (dx < 150.0 && dx > 100.0) {
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if (dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
                m_pressA = 2;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_gauge == 3000 && (*m_opponent)->pattern < 0xdc) {
                m_command = kCmd236236A;
                return;
            }
        }
        if (dx > 150.0) {
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
                m_command = kCmd236236A;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -40.0 && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < -50.0 && dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
        if (dy < 50.0 && dx < 100.0 && (WORD)Random(0, 100) < m_cpuSkill * 2) {
            m_command = (WORD)Random(0, 2) + kCmd236A;
            return;
        }
        if ((WORD)Random(0, 1000) < m_cpuSkill * 2) {
            m_command = kCmd236236A;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 100);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 17 && m_cpuRoll > 12 && m_gauge >= 3000) {
            m_command = kCmd236236A;
            return;
        }
        if (m_cpuRoll < 18 && m_cpuRoll > 20 && m_gauge == 3000) {
            m_command = kCmd236236B;
            return;
        }
        if (m_cpuRoll > 65) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 1000);
        if (m_cpuRoll < 2 && m_gauge >= 3000) {
            m_command = kCmd236236A;
            return;
        }
        if (m_cpuRoll < 4 && m_gauge >= 3000) {
            m_command = kCmd236236B;
            return;
        }
        if (m_cpuRoll > 58) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 100) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k623 || pattern == kUnusedDashC && (WORD)Random(0, 10) == 0 || pattern == kUnusedDash2C && (WORD)Random(0, 7) == 0)) {
        m_command = kCmd22C;
        return;
    }
    if (y == 0.0 && pattern < kJump && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kFirstGuard && m_cpuAction == 0) {
        if ((*m_opponent)->y < 0.0 && dy < 100.0 && dx < 130.0 && ((*m_opponent)->m_untechTime > 24 || (*m_opponent)->m_noAirRecovery == 1 || (*m_opponent)->pattern == kHitShock && (*m_opponent)->frame < 4)) {
            m_cpuAction = 0x1f;
            return;
        }
        if ((*m_opponent)->y < 0.0 && dy < 50.0 && dx < 70.0 && ((*m_opponent)->m_untechTime > 18 || (*m_opponent)->m_noAirRecovery == 1 || (*m_opponent)->pattern == kHitShock && (*m_opponent)->frame < 4)) {
            m_cpuAction = 0x1e;
            return;
        }
        if ((*m_opponent)->pattern == kHitWallBounce && m_gauge >= 3000 && (WORD)Random(0, 0) != 0) {
            if (dx < 150.0) {
                m_command = kCmd236236B;
                return;
            }
            if (dx > 150.0) {
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
        if (dy < 80.0 && (*m_opponent)->y < y) {
            m_pressA = 1;
            if (pattern == kJumpA) {
                m_cpuAction = 0x10;
                return;
            }
        }
        if (dy < 100.0) {
            m_pressB = 1;
            if ((*m_opponent)->m_untechTime < 24) {
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
        if ((WORD)Random(0, 200) == 1 && m_gauge == 3000) {
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
            if (dx > 80.0 && vx < 0.0 && (*m_opponent)->y - y > -40.0) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->m_untechTime < 45 && m_airActions > 0 && dy < 40.0 && (*m_opponent)->y - y < 0.0) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->m_untechTime < 45 && vx >= 0.0) {
                m_pressC = 1;
                return;
            }
            if ((dy < 20.0 && (*m_opponent)->y > y || (*m_opponent)->y < y) && (*m_opponent)->m_untechTime > 84 && m_airActions < 2) {
                m_inputX = facing;
                m_inputY = 0;
                return;
            }
            if (dy > 90.0 && (*m_opponent)->y < y && (*m_opponent)->m_untechTime > 45 && m_airActions < 2) {
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
        if (dx < 130.0) {
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
        if (dx < 130.0) {
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
        if (dx < 130.0) {
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
        if (dx < 130.0) {
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
        if ((*m_opponent)->m_untechTime < 60) {
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
        if ((WORD)Random(0, 100) < 2 && m_gauge >= 3000) {
            m_command = kCmd236236B;
            return;
        }
        if ((WORD)Random(0, 100) < 4 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
            m_command = kCmd236C;
            return;
        }
        if ((WORD)Random(0, 100) < 10) {
            m_command = kCmd236A;
            return;
        }
    }
    if (m_cpuAction == 0x22) {
        if (pattern > kJump) {
            m_cpuAction = 0;
        }
        if (dx < 50.0) {
            m_pressA = 1;
            m_inputY = 1;
            return;
        }
        if (dx < 90.0) {
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
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 100) < m_cpuSkill * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 1000);
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 130.0 && m_cpuRoll > 0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 100.0 && m_cpuRoll > 300 && m_cpuRoll < 600) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3 && (*m_opponent)->m_untechTime > 60) {
                m_cpuAction = 0xe;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3 && (*m_opponent)->m_untechTime <= 60) {
                m_cpuAction = 0x1e;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 600 && m_cpuRoll < 750) {
                m_inputX = facing;
                m_inputY = -1;
                m_cpuAction = 0xd;
                return;
            }
            if (m_cpuRoll > 100 && m_cpuRoll < 350 && dx < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_attackResult == 2 && m_cpuRoll > 350 && m_cpuRoll < 355) {
                m_inputX = facing;
                m_inputY = -1;
                if ((WORD)Random(0, 100) < 50) {
                    m_cpuAction = 6;
                }
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 450 && m_cpuRoll < 700 && dx < 150.0) {
                m_pressC = 1;
                return;
            }
        }
        if (pattern == k5BFar) {
            if (m_cpuRoll > 0 && m_cpuRoll < 10) {
                m_command = (WORD)Random(1, 3) + kCmd41236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 250 && m_cpuRoll < 255 && m_gauge >= 3000 && m_attackResult == 3) {
                m_command = kCmd236236B;
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 600 && dx < 140.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
        }
        if (pattern == k5C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 600) {
                m_command = (WORD)Random(0, 5) + kCmd41236A;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 600 && m_attackResult == 2) {
                m_command = kCmd214B;
                if (dx < 120.0) {
                    m_command = kCmd214A;
                }
                return;
            }
            if (m_cpuRoll > 900) {
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
            if (dx < 70.0 && m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 130.0 && m_cpuRoll > 200 && m_cpuRoll < 600) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0 && m_cpuRoll < 500) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll < 300) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 450 && dx < 120.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 450 && m_cpuRoll < 650) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 550 && m_cpuRoll < 630) {
                m_command = (WORD)Random(0, 5) + kCmd41236A;
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 50) {
                m_command = (WORD)Random(0, 3) + kCmd41236A;
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 800 && m_attackResult == 3 && (m_rfGauge > 500.0 || m_rfBlue == 1)) {
                m_command = kCmd623C;
                return;
            }
            if (m_cpuRoll > 900) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == kJumpA) {
            if (m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_cpuAction = 0x10;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                return;
            }
            if (dx < 60.0 && m_cpuRoll < 400) {
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
            if (m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_cpuAction = 0x11;
                return;
            }
            if (m_cpuRoll > 20 && m_cpuRoll < 60 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 80 && m_cpuRoll < 300) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 950 && m_attackResult != 3) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if ((*m_opponent)->y == 0.0 && m_cpuRoll > 350 && m_cpuRoll < 650 && y > -40.0 && m_attackResult == 3) {
                m_cpuAction = 0x22;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kJumpC) {
            if (m_cpuRoll < 200 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd214B;
                return;
            }
            if (m_cpuRoll > 900 && m_attackResult != 3) {
                m_inputX = facing;
                return;
            }
            if ((*m_opponent)->y == 0.0 && m_cpuRoll < 350 && (m_rfGauge > 500.0 || m_rfBlue > 0) && m_attackResult == 3 && timer < 3 && frame == 4) {
                m_cpuAction = 0x24;
                return;
            }
            if ((*m_opponent)->y == 0.0 && m_cpuRoll > 150 && m_cpuRoll < 650 && y > -70.0 && m_attackResult == 3) {
                m_cpuAction = 0x22;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == k236 && dx < 120.0 && m_rfGauge > 500.0 && frame == 5 && m_cpuRoll < 100) {
            m_command = kCmd22C;
            return;
        }
        if (pattern > 0x106 && pattern < 0x10b && (WORD)Random(0, 100) < 40) {
            m_cpuAction = 5;
            return;
        }
    }
    if ((WORD)Random(0, 256) < m_cpuSkill * m_cpuSkill * m_cpuSkill * m_cpuSkill) {
        m_cpuRoll = (WORD)Random(0, 1000);
        if (dx < 40.0 && dy < 90.0 && (*m_opponent)->pattern > kLastSharedAction && (WORD)Random(0, 2500) < 10) {
            m_command = kCmd623A;
            return;
        }
        if (dy < 90.0 && (*m_opponent)->pattern > kLastSharedAction && (WORD)Random(0, 10000) < 10 && (m_rfGauge > 500.0 || m_rfBlue == 1)) {
            m_command = kCmd236C;
            return;
        }
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown) {
                if (dx < 80.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 15 + 15 && m_cpuHitCooldown == 0) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (dx < 75.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 15 + 20 && m_cpuHitCooldown == 0) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (dx > 40.0 && dx < 140.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 15 + 45 && m_cpuRoll > 30 && m_cpuHitCooldown == 0) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (dx < 140.0 && dx > 60.0 && m_cpuRoll < 130 && m_cpuRoll > 80 && m_cpuHitCooldown == 0) {
                    m_pressB = 1;
                    m_inputY = (WORD)Random(0, 10) < 5 ? 1 : 0;
                    return;
                }
                if (dx < 70.0 && m_cpuRoll < 135 && m_cpuRoll > 130 && m_cpuHitCooldown == 0) {
                    m_cpuAction = 9;
                    return;
                }
                if (dx < 120.0 && m_cpuRoll < 150 && m_cpuRoll > 145 && m_cpuHitCooldown == 0) {
                    m_cpuAction = 0xb;
                    return;
                }
                if (dx > 50.0 && dx < 180.0 && dy < 50.0 && m_cpuRoll < 300 && m_cpuRoll > 250 && m_cpuHitCooldown == 0) {
                    m_command = kCmd236A;
                    return;
                }
                if (dy < 90.0 && m_cpuRoll < ((*m_opponent)->pattern > kLastSharedAction) * 15 + 305 && m_cpuRoll > 300 && m_cpuHitCooldown == 0 && m_rfGauge > 500.0) {
                    m_command = kCmd236C;
                    return;
                }
                if (dx > 130.0 && m_cpuRoll < 325 && m_cpuRoll > 310 && m_cpuHitCooldown == 0) {
                    m_command = kCmd41236A;
                    return;
                }
                if (dx > 130.0 && m_cpuRoll < 330 && m_cpuRoll > 325 && m_cpuHitCooldown == 0) {
                    m_command = kCmd41236C;
                    return;
                }
                if (dx < 130.0 && m_cpuRoll < 345 && m_cpuRoll > 340 && m_cpuHitCooldown == 0 && m_rfGauge > 500.0) {
                    m_command = kCmd41236C;
                    return;
                }
                if (dx > 200.0 && dx < 240.0 && m_cpuRoll < 370 && m_cpuRoll > 365 && m_cpuHitCooldown == 0) {
                    m_command = kCmd214A;
                    return;
                }
                if (dx > 180.0 && dx < 320.0 && m_cpuRoll < 380 && m_cpuRoll > 370 && m_cpuHitCooldown == 0) {
                    m_command = kCmd214B;
                    return;
                }
                if (dx > 240.0 && dx < 320.0 && m_cpuRoll < 400 && m_cpuRoll > 380 && m_cpuHitCooldown == 0) {
                    m_command = kCmd214C;
                    return;
                }
                if (dx < 120.0 && m_cpuRoll < 405 && m_cpuRoll > 400 && m_cpuHitCooldown == 0 && m_gauge >= 3000 && (*m_opponent)->m_roundsWon != 0) {
                    m_command = 0x5c;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 80.0 && m_rfGauge > 500.0 && m_cpuRoll < 2) {
                    m_command = kCmd623C;
                    return;
                }
                if ((*m_opponent)->vy < 0.0) {
                    if (dx < 80.0 && dy < 120.0 && m_cpuRoll < 10) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx < 40.0 && dy < 120.0 && m_cpuRoll < 30) {
                        m_inputY = 0;
                        m_pressB = 1;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 90.0 && dy < 140.0 && m_cpuRoll < ((*m_opponent)->pattern > kLastSharedAction) * 45 + 15 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623A;
                        return;
                    }
                    if (dx < 100.0 && dy < 170.0 && dy > 80.0 && m_cpuRoll < 110 && m_cpuRoll > 60) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 60.0 && dy < 210.0 && dy > 120.0 && m_cpuRoll < 180 && m_cpuRoll > 100) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if (dx < 180.0 && dy < 180.0 && (*m_opponent)->pattern > kFirstCharacterAction && m_cpuRoll < 5 && m_gauge >= 3000) {
                m_command = kCmd236236B;
                return;
            }
            if ((*m_opponent)->y == 0.0) {
                if (dx < 100.0 && dy < 100.0 && m_cpuRoll > 0 && m_cpuRoll < 600) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 110.0 && dy < 180.0 && m_cpuRoll > 600 && m_cpuRoll < 650) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 80.0 && dy < 100.0 && m_cpuRoll < 200 && (*m_opponent)->y < y) {
                    m_pressA = 1;
                    return;
                }
                if (dx > 20.0 && dx < 140.0 && dy > 60.0 && dy < 140.0 && (*m_opponent)->y > y && m_cpuRoll > 200 && m_cpuRoll < 250) {
                    m_pressB = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 5000) < 4.0f * m_cpuSkill * m_cpuSkill * m_cpuSkill && m_cpuHitCooldown == 0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && dx > 80.0 && dx < 120.0 && (WORD)Random(0, 10000) < m_cpuSkill * m_cpuSkill * m_cpuSkill && x > 150.0 && x < 490.0) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if (pattern == kFall || pattern == kSuperJump || pattern > kLand && pattern < 0x15) {
        if (dx > 100.0) {
            if ((WORD)Random(0, 1100) < 2 && m_cpuAirPause == 0) {
                m_cpuAirPause = 180;
            }
            if ((WORD)Random(0, 100) < 2 && y > -180.0 && m_cpuAirPause == 0) {
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if ((WORD)Random(0, 100) < 4 && m_cpuAirPause == 0) {
                m_inputX = facing;
                return;
            }
            if ((WORD)Random(0, 100) < 2 && m_cpuAirPause == 0) {
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
        if (dx < 100.0) {
            if ((WORD)Random(0, 1000) < 2) {
                m_inputY = 1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if ((WORD)Random(0, 500) < 2 && m_cpuAirPause == 0) {
                m_inputX = -facing;
                return;
            }
            if ((WORD)Random(0, 100) < 2 && m_cpuAirPause == 0) {
                m_inputX = facing;
                return;
            }
            if ((WORD)Random(0, 100) < 4 && m_cpuAirPause == 0) {
                m_inputX = facing;
                m_inputY = 1;
                return;
            }
        }
    }
    if ((WORD)Random(0, 500) < 10 && y == 0.0) {
        if ((WORD)Random(0, 100) < 4) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx > 40.0 && dx < 150.0 && (WORD)Random(0, 500) < 2) {
            m_cpuAction = 6;
            return;
        }
        if (dx > 150.0 && (WORD)Random(0, 500) < 2) {
            m_cpuAction = 7;
            return;
        }
        if (dx > 200.0 && (WORD)Random(0, 500) < 2) {
            m_inputX = facing;
            m_inputY = -1;
            return;
        }
        if (dx < 100.0 && (WORD)Random(0, 500) < 2) {
            m_inputX = -facing;
            m_inputY = -1;
            return;
        }
    }
    if (y == 0.0) {
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
        if ((WORD)Random(0, 1000) < 2) {
            if (facing == 1) {
                m_cpuWalkLeft = (WORD)Random(0, 200) + 60;
            } else {
                m_cpuWalkRight = (WORD)Random(0, 200) + 60;
            }
        }
        if ((WORD)Random(0, 100) < 2) {
            if (facing == 1) {
                m_cpuWalkRight = (WORD)Random(0, 400) + 60;
                return;
            }
            m_cpuWalkLeft = (WORD)Random(0, 400) + 60;
        }
    }
}

void CKanna::UpdateObjects()
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
            case kObj214A:
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].vy = -3.0;
                }
                if (m_objects[slot].vy < 0.0 && m_objects[slot].frame < 8) {
                    m_objects[slot].vy += 0.105;
                    if (m_objects[slot].vy > 0.0) {
                        m_objects[slot].vy = 0.0;
                    }
                }
                if (m_objects[slot].frame < 8 && pattern > kLastFreeAction && pattern < kAirRecoveryForward) {
                    RemoveObject(slot);
                    break;
                }
                if (m_objects[slot].frame == 8) {
                    m_objects[slot].vy += 0.055;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = 9;
                        effect.type = kObj214Impact;
                        effect.x = (double)((int)m_objects[slot].x + facing * 50);
                        effect.y = 0.0;
                        effect.scale = 0;
                        effect.shadow = 1;
                        effect.keep = 1;
                        effect.layer = 1;
                        effect.facing = facing;
                        SpawnObject(&effect);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 8 && m_objectVar2[slot] < 1) {
                        m_objects[slot].frame = 0;
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame == 8) {
                        m_objects[slot].vy = 7.0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214B:
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].vy = -3.0;
                }
                if (m_objects[slot].vy < 0.0 && m_objects[slot].frame < 8) {
                    m_objects[slot].vy += 0.105;
                    if (m_objects[slot].vy > 0.0) {
                        m_objects[slot].vy = 0.0;
                    }
                }
                if (m_objects[slot].frame < 8 && pattern > kLastFreeAction && pattern < kAirRecoveryForward) {
                    RemoveObject(slot);
                    break;
                }
                if (m_objects[slot].frame == 8) {
                    m_objects[slot].vy += 0.055;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = 9;
                        effect.type = kObj214Impact;
                        effect.x = (double)((int)m_objects[slot].x + facing * 125);
                        effect.y = 0.0;
                        effect.scale = 0;
                        effect.shadow = 1;
                        effect.keep = 1;
                        effect.layer = 1;
                        effect.facing = facing;
                        SpawnObject(&effect);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 8 && m_objectVar2[slot] < 1) {
                        m_objects[slot].frame = 0;
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame == 8) {
                        m_objects[slot].vy = 7.0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214C:
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].vy = -3.0;
                }
                if (m_objects[slot].vy < 0.0 && m_objects[slot].frame < 8) {
                    m_objects[slot].vy += 0.105;
                    if (m_objects[slot].vy > 0.0) {
                        m_objects[slot].vy = 0.0;
                    }
                }
                if (m_objects[slot].frame < 8 && pattern > kLastFreeAction && pattern < kAirRecoveryForward) {
                    RemoveObject(slot);
                    break;
                }
                if (m_objects[slot].frame == 8) {
                    m_objects[slot].vy += 0.055;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = 9;
                        effect.type = kObj214Impact;
                        effect.x = (double)((int)m_objects[slot].x + facing * 200);
                        effect.y = 0.0;
                        effect.scale = 0;
                        effect.shadow = 1;
                        effect.keep = 1;
                        effect.layer = 1;
                        effect.facing = facing;
                        SpawnObject(&effect);
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 8 && m_objectVar2[slot] < 1) {
                        m_objects[slot].frame = 0;
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame == 8) {
                        m_objects[slot].vy = 7.0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214Impact:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    ShakeScreen(5, 0);
                    m_playVoice = 3;
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
            case kObj236Effect:
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
            case kObj41236Flash:
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
            case kObj41236Shot:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 99;
                    m_objects[slot].vx = 3.0;
                    m_objects[slot].vy = 0.0;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].attackResult >= 2) {
                    m_objects[slot].pattern = kObj41236ShotEnd;
                    m_objects[slot].hitsLeft = 0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].frame > 740) {
                    RemoveObject(slot);
                }
                m_objects[slot].vx -= 0.025;
                if (m_objects[slot].vx < 1.2) {
                    m_objects[slot].vx = 1.2;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjUnused197:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 3.0;
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].attackResult >= 2 || pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].pattern = kObjUnused19a;
                    m_objects[slot].hitsLeft = 0;
                    break;
                }
                m_objects[slot].vx -= 0.015;
                if (m_objects[slot].vx < 0.4) {
                    m_objects[slot].vx = 0.4;
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
            case kObjUnused198:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
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
            case kObj41236ShotEnd:
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
            case kObjUnused19a:
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
            case kObjUnused19b:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = (WORD)Random(0, 10) * 0.1 + 2.5;
                    m_objects[slot].vy = -1.2 - (WORD)Random(0, 20) * 0.1;
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y >= 0.0 && m_objects[slot].vy > 0.0 && m_objects[slot].frame == 1) {
                    RemoveObject(slot);
                    break;
                }
                if ((m_objects[slot].y >= 0.0 || m_objects[slot].attackResult > 1) && m_objects[slot].frame == 0) {
                    m_objects[slot].y--;
                    m_objects[slot].frame = 1;
                    m_objects[slot].vy = -1.5;
                    effect.type = kObjUnused19c;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_playVoice = 1;
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
            case kObjUnused19c:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 10) * 0.1 + 1.5;
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
            case kObjUnused19d:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = (WORD)Random(0, 20) * 0.1 + 1.7;
                    m_objects[slot].vy = -0.5 - (WORD)Random(0, 10) * 0.1;
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y >= 0.0 && m_objects[slot].vy > 0.0 && m_objects[slot].frame == 1) {
                    RemoveObject(slot);
                    break;
                }
                if ((m_objects[slot].y >= 0.0 || m_objects[slot].attackResult > 1) && m_objects[slot].frame == 0) {
                    m_objects[slot].y--;
                    m_objects[slot].frame = 1;
                    m_objects[slot].vy = -1.5;
                    effect.type = kObjUnused19e;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_playVoice = 1;
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
            case kObjUnused19e:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = (WORD)Random(0, 10) * 0.1 + 1.5;
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
            case kObj236236ALead:
                if (m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = -3.0;
                    m_objects[slot].vy = 0.5;
                }
                m_objects[slot].vy = m_objects[slot].vy - m_objects[slot].ay;
                m_objects[slot].timer++;
                if (m_objects[slot].x > 680.0 && m_objects[slot].facing == 1 || m_objects[slot].x < -60.0 && m_objects[slot].facing == -1 || m_objects[slot].y < -320.0) {
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
            case kObjFeatherSlow:
                if (m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = (WORD)Random(0, 100) * 0.01 + 1.0;
                    m_objects[slot].ay = (WORD)Random(0, 100) * 0.0002;
                    m_objects[slot].vy = 0.5;
                    m_objects[slot].frame = Random(0, 15);
                }
                m_objects[slot].vy = m_objects[slot].vy - m_objects[slot].ay;
                m_objects[slot].timer++;
                if (m_objects[slot].x > 680.0 && m_objects[slot].facing == 1 || m_objects[slot].x < -60.0 && m_objects[slot].facing == -1 || m_objects[slot].y < -320.0) {
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
            case kObjFeatherFast:
                if (m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot]++;
                    m_objects[slot].vx = (WORD)Random(0, 100) * 0.01 + 3.5;
                    m_objects[slot].ay = (WORD)Random(0, 100) * 0.00015;
                    m_objects[slot].vy = 0.5;
                    m_objects[slot].frame = Random(0, 15);
                }
                m_objects[slot].vy = m_objects[slot].vy - m_objects[slot].ay;
                m_objects[slot].timer++;
                if (m_objects[slot].x > 680.0 && m_objects[slot].facing == 1 || m_objects[slot].x < -60.0 && m_objects[slot].facing == -1 || m_objects[slot].y < -320.0) {
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
            case kObj236236BBurst:
                if (pattern == k236236B) {
                    m_objects[slot].x = m_objects[slot].facing * 10 + x + 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 9 && frame < 13 && pattern == k236236B) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjUnused1a3:
                m_objects[slot].timer++;
                if (pattern == k623 && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj5BCloseEffect:
                if (pattern != k5BClose) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (pattern == k5BClose && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj5BFarEffect:
                if (pattern != k5BFar) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (pattern == k5BFar && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj2BEffect:
                if (pattern != k2B) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (pattern == k2B && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjJumpBEffect:
                if (pattern != kJumpB) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (pattern == kJumpB && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj5CEffect:
                if (pattern != k5C) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (pattern == k5C && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjJumpCEffect:
                if (pattern != kJumpC) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (pattern == kJumpC && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjAir236236B:
                m_objects[slot].x = x;
                m_objects[slot].y = y;
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
            case kObj236CFlash:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 4) {
                        effect.type = kObj236CBeam;
                        effect.x = (double)m_game->m_view.left;
                        effect.y = (double)((int)m_objects[slot].y - 60);
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.facing = 1;
                        SpawnObject(&effect);
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj236CBeam:
                m_objects[slot].x = m_game->m_view.left;
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
            case kObj41236CEmitter:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 4) {
                        effect.type = kObj41236CHoming;
                        effect.x = (double)(int)m_objects[slot].x;
                        effect.y = (double)(int)m_objects[slot].y;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.facing = m_objects[slot].facing;
                        effect.keep = 1;
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                        SpawnObject(&effect);
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj41236CHoming:
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objects[slot].hitsLeft = 1;
                    if (m_patternVar1 == 0) {
                        m_objects[slot].SetVelocity(-140.0, 3.0);
                    }
                    if (m_patternVar1 == 1) {
                        m_objects[slot].SetVelocity(-165.0, 3.0);
                    }
                    if (m_patternVar1 == 2) {
                        m_objects[slot].SetVelocity(-170.0, 3.0);
                    }
                    if (m_patternVar1 == 3) {
                        m_objects[slot].SetVelocity(140.0, 3.0);
                    }
                    if (m_patternVar1 == 4) {
                        m_objects[slot].SetVelocity(165.0, 3.0);
                    }
                    if (m_patternVar1 == 5) {
                        m_objects[slot].SetVelocity(170.0, 3.0);
                    }
                    m_patternVar1++;
                    if (m_patternVar1 == 6) {
                        m_patternVar1 = 0;
                    }
                }
                m_objects[slot].vx += 0.025;
                if (m_objects[slot].y > (*m_opponent)->y - 45.0) {
                    m_objects[slot].vy -= 0.015;
                }
                if (m_objects[slot].y < (*m_opponent)->y - 45.0) {
                    m_objects[slot].vy += 0.015;
                }
                if (m_objects[slot].timer == 0) {
                    effect.type = kObj41236CTrail;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].x > 900.0 || m_objects[slot].x < -360.0 || m_objects[slot].attackResult > 0) {
                    m_objects[slot].pattern = kObj41236CTrail;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
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
            case kObj41236CTrail:
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
            case kObjLv4Attached3:
                if (pattern != kLv4) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (pattern == kLv4 && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Attached4:
                if (pattern != kLv4) {
                    RemoveObject(slot);
                }
                m_objects[slot].drawnWhileHidden = 30000;
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (frame == 55 && m_objects[slot].frame < 80) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 80;
                    break;
                }
                if (frame > 55) {
                    RemoveObject(slot);
                    break;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 80 && frame < 55) {
                        m_objects[slot].frame = 56;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 108;
                    }
                }
                break;
            case kObjLv4Attached1:
                if (pattern != kLv4) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (pattern == kLv4 && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Attached2:
                if (pattern != kLv4) {
                    RemoveObject(slot);
                }
                m_objects[slot].x = x;
                m_objects[slot].y = y;
                m_objects[slot].timer++;
                if (pattern == kLv4 && m_hitstop > 0) {
                    m_objects[slot].timer--;
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Screen1:
                m_objects[slot].drawnWhileHidden = 30000;
                if (pattern != kLv4 || frame > 53) {
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
            case kObjLv4Screen2:
                m_objects[slot].drawnWhileHidden = 30000;
                if (pattern != kLv4 || frame > 53) {
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
            case kObjLv4Screen3:
                m_objects[slot].drawnWhileHidden = 30000;
                if (pattern != kLv4 || frame > 53) {
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
            case kObjLv4Sky:
                if (pattern != kLv4 || frame > 54) {
                    RemoveObject(slot);
                }
                m_objectVar1[slot]++;
                if (m_objectVar1[slot] == 150) {
                    effect.type = kObjLv4Sky1;
                    effect.x = m_objects[slot].x;
                    effect.y = m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = 1;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_objectVar1[slot] == 210) {
                    effect.type = kObjLv4Sky2;
                    effect.x = m_objects[slot].x;
                    effect.y = m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = 1;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_objectVar1[slot] == 270) {
                    effect.type = kObjLv4Sky3;
                    effect.x = m_objects[slot].x;
                    effect.y = m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = 1;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_objectVar1[slot] == 300) {
                    effect.type = kObjLv4Sky4;
                    effect.x = m_objects[slot].x;
                    effect.y = m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = 1;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_objectVar1[slot] == 330) {
                    effect.type = kObjLv4Sky5;
                    effect.x = m_objects[slot].x;
                    effect.y = m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = 1;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_objectVar1[slot] == 339) {
                    effect.type = kObjLv4Sky6;
                    effect.x = m_objects[slot].x;
                    effect.y = m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = 1;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
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
            case kObjLv4Rise:
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
            case kObj623Effect:
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
            case kObjLv4Sky1:
                if (pattern != kLv4 || frame > 54) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjLv4Sky2:
                if (pattern != kLv4 || frame > 54) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjLv4Sky3:
                if (pattern != kLv4 || frame > 54) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjLv4Sky4:
                if (pattern != kLv4 || frame > 54) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjLv4Sky5:
                if (pattern != kLv4 || frame > 54) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjLv4Sky6:
                if (pattern != kLv4 || frame > 54) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjLv4RiseSide:
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
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x + facing * 23);
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
                    effect.x = (double)((int)x - facing * 14);
                    effect.y = (double)((int)y - 26);
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
                    effect.x = (double)((int)x + facing * 30);
                    effect.y = (double)((int)y - 40);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x - facing * 25);
                    effect.y = (double)((int)y - 80);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x - facing * 35);
                    effect.y = (double)((int)y - 42);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x - facing * 18);
                    effect.y = (double)((int)y - 20);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x + facing * 2);
                    effect.y = (double)((int)y - 65);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
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
