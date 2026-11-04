// CIkumi (0x6a59c0-0x6be9bf).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CIkumi::CIkumi(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

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
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
}

void CIkumi::Reset()
{
    int i;

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
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
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
    int box;
    PatternFrame* frameData; // the frame's boxes and attack values being read
    EffectFrame* sprite; // the frame's sprite and timing being read
    int j;
    int i;
    int frameCount;
    int action; // the pattern the record is for
    int patternCount;

    CFile file("ikumi\\ikumi2.pat", 1);
    patternCount = file.ReadInt();
    i = 0;
    for (; i < patternCount; i++) {
        action = file.ReadInt();
        m_altPatterns[action].level = file.ReadInt();
        m_altPatterns[action].cancelLevel = file.ReadInt();
        m_altAnims[action].frameCount = file.ReadInt();
        frameCount = m_altAnims[action].frameCount;
        (TOPTR(PatternData*, TOINT(int, (char*)m_altPatterns) + action * 8))->Alloc(frameCount);
        (TOPTR(EffectAnim*, TOINT(int, (char*)m_altAnims) + action * 8))->Alloc(frameCount);
        j = 0;
        for (; j < frameCount; j++) {
            sprite = &m_altAnims[action].frames[j];
            frameData = &m_altPatterns[action].frames[j];
            sprite->duration = (short)file.ReadInt() * 3;
            sprite->surface = file.ReadInt();
            sprite->width = file.ReadInt();
            sprite->height = file.ReadInt();
            sprite->x = file.ReadInt();
            sprite->y = file.ReadInt();
            frameData->damage = file.ReadInt();
            frameData->flagsAA = file.ReadInt();
            frameData->airHitPattern = file.ReadInt();
            frameData->flagsB0 = file.ReadInt();
            frameData->untechTime = file.ReadInt();
            frameData->chipDamage = file.ReadInt();
            frameData->gaugeOnHit = file.ReadInt();
            frameData->gaugeOnGuard = file.ReadInt();
            frameData->hitVy = (short)file.ReadShort();
            frameData->hitVy = frameData->hitVy / 1e+02f;
            frameData->hitVx = (short)file.ReadShort();
            frameData->hitVx = frameData->hitVx / -1e+02f;
            frameData->hitSound = file.ReadShort();
            frameData->hitEffect = file.ReadShort();
            frameData->attackerHitstop = file.ReadInt();
            frameData->defenderHitstop = file.ReadInt();
            frameData->proration = file.ReadInt();
            frameData->groundHitPattern = file.ReadInt();
            file.Read((void*)&frameData->pushBox.left, 0x10);
            box = 0;
            for (; box < 2; box++) {
                file.Read((void*)((box << 4) + (char*)frameData), 0x10);
            }
            file.Read((void*)&frameData->attackBoxes[0].left, 0x10);
            box = 2;
            for (; box < 5; box++) {
                file.Read((void*)((box << 4) + (char*)frameData), 0x10);
            }
            box = 1;
            for (; box < 4; box++) {
                file.Read((void*)&frameData->attackBoxes[box].left, 0x10);
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

void CIkumi::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
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
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    if (m_modeTimer == 0) {
        sprite = *anims[0x2b].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(0x31 - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 0x10f - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_modeTimer > 0) {
        sprite = *anims[0x2c].frames;
        src = MakeRect(0, 0, sprite.width, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(0x31 - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 0x10f - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_modeTimer > 0) {
        sprite = *anims[0x2a].frames;
        src = MakeRect(0, 0, m_modeTimer * sprite.width / 0x4ec, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(0x31 - sprite.x, 0x1f - sprite.y, m_modeTimer * sprite.width / 0x4ec, sprite.height);
        } else {
            dst = MakeRect(sprite.x + 0x10f - m_modeTimer * sprite.width / 0x4ec, 0x1f - sprite.y, m_modeTimer * sprite.width / 0x4ec, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    }
    if (m_modeTimer == 0) {
        sprite = *anims[0x26].frames;
        src = MakeRect(0, 0, m_stockCharge * sprite.width / 0x64, sprite.height);
        if (m_side == 0) {
            dst = MakeRect(m_stocks * 8 + 0x32 - sprite.x, 0x1f - sprite.y, m_stockCharge * sprite.width / 0x64, sprite.height);
        } else {
            dst = MakeRect(0x10e - (m_stocks << 3) + sprite.x - sprite.width * m_stockCharge / 0x64, 0x1f - sprite.y, m_stockCharge * sprite.width / 0x64, sprite.height);
        }
        m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
        if (m_stocks > 0) {
            if (m_stocks > 0) {
                if (m_stocks < 9) {
                    sprite = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    sprite = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    sprite = *anims[0x27].frames;
                }
                src = MakeRect(0, 0, sprite.width, sprite.height);
                if (m_side == 0) {
                    dst = MakeRect(0x32 - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
                } else {
                    dst = MakeRect(sprite.x + 0x10e - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
                }
                m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
            }
            if (m_stocks > 1) {
                if (m_stocks < 9) {
                    sprite = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    sprite = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    sprite = *anims[0x27].frames;
                }
                src = MakeRect(0, 0, sprite.width, sprite.height);
                if (m_side == 0) {
                    dst = MakeRect(0x3a - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
                } else {
                    dst = MakeRect(sprite.x + 0x106 - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
                }
                m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
            }
            if (m_stocks > 2) {
                if (m_stocks < 9) {
                    sprite = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    sprite = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    sprite = *anims[0x27].frames;
                }
                src = MakeRect(0, 0, sprite.width, sprite.height);
                if (m_side == 0) {
                    dst = MakeRect(0x42 - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
                } else {
                    dst = MakeRect(sprite.x + 0xfe - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
                }
                m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
            }
            if (m_stocks > 3) {
                if (m_stocks < 9) {
                    sprite = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    sprite = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    sprite = *anims[0x27].frames;
                }
                src = MakeRect(0, 0, sprite.width, sprite.height);
                if (m_side == 0) {
                    dst = MakeRect(0x4a - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
                } else {
                    dst = MakeRect(sprite.x + 0xf6 - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
                }
                m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
            }
            if (m_stocks > 4) {
                if (m_stocks < 9) {
                    sprite = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    sprite = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    sprite = *anims[0x27].frames;
                }
                src = MakeRect(0, 0, sprite.width, sprite.height);
                if (m_side == 0) {
                    dst = MakeRect(0x52 - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
                } else {
                    dst = MakeRect(sprite.x + 0xee - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
                }
                m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
            }
            if (m_stocks > 5) {
                if (m_stocks < 9) {
                    sprite = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    sprite = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    sprite = *anims[0x27].frames;
                }
                src = MakeRect(0, 0, sprite.width, sprite.height);
                if (m_side == 0) {
                    dst = MakeRect(0x5a - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
                } else {
                    dst = MakeRect(sprite.x + 0xe6 - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
                }
                m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
            }
            if (m_stocks > 6) {
                if (m_stocks < 9) {
                    sprite = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    sprite = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    sprite = *anims[0x27].frames;
                }
                src = MakeRect(0, 0, sprite.width, sprite.height);
                if (m_side == 0) {
                    dst = MakeRect(0x62 - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
                } else {
                    dst = MakeRect(sprite.x + 0xde - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
                }
                m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
            }
            if (m_stocks > 7) {
                if (m_stocks < 9) {
                    sprite = *anims[0x29].frames;
                }
                if (m_stocks < 6) {
                    sprite = *anims[0x28].frames;
                }
                if (m_stocks < 3) {
                    sprite = *anims[0x27].frames;
                }
                src = MakeRect(0, 0, sprite.width, sprite.height);
                if (m_side == 0) {
                    dst = MakeRect(0x6a - sprite.x, 0x1f - sprite.y, sprite.width, sprite.height);
                } else {
                    dst = MakeRect(sprite.x + 0xd6 - sprite.width, 0x1f - sprite.y, sprite.width, sprite.height);
                }
                m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
            }
        }
    }
}

void CIkumi::PreUpdate()
{
    EffectDesc effect; // what CreateEffect or SpawnObject is to make
    InitEffectDesc((EffectDesc*)&effect);
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
            effect.type = kObjOrbBurst3;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = (*m_opponent)->y - 40.0;
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_orbBurstSpawned++;
        }
        if (pattern == kDashB || pattern == kDash2B) {
            effect.type = kObjOrbBurst5;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = (*m_opponent)->y - 40.0;
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_orbBurstSpawned++;
        }
        if (pattern == k236A || pattern == k236B || pattern == k623A || pattern == k623B) {
            effect.type = kObjOrbBurst6;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = (*m_opponent)->y - 40.0;
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_orbBurstSpawned++;
        }
        if (pattern == k236BStock3 || pattern == k236C || pattern == k236CStock3 || pattern == k623C || pattern == k623BStock3 || pattern == k623CStock3) {
            effect.type = kObjOrbBurst9;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = (*m_opponent)->y - 40.0;
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_orbBurstSpawned++;
        }
        if (pattern == k236BStock6 || pattern == k236CStock6 || pattern == k623BStock6 || pattern == k623CStock6) {
            effect.type = kObjOrbBurst10;
            effect.x = (double)(int)(*m_opponent)->x;
            effect.y = (*m_opponent)->y - 40.0;
            effect.scale = 0;
            effect.layer = 1;
            effect.facing = facing;
            SpawnObject(&effect);
            m_orbBurstSpawned++;
        }
    }
}

void CIkumi::UseAltPatterns(char on)
{
    int j;
    int i;

    if (on == 1 && m_altPatternsIn == 0) {
        anims = TOPTR(EffectAnim*, (int)m_altAnims);
        i = 0;
        for (; i < 0x40; i++) {
            m_objects[i].anims = TOPTR(EffectAnim*, (int)m_altAnims);
        }
        m_patterns = TOPTR(PatternData*, (int)m_altPatterns);
        m_altPatternsIn = 1;
        return;
    }
    if (on == 0 && m_altPatternsIn == 1) {
        anims = TOPTR(EffectAnim*, m_baseAnims);
        j = 0;
        for (; j < 0x40; j++) {
            m_objects[j].anims = TOPTR(EffectAnim*, m_baseAnims);
        }
        m_patterns = TOPTR(PatternData*, m_basePatterns);
        m_altPatternsIn = 0;
    }
}

void CIkumi::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CIkumi::ReadCommand()
{
    BYTE step; // how much of the motion has been read
    BYTE input; // its bits: 1 right, 2 left, 4 down, 8 up, 0x10-0x80 A-D
    int pos; // the entry of m_inputHistory read, oldest first

    m_command = kCmdNone;
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 110);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputC) != 0 && step == 9) {
            m_command = kCmd236236236C;
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 8) {
            if ((input & kInputC) != 0) {
                m_command = kCmd236236236C;
                return;
            }
            step = 9;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 7) {
            step = 8;
        }
        if ((input & kInputDirections) == kInputDown && step == 6) {
            step = 7;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 5) {
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
    pos = m_inputPos + (kInputHistoryLength - 135);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputButtons) != 0 && step == 7) {
            m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd4123641236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 5) {
            if ((input & kInputButtons) != 0) {
                m_command = ((input & (kInputB | kInputC | kInputD)) > 0) + kCmd4123641236A + ((input & (kInputC | kInputD)) > 0) + ((input & kInputD) > 0);
                return;
            }
            step = 8;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 6) {
            step = 7;
        }
        if ((input & kInputDirections) == 6 - (facing == -1) && step == 5) {
            step = 6;
        }
        if ((input & kInputDirections) == kInputLeft - (facing == -1) && step == 4) {
            step = 5;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 2) {
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
        if ((input & kInputDirections) == kInputDown && step == 0 && (m_gauge >= 0x3e8 || m_storedSuperLevel > 0)) {
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

void CIkumi::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == k41236CHold && m_hitsLeft > 1) {
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
                m_command = (WORD)Random(0, 3) + 0x78;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && dx < 150.0 && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
        }
        if (dx < 220.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = 0x5f;
                return;
            }
        }
        if (dx > 220.0) {
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
                if (dx > 120.0) {
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
                if (dx > 120.0) {
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
                m_command = (WORD)Random(0, 3) + 0x78;
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
                if (dx > 120.0) {
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
                    m_command = (WORD)Random(0, 3) + 0x78;
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
                    m_command = 0x28;
                    return;
                }
                if (dx > 140.0 && dx < 180.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = 0x29;
                    return;
                }
                if (dx > 200.0 && dx < 240.0 && m_cpuRoll < 0xd2 && m_cpuRoll > 0xbe) {
                    m_command = 0x2a;
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
                        m_command = (WORD)Random(0, 3) + 0x78;
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
                        m_command = (WORD)Random(0, 3) + 0x78;
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
                    m_command = (WORD)Random(0, 3) + 0x28;
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

void CIkumi::UpdateObjects()
{
    WORD frameCount; // frames in the object's animation
    WORD duration; // ticks the object's current frame lasts
    int slot; // the object being updated, an index into m_objects

    if (m_altPatternsIn == 1) {
        UpdateObjectsAlt();
        return;
    }
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
            case kObj623Effect:
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
            case kObj214GroundEffect:
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
            case kObj214Eruption:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.type = kObj214Pillar;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    effect.keep = 1;
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
            case kObj214Pillar:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].attackResult == 3 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot] = 1;
                    effect.type = kObjOrbBurst5;
                    effect.x = (double)(int)(*m_opponent)->x;
                    effect.y = (*m_opponent)->y - 40.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 0x2f) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x2f;
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
            case kObjThrowImpact:
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
            case kObj214EruptionStock3:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.type = kObj214PillarStock3;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    effect.keep = 1;
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
            case kObj214PillarStock3:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].attackResult == 3 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot] = 1;
                    effect.type = kObjOrbBurst5;
                    effect.x = (double)(int)(*m_opponent)->x;
                    effect.y = (*m_opponent)->y - 40.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 0x2f) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x2f;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 0x2f && m_objectVar1[slot] == 0) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 0x20;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214EruptionStock6:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.type = kObj214PillarStock6;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    effect.keep = 1;
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
            case kObj214PillarStock6:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 2;
                    m_objectVar1[slot] = 0;
                    m_objectVar2[slot] = 0;
                }
                if (m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 0x2f) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x2f;
                    break;
                }
                if (m_objects[slot].attackResult == 3 && m_objectVar2[slot] == 0) {
                    m_objectVar2[slot] = 1;
                    effect.type = kObjOrbBurst5;
                    effect.x = (double)(int)(*m_opponent)->x;
                    effect.y = (*m_opponent)->y - 40.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x2f && m_objectVar1[slot] < 3) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 0x20;
                        m_objects[slot].attackResult = 0;
                        m_objectVar2[slot] = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjModeStartAura:
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
            case kObjGrabSuperEffect1:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x28 && frame < 7) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabSuperEffect2:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x28 && frame < 7) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabSuperEffect3:
                if (m_objects[slot].timer == 0 && (m_objects[slot].frame == 0 || m_objects[slot].frame == 0xa || m_objects[slot].frame == 0x14 || m_objects[slot].frame == 0x1e)) {
                    effect.type = kObjGrabSuperSpark;
                    if ((WORD)Random(0, 0x64) < 0x32) {
                        effect.type = kObjGrabSuperSparkTall;
                    }
                    effect.x = (double)((int)m_objects[slot].x + -0x3c + (WORD)Random(0, 0x78));
                    effect.y = (double)((int)m_objects[slot].y - (WORD)Random(0, 0xa0));
                    effect.facing = m_objects[slot].facing;
                    if ((WORD)Random(0, 0x64) < 0x32) {
                        effect.facing = -m_objects[slot].facing;
                    }
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x28 && frame < 7) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabSuperSpark:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabSuperSparkTall:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjDouble236:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[slot].frame == 0x1b && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 2.5;
                    m_objects[slot].hitsLeft = 3;
                }
                if (m_objects[slot].frame == 0x1b && m_objects[slot].timer == 0) {
                    m_objectVar2[slot] = 1;
                }
                if (m_objects[slot].frame == 0x25 && m_objects[slot].timer == 0) {
                    m_playSound = 0x14;
                    effect.type = kObj236Effect;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                    m_playVoice = 2;
                }
                if (m_objects[slot].frame > 0x26) {
                    m_objects[slot].vx -= 0.07;
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                    }
                }
                if ((m_objects[slot].x - (*m_opponent)->x < 150.0 && m_objects[slot].facing == -1 || (*m_opponent)->x - m_objects[slot].x < 150.0 && m_objects[slot].facing == 1) && m_objectVar2[slot] != 0 && m_objects[slot].frame < 0x23) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x23;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 && m_objectVar1[slot] < 0) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 0xc) {
                        m_objects[slot].frame = 0x1b;
                    }
                    if (m_objects[slot].frame == 0x1b && m_objectVar1[slot] < 0) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 5;
                    }
                    if (m_objects[slot].frame == 0x23 && m_objectVar3[slot] < 1) {
                        m_objects[slot].frame = m_objects[slot].frame - 8;
                        m_objectVar3[slot]++;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObjDoubleLeap:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[slot].frame > 4 && m_objects[slot].frame < 0x1b && (m_objects[slot].x - (*m_opponent)->x < 50.0 && m_objects[slot].facing == -1 || (*m_opponent)->x - m_objects[slot].x < 50.0 && m_objects[slot].facing == 1)) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x1b;
                    break;
                }
                if ((m_objects[slot].frame == 0x1e || m_objects[slot].frame == 0x26 || m_objects[slot].frame == 0x2f) && m_objects[slot].timer == 0) {
                    m_playSound = 0x15;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                    if (m_objects[slot].y + m_objects[slot].vy > 0.0 && m_objects[slot].frame < 0x37) {
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = 0x37;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 && m_objectVar1[slot] < 8) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 0x1b && m_objectVar1[slot] < 0xd) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 5;
                    }
                    if (m_objects[slot].frame == 0x2d) {
                        m_objects[slot].vx = 1.0;
                        m_objects[slot].vy = -1.5;
                    }
                    if (m_objects[slot].frame == 0x37) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObjDouble214:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[slot].frame == 6) {
                    m_objects[slot].vx = 0.6;
                }
                if ((m_objects[slot].x - (*m_opponent)->x < 50.0 && m_objects[slot].facing == -1 || (*m_opponent)->x - m_objects[slot].x < 50.0 && m_objects[slot].facing == 1) && m_objects[slot].frame > 5 && m_objects[slot].frame < 0xe) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0xe;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 && m_objectVar1[slot] < 8) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 0xe && m_objectVar2[slot] < 5) {
                        m_objectVar2[slot]++;
                        m_objects[slot].frame = 6;
                        break;
                    }
                    if (m_objects[slot].frame == 0xe) {
                        m_objects[slot].vx = 0.0;
                    }
                    if (m_objects[slot].frame == 0x15) {
                        effect.type = kObjDoubleEruption;
                        effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 0x32);
                        effect.y = 0.0;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.keep = 1;
                        effect.facing = facing;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObj21436GroundEffect:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj21436Strike1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObj21436ExtraPillar:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 0;
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
            case kObj21436Strike2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObj21436Strike3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObjDoubleEruption:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.type = kObjDoublePillar;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    effect.keep = 1;
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
            case kObjDoublePillar:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 4;
                }
                if (m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 0x2f) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x2f;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x2f && m_objectVar1[slot] < 3) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 0x20;
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjDoubleVanish:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Strike1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 7.0;
                    m_objects[slot].vy = -3.5;
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
            case kObjLv4Strike2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 7.0;
                    m_objects[slot].vy = -3.5;
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
            case kObjLv4Strike3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 3.5;
                    m_objects[slot].vy = -7.0;
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
            case kObjLv4Strike4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 3.5;
                    m_objects[slot].vy = -7.0;
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
            case kObjLv4Figure1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 4.0;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_patternVar1 = 1;
                }
                if (frame == 0x18 && m_objects[slot].frame == 1) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].frame == 2) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = -4.0;
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
            case kObjLv4Figure2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = 6.0;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                }
                if (frame == 0x18 && m_objects[slot].frame == 1) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].frame == 2) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = -6.0;
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
            case kObjLv4Figure3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 4.0;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_patternVar1 = 1;
                }
                if (frame == 0x18 && m_objects[slot].frame == 1) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].frame == 2) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = -4.0;
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
            case kObjLv4Figure4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = 6.0;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                }
                if (frame == 0x18 && m_objects[slot].frame == 1) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].frame == 2) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = -6.0;
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
            case kObjLv4Blast:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].attackResult > 0) {
                    m_patternVar2 = 1;
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
            case kObjOrbBurst3:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
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
            case kObjOrbBurst6:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
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
            case kObjOrbSmall:
                m_objects[slot].vy += 0.035;
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objectVar2[slot] = (WORD)Random(0x5a, 0x61);
                    m_objects[slot].SetVelocity((double)-m_objectVar2[slot], (WORD)Random(0, 5) * 0.1 + 3.2);
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 1;
                    break;
                }
                if (m_objects[slot].frame > 0 && m_objects[slot].x - x < 15.0 && m_objects[slot].x - x > -15.0 && m_objects[slot].y - y < 0.0 && m_objects[slot].y - y > -50.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbCaught;
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
                if (m_objects[slot].frame > 0 && m_objects[slot].y >= 0.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbOnGround;
                    m_objects[slot].layer = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObjOrbMedium:
                m_objects[slot].vy += 0.035;
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objectVar2[slot] = (WORD)Random(0x5a, 0x64);
                    m_objects[slot].SetVelocity((double)-m_objectVar2[slot], (WORD)Random(0, 5) * 0.1 + 2.2);
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 1;
                    break;
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].x - x < 15.0 && m_objects[slot].x - x > -15.0 && m_objects[slot].y - y < 0.0 && m_objects[slot].y - y > -50.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbCaught;
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
                if (m_objects[slot].frame > 0 && m_objects[slot].y >= 0.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbOnGround;
                    m_objects[slot].layer = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObjOrbLarge:
                m_objects[slot].vy += 0.035;
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objectVar2[slot] = (WORD)Random(0x5a, 0x64);
                    m_objects[slot].SetVelocity((double)-m_objectVar2[slot], (WORD)Random(0, 5) * 0.1 + 2.8);
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 1;
                    break;
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].x - x < 15.0 && m_objects[slot].x - x > -15.0 && m_objects[slot].y - y < 0.0 && m_objects[slot].y - y > -50.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbCaught;
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
                if (m_objects[slot].frame > 0 && m_objects[slot].y >= 0.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbOnGround;
                    m_objects[slot].layer = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObjOrbCaught:
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
            case kObjOrbOnGround:
                if (m_objects[slot].frame == 4 && m_objects[slot].x - x > -15.0 && m_objects[slot].x - x < 15.0 && y == 0.0) {
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
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 7;
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
            case kObjOrbBurst14:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbLarge;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
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
            case kObjOrbBurst5:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
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
            case kObjOrbBurst9:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbLarge;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
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
            case kObjOrbBurst10:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbLarge;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
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
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x + facing * 0x17);
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
                    effect.x = (double)((int)x - facing * 0xe);
                    effect.y = (double)((int)y - 0x1a);
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
                    effect.x = (double)((int)x + facing * 0x1e);
                    effect.y = (double)((int)y - 0x28);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x - facing * 0x19);
                    effect.y = (double)((int)y - 0x50);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x - facing * 0x23);
                    effect.y = (double)((int)y - 0x2a);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x - facing * 0x12);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x + facing * 2);
                    effect.y = (double)((int)y - 0x41);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
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

