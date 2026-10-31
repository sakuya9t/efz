// CIkumi (0x6a59c0-0x6be9bf).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CIkumi::CIkumi(PTR32(CPlayer)* p1, CGame* p2, CGraphics* p3, CInput* p4, CSound* p5, BYTE p6)
    : CPlayer(p1, p2, p3, p4, p5, p6)
{
    int v4;

    m_altAnims = new EffectAnim[0x1f9];
    m_altPatterns = new PatternData[0x1f9];
    UseAltPatterns(0);
    m_altPatternsIn = 0;
    strcpy(m_name, "ikumi");
    lastSurface = 0x47c;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_stockCharge = 0;
    m_stocks = 0;
    m_modeTimer = 0;
    m_orbBurstSpawned = 0;
    m_modeTintTimer = 0;
    m_storedSuperLevel = 0;
    m_pointX[0] = -0x16;
    m_pointY[0] = -0x32;
    m_pointX[1] = -0x19;
    m_pointY[1] = 0;
    m_pointX[2] = -0x19;
    m_pointY[2] = -0xa;
    m_pointX[3] = 5;
    m_pointY[3] = -9;
    m_pointX[4] = 0x20;
    m_pointY[4] = -0x1b;
    m_resultPictures = 7;
    m_rivals[0] = 8;
    m_rivals[1] = 0xd;
    m_rivals[0xa] = 0xe;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
}

void CIkumi::Reset()
{
    int v4;

    UseAltPatterns(0);
    m_altPatternsIn = 0;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_stockCharge = 0;
    m_stocks = 0;
    m_modeTimer = 0;
    m_orbBurstSpawned = 0;
    m_modeTintTimer = 0;
    m_storedSuperLevel = 0;
    m_pointX[0] = -4;
    m_pointY[0] = -0x39;
    m_pointX[1] = -0x19;
    m_pointY[1] = 0;
    m_pointX[2] = 0x15;
    m_pointY[2] = -0xc;
    m_pointX[3] = 0x12;
    m_pointY[3] = -0xf;
    m_pointX[4] = 0x26;
    m_pointY[4] = -0x27;
    v4 = 0;
    for (; v4 < 0x40; v4++) {
        m_objectVar1[v4] = 0;
        m_objectVar2[v4] = 0;
        m_objectVar3[v4] = 0;
    }
    CPlayer::Reset();
}

CIkumi::~CIkumi()
{
    anims = TOPTR(EffectAnim*, m_baseAnims);
    m_patterns = TOPTR(PatternData*, m_basePatterns);
    delete[] m_altAnims;
    delete[] m_altPatterns;
    CPlayer::~CPlayer();
}

void CIkumi::Load()
{
    LoadAltPatterns();
    CPlayer::Load();
    m_baseAnims = (int)anims;
    m_basePatterns = (int)m_patterns;
}

void CIkumi::LoadAltPatterns()
{
    int k2c;
    PatternFrame* v28;
    EffectFrame* x24;
    int x20;
    int n1c;
    int a18;
    int k14;
    int l4;

    CFile v10("ikumi\\ikumi2.pat", 1);
    l4 = v10.ReadInt();
    n1c = 0;
    for (; n1c < l4; n1c++) {
        k14 = v10.ReadInt();
        m_altPatterns[k14].level = v10.ReadInt();
        m_altPatterns[k14].cancelLevel = v10.ReadInt();
        m_altAnims[k14].frameCount = v10.ReadInt();
        a18 = m_altAnims[k14].frameCount;
        (TOPTR(PatternData*, TOINT(int, (char*)m_altPatterns) + k14 * 8))->Alloc(a18);
        (TOPTR(EffectAnim*, TOINT(int, (char*)m_altAnims) + k14 * 8))->Alloc(a18);
        x20 = 0;
        for (; x20 < a18; x20++) {
            x24 = &m_altAnims[k14].frames[x20];
            v28 = &m_altPatterns[k14].frames[x20];
            x24->duration = (short)v10.ReadInt() * 3;
            x24->surface = v10.ReadInt();
            x24->width = v10.ReadInt();
            x24->height = v10.ReadInt();
            x24->x = v10.ReadInt();
            x24->y = v10.ReadInt();
            v28->damage = v10.ReadInt();
            v28->flagsAA = v10.ReadInt();
            v28->airHitPattern = v10.ReadInt();
            v28->flagsB0 = v10.ReadInt();
            v28->untechTime = v10.ReadInt();
            v28->chipDamage = v10.ReadInt();
            v28->gaugeOnHit = v10.ReadInt();
            v28->gaugeOnGuard = v10.ReadInt();
            v28->hitVy = (short)v10.ReadShort();
            v28->hitVy = v28->hitVy / 1e+02f;
            v28->hitVx = (short)v10.ReadShort();
            v28->hitVx = v28->hitVx / -1e+02f;
            v28->hitSound = v10.ReadShort();
            v28->hitEffect = v10.ReadShort();
            v28->attackerHitstop = v10.ReadInt();
            v28->defenderHitstop = v10.ReadInt();
            v28->proration = v10.ReadInt();
            v28->groundHitPattern = v10.ReadInt();
            v10.Read((void*)&v28->pushBox.left, 0x10);
            k2c = 0;
            for (; k2c < 2; k2c++) {
                v10.Read((void*)((k2c << 4) + (char*)v28), 0x10);
            }
            v10.Read((void*)&v28->attackBoxes[0].left, 0x10);
            k2c = 2;
            for (; k2c < 5; k2c++) {
                v10.Read((void*)((k2c << 4) + (char*)v28), 0x10);
            }
            k2c = 1;
            for (; k2c < 4; k2c++) {
                v10.Read((void*)&v28->attackBoxes[k2c].left, 0x10);
            }
        }
    }
}

void CIkumi::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_orbBurstSpawned = 0;
    CPlayer::StartPattern();
}

void CIkumi::RemoveObject(short p1)
{
    m_objectVar1[p1] = 0;
    m_objectVar2[p1] = 0;
    m_objectVar3[p1] = 0;
    CPlayer::RemoveObject(p1);
}

void CIkumi::Move()
{
    MoveOnGround();
}

