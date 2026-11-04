// CMai (0x6163b0-0x62a5df): the character class whose files are in mai\ in the game
// folder (mai.dat sprites, mai.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMai::CMai(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

    strcpy(m_name, "mai");
    lastSurface = 928;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_pointX[0] = -20;
    m_pointY[0] = -58;
    m_pointX[1] = -24;
    m_pointY[1] = 0;
    m_pointX[2] = 4;
    m_pointY[2] = -8;
    m_pointX[3] = 7;
    m_pointY[3] = -12;
    m_pointX[4] = 30;
    m_pointY[4] = -22;
    m_familiarState = 0;
    m_familiarGauge = 0;
    m_familiarSummoned = 0;
    m_familiarRate = 0;
    m_bounceDebrisOut = 0;
    m_resultPictures = 3;
    m_rivals[0] = 0;
    m_rivals[1] = 1;
    m_rivals[2] = 9;
    m_rivals[3] = 2;
    i = 0;
    for (; i < 64; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
}

void CMai::Reset()
{
    int i;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_pointX[0] = -23;
    m_pointY[0] = -58;
    m_pointX[1] = -24;
    m_pointY[1] = 0;
    m_pointX[2] = 4;
    m_pointY[2] = -8;
    m_pointX[3] = 7;
    m_pointY[3] = -12;
    m_pointX[4] = 30;
    m_pointY[4] = -22;
    m_familiarState = 0;
    m_familiarGauge = 0;
    m_familiarSummoned = 0;
    m_familiarRate = 0;
    m_bounceDebrisOut = 0;
    i = 0;
    for (; i < 64; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
    CPlayer::Reset();
}

void CMai::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CMai::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
}

void CMai::Move()
{
    MoveOnGround();
}