void CIkumi::UpdateObjectsAlt()
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
            case kObj623Effect:
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
            case kObj214GroundEffect:
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
            case kObj214Eruption:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.type = kObj214Pillar;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    effect.keep = 1;
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
            case kObj214Pillar:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].attackResult == 3 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot] = 1;
                    effect.type = kObjOrbBurst5;
                    effect.x = (double)(int)(*m_opponent)->x;
                    effect.y = (*m_opponent)->y - 40.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 0x2f) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x2f;
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
            case kObjThrowImpact:
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
            case kObj214EruptionStock3:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.type = kObj214PillarStock3;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    effect.keep = 1;
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
            case kObj214PillarStock3:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objectVar1[slot] = 0;
                }
                if (m_objects[slot].attackResult == 3 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot] = 1;
                    effect.type = kObjOrbBurst5;
                    effect.x = (double)(int)(*m_opponent)->x;
                    effect.y = (*m_opponent)->y - 40.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                }
                if (m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 0x2f) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x2f;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 0x2f && m_objectVar1[slot] == 0) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 0x20;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj214EruptionStock6:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.type = kObj214PillarStock6;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    effect.keep = 1;
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
            case kObj214PillarStock6:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 2;
                    m_objectVar1[slot] = 0;
                    m_objectVar2[slot] = 0;
                }
                if (m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 0x2f) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x2f;
                    break;
                }
                if (m_objects[slot].attackResult == 3 && m_objectVar2[slot] == 0) {
                    m_objectVar2[slot] = 1;
                    effect.type = kObjOrbBurst5;
                    effect.x = (double)(int)(*m_opponent)->x;
                    effect.y = (*m_opponent)->y - 40.0;
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x2f && m_objectVar1[slot] < 3) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 0x20;
                        m_objects[slot].attackResult = 0;
                        m_objectVar2[slot] = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjModeStartAura:
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
            case kObjGrabSuperEffect1:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x28 && frame < 7) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabSuperEffect2:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x28 && frame < 7) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabSuperEffect3:
                if (m_objects[slot].timer == 0 && (m_objects[slot].frame == 0 || m_objects[slot].frame == 0xa || m_objects[slot].frame == 0x14 || m_objects[slot].frame == 0x1e)) {
                    effect.type = kObjGrabSuperSpark;
                    if ((WORD)Random(0, 0x64) < 0x32) {
                        effect.type = kObjGrabSuperSparkTall;
                    }
                    effect.x = (double)((int)m_objects[slot].x + -0x3c + (WORD)Random(0, 0x78));
                    effect.y = (double)((int)m_objects[slot].y - (WORD)Random(0, 0xa0));
                    effect.facing = m_objects[slot].facing;
                    if ((WORD)Random(0, 0x64) < 0x32) {
                        effect.facing = -m_objects[slot].facing;
                    }
                    effect.layer = 1;
                    effect.scale = 2;
                    SpawnObject(&effect);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x28 && frame < 7) {
                        m_objects[slot].frame = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabSuperSpark:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjGrabSuperSparkTall:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjDouble236:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[slot].frame == 0x1b && m_objects[slot].timer == 0) {
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 2.5;
                    m_objects[slot].hitsLeft = 3;
                }
                if (m_objects[slot].frame == 0x1f && m_objects[slot].timer == 0) {
                    m_objectVar2[slot] = 1;
                }
                if (m_objects[slot].frame == 0x25 && m_objects[slot].timer == 0) {
                    m_playSound = 0x14;
                    effect.type = kObj236Effect;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = m_objects[slot].y;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.keep = 1;
                    effect.facing = m_objects[slot].facing;
                    SpawnObject(&effect);
                    m_playVoice = 2;
                }
                if (m_objects[slot].frame > 0x26) {
                    m_objects[slot].vx -= 0.045;
                    if (m_objects[slot].vx < 0.0) {
                        m_objects[slot].vx = 0.0;
                    }
                }
                if ((m_objects[slot].x - (*m_opponent)->x < 150.0 && m_objects[slot].facing == -1 || (*m_opponent)->x - m_objects[slot].x < 150.0 && m_objects[slot].facing == 1) && m_objectVar2[slot] != 0 && m_objects[slot].frame < 0x23) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x23;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 && m_objectVar1[slot] < 8) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 0x1b && m_objectVar1[slot] < 1) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 5;
                    }
                    if (m_objects[slot].frame == 0x23 && m_objectVar3[slot] < 1) {
                        m_objects[slot].frame = m_objects[slot].frame - 8;
                        m_objectVar3[slot]++;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObjDoubleLeap:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[slot].frame > 4 && m_objects[slot].frame < 0x1b && (m_objects[slot].x - (*m_opponent)->x < 50.0 && m_objects[slot].facing == -1 || (*m_opponent)->x - m_objects[slot].x < 50.0 && m_objects[slot].facing == 1)) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x1b;
                    break;
                }
                if ((m_objects[slot].frame == 0x1e || m_objects[slot].frame == 0x26 || m_objects[slot].frame == 0x2f) && m_objects[slot].timer == 0) {
                    m_playSound = 0x15;
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].y < 0.0) {
                    m_objects[slot].vy += 0.035;
                    if (m_objects[slot].y + m_objects[slot].vy > 0.0 && m_objects[slot].frame < 0x37) {
                        m_objects[slot].timer = 0;
                        m_objects[slot].frame = 0x37;
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        break;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 && m_objectVar1[slot] < 8) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 0x1b && m_objectVar1[slot] < 0xd) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 5;
                    }
                    if (m_objects[slot].frame == 0x2d) {
                        m_objects[slot].vx = 1.0;
                        m_objects[slot].vy = -1.5;
                    }
                    if (m_objects[slot].frame == 0x37) {
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObjDouble214:
                if (pattern > kLastFreeAction && pattern < kFirstGuard) {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].pattern = kObjDoubleVanish;
                    break;
                }
                if (m_objects[slot].frame == 6) {
                    m_objects[slot].vx = 0.6;
                }
                if ((m_objects[slot].x - (*m_opponent)->x < 50.0 && m_objects[slot].facing == -1 || (*m_opponent)->x - m_objects[slot].x < 50.0 && m_objects[slot].facing == 1) && m_objects[slot].frame > 5 && m_objects[slot].frame < 0xe) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0xe;
                    m_objects[slot].vx = 0.0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2 && m_objectVar1[slot] < 8) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = m_objects[slot].frame - 2;
                    }
                    if (m_objects[slot].frame == 0xe && m_objectVar2[slot] < 5) {
                        m_objectVar2[slot]++;
                        m_objects[slot].frame = 6;
                        break;
                    }
                    if (m_objects[slot].frame == 0xe) {
                        m_objects[slot].vx = 0.0;
                    }
                    if (m_objects[slot].frame == 0x15) {
                        effect.type = kObjDoubleEruption;
                        effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 0x32);
                        effect.y = 0.0;
                        effect.scale = 2;
                        effect.layer = 1;
                        effect.keep = 1;
                        effect.facing = facing;
                        SpawnObject(&effect);
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objects[slot].timer = 0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].pattern = kObjDoubleVanish;
                    }
                }
                break;
            case kObj21436GroundEffect:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj21436Strike1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObj21436ExtraPillar:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 0;
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
            case kObj21436Strike2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObj21436Strike3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 9;
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
            case kObjDoubleEruption:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 1;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    effect.type = kObjDoublePillar;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 2;
                    effect.keep = 1;
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
            case kObjDoublePillar:
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].hitsLeft = 2;
                }
                if (m_objects[slot].hitsLeft == 0 && m_objects[slot].frame < 0x2f) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 0x2f;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame == 0x2f && m_objectVar1[slot] < 3) {
                        m_objectVar1[slot]++;
                        m_objects[slot].frame = 0x20;
                        m_objects[slot].attackResult = 0;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjDoubleVanish:
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjLv4Strike1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 7.0;
                    m_objects[slot].vy = -3.5;
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
            case kObjLv4Strike2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 7.0;
                    m_objects[slot].vy = -3.5;
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
            case kObjLv4Strike3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 3.5;
                    m_objects[slot].vy = -7.0;
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
            case kObjLv4Strike4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 3.5;
                    m_objects[slot].vy = -7.0;
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
            case kObjLv4Figure1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 4.0;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_patternVar1 = 1;
                }
                if (frame == 0x18 && m_objects[slot].frame == 1) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].frame == 2) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = -4.0;
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
            case kObjLv4Figure2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = 6.0;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                }
                if (frame == 0x18 && m_objects[slot].frame == 1) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].frame == 2) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = -6.0;
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
            case kObjLv4Figure3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = 4.0;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                    m_patternVar1 = 1;
                }
                if (frame == 0x18 && m_objects[slot].frame == 1) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].frame == 2) {
                    m_objects[slot].vx = 4.0;
                    m_objects[slot].vy = -4.0;
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
            case kObjLv4Figure4:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = 6.0;
                }
                if (m_objects[slot].y > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].y = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].timer = 0;
                }
                if (frame == 0x18 && m_objects[slot].frame == 1) {
                    m_objects[slot].frame = 2;
                    m_objects[slot].timer = 0;
                    break;
                }
                if (m_objects[slot].frame == 2) {
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = -6.0;
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
            case kObjLv4Blast:
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
            case kObjOrbBurst3:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
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
            case kObjOrbBurst6:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
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
            case kObjOrbSmall:
                m_objects[slot].vy += 0.035;
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objectVar2[slot] = (WORD)Random(0x5a, 0x61);
                    m_objects[slot].SetVelocity((double)-m_objectVar2[slot], (WORD)Random(0, 5) * 0.1 + 3.2);
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 1;
                    break;
                }
                if (m_objects[slot].frame > 0 && m_objects[slot].x - x < 15.0 && m_objects[slot].x - x > -15.0 && m_objects[slot].y - y < 0.0 && m_objects[slot].y - y > -50.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbCaught;
                    m_modeTimer += 0xa;
                    if (m_modeTimer > 0x4ec) {
                        m_modeTimer = 0x4ec;
                    }
                    break;
                }
                if (m_objects[slot].frame > 0 && m_objects[slot].y >= 0.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbOnGround;
                    m_objects[slot].layer = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 1) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObjOrbMedium:
                m_objects[slot].vy += 0.035;
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objectVar2[slot] = (WORD)Random(0x5a, 0x64);
                    m_objects[slot].SetVelocity((double)-m_objectVar2[slot], (WORD)Random(0, 5) * 0.1 + 2.2);
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 1;
                    break;
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].x - x < 15.0 && m_objects[slot].x - x > -15.0 && m_objects[slot].y - y < 0.0 && m_objects[slot].y - y > -50.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbCaught;
                    m_modeTimer += 0x1e;
                    if (m_modeTimer > 0x4ec) {
                        m_modeTimer = 0x4ec;
                    }
                    break;
                }
                if (m_objects[slot].frame > 0 && m_objects[slot].y >= 0.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbOnGround;
                    m_objects[slot].layer = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObjOrbLarge:
                m_objects[slot].vy += 0.035;
                if (m_objectVar1[slot] == 0) {
                    m_objectVar1[slot]++;
                    m_objectVar2[slot] = (WORD)Random(0x5a, 0x64);
                    m_objects[slot].SetVelocity((double)-m_objectVar2[slot], (WORD)Random(0, 5) * 0.1 + 2.8);
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].frame == 0) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 1;
                    break;
                }
                if (m_objects[slot].vy > 0.0 && m_objects[slot].x - x < 15.0 && m_objects[slot].x - x > -15.0 && m_objects[slot].y - y < 0.0 && m_objects[slot].y - y > -50.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbCaught;
                    m_modeTimer += 0x32;
                    if (m_modeTimer > 0x4ec) {
                        m_modeTimer = 0x4ec;
                    }
                    break;
                }
                if (m_objects[slot].frame > 0 && m_objects[slot].y >= 0.0) {
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].pattern = kObjOrbOnGround;
                    m_objects[slot].layer = 0;
                    break;
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame--;
                    }
                }
                break;
            case kObjOrbCaught:
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
            case kObjOrbOnGround:
                if (m_objects[slot].frame == 4 && m_objects[slot].x - x > -15.0 && m_objects[slot].x - x < 15.0 && y == 0.0) {
                    m_modeTimer += 5;
                    if (m_modeTimer > 0x4ec) {
                        m_modeTimer = 0x4ec;
                    }
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 7;
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
            case kObjOrbBurst14:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbLarge;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
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
            case kObjOrbBurst5:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
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
            case kObjOrbBurst9:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbLarge;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
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
            case kObjOrbBurst10:
                if (m_objects[slot].frame == 2 && m_objects[slot].timer == 0) {
                    effect.type = kObjOrbSmall;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbMedium;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    SpawnObject(&effect);
                    effect.type = kObjOrbLarge;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = m_objects[slot].facing;
                    effect.layer = 1;
                    effect.scale = 0;
                    SpawnObject(&effect);
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
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x + facing * 0x17);
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
                    effect.x = (double)((int)x - facing * 0xe);
                    effect.y = (double)((int)y - 0x1a);
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
                    effect.x = (double)((int)x + facing * 0x1e);
                    effect.y = (double)((int)y - 0x28);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardSmall;
                    effect.x = (double)((int)x - facing * 0x19);
                    effect.y = (double)((int)y - 0x50);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x - facing * 0x23);
                    effect.y = (double)((int)y - 0x2a);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x - facing * 0x12);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
                    effect.x = (double)((int)x + facing * 2);
                    effect.y = (double)((int)y - 0x41);
                    effect.scale = 0;
                    effect.layer = 1;
                    effect.facing = facing;
                    SpawnObject(&effect);
                    effect.type = kObjShardLarge;
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
