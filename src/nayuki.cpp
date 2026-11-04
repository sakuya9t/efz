// CNayuki (0x461090-0x46d96f): the character class whose files are in nayuki\ in the game
// folder (nayuki.dat sprites, nayuki.pat patterns, wave\).
// Its constructor sets the folder name CPlayer's loaders use; its other methods override
// CPlayer's virtual ones (efz.h says what each does).
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "efz.h"

CNayuki::CNayuki(PTR32(CPlayer)* opponent, CGame* game, CGraphics* graphics, CInput* input, CSound* sound, BYTE side)
    : CPlayer(opponent, game, graphics, input, sound, side)
{
    int i;

    strcpy(m_name, "nayuki");
    lastSurface = 0x1fd;
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_warmUp = 3;
    m_upperEmitterX = 0;
    m_lowerEmitterX = 0;
    m_upperEmitterY = 0;
    m_lowerEmitterY = 0;
    m_pointX[0] = -5;
    m_pointY[0] = -0x3a;
    m_pointX[1] = 0x12;
    m_pointY[1] = 0;
    m_pointX[2] = 0xe;
    m_pointY[2] = -0x11;
    m_pointX[3] = 0x14;
    m_pointY[3] = -0x19;
    m_pointX[4] = 0x24;
    m_pointY[4] = -0x2c;
    m_resultPictures = 7;
    m_rivals[0] = 1;
    m_rivals[1] = 6;
    m_rivals[2] = 0x10;
    m_rivals[0xa] = 0xa;
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
}

void CNayuki::Reset()
{
    int i;

    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    m_encasedBreakOut = 0;
    m_warmUp = 3;
    m_upperEmitterX = 0;
    m_lowerEmitterX = 0;
    m_upperEmitterY = 0;
    m_lowerEmitterY = 0;
    m_pointX[0] = -5;
    m_pointY[0] = -0x3a;
    m_pointX[1] = 0x12;
    m_pointY[1] = 0;
    m_pointX[2] = 0xe;
    m_pointY[2] = -0x11;
    m_pointX[3] = 0x14;
    m_pointY[3] = -0x19;
    m_pointX[4] = 0x24;
    m_pointY[4] = -0x2c;
    i = 0;
    for (; i < 0x40; i++) {
        m_objectVar1[i] = 0;
        m_objectVar2[i] = 0;
        m_objectVar3[i] = 0;
    }
    CPlayer::Reset();
}

void CNayuki::StartPattern()
{
    m_patternVar1 = 0;
    m_patternVar2 = 0;
    m_patternVar3 = 0;
    CPlayer::StartPattern();
}

void CNayuki::RemoveObject(short slot)
{
    m_objectVar1[slot] = 0;
    m_objectVar2[slot] = 0;
    m_objectVar3[slot] = 0;
    CPlayer::RemoveObject(slot);
}

void CNayuki::Move()
{
    MoveOnGround();
}

