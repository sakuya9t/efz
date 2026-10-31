// CMai (0x6163b0-0x62a5df): the character class whose files are in mai\ in the game
// folder (mai.dat sprites, mai.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMai::CMai(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "mai");
    lastSurface = 0x3a0;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_pointX[0] = -0x14;
    m_pointY[0] = -0x3a;
    m_pointX[1] = -0x18;
    m_pointY[1] = 0;
    m_pointX[2] = 4;
    m_pointY[2] = -8;
    m_pointX[3] = 7;
    m_pointY[3] = -0xc;
    m_pointX[4] = 0x1e;
    m_pointY[4] = -0x16;
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
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
}

void CMai::Reset()
{
    int v4;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_pointX[0] = -0x17;
    m_pointY[0] = -0x3a;
    m_pointX[1] = -0x18;
    m_pointY[1] = 0;
    m_pointX[2] = 4;
    m_pointY[2] = -8;
    m_pointX[3] = 7;
    m_pointY[3] = -0xc;
    m_pointX[4] = 0x1e;
    m_pointY[4] = -0x16;
    m_familiarState = 0;
    m_familiarGauge = 0;
    m_familiarSummoned = 0;
    m_familiarRate = 0;
    m_bounceDebrisOut = 0;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
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

void CMai::RemoveObject(short p1)
{
    m_objectVar1[p1] = 0;
    m_objectVar2[p1] = 0;
    m_objectVar3[p1] = 0;
    CPlayer::RemoveObject(p1);
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
        if (m_familiarGauge > 0 && m_hp < 0xd05 && m_command == kCmd236236D && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 4 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kAwakened236236D].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kAwakened236236D;
            return;
        }
        if (m_hp < 0xd05 && m_command == kCmd236236D && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_familiarState == 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[kLv4Awaken].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4Awaken;
            return;
        }
        if (m_command == kCmd214214C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (m_familiarState == 0 || m_familiarState == 1) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv3].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv3;
            if (m_familiarState == 1) {
                pattern = k214214Lv3Familiar;
            }
            return;
        }
        if ((m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (m_familiarState == 0 || m_familiarState == 1) && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv2].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv2;
            if (m_familiarState == 1) {
                pattern = k214214Lv2Familiar;
            }
            return;
        }
        if ((m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (m_familiarState == 0 || m_familiarState == 1) && m_patterns[pattern].cancelLevel <= m_patterns[k214214Lv1].level && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214Lv1;
            if (m_familiarState == 1) {
                pattern = k214214Lv1Familiar;
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
        if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
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
    if (m_pressC == 1 || (m_bufferedPress & 0x40) != 0 || (m_dashBufferedPress & 0x40) != 0) {
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
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k2C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k2C;
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & 4) != 0 || (m_dashBufferedPress & 4) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k4C].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_inputX == facing) {
            StartPattern();
            ClearBufferedPress();
            pattern = k4C;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
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
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (m_familiarGauge > 0 && m_familiarState != 3) {
        x1c = *anims[0x29].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_familiarState == 3) {
        x1c = *anims[0x2a].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_familiarGauge > 0 && m_familiarState != 3) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width * m_familiarGauge / 0x2710, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, m_familiarGauge * x1c.width / 0x2710, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - m_familiarGauge * x1c.width / 0x2710, 0x1f - x1c.y, m_familiarGauge * x1c.width / 0x2710, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_familiarState == 3) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, m_familiarGauge * x1c.width / 0x4b0, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, m_familiarGauge * x1c.width / 0x4b0, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - m_familiarGauge * x1c.width / 0x4b0, 0x1f - x1c.y, m_familiarGauge * x1c.width / 0x4b0, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
}

void CMai::PreUpdate()
{
    EffectDesc v48;
    InitEffectDesc((EffectDesc*)&v48);
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
            v48.type = kEffectEnergySphere;
            v48.sound = 0xb;
            v48.x = (double)(int)x;
            v48.y = (double)(int)(y - 40.0);
            v48.scale = 2;
            v48.layer = 1;
            m_game->CreateEffect((EffectDesc*)&v48);
            m_familiarState = 0;
            m_familiarGauge = 0;
            m_familiarSummoned = 0;
            m_familiarRate = 0;
        }
        if (m_familiarState == 4 && pattern != kAwakened236236D && pattern != kAwakened236236DHit) {
            m_familiarGauge = 0x4b0;
            m_familiarState = 3;
            m_familiarSummoned = 0;
            m_familiarRate = 2;
        }
    }
}