void CMai::StartCommand()
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
        if (m_familiarGauge > 0 && m_hp < 3333 && m_command == kCmd236236D && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 4 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAwakened236236D].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAwakened236236D;
            return;
        }
        if (m_hp < 3333 && m_command == kCmd236236D && m_gauge >= 3000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4Awaken].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4Awaken;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 3000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (m_familiarState == 0 || m_familiarState == 1) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv3].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv3;
            if (m_familiarState == 1) {
                pattern = k214214Lv3Familiar;
            }
            return;
        }
        if ((m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 2000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (m_familiarState == 0 || m_familiarState == 1) && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv2].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv2;
            if (m_familiarState == 1) {
                pattern = k214214Lv2Familiar;
            }
            return;
        }
        if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 1000 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (m_familiarState == 0 || m_familiarState == 1) && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv1].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv1;
            if (m_familiarState == 1) {
                pattern = k214214Lv1Familiar;
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
        if (m_command == kCmd623C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 0 && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k623C].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623C;
            return;
        }
        if ((m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 0 && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k623B].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623B;
            return;
        }
        if (m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 0 && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k623A].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
            return;
        }
        if (m_command == kCmd623C && (m_rfGauge >= 500.0 || m_rfBlue > 0 || m_familiarState == 4) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kAir623C].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir623C;
            return;
        }
        if ((m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kAir623B].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir623B;
            return;
        }
        if (m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y < 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kAir623A].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAir623A;
            return;
        }
        if (m_command == kCmd214C && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (m_familiarState == 0 || m_familiarState == 4) && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k214C].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            return;
        }
        if ((m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (m_familiarState == 0 || m_familiarState == 4) && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k214B].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            return;
        }
        if (m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (m_familiarState == 0 || m_familiarState == 4) && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k214A].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            return;
        }
        if (m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 0 && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k236C].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            return;
        }
        if ((m_command == kCmd236C || m_command == kCmd236B) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 0 && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k236B].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236B;
            return;
        }
        if (m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 0 && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k236A].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236A;
            return;
        }
        if (m_command == kCmd412C && (m_familiarState == 4 || m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k412C].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412C;
            return;
        }
        if ((m_command == kCmd412B || m_command == kCmd412C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k412B].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412B;
            return;
        }
        if (m_command == kCmd412A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (m_patterns[pattern].cancelLevel <= m_patterns[k412A].level || pattern == k6C) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k412A;
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
        if (m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) {
            if (m_familiarState == 4 && m_patterns[pattern].cancelLevel <= m_patterns[k6AAwakened].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k6AAwakened;
                return;
            }
            if (pattern != k6C && m_patterns[pattern].cancelLevel <= m_patterns[k6A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k6A;
                if (m_familiarState == 4) {
                    pattern = k6AAwakened;
                }
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[k5A].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k5A;
                return;
            }
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
            if (m_familiarState == 4 && m_patterns[pattern].cancelLevel <= m_patterns[k6BAwakened].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k6BAwakened;
                return;
            }
            if (pattern != k6C && m_patterns[pattern].cancelLevel <= m_patterns[k6B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k6B;
                if (m_familiarState == 4) {
                    pattern = k6BAwakened;
                }
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
        if (y < -10.0 && pattern == kDashForward) {
            StartPattern();
            ClearBufferedPress();
            pattern = kDashHopC;
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
        if ((m_inputY == 1 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k4C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_inputX == facing) {
            StartPattern();
            ClearBufferedPress();
            pattern = k4C;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) {
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = kThrow;
                return;
            }
            if (m_familiarState == 4 && m_patterns[pattern].cancelLevel <= m_patterns[k6CAwakened].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k6CAwakened;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[k6C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k6C;
                if (m_familiarState == 4) {
                    pattern = k6CAwakened;
                }
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[k4C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == -facing && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k4C;
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
    if (m_sealLevel < 2 && m_inputY == 0 && m_pressD == 1) {
        if (m_patterns[pattern].cancelLevel <= m_patterns[kSummonFamiliar].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kSummonFamiliar;
            if (m_inputX == facing) {
                m_patternVar3 = 1;
            }
            if (m_inputX == -facing) {
                m_patternVar3 = 2;
            }
            return;
        }
        if (m_command == kCmdNone && m_patterns[pattern].cancelLevel <= m_patterns[kRecallFamiliar].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 1 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = kRecallFamiliar;
        }
    }
}

void CMai::DrawGauge()
{
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    if (m_familiarGauge > 0 && m_familiarState != 3) {
        sprite = *anims[0x29].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(49 - sprite.x, 31 - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 271 - sprite.width, 31 - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_familiarState == 3) {
        sprite = *anims[0x2a].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(49 - sprite.x, 31 - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 271 - sprite.width, 31 - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_familiarGauge > 0 && m_familiarState != 3) {
        sprite = *anims[0x2b].frames;
        src = MakeRect(0, 0, sprite.width * m_familiarGauge / 10000, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(49 - sprite.x, 31 - sprite.y, m_familiarGauge * sprite.width / 10000, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 271 - m_familiarGauge * sprite.width / 10000, 31 - sprite.y, m_familiarGauge * sprite.width / 10000, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_familiarState == 3) {
        sprite = *anims[0x2c].frames;
        src = MakeRect(0, 0, m_familiarGauge * sprite.width / 1200, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(49 - sprite.x, 31 - sprite.y, m_familiarGauge * sprite.width / 1200, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 271 - m_familiarGauge * sprite.width / 1200, 31 - sprite.y, m_familiarGauge * sprite.width / 1200, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
}

void CMai::PreUpdate()
{
    EffectDesc effect; // what CreateEffect or SpawnObject is to make
    InitEffectDesc((EffectDesc*)&effect);
    if (m_familiarGauge > 0) {
        m_familiarGauge--;
        if (m_familiarState == 3) {
            m_familiarGauge--;
        }
        if (m_familiarRate == 1) {
            m_familiarGauge -= 4;
        }
        if (m_familiarRate == 2) {
            m_familiarGauge++;
        }
        if (m_familiarRate == 3) {
            m_familiarGauge--;
        }
        if (m_familiarRate == 4) {
            m_familiarGauge--;
        }
    }
    if (m_familiarState == 4) {
        m_gauge = 0;
        m_game->FlashNegative(3);
    }
    if (m_familiarGauge <= 0) {
        if (m_familiarState == 3) {
            effect.type = kEffectEnergySphere;
            effect.sound = 11;
            effect.x = (double)(int)x;
            effect.y = (double)(int)(y - 40.0);
            effect.scale = 2;
            effect.layer = 1;
            m_game->CreateEffect((EffectDesc*)&effect);
            m_familiarState = 0;
            m_familiarGauge = 0;
            m_familiarSummoned = 0;
            m_familiarRate = 0;
        }
        if (m_familiarState == 4 && pattern != kAwakened236236D && pattern != kAwakened236236DHit) {
            m_familiarGauge = 1200;
            m_familiarState = 3;
            m_familiarSummoned = 0;
            m_familiarRate = 2;
        }
    }
}

void CMai::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CMai::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
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
        if ((input & kInputDirections) == kInputDown && step == 0) {
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

void CMai::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == k236B && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 100.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if (dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (dx < 120.0) {
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 60.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_gauge >= 1000) {
                m_command = kCmd214214A;
                return;
            }
            if (dx < 100.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if (dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_gauge >= 1000) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
        }
        if (dx < 160.0) {
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_gauge >= 1000) {
                m_command = kCmd214214A;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd214C;
                return;
            }
        }
        if (dx < 220.0 && dx > 160.0) {
            if ((WORD)Random(0, 100) < m_cpuSkill * 2 && m_gauge == 3000) {
                m_command = kCmd236236C;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 2) {
                m_command = kCmd412A;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && y == 0.0) {
                m_pressB = 1;
                m_inputX = facing;
                return;
            }
            if ((WORD)Random(0, 100) < m_cpuSkill * 3.0f && y == 0.0) {
                m_pressC = 1;
                m_inputX = facing;
                return;
            }
        }
        if (dx > 220.0 && (WORD)Random(0, 100) < m_cpuSkill * 2) {
            m_command = kCmd412A;
            return;
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (dy < 70.0 && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (dy < 60.0 && dx < 70.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_command = kCmd623A;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (dy < 40.0 && dx < 120.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && dx < 80.0 && (WORD)Random(0, 100) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 100);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0 && dx < 90.0 && (*m_opponent)->y == 0.0) {
            m_command = 0x48;
            return;
        }
        if (m_cpuRoll < 7 && m_rfGauge > 500.0 && dx < 70.0) {
            m_command = kCmd214C;
            return;
        }
        if (m_cpuRoll < 17 && m_cpuRoll > 12 && m_gauge >= 1000 && dx < 140.0) {
            m_command = (WORD)Random(0, 2) + kCmd214214A;
            return;
        }
        if (m_cpuRoll < 18 && m_cpuRoll > 22 && m_gauge >= 1000 && dx < 100.0) {
            m_command = (WORD)Random(0, 2) + kCmd236236A;
            return;
        }
        if (m_cpuRoll < 30) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 100) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 100);
        if (m_cpuRoll < 30) {
            m_cpuAction = 2;
            return;
        }
        if (dx < 100.0 && m_cpuRoll < 22 && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (dx < 100.0 && m_cpuRoll < 42) {
            m_command = kCmd623A;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 100) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == kAir623A || pattern == kAir623B || pattern == kAir623C || pattern == k412C || pattern == k236236Lv1 || pattern == k236236Lv2 || pattern == k236236Lv3)) {
        m_command = kCmd22C;
        return;
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 100) < 1.0f * m_cpuSkill && m_attackResult == 3 && (pattern == k412C || pattern == k6C && dx < 60.0)) {
        m_command = kCmd22C;
        return;
    }
    if ((pattern == k412A || pattern == k412B) && m_familiarState == 0 && m_familiarSummoned == 1 && (WORD)Random(0, 100) < 5.0f * m_cpuSkill) {
        m_pressD = 1;
        m_inputX = facing;
        return;
    }
    if (pattern == kWakeUp && dx < 120.0 && m_familiarState == 0 && m_familiarSummoned == 1 && (WORD)Random(0, 100) < 5.0f * m_cpuSkill) {
        m_pressD = 1;
        m_inputX = facing;
        return;
    }
    if ((*m_opponent)->pattern > kHitCrouchHeavy && (*m_opponent)->pattern < kAirRecoveryForward && m_familiarSummoned == 0 && (WORD)Random(0, 100) < 5.0f * m_cpuSkill) {
        m_pressD = 1;
        m_inputX = 0;
        m_inputY = 0;
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
    if (m_cpuAction == 6) {
        if (y == 0.0) {
            m_inputY = -1;
            m_inputX = facing;
        }
        if (y < 0.0) {
            m_command = kCmd623A;
        }
        if (pattern == kAir623A) {
            m_cpuAction = 0;
            if (m_familiarState == 0 && m_familiarSummoned == 1) {
                m_pressD = 1;
                m_inputX = ((WORD)Random(0, 2) == 0) * facing;
            }
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
            if (dx < 160.0 && m_cpuRoll < 10) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 125.0 && m_cpuRoll > 100 && m_cpuRoll < 400) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 440) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 900 - (m_familiarState == 0 && m_familiarSummoned == 0) * 200) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 699 - (m_familiarState == 0 && m_familiarSummoned == 1) * 300) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 200 && m_attackResult == 3) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (dx < 50.0 && m_attackResult == 2 && m_cpuRoll < 150 && (WORD)Random(0, 3) == 0) {
                m_cpuAction = 6;
                m_inputY = 0;
                m_pressA = 0;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 200 && m_cpuRoll < 500) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 130 && m_familiarSummoned == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 130 && m_cpuRoll < 400 && dx < 140.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 400 && m_cpuRoll < 460 && dx < 140.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 570 - (m_familiarSummoned == 1) * 150 && m_cpuRoll < 680) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 460 && m_cpuRoll < 560 && (*m_opponent)->y == 0.0 && dx < 100.0 && m_familiarSummoned == 0) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 900 - (m_familiarState == 0 && m_familiarSummoned == 0) * 200) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
                return;
            }
            if (m_cpuRoll > 700 - (m_familiarState == 0 && m_familiarSummoned == 0) * 200) {
                m_cpuAction = 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && dx < 90.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 300 && m_cpuRoll < 500 && dx > 150.0) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 500 && m_cpuRoll < 600 && m_familiarSummoned == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll < 100 && dx < 110.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 100 && m_cpuRoll < 300) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 300 && m_cpuRoll < 450 && (*m_opponent)->y == 0.0) {
                m_command = kCmd214A;
                if (dx > 120.0) {
                    m_command = kCmd214B;
                }
                return;
            }
            if (m_cpuRoll > 570 && m_cpuRoll < 620) {
                m_command = (WORD)Random(0, 1) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 900 - (m_familiarState == 0 && m_familiarSummoned == 0) * 200) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
                return;
            }
            if (m_cpuRoll > 700) {
                m_cpuAction = 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
            }
        }
        if (pattern == k5C) {
            if (m_cpuRoll > 200 && m_cpuRoll < 500 && m_familiarSummoned == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 300 && (*m_opponent)->y == 0.0) {
                m_pressC = 1;
                m_inputX = facing;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 500 && m_cpuRoll < 550 && (*m_opponent)->y == 0.0) {
                m_command = kCmd214A;
                if (dx > 120.0) {
                    m_command = kCmd214B;
                }
                return;
            }
            if (m_cpuRoll > 650 && m_cpuRoll < 700) {
                m_command = (WORD)Random(0, 1) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 650 && m_cpuRoll < 700) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 700) {
                m_cpuAction = 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
            }
        }
        if (pattern == k2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300 && dx < 50.0) {
                m_pressA = 1;
                m_inputY = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 6;
                    m_inputY = 0;
                    m_pressA = 0;
                }
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 400) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 900 - (m_familiarState == 0 && m_familiarSummoned == 0) * 100) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
                return;
            }
            if (m_cpuRoll > 800) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == k2B) {
            if (m_cpuRoll < 300) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll < 400 && dx > 140.0 && (*m_opponent)->y == 0.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll < 400 && m_cpuRoll < 500 && dx < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 550 - (m_familiarSummoned == 1) * 150 && m_cpuRoll < 700) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 900 - (m_familiarState == 0 && m_familiarSummoned == 0) * 200 && m_attackResult == 3) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 900 - (m_familiarState == 0 && m_familiarSummoned == 0) * 200) {
                m_cpuAction = 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 200 && m_cpuRoll < 500 && m_familiarSummoned == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 300) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 350 && m_cpuRoll < 400 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 550 - (m_familiarSummoned == 1) * 150 && m_cpuRoll < 700) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 700) {
                m_cpuAction = 1;
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
            if (m_cpuRoll > 699 - (m_familiarState == 0 && m_familiarSummoned == 1) * 300) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 3;
                }
                return;
            }
        }
        if (pattern == kJumpB) {
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
            if (m_cpuRoll > 950) {
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 649) {
                m_cpuAction = 3;
                return;
            }
        }
    }
    if ((WORD)Random(0, 100) < 25.0f * m_cpuSkill) {
        m_cpuRoll = (WORD)Random(0, 1000);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown) {
                if (dx < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 3) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (dx < 60.0 && (*m_opponent)->pattern < kFirstHitReaction && (*m_opponent)->pattern < kRecoilGuardStand && m_cpuRoll < 5) {
                    m_cpuAction = 6;
                    return;
                }
                if (dx < 50.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward) * 50 + 25 && (*m_opponent)->pattern < kFirstCharacterAction) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (dx < 80.0 && m_cpuRoll < 10 && m_gauge >= 1000 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 2) + kCmd236236A;
                    return;
                }
                if (dx > 80.0 && dx < 120.0 && m_cpuRoll < 20) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 130.0 && dx > 80.0 && m_cpuRoll < 30 && m_cpuRoll > 15) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 150.0 && dx > 90.0 && m_cpuRoll < 30 && m_cpuRoll > 20) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 200.0 && dx > 160.0 && m_cpuRoll < 45 && m_cpuRoll > 30) {
                    m_pressB = 1;
                    if ((WORD)Random(0, 2) == 0) {
                        m_pressB = 0;
                        m_pressC = 1;
                    }
                    m_inputY = 0;
                    m_inputX = facing;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0) {
                    if (dx < 80.0 && dy < 180.0 && dy > 90.0 && m_cpuRoll < 30) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx > 130.0 && dy < 180.0 && dy > 90.0 && m_cpuRoll > 30 && m_cpuRoll < 70) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx < 150.0 && dx > 60.0 && m_cpuRoll > 70 && m_cpuRoll < 110) {
                        m_pressA = 1;
                        m_inputX = facing;
                        m_inputY = 0;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 80.0 && dy < 180.0 && dy > 90.0 && m_cpuRoll < 30) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx > 130.0 && dy < 180.0 && dy > 90.0 && m_cpuRoll > 30 && m_cpuRoll < 70) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (dx < 150.0 && dx > 60.0 && dy > 130.0 && m_cpuRoll > 70 && m_cpuRoll < 110) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (dx < 100.0 && dy > 160.0 && dy < 240.0 && m_cpuRoll > 0 && m_cpuRoll < 140) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 140.0 && dx > 90.0 && dy > 90.0 && m_cpuRoll > 160 && m_cpuRoll < 220) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (dx < 130.0 && dy < 80.0 && m_cpuRoll > 220 && m_cpuRoll < 300 && m_rfGauge > 500.0) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 100.0 && dy < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->y == 0.0) * 100 + 100) {
                        m_pressA = 1;
                        return;
                    }
                }
                if (dx < 140.0 && dy < 80.0 && m_cpuRoll > 200 && m_cpuRoll < 260) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 140.0 && dx > 80.0 && dy > 40.0 && dy < 80.0 && m_cpuRoll > 260 && m_cpuRoll < 265) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 120.0 && dy < 90.0 && (*m_opponent)->y > y && m_cpuRoll < 110) {
                    m_pressA = 1;
                    return;
                }
                if (dx < 140.0 && dy < 90.0 && m_cpuRoll < 210) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 150.0 && dx > 100.0 && dy < 90.0 && (*m_opponent)->y > y && m_cpuRoll < 2500) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0) {
        if ((WORD)Random(0, 100) < ((m_familiarState == 1 && m_familiarSummoned == 1 && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir)) * 2 + (((*m_opponent)->pattern == kLyingDown) << 2) + 1) * m_cpuSkill && dx > 80.0) {
            m_command = facing == 1;
            return;
        }
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && dx > 60.0 && dx < 140.0 && (WORD)Random(0, 100) < 2.0f * m_cpuSkill && x > 120.0 && x < 520.0 && m_familiarSummoned == 0) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if ((WORD)Random(0, 1000) < (m_familiarSummoned == 1) + 2) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 100) < 2) {
        if ((WORD)Random(0, 100) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (dx > 160.0 && y == 0.0 && (WORD)Random(0, 100) < 3) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx < 100.0 && y == 0.0 && (WORD)Random(0, 100) < 2 && (*m_opponent)->pattern < kRecoilGuardStand) {
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
    if ((WORD)Random(0, 100) < 60 && dx < 150.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 200) + 60;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 200) + 60;
        }
    }
    if ((WORD)Random(0, 100) < 40) {
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

void CMai::UpdateObjects()
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
            case kObjFamiliar:
                m_familiarState = 1;
                if (m_objects[slot].frame > 2) {
                    if (m_objects[slot].vx >= 0.1) {
                        m_objects[slot].vx -= 0.02;
                    }
                    if (m_objects[slot].vx <= -0.1) {
                        m_objects[slot].vx += 0.02;
                    }
                    if (m_objects[slot].vy >= 0.1) {
                        m_objects[slot].vy -= 0.02;
                    }
                    if (m_objects[slot].vy <= -0.1) {
                        m_objects[slot].vy += 0.02;
                    }
                    if (m_objects[slot].vx < 0.1 && m_objects[slot].vx > -0.1) {
                        m_objects[slot].vx = 0.0;
                    }
                    if (m_objects[slot].vy < 0.1 && m_objects[slot].vy > -0.1) {
                        m_objects[slot].vy = 0.0;
                    }
                    if (m_familiarRate == 1) {
                        m_familiarRate = 0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        if (m_objects[slot].y > -30.0) {
                            effect.type = 0x1f;
                            effect.x = (double)(int)m_objects[slot].x;
                            effect.y = (double)(int)m_objects[slot].y;
                            effect.scale = 0;
                            effect.layer = 0;
                            effect.side = m_objects[slot].facing == -1;
                            m_game->CreateEffect((EffectDesc*)&effect);
                        }
                    }
                    if (m_familiarGauge <= 0) {
                        m_objects[slot].pattern = kObjFamiliarExpire;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = 0;
                        m_familiarGauge = 0;
                        m_familiarState = 2;
                        break;
                    }
                    if (m_objects[slot].x > (*m_opponent)->x) {
                        m_objects[slot].facing = -1;
                    }
                    if (m_objects[slot].x <= (*m_opponent)->x) {
                        m_objects[slot].facing = 1;
                    }
                    if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                        m_objects[slot].pattern = kObjFamiliarKnockedOut;
                        m_familiarState = 2;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        break;
                    }
                    if (pattern == kRecallFamiliar) {
                        m_objects[slot].pattern = kObjFamiliarRecall;
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = 0;
                        m_familiarGauge = 0;
                        break;
                    }
                    if (pattern == k214214Lv3Familiar && frame == 3 && timer == 0) {
                        m_objects[slot].pattern = kObjFamiliarOut214214Lv3;
                        m_familiarState = 2;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        break;
                    }
                    if (pattern == k214214Lv2Familiar && frame == 3 && timer == 0) {
                        m_objects[slot].pattern = kObjFamiliarOut214214Lv2;
                        m_familiarState = 2;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        break;
                    }
                    if (pattern == k214214Lv1Familiar && frame == 3 && timer == 0) {
                        m_objects[slot].pattern = kObjFamiliarOut214214Lv1;
                        m_familiarState = 2;
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        break;
                    }
                    if ((pattern < kFirstGuard || pattern > kGuardAir) && pattern != kRecoilGuardStand && pattern != kRecoilGuardCrouch && pattern != kRecoilGuardAir && pattern != kSummonFamiliar && pattern != kRecallFamiliar) {
                        if (m_command == kCmd214D) {
                            m_objects[slot].pattern = kObjFamiliar214D;
                            m_objects[slot].frame = 0;
                            m_objects[slot].timer = 0;
                            m_familiarState = 2;
                            break;
                        }
                        if (m_command == kCmd412D) {
                            m_objects[slot].pattern = kObjFamiliar412D;
                            m_objects[slot].frame = 0;
                            m_objects[slot].timer = 0;
                            m_familiarState = 2;
                            break;
                        }
                        if (m_command == kCmd236D) {
                            m_objects[slot].pattern = kObjFamiliar236D;
                            m_objects[slot].frame = 0;
                            m_objects[slot].timer = 0;
                            m_familiarState = 2;
                            break;
                        }
                        if (m_command == kCmd22D) {
                            m_objects[slot].pattern = kObjFamiliar22D;
                            m_objects[slot].frame = 0;
                            m_objects[slot].timer = 0;
                            m_familiarState = 2;
                            break;
                        }
                    }
                }
                if (m_objects[slot].x > 600.0) {
                    m_objects[slot].x = 600.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 40.0) {
                    m_objects[slot].x = 40.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 3;
                    }
                }
                break;
            case kObjFamiliarKnockedOut:
                m_familiarState = 2;
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = -2.0;
                    m_objects[slot].vy = -2.0;
                    m_objects[slot].ax = 0.05;
                    m_objectVar1[slot] = 1;
                }
                m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ax;
                if (m_objects[slot].vx > 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].attackResult == 1) {
                    RemoveObject(slot);
                }
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 && m_objectVar2[slot] < 5) {
                        m_objectVar2[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarSummoned = 0;
                        m_familiarGauge = 1200;
                        m_familiarState = 3;
                        m_objectVar2[slot] = 0;
                        m_objectVar1[slot] = 0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliarExpire:
                m_familiarState = 2;
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarGauge = 1200;
                        m_familiarState = 3;
                        m_familiarRate = 0;
                        m_familiarSummoned = 0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliarRecall:
                m_familiarState = 2;
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarGauge = 1200;
                        m_familiarState = 3;
                        m_familiarRate = 1;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliarUnusedFly:
                m_familiarGauge--;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objects[slot].x > 590.0 && m_objects[slot].facing == 1) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 50.0 && m_objects[slot].facing == -1) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vx < 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0) {
                    if (m_familiarGauge > 1) {
                        m_familiarGauge -= 5000;
                    } else {
                        m_familiarGauge = 0;
                    }
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].ax = 0.0;
                }
                if (m_objects[slot].frame == 7 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 2.5;
                    m_objects[slot].ax = -0.015;
                    m_objectVar1[slot] = 6;
                    m_objects[slot].vy = 0.9;
                    m_objects[slot].ay = -0.035;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 11 && m_objectVar1[slot] > 0) {
                        m_objects[slot].frame = 7;
                        m_objectVar1[slot]--;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].pattern = kObjFamiliar;
                        m_familiarState = 0;
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjFamiliarUnusedShoot:
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0 && m_objectVar2[slot] == 0) {
                    m_familiarGauge = 0;
                }
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0 && m_objectVar2[slot] != 1) {
                    effect.type = 0x198;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 29);
                    effect.y = (double)(int)(m_objects[slot].y - 49.0);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                    m_objectVar2[slot] = 1;
                    m_objectVar1[slot] = 0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 8 && m_objectVar1[slot] < 5) {
                        m_objects[slot].frame = m_objects[slot].frame - 4;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].pattern = kObjFamiliarExpire;
                        m_familiarState = 0;
                        m_objects[slot].frame = 0;
                        m_objectVar2[slot] = 0;
                        m_objectVar1[slot] = 0;
                    }
                }
                break;
            case kObjUnusedHomingShot:
                if (m_objects[slot].timer == 0 && m_objects[slot].frame == 0 && m_objectVar1[slot] <= 0) {
                    if (m_objectVar2[slot] == 0) {
                        m_objects[slot].hitsLeft = 1;
                    }
                    if (m_objectVar2[slot] < 3 && m_objects[slot].hitsLeft > 0) {
                        m_objectVar3[slot] = (int)AngleTo((*m_opponent)->x - m_objects[slot].x, (*m_opponent)->y - 50.0 - m_objects[slot].y);
                        m_objects[slot].SetVelocity((double)m_objectVar3[slot], -0.00875);
                        m_objects[slot].ax = m_objects[slot].vx;
                        m_objects[slot].ay = m_objects[slot].vy;
                        m_objects[slot].SetVelocity((double)m_objectVar3[slot], 1.4);
                        if (m_objects[slot].facing == -1) {
                            m_objects[slot].ax = -m_objects[slot].ax;
                            m_objects[slot].vx = -m_objects[slot].vx;
                        }
                        m_objectVar3[slot] = 160;
                        m_objectVar2[slot]++;
                        m_objectVar1[slot] = 240;
                    }
                }
                if (m_objectVar3[slot] > 0) {
                    m_objects[slot].vx = m_objects[slot].vx + m_objects[slot].ax;
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                    m_objectVar3[slot]--;
                }
                m_objectVar1[slot]--;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        if ((m_objectVar2[slot] > 2 || m_objects[slot].hitsLeft == 0) && m_objectVar1[slot] <= 0) {
                            RemoveObject(slot);
                        }
                    }
                }
                break;
            case kObjFamiliarUnusedSuper:
                m_familiarState = 1;
                if (pattern == kUnusedSuperLv3) {
                    m_game->FlashNegative(15);
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].movesInFreeze = 1;
                    if (pattern == kUnusedSuperLv1) {
                        m_gauge = m_gauge - 1000;
                    }
                    if (pattern == kUnusedSuperLv2) {
                        m_gauge = m_gauge - 2000;
                    }
                    if (pattern == kUnusedSuperLv3) {
                        m_gauge = m_gauge - 3000;
                    }
                    m_patternVar3 = 0;
                    m_objectVar1[slot] = 0;
                    m_freezeTime = 120;
                    FillBackground(176, 3);
                    effect.type = 9;
                    effect.sound = 5;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 28);
                    effect.y = (double)(int)(m_objects[slot].y - 52.0);
                    effect.scale = 2;
                    effect.keep = 1;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_playSound = 37;
                }
                if (m_objects[slot].frame > 4 && m_objects[slot].frame < 12 && m_freezeTime == 0) {
                    if (m_objectVar3[slot] == 0) {
                        m_playVoice = 6;
                        m_objectVar3[slot]++;
                    }
                    if (m_objectVar2[slot] >= 15) {
                        m_objectVar2[slot] = 0;
                        if (pattern == kUnusedSuperLv1 && m_patternVar3 < 3) {
                            effect.type = 0x19a;
                            effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 29);
                            effect.y = (double)(int)(m_objects[slot].y - 49.0);
                            effect.scale = 2;
                            effect.layer = 1;
                            effect.facing = m_objects[slot].facing;
                            effect.facing = effect.facing;
                            SpawnObject(&effect);
                            m_patternVar3++;
                        }
                        if (pattern == kUnusedSuperLv2 && m_patternVar3 < 5) {
                            effect.type = 0x1a7;
                            effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 29);
                            effect.y = (double)(int)(m_objects[slot].y - 49.0);
                            effect.scale = 2;
                            effect.layer = 1;
                            effect.facing = m_objects[slot].facing;
                            effect.facing = effect.facing;
                            SpawnObject(&effect);
                            m_patternVar3++;
                        }
                        if (pattern == kUnusedSuperLv3 && m_patternVar3 < 10) {
                            effect.type = 0x1a9;
                            effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 29);
                            effect.y = (double)(int)(m_objects[slot].y - 49.0);
                            effect.scale = 2;
                            effect.layer = 1;
                            effect.facing = m_objects[slot].facing;
                            effect.facing = effect.facing;
                            SpawnObject(&effect);
                            m_patternVar3++;
                        }
                    }
                }
                m_objects[slot].vx = 0.0;
                m_objects[slot].vy = 0.0;
                m_objectVar2[slot]++;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 12 && m_objectVar1[slot] < 5) {
                        m_objects[slot].frame = m_objects[slot].frame - 4;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].pattern = kObjFamiliarExpire;
                        m_familiarState = 0;
                        m_objects[slot].movesInFreeze = 0;
                        m_objects[slot].frame = 0;
                    }
                }
                break;
            case kObjUnusedDropLv1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = m_patternVar3;
                    m_objectVar1[slot]++;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vy += 0.045;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjUnusedBurstLv1;
                    m_playSound = 18;
                }
                break;
            case kObjUnusedBurstLv1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 7;
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
            case kObjFamiliar214:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 6;
                    m_objectVar2[slot] = 180;
                }
                if (m_objects[slot].frame > 5) {
                    m_objectVar2[slot] -= 4;
                }
                if (m_objectVar2[slot] < 15) {
                    m_objectVar2[slot] = 15;
                }
                if (m_objects[slot].frame > 4) {
                    m_objects[slot].SetVelocity(-60.0, m_objectVar2[slot] * 0.01);
                }
                if (m_objects[slot].frame > 8) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 6 || m_objects[slot].frame == 8) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == 8 && m_objectVar1[slot] < 8) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        break;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarSummoned = 0;
                        m_familiarGauge = 1200;
                        m_familiarRate = 1;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        RemoveObject(slot);
                        break;
                    }
                }
                break;
            case kObjFamiliarUnusedWalk:
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 4;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 2) {
                        m_objects[slot].vx = 0.6;
                    }
                    if (m_objects[slot].frame == 4 && m_objectVar1[slot] < 20) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 7) {
                        m_objects[slot].vy = -0.1;
                        m_objects[slot].vx = 0.0;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] < 14) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            break;
                        }
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].pattern = kObjFamiliar22D;
                        break;
                    }
                }
                break;
            case kObjFamiliar22D:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 6;
                    m_objectVar2[slot] = 180;
                }
                if (m_objects[slot].frame > 1) {
                    m_objectVar2[slot] -= 2;
                }
                if (m_objectVar2[slot] < 30) {
                    m_objectVar2[slot] = 30;
                }
                if (m_objects[slot].frame > 0) {
                    m_objects[slot].SetVelocity(-30.0, m_objectVar2[slot] * 0.01);
                }
                if (m_objects[slot].frame > 4) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 2 || m_objects[slot].frame == 4) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == 4 && m_objectVar1[slot] < 12) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        break;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarSummoned = 0;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        RemoveObject(slot);
                        break;
                    }
                }
                break;
            case kObj6A:
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
            case kObj6B:
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
            case kObj6C:
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
            case kObjAir623C:
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
            case kObjFlurryOverlay1:
                if (pattern != k236236Lv3Flurry) {
                    if (m_objectVar1[slot] < 9) {
                        m_objects[slot].scale = 1;
                        m_objectVar1[slot]++;
                        break;
                    }
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                }
                break;
            case kObjFlurryOverlay2:
                if (pattern != k236236Lv3Flurry) {
                    if (m_objectVar1[slot] < 9) {
                        m_objects[slot].scale = 1;
                        m_objectVar1[slot]++;
                        break;
                    }
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                }
                break;
            case kObjUnusedArc1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 1.1;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].ay = 0.04;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objects[slot].attackResult == 1 || m_objects[slot].y >= 0.0) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].scale = 1;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 1;
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y < -480.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjUnusedArc2:
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.8;
                    m_objects[slot].vy = -0.5;
                    m_objects[slot].ay = 0.03;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 1;
                    }
                }
                if (m_objects[slot].x < -100.0 || m_objects[slot].x > 800.0 || m_objects[slot].y > 50.0) {
                    RemoveObject(slot);
                }
                break;
            case kObjUnusedDropLv2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = m_patternVar3;
                    m_objectVar1[slot]++;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vy += 0.045;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjGroundBurst;
                    m_playSound = 18;
                }
                break;
            case kObjGroundBurst:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 7;
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
            case kObjUnusedDropLv3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = m_patternVar3 - (m_patternVar3 > 5) * 5;
                    m_objectVar1[slot]++;
                    m_objects[slot].hitsLeft = 1;
                }
                m_objects[slot].vy += 0.045;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                    }
                }
                if (m_objects[slot].y + m_objects[slot].vy >= 0.0) {
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjUnusedBurstLv3;
                }
                break;
            case kObjUnusedBurstLv3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 7;
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
            case kObjAwakening:
                m_game->FlashNegative(15);
                m_freezeTime = 2;
                FillBackground(176, 1);
                m_objects[slot].vy += 0.05;
                if (m_objects[slot].vy > -0.1) {
                    m_objects[slot].vy = -0.1;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 7) {
                        m_objects[slot].vy = -1.5;
                        m_objects[slot].vx = 0.0;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar1[slot] < 6) {
                            m_objectVar1[slot]++;
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            break;
                        }
                        m_playVoice = 4;
                        effect.type = 1;
                        effect.sound = 0;
                        effect.x = (double)(int)m_objects[slot].x;
                        effect.y = (double)(int)(m_objects[slot].y - 40.0);
                        effect.scale = 2;
                        effect.layer = 1;
                        m_game->CreateEffect((EffectDesc*)&effect);
                        m_familiarGauge = 10000;
                        m_familiarState = 4;
                        m_freezeTime = 60;
                        FillBackground(176, 20);
                        RemoveObject(slot);
                        break;
                    }
                }
                break;
            case kObjFamiliar236A:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 4;
                    m_objects[slot].vx = 1.7;
                }
                m_objects[slot].vx -= 0.035;
                if (m_objects[slot].vx < 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x > 600.0 && m_objects[slot].facing == 1) {
                    m_objects[slot].x = 600.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 40.0 && m_objects[slot].facing == -1) {
                    m_objects[slot].x = 40.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 7 && m_objectVar1[slot] < 3) {
                        m_objects[slot].frame = m_objects[slot].frame - 4;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 6 || m_objects[slot].frame < 3) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == 9 && m_objectVar2[slot] < 1) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar2[slot]++;
                        break;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarSummoned = 0;
                        m_familiarGauge = 1200;
                        m_familiarRate = 1;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliar236B:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 4;
                    m_objects[slot].vx = 1.7;
                }
                m_objects[slot].vx -= 0.025;
                if (m_objects[slot].vx < 0.1) {
                    m_objects[slot].vx = 0.1;
                }
                if (m_objects[slot].x > 600.0 && m_objects[slot].facing == 1) {
                    m_objects[slot].x = 600.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 40.0 && m_objects[slot].facing == -1) {
                    m_objects[slot].x = 40.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 7 && m_objectVar1[slot] < 1) {
                        m_objects[slot].frame = m_objects[slot].frame - 4;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 6 || m_objects[slot].frame < 3) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar2[slot] < 2) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar2[slot]++;
                            break;
                        }
                        m_objects[slot].pattern = kObjFamiliar;
                        m_familiarState = 1;
                        m_familiarGauge = 10000;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 3;
                    }
                }
                break;
            case kObjFamiliar236C:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 16;
                    m_objects[slot].vx = 2.0;
                }
                m_objects[slot].vx -= 0.025;
                if (m_objects[slot].vx < 0.4) {
                    m_objects[slot].vx = 0.4;
                }
                if (m_objects[slot].x > 600.0) {
                    m_objects[slot].x = 600.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 40.0) {
                    m_objects[slot].x = 40.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 7 && m_objectVar1[slot] < 7) {
                        m_objects[slot].frame = m_objects[slot].frame - 4;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 6 || m_objects[slot].frame < 3) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        if (m_objectVar2[slot] < 5) {
                            m_objects[slot].frame = m_objects[slot].frame - 2;
                            m_objectVar2[slot]++;
                            break;
                        }
                        m_objects[slot].pattern = kObjFamiliar;
                        m_familiarState = 1;
                        m_familiarGauge = 10000;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 3;
                    }
                }
                break;
            case kObjFamiliar236D:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 8;
                    m_objects[slot].vx = 1.3;
                }
                m_objects[slot].vx -= 0.025;
                if (m_objects[slot].vx < 0.1) {
                    m_objects[slot].vx = 0.1;
                }
                if (m_objects[slot].x > 600.0) {
                    m_objects[slot].x = 600.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 40.0) {
                    m_objects[slot].x = 40.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 7 && m_objectVar1[slot] < 3) {
                        m_objects[slot].frame = m_objects[slot].frame - 4;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame == 9 && m_objectVar2[slot] < 2) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar2[slot]++;
                        break;
                    }
                    if (m_objects[slot].frame == 4 || m_objects[slot].frame == 6 || m_objects[slot].frame < 3) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliar623:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = 0x1c5;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 60);
                    effect.y = (double)(int)(m_objects[slot].y - 50.0);
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].x > 600.0) {
                    m_objects[slot].x = 600.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 40.0) {
                    m_objects[slot].x = 40.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 5 && m_objectVar1[slot] < 4) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 3;
                        m_objects[slot].timer = 0;
                        m_objects[slot].pattern = kObjFamiliar;
                        m_objectVar1[slot] = 0;
                        m_familiarGauge = 10000;
                        m_familiarState = 1;
                    }
                }
                break;
            case 0x1b1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
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
            case 0x1b2:
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
            case kObjFamiliarUnusedRush:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 5.25;
                }
                if (m_objects[slot].frame > 3) {
                    m_objects[slot].vx -= 0.4;
                    if (m_objects[slot].vx < 0.2) {
                        m_objects[slot].vx = 0.2;
                    }
                }
                if ((*m_opponent)->x - m_objects[slot].x < 120.0 && m_objects[slot].facing == 1 && m_objects[slot].frame == 3) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 4;
                    break;
                }
                if (m_objects[slot].x - (*m_opponent)->x < 120.0 && m_objects[slot].facing == -1 && m_objects[slot].frame == 3) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 4;
                    break;
                }
                if (m_objects[slot].x > 600.0) {
                    m_objects[slot].x = 600.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 40.0) {
                    m_objects[slot].x = 40.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 10 && m_objectVar1[slot] < 2) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarRate = 1;
                        m_familiarState = 3;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliar412D:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].frame == 4 && m_objects[slot].timer == 0) {
                    effect.type = 0x1c6;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 36);
                    effect.y = (double)(int)(m_objects[slot].y - 60.0);
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].x > 600.0) {
                    m_objects[slot].x = 600.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 40.0) {
                    m_objects[slot].x = 40.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 7 && m_objectVar1[slot] < 3) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarRate = 1;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjUnusedShot1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 3;
                }
                if (m_objects[slot].frame == 7 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].vx = 0.7;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 40) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 40;
                    break;
                }
                if (m_objects[slot].x > 740.0 || m_objects[slot].x < -100.0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 40 && m_objects[slot].hitsLeft > 1) {
                        m_objects[slot].frame = 18;
                        m_objects[slot].hitsLeft--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliar214214Lv1:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -1.5;
                }
                if (m_objects[slot].vx < 0.0) {
                    m_objects[slot].vx += 0.03;
                }
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].vy += 0.025;
                }
                if (m_objects[slot].vx > 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].frame == 7 && m_objects[slot].timer == 0) {
                    effect.type = 0x1b8;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 28);
                    effect.y = (double)(int)(m_objects[slot].y - 57.0);
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 10 && m_objectVar1[slot] < 10) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliarOut214214Lv1:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_freezeTime = 120;
                    m_gauge = m_gauge - 1000;
                    FillBackground(176, 3);
                    effect.type = 0x44;
                    effect.sound = 19;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)((int)m_objects[slot].y - 50);
                    effect.scale = 2;
                    effect.keep = 1;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objects[slot].movesInFreeze = 120;
                }
                if (m_objects[slot].frame == 7 && m_objects[slot].timer == 0) {
                    effect.type = 0x1b9;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 28);
                    effect.y = (double)(int)(m_objects[slot].y - 57.0);
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 10 && m_objectVar2[slot] < 1) {
                        m_objects[slot].frame = 5;
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame == 10 && m_objectVar1[slot] < 10) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214214ShotLv1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 5;
                    m_objects[slot].vx = 2.8;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 21) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 21;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                if (m_objects[slot].x > 740.0 || m_objects[slot].x < -100.0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 21) {
                        m_objects[slot].frame = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214214ShotFamiliar:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 4.0;
                    m_objectVar1[slot]++;
                }
                m_objects[slot].vx -= 0.035;
                if (m_objects[slot].vx < 1.0) {
                    m_objects[slot].vx = 1.0;
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 11) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 11;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                if (m_objects[slot].x > 740.0 || m_objects[slot].x < -100.0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 11) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliar214214Lv2:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -1.5;
                }
                if (m_objects[slot].vx < 0.0) {
                    m_objects[slot].vx += 0.03;
                }
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].vy += 0.025;
                }
                if (m_objects[slot].vx > 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].frame == 7 && m_objects[slot].timer == 0) {
                    effect.type = 0x1bc;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 28);
                    effect.y = (double)(int)(m_objects[slot].y - 57.0);
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 10 && m_objectVar1[slot] < 10) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliarOut214214Lv2:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_freezeTime = 120;
                    m_gauge = m_gauge - 2000;
                    FillBackground(176, 3);
                    effect.type = 0x45;
                    effect.sound = 5;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)((int)m_objects[slot].y - 50);
                    effect.scale = 2;
                    effect.keep = 1;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objects[slot].movesInFreeze = 120;
                }
                if (m_objects[slot].frame == 7 && m_objects[slot].timer == 0) {
                    effect.type = 0x1b9;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 28);
                    if (m_objectVar2[slot] == 0) {
                        effect.y = (double)(int)(m_objects[slot].y - 27.0);
                    }
                    if (m_objectVar2[slot] == 1) {
                        effect.y = (double)(int)(m_objects[slot].y - 87.0);
                    }
                    if (m_objectVar2[slot] == 2) {
                        effect.y = (double)(int)(m_objects[slot].y - 27.0);
                    }
                    if (m_objectVar2[slot] == 3) {
                        effect.y = (double)(int)(m_objects[slot].y - 87.0);
                    }
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 10 && m_objectVar2[slot] < 3) {
                        m_objects[slot].frame = 5;
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame == 10 && m_objectVar1[slot] < 10) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214214ShotLv2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 7;
                    m_objects[slot].vx = 3.5;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].x > 740.0 || m_objects[slot].x < -100.0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                break;
            case kObjUnusedShot2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 2;
                    m_objects[slot].vx = 1.3;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 11) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 11;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                if (m_objects[slot].x > 740.0 || m_objects[slot].x < -100.0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 11) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliar214214Lv3:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = -1.5;
                }
                if (m_objects[slot].vx < 0.0) {
                    m_objects[slot].vx += 0.03;
                }
                if (m_objects[slot].vy < 0.0) {
                    m_objects[slot].vy += 0.025;
                }
                if (m_objects[slot].vx > 0.0) {
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].vy > 0.0) {
                    m_objects[slot].vy = 0.0;
                }
                if (m_objects[slot].frame == 7 && m_objects[slot].timer == 0) {
                    effect.type = 0x1c0;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 28);
                    effect.y = (double)(int)(m_objects[slot].y - 57.0);
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 10 && m_objectVar1[slot] < 10) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliarOut214214Lv3:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_freezeTime = 120;
                    m_gauge = m_gauge - 3000;
                    FillBackground(176, 3);
                    effect.type = 0x46;
                    effect.sound = 64;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)((int)m_objects[slot].y - 50);
                    effect.scale = 2;
                    effect.keep = 1;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objects[slot].movesInFreeze = 120;
                }
                if (m_objects[slot].frame == 7 && m_objects[slot].timer == 0) {
                    effect.type = 0x1b9;
                    effect.x = (double)(int)(m_objects[slot].x + m_objects[slot].facing * 28);
                    effect.y = (double)(int)(m_objects[slot].y - 107.0 + (WORD)Random(0, 100));
                    effect.keep = 1;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 10 && m_objectVar2[slot] < 5) {
                        m_objects[slot].frame = 5;
                        m_objectVar2[slot]++;
                    }
                    if (m_objects[slot].frame == 10 && m_objectVar1[slot] < 10) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214214ShotLv3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 10;
                    m_objects[slot].vx = 4.2;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].x > 740.0 || m_objects[slot].x < -100.0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 1;
                    }
                }
                break;
            case kObjUnusedShot3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] == 0) {
                    m_objects[slot].hitsLeft = 3;
                    m_objects[slot].vx = 1.9;
                    m_objectVar1[slot]++;
                }
                if (m_objects[slot].attackResult > 0 && m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 11) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 11;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                if (m_objects[slot].x > 740.0 || m_objects[slot].x < -100.0) {
                    RemoveObject(slot);
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 11) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjAwakenedFinisherScreen:
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
            case kObjFamiliar214D:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[slot].attackResult == 4 || m_objects[slot].attackResult == 5) {
                    m_objects[slot].pattern = kObjFamiliarKnockedOut;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    return;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 4.0;
                }
                if (m_objects[slot].frame > 3) {
                    m_objects[slot].vx -= 0.15;
                    if (m_objects[slot].vx < 0.2) {
                        m_objects[slot].vx = 0.2;
                    }
                }
                if ((*m_opponent)->x - m_objects[slot].x < 120.0 && m_objects[slot].facing == 1 && m_objects[slot].frame == 3) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 4;
                    break;
                }
                if (m_objects[slot].x - (*m_opponent)->x < 120.0 && m_objects[slot].facing == -1 && m_objects[slot].frame == 3) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 4;
                    break;
                }
                if (m_objects[slot].x > 600.0) {
                    m_objects[slot].x = 600.0;
                    m_objects[slot].vx = 0.0;
                }
                if (m_objects[slot].x < 40.0) {
                    m_objects[slot].x = 40.0;
                    m_objects[slot].vx = 0.0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 10 && m_objectVar1[slot] < 2) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                        m_objectVar1[slot]++;
                    }
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_familiarState = 3;
                        m_familiarRate = 4;
                        m_familiarGauge = 1200;
                        m_objectVar1[slot] = 0;
                        m_objectVar2[slot] = 0;
                        m_objects[slot].frame = 0;
                        m_objects[slot].vx = 0.0;
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliar623Hit:
                if ((pattern > kLastFreeAction && pattern < kFirstGuard || m_familiarState == 3) && m_objects[slot].frame < 30) {
                    m_objects[slot].frame = 30;
                    break;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 2;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 1 || m_objects[slot].frame == 18) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjFamiliar412DHit:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].attackResult = 0;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 2) {
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame == 4) {
                        m_objects[slot].attackResult = 0;
                    }
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
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x + facing * 23);
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
                    effect.x = (double)((int)x - facing * 14);
                    effect.y = (double)((int)y - 26);
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
                    effect.x = (double)((int)x + facing * 30);
                    effect.y = (double)((int)y - 40);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f1;
                    effect.x = (double)((int)x - facing * 25);
                    effect.y = (double)((int)y - 80);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x - facing * 35);
                    effect.y = (double)((int)y - 42);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x - facing * 18);
                    effect.y = (double)((int)y - 20);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x + facing * 2);
                    effect.y = (double)((int)y - 65);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = 0x1f2;
                    effect.x = (double)((int)x + (facing << 4));
                    effect.y = (double)((int)y - 80);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    m_playSound = 34;
                    RemoveObject(slot);
                    m_bounceDebrisOut = 0;
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