void CNayuki::StartCommand()
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
        if (m_hp < 0xd05 && m_command == kCmdC236236 && m_gauge >= 0xbb8 && y == 0.0 && m_attackResult != 6 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_patterns[pattern].cancelLevel <= m_patterns[kLv4].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = kLv4;
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
        if (m_warmUp > 0) {
            if (m_command == kCmd41236C && (m_rfGauge >= 500.0 || m_rfBlue > 0) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236C].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k41236C;
                return;
            }
            if ((m_command == kCmd41236B || m_command == kCmd41236C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236B].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k41236B;
                return;
            }
            if (m_command == kCmd41236A && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k41236A].level) {
                StartPattern();
                ClearBufferedPress();
                pattern = k41236A;
                return;
            }
        }
        if ((m_command == kCmd214A || m_command == kCmd214B || m_command == kCmd214C) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && (m_patterns[pattern].cancelLevel <= m_patterns[k214Stance].level + (m_warmUp > 6) * 0xa || pattern == k41236A || pattern == k41236B)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k214Stance;
            return;
        }
        if (m_warmUp > 1) {
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
        }
        if (m_command == kCmd236D && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && m_patterns[pattern].cancelLevel <= m_patterns[k236D].level) {
            StartPattern();
            ClearBufferedPress();
            pattern = k236D;
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
    if (m_sealLevel < 1 && (m_command == kCmdDashLeft || m_command == kCmdDashRight)) {
        if (y < 0.0 && m_airDashes < (m_warmUp > 2) + 1 + (m_warmUp > 7)) {
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) < 0.0 || 0.0 == (*m_opponent)->x - x && facing == (1 - (m_command << 1)) * -1) && m_patterns[pattern].cancelLevel <= m_patterns[kAirDashForward].level && pattern != kRecoilGuardAir && y < -40.0 && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                pattern = kAirDashForward;
                FaceOpponent();
                m_airDashes++;
                m_airActions++;
                m_bufferedPress = 0;
                return;
            }
            if ((((*m_opponent)->x - x) * (1 - (m_command << 1)) > 0.0 || 0.0 == (*m_opponent)->x - x && facing == 1 - (m_command << 1)) && m_patterns[pattern].cancelLevel <= m_patterns[kAirDashBack].level && pattern != kRecoilGuardAir && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
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
        if (y < 0.0) {
            if (m_patterns[pattern].cancelLevel <= m_patterns[kJumpA].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                if (pattern == kDashForward) {
                    pattern = kDashJumpA;
                    return;
                }
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
                if (pattern == kDashForward) {
                    pattern = kDashJumpB;
                    return;
                }
                pattern = kJumpB;
            }
            return;
        }
        if ((m_inputY == 1 || (m_bufferedPress & kInputDown) != 0 || (m_dashBufferedPress & kInputDown) != 0) && (m_patterns[pattern].cancelLevel <= m_patterns[k2B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && pattern != k5BClose || m_patterns[pattern].cancelLevel <= m_patterns[k2B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_warmUp > 0) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
            StartPattern();
            ClearBufferedPress();
            pattern = k2B;
            return;
        }
        if (m_inputY == 0 || (m_bufferedPress & kInputDown) == 0 || (m_dashBufferedPress & kInputDown) == 0) {
            if (m_patterns[pattern].cancelLevel <= m_patterns[k6B].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_inputX == facing && m_warmUp > 1 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k6B;
                return;
            }
            if (m_patterns[pattern].cancelLevel <= m_patterns[k5BClose].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && x - (*m_opponent)->x > -80.0 && x - (*m_opponent)->x < 80.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k5BClose;
                return;
            }
            if (pattern == k2B && m_warmUp > 1 || m_patterns[pattern].cancelLevel <= m_patterns[k5BFar].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                pattern = k5BFar;
                return;
            }
        }
    }
    if (m_pressC == 1 || (m_bufferedPress & kInputC) != 0 || (m_dashBufferedPress & kInputC) != 0) {
        if (y < 0.0) {
            if (m_inputX == facing && m_inputY == 0 && x - (*m_opponent)->x > -100.0 && x - (*m_opponent)->x < 100.0 && (*m_opponent)->y < 0.0 && m_patterns[pattern].cancelLevel <= m_patterns[kAirThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                if (pattern == kDashForward) {
                    pattern = kDashJumpC;
                    return;
                }
                pattern = kAirThrow;
                return;
            }
            if ((m_patterns[pattern].cancelLevel <= m_patterns[kJumpC].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && pattern != k5BFar || m_patterns[pattern].cancelLevel <= m_patterns[kJumpC].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_warmUp > 4) && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
                StartPattern();
                ClearBufferedPress();
                if (pattern == kDashForward) {
                    pattern = kDashJumpC;
                    return;
                }
                if (pattern == k5BFar) {
                    pattern = k5BFarC;
                    return;
                }
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
            if (m_inputX != 0 && (*m_opponent)->y == 0.0 && x - (*m_opponent)->x > -30.0 && x - (*m_opponent)->x < 30.0 && m_patterns[pattern].cancelLevel <= m_patterns[kThrow].level && ((*m_opponent)->pattern < kFirstHitReaction || (*m_opponent)->pattern > kGuardAir) && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction) && (*m_opponent)->y == 0.0) {
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
    if (m_sealLevel < 2 && (m_pressD == 1 || (m_bufferedPress & kInputD) != 0 || (m_dashBufferedPress & kInputD) != 0) && m_patterns[pattern].cancelLevel <= m_patterns[k5D].level && (m_patterns[pattern].frames[frame].flagsB0 & kStateCancellable) > 0 && m_warmUp < 9 && y == 0.0 && (pattern >= kFirstCharacterAction && m_attackResult >= 2 && m_attackResult != 6 || pattern < kFirstCharacterAction)) {
        StartPattern();
        ClearBufferedPress();
        pattern = k5D;
        if (m_inputY == 1) {
            pattern = k2D;
        }
    }
}

void CNayuki::DrawGauge()
{
    RECT src; // the part of the sprite drawn
    EffectFrame sprite; // the frame drawn
    RECT dst; // where on the screen

    sprite = *anims[0x2c].frames;
    src = MakeRect(0, 0, sprite.width, sprite.height);
    if (m_side == 0) {
        dst = MakeRect(2 - sprite.x, 0xbf - sprite.y, sprite.width, sprite.height);
    } else {
        dst = MakeRect(sprite.x + 0x118, 0xbf - sprite.y, sprite.width, sprite.height);
    }
    m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
    sprite = *(EffectFrame*)PTRAT((char*)&anims[m_warmUp].frameCount + 0x114);
    src = MakeRect(0, 0, sprite.width, sprite.height);
    if (m_side == 0) {
        dst = MakeRect(2 - sprite.x, 0xbf - sprite.y, sprite.width, sprite.height);
    } else {
        dst = MakeRect(0x118 - sprite.x, 0xbf - sprite.y, sprite.width, sprite.height);
    }
    m_graphics->Blit(dst, surfaces[sprite.surface], src, colorKey, 0);
}

void CNayuki::PreUpdate()
{
}

void CNayuki::SpawnObject(EffectDesc* desc)
{
    RemoveObject(m_objectHead);
    CPlayer::SpawnObject(desc);
}

void CNayuki::ReadCommand()
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
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 0x3e8) {
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
        if ((input & kInputDirections) == kInputDown && step == 0 && m_gauge >= 0x3e8) {
            step = 1;
        }
    }
    step = 0;
    pos = m_inputPos + (kInputHistoryLength - 90);
    for (; pos < m_inputPos + kInputHistoryLength; pos++) {
        input = m_inputHistory[(pos - (pos >= kInputHistoryLength) * kInputHistoryLength)];
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 6) {
            m_command = kCmdC236236;
            return;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 5) {
            step = 6;
        }
        if ((input & kInputDirections) == kInputDown && step == 4) {
            step = 5;
        }
        if ((input & kInputDirections) == (facing == -1) + 1 && step == 3) {
            step = 4;
        }
        if ((input & kInputDirections) == (facing == -1) + 5 && step == 2) {
            step = 3;
        }
        if ((input & kInputDirections) == kInputDown && step == 1) {
            step = 2;
        }
        if ((input & kInputC) != 0 && step == 0 && m_gauge == 0xbb8) {
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

void CNayuki::CpuInput()
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
    if ((*m_opponent)->pattern >= kFirstHitReaction && (*m_opponent)->pattern < kFirstGuard && pattern == k41236A && m_hitsLeft > 1) {
        return;
    }
    if (pattern == kRecoilGuardStand && timer < 6) {
        if ((*m_opponent)->pattern != 0xc8 && (*m_opponent)->pattern != 0xcc && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && dx < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 3.0f) {
            m_pressA = 1;
            m_inputY = 1;
            return;
        }
        if (((*m_opponent)->pattern == 0xc9 || (*m_opponent)->pattern == 0xca || (*m_opponent)->pattern == 0xcd) && (*m_opponent)->pattern < 0xfa && (*m_opponent)->y == 0.0 && (*m_opponent)->m_hitsLeft == 0 && dx > 40.0 && dx < 80.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 2) {
            m_pressB = 1;
            m_inputY = 0;
            return;
        }
    }
    if (pattern == kRecoilGuardStand || pattern == kRecoilGuardCrouch) {
        if (dx < 100.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd41236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 3.0f && m_rfGauge > 500.0) {
                m_command = kCmd623C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 1.0f && m_gauge == 0xbb8) {
                m_command = kCmdC236236;
                return;
            }
        }
        if (dx < 220.0) {
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_rfGauge > 500.0) {
                m_command = kCmd41236C;
                return;
            }
            if ((WORD)Random(0, 0x64) < m_cpuSkill * 2 && m_rfGauge > 500.0) {
                m_command = kCmd236C;
                return;
            }
        }
    }
    if (pattern == kRecoilGuardAir && frame == 1 && timer == 0) {
        if ((WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_cpuAction = 3;
            return;
        }
        if (y - (*m_opponent)->y > -40.0 && y - (*m_opponent)->y < 40.0 && dx < 60.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressA = 1;
            return;
        }
        if (dy < 50.0 && dx < 50.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressB = 1;
            return;
        }
        if (dy < 50.0 && dx < 130.0 && (WORD)Random(0, 0x64) < m_cpuSkill * 5.0f) {
            m_pressC = 1;
            m_inputY = 0;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y == 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 4 && m_rfGauge > 500.0) {
            m_command = kCmd41236C;
            return;
        }
        if (m_cpuRoll < 0xa && m_rfGauge > 500.0) {
            m_command = kCmd623C;
            return;
        }
        if (m_cpuRoll < 0xd && m_rfGauge > 500.0) {
            m_command = kCmd236C;
            return;
        }
        if (m_cpuRoll < 0x11 && m_cpuRoll > 0xc && m_gauge >= 0x3e8) {
            m_command = (WORD)Random(0, 2) * 0x6e;
            return;
        }
        if (m_cpuRoll < 0x10 && m_cpuRoll > 0x12 && m_gauge == 0xbb8) {
            m_command = kCmdC236236;
            return;
        }
    }
    if (((*m_opponent)->pattern == kRecoilGuardStand || (*m_opponent)->pattern == kRecoilGuardCrouch || (*m_opponent)->pattern == kRecoilGuardAir) && y < 0.0 && (WORD)Random(0, 0x64) < 15.0f * m_cpuSkill && m_cpuAction != 2 && (*m_opponent)->m_freezeTime == 0) {
        m_cpuRoll = (WORD)Random(0, 0x64);
        if (m_cpuRoll < 0x3c) {
            m_cpuAction = 2;
            return;
        }
    }
    if ((m_rfGauge > 500.0 || m_rfBlue > 0) && (WORD)Random(0, 0x64) < 8.0f * m_cpuSkill && (*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kAirRecoveryForward && (pattern == k623A || pattern == k623B || pattern == k623C || pattern == k623B || pattern == k41236A || pattern == k41236B)) {
        m_command = kCmd22C;
        return;
    }
    if (pattern == kAirDashForward || pattern == kAirDashBack) {
        m_pressA = 1;
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
        if ((pattern == kJump || pattern == kJumpForward || pattern == kJumpBack) && (y < -60.0 || m_warmUp > 6)) {
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
        if (pattern == kJumpB) {
            m_cpuAction = 0;
        }
        m_pressB = 1;
        return;
    }
    if (m_cpuAction == 7 && pattern < kFirstHitReaction) {
        m_cpuAction = 8;
        return;
    }
    if (m_cpuAction == 8 && pattern == kFall) {
        if (pattern == kJumpA) {
            m_cpuAction = 0;
        }
        m_pressA = 1;
        return;
    }
    if (m_cpuAction == 9 && pattern < kFirstHitReaction) {
        m_inputY = 1;
        m_pressC = 1;
        if (pattern == k2C) {
            m_cpuAction = 0;
        }
        return;
    }
    if (m_cpuAction == 0xa && pattern < kFirstHitReaction) {
        m_inputY = 0;
        m_pressC = 1;
        if (pattern == k5C) {
            m_cpuAction = 0;
        }
        return;
    }
    if ((pattern == k236A || pattern == k236C) && (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kAirRecoveryForward) {
        if (m_cpuRoll < 0x12c && (*m_opponent)->y == 0.0) {
            m_cpuAction = 7;
            return;
        }
        if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && (*m_opponent)->y == 0.0) {
            m_cpuAction = 4;
            return;
        }
        if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x226 && (*m_opponent)->y < 0.0 && dx < 60.0) {
            m_cpuAction = 9;
            return;
        }
        if (m_cpuRoll > 0x226 && m_cpuRoll < 0x28a && (*m_opponent)->y < 0.0 && dx < 100.0) {
            m_cpuAction = 0xa;
            return;
        }
    }
    if (pattern == k214Stance) {
        if (m_cpuRoll < 0x12c && dx < 120.0 && ((*m_opponent)->pattern > kLastSharedAction || (*m_opponent)->y < 0.0)) {
            m_pressA = 1;
            return;
        }
        if (m_cpuRoll < 0x1c2 && m_cpuRoll > 0x12c && (*m_opponent)->y == 0.0 && dx < 160.0) {
            m_pressB = 1;
            return;
        }
        if (m_cpuRoll < 0x258 && m_cpuRoll > 0x1c2 && (*m_opponent)->y == 0.0 && dx < 100.0) {
            m_pressC = 1;
            return;
        }
        if (m_cpuRoll < 0x28a && m_cpuRoll > 0x258 && (*m_opponent)->y == 0.0 && m_warmUp < 9) {
            m_pressD = 1;
            return;
        }
    }
    if (m_attackResult > 1 && m_hitstop == 0 && (WORD)Random(0, 0x64) < m_cpuSkill * 25.0f && m_cpuAction == 0 && m_cpuAction != 2) {
        m_cpuRoll = (WORD)Random(0, 0x3e8);
        if (pattern == k5A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 80.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
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
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 7;
                }
                return;
            }
        }
        if (pattern == k5BClose) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_command = kCmd623A;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12b && m_cpuRoll < 0x258) {
                m_pressD = 1;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x257 && m_cpuRoll < 0x2bc) {
                m_inputY = -1;
                m_inputX = facing;
                return;
            }
            if (m_cpuRoll < 0x15e && m_attackResult == 3) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x1f4 && m_attackResult == 3) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x226 && m_warmUp > 2) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x1f4) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x257) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 7;
                }
                return;
            }
        }
        if (pattern == k5BFar) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c && m_attackResult == 3) {
                m_pressC = 1;
                return;
            }
            if ((*m_opponent)->y < 0.0 && m_cpuRoll > 0x12c && m_cpuRoll < 0x140 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 3) + kCmd214214A;
                return;
            }
            if (m_cpuRoll < 0x96 && dx < 80.0) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x96) {
                if (m_cpuRoll < (y < 0.0) * 0x96 + 0x15e) {
                    m_pressC = 1;
                    m_inputY = 0;
                    return;
                }
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x190) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < m_warmUp * 0xa + 0x1c2) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x262 && y < 0.0) {
                m_command = kCmd22C;
                return;
            }
        }
        if (pattern == k5C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x96) {
                m_command = kCmd236A;
                return;
            }
            if (m_cpuRoll > 0x96 && m_cpuRoll < 0x12c) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2) {
                m_command = kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x1f4 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x226 && m_attackResult == 3 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd214214A;
                return;
            }
            if (m_cpuRoll > 0x226 && m_cpuRoll < 0x230 && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
            if (m_cpuRoll > 0x38e) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
        }
        if (pattern == k2A) {
            if ((*m_opponent)->y < 0.0 && m_cpuRoll < 0x12c) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 80.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 1;
                return;
            }
            if (dx < 50.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                m_inputY = 0;
                return;
            }
            if (dx < 125.0 && m_cpuRoll > 0x18f && m_cpuRoll < 0x2bc) {
                m_pressB = 1;
                m_inputY = (WORD)Random(0, 2) == 0 ? 1 : 0;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x2bb) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 3) == 0) {
                    m_cpuAction = 7;
                }
                return;
            }
        }
        if (pattern == k2B) {
            if (m_cpuRoll < 0x15e && m_attackResult == 3) {
                m_pressC = 1;
                m_inputY = 1;
                return;
            }
            if (m_cpuRoll > 0x15e && m_cpuRoll < 0x1f4 && m_attackResult == 3) {
                m_pressC = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x1f4 && m_cpuRoll < 0x226 && m_warmUp > 2) {
                m_pressB = 1;
                m_inputY = 0;
                m_inputX = facing;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x1f4) {
                m_pressB = 1;
                m_inputY = 0;
                return;
            }
            if (m_cpuRoll > 0x384) {
                m_cpuAction = 4;
                m_inputY = -1;
                m_inputX = (WORD)Random(0, 2) - 1;
                return;
            }
            if (m_cpuRoll > 0x257) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 2) == 0) {
                    m_cpuAction = 7;
                }
                return;
            }
        }
        if (pattern == k2C) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190 && m_attackResult == 3) {
                m_inputX = facing;
                m_inputY = -1;
                return;
            }
            if (m_cpuRoll > 0x190 && m_cpuRoll < 0x320 && m_attackResult == 3 && m_warmUp < 9) {
                m_pressD = 1;
                return;
            }
            if (m_cpuRoll > 0 && m_cpuRoll < 0x96) {
                m_command = kCmd236A;
                if ((*m_opponent)->y < 0.0) {
                    m_command = kCmd236B;
                }
                return;
            }
            if (m_cpuRoll > 0x96 && m_cpuRoll < 0x12c) {
                m_command = kCmd214A;
                return;
            }
            if (m_cpuRoll > 0x12c && m_cpuRoll < 0x1c2 && (*m_opponent)->y == 0.0) {
                m_command = kCmd41236A;
                return;
            }
            if (m_cpuRoll > 0x1c2 && m_cpuRoll < 0x258 && m_rfGauge > 500.0) {
                m_command = kCmd22C;
                return;
            }
            if (m_cpuRoll > 0x258 && m_cpuRoll < 0x64a && m_gauge >= 0x3e8) {
                m_command = (WORD)Random(0, 2) + kCmd236236A;
                return;
            }
        }
        if (pattern == kJumpA) {
            if (dx < 60.0 && dy < 30.0 && m_cpuRoll < 0x190) {
                m_pressA = 1;
                return;
            }
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
            if (m_cpuRoll > 0x320) {
                m_cpuAction = 1;
                if ((WORD)Random(0, 4) == 0) {
                    m_cpuAction = 3;
                }
                return;
            }
        }
        if (pattern == kJumpB) {
            if (m_cpuRoll > 0 && m_cpuRoll < 0x190) {
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
            if (m_cpuRoll > 0x258) {
                m_cpuAction = 3;
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
                if (dx < 35.0 && m_cpuRoll < 0xf) {
                    m_pressA = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 50.0 && m_cpuRoll < 0x1e) {
                    m_pressA = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 90.0 && dx > 60.0 && m_cpuRoll < 0x4b && m_cpuRoll < 0x1e) {
                    m_pressB = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 150.0 && 0x46 - (m_warmUp > 6) * 0x14 < dx && m_cpuRoll < 0x87 && m_cpuRoll < 0x4b) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 150.0 && 0x46 - (m_warmUp > 6) * 0x14 < dx && m_cpuRoll < 0x87 && m_cpuRoll < 0xa0 && m_warmUp > 2) {
                    m_pressB = 1;
                    m_inputY = 0;
                    return;
                }
                if (dx < 150.0 && dx > 90.0 && m_cpuRoll < 0xf0 && m_cpuRoll > 0xa0) {
                    m_pressC = 1;
                    m_inputY = 1;
                    return;
                }
                if (dx < 260.0 && dx > 100.0 && m_cpuRoll < 0x154 && m_cpuRoll > 0x12c) {
                    m_command = (WORD)Random(0, 3) + kCmd236A;
                    return;
                }
                if (dx < 200.0 && dx > 70.0 && m_cpuRoll < m_warmUp * 5 + 0x168 && m_cpuRoll > 0x15e) {
                    m_command = (WORD)Random(0, 3) + kCmd41236A;
                    return;
                }
                if (dx < 200.0 && dx > 70.0 && m_cpuRoll < m_warmUp * 5 + 0x1a4 && m_cpuRoll > 0x19a && m_warmUp > 3 && m_rfGauge > 500.0) {
                    m_command = kCmd623B;
                    return;
                }
                if (dx < 200.0 && dx < 100.0 && m_cpuRoll < m_warmUp * 2 + 0x1e0 && m_cpuRoll > 0x1d6 && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd41236C;
                    return;
                }
                if (dx < 200.0 && dx < 70.0 && m_cpuRoll < m_warmUp * 2 + 0x1fe && m_cpuRoll > 0x1f4 && m_rfGauge > 500.0 && (*m_opponent)->pattern > kLastSharedAction) {
                    m_command = kCmd623C;
                    return;
                }
                if (m_cpuRoll > 0x212) {
                    if (m_cpuRoll < ((*m_opponent)->pattern > kHitCrouchHeavy && (*m_opponent)->pattern < kThrownStandHigh && (*m_opponent)->pattern != kWakeUp) * 0x96 + 0x212 + ((*m_opponent)->pattern > 0x5f && (*m_opponent)->pattern < kThrownStandHigh && (*m_opponent)->pattern != kWakeUp) * 0x12c + (dx > 180.0) * 0x14 && m_warmUp < 9) {
                        m_pressD = 1;
                        return;
                    }
                }
                if (m_cpuRoll < 0x2a && m_cpuRoll > 0x2f) {
                    m_command = facing;
                    m_cpuAction = 5;
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
                    if (dx < 80.0 && dy < 70.0 && m_cpuRoll < 0x14) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                }
                if ((*m_opponent)->vy > 0.0) {
                    if (dx < 70.0 && dy > 40.0 && dy < 90.0 && m_cpuRoll < 0x32 && (m_rfGauge > 500.0 || m_rfBlue > 0)) {
                        m_command = kCmd623A;
                        return;
                    }
                    if (dx < 80.0 && dy < 150.0 && dy > 80.0 && m_cpuRoll < 0x5a) {
                        m_pressC = 1;
                        m_inputY = 1;
                        return;
                    }
                    if (dx < 150.0 && dx > 100.0 && dy < 120.0 && dy > 90.0 && m_cpuRoll < 0x6e && m_cpuRoll > 0x5a) {
                        m_pressB = 1;
                        m_inputY = 0;
                        return;
                    }
                }
            }
        }
        if (y < 0.0 && m_cpuAction != 3) {
            if ((*m_opponent)->y == 0.0) {
                if (dx < 70.0 && dy < 50.0 && m_cpuRoll < 0xc8) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 70.0 && dy < 100.0) {
                    if (m_cpuRoll < ((*m_opponent)->y == 0.0) * 0x64 + 0xfa) {
                        m_pressB = 1;
                        return;
                    }
                }
                if (dx < 110.0 && dy > 60.0 && dy < 80.0 && vy > 0.0 && (*m_opponent)->y > y && m_cpuRoll > 0x1f4 && m_cpuRoll < 0x26c) {
                    m_pressC = 1;
                    return;
                }
            }
            if ((*m_opponent)->y < 0.0) {
                if (dx < 60.0 && dy > 60.0 && m_cpuRoll < 0x6e) {
                    m_pressB = 1;
                    return;
                }
                if (dx < 150.0 && dx > 100.0 && dy < 80.0 && (*m_opponent)->y < y && m_cpuRoll < 0xfa && m_cpuRoll > 0x6e) {
                    m_pressC = 1;
                    return;
                }
            }
        }
    }
    if (pattern < kFirstHitReaction && ((*m_opponent)->pattern > kLastHitReaction && (*m_opponent)->pattern < kGuardAir || (*m_opponent)->pattern > kLastFreeAction && (*m_opponent)->pattern < kHitAir) && y == 0.0 && (WORD)Random(0, 0x64) < 3.0f * m_cpuSkill) {
        if (dx < 150.0) {
            m_command = facing == 1;
        }
        return;
    }
    if (pattern < kFirstHitReaction && y == 0.0 && (WORD)Random(0, 0x64) < 1.0f * m_cpuSkill && dx > 80.0 && dx < 160.0) {
        if (dx < 150.0) {
            m_command = facing == 1;
        }
        return;
    }
    if ((WORD)Random(0, 0x3e8) < 2) {
        m_cpuAction = 4;
        return;
    }
    if ((WORD)Random(0, 0x64) < 2) {
        if ((WORD)Random(0, 0x64) < 4.0f * m_cpuSkill) {
            m_cpuAction = 3;
        } else {
            m_cpuAction = 0;
        }
        if (dx > 240.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx < 80.0 && y == 0.0 && (WORD)Random(0, 0x64) < 2) {
            m_inputX = 0;
            m_inputY = -1;
            return;
        }
        if (dx < 140.0 && dx > 100.0 && y == 0.0) {
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
    if ((WORD)Random(0, 0x64) < 0x28 && dx < 100.0) {
        if (facing == 1) {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x5a;
        } else {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x5a;
        }
    }
    if ((WORD)Random(0, 0x64) < 0x50) {
        if (facing == 1) {
            m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x5a;
        } else {
            m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x5a;
        }
        return;
    }
    if (facing == -1) {
        m_cpuWalkRight = (WORD)Random(0, 0xc8) + 0x5a;
        return;
    }
    m_cpuWalkLeft = (WORD)Random(0, 0xc8) + 0x5a;
}

void CNayuki::UpdateObjects()
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
            case kObjAirDashStep:
                if (m_objects[slot].frame == 5 && m_patternVar1 == 0) {
                    m_patternVar1 = 1;
                    effect.type = 0;
                    effect.x = (double)((int)m_objects[slot].x + m_objects[slot].facing * 0x17);
                    effect.y = (double)((int)m_objects[slot].y - 9);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.sound = 2;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objects[slot].vx = -0.9;
                    m_objects[slot].vy = -1.0;
                    m_objects[slot].ay = 0.035;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 7) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj236A:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 0.3;
                    m_objects[slot].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vy += 0.045;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].frame = 1;
                        m_objects[slot].layer = 1;
                    }
                }
                if (m_objects[slot].frame > 4 && m_objects[slot].vy + m_objects[slot].y > 0.0) {
                    m_objects[slot].shadow = 0;
                }
                if (m_objects[slot].scale == 0 && frame == 6 && pattern == k236A && m_objects[slot].frame < 5 && (x - m_objects[slot].x < 60.0 && x - m_objects[slot].x > 0.0 && facing == -1 || x - m_objects[slot].x > -60.0 && x - m_objects[slot].x < 0.0 && facing == 1)) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 5;
                    effect.type = 0;
                    effect.x = (double)((int)x + facing * 0x1e);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.sound = 2;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objects[slot].vx = 1.8;
                    m_objects[slot].vy = -0.9;
                    m_objects[slot].ay = 0.025;
                }
                if (m_objects[slot].frame > 4) {
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                }
                if (m_objects[slot].attackResult > 1) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].frame = 6;
                    m_objects[slot].vy = -1.5;
                    m_objects[slot].vx = -m_objects[slot].vx * 0.5;
                    m_objects[slot].ay = 0.035;
                }
                if (m_objects[slot].frame == 7) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].y > 60.0) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame == 3) {
                        RemoveObject(slot);
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj236B:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 0.3;
                    m_objects[slot].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vy += 0.045;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].frame = 1;
                        m_objects[slot].layer = 1;
                    }
                }
                if (frame == 6 && pattern == k236B && m_objects[slot].frame < 5 && (x - m_objects[slot].x < 60.0 && x - m_objects[slot].x > 0.0 && facing == -1 || x - m_objects[slot].x > -60.0 && x - m_objects[slot].x < 0.0 && facing == 1)) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 5;
                    effect.type = 0;
                    effect.x = (double)((int)x + facing * 0x1e);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.sound = 2;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objects[slot].vx = 2.0;
                    m_objects[slot].vy = -3.5;
                    m_objects[slot].ay = 0.025;
                }
                if (m_objects[slot].frame > 4) {
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                }
                if (m_objects[slot].attackResult > 1) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].frame = 6;
                    m_objects[slot].vy = -1.5;
                    m_objects[slot].vx = -m_objects[slot].vx * 0.5;
                    m_objects[slot].ay = 0.035;
                }
                if (m_objects[slot].frame == 7) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].y > 60.0) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame == 3) {
                        RemoveObject(slot);
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObj236C:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 5;
                    m_objects[slot].vx = 0.3;
                    m_objects[slot].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vy += 0.045;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].frame = 1;
                        m_objects[slot].layer = 1;
                    }
                }
                if (m_objects[slot].frame > 4 && m_objects[slot].vy + m_objects[slot].y > 0.0) {
                    m_objects[slot].shadow = 0;
                }
                if (frame == 6 && pattern == k236C && m_objects[slot].frame < 5 && (x - m_objects[slot].x < 60.0 && x - m_objects[slot].x > 0.0 && facing == -1 || x - m_objects[slot].x > -60.0 && x - m_objects[slot].x < 0.0 && facing == 1)) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame = 5;
                    effect.type = 0;
                    effect.x = (double)((int)x + facing * 0x1e);
                    effect.y = (double)((int)y - 0x14);
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.sound = 2;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objects[slot].vx = 2.2;
                    m_objects[slot].vy = -1.6;
                    m_objects[slot].ay = 0.025;
                }
                if (m_objects[slot].frame > 4) {
                    m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                }
                if (m_objects[slot].hitsLeft == 0 && m_objects[slot].attackResult > 1) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].frame = 6;
                    m_objects[slot].vy = -1.5;
                    m_objects[slot].vx = -m_objects[slot].vx * 0.5;
                    m_objects[slot].ay = 0.035;
                }
                if (m_objects[slot].frame == 7) {
                    m_objects[slot].scale = 1;
                }
                if (m_objects[slot].y > 60.0) {
                    RemoveObject(slot);
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 2) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame == 3) {
                        RemoveObject(slot);
                    }
                    if (m_objects[slot].frame == 6) {
                        m_objects[slot].frame--;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjUnused194:
                if (pattern == kUnusedFe) {
                    m_objects[slot].x = x;
                    m_objects[slot].y = y;
                } else {
                    m_objects[slot].vx = 1.7;
                    m_objects[slot].vy = -1.7;
                }
                if (m_objects[slot].y < m_game->m_view.top - 0x28) {
                    RemoveObject(slot);
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
            case kObj214214EmitterEnd:
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
            case kObj236236ABomb:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.3;
                    m_objects[slot].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vy += 0.045;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].frame = 1;
                        m_objects[slot].layer = 1;
                    }
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0x1e) {
                    ShakeScreen(5, 0);
                    effect.type = 0x199;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
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
            case kObj236236BBomb:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.3;
                    m_objects[slot].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vy += 0.045;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].frame = 1;
                        m_objects[slot].layer = 1;
                    }
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0x18) {
                    ShakeScreen(0xa, 0);
                    effect.type = 0x19a;
                    effect.x = (double)((int)m_objects[slot].x + 0x28);
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_playVoice = 1;
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0x1e) {
                    effect.type = 0x19a;
                    effect.facing = facing;
                    effect.scale = 2;
                    effect.layer = 1;
                    effect.x = (double)((int)m_objects[slot].x - 0x28);
                    effect.y = (double)(int)m_objects[slot].y;
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
            case kObj236236CBomb:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 0.3;
                    m_objects[slot].vy = -1.2;
                    m_playVoice = 0;
                }
                if (m_objects[slot].frame == 0) {
                    m_objects[slot].vy += 0.045;
                    if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                        m_objects[slot].y = 0.0;
                        m_objects[slot].vy = 0.0;
                        m_objects[slot].vx = 0.0;
                        m_objects[slot].frame = 1;
                        m_objects[slot].layer = 1;
                    }
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0x13) {
                    ShakeScreen(0xf, 0);
                    effect.type = 0x19b;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)((int)m_objects[slot].y + 0xf);
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_playVoice = 1;
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0x18) {
                    effect.type = 0x19b;
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.x = (double)((int)m_objects[slot].x + 0x32);
                    effect.y = (double)((int)m_objects[slot].y - 0xa);
                    SpawnObject(&effect);
                }
                if (m_objects[slot].frame == 5 && m_objects[slot].timer == 0x1e) {
                    effect.type = 0x19b;
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    effect.x = (double)((int)m_objects[slot].x - 0x32);
                    effect.y = (double)((int)m_objects[slot].y - 0xa);
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
            case kObjExplosion1:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 1;
                }
                if (m_objects[slot].frame < 0xc && (WORD)Random(0, 0x64) < 0xe) {
                    effect.type = 0x19c;
                    effect.x = (double)(int)(m_objects[slot].x - 50.0 + (WORD)Random(0, 0x64));
                    effect.y = (double)(int)(m_objects[slot].y - (WORD)Random(0, 0x64));
                    effect.scale = 2;
                    effect.facing = facing;
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
            case kObjExplosion2:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 1;
                }
                if (m_objects[slot].frame < 0xc && (WORD)Random(0, 0x64) < 0xc) {
                    effect.type = 0x19c;
                    effect.x = (double)(int)(m_objects[slot].x - 50.0 + (WORD)Random(0, 0x64));
                    effect.y = (double)(int)(m_objects[slot].y - (WORD)Random(0, 0x64));
                    effect.scale = 2;
                    effect.facing = facing;
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
            case kObjExplosion3:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 1;
                }
                if (m_objects[slot].frame < 0xc && (WORD)Random(0, 0x64) < 0xa) {
                    effect.type = 0x19c;
                    effect.x = (double)(int)(m_objects[slot].x - 50.0 + (WORD)Random(0, 0x64));
                    effect.y = (double)(int)(m_objects[slot].y - (WORD)Random(0, 0x64));
                    effect.scale = 2;
                    effect.facing = facing;
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
            case kObjExplosionSpark:
                if (m_objectVar1[slot] <= 0) {
                    effect.type = 0x22;
                    effect.x = (double)((int)m_objects[slot].x + (0x14 - (WORD)Random(0, 0x28)) * facing);
                    effect.y = (double)((int)m_objects[slot].y + 0x14 - (WORD)Random(0, 0x28));
                    effect.scale = 2;
                    effect.layer = 1;
                    m_game->CreateEffect((EffectDesc*)&effect);
                    m_objectVar1[slot] = 2;
                }
                m_objectVar1[slot]--;
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
            case kObj214214Upper:
                if ((pattern == k214214A || pattern == k214214B || pattern == k214214C) && frame < 8) {
                    m_objects[slot].x = x;
                    m_objects[slot].y = y - 80.0;
                } else {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].pattern = kObj214214EmitterEnd;
                }
                m_upperEmitterX = (int)m_objects[slot].x;
                m_upperEmitterY = (int)m_objects[slot].y;
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] <= 0) {
                    effect.type = 0x19f;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectVar1[slot] = 3;
                    if (pattern == k214214B) {
                        m_objectVar1[slot] = 2;
                    }
                    if (pattern == k214214C) {
                        m_objectVar1[slot] = 1;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objectVar1[slot]--;
                    }
                }
                break;
            case kObj214214Lower:
                if ((pattern == k214214A || pattern == k214214B || pattern == k214214C) && frame < 8) {
                    m_objects[slot].x = x;
                    m_objects[slot].y = y;
                } else {
                    m_objects[slot].frame = 0;
                    m_objects[slot].timer = 0;
                    m_objects[slot].vx = 0.0;
                    m_objects[slot].vy = 0.0;
                    m_objects[slot].pattern = kObj214214EmitterEnd;
                }
                m_lowerEmitterX = (int)m_objects[slot].x;
                m_lowerEmitterY = (int)m_objects[slot].y;
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0 && m_objectVar1[slot] <= 0) {
                    effect.type = 0x1a0;
                    effect.x = (double)(int)m_objects[slot].x;
                    effect.y = (double)(int)m_objects[slot].y;
                    effect.scale = 2;
                    effect.facing = facing;
                    effect.layer = 1;
                    SpawnObject(&effect);
                    m_objectVar1[slot] = 3;
                    if (pattern == k214214B) {
                        m_objectVar1[slot] = 2;
                    }
                    if (pattern == k214214C) {
                        m_objectVar1[slot] = 1;
                    }
                }
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame >= frameCount) {
                        m_objects[slot].frame = 0;
                        m_objectVar1[slot]--;
                    }
                }
                break;
            case kObj214214UpperHit:
                if (pattern == k214214A || pattern == k214214B || pattern == k214214C) {
                    m_objects[slot].x = m_upperEmitterX;
                    m_objects[slot].y = m_upperEmitterY;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 2;
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
            case kObj214214LowerHit:
                if (pattern == k214214A || pattern == k214214B || pattern == k214214C) {
                    m_objects[slot].x = m_lowerEmitterX;
                    m_objects[slot].y = m_lowerEmitterY;
                }
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_playVoice = 2;
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
            case kObjLv4Shed:
                if (m_objects[slot].frame == 0 && m_objectVar1[slot] == 0) {
                    m_objectVar1[slot] = 1;
                    m_objects[slot].vx = -1.9;
                    m_objects[slot].vy = -2.5;
                    m_objects[slot].ay = 0.035;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                m_objects[slot].timer++;
                if (m_objects[slot].timer >= duration) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].frame++;
                    m_objects[slot].attackResult = 0;
                    if (m_objects[slot].frame == 7) {
                        m_objects[slot].scale = 1;
                    }
                    if (m_objects[slot].frame >= frameCount) {
                        RemoveObject(slot);
                    }
                }
                break;
            case kObjStanceBBack:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 0.3;
                    m_objects[slot].vy = -3.5;
                    m_objects[slot].ay = 0.045;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                    m_objects[slot].shadow = 0;
                }
                if (m_objects[slot].attackResult > 1) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].vy = -1.5;
                    m_objects[slot].vx = -m_objects[slot].vx * 0.5;
                    m_objects[slot].ay = 0.035;
                }
                if (m_objects[slot].y > 60.0) {
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
            case kObjStanceB:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 0.8;
                    m_objects[slot].vy = -3.5;
                    m_objects[slot].ay = 0.045;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                    m_objects[slot].shadow = 0;
                }
                if (m_objects[slot].attackResult > 1) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].vy = -1.5;
                    m_objects[slot].vx = -m_objects[slot].vx * 0.5;
                    m_objects[slot].ay = 0.035;
                }
                if (m_objects[slot].y > 60.0) {
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
            case kObjStanceBForward:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].hitsLeft = 1;
                    m_objects[slot].vx = 1.3;
                    m_objects[slot].vy = -3.5;
                    m_objects[slot].ay = 0.045;
                }
                m_objects[slot].vy = m_objects[slot].vy + m_objects[slot].ay;
                if (m_objects[slot].vy + m_objects[slot].y > 0.0) {
                    m_objects[slot].shadow = 0;
                }
                if (m_objects[slot].attackResult > 1) {
                    m_objects[slot].timer = 0;
                    m_objects[slot].attackResult = 0;
                    m_objects[slot].frame = 1;
                    m_objects[slot].vy = -1.5;
                    m_objects[slot].vx = -m_objects[slot].vx * 0.5;
                    m_objects[slot].ay = 0.035;
                }
                if (m_objects[slot].y > 60.0) {
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
            case kObjState7b:
                if (m_objects[slot].frame == 0 && m_objects[slot].timer == 0) {
                    m_objects[slot].vx = 1.5;
                }
                if (pattern != kEatingJam || pattern == kEatingJam && frame > 2) {
                    RemoveObject(slot);
                }
                m_objects[slot].vy += 0.02;
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