void CMai::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CMai::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = kCmdNone;
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
        if ((v5 & 0xf) == 4 && x6 == 0) {
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

void CMai::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == k236B && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if (v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (v10 < 120.0) {
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_gauge >= 0x3e8) {
                m_command = kCmd214214A;
                return;
            }
            if (v10 < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if (v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
        }
        if (v10 < 160.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_gauge >= 0x3e8) {
                m_command = kCmd214214A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd412C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd214C;
                return;
            }
        }
        if (v10 < 220.0 && v10 > 160.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_gauge == 0xbb8) {
                m_command = kCmd236236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_command = kCmd412A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && y == 0.0) {
                m_pressB = 1;
                m_inputX = facing;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && y == 0.0) {
                m_pressC = 1;
                m_inputX = facing;
                return;
            }
        }
        if (v10 > 220.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
            m_command = kCmd412A;
            return;
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (x8 < 70.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (x8 < 60.0 && v10 < 70.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_command = kCmd623A;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (x8 < 40.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y < 0.0 && y - (*m_opponent)->y > -60.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0 && v10 < 90.0 && (*m_opponent)->y == 0.0) {
            m_command = 0x48;
            return;
        }
        if (m_cpuRoll < 7 && m_rfGauge > 500.0 && v10 < 70.0) {
            m_command = kCmd214C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8 && v10 < 140.0) {
            m_command = (WORD)Random(0, 2) + kCmd214214A;
            return;
        }
        if (m_cpuRoll < 0x12 && m_cpuRoll > 0x16 && m_gauge >= 0x3e8 && v10 < 100.0) {
            m_command = (WORD)Random(0, 2) + kCmd236236A;
            return;
        }
        if (m_cpuRoll < 0x1e) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 0x1e) {
            m_cpuAction = 2;
            return;
        }
        if (v10 < 100.0 && m_cpuRoll < 0x16 && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (v10 < 100.0 && m_cpuRoll < 0x2a) {
            m_command = kCmd623A;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == kAir623A || pattern == kAir623B || pattern == kAir623C || pattern == k412C || pattern == k236236Lv1 || pattern == k236236Lv2 || pattern == k236236Lv3)) {
        m_command = kCmd22C;
        return;
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 1.0f * m_cpuSkill && m_attackResult == 3 && (pattern == k412C || pattern == k6C && v10 < 60.0)) {
        m_command = kCmd22C;
        return;
    }
    if ((pattern == k412A || pattern == k412B) && m_familiarState == 0 && m_familiarSummoned == 1 && (WORD)Random(0, 0x64) < 5.0f * m_cpuSkill) {
        m_pressD = 1;
        m_inputX = facing;
        return;
    }
    if (pattern == kWakeUp && v10 < 120.0 && m_familiarState == 0 && m_familiarSummoned == 1 && (WORD)Random(0, 0x64) < 5.0f * m_cpuSkill) {
        m_pressD = 1;
        m_inputX = facing;
        return;
    }
    if ((*m_opponent)->pattern > kHitCrouchHeavy && (*m_opponent)->pattern < kAirRecoveryForward && m_familiarSummoned == 0 && (WORD)Random(0, 0x64) < 5.0f * m_cpuSkill) {
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
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 0x64) < m_cpuSkill * 25.0f && m_cpuAction != 1 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 160.0 && m_cpuRoll < 0xa) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 125.0 && m_cpuRoll > 0x64 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1b8) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x384 - (m_familiarState == 0 && m_familiarSummoned == 0) * 0xc8) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb - (m_familiarState == 0 && m_familiarSummoned == 1) * 0x12c) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (v10 < 50.0 && m_attackResult == 2 && m_cpuRoll < 0x96 && (WORD)Random(0, 3) == 0) {
                m_cpuAction = 6;
                m_inputY = 0;
                m_pressA = 0;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x1f4) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x82 && m_familiarSummoned == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x82 && m_cpuRoll < 0x190 && v10 < 140.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x1cc && v10 < 140.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x23a - (m_familiarSummoned == 1) * 0x96 && m_cpuRoll < 0x2a8) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 0x1cc && m_cpuRoll < 0x230 && (*m_opponent)->y == 0.0 && v10 < 100.0 && m_familiarSummoned == 0) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x384 - (m_familiarState == 0 && m_familiarSummoned == 0) * 0xc8) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
                return;
            }
            if (m_cpuRoll > 0x2bc - (m_familiarState == 0 && m_familiarSummoned == 0) * 0xc8) {
                m_cpuAction = 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && v10 < 90.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x1f4 && v10 > 150.0) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1f4 && m_cpuRoll < 0x258 && m_familiarSummoned == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll < 0x64 && v10 < 110.0) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x12c) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && (*m_opponent)->y == 0.0) {
                m_command = kCmd214A;
                if (v10 > 120.0) {
                    m_command = kCmd214B;
                }
                return;
            }
            if (m_cpuRoll > 0x23a && m_cpuRoll < 0x26c) {
                m_command = (WORD)Random(0, 1) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 0x384 - (m_familiarState == 0 && m_familiarSummoned == 0) * 0xc8) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
            }
        }
        if (pattern == k5C) {
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x1f4 && m_familiarSummoned == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c && (*m_opponent)->y == 0.0) {
                m_pressC = 1;
                m_inputX = facing;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x226 && (*m_opponent)->y == 0.0) {
                m_command = kCmd214A;
                if (v10 > 120.0) {
                    m_command = kCmd214B;
                }
                return;
            }
            if (m_cpuRoll > 0x28a && m_cpuRoll < 0x2bc) {
                m_command = (WORD)Random(0, 1) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 0x28a && m_cpuRoll < 0x2bc) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
            }
        }
        if (pattern == k2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && v10 < 50.0) {
                m_pressA = 1;
                m_inputY = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 6;
                    m_inputY = 0;
                    m_pressA = 0;
                }
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 50.0 && m_cpuRoll < 0x190) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x384 - (m_familiarState == 0 && m_familiarSummoned == 0) * 0x64) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
                return;
            }
            if (m_cpuRoll > 0x320) {
                m_cpuAction = 1;
                return;
            }
        }
        if (pattern == k2B) {
            if (m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll < 0x190 && v10 > 140.0 && (*m_opponent)->y == 0.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll < 0x190 && m_cpuRoll < 0x1f4 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x226 - (m_familiarSummoned == 1) * 0x96 && m_cpuRoll < 0x2bc) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 0x384 - (m_familiarState == 0 && m_familiarSummoned == 0) * 0xc8 && m_attackResult == 3) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x384 - (m_familiarState == 0 && m_familiarSummoned == 0) * 0xc8) {
                m_cpuAction = 1;
                if (m_familiarState == 0 && m_familiarSummoned == 1) {
                    m_pressD = 1;
                    m_inputX = ((WORD)Random(0, 2) == 0) * facing;
                }
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x1f4 && m_familiarSummoned == 0) {
                m_pressD = 1;
                m_inputX = 0;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x226 - (m_familiarSummoned == 1) * 0x96 && m_cpuRoll < 0x2bc) {
                m_command = (WORD)Random(0, 2) + kCmd412A;
                if (m_attackResult == 3 && m_rfGauge > 500.0) {
                    m_command = kCmd412C;
                }
                return;
            }
            if (m_cpuRoll > 0x2bc) {
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
            if (m_cpuRoll > 0x2bb - (m_familiarState == 0 && m_familiarSummoned == 1) * 0x12c) {
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
    }
    if ((WORD)Random(0, 0x64) < 25.0f * m_cpuSkill) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (y == 0.0) {
            if ((*m_opponent)->y == 0.0 && (*m_opponent)->pattern != kLyingDown) {
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 3) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 60.0 && (*m_opponent)->pattern < kFirstHitReaction && (*m_opponent)->pattern < kRecoilGuardStand && m_cpuRoll < 5) {
                    m_cpuAction = 6;
                    return;
                }
                if (v10 < 50.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward) * 0x32 + 0x19 && (*m_opponent)->pattern < kFirstCharacterAction) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 80.0 && m_cpuRoll < 0xa && m_gauge >= 0x3e8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 2) + kCmd236236A;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 130.0 && v10 > 80.0 && m_cpuRoll < 0x1e && m_cpuRoll > 0xf) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 90.0 && m_cpuRoll < 0x1e && m_cpuRoll > 0x14) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 200.0 && v10 > 160.0 && m_cpuRoll < 0x2d && m_cpuRoll > 0x1e) {
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
                    if (v10 < 80.0 && x8 < 180.0 && x8 > 90.0 && m_cpuRoll < 0x1e) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 > 130.0 && x8 < 180.0 && x8 > 90.0 && m_cpuRoll > 0x1e && m_cpuRoll < 0x46) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 150.0 && v10 > 60.0 && m_cpuRoll > 0x46 && m_cpuRoll < 0x6e) {
                        m_pressA = 1;
                        m_inputX = facing;
                        m_inputY = 0;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 80.0 && x8 < 180.0 && x8 > 90.0 && m_cpuRoll < 0x1e) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 > 130.0 && x8 < 180.0 && x8 > 90.0 && m_cpuRoll > 0x1e && m_cpuRoll < 0x46) {
                        m_inputY = -1;
                        m_inputX = -facing;
                        return;
                    }
                    if (v10 < 150.0 && v10 > 60.0 && x8 > 130.0 && m_cpuRoll > 0x46 && m_cpuRoll < 0x6e) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (v10 < 100.0 && x8 > 160.0 && x8 < 240.0 && m_cpuRoll > 0 && m_cpuRoll < 0x8c) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 140.0 && v10 > 90.0 && x8 > 90.0 && m_cpuRoll > 0xa0 && m_cpuRoll < 0xdc) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 130.0 && x8 < 80.0 && m_cpuRoll > 0xdc && m_cpuRoll < 0x12c && m_rfGauge > 500.0) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 100.0 && x8 < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->y == 0.0) * 0x64 + 0x64) {
                        m_pressA = 1;
                        return;
                    }
                }
                if (v10 < 140.0 && x8 < 80.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x104) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 140.0 && v10 > 80.0 && x8 > 40.0 && x8 < 80.0 && m_cpuRoll > 0x104 && m_cpuRoll < 0x109) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 120.0 && x8 < 90.0 && (*m_opponent)->y > y && m_cpuRoll < 0x6e) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 140.0 && x8 < 90.0 && m_cpuRoll < 0xd2) {
                    m_pressB = 1;
                    return;
                }
                if (v10 < 150.0 && v10 > 100.0 && x8 < 90.0 && (*m_opponent)->y > y && m_cpuRoll < 0x9c4) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0) {
        if ((WORD)Random(0, 0x64) < ((m_familiarState == 1 && m_familiarSummoned == 1 && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir)) * 2 + (((*m_opponent)->pattern == kLyingDown) << 2) + 1) * m_cpuSkill && v10 > 80.0) {
            m_command = facing == 1;
            return;
        }
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && v10 > 60.0 && v10 < 140.0 && (WORD)Random(0, 0x64) < 2.0f * m_cpuSkill && x > 120.0 && x < 520.0 && m_familiarSummoned == 0) {
        m_command = -((facing == 1) - 1);
        return;
    }
    if ((WORD)Random(0, 0x3e8) < (m_familiarSummoned == 1) + 2) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 0x64) < 2) {
        if ((WORD)Random(0, 0x64) < 8.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (v10 > 160.0 && y == 0.0 && (WORD)Random(0, 0x64) < 3) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (v10 < 100.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2 && (*m_opponent)->pattern < kRecoilGuardStand) {
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
    if ((WORD)Random(0, 0x64) < 0x3c && v10 < 150.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x3c;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x28) {
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

void CMai::UpdateObjects()
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
            case kObjFamiliar:
                m_familiarState = 1;
                if (m_objects[v4].frame > 2) {
                    if (m_objects[v4].vx >= 0.1) {
                        m_objects[v4].vx -= 0.02;
                    }
                    if (m_objects[v4].vx <= -0.1) {
                        m_objects[v4].vx += 0.02;
                    }
                    if (m_objects[v4].vy >= 0.1) {
                        m_objects[v4].vy -= 0.02;
                    }
                    if (m_objects[v4].vy <= -0.1) {
                        m_objects[v4].vy += 0.02;
                    }
                    if (m_objects[v4].vx < 0.1 && m_objects[v4].vx > -0.1) {
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].vy < 0.1 && m_objects[v4].vy > -0.1) {
                        m_objects[v4].vy = 0.0;
                    }
                    if (m_familiarRate == 1) {
                        m_familiarRate = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        if (m_objects[v4].y > -30.0) {
                            l50.type = 0x1f;
                            l50.x = (double)(int)m_objects[v4].x;
                            l50.y = (double)(int)m_objects[v4].y;
                            l50.scale = 0;
                            l50.layer = 0;
                            l50.side = m_objects[v4].facing == -1;
                            m_game->CreateEffect((EffectDesc*)&l50);
                        }
                    }
                    if (m_familiarGauge <= 0) {
                        m_objects[v4].pattern = kObjFamiliarExpire;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0;
                        m_familiarGauge = 0;
                        m_familiarState = 2;
                        break;
                    }
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    }
                    if (m_objects[v4].x <= (*m_opponent)->x) {
                        m_objects[v4].facing = 1;
                    }
                    if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                        m_objects[v4].pattern = kObjFamiliarKnockedOut;
                        m_familiarState = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == kRecallFamiliar) {
                        m_objects[v4].pattern = kObjFamiliarRecall;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0;
                        m_familiarGauge = 0;
                        break;
                    }
                    if (pattern == k214214Lv3Familiar && frame == 3 && timer == 0) {
                        m_objects[v4].pattern = kObjFamiliarOut214214Lv3;
                        m_familiarState = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k214214Lv2Familiar && frame == 3 && timer == 0) {
                        m_objects[v4].pattern = kObjFamiliarOut214214Lv2;
                        m_familiarState = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k214214Lv1Familiar && frame == 3 && timer == 0) {
                        m_objects[v4].pattern = kObjFamiliarOut214214Lv1;
                        m_familiarState = 2;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if ((pattern < kFirstGuard || pattern > kGuardAir) && pattern != kRecoilGuardStand && pattern != kRecoilGuardCrouch && pattern != kRecoilGuardAir && pattern != kSummonFamiliar && pattern != kRecallFamiliar) {
                        if (m_command == kCmd214D) {
                            m_objects[v4].pattern = kObjFamiliar214D;
                            m_objects[v4].frame = 0;
                            m_objects[v4].timer = 0;
                            m_familiarState = 2;
                            break;
                        }
                        if (m_command == kCmd412D) {
                            m_objects[v4].pattern = kObjFamiliar412D;
                            m_objects[v4].frame = 0;
                            m_objects[v4].timer = 0;
                            m_familiarState = 2;
                            break;
                        }
                        if (m_command == kCmd236D) {
                            m_objects[v4].pattern = kObjFamiliar236D;
                            m_objects[v4].frame = 0;
                            m_objects[v4].timer = 0;
                            m_familiarState = 2;
                            break;
                        }
                        if (m_command == kCmd22D) {
                            m_objects[v4].pattern = kObjFamiliar22D;
                            m_objects[v4].frame = 0;
                            m_objects[v4].timer = 0;
                            m_familiarState = 2;
                            break;
                        }
                    }
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 3;
                    }
                }
                break;
            case kObjFamiliarKnockedOut:
                m_familiarState = 2;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = -2.0;
                    m_objects[v4].vy = -2.0;
                    m_objects[v4].ax = 0.05;
                    m_objectVar1[v4] = 1;
                }
                m_objects[v4].vx = m_objects[v4].vx + m_objects[v4].ax;
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ax;
                if (m_objects[v4].vx > 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].attackResult == 1) {
                    RemoveObject(v4);
                }
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2 && m_objectVar2[v4] < 5) {
                        m_objectVar2[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_familiarSummoned = 0;
                        m_familiarGauge = 0x4b0;
                        m_familiarState = 3;
                        m_objectVar2[v4] = 0;
                        m_objectVar1[v4] = 0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliarExpire:
                m_familiarState = 2;
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarGauge = 0x4b0;
                        m_familiarState = 3;
                        m_familiarRate = 0;
                        m_familiarSummoned = 0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliarRecall:
                m_familiarState = 2;
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarGauge = 0x4b0;
                        m_familiarState = 3;
                        m_familiarRate = 1;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliarUnusedFly:
                m_familiarGauge--;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                m_objects[v4].vx = m_objects[v4].vx + m_objects[v4].ax;
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].x > 590.0 && m_objects[v4].facing == 1) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 50.0 && m_objects[v4].facing == -1) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    if (m_familiarGauge > 1) {
                        m_familiarGauge -= 0x1388;
                    } else {
                        m_familiarGauge = 0;
                    }
                }
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].ax = 0.0;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.5;
                    m_objects[v4].ax = -0.015;
                    m_objectVar1[v4] = 6;
                    m_objects[v4].vy = 0.9;
                    m_objects[v4].ay = -0.035;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xb && m_objectVar1[v4] > 0) {
                        m_objects[v4].frame = 7;
                        m_objectVar1[v4]--;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjFamiliar;
                        m_familiarState = 0;
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case kObjFamiliarUnusedShoot:
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0 && m_objectVar2[v4] == 0) {
                    m_familiarGauge = 0;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].frame == 5 && m_objects[v4].timer == 0 && m_objectVar2[v4] != 1) {
                    l50.type = 0x198;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1d);
                    l50.y = (double)(int)(m_objects[v4].y - 49.0);
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                    m_objectVar2[v4] = 1;
                    m_objectVar1[v4] = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 8 && m_objectVar1[v4] < 5) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjFamiliarExpire;
                        m_familiarState = 0;
                        m_objects[v4].frame = 0;
                        m_objectVar2[v4] = 0;
                        m_objectVar1[v4] = 0;
                    }
                }
                break;
            case kObjUnusedHomingShot:
                if (m_objects[v4].timer == 0 && m_objects[v4].frame == 0 && m_objectVar1[v4] <= 0) {
                    if (m_objectVar2[v4] == 0) {
                        m_objects[v4].hitsLeft = 1;
                    }
                    if (m_objectVar2[v4] < 3 && m_objects[v4].hitsLeft > 0) {
                        m_objectVar3[v4] = (int)AngleTo((*m_opponent)->x - m_objects[v4].x, (*m_opponent)->y - 50.0 - m_objects[v4].y);
                        m_objects[v4].SetVelocity((double)m_objectVar3[v4], -0.00875);
                        m_objects[v4].ax = m_objects[v4].vx;
                        m_objects[v4].ay = m_objects[v4].vy;
                        m_objects[v4].SetVelocity((double)m_objectVar3[v4], 1.4);
                        if (m_objects[v4].facing == -1) {
                            m_objects[v4].ax = -m_objects[v4].ax;
                            m_objects[v4].vx = -m_objects[v4].vx;
                        }
                        m_objectVar3[v4] = 0xa0;
                        m_objectVar2[v4]++;
                        m_objectVar1[v4] = 0xf0;
                    }
                }
                if (m_objectVar3[v4] > 0) {
                    m_objects[v4].vx = m_objects[v4].vx + m_objects[v4].ax;
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    m_objectVar3[v4]--;
                }
                m_objectVar1[v4]--;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if ((m_objectVar2[v4] > 2 || m_objects[v4].hitsLeft == 0) && m_objectVar1[v4] <= 0) {
                            RemoveObject(v4);
                        }
                    }
                }
                break;
            case kObjFamiliarUnusedSuper:
                m_familiarState = 1;
                if (pattern == kUnusedSuperLv3) {
                    m_game->FlashNegative(0xf);
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].movesInFreeze = 1;
                    if (pattern == kUnusedSuperLv1) {
                        m_gauge = m_gauge - 0x3e8;
                    }
                    if (pattern == kUnusedSuperLv2) {
                        m_gauge = m_gauge - 0x7d0;
                    }
                    if (pattern == kUnusedSuperLv3) {
                        m_gauge = m_gauge - 0xbb8;
                    }
                    m_patternVar3 = 0;
                    m_objectVar1[v4] = 0;
                    m_freezeTime = 0x78;
                    FillBackground(0xb0, 3);
                    l50.type = 9;
                    l50.sound = 5;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 52.0);
                    l50.scale = 2;
                    l50.keep = 1;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_playSound = 0x25;
                }
                if (m_objects[v4].frame > 4 && m_objects[v4].frame < 0xc && m_freezeTime == 0) {
                    if (m_objectVar3[v4] == 0) {
                        m_playVoice = 6;
                        m_objectVar3[v4]++;
                    }
                    if (m_objectVar2[v4] >= 0xf) {
                        m_objectVar2[v4] = 0;
                        if (pattern == kUnusedSuperLv1 && m_patternVar3 < 3) {
                            l50.type = 0x19a;
                            l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1d);
                            l50.y = (double)(int)(m_objects[v4].y - 49.0);
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.facing = m_objects[v4].facing;
                            l50.facing = l50.facing;
                            SpawnObject(&l50);
                            m_patternVar3++;
                        }
                        if (pattern == kUnusedSuperLv2 && m_patternVar3 < 5) {
                            l50.type = 0x1a7;
                            l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1d);
                            l50.y = (double)(int)(m_objects[v4].y - 49.0);
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.facing = m_objects[v4].facing;
                            l50.facing = l50.facing;
                            SpawnObject(&l50);
                            m_patternVar3++;
                        }
                        if (pattern == kUnusedSuperLv3 && m_patternVar3 < 0xa) {
                            l50.type = 0x1a9;
                            l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1d);
                            l50.y = (double)(int)(m_objects[v4].y - 49.0);
                            l50.scale = 2;
                            l50.layer = 1;
                            l50.facing = m_objects[v4].facing;
                            l50.facing = l50.facing;
                            SpawnObject(&l50);
                            m_patternVar3++;
                        }
                    }
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_objectVar2[v4]++;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xc && m_objectVar1[v4] < 5) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjFamiliarExpire;
                        m_familiarState = 0;
                        m_objects[v4].movesInFreeze = 0;
                        m_objects[v4].frame = 0;
                    }
                }
                break;
            case kObjUnusedDropLv1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = m_patternVar3;
                    m_objectVar1[v4]++;
                    m_objects[v4].hitsLeft = 1;
                }
                m_objects[v4].vy += 0.045;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjUnusedBurstLv1;
                    m_playSound = 0x12;
                }
                break;
            case kObjUnusedBurstLv1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 7;
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
            case kObjFamiliar214:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 6;
                    m_objectVar2[v4] = 0xb4;
                }
                if (m_objects[v4].frame > 5) {
                    m_objectVar2[v4] -= 4;
                }
                if (m_objectVar2[v4] < 0xf) {
                    m_objectVar2[v4] = 0xf;
                }
                if (m_objects[v4].frame > 4) {
                    m_objects[v4].SetVelocity(-60.0, m_objectVar2[v4] * 0.01);
                }
                if (m_objects[v4].frame > 8) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 8) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 8 && m_objectVar1[v4] < 8) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarSummoned = 0;
                        m_familiarGauge = 0x4b0;
                        m_familiarRate = 1;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        RemoveObject(v4);
                        break;
                    }
                }
                break;
            case kObjFamiliarUnusedWalk:
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 4;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].vx = 0.6;
                    }
                    if (m_objects[v4].frame == 4 && m_objectVar1[v4] < 0x14) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].vy = -0.1;
                        m_objects[v4].vx = 0.0;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar1[v4] < 0xe) {
                            m_objectVar1[v4]++;
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            break;
                        }
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].pattern = kObjFamiliar22D;
                        break;
                    }
                }
                break;
            case kObjFamiliar22D:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 6;
                    m_objectVar2[v4] = 0xb4;
                }
                if (m_objects[v4].frame > 1) {
                    m_objectVar2[v4] -= 2;
                }
                if (m_objectVar2[v4] < 0x1e) {
                    m_objectVar2[v4] = 0x1e;
                }
                if (m_objects[v4].frame > 0) {
                    m_objects[v4].SetVelocity(-30.0, m_objectVar2[v4] * 0.01);
                }
                if (m_objects[v4].frame > 4) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2 || m_objects[v4].frame == 4) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 4 && m_objectVar1[v4] < 0xc) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarSummoned = 0;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        RemoveObject(v4);
                        break;
                    }
                }
                break;
            case kObj6A:
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
            case kObj6B:
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
            case kObj6C:
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
            case kObjAir623C:
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
            case kObjFlurryOverlay1:
                if (pattern != k236236Lv3Flurry) {
                    if (m_objectVar1[v4] < 9) {
                        m_objects[v4].scale = 1;
                        m_objectVar1[v4]++;
                        break;
                    }
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                }
                break;
            case kObjFlurryOverlay2:
                if (pattern != k236236Lv3Flurry) {
                    if (m_objectVar1[v4] < 9) {
                        m_objects[v4].scale = 1;
                        m_objectVar1[v4]++;
                        break;
                    }
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                }
                break;
            case kObjUnusedArc1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.1;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].ay = 0.04;
                    m_objects[v4].hitsLeft = 1;
                }
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].attackResult == 1 || m_objects[v4].y >= 0.0) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].scale = 1;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 1;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y < -480.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjUnusedArc2:
                m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.8;
                    m_objects[v4].vy = -0.5;
                    m_objects[v4].ay = 0.03;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 1;
                    }
                }
                if (m_objects[v4].x < -100.0 || m_objects[v4].x > 800.0 || m_objects[v4].y > 50.0) {
                    RemoveObject(v4);
                }
                break;
            case kObjUnusedDropLv2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = m_patternVar3;
                    m_objectVar1[v4]++;
                    m_objects[v4].hitsLeft = 1;
                }
                m_objects[v4].vy += 0.045;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjGroundBurst;
                    m_playSound = 0x12;
                }
                break;
            case kObjGroundBurst:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 7;
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
            case kObjUnusedDropLv3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = m_patternVar3 - (m_patternVar3 > 5) * 5;
                    m_objectVar1[v4]++;
                    m_objects[v4].hitsLeft = 1;
                }
                m_objects[v4].vy += 0.045;
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                    }
                }
                if (m_objects[v4].y + m_objects[v4].vy >= 0.0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjUnusedBurstLv3;
                }
                break;
            case kObjUnusedBurstLv3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 7;
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
            case kObjAwakening:
                m_game->FlashNegative(0xf);
                m_freezeTime = 2;
                FillBackground(0xb0, 1);
                m_objects[v4].vy += 0.05;
                if (m_objects[v4].vy > -0.1) {
                    m_objects[v4].vy = -0.1;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].vy = -1.5;
                        m_objects[v4].vx = 0.0;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar1[v4] < 6) {
                            m_objectVar1[v4]++;
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            break;
                        }
                        m_playVoice = 4;
                        l50.type = 1;
                        l50.sound = 0;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)(m_objects[v4].y - 40.0);
                        l50.scale = 2;
                        l50.layer = 1;
                        m_game->CreateEffect((EffectDesc*)&l50);
                        m_familiarGauge = 0x2710;
                        m_familiarState = 4;
                        m_freezeTime = 0x3c;
                        FillBackground(0xb0, 0x14);
                        RemoveObject(v4);
                        break;
                    }
                }
                break;
            case kObjFamiliar236A:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 4;
                    m_objects[v4].vx = 1.7;
                }
                m_objects[v4].vx -= 0.035;
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x > 600.0 && m_objects[v4].facing == 1) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0 && m_objects[v4].facing == -1) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && m_objectVar1[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame < 3) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 9 && m_objectVar2[v4] < 1) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar2[v4]++;
                        break;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarSummoned = 0;
                        m_familiarGauge = 0x4b0;
                        m_familiarRate = 1;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliar236B:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 4;
                    m_objects[v4].vx = 1.7;
                }
                m_objects[v4].vx -= 0.025;
                if (m_objects[v4].vx < 0.1) {
                    m_objects[v4].vx = 0.1;
                }
                if (m_objects[v4].x > 600.0 && m_objects[v4].facing == 1) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0 && m_objects[v4].facing == -1) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && m_objectVar1[v4] < 1) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame < 3) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar2[v4] < 2) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            m_objectVar2[v4]++;
                            break;
                        }
                        m_objects[v4].pattern = kObjFamiliar;
                        m_familiarState = 1;
                        m_familiarGauge = 0x2710;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 3;
                    }
                }
                break;
            case kObjFamiliar236C:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 0x10;
                    m_objects[v4].vx = 2.0;
                }
                m_objects[v4].vx -= 0.025;
                if (m_objects[v4].vx < 0.4) {
                    m_objects[v4].vx = 0.4;
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && m_objectVar1[v4] < 7) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame < 3) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        if (m_objectVar2[v4] < 5) {
                            m_objects[v4].frame = m_objects[v4].frame - 2;
                            m_objectVar2[v4]++;
                            break;
                        }
                        m_objects[v4].pattern = kObjFamiliar;
                        m_familiarState = 1;
                        m_familiarGauge = 0x2710;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 3;
                    }
                }
                break;
            case kObjFamiliar236D:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 8;
                    m_objects[v4].vx = 1.3;
                }
                m_objects[v4].vx -= 0.025;
                if (m_objects[v4].vx < 0.1) {
                    m_objects[v4].vx = 0.1;
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && m_objectVar1[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 9 && m_objectVar2[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar2[v4]++;
                        break;
                    }
                    if (m_objects[v4].frame == 4 || m_objects[v4].frame == 6 || m_objects[v4].frame < 3) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliar623:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = 0x1c5;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x3c);
                    l50.y = (double)(int)(m_objects[v4].y - 50.0);
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 5 && m_objectVar1[v4] < 4) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 3;
                        m_objects[v4].timer = 0;
                        m_objects[v4].pattern = kObjFamiliar;
                        m_objectVar1[v4] = 0;
                        m_familiarGauge = 0x2710;
                        m_familiarState = 1;
                    }
                }
                break;
            case 0x1b1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
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
            case 0x1b2:
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
            case kObjFamiliarUnusedRush:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 5.25;
                }
                if (m_objects[v4].frame > 3) {
                    m_objects[v4].vx -= 0.4;
                    if (m_objects[v4].vx < 0.2) {
                        m_objects[v4].vx = 0.2;
                    }
                }
                if ((*m_opponent)->x - m_objects[v4].x < 120.0 && m_objects[v4].facing == 1 && m_objects[v4].frame == 3) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    break;
                }
                if (m_objects[v4].x - (*m_opponent)->x < 120.0 && m_objects[v4].facing == -1 && m_objects[v4].frame == 3) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    break;
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && m_objectVar1[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarRate = 1;
                        m_familiarState = 3;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliar412D:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    l50.type = 0x1c6;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x24);
                    l50.y = (double)(int)(m_objects[v4].y - 60.0);
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 7 && m_objectVar1[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarRate = 1;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjUnusedShot1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 3;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 0.7;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].attackResult > 0 && m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x28) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x28;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0x28 && m_objects[v4].hitsLeft > 1) {
                        m_objects[v4].frame = 0x12;
                        m_objects[v4].hitsLeft--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliar214214Lv1:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.5;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx += 0.03;
                }
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].vy += 0.025;
                }
                if (m_objects[v4].vx > 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1b8;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 57.0);
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && m_objectVar1[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliarOut214214Lv1:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_freezeTime = 0x78;
                    m_gauge = m_gauge - 0x3e8;
                    FillBackground(0xb0, 3);
                    l50.type = 0x44;
                    l50.sound = 0x13;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y - 0x32);
                    l50.scale = 2;
                    l50.keep = 1;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].movesInFreeze = 0x78;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 57.0);
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && m_objectVar2[v4] < 1) {
                        m_objects[v4].frame = 5;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 0xa && m_objectVar1[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214214ShotLv1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 5;
                    m_objects[v4].vx = 2.8;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].attackResult > 0 && m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x15) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x15;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0x15) {
                        m_objects[v4].frame = 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214214ShotFamiliar:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 4.0;
                    m_objectVar1[v4]++;
                }
                m_objects[v4].vx -= 0.035;
                if (m_objects[v4].vx < 1.0) {
                    m_objects[v4].vx = 1.0;
                }
                if (m_objects[v4].attackResult > 0 && m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0xb) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliar214214Lv2:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.5;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx += 0.03;
                }
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].vy += 0.025;
                }
                if (m_objects[v4].vx > 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1bc;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 57.0);
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && m_objectVar1[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliarOut214214Lv2:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_freezeTime = 0x78;
                    m_gauge = m_gauge - 0x7d0;
                    FillBackground(0xb0, 3);
                    l50.type = 0x45;
                    l50.sound = 5;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y - 0x32);
                    l50.scale = 2;
                    l50.keep = 1;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].movesInFreeze = 0x78;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    if (m_objectVar2[v4] == 0) {
                        l50.y = (double)(int)(m_objects[v4].y - 27.0);
                    }
                    if (m_objectVar2[v4] == 1) {
                        l50.y = (double)(int)(m_objects[v4].y - 87.0);
                    }
                    if (m_objectVar2[v4] == 2) {
                        l50.y = (double)(int)(m_objects[v4].y - 27.0);
                    }
                    if (m_objectVar2[v4] == 3) {
                        l50.y = (double)(int)(m_objects[v4].y - 87.0);
                    }
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && m_objectVar2[v4] < 3) {
                        m_objects[v4].frame = 5;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 0xa && m_objectVar1[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214214ShotLv2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 7;
                    m_objects[v4].vx = 3.5;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                break;
            case kObjUnusedShot2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 2;
                    m_objects[v4].vx = 1.3;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].attackResult > 0 && m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0xb) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliar214214Lv3:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.5;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx += 0.03;
                }
                if (m_objects[v4].vy < 0.0) {
                    m_objects[v4].vy += 0.025;
                }
                if (m_objects[v4].vx > 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].vy > 0.0) {
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1c0;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 57.0);
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && m_objectVar1[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliarOut214214Lv3:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_freezeTime = 0x78;
                    m_gauge = m_gauge - 0xbb8;
                    FillBackground(0xb0, 3);
                    l50.type = 0x46;
                    l50.sound = 0x40;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)((int)m_objects[v4].y - 0x32);
                    l50.scale = 2;
                    l50.keep = 1;
                    l50.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].movesInFreeze = 0x78;
                }
                if (m_objects[v4].frame == 7 && m_objects[v4].timer == 0) {
                    l50.type = 0x1b9;
                    l50.x = (double)(int)(m_objects[v4].x + m_objects[v4].facing * 0x1c);
                    l50.y = (double)(int)(m_objects[v4].y - 107.0 + (WORD)Random(0, 0x64));
                    l50.keep = 1;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && m_objectVar2[v4] < 5) {
                        m_objects[v4].frame = 5;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 0xa && m_objectVar1[v4] < 0xa) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214214ShotLv3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 0xa;
                    m_objects[v4].vx = 4.2;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 1;
                    }
                }
                break;
            case kObjUnusedShot3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].hitsLeft = 3;
                    m_objects[v4].vx = 1.9;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].attackResult > 0 && m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0xb) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                if (m_objects[v4].x > 740.0 || m_objects[v4].x < -100.0) {
                    RemoveObject(v4);
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjAwakenedFinisherScreen:
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
            case kObjFamiliar214D:
                m_familiarState = 2;
                if (pattern > kLastFreeAction && pattern < kFirstGuard || m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjFamiliarKnockedOut;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    return;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                }
                if (m_objects[v4].frame > 3) {
                    m_objects[v4].vx -= 0.15;
                    if (m_objects[v4].vx < 0.2) {
                        m_objects[v4].vx = 0.2;
                    }
                }
                if ((*m_opponent)->x - m_objects[v4].x < 120.0 && m_objects[v4].facing == 1 && m_objects[v4].frame == 3) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    break;
                }
                if (m_objects[v4].x - (*m_opponent)->x < 120.0 && m_objects[v4].facing == -1 && m_objects[v4].frame == 3) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 4;
                    break;
                }
                if (m_objects[v4].x > 600.0) {
                    m_objects[v4].x = 600.0;
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].x < 40.0) {
                    m_objects[v4].x = 40.0;
                    m_objects[v4].vx = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0xa && m_objectVar1[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                        m_objectVar1[v4]++;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_familiarState = 3;
                        m_familiarRate = 4;
                        m_familiarGauge = 0x4b0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].frame = 0;
                        m_objects[v4].vx = 0.0;
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliar623Hit:
                if ((pattern > kLastFreeAction && pattern < kFirstGuard || m_familiarState == 3) && m_objects[v4].frame < 0x1e) {
                    m_objects[v4].frame = 0x1e;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 2;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 0x12) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjFamiliar412DHit:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].attackResult = 0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 2) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].attackResult = 0;
                    }
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
                    m_bounceDebrisOut = 0;
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
