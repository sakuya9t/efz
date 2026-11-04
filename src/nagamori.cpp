// CNagamori (0x4add90-0x4c04af).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNagamori::CNagamori(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

    strcpy(m_name, "nagamori");
    lastSurface = 727;
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
    m_pointY[0] = -61;
    m_pointX[1] = 21;
    m_pointY[1] = 0;
    m_pointX[2] = 12;
    m_pointY[2] = -5;
    m_pointX[3] = 22;
    m_pointY[3] = -18;
    m_pointX[4] = 25;
    m_pointY[4] = -23;
    m_resultPictures = 5;
    m_rivals[0] = 0;
    m_rivals[1] = 5;
    m_rivals[2] = 10;
    m_rivals[3] = 1;
    m_rivals[10] = 6;
    i = 0;
    for (; i < 64; i++) {
        m_objectTriggered[i] = 0;
        m_objectState[i] = 0;
        m_objectTimer[i] = 0;
        m_objectPhase[i] = 0;
    }
}

void CNagamori::Reset()
{
    int i;

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
    m_pointY[0] = -61;
    m_pointX[1] = 21;
    m_pointY[1] = 0;
    m_pointX[2] = 12;
    m_pointY[2] = -5;
    m_pointX[3] = 22;
    m_pointY[3] = -18;
    m_pointX[4] = 25;
    m_pointY[4] = -23;
    i = 0;
    for (; i < 64; i++) {
        m_objectTriggered[i] = 0;
        m_objectState[i] = 0;
        m_objectTimer[i] = 0;
        m_objectPhase[i] = 0;
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

void CNagamori::RemoveObject(short slot)
{
    m_objectTriggered[slot] = 0;
    m_objectState[slot] = 0;
    m_objectTimer[slot] = 0;
    m_objectPhase[slot] = 0;
    CPlayer::RemoveObject(slot);
}

void CNagamori::TriggerObjectsNear(short centerX, short centerY, short rangeX, short rangeY)
{
    int slot; // the object tested, an index into m_objects

    slot = m_objectTail;
    while (slot != m_objectHead) {
        if (m_objectActive[slot] != 0 && fabs(centerX - m_objects[slot].x) < rangeX && fabs(centerY - m_objects[slot].y) < rangeY) {
            m_objectTriggered[slot] = 1;
        }
        slot++;
        if (slot >= 64) {
            slot = 0;
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
        if (m_hp < 3333 && m_command == kCmd6BA65A && m_gauge >= 3000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_attackResult != 6 && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd641236C && m_gauge >= 3000 && m_shotState == 0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k6413Lv3].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k6413Lv3;
            return;
        }
        if ((m_command == kCmd641236B || m_command == kCmd641236C) && m_shotState == 0 && m_gauge >= 2000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k6413Lv2].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k6413Lv2;
            return;
        }
        if ((m_command == kCmd641236A || m_command == kCmd641236B || m_command == kCmd641236C) && m_shotState == 0 && m_gauge >= 1000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k6413Lv1].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k6413Lv1;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_bouncerOut == 0 && y == 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214C;
            if (y < 0.0) {
                pattern = kAir214214C;
            }
            return;
        }
        if (m_command == kCmd214214B && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214B;
            if (y < 0.0) {
                pattern = kAir214214B;
            }
            return;
        }
        if (m_command == kCmd214214A && m_gauge >= 1000 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_patterns[pattern].cancelLevel <= m_patterns[k214214A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214A;
            if (y < 0.0) {
                pattern = kAir214214A;
            }
            return;
        }
        if (m_command == kCmd236236C && m_gauge >= 3000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236236Lv3].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236Lv3;
            return;
        }
        if ((m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 2000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236236Lv2].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236Lv2;
            return;
        }
        if ((m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 1000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[k236236Lv1].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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
        if (m_command == kCmd214C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_gauge > 50 && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            if (y < 0.0) {
                pattern = kAir214C;
            }
            return;
        }
        if (m_command == kCmd214B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_gauge > 50 && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            if (y < 0.0) {
                pattern = kAir214B;
            }
            return;
        }
        if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_shotState == 0 && m_gauge > 50 && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            if (y < 0.0) {
                pattern = kAir214A;
            }
            return;
        }
        if (m_command == kCmd236C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_shotState == 0 && m_gauge > 50 && m_patterns[pattern].cancelLevel <= m_patterns[kAir236C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236C;
            return;
        }
        if (m_command == kCmd236B && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_shotState == 0 && m_gauge > 50 && m_patterns[pattern].cancelLevel <= m_patterns[kAir236B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir236B;
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_shotState == 0 && m_gauge > 50 && m_patterns[pattern].cancelLevel <= m_patterns[kAir236A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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
            if (m_shotState > 0) {
                pattern = k2CShotOut;
            }
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
            }
        }
    }
}

void CNagamori::DrawGauge()
{
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    if (m_lv4Time > 0) {
        sprite = *anims[0x2b].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(49 - sprite.x, 31 - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 271 - sprite.width, 31 - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_lv4Time > 0) {
        sprite = *anims[0x2c].frames;
        src = MakeRect(0, 0, m_lv4Time * sprite.width / 1200, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(49 - sprite.x, 31 - sprite.y, m_lv4Time * sprite.width / 1200, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 271 - m_lv4Time * sprite.width / 1200, 31 - sprite.y, m_lv4Time * sprite.width / 1200, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
}

void CNagamori::PreUpdate()
{
    if (unk315c > 0) {
        unk315c--;
    }
}

void CNagamori::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CNagamori::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 135);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & (kInputB | kInputC | kInputD)) != 0 && step == 5) {
            break;
        }
        if ((input & kInputA) != 0 && step == 5) {
            m_command = kCmd6BA65A;
            return;
        }
        if (input == 0 && step == 4) {
            step = 5;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 3) {
            step = 4;
        }
        if ((input & (kInputB | kInputC | kInputD)) != 0 && step == 2) {
            break;
        }
        if ((input & kInputA) != 0 && step == 2) {
            step = 3;
        }
        if ((input & (kInputA | kInputC | kInputD)) != 0 && step == 1) {
            break;
        }
        if ((input & kInputB) != 0 && step == 1) {
            step = 2;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 0 && m_gauge == 3000 && y == 0.0) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 80);
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
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 0) {
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
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 1000) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
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
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 1000 && y == 0.0) {
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

void CNagamori::CpuInput()
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
    if ((*m_opponent)->pattern == kWakeUp) {
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
    if ((pattern >= kJump && pattern <= kJumpBack || pattern >= kSuperJump && pattern <= kSuperJumpBack) && y == 0.0) {
        return;
    }
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == 0x108 && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 40.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx > 40.0 && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (dx > 60.0 && dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (dx < 100.0) {
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f + ((m_rfGauge > 500.0) << 1)) {
                m_command = 0x48;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f + ((m_rfGauge > 500.0) << 1)) {
                m_command = ((WORD)Random(0, 1) == 1) * 2 + kCmd623A;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && dx < 60.0 && m_gauge >= 2000) {
                m_command = kCmd236236B;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && dx < 150.0 && m_gauge == 3000) {
                m_command = kCmd236236C;
                return;
            }
        }
        if (dx < 160.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (dx < 220.0 && dx > 160.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f) {
            m_command = (WORD)Random(0, 2) + 70;
            return;
        }
        if (dx > 220.0 && (WORD)Random(0, 100) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
            m_command = (WORD)Random(0, 2) + kCmd236A;
            return;
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
        if (y - (*m_opponent)->y > -30.0 && y - (*m_opponent)->y < 0.0 && dx < 100.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -50.0 && y - (*m_opponent)->y < 50.0 && dy < 60.0 && dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (dy < 50.0 && dx < 100.0 && (WORD)Random(0, 100) < m_cpuSkill * 2) {
            m_command = kCmd623C;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 100);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0) {
            m_command = 0x48;
            return;
        }
        if (m_cpuRoll < 7 && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 10 && m_rfGauge > 500.0) {
            m_command = kCmd623A;
            return;
        }
        if (m_cpuRoll < 13 && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 17 && m_cpuRoll > 12 && m_gauge >= 2000) {
            m_command = (WORD)Random(0, 1) + kCmd236236B;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 100);
        if (m_cpuRoll < 20) {
            m_cpuAction = 2;
            return;
        }
        if (dx < 100.0 && m_cpuRoll < 22) {
            m_command = kCmd623C;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 100) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k623A || pattern == k623B || pattern == k623C || pattern == k412A || pattern == k412B || pattern == k412C)) {
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
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 100) < m_cpuSkill * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 1000);
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 40.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 100) < 30) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (dx < 125.0 && m_cpuRoll > 399 && m_cpuRoll < 700) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 440 && m_attackResult == 2) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
                return;
            }
            if (m_cpuRoll > 950) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 699) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 6;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_command = kCmd214B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 320 && m_cpuRoll < 600 && dx < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 200) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 450 && dx < 90.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 450 && m_cpuRoll < 700) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 920) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 700) {
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
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_command = kCmd214B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 320 && m_cpuRoll < 600 && dx < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 500 && m_attackResult == 3 && dx < 80.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 499 && m_cpuRoll < 550) {
                m_command = (((WORD)Random(0, 2) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 549 && m_cpuRoll < 680) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 950) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 700) {
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
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 250 && dx < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 250 && m_cpuRoll < 350 && dx < 120.0 && m_rfGauge > 500.0) {
                m_command = 0x48;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 430 && m_attackResult == 3 && m_gauge >= 1000 && dx < 90.0) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
            if (m_cpuRoll > 430 && m_cpuRoll < 540) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 540 && m_cpuRoll < 570 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if (m_cpuRoll > 910 && m_attackResult == 3) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == k2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 40.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 400) {
                m_pressA = 1;
                m_inputY = 0;
                if (m_attackResult == 2 && (WORD)Random(0, 100) < 20) {
                    m_pressC = 1;
                    m_inputY = 1;
                }
                return;
            }
            if (dx < 135.0 && m_cpuRoll < 600) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 950) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 699) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 1) == 0) {
                    m_cpuAction = 5;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_command = kCmd214B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 320 && m_cpuRoll < 600 && dx < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 100) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 100 && m_cpuRoll < 300 && dx < 100.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 300 && m_cpuRoll < 600) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 900) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 700) {
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
            if (m_cpuRoll > 0 && m_cpuRoll < 150) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 150 && m_cpuRoll < 350 && dx < 90.0 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 450 && m_attackResult == 3 && m_gauge >= 1000 && dx < 90.0) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
            if (m_cpuRoll > 450 && m_cpuRoll < 640) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 640 && m_cpuRoll < 700 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if (m_cpuRoll > 700) {
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
        if (pattern == kJumpA) {
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
            if (m_cpuRoll < 20 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 20 && m_cpuRoll < 60 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 60 && m_cpuRoll < 80 && m_gauge >= 1000 && (*m_opponent)->y < 0.0) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if (m_cpuRoll > 80 && m_cpuRoll < 300) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 950) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kJumpC) {
            if (m_cpuRoll < 20 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 20 && m_cpuRoll < 90 && m_attackResult == 3 && (*m_opponent)->y < 0.0) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 950) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 3;
                return;
            }
        }
        if (pattern == kDashB) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 299 && m_cpuRoll < 320) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 200) {
                m_command = (((WORD)Random(0, 3) == 0) << 1) * (m_rfGauge > 500.0) + kCmd236A;
                return;
            }
            if (m_cpuRoll > 200 && m_cpuRoll < 250 && dx < 90.0 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 250 && m_cpuRoll < 350 && dx < 120.0 && m_rfGauge > 500.0) {
                m_command = 0x48;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 700) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 700 && m_cpuRoll < 730 && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if (m_cpuRoll > 649 && (WORD)Random(0, 3) == 0) {
                m_cpuAction = 6;
                if (dx > 110.0) {
                    m_cpuAction = 8;
                }
            }
        }
    }
    if ((WORD)Random(0, 100) < 25.0f * m_cpuSkill) {
        m_cpuRoll = (WORD)Random(0, 1000);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown) {
                if (dx < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (dx < 55.0 && m_cpuRoll < 20) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 70.0 && m_cpuRoll < 30) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 100.0 && dx > 70.0 && m_cpuRoll < 15) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 120.0 && m_cpuRoll < 20) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx > 120.0 && m_cpuRoll < 30) {
                    m_cpuAction = 8;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 80 && m_cpuRoll > 37 && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kAirRecoveryForward) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 90.0 && dx > 60.0 && m_cpuRoll < 37) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 100.0 && dx > 70.0 && m_cpuRoll < 40) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 80.0 && m_cpuRoll < 42 && m_cpuRoll > 40) {
                    m_command = kCmd623A;
                    return;
                }
                if (m_cpuRoll < 42 && m_cpuRoll > 50) {
                    m_command = facing;
                    m_cpuAction = 5;
                    return;
                }
                if ((WORD)Random(0, 320) < dx - 70.0 && vy > 0.0 && (*m_opponent)->y > y && m_cpuRoll > 235 && m_cpuRoll < 250) {
                    m_command = (WORD)Random(0, 2) + kCmd214A;
                    return;
                }
                if (dx > 180.0 && m_cpuRoll > 250 && m_cpuRoll < 252 && m_gauge >= 1000) {
                    m_command = (WORD)Random(0, 2) + kCmd214214A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0) {
                    if (dx < 80.0 && dy < 120.0 && m_cpuRoll < 10) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx < 80.0 && m_cpuRoll < 15) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 80.0 && dy < 120.0 && m_cpuRoll < 17) {
                        m_command = kCmd623B;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 80.0 && dy < 120.0) {
                        if (m_cpuRoll < (m_rfGauge > 500.0 || m_rfBlue > 0) * 5 + 6) {
                            m_command = kCmd623B;
                            return;
                        }
                    }
                    if (dx < 90.0 && dy < 120.0 && dy > 90.0 && m_cpuRoll < 15) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 120.0 && dy < 100.0 && m_cpuRoll < 17 && m_gauge >= 2000) {
                        m_command = (WORD)Random(0, 1) + kCmd236236B;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 70.0 && dy < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->y == 0.0) * 100 + 100) {
                        m_pressA = 1;
                        return;
                    }
                }
                if (dx < 120.0 && dy > 50.0 && dy < 60.0 && m_cpuRoll > 200 && m_cpuRoll < 260) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 130.0 && dy > 40.0 && dy < 80.0 && m_cpuRoll > 260 && m_cpuRoll < 265) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 320) < dx - 70.0 && m_cpuRoll > 270 && m_cpuRoll < 350) {
                    m_command = (WORD)Random(0, 2) + kCmd214A;
                    return;
                }
                if (dx > 180.0 && m_cpuRoll > 350 && m_cpuRoll < 352 && m_gauge >= 1000) {
                    m_command = (WORD)Random(0, 2) + kCmd214214A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 80.0 && dy < 80.0 && (*m_opponent)->y < y) {
                    if (m_cpuRoll < (m_rfGauge > 500.0 || m_rfBlue > 0) * 20 + 6) {
                        m_command = kCmd623A;
                        return;
                    }
                }
                if (dx < 140.0 && dy > 90.0 && m_cpuRoll < 110) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 150.0 && dy < 90.0 && m_cpuRoll < 200) {
                    m_pressC = 1;
                    return;
                }
                if (dx > 180.0 && m_cpuRoll > 235 && m_cpuRoll < 250) {
                    m_command = (WORD)Random(0, 2) + kCmd214A;
                    return;
                }
                if (dx > 180.0 && m_cpuRoll > 250 && m_cpuRoll < 252 && m_gauge >= 1000) {
                    m_command = (WORD)Random(0, 2) + kCmd214214A;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 100) < 3.0f * m_cpuSkill) {
        m_command = facing == 1;
        return;
    }
    if ((WORD)Random(0, 1000) < 2) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 100) < 2) {
        if ((WORD)Random(0, 100) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (dx > 160.0 && y == 0.0 && (WORD)Random(0, 100) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx < 100.0 && y == 0.0 && (WORD)Random(0, 100) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx < 170.0 && dx > 120.0 && y == 0.0) {
            m_inputX = facing;
            m_inputY = -1;
            return;
        }
    }
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
    if ((WORD)Random(0, 100) < 50 && dx < 100.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 200) + 30;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 200) + 30;
        }
    }
    if ((WORD)Random(0, 100) < 60) {
        if (facing == 1) {
            m_cpuWalkRight = (WORD)Random(0, 200) + 30;
        } else {
            m_cpuWalkLeft = (WORD)Random(0, 200) + 30;
        }
        return;
    }
    if (facing == -1) {
        m_cpuWalkRight = (WORD)Random(0, 200) + 30;
        return;
    }
    m_cpuWalkLeft = (WORD)Random(0, 200) + 30;
}