void CIkumi::StartCommand()
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
        if (m_command == kCmd236236236C && m_gauge >= 0xbb8 && m_hp < 0xd05 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && m_attackResult != 6 && m_modeTimer == 0 && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
            return;
        }
        if (m_modeTimer == 0 && m_command == kCmd214214C && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214C;
            return;
        }
        if (m_modeTimer == 0 && m_command == kCmd214214B && y == 0.0 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214B;
            return;
        }
        if (m_modeTimer == 0 && m_command == kCmd214214A && y == 0.0 && m_gauge >= 0x3e8 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214214A;
            return;
        }
        if (m_modeTimer > 0 && m_command == kCmd21436C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436CMode].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436CMode;
            return;
        }
        if (m_modeTimer > 0 && (m_command == kCmd21436B || m_command == kCmd21436C) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436BMode].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436BMode;
            return;
        }
        if (m_modeTimer > 0 && (m_command == kCmd21436A || m_command == kCmd21436B || m_command == kCmd21436C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436AMode].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436AMode;
            return;
        }
        if ((m_command == kCmd21436A || m_command == kCmd21436B || m_command == kCmd21436C) && m_storedSuperLevel > 0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436Release1].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436Release1;
            if (m_storedSuperLevel == 2) {
                pattern = k21436Release2;
            }
            if (m_storedSuperLevel == 3) {
                pattern = k21436Release3;
            }
            return;
        }
        if (m_command == kCmd21436C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436C;
            return;
        }
        if ((m_command == kCmd21436B || m_command == kCmd21436C) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436B;
            return;
        }
        if ((m_command == kCmd21436A || m_command == kCmd21436B || m_command == kCmd21436C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k21436A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k21436A;
            return;
        }
        if (m_command == kCmd4123641236C && m_gauge >= 0xbb8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k4123641236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k4123641236C;
            return;
        }
        if ((m_command == kCmd4123641236C || m_command == kCmd4123641236B) && m_gauge >= 0x7d0 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k4123641236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k4123641236B;
            return;
        }
        if ((m_command == kCmd4123641236A || m_command == kCmd4123641236B || m_command == kCmd4123641236C) && m_gauge >= 0x3e8 && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k4123641236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k4123641236A;
            return;
        }
        if (m_command == kCmd41236C && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k41236C;
            return;
        }
        if (m_command == kCmd623C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623C;
            if (m_stocks > 5 || m_modeTimer > 0) {
                pattern = k623CStock6;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            if (m_stocks > 2) {
                pattern = k623CStock3;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            return;
        }
        if ((m_command == kCmd623B || m_command == kCmd623C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623B;
            if (m_stocks > 5 || m_modeTimer > 0) {
                pattern = k623BStock6;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            if (m_stocks > 2) {
                pattern = k623BStock3;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            return;
        }
        if (m_command == kCmd623A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k623A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k623A;
            return;
        }
        if (m_command == kCmd214C && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214C;
            if (m_stocks > 5 || m_modeTimer > 0) {
                pattern = k214CStock6;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            if (m_stocks > 2) {
                pattern = k214CStock3;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            return;
        }
        if (m_command == kCmd214B && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214B;
            if (m_stocks > 5 || m_modeTimer > 0) {
                pattern = k214BStock6;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            if (m_stocks > 2) {
                pattern = k214BStock3;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            return;
        }
        if (m_command == kCmd214A && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k214A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214A;
            if (m_stocks > 5 || m_modeTimer > 0) {
                pattern = k214AStock6;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            if (m_stocks > 2) {
                pattern = k214AStock3;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            return;
        }
        if (m_command == kCmd236C && y == 0.0 && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236C].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236C;
            if (m_stocks > 5 || m_modeTimer > 0) {
                pattern = k236CStock6;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            if (m_stocks > 2) {
                pattern = k236CStock3;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            return;
        }
        if ((m_command == kCmd236B || m_command == kCmd236C) && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236B].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236B;
            if (m_stocks > 5 || m_modeTimer > 0) {
                pattern = k236BStock6;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            if (m_stocks > 2) {
                pattern = k236BStock3;
                if (m_modeTimer == 0) {
                    m_stocks--;
                }
                return;
            }
            return;
        }
        if (m_command == kCmd236A && y == 0.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236A].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236A;
            return;
        }
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
            if (m_inputX != 0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
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

void CIkumi::DrawGauge()
{
    RECT v2c;
    EffectFrame x1c;
    RECT v10;

    if (m_modeTimer == 0) {
        x1c = *anims[0x2b].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_modeTimer > 0) {
        x1c = *anims[0x2c].frames;
        v2c = MakeRect(0, 0, x1c.width, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_modeTimer > 0) {
        x1c = *anims[0x2a].frames;
        v2c = MakeRect(0, 0, m_modeTimer * x1c.width / 0x4ec, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(0x31 - x1c.x, 0x1f - x1c.y, m_modeTimer * x1c.width / 0x4ec, x1c.height);
        } else {
            v10 = MakeRect(x1c.x + 0x10f - m_modeTimer * x1c.width / 0x4ec, 0x1f - x1c.y, m_modeTimer * x1c.width / 0x4ec, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
    }
    if (m_modeTimer == 0) {
        x1c = *anims[0x26].frames;
        v2c = MakeRect(0, 0, m_stockCharge * x1c.width / 0x64, x1c.height);
        if (m_side == 0) {
            v10 = MakeRect(m_stocks * 8 + 0x32 - x1c.x, 0x1f - x1c.y, m_stockCharge * x1c.width / 0x64, x1c.height);
        } else {
            v10 = MakeRect(0x10e - (m_stocks << 3) + x1c.x - x1c.width * m_stockCharge / 0x64, 0x1f - x1c.y, m_stockCharge * x1c.width / 0x64, x1c.height);
        }
        m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
        if (m_stocks > 0) {
            if (m_stocks > 0) {
                if (m_stocks < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x32 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0x10e - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (m_stocks > 1) {
                if (m_stocks < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x3a - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0x106 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (m_stocks > 2) {
                if (m_stocks < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x42 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xfe - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (m_stocks > 3) {
                if (m_stocks < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x4a - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xf6 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (m_stocks > 4) {
                if (m_stocks < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x52 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xee - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (m_stocks > 5) {
                if (m_stocks < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x5a - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xe6 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (m_stocks > 6) {
                if (m_stocks < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x62 - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xde - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
            if (m_stocks > 7) {
                if (m_stocks < 9) {
                    x1c = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    x1c = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    x1c = *anims[0x27].frames;
                }
                v2c = MakeRect(0, 0, x1c.width, x1c.height);
                if (m_side == 0) {
                    v10 = MakeRect(0x6a - x1c.x, 0x1f - x1c.y, x1c.width, x1c.height);
                } else {
                    v10 = MakeRect(x1c.x + 0xd6 - x1c.width, 0x1f - x1c.y, x1c.width, x1c.height);
                }
                m_graphics->Blit(v10, surfaces[x1c.surface], v2c, colorKey, 0);
            }
        }
    }
}

void CIkumi::PreUpdate()
{
    EffectDesc v48;
    InitEffectDesc((EffectDesc*)&v48);
    if (m_stocks == 8 && y == 0.0 && pattern < kCrouchDown && pattern != kModeStart) {
        StartPattern();
        StopMoving();
        pattern = kModeStart;
    }
    if (m_stocks == 0xa) {
        m_modeTintTimer++;
        if (m_modeTintTimer > 0xb9) {
            m_modeTintTimer = 0;
        }
        m_modeTimer--;
        m_armorTime = 2;
        m_noGuardTime = 2;
        StartAfterimages(2);
        if (m_modeTintTimer == 6) {
            Tint(0xd5, 9);
        }
        if (m_modeTintTimer == 0xc) {
            Tint(0xd6, 9);
        }
        if (m_modeTintTimer == 0x12) {
            Tint(0xea, 9);
        }
        if (m_modeTintTimer == 0x18) {
            Tint(0xe9, 9);
        }
        if (m_modeTintTimer == 0x1e) {
            Tint(0xe8, 9);
        }
        if (m_modeTintTimer == 0x24) {
            Tint(0xe7, 9);
        }
        if (m_modeTintTimer == 0x2a) {
            Tint(0xe6, 9);
        }
        if (m_modeTintTimer == 0x30) {
            Tint(0xe5, 9);
        }
        if (m_modeTintTimer == 0x36) {
            Tint(0xe4, 9);
        }
        if (m_modeTintTimer == 0x3c) {
            Tint(0xe5, 9);
        }
        if (m_modeTintTimer == 0x42) {
            Tint(0xe6, 9);
        }
        if (m_modeTintTimer == 0x48) {
            Tint(0xe7, 9);
        }
        if (m_modeTintTimer == 0x4e) {
            Tint(0xe8, 9);
        }
        if (m_modeTintTimer == 0x54) {
            Tint(0xe9, 9);
        }
        if (m_modeTintTimer == 0x5a) {
            Tint(0xea, 9);
        }
        if (m_modeTintTimer == 0x60) {
            Tint(0xd6, 9);
        }
        if (m_modeTintTimer == 0x66) {
            Tint(0xd5, 9);
        }
        if (m_modeTimer <= 0) {
            m_stocks = 0;
            m_stockCharge = 0;
            UseAltPatterns(0);
        }
    }
    if (m_attackResult == 3 && m_orbBurstSpawned == 0) {
        if (pattern == k5BClose || pattern == k5BFar || pattern == k2B || pattern == kJumpB) {
            v48.type = kObjOrbBurst3;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.facing = facing;
            SpawnObject(&v48);
            m_orbBurstSpawned++;
        }
        if (pattern == kDashB || pattern == kDash2B) {
            v48.type = kObjOrbBurst5;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.facing = facing;
            SpawnObject(&v48);
            m_orbBurstSpawned++;
        }
        if (pattern == k236A || pattern == k236B || pattern == k623A || pattern == k623B) {
            v48.type = kObjOrbBurst6;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.facing = facing;
            SpawnObject(&v48);
            m_orbBurstSpawned++;
        }
        if (pattern == k236BStock3 || pattern == k236C || pattern == k236CStock3 || pattern == k623C || pattern == k623BStock3 || pattern == k623CStock3) {
            v48.type = kObjOrbBurst9;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.facing = facing;
            SpawnObject(&v48);
            m_orbBurstSpawned++;
        }
        if (pattern == k236BStock6 || pattern == k236CStock6 || pattern == k623BStock6 || pattern == k623CStock6) {
            v48.type = kObjOrbBurst10;
            v48.x = (double)(int)(*m_opponent)->x;
            v48.y = (*m_opponent)->y - 40.0;
            v48.scale = 0;
            v48.layer = 1;
            v48.facing = facing;
            SpawnObject(&v48);
            m_orbBurstSpawned++;
        }
    }
}

void CIkumi::UseAltPatterns(char p1)
{
    int v8;
    int v4;

    if (p1 == 1 && m_altPatternsIn == 0) {
        anims = TOPTR(EffectAnim*, (int)m_altAnims);
        v4 = 0;
        for (; v4 < 0x40; v4++) {
            m_objects[v4].anims = TOPTR(EffectAnim*, (int)m_altAnims);
        }
        m_patterns = TOPTR(PatternData*, (int)m_altPatterns);
        m_altPatternsIn = 1;
        return;
    }
    if (p1 == 0 && m_altPatternsIn == 1) {
        anims = TOPTR(EffectAnim*, m_baseAnims);
        v8 = 0;
        for (; v8 < 0x40; v8++) {
            m_objects[v8].anims = TOPTR(EffectAnim*, m_baseAnims);
        }
        m_patterns = TOPTR(PatternData*, m_basePatterns);
        m_altPatternsIn = 0;
    }
}

void CIkumi::SpawnObject(EffectDesc* p1)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(p1);
}

void CIkumi::ReadCommand()
{
    BYTE x6;
    BYTE v5;
    int v4;

    m_command = kCmdNone;
    x6 = 0;
    v4 = m_inputPos + 0x46;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0x40) != 0 && x6 == 9) {
            m_command = kCmd236236236C;
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 8) {
            if ((v5 & 0x40) != 0) {
                m_command = kCmd236236236C;
                return;
            }
            x6 = 9;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 7) {
            x6 = 8;
        }
        if ((v5 & 0xf) == 4 && x6 == 6) {
            x6 = 7;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
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
    v4 = m_inputPos + 0x2d;
    for (; v4 < m_inputPos + 0xb4; v4++) {
        v5 = m_inputHistory[(v4 - (v4 >= 0xb4) * 0xb4)];
        if ((v5 & 0xf0) != 0 && x6 == 7) {
            m_command = ((v5 & 0xe0) > 0) + kCmd4123641236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
            return;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 5) {
            if ((v5 & 0xf0) != 0) {
                m_command = ((v5 & 0xe0) > 0) + kCmd4123641236A + ((v5 & 0xc0) > 0) + ((v5 & 0x80) > 0);
                return;
            }
            x6 = 8;
        }
        if ((v5 & 0xf) == (facing == -1) + 5 && x6 == 6) {
            x6 = 7;
        }
        if ((v5 & 0xf) == 6 - (facing == -1) && x6 == 5) {
            x6 = 6;
        }
        if ((v5 & 0xf) == 2 - (facing == -1) && x6 == 4) {
            x6 = 5;
        }
        if ((v5 & 0xf) == (facing == -1) + 1 && x6 == 3) {
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
    v4 = m_inputPos + 0x5a;
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
        if ((v5 & 0xf) == 4 && x6 == 0 && (m_gauge >= 0x3e8 || m_storedSuperLevel > 0)) {
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

void CIkumi::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == k41236CHold && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 < 40.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0) {
            if (v10 > 20.0 && v10 < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressB = 1;
                m_inputY = 1;
                m_inputX = 0;
                return;
            }
            if (v10 > 60.0 && v10 < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
                m_pressA = 3;
                m_inputY = 1;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (v10 < 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd623C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && v10 < 80.0 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + 0x78;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && v10 < 150.0 && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
        }
        if (v10 < 220.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
        }
        if (v10 > 220.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_rfGauge > 500.0) {
                m_command = (WORD)Random(0, 3) + kCmd236A;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5f;
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
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 100.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (y - (*m_opponent)->y > -100.0 && y - (*m_opponent)->y < -50.0 && v10 < 120.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
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
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 4 && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 3) + 0x78;
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
            m_command = (WORD)Random(0, 3) + 0x78;
            return;
        }
        if (m_cpuRoll > 0x55) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k214A || pattern == k214B || pattern == k214C || pattern == k236CStock6 || pattern == 0x10f || pattern == k623BStock3)) {
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
                m_command = (WORD)Random(0, 3) + 0x78;
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
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0x1c2 && v10 < 90.0) {
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
                    if (v10 > 80.0) {
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
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x140 && m_cpuRoll < 0x258 && v10 < 100.0) {
                m_pressC = 1;
                return;
            }
            if (m_cpuRoll < 0x1f4 && m_attackResult == 3 && v10 < 80.0) {
                m_pressC = 1;
                m_inputY = 0;
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
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)Random(0, 3) + 0x78;
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
                m_command = 0x5f;
                return;
            }
            if (m_cpuRoll > 0x1ae && m_cpuRoll < 0x21c && m_attackResult != 3) {
                m_command = 0x28;
                if (v10 > 120.0) {
                    m_command = 0x29;
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
                    m_cpuAction = 6;
                    if (v10 > 110.0) {
                        m_cpuAction = 8;
                    }
                    return;
                }
                return;
            }
        }
        if (pattern == k2B) {
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
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)Random(0, 3) + 0x78;
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
                m_command = 0x28;
                if (v10 > 120.0) {
                    m_command = 0x29;
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
            if (m_cpuRoll > 0xc8 && m_cpuRoll < 0xdc && v10 < 90.0 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + 0x78;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x289 && (WORD)Random(0, 2) == 0) {
                m_cpuAction = 0xc;
                if (v10 > 110.0) {
                    m_cpuAction = 8;
                }
            }
        }
        if (pattern == kDashC) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = kCmd236A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x140 && m_gauge >= 0x3e8 && v10 < 90.0) {
                m_command = (WORD)Random(0, 3) + 0x78;
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
                m_command = 0x5f;
                return;
            }
            if (m_cpuRoll > 0x1ae && m_cpuRoll < 0x21c && m_attackResult != 3) {
                m_command = 0x28;
                if (v10 > 120.0) {
                    m_command = 0x29;
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
                if (v10 < 40.0 && (*m_opponent)->y == 0.0 && m_cpuRoll < 5) {
                    m_pressC = 1;
                    m_inputX = -facing;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 50.0 && m_cpuRoll < 0x17) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 75.0 && m_cpuRoll < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x28 && m_cpuRoll > 0x1e) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0x34 && m_cpuRoll > 0x28 || v10 > 80.0 && v10 < 130.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x34) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && m_cpuRoll < 0x64 && m_cpuRoll > 0x50) {
                    m_cpuAction = 8;
                    return;
                }
                if (v10 > 70.0 && v10 < 120.0 && m_cpuRoll < 0x78 && m_cpuRoll > 0x64) {
                    m_cpuAction = 8;
                    return;
                }
                if (v10 < 90.0 && v10 > 70.0 && m_cpuRoll < 0x82 && m_cpuRoll > 0x78) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (v10 < 120.0 && v10 > 70.0 && m_cpuRoll < 0x91 && m_cpuRoll > 0x82) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
                if (v10 > 100.0 && v10 < 140.0 && m_cpuRoll < 0x98 && m_cpuRoll > 0x91) {
                    m_cpuAction = 0xa;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0xa5 && m_cpuRoll > 0x91 && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd623C;
                    return;
                }
                if (v10 < 80.0 && m_cpuRoll < 0xaa && m_cpuRoll > 0xa5 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 3) + 0x78;
                    return;
                }
                if (v10 > 200.0 && m_cpuRoll < 0xaa && m_cpuRoll > 0xa5 && m_gauge >= 0x3e8 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = (WORD)Random(0, 3) + 0x82;
                    return;
                }
                if (v10 > 200.0 && m_cpuRoll < 0xbe && m_cpuRoll > 0xaa) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (v10 > 80.0 && v10 < 120.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = 0x28;
                    return;
                }
                if (v10 > 140.0 && v10 < 180.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = 0x29;
                    return;
                }
                if (v10 > 200.0 && v10 < 240.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = 0x2a;
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
                    if (v10 < 80.0 && m_cpuRoll < 0xf && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + 0x78;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (v10 < 90.0 && x8 < 140.0 && m_cpuRoll < 6 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623C;
                        return;
                    }
                    if (v10 < 90.0 && x8 < 140.0 && x8 > 100.0 && m_cpuRoll < 0x23 && m_cpuRoll > 0xa) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 > 100.0 && v10 < 140.0 && x8 < 180.0 && x8 > 140.0 && m_cpuRoll < 0x3c && m_cpuRoll > 0x23) {
                        m_pressC = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 > 100.0 && v10 < 140.0 && x8 < 140.0 && x8 > 100.0 && m_cpuRoll < 0x50 && m_cpuRoll > 0x3c) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                    if (v10 < 80.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x50 && (*m_opponent)->y < -50.0 && m_gauge >= 0x3e8) {
                        m_command = (WORD)Random(0, 3) + 0x78;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x32) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 120.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x32 && m_cpuRoll < 0x78) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && x8 > 100.0 && x8 < 180.0 && m_cpuRoll > 0x78 && m_cpuRoll < 0xaa) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 0x140) < v10 - 100.0 && x8 < 90.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xdc) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (v10 > 100.0 && m_cpuRoll > 0xf0 && m_cpuRoll < 0x14a && x8 + 40.0 > v10 && x8 - 40.0 < v10) {
                    m_command = (WORD)Random(0, 3) + 0x28;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (v10 < 80.0 && x8 < 100.0 && m_cpuRoll < 0x14) {
                    m_pressA = 1;
                    return;
                }
                if (v10 > 60.0 && v10 < 120.0 && x8 > 90.0 && x8 < 120.0 && (*m_opponent)->y < y && m_cpuRoll > 0x14 && m_cpuRoll < 0x28) {
                    m_pressB = 1;
                    return;
                }
                if (v10 > 80.0 && v10 < 140.0 && x8 > 100.0 && x8 < 180.0 && m_cpuRoll > 0x28 && m_cpuRoll < 0x32) {
                    m_pressC = 1;
                    return;
                }
                if ((WORD)Random(0, 0x140) < v10 - 100.0 && x8 < 180.0 && m_cpuRoll > 0xaa && m_cpuRoll < 0xf0) {
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
    if (pattern < kFirstHitReaction && (*m_opponent)->pattern < kFirstHitReaction && v10 > 60.0 && v10 < 140.0 && (WORD)Random(0, 0x64) < 2.0f * m_cpuSkill && x > 120.0 && x < 520.0) {
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

void CIkumi::UpdateObjects()
{
    WORD v58;
    WORD v54;
    int v4;

    if (m_altPatternsIn == 1) {
        UpdateObjectsAlt();
        return;
    }
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
            case kObj623Effect:
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
            case kObj214GroundEffect:
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
            case kObj214Eruption:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = kObj214Pillar;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.keep = 1;
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
            case kObj214Pillar:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    m_objectVar1[v4] = 1;
                    l50.type = kObjOrbBurst5;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
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
            case kObjThrowImpact:
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
            case kObj214EruptionStock3:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = kObj214PillarStock3;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.keep = 1;
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
            case kObj214PillarStock3:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    m_objectVar1[v4] = 1;
                    l50.type = kObjOrbBurst5;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0x2f && m_objectVar1[v4] == 0) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 0x20;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214EruptionStock6:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = kObj214PillarStock6;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.keep = 1;
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
            case kObj214PillarStock6:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 2;
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                }
                if (m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                if (m_objects[v4].attackResult == 3 && m_objectVar2[v4] == 0) {
                    m_objectVar2[v4] = 1;
                    l50.type = kObjOrbBurst5;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x2f && m_objectVar1[v4] < 3) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 0x20;
                        m_objects[v4].attackResult = 0;
                        m_objectVar2[v4] = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjModeStartAura:
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
            case kObjGrabSuperEffect1:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjGrabSuperEffect2:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjGrabSuperEffect3:
                if (m_objects[v4].timer == 0 && (m_objects[v4].frame == 0 || m_objects[v4].frame == 0xa || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x1e)) {
                    l50.type = kObjGrabSuperSpark;
                    if ((WORD)Random(0, 0x64) < 0x32) {
                        l50.type = kObjGrabSuperSparkTall;
                    }
                    l50.x = (double)((int)m_objects[v4].x + -0x3c + (WORD)Random(0, 0x78));
                    l50.y = (double)((int)m_objects[v4].y - (WORD)Random(0, 0xa0));
                    l50.facing = m_objects[v4].facing;
                    if ((WORD)Random(0, 0x64) < 0x32) {
                        l50.facing = -m_objects[v4].facing;
                    }
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjGrabSuperSpark:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjGrabSuperSparkTall:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjDouble236:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[v4].frame == 0x1b && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 2.5;
                    m_objects[v4].hitsLeft = 3;
                }
                if (m_objects[v4].frame == 0x1b && m_objects[v4].timer == 0) {
                    m_objectVar2[v4] = 1;
                }
                if (m_objects[v4].frame == 0x25 && m_objects[v4].timer == 0) {
                    m_playSound = 0x14;
                    l50.type = kObj236Effect;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                    m_playVoice = 2;
                }
                if (m_objects[v4].frame > 0x26) {
                    m_objects[v4].vx -= 0.07;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if ((m_objects[v4].x - (*m_opponent)->x < 150.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 150.0 && m_objects[v4].facing == 1) && m_objectVar2[v4] != 0 && m_objects[v4].frame < 0x23) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x23;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2 && m_objectVar1[v4] < 0) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0xc) {
                        m_objects[v4].frame = 0x1b;
                    }
                    if (m_objects[v4].frame == 0x1b && m_objectVar1[v4] < 0) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 5;
                    }
                    if (m_objects[v4].frame == 0x23 && m_objectVar3[v4] < 1) {
                        m_objects[v4].frame = m_objects[v4].frame - 8;
                        m_objectVar3[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObjDoubleLeap:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[v4].frame > 4 && m_objects[v4].frame < 0x1b && (m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 50.0 && m_objects[v4].facing == 1)) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1b;
                    break;
                }
                if ((m_objects[v4].frame == 0x1e || m_objects[v4].frame == 0x26 || m_objects[v4].frame == 0x2f) && m_objects[v4].timer == 0) {
                    m_playSound = 0x15;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame < 0x37) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x37;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2 && m_objectVar1[v4] < 8) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0x1b && m_objectVar1[v4] < 0xd) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 5;
                    }
                    if (m_objects[v4].frame == 0x2d) {
                        m_objects[v4].vx = 1.0;
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objects[v4].frame == 0x37) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObjDouble214:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[v4].frame == 6) {
                    m_objects[v4].vx = 0.6;
                }
                if ((m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 50.0 && m_objects[v4].facing == 1) && m_objects[v4].frame > 5 && m_objects[v4].frame < 0xe) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xe;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2 && m_objectVar1[v4] < 8) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0xe && m_objectVar2[v4] < 5) {
                        m_objectVar2[v4]++;
                        m_objects[v4].frame = 6;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].frame == 0x15) {
                        l50.type = kObjDoubleEruption;
                        l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x32);
                        l50.y = 0.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.keep = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObj21436GroundEffect:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj21436Strike1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObj21436ExtraPillar:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 0;
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
            case kObj21436Strike2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObj21436Strike3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObjDoubleEruption:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = kObjDoublePillar;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.keep = 1;
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
            case kObjDoublePillar:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 4;
                }
                if (m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x2f && m_objectVar1[v4] < 3) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 0x20;
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjDoubleVanish:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Strike1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 7.0;
                    m_objects[v4].vy = -3.5;
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
            case kObjLv4Strike2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 7.0;
                    m_objects[v4].vy = -3.5;
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
            case kObjLv4Strike3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 3.5;
                    m_objects[v4].vy = -7.0;
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
            case kObjLv4Strike4:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 3.5;
                    m_objects[v4].vy = -7.0;
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
            case kObjLv4Figure1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 4.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_patternVar1 = 1;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = -4.0;
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
            case kObjLv4Figure2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 6.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -6.0;
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
            case kObjLv4Figure3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 4.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_patternVar1 = 1;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = -4.0;
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
            case kObjLv4Figure4:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 6.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -6.0;
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
            case kObjLv4Blast:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].attackResult > 0) {
                    m_patternVar2 = 1;
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
            case kObjOrbBurst3:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
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
            case kObjOrbBurst6:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
            case kObjOrbSmall:
                m_objects[v4].vy += 0.035;
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objectVar2[v4] = (WORD)Random(0x5a, 0x61);
                    m_objects[v4].SetVelocity((double)-m_objectVar2[v4], (WORD)Random(0, 5) * 0.1 + 3.2);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbCaught;
                    if (m_stocks < 8) {
                        m_stockCharge += 0xa;
                    }
                    if (m_stockCharge >= 0x64) {
                        m_stockCharge = 0;
                        m_stocks++;
                        if (m_stocks > 8) {
                            m_stocks = 8;
                        }
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbOnGround;
                    m_objects[v4].layer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case kObjOrbMedium:
                m_objects[v4].vy += 0.035;
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objectVar2[v4] = (WORD)Random(0x5a, 0x64);
                    m_objects[v4].SetVelocity((double)-m_objectVar2[v4], (WORD)Random(0, 5) * 0.1 + 2.2);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbCaught;
                    if (m_stocks < 8) {
                        m_stockCharge += 0x1e;
                    }
                    if (m_stockCharge >= 0x64) {
                        m_stockCharge = 0;
                        m_stocks++;
                        if (m_stocks > 8) {
                            m_stocks = 8;
                        }
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbOnGround;
                    m_objects[v4].layer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case kObjOrbLarge:
                m_objects[v4].vy += 0.035;
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objectVar2[v4] = (WORD)Random(0x5a, 0x64);
                    m_objects[v4].SetVelocity((double)-m_objectVar2[v4], (WORD)Random(0, 5) * 0.1 + 2.8);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbCaught;
                    if (m_stocks < 8) {
                        m_stockCharge += 0x32;
                    }
                    if (m_stockCharge >= 0x64) {
                        m_stockCharge = 0;
                        m_stocks++;
                        if (m_stocks > 8) {
                            m_stocks = 8;
                        }
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbOnGround;
                    m_objects[v4].layer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case kObjOrbCaught:
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
            case kObjOrbOnGround:
                if (m_objects[v4].frame == 4 && m_objects[v4].x - x > -15.0 && m_objects[v4].x - x < 15.0 && y == 0.0) {
                    if (m_stocks < 8) {
                        m_stockCharge += 8;
                    }
                    if (m_stockCharge >= 0x64) {
                        m_stockCharge = 0;
                        m_stocks++;
                        if (m_stocks > 8) {
                            m_stocks = 8;
                        }
                    }
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 7;
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
            case kObjOrbBurst14:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbLarge;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
            case kObjOrbBurst5:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
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
            case kObjOrbBurst9:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbLarge;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
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
            case kObjOrbBurst10:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbLarge;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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

void CIkumi::UpdateObjectsAlt()
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
            case kObj623Effect:
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
            case kObj214GroundEffect:
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
            case kObj214Eruption:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = kObj214Pillar;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.keep = 1;
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
            case kObj214Pillar:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    m_objectVar1[v4] = 1;
                    l50.type = kObjOrbBurst5;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
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
            case kObjThrowImpact:
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
            case kObj214EruptionStock3:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = kObj214PillarStock3;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.keep = 1;
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
            case kObj214PillarStock3:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objectVar1[v4] = 0;
                }
                if (m_objects[v4].attackResult == 3 && m_objectVar1[v4] == 0) {
                    m_objectVar1[v4] = 1;
                    l50.type = kObjOrbBurst5;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                if (m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 0x2f && m_objectVar1[v4] == 0) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 0x20;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj214EruptionStock6:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = kObj214PillarStock6;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.keep = 1;
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
            case kObj214PillarStock6:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 2;
                    m_objectVar1[v4] = 0;
                    m_objectVar2[v4] = 0;
                }
                if (m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                if (m_objects[v4].attackResult == 3 && m_objectVar2[v4] == 0) {
                    m_objectVar2[v4] = 1;
                    l50.type = kObjOrbBurst5;
                    l50.x = (double)(int)(*m_opponent)->x;
                    l50.y = (*m_opponent)->y - 40.0;
                    l50.scale = 0;
                    l50.layer = 1;
                    l50.facing = facing;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x2f && m_objectVar1[v4] < 3) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 0x20;
                        m_objects[v4].attackResult = 0;
                        m_objectVar2[v4] = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjModeStartAura:
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
            case kObjGrabSuperEffect1:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjGrabSuperEffect2:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjGrabSuperEffect3:
                if (m_objects[v4].timer == 0 && (m_objects[v4].frame == 0 || m_objects[v4].frame == 0xa || m_objects[v4].frame == 0x14 || m_objects[v4].frame == 0x1e)) {
                    l50.type = kObjGrabSuperSpark;
                    if ((WORD)Random(0, 0x64) < 0x32) {
                        l50.type = kObjGrabSuperSparkTall;
                    }
                    l50.x = (double)((int)m_objects[v4].x + -0x3c + (WORD)Random(0, 0x78));
                    l50.y = (double)((int)m_objects[v4].y - (WORD)Random(0, 0xa0));
                    l50.facing = m_objects[v4].facing;
                    if ((WORD)Random(0, 0x64) < 0x32) {
                        l50.facing = -m_objects[v4].facing;
                    }
                    l50.layer = 1;
                    l50.scale = 2;
                    SpawnObject(&l50);
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x28 && frame < 7) {
                        m_objects[v4].frame = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjGrabSuperSpark:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjGrabSuperSparkTall:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjDouble236:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[v4].frame == 0x1b && m_objects[v4].timer == 0) {
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 2.5;
                    m_objects[v4].hitsLeft = 3;
                }
                if (m_objects[v4].frame == 0x1f && m_objects[v4].timer == 0) {
                    m_objectVar2[v4] = 1;
                }
                if (m_objects[v4].frame == 0x25 && m_objects[v4].timer == 0) {
                    m_playSound = 0x14;
                    l50.type = kObj236Effect;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = m_objects[v4].y;
                    l50.scale = 2;
                    l50.layer = 1;
                    l50.keep = 1;
                    l50.facing = m_objects[v4].facing;
                    SpawnObject(&l50);
                    m_playVoice = 2;
                }
                if (m_objects[v4].frame > 0x26) {
                    m_objects[v4].vx -= 0.045;
                    if (m_objects[v4].vx < 0.0) {
                        m_objects[v4].vx = 0.0;
                    }
                }
                if ((m_objects[v4].x - (*m_opponent)->x < 150.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 150.0 && m_objects[v4].facing == 1) && m_objectVar2[v4] != 0 && m_objects[v4].frame < 0x23) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x23;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2 && m_objectVar1[v4] < 8) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0x1b && m_objectVar1[v4] < 1) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 5;
                    }
                    if (m_objects[v4].frame == 0x23 && m_objectVar3[v4] < 1) {
                        m_objects[v4].frame = m_objects[v4].frame - 8;
                        m_objectVar3[v4]++;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObjDoubleLeap:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[v4].frame > 4 && m_objects[v4].frame < 0x1b && (m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 50.0 && m_objects[v4].facing == 1)) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x1b;
                    break;
                }
                if ((m_objects[v4].frame == 0x1e || m_objects[v4].frame == 0x26 || m_objects[v4].frame == 0x2f) && m_objects[v4].timer == 0) {
                    m_playSound = 0x15;
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].y < 0.0) {
                    m_objects[v4].vy += 0.035;
                    if (m_objects[v4].y + m_objects[v4].vy > 0.0 && m_objects[v4].frame < 0x37) {
                        m_objects[v4].timer = 0;
                        m_objects[v4].frame = 0x37;
                        m_objects[v4].y = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].vx = 0.0;
                        break;
                    }
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2 && m_objectVar1[v4] < 8) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0x1b && m_objectVar1[v4] < 0xd) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 5;
                    }
                    if (m_objects[v4].frame == 0x2d) {
                        m_objects[v4].vx = 1.0;
                        m_objects[v4].vy = -1.5;
                    }
                    if (m_objects[v4].frame == 0x37) {
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObjDouble214:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[v4].frame == 6) {
                    m_objects[v4].vx = 0.6;
                }
                if ((m_objects[v4].x - (*m_opponent)->x < 50.0 && m_objects[v4].facing == -1 || (*m_opponent)->x - m_objects[v4].x < 50.0 && m_objects[v4].facing == 1) && m_objects[v4].frame > 5 && m_objects[v4].frame < 0xe) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0xe;
                    m_objects[v4].vx = 0.0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 2 && m_objectVar1[v4] < 8) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = m_objects[v4].frame - 2;
                    }
                    if (m_objects[v4].frame == 0xe && m_objectVar2[v4] < 5) {
                        m_objectVar2[v4]++;
                        m_objects[v4].frame = 6;
                        break;
                    }
                    if (m_objects[v4].frame == 0xe) {
                        m_objects[v4].vx = 0.0;
                    }
                    if (m_objects[v4].frame == 0x15) {
                        l50.type = kObjDoubleEruption;
                        l50.x = (double)((int)m_objects[v4].x + m_objects[v4].facing * 0x32);
                        l50.y = 0.0;
                        l50.scale = 2;
                        l50.layer = 1;
                        l50.keep = 1;
                        l50.facing = facing;
                        SpawnObject(&l50);
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame = 0;
                        m_objects[v4].timer = 0;
                        m_objects[v4].vx = 0.0;
                        m_objects[v4].vy = 0.0;
                        m_objects[v4].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObj21436GroundEffect:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObj21436Strike1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObj21436ExtraPillar:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 0;
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
            case kObj21436Strike2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObj21436Strike3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObjDoubleEruption:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 1;
                }
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    l50.type = kObjDoublePillar;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 2;
                    l50.keep = 1;
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
            case kObjDoublePillar:
                if (m_objects[v4].frame == 0) {
                    m_objects[v4].hitsLeft = 2;
                }
                if (m_objects[v4].hitsLeft == 0 && m_objects[v4].frame < 0x2f) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 0x2f;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame == 0x2f && m_objectVar1[v4] < 3) {
                        m_objectVar1[v4]++;
                        m_objects[v4].frame = 0x20;
                        m_objects[v4].attackResult = 0;
                    }
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjDoubleVanish:
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    if (m_objects[v4].frame >= v58) {
                        RemoveObject(v4);
                    }
                }
                break;
            case kObjLv4Strike1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 7.0;
                    m_objects[v4].vy = -3.5;
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
            case kObjLv4Strike2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 7.0;
                    m_objects[v4].vy = -3.5;
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
            case kObjLv4Strike3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 3.5;
                    m_objects[v4].vy = -7.0;
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
            case kObjLv4Strike4:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].hitsLeft = 1;
                    m_objects[v4].vx = 3.5;
                    m_objects[v4].vy = -7.0;
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
            case kObjLv4Figure1:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 4.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_patternVar1 = 1;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = -4.0;
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
            case kObjLv4Figure2:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 6.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -6.0;
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
            case kObjLv4Figure3:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = 4.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                    m_patternVar1 = 1;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 4.0;
                    m_objects[v4].vy = -4.0;
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
            case kObjLv4Figure4:
                if (m_objects[v4].frame == 0 && m_objects[v4].timer == 0) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = 6.0;
                }
                if (m_objects[v4].y > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].y = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].frame = 1;
                    m_objects[v4].timer = 0;
                }
                if (frame == 0x18 && m_objects[v4].frame == 1) {
                    m_objects[v4].frame = 2;
                    m_objects[v4].timer = 0;
                    break;
                }
                if (m_objects[v4].frame == 2) {
                    m_objects[v4].vx = 2.0;
                    m_objects[v4].vy = -6.0;
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
            case kObjLv4Blast:
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
            case kObjOrbBurst3:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
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
            case kObjOrbBurst6:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
            case kObjOrbSmall:
                m_objects[v4].vy += 0.035;
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objectVar2[v4] = (WORD)Random(0x5a, 0x61);
                    m_objects[v4].SetVelocity((double)-m_objectVar2[v4], (WORD)Random(0, 5) * 0.1 + 3.2);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbCaught;
                    m_modeTimer += 0xa;
                    if (m_modeTimer > 0x4ec) {
                        m_modeTimer = 0x4ec;
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbOnGround;
                    m_objects[v4].layer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame == 1) {
                        m_objects[v4].frame--;
                    }
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case kObjOrbMedium:
                m_objects[v4].vy += 0.035;
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objectVar2[v4] = (WORD)Random(0x5a, 0x64);
                    m_objects[v4].SetVelocity((double)-m_objectVar2[v4], (WORD)Random(0, 5) * 0.1 + 2.2);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbCaught;
                    m_modeTimer += 0x1e;
                    if (m_modeTimer > 0x4ec) {
                        m_modeTimer = 0x4ec;
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbOnGround;
                    m_objects[v4].layer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case kObjOrbLarge:
                m_objects[v4].vy += 0.035;
                if (m_objectVar1[v4] == 0) {
                    m_objectVar1[v4]++;
                    m_objectVar2[v4] = (WORD)Random(0x5a, 0x64);
                    m_objects[v4].SetVelocity((double)-m_objectVar2[v4], (WORD)Random(0, 5) * 0.1 + 2.8);
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].frame == 0) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 1;
                    break;
                }
                if (m_objects[v4].vy > 0.0 && m_objects[v4].x - x < 15.0 && m_objects[v4].x - x > -15.0 && m_objects[v4].y - y < 0.0 && m_objects[v4].y - y > -50.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbCaught;
                    m_modeTimer += 0x32;
                    if (m_modeTimer > 0x4ec) {
                        m_modeTimer = 0x4ec;
                    }
                    break;
                }
                if (m_objects[v4].frame > 0 && m_objects[v4].y >= 0.0) {
                    m_objects[v4].vx = 0.0;
                    m_objects[v4].vy = 0.0;
                    m_objects[v4].frame = 0;
                    m_objects[v4].timer = 0;
                    m_objects[v4].pattern = kObjOrbOnGround;
                    m_objects[v4].layer = 0;
                    break;
                }
                m_objects[v4].timer++;
                if (m_objects[v4].timer >= v54) {
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame++;
                    m_objects[v4].attackResult = 0;
                    if (m_objects[v4].frame >= v58) {
                        m_objects[v4].frame--;
                    }
                }
                break;
            case kObjOrbCaught:
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
            case kObjOrbOnGround:
                if (m_objects[v4].frame == 4 && m_objects[v4].x - x > -15.0 && m_objects[v4].x - x < 15.0 && y == 0.0) {
                    m_modeTimer += 5;
                    if (m_modeTimer > 0x4ec) {
                        m_modeTimer = 0x4ec;
                    }
                    m_objects[v4].timer = 0;
                    m_objects[v4].frame = 7;
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
            case kObjOrbBurst14:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbLarge;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
            case kObjOrbBurst5:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
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
            case kObjOrbBurst9:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbLarge;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
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
            case kObjOrbBurst10:
                if (m_objects[v4].frame == 2 && m_objects[v4].timer == 0) {
                    l50.type = kObjOrbSmall;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbMedium;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    SpawnObject(&l50);
                    l50.type = kObjOrbLarge;
                    l50.x = (double)(int)m_objects[v4].x;
                    l50.y = (double)(int)m_objects[v4].y;
                    l50.facing = m_objects[v4].facing;
                    l50.layer = 1;
                    l50.scale = 0;
                    SpawnObject(&l50);
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
