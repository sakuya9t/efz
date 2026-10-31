// CMinagi (0x5a9fa0-0x5c857f): the character class whose files are in minagi\ in the game
// folder (minagi.dat sprites, minagi.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CMinagi::CMinagi(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    strcpy(m_name, "minagi");
    lastSurface = 0x2b4;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_michiruState = 0;
    m_shotState = 0;
    m_shotX = 0;
    m_pointX[0] = -8;
    m_pointY[0] = -0x42;
    m_pointX[1] = -0x13;
    m_pointY[1] = 0;
    m_pointX[2] = 3;
    m_pointY[2] = -7;
    m_pointX[3] = 9;
    m_pointY[3] = -2;
    m_pointX[4] = 0x23;
    m_pointY[4] = -0x25;
    m_resultPictures = 8;
    m_rivals[0] = 1;
    m_rivals[1] = 0;
    m_rivals[2] = 0xb;
    m_rivals[3] = 0x18;
    m_rivals[4] = 2;
    m_rivals[5] = 0x13;
    m_rivals[6] = 0x17;
    m_rivals[0xa] = 7;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
}

void CMinagi::Reset()
{
    int l4c;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_michiruState = 0;
    m_shotState = 0;
    m_shotX = 0;
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
    l4c = 0;
    for (; l4c < 0x40; l4c++) {
        m_objectVar1[l4c] = 0;
        m_objectVar2[l4c] = 0;
        m_objectVar3[l4c] = 0;
    }
    CPlayer::Reset();
    EffectDesc l48;
    InitEffectDesc((EffectDesc*)&l48);
    l48.type = kObjMichiru;
    l48.x = (double)((int)x - facing * 0x28);
    l48.y = (double)(int)y;
    l48.scale = 0;
    l48.screen = 0;
    l48.layer = 0;
    l48.shadow = 1;
    l48.keep = 1;
    l48.facing = facing;
    SpawnObject(&l48);
}