void CNagamori::UpdateObjects()
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
            case kObjBomb:
                if (m_objectPhase[slot] == 0) {
                    m_objectPhase[slot] = unk3158 + 10;
                }
                if (m_objects[slot].ay == 0.0) {
                    m_objects[slot].ay = -0.015;
                }
                if (m_objects[slot].vy > 0.7) {
                    m_objects[slot].ay = -0.015;
                }
                if (m_objects[slot].vy < -0.7) {
                    m_objects[slot].ay = 0.015;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objectTriggered[slot] == 1 && m_objectTimer[slot] <= 0) {
                    effect.keep = 0;
                    effect.type = kObjExplosion;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectTriggered[slot] = 0;
                    m_objectTimer[slot] = 120;
                    if (m_keepBombs == 0) {
                        RemoveObject(slot);
                    }
                    break;
                }
                m_objectTriggered[slot] = 0;
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 16) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObjBouncer:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.75;
                    m_objects[slot].vy = -2.5;
                    m_bouncerDrops = 0;
                    m_bouncerOut = 1;
                }
                m_objects[slot].vy += 0.045;
                if (m_objects[slot].vy + m_objects[slot].y >= 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                    m_objects[slot].y = 0.0;
                }
                if (m_objects[slot].timer == 0 && m_objectPhase[slot] >= 20) {
                    effect.keep = 0;
                    effect.type = kObjBouncerDrop;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    m_objectPhase[slot] = 0;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].x > 680.0 || m_objects[slot].x < -40.0) {
                    RemoveObject(slot);
                    m_bouncerOut = 0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objectPhase[slot]++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 9;
                    }
                }
                break;
            case kObjSuperBomb:
                m_objectTimer[slot]--;
                if (m_objects[slot].ay == 0.0) {
                    m_objects[slot].ay = -0.015;
                }
                if (m_objects[slot].vy > 0.7) {
                    m_objects[slot].ay = -0.015;
                }
                if (m_objects[slot].vy < -0.7) {
                    m_objects[slot].ay = 0.015;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objectTriggered[slot] == 1 && m_objectTimer[slot] <= 0) {
                    effect.keep = 0;
                    effect.type = kObjExplosion;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectTriggered[slot] = 0;
                    m_objectTimer[slot] = 120;
                    break;
                }
                m_objectTriggered[slot] = 0;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 12) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObjSuperBombBig:
                if (m_objectPhase[slot] == 0) {
                    m_objectPhase[slot] = unk3158 + 10;
                }
                if (m_objects[slot].ay == 0.0) {
                    m_objects[slot].ay = -0.015;
                }
                if (m_objects[slot].vy > 0.7) {
                    m_objects[slot].ay = -0.015;
                }
                if (m_objects[slot].vy < -0.7) {
                    m_objects[slot].ay = 0.015;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objectTriggered[slot] == 1 && m_objectTimer[slot] <= 0) {
                    effect.keep = 0;
                    effect.type = kObjExplosionBig;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectTriggered[slot] = 0;
                    m_objectTimer[slot] = 120;
                    if (m_keepBombs == 0) {
                        RemoveObject(slot);
                    }
                    break;
                }
                m_objectTriggered[slot] = 0;
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 16) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObj2CFx:
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
            case kObjExplosion:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0) {
                    m_playVoice = 1;
                }
                if (m_objects[slot].frame == 14 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    TriggerObjectsNear((int)m_objects[slot].x, (int)m_objects[slot].y, 90, 90);
                    m_objectTriggered[slot] = 0;
                }
                if (m_objects[slot].attackResult == 3) {
                    m_objectState[slot] = (int)AngleTo(m_objects[slot].x - (*m_opponent)->x, m_objects[slot].y - (*m_opponent)->y - 50.0);
                    (*m_opponent)->SetVelocity((double)m_objectState[slot], 2.2);
                    if ((*m_opponent)->facing == 1) {
                        (*m_opponent)->vx *= -1.0;
                    }
                    m_objects[slot].attackResult = 1;
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
            case kObjBombB:
                if (m_objectPhase[slot] == 2) {
                    if (m_objects[slot].ay == 0.0) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy > 0.7) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy < -0.7) {
                        m_objects[slot].ay = 0.015;
                    }
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                }
                if (m_objectPhase[slot] == 0) {
                    m_objects[slot].vx = 1.8;
                    m_objectPhase[slot] = 1;
                }
                if (m_objectPhase[slot] == 1) {
                    m_objects[slot].vx -= 0.015;
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                }
                if (m_objectTriggered[slot] == 1 && m_objectTimer[slot] <= 0 && m_objectPhase[slot] == 2) {
                    effect.keep = 0;
                    effect.type = kObjExplosion;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectTriggered[slot] = 0;
                    m_objectTimer[slot] = 120;
                    if (m_keepBombs == 0) {
                        RemoveObject(slot);
                    }
                    break;
                }
                m_objectTriggered[slot] = 0;
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 16) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObjBombC:
                if (m_objectPhase[slot] == 2) {
                    if (m_objects[slot].ay == 0.0) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy > 0.7) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy < -0.7) {
                        m_objects[slot].ay = 0.015;
                    }
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                }
                if (m_objectPhase[slot] == 0) {
                    m_objects[slot].vx = 1.8;
                    m_objects[slot].vy = -1.8;
                    m_objectPhase[slot] = 1;
                }
                if (m_objectPhase[slot] == 1) {
                    m_objects[slot].vx -= 0.015;
                    m_objects[slot].vy += 0.015;
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                }
                if (m_objectTriggered[slot] == 1 && m_objectTimer[slot] <= 0 && m_objectPhase[slot] == 2) {
                    effect.keep = 0;
                    effect.type = kObjExplosion;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectTriggered[slot] = 0;
                    m_objectTimer[slot] = 120;
                    if (m_keepBombs == 0) {
                        RemoveObject(slot);
                    }
                    break;
                }
                m_objectTriggered[slot] = 0;
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 16) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObjBombAirC:
                if (m_objectPhase[slot] == 2) {
                    if (m_objects[slot].ay == 0.0) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy > 0.7) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy < -0.7) {
                        m_objects[slot].ay = 0.015;
                    }
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                }
                if (m_objectPhase[slot] == 0) {
                    m_objects[slot].vx = 1.8;
                    m_objects[slot].vy = 1.8;
                    m_objectPhase[slot] = 1;
                }
                if (m_objectPhase[slot] == 1) {
                    m_objects[slot].vx -= 0.015;
                    m_objects[slot].vy -= 0.015;
                    if (m_objects[slot].y > -10.0) {
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                }
                if (m_objectTriggered[slot] == 1 && m_objectTimer[slot] <= 0 && m_objectPhase[slot] == 2) {
                    effect.keep = 0;
                    effect.type = kObjExplosion;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectTriggered[slot] = 0;
                    m_objectTimer[slot] = 120;
                    if (m_keepBombs == 0) {
                        RemoveObject(slot);
                    }
                    break;
                }
                m_objectTriggered[slot] = 0;
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 16) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObjBombRise:
                if (m_objectPhase[slot] == 2) {
                    if (m_objects[slot].ay == 0.0) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy > 0.7) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy < -0.7) {
                        m_objects[slot].ay = 0.015;
                    }
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                }
                if (m_objectPhase[slot] == 0) {
                    m_objects[slot].vy = -1.2;
                    m_objectPhase[slot] = 1;
                }
                if (m_objectPhase[slot] == 1) {
                    m_objects[slot].vy += 0.015;
                    if (m_objects[slot].y > -10.0) {
                        m_objects[slot].vy = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                    if (m_objects[slot].vy > 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                }
                if (m_objectTriggered[slot] == 1 && m_objectTimer[slot] <= 0 && m_objectPhase[slot] == 2) {
                    effect.keep = 0;
                    effect.type = kObjExplosion;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectTriggered[slot] = 0;
                    m_objectTimer[slot] = 120;
                    if (m_keepBombs == 0) {
                        RemoveObject(slot);
                    }
                    break;
                }
                m_objectTriggered[slot] = 0;
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 10) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObjBouncerDrop:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0) {
                    m_playVoice = 1;
                }
                if (m_objects[slot].frame == 6 && m_objects[slot].timer == 0) {
                    m_bouncerDrops++;
                    if (m_bouncerDrops > 2) {
                        m_bouncerDrops = 0;
                    }
                    effect.keep = 0;
                    effect.type = kObjBombFwd;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    effect.type = kObjBombBack;
                    SpawnObject(&effect);
                    effect.type = kObjBombRise;
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
            case kObjShotA:
                TriggerObjectsNear((int)m_objects[slot].x, (int)m_objects[slot].y, 30, 30);
                if (m_shotOrder == 1) {
                    m_objects[slot].vy -= 2.5;
                    if (m_objectState[slot] > 1) {
                        m_objects[slot].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == -1) {
                    m_objects[slot].vy += 2.5;
                    if (m_objectState[slot] > 1) {
                        m_objects[slot].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == 2) {
                    m_shotState = 1;
                    m_objectState[slot] = 1;
                    m_objects[slot].vx = 3.0;
                    if (facing != m_objects[slot].facing) {
                        m_objects[slot].facing = facing;
                    }
                    m_shotOrder = 0;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectState[slot] == 0) {
                    m_objects[slot].vx = 4.2;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot] = 1;
                }
                if (m_objectState[slot] == 1) {
                    m_objects[slot].vx -= 0.045;
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                    }
                }
                if (m_objects[slot].vx == 0.0 && m_objectState[slot] == 1) {
                    m_objectState[slot] = 2;
                    m_shotState = 2;
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] >= 2) {
                    if (m_objects[slot].y < y - 50.0) {
                        m_objects[slot].vy += 0.06;
                    }
                    if (m_objects[slot].y > y - 70.0) {
                        m_objects[slot].vy -= 0.06;
                    }
                    if (m_objects[slot].x < x) {
                        m_objects[slot].vx += m_objects[slot].facing * 0.04;
                    }
                    if (m_objects[slot].x > x) {
                        m_objects[slot].vx = m_objects[slot].vx - m_objects[slot].facing * 0.04;
                    }
                    if (m_objects[slot].vy < -2.0) {
                        m_objects[slot].vy = -2.0;
                    } else if (m_objects[slot].vy > 2.0) {
                        m_objects[slot].vy = 2.0;
                    }
                    if (m_objects[slot].vx < -2.0) {
                        m_objects[slot].vx = -2.0;
                    } else if (m_objects[slot].vx > 2.0) {
                        m_objects[slot].vx = 2.0;
                    }
                    if (m_objects[slot].y > y - 70.0 && m_objects[slot].y < y - 20.0 && m_objects[slot].x > x - 10.0 && m_objects[slot].x < x + 10.0 && m_shotState >= 2) {
                        RemoveObject(slot);
                        m_shotState = 0;
                        m_playSound = 26;
                        break;
                    }
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
            case kObjShotB:
                TriggerObjectsNear((int)m_objects[slot].x, (int)m_objects[slot].y, 30, 30);
                if (m_shotOrder == 1) {
                    m_objects[slot].vy -= 2.5;
                    if (m_objectState[slot] > 1) {
                        m_objects[slot].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == -1) {
                    m_objects[slot].vy += 2.5;
                    if (m_objectState[slot] > 1) {
                        m_objects[slot].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == 2) {
                    m_shotState = 1;
                    m_objectState[slot] = 1;
                    m_objects[slot].vx = 3.0;
                    if (facing != m_objects[slot].facing) {
                        m_objects[slot].facing = facing;
                    }
                    m_shotOrder = 0;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectState[slot] == 0) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = -2.3;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot] = 1;
                }
                if (m_objectState[slot] == 1) {
                    m_objects[slot].vx -= 0.03;
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                    }
                }
                if (m_objects[slot].vx == 0.0 && m_objectState[slot] == 1) {
                    m_objectState[slot] = 2;
                    m_shotState = 2;
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] >= 2) {
                    if (m_objects[slot].y < y - 50.0) {
                        m_objects[slot].vy += 0.06;
                    }
                    if (m_objects[slot].y > y - 70.0) {
                        m_objects[slot].vy -= 0.06;
                    }
                    if (m_objects[slot].x < x) {
                        m_objects[slot].vx += m_objects[slot].facing * 0.06;
                    }
                    if (m_objects[slot].x > x) {
                        m_objects[slot].vx = m_objects[slot].vx - m_objects[slot].facing * 0.06;
                    }
                    if (m_objects[slot].vy < -2.0) {
                        m_objects[slot].vy = -2.0;
                    } else if (m_objects[slot].vy > 2.0) {
                        m_objects[slot].vy = 2.0;
                    }
                    if (m_objects[slot].vx < -2.0) {
                        m_objects[slot].vx = -2.0;
                    } else if (m_objects[slot].vx > 2.0) {
                        m_objects[slot].vx = 2.0;
                    }
                    if (m_objects[slot].y > y - 70.0 && m_objects[slot].y < y - 20.0 && m_objects[slot].x > x - 10.0 && m_objects[slot].x < x + 10.0 && m_shotState >= 2) {
                        RemoveObject(slot);
                        m_shotState = 0;
                        m_playSound = 26;
                        break;
                    }
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
            case kObjShotC:
                if (m_shotOrder == 1) {
                    m_objects[slot].vy -= 2.5;
                    if (m_objectState[slot] > 1) {
                        m_objects[slot].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == -1) {
                    m_objects[slot].vy += 2.5;
                    if (m_objectState[slot] > 1) {
                        m_objects[slot].vx *= 0.5;
                    }
                    m_shotOrder = 0;
                }
                if (m_shotOrder == 2) {
                    m_shotState = 1;
                    m_objectState[slot] = 1;
                    m_objects[slot].vx = 3.0;
                    if (facing != m_objects[slot].facing) {
                        m_objects[slot].facing = facing;
                    }
                    m_shotOrder = 0;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectState[slot] == 0) {
                    m_objects[slot].vx = 2.7;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].hitsLeft = 1;
                    m_objectState[slot] = 1;
                }
                if (m_objectState[slot] == 1) {
                    m_objects[slot].vx -= 0.02;
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                    }
                }
                if (m_objects[slot].vx == 0.0 && m_objectState[slot] == 1) {
                    m_objectState[slot] = 2;
                    m_shotState = 2;
                    m_objects[slot].hitsLeft = 0;
                }
                if (m_objectState[slot] >= 2) {
                    if (m_objects[slot].y < y - 50.0) {
                        m_objects[slot].vy += 0.06;
                    }
                    if (m_objects[slot].y > y - 70.0) {
                        m_objects[slot].vy -= 0.06;
                    }
                    if (m_objects[slot].x < x) {
                        m_objects[slot].vx += m_objects[slot].facing * 0.04;
                    }
                    if (m_objects[slot].x > x) {
                        m_objects[slot].vx = m_objects[slot].vx - m_objects[slot].facing * 0.04;
                    }
                    if (m_objects[slot].vy < -2.0) {
                        m_objects[slot].vy = -2.0;
                    } else if (m_objects[slot].vy > 2.0) {
                        m_objects[slot].vy = 2.0;
                    }
                    if (m_objects[slot].vx < -2.0) {
                        m_objects[slot].vx = -2.0;
                    } else if (m_objects[slot].vx > 2.0) {
                        m_objects[slot].vx = 2.0;
                    }
                    if (m_objectState[slot] > 1 && m_objectTimer[slot] > 89 && m_objectPhase[slot] < 5) {
                        effect.keep = 0;
                        effect.type = kObjBomb;
                        effect.x = (double)(int)m_objects[slot].x;
                        effect.y = (double)(int)m_objects[slot].y;
                        effect.facing = m_objects[slot].facing;
                        effect.scale = 2;
                        effect.layer = 1;
                        SpawnObject(&effect);
                        effect.type = kObjPlaceFx;
                        SpawnObject(&effect);
                        m_objectTimer[slot] = 0;
                        m_objectPhase[slot]++;
                    }
                    if (m_objects[slot].y > y - 70.0 && m_objects[slot].y < y - 20.0 && m_objects[slot].x > x - 10.0 && m_objects[slot].x < x + 10.0 && m_shotState >= 2) {
                        RemoveObject(slot);
                        m_shotState = 0;
                        m_playSound = 26;
                        break;
                    }
                }
                m_objects[slot].timer++;
                m_objectTimer[slot]++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                }
                break;
            case kObjPlaceFx:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0) {
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
            case kObjBombBack:
                if (m_objectPhase[slot] == 2) {
                    if (m_objects[slot].ay == 0.0) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy > 0.7) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy < -0.7) {
                        m_objects[slot].ay = 0.015;
                    }
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                }
                if (m_objectPhase[slot] == 0) {
                    m_objects[slot].vx = -1.2;
                    m_objects[slot].vy = 1.2;
                    m_objectPhase[slot] = 1;
                }
                if (m_objectPhase[slot] == 1) {
                    m_objects[slot].vx += 0.015;
                    m_objects[slot].vy -= 0.015;
                    if (m_objects[slot].y > -10.0) {
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                    if (m_objects[slot].vx > 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                }
                if (m_objectTriggered[slot] == 1 && m_objectTimer[slot] <= 0 && m_objectPhase[slot] == 2) {
                    effect.keep = 0;
                    effect.type = kObjExplosion;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectTriggered[slot] = 0;
                    m_objectTimer[slot] = 120;
                    if (m_keepBombs == 0) {
                        RemoveObject(slot);
                    }
                    break;
                }
                m_objectTriggered[slot] = 0;
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 10) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObjUnused1a0:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0) {
                    m_playVoice = 1;
                    m_keepBombs = 0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                        m_keepBombs = 0;
                    }
                }
                break;
            case kObjLv4Director:
                m_lv4Time--;
                m_freezeTime = 1200;
                (*m_opponent)->m_noGuardTime = 1;
                m_invulTime = 1;
                m_gauge = 0;
                (*m_opponent)->m_koDelay = 2;
                if (m_lv4Time == 0) {
                    m_freezeTime = 0;
                    (*m_opponent)->m_noGuardTime = 0;
                    RemoveObject(slot);
                    m_playSound = 22;
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
                if (m_lv4Time == 1150) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene01;
                    effect.x = 0.0;
                    effect.y = 80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1140) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene02;
                    effect.x = 190.0;
                    effect.y = 320.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1130) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene03;
                    effect.x = 320.0;
                    effect.y = 170.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1120) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene04;
                    effect.x = 0.0;
                    effect.y = 120.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1110) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene05;
                    effect.x = 60.0;
                    effect.y = -80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1100) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene06;
                    effect.x = 320.0;
                    effect.y = 40.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1080) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene07;
                    effect.x = 240.0;
                    effect.y = 320.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1060) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene08;
                    effect.x = 180.0;
                    effect.y = -80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1040) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene09;
                    effect.x = 0.0;
                    effect.y = 80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1020) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene10;
                    effect.x = 180.0;
                    effect.y = -80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 1000) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene11;
                    effect.x = 320.0;
                    effect.y = 210.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 980) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene12;
                    effect.x = 80.0;
                    effect.y = 320.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 970) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene13;
                    effect.x = 240.0;
                    effect.y = 320.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 950) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene14;
                    effect.x = 0.0;
                    effect.y = 60.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 930) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene15;
                    effect.x = 160.0;
                    effect.y = -80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 910) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene16;
                    effect.x = 320.0;
                    effect.y = 80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 890) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene17;
                    effect.x = 180.0;
                    effect.y = 320.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 870) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene18;
                    effect.x = 0.0;
                    effect.y = 160.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 850) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene19;
                    effect.x = 60.0;
                    effect.y = -80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 830) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene20;
                    effect.x = 320.0;
                    effect.y = 50.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 810) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene21;
                    effect.x = 0.0;
                    effect.y = 170.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 790) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene22;
                    effect.x = 320.0;
                    effect.y = 160.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 770) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene23;
                    effect.x = 160.0;
                    effect.y = 320.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 750) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene24;
                    effect.x = 60.0;
                    effect.y = -80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 730) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene25;
                    effect.x = 0.0;
                    effect.y = 120.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 710) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene26;
                    effect.x = 190.0;
                    effect.y = 320.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 690) {
                    effect.keep = 0;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene27;
                    effect.x = 120.0;
                    effect.y = -80.0;
                    effect.facing = 1;
                    effect.scale = 1;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 540) {
                    effect.keep = 1;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene28;
                    effect.x = 0.0;
                    effect.y = 120.0;
                    effect.facing = 1;
                    effect.scale = 0;
                    effect.layer = 0;
                    effect.movesInFreeze = 1;
                    SpawnObject(&effect);
                }
                if (m_lv4Time == 300) {
                    effect.keep = 1;
                    effect.screen = 1;
                    effect.type = kObjLv4Scene29;
                    effect.x = 320.0;
                    effect.y = 160.0;
                    effect.facing = 1;
                    effect.scale = 0;
                    effect.layer = 0;
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
            case kObjLv4Scene01:
                m_objects[slot].vx = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene02:
                m_objects[slot].vy = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene03:
                m_objects[slot].vx = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene04:
                m_objects[slot].vx = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene05:
                m_objects[slot].vy = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene06:
                m_objects[slot].vx = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene07:
                m_objects[slot].vy = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene08:
                m_objects[slot].vy = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene09:
                m_objects[slot].vx = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene10:
                m_objects[slot].vy = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene11:
                m_objects[slot].vx = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene12:
                m_objects[slot].vy = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene13:
                m_objects[slot].vy = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene14:
                m_objects[slot].vx = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene15:
                m_objects[slot].vy = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene16:
                m_objects[slot].vx = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene17:
                m_objects[slot].vy = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene18:
                m_objects[slot].vx = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene19:
                m_objects[slot].vy = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene20:
                m_objects[slot].vx = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene21:
                m_objects[slot].vx = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene22:
                m_objects[slot].vx = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene23:
                m_objects[slot].vy = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = -0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = -10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene24:
                m_objects[slot].vy = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vy = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene25:
                m_objects[slot].vx = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vx = 0.3;
                }
                if (m_objects[slot].timer > 90) {
                    m_objects[slot].vx = 10.0;
                }
                if (m_objects[slot].timer > 130) {
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
            case kObjLv4Scene26:
                m_objects[slot].vy = -10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = -0.3;
                }
                if (m_objects[slot].timer > 150) {
                    m_objects[slot].vy = -10.0;
                }
                if (m_objects[slot].timer > 180) {
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
            case kObjLv4Scene27:
                m_objects[slot].vy = 10.0;
                if (m_objects[slot].timer > 28) {
                    m_objects[slot].vy = 0.3;
                }
                if (m_objects[slot].timer > 150) {
                    m_objects[slot].vy = 10.0;
                }
                if (m_objects[slot].timer > 180) {
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
            case kObjLv4Scene28:
                m_objects[slot].vx = 10.0;
                if (m_objects[slot].timer > 23) {
                    m_objects[slot].vx = 0.3;
                }
                if (m_objects[slot].timer > 510) {
                    m_objects[slot].vx = 10.0;
                }
                if (m_objects[slot].timer > 540) {
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
            case kObjLv4Scene29:
                m_objects[slot].vx = -10.0;
                if (m_objects[slot].timer > 26) {
                    m_objects[slot].vx = -0.3;
                }
                if (m_objects[slot].timer > 270) {
                    m_objects[slot].vx = -10.0;
                }
                if (m_objects[slot].timer > 300) {
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
            case kObjLv4Start:
                if (pattern != kLv4) {
                    RemoveObject(slot);
                }
                if (m_objects[slot].frame == 25) {
                    if (m_patternVar1 == 0) {
                        m_playVoice = 3;
                        TriggerObjectsNear((int)x, (int)y, 320, 320);
                        m_game->FlashWhite(3, 6, 9);
                    }
                    m_patternVar1 = 1;
                }
                if (m_objects[slot].frame == 40) {
                    if (m_patternVar1 == 1) {
                        m_playVoice = 4;
                    }
                    m_patternVar1 = 2;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].pattern = kObjLv4StartEnd;
                    }
                }
                break;
            case kObjLv4StartEnd:
                if (pattern != kLv4) {
                    RemoveObject(slot);
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
            case kObjBombFwd:
                if (m_objectPhase[slot] == 2) {
                    if (m_objects[slot].ay == 0.0) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy > 0.7) {
                        m_objects[slot].ay = -0.015;
                    }
                    if (m_objects[slot].vy < -0.7) {
                        m_objects[slot].ay = 0.015;
                    }
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                }
                if (m_objectPhase[slot] == 0) {
                    m_objects[slot].vx = 1.2;
                    m_objects[slot].vy = 1.2;
                    m_objectPhase[slot] = 1;
                }
                if (m_objectPhase[slot] == 1) {
                    m_objects[slot].vx -= 0.015;
                    m_objects[slot].vy -= 0.015;
                    if (m_objects[slot].y > -10.0) {
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objectPhase[slot] = 2;
                    }
                }
                if (m_objectTriggered[slot] == 1 && m_objectTimer[slot] <= 0 && m_objectPhase[slot] == 2) {
                    effect.keep = 0;
                    effect.type = kObjExplosion;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectTriggered[slot] = 0;
                    m_objectTimer[slot] = 120;
                    if (m_keepBombs == 0) {
                        RemoveObject(slot);
                    }
                    break;
                }
                m_objectTriggered[slot] = 0;
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectState[slot] < 10) {
                            m_objects[slot].frame = 0;
                            m_objectState[slot]++;
                        } else {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObj6413Lv1Blast:
                m_objects[slot].x = x;
                m_objects[slot].y = y - 55.0;
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    effect.keep = 1;
                    effect.type = kObj6413Flash;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
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
            case kObj6413Lv2Blast:
                m_objects[slot].x = x;
                m_objects[slot].y = y - 55.0;
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    effect.keep = 1;
                    effect.type = kObj6413Flash;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
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
            case kObj6413Lv3Blast:
                m_objects[slot].x = x;
                m_objects[slot].y = y - 55.0;
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    effect.keep = 1;
                    effect.type = kObj6413Flash;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
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
            case kObj6413Flash:
                m_objects[slot].x = x;
                m_objects[slot].y = y - 55.0;
                if (m_objects[slot].frame == 1 && m_objects[slot].timer == 0) {
                    m_keepBombs = 0;
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
            case kObjExplosionBig:
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0) {
                    m_playVoice = 1;
                }
                if (m_objects[slot].frame == 13 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    TriggerObjectsNear((int)m_objects[slot].x, (int)m_objects[slot].y, 120, 120);
                    m_objectTriggered[slot] = 0;
                }
                if (m_objects[slot].attackResult == 3) {
                    m_objectState[slot] = (int)AngleTo(m_objects[slot].x - (*m_opponent)->x, m_objects[slot].y - (*m_opponent)->y - 50.0);
                    (*m_opponent)->SetVelocity((double)m_objectState[slot], 2.2);
                    if ((*m_opponent)->facing == 1) {
                        (*m_opponent)->vx *= -1.0;
                    }
                    m_objects[slot].attackResult = 1;
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
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectState[slot] == 0) {
                    m_objectTimer[slot] = (rand() > 16000) * 40 + 80 + (rand() > 16000) * 20;
                    m_objectState[slot]++;
                    m_objects[slot].vx = (rand() > 16000) * 1.2 + (rand() > 16000) * 0.7 + (rand() > 16000) * 1.7 + -1.8;
                    m_objects[slot].vy = -1.2 - ((rand() > 16000) * 0.6 + (rand() > 16000) * 0.9 + (rand() > 16000) * 1.4);
                }
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectTimer[slot] < 10) {
                    m_objects[slot].scale = 1;
                }
                if (m_objectTimer[slot] < 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
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
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectState[slot] == 0) {
                    m_objectTimer[slot] = (rand() > 16000) * 60 + 120 + (rand() > 16000) * 40;
                    m_objectState[slot]++;
                    m_objects[slot].vx = (double)(rand() > 16000) + (rand() > 16000) * 0.5 + (rand() > 16000) * 1.5 + -1.5;
                    m_objects[slot].vy = -1.0 - ((rand() > 16000) * 0.5 + (rand() > 16000) * 0.8 + (rand() > 16000) * 1.2);
                }
                m_objects[slot].vy += 0.03;
                if (m_objects[slot].y > 0.0 && m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = -m_objects[slot].vy;
                }
                if (m_objectTimer[slot] < 10) {
                    m_objects[slot].scale = 1;
                }
                if (m_objectTimer[slot] < 0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                m_objectTimer[slot]--;
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