void CMinagi::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CMinagi::RemoveObject(short p1)
{
    m_objectVar1[p1] = 0;
    m_objectVar2[p1] = 0;
    m_objectVar3[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CMinagi::Move()
{
    MoveOnGround();
}

void CMinagi::StartCommand()
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
        if (m_hp < 0xd05 && m_michiruState != 4 && m_command == kCmd222D && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_command == kCmd21436C && y == 0.0 && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436C;
            return;
        }
        if (y == 0.0 && (m_command == kCmd21436B || m_command == kCmd21436C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436B;
            return;
        }
        if (y == 0.0 && (m_command == kCmd21436A || m_command == kCmd21436B || m_command == kCmd21436C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436A;
            return;
        }
        if (m_michiruState != 4 && m_command == kCmd214214C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214C;
            if (y < 0.0) {
                pattern = kAir214214C;
            }
            return;
        }
        if (m_michiruState != 4 && (m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214B;
            if (y < 0.0) {
                pattern = kAir214214B;
            }
            return;
        }
        if (m_michiruState != 4 && (m_command == kCmd214214A || m_command == kCmd214214B || m_command == kCmd214214C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214A;
            if (y < 0.0) {
                pattern = kAir214214A;
            }
            return;
        }
        if (m_michiruState != 4 && m_command == kCmd236236C && m_gauge >= 0xbb8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236C;
            if (y < 0.0) {
                pattern = kAir236236C;
            }
            return;
        }
        if (m_michiruState != 4 && (m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x7d0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236B;
            if (y < 0.0) {
                pattern = kAir236236B;
            }
            return;
        }
        if (m_michiruState != 4 && (m_command == kCmd236236A || m_command == kCmd236236B || m_command == kCmd236236C) && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236236A;
            if (y < 0.0) {
                pattern = kAir236236A;
            }
            return;
        }
        if (m_command == kCmd4136C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236C].level && m_shotState == 0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236C;
            return;
        }
        if ((m_command == kCmd4136B || m_command == kCmd4136C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236B].level && m_shotState == 0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236B;
            return;
        }
        if (m_command == kCmd4136A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236A].level && m_shotState == 0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236A;
            return;
        }
        if (m_michiruState != 4 && m_command == kCmd214C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            if (y < 0.0) {
                pattern = kAir214C;
            }
            return;
        }
        if (m_michiruState != 4 && (m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            if (y < 0.0) {
                pattern = kAir214B;
            }
            return;
        }
        if (m_michiruState != 4 && m_command == kCmd214A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            if (y < 0.0) {
                pattern = kAir214A;
            }
            return;
        }
        if (m_michiruState != 4 && y == 0.0 && m_command == kCmd623C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623C;
            return;
        }
        if (m_michiruState != 4 && y == 0.0 && (m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623B;
            return;
        }
        if (m_michiruState != 4 && y == 0.0 && m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
            return;
        }
        if (m_michiruState != 4 && m_command == kCmd421C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k421C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k421C;
            if (y < 0.0) {
                pattern = kAir421C;
            }
            return;
        }
        if (m_michiruState != 4 && (m_command == kCmd421B || m_command == kCmd421C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k421B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k421B;
            if (y < 0.0) {
                pattern = kAir421B;
            }
            return;
        }
        if (m_michiruState != 4 && m_command == kCmd421A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k421A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k421A;
            if (y < 0.0) {
                pattern = kAir421A;
            }
            return;
        }
        if (m_michiruState != 4 && m_command == kCmd236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            if (y < 0.0) {
                pattern = kAir236C;
            }
            return;
        }
        if (m_michiruState != 4 && (m_command == kCmd236B || m_command == kCmd236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236B;
            if (y < 0.0) {
                pattern = kAir236B;
            }
            return;
        }
        if (m_michiruState != 4 && m_command == kCmd236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236A;
            if (y < 0.0) {
                pattern = kAir236A;
            }
            return;
        }
    }
    if (m_sealLevel < 1 && (m_command == kCmdDashLeft || m_command == kCmdDashRight)) {
        if (y < 0.0 && m_airDashes < 1) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].cancelLevel <= m_patterns[kAirDashForward].level && pattern != kRecoilGuardAir && y < -30.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && pattern != k236A) {
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
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && pattern != kRecoilGuardAir && m_patterns[pattern].cancelLevel <= m_patterns[kAirDashBack].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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
            if (m_patterns[pattern].cancelLevel <= m_patterns[k5BClose].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && x - (*m_opponent)->x > -50.0 && x - (*m_opponent)->x < 50.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & 4) == 0 || (m_dashBufferedPress & 4) == 0) {
            if ((*m_opponent)->y == 0.0 && m_inputX != 0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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
    if (m_sealLevel < 2 && (m_pressD == 1 || (m_bufferedPress & 0x80) != 0 || (m_dashBufferedPress & 0x80) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k5D].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
        if ((m_michiruState == 0 || m_michiruState == 2 || m_michiruState == 3) && m_inputX == 0) {
            StartPattern();
            ClearBufferedPress();
            pattern = k5D;
            return;
        }
        if (m_michiruState == 0 && m_inputX == 1) {
            StartPattern();
            ClearBufferedPress();
            pattern = kDRight;
            return;
        }
        if (m_michiruState == 0 && m_inputX == -1) {
            StartPattern();
            ClearBufferedPress();
            pattern = kDLeft;
        }
    }
}

void CMinagi::DrawGauge()
{
}

void CMinagi::PreUpdate()
{
}

void CMinagi::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CMinagi::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = kCmdNone;
    x6 = 0;
    v4 = m_inputPos + 0x5a;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x80) != 0 && x6 == 6) {
            m_command = kCmd222D;
            return;
        }
        if ((v5 & 0xf) == 4 && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xf) == 0 && x6 == 4) {
            x6 = 5;
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
        if ((v5 & 0xf) == 0 && x6 == 0 && m_gauge == 0xbb8) {
            x6 = 1;
        }
    }
    x6 = 0;
    v4 = m_inputPos + 0x64;
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
        if ((v5 & 0xf) == 4 && x6 == 0) {
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
    v4 = m_inputPos + 0x6e;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 4 && y == 0.0) {
            m_command = ((v5 & 0xe0) > 0) + kCmd4136A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
            if ((v5 & 0xf0) != 0 && y == 0.0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd4136A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 4;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 2) {
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
            m_command = ((v5 & 0xe0) > 0) + kCmd421A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 2) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd421A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
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

void CMinagi::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == k41236C && m_hitsLeft > 1) {
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
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 4.0f && m_rfGauge > 500.0) {
                m_command = kCmd214C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = kCmd222D;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && v10 < 80.0 && m_gauge >= 0x7d0) {
                m_command = (WORD)Random(0, 2) + kCmd236236B;
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
                m_command = kCmd222D;
                return;
            }
        }
        if (v10 > 150.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = (WORD)Random(0, 2) + kCmd214A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f) {
                m_command = (WORD)Random(0, 2) + kCmd236B;
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
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
        if (x8 < 50.0 && v10 < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
            m_command = (WORD)Random(0, 2) + kCmd214B;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 3 && m_rfGauge > 500.0) {
            m_command = kCmd214C;
            return;
        }
        if (m_cpuRoll < 5 && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 3) + kCmd236236A;
            return;
        }
        if (m_cpuRoll < 0x12 && m_cpuRoll > 0x14 && m_gauge == 0xbb8) {
            m_command = kCmd222D;
            return;
        }
        if (m_cpuRoll > 0x41) {
            m_cpuAction = 2;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 2 && m_rfGauge > 500.0) {
            m_command = kCmd214C;
            return;
        }
        if (m_cpuRoll > 0x3a) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == kDRight || pattern == kDashC && (WORD)Random(0, 0xa) == 0 || pattern == k5D && (WORD)Random(0, 0x64) < 2 || pattern == kDash2C && (WORD)Random(0, 7) == 0)) {
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
            if ((*m_opponent)->y < 0.0 && v10 < 90.0 && m_cpuRoll < 0x258 && m_cpuRoll > 0x12c) {
                m_cpuAction = 6;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 70.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x258) {
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
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
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
                m_command = kCmd214B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x226 && m_cpuRoll < 0x258 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd236236A;
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
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && v10 < 80.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x258) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0 && m_cpuRoll < 0x96) {
                m_command = kCmd214B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x96 && m_cpuRoll < 0xc8 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd236236A;
                return;
            }
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x190) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 0xe;
                }
                return;
            }
        }
        if (pattern == k5C) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = (WORD)Random(0, 3) + kCmd214A;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x12c) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x12c && m_rfGauge > 350.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x258) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && m_rfGauge > 500.0) {
                m_command = kCmd214B;
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
            if ((*m_opponent)->y < 0.0 && v10 < 90.0 && m_cpuRoll < 0x258 && m_cpuRoll > 0x12c) {
                m_cpuAction = 6;
                return;
            }
            if (v10 < 70.0 && m_cpuRoll > 0 && m_cpuRoll < 0xc8) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (v10 < 80.0 && m_cpuRoll > 0xc8 && m_cpuRoll < 0x258) {
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
            if (m_cpuRoll > 0x320) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x226) {
                m_command = kCmd214B;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x226 && m_cpuRoll < 0x258 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd236236A;
                return;
            }
            if (m_cpuRoll < 0x64) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x64 && m_cpuRoll < 0x15e && v10 < 110.0) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x15e && m_cpuRoll < 0x226 && v10 < 90.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x276 && m_attackResult == 2) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x3b6) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x1f4) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x258) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x28a && m_cpuRoll < 0x258 && m_rfGauge > 350.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x28a && m_cpuRoll < 0x320) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x320 && m_cpuRoll < 0x352 && m_rfGauge > 500.0) {
                m_command = kCmd214B;
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
            if (m_cpuRoll < 0xc8 && m_attackResult == 3) {
                m_command = (WORD)Random(0, 2) + kCmd214B;
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
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x190 && m_rfGauge > 350.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && m_rfGauge > 500.0) {
                m_command = kCmd214B;
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
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == k5D && m_cpuRoll > 0x258 && y == 0.0) {
            m_cpuAction = 1;
            if (v10 < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
        if (pattern == kDash2A && m_cpuRoll > 0x1f4) {
            m_cpuAction = 1;
            if (v10 < 50.0) {
                m_cpuAction = 0x14;
            }
            return;
        }
        if (pattern == kDash2B) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x190 && m_rfGauge > 350.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x28a && m_rfGauge > 500.0) {
                m_command = kCmd214B;
                return;
            }
            if (m_cpuRoll > 0x2bc) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 6;
                }
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 8;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xc;
                }
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 0xe;
                }
                if (v10 < 50.0 && (WORD)Random(0, 2) == 0) {
                    m_cpuAction = 0x14;
                }
                return;
            }
        }
        if (pattern == kDash2C && m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258) {
            m_command = kCmd214A;
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
                if (v10 < 50.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0xf) {
                        m_pressA = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (v10 < 65.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x14) {
                        m_pressA = 1;
                        m_inputY = 0;
                        return;
                    }
                }
                if (v10 > 60.0 && v10 < 90.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x23 && m_cpuRoll > 0x1e) {
                        m_pressB = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x46 < v10 && v10 < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 2 + 0x54 && m_cpuRoll > 0x50) {
                        m_cpuAction = 0xc;
                        return;
                    }
                }
                if (0x46 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x46 < v10 && v10 < 120.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x80 && m_cpuRoll > 0x78) {
                        m_cpuAction = 8;
                        return;
                    }
                }
                if (v10 < 150.0 && v10 > 120.0 && m_cpuRoll < 0x7e && m_cpuRoll > 0x78) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 120.0 && v10 > 70.0 && m_cpuRoll < 0x91 && m_cpuRoll > 0x82) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (0x50 - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x50 < v10 && v10 < 130.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0x9b && m_cpuRoll > 0x91) {
                        m_cpuAction = 0xe;
                        return;
                    }
                }
                if (0x5a - ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0x5a < v10 && v10 < 140.0) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir) * 0xf + 0xb4 && m_cpuRoll > 0xa5) {
                        m_cpuAction = 0xa;
                        return;
                    }
                }
                if (v10 > 110.0 && v10 < 160.0 && m_cpuRoll < 0xcd && m_cpuRoll > 0xc8) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0xeb && m_cpuRoll > 0xdc && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd214C;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0xf0 && m_cpuRoll > 0xeb && m_gauge >= 0x7d0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 3) + kCmd236236B;
                    return;
                }
                if (v10 < 100.0 && m_cpuRoll < 0xf2 && m_cpuRoll > 0xf0 && m_gauge == 0xbb8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd222D;
                    return;
                }
                if (v10 > 100.0 && v10 < 130.0 && m_cpuRoll < 0x136 && m_cpuRoll > 0x12c) {
                    m_command = kCmd236A;
                    return;
                }
                if (v10 > 130.0 && v10 < 180.0 && m_cpuRoll < 0x13b && m_cpuRoll > 0x136) {
                    m_command = kCmd236B;
                    return;
                }
                if (v10 > 90.0 && v10 < 140.0 && m_cpuRoll < 0x14a && m_cpuRoll > 0x140) {
                    m_command = kCmd214A;
                    return;
                }
                if (v10 > 90.0 && v10 < 140.0 && m_cpuRoll < 0x154 && m_cpuRoll > 0x14a && m_rfGauge > 500.0) {
                    m_command = kCmd214B;
                    return;
                }
                if (m_cpuRoll < 0x2ee && m_cpuRoll > 0x2bc && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kGuardAir && v10 > 100.0) {
                    m_cpuAction = 5;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if ((*m_opponent)->vy < 0.0 && v10 < 80.0 && x8 < 120.0 && m_cpuRoll < 0xa) {
                    m_inputY = -1;
                    m_inputX = -facing;
                    return;
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 80.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623C;
                        return;
                    }
                    if (v10 < 80.0 && x8 < 140.0 && x8 > 100.0 && m_cpuRoll < 0x2d && m_cpuRoll > 0xa) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 170.0 && x8 > 150.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x2d) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 > 120.0 && v10 < 140.0 && x8 < 150.0 && x8 > 120.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x50) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 70.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xc8 && (*m_opponent)->y < -50.0 && x8 < 90.0 && m_gauge >= 0x7d0) {
                        m_command = (WORD)Random(0, 2) + kCmd236236B;
                        return;
                    }
                    if (v10 < 100.0 && m_cpuRoll < 0x12e && m_cpuRoll > 0x12c && (*m_opponent)->y < -50.0 && x8 < 100.0 && m_gauge == 0xbb8) {
                        m_command = kCmd222D;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x64) {
                    m_pressA = 1;
                    return;
                }
                if (v10 < 80.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x64 && m_cpuRoll < 0xb4) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 110.0 && x8 > 0.0 && x8 < 70.0 && m_cpuRoll > 0xb4 && m_cpuRoll < 0xf0) {
                    m_pressC = 1;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll > 0xf0 && m_cpuRoll < 0xf2 && x8 > 80.0) {
                    m_command = (WORD)Random(0, 3) + kCmd214214A;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 20.0 && v10 < 90.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x14 && m_cpuRoll < 0x28) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 110.0 && x8 > 0.0 && x8 < 50.0 && m_cpuRoll > 0x28 && m_cpuRoll < 0x32) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 4.0f * m_cpuSkill && v10 > 120.0) {
        m_command = facing == 1;
        return;
    }
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && v10 > 800.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < 2.0f * m_cpuSkill && x > 150.0 && x < 490.0) {
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
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x3c;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x3c;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x32) {
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

void CMinagi::UpdateObjects()
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
            case kObjMichiru:
                m_objectVar1[v4] = 0;
                m_objects[v4].hitsLeft = 0;
                if (m_objects[v4].x > (*m_opponent)->x) {
                    m_objects[v4].facing = -1;
                } else {
                    m_objects[v4].facing = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_michiruState = 0;
                if (pattern == k5D && frame == 0) {
                    m_michiruState = 1;
                    m_objects[v4].pattern = kObjMichiruReady;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kDRight || pattern == kDLeft) {
                    m_michiruState = 2;
                    m_objects[v4].pattern = kObjMichiruWalk;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236A && frame == 2 || pattern == kAir236A && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236A;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236B && frame == 2 || pattern == kAir236B && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236B;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236C && frame == 2 || pattern == kAir236C && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236C;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k421A && frame == 2 || pattern == kAir421A && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru421A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k421B && frame == 2 || pattern == kAir421B && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru421B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k421C && frame == 2 || pattern == kAir421C && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru421C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214A && frame == 2 || pattern == kAir214A && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214B && frame == 2 || pattern == kAir214B && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214C && frame == 2 || pattern == kAir214C && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k623A && frame == 2) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru623A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k623B && frame == 2) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru623B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k623C && frame == 2) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru623C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236236A && frame == 2 || pattern == kAir236236A && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236236B && frame == 2 || pattern == kAir236236B && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236236C && frame == 2 || pattern == kAir236236C && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214214A && frame == 2 || pattern == kAir214214A && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214214A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214214B && frame == 2 || pattern == kAir214214B && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214214B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214214C && frame == 2 || pattern == kAir214214C && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214214C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if ((pattern == k21436A || pattern == k21436B || pattern == k21436C) && frame == 2) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru21436;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kLv4 && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiruLv4;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kUnused236236A && frame == 2 || pattern == kUnusedAir236236A && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kUnused236236B && frame == 2 || pattern == kUnusedAir236236B && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kUnused236236C && frame == 2 || pattern == kUnusedAir236236C && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kEatingJam) {
                    m_michiruState = 4;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].pattern = kObjMichiruHeld;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (x - m_objects[v4].x > 300.0 || x - m_objects[v4].x < -300.0) {
                    m_michiruState = 2;
                    m_objects[v4].pattern = kObjMichiruWalkBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    if (x > m_objects[v4].x) {
                        m_objects[v4].facing = 1;
                    }
                    if (x <= m_objects[v4].x) {
                        m_objects[v4].facing = -1;
                    }
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
            case kObjMichiruReady:
                m_objectVar1[v4] = 0;
                m_objects[v4].vy = 0.0;
                m_objects[v4].vx = 0.0;
                m_objects[v4].hitsLeft = 0;
                if (m_objects[v4].x > (*m_opponent)->x) {
                    m_objects[v4].facing = -1;
                } else {
                    m_objects[v4].facing = 1;
                }
                m_objects[v4].vx = 0.0;
                m_objects[v4].vy = 0.0;
                m_michiruState = 1;
                if (m_objects[v4].frame >= 8 && m_objects[v4].frame < 0x11) {
                    m_michiruState = 3;
                    if (pattern == k5D && frame == 0) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x11;
                        break;
                    }
                    if (pattern == k236A && frame == 2 || pattern == kAir236A && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruReady236A;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k236B && frame == 2 || pattern == kAir236B && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruReady236B;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k236C && frame == 2 || pattern == kAir236C && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruReady236C;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k421A && frame == 2 || pattern == kAir421A && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru421A;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k421B && frame == 2 || pattern == kAir421B && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru421B;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k421C && frame == 2 || pattern == kAir421C && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru421C;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k214A && frame == 2 || pattern == kAir214A && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruReady214A;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k214B && frame == 2 || pattern == kAir214B && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruReady214B;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k214C && frame == 2 || pattern == kAir214C && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruReady214C;
                        m_objects[v4].frame = 8;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k623A && frame == 2) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru623A;
                        m_objects[v4].frame = 9;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k623B && frame == 2) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru623B;
                        m_objects[v4].frame = 9;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k623C && frame == 2) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru623C;
                        m_objects[v4].frame = 9;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k236236A && frame == 2 || pattern == kAir236236A && frame == 1) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru236236A;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k236236B && frame == 2 || pattern == kAir236236B && frame == 1) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru236236B;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k236236C && frame == 2 || pattern == kAir236236C && frame == 1) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru236236C;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k214214A && frame == 2 || pattern == kAir214214A && frame == 1) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruReady214214A;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k214214B && frame == 2 || pattern == kAir214214B && frame == 1) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruReady214214B;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == k214214C && frame == 2 || pattern == kAir214214C && frame == 1) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruReady214214C;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if ((pattern == k21436A || pattern == k21436B || pattern == k21436C) && frame == 2) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiru21436;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == kLv4 && frame == 3) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruLv4;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == kUnused236236A && frame == 2 || pattern == kUnusedAir236236A && frame == 1) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruUnused236236A;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == kUnused236236B && frame == 2 || pattern == kUnusedAir236236B && frame == 1) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruUnused236236B;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == kUnused236236C && frame == 2 || pattern == kUnusedAir236236C && frame == 1) {
                        m_michiruState = 4;
                        m_objects[v4].pattern = kObjMichiruUnused236236C;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        break;
                    }
                    if (pattern == kEatingJam) {
                        m_michiruState = 4;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].ay = 0.0;
                        m_objects[v4].pattern = kObjMichiruHeld;
                        m_objects[v4].frame = 0xb;
                        m_objects[v4].timer = 0;
                        break;
                    }
                }
                if (pattern == kDRight || pattern == kDLeft) {
                    m_michiruState = 1;
                    m_objects[v4].pattern = kObjMichiruWalk;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0x11) {
                        m_objects[v4].frame = 8;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].pattern = kObjMichiru;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruWalk:
                m_michiruState = 2;
                m_objects[v4].hitsLeft = 0;
                if (m_objects[v4].frame < 0xb) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame > 0xa) {
                    if (m_objects[v4].vx > 0.0) {
                        m_objects[v4].vx -= 0.035;
                    }
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                if (pattern == k236A && frame == 2 || pattern == kAir236A && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236A;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k236B && frame == 2 || pattern == kAir236B && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236B;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k236C && frame == 2 || pattern == kAir236C && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236C;
                    m_objects[v4].frame = 7;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k421A && frame == 2 || pattern == kAir421A && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru421A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k421B && frame == 2 || pattern == kAir421B && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru421B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k421C && frame == 2 || pattern == kAir421C && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru421C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k214A && frame == 2 || pattern == kAir214A && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k214B && frame == 2 || pattern == kAir214B && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k214C && frame == 2 || pattern == kAir214C && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k623A && frame == 2) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru623A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k623B && frame == 2) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru623B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k623C && frame == 2) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru623C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k236236A && frame == 2 || pattern == kAir236236A && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k236236B && frame == 2 || pattern == kAir236236B && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k236236C && frame == 2 || pattern == kAir236236C && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k214214A && frame == 2 || pattern == kAir214214A && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214214A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k214214B && frame == 2 || pattern == kAir214214B && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214214B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == k214214C && frame == 2 || pattern == kAir214214C && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214214C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if ((pattern == k21436A || pattern == k21436B || pattern == k21436C) && frame == 2) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru21436;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == kLv4 && frame == 3) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiruLv4;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == kUnused236236A && frame == 2 || pattern == kUnusedAir236236A && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == kUnused236236B && frame == 2 || pattern == kUnusedAir236236B && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == kUnused236236C && frame == 2 || pattern == kUnusedAir236236C && frame == 1) {
                    if (m_objects[v4].x > (*m_opponent)->x) {
                        m_objects[v4].facing = -1;
                    } else {
                        m_objects[v4].facing = 1;
                    }
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (pattern == kEatingJam) {
                    m_michiruState = 4;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].pattern = kObjMichiruHeld;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4] = 1;
                    if (pattern == kDRight) {
                        m_objects[v4].facing = 1;
                    }
                    if (pattern == kDLeft) {
                        m_objects[v4].facing = -1;
                    }
                    break;
                }
                if (pattern == k5D) {
                    m_michiruState = 1;
                    m_objects[v4].pattern = kObjMichiruReady;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xb && m_objectVar1[v4] < 0) {
                        m_objects[v4].frame = 0;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].pattern = kObjMichiru;
                        m_objectVar1[v4] = 0;
                    }
                }
                break;
            case kObjMichiruKnockedBack:
                m_michiruState = 4;
                m_objects[v4].movesInFreeze = 0;
                m_objectVar1[v4] = 0;
                m_objectVar2[v4] = 0;
                m_objectVar3[v4] = 0;
                if (pattern == kEatingJam) {
                    m_michiruState = 4;
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].ay = 0.0;
                    m_objects[v4].pattern = kObjMichiruHeld;
                    m_objects[v4].frame = 0xb;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -2.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 7) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 7;
                        ShakeScreen(3, 0);
                        l50.type = 3;
                        l50.x = (double)(int)m_objects[v4].x;
                        l50.y = (double)(int)m_objects[v4].y;
                        l50.scale = 2;
                        l50.layer = 0;
                        m_game->CreateEffect((EffectDesc*)&l50);
                        m_playSound = 7;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 7) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru236A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.9;
                    m_objects[v4].vy = -1.1;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].attackResult > 0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjMichiru236Rebound;
                    break;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru236B:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = -1.4;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].attackResult > 0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjMichiru236Rebound;
                    break;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru236C:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -1.4;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].hitsLeft = 5;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].attackResult > 0) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjMichiru236Rebound;
                    break;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru421A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].hitsLeft = 0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.2;
                    m_objects[v4].vy = -2.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].frame == 9) {
                    if ((*m_opponent)->y < 0.0) {
                        m_objects[v4].hitsLeft = 1;
                    } else {
                        m_objects[v4].hitsLeft = 0;
                    }
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                    }
                }
                if (m_objects[v4].frame == 0x12 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].ay = 0.035;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0x17 && m_objects[v4].frame > 0x12) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru421B:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].hitsLeft = 0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.5;
                    m_objects[v4].vy = -2.5;
                    m_objects[v4].ay = 0.035;
                }
                if (m_objects[v4].frame == 9) {
                    if ((*m_opponent)->y < 0.0) {
                        m_objects[v4].hitsLeft = 1;
                    } else {
                        m_objects[v4].hitsLeft = 0;
                    }
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                    }
                }
                if (m_objects[v4].frame == 0x12 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -0.8;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].ay = 0.035;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0x17 && m_objects[v4].frame > 0x12) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru421C:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].hitsLeft = 0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.3;
                    m_objects[v4].vy = -3.5;
                    m_objects[v4].ay = 0.045;
                }
                if (m_objects[v4].frame == 9) {
                    if ((*m_opponent)->y < 0.0) {
                        m_objects[v4].hitsLeft = 1;
                    } else {
                        m_objects[v4].hitsLeft = 0;
                    }
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].vx > 0.0 && m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].x - (*m_opponent)->x > -50.0 && m_objects[v4].frame < 0x11) {
                    m_objects[v4].vx -= 0.02;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        m_objects[v4].attackResult = 0;
                    }
                }
                if (m_objects[v4].frame == 0x12 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = -1.0;
                    m_objects[v4].vy = -1.0;
                    m_objects[v4].ay = 0.035;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0x17 && m_objects[v4].frame > 0x12) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                        m_objects[v4].attackResult = 0;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 1;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru214A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -1.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].hitsLeft = 4;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.3) {
                        m_objects[v4].vy = 0.3;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru214B:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -2.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].hitsLeft = 6;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.3) {
                        m_objects[v4].vy = 0.3;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru214C:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -1.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].hitsLeft = 0xc;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.15) {
                        m_objects[v4].vy = 0.15;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case 0x19d:
                m_michiruState = 4;
                if (m_objects[v4].frame < 0x10) {
                    (*m_opponent)->FocusCameraY(0x32, 0x1e);
                }
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k236236A && pattern != kAir236236A) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x14;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objectVar2[v4] = 0;
                        m_objectVar1[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && m_objectVar2[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.2;
                    }
                    if (m_objects[v4].frame == 0x10 && m_objectVar1[v4] < 2) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x14) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case 0x19e:
                m_michiruState = 4;
                if (m_objects[v4].frame < 0x14) {
                    (*m_opponent)->FocusCameraY(0x32, 0x1e);
                }
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k236236B && pattern != kAir236236B) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objectVar2[v4] = 0;
                        m_objectVar1[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && m_objectVar2[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.6;
                    }
                    if (m_objects[v4].frame == 0x10 && m_objectVar1[v4] < 3) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case 0x19f:
                m_michiruState = 4;
                if (m_objects[v4].frame < 0x17) {
                    (*m_opponent)->FocusCameraY(0x32, 0x1e);
                    m_game->FlashNegative(0xf);
                }
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k236236C && pattern != kAir236236C) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x1a;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objectVar2[v4] = 0;
                        m_objectVar1[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && m_objectVar2[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.6;
                    }
                    if (m_objects[v4].frame == 0x10 && m_objectVar1[v4] < 4) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x1a) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru214214A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    (*m_opponent)->m_hitstop = 0x2d;
                    m_objects[v4].hitstop = 0x2d;
                    m_objectVar1[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruReady214214A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (m_objects[v4].frame > 1 && m_objects[v4].frame < 6) {
                    if (m_objects[v4].x - (*m_opponent)->x > -50.0 && m_objects[v4].x - (*m_opponent)->x < 50.0) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 6;
                    }
                    m_objects[v4].vx = 2.2;
                }
                if (m_objects[v4].frame > 5) {
                    m_objects[v4].vx -= 0.1;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    (*m_opponent)->m_hitstop = 0x5a;
                    m_objects[v4].hitstop = 0x5a;
                    m_objectVar1[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 6 && m_objectVar2[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                    }
                }
                break;
            case kObjMichiru214214B:
                m_michiruState = 4;
                if (m_objects[v4].frame < 0x10) {
                    (*m_opponent)->FocusCameraY(0x32, 0x1e);
                }
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    (*m_opponent)->m_hitstop = 0x4b;
                    m_objects[v4].hitstop = 0x4b;
                    m_objectVar1[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruReady214214B:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (m_objects[v4].frame > 1 && m_objects[v4].frame < 6) {
                    if (m_objects[v4].x - (*m_opponent)->x > -50.0 && m_objects[v4].x - (*m_opponent)->x < 50.0) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 6;
                    }
                    m_objects[v4].vx = 2.2;
                }
                if (m_objects[v4].frame > 5) {
                    m_objects[v4].vx -= 0.1;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    (*m_opponent)->m_hitstop = 0x96;
                    m_objects[v4].hitstop = 0x96;
                    m_objectVar1[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 6 && m_objectVar2[v4] < 4) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                    }
                }
                break;
            case kObjMichiru214214C:
                m_michiruState = 4;
                if (m_objects[v4].frame < 0x10) {
                    (*m_opponent)->FocusCameraY(0x32, 0x1e);
                }
                m_game->FlashNegative(0xf);
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame == 4 && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 5 && m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    (*m_opponent)->m_hitstop = 0x64;
                    m_objects[v4].hitstop = 0x64;
                    m_objectVar1[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruReady214214C:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar1[v4] = 0;
                    break;
                }
                if (m_objects[v4].frame > 1 && m_objects[v4].frame < 6) {
                    if (m_objects[v4].x - (*m_opponent)->x > -50.0 && m_objects[v4].x - (*m_opponent)->x < 50.0) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 6;
                    }
                    m_objects[v4].vx = 2.2;
                }
                if (m_objects[v4].frame > 5) {
                    m_objects[v4].vx -= 0.1;
                }
                if (m_objects[v4].vx < 0.0) {
                    m_objects[v4].vx = 0.0;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].frame == 0xa && m_objects[v4].timer == 0) {
                    l50.type = 0x1f;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.side = m_objects[v4].facing == 1;
                    m_game->CreateEffect((EffectDesc*)&l50);
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    (*m_opponent)->m_hitstop = 0xc8;
                    m_objects[v4].hitstop = 0xc8;
                    m_objectVar1[v4] = 1;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 6 && m_objectVar2[v4] < 6) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                        m_objectVar1[v4] = 0;
                        m_objectVar2[v4] = 0;
                    }
                }
                break;
            case kObjMichiruReady236A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.9;
                    m_objects[v4].vy = -1.1;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruReady236B:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = -1.4;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruReady236C:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -1.4;
                    m_objects[v4].ay = 0.025;
                    m_objects[v4].hitsLeft = 5;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xc) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xc;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru236Rebound:
                m_michiruState = 4;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = -m_objects[v4].vx * 0.5;
                    m_objects[v4].vy = -2.5;
                    m_objects[v4].ay = 0.025;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                        m_objectVar1[v4] = 0;
                    }
                }
                break;
            case kObjMichiruReady214A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                }
                if (m_objects[v4].y < 0.0) {
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx = m_objects[v4].facing * 0.5;
                    } else {
                        m_objects[v4].vx = m_objects[v4].facing * -0.5;
                    }
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -1.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].hitsLeft = 4;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.3) {
                        m_objects[v4].vy = 0.3;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruReady214B:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                }
                if (m_objects[v4].y < 0.0) {
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx = m_objects[v4].facing * 0.5;
                    } else {
                        m_objects[v4].vx = m_objects[v4].facing * -0.5;
                    }
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -2.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].hitsLeft = 6;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.3) {
                        m_objects[v4].vy = 0.3;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruReady214C:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].frame == 9 && m_objects[v4].timer == 0) {
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                }
                if (m_objects[v4].y < 0.0) {
                    if (m_objects[v4].x < x) {
                        m_objects[v4].vx = m_objects[v4].facing * 0.5;
                    } else {
                        m_objects[v4].vx = m_objects[v4].facing * -0.5;
                    }
                }
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0 && m_objectVar1[v4] == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = -1.8;
                    m_objects[v4].ay = 0.055;
                    m_objects[v4].hitsLeft = 0xc;
                    m_objectVar1[v4]++;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame < 0xf) {
                    m_objects[v4].vy = m_objects[v4].vy + m_objects[v4].ay;
                    if (m_objects[v4].vy > 0.15) {
                        m_objects[v4].vy = 0.15;
                    }
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0xf;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjShot41236A:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar2[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar2[v4]++;
                    m_objects[v4].vx = 1.7;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.035;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                if (m_objects[v4].attackResult > 0 && m_objectVar1[v4] == 0 && m_objects[v4].scale == 0) {
                    m_objects[v4].scale = 1;
                    m_objectVar1[v4] = 0x1e;
                }
                if (m_objects[v4].scale == 1) {
                    m_objectVar1[v4]--;
                    if (m_objectVar1[v4] < 0) {
                        RemoveObject(v4);
                        m_shotState = 0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (m_objectVar3[v4] > 0) {
                            RemoveObject(v4);
                            m_shotState = 0;
                        } else {
                            m_objectVar3[v4]++;
                        }
                    }
                }
                break;
            case kObjShot41236B:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar2[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar2[v4]++;
                    m_objects[v4].vx = 2.1;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.035;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                if (m_objects[v4].attackResult > 0 && m_objectVar1[v4] == 0 && m_objects[v4].scale == 0) {
                    m_objects[v4].scale = 1;
                    m_objectVar1[v4] = 0x1e;
                }
                if (m_objects[v4].scale == 1) {
                    m_objectVar1[v4]--;
                    if (m_objectVar1[v4] < 0) {
                        RemoveObject(v4);
                        m_shotState = 0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (m_objectVar3[v4] > 1) {
                            RemoveObject(v4);
                            m_shotState = 0;
                        } else {
                            m_objectVar3[v4]++;
                        }
                    }
                }
                break;
            case kObjShot41236C:
                m_shotX = (int)m_objects[v4].x;
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar2[v4] == 0) {
                    m_objects[v4].hitsLeft = 2;
                    m_objectVar2[v4]++;
                    m_objects[v4].vx = 2.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.035;
                    if (m_objects[v4].vx < 0.6) {
                        m_objects[v4].vx = 0.6;
                    }
                }
                if (m_objects[v4].hitsLeft == 0 && m_objectVar1[v4] == 0 && m_objects[v4].scale == 0) {
                    m_shotState = 2;
                    m_objects[v4].scale = 1;
                    m_objectVar1[v4] = 0x1e;
                }
                if (m_objects[v4].scale == 1) {
                    m_objectVar1[v4]--;
                    if (m_objectVar1[v4] < 0) {
                        RemoveObject(v4);
                        m_shotState = 0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 6 || m_objects[v4].frame == 0xc) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        if (m_objectVar3[v4] > 2) {
                            RemoveObject(v4);
                            m_shotState = 0;
                        } else {
                            m_objectVar3[v4]++;
                        }
                    }
                }
                break;
            case kObjShot41236CFollower:
                m_objects[v4].x = m_shotX;
                if ((m_shotState == 2 || m_shotState == 0) && m_objects[v4].frame < 0x18) {
                    m_objects[v4].frame = 0x18;
                    m_objects[v4].timer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0x18) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjMichiruWalkBack:
                m_michiruState = 2;
                m_objects[v4].hitsLeft = 0;
                if (m_objects[v4].frame < 0xa) {
                    m_objects[v4].vx = 1.5;
                }
                m_objects[v4].vy = 0.0;
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                if (m_objects[v4].frame > 9) {
                    m_objects[v4].vx -= 0.035;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if (pattern == k5D && frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].pattern = kObjMichiru;
                    break;
                }
                if (pattern == k236A && frame == 2 || pattern == kAir236A && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236A;
                    m_objects[v4].frame = 8;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236B && frame == 2 || pattern == kAir236B && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236B;
                    m_objects[v4].frame = 8;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236C && frame == 2 || pattern == kAir236C && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236C;
                    m_objects[v4].frame = 8;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k421A && frame == 2 || pattern == kAir421A && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru421A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k421B && frame == 2 || pattern == kAir421B && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru421B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k421C && frame == 2 || pattern == kAir421C && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru421C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214A && frame == 2 || pattern == kAir214A && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214B && frame == 2 || pattern == kAir214B && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214C && frame == 2 || pattern == kAir214C && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236236A && frame == 2 || pattern == kAir236236A && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236236B && frame == 2 || pattern == kAir236236B && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k236236C && frame == 2 || pattern == kAir236236C && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214214A && frame == 2 || pattern == kAir214214A && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214214A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214214B && frame == 2 || pattern == kAir214214B && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214214B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == k214214C && frame == 2 || pattern == kAir214214C && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru214214C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if ((pattern == k21436A || pattern == k21436B || pattern == k21436C) && frame == 2) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru21436;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kLv4 && frame == 3) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiruLv4;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kUnused236236A && frame == 2 || pattern == kUnusedAir236236A && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236A;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kUnused236236B && frame == 2 || pattern == kUnusedAir236236B && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236B;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (pattern == kUnused236236C && frame == 2 || pattern == kUnusedAir236236C && frame == 1) {
                    m_michiruState = 4;
                    m_objects[v4].pattern = kObjMichiru236236C;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4] = 1;
                    if (pattern == kDRight) {
                        m_objects[v4].facing = 1;
                    }
                    if (pattern == kDLeft) {
                        m_objects[v4].facing = -1;
                    }
                    break;
                }
                if (pattern == k5D) {
                    m_michiruState = 1;
                    m_objects[v4].pattern = kObjMichiruReady;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xa && (m_objects[v4].x < x && m_objects[v4].x - x < -200.0 || m_objects[v4].x > x && m_objects[v4].x - x > 200.0)) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].pattern = kObjMichiru;
                        m_objectVar1[v4] = 0;
                    }
                }
                break;
            case kObjMichiru21436:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k21436A && pattern != k21436B && pattern != k21436C) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                if (m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objectVar3[v4]--;
                    if (m_objectVar3[v4] <= 0) {
                        l50.type = 0x1bb;
                        l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x17);
                        l50.y = (double)((int)m_objects[v4].y - 0x21);
                        l50.scale = 2;
                        l50.facing = m_objects[v4].facing;
                        l50.layer = 1;
                        SpawnObject(&l50);
                        m_objectVar3[v4] = 0x15;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 8 && m_objectVar2[v4] < (pattern == k21436B) * 3 + 5 + (pattern == k21436C) * 6) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_michiruState = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].movesInFreeze = 0;
                    }
                }
                break;
            case kObjShot21436A:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar2[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar2[v4]++;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 1.2;
                    m_objects[v4].vy = (WORD)Random(0, 0xa) * 0.1 + 0.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                m_objects[v4].vy -= 0.015;
                if (m_objects[v4].attackResult > 0 && m_objects[v4].frame < 0x18) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x18;
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
            case kObjShot21436B:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar2[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar2[v4]++;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 1.6;
                    m_objects[v4].vy = (WORD)Random(0, 0xa) * 0.1 + 0.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                m_objects[v4].vy -= 0.015;
                if (m_objects[v4].attackResult > 0 && m_objects[v4].frame < 0x18) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x18;
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
            case kObjShot21436C:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar2[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar2[v4]++;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 2.0;
                    m_objects[v4].vy = (WORD)Random(0, 0xa) * 0.1 + 0.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.8) {
                        m_objects[v4].vx = 0.8;
                    }
                }
                m_objects[v4].vy -= 0.015;
                if (m_objects[v4].attackResult > 0 && m_objects[v4].frame < 0x18) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x18;
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
            case kObjMichiruShot21436:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar2[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar2[v4]++;
                    m_objects[v4].vx = (WORD)Random(0, 0xa) * 0.1 + 0.5;
                    m_objects[v4].vy = (WORD)Random(0, 0xa) * 0.1 + 0.0;
                }
                if (m_objects[v4].vx > 0.8) {
                    m_objects[v4].vx -= 0.015;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                m_objects[v4].vy -= 0.015;
                if (m_objects[v4].attackResult > 0 && m_objects[v4].frame < 0x18) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x18;
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
            case kObjMichiruLv4:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objectVar2[v4] = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                    m_playVoice = 2;
                }
                if (pattern != kLv4) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                if (m_objects[v4].frame > 9 && m_objects[v4].frame < 0x16) {
                    m_objectVar3[v4]--;
                    if (m_objectVar3[v4] <= 0) {
                        l50.type = 0x1bf;
                        l50.keep = 1;
                        l50.x = x - (WORD)Random(0, 0x1e0) + 240.0 - m_objects[v4].facing * 0x78;
                        l50.y = -480.0;
                        l50.scale = 2;
                        l50.facing = m_objects[v4].facing;
                        l50.layer = 1;
                        SpawnObject(&l50);
                        m_objectVar3[v4] = 0x12;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0x16 && m_objectVar2[v4] < 0x11) {
                        m_objects[v4].frame = m_objects[v4].frame - 6;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_michiruState = 0;
                        m_objectVar2[v4] = 0;
                        m_objects[v4].movesInFreeze = 0;
                    }
                }
                break;
            case kObjLv4FallingShot:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0 && m_objectVar2[v4] == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar2[v4]++;
                    m_objects[v4].vx = 1.5;
                    m_objects[v4].vy = 3.0;
                }
                m_objectVar3[v4]--;
                if (m_objectVar3[v4] <= 0) {
                    l50.type = m_objectVar2[v4] + 0x1c0;
                    l50.x = m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 0;
                    SpawnObject(&l50);
                    m_objectVar3[v4] = 6;
                    m_objectVar2[v4]++;
                    if (m_objectVar2[v4] > 4) {
                        m_objectVar2[v4] = 0;
                    }
                }
                if (m_objects[v4].y > 200.0) {
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
            case kObjLv4Trail0:
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
            case kObjLv4Trail1:
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
            case kObjLv4Trail2:
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
            case kObjLv4Trail3:
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
            case kObjLv4Trail4:
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
            case kObjAirThrowSlam:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].vy = 3.0;
                    (*m_opponent)->x = m_objects[v4].x;
                    (*m_opponent)->y = m_objects[v4].y;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].y + m_objects[v4].vy > 0.0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    (*m_opponent)->StartPattern();
                    (*m_opponent)->pattern = kKnockdown;
                    (*m_opponent)->y = 0.0;
                    (*m_opponent)->x = m_objects[v4].x;
                    DealDamage(0x4b0, 500.0);
                    m_objects[v4].vy = 0.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 3) {
                        m_objects[v4].scale = 1;
                    }
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjMichiru236236A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k236236A && pattern != kAir236236A) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.0035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame > 3 && m_objects[v4].frame < 9) {
                        l50.type = 0x1cf;
                        l50.x = m_objects[v4].x + (WORD)Random(0, 0x1e) * m_objects[v4].facing;
                        l50.y = m_objects[v4].y - (WORD)Random(0, 0x50) + 40.0 - 30.0;
                        l50.facing = m_objects[v4].facing;
                        l50.layer = 1;
                        l50.scale = 2;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -0.5;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                        m_objectVar1[v4] = 0;
                    }
                }
                break;
            case kObjMichiru236236B:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k236236B && pattern != kAir236236B) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.0035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame > 3 && m_objects[v4].frame < 9) {
                        l50.type = ((WORD)Random(0, 0x64) > 0x32) + 0x1cf;
                        l50.x = m_objects[v4].x + (WORD)Random(0, 0x28) * m_objects[v4].facing;
                        l50.y = m_objects[v4].y - (WORD)Random(0, 0x78) + 60.0 - 30.0;
                        l50.facing = m_objects[v4].facing;
                        l50.layer = 1;
                        l50.scale = 2;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objects[v4].vx = 0.65;
                        m_objects[v4].vy = -0.52;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                        m_objectVar1[v4] = 0;
                    }
                }
                break;
            case kObjMichiru236236C:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k236236C && pattern != kAir236236C) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.003;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame > 3 && m_objects[v4].frame < 9) {
                        l50.type = ((WORD)Random(0, 0x64) > 0x46) + 0x1cf + ((WORD)Random(0, 0x64) > 0x1e);
                        l50.x = m_objects[v4].x + (WORD)Random(0, 0x28) * m_objects[v4].facing;
                        l50.y = m_objects[v4].y - (WORD)Random(0, 0x8c) + 70.0 - 30.0;
                        l50.facing = m_objects[v4].facing;
                        l50.layer = 1;
                        l50.scale = 2;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objects[v4].vx = 0.85;
                        m_objects[v4].vy = -0.55;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                        m_objectVar1[v4] = 0;
                    }
                }
                break;
            case kObjMichiruUnused236236A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != kUnused236236A && pattern != kUnusedAir236236A) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].hitsLeft = 5;
                        m_objects[v4].vx = 1.5;
                        m_objects[v4].vy = -1.4;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruUnused236236B:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != kUnused236236B && pattern != kUnusedAir236236B) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].hitsLeft = 8;
                        m_objects[v4].vx = 1.8;
                        m_objects[v4].vy = -1.4;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruUnused236236C:
                m_michiruState = 4;
                m_game->FlashNegative(0xf);
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != kUnused236236C && pattern != kUnusedAir236236C) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 3 && m_objects[v4].frame < 8) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 8;
                        m_playSound = 7;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 1 || m_objects[v4].frame == 5 || m_objects[v4].frame == 7) {
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame == 4) {
                        m_objects[v4].hitsLeft = 0xc;
                        m_objects[v4].vx = 2.1;
                        m_objects[v4].vy = -1.4;
                        break;
                    }
                    if (m_objects[v4].frame == 8) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case 0x1cc:
                m_michiruState = 4;
                if (m_objects[v4].frame < 0x10) {
                    (*m_opponent)->FocusCameraY(0x32, 0x1e);
                }
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k236236A && pattern != kAir236236A) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x14;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objectVar2[v4] = 0;
                        m_objectVar1[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && m_objectVar2[v4] < 2) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.2;
                    }
                    if (m_objects[v4].frame == 0x10 && m_objectVar1[v4] < 2) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x14) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case 0x1cd:
                m_michiruState = 4;
                if (m_objects[v4].frame < 0x14) {
                    (*m_opponent)->FocusCameraY(0x32, 0x1e);
                }
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k236236B && pattern != kAir236236B) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x17;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objectVar2[v4] = 0;
                        m_objectVar1[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && m_objectVar2[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.6;
                    }
                    if (m_objects[v4].frame == 0x10 && m_objectVar1[v4] < 3) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x17) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case 0x1ce:
                m_michiruState = 4;
                if (m_objects[v4].frame < 0x17) {
                    (*m_opponent)->FocusCameraY(0x32, 0x1e);
                    m_game->FlashNegative(0xf);
                }
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].movesInFreeze = 1;
                }
                if (pattern != k236236C && pattern != kAir236236C) {
                    m_objects[v4].movesInFreeze = 0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0x10) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x1a;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xa) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objectVar2[v4] = 0;
                        m_objectVar1[v4] = 0;
                        m_objects[v4].frame = m_objects[v4].frame + 4;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe && m_objectVar2[v4] < 3) {
                        m_objects[v4].frame = m_objects[v4].frame - 4;
                        m_objectVar2[v4]++;
                    }
                    if (m_objects[v4].frame == 0xf) {
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.6;
                    }
                    if (m_objects[v4].frame == 0x10 && m_objectVar1[v4] < 4) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame == 0x1a) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObj236236Spray1:
                m_objects[v4].vx = 2.0;
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
            case kObj236236Spray2:
                m_objects[v4].vx = 2.5;
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
            case kObj236236Spray3:
                m_objects[v4].vx = 3.0;
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
            case kObjMichiru623A:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0xb) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].frame < 0x10) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x10;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.0;
                    }
                    if (m_objects[v4].frame == 0x10) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru623B:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0xb) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].frame < 0x10) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x10;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.0;
                    }
                    if (m_objects[v4].frame == 0x10) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiru623C:
                m_michiruState = 4;
                if (m_objects[v4].attackResult == 4 || m_objects[v4].attackResult == 5) {
                    m_objects[v4].pattern = kObjMichiruKnockedBack;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                }
                if (m_objects[v4].y < 0.0 && m_objects[v4].frame > 0xb) {
                    m_objects[v4].vy += 0.025;
                    if (m_objects[v4].vy + m_objects[v4].y > 0.0 && m_objects[v4].frame < 0x16) {
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x16;
                        break;
                    }
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0xb) {
                        m_objects[v4].hitsLeft = 0x63;
                        m_objects[v4].vx = 0.5;
                        m_objects[v4].vy = -2.0;
                    }
                    if (m_objects[v4].frame == 0xc && m_objectVar1[v4] < 3) {
                        m_objects[v4].frame--;
                        m_objectVar1[v4]++;
                    }
                    if (m_objects[v4].frame == 0x16) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
                    }
                }
                break;
            case kObjMichiruHeld:
                m_michiruState = 4;
                m_objects[v4].movesInFreeze = 0;
                m_objectVar1[v4] = 0;
                m_objectVar2[v4] = 0;
                m_objectVar3[v4] = 0;
                if (m_objects[v4].frame == 0xb && m_objects[v4].timer == 0) {
                    m_objects[v4].x = facing * 0x3c + x;
                }
                if (m_objects[v4].x > 620.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 620.0;
                }
                if (m_objects[v4].x < 20.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].x = 20.0;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].pattern = kObjMichiru;
                        m_objects[v4].frame = 0;
                        m_michiruState = 0;
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
